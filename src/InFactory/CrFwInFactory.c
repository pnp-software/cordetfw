/**
 * @file
 *
 * Implementation of InFactory component.
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

#include <stdlib.h>
/* Include configuration files */
#include "CrFwInFactoryUserPar.h"
#include "CrFwCmpData.h"
/* Include framework files */
#include "CrFwConstants.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "OutCmp/CrFwOutCmp.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "BaseCmp/CrFwInitProc.h"
#include "BaseCmp/CrFwResetProc.h"
#include "BaseCmp/CrFwDummyExecProc.h"
#include "Pckt/CrFwPckt.h"
#include "InCmd/CrFwInCmd.h"
#include "InRep/CrFwInRep.h"
#include "InRep/CrFwInRepExecProc.h"
#include "InRegistry/CrFwInRegistry.h"
#include "CrFwInFactory.h"
/* Include FW Profile files */
#include "FwPrConfig.h"
#include "FwPrDCreate.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwSmDCreate.h"
#include "FwPrCore.h"

/** Array holding the keys of the InCommand kinds */
static CrFwCmdRepKindKey_t inCmdKindKey[CR_FW_INCMD_NKINDS];

/** Array holding the keys of the InReport kinds */
static CrFwCmdRepKindKey_t inRepKindKey[CR_FW_INREP_NKINDS];

/** Array of InCommand service descriptors (see <code>CrFwServDesc_t</code>). */
static CrFwInCmdKindDesc_t inCmdKindDesc[CR_FW_INCMD_NKINDS] = CR_FW_INCMD_INIT_KIND_DESC;

/** Array of InReport service descriptors (see <code>CrFwServDesc_t</code>). */
static CrFwInRepKindDesc_t inRepKindDesc[CR_FW_INREP_NKINDS] = CR_FW_INREP_INIT_KIND_DESC;

/** The pre-allocated InCommand instances */
static FwSmDesc_t inCmd[CR_FW_INFACTORY_MAX_NOF_INCMD];

/** The pre-allocated InReport instances */
static FwSmDesc_t inRep[CR_FW_INFACTORY_MAX_NOF_INREP];

/** The base data for the pre-allocated InCommand instances */
static CrFwCmpData_t inCmdData[CR_FW_INFACTORY_MAX_NOF_INCMD];

/** The component-specific data for the pre-allocated InCommand instances */
static CrFwInCmdData_t inCmdCmpSpecificData[CR_FW_INFACTORY_MAX_NOF_INCMD];

/** The base data for the pre-allocated InReport instances */
static CrFwCmpData_t inRepData[CR_FW_INFACTORY_MAX_NOF_INREP];

/** The component-specific data for the pre-allocated InReport instances */
static CrFwInRepData_t inRepCmpSpecificData[CR_FW_INFACTORY_MAX_NOF_INREP];

/** The in-use status of each pre-allocated InReport instance */
static CrFwBool_t inRepInUse[CR_FW_INFACTORY_MAX_NOF_INREP];

/** The in-use status of each pre-allocated InCommand instance */
static CrFwBool_t inCmdInUse[CR_FW_INFACTORY_MAX_NOF_INCMD];

/** The number of currently allocated InCommands */
static CrFwInFactoryPoolIndex_t nOfAllocatedInCmd;

/** The number of currently allocated InReports */
static CrFwInFactoryPoolIndex_t nOfAllocatedInRep;

/**
 * The index of the next free position in the pool of pre-allocated InCommands
 * instances (a value of <code>#CR_FW_INFACTORY_MAX_NOF_INCMD</code> indicates that all InCommand
 * instances have been allocated and there are no free positions left) */
static CrFwInFactoryPoolIndex_t nextInCmdFreePos;

/**
 * The index of the next free position in the pool of pre-allocated InReports
 * instances (a value of <code>#CR_FW_INFACTORY_MAX_NOF_INREP</code> indicates that all InReport
 * instances have been allocated and there are no free positions left) */
static CrFwInFactoryPoolIndex_t nextInRepFreePos;

/** The total number of InCommands or InCommand allocated since the InFactory was reset */
static CrFwInstanceId_t nOfAllocatedInCmdSinceReset = 0;

