/**
 * @file
 *
 * Implementation of test cases for InStream Component.
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
#include "CrFwInStreamTestCases.h"
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

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInStreamTestCase1() {
	FwSmDesc_t inStream0, inStreamBis, inStream[CR_FW_NOF_INSTREAM];
	CrFwDestSrc_t inStreamSrcPairs[CR_FW_INSTREAM_NOF_SRCS][2] = CR_FW_INSTREAM_SRC_PAIRS;
	CrFwInstanceId_t i;

	/* Attempt to instantiate an InStream with an illegal identifier */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;
	inStream0 = CrFwInStreamMake(CR_FW_NOF_INSTREAM + 1);
	if (inStream0 != NULL)
		return 0;
	if (CrFwGetAppErrCode() != crInStreamIllId)
		return 0;
	CrFwSetAppErrCode(crNoAppErr); 	/* reset application error code */

	/* Create the first InStream */
	inStream0 = CrFwInStreamMake(0);
	if (inStream0 == NULL)
		return 0;

	/* Create the first InStream again and check that the same component is returned */
	inStreamBis = CrFwInStreamMake(0);
	if (inStream0 != inStreamBis)
		return 0;

	/* Check configuration of InStream */
	if (FwSmCheckRec(inStream0) != smSuccess)
		return 0;

	/* Initialize inStream and check success */
	if (!CrFwCmpIsInCreated(inStream0))
		return 0;

	CrFwCmpInit(inStream0);
	if (!CrFwCmpIsInInitialized(inStream0))
		return 0;

	/* Verify sources attached to inStream0 */
	if (CrFwInStreamGetNOfSrc(inStream0) != 2)	/* Sources of inStream0 are defined in CR_FW_INSTREAM_SRC_PAIRS */
		return 0;
	if (CrFwInStreamGetSrc(inStream0, 1) != 1)
		return 0;
	if (CrFwInStreamGetSrc(inStream0, 2) != 6)
		return 0;

	/* Verify packet queue size (defined in CR_FW_INSTREAM_PQSIZE) */
	if (CrFwInStreamGetPcktQueueSize(inStream0) != 3)
		return 0;

	/* Reset InStream */
	CrFwCmpReset(inStream0);
	if (!CrFwCmpIsInConfigured(inStream0))
		return 0;

	/* Since the packet available stub declares "packet is not available", the InStream is in WAITING */
	if (!CrFwInStreamIsInWaiting(inStream0))
		return 0;

	if (CrFwInStreamGetSeqCnt(0) != 0)
		return 0;

	if (CrFwInStreamGetNOfPendingPckts(inStream0) != 0)
		return 0;

	/* Check the function to get the InStream as a function of packet source under nominal conditions */
	for (i=0; i<CR_FW_NOF_INSTREAM; i++)
		inStream[i] = CrFwInStreamMake(i);
	if (CrFwInStreamGet(inStreamSrcPairs[0][0])!=inStream[inStreamSrcPairs[0][1]])
		return 0;
	if (CrFwInStreamGet(inStreamSrcPairs[1][0])!=inStream[inStreamSrcPairs[1][1]])
		return 0;
	if (CrFwInStreamGet(inStreamSrcPairs[CR_FW_INSTREAM_NOF_SRCS-1][0])!=\
			inStream[inStreamSrcPairs[CR_FW_INSTREAM_NOF_SRCS-1][1]])
		return 0;

	/* Check the function to get the InStream as a function of packet source under non-nominal conditions */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;
	if (CrFwInStreamGet(0)!=NULL)	/* No packet source has identifier zero */
		return 0;
	if (CrFwGetAppErrCode() != crInStreamUndefDest)
		return 0;
	CrFwSetAppErrCode(crNoAppErr); 	/* reset application error code */

	/* Check the function to get the number of groups (this is set in CrFwInStreamUserPar.h) */
	if (CrFwInStreamGetNOfGroups() != 2)
		return 0;

	/* Check that all packets have been de-allocated */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInStreamTestCase2() {
	FwSmDesc_t inStream0;
	CrFwPckt_t pckt1, pckt2;

	/* Retrieve the first InStream */
	inStream0 = CrFwInStreamMake(0);
	if (inStream0 == NULL)
		return 0;

	/* Check packet queue size (defined in CR_FW_INSTREAM_PQSIZE)*/
	if (CrFwInStreamGetPcktQueueSize(inStream0) != 3)
		return 0;

	/* Verify that InStream is in WAITING */
	if (!CrFwInStreamIsInWaiting(inStream0))
		return 0;

	/* Send PACKET_AVAILABLE command to InStream at a time when no packets are available and
	 * verify that InStream remains in WAITING */
	CrFwInStreamPcktAvail(inStream0);
	if (!CrFwInStreamIsInWaiting(inStream0))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream0) != 0)
		return 0;

	/* Send GET_PCKT command to InStream and verify that nothing is returned */
	pckt1 = CrFwInStreamGetPckt(inStream0);
	if (pckt1 != NULL)
		return 0;
	if (!CrFwInStreamIsInWaiting(inStream0))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream0) != 0)
		return 0;

	/* Set up stub to simulate presence of two packets for the host application */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);
	CrFwInStreamStubSetPcktGroup(0);		
	CrFwInStreamStubSetPcktCollectionCnt(2);
	CrFwInStreamStubSetPcktSeqCnt(5555);

	/* Send PACKET_AVAILABLE command to InStream */
	CrFwInStreamSetSeqCnt(0, 5555);
	CrFwInStreamPcktAvail(inStream0);
	if (!CrFwInStreamIsInPcktAvail(inStream0))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream0) != 2)
		return 0;
	if (CrFwInStreamGetSeqCnt(0) != (5555+2))
		return 0;

	/* Send first GET_PCKT command to InStream */
	pckt1 = CrFwInStreamGetPckt(inStream0);
	if (!CrFwInStreamIsInPcktAvail(inStream0))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream0) != 1)
		return 0;
	if (CrFwPcktGetSeqCnt(pckt1) != 5556)
		return 0;

	/* Send second GET_PCKT command to InStream */
	pckt2 = CrFwInStreamGetPckt(inStream0);
	if (!CrFwInStreamIsInWaiting(inStream0))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream0) != 0)
		return 0;
	if (CrFwPcktGetSeqCnt(pckt2) != 5557)
		return 0;

	/* De-allocate packets */
	CrFwPcktRelease(pckt1);
	CrFwPcktRelease(pckt2);

	/* Check that all packets have been de-allocated */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInStreamTestCase3() {
	FwSmDesc_t inStream0;
	CrFwSeqCnt_t seqCnt;

	/* Retrieve the first InStream */
	inStream0 = CrFwInStreamMake(0);
	if (inStream0 == NULL)
		return 0;

	/* Set up stub to simulate presence of one packet for the host application */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);
	CrFwInStreamStubSetPcktGroup(0);		/* First InStream only has one group */
	CrFwInStreamStubSetPcktCollectionCnt(1);

	/* Check initial state of InStream */
	if (!CrFwInStreamIsInWaiting(inStream0))
		return 0;

	/* Get current sequence counter value */
	seqCnt = CrFwInStreamGetSeqCnt(0);

	/* Send PACKET_AVAILABLE command to InStream */
	CrFwInStreamPcktAvail(inStream0);
	if (!CrFwInStreamIsInPcktAvail(inStream0))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream0) != 1)
		return 0;
	if (CrFwInStreamGetSeqCnt(0) != seqCnt+1)
		return 0;

	/* Set up stub to simulate presence of one more packet in the middleware */
	CrFwInStreamStubSetPcktCollectionCnt(1);

	/* Send PACKET_AVAILABLE command again to InStream */
	CrFwInStreamPcktAvail(inStream0);
	if (!CrFwInStreamIsInPcktAvail(inStream0))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream0) != 2)
		return 0;
	if (CrFwInStreamGetSeqCnt(0) != seqCnt+2)
		return 0;

	/* Send SHUTDOWN command to InStream */
	CrFwCmpShutdown(inStream0);
	if (CrFwCmpIsStarted(inStream0) != 0)
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream0) != 0)
		return 0;

	/* Check that all packets have been de-allocated */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInStreamTestCase4() {
	FwSmDesc_t inStream0;
	CrFwCounterU2_t errRepPosLocal;
	CrFwPckt_t pckt;
	CrFwPcktLength_t i, n;

	/* Reset the error reporting interface */
	CrFwRepErrStubReset();

	/* Retrieve the first InStream */
	inStream0 = CrFwInStreamMake(0);
	if (inStream0 == NULL)
		return 0;

	/* Check the initial state of the InStream */
	if (CrFwCmpIsStarted(inStream0) != 0)
		return 0;

	/* Set up stub to simulate absence of packets in the middleware */
	CrFwInStreamStubSetPcktCollectionCnt(0);

	/* Start and configure the InStream */
	FwSmStart(inStream0);
	CrFwCmpInit(inStream0);
	CrFwCmpReset(inStream0);
	if (!CrFwInStreamIsInWaiting(inStream0))
		return 0;

	/* Set up stub to simulate packets for the host application (i.e. not in transit) */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);
	CrFwInStreamStubSetPcktGroup(0);		/* First InStream only has one group */

	/* Set up stub to simulate presence of one packet for the host application */
	CrFwInStreamStubSetPcktCollectionCnt(1);

	/* Reset the sequence counter of the packets generated by the middleware stub */
	CrFwInStreamStubSetPcktSeqCnt(0);

	/* Send PACKET_AVAILABLE command to InStream */
	CrFwInStreamPcktAvail(inStream0);
	if (!CrFwInStreamIsInPcktAvail(inStream0))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream0) != 1)
		return 0;
	if (CrFwInStreamGetSeqCnt(0) != 1)
		return 0;

	/* Set up stub to simulate presence of one more packet in the middleware */
	CrFwInStreamStubSetPcktCollectionCnt(1);

	/* Set up the stub to simulate a sequence counter error */
	CrFwInStreamStubSetPcktSeqCnt(9);

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Send PACKET_AVAILABLE command to InStream */
	CrFwInStreamPcktAvail(inStream0);
	if (!CrFwInStreamIsInPcktAvail(inStream0))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream0) != 2)
		return 0;
	if (CrFwInStreamGetSeqCnt(0) != 10)
		return 0;
	if (CrFwRepErrStubGetPos() != errRepPosLocal+1)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crInStreamSCErr)
		return 0;
	if (CrFwRepErrStubGetTypeId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != CR_FW_INSTREAM_TYPE)
		return 0;
	if (CrFwRepErrStubGetInstanceId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != 0)
		return 0;
	if (CrFwRepErrStubGetExpSeqCnt((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != 2)
		return 0;
	if (CrFwRepErrStubGetActualSeqCnt((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != 10)
		return 0;

	/* Set up stub to simulate presence of a packet in transit in the middleware */
	CrFwInStreamStubSetPcktCollectionCnt(1);
	CrFwInStreamStubSetPcktGroup(99);		/* group should not matter since packet is in transit */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID+1);

	/* Set up the stub to simulate a sequence counter error */
	CrFwInStreamStubSetPcktSeqCnt(99);

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Send PACKET_AVAILABLE command to InStream */
	CrFwInStreamPcktAvail(inStream0);
	if (!CrFwInStreamIsInPcktAvail(inStream0))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream0) != 3)
		return 0;
	if (CrFwInStreamGetSeqCnt(0) != 10)
		return 0;
	if (CrFwRepErrStubGetPos() != errRepPosLocal)
		return 0;

	/* Collect and release the packets in the packet queue */
	n = CrFwInStreamGetNOfPendingPckts(inStream0);
	for (i=0; i<n; i++) {
		pckt = CrFwInStreamGetPckt(inStream0);
		if (pckt == NULL)
			return 0;
		CrFwPcktRelease(pckt);
	}

	/* Set up the stub to simulate the presence of (N+1) packets for the host application */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);
	CrFwInStreamStubSetPcktGroup(0);		/* First InStream only has one group */
	CrFwInStreamStubSetPcktCollectionCnt((CrFwCounterU1_t)(CrFwInStreamGetPcktQueueSize(inStream0) + 1));
	CrFwInStreamStubSetPcktSeqCnt(CrFwInStreamGetSeqCnt(0));	/* no seq. cnt. error */

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Send PACKET_AVAILABLE command to InStream (this results in a "PQ Full" error */
	CrFwInStreamPcktAvail(inStream0);
	if (!CrFwInStreamIsInPcktAvail(inStream0))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream0) != CrFwInStreamGetPcktQueueSize(inStream0))
		return 0;
	if (CrFwInStreamGetSeqCnt(0) != (CrFwSeqCnt_t)(10+CrFwInStreamGetPcktQueueSize(inStream0)+1))
		return 0;
	if (CrFwRepErrStubGetPos() != errRepPosLocal+1)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crInStreamPQFull)
		return 0;
	if (CrFwRepErrStubGetTypeId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != CR_FW_INSTREAM_TYPE)
		return 0;
	if (CrFwRepErrStubGetInstanceId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != 0)
		return 0;

	/* Collect and release the packets in the packet queue */
	n = CrFwInStreamGetNOfPendingPckts(inStream0);
	for (i=0; i<n; i++) {
		pckt = CrFwInStreamGetPckt(inStream0);
		if (pckt == NULL)
			return 0;
		CrFwPcktRelease(pckt);
	}

	/* Reset InStream (to ensure that any hanging packets are released) */
	CrFwCmpReset(inStream0);

	/* Check that all packets have been released */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}


