/**
 * @file
 *
 * Implementation of OutManager State Machine.
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
#include "CrFwOutManagerUserPar.h"
#include "CrFwCmpData.h"
/* Include framework files */
#include "CrFwConstants.h"
#include "CrFwRepErr.h"
#include "CrFwTime.h"
#include "CrFwOutManager.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "BaseCmp/CrFwInitProc.h"
#include "BaseCmp/CrFwResetProc.h"
#include "BaseCmp/CrFwDummyExecProc.h"
#include "Pckt/CrFwPckt.h"
#include "Pckt/CrFwPcktQueue.h"
#include "OutFactory/CrFwOutFactory.h"
#include "OutRegistry/CrFwOutRegistry.h"
#include "OutCmp/CrFwOutCmp.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmDCreate.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"

/** The sizes of the POCL in the OutManager components. */
static CrFwCounterU2_t outManagerPoclSize[CR_FW_NOF_OUTMANAGER] = CR_FW_OUTMANAGER_POCLSIZE;

/** The descriptors of the OutManager State Machines. */
static FwSmDesc_t outManagerDesc[CR_FW_NOF_OUTMANAGER];

/** The data structures for the OutManager State Machines and their Procedures. */
static CrFwCmpData_t outManagerData[CR_FW_NOF_OUTMANAGER];

/** The component-specific data for the OutManager instances */
static CrFwOutManagerData_t outManagerCmpSpecificData[CR_FW_NOF_OUTMANAGER];

/**
 * Initialization action for OutManagers.
 * This function allocates the memory for the OutManager data structures and
 * initializes them.
 * The outcome of the initialization action is always "success" (the situation
 * where the memory allocation fails is not handled).
 * @param initPr the Initialization Procedure of the OutManager
 */
static void OutManagerInitAction(FwPrDesc_t initPr);

/**
 * Configuration action for OutManagers.
 * This function resets the POCL and releases all OutComponents in the POCL.
 * The outcome of the initialization action is always: "success"
 * @param initPr the Initialization Procedure of the OutManager
 */
static void OutManagerConfigAction(FwPrDesc_t initPr);

/**
 * Shutdown action for OutManager.
 * This function resets the POCL and releases all OutComponents in the POCL.
 * @param smDesc the OutManager state machine
 */
static void OutManagerShutdownAction(FwSmDesc_t smDesc);

/**
 * Implement the logic of the Execution Procedure (see figure below).
 * This function is executed every time the Execution Procedure of the OutManager
 * is executed.
 * @image html OutManagerExecution.png
 * @param execPr the Execution Procedure of the OutManager
 */
static void OutManagerExecAction(FwPrDesc_t execPr);

/*-----------------------------------------------------------------------------------------*/
FwSmDesc_t CrFwOutManagerMake(CrFwInstanceId_t i) {
	FwPrDesc_t resetPr, execPr, initPr;

	if (i >= CR_FW_NOF_OUTMANAGER) {
		CrFwSetAppErrCode(crOutManagerIllId);
		return NULL;
	}

	if (outManagerDesc[i] != NULL) {
		return outManagerDesc[i];	/* The requested SM has already been created */
	}

	/* Create the requested SM as an extension of the base component SM */
	outManagerDesc[i] = FwSmCreateDer(CrFwBaseCmpMake());

	/* Create the Reset Procedure for the OutManager Component */
	resetPr = FwPrCreateDer(CrFwCmpGetResetProc());
	FwPrOverrideAction(resetPr, &CrFwBaseCmpDefConfigAction, &OutManagerConfigAction);

	/* Create the Initialization Procedure for the OutManager Component */
	initPr = FwPrCreateDer(CrFwCmpGetInitProc());
	FwPrOverrideAction(initPr, &CrFwBaseCmpDefInitAction, &OutManagerInitAction);

	/* Create the Execution Procedure for the OutManager Component */
	execPr = FwPrCreateDer(CrFwBaseCmpGetDummyExecProc());
	FwPrOverrideAction(execPr, &CwFwBaseCmpDummyExecAction, &OutManagerExecAction);

	/* Override the Shutdown Action for the OutManager Component */
	FwSmOverrideAction(outManagerDesc[i], &CrFwBaseCmpDefShutdownAction, &OutManagerShutdownAction);

	/* Initialize the data for the requested SM */
	outManagerData[i].outcome = 1;
	outManagerData[i].initProc = initPr;
	outManagerData[i].resetProc = resetPr;
	outManagerData[i].execProc = execPr;
	outManagerData[i].instanceId = i;
	outManagerData[i].typeId = CR_FW_OUTMANAGER_TYPE;
	outManagerData[i].cmpSpecificData = &outManagerCmpSpecificData[i];

	/* Attach the data to the OutManager state machine and to its procedures. */
	FwSmSetData(outManagerDesc[i], &outManagerData[i]);
	FwPrSetData(outManagerData[i].initProc, &outManagerData[i]);
	FwPrSetData(outManagerData[i].resetProc, &outManagerData[i]);
	FwPrSetData(outManagerData[i].execProc, &outManagerData[i]);

	/* Start the OutManager */
	FwSmStart(outManagerDesc[i]);

	return outManagerDesc[i];
}

