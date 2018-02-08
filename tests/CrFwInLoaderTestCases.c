/**
 * @file
 *
 * Implementation of test cases for InLoader component.
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

#include <stdio.h>
#include <stdlib.h>
#include "CrFwInLoaderTestCases.h"
#include "CrFwInCmdSample1.h"
#include "CrFwInRepSample1.h"
#include "CrFwRepInCmdOutcomeStub.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include framework files */
#include "InRegistry/CrFwInRegistry.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "InRep/CrFwInRep.h"
#include "InCmd/CrFwInCmd.h"
#include "InStream/CrFwInStream.h"
#include "OutStream/CrFwOutStream.h"
#include "InFactory/CrFwInFactory.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include configuration files */
#include "CrFwInRegistryUserPar.h"
#include "CrFwInLoaderUserPar.h"
#include "CrFwInStreamStub.h"
#include "CrFwOutStreamStub.h"
#include "CrFwRepErrStub.h"
#include "CrFwInFactoryUserPar.h"
#include "CrFwOutFactoryUserPar.h"
#include "CrFwCmpData.h"
#include "CrFwRepInCmdOutcome.h"

/** Return value of function <code>CrFwInLoaderDefGetReroutingDestination</code>. */
static CrFwDestSrc_t reroutingDest = 0;

/* ---------------------------------------------------------------------------------------------*/
/**
 * Function to set the return value of function <code>::CrFwInLoaderTestCaseGetReroutingDestination</code>.
 * @param retValue the return value of function <code>::CrFwInLoaderTestCaseGetReroutingDestination</code>.
 */
