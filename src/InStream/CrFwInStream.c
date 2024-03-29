/**
 * @file
 *
 * Implementation of InStream State Machine.
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
/* Include configuration files */
#include "CrFwInStreamUserPar.h"
#include "CrFwCmpData.h"
/* Include framework files */
#include "CrFwConstants.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "CrFwRepErr.h"
#include "CrFwTime.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "CrFwInStream.h"
#include "BaseCmp/CrFwInitProc.h"
#include "BaseCmp/CrFwResetProc.h"
#include "BaseCmp/CrFwDummyExecProc.h"
#include "Pckt/CrFwPckt.h"
#include "Pckt/CrFwPcktQueue.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmDCreate.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"

/** Base InStream from which all other InStreams are derived. */
static FwSmDesc_t baseInStreamSmDesc = NULL;

/** The sizes of the packet queues in the InStream components. */
static CrFwCounterU1_t inStreamPcktQueueSize[CR_FW_NOF_INSTREAM] = CR_FW_INSTREAM_PQSIZE;

/** The sequence counters managed by the OutStreams. */
static CrFwSeqCnt_t inStreamSeqCounter[CR_FW_INSTREAM_NOF_GROUPS];

/** The functions implementing the packet hand-over operations for the InStream components. */
static CrFwPcktCollect_t inStreamPcktCollect[CR_FW_NOF_INSTREAM] = CR_FW_INSTREAM_PCKTCOLLECT;

/** The functions implementing the packet available check operations for the InStream components. */
static CrFwPcktAvailCheck_t inStreamPcktAvailCheck[CR_FW_NOF_INSTREAM] = CR_FW_INSTREAM_PCKTAVAILCHECK;

/** The functions implementing the initialization checks for the InStream components. */
static FwPrAction_t inStreamInitCheck[CR_FW_NOF_INSTREAM] = CR_FW_INSTREAM_INITCHECK;

/** The functions implementing the initialization actions for the InStream components. */
static FwPrAction_t inStreamInitAction[CR_FW_NOF_INSTREAM] = CR_FW_INSTREAM_INITACTION;

/** The functions implementing the configuration checks for the InStream components. */
static FwPrAction_t inStreamConfigCheck[CR_FW_NOF_INSTREAM] = CR_FW_INSTREAM_CONFIGCHECK;

/** The functions implementing the configuration actions for the InStream components. */
static FwPrAction_t inStreamConfigAction[CR_FW_NOF_INSTREAM] = CR_FW_INSTREAM_CONFIGACTION;

/** The functions implementing the shutdown actions for the InStream components. */
static FwSmAction_t inStreamShutdownAction[CR_FW_NOF_INSTREAM] = CR_FW_INSTREAM_SHUTDOWNACTION;

/** The association between sources and inSreams. */
static CrFwDestSrc_t inStreamSrcPairs[CR_FW_INSTREAM_NOF_SRCS][2] = CR_FW_INSTREAM_SRC_PAIRS;

/** The sources associated to each inStream */
static CrFwDestSrc_t* inStreamSrc[CR_FW_NOF_INSTREAM];

/** The number of sources associated to each inStream */
static CrFwDestSrc_t inStreamNofSrc[CR_FW_NOF_INSTREAM];

/** The descriptors of the InStream State Machines. */
static FwSmDesc_t inStreamDesc[CR_FW_NOF_INSTREAM];

/** The data structures for the InStream State Machines and their Procedures. */
static CrFwCmpData_t inStreamData[CR_FW_NOF_INSTREAM];

/** The component-specific data for the InStream State Machines and their Procedures. */
static CrFwInStreamData_t inStreamCmpSpecificData[CR_FW_NOF_INSTREAM];

/**
 * Function which checks if the packet queue is empty.
 * This function is used as guard for the transition into state WAITING.
 * @param smDesc the state machine descriptor
 * @return 1 if the packet queue is empty; zero otherwise.
 */
static int IsPcktQueueEmpty(FwSmDesc_t smDesc);