/*-----------------------------------------------------------------------------------------*/
static void OutManagerExecAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outManagerDataLocal = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwOutManagerData_t* outManagerCSData = (CrFwOutManagerData_t*)outManagerDataLocal->cmpSpecificData;
	CrFwInstanceId_t id = outManagerDataLocal->instanceId;
	FwSmDesc_t outCmp;
	CrFwCounterU2_t i;
	CrFwOutRegistryCmdRepState_t outCmpState;

	outManagerCSData->nextFreePoclPos = 0;
	for (i=0; i<outManagerPoclSize[id]; i++) {
		outCmp = outManagerCSData->pocl[i];
		if (outCmp != NULL) {
			FwSmExecute(outCmp);
			CrFwOutCmpTerminate(outCmp);
			if (CrFwOutCmpIsInAborted(outCmp))
				outCmpState = crOutRegistryAborted;
			else if (CrFwOutCmpIsInPending(outCmp))
				outCmpState = crOutRegistryPending;
			else
				outCmpState = crOutRegistryTerminated;

			if (outCmpState != crOutRegistryPending) {
				CrFwOutRegistryUpdateState(outCmp,outCmpState);
				CrFwOutFactoryReleaseOutCmp(outCmp);
				outManagerCSData->pocl[i] = NULL;
				outManagerCSData->nOfOutCmpInPocl--;
			}
		}
	}
}

/*-----------------------------------------------------------------------------------------*/
void CrFwOutManagerLoad(FwSmDesc_t smDesc, FwSmDesc_t outCmp) {
	CrFwCmpData_t* outManagerDataLocal = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutManagerData_t* outManagerCSData = (CrFwOutManagerData_t*)outManagerDataLocal->cmpSpecificData;
	CrFwInstanceId_t id = outManagerDataLocal->instanceId;
	CrFwCounterU2_t i, freePos, size;

	freePos = outManagerCSData->nextFreePoclPos;
	size = outManagerPoclSize[id];

	/* Check if POCL is already full */
	if (outManagerCSData->nOfOutCmpInPocl == size) {
		CrFwRepErr(crOutManagerPoclFull, outManagerDataLocal->typeId, outManagerDataLocal->instanceId);
		CrFwOutFactoryReleaseOutCmp(outCmp);
		return;
	}

	/* Check if this is the first load request after the OutManager was reset or after it was executed.
	 * If this is the case, find the first free position in the POCL.
	 * NB: Since the for-loop is only entered if the POCL is not full, it will always terminate
	 *     through the break. This means that, when measuring branch coverage, the fall-through case
	 *     at the for-loop will never occur. */
	if (freePos == 0)
		for (i=0; i<size; i++)
			if (outManagerCSData->pocl[i] == NULL) {
				freePos = i;
				break;
			}

	/* POCL is not full --> load outCmp */
	outManagerCSData->pocl[freePos] = outCmp;
	outManagerCSData->nOfOutCmpInPocl++;
	outManagerCSData->nOfLoadedOutCmp++;

	/* Start tracking OutComponent */
	CrFwOutRegistryStartTracking(outCmp);

	/* Identify next free position in POCL */
	for (i=freePos+1; i<size; i++)
		if (outManagerCSData->pocl[i] == NULL) {
			outManagerCSData->nextFreePoclPos = (CrFwCounterU1_t)i;
			return; /* a free position has been found */
		}

	outManagerCSData->nextFreePoclPos = (CrFwCounterU1_t)size;	/* no free position was found */
}

