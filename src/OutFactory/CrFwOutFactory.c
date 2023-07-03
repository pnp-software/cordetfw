/**
 * @file
 *
 * Implementation of OutFactory component.
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
#include "CrFwOutFactoryUserPar.h"
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
#include "OutRegistry/CrFwOutRegistry.h"
#include "CrFwOutFactory.h"
#include "CrFwTime.h"
/* Include FW Profile files */
#include "FwPrConfig.h"
#include "FwPrDCreate.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwSmDCreate.h"
#include "FwPrCore.h"

/** Array holding the keys of the OutComponents kinds */
static CrFwCmdRepKindKey_t outCmpKindKey[CR_FW_OUTCMP_NKINDS];

/** Array of service descriptors */
static CrFwOutCmpKindDesc_t outCmpKindDesc[CR_FW_OUTCMP_NKINDS] = CR_FW_OUTCMP_INIT_KIND_DESC;

/** The pre-allocated OutComponent instances */
static FwSmDesc_t outCmp[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];

/** The data for the pre-allocated OutComponent instances */
static CrFwCmpData_t outCmpData[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];

/** The component-specific data for the pre-allocated OutReport instances */
static CrFwOutCmpData_t outCmpSpecificData[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];

/** The in-use status of each pre-allocated OutComponent instance */
static CrFwBool_t outCmpInUse[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];

/** The number of currently allocated OutComponents */
static CrFwOutFactoryPoolIndex_t nOfAllocatedOutCmp;

/**
 * The index of the next free position in the pool of pre-allocated OutComponent instances
 * (a value of CR_FW_OUTFACTORY_MAX_NOF_OUTCMP indicates that all OutComponent instances
 * have been allocated and there are no free positions left) */
static CrFwOutFactoryPoolIndex_t nextFreePos;

/** The total number of OutComponents allocated since the OutFactory was reset */
static CrFwInstanceId_t nOfAllocatedOutCmpSinceReset = 0;

/** The singleton instance of the OutFactory */
static FwSmDesc_t outFactory;

/** The data for the OutFactory singleton. */
static CrFwCmpData_t outFactoryData;

/** The part of the command or report identifier which depends on the application identifier */
static CrFwInstanceId_t apidInstanceId = CR_FW_HOST_APP_ID << (sizeof(CrFwInstanceId_t)*8-CR_FW_NBITS_APP_ID);

/** The highest value of cmd/rep identifier (before overflowing into the application identifier bits) */
static CrFwInstanceId_t maxInstanceId = (1 << (sizeof(CrFwInstanceId_t)*8-CR_FW_NBITS_APP_ID));

/**
 * Initialization action for OutFactory.
 * This function allocates the memory for the OutFactory data structures and
 * initializes the array of descriptors <code>::outCmpKindDesc</code>.
 * The outcome of the initialization action is "successful" in all cases except when
 * the memory allocation operation fails.
 * @param initPr the Initialization Procedure of the OutFactory
 */
static void OutFactoryInitAction(FwPrDesc_t initPr);

/**
 * Configuration action for OutFactory.
 * This function releases all the OutComponents which are currently allocated.
 * After this function has been called, any OutComponent which is still in
 * use within the application is no longer valid and should be discarded.
 *
 * This function also resets the counter used to initialize the instance
 * identifier of the OutComponents created by the OutFactory.
 * After reset, the first OutComponent made by the OutFactory will have its
 * instance identifier set to 1.
 *
 * The outcome of the initialization action is always: "successful"
 * @param initPr the Initialization Procedure of the OutFactory
 */
static void OutFactoryConfigAction(FwPrDesc_t initPr);

/**
 * Shutdown action for OutFactory.
 * This function releases the memory which was allocated when the OutFactory was
 * initialized and it sets the number of allocated OutComponents to zero.
 * After this function has been called, any OutComponent which is still in
 * use within the application is no longer valid and should be discarded.
 * @param smDesc the OutFactory state machine
 */
static void OutFactoryShutdownAction(FwSmDesc_t smDesc);