/** The total number of InReports or InCommand allocated since the InFactory was reset */
static CrFwInstanceId_t nOfAllocatedInRepSinceReset = 0;

/** The singleton instance of the InFactory */
static FwSmDesc_t inFactory;

/** The data for the InFactory singleton. */
static CrFwCmpData_t inFactoryData;

/**
 * Initialization action for InFactory.
 * This function: (a) allocates the memory for the InFactory data structures;
 * (b) initializes the arrays of descriptors <code>::inCmdKindDesc</code> and
 * <code>::inRepKindDesc</code>; and (c) initializes the component-specific
 * field of the data structures for InCommands and InReports.
 * The outcome of the initialization action is "success" in all cases except when
 * a memory allocation operation fails.
 * @param initPr the Initialization Procedure of the InFactory
 */
static void InFactoryInitAction(FwPrDesc_t initPr);

/**
 * Configuration action for InFactory.
 * This function releases all the InCommands and InReports which are currently
 * allocated.
 * After this function has been called, any InCommand or InReport which is still in
 * use within the application is no longer valid and should be discarded.
 *
 * This function also resets the counter used to initialize the instance
 * identifiers of the InCommands and InReports created by the InFactory.
 * After reset, the first InCommand or InReport made by the InFactory will have
 * instance identifier set to 1.
 *
 * The outcome of the initialization action is always: "success"
 * @param initPr the Initialization Procedure of the InFactory
 */
static void InFactoryConfigAction(FwPrDesc_t initPr);

/**
 * Shutdown action for InFactory.
 * This function releases the memory which was allocated when the InFactory was
 * initialized and it sets the number of allocated InCommands and InReports to zero.
 * After this function has been called, any InCommand or InReport which is still in
 * use within the application is no longer valid and should be discarded.
 * @param smDesc the InFactory state machine
 */
static void InFactoryShutdownAction(FwSmDesc_t smDesc);

/* ------------------------------------------------------------------------------------ */
FwSmDesc_t CrFwInFactoryMake() {
	FwPrDesc_t resetPr, execPr, initPr;

	if (inFactory != NULL) {
		return inFactory;
	}

	/* Extend the Base Component */
	inFactory = FwSmCreateDer(CrFwBaseCmpMake());

	/* Create the Reset Procedure for the InFactory Component */
	resetPr = FwPrCreateDer(CrFwCmpGetResetProc());
	FwPrOverrideAction(resetPr, &CrFwBaseCmpDefConfigAction, &InFactoryConfigAction);

	/* Create the Initialization Procedure for the InFactory Component */
	initPr = FwPrCreateDer(CrFwCmpGetInitProc());
	FwPrOverrideAction(initPr, &CrFwBaseCmpDefInitAction, &InFactoryInitAction);

	/* Override the Shutdown Action for the InFactory Component */
	FwSmOverrideAction(inFactory, &CrFwBaseCmpDefShutdownAction, &InFactoryShutdownAction);

	/* Get the Dummy Execution Procedure for the InFactory Component */
	execPr = CrFwBaseCmpGetDummyExecProc();

	/* Initialize the data for the requested SM */
	inFactoryData.outcome = 1;
	inFactoryData.initProc = initPr;
	inFactoryData.resetProc = resetPr;
	inFactoryData.execProc = execPr;
	inFactoryData.instanceId = 0;
	inFactoryData.typeId = CR_FW_INFACTORY_TYPE;

	/* Attach the data to the InFactory state machine and to its procedures. */
	FwSmSetData(inFactory, &inFactoryData);
	FwPrSetData(inFactoryData.initProc, &inFactoryData);
	FwPrSetData(inFactoryData.resetProc, &inFactoryData);

	/* Start the InFactory */
	FwSmStart(inFactory);

	return inFactory;
}

