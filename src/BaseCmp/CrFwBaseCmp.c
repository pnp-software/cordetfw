/**
 * @file
 *
 * Implementation of Base State Machine.
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
#include "CrFwBaseCmp.h"
#include "CrFwInitProc.h"
#include "CrFwResetProc.h"
/* Include FW Profile files */
#include "FwProfile/FwSmConstants.h"
#include "FwProfile/FwSmDCreate.h"
#include "FwProfile/FwSmConfig.h"
#include "FwProfile/FwSmCore.h"
#include "FwProfile/FwPrConstants.h"
#include "FwProfile/FwPrDCreate.h"
#include "FwProfile/FwPrConfig.h"
#include "FwProfile/FwPrCore.h"
/* Include configuration files */
#include "CrFwCmpData.h"

/** The singleton instance of the Base State Machine. */
static FwSmDesc_t baseCmpSmDesc = NULL;

/**
 * Function which runs the Component Initialization Procedure.
 * This function is used as exit action for the CREATED state.
 * @param smDesc the state machine descriptor
 */
static void RunCIP(FwSmDesc_t smDesc);

/**
 * Function which runs the Component Reset Procedure.
 * This function is used as exit action for the INITIALIZED state.
 * @param smDesc the state machine descriptor
 */
static void RunCRP(FwSmDesc_t smDesc);

/**
 * Function which starts the Component Execution Procedure.
 * This function is used as entry action for the CONFIGURED state.
 * @param smDesc the state machine descriptor
 */
static void StartCEP(FwSmDesc_t smDesc);

/**
 * Function which executes the Component Execution Procedure.
 * This function is used as do-action for the CONFIGURED state.
 * @param smDesc the state machine descriptor
 */
static void ExecCEP(FwSmDesc_t smDesc);

/**
 * Function which stops the Component Execution Procedure.
 * This function is used as exit action for the CONFIGURED state.
 * @param smDesc the state machine descriptor
 */
static void StopCEP(FwSmDesc_t smDesc);