/*-----------------------------------------------------------------------------------------*/
static void OutManagerInitAction(FwPrDesc_t initPr) {
	CrFwCounterU1_t i;
	CrFwCmpData_t* outManagerDataLocal = (CrFwCmpData_t*)FwPrGetData(initPr);
	CrFwOutManagerData_t* outManagerCSData = (CrFwOutManagerData_t*)outManagerDataLocal->cmpSpecificData;
	CrFwInstanceId_t id = outManagerDataLocal->instanceId;
	outManagerCSData->pocl = malloc(sizeof(FwSmDesc_t)*outManagerPoclSize[id]);
	for (i=0; i<outManagerPoclSize[id]; i++)
		outManagerCSData->pocl[i] = NULL;
	outManagerCSData->nOfOutCmpInPocl = 0;
	outManagerDataLocal->outcome = 1;
}

/*-----------------------------------------------------------------------------------------*/
static void OutManagerConfigAction(FwPrDesc_t initPr) {
	CrFwCmpData_t* outManagerDataLocal = (CrFwCmpData_t*)FwPrGetData(initPr);
	CrFwOutManagerData_t* outManagerCSData = (CrFwOutManagerData_t*)outManagerDataLocal->cmpSpecificData;
	CrFwInstanceId_t id = outManagerDataLocal->instanceId;
	CrFwCounterU1_t i;

	for (i=0; i<outManagerPoclSize[id]; i++) {
		if (outManagerCSData->pocl[i] != NULL) {
			CrFwOutFactoryReleaseOutCmp(outManagerCSData->pocl[i]);
			outManagerCSData->pocl[i] = NULL;
		}
	}
	outManagerCSData->nOfOutCmpInPocl = 0;
	outManagerCSData->nOfLoadedOutCmp = 0;
	outManagerCSData->nextFreePoclPos = 0;
	outManagerDataLocal->outcome = 1;
}

/*-----------------------------------------------------------------------------------------*/
static void OutManagerShutdownAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outManagerDataLocal = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutManagerData_t* outManagerCSData = (CrFwOutManagerData_t*)outManagerDataLocal->cmpSpecificData;
	CrFwInstanceId_t id = outManagerDataLocal->instanceId;
	CrFwCounterU1_t i;

	for (i=0; i<outManagerPoclSize[id]; i++) {
		if (outManagerCSData->pocl[i] != NULL) {
			CrFwOutFactoryReleaseOutCmp(outManagerCSData->pocl[i]);
			outManagerCSData->pocl[i] = NULL;
		}
	}
	free(outManagerCSData->pocl);
	outManagerCSData->nOfOutCmpInPocl = 0;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwOutManagerGetNOfPendingOutCmp(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outManagerDataLocal = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutManagerData_t* outManagerCSData = (CrFwOutManagerData_t*)outManagerDataLocal->cmpSpecificData;
	return outManagerCSData->nOfOutCmpInPocl;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU2_t CrFwOutManagerGetNOfLoadedOutCmp(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outManagerDataLocal = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutManagerData_t* outManagerCSData = (CrFwOutManagerData_t*)outManagerDataLocal->cmpSpecificData;
	return outManagerCSData->nOfLoadedOutCmp;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwOutManagerGetPOCLSize(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outManagerDataLocal = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInstanceId_t id = outManagerDataLocal->instanceId;
	return (CrFwCounterU1_t)outManagerPoclSize[id];
}

