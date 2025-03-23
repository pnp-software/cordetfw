/**
 * @file
 * @ingroup inMngGroup
 * Definition of the InLoader component.
 *
 * The InLoader component is responsible for retrieving incoming packets which become available
 * at an InStream (see <code>CrFwInStream.h</code>).
 *
 * The InLoader component is a singleton component.
 * It is defined as an extension of the Base Component (see <code>CrFwBaseCmp.h</code>).
 * It overrides its execution procedure with the InLoader Execution Procedure shown in the figure:
 * @image html InLoaderExecution.png
 * The Load/Command Report Procedure is shown in the next figure:
 * @image html InLoaderLoadCommandReport.png
 *
 * Execution of the InLoader causes a query to be made on InStream to check whether a packet is
 * available at that InStream. If a packet is available, it is collected and if it passes
 * its acceptance check, it is loaded in an InManager. The selection of the InManager is an
 * adaptation point implemented through a function pointer defined in
 * <code>CrFwInLoaderUserPar.h</code>.
 *
 * The acceptance check is split into four sub-checks:
 * -# The type/sub-type/discriminant of the incoming command or report is valid (i.e. it is
 *    defined in <code>CrFwInFactoryUserPar.h</code> and is therefore known to the application)
 *    and is consistent with the packet length;
 * -# The InFactory has sufficient resources to provide an InCommand or InReport component
 *    to hold the command or report encapsulated in the packet;
 * -# The InCommand or InReport is successfully configured (i.e. it enters state CONFIGURED);
 * -# The InCommand or InReport is successfully loaded in the InManager.
 * .
 * Sub-checks 1, 2 and 4 are fully implemented at framework level.
 * Sub-check 3 is application-specific.
 * It is called the <i>Validity Check</i> because it verifies the validity of the parameters of the
 * incoming report or command and is implemented by a user-provided function which must conform
 * to the prototype of function pointers <code>::CrFwInRepValidityCheck_t</code> for incoming
 * reports or <code>::CrFwInCmdValidityCheck_t</code> for incoming commands.
 * The functions implementing the validity checks are defined in <code>CrFwInFactoryUserPar.h</code>.
 *
 * Function <code>::InLoaderLoadCmdRep</code> in the InLoader is responsible for checking whether the
 * sub-checks are passed.
 * For incoming commands, failure to pass a sub-check is handled as follows:
 * - Failure of sub-checks 1 and 2 is handled by calling function <code>::CrFwRepInCmdOutcomeCreFail</code>
 *   with outcome #crCmdAckCreFail.
 * - Failure of sub-check 3 is handled by calling function <code>::CrFwRepInCmdOutcome</code> with
 *   outcome #crCmdAckAccFail.
 * - Failure of sub-check 4 is handled by calling function <code>::CrFwRepInCmdOutcome</code> with
 *   outcome #crCmdAckLdFail.
 * .
 * If all sub-checks is passed, the incoming command is declared "accepted" and, if acknowledgement of
 * successful acceptance for the command was required, function
 * <code>::CrFwRepInCmdOutcome</code> is called with the outcome set to #crCmdAckAccSucc.
 *
 * For incoming reports, failure to pass a sub-check is treated as an error and is handled as follows:
 * - Failure of sub-checks 1 and 2 is handled by calling function <code>::CrFwRepInCmdOutcomeCreFail</code>
 *   with failure code #crCmdAckCreFail.
 * - Failure of sub-check 3 is handled by calling function <code>::CrFwRepErrRep</code>
 *   with failure code #crInLoaderAccFail.
 * - Failure of sub-check 4 is handled by calling function <code>::CrFwRepErrRep</code>
 *   with failure code #crInLoaderLdFail.
 * .
 *
 * <b>Mode of Use of an InLoader Component</b>
 *
 * The configuration of the InLoader components is defined statically in
 * <code>CrFwInLoaderUserPar.h</code>.
 *
 * The InLoader singleton component is created with function <code>::CrFwInLoaderMake</code>.
 * After being created, the InLoader must be initialized and reset.
 * This is done with functions <code>::CrFwCmpInit</code> and <code>::CrFwCmpReset</code>.
 * Nominally, after being initialized and reset the InManager State Machine should be
 * in state CONFIGURED (this can be checked by verifying that function <code>FwSmGetCurState</code>
 * returns CR_FW_BASE_STATE_CONFIGURED).
 *
 * After an InLoader has been configured, it can be executed by means of function
 * <code>FwSmExecute</code>.
 * Execution of an InLoader causes its Execution Procedure (see figure above) to be
 * executed.
 *
 * The InLoader should be executed either when it is known that a packet has arrived at an InStream
 * or periodically to check whether a packet is available and, if it is, to process it.
 * During one execution cycle, the InLoader processes one single packet from one single InStream.
 * The target InStream is conceptually an argument of the execution command; in practice, the target
 * InStream is passed to the InLoader through function <code>::CrFwInLoaderSetInStream</code>.
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#ifndef CRFW_INLOADER_H_
#define CRFW_INLOADER_H_

/* Include FW Profile Files */
#include "FwSmConstants.h"
#include "FwPrConstants.h"
/* Include Framework Files */
#include "CrFwConstants.h"
/* Include Configuration Files */
#include "CrFwUserConstants.h"
#include "Pckt/CrFwPcktQueue.h"

