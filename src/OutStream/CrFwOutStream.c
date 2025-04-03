/**
 * @file
 *
 * Implementation of OutStream State Machine.
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
#include<string.h>
/* Include configuration files */
#include "CrFwOutStreamUserPar.h"
#include "CrFwOutFactoryUserPar.h"
#include "CrFwCmpData.h"
/* Include framework files */
#include "CrFwConstants.h"
#include "CrFwRepErr.h"
#include "CrFwTime.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "CrFwOutStream.h"
#include "BaseCmp/CrFwInitProc.h"
#include "BaseCmp/CrFwResetProc.h"
#include "BaseCmp/CrFwDummyExecProc.h"
#include "Pckt/CrFwPckt.h"
#include "Pckt/CrFwPcktQueue.h"
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

#include <assert.h>

/** Base OutStream from which all other OutStreams are derived. */
static FwSmDesc_t baseOutStreamSmDesc = NULL;

/** The sizes of the packet queues in the OutStream components. */
static CrFwCounterU1_t outStreamPcktQueueSize[CR_FW_NOF_OUTSTREAM] = CR_FW_OUTSTREAM_PQSIZE;

/** The (destination, outStream) pairs */
static CrFwDestSrc_t outStreamDestPairs[CR_FW_OUTSTREAM_NOF_DEST][2] = CR_FW_OUTSTREAM_DEST_PAIRS;

/** The destinations associated to each outStream */
static CrFwDestSrc_t* outStreamDest[CR_FW_NOF_OUTSTREAM];

/** The number of destinations associated to each outStream */
static CrFwDestSrc_t outStreamNofDest[CR_FW_NOF_OUTSTREAM];

/** The sequence counters managed by the OutStreams. */
static CrFwSeqCnt_t outStreamSeqCounter[CR_FW_OUTSTREAM_NOF_GROUPS];

/** The number of type counters maintained by the OutStreams. */
static CrFwCounterU2_t outStreamNofTypeCounter = 0;

/** 
 * The type counters managed by the OutStreams. 
 * This array has (<code>::outStreamNofTypeCounter</code>+1) entries.
 * The first <code>::outStreamNofTypeCounter</code> entries are the 
 * type counters. 
 * The last entry is always equal to zero.
 */
static CrFwTypeCnt_t* outStreamTypeCounter = NULL;

/**
 * Array of destination-type keys.
 * A destination-type key is an unsigned integer obtained as the product of: 
 * 		t*s_max*d_max + s*d_max + d, 
 * where d, t, and s are a destination identifier, a service type identifier and 
 * a service sub-type identifier for which a type counter is maintained by the 
 * OutStreams and d_max and s_max are the maximum value of d and s (as given
 * by constants <code>#CR_FW_MAX_DEST</code> and <code>#CR_FW_MAX_SERV_SUBTYPE</code>).
 * 
 * The entries in this array are populated by function 
 * <code>#CR_FW_OUTSTREAM_SET_DTS</code>. 
 * They hold all the destination-type triplets for which a type counter is maintained.
 * The entries in the array are arranged in increasing order so that the arrays can be 
 * searched through utility function <code>::CrFwFindKeyIndex</code>.
 * The size of this array should be equal to the value of #outStreamNofTypeCounter.
*/
static CrFwDestTypeKey_t* outStreamDestTypeKey = NULL;

/** The function implementing the Set DTS Operation */
static CrFwSetDst_t outStreamSetDts = CR_FW_OUTSTREAM_SET_DTS;

/** The functions implementing the packet hand-over operations for the OutStream components */
static CrFwPcktHandover_t outStreamHandoverPckt[CR_FW_NOF_OUTSTREAM] = CR_FW_OUTSTREAM_PCKTHANDOVER;

/** The functions implementing the initialization checks for the InStream components. */
static FwPrAction_t outStreamInitCheck[CR_FW_NOF_OUTSTREAM] = CR_FW_OUTSTREAM_INITCHECK;