/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInStreamTestCase5() {
	FwSmDesc_t inStream3;

	/* Create the fourth InStream */
	inStream3 = CrFwInStreamMake(3);
	if (inStream3 == NULL)
		return 0;

	/* Configure the newly-created InStream */
	CrFwCmpInit(inStream3);
	CrFwCmpReset(inStream3);
	if (!CrFwCmpIsInConfigured(inStream3))
		return 0;

	/* Check that the correct source has been loaded */
	if (CrFwInStreamGetSrc(inStream3, 1) != 4)
		return 0;

	/* Shut down the newly-created InStream */
	CrFwCmpShutdown(inStream3);

	/* Configure initialization check and action until initialization succeeds */
	CrFwInStreamStubSetCheckFlag(0);
	CrFwInStreamStubSetActionFlag(0);
	FwSmStart(inStream3);
	if (!CrFwCmpIsInCreated(inStream3))
		return 0;

	CrFwCmpInit(inStream3);
	if (!CrFwCmpIsInCreated(inStream3))
		return 0;

	CrFwInStreamStubSetCheckFlag(1);
	CrFwInStreamStubSetActionFlag(0);
	CrFwCmpInit(inStream3);
	if (!CrFwCmpIsInCreated(inStream3))
		return 0;

	CrFwInStreamStubSetCheckFlag(0);
	CrFwInStreamStubSetActionFlag(1);
	CrFwCmpInit(inStream3);
	if (!CrFwCmpIsInCreated(inStream3))
		return 0;

	CrFwInStreamStubSetCheckFlag(1);
	CrFwInStreamStubSetActionFlag(1);
	CrFwCmpInit(inStream3);
	if (!CrFwCmpIsInInitialized(inStream3))
		return 0;

	/* Configure configuration check and action until configuration succeeds */
	CrFwInStreamStubSetCheckFlag(0);
	CrFwInStreamStubSetActionFlag(0);
	CrFwCmpReset(inStream3);
	if (!CrFwCmpIsInInitialized(inStream3))
		return 0;

	CrFwInStreamStubSetCheckFlag(1);
	CrFwInStreamStubSetActionFlag(0);
	CrFwCmpReset(inStream3);
	if (!CrFwCmpIsInInitialized(inStream3))
		return 0;

	CrFwInStreamStubSetCheckFlag(0);
	CrFwInStreamStubSetActionFlag(1);
	CrFwCmpReset(inStream3);
	if (!CrFwCmpIsInInitialized(inStream3))
		return 0;

	CrFwInStreamStubSetCheckFlag(1);
	CrFwInStreamStubSetActionFlag(1);
	CrFwCmpReset(inStream3);
	if (!CrFwCmpIsInConfigured(inStream3))
		return 0;

	/* Configure configuration check and action to fail and then check that component reset fails */
	CrFwInStreamStubSetCheckFlag(0);
	CrFwCmpReset(inStream3);
	if (!CrFwCmpIsInInitialized(inStream3))
		return 0;

	/* Shut down the InStream */
	CrFwCmpShutdown(inStream3);

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInStreamTestCase6() {
	FwSmDesc_t inStream1;

	/* Create the second InStream */
	inStream1 = CrFwInStreamMake(1);
	if (inStream1 == NULL)
		return 0;

	/* Check that InStream is in STARTED state */
	if (CrFwCmpIsStarted(inStream1) != 1)
		return 0;

	/* Set up stub to simulate presence of one packet for the host application */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);
	CrFwInStreamStubSetPcktGroup(0);		/* Second InStream only has one group */
	CrFwInStreamStubSetPcktCollectionCnt(1);

	/* Bring InStream to state CONFIGURED */
	FwSmStart(inStream1);
	CrFwCmpInit(inStream1);
	CrFwCmpReset(inStream1);
	if (!CrFwCmpIsInConfigured(inStream1))
		return 0;

	/* Check that InStream is in PCKT_AVAIL */
	if (!CrFwInStreamIsInPcktAvail(inStream1))
		return 0;

	/* Shutdown the newly-created InStream */
	CrFwCmpShutdown(inStream1);
	if (CrFwInStreamStubGetShutdownCnt() != 1)
		return 0;

	if (CrFwCmpIsStarted(inStream1) != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInStreamTestCase7() {
	FwSmDesc_t inStream2;
	CrFwPckt_t pckt1, pckt2, pckt3;
	CrFwGroup_t i;
	CrFwCounterU2_t errRepPosLocal;

	/* Reset the error reporting interface */
	CrFwRepErrStubReset();

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Retrieve the third InStream (this InStream must have two groups) */
	inStream2 = CrFwInStreamMake(2);
	if (inStream2 == NULL)
		return 0;

	/* Start and configure the InStream */
	FwSmStart(inStream2);
	CrFwCmpInit(inStream2);
	CrFwCmpReset(inStream2);
	if (!CrFwInStreamIsInWaiting(inStream2))
		return 0;

	/* Check value of sequence counters */
	for (i=0; i<CrFwInStreamGetNOfGroups(); i++)
		if (CrFwInStreamGetSeqCnt(i) != 0)
			return 0;

	/* Set up stub to simulate presence of two packets for the host application belonging to first group */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);
	CrFwInStreamStubSetPcktSeqCnt(100);
	CrFwInStreamStubSetPcktGroup(0);
	CrFwInStreamStubSetPcktCollectionCnt(2);

	/* Send PACKET_AVAILABLE command to InStream */
	CrFwInStreamPcktAvail(inStream2);
	if (!CrFwInStreamIsInPcktAvail(inStream2))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream2) != 2)
		return 0;
	if (CrFwInStreamGetSeqCnt(0) != 102)
		return 0;

	/* Set up stub to simulate presence of packet for the host application belonging to second group */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);
	CrFwInStreamStubSetPcktSeqCnt(200);
	CrFwInStreamStubSetPcktGroup(1);
	CrFwInStreamStubSetPcktCollectionCnt(1);

	/* Send PACKET_AVAILABLE command to InStream */
	CrFwInStreamPcktAvail(inStream2);
	if (!CrFwInStreamIsInPcktAvail(inStream2))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream2) != 3)
		return 0;
	if (CrFwInStreamGetSeqCnt(1) != 201)
		return 0;

	/* Send GET_PCKT commands to InStream */
	pckt1 = CrFwInStreamGetPckt(inStream2);
	if (!CrFwInStreamIsInPcktAvail(inStream2))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream2) != 2)
		return 0;
	if (CrFwPcktGetSeqCnt(pckt1) != 101)
		return 0;

	pckt2 = CrFwInStreamGetPckt(inStream2);
	if (!CrFwInStreamIsInPcktAvail(inStream2))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream2) != 1)
		return 0;
	if (CrFwPcktGetSeqCnt(pckt2) != 102)
		return 0;

	pckt3 = CrFwInStreamGetPckt(inStream2);
	if (!CrFwInStreamIsInWaiting(inStream2))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream2) != 0)
		return 0;
	if (CrFwPcktGetSeqCnt(pckt3) != 201)
		return 0;

	if (CrFwRepErrStubGetPos() != errRepPosLocal)
		return 0;

	/* De-allocate packets */
	CrFwPcktRelease(pckt1);
	CrFwPcktRelease(pckt2);
	CrFwPcktRelease(pckt3);

	/* Set up stub to simulate presence of packet for the host application belonging to non-existent group */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);
	CrFwInStreamStubSetPcktGroup((CrFwGroup_t)(CrFwInStreamGetNOfGroups()+1));
	CrFwInStreamStubSetPcktCollectionCnt(1);

	/* Send PACKET_AVAILABLE command to InStream */
	CrFwInStreamPcktAvail(inStream2);
	if (!CrFwInStreamIsInPcktAvail(inStream2))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream2) != 1)
		return 0;
	if (CrFwInStreamGetSeqCnt(0) != 102)
		return 0;
	if (CrFwInStreamGetSeqCnt(1) != 201)
		return 0;

	if (CrFwRepErrStubGetPos() != errRepPosLocal+1)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crInStreamIllGroup)
		return 0;

	/* Send GET_PCKT command to InStream */
	pckt1 = CrFwInStreamGetPckt(inStream2);
	if (!CrFwInStreamIsInWaiting(inStream2))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream2) != 0)
		return 0;

	/* De-allocate packets */
	CrFwPcktRelease(pckt1);

	/* Shutdown the InStream */
	CrFwCmpShutdown(inStream2);

	/* Check that all packets have been de-allocated */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}
