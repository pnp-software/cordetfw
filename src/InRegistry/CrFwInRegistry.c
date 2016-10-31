/**
 * @file
 *
 * Implementation of InRegistry component.
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
/* Include configuration files */
#include "CrFwInRegistryUserPar.h"
#include "CrFwCmpData.h"
/* Include framework files */
#include "CrFwConstants.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "OutCmp/CrFwOutCmp.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "BaseCmp/CrFwInitProc.h"
#include "BaseCmp/CrFwResetProc.h"
#include "BaseCmp/CrFwDummyExecProc.h"
#include "CrFwInRegistry.h"
/* Include FW Profile files */
#include "FwPrConfig.h"
#include "FwPrDCreate.h"
#include "FwSmConfig.h"
#include "FwSmDCreate.h"
#include "FwPrCore.h"

/**
 * An instance of this type holds the information about an incoming command or report
 * which is being tracked by the OuRegistry.
 */
typedef struct {
	/** The identifier of the incoming command or report */
	CrFwInstanceId_t instanceId;
	/** The state of the incoming command or report */
	CrFwInRegistryCmdRepState_t state;
} CrFwTrackedState_t;

/** Array to track the state of incoming commands or reports */
static CrFwTrackedState_t cmdRepState[CR_FW_OUTREGISTRY_N];

/** The index of the most recent entry in <code>cmdRepState</code>. */
static CrFwTrackingIndex_t cmdRepStateIndex = 0;

/** The InRegistry singleton. */
static FwSmDesc_t inRegistry = NULL;

/** The data for the InRegistry singleton. */
static CrFwCmpData_t inRegistryData;

/**
 * Configuration action for InRegistry.
 * This function resets the queue of tracked commands and reports.
 * The outcome of the configuration action is always: "successful"
 * @param resetPr the Configuration Procedure of the InRegistry
 */
static void InRegistryConfigAction(FwPrDesc_t resetPr);

/**
 * Shutdown action for InRegistry.
 * This function resets the queue of tracked commands and reports.
 * @param smDesc the InRegistry state machine
 */
static void InRegistryShutdownAction(FwSmDesc_t smDesc);

/*------------------------------------------------------------------------------------*/
FwSmDesc_t CrFwInRegistryMake() {
	FwPrDesc_t resetPr, execPr, initPr;

	if (inRegistry != NULL) {
		return inRegistry;
	}

	/* Extend the Base Component */
	inRegistry = FwSmCreateDer(CrFwBaseCmpMake());

	/* Create the Reset Procedure for the OuRegistry Component */
	resetPr = FwPrCreateDer(CrFwCmpGetResetProc());
	FwPrOverrideAction(resetPr, &CrFwBaseCmpDefConfigAction, &InRegistryConfigAction);

	/* Create the Initialization Procedure for the OuRegistry Component */
	initPr = FwPrCreateDer(CrFwCmpGetInitProc());

	/* Override the Shutdown Action for the InStream Component */
	FwSmOverrideAction(inRegistry, &CrFwBaseCmpDefShutdownAction, &InRegistryShutdownAction);

	/* Get the Dummy Execution Procedure for the InRegistry Component */
	execPr = CrFwBaseCmpGetDummyExecProc();

	/* Initialize the data for the requested SM */
	inRegistryData.outcome = 1;
	inRegistryData.initProc = initPr;
	inRegistryData.resetProc = resetPr;
	inRegistryData.execProc = execPr;
	inRegistryData.instanceId = 0;
	inRegistryData.typeId = CR_FW_INREGISTRY_TYPE;

	/* Attach the data to the InRegistry state machine and to its procedures. */
	FwSmSetData(inRegistry, &inRegistryData);
	FwPrSetData(inRegistryData.initProc, &inRegistryData);
	FwPrSetData(inRegistryData.resetProc, &inRegistryData);

	/* Start the InRegistry */
	FwSmStart(inRegistry);

	return inRegistry;
}