/* ------------------------------------------------------------------------------------ */
FwSmDesc_t CrFwOutFactoryMake() {
	FwPrDesc_t resetPr, execPr, initPr;

	if (outFactory != NULL) {
		return outFactory;
	}

	/* Extend the Base Component */
	outFactory = FwSmCreateDer(CrFwBaseCmpMake());

	/* Create the Reset Procedure for the OutFactory Component */
	resetPr = FwPrCreateDer(CrFwCmpGetResetProc());
	FwPrOverrideAction(resetPr, &CrFwBaseCmpDefConfigAction, &OutFactoryConfigAction);

	/* Create the Initialization Procedure for the OuFactory Component */
	initPr = FwPrCreateDer(CrFwCmpGetInitProc());
	FwPrOverrideAction(initPr, &CrFwBaseCmpDefInitAction, &OutFactoryInitAction);

	/* Override the Shutdown Action for the OuFactory Component */
	FwSmOverrideAction(outFactory, &CrFwBaseCmpDefShutdownAction, &OutFactoryShutdownAction);

	/* Get the Dummy Execution Procedure for the OuFactory Component */
	execPr = CrFwBaseCmpGetDummyExecProc();

	/* Initialize the data for the requested SM */
	outFactoryData.outcome = 1;
	outFactoryData.initProc = initPr;
	outFactoryData.resetProc = resetPr;
	outFactoryData.execProc = execPr;
	outFactoryData.instanceId = 0;
	outFactoryData.typeId = CR_FW_OUTFACTORY_TYPE;

	/* Attach the data to the OutFactory state machine and to its procedures. */
	FwSmSetData(outFactory, &outFactoryData);
	FwPrSetData(outFactoryData.initProc, &outFactoryData);
	FwPrSetData(outFactoryData.resetProc, &outFactoryData);

	/* Start the OuFactory */
	FwSmStart(outFactory);

	return outFactory;
}

/* ------------------------------------------------------------------------------------ */
FwSmDesc_t CrFwOutFactoryMakeOutCmp(CrFwServType_t type, CrFwServSubType_t subType,
                                    CrFwDiscriminant_t discriminant, CrFwPcktLength_t length) {
	CrFwOutFactoryPoolIndex_t j, k, freePos;
	CrFwCmdRepKindIndex_t kindIndex;
	CrFwCmdRepKindKey_t targetKey;
	CrFwPckt_t pckt;
	CrFwPcktLength_t len;

	if (nextFreePos == CR_FW_OUTFACTORY_MAX_NOF_OUTCMP) {	/* All positions are occupied */
		CrFwSetAppErrCode(crOutCmpAllocationFail);
		return NULL;
	}

	targetKey = (CrFwCmdRepKindKey_t)(type*CR_FW_MAX_DISCRIMINANT*CR_FW_MAX_SERV_SUBTYPE+subType*CR_FW_MAX_DISCRIMINANT+discriminant);
	kindIndex = CrFwFindKeyIndex(outCmpKindKey, CR_FW_OUTCMP_NKINDS, targetKey);
	if (kindIndex == CR_FW_OUTCMP_NKINDS) {
		CrFwSetAppErrCode(crIllOutCmpKind);
		return NULL;
	}

	if (length == 0)
	    len = outCmpKindDesc[kindIndex].pcktLength;
	else
	    len = length;

	pckt = CrFwPcktMake(len);	/* The packet length is assumed to be non-negative */
	if (pckt == NULL) {
		CrFwSetAppErrCode(crOutCmpAllocationFail);
		return NULL;
	}

	freePos = nextFreePos;
	outCmpSpecificData[freePos].index = CrFwOutRegistryGetCmdRepIndex(type,subType);
	outCmpSpecificData[freePos].isEnabled = outCmpKindDesc[kindIndex].isEnabled;
	outCmpSpecificData[freePos].isReady = outCmpKindDesc[kindIndex].isReady;
	outCmpSpecificData[freePos].isRepeat = outCmpKindDesc[kindIndex].isRepeat;
	outCmpSpecificData[freePos].serialize = outCmpKindDesc[kindIndex].serialize;
	outCmpSpecificData[freePos].update= outCmpKindDesc[kindIndex].update;
	outCmpSpecificData[freePos].factoryPoolIndex = freePos;

	CrFwPcktSetCmdRepType(pckt,outCmpKindDesc[kindIndex].cmdRepType);
	CrFwPcktSetSrc(pckt,CR_FW_HOST_APP_ID);
	CrFwPcktSetGroup(pckt,0);
	CrFwPcktSetServType(pckt,type);
	CrFwPcktSetServSubType(pckt,subType);
	CrFwPcktSetDiscriminant(pckt,discriminant);
	CrFwPcktSetSeqCnt(pckt,0);

	outCmpSpecificData[freePos].pckt = pckt;

	nOfAllocatedOutCmpSinceReset++;
	if (nOfAllocatedOutCmpSinceReset == maxInstanceId)
		nOfAllocatedOutCmpSinceReset = 0;
	outCmpData[freePos].instanceId = (CrFwInstanceId_t)(apidInstanceId + nOfAllocatedOutCmpSinceReset);

	/* Reset the OutComponent */
	CrFwCmpReset(outCmp[freePos]);

	nOfAllocatedOutCmp++;
	outCmpInUse[freePos] = 1;

	/* Find the next free position in the pool of pre-allocated OutComponent instances */
	k = (CrFwOutFactoryPoolIndex_t)(freePos + 1);
	for (j=0; j<(CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1); j++) {
		if (k == CR_FW_OUTFACTORY_MAX_NOF_OUTCMP)
			k = 0;
		if (outCmpInUse[k] == 0) {
			nextFreePos = k;
			return (outCmp[freePos]);	/* Next free position has been found */
		}
		k = (CrFwOutFactoryPoolIndex_t)(k + 1);
	}

	nextFreePos = CR_FW_OUTFACTORY_MAX_NOF_OUTCMP; /* There are no free positions left */
	return (outCmp[freePos]);
}

