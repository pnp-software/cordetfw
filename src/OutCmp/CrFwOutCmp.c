/**
 * @file
 *
 * Implementation of OutComponent component.
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
#include "CrFwCmpData.h"
/* Include framework files */
#include "CrFwConstants.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "OutStream/CrFwOutStream.h"
#include "OutCmp/CrFwOutCmp.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "BaseCmp/CrFwInitProc.h"
#include "BaseCmp/CrFwResetProc.h"
#include "BaseCmp/CrFwDummyExecProc.h"
#include "OutFactory/CrFwOutFactory.h"
#include "Pckt/CrFwPckt.h"
#include "CrFwTime.h"
/* Include FW Profile files */
#include "FwPrConfig.h"
#include "FwPrDCreate.h"
#include "FwSmConfig.h"
#include "FwSmDCreate.h"
#include "FwPrCore.h"

/** Base OutComponent from which all other OutComponents are derived. */
static FwSmDesc_t baseOutCmpSmDesc = NULL;

/**
 * Transition action on the transition out of the LOADED state.
 * This transition action executes the enable check and then
 * sets the outcome as follows:
 * - if the enable check returns "not enabled", the outcome is set to 0
 * - if the enable check returns "enabled" the outcome is set to 1
 * .
 * The setting of the <code>isRepeat</code> flag is not done in this function.
 * This flag will only be evaluated after the Repeat Check is performed and
 * there is therefore no need to set it here.
 * @param smDesc the descriptor of the OutComponent state machine
 */
void LoadedToCpsTransAction(FwSmDesc_t smDesc);

/**
 * Do action of the PENDING state (including behaviour of Send Packet Procedure).
 * The outcome of the Repeat Check and of the Enable Check are stored in the outcome
 * field of the component data as follows:
 * - If the Enable Check reports 'Not Enabled', the outcome is set to zero
 * - If the Enable Check reports 'Enabled' and the Repeat Check reports 'No Repeat',
 *   the outcome is set to 2
 * - In all other cases, the outcome is set to 1.
 * .
 * In order to understand why the logic in this function is equivalent to that of the
 * specification, consider the outcome of executing and terminating the OutComponent
 * for all possible values of the Ready Check, Repeat Check, Enable Check and validity
 * statuses of the OutComponent's destination:
 * - isReady==true, isRepeat==true, isEnabled==true, dest. is valid --> PENDING, outcome=1
 * - isReady=='any', isRepeat=='any', isEnabled==false, dest. is 'any' --> ABORTED, outcome=0
 * - isReady==true, isRepeat==false, isEnabled==true, dest. is valid --> TERMINATED, outcome=2
 * - isReady==true, isRepeat=='any', isEnabled==true, dest. is false --> TERMINATED, outcome=2
 * - isReady==false, isRepeat=='any', isEnabled==true, dest. is 'any' --> PENDING, outcome=1
 * .
 * @image html SendPacket.png
 * @param smDesc the descriptor of the OutComponent state machine
 */
void PendingDoAction(FwSmDesc_t smDesc);

/**
 * Entry action of the SENDING state (including behaviour of Send Packet Procedure).
 * The outcome of the Repeat Check is stored in the outcome field of the component
 * data (a value of '1' corresponds to: 'Repeat' and a value of '2' corresponds to:
 * 'No Repeat').
 *
 * In order to understand why the logic in this function is equivalent to that of the
 * specification, consider the outcome of executing and terminating the OutComponent
 * for all possible for all possible values of the Ready Check, Repeat Check, and
 * validity statuses of the OutComponent's destination (recall that isRepeat and
 * isEnabled are guaranteed to be true at entry):
 * - isReady==true, isRepeat==true, dest. is valid --> PENDING, outcome=1
 * - isReady==true, isRepeat==false, dest. is valid --> TERMINATED, outcome=2
 * - isReady==false, isRepeat=='any', dest. is 'any' --> PENDING, outcome=1
 * - isReady==true, isRepeat=='any', dest. is not valid --> TERMINATED, outcome=2
 * .
 * @image html SendPacket.png
 * @param smDesc the descriptor of the OutComponent state machine
 */
void PendingEntryAction(FwSmDesc_t smDesc);

