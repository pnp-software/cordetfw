/**
 * @file
 *
 * Implementation of InManager State Machine.
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
#include "CrFwInManagerUserPar.h"
#include "CrFwCmpData.h"
/* Include framework files */
#include "CrFwInManager.h"
#include "CrFwConstants.h"
#include "CrFwRepErr.h"
#include "CrFwTime.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "BaseCmp/CrFwInitProc.h"
#include "BaseCmp/CrFwResetProc.h"
#include "BaseCmp/CrFwDummyExecProc.h"
#include "Pckt/CrFwPckt.h"
#include "Pckt/CrFwPcktQueue.h"
#include "InRegistry/CrFwInRegistry.h"
#include "InFactory/CrFwInFactory.h"
#include "InCmd/CrFwInCmd.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include FW Profile files */
#include "FwProfile/FwSmConstants.h"
#include "FwProfile/FwSmDCreate.h"
#include "FwProfile/FwSmConfig.h"
#include "FwProfile/FwSmCore.h"
#include "FwProfile/FwPrConstants.h"
#include "FwProfile/FwPrDCreate.h"
#include "FwProfile/FwPrConfig.h"
#include "FwProfile/FwPrCore.h"

/** The sizes of the PCRL in the InManager components. */
static CrFwCounterU2_t inManagerPcrlSize[CR_FW_NOF_INMANAGER] = CR_FW_INMANAGER_PCRLSIZE;

/** The descriptors of the InManager State Machines. */
static FwSmDesc_t inManagerDesc[CR_FW_NOF_INMANAGER];

/** The data structures for the InManager State Machines and their Procedures. */
static CrFwCmpData_t inManagerData[CR_FW_NOF_INMANAGER];

/** The component-specific data for the InManager instances */
static CrFwInManagerData_t inManagerCmpSpecificData[CR_FW_NOF_INMANAGER];

/**
 * Initialization action for InManagers.
 * This function allocates the memory for the InManager data structures and
 * initializes them.
 * The outcome of the initialization action is always "success" (the situation
 * where the memory allocation fails is not handled).
 * @param initPr the Initialization Procedure of the InManager
 */
static void InManagerInitAction(FwPrDesc_t initPr);

/**
 * Configuration action for InManagers.
 * This function resets the PCRL, releases all InCommands and InReports in the PCRL
 * and resets the counter of successfully loaded InReports or InCommands.
 * The outcome of the initialization action is always: "success"
 * @param initPr the Initialization Procedure of the InManager
 */
static void InManagerConfigAction(FwPrDesc_t initPr);

/**
 * Shutdown action for InManager.
 * This function resets the PCRL and releases all InCommands and InReports in the PCRL.
 * @param smDesc the InManager state machine
 */
static void InManagerShutdownAction(FwSmDesc_t smDesc);

/**
 * Implement the logic of the Execution Procedure (see figure below).
 * This function is executed every time the Execution Procedure of the InManager
 * is executed.
 * @image html InManagerExecution.png
 * @param execPr the Execution Procedure of the InManager
 */
static void InManagerExecAction(FwPrDesc_t execPr);

/*-----------------------------------------------------------------------------------------*/
FwSmDesc_t CrFwInManagerMake(CrFwInstanceId_t i) {
	FwPrDesc_t resetPr, execPr, initPr;

	if (i >= CR_FW_NOF_INMANAGER) {
		CrFwSetAppErrCode(crInManagerIllId);
		return NULL;
	}

	if (inManagerDesc[i] != NULL) {
		return inManagerDesc[i];	/* The requested SM has already been created */
	}

	/* Create the requested SM as an extension of the base component SM */
	inManagerDesc[i] = FwSmCreateDer(CrFwBaseCmpMake());

	/* Create the Reset Procedure for the InManager Component */
	resetPr = FwPrCreateDer(CrFwCmpGetResetProc());
	FwPrOverrideAction(resetPr, &CrFwBaseCmpDefConfigAction, &InManagerConfigAction);

	/* Create the Initialization Procedure for the InManager Component */
	initPr = FwPrCreateDer(CrFwCmpGetInitProc());
	FwPrOverrideAction(initPr, &CrFwBaseCmpDefInitAction, &InManagerInitAction);

	/* Create the Execution Procedure for the InManager Component */
	execPr = FwPrCreateDer(CrFwBaseCmpGetDummyExecProc());
	FwPrOverrideAction(execPr, &CwFwBaseCmpDummyExecAction, &InManagerExecAction);

	/* Override the Shutdown Action for the InManager Component */
	FwSmOverrideAction(inManagerDesc[i], &CrFwBaseCmpDefShutdownAction, &InManagerShutdownAction);

	/* Initialize the data for the requested SM */
	inManagerData[i].outcome = 1;
	inManagerData[i].initProc = initPr;
	inManagerData[i].resetProc = resetPr;
	inManagerData[i].execProc = execPr;
	inManagerData[i].instanceId = i;
	inManagerData[i].typeId = CR_FW_INMANAGER_TYPE;
	inManagerData[i].cmpSpecificData = &inManagerCmpSpecificData[i];

	/* Attach the data to the InLoader state machine and to its procedures. */
	FwSmSetData(inManagerDesc[i], &inManagerData[i]);
	FwPrSetData(inManagerData[i].initProc, &inManagerData[i]);
	FwPrSetData(inManagerData[i].resetProc, &inManagerData[i]);
	FwPrSetData(inManagerData[i].execProc, &inManagerData[i]);

	/* Start the InManager */
	FwSmStart(inManagerDesc[i]);

	return inManagerDesc[i];
}

