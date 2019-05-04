/**
 * @file
 *
 * Implementation of OutRegistry component.
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
#include "CrFwOutRegistryUserPar.h"
#include "CrFwCmpData.h"
/* Include framework files */
#include "CrFwConstants.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "OutCmp/CrFwOutCmp.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "BaseCmp/CrFwInitProc.h"
#include "BaseCmp/CrFwResetProc.h"
#include "BaseCmp/CrFwDummyExecProc.h"
#include "CrFwOutRegistry.h"
/* Include FW Profile files */
#include "FwPrConfig.h"
#include "FwPrDCreate.h"
#include "FwSmConfig.h"
#include "FwSmDCreate.h"
#include "FwPrCore.h"

/** Array of service descriptors (see <code>CrFwServDesc_t</code>). */
static CrFwServDesc_t servDesc[CR_FW_OUTREGISTRY_NSERV] = CR_FW_OUTREGISTRY_INIT_SERV_DESC;

/**
 * An instance of this type holds the information about an out-going command or report
 * which is being tracked by the OuRegistry.
 */
typedef struct {
	/** The identifier of the out-going command or report */
	CrFwInstanceId_t instanceId;
	/** The state of the out-going command or report */
	CrFwOutRegistryCmdRepState_t state;
} CrFwTrackedState_t;

/** Array to track the state of out-going commands or reports */
static CrFwTrackedState_t cmdRepState[CR_FW_OUTREGISTRY_N];

/** The index of the most recent entry in <code>cmdRepState</code>. */
static CrFwTrackingIndex_t cmdRepStateIndex = 0;

/** The OutRegistry singleton. */
static FwSmDesc_t outRegistry = NULL;

/** The data for the OutRegistry singleton. */
static CrFwCmpData_t outRegistryData;

/**
 * Initialization action for OutRegistry.
 * This function allocates the memory for the OutRegistry data structures and
 * initializes all data structures which depend on the set of services supported
 * by the application.
 * The outcome of the initialization action is always "success".
 * The situation where the memory allocation for the OutRegistry data structures
 * fails is not handled and will result in undefined behaviour (probably a run-time
 * exception).
 * @param initPr the Initialization Procedure of the OutRegistry
 */
static void OutRegistryInitAction(FwPrDesc_t initPr);

/**
 * Configuration action for OutRegistry.
 * This function sets the enable state of all service types, sub-types and discriminant
 * to "enabled" and resets the queue of tracked commands and reports.
 * The outcome of the configuration action is always: "successful"
 * @param resetPr the Configuration Procedure of the OutRegistry
 */
static void OutRegistryConfigAction(FwPrDesc_t resetPr);

/**
 * Shutdown action for OutRegistry.
 * This function sets the enable state of all service types, sub-types and discriminant
 * to "enabled" and resets the queue of tracked commands and reports.
 * This function also releases the memory allocated when the OutRegistry was initialized.
 * @param smDesc the OutRegistry state machine
 */
static void OutRegistryShutdownAction(FwSmDesc_t smDesc);

