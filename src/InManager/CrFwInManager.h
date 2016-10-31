/**
 * @file
 * @ingroup inMngGroup
 * Definition of the InManager component.
 *
 * The InManager component is responsible for maintaining a list of
 * pending InReports (see <code>CrFwInRep.h</code>) and InCommands (see <code>CrFwInCmd.h</code>)
 * and for repeatedly executing them until they are either aborted or terminated.
 *
 * The list of pending InReports or InCommands is called the Pending Command/Report List or PCRL.
 * The PCRL has a fixed size which is defined statically in <code>CrFwInManagerUserPar.h</code>.
 *
 * The InManager is defined as an extension of the Base Component (see <code>CrFwBaseCmp.h</code>).
 * It uses the Execution Procedure of the Base Component to process the pending InReport and InCommands.
 * The InManager component processes the pending InReports or InCommands by sending them an Execute
 * command.
 * After each Execute command, the state of the pending item is reported to the InRegistry
 * (see <code>CrFwInRegistry.h</code>).
 * InReports or InCommands which have been aborted or have terminated are removed
 * from the PCRL and are returned to the InFactory.
 * The Execution Procedure of the InManager is shown in the figure below.
 *
 * <b>Mode of Use of an InManager Component</b>
 *
 * The configuration of the InManager components is defined statically in
 * <code>CrFwInManagerUserPar.h</code>.
 *
 * An InManager component is created with function <code>::CrFwInManagerMake</code>.
 * After being created, the InManager must be initialized and reset.
 * This is done with functions <code>::CrFwCmpInit</code> and <code>::CrFwCmpReset</code>.
 * Nominally, after being initialized and reset the InManager State Machine should be
 * in state CONFIGURED (this can be checked by verifying that function <code>FwSmGetCurState</code>
 * returns CR_FW_BASE_STATE_CONFIGURED).
 *
 * Note that an application can have any number of InManagers.
 *
 * An InManager offers a Load operation (<code>::CrFwInManagerLoad</code>) through which
 * an InReport or InCommand can be added to the PCRL.
 * This operation is normally called by the InLoader (see <code>CrFwInLoader.h</code>).
 *
 * Note that there is no mechanism to “unload” a pending InReport or InCommand.
 * The InManager autonomously returns an InReport or InCommand to its factory when the
 * component has terminated or has been aborted.
 * InReports are considered to have been terminated after they are executed once.
 * InCommands are terminated if they are in state TERMINATED and they are aborted if
 * they are in state ABORTED.
 *
 * After an InManager has been configured, it can be executed by means of function
 * <code>FwSmExecute</code>.
 * Execution of an InManager causes its Execution Procedure (see figure below) to be
 * executed.
 *
 * When an InManager is reset or shutdown, its PCRL is reset (all pending InCommands and
 * InReports are cleared and returned to theirs factories).
 *
 * @image html InManagerExecution.png
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of CORDET Framework.
 *
 * CORDET Framework is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CORDET Framework is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CORDET Framework.  If not, see <http://www.gnu.org/licenses/>.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#ifndef CRFW_INMANAGER_H_
#define CRFW_INMANAGER_H_

/* Include FW Profile Files */
#include "FwSmConstants.h"
#include "FwPrConstants.h"
/* Include Framework Files */
#include "CrFwConstants.h"
/* Include Configuration Files */
#include "CrFwUserConstants.h"
#include "Pckt/CrFwPcktQueue.h"

/**
 * Factory function to retrieve the i-th InManager State Machine instance.
 * The first time this function is called with a certain value of the argument i, it
 * creates the i-th InManager State Machine instance.
 * Subsequent calls returns the same instance.
 *
 * The InManager identifier i must be in the range: [0, <code>#CR_FW_NOF_INMANAGER</code>-1].
 * If the identifier is out of range, the function returns NULL and sets the application
 * error code to: <code>::crInManagerIllId</code>.
 *
 * The first time this function is called with a certain value of i, it returns an
 * InManager State Machine which has been started but which still needs to be initialized and
 * configured.
 * @param inManagerId the identifier of the InManager
 * @return the descriptor of the InManager State Machine or NULL
 * if the state machine could not be created or if the identifier i is out of range.
 */
FwSmDesc_t CrFwInManagerMake(CrFwInstanceId_t inManagerId);

/**
 * Load a new InReport or InCommand into the InManager.
 * The behaviour implemented by this function is shown in the activity diagram below.
 * The algorithm to search for a free position in the Pending Command/Report List (PCRL)
 * is optimized for a situation where multiple load operations are performed before
 * the InManager is executed.
 * However, in a worst-case, the algorithm may have to scan the entire PCRL to find a
 * free position where to insert the InCommand or InReport.
 * @image html InManagerLoad.png
 * @param smDesc the descriptor of the InManager State Machine.
 * @param inCmp the descriptor of the InCommand or InReport to be loaded in the InManager
 * @return 1 if the load operation was successful (the PCRL was not full and the
 * InReport/InCommand was successfully loaded in the InManager) or 0 if
 * the load operation has failed (the PCRL was full and the InReport/InCommand
 * could not be loaded in the InManager).
 */
CrFwBool_t CrFwInManagerLoad(FwSmDesc_t smDesc, FwSmDesc_t inCmp);

/**
 * Return the number of InReport or InCommands currently in the PCRL of an InManager.
 * @param smDesc the descriptor of the InManager State Machine.
 * @return the number of OutComponents currently in the PCRL of an InManager.
 */
CrFwCounterU1_t CrFwInManagerGetNOfPendingInCmp(FwSmDesc_t smDesc);


/**
 * Return the number of InReport or InCommands successfully loaded since the InManager
 * was last reset.
 * @param smDesc the descriptor of the InManager State Machine.
 * @return the number of InReport or InCommands currently in the PCRL of an InManager.
 */
CrFwCounterU2_t CrFwInManagerGetNOfLoadedInCmp(FwSmDesc_t smDesc);

/**
 * Return the size of the PCRL of an InManager.
 * @param smDesc the descriptor of the InManager State Machine.
 * @return the size of the PCRL of an InManager.
 */
CrFwCounterU1_t CrFwInManagerGetPCRLSize(FwSmDesc_t smDesc);

#endif /* CRFW_INMANAGER_H_ */
