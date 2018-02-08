/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the Application State Machine (see <code>CrFwAppSm.h</code>).
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

#ifndef CRFW_APPSM_TESTCASES_H_
#define CRFW_APPSM_TESTCASES_H_

#include "CrFwConstants.h"

/**
 * Check the creation and configuration of the Application State Machine.
 * The following actions are performed in this test:
 * - The Application State Machine (ASM) is created and it is checked that it is in correctly configured
 *   and that it has not yet been started.
 * - An attempt is made to create the ASM a second time and it is checked that the same instance as the
 *   first time is returned.
 * - It is checked that the state machines embedded in the states of the Application State Machine are
 *   correct.
 * - The ASM is started and it is checked that state START_UP is entered and that the Application
 *   Start-Up Procedure has been started.
 * - The ASM is executed and it is checked that it remains in state START_UP.
 * - The Application Start-Up Procedure is executed until it terminates; the ASM is executed again and
 *   it is checked that it makes a transition to state NORMAL.
 * - The ASM is sent command Reset and it is checked that state RESET is entered and that the Application
 *   Reset Procedure has been started.
 * - The ASM is executed and it is checked that it remains in state RESET.
 * - The Application Reset Procedure is executed until it terminates; the ASM is executed again and
 *   it is checked that it makes a transition to state NORMAL.
 * - The ASM is sent command Shutdown and it is checked that state SHUTDOWN is entered and that the Application
 *   Shutdown Procedure has been started.
 * - The ASM is executed and it is checked that it remains in state SHUTDOWN.
 * - The Application Shutdown Procedure is executed until it terminates; the ASM is executed again and
 *   it is checked that it terminates.
 * .
 * @verify Application SM Transition: IPS->START_UP
 * @verify Application SM Transition: START_UP->NORMAL (with transition guard evaluating TRUE)
 * @verify Application SM Transition: START_UP->NORMAL (with transition guard evaluating FALSE)
 * @verify Application SM Transition: NORMAL->RESET
 * @verify Application SM Transition: RESET->NORMAL (with transition guard evaluating TRUE)
 * @verify Application SM Transition: RESET->NORMAL (with transition guard evaluating FALSE)
 * @verify Application SM Transition: NORMAL->SHUTDOWN
 * @verify Application SM Transition: SHUTDOWN->FPS (with transition guard evaluating TRUE)
 * @verify Application SM Transition: SHUTDOWN->FPS (with transition guard evaluating FALSE)
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwAppSmTestCase1();

/**
 * Return the dummy state machine to be embedded in state START-UP of the Application
 * State Machine.
 * @return the dummy state machine to be embedded in state START-UP of the Application
 * State Machine.
 */
FwSmDesc_t CrFwAppSmTestCasesGetStartUpEsm();

/**
 * Return the dummy state machine to be embedded in state NORMAL of the Application
 * State Machine.
 * @return the dummy state machine to be embedded in state NORMAL of the Application
 * State Machine.
 */
FwSmDesc_t CrFwAppSmTestCasesGetNormalEsm();

/**
 * Return the dummy state machine to be embedded in state RESET of the Application
 * State Machine.
 * @return the dummy state machine to be embedded in state RESET of the Application
 * State Machine.
 */
FwSmDesc_t CrFwAppSmTestCasesGetResetEsm();

#endif /* CRFW_APPSM_TESTCASES_H_ */