/* ------------------------------------------------------------------------------------ */
void CrFwOutFactoryReleaseOutCmp(FwSmDesc_t outCmpInstance) {
	CrFwCmpData_t* outCmpInstanceData = (CrFwCmpData_t*)FwSmGetData(outCmpInstance);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(outCmpInstanceData->cmpSpecificData);
	CrFwOutFactoryPoolIndex_t posToBeFreed;

	posToBeFreed = cmpSpecificData->factoryPoolIndex;
	if (outCmpInUse[posToBeFreed] == 1) {
		outCmpInUse[posToBeFreed] = 0;
		nOfAllocatedOutCmp--;
		nextFreePos = posToBeFreed;
		CrFwPcktRelease(outCmpSpecificData[posToBeFreed].pckt);
		outCmpSpecificData[posToBeFreed].pckt = NULL;
		return;
	}
	CrFwSetAppErrCode(crOutCmpRelErr);

	return;
}

/* ------------------------------------------------------------------------------------ */
CrFwOutFactoryPoolIndex_t CrFwOutFactoryGetNOfAllocatedOutCmp() {
	return nOfAllocatedOutCmp;
}

/* ------------------------------------------------------------------------------------ */
CrFwOutFactoryPoolIndex_t CrFwOutFactoryGetMaxNOfOutCmp() {
	return CR_FW_OUTFACTORY_MAX_NOF_OUTCMP;
}

/* ------------------------------------------------------------------------------------ */
CrFwInstanceId_t CrFwOutFactoryGetNOfInstanceId() {
	return maxInstanceId;
}

