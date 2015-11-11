/**
 * @file
 *
 * Implementation of Application State Machine.
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

#include <stdlib.h>
/* Include framework files */
#include "CrFwConstants.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "CrFwAppSm.h"
#include "CrFwAppStartUpProc.h"
#include "CrFwAppResetProc.h"
#include "CrFwAppShutdownProc.h"
/* Include FW Profile files */
#include "FwProfile/FwSmConstants.h"
#include "FwProfile/FwSmDCreate.h"
#include "FwProfile/FwSmConfig.h"
#include "FwProfile/FwSmCore.h"
#include "FwProfile/FwPrConstants.h"
#include "FwProfile/FwPrDCreate.h"
#include "FwProfile/FwPrConfig.h"
#include "FwProfile/FwPrCore.h"
/* Include FW Profile files */
#include "CrFwAppSmUserPar.h"

/** State identifier for state START_UP in the application State Machine. */
#define CR_FW_APP_STATE_START_UP 1

/** State identifier for state NORMAL in the application State Machine. */
#define CR_FW_APP_STATE_NORMAL 2

/** State identifier for state RESET in the application State Machine. */
#define CR_FW_APP_STATE_RESET 3

/** State identifier for state SHUTDOWN in the application State Machine. */
#define CR_FW_APP_STATE_SHUTDOWN 4

/** Identifier for transition command "Reset" in the Application State Machine. */
#define CR_FW_APP_TR_RESET CR_FW_APP_TYPE*CR_FW_MAX_NOF_TRANS_CMDS+0

/** Identifier for transition command "Shutdown" in the Application State Machine. */
#define CR_FW_APP_TR_SHUTDOWN CR_FW_APP_TYPE*CR_FW_MAX_NOF_TRANS_CMDS+1

/** The singleton instance of the Application State Machine. */
static FwSmDesc_t appSmDesc = NULL;

/**
 * Function which starts the Application Start-Up Procedure.
 * This function is used as entry action for the START_UP state.
 * @param smDesc the state machine descriptor
 */
static void StartAppStartUpPr(FwSmDesc_t smDesc);

/**
 * Function which starts the Application Reset Procedure.
 * This function is used as entry action for the RESET state.
 * @param smDesc the state machine descriptor
 */
static void StartAppResetPr(FwSmDesc_t smDesc);

/**
 * Function which starts the Application Shutdown Procedure.
 * This function is used as entry action for the SHUTDOWN state.
 * @param smDesc the state machine descriptor
 */
static void StartAppShutdownPr(FwSmDesc_t smDesc);

/**
 * Function which checks whether the Application Start-Up Procedure has terminated.
 * This function acts as guard on the transition out of START_UP.
 * @param smDesc the state machine descriptor
 * @return 1 if the Application Start-Up Procedure has terminated, 0 otherwise
 */
static FwSmBool_t IsStartUpPrTerminated(FwSmDesc_t smDesc);

/**
 * Function which checks whether the Application Reset Procedure has terminated.
 * This function acts as guard on the transition out of RESET.
 * @param smDesc the state machine descriptor
 * @return 1 if the Application Reset Procedure has terminated, 0 otherwise
 */
static FwSmBool_t IsResetPrTerminated(FwSmDesc_t smDesc);

/**
 * Function which checks whether the Application Shutdown Procedure has terminated.
 * This function acts as guard on the transition out of SHUTDOWN.
 * @param smDesc the state machine descriptor
 * @return 1 if the Application Shutdown Procedure has terminated, 0 otherwise
 */
static FwSmBool_t IsShutdownPrTerminated(FwSmDesc_t smDesc);