/** The functions implementing the initialization actions for the InStream components. */
static FwPrAction_t outStreamInitAction[CR_FW_NOF_OUTSTREAM] = CR_FW_OUTSTREAM_INITACTION;

/** The functions implementing the configuration checks for the InStream components. */
static FwPrAction_t outStreamConfigCheck[CR_FW_NOF_OUTSTREAM] = CR_FW_OUTSTREAM_CONFIGCHECK;

/** The functions implementing the configuration actions for the InStream components. */
static FwPrAction_t outStreamConfigAction[CR_FW_NOF_OUTSTREAM] = CR_FW_OUTSTREAM_CONFIGACTION;

/** The functions implementing the shutdown actions for the InStream components. */
static FwSmAction_t outStreamShutdownAction[CR_FW_NOF_OUTSTREAM] = CR_FW_OUTSTREAM_SHUTDOWNACTION;

/** The descriptors of the OutStream State Machines. */
static FwSmDesc_t outStreamDesc[CR_FW_NOF_OUTSTREAM];

/** The base data structures for the OutStream State Machines and their Procedures. */
static CrFwCmpData_t outStreamData[CR_FW_NOF_OUTSTREAM];

/** The component-specific data for the OutStream State Machines and their Procedures. */
static CrFwOutStreamData_t outStreamCmpSpecificData[CR_FW_NOF_OUTSTREAM];

/**
 * Function which enqueues a packet on the packet queue.
 * The packet to be enqueued is taken from the data associated to OutStream State
 * Machine.
 * This function is used as the transition action for the self-transition on the
 * BUFFERING state and as a transition action on the transition out of the
 * READY state.
 * If the packet cannot be enqueued because the packet queue is full, an error
 * is generated and the packet is released.
 * @param smDesc the state machine descriptor
 */
static void EnqueuePckt(FwSmDesc_t smDesc);

/**
 * Function which flushes the packet queue.
 * This function is used as the transition action on the transition out of state
 * BUFFERING.
 * @param smDesc the state machine descriptor
 */
static void FlushPcktQueue(FwSmDesc_t smDesc);

/**
 * Function which resets to 1 all sequence and type counters of the OutStreams.
 * This function is used as transition action on the transition out of the initial
 * state of an OutStream state machine.
 * Note that this means that, if an application has more than one OutStream, this 
 * action will be called multiple times during the application's initialization. 
 * @param smDesc the state machine descriptor
 */
static void ResetSeqAndTypeCounters(FwSmDesc_t smDesc);

/**
 * Function which first attempts to hand over a packet to the middleware and,
 * if this fails, it pushes it on the packet queue.
 * This function is used as the transition action out of state READY.
 * @param smDesc the state machine descriptor
 */
static void SendOrEnqueue(FwSmDesc_t smDesc);

/**
 * Function which checks if the packet queue is empty.
 * This function is used as guard for the transition into state READY.
 * @param smDesc the state machine descriptor
 * @return 1 if the packet queue is empty; zero otherwise.
 */
static int IsPacketQueueEmpty(FwSmDesc_t smDesc);

/**
 * Compute the destination-type key of the argument packet and returns
 * its position (starting from zero) in the array of destination-type keys
 * <code>::outStreamDestTypeKey</code>.
 * If the destination-type key of the argument packet is not in 
 * the array <code>::outStreamDestTypeKey</code>, then the length of the
 * of the array is returned.
 * Packets whose destination-type key is not in array 
 * <code>::outStreamDestTypeKey</code> are those for which
 * the type counter does not need to be maintained and can be set to zero.
 * 
 * @param pckt the packet whose destination-type key is computed
 * @return the position of the packet's destination-type key in array
 * <code>::outStreamDestTypeKey</code> or the array's length if the packet's
 * destination-type key is not found 
 */
static CrFwTypeCnt_t GetDestTypeKeyPos(CrFwPckt_t pckt);

