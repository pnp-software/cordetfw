/**
 * @file
 *
 * Implementation of InStream Stub.
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
#include "CrFwRepErrStub.h"
#include "CrFwInStreamStub.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include configuration files */
#include "CrFwInStreamUserPar.h"
#include "CrFwCmpData.h"
/* Include framework files */
#include "InStream/CrFwInStream.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"

/** Number of packets currently waiting to be collected from the middleware */
static CrFwCounterU1_t pcktCollectCnt = 0;

/** Sequence counter  */
static CrFwSeqCnt_t pcktSeqCnt = 0;

/** Destination */
static CrFwDestSrc_t dest = 0;

/** Destination */
static CrFwCmdRepType_t cmdRepType = crCmdType;

/** Service type */
static CrFwServType_t servType = 0;

/** Service sub-type */
static CrFwServSubType_t servSubType = 0;

/** Discriminant */
static CrFwDiscriminant_t disc = 0;

/** group */
static CrFwGroup_t pcktGroup = 0;

/** Acknowledge level for acceptance */
static CrFwBool_t ackAcc = 0;

/** Acknowledge level for start */
static CrFwBool_t ackStr = 0;

/** Acknowledge level for progress */
static CrFwBool_t ackPrg = 0;

/** Acknowledge level for termination */
static CrFwBool_t ackTrm = 0;

/** Command or Report Identifier */
static CrFwInstanceId_t cmdRepId = 0;

/** Outcome of dummy check */
static CrFwBool_t checkFlag = 1;

/** Outcome of dummy action */
static CrFwBool_t actionFlag = 1;

/** Counter incremented by stub Shutdown Operation */
static CrFwCounterU1_t shutdownCnt = 0;

/* ---------------------------------------------------------------------------------------------*/
CrFwPckt_t CrFwInStreamStubPcktCollect(CrFwDestSrc_t src) {
	CrFwPckt_t pckt;
	(void)(src);

	if (pcktCollectCnt == 0)
		return NULL;

	pcktCollectCnt--;
	pcktSeqCnt++;
	pckt = CrFwPcktMake(CrFwPcktGetMaxLength());
	CrFwPcktSetSeqCnt(pckt, pcktSeqCnt);
	CrFwPcktSetGroup(pckt, pcktGroup);
	CrFwPcktSetDest(pckt, dest);
	CrFwPcktSetCmdRepId(pckt, cmdRepId);
	CrFwPcktSetCmdRepType(pckt, cmdRepType);
	CrFwPcktSetServType(pckt, servType);
	CrFwPcktSetServSubType(pckt, servSubType);
	CrFwPcktSetDiscriminant(pckt, disc);
	CrFwPcktSetAckLevel(pckt, ackAcc, ackStr, ackPrg, ackTrm);

	return pckt;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInStreamStubIsPcktAvail(CrFwDestSrc_t src) {
	(void)(src);
	return (pcktCollectCnt != 0);
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamStubDummyCheck(FwPrDesc_t prDesc) {
	CrFwCmpData_t* inStreamData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	inStreamData->outcome = (CrFwOutcome_t)checkFlag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamStubInitAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* inStreamBaseData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwInStreamData_t* cmpSpecificData = (CrFwInStreamData_t*)inStreamBaseData->cmpSpecificData;
	if (cmpSpecificData->seqCnt == NULL)
		CrFwInStreamDefInitAction(prDesc);
	inStreamBaseData->outcome = (CrFwOutcome_t)actionFlag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamStubConfigAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* inStreamData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwInStreamDefConfigAction(prDesc);
	inStreamData->outcome = (CrFwOutcome_t)actionFlag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamStubShutdown(FwSmDesc_t smDesc) {
	shutdownCnt++;
	CrFwInStreamDefShutdownAction(smDesc);
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamStubSetCheckFlag(CrFwBool_t flag) {
	checkFlag = flag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamStubSetActionFlag(CrFwBool_t flag) {
	actionFlag = flag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamStubSetPcktCollectionCnt(CrFwCounterU1_t cnt) {
	pcktCollectCnt = cnt;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamStubSetPcktSeqCnt(CrFwSeqCnt_t cnt) {
	pcktSeqCnt = cnt;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamStubSetPcktGroup(CrFwGroup_t group) {
	pcktGroup = group;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamStubSetPcktDest(CrFwDestSrc_t d) {
	dest = d;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamStubSetPcktCmdRepId(CrFwInstanceId_t id) {
	cmdRepId = id;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamStubSetPcktCmdRepType(CrFwCmdRepType_t type) {
	cmdRepType = type;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamStubSetPcktAckLevel(CrFwBool_t acc, CrFwBool_t str, CrFwBool_t prg, CrFwBool_t trm) {
	ackAcc = acc;
	ackStr = str;
	ackPrg = prg;
	ackTrm = trm;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamStubSetPcktType(CrFwServType_t sType, CrFwServSubType_t sSubType,
                                 CrFwDiscriminant_t d) {
	servType = sType;
	servSubType = sSubType;
	disc = d;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwInStreamStubGetShutdownCnt() {
	return shutdownCnt;
}