/* ------------------------------------------------------------------------------------ */
FwSmDesc_t CrFwInFactoryMakeInCmd(CrFwPckt_t pckt) {
	CrFwInFactoryPoolIndex_t j, k, freePos;
	CrFwCmdRepKindIndex_t kindIndex;
	CrFwCmdRepKindKey_t targetKey;
	CrFwServType_t type;
	CrFwServSubType_t subType;
	CrFwDiscriminant_t discriminant;

	if (nextInCmdFreePos == CR_FW_INFACTORY_MAX_NOF_INCMD) {	/* All positions are occupied */
		CrFwSetAppErrCode(crInCmdAllocationFail);
		return NULL;
	}

	type = CrFwPcktGetServType(pckt);
	subType = CrFwPcktGetServSubType(pckt);
	discriminant = CrFwPcktGetDiscriminant(pckt);
	targetKey = (CrFwCmdRepKindKey_t)(type*CR_FW_MAX_DISCRIMINANT*CR_FW_MAX_SERV_SUBTYPE+subType*CR_FW_MAX_DISCRIMINANT+discriminant);
	kindIndex = CrFwFindCmdRepKindIndex(inCmdKindKey, CR_FW_INCMD_NKINDS, targetKey);
	if (kindIndex == CR_FW_INCMD_NKINDS) {
		CrFwSetAppErrCode(crIllInCmdKind);
		return NULL;
	}
	freePos = nextInCmdFreePos;

	inCmdData[freePos].instanceId = CrFwPcktGetCmdRepId(pckt);

	inCmdCmpSpecificData[freePos].abortAction = inCmdKindDesc[kindIndex].abortAction;
	inCmdCmpSpecificData[freePos].startAction = inCmdKindDesc[kindIndex].startAction;
	inCmdCmpSpecificData[freePos].progressAction = inCmdKindDesc[kindIndex].progressAction;
	inCmdCmpSpecificData[freePos].terminationAction = inCmdKindDesc[kindIndex].terminationAction;
	inCmdCmpSpecificData[freePos].isReady = inCmdKindDesc[kindIndex].isReady;
	inCmdCmpSpecificData[freePos].isValid = inCmdKindDesc[kindIndex].isValid;
	inCmdCmpSpecificData[freePos].factoryPoolIndex = freePos;
	inCmdCmpSpecificData[freePos].progressStepId = 1;
	inCmdCmpSpecificData[freePos].isProgressActionCompleted = 1;
	inCmdCmpSpecificData[freePos].nOfFailedProgressSteps = 0;
	inCmdCmpSpecificData[freePos].pckt = pckt;

	/* Reset the InCommand */
	CrFwCmpReset(inCmd[freePos]);

	nOfAllocatedInCmd++;
	inCmdInUse[freePos] = 1;

	/* Find the next free position in the pool of pre-allocated InCommand instances */
	k = (CrFwInFactoryPoolIndex_t)(freePos + 1);
	for (j=0; j<(CR_FW_INFACTORY_MAX_NOF_INCMD-1); j++) {
		if (k == CR_FW_INFACTORY_MAX_NOF_INCMD)
			k = 0;
		if (inCmdInUse[k] == 0) {
			nextInCmdFreePos = k;
			return (inCmd[freePos]);	/* Next free position has been found */
		}
		k = (CrFwInFactoryPoolIndex_t)(k + 1);
	}

	nextInCmdFreePos = CR_FW_INFACTORY_MAX_NOF_INCMD; /* There are no free positions left */
	return (inCmd[freePos]);
}

