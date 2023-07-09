/**
 * @file
 *
 * Implementation of OutStream stub.
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
#include <assert.h>
#include "CrFwOutStreamStub.h"
#include "CrFwRepErrStub.h"
/* Include configuration files */
#include "CrFwOutStreamUserPar.h"
#include "CrFwCmpData.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include framework files */
#include "OutStream/CrFwOutStream.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "Pckt/CrFwPckt.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"

/** Counter incremented every time the packet hand-over operation is called */
static CrFwCounterU1_t pcktHandOverCnt = 0;

/** 
 * Counter incremented every time the packet hand-over operation is called 
 * and the packet handover is successful.
*/
static CrFwCounterU1_t pcktHandOverSuccCnt = 0;

/** Return value of the packet hand-over operation */
static CrFwBool_t pcktHandOverFlag = 1;

/** Outcome of dummy check */
static CrFwBool_t checkFlag = 1;

/** Outcome of dummy action */
static CrFwBool_t actionFlag = 1;

/** Counter incremented by stub Shutdown Operation */
static CrFwCounterU1_t shutdownCnt = 0;

/** Number of sequence and type counters kept in memory */
#define CR_FW_OUTSTREAM_STUB_MEM_LEN 100

/** Sequence counters of most recently received packets */
static CrFwSeqCnt_t seqCnt[CR_FW_OUTSTREAM_STUB_MEM_LEN];

/** Type counters of most recently received packets */
static CrFwTypeCnt_t typeCnt[CR_FW_OUTSTREAM_STUB_MEM_LEN];

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutStreamStubPcktHandover(CrFwPckt_t pckt) {
	(void)(pckt);
	if (pcktHandOverFlag == 1) {
		CrFwCounterU1_t pos = pcktHandOverSuccCnt % CR_FW_OUTSTREAM_STUB_MEM_LEN;
		seqCnt[pos] = CrFwPcktGetSeqCnt(pckt);
		typeCnt[pos] = CrFwPcktGetTypeCnt(pckt);
		pcktHandOverSuccCnt++;
	}
	pcktHandOverCnt++;
	return pcktHandOverFlag;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwOutStreamStubGetHandoverCnt() {
	return pcktHandOverCnt;
}

CrFwCounterU1_t CrFwOutStreamStubGetHandoverSuccCnt() {
	return pcktHandOverSuccCnt;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwOutStreamStubGetShutdownCnt() {
	return shutdownCnt;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamStubSetHandoverFlag(CrFwBool_t flag) {
	pcktHandOverFlag = flag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamStubDummyCheck(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	outStreamData->outcome = (CrFwOutcome_t)checkFlag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamStubSetCheckFlag(CrFwBool_t flag) {
	checkFlag = flag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamStubInitAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwOutStreamDefInitAction(prDesc);
	outStreamBaseData->outcome = (CrFwOutcome_t)actionFlag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamStubConfigAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwOutStreamDefConfigAction(prDesc);
	outStreamData->outcome = (CrFwOutcome_t)actionFlag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamStubSetActionFlag(CrFwBool_t flag) {
	actionFlag = flag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamStubShutdown(FwSmDesc_t smDesc) {
	shutdownCnt++;
	CrFwOutStreamDefShutdownAction(smDesc);
}

/* ---------------------------------------------------------------------------------------------*/
CrFwSeqCnt_t CrFwOutStreamStubGetSeqCnt(CrFwCounterU1_t n) {
	assert(n<=CR_FW_OUTSTREAM_STUB_MEM_LEN);
	return seqCnt[n-1];
}

/* ---------------------------------------------------------------------------------------------*/
CrFwSeqCnt_t CrFwOutStreamStubGetTypeCnt(CrFwCounterU1_t n) {
	assert(n<=CR_FW_OUTSTREAM_STUB_MEM_LEN);
	return typeCnt[n-1];
}