/**
 * Type for a pointer to the function which determines the re-routing destination of
 * a packet.
 * The function to determine the re-routing destination of a packet is one of the
 * adaptation points of the framework.
 * A function which implements this operation takes the packet destination as an
 * argument and returns either zero (if the argument destination is invalid) or
 * else it returns the destination to which the packet should be re-routed
 * (if the argument destination is valid).
 */
typedef CrFwDestSrc_t (*CrFwInLoaderGetReroutingDest_t)(CrFwDestSrc_t);

/**
 * Type for a pointer to the function which selects the InManager where the InCommand
 * or InReport must be loaded.
 * The function to determine the re-routing destination of a packet is one of the
 * adaptation points of the framework.
 * A function which implements this operation takes as input the service type, service sub-type,
 * and discriminant of the InReport/InCommand and a flag which indicates whether the
 * item to be loaded in the InManaher encapsulates an InCommand or an InReport.
 * The function returns the identifier of the selected InManager (see <code>::CrFwInManagerMake</code>).
 */
typedef CrFwInstanceId_t (*CrFwInLoaderGetInManager_t)(CrFwServType_t, CrFwServSubType_t,
        CrFwDiscriminant_t, CrFwCmdRepType_t);

/**
 * Factory function to retrieve the state machine implementing the InLoader singleton
 * component.
 * The first time this function is called, it creates the InLoader State Machine singleton
 * instance.
 * Subsequent calls returns the same instance.
 *
 * The first time this function is called, it returns the InLoader State Machine
 * after it has been started but before it has been initialized and
 * configured.
 * @return the descriptor of the InLoader State Machine or NULL
 * if the state machine could not be created.
 */
FwSmDesc_t CrFwInLoaderMake();

/**
 * Default implementation of the function which checks the legality of a destination and
 * returns the re-routing destination.
 * This default implementation always assumes that the argument destination is valid and
 * it returns it unchanged.
 * This default implementation is suitable for applications which are acting as gateways
 * with one level of indirection (i.e. a situation where a packet is generated by application
 * A for application B as its final destination, but the packet is sent to application C
 * as a re-routing destination so that the packet travels from A to B and then from B to C).
 * This function must conform to the prototype defined by <code>::CrFwInLoaderGetReroutingDest_t</code>.
 * @param pcktDest the packet destination.
 * @return the value of pcktDest.
 */
CrFwDestSrc_t CrFwInLoaderDefGetReroutingDestination(CrFwDestSrc_t pcktDest);

/**
 * Default implementation of the function which checks the legality of a destination and
 * returns the re-routing destination.
 * This default implementation always assumes that the argument destination is invalid and
 * therefore it always returns zero.
 * This default implementation is suitable for applications which do not perform
 * any packet re-routing (i.e. applications where a packet is always sent to its final
 * destination).
 * This function must conform to the prototype defined by <code>::CrFwInLoaderGetReroutingDest_t</code>.
 * @param pcktDest the packet destination.
 * @return the value of pcktDest.
 */
CrFwDestSrc_t CrFwInLoaderDefNoRerouting(CrFwDestSrc_t pcktDest);

/**
 * Default implementation of the function which selects the InManager to which an
 * incoming InReport or InCommand must be loaded.
 * This default implementation returns 0 if the component to be loaded is an InCommand
 * (namely if argument <code>cmdRepFlag</code> is equal to <code>::crCmdType</code>) and
 * it returns 1 if the component to be loaded is an InReport (namely if argument
 * <code>cmdRepFlag</code> is equal to <code>::crRepType</code>).
 * This function must conform to the prototype defined by <code>::CrFwInLoaderGetInManager_t</code>.
 * @param servType the service type of the incoming InCommand or InReport.
 * @param servSubType the service sub-type of the incoming InCommand or InReport.
 * @param discriminant the discriminant of the incoming InCommand or InReport.
 * @param cmdRepFlag a flag indicating whether the item to be loaded is an InCommand or an InReport.
 * @return the identifier of the InManager into which the incoming InCommand or InReport must be loaded.
 */
CrFwInstanceId_t CrFwInLoaderDefGetInManager(CrFwServType_t servType, CrFwServSubType_t servSubType,
        CrFwDiscriminant_t discriminant, CrFwCmdRepType_t cmdRepFlag);

/**
 * Set the InStream from which the packets will be retrieved the next time the InLoader
 * is executed.
 * @param inStream the InStream from which the packets will be retrieved the next time
 * the InLoader is executed.
 */
void CrFwInLoaderSetInStream(FwSmDesc_t inStream);

#endif /* CRFW_INLOADER_H_ */