/*------------------------------------------------------------------------------------*/
FwSmDesc_t CrFwOutRegistryMake() {
	FwPrDesc_t resetPr, execPr, initPr;

	if (outRegistry != NULL) {
		return outRegistry;
	}

	/* Extend the Base Component */
	outRegistry = FwSmCreateDer(CrFwBaseCmpMake());

	/* Create the Reset Procedure for the OuRegistry Component */
	resetPr = FwPrCreateDer(CrFwCmpGetResetProc());
	FwPrOverrideAction(resetPr, &CrFwBaseCmpDefConfigAction, &OutRegistryConfigAction);

	/* Create the Initialization Procedure for the OuRegistry Component */
	initPr = FwPrCreateDer(CrFwCmpGetInitProc());
	FwPrOverrideAction(initPr, &CrFwBaseCmpDefInitAction, &OutRegistryInitAction);

	/* Override the Shutdown Action for the InStream Component */
	FwSmOverrideAction(outRegistry, &CrFwBaseCmpDefShutdownAction, &OutRegistryShutdownAction);

	/* Get the Dummy Execution Procedure for the OutRegistry Component */
	execPr = CrFwBaseCmpGetDummyExecProc();

	/* Initialize the data for the requested SM */
	outRegistryData.outcome = 1;
	outRegistryData.initProc = initPr;
	outRegistryData.resetProc = resetPr;
	outRegistryData.execProc = execPr;
	outRegistryData.instanceId = 0;
	outRegistryData.typeId = CR_FW_OUTREGISTRY_TYPE;

	/* Attach the data to the OutRegistry state machine and to its procedures. */
	FwSmSetData(outRegistry, &outRegistryData);
	FwPrSetData(outRegistryData.initProc, &outRegistryData);
	FwPrSetData(outRegistryData.resetProc, &outRegistryData);

	/* Start the OutRegistry */
	FwSmStart(outRegistry);

	return outRegistry;
}

/*------------------------------------------------------------------------------------*/
CrFwServType_t CrFwOutRegistryGetServType(CrFwCmdRepIndex_t cmdRepIndex) {
	return servDesc[cmdRepIndex].servType;
}

/*------------------------------------------------------------------------------------*/
CrFwServSubType_t CrFwOutRegistryGetServSubType(CrFwCmdRepIndex_t cmdRepIndex) {
	return servDesc[cmdRepIndex].servSubType;
}

/*------------------------------------------------------------------------------------*/
CrFwDiscriminant_t CrFwOutRegistryGetUpperDiscriminant(CrFwCmdRepIndex_t cmdRepIndex) {
    return servDesc[cmdRepIndex].upperBoundDisc;
}

/*------------------------------------------------------------------------------------*/
CrFwDiscriminant_t CrFwOutRegistryGetLowerDiscriminant(CrFwCmdRepIndex_t cmdRepIndex) {
    return servDesc[cmdRepIndex].lowerBoundDisc;
}

/*------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutRegistryIsDiscriminantEnabled(CrFwCmdRepIndex_t cmdRepIndex, CrFwDiscriminant_t disc) {
    CrFwDiscriminant_t lowerBound = servDesc[cmdRepIndex].lowerBoundDisc;
    return servDesc[cmdRepIndex].isDiscriminantEnabled[disc - lowerBound];
}

/*------------------------------------------------------------------------------------*/
CrFwCmdRepIndex_t CrFwOutRegistryGetCmdRepIndex(CrFwServType_t servType, CrFwServSubType_t servSubType) {
	CrFwCmdRepIndex_t i = 0;

	while (servDesc[i].nextServType != 0)
		if (servDesc[i].servType < servType)
			i = servDesc[i].nextServType;
		else if (servDesc[i].servType > servType)
			return CR_FW_OUTREGISTRY_NSERV;	/* The specified type does not exist */
		else
			break;

	if (servDesc[i].servType != servType)
		return CR_FW_OUTREGISTRY_NSERV;	/* The specified type does not exist */

	while (servDesc[i].servSubType <= servSubType) {
		if (servDesc[i].servSubType == servSubType)
			return i;	/* Cmd-Rep index found! */
		i++;
		if (servDesc[i].servType != servType)
			return CR_FW_OUTREGISTRY_NSERV; /* The specified sub-type does not exist in the specified type */
	}

	return CR_FW_OUTREGISTRY_NSERV; /* The specified sub-type does not exist in the specified type */
}

