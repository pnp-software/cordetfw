/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the InCommand Component (see <code>CrFwInCmd.h</code>).
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

#ifndef CRFW_INCMD_TESTCASES_H_
#define CRFW_INCMD_TESTCASES_H_

#include "CrFwConstants.h"

/**
 * Check the configuration of a newly created InCommand.
 * The following actions are performed in this test:
 * - The InFactory is reset and then two InCommands are retrieved from the InFactory
 *   and it is checked that their instance identifier and type identifier are correct.
 * - It is checked that the InCommands are initially in state CONFIGURED.
 * - It is checked that the InCommand is correctly configured.
 * - It is checked that the length and start address of the InCommand's parameter area
 *   are correct.
 * - It is checked that the service type and sub-type and the discriminant value of the
 *   InCommand are correct.
 * - It is checked that the InCommand source, group and sequence counter are correctly set.
 * - It is checked that the acknowledge levels of the InCommands are correct.
 * - It is checked that the progress step is equal to zero.
 * .
 * @verify InCommand SM Transition: IPS->ACCEPTED
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInCmdTestCase1();

/**
 * Check the transition from ACCEPTED to PROGRESS for an InCommand.
 * The following actions are performed in this test:
 * - The InFactory is reset and then one Sample1 InCommand (see <code>CrFwInCmdSample1.h</code>) is
 *   retrieved from the InFactory;
 * - The sample InCommand is configured to have a validity check which returns: "valid" and
 *   to have no acknowledgement of acceptance.
 * - The Ready Check of the sample InCommand is configured to return "not ready".
 * - The sample InCommand is executed and it is checked that it remains in state ACCEPTED.
 * - The Ready Check of the sample InCommand is configured to return "ready"; its
 *   Start Actions is configured to have an outcome of "success".
 * - The sample InCommand is executed and it is checked that it enters state PROGRESS and that the
 *   progress and the start action are performed.
 * .
 * @verify InCommand SM Transition: IPS->ACCEPTED
 * @verify InCommand SM Transition: ACCEPTED->CPS1
 * @verify InCommand SM Transition: CPS1->PROGRESS
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInCmdTestCase2();

/**
 * Check the transition from ACCEPTED to ABORTED for an InCommand.
 * The following actions are performed in this test:
 * - The InFactory is reset and then one Sample1 InCommand (see <code>CrFwInCmdSample1.h</code>) is
 *   retrieved from the InFactory.
 * - The sample InCommand is configured to have a validity check which returns: "valid" and
 *   to have no acknowledgement of acceptance.
 * - The Ready Check of the sample InCommand is configured to return "ready" and its Start Action
 *   is configured to have an outcome of "failed"
 * - The sample InCommand is executed and it is checked that it enters state ABORTED; that the
 *   Abort Action is executed; and that a start failure report is generated.
 * - The sample InCommand is executed again and it is checked that it remains in state ABORTED.
 * .
 * @verify InCommand SM Transition: IPS->ACCEPTED
 * @verify InCommand SM Transition: ACCEPTED->CPS1
 * @verify InCommand SM Transition: CPS1->ABORTED
 * @verify InCommand Outcome Report: crCmdAckStrFail
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInCmdTestCase3();

/**
 * Check the failure of the Validity Check of an InCommand.
 * The following actions are performed in this test:
 * - The InFactory is reset and then one Sample1 InCommand (see <code>CrFwInCmdSample1.h</code>) is
 *   retrieved from the InFactory.
 * - The validity check of the InCommand is configured to return: "not valid" and it is checked that
 *   that the InCommand is returned by the InFactory in state INITIALIZED.
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInCmdTestCase4();

/**
 * Check the behaviour of the InCommand in state PROGRESS.
 * The following actions are performed in this test:
 * - The InFactory is reset and then one Sample1 InCommand (see <code>CrFwInCmdSample1.h</code>) is
 *   retrieved from the InFactory.
 * - The validity check of the InCommand is configured to return: "valid"; the Ready Check is configured
 *   to return: "ready"; the Start Action is configured to have an outcome of "success"; the
 *   acknowledgement level is configured to acknowledge neither acceptance, nor start, nor progress
 *   nor termination;
 *   the progress action is configured to set the outcome to "continue".
 * - The InCommand is executed and it is checked that state PROGRESS is entered, that the Progress
 *   Action is executed, and that no acknowledge report is generated.
 * - The InCommand is executed again and it is checked that state PROGRESS is maintained, that the Progress
 *   Action is executed again, and that no acknowledge report is generated.
 * - Command Terminate is sent to the InCommand and it is checked that state PROGRESS is maintained and that
 *   the progress action is not executed.
 * .
 * @verify InCommand SM Transition: IPS->ACCEPTED
 * @verify InCommand SM Transition: ACCEPTED->CPS1
 * @verify InCommand SM Transition: CPS1->PROGRESS
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInCmdTestCase5();

/**
 * Check the transition from state PROGRESS to state TERMINATED for an InCommand.
 * The following actions are performed in this test:
 * - The InFactory is reset and then one Sample1 InCommand (see <code>CrFwInCmdSample1.h</code>) is
 *   retrieved from the InFactory.
 * - The validity check of the InCommand is configured to return: "valid"; the Ready Check is configured
 *   to return: "ready"; the Start Action is configured to have an outcome of "success"; the
 *   acknowledgement level is configured to acknowledge neither acceptance, nor start, nor progress
 *   nor termination;
 *   the progress action is configured to set the outcome to "continue"; the Termination Action is
 *   configured to set the outcome to "success".
 * - The InCommand is executed and it is checked that state PROGRESS is entered, that the Progress
 *   Action is executed, and that no acknowledge report is generated.
 * - The InCommand is executed again and it is checked that state PROGRESS is maintained, that the Progress
 *   Action is executed again, and that no acknowledge report is generated.
 * - The Progress Action of the Sample InCommand is configured to have an outcome of "completed".
 * - Command Terminate is sent to the InCommand and it is checked that state TERMINATED is entered and
 *   that the Termination Action is executed.
 * - It is checked that the progress step is equal to zero.
 * .
 * @verify InCommand SM Transition: IPS->ACCEPTED
 * @verify InCommand SM Transition: ACCEPTED->CPS1
 * @verify InCommand SM Transition: CPS1->PROGRESS
 * @verify InCommand SM Transition: PROGRESS->CPS2
 * @verify InCommand SM Transition: CPS2->TERMINATED
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInCmdTestCase6();

/**
 * Check the direct transition from state PROGRESS to state ABORTED for an InCommand.
 * The following actions are performed in this test:
 * - The InFactory is reset and then one Sample1 InCommand (see <code>CrFwInCmdSample1.h</code>) is
 *   retrieved from the InFactory.
 * - The validity check of the InCommand is configured to return: "valid"; the Ready Check is configured
 *   to return: "ready"; the Start Action is configured to have an outcome of "success"; the
 *   acknowledgement level is configured to acknowledge neither acceptance, nor start, nor progress
 *   nor termination;
 *   the progress action is configured to set the outcome to "continue"; the Termination Action is
 *   configured to set the outcome to "success".
 * - The InCommand is executed and it is checked that state PROGRESS is entered, that the Progress
 *   Action is executed, and that no acknowledge report is generated.
 * - The Progress Action is configured to set the outcome to "failure" and then the InCommand is executed
 *   again.
 * - Command Terminate is sent to the InCommand and it is checked that state ABORTED is entered;
 *   that the Abort Action is executed; and that a progress failure report is generated.
 * .
 * @verify InCommand SM Transition: IPS->ACCEPTED
 * @verify InCommand SM Transition: ACCEPTED->CPS1
 * @verify InCommand SM Transition: CPS1->PROGRESS
 * @verify InCommand SM Transition: PROGRESS->ABORTED
 * @verify InCommand Outcome Report: crCmdAckPrgFail
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInCmdTestCase7();

/**
 * Check the indirect transition from state PROGRESS to state ABORTED for an InCommand.
 * The following actions are performed in this test:
 * - The InFactory is reset and then one Sample1 InCommand (see <code>CrFwInCmdSample1.h</code>) is
 *   retrieved from the InFactory.
 * - The validity check of the InCommand is configured to return: "valid"; the Ready Check is configured
 *   to return: "ready"; the Start Action is configured to have an outcome of "success"; the
 *   acknowledgement level is configured to acknowledge neither acceptance, nor start, nor progress,
 *   nor termination;
 *   the progress action is configured to set the outcome to "completed"; the Termination Action is
 *   configured to set the outcome to "failed".
 * - The InCommand is executed and it is checked that state PROGRESS is entered, that the Progress
 *   Action is executed, and that no acknowledge report is generated.
 * - Command Terminate is sent to the InCommand and it is checked that state ABORTED is entered;
 *   that the Abort Action is executed; and that a termination failure report is generated.
 * .
 * @verify InCommand SM Transition: IPS->ACCEPTED
 * @verify InCommand SM Transition: ACCEPTED->CPS1
 * @verify InCommand SM Transition: CPS1->PROGRESS
 * @verify InCommand SM Transition: PROGRESS->CPS2
 * @verify InCommand SM Transition: CPS2->TERMINATED
 * @verify InCommand Outcome Report: crCmdAckTrmFail
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInCmdTestCase8();

/**
 * Check the generation of the "start successful" outcome report of an InCommand.
 * The following actions are performed in this test:
 * - The InFactory is reset and then one Sample1 InCommand (see <code>CrFwInCmdSample1.h</code>) is
 *   retrieved from the InFactory.
 * - The validity check of the InCommand is configured to return: "valid"; the Ready Check is configured
 *   to return: "ready"; the Start Action is configured to have an outcome of "success"; the
 *   acknowledgement level is configured to acknowledge start but none of the other outcomes;
 *   the progress action is configured to set the outcome to "continue"; the Termination Action is
 *   configured to set the outcome to "success".
 * - The InCommand is executed and it is checked that state PROGRESS is entered, that the Progress
 *   Action is executed, and that the start acknowledge report is generated.
 * .
 * @verify InCommand SM Transition: IPS->ACCEPTED
 * @verify InCommand SM Transition: ACCEPTED->CPS1
 * @verify InCommand SM Transition: CPS1->PROGRESS
 * @verify InCommand Outcome Report: crCmdAckStrSucc
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInCmdTestCase9();

/**
 * Check the generation of the "progress successful" outcome report of an InCommand.
 * The following actions are performed in this test:
 * - The InFactory is reset and then one Sample1 InCommand (see <code>CrFwInCmdSample1.h</code>) is
 *   retrieved from the InFactory.
 * - The validity check of the InCommand is configured to return: "valid"; the Ready Check is configured
 *   to return: "ready"; the Start Action is configured to have an outcome of "success"; the
 *   acknowledgement level is configured to acknowledge progress but none of the other outcomes;
 *   the progress action is configured to set the outcome to "continue"; the Termination Action is
 *   configured to set the outcome to "success".
 * - The InCommand is executed and it is checked that state PROGRESS is entered, that the Progress
 *   Action is executed, and that the progress acknowledge report is generated.
 * - The InCommand is executed again and it is checked that state PROGRESS is maintained, that the Progress
 *   Action is executed again, and that the progress acknowledge report is generated again.
 * - The Progress Step is retrieve and it is checked that it is equal to 2.
 * .
 * @verify InCommand SM Transition: IPS->ACCEPTED
 * @verify InCommand SM Transition: ACCEPTED->CPS1
 * @verify InCommand SM Transition: CPS1->PROGRESS
 * @verify InCommand Outcome Report: crCmdAckPrgSucc
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInCmdTestCase10();

/**
 * Check the generation of the "termination successful" outcome report of an InCommand.
 * The following actions are performed in this test:
 * - The InFactory is reset and then one Sample1 InCommand (see <code>CrFwInCmdSample1.h</code>) is
 *   retrieved from the InFactory.
 * - The validity check of the InCommand is configured to return: "valid"; the Ready Check is configured
 *   to return: "ready"; the Start Action is configured to have an outcome of "success"; the
 *   acknowledgement level is configured to acknowledge termination but none of the other outcomes;
 *   the progress action is configured to set the outcome to "continue"; the Termination Action is
 *   configured to set the outcome to "success".
 * - The InCommand is executed and it is checked that state PROGRESS is entered, that the Progress
 *   Action is executed, and that no acknowledge report is generated.
 * - The InCommand is executed again and it is checked that state PROGRESS is maintained, that the Progress
 *   Action is executed again, and that no acknowledge report is generated.
 * - The Progress Action of the Sample InCommand is configured to have an outcome of "completed".
 * - Command Terminate is sent to the InCommand and it is checked that state TERMINATED is entered;
 *   that the Termination Action is executed; and that the termination acknowledge report is generated.
 * .
 * @verify InCommand SM Transition: IPS->ACCEPTED
 * @verify InCommand SM Transition: ACCEPTED->CPS1
 * @verify InCommand SM Transition: CPS1->PROGRESS
 * @verify InCommand SM Transition: PROGRESS->CPS2
 * @verify InCommand SM Transition: CPS2->TERMINATED
 * @verify InCommand Outcome Report: crCmdAckTrmSucc
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInCmdTestCase11();

/**
 * Check the parameters of the "successful" outcome reports of an InCommand.
 * The following actions are performed in this test:
 * - The InFactory is reset and then one Sample1 InCommand (see <code>CrFwInCmdSample1.h</code>) is
 *   retrieved from the InFactory.
 * - The validity check of the InCommand is configured to return: "valid"; the Ready Check is configured
 *   to return: "ready"; the Start Action is configured to have an outcome of "success"; the
 *   progress action is configured to have an outcome of "completed"; the termination action is configured
 *   to have an outcome of "success"; the acknowledgement level is configured to acknowledge
 *   all outcomes.
 * - The InCommand is executed and then it is sent command Terminated.
 * - It is checked that the InCommand is in state TERMINATED and that three success outcome reports have been
 *   generated with the correct parameters.
 * .
 * @verify InCommand SM Transition: IPS->ACCEPTED
 * @verify InCommand SM Transition: ACCEPTED->CPS1
 * @verify InCommand SM Transition: CPS1->PROGRESS
 * @verify InCommand SM Transition: PROGRESS->CPS2
 * @verify InCommand SM Transition: CPS2->TERMINATED
 * @verify InCommand Outcome Report: crCmdAckStrSucc
 * @verify InCommand Outcome Report: crCmdAckPrgSucc
 * @verify InCommand Outcome Report: crCmdAckTrmSucc
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInCmdTestCase12();

#endif /* CRFW_INCMD_TESTCASES_H_ */
