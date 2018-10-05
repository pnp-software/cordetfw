/**
 * @file
 * @ingroup crTestSuiteGroup
 * Implementation of the Sample 1 InCommand.
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
#include "InCmd/CrFwInCmd.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "BaseCmp/CrFwInitProc.h"
#include "BaseCmp/CrFwResetProc.h"
#include "BaseCmp/CrFwDummyExecProc.h"
#include "OutFactory/CrFwOutFactory.h"
#include "Pckt/CrFwPckt.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include FW Profile files */
#include "FwPrConfig.h"
#include "FwPrDCreate.h"
#include "FwSmConfig.h"
#include "FwSmDCreate.h"
#include "FwPrCore.h"

/** The Validity Flag. */
static CrFwBool_t validityFlag;

/** The InCommand type as computed in the Validity Check */
static CrFwServType_t servType = 0;

/** The Ready Flag. */
static CrFwBool_t readyFlag;

/** The Start Action Outcome. */
static CrFwOutcome_t startOutcome;

/** The Progress Action Outcome. */
static CrFwOutcome_t progressOutcome;

/** The Progress Action Completion Outcome. */
static CrFwOutcome_t progressCompletionOutcome;

/** The Progress Step Flag. */
static CrFwBool_t progressStepFlag ;

/** The Abort Action Outcome. */
static CrFwOutcome_t abortOutcome = 0;

/** The Termination Action Outcome. */
static CrFwOutcome_t terminationOutcome;

/** The Start Action Counter. */
static CrFwCounterU1_t startCounter = 0;

/** The Progress Action Counter. */
static CrFwCounterU1_t progressCounter = 0;

/** The Termination Action Counter. */
static CrFwCounterU1_t terminationCounter = 0;

/** The abort Action Counter. */
static CrFwCounterU1_t abortCounter = 0;

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInCmdSample1ValidityCheck(FwPrDesc_t prDesc) {
	CrFwPckt_t pckt;
	pckt = CrFwInCmdGetPcktFromPrDesc(prDesc);
	servType = CrFwPcktGetServType(pckt);
	return validityFlag;
}

/*-----------------------------------------------------------------------------------------*/
CrFwServType_t CrFwInCmdSample1GetType() {
    return servType;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1SetProgressStepFlag(CrFwBool_t flag) {
    progressStepFlag = flag;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1SetValidityFlag(CrFwBool_t flag) {
	validityFlag = flag;
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInCmdSample1ReadyCheck(FwSmDesc_t smDesc) {
	(void)(smDesc);
	return readyFlag;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1SetReadyFlag(CrFwBool_t flag) {
	readyFlag = flag;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1StartAction(FwSmDesc_t smDesc) {
	CrFwSetSmOutcome(smDesc, startOutcome);
	startCounter++;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1SetStartActionOutcome(CrFwOutcome_t outcome) {
	startOutcome = outcome;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwInCmdSample1GetStartActionCounter() {
	return startCounter;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1ProgressAction(FwSmDesc_t smDesc) {
    CrFwProgressStepId_t progressStepId;
	CrFwSetSmOutcome(smDesc, progressOutcome);
	progressStepId = CrFwInCmdGetProgressStepId(smDesc);
	if (progressStepFlag)
	    CrFwInCmdSetProgressStepId(smDesc,progressStepId+1);

	progressCounter++;
	CrFwInCmdSetProgressActionCompleted(smDesc, progressCompletionOutcome);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1SetProgressActionOutcome(CrFwOutcome_t outcome) {
	progressOutcome = outcome;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1SetProgressActionCompletionOutcome(CrFwOutcome_t outcome) {
    progressCompletionOutcome = outcome;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwInCmdSample1GetProgressActionCounter() {
	return progressCounter;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1AbortAction(FwSmDesc_t smDesc) {
	CrFwSetSmOutcome(smDesc, abortOutcome);
	abortCounter++;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1SetAbortActionOutcome(CrFwOutcome_t outcome) {
	abortOutcome = outcome;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwInCmdSample1GetAbortActionCounter() {
	return abortCounter;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1TerminationAction(FwSmDesc_t smDesc) {
	CrFwSetSmOutcome(smDesc, terminationOutcome);
	terminationCounter++;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1SetTerminationActionOutcome(CrFwOutcome_t outcome) {
	terminationOutcome = outcome;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwInCmdSample1GetTerminationActionCounter() {
	return terminationCounter;

}