static void CrFwInLoaderTestCaseSetReroutingDest(CrFwDestSrc_t retValue) {
	reroutingDest = retValue;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwDestSrc_t CrFwInLoaderTestCaseGetReroutingDestination(CrFwDestSrc_t pcktDest) {
	(void)(pcktDest);
	return reroutingDest;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInLoaderTestCase1() {
	FwSmDesc_t inLoader;

	/* Instantiate the InLoader */
	inLoader = CrFwInLoaderMake();

	/* Check current state of InLoader */
	if (!CrFwCmpIsInCreated(inLoader))
		return 0;

	/* Initialize and Configure InLoader and check success */
	CrFwCmpInit(inLoader);
	if (!CrFwCmpIsInInitialized(inLoader))
		return 0;
	CrFwCmpReset(inLoader);
	if (!CrFwCmpIsInConfigured(inLoader))
		return 0;

	/* Check Instance and Type Identifiers */
	if (CrFwCmpGetInstanceId(inLoader) != 0)
		return 0;
	if (CrFwCmpGetTypeId(inLoader) != CR_FW_INLOADER_TYPE)
		return 0;

	/* Check default implementation of function which re-routes a destination */
	if (CrFwInLoaderDefGetReroutingDestination(0) != 0)
		return 0;
	if (CrFwInLoaderDefGetReroutingDestination(1) != 1)
		return 0;
	if (CrFwInLoaderDefGetReroutingDestination(2) != 2)
		return 0;

	/* Check default implementation of function which re-routes a destination */
	if (CrFwInLoaderDefNoRerouting(1) != 0)
		return 0;
	if (CrFwInLoaderDefNoRerouting(0) != 0)
		return 0;
	if (CrFwInLoaderDefNoRerouting(2) != 0)
		return 0;

	/* Check default implementation of function which selects the InManager */
	if (CrFwInLoaderDefGetInManager(0,0,0,crCmdType) != 0)
		return 0;
	if (CrFwInLoaderDefGetInManager(0,0,0,crRepType) != 1)
		return 0;

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInLoaderTestCase2() {
	FwSmDesc_t inLoader, inStream;
	CrFwCounterU2_t errRepPosLocal;

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Instantiate, initialize and configure the InLoader */
	inLoader = CrFwInLoaderMake();
	CrFwCmpInit(inLoader);
	CrFwCmpReset(inLoader);
	if (!CrFwCmpIsInConfigured(inLoader))
		return 0;

	/* Create InStream and configure it to have no pending packet */
	inStream = CrFwInStreamMake(0);
	CrFwInStreamStubSetPcktCollectionCnt(0);
	CrFwCmpInit(inStream);
	CrFwCmpReset(inStream);
	if (!CrFwCmpIsInConfigured(inStream))
		return 0;

	/* Configure InLoader to return "destination invalid" */
	CrFwInLoaderTestCaseSetReroutingDest(0);

	/* Load InStream in the InLoader and execute InLoader*/
	CrFwInLoaderSetInStream(inStream);
	CrFwCmpExecute(inLoader);

	/* Check that no error report has been generated */
	if (CrFwRepErrStubGetPos() != errRepPosLocal)
		return 0;

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInLoaderTestCase3() {
	FwSmDesc_t inLoader, inStream;
	CrFwCounterU2_t errRepPosLocal;

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Instantiate, initialize and configure the InLoader */
	inLoader = CrFwInLoaderMake();
	CrFwCmpInit(inLoader);
	CrFwCmpReset(inLoader);
	if (!CrFwCmpIsInConfigured(inLoader))
		return 0;

	/* Create InStream and configure it to have one pending packet for another application */
	inStream = CrFwInStreamMake(0);
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID+1);	/* Packet destination is not the host application */
	CrFwInStreamStubSetPcktCollectionCnt(1);	/* One pending packet in InStream */
	CrFwInStreamStubSetPcktCmdRepId(111);		 /* Define command/report identifier */
	CrFwCmpInit(inStream);
	CrFwCmpReset(inStream);
	if (!CrFwCmpIsInConfigured(inStream))
		return 0;

	/* Configure InLoader to return "destination invalid" */
	CrFwInLoaderTestCaseSetReroutingDest(0);

	/* Load InStream in the InLoader and execute InLoader*/
	CrFwInLoaderSetInStream(inStream);
	CrFwCmpExecute(inLoader);

	/* Check that an error report has been generated */
	if (CrFwRepErrStubGetPos() != errRepPosLocal + 1)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crInLoaderInvDest)
		return 0;
	if (CrFwRepErrStubGetTypeId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != CR_FW_INLOADER_TYPE)
		return 0;
	if (CrFwRepErrStubGetInstanceId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != 0)
		return 0;
	if (CrFwRepErrStubGetSecondatyInstanceId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != 111)
		return 0;
	if (CrFwRepErrStubGetDest((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != CR_FW_HOST_APP_ID+1)
		return 0;

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInLoaderTestCase4() {
	FwSmDesc_t inLoader, inStream, outStream;
	CrFwCounterU2_t errRepPosLocal;
	CrFwCounterU1_t handoverCnt;

	/* Store the current value of the OutStream packet handover counter */
	handoverCnt = CrFwOutStreamStubGetHandoverCnt();

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Instantiate, initialize and configure the InLoader */
	inLoader = CrFwInLoaderMake();
	CrFwCmpInit(inLoader);
	CrFwCmpReset(inLoader);
	if (!CrFwCmpIsInConfigured(inLoader))
		return 0;

	/* Create InStream and configure it to be in state AVAIL with one pending packet */
	inStream = CrFwInStreamMake(0);
	CrFwInStreamStubSetPcktCollectionCnt(1);
	CrFwCmpInit(inStream);
	CrFwCmpReset(inStream);
	if (!CrFwCmpIsInConfigured(inStream))
		return 0;
	if (!CrFwInStreamIsInPcktAvail(inStream))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream) != 1)
		return 0;

	/* Create OutStream */
	outStream = CrFwOutStreamMake(0);
	FwSmStart(outStream);
	CrFwCmpInit(outStream);
	CrFwCmpReset(outStream);
	if (!CrFwCmpIsInConfigured(outStream))
		return 0;
	CrFwOutStreamStubSetHandoverFlag(1); /* Configure Packet Hand-Over Operation to return "hand-over successful" */
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)	/* Check that there are no pending packets */
		return 0;

	/* Configure InLoader to return destination associated to OutStream */
	CrFwInLoaderTestCaseSetReroutingDest(CrFwOutStreamGetDest(outStream));

	/* Load InStream in the InLoader and execute InLoader*/
	CrFwInLoaderSetInStream(inStream);
	CrFwCmpExecute(inLoader);

	/* Check that a packet was loaded into the OutStream and was passed on to the middleware */
	if (CrFwOutStreamStubGetHandoverCnt() != handoverCnt + 1)
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)
		return 0;

	/* Check that no error report has been generated */
	if (CrFwRepErrStubGetPos() != errRepPosLocal)
		return 0;

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInLoaderTestCase5() {
	FwSmDesc_t inLoader, inStream, outStream, inFactory;
	CrFwCounterU2_t errRepPosLocal;
	CrFwCounterU1_t handoverCnt;
	CrFwCounterU2_t cmdRepPos;

	/* Store the current value of the command report counter */
	cmdRepPos = CrFwRepInCmdOutcomeStubGetPos();

	/* Store the current value of the OutStream packet handover counter */
	handoverCnt = CrFwOutStreamStubGetHandoverCnt();

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Instantiate, initialize and configure the InLoader */
	inLoader = CrFwInLoaderMake();
	CrFwCmpInit(inLoader);
	CrFwCmpReset(inLoader);
	if (!CrFwCmpIsInConfigured(inLoader))
		return 0;

	/* Create InStream and configure it to be in state AVAIL with one pending packet */
	inStream = CrFwInStreamMake(0);
	CrFwInStreamStubSetPcktCollectionCnt(1); /* One pending packet in InStream */
	CrFwInStreamStubSetPcktType(0,0,0);		 /* Set packet type to invalid */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);		 /* Set packet destination to current destination */
	CrFwInStreamStubSetPcktCmdRepType(crRepType);		 /* Define packet as InReport */
	CrFwInStreamStubSetPcktCmdRepId(111);		 /* Define command/report identifier */
	CrFwCmpInit(inStream);
	CrFwCmpReset(inStream);
	if (!CrFwCmpIsInConfigured(inStream))
		return 0;
	if (!CrFwInStreamIsInPcktAvail(inStream))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream) != 1)
		return 0;

	/* Create OutStream */
	outStream = CrFwOutStreamMake(0);
	FwSmStart(outStream);
	CrFwCmpInit(outStream);
	CrFwCmpReset(outStream);
	if (!CrFwCmpIsInConfigured(outStream))
		return 0;
	CrFwOutStreamStubSetHandoverFlag(1); /* Configure Packet Hand-Over Operation to return "hand-over successful" */
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)	/* Check that there are no pending packets */
		return 0;

	/* Create InFactory */
	inFactory = CrFwInFactoryMake();
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Load InStream in the InLoader and execute InLoader*/
	CrFwInLoaderSetInStream(inStream);
	CrFwCmpExecute(inLoader);

	/* Check that no packet was loaded into the OutStream */
	if (CrFwOutStreamStubGetHandoverCnt() != handoverCnt)
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)
		return 0;

	/* Check application error */
	if (CrFwGetAppErrCode() != crIllInRepKind)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);

	/* Check that error report has been generated */
	if (CrFwRepErrStubGetPos() != errRepPosLocal+1)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crInLoaderCreFail)
		return 0;
	if (CrFwRepErrStubGetTypeId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != CR_FW_INLOADER_TYPE)
		return 0;
	if (CrFwRepErrStubGetInstanceId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != 0)
		return 0;

	/* Load the InStream with a packet representing an InCommand */
	CrFwInStreamStubSetPcktCollectionCnt(1); /* One pending packet in InStream */
	CrFwInStreamStubSetPcktType(0,1,2);		 /* Set packet type to invalid */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);		 /* Set packet destination to current destination */
	CrFwInStreamStubSetPcktCmdRepType(crCmdType);		 /* Define packet as InReport */
	CrFwInStreamStubSetPcktCmdRepId(111);		 /* Define command/report identifier */
	CrFwCmpReset(inStream);

	/* Execute InLoader*/
	CrFwCmpExecute(inLoader);

	/* Check that no packet was loaded into the OutStream */
	if (CrFwOutStreamStubGetHandoverCnt() != handoverCnt)
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)
		return 0;

	/* Check application error */
	if (CrFwGetAppErrCode() != crIllInCmdKind)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);

	/* Check that acceptance failure report has been generated */
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetOutcome(cmdRepPos) != crCmdAckCreFail)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetFailCode(cmdRepPos) != 0)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetServType(cmdRepPos) != 0)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetServSubType(cmdRepPos) != 1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetDiscriminant(cmdRepPos) != 2)
		return 0;

	/* Check that no error reports were generated */
	if (CrFwRepErrStubGetPos() != errRepPosLocal+1)
		return 0;

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInLoaderTestCase6() {
	FwSmDesc_t inLoader, inStream, outStream, inFactory;
	CrFwCounterU2_t errRepPosLocal;
	CrFwCounterU1_t handoverCnt;
	CrFwCounterU2_t cmdRepPos;
	CrFwCounterU2_t i;
	CrFwPckt_t inRepPckt, inCmdPckt;
	FwSmDesc_t inRepArray[CR_FW_INFACTORY_MAX_NOF_INREP];
	FwSmDesc_t inCmdArray[CR_FW_INFACTORY_MAX_NOF_INCMD];

	/* Store the current value of the command report counter */
	cmdRepPos = CrFwRepInCmdOutcomeStubGetPos();

	/* Store the current value of the OutStream packet handover counter */
	handoverCnt = CrFwOutStreamStubGetHandoverCnt();

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Instantiate, initialize and configure the InLoader */
	inLoader = CrFwInLoaderMake();
	CrFwCmpInit(inLoader);
	CrFwCmpReset(inLoader);
	if (!CrFwCmpIsInConfigured(inLoader))
		return 0;

	/* Create InStream and configure it to be in state AVAIL with one pending packet */
	inStream = CrFwInStreamMake(0);
	CrFwInStreamStubSetPcktCollectionCnt(1); /* One pending packet in InStream */
	CrFwInStreamStubSetPcktType(5,1,1);		 /* Set packet type to a valid value */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);		 /* Set packet destination to current destination */
	CrFwInStreamStubSetPcktCmdRepType(crRepType);		 /* Define packet as InReport */
	CrFwInStreamStubSetPcktCmdRepId(111);		 /* Define command/report identifier */
	CrFwCmpInit(inStream);
	CrFwCmpReset(inStream);
	if (!CrFwCmpIsInConfigured(inStream))
		return 0;
	if (!CrFwInStreamIsInPcktAvail(inStream))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream) != 1)
		return 0;

	/* Create OutStream */
	outStream = CrFwOutStreamMake(0);
	FwSmStart(outStream);
	CrFwCmpInit(outStream);
	CrFwCmpReset(outStream);
	if (!CrFwCmpIsInConfigured(outStream))
		return 0;
	CrFwOutStreamStubSetHandoverFlag(1); /* Configure Packet Hand-Over Operation to return "hand-over successful" */
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)	/* Check that there are no pending packets */
		return 0;

	/* Create InFactory */
	inFactory = CrFwInFactoryMake();
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Configure InFactory to have no spare InReports */
	for (i=0; i<CR_FW_INFACTORY_MAX_NOF_INREP; i++) {
		inRepPckt = CrFwPcktMake(100);
		CrFwPcktSetServType(inRepPckt,5);
		CrFwPcktSetServSubType(inRepPckt,1);
		CrFwPcktSetDiscriminant(inRepPckt,1);
		inRepArray[i] = CrFwInFactoryMakeInRep(inRepPckt);
		if (inRepArray[i]==NULL)
			return 0;
	}

	/* Load InStream in the InLoader and execute InLoader*/
	CrFwInLoaderSetInStream(inStream);
	CrFwCmpExecute(inLoader);

	/* Check that no packet was loaded into the OutStream */
	if (CrFwOutStreamStubGetHandoverCnt() != handoverCnt)
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)
		return 0;

	/* Check application error */
	if (CrFwGetAppErrCode() != crInRepAllocationFail)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);

	/* Check that error report has been generated */
	if (CrFwRepErrStubGetPos() != errRepPosLocal+1)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crInLoaderCreFail)
		return 0;
	if (CrFwRepErrStubGetTypeId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != CR_FW_INLOADER_TYPE)
		return 0;
	if (CrFwRepErrStubGetInstanceId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != 0)
		return 0;

	/* Release all InReports */
	for (i=0; i<CR_FW_INFACTORY_MAX_NOF_INREP; i++)
		CrFwInFactoryReleaseInRep(inRepArray[i]);

	/* Load the InStream with a packet representing an InCommand */
	CrFwInStreamStubSetPcktCollectionCnt(1); /* One pending packet in InStream */
	CrFwInStreamStubSetPcktType(8,1,1);		 /* Set packet type to invalid */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);		 /* Set packet destination to current destination */
	CrFwInStreamStubSetPcktCmdRepType(crCmdType);		 /* Define packet as InReport */
	CrFwInStreamStubSetPcktCmdRepId(111);		 /* Define command/report identifier */
	CrFwCmpReset(inStream);

	/* Configure InFactory to have no spare InCommands */
	for (i=0; i<CR_FW_INFACTORY_MAX_NOF_INCMD; i++) {
		inCmdPckt = CrFwPcktMake(100);
		CrFwPcktSetServType(inCmdPckt,8);
		CrFwPcktSetServSubType(inCmdPckt,1);
		CrFwPcktSetDiscriminant(inCmdPckt,1);
		inCmdArray[i] = CrFwInFactoryMakeInCmd(inCmdPckt);
		if (inCmdArray[i]==NULL)
			return 0;
	}

	/* Execute InLoader*/
	CrFwCmpExecute(inLoader);

	/* Check that no packet was loaded into the OutStream */
	if (CrFwOutStreamStubGetHandoverCnt() != handoverCnt)
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)
		return 0;

	/* Check application error */
	if (CrFwGetAppErrCode() != crInCmdAllocationFail)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);

	/* Check that acceptance failure report has been generated */
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetOutcome(cmdRepPos) != crCmdAckCreFail)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetFailCode(cmdRepPos) != 0)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetServType(cmdRepPos) != 8)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetServSubType(cmdRepPos) != 1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetDiscriminant(cmdRepPos) != 1)
		return 0;

	/* Check that no error reports were generated */
	if (CrFwRepErrStubGetPos() != errRepPosLocal+1)
		return 0;

	/* Release all InCommands */
	for (i=0; i<CR_FW_INFACTORY_MAX_NOF_INCMD; i++)
		CrFwInFactoryReleaseInCmd(inCmdArray[i]);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInLoaderTestCase7() {
	FwSmDesc_t inLoader, inStream, outStream, inFactory;
	CrFwCounterU2_t errRepPosLocal;
	CrFwCounterU1_t handoverCnt;
	CrFwCounterU2_t cmdRepPos;

	/* Store the current value of the command report counter */
	cmdRepPos = CrFwRepInCmdOutcomeStubGetPos();

	/* Store the current value of the OutStream packet handover counter */
	handoverCnt = CrFwOutStreamStubGetHandoverCnt();

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Instantiate, initialize and configure the InLoader */
	inLoader = CrFwInLoaderMake();
	CrFwCmpInit(inLoader);
	CrFwCmpReset(inLoader);
	if (!CrFwCmpIsInConfigured(inLoader))
		return 0;

	/* Create InStream and configure it to be in state AVAIL with one pending packet */
	inStream = CrFwInStreamMake(0);
	CrFwInStreamStubSetPcktCollectionCnt(1); /* One pending packet in InStream */
	CrFwInStreamStubSetPcktType(40,1,0);		 /* Set packet type to be Sample 1 InReport */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);		 /* Set packet destination to current destination */
	CrFwInStreamStubSetPcktCmdRepType(crRepType);		 /* Define packet as InReport */
	CrFwInStreamStubSetPcktCmdRepId(111);		 /* Define command/report identifier */
	CrFwInRepSample1SetValidityFlag(0);		/* Validity Check of InReport will fail */
	CrFwCmpInit(inStream);
	CrFwCmpReset(inStream);
	if (!CrFwCmpIsInConfigured(inStream))
		return 0;
	if (!CrFwInStreamIsInPcktAvail(inStream))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream) != 1)
		return 0;

	/* Create OutStream */
	outStream = CrFwOutStreamMake(0);
	FwSmStart(outStream);
	CrFwCmpInit(outStream);
	CrFwCmpReset(outStream);
	if (!CrFwCmpIsInConfigured(outStream))
		return 0;
	CrFwOutStreamStubSetHandoverFlag(1); /* Configure Packet Hand-Over Operation to return "hand-over successful" */
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)	/* Check that there are no pending packets */
		return 0;

	/* Create InFactory */
	inFactory = CrFwInFactoryMake();
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Load InStream in the InLoader and execute InLoader*/
	CrFwInLoaderSetInStream(inStream);
	CrFwCmpExecute(inLoader);

	/* Check that no packet was loaded into the OutStream */
	if (CrFwOutStreamStubGetHandoverCnt() != handoverCnt)
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)
		return 0;

	/* Check that error report has been generated */
	if (CrFwRepErrStubGetPos() != errRepPosLocal+1)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crInLoaderAccFail)
		return 0;
	if (CrFwRepErrStubGetTypeId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != CR_FW_INLOADER_TYPE)
		return 0;

	/* Load the InStream with a packet representing an InCommand */
	CrFwInStreamStubSetPcktCollectionCnt(1); /* One pending packet in InStream */
	CrFwInStreamStubSetPcktType(50,1,0);		 /* Set packet type to Sample 1 InCommand */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);		 /* Set packet destination to current destination */
	CrFwInStreamStubSetPcktCmdRepType(crCmdType);		 /* Define packet as InReport */
	CrFwInStreamStubSetPcktCmdRepId(111);		 /* Define command/report identifier */
	CrFwInCmdSample1SetValidityFlag(0);		/* Validity Check of InCommand will fail */
	CrFwCmpReset(inStream);

	/* Execute InLoader*/
	CrFwCmpExecute(inLoader);

	/* Check that no packet was loaded into the OutStream */
	if (CrFwOutStreamStubGetHandoverCnt() != handoverCnt)
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)
		return 0;

	/* Check that acceptance failure report has been generated */
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetOutcome(cmdRepPos) != crCmdAckAccFail)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetFailCode(cmdRepPos) != 0)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetServType(cmdRepPos) != 50)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetServSubType(cmdRepPos) != 1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetDiscriminant(cmdRepPos) != 0)
		return 0;

	/* Check that no error reports were generated */
	if (CrFwRepErrStubGetPos() != errRepPosLocal+1)
		return 0;

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInLoaderTestCase8() {
	FwSmDesc_t inLoader, inStream, outStream, inFactory, inManager;
	CrFwCounterU2_t errRepPosLocal;
	CrFwCounterU1_t handoverCnt;
	CrFwCounterU2_t cmdRepPos;
	CrFwCounterU2_t i;
	CrFwPckt_t pckt;

	/* Store the current value of the command report counter */
	cmdRepPos = CrFwRepInCmdOutcomeStubGetPos();

	/* Store the current value of the OutStream packet handover counter */
	handoverCnt = CrFwOutStreamStubGetHandoverCnt();

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Instantiate, initialize and configure the InLoader */
	inLoader = CrFwInLoaderMake();
	CrFwCmpInit(inLoader);
	CrFwCmpReset(inLoader);
	if (!CrFwCmpIsInConfigured(inLoader))
		return 0;

	/* Create InStream and configure it to be in state AVAIL with one pending packet */
	inStream = CrFwInStreamMake(0);
	CrFwInStreamStubSetPcktCollectionCnt(1); /* One pending packet in InStream */
	CrFwInStreamStubSetPcktType(40,1,0);		 /* Set packet type to be Sample 1 InReport */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);		 /* Set packet destination to current destination */
	CrFwInStreamStubSetPcktCmdRepType(crRepType);		 /* Define packet as InReport */
	CrFwInStreamStubSetPcktCmdRepId(111);		 /* Define command/report identifier */
	CrFwInRepSample1SetValidityFlag(1);		/* Validity Check of InReport will succeed */
	CrFwCmpInit(inStream);
	CrFwCmpReset(inStream);
	if (!CrFwCmpIsInConfigured(inStream))
		return 0;
	if (!CrFwInStreamIsInPcktAvail(inStream))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream) != 1)
		return 0;

	/* Create OutStream */
	outStream = CrFwOutStreamMake(0);
	FwSmStart(outStream);
	CrFwCmpInit(outStream);
	CrFwCmpReset(outStream);
	if (!CrFwCmpIsInConfigured(outStream))
		return 0;
	CrFwOutStreamStubSetHandoverFlag(1); /* Configure Packet Hand-Over Operation to return "hand-over successful" */
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)	/* Check that there are no pending packets */
		return 0;

	/* Create InFactory */
	inFactory = CrFwInFactoryMake();
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Create InManager for InReports and configure it to be full */
	inManager = CrFwInManagerMake(1);	/* InManager for InReports */
	CrFwCmpInit(inManager);
	CrFwCmpReset(inManager);
	if (!CrFwCmpIsInConfigured(inManager))
		return 0;
	for (i=0; i<CrFwInManagerGetPCRLSize(inManager); i++) {
		pckt = CrFwPcktMake(100);
		CrFwPcktSetServType(pckt,5);
		CrFwPcktSetServSubType(pckt,1);
		CrFwPcktSetDiscriminant(pckt,1);
		CrFwInManagerLoad(inManager, CrFwInFactoryMakeInRep(pckt));
	}

	/* Load InStream in the InLoader and execute InLoader*/
	CrFwInLoaderSetInStream(inStream);
	CrFwCmpExecute(inLoader);

	/* Check that no packet was loaded into the OutStream */
	if (CrFwOutStreamStubGetHandoverCnt() != handoverCnt)
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)
		return 0;

	/* Check that error reports have been generated (one by the Load operation of the InManager
	 * and one by the InLoader) */
	if (CrFwRepErrStubGetPos() != errRepPosLocal+2)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crInLoaderLdFail)
		return 0;
	if (CrFwRepErrStubGetTypeId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != CR_FW_INLOADER_TYPE)
		return 0;
	if (CrFwRepErrStubGetInstanceId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != 0)
		return 0;

	/* Reset the InManager (this should clear the PCRL and release all loaded components) */
	CrFwCmpReset(inManager);

	/* Create InManager for InCommands and configure it to be full */
	inManager = CrFwInManagerMake(0);	/* InManager for InCommands */
	CrFwCmpInit(inManager);
	CrFwCmpReset(inManager);
	if (!CrFwCmpIsInConfigured(inManager))
		return 0;
	for (i=0; i<CrFwInManagerGetPCRLSize(inManager); i++) {
		pckt = CrFwPcktMake(100);
		CrFwPcktSetServType(pckt,8);
		CrFwPcktSetServSubType(pckt,1);
		CrFwPcktSetDiscriminant(pckt,1);
		CrFwInManagerLoad(inManager, CrFwInFactoryMakeInCmd(pckt));
	}

	/* Load the InStream with a packet representing an InCommand */
	CrFwInStreamStubSetPcktCollectionCnt(1); /* One pending packet in InStream */
	CrFwInStreamStubSetPcktType(50,1,0);		 /* Set packet type to Sample 1 InCommand */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);		 /* Set packet destination to current destination */
	CrFwInStreamStubSetPcktCmdRepType(crCmdType);		 /* Define packet as InCommand */
	CrFwInStreamStubSetPcktCmdRepId(111);		 /* Define command/report identifier */
	CrFwInCmdSample1SetValidityFlag(1);		/* Validity Check of InCommand will succeed */
	CrFwCmpReset(inStream);

	/* Execute InLoader*/
	CrFwCmpExecute(inLoader);

	/* Check that no packet was loaded into the OutStream */
	if (CrFwOutStreamStubGetHandoverCnt() != handoverCnt)
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)
		return 0;

	/* Check that acceptance failure report has been generated */
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetOutcome(cmdRepPos) != crCmdAckLdFail)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetFailCode(cmdRepPos) != 0)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetServType(cmdRepPos) != 50)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetServSubType(cmdRepPos) != 1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetDiscriminant(cmdRepPos) != 0)
		return 0;

	/* Check that no error reports were generated (other than the one generated by the load
	 * operation on the InManager) */
	if (CrFwRepErrStubGetPos() != errRepPosLocal+3)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crInManagerPcrlFull)
		return 0;

	/* Reset the InManager (this should clear the PCRL and release all loaded components) */
	CrFwCmpReset(inManager);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInLoaderTestCase9() {
	FwSmDesc_t inLoader, inStream, outStream, inFactory, inManager;
	CrFwCounterU2_t errRepPosLocal;
	CrFwCounterU1_t handoverCnt;
	CrFwCounterU2_t cmdRepPos;

	/* Store the current value of the command report counter */
	cmdRepPos = CrFwRepInCmdOutcomeStubGetPos();

	/* Store the current value of the OutStream packet handover counter */
	handoverCnt = CrFwOutStreamStubGetHandoverCnt();

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Instantiate, initialize and configure the InLoader */
	inLoader = CrFwInLoaderMake();
	CrFwCmpInit(inLoader);
	CrFwCmpReset(inLoader);
	if (!CrFwCmpIsInConfigured(inLoader))
		return 0;

	/* Create InStream and configure it to be in state AVAIL with one pending packet */
	inStream = CrFwInStreamMake(0);
	CrFwInStreamStubSetPcktCollectionCnt(1); /* One pending packet in InStream */
	CrFwInStreamStubSetPcktType(40,1,0);		 /* Set packet type to be Sample 1 InReport */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);		 /* Set packet destination to current destination */
	CrFwInStreamStubSetPcktCmdRepType(crRepType);		 /* Define packet as InReport */
	CrFwInStreamStubSetPcktCmdRepId(111);		 /* Define command/report identifier */
	CrFwInRepSample1SetValidityFlag(1);		/* Validity Check of InReport will succeed */
	CrFwCmpInit(inStream);
	CrFwCmpReset(inStream);
	if (!CrFwCmpIsInConfigured(inStream))
		return 0;
	if (!CrFwInStreamIsInPcktAvail(inStream))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream) != 1)
		return 0;

	/* Create OutStream */
	outStream = CrFwOutStreamMake(0);
	FwSmStart(outStream);
	CrFwCmpInit(outStream);
	CrFwCmpReset(outStream);
	if (!CrFwCmpIsInConfigured(outStream))
		return 0;
	CrFwOutStreamStubSetHandoverFlag(1); /* Configure Packet Hand-Over Operation to return "hand-over successful" */
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)	/* Check that there are no pending packets */
		return 0;

	/* Create InFactory */
	inFactory = CrFwInFactoryMake();
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Create InManager for InReports */
	inManager = CrFwInManagerMake(1);	/* InManager for InReports */
	CrFwCmpInit(inManager);
	CrFwCmpReset(inManager);
	if (!CrFwCmpIsInConfigured(inManager))
		return 0;

	/* Load InStream in the InLoader and execute InLoader*/
	CrFwInLoaderSetInStream(inStream);
	CrFwCmpExecute(inLoader);

	/* Check that no packet was loaded into the OutStream */
	if (CrFwOutStreamStubGetHandoverCnt() != handoverCnt)
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)
		return 0;

	/* Check that one component has been loaded in the InManager */
	if (CrFwInManagerGetNOfPendingInCmp(inManager) != 1)
		return 0;

	/* Reset the InManager (this should clear the PCRL and release all loaded components) */
	CrFwCmpReset(inManager);

	/* Check that no command reports were generated  */
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos)
		return 0;

	/* Check that no error reports were generated  */
	if (CrFwRepErrStubGetPos() != errRepPosLocal)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crInManagerPcrlFull)
		return 0;

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInLoaderTestCase10() {
	FwSmDesc_t inLoader, inStream, outStream, inFactory, inManager;
	CrFwCounterU2_t errRepPosLocal;
	CrFwCounterU1_t handoverCnt;
	CrFwCounterU2_t cmdRepPos;

	/* Store the current value of the command report counter */
	cmdRepPos = CrFwRepInCmdOutcomeStubGetPos();

	/* Store the current value of the OutStream packet handover counter */
	handoverCnt = CrFwOutStreamStubGetHandoverCnt();

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Instantiate, initialize and configure the InLoader */
	inLoader = CrFwInLoaderMake();
	CrFwCmpInit(inLoader);
	CrFwCmpReset(inLoader);
	if (!CrFwCmpIsInConfigured(inLoader))
		return 0;

	/* Create InStream and configure it to be in state AVAIL with one pending packet */
	inStream = CrFwInStreamMake(0);
	CrFwInStreamStubSetPcktCollectionCnt(1); /* One pending packet in InStream */
	CrFwInStreamStubSetPcktType(50,1,0);		 /* Set packet type to Sample 1 InCommand */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);		 /* Set packet destination to current destination */
	CrFwInStreamStubSetPcktCmdRepType(crCmdType);		 /* Define packet as InReport */
	CrFwInStreamStubSetPcktAckLevel(0,0,0,0);			/* Do not acknolwedge */
	CrFwInStreamStubSetPcktCmdRepId(111);		 /* Define command/report identifier */
	CrFwInCmdSample1SetValidityFlag(1);		/* Validity Check of InCommand will succeed */

	CrFwCmpInit(inStream);
	CrFwCmpReset(inStream);
	if (!CrFwCmpIsInConfigured(inStream))
		return 0;
	if (!CrFwInStreamIsInPcktAvail(inStream))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream) != 1)
		return 0;

	/* Create OutStream */
	outStream = CrFwOutStreamMake(0);
	FwSmStart(outStream);
	CrFwCmpInit(outStream);
	CrFwCmpReset(outStream);
	if (!CrFwCmpIsInConfigured(outStream))
		return 0;
	CrFwOutStreamStubSetHandoverFlag(1); /* Configure Packet Hand-Over Operation to return "hand-over successful" */
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)	/* Check that there are no pending packets */
		return 0;

	/* Create InFactory */
	inFactory = CrFwInFactoryMake();
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Create InManager for InCommands */
	inManager = CrFwInManagerMake(0);	/* InManager for InCommands */
	CrFwCmpInit(inManager);
	CrFwCmpReset(inManager);
	if (!CrFwCmpIsInConfigured(inManager))
		return 0;

	/* Load InStream in the InLoader and execute InLoader*/
	CrFwInLoaderSetInStream(inStream);
	CrFwCmpExecute(inLoader);

	/* Check that no packet was loaded into the OutStream */
	if (CrFwOutStreamStubGetHandoverCnt() != handoverCnt)
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)
		return 0;

	/* Check that one component has been loaded in the InManager */
	if (CrFwInManagerGetNOfPendingInCmp(inManager) != 1)
		return 0;

	/* Reset the InManager (this should clear the PCRL and release all loaded components) */
	CrFwCmpReset(inManager);

	/* Check that no command reports were generated  */
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos)
		return 0;

	/* Check that no error reports were generated  */
	if (CrFwRepErrStubGetPos() != errRepPosLocal)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crInManagerPcrlFull)
		return 0;

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInLoaderTestCase11() {
	FwSmDesc_t inLoader, inStream, outStream, inFactory, inManager;
	CrFwCounterU2_t errRepPosLocal;
	CrFwCounterU1_t handoverCnt;
	CrFwCounterU2_t cmdRepPos;

	/* Store the current value of the command report counter */
	cmdRepPos = CrFwRepInCmdOutcomeStubGetPos();

	/* Store the current value of the OutStream packet handover counter */
	handoverCnt = CrFwOutStreamStubGetHandoverCnt();

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Instantiate, initialize and configure the InLoader */
	inLoader = CrFwInLoaderMake();
	CrFwCmpInit(inLoader);
	CrFwCmpReset(inLoader);
	if (!CrFwCmpIsInConfigured(inLoader))
		return 0;

	/* Create InStream and configure it to be in state AVAIL with one pending packet */
	inStream = CrFwInStreamMake(0);
	CrFwInStreamStubSetPcktCollectionCnt(1); /* One pending packet in InStream */
	CrFwInStreamStubSetPcktType(50,1,0);		 /* Set packet type to Sample 1 InCommand */
	CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);		 /* Set packet destination to current destination */
	CrFwInStreamStubSetPcktCmdRepType(crCmdType);		 /* Define packet as InReport */
	CrFwInStreamStubSetPcktAckLevel(1,0,0,0);			/* Acknolwedge acceptance */
	CrFwInStreamStubSetPcktCmdRepId(111);		 /* Define command/report identifier */
	CrFwInCmdSample1SetValidityFlag(1);		/* Validity Check of InCommand will succeed */

	CrFwCmpInit(inStream);
	CrFwCmpReset(inStream);
	if (!CrFwCmpIsInConfigured(inStream))
		return 0;
	if (!CrFwInStreamIsInPcktAvail(inStream))
		return 0;
	if (CrFwInStreamGetNOfPendingPckts(inStream) != 1)
		return 0;

	/* Create OutStream */
	outStream = CrFwOutStreamMake(0);
	FwSmStart(outStream);
	CrFwCmpInit(outStream);
	CrFwCmpReset(outStream);
	if (!CrFwCmpIsInConfigured(outStream))
		return 0;
	CrFwOutStreamStubSetHandoverFlag(1); /* Configure Packet Hand-Over Operation to return "hand-over successful" */
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)	/* Check that there are no pending packets */
		return 0;

	/* Create InFactory */
	inFactory = CrFwInFactoryMake();
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Create InManager for InCommands */
	inManager = CrFwInManagerMake(0);	/* InManager for InCommands */
	CrFwCmpInit(inManager);
	CrFwCmpReset(inManager);
	if (!CrFwCmpIsInConfigured(inManager))
		return 0;

	/* Load InStream in the InLoader and execute InLoader*/
	CrFwInLoaderSetInStream(inStream);
	CrFwCmpExecute(inLoader);

	/* Check that no packet was loaded into the OutStream */
	if (CrFwOutStreamStubGetHandoverCnt() != handoverCnt)
		return 0;
	if (CrFwOutStreamGetNOfPendingPckts(outStream) != 0)
		return 0;

	/* Check that one component has been loaded in the InManager */
	if (CrFwInManagerGetNOfPendingInCmp(inManager) != 1)
		return 0;

	/* Reset the InManager (this should clear the PCRL and release all loaded components) */
	CrFwCmpReset(inManager);

	/* Check that command acceptance acknowledge report was generated  */
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetOutcome(cmdRepPos) != crCmdAckAccSucc)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetServType(cmdRepPos) != 50)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetServSubType(cmdRepPos) != 1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetDiscriminant(cmdRepPos) != 0)
		return 0;

	/* Check that no error reports were generated  */
	if (CrFwRepErrStubGetPos() != errRepPosLocal)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crInManagerPcrlFull)
		return 0;

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

