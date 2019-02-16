/**
 * @file
 * @ingroup outMngGroup
 * Definition of the OutManager component.
 *
 * The OutManager component is responsible for maintaining a list of
 * pending OutComponents (see <code>CrFwOutCmp.h</code>) and for repeatedly
 * executing them until they are either aborted or else they are serialized
 * and sent to their destination.
 *
 * The list of pending commands is called the Pending OutComponent List or POCL.
 * The POCL has a fixed size which is defined statically in <code>CrFwOutManagerUserPar.h</code>.
 *
 * The OutManager is defined as an extension of the Base Component (see <code>CrFwBaseCmp.h</code>).
 * It uses the Execution Procedure of the Base Component to process the pending OutComponents.
 * The OutManager component processes the pending OutComponents by sending them an Execute command.
 * After each Execute command, the state of the OutComponent is reported to the OutRegistry
 * (see <code>CrFwOutRegistry.h</code>).
 * Commands which have been aborted or have been sent to their destination are removed
 * from the POCL and are returned to the OutFactory (see <code>CrFwOutFactory.h</code>).
 * The Execution Procedure of the OutManager is shown in the figure below.
 *
 * <b>Mode of Use of an OutManager Component</b>
 *
 * The configuration of the OutManager components is defined statically in
 * <code>CrFwOutManagerUserPar.h</code>.
 *
 * An OutManager component is created with function <code>::CrFwOutManagerMake</code>.
 * After being created, the OutManager must be initialized and reset.
 * This is done with functions <code>::CrFwCmpInit</code> and <code>::CrFwCmpReset</code>.
 * Nominally, after being initialized and reset the OutManager State Machine should be
 * in state CONFIGURED (this can be checked by verifying that function <code>FwSmGetCurState</code>
 * returns CR_FW_BASE_STATE_CONFIGURED).
 *
 * An application can have any number of OutManagers.
 *
 * An OutManager offers a Load operation (<code>::CrFwOutManagerLoad</code>) through which
 * an OutComponent can be added to the POCL.
 * This operation is normally called by the OutLoader (see <code>CrFwOutLoader.h</code>).
 *
 * There is no mechanism to “unload” a pending OutComponent.
 * The OutManager autonomously returns an OutComponent to the OutFactory when the
 * OutComponent has been sent to its destination (i.e. when the OutComponent is in
 * state TERMINATED) or when it has been aborted (i.e. when the OutComponent is in
 * state ABORTED).
 *
 * After an OutManager has been configured, it can be executed by means of function
 * <code>FwSmExecute</code>.
 * Execution of an OutManager causes its Execution Procedure (see figure below) to be
 * executed.
 *
 * When an OutManager is reset or shutdown, its POCL is reset (all pending OutComponents
 * are cleared and returned to the OutFactory).
 *
 * @image html OutManagerExecution.png
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

#ifndef CRFW_OUT_MANAGER_H_
#define CRFW_OUT_MANAGER_H_

/* Include FW Profile Files */
#include "FwSmConstants.h"
#include "FwPrConstants.h"
/* Include Framework Files */
#include "CrFwConstants.h"
/* Include Configuration Files */
#include "CrFwUserConstants.h"
#include "Pckt/CrFwPcktQueue.h"

/**
 * Factory function to retrieve the i-th OutManager State Machine instance.
 * The first time this function is called with a certain value of the argument i, it
 * creates the i-th OutManager State Machine instance.
 * Subsequent calls returns the same instance.
 *
 * The OutManager identifier i must be in the range: [0, <code>#CR_FW_NOF_OUTMANAGER</code>-1].
 * If the identifier is out of range, the function returns NULL and sets the application
 * error code to: <code>::crOutManagerIllId</code>.
 *
 * The first time this function is called with a certain value of i, it returns an
 * OutManager State Machine which has been started but which still needs to be initialized and
 * configured.
 * @param outManagerId the identifier of the OutManager
 * @return the descriptor of the OutManager State Machine or NULL
 * if the state machine could not be created or if the identifier i is out of range.
 */
FwSmDesc_t CrFwOutManagerMake(CrFwInstanceId_t outManagerId);

/**
 * Load a new OutComponent into the OutManager.
 * The behaviour implemented by this function is shown in the activity diagram below.
 * If the POCL is not full, the function identifies a free position in the POCL where
 * to store the OutComponent.
 * If the POCL is full, the function generates the error report #crOutManagerPoclFull
 * and then releases the OutCompoment and returns.
 *
 * This function adds OutComponents to the POCL. The POCL is flushed when the OutManager
 * is executed (i.e. it is flushed by function <code>::OutManagerExecAction</code>).
 * The algorithms to identify a free position in the POCL and to process the POCL
 * entries when the OutManager is executed are optimized for a situation where multiple
 * load operations are performed before the OutManager is executed.
 *
 * Additionally, these algorithms guarantee the following ordering constraint.
 * Let OutComponents C1 to Cn be successfully loaded into an OutManager through a sequence
 * of calls to function <code>::CrFwOutManagerLoad</code> and assume that this sequence
 * of load operations is not interrupted by an execution of the OutManager.
 * Under these conditions, when the OutManager is executed next, the OutComponents C1 to
 * Cn will be processed in the order in which they have been loaded.
 *
 * The implementation of function <code>::CrFwOutManagerLoad</code> is based on the
 * internal variable <code>freePos</code>. This variable has the following
 * characteristics:
 * - it is initialized to point to the first entry in the POCL;
 * - after the execution of the load function, <code>freePos</code> either points to the next
 * free position in the POCL or is equal to the POCL size if the POCL is full;
 * - after execution of the OutManager, it is re-initialized to point to the first position
 * in the POCL.
 * .
 * @image html OutManagerLoad.png
 * @param smDesc the descriptor of the OutManager State Machine.
 * @param outCmp the descriptor of the OutComponent to be loaded in the OutManager
 * @return 1 if the load operation was successful (the POCL was not full and the
 * OutComponent was successfully loaded in the OutManager) or 0 if
 * the load operation has failed (the POCL was full and the OutComponent
 * could not be loaded in the OutManager).
 */
CrFwBool_t CrFwOutManagerLoad(FwSmDesc_t smDesc, FwSmDesc_t outCmp);

/**
 * Return the number of OutComponents currently in the POCL of an OutManager.
 * @param smDesc the descriptor of the OutManager State Machine.
 * @return the number of OutComponents currently in the POCL of an OutManager.
 */
CrFwCounterU1_t CrFwOutManagerGetNOfPendingOutCmp(FwSmDesc_t smDesc);

/**
 * Return the number of OutComponents successfully loaded in the POCL of an OutManager
 * since the OutManager was last reset.
 * @param smDesc the descriptor of the OutManager State Machine.
 * @return the number of OutComponents successfully loaded in the POCL of an OutManager.
 */
CrFwCounterU2_t CrFwOutManagerGetNOfLoadedOutCmp(FwSmDesc_t smDesc);

/**
 * Return the size of the POCL of an OutManager.
 * @param smDesc the descriptor of the OutManager State Machine.
 * @return the size of the POCL of an OutManager.
 */
CrFwCounterU1_t CrFwOutManagerGetPOCLSize(FwSmDesc_t smDesc);

#endif /* CRFW_OUT_MANAGER_H_ */