/**
 * Function which checks if a packet is available.
 * This function is used as guard for the transition into state PCKT_AVAIL.
 * @param smDesc the state machine descriptor
 * @return 1 if the packet queue is empty; zero otherwise.
 */
static int IsPcktAvail(FwSmDesc_t smDesc);

/**
 * Function which performs Action A in the InStream State Machine.
 * This function is used as a transition action in the InStream State Machine.
 * @param smDesc the state machine descriptor
 * @return 1 if the packet queue is empty; zero otherwise.
 */
static void DoActionA(FwSmDesc_t smDesc);

/**
 * Function which performs Action b in the InStream State Machine.
 * This function is used as a transition action in the InStream State Machine.
 * @param smDesc the state machine descriptor
 * @return 1 if the packet queue is empty; zero otherwise.
 */
static void DoActionB(FwSmDesc_t smDesc);


/*-----------------------------------------------------------------------------------------*/
FwSmDesc_t CrFwInStreamMake(CrFwInstanceId_t i) {
	const FwSmCounterS1_t nOfStates = 2;	/* Number of states */
	const FwSmCounterS1_t nOfChoicePseudoStates = 2;	/* Number of choice pseudo-states */
	const FwSmCounterS1_t nOfTrans = 8;		/* Number of transitions */
	const FwSmCounterS1_t nOfActions = 2;	/* Number of actions */
	const FwSmCounterS1_t nOfGuards = 2;	/* Number of guards */
	const FwSmCounterS1_t CPS_1 = 1;		/* Identifier of first choice pseudo-state */
	const FwSmCounterS1_t CPS_2 = 2;		/* Identifier of second choice pseudo-state */
	FwSmDesc_t esm;
	FwPrDesc_t resetPr, execPr, initPr;

	if (i >= CR_FW_NOF_INSTREAM) {
		CrFwSetAppErrCode(crInStreamIllId);
		return NULL;
	}

	/* If not yet done, create the base InStream SM */
	if (baseInStreamSmDesc == NULL) {
		/* Extend the Base Component */
		baseInStreamSmDesc = FwSmCreateDer(CrFwBaseCmpMake());
		/* Create the InStream SM and then embed it in state CONFIGURED of the Base Component */
		esm = FwSmCreate(nOfStates, nOfChoicePseudoStates, nOfTrans, nOfActions, nOfGuards);
		FwSmAddState(esm, CR_FW_INSTREAM_STATE_WAITING, 1, NULL, NULL, NULL, NULL);
		FwSmAddState(esm, CR_FW_INSTREAM_STATE_PCKT_AVAIL, 2, NULL, NULL, NULL, NULL);
		FwSmAddChoicePseudoState(esm, CPS_1, 2);
		FwSmAddChoicePseudoState(esm, CPS_2, 2);
		FwSmAddTransIpsToCps(esm, CPS_1, NULL);
		FwSmAddTransCpsToSta(esm, CPS_1, CR_FW_INSTREAM_STATE_PCKT_AVAIL, &DoActionB, &IsPcktAvail);
		FwSmAddTransCpsToSta(esm, CPS_1, CR_FW_INSTREAM_STATE_WAITING, NULL, NULL);	/* Else Transition */
		FwSmAddTransStaToSta(esm, CR_FW_INSTREAM_TR_PACKET_AVAILABLE, CR_FW_INSTREAM_STATE_PCKT_AVAIL,
		                     CR_FW_INSTREAM_STATE_PCKT_AVAIL, &DoActionB, NULL);
		FwSmAddTransStaToCps(esm, CR_FW_INSTREAM_TR_PACKET_AVAILABLE, CR_FW_INSTREAM_STATE_WAITING,
							 CPS_2, &DoActionB, NULL);
		FwSmAddTransStaToCps(esm, CR_FW_INSTREAM_TR_GET_PCKT, CR_FW_INSTREAM_STATE_PCKT_AVAIL,
		                     CPS_2, &DoActionA, NULL);
		FwSmAddTransCpsToSta(esm, CPS_2, CR_FW_INSTREAM_STATE_WAITING, NULL, &IsPcktQueueEmpty);
		FwSmAddTransCpsToSta(esm, CPS_2, CR_FW_INSTREAM_STATE_PCKT_AVAIL, NULL, NULL); /* Else Transition */
		FwSmEmbed(baseInStreamSmDesc, CR_FW_BASE_STATE_CONFIGURED, esm);
	}

	if (inStreamDesc[i] != NULL) {
		return inStreamDesc[i];	/* The requested SM has already been created */
	}

	/* Create the requested SM as an extension of the base InStream SM */
	inStreamDesc[i] = FwSmCreateDer(baseInStreamSmDesc);

	/* Create the Reset Procedure for the InStream Component */
	resetPr = FwPrCreateDer(CrFwCmpGetResetProc());
	FwPrOverrideAction(resetPr, &CrFwBaseCmpDefConfigCheck, inStreamConfigCheck[i]);
	FwPrOverrideAction(resetPr, &CrFwBaseCmpDefConfigAction, inStreamConfigAction[i]);

	/* Create the Initialization Procedure for the InStream Component */
	initPr = FwPrCreateDer(CrFwCmpGetInitProc());
	FwPrOverrideAction(initPr, &CrFwBaseCmpDefInitCheck, inStreamInitCheck[i]);
	FwPrOverrideAction(initPr, &CrFwBaseCmpDefInitAction, inStreamInitAction[i]);

	/* Override the Shutdown Action for the InStream Component */
	FwSmOverrideAction(inStreamDesc[i], &CrFwBaseCmpDefShutdownAction, inStreamShutdownAction[i]);

	/* Get the Dummy Execution Procedure for the InStream Component */
	execPr = CrFwBaseCmpGetDummyExecProc();

	/* Initialize the data for the requested InStream Component */
	inStreamData[i].outcome = 1;
	inStreamData[i].initProc = initPr;
	inStreamData[i].resetProc = resetPr;
	inStreamData[i].execProc = execPr;
	inStreamData[i].instanceId = i;
	inStreamData[i].typeId = CR_FW_INSTREAM_TYPE;
	inStreamCmpSpecificData[i].collectPckt = inStreamPcktCollect[i];
	inStreamCmpSpecificData[i].isPcktAvail = inStreamPcktAvailCheck[i];
	inStreamData[i].cmpSpecificData = &inStreamCmpSpecificData[i];

	/* Attach the data to the InStream state machine and to its procedures.
	 * The data is attached to the outer SM and to the SM embedded in state CONFIGURED
	 * and to the Initialization and Reset Procedures. */
	FwSmSetData(inStreamDesc[i], &inStreamData[i]);
	FwSmSetData(FwSmGetEmbSm(inStreamDesc[i], CR_FW_BASE_STATE_CONFIGURED), &inStreamData[i]);
	FwPrSetData(inStreamData[i].initProc, &inStreamData[i]);
	FwPrSetData(inStreamData[i].resetProc, &inStreamData[i]);

	/* Start the InStream */
	FwSmStart(inStreamDesc[i]);

	return inStreamDesc[i];
}