/*-----------------------------------------------------------------------------------------*/
FwSmDesc_t CrFwBaseCmpMake() {
	FwSmCounterS1_t nOfStates = 3;	/* Number of states */
	FwSmCounterS1_t nOfChoicePseudoStates = 2;	/* Number of choice pseudo-states */
	FwSmCounterS1_t nOfTrans = 9;	/* Number of transitions */
	FwSmCounterS1_t nOfActions = 6;	/* Number of actions */
	FwSmCounterS1_t nOfGuards = 1;	/* Number of guards */
	FwSmCounterS1_t CPS_1 = 1;		/* Identifier of first choice pseudo-state */
	FwSmCounterS1_t CPS_2 = 2;		/* Identifier of second choice pseudo-state */

	if (baseCmpSmDesc != NULL)
		return baseCmpSmDesc;

	/* Create the base component state machine */
	baseCmpSmDesc = FwSmCreate(nOfStates, nOfChoicePseudoStates, nOfTrans, nOfActions, nOfGuards);

	/* Configure the base component state machine */
	FwSmAddState(baseCmpSmDesc, CR_FW_BASE_STATE_CREATED, 1, NULL, &RunCIP, NULL, NULL);
	FwSmAddState(baseCmpSmDesc, CR_FW_BASE_STATE_INITIALIZED, 1, NULL, &RunCRP, NULL, NULL);
	FwSmAddState(baseCmpSmDesc, CR_FW_BASE_STATE_CONFIGURED, 2, &StartCEP, &StopCEP, &ExecCEP, NULL);
	FwSmAddChoicePseudoState(baseCmpSmDesc, CPS_1, 2);
	FwSmAddChoicePseudoState(baseCmpSmDesc, CPS_2, 2);
	FwSmAddTransIpsToSta(baseCmpSmDesc, CR_FW_BASE_STATE_CREATED, NULL);
	FwSmAddTransStaToCps(baseCmpSmDesc, CR_FW_BASE_TR_INIT, CR_FW_BASE_STATE_CREATED, CPS_1, NULL, NULL);
	FwSmAddTransCpsToSta(baseCmpSmDesc, CPS_1, CR_FW_BASE_STATE_INITIALIZED, NULL, &CrFwIsSmOutcomeOne);
	FwSmAddTransCpsToSta(baseCmpSmDesc, CPS_1, CR_FW_BASE_STATE_CREATED, NULL, NULL);	/* Else Transition */
	FwSmAddTransStaToCps(baseCmpSmDesc, CR_FW_BASE_TR_RESET, CR_FW_BASE_STATE_INITIALIZED, CPS_2, NULL, NULL);
	FwSmAddTransCpsToSta(baseCmpSmDesc, CPS_2, CR_FW_BASE_STATE_CONFIGURED, NULL, &CrFwIsSmOutcomeOne);
	FwSmAddTransCpsToSta(baseCmpSmDesc, CPS_2, CR_FW_BASE_STATE_INITIALIZED, NULL, NULL);	/* Else Transition */
	FwSmAddTransStaToCps(baseCmpSmDesc, CR_FW_BASE_TR_RESET, CR_FW_BASE_STATE_CONFIGURED, CPS_2, &RunCRP, NULL);
	FwSmAddTransStaToFps(baseCmpSmDesc, CR_FW_BASE_TR_SHUTDOWN, CR_FW_BASE_STATE_CONFIGURED, &CrFwBaseCmpDefShutdownAction, NULL);

	return baseCmpSmDesc;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwCmpInit(FwSmDesc_t smDesc) {
	FwSmMakeTrans(smDesc, CR_FW_BASE_TR_INIT);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwCmpReset(FwSmDesc_t smDesc) {
	FwSmMakeTrans(smDesc, CR_FW_BASE_TR_RESET);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwCmpShutdown(FwSmDesc_t smDesc) {
	FwSmMakeTrans(smDesc, CR_FW_BASE_TR_SHUTDOWN);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwCmpExecute(FwSmDesc_t smDesc) {
	FwSmMakeTrans(smDesc, FW_TR_EXECUTE);
}

/*-----------------------------------------------------------------------------------------*/
FwPrDesc_t CrFwCmpGetInitPr(FwSmDesc_t smDesc) {
	CrFwCmpData_t* baseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	return baseData->initProc;
}

/*-----------------------------------------------------------------------------------------*/
FwPrDesc_t CrFwCmpGetResetPr(FwSmDesc_t smDesc) {
	CrFwCmpData_t* baseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	return baseData->resetProc;
}

/*-----------------------------------------------------------------------------------------*/
FwPrDesc_t CrFwCmpGetExecPr(FwSmDesc_t smDesc) {
	CrFwCmpData_t* baseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	return baseData->execProc;
}

/*-----------------------------------------------------------------------------------------*/
CrFwInstanceId_t CrFwCmpGetInstanceId(FwSmDesc_t smDesc) {
	CrFwCmpData_t* baseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	return baseData->instanceId;
}

/*-----------------------------------------------------------------------------------------*/
CrFwTypeId_t CrFwCmpGetTypeId(FwSmDesc_t smDesc) {
	CrFwCmpData_t* baseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	return baseData->typeId;
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwCmpIsStarted(FwSmDesc_t smDesc) {
	return FwSmIsStarted(smDesc);
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwCmpIsInCreated(FwSmDesc_t smDesc) {
	return (FwSmGetCurState(smDesc) == CR_FW_BASE_STATE_CREATED);
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwCmpIsInInitialized(FwSmDesc_t smDesc) {
	return (FwSmGetCurState(smDesc) == CR_FW_BASE_STATE_INITIALIZED);
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwCmpIsInConfigured(FwSmDesc_t smDesc) {
	return (FwSmGetCurState(smDesc) == CR_FW_BASE_STATE_CONFIGURED);
}

/*-----------------------------------------------------------------------------------------*/
static void RunCIP(FwSmDesc_t smDesc) {
	CrFwCmpData_t* baseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	FwPrRun(baseData->initProc);
	return;
}

/*-----------------------------------------------------------------------------------------*/
static void RunCRP(FwSmDesc_t smDesc) {
	CrFwCmpData_t* baseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	FwPrRun(baseData->resetProc);
	return;
}

/*-----------------------------------------------------------------------------------------*/
static void StartCEP(FwSmDesc_t smDesc) {
	CrFwCmpData_t* baseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	FwPrStart(baseData->execProc);
	return;
}

/*-----------------------------------------------------------------------------------------*/
static void StopCEP(FwSmDesc_t smDesc) {
	CrFwCmpData_t* baseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	FwPrStop(baseData->execProc);
	return;
}

/*-----------------------------------------------------------------------------------------*/
static void ExecCEP(FwSmDesc_t smDesc) {
	CrFwCmpData_t* baseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	FwPrExecute(baseData->execProc);
	return;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwBaseCmpDefShutdownAction(FwSmDesc_t smDesc) {
	CRFW_UNUSED(smDesc);
	return;
}