/* --------------------------------------------------------------------------------- */
FwSmDesc_t CrFwOutCmpMakeBase() {
	FwSmCounterS1_t nOfStates = 4;		/* Number of states */
	FwSmCounterS1_t nOfChoicePseudoStates = 1;	/* Number of choice pseudo-states */
	FwSmCounterS1_t nOfTrans = 6;		/* Number of transitions */
	FwSmCounterS1_t nOfActions = 3;		/* Number of actions */
	FwSmCounterS1_t nOfGuards = 3;		/* Number of guards */
	FwSmCounterS1_t CPS_1 = 1;			/* Identifier of first choice pseudo-state */
	FwSmDesc_t esm;

	if (baseOutCmpSmDesc != NULL)
		return baseOutCmpSmDesc;

	/* Create and configure the base OutComponent */

	/* Extend the Base Component */
	baseOutCmpSmDesc = FwSmCreateDer(CrFwBaseCmpMake());
	/* Create the OutComponent SM and then embed it in state CONFIGURED of the Base Component */
	esm = FwSmCreate(nOfStates, nOfChoicePseudoStates, nOfTrans, nOfActions, nOfGuards);
	FwSmAddState(esm, CR_FW_OUTCMP_STATE_LOADED, 1, NULL, NULL, NULL, NULL);
	FwSmAddState(esm, CR_FW_OUTCMP_STATE_ABORTED, 0, NULL, NULL, NULL, NULL);
	FwSmAddState(esm, CR_FW_OUTCMP_STATE_PENDING, 2, &PendingEntryAction, NULL, &PendingDoAction, NULL);
	FwSmAddState(esm, CR_FW_OUTCMP_STATE_TERMINATED, 0, NULL, NULL, NULL, NULL);
	FwSmAddChoicePseudoState(esm, CPS_1, 2);
	FwSmAddTransIpsToSta(esm, CR_FW_OUTCMP_STATE_LOADED, NULL);
	FwSmAddTransStaToCps(esm, FW_TR_EXECUTE, CR_FW_OUTCMP_STATE_LOADED, CPS_1,
	                     &LoadedToCpsTransAction, NULL);
	FwSmAddTransCpsToSta(esm, CPS_1, CR_FW_OUTCMP_STATE_ABORTED, NULL, &CrFwIsSmOutcomeZero);
	FwSmAddTransCpsToSta(esm, CPS_1, CR_FW_OUTCMP_STATE_PENDING, NULL, &CrFwIsSmOutcomeOne);
	FwSmAddTransStaToSta(esm, CR_FW_OUTCMP_TR_TERMINATE, CR_FW_OUTCMP_STATE_PENDING,
	                     CR_FW_OUTCMP_STATE_TERMINATED, NULL, &CrFwIsSmOutcomeTwo);
	FwSmAddTransStaToSta(esm, CR_FW_OUTCMP_TR_TERMINATE, CR_FW_OUTCMP_STATE_PENDING,
	                     CR_FW_OUTCMP_STATE_ABORTED, NULL, &CrFwIsSmOutcomeZero);
	FwSmEmbed(baseOutCmpSmDesc, CR_FW_BASE_STATE_CONFIGURED, esm);

	return baseOutCmpSmDesc;
}