/*-----------------------------------------------------------------------------------------*/
FwSmDesc_t CrFwOutStreamMake(CrFwInstanceId_t i) {
	const FwSmCounterS1_t nOfStates = 2;	/* Number of states */
	const FwSmCounterS1_t nOfChoicePseudoStates = 1;	/* Number of choice pseudo-states */
	const FwSmCounterS1_t nOfTrans = 6;		/* Number of transitions */
	const FwSmCounterS1_t nOfActions = 4;	/* Number of actions */
	const FwSmCounterS1_t nOfGuards = 1;	/* Number of guards */
	const FwSmCounterS1_t CPS_1 = 1;		/* Identifier of first choice pseudo-state */
	FwSmDesc_t esm;
	FwPrDesc_t resetPr, execPr, initPr;

	if (i >= CR_FW_NOF_OUTSTREAM) {
		CrFwSetAppErrCode(crOutStreamIllId);
		return NULL;
	}

	/* If not yet done, create the DTS_SET and allocate type counter array */
	if (outStreamNofTypeCounter == 0) {
		outStreamSetDts(&outStreamNofTypeCounter, &outStreamDestTypeKey);
		outStreamTypeCounter = malloc(sizeof(CrFwTypeCnt_t) * (outStreamNofTypeCounter + 1));
	}
	
	/* If not yet done, create the base OutStream SM */
	if (baseOutStreamSmDesc == NULL) {
		/* Extend the Base Component */
		baseOutStreamSmDesc = FwSmCreateDer(CrFwBaseCmpMake());
		/* Create the OutStream SM and then embed it in state CONFIGURED of the Base Component */
		esm = FwSmCreate(nOfStates, nOfChoicePseudoStates, nOfTrans, nOfActions, nOfGuards);
		FwSmAddState(esm, CR_FW_OUTSTREAM_STATE_READY, 1, NULL, NULL, NULL, NULL);
		FwSmAddState(esm, CR_FW_OUTSTREAM_STATE_BUFFERING, 2, NULL, NULL, NULL, NULL);
		FwSmAddChoicePseudoState(esm, CPS_1, 2);
		FwSmAddTransIpsToSta(esm, CR_FW_OUTSTREAM_STATE_READY, &ResetSeqAndTypeCounters);
		FwSmAddTransStaToCps(esm, CR_FW_OUTSTREAM_TR_SEND, CR_FW_OUTSTREAM_STATE_READY, CPS_1,
		                     &SendOrEnqueue, NULL);
		FwSmAddTransCpsToSta(esm, CPS_1, CR_FW_OUTSTREAM_STATE_READY, NULL, &IsPacketQueueEmpty);
		FwSmAddTransCpsToSta(esm, CPS_1, CR_FW_OUTSTREAM_STATE_BUFFERING, NULL, NULL);	/* Else Transition */
		FwSmAddTransStaToCps(esm, CR_FW_OUTSTREAM_TR_CONNECTION_AVAILABLE, CR_FW_OUTSTREAM_STATE_BUFFERING,
		                     CPS_1, &FlushPcktQueue, NULL);
		FwSmAddTransStaToSta(esm, CR_FW_OUTSTREAM_TR_SEND, CR_FW_OUTSTREAM_STATE_BUFFERING,
		                     CR_FW_OUTSTREAM_STATE_BUFFERING, &EnqueuePckt, NULL);
		FwSmEmbed(baseOutStreamSmDesc, CR_FW_BASE_STATE_CONFIGURED, esm);
	}

	if (outStreamDesc[i] != NULL) {
		return outStreamDesc[i];	/* The requested SM has already been created */
	}

	/* Create the requested SM as an extension of the base OutStream SM */
	outStreamDesc[i] = FwSmCreateDer(baseOutStreamSmDesc);

	/* Create the Reset Procedure for the OutStream Component */
	resetPr = FwPrCreateDer(CrFwCmpGetResetProc());
	FwPrOverrideAction(resetPr, &CrFwBaseCmpDefConfigCheck, outStreamConfigCheck[i]);
	FwPrOverrideAction(resetPr, &CrFwBaseCmpDefConfigAction, outStreamConfigAction[i]);

	/* Create the Initialization Procedure for the OutStream Component */
	initPr = FwPrCreateDer(CrFwCmpGetInitProc());
	FwPrOverrideAction(initPr, &CrFwBaseCmpDefInitCheck, outStreamInitCheck[i]);
	FwPrOverrideAction(initPr, &CrFwBaseCmpDefInitAction, outStreamInitAction[i]);

	/* Override the Shutdown Action for the OutStream Component */
	FwSmOverrideAction(outStreamDesc[i], &CrFwBaseCmpDefShutdownAction, outStreamShutdownAction[i]);

	/* Get the Dummy Execution Procedure for the OutStream Component */
	execPr = CrFwBaseCmpGetDummyExecProc();

	/* Initialize the data for the requested SM */
	outStreamData[i].outcome = 1;
	outStreamData[i].initProc = initPr;
	outStreamData[i].resetProc = resetPr;
	outStreamData[i].execProc = execPr;
	outStreamData[i].instanceId = i;
	outStreamData[i].typeId = CR_FW_OUTSTREAM_TYPE;
	outStreamCmpSpecificData[i].handoverPckt = outStreamHandoverPckt[i];
	outStreamData[i].cmpSpecificData = &outStreamCmpSpecificData[i];

	/* Attach the data to the OutStream state machine and to its procedures.
	 * The data is attached to the outer SM and to the SM embedded in state CONFIGURED
	 * and to the Initialization and Reset Procedures. */
	FwSmSetData(outStreamDesc[i], &outStreamData[i]);
	FwSmSetData(FwSmGetEmbSm(outStreamDesc[i], CR_FW_BASE_STATE_CONFIGURED), &outStreamData[i]);
	FwPrSetData(outStreamData[i].initProc, &outStreamData[i]);
	FwPrSetData(outStreamData[i].resetProc, &outStreamData[i]);

	/* Start the OutStream */
	FwSmStart(outStreamDesc[i]);

	return outStreamDesc[i];
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutStreamIsInReady(FwSmDesc_t smDesc) {
	return (FwSmGetCurStateEmb(smDesc) == CR_FW_OUTSTREAM_STATE_READY);
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutStreamIsInBuffering(FwSmDesc_t smDesc) {
	return (FwSmGetCurStateEmb(smDesc) == CR_FW_OUTSTREAM_STATE_BUFFERING);
}

/*-----------------------------------------------------------------------------------------*/
FwSmDesc_t CrFwOutStreamGet(CrFwDestSrc_t dest) {
	unsigned int i;
	for (i=0; i<CR_FW_OUTSTREAM_NOF_DEST; i++)
		if (outStreamDestPairs[i][0] == dest) {
			assert(outStreamDestPairs[i][1] < CR_FW_NOF_OUTSTREAM);
			return outStreamDesc[outStreamDestPairs[i][1]];
		}

	CrFwSetAppErrCode(crOutStreamUndefDest);
	return NULL;
}

/*-----------------------------------------------------------------------------------------*/
CrFwDestSrc_t CrFwOutStreamGetDest(FwSmDesc_t outStream, CrFwCounterU1_t i) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(outStream);
	CrFwInstanceId_t outStreamId = outStreamBaseData->instanceId;
	assert(i <= outStreamNofDest[outStreamId]);
	return outStreamDest[outStreamId][i-1];
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwOutStreamGetNOfDest(FwSmDesc_t outStream) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(outStream);
	CrFwInstanceId_t outStreamId = outStreamBaseData->instanceId;
	return outStreamNofDest[outStreamId];
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU3_t CrFwOutStreamGetNOfHandedOverBytes(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	return cmpSpecificData->nOfHandedOverBytes;
}

CrFwCounterU3_t CrFwOutStreamGetNOfHandedOverPckts(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	return cmpSpecificData->nOfHandedOverPckts;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwOutStreamSend(FwSmDesc_t smDesc, CrFwPckt_t pckt) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	cmpSpecificData->pckt = pckt;
	FwSmMakeTrans(smDesc, CR_FW_OUTSTREAM_TR_SEND);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwOutStreamConnectionAvail(FwSmDesc_t smDesc) {
	FwSmMakeTrans(smDesc, CR_FW_OUTSTREAM_TR_CONNECTION_AVAILABLE);
}

/*-----------------------------------------------------------------------------------------*/
CrFwSeqCnt_t CrFwOutStreamGetSeqCnt(CrFwGroup_t group) {
	return outStreamSeqCounter[group];
}

/*-----------------------------------------------------------------------------------------*/
void CrFwOutStreamSetSeqCnt(CrFwGroup_t group, CrFwSeqCnt_t seqCnt) {
	outStreamSeqCounter[group] = seqCnt;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwOutStreamGetNOfPendingPckts(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	return CrFwPcktQueueGetNOfPckts(&(cmpSpecificData->pcktQueue));
}

/*-----------------------------------------------------------------------------------------*/
CrFwGroup_t CrFwOutStreamGetNOfGroups() {
	return CR_FW_OUTSTREAM_NOF_GROUPS;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwOutStreamGetPcktQueueSize(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	return CrFwPcktQueueGetSize(&(cmpSpecificData->pcktQueue));
}

/*-----------------------------------------------------------------------------------------*/
void CrFwOutStreamDefConfigAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;

	CrFwPcktQueueReset(&(cmpSpecificData->pcktQueue));
	cmpSpecificData->nOfHandedOverBytes = 0;
	cmpSpecificData->nOfHandedOverPckts = 0;
	cmpSpecificData->handoverPckt = outStreamHandoverPckt[outStreamBaseData->instanceId];
	outStreamBaseData->outcome = 1;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwOutStreamDefShutdownAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInstanceId_t outStreamId = outStreamBaseData->instanceId;
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	free(outStreamDest[outStreamId]);
	outStreamDest[outStreamId] = NULL;
	outStreamNofDest[outStreamId] = 0;
	cmpSpecificData->nOfHandedOverBytes = 0;
	cmpSpecificData->nOfHandedOverPckts = 0;
	CrFwPcktQueueShutdown(&(cmpSpecificData->pcktQueue));
}

/*-----------------------------------------------------------------------------------------*/
void CrFwOutStreamDefInitAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwInstanceId_t outStreamId = outStreamBaseData->instanceId;
	unsigned int i, j;

	if (outStreamNofDest[outStreamId] != 0) {
		outStreamBaseData->outcome = 1;
		return;
	}

	outStreamNofDest[outStreamId] = 0;
	for (i=0; i<CR_FW_OUTSTREAM_NOF_DEST; i++)
		if (outStreamDestPairs[i][1] == outStreamId) {
			outStreamNofDest[outStreamId]++;
		}
	
	assert(outStreamNofDest[outStreamId] > 0);
	outStreamDest[outStreamId] = malloc(sizeof(CrFwDestSrc_t) * outStreamNofDest[outStreamId]);

	j = 0;
	for (i=0; i<CR_FW_OUTSTREAM_NOF_DEST; i++)
		if (outStreamDestPairs[i][1] == outStreamId) {
			outStreamDest[outStreamId][j] = outStreamDestPairs[i][0];
			j++;
		}
	assert(j == outStreamNofDest[outStreamId]);

	CrFwPcktQueueInit(&(outStreamCmpSpecificData[outStreamId].pcktQueue),outStreamPcktQueueSize[outStreamId]);
	outStreamBaseData->outcome = 1;
}

/*-----------------------------------------------------------------------------------------*/
static void EnqueuePckt(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	CrFwPckt_t pckt = cmpSpecificData->pckt;
	CrFwPckt_t pcktCopy;
	CrFwPcktQueue_t pcktQueue = &(cmpSpecificData->pcktQueue);
	CrFwPcktLength_t len = CrFwPcktGetLength(pckt);

	pcktCopy = CrFwPcktMake(CrFwPcktGetLength(pckt));
	if (pcktCopy == NULL) {
		CrFwRepErr(crOutStreamNoMorePckt, outStreamBaseData->typeId, outStreamBaseData->instanceId);
		return;
	}
	memcpy(pcktCopy,pckt,len);
	if (!CrFwPcktQueuePush(pcktQueue, pcktCopy)) {
		CrFwRepErr(crOutStreamPQFull, outStreamBaseData->typeId, outStreamBaseData->instanceId);
		CrFwPcktRelease(pcktCopy);
	}

	return;
}

/*-----------------------------------------------------------------------------------------*/
static void FlushPcktQueue(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	CrFwPckt_t oldestPckt;
	CrFwPcktLength_t oldestPcktLen;
	CrFwPcktQueue_t pcktQueue = &(cmpSpecificData->pcktQueue);
	CrFwGroup_t oldestPcktGroup = 0;
	CrFwTypeCnt_t typeCnt;
	CrFwCounterU2_t destTypeKeyPos;
	CrFwCrc_t crc;

	while (CrFwPcktQueueIsEmpty(pcktQueue)==0) {
		oldestPckt = CrFwPcktQueueGetOldest(pcktQueue);
		oldestPcktLen = CrFwPcktGetLength(oldestPckt);
		if (CrFwPcktGetSrc(oldestPckt) == CR_FW_HOST_APP_ID) { /* pckt originates from host application */
			oldestPcktGroup = CrFwPcktGetGroup(oldestPckt);
			if (oldestPcktGroup < CR_FW_OUTSTREAM_NOF_GROUPS) {
				CrFwPcktSetSeqCnt(oldestPckt, outStreamSeqCounter[oldestPcktGroup]);
			} else {	/* pckt belongs to a non-existent group */
				CrFwRepErrGroup(crOutStreamIllGroup, outStreamBaseData->typeId,
				                outStreamBaseData->instanceId, oldestPcktGroup);
				CrFwPcktSetSeqCnt(oldestPckt, 0);
			}

			/* If pckt has no type counter, destTypeKeyPos will be equal to outStreamNofTypeCounter 
			   and its type counter will be set to the last element of array outStreamTypeCounter,
			   which is always equal to zero */
			destTypeKeyPos = GetDestTypeKeyPos(oldestPckt);
			assert(destTypeKeyPos <= outStreamNofTypeCounter);
			typeCnt = outStreamTypeCounter[destTypeKeyPos];
			CrFwPcktSetTypeCnt(oldestPckt, typeCnt);

			crc = CrFwPcktComputeCrc(oldestPckt);
			CrFwPcktSetCrc(oldestPckt, crc);
		}
		if (cmpSpecificData->handoverPckt(oldestPckt) != 1)
			return;
		if (CrFwPcktGetSrc(oldestPckt) == CR_FW_HOST_APP_ID) {
			if (oldestPcktGroup < CR_FW_OUTSTREAM_NOF_GROUPS)
				outStreamSeqCounter[oldestPcktGroup]++;
			if (destTypeKeyPos < outStreamNofTypeCounter)
				outStreamTypeCounter[destTypeKeyPos]++;
		}
		cmpSpecificData->nOfHandedOverPckts++;
		cmpSpecificData->nOfHandedOverBytes += oldestPcktLen;
		CrFwPcktQueuePop(pcktQueue);	/* remove packet from PQ */
		CrFwPcktRelease(oldestPckt);
	}
	return;
}

/*-----------------------------------------------------------------------------------------*/
static void ResetSeqAndTypeCounters(FwSmDesc_t smDesc) {
	CrFwGroup_t i;
	CrFwTypeCnt_t j;
	(void)smDesc;
	for (i=0; i<CR_FW_OUTSTREAM_NOF_GROUPS; i++)
		outStreamSeqCounter[i] = 1;

	assert(outStreamNofTypeCounter>0);
	for (j=0; j<outStreamNofTypeCounter; j++)
		outStreamTypeCounter[j] = 1;
	outStreamTypeCounter[outStreamNofTypeCounter] = 0;
}

/*-----------------------------------------------------------------------------------------*/
static void SendOrEnqueue(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	CrFwPckt_t pckt = cmpSpecificData->pckt;
	CrFwPcktLength_t pcktLen = CrFwPcktGetLength(pckt);
	CrFwPckt_t pcktCopy;
	CrFwPcktLength_t len;
	CrFwDestSrc_t pcktSrc;
	CrFwPcktQueue_t pcktQueue;
	CrFwGroup_t pcktGroup;
	CrFwTypeCnt_t typeCnt;
	CrFwCounterU2_t destTypeKeyPos;
	CrFwCrc_t crc;

	pcktSrc = CrFwPcktGetSrc(pckt);
	if (pcktSrc == CR_FW_HOST_APP_ID) { /* pckt originates from host application */
		pcktGroup = CrFwPcktGetGroup(pckt);
		if (pcktGroup < CR_FW_OUTSTREAM_NOF_GROUPS) {
			CrFwPcktSetSeqCnt(pckt, outStreamSeqCounter[pcktGroup]);
		} else {	/* pckt belongs to a non-existent group */
			CrFwRepErrGroup(crOutStreamIllGroup, outStreamBaseData->typeId,
			                outStreamBaseData->instanceId, pcktGroup);
			CrFwPcktSetSeqCnt(pckt, 0);
		}

		/* If pckt has no type counter, destTypeKeyPos will be equal to outStreamNofTypeCounter 
		   and its type counter will be set to the last element of array outStreamTypeCounter,
		   which is always equal to zero */
		destTypeKeyPos = GetDestTypeKeyPos(pckt);
		assert(destTypeKeyPos <= outStreamNofTypeCounter);
		typeCnt = outStreamTypeCounter[destTypeKeyPos];
		CrFwPcktSetTypeCnt(pckt, typeCnt);

    	crc = CrFwPcktComputeCrc(pckt);
        CrFwPcktSetCrc(pckt, crc);
	}
	if (cmpSpecificData->handoverPckt(pckt) != 1) {
		pcktQueue = &(cmpSpecificData->pcktQueue);
		len = CrFwPcktGetLength(pckt);
		pcktCopy = CrFwPcktMake(len);	/* Will eventually be released by FlushPcktQueue */
		if (pcktCopy == NULL) {
			CrFwRepErr(crOutStreamNoMorePckt, outStreamBaseData->typeId, outStreamBaseData->instanceId);
			return;
		}
		memcpy(pcktCopy,pckt,len);
		CrFwPcktQueuePush(pcktQueue,pcktCopy);	/* Enqueue packet, queue is empty at entry in READY */
	} else {
		cmpSpecificData->nOfHandedOverPckts++;
		cmpSpecificData->nOfHandedOverBytes += pcktLen;
		if (pcktSrc == CR_FW_HOST_APP_ID) {
			if (pcktGroup < CR_FW_OUTSTREAM_NOF_GROUPS)
				outStreamSeqCounter[pcktGroup]++;
			if (destTypeKeyPos < outStreamNofTypeCounter)
				outStreamTypeCounter[destTypeKeyPos]++;
		}
	}
}

/*-----------------------------------------------------------------------------------------*/
static CrFwTypeCnt_t GetDestTypeKeyPos(CrFwPckt_t pckt) {
	CrFwDestTypeKey_t key;
	CrFwDestSrc_t dest;
	CrFwServType_t type;
	CrFwServSubType_t subType;

	dest = CrFwPcktGetDest(pckt);
	type = CrFwPcktGetServType(pckt);
	subType = CrFwPcktGetServSubType(pckt);
	key = type * CR_FW_MAX_SERV_SUBTYPE * CR_FW_MAX_DEST + subType * CR_FW_MAX_DEST + dest;
	
	return CrFwFindKeyIndex(outStreamDestTypeKey, outStreamNofTypeCounter, key);
}

/*-----------------------------------------------------------------------------------------*/
static int IsPacketQueueEmpty(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	return CrFwPcktQueueIsEmpty(&(cmpSpecificData->pcktQueue));
}

/*-----------------------------------------------------------------------------------------*/
void CrFwOutStreamDefSetDTS(CrFwCounterU2_t* pNofTypeCounter, 
							CrFwDestTypeKey_t** pDestTypeKey) {
	CrFwOutCmpKindDesc_t outCmpKindDesc[CR_FW_OUTCMP_NKINDS] = CR_FW_OUTCMP_INIT_KIND_DESC;
	CrFwDestSrc_t dest = 1;
	CrFwServType_t prevServType = 0;
	CrFwServType_t servType;
	CrFwServSubType_t prevServSubType = 0;
	CrFwServSubType_t servSubType;
	unsigned int i, j;

	for (i=0; i<CR_FW_OUTCMP_NKINDS; i++) {
		servType = outCmpKindDesc[i].servType;
		servSubType = outCmpKindDesc[i].servSubType;
		if ((servType != prevServType) || (servSubType != prevServSubType))
			(*pNofTypeCounter)++;
		prevServType = servType;
		prevServSubType = servSubType;
	}

	(*pDestTypeKey) = malloc(sizeof(CrFwTypeCnt_t) * (*pNofTypeCounter));

	j = 0;
	for (i=0; i<CR_FW_OUTCMP_NKINDS; i++) {
		servType = outCmpKindDesc[i].servType;
		servSubType = outCmpKindDesc[i].servSubType;
		if ((servType != prevServType) || (servSubType != prevServSubType)) {
			assert(j<(*pNofTypeCounter));
			(*pDestTypeKey)[j] = servType * CR_FW_MAX_SERV_SUBTYPE * CR_FW_MAX_DEST + \
							     servSubType * CR_FW_MAX_DEST + dest;
			j = j + 1;
		}
		prevServType = servType;
		prevServSubType = servSubType;
	}

	return;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU2_t CrFwOutStreamGetNOfTypeCounters() {
	return outStreamNofTypeCounter;
}

/*-----------------------------------------------------------------------------------------*/
CrFwTypeCnt_t CrFwOutStreamGetTypeCounter(CrFwDestSrc_t dest, 
                                          CrFwServType_t servType,
                                          CrFwServSubType_t servSubType) {
	CrFwDestTypeKey_t key;
	CrFwCounterU2_t pos;
	key = servType*CR_FW_MAX_SERV_SUBTYPE*CR_FW_MAX_DEST + servSubType*CR_FW_MAX_DEST + dest;
	pos = CrFwFindKeyIndex(outStreamDestTypeKey, outStreamNofTypeCounter, key);
	return outStreamTypeCounter[pos];
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutStreamIsInDtsSet(CrFwDestSrc_t dest, 
                                   CrFwServType_t servType,
                                   CrFwServSubType_t servSubType) {

	CrFwDestTypeKey_t key;
	CrFwCounterU2_t pos;
	key = servType*CR_FW_MAX_SERV_SUBTYPE*CR_FW_MAX_DEST + servSubType*CR_FW_MAX_DEST + dest;
	pos = CrFwFindKeyIndex(outStreamDestTypeKey, outStreamNofTypeCounter, key);
	if (pos == outStreamNofTypeCounter)
		return 0;
	else
		return 1;
}