/* ------------------------------------------------------------------------------------ */
FwSmDesc_t CrFwInFactoryMakeInRep(CrFwPckt_t pckt) {
	CrFwInFactoryPoolIndex_t j, k, freePos;
	CrFwCmdRepKindIndex_t kindIndex;
	CrFwCmdRepKindKey_t targetKey;
	CrFwServType_t type;
	CrFwServSubType_t subType;
	CrFwDiscriminant_t discriminant;

	if (nextInRepFreePos == CR_FW_INFACTORY_MAX_NOF_INREP) {	/* All positions are occupied */
		CrFwSetAppErrCode(crInRepAllocationFail);
		return NULL;
	}

	type = CrFwPcktGetServType(pckt);
	subType = CrFwPcktGetServSubType(pckt);
	discriminant = CrFwPcktGetDiscriminant(pckt);
	targetKey = (CrFwCmdRepKindKey_t)(type*CR_FW_MAX_DISCRIMINANT*CR_FW_MAX_SERV_SUBTYPE+subType*CR_FW_MAX_DISCRIMINANT+discriminant);
	kindIndex = CrFwFindCmdRepKindIndex(inRepKindKey, CR_FW_INREP_NKINDS, targetKey);
	if (kindIndex == CR_FW_INREP_NKINDS) {
		CrFwSetAppErrCode(crIllInRepKind);
		return NULL;
	}
	freePos = nextInRepFreePos;

	inRepCmpSpecificData[freePos].updateAction = inRepKindDesc[kindIndex].updateAction;
	inRepCmpSpecificData[freePos].isValid = inRepKindDesc[kindIndex].isValid;
	inRepCmpSpecificData[freePos].factoryPoolIndex = freePos;
	inRepCmpSpecificData[freePos].pckt = pckt;
	inRepData[freePos].instanceId = CrFwPcktGetCmdRepId(pckt);

	/* Reset the InReport */
	CrFwCmpReset(inRep[freePos]);

	nOfAllocatedInRep++;
	inRepInUse[freePos] = 1;

	/* Find the next free position in the pool of pre-allocated InReport/InCommand instances */
	k = (CrFwInFactoryPoolIndex_t)(freePos + 1);
	for (j=0; j<(CR_FW_INFACTORY_MAX_NOF_INREP-1); j++) {
		if (k == CR_FW_INFACTORY_MAX_NOF_INREP)
			k = 0;
		if (inRepInUse[k] == 0) {
			nextInRepFreePos = k;
			return (inRep[freePos]);	/* Next free position has been found */
		}
		k = (CrFwInFactoryPoolIndex_t)(k + 1);
	}

	nextInRepFreePos = CR_FW_INFACTORY_MAX_NOF_INREP; /* There are no free positions left */
	return (inRep[freePos]);
}

/* ------------------------------------------------------------------------------------ */
void CrFwInFactoryReleaseInCmd(FwSmDesc_t inCmdInstance) {
	CrFwCmpData_t* inCmdInstanceData = (CrFwCmpData_t*)FwSmGetData(inCmdInstance);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(inCmdInstanceData->cmpSpecificData);
	CrFwInFactoryPoolIndex_t posToBeFreed;

	posToBeFreed = cmpSpecificData->factoryPoolIndex;

	if (inCmdInUse[posToBeFreed] == 1) {
		inCmdInUse[posToBeFreed] = 0;
		nOfAllocatedInCmd--;
		nextInCmdFreePos = posToBeFreed;
		CrFwPcktRelease(inCmdCmpSpecificData[posToBeFreed].pckt);
		inCmdCmpSpecificData[posToBeFreed].pckt = NULL;
		return;
	}
	CrFwSetAppErrCode(crInCmdRelErr);

	return;
}

/* ------------------------------------------------------------------------------------ */
void CrFwInFactoryReleaseInRep(FwSmDesc_t inRepInstance) {
	CrFwCmpData_t* inRepInstanceData = (CrFwCmpData_t*)FwSmGetData(inRepInstance);
	CrFwInRepData_t* cmpSpecificData = (CrFwInRepData_t*)(inRepInstanceData->cmpSpecificData);
	CrFwInFactoryPoolIndex_t posToBeFreed;

	posToBeFreed = cmpSpecificData->factoryPoolIndex;

	if (inRepInUse[posToBeFreed] == 1) {
		inRepInUse[posToBeFreed] = 0;
		nOfAllocatedInRep--;
		nextInRepFreePos = posToBeFreed;
		CrFwPcktRelease(inRepCmpSpecificData[posToBeFreed].pckt);
		inRepCmpSpecificData[posToBeFreed].pckt = NULL;
		return;
	}
	CrFwSetAppErrCode(crInRepRelErr);

	return;
}

/* ------------------------------------------------------------------------------------ */
CrFwInFactoryPoolIndex_t CrFwInFactoryGetNOfAllocatedInCmd() {
	return nOfAllocatedInCmd;
}

/* ------------------------------------------------------------------------------------ */
CrFwInFactoryPoolIndex_t CrFwInFactoryGetMaxNOfInCmd() {
	return CR_FW_INFACTORY_MAX_NOF_INCMD;
}

/* ------------------------------------------------------------------------------------ */
CrFwInFactoryPoolIndex_t CrFwInFactoryGetNOfAllocatedInRep() {
	return nOfAllocatedInRep;
}