/*------------------------------------------------------------------------------------*/
static void OutFactoryInitAction(FwPrDesc_t initPr) {
	CrFwCounterU2_t i;
	CrFwCmdRepKindIndex_t j;
	FwPrDesc_t outCmpInitPr, outCmpResetPr, outCmpExecPr;
	CRFW_UNUSED(initPr);

	/* Create the pre-allocated OutComponents */
	for (i=0; i<CR_FW_OUTFACTORY_MAX_NOF_OUTCMP; i++) {
		/* Create the i-th OutCmp as an extension of the Base OutComponent */
		outCmp[i] = FwSmCreateDer(CrFwOutCmpMakeBase());

		/* Create the Reset Procedure for the OutComponent */
		outCmpResetPr = FwPrCreateDer(CrFwCmpGetResetProc());
		outCmpData[i].resetProc = outCmpResetPr;

		/* Create the Initialization Procedure for the OutComponent */
		outCmpInitPr = FwPrCreateDer(CrFwCmpGetInitProc());
		outCmpData[i].initProc = outCmpInitPr;

		/* Get the Dummy Execution Procedure for the OutComponent */
		outCmpExecPr = CrFwBaseCmpGetDummyExecProc();
		outCmpData[i].execProc = outCmpExecPr;

		/* Set the OutComponent type */
		outCmpData[i].typeId = CR_FW_OUTCMP_TYPE;

		/* Set the pointer to the component-specific data */
		outCmpData[i].cmpSpecificData = &outCmpSpecificData[i];

		/* Attach the data to the OutComponent state machine and to its procedures. */
		FwSmSetData(outCmp[i], &outCmpData[i]);
		FwSmSetData(FwSmGetEmbSm(outCmp[i], CR_FW_BASE_STATE_CONFIGURED), &outCmpData[i]);
		FwPrSetData(outCmpData[i].initProc, &outCmpData[i]);
		FwPrSetData(outCmpData[i].resetProc, &outCmpData[i]);

		/* Start and initialize the OutComponent */
		FwSmStart(outCmp[i]);
		CrFwCmpInit(outCmp[i]);
	}

	/* Initialize the array holding the keys of the OutCommand kinds */
	for (j=0; j<CR_FW_OUTCMP_NKINDS; j++)
		outCmpKindKey[j] = (CrFwCmdRepKindKey_t)(outCmpKindDesc[j].servType*CR_FW_MAX_DISCRIMINANT*CR_FW_MAX_SERV_SUBTYPE +
		                   outCmpKindDesc[j].servSubType*CR_FW_MAX_DISCRIMINANT+outCmpKindDesc[j].discriminant);
}

/*------------------------------------------------------------------------------------*/
static void OutFactoryConfigAction(FwPrDesc_t initPr) {
	CrFwCounterU2_t i;
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwPrGetData(initPr);

	for (i=0; i<CR_FW_OUTFACTORY_MAX_NOF_OUTCMP; i++)
		if (outCmpInUse[i] != 0) {
			outCmpInUse[i] = 0;
			CrFwPcktRelease(outCmpSpecificData[i].pckt);
			outCmpSpecificData[i].pckt = NULL;
		}


	nOfAllocatedOutCmp = 0;
	nOfAllocatedOutCmpSinceReset = 0;
	nextFreePos = 0;

	cmpData->outcome = 1;
}

/*------------------------------------------------------------------------------------*/
static void OutFactoryShutdownAction(FwSmDesc_t smDesc) {
	CrFwCounterU2_t i;
	CRFW_UNUSED(smDesc);

	for (i=0; i<CR_FW_OUTFACTORY_MAX_NOF_OUTCMP; i++) {
		/* Release memory allocated to OutComponent Initialization Procedure */
		FwPrReleaseDer(outCmpData[i].initProc);
		/* Release memory allocated to OutComponent Reset Procedure */
		FwPrReleaseDer(outCmpData[i].resetProc);
		/* Release memory allocated to OutComponent */
		FwSmReleaseDer(FwSmGetEmbSm(outCmp[i],CR_FW_BASE_STATE_CONFIGURED));
		FwSmReleaseDer(outCmp[i]);
		/* Mark all OutComponents as not-in-use */
		outCmpInUse[i] = 0;
		/* Release packet associated to OutComponent */
		if (outCmpSpecificData[i].pckt != NULL)
			CrFwPcktRelease(outCmpSpecificData[i].pckt);
	}

	nOfAllocatedOutCmp = 0;
}

