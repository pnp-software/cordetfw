/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Sample InCommand used in the Test Suite.
 * An InCommand is defined by defining the functions which override its
 * adaptation points, namely (see <code>CrFwInCmd.h</code>):
 * - The Validity Check Operation
 * - The Ready Check Operation
 * - The Start Action Operation
 * - The Progress Action Operation
 * - The Termination Action Operation
 * - The Abort Action Operation
 * .
 * This module defines functions which implement the above operations.
 * These functions are associated to a specific kind of InCommand in
 * the initializer <code>#CR_FW_INCMD_INIT_KIND_DESC</code>.
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

#ifndef CRFW_INCMD_SAMPLE1_H_
#define CRFW_INCMD_SAMPLE1_H_

/* Include configuration files */
#include "CrFwUserConstants.h"
/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile components */
#include "FwSmCore.h"

/**
 * Implementation of the Validity Check Operation for the Sample 1 InCommand.
 * This function returns the value of an internal flag (the Validity Flag)
 * whose value is set through function <code>::CrFwInCmdSample1SetValidityFlag</code>.
 * @param prDesc the descriptor of the InCommand reset procedure
 * @return the value of Validity Flag
 */
CrFwBool_t CrFwInCmdSample1ValidityCheck(FwPrDesc_t prDesc);

/**
 * Set the value of the Validity Flag (see <code>::CrFwInCmdSample1ValidityCheck</code>).
 * @param flag the value of the validity flag
 */
void CrFwInCmdSample1SetValidityFlag(CrFwBool_t flag);

/**
 * Implementation of the Ready Check Operation for the Sample 1 InCommand.
 * This function returns the value of an internal flag (the Ready Flag)
 * whose value is set through function <code>::CrFwInCmdSample1SetReadyFlag</code>.
 * @param smDesc the descriptor of the InCommand state machine
 * @return the value of the Ready Flag
 */
CrFwBool_t CrFwInCmdSample1ReadyCheck(FwSmDesc_t smDesc);

/**
 * Set the value of the Ready Flag (see <code>::CrFwInCmdSample1ReadyCheck</code>).
 * @param flag the value of the ready flag
 */
void CrFwInCmdSample1SetReadyFlag(CrFwBool_t flag);

/**
 * Implementation of the Start Action Operation for the Sample 1 InCommand.
 * This function sets the outcome to the value of an internal counter (the
 * Start Action Outcome Counter) whose value is set through function
 * <code>::CrFwInCmdSample1SetStartActionOutcome</code> and it increments
 * the value of a counter (the Start Action Counter) whose value
 * is read through function <code>::CrFwInCmdSample1GetStartActionCounter</code>.
 * @param smDesc the descriptor of the InCommand state machine
 */
void CrFwInCmdSample1StartAction(FwSmDesc_t smDesc);

/**
 * Set the value of the Start Action Outcome Counter
 * (see <code>::CrFwInCmdSample1StartAction</code>).
 * @param outcome the value of the Start Action Outcome
 */
void CrFwInCmdSample1SetStartActionOutcome(CrFwOutcome_t outcome);

/**
 * Get the value of the Start Action Counter (see <code>::CrFwInCmdSample1StartAction</code>).
 * @return the value of the Start Action Counter
 */
CrFwCounterU1_t CrFwInCmdSample1GetStartActionCounter();

/**
 * Implementation of the Progress Action Operation for the Sample 1 InCommand.
 * This function sets the outcome to the value of an internal counter (the
 * Progress Action Outcome Counter) whose value is set through function
 * <code>::CrFwInCmdSample1SetProgressActionOutcome</code> and it increments
 * the value of a counter (the Progress Action Counter) whose value
 * is read through function <code>::CrFwInCmdSample1GetProgressActionCounter</code>.
 * @param smDesc the descriptor of the InCommand state machine
 */
void CrFwInCmdSample1ProgressAction(FwSmDesc_t smDesc);

/**
 * Set the value of the Progress Action Outcome Counter
 * (see <code>::CrFwInCmdSample1ProgressAction</code>).
 * @param outcome the value of the Progress Action Outcome
 */
void CrFwInCmdSample1SetProgressActionOutcome(CrFwOutcome_t outcome);

/**
 * Get the value of the Progress Action Counter (see <code>::CrFwInCmdSample1ProgressAction</code>).
 * @return the value of the Progress Action Counter
 */
CrFwCounterU1_t CrFwInCmdSample1GetProgressActionCounter();

/**
 * Implementation of the Abort Action Operation for the Sample 1 InCommand.
 * This function sets the outcome to the value of an internal counter (the
 * Abort Action Outcome Counter) whose value is set through function
 * <code>::CrFwInCmdSample1SetAbortActionOutcome</code> and it increments
 * the value of a counter (the Abort Action Counter) whose value
 * is read through function <code>::CrFwInCmdSample1GetAbortActionCounter</code>.
 * @param smDesc the descriptor of the InCommand state machine
 */
void CrFwInCmdSample1AbortAction(FwSmDesc_t smDesc);

/**
 * Set the value of the Abort Action Outcome Counter
 * (see <code>::CrFwInCmdSample1AbortAction</code>).
 * @param outcome the value of the Abort Action Outcome
 */
void CrFwInCmdSample1SetAbortActionOutcome(CrFwOutcome_t outcome);

/**
 * Get the value of the Abort Action Counter (see <code>::CrFwInCmdSample1AbortAction</code>).
 * @return the value of the Abort Action Counter
 */
CrFwCounterU1_t CrFwInCmdSample1GetAbortActionCounter();

/**
 * Implementation of the Termination Action Operation for the Sample 1 InCommand.
 * This function sets the outcome to the value of an internal counter (the
 * Termination Action Outcome Counter) whose value is set through function
 * <code>::CrFwInCmdSample1SetTerminationActionOutcome</code> and it increments
 * the value of a counter (the Termination Action Counter) whose value
 * is read through function <code>::CrFwInCmdSample1GetTerminationActionCounter</code>.
 * @param smDesc the descriptor of the InCommand state machine
 */
void CrFwInCmdSample1TerminationAction(FwSmDesc_t smDesc);

/**
 * Set the value of the Termination Action Outcome Counter
 * (see <code>::CrFwInCmdSample1TerminationAction</code>).
 * @param outcome the value of the Termination Action Outcome
 */
void CrFwInCmdSample1SetTerminationActionOutcome(CrFwOutcome_t outcome);

/**
 * Get the value of the Termination Action Counter (see <code>::CrFwInCmdSample1TerminationAction</code>).
 * @return the value of the Termination Action Counter
 */
CrFwCounterU1_t CrFwInCmdSample1GetTerminationActionCounter();

#endif /* CRFW_INCMD_SAMPLE1_H_ */