/* ------------------------------------------------------------------------------------ */
CrFwInFactoryPoolIndex_t CrFwInFactoryGetMaxNOfInRep() {
	return CR_FW_INFACTORY_MAX_NOF_INREP;
}

/*------------------------------------------------------------------------------------*/
static void InFactoryInitAction(FwPrDesc_t initPr) {
	CrFwCounterU2_t i;
	CrFwCmdRepKindIndex_t j;
	FwPrDesc_t inCmdInitPr, inCmdResetPr, inCmdExecPr;
	FwPrDesc_t inRepInitPr, inRepResetPr, inRepExecPr;
	CRFW_UNUSED(initPr);

	/* Create the pre-allocated InCommands */
	for (i=0; i<CR_FW_INFACTORY_MAX_NOF_INCMD; i++) {
		/* Create the i-th InCommand as an extension of the Base OutComponent */
		inCmd[i] = FwSmCreateDer(CrFwInCmdMakeBase());

		/* Create the Reset Procedure for the InCommand */
		inCmdResetPr = FwPrCreateDer(CrFwCmpGetResetProc());
		FwPrOverrideAction(inCmdResetPr, &CrFwBaseCmpDefConfigCheck, &CrFwInCmdConfigCheck);
		inCmdData[i].resetProc = inCmdResetPr;

		/* Create the Initialization Procedure for the InCommand */
		inCmdInitPr = FwPrCreateDer(CrFwCmpGetInitProc());
		inCmdData[i].initProc = inCmdInitPr;

		/* Get the Execution Procedure for the InCommand */
		inCmdExecPr = CrFwBaseCmpGetDummyExecProc();
		inCmdData[i].execProc = inCmdExecPr;

		/* Set the component type */
		inCmdData[i].typeId = CR_FW_INCOMMAND_TYPE;

		/* Set the pointer to the component-specific data */
		inCmdData[i].cmpSpecificData = &inCmdCmpSpecificData[i];

		/* Attach the data to the InCommand state machine and to its procedures. */
		FwSmSetData(inCmd[i], &inCmdData[i]);
		FwSmSetData(FwSmGetEmbSm(inCmd[i], CR_FW_BASE_STATE_CONFIGURED), &inCmdData[i]);
		FwPrSetData(inCmdData[i].initProc, &inCmdData[i]);
		FwPrSetData(inCmdData[i].resetProc, &inCmdData[i]);

		/* Start and initialize the InCommand */
		FwSmStart(inCmd[i]);
		CrFwCmpInit(inCmd[i]);
	}

	/* Initialize the array holding the keys of the InCommand kinds */
	for (j=0; j<CR_FW_INCMD_NKINDS; j++)
		inCmdKindKey[j] = (CrFwCmdRepKindKey_t)(inCmdKindDesc[j].servType*CR_FW_MAX_DISCRIMINANT*CR_FW_MAX_SERV_SUBTYPE +
		                  inCmdKindDesc[j].servSubType*CR_FW_MAX_DISCRIMINANT+inCmdKindDesc[j].discriminant);

	/* Create the pre-allocated InReports */
	for (i=0; i<CR_FW_INFACTORY_MAX_NOF_INREP; i++) {
		/* Create the i-th InReport as an extension of the Base OutComponent */
		inRep[i] = FwSmCreateDer(CrFwBaseCmpMake());

		/* Create the Reset Procedure for the InReport */
		inRepResetPr = FwPrCreateDer(CrFwCmpGetResetProc());
		FwPrOverrideAction(inRepResetPr, &CrFwBaseCmpDefConfigCheck, &CrFwInRepConfigCheck);
		inRepData[i].resetProc = inRepResetPr;

		/* Create the Initialization Procedure for the InReport */
		inRepInitPr = FwPrCreateDer(CrFwCmpGetInitProc());
		inRepData[i].initProc = inRepInitPr;

		/* Get the Execution Procedure for the InReport */
		inRepExecPr = CrFwInRepExecProcMake();
		inRepData[i].execProc = inRepExecPr;

		/* Set the component type */
		inRepData[i].typeId = CR_FW_INREPORT_TYPE;

		/* Set the pointer to the component-specific data */
		inRepData[i].cmpSpecificData = &inRepCmpSpecificData[i];

		/* Attach the data to the InReport  state machine and to its procedures. */
		FwSmSetData(inRep[i], &inRepData[i]);
		FwPrSetData(inRepData[i].initProc, &inRepData[i]);
		FwPrSetData(inRepData[i].resetProc, &inRepData[i]);
		FwPrSetData(inRepData[i].execProc, &inRepData[i]);

		/* Start and initialize the InReport */
		FwSmStart(inRep[i]);
		CrFwCmpInit(inRep[i]);
	}

	/* Initialize the array holding the keys of the InReport kinds */
	for (j=0; j<CR_FW_INREP_NKINDS; j++)
		inRepKindKey[j] = (CrFwCmdRepKindKey_t)(inRepKindDesc[j].servType*CR_FW_MAX_DISCRIMINANT*CR_FW_MAX_SERV_SUBTYPE +
		                  inRepKindDesc[j].servSubType*CR_FW_MAX_DISCRIMINANT+inRepKindDesc[j].discriminant);

}