/*------------------------------------------------------------------------------------*/
void CrFwOutRegistrySetEnable(CrFwServType_t servType, CrFwServSubType_t servSubType,
                              CrFwDiscriminant_t discriminant, CrFwBool_t isEnabled) {
	CrFwCmdRepIndex_t i = 0;
	CrFwDiscriminant_t discOffset;

	while (servDesc[i].nextServType != 0)
		if (servDesc[i].servType < servType)
			i = servDesc[i].nextServType;
		else if (servDesc[i].servType > servType) {
			CrFwSetAppErrCode(crIllServType);
			return;
		} else
			break;

	if (servDesc[i].servType != servType) {
		CrFwSetAppErrCode(crIllServType);
		return;
	}

	if (servSubType == 0) {
		while (servDesc[i].servType == servType) {
			servDesc[i].isServTypeEnabled = isEnabled;
			i++;
			if (i == CR_FW_OUTREGISTRY_NSERV)
				return;
		}
		return;
	}

	while (servDesc[i].servType == servType) {
		if (servDesc[i].servSubType < servSubType)
			i++;
		else if (servDesc[i].servSubType > servSubType) {
			CrFwSetAppErrCode(crIllServSubType);
			return;
		} else
			break;
	}

	if (servDesc[i].servSubType < servSubType) {
		CrFwSetAppErrCode(crIllServSubType);
		return;
	}

	if (discriminant == 0) {
		servDesc[i].isServSubTypeEnabled = isEnabled;
		return;
	}

	if (discriminant > servDesc[i].upperBoundDisc) {
		CrFwSetAppErrCode(crIllDiscriminant);
	    return;
    }

	if (discriminant < servDesc[i].lowerBoundDisc) {
        CrFwSetAppErrCode(crIllDiscriminant);
        return;
    }

	discOffset = discriminant - servDesc[i].lowerBoundDisc;
	servDesc[i].isDiscriminantEnabled[discOffset] = isEnabled;
}

/*------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutRegistryIsEnabled(FwSmDesc_t outCmp) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)cmpData->cmpSpecificData;
	CrFwCmdRepIndex_t cmdRepIndex;
	CrFwDiscriminant_t discriminant, discOffset;

	cmdRepIndex = cmpSpecificData->index;
	if (servDesc[cmdRepIndex].isServTypeEnabled == 0)
		return 0;

	if (servDesc[cmdRepIndex].isServSubTypeEnabled == 0)
		return 0;

	discriminant = CrFwOutCmpGetDiscriminant(outCmp);
	if (discriminant == 0)
		return 1;
	discOffset = (discriminant - servDesc[cmdRepIndex].lowerBoundDisc);
	return servDesc[cmdRepIndex].isDiscriminantEnabled[discOffset];
}

/*------------------------------------------------------------------------------------*/
void CrFwOutRegistryStartTracking(FwSmDesc_t outCmp) {
	CrFwCmpData_t* outCmpData = (CrFwCmpData_t*)FwSmGetData(outCmp);
	CrFwOutCmpData_t* outCmpSpecificData = (CrFwOutCmpData_t*)outCmpData->cmpSpecificData;

	cmdRepState[cmdRepStateIndex].instanceId = outCmpData->instanceId;
	cmdRepState[cmdRepStateIndex].state = crOutRegistryPending;
	outCmpSpecificData->trackingIndex = cmdRepStateIndex;
	/*outCmpData->cmpSpecificData.outCmpData.trackingIndex = cmdRepStateIndex;*/

	if (cmdRepStateIndex == (CR_FW_OUTREGISTRY_N-1))
		cmdRepStateIndex = 0;
	else
		cmdRepStateIndex++;
}

/*------------------------------------------------------------------------------------*/
void CrFwOutRegistryUpdateState(FwSmDesc_t outCmp, CrFwOutRegistryCmdRepState_t newState) {
	CrFwCmpData_t* outCmpData = (CrFwCmpData_t*)FwSmGetData(outCmp);
	CrFwOutCmpData_t* outCmpSpecificData = (CrFwOutCmpData_t*)outCmpData->cmpSpecificData;
	CrFwTrackingIndex_t i;

	i = outCmpSpecificData->trackingIndex;
	/*i = outCmpData->cmpSpecificData.outCmpData.trackingIndex;*/
	if (cmdRepState[i].instanceId == outCmpData->instanceId) {
		cmdRepState[i].state = newState;
	}
}

