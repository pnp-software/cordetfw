/**
 * @file
 *
 * Implementation of test cases for OutStream Component.
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
#include "CrFwOutStreamTestCases.h"
#include "CrFwOutStreamStub.h"
#include "CrFwRepErrStub.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include configuration files */
#include "CrFwOutStreamUserPar.h"
#include "CrFwCmpData.h"
/* Include framework files */
#include "OutStream/CrFwOutStream.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "Pckt/CrFwPckt.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutStreamTestCase1() {
	FwSmDesc_t outStream0, outStreamBis;
	CrFwPckt_t pckt, pckt1, pckt2;
	CrFwCounterU2_t i, errRepPosLocal;

	/* Reset error reporting interface */
	CrFwRepErrStubReset();

	/* Attempt to instantiate an OutStream with an illegal identifier */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;
	outStream0 = CrFwOutStreamMake(CR_FW_NOF_OUTSTREAM);
	if (outStream0 != NULL)
		return 0;
	if (CrFwGetAppErrCode() != crOutStreamIllId)
		return 0;
	CrFwSetAppErrCode(crNoAppErr); 	/* reset application error code */

	/* Check that the type counter array has not yet been instantiated */
	if (CrFwOutStreamGetNOfTypeCounters() != 0)
		return 0;

	/* Create the first OutStream */
	outStream0 = CrFwOutStreamMake(0);
	if (outStream0 == NULL)
		return 0;

	/* Check that the type counter array has been instantiated 
	   (expected number is number of (type.sub-type) pairs defined in OutFactoryUserPar.h) )*/
	if (CrFwOutStreamGetNOfTypeCounters() != 10)
		return 0;

	/* Create the first OutStream again and check that the same component is returned */
	outStreamBis = CrFwOutStreamMake(0);
	if (outStream0 != outStreamBis)
		return 0;

	/* Check configuration of OutStream */
	if (FwSmCheckRec(outStream0) != smSuccess)
		return 0;

	if (FwPrCheck(CrFwCmpGetInitPr(outStream0)) != prSuccess)
		return 0;

	if (FwPrCheck(CrFwCmpGetResetPr(outStream0)) != prSuccess)
		return 0;

	if (FwPrCheck(CrFwCmpGetExecPr(outStream0)) != prSuccess)
		return 0;

	/* Initialize and reset outStream and check success */
	if (!CrFwCmpIsInCreated(outStream0))
		return 0;

	CrFwCmpInit(outStream0);
	if (!CrFwCmpIsInInitialized(outStream0))
		return 0;

	CrFwCmpReset(outStream0);
	if (!CrFwCmpIsInConfigured(outStream0))
		return 0;
	if (!CrFwOutStreamIsInReady(outStream0))
		return 0;

	/* Check that handed-over counters are zero */
	if (CrFwOutStreamGetNOfHandedOverBytes(outStream0) != 0) 
		return 0;
	if (CrFwOutStreamGetNOfHandedOverPckts(outStream0) != 0)
		return 0;		

	/* Check initial value of sequence counters */
	for (i=0; i<CrFwOutStreamGetNOfGroups(); i++)
		if (CrFwOutStreamGetSeqCnt((CrFwGroup_t)i) != 1)
			return 0;

	/* Check the association between destination and outStream 
	   (the (dest,outStream) pairs are defined in CR_FW_OUTSTREAM_DEST_PAIRS)*/
	if (CrFwOutStreamGetNOfDest(outStream0) != 2)
		return 0;
	if (CrFwOutStreamGetDest(outStream0,1) != 1)
		return 0;
	if (CrFwOutStreamGetDest(outStream0,2) != 2)
		return 0;
		
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 0)
		return 0;

	/* Configure the Packet Hand-Over Operation to return "hand-over failed" */
	CrFwOutStreamStubSetHandoverFlag(0);

	/* Make a packet and assign it to the first group */
	pckt1 = CrFwPcktMake(CrFwPcktGetMaxLength());
	CrFwPcktSetGroup(pckt1,0);
	CrFwPcktSetTypeCnt(pckt1,0);
	CrFwPcktSetSeqCnt(pckt1,0);

	/* Send a packet to the OutStream and check outcome */
	CrFwOutStreamSend(outStream0, pckt1);
	if (!CrFwOutStreamIsInBuffering(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 1)
		return 0;
	if (CrFwOutStreamGetSeqCnt(0) != 1)
		return 0;
	if (CrFwPcktGetSeqCnt(pckt1) != 0)
		return 0;
	if (CrFwPcktGetTypeCnt(pckt1) != 0)
		return 0;
	CrFwPcktRelease(pckt1);

	/* Check that handed-over counters are zero */
	if (CrFwOutStreamGetNOfHandedOverBytes(outStream0) != 0) 
		return 0;
	if (CrFwOutStreamGetNOfHandedOverPckts(outStream0) != 0)
		return 0;		

	/* Fill up packet queue */
	for (i=1; i<CrFwOutStreamGetPcktQueueSize(outStream0); i++) {
		pckt = CrFwPcktMake(CrFwPcktGetMaxLength());
		CrFwPcktSetGroup(pckt,0);
		CrFwOutStreamSend(outStream0, pckt);
		CrFwPcktRelease(pckt);
	}
	if (!CrFwOutStreamIsInBuffering(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != CrFwOutStreamGetPcktQueueSize(outStream0))
		return 0;
	if (CrFwOutStreamGetSeqCnt(0) != 1)
		return 0;

	/* Make a new packet and send it (this overflows the packet queue) */
	errRepPosLocal = CrFwRepErrStubGetPos();
	pckt2 = CrFwPcktMake(CrFwPcktGetMaxLength());
	for (i=1; i<CrFwPcktGetMaxLength(); i++)
		pckt2[i] = 0;	/* clear packet content */
	CrFwOutStreamSend(outStream0, pckt2);
	if (!CrFwOutStreamIsInBuffering(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != CrFwOutStreamGetPcktQueueSize(outStream0))
		return 0;
	if (CrFwOutStreamGetSeqCnt(0) != 1)
		return 0;
	if (CrFwPcktGetSeqCnt(pckt2) != 0)
		return 0;
	if (CrFwRepErrStubGetPos() != errRepPosLocal+1)
		return 0;
	if (CrFwRepErrStubGetErrCode(errRepPosLocal) != crOutStreamPQFull)
		return 0;
	if (CrFwRepErrStubGetTypeId(errRepPosLocal) != CR_FW_OUTSTREAM_TYPE)
		return 0;
	if (CrFwRepErrStubGetInstanceId(errRepPosLocal) != 0)
		return 0;
	CrFwPcktRelease(pckt2);

	/* Reset the OutStream */
	CrFwCmpReset(outStream0);
	if (!CrFwOutStreamIsInReady(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 0)
		return 0;

	/* Shutdown the OutStream */
	CrFwCmpShutdown(outStream0);

	if (CrFwCmpIsStarted(outStream0) != 0)
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 0)
		return 0;
	if (CrFwOutStreamGetNOfDest(outStream0) != 0)
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
CrFwBool_t CrFwOutStreamTestCase2() {
	FwSmDesc_t outStream3;

	/* Create the fourth OutStream */
	outStream3 = CrFwOutStreamMake(3);
	if (outStream3 == NULL)
		return 0;

	/* Configure initialization check and action until initialization succeeds */
	CrFwOutStreamStubSetCheckFlag(0);
	CrFwOutStreamStubSetActionFlag(0);
	if (!CrFwCmpIsInCreated(outStream3))
		return 0;

	CrFwCmpInit(outStream3);
	if (!CrFwCmpIsInCreated(outStream3))
		return 0;

	/* Shut down InStream to prevent memory leak when the component is initialized again */
	CrFwCmpShutdown(outStream3);

	CrFwOutStreamStubSetCheckFlag(1);
	CrFwOutStreamStubSetActionFlag(0);
	CrFwCmpInit(outStream3);
	if (!CrFwCmpIsInCreated(outStream3))
		return 0;

	/* Shut down InStream to prevent memory leak when the component is initialized again */
	CrFwCmpShutdown(outStream3);

	CrFwOutStreamStubSetCheckFlag(0);
	CrFwOutStreamStubSetActionFlag(1);
	CrFwCmpInit(outStream3);
	if (!CrFwCmpIsInCreated(outStream3))
		return 0;

	/* Shut down InStream to prevent memory leak when the component is initialized again */
	CrFwCmpShutdown(outStream3);

 	CrFwOutStreamStubSetCheckFlag(1);
	CrFwOutStreamStubSetActionFlag(1);
	CrFwCmpInit(outStream3);
	if (!CrFwCmpIsInInitialized(outStream3))
		return 0;

	/* Configure configuration check and action until configuration succeeds */
	CrFwOutStreamStubSetCheckFlag(0);
	CrFwOutStreamStubSetActionFlag(0);
	CrFwCmpReset(outStream3);
	if (!CrFwCmpIsInInitialized(outStream3))
		return 0;

	CrFwOutStreamStubSetCheckFlag(1);
	CrFwOutStreamStubSetActionFlag(0);
	CrFwCmpReset(outStream3);
	if (!CrFwCmpIsInInitialized(outStream3))
		return 0;

	CrFwOutStreamStubSetCheckFlag(0);
	CrFwOutStreamStubSetActionFlag(1);
	CrFwCmpReset(outStream3);
	if (!CrFwCmpIsInInitialized(outStream3))
		return 0;

	CrFwOutStreamStubSetCheckFlag(1);
	CrFwOutStreamStubSetActionFlag(1);
	CrFwCmpReset(outStream3);
	if (!CrFwCmpIsInConfigured(outStream3))
		return 0;

	/* Configure configuration check and action to fail and then check that component reset fails */
	CrFwOutStreamStubSetCheckFlag(0);
	CrFwCmpReset(outStream3);
	if (!CrFwCmpIsInInitialized(outStream3))
		return 0;

	/* Shut down OutStream */	
	CrFwCmpShutdown(outStream3);

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutStreamTestCase3() {
	FwSmDesc_t outStream0;
	CrFwPckt_t pckt1, pckt2, pckt3, pckt;
	CrFwPckt_t  pcktArray[CR_FW_MAX_NOF_PCKTS];
	CrFwCounterU2_t i;
	CrFwCounterU2_t errRepPosLocal;
	CrFwPcktLength_t len;

	/* Retrieve the first OutStream */
	outStream0 = CrFwOutStreamMake(0);
	if (outStream0 == NULL)
		return 0;

	/* Check configuration of OutStream */
	if (FwSmCheckRec(outStream0) != smSuccess)
		return 0;

	/* Start, initialize and reset outStream and check its state */
	FwSmStart(outStream0);
	if (!CrFwCmpIsInCreated(outStream0))
		return 0;
	CrFwCmpInit(outStream0);
	if (!CrFwCmpIsInInitialized(outStream0))
		return 0;
	CrFwCmpReset(outStream0);
	if (!CrFwCmpIsInConfigured(outStream0))
		return 0;
	if (!CrFwOutStreamIsInReady(outStream0))
		return 0;
	if (CrFwOutStreamGetSeqCnt(0) != 1)
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 0)
		return 0;

	/* Configure the Packet Hand-Over Operation to return "hand-over successful" */
	CrFwOutStreamStubSetHandoverFlag(1);

	/* Make a dummy packet and configure it to belong to the first group and
	 * with the source equal to the host application */
	pckt1 = CrFwPcktMake(CrFwPcktGetMaxLength());
	len = CrFwPcktGetLength(pckt1);
	CrFwPcktSetSrc(pckt1,CR_FW_HOST_APP_ID);
	CrFwPcktSetGroup(pckt1,0);

	/* Send the packet to the OutStream and check outcome */
	CrFwOutStreamSend(outStream0, pckt1);
	if (!CrFwOutStreamIsInReady(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 0)
		return 0;
	if (CrFwOutStreamGetSeqCnt(0) != 2)
		return 0;
	if (CrFwPcktGetSeqCnt(pckt1) != 1)
		return 0;
	if (CrFwOutStreamGetNOfHandedOverBytes(outStream0) != len) 
		return 0;
	if (CrFwOutStreamGetNOfHandedOverPckts(outStream0) != 1)
		return 0;		
	CrFwPcktRelease(pckt1);

	/* Configure the Packet Hand-Over Operation to return "hand-over failed" */
	CrFwOutStreamStubSetHandoverFlag(0);

	/* Make, configure and send two more packets to the OutStream and check outcome */
	pckt2 = CrFwPcktMake(CrFwPcktGetMaxLength());
	CrFwPcktSetSrc(pckt2,CR_FW_HOST_APP_ID);
	CrFwPcktSetGroup(pckt2,0);
	pckt3 = CrFwPcktMake(CrFwPcktGetMaxLength());
	CrFwPcktSetSrc(pckt3,CR_FW_HOST_APP_ID);
	CrFwPcktSetGroup(pckt3,0);

	CrFwOutStreamSend(outStream0, pckt2);
	if (!CrFwOutStreamIsInBuffering(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 1)
		return 0;
	if (CrFwOutStreamGetSeqCnt(0) != 2)
		return 0;
	CrFwOutStreamSend(outStream0, pckt3);
	if (!CrFwOutStreamIsInBuffering(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 2)
		return 0;
	if (CrFwOutStreamGetSeqCnt(0) != 2)
		return 0;
	if (CrFwOutStreamGetNOfHandedOverBytes(outStream0) != len) 
		return 0;
	if (CrFwOutStreamGetNOfHandedOverPckts(outStream0) != 1)
		return 0;	
	len += CrFwPcktGetLength(pckt2);	
	len += CrFwPcktGetLength(pckt3);	
	CrFwPcktRelease(pckt2);
	CrFwPcktRelease(pckt3);

	/* Empty the packet factory and then attempt to send one more packet to the OutStream
	 * and verify that this results in error crOutStreamNoMorePckt */
	for (i=0; i<CR_FW_MAX_NOF_PCKTS; i++)
		pcktArray[i] = CrFwPcktMake(CrFwPcktGetMaxLength());

	errRepPosLocal = CrFwRepErrStubGetPos(); /* Store the current value of the error report counter */
	CrFwOutStreamSend(outStream0, pcktArray[0]);
	if (CrFwRepErrStubGetPos() != errRepPosLocal+1)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crOutStreamNoMorePckt)
		return 0;
	if (CrFwRepErrStubGetTypeId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != CR_FW_OUTSTREAM_TYPE)
		return 0;

	CrFwSetAppErrCode(crNoAppErr);	/* Reset application error code */

	for (i=0; i<CR_FW_MAX_NOF_PCKTS; i++)
		if (pcktArray[i] != NULL)
			CrFwPcktRelease(pcktArray[i]);

	/* Configure the Packet Hand-Over Operation to return "hand-over successful" */
	CrFwOutStreamStubSetHandoverFlag(1);

	/* Send the Connection Available signal to the OutStream and check that PQ is flushed */
	CrFwOutStreamConnectionAvail(outStream0);
	if (!CrFwOutStreamIsInReady(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 0)
		return 0;
	if (CrFwOutStreamGetSeqCnt(0) != 4)
		return 0;
	if (CrFwOutStreamGetNOfHandedOverBytes(outStream0) != len) 
		return 0;
	if (CrFwOutStreamGetNOfHandedOverPckts(outStream0) != 3)
		return 0;		

	/* Configure the Packet Hand-Over Operation to return "hand-over failed" */
	CrFwOutStreamStubSetHandoverFlag(0);

	/* Fill up packet queue */
	for (i=0; i<CrFwOutStreamGetPcktQueueSize(outStream0); i++) {
		pckt = CrFwPcktMake(CrFwPcktGetMaxLength());
		CrFwPcktSetGroup(pckt,0);
		CrFwOutStreamSend(outStream0, pckt);
		CrFwPcktRelease(pckt);
	}
	if (!CrFwOutStreamIsInBuffering(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != CrFwOutStreamGetPcktQueueSize(outStream0))
		return 0;

	/* Send the Connection Available signal to the OutStream and check that PQ is not flushed */
	CrFwOutStreamConnectionAvail(outStream0);
	if (!CrFwOutStreamIsInBuffering(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != CrFwOutStreamGetPcktQueueSize(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfHandedOverBytes(outStream0) != len) 
		return 0;
	if (CrFwOutStreamGetNOfHandedOverPckts(outStream0) != 3)
		return 0;		

	/* Configure the Packet Hand-Over Operation to return "hand-over successful" */
	CrFwOutStreamStubSetHandoverFlag(1);

	/* Send the Connection Available signal to the OutStream and check that PQ is flushed */
	CrFwOutStreamConnectionAvail(outStream0);
	if (!CrFwOutStreamIsInReady(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 0)
		return 0;
	if (CrFwOutStreamGetNOfHandedOverBytes(outStream0) != 
			(CrFwCounterU3_t)(len+CrFwOutStreamGetPcktQueueSize(outStream0)*CrFwPcktGetMaxLength())) 
		return 0;
	if (CrFwOutStreamGetNOfHandedOverPckts(outStream0) != 
			(CrFwCounterU3_t)(3+CrFwOutStreamGetPcktQueueSize(outStream0)))
		return 0;		

	/* Configure the middleware to be not ready to receive packets,
	 * empty the packet factory and then attempt to send one more packet to the OutStream
	 * and verify that this results in error crOutStreamNoMorePckt */
	CrFwOutStreamStubSetHandoverFlag(0);

	for (i=0; i<CR_FW_MAX_NOF_PCKTS; i++)
		pcktArray[i] = CrFwPcktMake(CrFwPcktGetMaxLength());

	errRepPosLocal = CrFwRepErrStubGetPos(); /* Store the current value of the error report counter */
	CrFwOutStreamSend(outStream0, pcktArray[0]);
	if (CrFwRepErrStubGetPos() != errRepPosLocal+1)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crOutStreamNoMorePckt)
		return 0;
	if (CrFwRepErrStubGetTypeId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != CR_FW_OUTSTREAM_TYPE)
		return 0;
	if (!CrFwOutStreamIsInReady(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 0)
		return 0;

	CrFwSetAppErrCode(crNoAppErr);	/* Reset application error code */

	for (i=0; i<CR_FW_MAX_NOF_PCKTS; i++)
		if (pcktArray[i] != NULL)
			CrFwPcktRelease(pcktArray[i]);

	/* Reset the OutStream and check new state */
	CrFwCmpReset(outStream0);
	if (!CrFwOutStreamIsInReady(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 0)
		return 0;
	if (CrFwOutStreamGetNOfHandedOverBytes(outStream0) != 0) 
		return 0;
	if (CrFwOutStreamGetNOfHandedOverPckts(outStream0) != 0)
		return 0;		

	/* Check that all packets have been de-allocated */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	/* Shutdown the OutStream (the packets are released when they are flushed) */
	CrFwCmpShutdown(outStream0);
	/* FwSmStop(outStream0); */

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutStreamTestCase4() {
	FwSmDesc_t outStream[CR_FW_NOF_OUTSTREAM];
	CrFwDestSrc_t dest[CR_FW_OUTSTREAM_NOF_DEST];
	CrFwInstanceId_t i;

	/* Initialize the destinations (the initialization values must be the same as
	   specified in <code>CrFwOutStreamUserPar.h</code>). */
	for (i=0; i<CR_FW_OUTSTREAM_NOF_DEST; i++)
		dest[i] = (CrFwDestSrc_t)(i+1);

	/* Make the OutStreams and associate them to their destinations */
	for (i=0; i<CR_FW_NOF_OUTSTREAM; i++)
		outStream[i] = CrFwOutStreamMake(i);

	/* Retrieve the OutStream from their destinations (association between destination
	   and OutStream is in CR_FW_OUTSTREAM_DEST_PAIRS)*/
	if (CrFwOutStreamGet(dest[0]) != outStream[0])
		return 0;
	if (CrFwOutStreamGet(dest[1]) != outStream[0])
		return 0;
	if (CrFwOutStreamGet(dest[2]) != outStream[2])
		return 0;
	if (CrFwOutStreamGet(dest[7]) != outStream[1])
		return 0;
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	/* Check response to non-existent destination */
	if (CrFwOutStreamGet(255) != NULL)
		return 0;
	if (CrFwGetAppErrCode() != crOutStreamUndefDest)
		return 0;
	CrFwSetAppErrCode(crNoAppErr); 	/* reset application error code */

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutStreamTestCase5() {
	FwSmDesc_t outStream1;
	CrFwCounterU1_t nShutdown;

	/* Create the first InStream */
	outStream1 = CrFwOutStreamMake(1);
	if (outStream1 == NULL)
		return 0;

	/* Retrieve the shutdown counter for the OutStream Stub */
	nShutdown = CrFwOutStreamStubGetShutdownCnt();

	/* Bring OutStream to state CONFIGURED */
	if (CrFwCmpIsStarted(outStream1) == 0)
		FwSmStart(outStream1);
	CrFwCmpInit(outStream1);
	CrFwCmpReset(outStream1);
	if (!CrFwCmpIsInConfigured(outStream1))
		return 0;

	/* Shutdown the newly-created InStream */
	CrFwCmpShutdown(outStream1);
	if (CrFwOutStreamStubGetShutdownCnt() != nShutdown+1)
		return 0;

	if (CrFwCmpIsStarted(outStream1) != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutStreamTestCase6() {
	FwSmDesc_t outStream0;
	CrFwPckt_t pckt1, pckt2, pckt3, pckt;
	CrFwCounterU2_t i;

	/* Retrieve the first OutStream */
	outStream0 = CrFwOutStreamMake(0);
	if (outStream0 == NULL)
		return 0;

	/* Check configuration of OutStream */
	if (FwSmCheckRec(outStream0) != smSuccess)
		return 0;

	/* Start, initialize and reset outStream and check its state */
	FwSmStart(outStream0);
	CrFwCmpInit(outStream0);
	CrFwCmpReset(outStream0);
	if (!CrFwCmpIsInConfigured(outStream0))
		return 0;
	if (!CrFwOutStreamIsInReady(outStream0))
		return 0;

	if (CrFwOutStreamGetSeqCnt(0) != 1)
		return 0;

	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 0)
		return 0;

	/* Configure the Packet Hand-Over Operation to return "hand-over successful" */
	CrFwOutStreamStubSetHandoverFlag(1);

	/* Make a dummy packet and configure it with the source equal to an external application */
	pckt1 = CrFwPcktMake(CrFwPcktGetMaxLength());
	CrFwPcktSetSrc(pckt1,(CR_FW_HOST_APP_ID+1));

	/* Set the sequence counter of the packet */
	CrFwPcktSetSeqCnt(pckt1,100);

	/* Send the packet to the OutStream and check outcome */
	CrFwOutStreamSend(outStream0, pckt1);
	if (!CrFwOutStreamIsInReady(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 0)
		return 0;
	if (CrFwOutStreamGetSeqCnt(0) != 1)
		return 0;
	if (CrFwPcktGetSeqCnt(pckt1) != 100)
		return 0;
	CrFwPcktRelease(pckt1);

	/* Configure the Packet Hand-Over Operation to return "hand-over failed" */
	CrFwOutStreamStubSetHandoverFlag(0);

	/* Make, configure and send two more packets to the OutStream and check outcome */
	pckt2 = CrFwPcktMake(CrFwPcktGetMaxLength());
	CrFwPcktSetSrc(pckt2,(CR_FW_HOST_APP_ID+1));
	CrFwPcktSetSeqCnt(pckt2,101);
	pckt3 = CrFwPcktMake(CrFwPcktGetMaxLength());
	CrFwPcktSetSrc(pckt3,(CR_FW_HOST_APP_ID+1));
	CrFwPcktSetSeqCnt(pckt3,102);

	CrFwOutStreamSend(outStream0, pckt2);
	if (!CrFwOutStreamIsInBuffering(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 1)
		return 0;
	if (CrFwOutStreamGetSeqCnt(0) != 1)
		return 0;
	CrFwOutStreamSend(outStream0, pckt3);
	if (!CrFwOutStreamIsInBuffering(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 2)
		return 0;
	if (CrFwOutStreamGetSeqCnt(0) != 1)
		return 0;
	CrFwPcktRelease(pckt2);
	CrFwPcktRelease(pckt3);

	/* Configure the Packet Hand-Over Operation to return "hand-over successful" */
	CrFwOutStreamStubSetHandoverFlag(1);

	/* Send the Connection Available signal to the OutStream and check that PQ is flushed */
	CrFwOutStreamConnectionAvail(outStream0);
	if (!CrFwOutStreamIsInReady(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 0)
		return 0;
	if (CrFwOutStreamGetSeqCnt(0) != 1)
		return 0;
	if (CrFwPcktGetSeqCnt(pckt2) != 101)
		return 0;
	if (CrFwPcktGetSeqCnt(pckt3) != 102)
		return 0;

	/* Configure the Packet Hand-Over Operation to return "hand-over failed" */
	CrFwOutStreamStubSetHandoverFlag(0);

	/* Fill up packet queue */
	for (i=0; i<CrFwOutStreamGetPcktQueueSize(outStream0); i++) {
		pckt = CrFwPcktMake(CrFwPcktGetMaxLength());
		CrFwPcktSetSrc(pckt2,(CR_FW_HOST_APP_ID+1));
		CrFwPcktSetSeqCnt(pckt,111);
		CrFwOutStreamSend(outStream0, pckt);
		CrFwPcktRelease(pckt);
	}
	if (!CrFwOutStreamIsInBuffering(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != CrFwOutStreamGetPcktQueueSize(outStream0))
		return 0;

	/* Configure the Packet Hand-Over Operation to return "hand-over successful" */
	CrFwOutStreamStubSetHandoverFlag(1);

	/* Send the Connection Available signal to the OutStream and check that PQ is flushed */
	CrFwOutStreamConnectionAvail(outStream0);
	if (!CrFwOutStreamIsInReady(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 0)
		return 0;

	/* Reset the OutStream and check new state */
	CrFwCmpReset(outStream0);
	if (!CrFwOutStreamIsInReady(outStream0))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream0) != 0)
		return 0;

	/* Check that all packets have been de-allocated */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	/* Stop the OutStream (the packets are released when they are flushed) */
	FwSmStop(outStream0);

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutStreamTestCase7() {
	FwSmDesc_t outStream1;
	CrFwPckt_t pckt1, pckt2, pckt3;
	CrFwCounterU2_t errRepPosLocal;
	CrFwCounterU1_t handoverSuccCnt;

	/* Retrieve the second OutStream */
	outStream1 = CrFwOutStreamMake(1);
	if (outStream1 == NULL)
		return 0;

	/* Start, initialize and reset outStream and check its state */
	FwSmStart(outStream1);
	CrFwCmpInit(outStream1);
	CrFwCmpReset(outStream1);
	if (!CrFwCmpIsInConfigured(outStream1))
		return 0;
	if (!CrFwOutStreamIsInReady(outStream1))
		return 0;

	/* Retrieve error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Check configuration of OutStream */
	if (FwSmCheckRec(outStream1) != smSuccess)
		return 0;

	/* Check number of groups of OutStreams (this is set in CrFwOutStreamUserPar.h */
	if (CrFwOutStreamGetNOfGroups()!=2)
		return 0;

	/* Check destination associated to outStream (given by CR_FW_OUTSTREAM_DEST_PAIRS)*/
	if (CrFwOutStreamGetNOfDest(outStream1) != 1)
		return 0;
	if (CrFwOutStreamGetDest(outStream1,1) != 8)
		return 0;

	/* Check number of type counters (this is set by function CrFwOutStreamDefSetDTS and
	   is equal to the number of distinct (type,sub-type) pairs in CR_FW_OUTCMP_INIT_KIND_DESC */
	if (CrFwOutStreamGetNOfTypeCounters()!=10)
		return 0;

	/* Start, initialize and reset outStream and check its state */
	FwSmStart(outStream1);
	CrFwCmpInit(outStream1);
	CrFwCmpReset(outStream1);
	if (!CrFwCmpIsInConfigured(outStream1))
		return 0;
	if (!CrFwOutStreamIsInReady(outStream1))
		return 0;
	if (CrFwOutStreamGetSeqCnt(0) != 1)
		return 0;
	if (CrFwOutStreamGetSeqCnt(1) != 1)
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream1) != 0)
		return 0;

	/* Check the initial value of the type counters */
	if (CrFwOutStreamGetTypeCounter(1,1,1) != 1)	/* (1,1) is a type in CR_FW_OUTCMP_INIT_KIND_DESC */
		return 0;
	if (CrFwOutStreamGetTypeCounter(1,5,1) != 1)	/* (5,1) is a type in CR_FW_OUTCMP_INIT_KIND_DESC */
		return 0;
	if (CrFwOutStreamGetTypeCounter(1,50,1) != 1)	/* (50,1) is a type in CR_FW_OUTCMP_INIT_KIND_DESC */
		return 0;
	if (CrFwOutStreamGetTypeCounter(99,5,1) != 0)	/* destination 99 is not in DTS_SET */
		return 0;
	if (CrFwOutStreamGetTypeCounter(1,5,99) != 0)	/* (5,99) is not a type in CR_FW_OUTCMP_INIT_KIND_DESC */
		return 0;
	if (CrFwOutStreamGetTypeCounter(1,99,1) != 0)	/* (5,99) is not a type in CR_FW_OUTCMP_INIT_KIND_DESC */
		return 0;

	/* Check computation of DTS_SET */
	if (CrFwOutStreamIsInDtsSet(1,1,1) != 1)	/* (1,1) is a type in CR_FW_OUTCMP_INIT_KIND_DESC */
		return 0;
	if (CrFwOutStreamIsInDtsSet(1,5,1) != 1)	/* (5,1) is a type in CR_FW_OUTCMP_INIT_KIND_DESC */
		return 0;
	if (CrFwOutStreamIsInDtsSet(1,50,1) != 1)	/* (50,1) is a type in CR_FW_OUTCMP_INIT_KIND_DESC */
		return 0;
	if (CrFwOutStreamIsInDtsSet(99,5,1) != 0)	/* destination 99 is not in DTS_SET */
		return 0;
	if (CrFwOutStreamIsInDtsSet(1,5,99) != 0)	/* (5,99) is not a type in CR_FW_OUTCMP_INIT_KIND_DESC */
		return 0;
	if (CrFwOutStreamIsInDtsSet(1,99,1) != 0)	/* (5,99) is not a type in CR_FW_OUTCMP_INIT_KIND_DESC */
		return 0;

	/* Configure the Packet Hand-Over Operation to return "hand-over successful" */
	CrFwOutStreamStubSetHandoverFlag(1);

	/* Make three dummy packets, configure them to belong to the first, second and third group and
	 * with the source equal to the host application. Also configure the first and second packets
	   to belong to the DTS_SET and the third one to be outside the DTS_SET */
	pckt1 = CrFwPcktMake(CrFwPcktGetMaxLength());
	CrFwPcktSetSrc(pckt1,CR_FW_HOST_APP_ID);
	CrFwPcktSetGroup(pckt1,0);
	CrFwPcktSetSeqCnt(pckt1,99);
	CrFwPcktSetDest(pckt1,1);
	CrFwPcktSetServType(pckt1,5);
	CrFwPcktSetServSubType(pckt1,1);
	CrFwPcktSetTypeCnt(pckt1, 1000);
	pckt2 = CrFwPcktMake(CrFwPcktGetMaxLength());
	CrFwPcktSetSrc(pckt2,CR_FW_HOST_APP_ID);
	CrFwPcktSetGroup(pckt2,1);
	CrFwPcktSetSeqCnt(pckt2,99);
	CrFwPcktSetDest(pckt2,1);
	CrFwPcktSetServType(pckt2,5);
	CrFwPcktSetServSubType(pckt2,99);	/* non-existent sub-type */
	CrFwPcktSetTypeCnt(pckt2, 2000);
	pckt3 = CrFwPcktMake(CrFwPcktGetMaxLength());
	CrFwPcktSetSrc(pckt3,CR_FW_HOST_APP_ID);
	CrFwPcktSetGroup(pckt3,88);	/* non-existent group */
	CrFwPcktSetSeqCnt(pckt3,99);
	CrFwPcktSetDest(pckt3,1);
	CrFwPcktSetServType(pckt3,5);
	CrFwPcktSetServSubType(pckt3,1);	
	CrFwPcktSetTypeCnt(pckt3, 3000);

	/* Send the packets to the OutStream and check outcome */
	CrFwOutStreamSetSeqCnt(1, 2222);
	CrFwOutStreamSend(outStream1, pckt1);
	CrFwOutStreamSend(outStream1, pckt2);
	CrFwOutStreamSend(outStream1, pckt3);
	if (!CrFwOutStreamIsInReady(outStream1))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream1) != 0)
		return 0;
	if (CrFwOutStreamGetSeqCnt(0) != 2)
		return 0;
	if (CrFwOutStreamGetSeqCnt(1) != 2223)
		return 0;
	if (CrFwPcktGetSeqCnt(pckt1) != 1)
		return 0;
	if (CrFwPcktGetTypeCnt(pckt1) != 1)
		return 0;
	if (CrFwPcktGetSeqCnt(pckt2) != 2222)
		return 0;
	if (CrFwPcktGetTypeCnt(pckt2) != 0)
		return 0;
	if (CrFwPcktGetSeqCnt(pckt3) != 0)
		return 0;
	if (CrFwPcktGetTypeCnt(pckt3) != 2)
		return 0;
	if (CrFwRepErrStubGetPos() != errRepPosLocal+1)
		return 0;
	if (CrFwRepErrStubGetErrCode(errRepPosLocal) != crOutStreamIllGroup)
		return 0;
	CrFwPcktRelease(pckt1);
	CrFwPcktRelease(pckt2);
	CrFwPcktRelease(pckt3);

	/* Configure the Packet Hand-Over Operation to return "hand-over failed" */
	CrFwOutStreamStubSetHandoverFlag(0);

	/* Store the current value of the OutStream packet handover counter */
	handoverSuccCnt = CrFwOutStreamStubGetHandoverSuccCnt();

	/* Make, configure and send three more packets to the OutStream and check outcome */
	pckt1 = CrFwPcktMake(CrFwPcktGetMaxLength());
	CrFwPcktSetSrc(pckt1,CR_FW_HOST_APP_ID);
	CrFwPcktSetGroup(pckt1,0);
	CrFwPcktSetSeqCnt(pckt1,99);
	CrFwPcktSetDest(pckt1,1);
	CrFwPcktSetServType(pckt1,5);
	CrFwPcktSetServSubType(pckt1,1);
	CrFwPcktSetTypeCnt(pckt1, 1000);
	pckt2 = CrFwPcktMake(CrFwPcktGetMaxLength());
	CrFwPcktSetSrc(pckt2,CR_FW_HOST_APP_ID);
	CrFwPcktSetGroup(pckt2,1);
	CrFwPcktSetSeqCnt(pckt2,99);
	CrFwPcktSetDest(pckt2,1);
	CrFwPcktSetServType(pckt2,5);
	CrFwPcktSetServSubType(pckt2,99);	/* non-existent sub-type */
	CrFwPcktSetTypeCnt(pckt2, 2000);
	pckt3 = CrFwPcktMake(CrFwPcktGetMaxLength());
	CrFwPcktSetSrc(pckt3,CR_FW_HOST_APP_ID);
	CrFwPcktSetGroup(pckt3,88);	/* non-existent group */
	CrFwPcktSetSeqCnt(pckt3,99);
	CrFwPcktSetDest(pckt3,1);
	CrFwPcktSetServType(pckt3,5);
	CrFwPcktSetServSubType(pckt3,1);	
	CrFwPcktSetTypeCnt(pckt3, 3000);

	CrFwOutStreamSend(outStream1, pckt1);
	CrFwOutStreamSend(outStream1, pckt2);
	CrFwOutStreamSend(outStream1, pckt3);
	if (!CrFwOutStreamIsInBuffering(outStream1))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream1) != 3)
		return 0;
	if (CrFwOutStreamGetSeqCnt(0) != 2)
		return 0;
	if (CrFwOutStreamGetSeqCnt(1) != 2223)
		return 0;
	if (CrFwRepErrStubGetPos() != errRepPosLocal+1)
		return 0;
	if (CrFwOutStreamStubGetHandoverSuccCnt() != handoverSuccCnt)
		return 0;
	CrFwPcktRelease(pckt1);
	CrFwPcktRelease(pckt2);
	CrFwPcktRelease(pckt3);

	/* Configure the Packet Hand-Over Operation to return "hand-over successful" */
	CrFwOutStreamStubSetHandoverFlag(1);

	/* Send the Connection Available signal to the OutStream and check that PQ is flushed */
	CrFwOutStreamConnectionAvail(outStream1);
	if (!CrFwOutStreamIsInReady(outStream1))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream1) != 0)
		return 0;
	if (CrFwOutStreamGetSeqCnt(0) != 3)
		return 0;
	if (CrFwOutStreamGetSeqCnt(1) != 2224)
		return 0;
	if (CrFwOutStreamGetTypeCounter(1,5,1) != 5)
		return 0;
	if (CrFwRepErrStubGetPos() != errRepPosLocal+2)
		return 0;
	if (CrFwRepErrStubGetErrCode(errRepPosLocal) != crOutStreamIllGroup)
		return 0;
	if (CrFwOutStreamStubGetHandoverSuccCnt() != handoverSuccCnt+3)
		return 0;
	if (CrFwOutStreamStubGetTypeCnt(handoverSuccCnt+1) != 3)
		return 0;
	if (CrFwOutStreamStubGetTypeCnt(handoverSuccCnt+2) != 0)
		return 0;
	if (CrFwOutStreamStubGetTypeCnt(handoverSuccCnt+3) != 4)
		return 0;

	/* Reset the OutStream and check new state */
	CrFwCmpReset(outStream1);
	if (!CrFwOutStreamIsInReady(outStream1))
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream1) != 0)
		return 0;

	/* Check that all packets have been de-allocated */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	/* Stop the OutStream (the packets are released when they are flushed) */
	FwSmStop(outStream1);

	return 1;
}