/*------------------------------------------------------------------------------------*/
static void InFactoryConfigAction(FwPrDesc_t initPr) {
	CrFwCounterU2_t i;
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwPrGetData(initPr);

	for (i=0; i<CR_FW_INFACTORY_MAX_NOF_INCMD; i++)
		if (inCmdInUse[i] != 0) {
			inCmdInUse[i] = 0;
			CrFwPcktRelease(inCmdCmpSpecificData[i].pckt);
			inCmdCmpSpecificData[i].pckt = NULL;
		}

	for (i=0; i<CR_FW_INFACTORY_MAX_NOF_INREP; i++)
		if (inRepInUse[i] == 1) {
			inRepInUse[i] = 0;
			CrFwPcktRelease(inRepCmpSpecificData[i].pckt);
			inRepCmpSpecificData[i].pckt = NULL;
		}

	nOfAllocatedInRep = 0;
	nOfAllocatedInRepSinceReset = 0;
	nextInRepFreePos = 0;

	nOfAllocatedInCmd = 0;
	nOfAllocatedInCmdSinceReset = 0;
	nextInCmdFreePos = 0;

	cmpData->outcome = 1;
}

/*------------------------------------------------------------------------------------*/
static void InFactoryShutdownAction(FwSmDesc_t smDesc) {
	CrFwCounterU2_t i;
	CRFW_UNUSED(smDesc);

	for (i=0; i<CR_FW_INFACTORY_MAX_NOF_INCMD; i++) {
		/* Release memory allocated to InCommand Initialization Procedure */
		FwPrReleaseDer(inCmdData[i].initProc);
		/* Release memory allocated to InCommand Reset Procedure */
		FwPrReleaseDer(inCmdData[i].resetProc);
		/* Release memory allocated to InCommand */
		FwSmReleaseDer(FwSmGetEmbSm(inCmd[i],CR_FW_BASE_STATE_CONFIGURED));
		FwSmReleaseDer(inCmd[i]);
		if (inCmdInUse[i] == 1) {
			/* Mark all InCommand as not-in-use */
			inCmdInUse[i] = 0;
			/* Release packet associated to InCommand */
			CrFwPcktRelease(inCmdCmpSpecificData[i].pckt);
		}
	}

	for (i=0; i<CR_FW_INFACTORY_MAX_NOF_INREP; i++) {
		/* Release memory allocated to InReport Initialization Procedure */
		FwPrReleaseDer(inRepData[i].initProc);
		/* Release memory allocated to InReport Reset Procedure */
		FwPrReleaseDer(inRepData[i].resetProc);
		/* Release memory allocated to InReport Execution Procedure */
		FwPrRelease(inRepData[i].execProc);
		/* Release memory allocated to InReport */
		FwSmReleaseDer(inRep[i]);
		/* Mark all InReports as not-in-use */
		if (inRepInUse[i] == 1) {
			inRepInUse[i] = 0;
			/* Release packet associated to InRepor */
			CrFwPcktRelease(inRepCmpSpecificData[i].pckt);
		}
	}

	nOfAllocatedInRep = 0;
	nOfAllocatedInCmd = 0;
}











