/**
 * @file
 *
 * Implementation of OutStream State Machine.
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
#include<string.h>
/* Include configuration files */
#include "CrFwOutStreamUserPar.h"
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

/** Base OutStream from which all other OutStreams are derived. */
static FwSmDesc_t baseOutStreamSmDesc = NULL;

/** The sizes of the packet queues in the OutStream components. */
static CrFwCounterU1_t outStreamPcktQueueSize[CR_FW_NOF_OUTSTREAM] = CR_FW_OUTSTREAM_PQSIZE;

/** The destinations associated to the OutStream components. */
static CrFwDestSrc_t outStreamDest[CR_FW_NOF_OUTSTREAM] = CR_FW_OUTSTREAM_DEST;

/** The number of groups associated to the OutStream components. */
static CrFwGroup_t outStreamNOfGroups[CR_FW_NOF_OUTSTREAM] = CR_FW_OUTSTREAM_NOF_GROUPS;

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
 * Function which resets to 1 the sequence counter of an out-going packet.
 * This function is used as transition action on the transition out of the initial
 * state.
 * @param smDesc the state machine descriptor
 */
static void ResetSeqCounter(FwSmDesc_t smDesc);

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

	/* If not yet done, create the base OutStream SM */
	if (baseOutStreamSmDesc == NULL) {
		/* Extend the Base Component */
		baseOutStreamSmDesc = FwSmCreateDer(CrFwBaseCmpMake());
		/* Create the OutStream SM and then embed it in state CONFIGURED of the Base Component */
		esm = FwSmCreate(nOfStates, nOfChoicePseudoStates, nOfTrans, nOfActions, nOfGuards);
		FwSmAddState(esm, CR_FW_OUTSTREAM_STATE_READY, 1, NULL, NULL, NULL, NULL);
		FwSmAddState(esm, CR_FW_OUTSTREAM_STATE_BUFFERING, 2, NULL, NULL, NULL, NULL);
		FwSmAddChoicePseudoState(esm, CPS_1, 2);
		FwSmAddTransIpsToSta(esm, CR_FW_OUTSTREAM_STATE_READY, &ResetSeqCounter);
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
	outStreamCmpSpecificData[i].dest = outStreamDest[i];
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
	CrFwInstanceId_t i;
	for (i=0; i<CR_FW_NOF_OUTSTREAM; i++)
		if (outStreamCmpSpecificData[i].dest == dest)
			return outStreamDesc[i];

	CrFwSetAppErrCode(crOutStreamUndefDest);
	return NULL;
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
CrFwDestSrc_t CrFwOutStreamGetDest(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	return cmpSpecificData->dest;
}

/*-----------------------------------------------------------------------------------------*/
CrFwSeqCnt_t CrFwOutStreamGetSeqCnt(FwSmDesc_t smDesc, CrFwGroup_t group) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	return cmpSpecificData->seqCnt[group];
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwOutStreamGetNOfPendingPckts(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	return CrFwPcktQueueGetNOfPckts(&(cmpSpecificData->pcktQueue));
}

/*-----------------------------------------------------------------------------------------*/
CrFwGroup_t CrFwOutStreamGetNOfGroups(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	return outStreamNOfGroups[outStreamBaseData->instanceId];
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
	cmpSpecificData->dest = outStreamDest[outStreamBaseData->instanceId];
	cmpSpecificData->handoverPckt = outStreamHandoverPckt[outStreamBaseData->instanceId];
	outStreamBaseData->outcome = 1;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwOutStreamDefShutdownAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	CrFwPcktQueueShutdown(&(cmpSpecificData->pcktQueue));
	free(cmpSpecificData->seqCnt);
	cmpSpecificData->seqCnt = NULL;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwOutStreamDefInitAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwInstanceId_t i = outStreamBaseData->instanceId;
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;

	cmpSpecificData->seqCnt = malloc(sizeof(CrFwSeqCnt_t)*outStreamNOfGroups[i]);
	CrFwPcktQueueInit(&(outStreamCmpSpecificData[i].pcktQueue),outStreamPcktQueueSize[i]);
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
	CrFwPcktQueue_t pcktQueue = &(cmpSpecificData->pcktQueue);
	CrFwGroup_t oldestPcktGroup;

	while (CrFwPcktQueueIsEmpty(pcktQueue)==0) {
		oldestPckt = CrFwPcktQueueGetOldest(pcktQueue);
		if (CrFwPcktGetSrc(oldestPckt) == CR_FW_HOST_APP_ID) { /* pckt originates from host application */
			oldestPcktGroup = CrFwPcktGetGroup(oldestPckt);
			if (oldestPcktGroup < outStreamNOfGroups[outStreamBaseData->instanceId])
				CrFwPcktSetSeqCnt(oldestPckt, cmpSpecificData->seqCnt[oldestPcktGroup]);
			else	/* pckt belongs to a non-existent group */
				CrFwRepErrGroup(crOutStreamIllGroup, outStreamBaseData->typeId,
				                outStreamBaseData->instanceId, oldestPcktGroup);
		}
		if (cmpSpecificData->handoverPckt(oldestPckt) != 1)
			return;
		if (CrFwPcktGetSrc(oldestPckt) == CR_FW_HOST_APP_ID)
			if (oldestPcktGroup < outStreamNOfGroups[outStreamBaseData->instanceId])
				cmpSpecificData->seqCnt[oldestPcktGroup]++;
		CrFwPcktQueuePop(pcktQueue);	/* remove packet from PQ */
		CrFwPcktRelease(oldestPckt);
	}
	return;
}

/*-----------------------------------------------------------------------------------------*/
static void ResetSeqCounter(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	CrFwGroup_t i;
	for (i=0; i<outStreamNOfGroups[outStreamBaseData->instanceId]; i++)
		cmpSpecificData->seqCnt[i] = 1;
}

/*-----------------------------------------------------------------------------------------*/
static void SendOrEnqueue(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	CrFwPckt_t pckt = cmpSpecificData->pckt;
	CrFwPckt_t pcktCopy;
	CrFwPcktLength_t len;
	CrFwPcktQueue_t pcktQueue;
	CrFwGroup_t pcktGroup;

	if (CrFwPcktGetSrc(pckt) == CR_FW_HOST_APP_ID) { /* pckt originates from host application */
		pcktGroup = CrFwPcktGetGroup(pckt);
		if (pcktGroup < outStreamNOfGroups[outStreamBaseData->instanceId])
			CrFwPcktSetSeqCnt(pckt, cmpSpecificData->seqCnt[pcktGroup]);
		else	/* pckt belongs to a non-existent group */
			CrFwRepErrGroup(crOutStreamIllGroup, outStreamBaseData->typeId,
			                outStreamBaseData->instanceId, pcktGroup);
	}
	if (cmpSpecificData->handoverPckt(pckt) != 1) {
		pcktQueue = &(cmpSpecificData->pcktQueue);
		len = CrFwPcktGetLength(pckt);
		pcktCopy = CrFwPcktMake(len);
		if (pcktCopy == NULL) {
			CrFwRepErr(crOutStreamNoMorePckt, outStreamBaseData->typeId, outStreamBaseData->instanceId);
			return;
		}
		memcpy(pcktCopy,pckt,len);
		CrFwPcktQueuePush(pcktQueue,pcktCopy);	/* Enqueue packet, queue is empty at entry in READY */
	} else {
		if (CrFwPcktGetSrc(pckt) == CR_FW_HOST_APP_ID)
			if (pcktGroup < outStreamNOfGroups[outStreamBaseData->instanceId])
				cmpSpecificData->seqCnt[pcktGroup]++;
	}
}

/*-----------------------------------------------------------------------------------------*/
static int IsPacketQueueEmpty(FwSmDesc_t smDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	return CrFwPcktQueueIsEmpty(&(cmpSpecificData->pcktQueue));
}