/*-----------------------------------------------------------------------------------------*/
static void InManagerExecAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* inManagerData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwInManagerData_t* inManagerCSData = (CrFwInManagerData_t*)inManagerData->cmpSpecificData;
	CrFwInstanceId_t id = inManagerData->instanceId;
	FwSmDesc_t inCmp;
	CrFwCmpData_t* inCmpData;
	CrFwCounterU2_t i;
	CrFwInRegistryCmdRepState_t inCmpState;

	for (i=0; i<inManagerPcrlSize[id]; i++) {
		inCmp = inManagerCSData->pcrl[i];
		if (inCmp != NULL) {
			FwSmExecute(inCmp);
			inCmpData = (CrFwCmpData_t*)FwSmGetData(inCmp);
			if (inCmpData->typeId == CR_FW_INREPORT_TYPE) {
				inCmpState = crInRegistryTerminated;
			} else {
				CrFwInCmdTerminate(inCmp);
				if (CrFwInCmdIsInAborted(inCmp))
					inCmpState = crInRegistryAborted;
				else if (CrFwInCmdIsInTerminated(inCmp))
					inCmpState = crInRegistryTerminated;
				else
					inCmpState = crInRegistryPending;
			}
			if (inCmpState != crInRegistryPending) {
				CrFwInRegistryUpdateState(inCmp, inCmpState);
				/* Remove inCmp from PCRL */
				inManagerCSData->pcrl[i] = NULL;
				inManagerCSData->nOfInCmpInPcrl--;
				inManagerCSData->nextFreePcrlPos = (CrFwCounterU1_t)i;
				if (inCmpData->typeId == CR_FW_INREPORT_TYPE)
					CrFwInFactoryReleaseInRep(inCmp);
				else
					CrFwInFactoryReleaseInCmd(inCmp);
			}
		}
	}
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInManagerLoad(FwSmDesc_t smDesc, FwSmDesc_t inCmp) {
	CrFwCmpData_t* inManagerData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInManagerData_t* inManagerCSData = (CrFwInManagerData_t*)inManagerData->cmpSpecificData;
	CrFwInstanceId_t id = inManagerData->instanceId;
	CrFwCounterU2_t i, j, freePos, size;

	freePos = inManagerCSData->nextFreePcrlPos;
	size = inManagerPcrlSize[id];

	/* Check if PCRL is already full */
	if (freePos == size) {
		CrFwRepErr(crInManagerPcrlFull, inManagerData->typeId, inManagerData->instanceId);
		return 0;
	}

	/* PCRL is not full --> load inCmp */
	inManagerCSData->pcrl[freePos] = inCmp;
	inManagerCSData->nOfInCmpInPcrl++;
	inManagerCSData->nOfLoadedInCmp++;

	/* Start tracking inCmp */
	CrFwInRegistryStartTracking(inCmp);

	/* Identify next free position in PCRL. This is done by moving backward from the current
	 * free position. We move backward in order to improve the chances of finding a free position
	 * quickly (recall that InManagerExecAction moves forward when executing InReports/InCommands) */
	j = freePos;
	for (i=0; i<(size-1); i++) {
		if (j == 0)
			j = (CrFwCounterU2_t)(size-1);
		else
			j--;
		if (inManagerCSData->pcrl[j] == NULL) {
			inManagerCSData->nextFreePcrlPos = (CrFwCounterU1_t)j;
			return 1; /* a free position has been found */
		}
	}
	inManagerCSData->nextFreePcrlPos = (CrFwCounterU1_t)size;	/* no free position was found */

	return 1;
}