/*-----------------------------------------------------------------------------------------*/
FwSmDesc_t CrFwAppSmMake() {
	FwSmCounterS1_t nOfStates = 4;	/* Number of states */
	FwSmCounterS1_t nOfChoicePseudoStates = 0;	/* Number of choice pseudo-states */
	FwSmCounterS1_t nOfTrans = 6;	/* Number of transitions */
	FwSmCounterS1_t nOfActions = 3;	/* Number of actions */
	FwSmCounterS1_t nOfGuards = 3;	/* Number of guards */

	if (appSmDesc != NULL)
		return appSmDesc;

	/* Create the application state machine */
	appSmDesc = FwSmCreate(nOfStates, nOfChoicePseudoStates, nOfTrans, nOfActions, nOfGuards);

	/* Configure the application state machine */
	FwSmAddState(appSmDesc, CR_FW_APP_STATE_START_UP, 1, &StartAppStartUpPr, NULL, NULL, CR_FW_APPSM_STARTUP_ESM);
	FwSmAddState(appSmDesc, CR_FW_APP_STATE_NORMAL, 2, NULL, NULL, NULL, CR_FW_APPSM_NORMAL_ESM);
	FwSmAddState(appSmDesc, CR_FW_APP_STATE_RESET, 1, &StartAppResetPr, NULL, NULL, CR_FW_APPSM_RESET_ESM);
	FwSmAddState(appSmDesc, CR_FW_APP_STATE_SHUTDOWN, 1, &StartAppShutdownPr, NULL, NULL, CR_FW_APPSM_SHUTDOWN_ESM);
	FwSmAddTransIpsToSta(appSmDesc, CR_FW_APP_STATE_START_UP, NULL);
	FwSmAddTransStaToSta(appSmDesc, FW_TR_EXECUTE, CR_FW_APP_STATE_START_UP, CR_FW_APP_STATE_NORMAL,
	                     NULL, &IsStartUpPrTerminated);
	FwSmAddTransStaToSta(appSmDesc, CR_FW_APP_TR_RESET, CR_FW_APP_STATE_NORMAL, CR_FW_APP_STATE_RESET,
	                     NULL, NULL);
	FwSmAddTransStaToSta(appSmDesc, FW_TR_EXECUTE, CR_FW_APP_STATE_RESET, CR_FW_APP_STATE_NORMAL,
	                     NULL, &IsResetPrTerminated);
	FwSmAddTransStaToSta(appSmDesc, CR_FW_APP_TR_SHUTDOWN, CR_FW_APP_STATE_NORMAL, CR_FW_APP_STATE_SHUTDOWN,
	                     NULL, NULL);
	FwSmAddTransStaToFps(appSmDesc, FW_TR_EXECUTE, CR_FW_APP_STATE_SHUTDOWN, NULL, &IsShutdownPrTerminated);

	return appSmDesc;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwAppSmStart() {
	FwSmStart(appSmDesc);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwAppSmExecute() {
	FwSmExecute(appSmDesc);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwAppSmReset() {
	FwSmMakeTrans(appSmDesc, CR_FW_APP_TR_RESET);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwAppSmShutdown() {
	FwSmMakeTrans(appSmDesc, CR_FW_APP_TR_SHUTDOWN);
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwAppSmIsStarted() {
	return FwSmIsStarted(appSmDesc);
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwAppSmIsInStartUp() {
	return (FwSmGetCurState(appSmDesc) == CR_FW_APP_STATE_START_UP);
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwAppSmIsInNormal() {
	return (FwSmGetCurState(appSmDesc) == CR_FW_APP_STATE_NORMAL);
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwAppSmIsInReset() {
	return (FwSmGetCurState(appSmDesc) == CR_FW_APP_STATE_RESET);
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwAppSmIsInShutdown() {
	return (FwSmGetCurState(appSmDesc) == CR_FW_APP_STATE_SHUTDOWN);
}

/*-----------------------------------------------------------------------------------------*/
static void StartAppStartUpPr(FwSmDesc_t smDesc) {
	(void)(smDesc);
	FwPrStart(CrFwAppSmGetAppStartUpProc());
	return;
}

/*-----------------------------------------------------------------------------------------*/
static void StartAppResetPr(FwSmDesc_t smDesc) {
	(void)(smDesc);
	FwPrStart(CrFwAppSmGetAppResetProc());
	return;
}

/*-----------------------------------------------------------------------------------------*/
static void StartAppShutdownPr(FwSmDesc_t smDesc) {
	(void)(smDesc);
	FwPrStart(CrFwAppSmGetAppShutdownProc());
	return;
}

/*-----------------------------------------------------------------------------------------*/
static FwSmBool_t IsStartUpPrTerminated(FwSmDesc_t smDesc) {
	(void)(smDesc);
	return (FwPrIsStarted(CrFwAppSmGetAppStartUpProc()) == 0);
}

/*-----------------------------------------------------------------------------------------*/
static FwSmBool_t IsResetPrTerminated(FwSmDesc_t smDesc) {
	(void)(smDesc);
	return (FwPrIsStarted(CrFwAppSmGetAppResetProc()) == 0);
}

/*-----------------------------------------------------------------------------------------*/
static FwSmBool_t IsShutdownPrTerminated(FwSmDesc_t smDesc) {
	(void)(smDesc);
	return (FwPrIsStarted(CrFwAppSmGetAppShutdownProc()) == 0);
}

/*-----------------------------------------------------------------------------------------*/
FwSmDesc_t CrFwAppSmGetEsmStartUp() {
	return FwSmGetEmbSm(appSmDesc, CR_FW_APP_STATE_START_UP);
}

/*-----------------------------------------------------------------------------------------*/
FwSmDesc_t CrFwAppSmGetEsmNormal() {
	return FwSmGetEmbSm(appSmDesc, CR_FW_APP_STATE_NORMAL);
}

/*-----------------------------------------------------------------------------------------*/
FwSmDesc_t CrFwAppSmGetEsmReset() {
	return FwSmGetEmbSm(appSmDesc, CR_FW_APP_STATE_RESET);
}

/*-----------------------------------------------------------------------------------------*/
FwSmDesc_t CrFwAppSmGetEsmShutdown()  {
	return FwSmGetEmbSm(appSmDesc, CR_FW_APP_STATE_SHUTDOWN);
}