/*------------------------------------------------------------------------------------*/
CrFwOutRegistryCmdRepState_t CrFwOutRegistryGetState(CrFwInstanceId_t cmdRepId) {
	CrFwTrackingIndex_t i;
	CrFwTrackingIndex_t j;

	if (cmdRepStateIndex > 0)
		i = (CrFwTrackingIndex_t)(cmdRepStateIndex-1);
	else
		i = (CR_FW_OUTREGISTRY_N-1);

	for (j=0; j<CR_FW_OUTREGISTRY_N; j++) {
		if (cmdRepState[i].state == crOutRegistryNoEntry)
			break;
		if (cmdRepState[i].instanceId == cmdRepId) {
			return cmdRepState[i].state;
		} else if (i == 0)
			i = (CR_FW_OUTREGISTRY_N-1);
		else
			i--;
	}

	return crOutRegistryNotTracked;
}

/*------------------------------------------------------------------------------------*/
static void OutRegistryInitAction(FwPrDesc_t initPr) {
    CrFwCmdRepIndex_t i, nextServType;
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwPrGetData(initPr);
    CrFwDiscriminant_t nOfDiscValues;

	for (i=0; i<CR_FW_OUTREGISTRY_NSERV; i++) {
		if (servDesc[i].upperBoundDisc == 0)
		    servDesc[i].isDiscriminantEnabled = malloc(1);  /* To avoid dangling pointers */
		else {
		    nOfDiscValues = servDesc[i].upperBoundDisc - servDesc[i].lowerBoundDisc + 1;
		    servDesc[i].isDiscriminantEnabled = malloc(nOfDiscValues);
		}
	}

	nextServType = 0;
	for (i=CR_FW_OUTREGISTRY_NSERV-1; i>0; i--) {
		servDesc[i].nextServType = nextServType;
		if (servDesc[i-1].servType != servDesc[i].servType)
			nextServType = i;
	}
	servDesc[0].nextServType = nextServType;

	cmpData->outcome = 1;
}

/*------------------------------------------------------------------------------------*/
static void OutRegistryConfigAction(FwPrDesc_t initPr) {
	CrFwCmdRepIndex_t i;
	CrFwDiscriminant_t j;
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwPrGetData(initPr);
	CrFwCounterU2_t k;
	CrFwDiscriminant_t nOfDiscValues;

	for (i=0; i<CR_FW_OUTREGISTRY_NSERV; i++) {
		servDesc[i].isServTypeEnabled = 1;
		servDesc[i].isServSubTypeEnabled = 1;
		nOfDiscValues = servDesc[i].upperBoundDisc - servDesc[i].lowerBoundDisc + 1;
		if (servDesc[i].upperBoundDisc != 0)
			for (j=0; j<nOfDiscValues; j++)
				servDesc[i].isDiscriminantEnabled[j] = 1;
	}

	for (k=0; k<CR_FW_OUTREGISTRY_N; k++)
		cmdRepState[k].state = crOutRegistryNoEntry;

	cmdRepStateIndex = 0;

	cmpData->outcome = 1;
}

/*------------------------------------------------------------------------------------*/
static void OutRegistryShutdownAction(FwSmDesc_t smDesc) {
	CrFwCmdRepIndex_t i;
	CrFwCounterU2_t k;
	CRFW_UNUSED(smDesc);

	for (i=0; i<CR_FW_OUTREGISTRY_NSERV; i++) {
		servDesc[i].isServTypeEnabled = 1;
		servDesc[i].isServSubTypeEnabled = 1;
		free(servDesc[i].isDiscriminantEnabled);
	}

	for (k=0; k<CR_FW_OUTREGISTRY_N; k++)
		cmdRepState[k].state = crOutRegistryNoEntry;

	cmdRepStateIndex = 0;
}