/*-----------------------------------------------------------------------------------------*/
static void InManagerInitAction(FwPrDesc_t initPr) {
	CrFwCounterU1_t i;
	CrFwCmpData_t* inManagerData = (CrFwCmpData_t*)FwPrGetData(initPr);
	CrFwInManagerData_t* inManagerCSData = (CrFwInManagerData_t*)inManagerData->cmpSpecificData;
	CrFwInstanceId_t id = inManagerData->instanceId;
	inManagerCSData->pcrl = malloc(sizeof(FwSmDesc_t)*inManagerPcrlSize[id]);
	for (i=0; i<inManagerPcrlSize[id]; i++)
		inManagerCSData->pcrl[i] = NULL;
	inManagerCSData->nOfInCmpInPcrl = 0;
	inManagerData->outcome = 1;
}

/*-----------------------------------------------------------------------------------------*/
static void InManagerConfigAction(FwPrDesc_t initPr) {
	CrFwCmpData_t* inManagerData = (CrFwCmpData_t*)FwPrGetData(initPr);
	CrFwInManagerData_t* inManagerCSData = (CrFwInManagerData_t*)inManagerData->cmpSpecificData;
	CrFwInstanceId_t id = inManagerData->instanceId;
	CrFwCmpData_t* inCmpData;
	CrFwCounterU1_t i;

	for (i=0; i<inManagerPcrlSize[id]; i++) {
		if (inManagerCSData->pcrl[i] != NULL) {
			inCmpData = (CrFwCmpData_t*)FwSmGetData(inManagerCSData->pcrl[i]);
			if (inCmpData->typeId == CR_FW_INREPORT_TYPE)	/* pending component is an InReport */
				CrFwInFactoryReleaseInRep(inManagerCSData->pcrl[i]);
			else
				CrFwInFactoryReleaseInCmd(inManagerCSData->pcrl[i]);
			inManagerCSData->pcrl[i] = NULL;
		}
	}
	inManagerCSData->nOfInCmpInPcrl = 0;
	inManagerCSData->nOfLoadedInCmp = 0;
	inManagerCSData->nextFreePcrlPos = 0;
	inManagerData->outcome = 1;
}

/*-----------------------------------------------------------------------------------------*/
static void InManagerShutdownAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* inManagerData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInManagerData_t* inManagerCSData = (CrFwInManagerData_t*)inManagerData->cmpSpecificData;
	CrFwInstanceId_t id = inManagerData->instanceId;
	CrFwCmpData_t* inCmpData;
	CrFwCounterU1_t i;

	for (i=0; i<inManagerPcrlSize[id]; i++) {
		if (inManagerCSData->pcrl[i] != NULL) {
			inCmpData = (CrFwCmpData_t*)FwSmGetData(inManagerCSData->pcrl[i]);
			if (inCmpData->typeId == CR_FW_INREPORT_TYPE)	/* pending component is an InReport */
				CrFwInFactoryReleaseInRep(inManagerCSData->pcrl[i]);
			else
				CrFwInFactoryReleaseInCmd(inManagerCSData->pcrl[i]);
			inManagerCSData->pcrl[i] = NULL;
		}
	}
	free(inManagerCSData->pcrl);
	inManagerCSData->nOfInCmpInPcrl = 0;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwInManagerGetNOfPendingInCmp(FwSmDesc_t smDesc) {
	CrFwCmpData_t* inManagerData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInManagerData_t* inManagerCSData = (CrFwInManagerData_t*)inManagerData->cmpSpecificData;
	return inManagerCSData->nOfInCmpInPcrl;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU2_t CrFwInManagerGetNOfLoadedInCmp(FwSmDesc_t smDesc) {
	CrFwCmpData_t* inManagerData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInManagerData_t* inManagerCSData = (CrFwInManagerData_t*)inManagerData->cmpSpecificData;
	return inManagerCSData->nOfLoadedInCmp;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwInManagerGetPCRLSize(FwSmDesc_t smDesc) {
	CrFwCmpData_t* inManagerData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInstanceId_t id = inManagerData->instanceId;
	return (CrFwCounterU1_t)inManagerPcrlSize[id];
}