/* --------------------------------------------------------------------------------- */
void CrFwOutCmpTerminate(FwSmDesc_t smDesc) {
	FwSmMakeTrans(smDesc, CR_FW_OUTCMP_TR_TERMINATE);
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwOutCmpIsInLoaded(FwSmDesc_t smDesc) {
	return (FwSmGetCurStateEmb(smDesc) == CR_FW_OUTCMP_STATE_LOADED);
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwOutCmpIsInAborted(FwSmDesc_t smDesc) {
	return (FwSmGetCurStateEmb(smDesc) == CR_FW_OUTCMP_STATE_ABORTED);
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwOutCmpIsInPending(FwSmDesc_t smDesc) {
	return (FwSmGetCurStateEmb(smDesc) == CR_FW_OUTCMP_STATE_PENDING);
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwOutCmpIsInTerminated(FwSmDesc_t smDesc) {
	return (FwSmGetCurStateEmb(smDesc) == CR_FW_OUTCMP_STATE_TERMINATED);
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwOutCmpDefEnableCheck(FwSmDesc_t smDesc) {
	return CrFwOutRegistryIsEnabled(smDesc);
}

/* --------------------------------------------------------------------------------- */
void CrFwOutCmpDefSerialize(FwSmDesc_t smDesc) {
	CrFwPckt_t pckt;
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

	pckt = cmpSpecificData->pckt;
	CrFwPcktSetCmdRepId(pckt,cmpData->instanceId);

	return;
}

/* --------------------------------------------------------------------------------- */
CrFwDestSrc_t CrFwOutCmpGetDest(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetDest(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
void CrFwOutCmpSetDest(FwSmDesc_t smDesc, CrFwDestSrc_t dest) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	CrFwPcktSetDest(cmpSpecificData->pckt, dest);
	return;
}

/* --------------------------------------------------------------------------------- */
CrFwGroup_t CrFwOutCmpGetGroup(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetGroup(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
void CrFwOutCmpSetGroup(FwSmDesc_t smDesc, CrFwGroup_t group) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	CrFwPcktSetGroup(cmpSpecificData->pckt, group);
	return;
}

/* --------------------------------------------------------------------------------- */
CrFwTimeStamp_t CrFwOutCmpGetTimeStamp(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetTimeStamp(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
void CrFwOutCmpSetTimeStamp(FwSmDesc_t smDesc, CrFwTimeStamp_t timeStamp) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	CrFwPcktSetTimeStamp(cmpSpecificData->pckt, timeStamp);
	return;
}

/* --------------------------------------------------------------------------------- */
CrFwServType_t CrFwOutCmpGetServType(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetServType(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwDestSrc_t CrFwOutCmpGetSrc(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetSrc(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwServType_t CrFwOutCmpGetServSubType(FwSmDesc_t smDesc)  {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetServSubType(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwDiscriminant_t CrFwOutCmpGetDiscriminant(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetDiscriminant(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
void CrFwOutCmpSetDiscriminant(FwSmDesc_t smDesc, CrFwDiscriminant_t discriminant) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	CrFwPcktSetDiscriminant(cmpSpecificData->pckt, discriminant);
}

/* --------------------------------------------------------------------------------- */
void CrFwOutCmpSetAckLevel(FwSmDesc_t smDesc, CrFwBool_t accept, CrFwBool_t start,
                           CrFwBool_t progress, CrFwBool_t term) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	CrFwPcktSetAckLevel(cmpSpecificData->pckt,accept,start,progress,term);
	return;
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwOutCmpIsAcceptAck(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktIsAcceptAck(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwOutCmpIsStartAck(FwSmDesc_t smDesc)  {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktIsStartAck(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwOutCmpIsProgressAck(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktIsProgressAck(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwOutCmpIsTermAck(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktIsTermAck(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
void LoadedToCpsTransAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	cmpData->outcome = (CrFwOutcome_t)cmpSpecificData->isEnabled(smDesc);
	return;
}

/* --------------------------------------------------------------------------------- */
void PendingEntryAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	CrFwBool_t isReady;
	CrFwBool_t isRepeat;
	CrFwDestSrc_t dest;
	FwSmDesc_t outStream;

	isReady = cmpSpecificData->isReady(smDesc);
	if (isReady) {
		cmpSpecificData->update(smDesc);
		dest = CrFwPcktGetDest(cmpSpecificData->pckt);
		outStream = CrFwOutStreamGet(dest);
		if (outStream == NULL) {
			CrFwRepErrDestSrc(crOutCmpSendPcktInvDest, cmpData->typeId, cmpData->instanceId, dest);
			isRepeat = 0;
		} else {
			CrFwOutCmpSetTimeStamp(smDesc,CrFwGetCurrentTimeStamp());
			cmpSpecificData->serialize(smDesc);
			CrFwOutStreamSend(outStream, cmpSpecificData->pckt);
			isRepeat = cmpSpecificData->isRepeat(smDesc);
		}
		if (isRepeat == 1)
			cmpData->outcome = 1;
		else
			cmpData->outcome = 2;
	}
}

/* --------------------------------------------------------------------------------- */
void PendingDoAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	CrFwDestSrc_t dest;
	FwSmDesc_t outStream;
	CrFwBool_t isReady;
	CrFwBool_t isRepeat;
	CrFwBool_t isEnabled;

	isReady = cmpSpecificData->isReady(smDesc);
	isEnabled = cmpSpecificData->isEnabled(smDesc);

	if (isReady == 1)
		if (isEnabled ==1) {
			cmpSpecificData->update(smDesc);
			dest = CrFwPcktGetDest(cmpSpecificData->pckt);
			outStream = CrFwOutStreamGet(dest);
			if (outStream == NULL) {
				CrFwRepErrDestSrc(crOutCmpSendPcktInvDest, cmpData->typeId, cmpData->instanceId, dest);
				isRepeat = 0;
			} else {
				CrFwOutCmpSetTimeStamp(smDesc,CrFwGetCurrentTimeStamp());
				cmpSpecificData->serialize(smDesc);
				CrFwOutStreamSend(outStream, cmpSpecificData->pckt);
				isRepeat = cmpSpecificData->isRepeat(smDesc);
			}
			if (isRepeat == 0) {
				cmpData->outcome = 2;
				return;
			}
		}

	if (isEnabled == 0) {
		cmpData->outcome = 0;
		return;
	}

	cmpData->outcome = 1;
}

/* --------------------------------------------------------------------------------- */
CrFwPckt_t CrFwOutCmpGetParStart(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetParStart(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwPcktLength_t CrFwOutCmpGetParLength(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetParLength(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwPcktLength_t CrFwOutCmpGetLength(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetLength(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwPckt_t CrFwOutCmpGetPckt(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
	return cmpSpecificData->pckt;
}