/*-----------------------------------------------------------------------------------------*/
FwSmDesc_t CrFwInStreamGet(CrFwDestSrc_t src) {
	CrFwDestSrc_t i;
	for (i=0; i<CR_FW_INSTREAM_NOF_SRCS; i++)
		if (inStreamSrcPairs[i][0] == src)
			return inStreamDesc[inStreamSrcPairs[i][1]];

	CrFwSetAppErrCode(crInStreamUndefDest);
	return NULL;
}

/*-----------------------------------------------------------------------------------------*/
CrFwDestSrc_t CrFwInStreamGetSrc(FwSmDesc_t smDesc, CrFwCounterU1_t i) {
	CrFwCmpData_t* inStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInstanceId_t inStreamId = inStreamBaseData->instanceId;
	assert(i <= inStreamNofSrc[inStreamId]);
	return inStreamSrc[inStreamId][i-1];
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwInStreamGetNOfSrc(FwSmDesc_t smDesc) {
	CrFwCmpData_t* inStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInstanceId_t inStreamId = inStreamBaseData->instanceId;
	return inStreamNofSrc[inStreamId];
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInStreamIsInWaiting(FwSmDesc_t smDesc) {
	return (FwSmGetCurStateEmb(smDesc) == CR_FW_INSTREAM_STATE_WAITING);
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInStreamIsInPcktAvail(FwSmDesc_t smDesc) {
	return (FwSmGetCurStateEmb(smDesc) == CR_FW_INSTREAM_STATE_PCKT_AVAIL);
}

/*-----------------------------------------------------------------------------------------*/
CrFwPckt_t CrFwInStreamGetPckt(FwSmDesc_t smDesc) {
	CrFwCmpData_t* inStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInStreamData_t* cmpSpecificData = (CrFwInStreamData_t*)inStreamBaseData->cmpSpecificData;
	cmpSpecificData->pckt = NULL;
	FwSmMakeTrans(smDesc, CR_FW_INSTREAM_TR_GET_PCKT);
	return cmpSpecificData->pckt;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInStreamPcktAvail(FwSmDesc_t smDesc) {
	FwSmMakeTrans(smDesc, CR_FW_INSTREAM_TR_PACKET_AVAILABLE);
}

/*-----------------------------------------------------------------------------------------*/
CrFwSeqCnt_t CrFwInStreamGetSeqCnt(CrFwGroup_t group) {
	assert(group < CR_FW_INSTREAM_NOF_GROUPS);
	return inStreamSeqCounter[group];
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInStreamSetSeqCnt(CrFwGroup_t group, CrFwSeqCnt_t seqCnt) {
	assert(group < CR_FW_INSTREAM_NOF_GROUPS);
	inStreamSeqCounter[group] = seqCnt;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwInStreamGetNOfPendingPckts(FwSmDesc_t smDesc) {
	CrFwCmpData_t* inStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInStreamData_t* cmpSpecificData = (CrFwInStreamData_t*)inStreamBaseData->cmpSpecificData;
	return CrFwPcktQueueGetNOfPckts(&(cmpSpecificData->pcktQueue));
}

/*-----------------------------------------------------------------------------------------*/
CrFwGroup_t CrFwInStreamGetNOfGroups() {
	return CR_FW_INSTREAM_NOF_GROUPS;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwInStreamGetPcktQueueSize(FwSmDesc_t smDesc) {
	CrFwCmpData_t* inStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInStreamData_t* cmpSpecificData = (CrFwInStreamData_t*)inStreamBaseData->cmpSpecificData;
	return CrFwPcktQueueGetSize(&(cmpSpecificData->pcktQueue));
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInStreamDefConfigAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* inStreamBaseData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwInStreamData_t* cmpSpecificData = (CrFwInStreamData_t*)inStreamBaseData->cmpSpecificData;
	CrFwGroup_t i;

	CrFwPcktQueueReset(&(cmpSpecificData->pcktQueue));
	cmpSpecificData->pckt = NULL;
	for (i=0; i<CR_FW_INSTREAM_NOF_GROUPS; i++)
		inStreamSeqCounter[i] = 0;
	inStreamData->outcome = 1;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInStreamDefShutdownAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* inStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInStreamData_t* cmpSpecificData = (CrFwInStreamData_t*)inStreamBaseData->cmpSpecificData;
	CrFwInstanceId_t i = inStreamBaseData->instanceId;
	
	free(inStreamSrc[i]);
	inStreamNofSrc[i] = 0;
	inStreamSrc[i] = NULL;
	CrFwPcktQueueShutdown(&(cmpSpecificData->pcktQueue));
	cmpSpecificData->pckt = NULL;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInStreamDefInitAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* inStreamBaseData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwInStreamData_t* cmpSpecificData = (CrFwInStreamData_t*)inStreamBaseData->cmpSpecificData;
	CrFwInstanceId_t inStreamId = inStreamBaseData->instanceId;
	unsigned int i, j;
	
	inStreamNofSrc[inStreamId] = 0;
	for (i=0; i<CR_FW_INSTREAM_NOF_SRCS; i++)
		if (inStreamSrcPairs[i][1] == inStreamId) {
			inStreamNofSrc[inStreamId]++;
		}
	
	assert(inStreamNofSrc[inStreamId] > 0);
	inStreamSrc[inStreamId] = malloc(sizeof(CrFwDestSrc_t) * inStreamNofSrc[inStreamId]);

	j = 0;
	for (i=0; i<CR_FW_INSTREAM_NOF_SRCS; i++)
		if (inStreamSrcPairs[i][1] == inStreamId) {
			inStreamSrc[inStreamId][j] = inStreamSrcPairs[i][0];
			j++;
		}
	assert(j == inStreamNofSrc[inStreamId]);

	CrFwPcktQueueInit(&(cmpSpecificData->pcktQueue), inStreamPcktQueueSize[inStreamId]);
}

/*-----------------------------------------------------------------------------------------*/
static void DoActionA(FwSmDesc_t smDesc) {
	CrFwCmpData_t* inStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInStreamData_t* cmpSpecificData = (CrFwInStreamData_t*)inStreamBaseData->cmpSpecificData;
	cmpSpecificData->pckt = CrFwPcktQueuePop(&(cmpSpecificData->pcktQueue));
}

/*-----------------------------------------------------------------------------------------*/
static void DoActionB(FwSmDesc_t smDesc) {
	CrFwCmpData_t* inStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInstanceId_t inStreamId = inStreamBaseData->instanceId;
	CrFwInStreamData_t* cmpSpecificData = (CrFwInStreamData_t*)inStreamBaseData->cmpSpecificData;
	CrFwPckt_t pckt;
	CrFwSeqCnt_t seqCnt;
	CrFwGroup_t group;
	CrFwDestSrc_t nOfSrcs = inStreamNofSrc[inStreamId];
	CrFwDestSrc_t* srcs = inStreamSrc[inStreamId];

	while (cmpSpecificData->isPcktAvail(nOfSrcs, srcs)) {
		pckt = cmpSpecificData->collectPckt(nOfSrcs, srcs);

		if (CrFwPcktGetDest(pckt) == CR_FW_HOST_APP_ID) {
			seqCnt = CrFwPcktGetSeqCnt(pckt);
			group = CrFwPcktGetGroup(pckt);
			if (group < CR_FW_INSTREAM_NOF_GROUPS) {
				if (inStreamSeqCounter[group] != 0)
					if ((inStreamSeqCounter[group]+1) != seqCnt)
						CrFwRepErrSeqCnt(crInStreamSCErr, inStreamData->typeId, inStreamData->instanceId,
										(inStreamSeqCounter[group]+1), seqCnt, pckt);

				inStreamSeqCounter[group] = seqCnt;
			} else
				CrFwRepErrGroup(crInStreamIllGroup, inStreamBaseData->typeId,
								inStreamBaseData->instanceId, group);
		}
		if (CrFwPcktQueuePush(&(cmpSpecificData->pcktQueue), pckt) == 0) {
			CrFwRepErr(crInStreamPQFull, inStreamData->typeId, inStreamData->instanceId);
			CrFwPcktRelease(pckt);
		}
	}

}

/*-----------------------------------------------------------------------------------------*/
static int IsPcktAvail(FwSmDesc_t smDesc) {
	CrFwCmpData_t* inStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInStreamData_t* cmpSpecificData = (CrFwInStreamData_t*)inStreamBaseData->cmpSpecificData;
	CrFwInstanceId_t inStreamId = inStreamBaseData->instanceId;
	CrFwDestSrc_t nOfSrcs = inStreamNofSrc[inStreamId];
	CrFwDestSrc_t* srcs = inStreamSrc[inStreamId];
	return cmpSpecificData->isPcktAvail(nOfSrcs, srcs);
}

/*-----------------------------------------------------------------------------------------*/
static int IsPcktQueueEmpty(FwSmDesc_t smDesc) {
	CrFwCmpData_t* inStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInStreamData_t* cmpSpecificData = (CrFwInStreamData_t*)inStreamBaseData->cmpSpecificData;
	return CrFwPcktQueueIsEmpty(&(cmpSpecificData->pcktQueue));
}

