/**
 * @file
 * @ingroup inMngGroup
 * Definition of the InReport Component of the framework.
 *
 * An InReport encapsulates an incoming report in a service user application.
 * The InReport is responsible for storing the attributes of an incoming report
 * and for executing the conditional checks and actions associated to the report.
 * The behaviour of an InReport is defined by the InReport State Machine
 * (see figure below).
 *
 * <b>Mode of Use of an InReport Component</b>
 *
 * InReports are created dynamically by the InLoader when it processes an incoming
 * packet which holds a report.
 * The InReport component is created through a call to the factory function
 * <code>::CrFwInFactoryMakeInRep</code>.
 * The InLoader loads the InReport into an InManager who is then responsible for
 * executing it and, eventually, for returning it to the InFactory.
 *
 * An InReport encapsulates an incoming report of a certain kind.
 * The "kind" of an incoming command is defined by the triplet:
 * [service type, service sub-type, discriminant].
 * InReports are adapted to a certain incoming report kind by modifying the
 * implementation of the following operations:
 * - Validity Check Operation
 * - Update Action Operation
 * .
 * These operations are statically defined for each kind of InReport in
 * <code>CrFwInFactoryUserPar.h</code>.
 *
 * The Validity Check Operation is called
 * when the InReport is reset (this is, for instance, done when the
 * InReport component is created by the InFactory).
 * The operation typically returns true when the data in the InReport are valid
 * and it should return false otherwise.
 * The default implementation for this operation is provided by function
 * <code>::CrFwPrCheckAlwaysTrue</code>.
 *
 * The Update Operation is called when the InReport is executed by its
 * InManager.
 * It typically transfers the content of the InReport to the application's
 * internal data structures.
 * The default implementation for this operation is provided by
 * <code>::CrFwPrEmptyAction</code>
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

#ifndef CRFW_INREP_H_
#define CRFW_INREP_H_

/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwPrConstants.h"
/* Include configuration files */
#include "Pckt/CrFwPcktQueue.h"
#include "CrFwUserConstants.h"
/* Include framework files */
#include "CrFwConstants.h"

/**
 * Return the source of the InReport.
 * @param smDesc the descriptor of the InRep State Machine
 * @return the source of the InReport
 */
CrFwDestSrc_t CrFwInRepGetSrc(FwSmDesc_t smDesc);

/**
 * Return the group of the InReport.
 * @param smDesc the descriptor of the InRep State Machine
 * @return the group of the InReport
 */
CrFwGroup_t CrFwInRepGetGroup(FwSmDesc_t smDesc);

/**
 * Return the type of the InReport.
 * @param smDesc the descriptor of the InRep State Machine
 * @return the type of the InReport
 */
CrFwServType_t CrFwInRepGetServType(FwSmDesc_t smDesc);

/**
 * Return the sub-type of the InReport.
 * @param smDesc the descriptor of the InRep State Machine
 * @return the sub-type of the InReport
 */
CrFwServType_t CrFwInRepGetServSubType(FwSmDesc_t smDesc);

/**
 * Return the discriminant of the InReport.
 * @param smDesc the descriptor of the InRep State Machine
 * @return the discriminant of the InReport
 */
CrFwDiscriminant_t CrFwInRepGetDiscriminant(FwSmDesc_t smDesc);

/**
 * Return the sequence counter of the InReport.
 * @param smDesc the descriptor of the InRep State Machine
 * @return the sequence counter of the InReport
 */
CrFwSeqCnt_t CrFwInRepGetSeqCnt(FwSmDesc_t smDesc);

/**
 * Return the start address of the parameter area of the InReport.
 * The InReport is encapsulated in a packet.
 * The parameter area of the InReport is the part of the packet which is reserved to the
 * storage of the parameters of the InReport.
 * The parameter area consists of an uninterrupted sequence of bytes.
 * The size of the parameter area is returned by function <code>::CrFwInRepGetParLength</code>.
 * @param smDesc the descriptor of the Base State Machine of the InReport
 * @return the start address of the InReport parameter area.
 */
CrFwPckt_t CrFwInRepGetParStart(FwSmDesc_t smDesc);

/**
 * Return the length in bytes of the parameter area of the InReport.
 * The InReport is encapsulated in a packet.
 * The parameter area of the InReport is the part of the packet which is reserved to the
 * storage of the parameters of the InReport.
 * The parameter area consists of an uninterrupted sequence of bytes.
 * The start address of the parameter area is returned by function <code>::CrFwInRepGetParStart</code>.
 * @param smDesc the descriptor of the Base State Machine of the InReport
 * @return the length in bytes of the InReport parameter area
 */
CrFwPcktLength_t CrFwInRepGetParLength(FwSmDesc_t smDesc);

/**
 * Configuration check for an InReport.
 * This function executes the Validity Check of the InReport and sets the
 * action outcome to 1 if the Validity Check returns true and sets it to
 * zero if it returns false.
 * The Validity Check is implemented in a function of type <code>::CrFwInRepValidityCheck_t</code>.
 * The function is defined by the applicaiton developer in <code>::CR_FW_INREP_INIT_KIND_DESC</code>
 *
 * This function is not intended to be called by applications.
 * It is declared as a public function because it is needed by the
 * InFactory (see <code>CrFwInFactory.h</code>).
 * @param prDesc the descriptor of the InReport Configuration Procedure.
 */
void CrFwInRepConfigCheck(FwPrDesc_t prDesc);

/**
 * Return the pointer to the packet which holds the InReport.
 * The InReport is encapsulated in a packet.
 * This function returns this packet.
 * The packet is only initialized if the InReport has been correctly de-serialized.
 * This is normally the case if the InReport has been successfully returned by the InFactory.
 * The length of the packet is stored in the packet itself and can be retrieved
 * with function <code>::CrFwPcktGetLength</code>.
 * @param smDesc the descriptor of the Base State Machine of the InReport
 * @return the pointer to the packet holding the InReport.
 */
CrFwPckt_t CrFwInRepGetPckt(FwSmDesc_t smDesc);

/**
 * Convenience function to extract the InReport's packet from the descriptor
 * of the InReport's execution procedure.
 *
 * One situation where this function is useful is as follows.
 * The Update Action Operation and the Validity Check Operation are adaptation
 * points of an InReport.
 * These operations are implemented by functions of type, respectively,
 * <code>::CrFwInRepUpdateAction_t</code> and
 * <code>::CrFwInRepValidityCheck_t</code>.
 * These functions take as an argument the descriptor of the InReport's Execution Procedure.
 * Applications will often have to provide an implementation of these functions
 * and, to do so, they will often need to access the packet holding the InReport so
 * as to access the InReport's parameters,
 * The present function offers an easy way to retrieve this packet.
 *
 * @param prDesc the descriptor of the InReport's Execution Procedure
 * @return the packet holding the InReport
 */
CrFwPckt_t CrFwInRepGetPcktFromPrDesc(FwPrDesc_t prDesc);

/**
 * Default implementation of the validity check of an InReport.
 * The validity check of an InReport must conform to the <code>::CrFwInRepValidityCheck_t</code>
 * function prototype.
 * This default implementation verifies the correctness of the CRC of the packet
 * which carries the report.
 * The CRC is processed using the CRC functions defined by interface
 * <code>CrFwPckt.h</code>.
 *
 * @param prDesc the descriptor of the InReport's Reset Procedure
 * @return true if the CRC of the InReport packet is correct
 */
CrFwBool_t CrFwInRepDefValidityCheck(FwPrDesc_t prDesc);

#endif /* CRFW_INREP_H_ */