/*------------------------------------------------------------------------------------*/
void CrFwInRegistryStartTracking(FwSmDesc_t inCmp) {
	CrFwCmpData_t* inCmpData = (CrFwCmpData_t*)FwSmGetData(inCmp);
	CrFwInCmdData_t* inCmdCmpSpecificData;
	CrFwInRepData_t* inRepCmpSpecificData;

	cmdRepState[cmdRepStateIndex].instanceId = inCmpData->instanceId;
	cmdRepState[cmdRepStateIndex].state = crInRegistryPending;
	if (inCmpData->typeId == CR_FW_INREPORT_TYPE) {
		inRepCmpSpecificData = (CrFwInRepData_t*)(inCmpData->cmpSpecificData);
		inRepCmpSpecificData->trackingIndex = cmdRepStateIndex;
	} else {
		inCmdCmpSpecificData = (CrFwInCmdData_t*)(inCmpData->cmpSpecificData);
		inCmdCmpSpecificData->trackingIndex = cmdRepStateIndex;
	}

	if (cmdRepStateIndex == (CR_FW_OUTREGISTRY_N-1))
		cmdRepStateIndex = 0;
	else
		cmdRepStateIndex++;
}

/*------------------------------------------------------------------------------------*/
void CrFwInRegistryUpdateState(FwSmDesc_t inCmp, CrFwInRegistryCmdRepState_t newState) {
	CrFwCmpData_t* inCmpData = (CrFwCmpData_t*)FwSmGetData(inCmp);
	CrFwInCmdData_t* inCmdCmpSpecificData;
	CrFwInRepData_t* inRepCmpSpecificData;
	CrFwTrackingIndex_t i;

	if (inCmpData->typeId == CR_FW_INREPORT_TYPE) {
		inRepCmpSpecificData = (CrFwInRepData_t*)(inCmpData->cmpSpecificData);
		i = inRepCmpSpecificData->trackingIndex;
	} else {
		inCmdCmpSpecificData = (CrFwInCmdData_t*)(inCmpData->cmpSpecificData);
		i = inCmdCmpSpecificData->trackingIndex;
	}
	if (cmdRepState[i].instanceId == inCmpData->instanceId) {
		cmdRepState[i].state = newState;
	}
}

/*------------------------------------------------------------------------------------*/
CrFwInRegistryCmdRepState_t CrFwInRegistryGetState(CrFwInstanceId_t cmdRepId) {
	CrFwTrackingIndex_t i;
	CrFwTrackingIndex_t j;

	if (cmdRepStateIndex > 0)
		i = (CrFwTrackingIndex_t)(cmdRepStateIndex-1);
	else
		i = (CR_FW_OUTREGISTRY_N-1);

	for (j=0; j<CR_FW_OUTREGISTRY_N; j++) {
		if (cmdRepState[i].state == crInRegistryNoEntry)
			break;
		if (cmdRepState[i].instanceId == cmdRepId) {
			return cmdRepState[i].state;
		} else if (i == 0)
			i = (CR_FW_OUTREGISTRY_N-1);
		else
			i--;
	}

	return crInRegistryNotTracked;
}

/*------------------------------------------------------------------------------------*/
static void InRegistryConfigAction(FwPrDesc_t initPr) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwPrGetData(initPr);
	CrFwCounterU2_t k;

	for (k=0; k<CR_FW_OUTREGISTRY_N; k++)
		cmdRepState[k].state = crInRegistryNoEntry;

	cmdRepStateIndex = 0;

	cmpData->outcome = 1;
}

/*------------------------------------------------------------------------------------*/
static void InRegistryShutdownAction(FwSmDesc_t smDesc) {
	CrFwCounterU2_t k;
	CRFW_UNUSED(smDesc);

	for (k=0; k<CR_FW_OUTREGISTRY_N; k++)
		cmdRepState[k].state = crInRegistryNoEntry;

	cmdRepStateIndex = 0;
}
