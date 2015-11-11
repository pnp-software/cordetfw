/**
 * @file
 * @ingroup inMngGroup
 * Definition of the InRegistry Component.
 *
 * An InRegistry acts as a registry for incoming commands or reports (namely for
 * commands or reports which have been loaded into an InManager).
 * The InRegistry is responsible for keeping track of the state of an incoming
 * command or report.
 *
 * The InRegistry is a singleton component which is implemented as an extension
 * of the Base Component of <code>CrFwBaseCmp.h</code>.
 *
 * The InRegistry maintains a list of the last N commands or reports to have been
 * loaded in an InManager.
 * The InRegistry maintains the state of each such command or report.
 * The command's or report's state in the InRegistry can have one of the following values:
 * - PENDING: the command or report is waiting to be executed
 * - EXECUTING: the command has already been executed but has not yet completed
 *   execution
 * - ABORTED: the command was aborted during execution
 * - TERMINATED: the command or report has completed execution
 * .
 * Note that the states EXECUTING and ABORTED only apply to incoming commands (incoming
 * reports are only executed once and then are terminated).
 *
 * The value of N (the maximum number of items which can be tracked by the InRegistry)
 * is fixed and is an initialization parameter.
 *
 * The InRegistry uses the instance identifier of the incoming command or report
 * as the key through which the command or report state is tracked.
 *
 * <b>Mode of Use of an InRegistry Component</b>
 *
 * The configuration of the InRegistry component is defined statically in
 * <code>CrFwInRegistryUserPar.h</code>.
 *
 * The InRegistry component is a "final" component that does not normally need
 * to be extended.
 *
 * An InRegistry component is created with function <code>::CrFwInRegistryMake</code>.
 * After being created, the InRegistry must be initialized and reset.
 * This is done with functions <code>::CrFwCmpInit</code> and <code>::CrFwCmpReset</code>.
 * Nominally, after being initialized and reset the InRegistry State Machine should be
 * in state CONFIGURED (this can be checked by verifying that function <code>FwSmGetCurState</code>
 * returns CR_FW_BASE_STATE_CONFIGURED).
 *
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

#ifndef CRFW_INREGISTRY_H_
#define CRFW_INREGISTRY_H_

/* Include configuration files */
#include "CrFwInRegistryUserPar.h"
#include "CrFwUserConstants.h"
/* Include FW Profile files */
#include "FwProfile/FwSmConstants.h"
#include "FwProfile/FwPrConstants.h"
/* Include framework files */
#include "CrFwConstants.h"

/** Enumerated type for the state of a command or report tracked by the InRegistry */
typedef enum {
	/** No entry yet in InRegistry */
	crInRegistryNoEntry = 0,
	/** Incoming command or report is pending (waiting to be sent) */
	crInRegistryPending = 1,
	/** Incoming command has been executed but has not yet completed execution */
	crInRegistryExecuting = 2,
	/** Incoming command has been aborted */
	crInRegistryAborted = 3,
	/** Incoming command or report has completed execution */
	crInRegistryTerminated = 4,
	/** Incoming command or report is not tracked */
	crInRegistryNotTracked = 5
} CrFwInRegistryCmdRepState_t;

/**
 * Factory function for the singleton instance of the InRegistry.
 * The first time this function is called, it creates and configures the InRegistry.
 * Subsequent calls returns the same singleton instance.
 * The first time this function is called, it returns the InRegistry in state CREATED.
 *
 * If the creation or the configuration of the InRegistry fails, the function
 * returns NULL.
 * @return singleton instance of the InRegistry or NULL if the creation or configuration
 * of the InRegistry failed.
 */
FwSmDesc_t CrFwInRegistryMake();

/**
 * Ask the InRegistry to start tracking an incoming command or report.
 * The InRegistry tracks the state of the last N incoming command or reports
 * to have been loaded with this function.
 * Initially, when this function is called, the incoming command or report is
 * placed in state PENDING.
 *
 * This function runs the procedure in the left-hand
 * side of the activity diagram shown in the figure.
 * @image html RegistryStartTrackingAndUpdate.png
 * @param inCmp the incoming command or report to be tracked
 */
void CrFwInRegistryStartTracking(FwSmDesc_t inCmp);

/**
 * Ask the InRegistry to update the state of an incoming command or report.
 * If the argument component is not tracked by the InRegistry (perhaps because
 * too many commands and reports have been added to the list of tracked components),
 * nothing is done.
 * This function runs the procedure in the right-hand
 * side of the activity diagram shown in the figure.
 * @image html RegistryStartTrackingAndUpdate.png
 * @param inCmp the incoming command or report to be tracked
 * @param newState the new state of the incoming command or report
 */
void CrFwInRegistryUpdateState(FwSmDesc_t inCmp, CrFwInRegistryCmdRepState_t newState);

/**
 * Query the InRegistry for the state of an incoming command or report.
 * If the specified index does not correspond to any command or report being
 * tracked by the InRegistry, a value of <code>::crInRegistryNotTracked</code>
 * is returned.
 * This function searches all locations in the InRegistry in sequence until it
 * finds the incoming command or report.
 * @param cmdRepId the instance identifier of the incoming command or report.
 * @return the state of the incoming command or report (or <code>::crInRegistryNotTracked</code>
 * if the command or report is not tracked)
 */
CrFwInRegistryCmdRepState_t CrFwInRegistryGetState(CrFwInstanceId_t cmdRepId);

#endif /* CRFW_INREGISTRY_H_ */
