/**
 * @file
 * @ingroup appSmgroup
 * Definition of Application State Machine.
 * The Application State Machine implements the application start-up behaviour
 * (see figures below).
 *
 * The Application State Machine is a singleton.
 * Initially, after it has been started through function <code>FwSmStart</code>,
 * it is in state START-UP.
 * At entry into this state, the Application Start-Up Procedure is executed.
 * This procedure is an adaptation point for the application (it is defined in
 * <code>CrFwAppShutdownProc.c</code>).
 *
 * Normal operation takes place in state NORMAL.
 * In particular, the services provided by an application to its users are only
 * guaranteed to be available when the application is in state NORMAL and it is
 * only from this state that the application makes use of the services provided by
 * other applications.
 * Thus, in state NORMAL, an application may assume that its service interfaces
 * are all operational.
 *
 * When state NORMAL is entered or exited, a notification is sent to the users
 * of the application services.
 * The content of this notification is an adaptation point.
 *
 * An application can be reset by sending command Reset to its Application State
 * Machine (this is done through function <code>::CrFwAppSmReset</code>).
 * This causes a transition to state RESET where the Application Reset Procedure
 * is executed.
 * This procedure is an adaptation point for the application (it is defined in
 * <code>CrFwAppResetProc.c</code>).
 *
 * Finally, the orderly shutdown of an application is performed by sending command
 * Shutdown to the Application State Machine (this is done through function
 * <code>::CrFwAppSmShutdown</code>).
 * This triggers a transition to state SHUTDOWN where the Application Shutdown Procedure
 * is executed.
 * This procedure is an adaptation point for the application (it is defined in
 * <code>CrFwAppShutdownProc.c</code>).
 *
 * Applications may define embedded state machines in the states
 * of the Application State Machine.
 * The embedded state machines are adaptation points for the framework.
 * They are defined in <code>CrFwAppSmUserPar.h</code>.
 *
 * @image html ApplicationSM.png
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

#ifndef CRFW_APP_SM_H_
#define CRFW_APP_SM_H_

/* Include FW Profile Files */
#include "FwSmConstants.h"
#include "FwPrConstants.h"
/* Include Framework Files */
#include "CrFwConstants.h"
/* Include Configuration Files */
#include "CrFwUserConstants.h"

/**
 * Retrieve the singleton instance of the Application State Machine.
 * The Application State Machine is a singleton.
 * The first time this function is called, it creates the Application State
 * Machine.
 * Subsequently, it always returns the same instance.
 *
 * The first time this function is called, it returns the Application State Machine
 * before it has been started.
 * @return the descriptor of the Application State Machine or NULL
 * if the state machine could not be created.
 */
FwSmDesc_t CrFwAppSmMake();

/**
 * Start the Application State Machine.
 * This function causes the Application State Machine to make the transition from
 * its initial pseudo-state into its initial state START_UP.
 */
void CrFwAppSmStart();

/**
 * Execute the Application State Machine.
 * This function sends command <code>Execute</code> to the Application State Machine.
 */
void CrFwAppSmExecute();

/**
 * Reset the Application State Machine.
 * This function sends command <code>Reset</code> to the Application State Machine.
 */
void CrFwAppSmReset();

/**
 * Shutdown the Application State Machine.
 * This function sends command <code>Shutdown</code> to the Application State Machine.
 */
void CrFwAppSmShutdown();

/**
 * Return true if the Application State Machine has been started.
 * @return 1 if the Application State Machine has been started; 0 otherwise
 */
CrFwBool_t CrFwAppSmIsStarted();

/**
 * Return true if the Application State Machine is in state START_UP.
 * @return 1 if the Application State Machine is in state START_UP; 0 otherwise
 */
CrFwBool_t CrFwAppSmIsInStartUp();

/**
 * Return true if the Application State Machine is in state NORMAL.
 * @return 1 if the Application State Machine is in state NORMAL; 0 otherwise
 */
CrFwBool_t CrFwAppSmIsInNormal();

/**
 * Return true if the Application State Machine is in state RESET.
 * @return 1 if the Application State Machine is in state RESET; 0 otherwise
 */
CrFwBool_t CrFwAppSmIsInReset();

/**
 * Return true if the Application State Machine is in state SHUTDOWN.
 * @return 1 if the Application State Machine is in state SHUTDOWN; 0 otherwise
 */
CrFwBool_t CrFwAppSmIsInShutdown();

/**
 * Return the state machine embedded in state START-UP (or NULL if no state machine
 * is embedded in START-UP).
 * @return the state machine embedded in state START-UP (or NULL if no state machine
 * is embedded in START-UP)
 */
FwSmDesc_t CrFwAppSmGetEsmStartUp();

/**
 * Return the state machine embedded in state NORMAL (or NULL if no state machine
 * is embedded in NORMAL).
 * @return the state machine embedded in state NORMAL (or NULL if no state machine
 * is embedded in NORMAL)
 */
FwSmDesc_t CrFwAppSmGetEsmNormal();

/**
 * Return the state machine embedded in state RESET (or NULL if no state machine
 * is embedded in RESET).
 * @return the state machine embedded in state RESET (or NULL if no state machine
 * is embedded in RESET)
 */
FwSmDesc_t CrFwAppSmGetEsmReset();

/**
 * Return the state machine embedded in state SHUTDOWN (or NULL if no state machine
 * is embedded in SHUTDOWN).
 * @return the state machine embedded in state SHUTDOWN (or NULL if no state machine
 * is embedded in SHUTDOWN)
 */
FwSmDesc_t CrFwAppSmGetEsmShutdown();

#endif /* CRFW_APP_SM_H_ */
