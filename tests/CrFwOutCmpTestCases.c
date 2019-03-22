/**
 * @file
 *
 * Implementation of test cases for OutComponent component.
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
#include "CrFwOutCmpTestCases.h"
#include "CrFwOutStreamStub.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include framework files */
#include "CrFwOutRegistryUserPar.h"
#include "OutRegistry/CrFwOutRegistry.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutFactory/CrFwOutFactory.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include configuration files */
#include "CrFwRepErrStub.h"
#include "CrFwOutFactoryUserPar.h"
#include "CrFwCmpData.h"

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutCmpTestCase1() {
	FwSmDesc_t outFactory, outCmp1, outCmp2;
	CrFwCmpData_t* outCmpData;
	CrFwOutCmpData_t* cmpSpecificData;
	CrFwPckt_t pckt;
	CrFwInstanceId_t apidInstanceId = CR_FW_HOST_APP_ID << (sizeof(CrFwInstanceId_t)*8-CR_FW_NBITS_APP_ID);

	/* Instantiate the OutFactory */
	outFactory = CrFwOutFactoryMake();

	/* Initialize and Configure OutFactory and check success */
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Allocate two OutComponents */
	outCmp1 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	outCmp2 = CrFwOutFactoryMakeOutCmp(5,4,5,0);

	/* Perform a configuration check on one of the OutComponents */
	if (FwSmCheckRec(outCmp1) != smSuccess)
		return 0;

	/* Check the instance identifiers and the type identifier */
	if (CrFwCmpGetInstanceId(outCmp1) != apidInstanceId + 1)
		return 0;
	if (CrFwCmpGetInstanceId(outCmp2) != apidInstanceId + 2)
		return 0;
	if (CrFwCmpGetTypeId(outCmp1) != CR_FW_OUTCMP_TYPE)
		return 0;
	if (CrFwCmpGetTypeId(outCmp2) != CR_FW_OUTCMP_TYPE)
		return 0;

	/* Check the group */
	if (CrFwOutCmpGetGroup(outCmp1) != 0)
		return 0;

	/* Check OutComponent state */
	if (!CrFwCmpIsInConfigured(outCmp1))
		return 0;
	if (!CrFwOutCmpIsInLoaded(outCmp1))
		return 0;

	/* Check type, sub-type and discriminant */
	if (CrFwOutCmpGetServType(outCmp1) != 1)
		return 0;
	if (CrFwOutCmpGetServType(outCmp2) != 5)
		return 0;

	if (CrFwOutCmpGetServSubType(outCmp1) != 1)
		return 0;
	if (CrFwOutCmpGetServSubType(outCmp2) != 4)
		return 0;

	if (CrFwOutCmpGetDiscriminant(outCmp1) != 0)
		return 0;
	if (CrFwOutCmpGetDiscriminant(outCmp2) != 5)
		return 0;

	/* Check group set and read-back */
	CrFwOutCmpSetGroup(outCmp1, 12);
	if (CrFwOutCmpGetGroup(outCmp1) != 12)
		return 0;

	/* Check destination set and read-back */
	CrFwOutCmpSetDest(outCmp1, 4);
	if (CrFwOutCmpGetDest(outCmp1) != 4)
		return 0;

	/* Check discriminant set and read-back */
	CrFwOutCmpSetDiscriminant(outCmp1, 7);
	if (CrFwOutCmpGetDiscriminant(outCmp1) != 7)
		return 0;

	/* Check time stamp set and read-back */
	CrFwOutCmpSetTimeStamp(outCmp1, 33);
	if (CrFwOutCmpGetTimeStamp(outCmp1) != 33)
		return 0;

	/* Check acknowledge level set and read-back */
	CrFwOutCmpSetAckLevel(outCmp1, 1, 0, 0, 0);
	if (CrFwOutCmpIsAcceptAck(outCmp1) != 1)
		return 0;
	if (CrFwOutCmpIsStartAck(outCmp1) != 0)
		return 0;
	if (CrFwOutCmpIsProgressAck(outCmp1) != 0)
		return 0;
	if (CrFwOutCmpIsTermAck(outCmp1) != 0)
		return 0;

	CrFwOutCmpSetAckLevel(outCmp1, 0, 1, 0, 0);
	if (CrFwOutCmpIsAcceptAck(outCmp1) != 0)
		return 0;
	if (CrFwOutCmpIsStartAck(outCmp1) != 1)
		return 0;
	if (CrFwOutCmpIsProgressAck(outCmp1) != 0)
		return 0;
	if (CrFwOutCmpIsTermAck(outCmp1) != 0)
		return 0;

	CrFwOutCmpSetAckLevel(outCmp1, 0, 0, 1, 0);
	if (CrFwOutCmpIsAcceptAck(outCmp1) != 0)
		return 0;
	if (CrFwOutCmpIsStartAck(outCmp1) != 0)
		return 0;
	if (CrFwOutCmpIsProgressAck(outCmp1) != 1)
		return 0;
	if (CrFwOutCmpIsTermAck(outCmp1) != 0)
		return 0;

	CrFwOutCmpSetAckLevel(outCmp1, 0, 0, 0, 1);
	if (CrFwOutCmpIsAcceptAck(outCmp1) != 0)
		return 0;
	if (CrFwOutCmpIsStartAck(outCmp1) != 0)
		return 0;
	if (CrFwOutCmpIsProgressAck(outCmp1) != 0)
		return 0;
	if (CrFwOutCmpIsTermAck(outCmp1) != 1)
		return 0;

	/* Check functions to get parameter area */
	outCmpData = (CrFwCmpData_t*)FwSmGetData(outCmp1);
	cmpSpecificData = (CrFwOutCmpData_t*)(outCmpData->cmpSpecificData);
	if (CrFwOutCmpGetParStart(outCmp1) != CrFwPcktGetParStart(cmpSpecificData->pckt))
		return 0;
	if (CrFwOutCmpGetParLength(outCmp1) != CrFwPcktGetParLength(cmpSpecificData->pckt))
		return 0;

	/* Check the function to get the OutComponent packets */
	pckt = CrFwOutCmpGetPckt(outCmp1);
	if (CrFwPcktGetServType(pckt)!=1)
		return 0;
	if (CrFwPcktGetServSubType(pckt)!=1)
		return 0;

	pckt = CrFwOutCmpGetPckt(outCmp2);
	if (CrFwPcktGetServType(pckt)!=5)
		return 0;
	if (CrFwPcktGetServSubType(pckt)!=4)
		return 0;

	/* Release the OutComponents */
	CrFwOutFactoryReleaseOutCmp(outCmp1);
	CrFwOutFactoryReleaseOutCmp(outCmp2);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutCmpTestCase2() {
	FwSmDesc_t outFactory, outCmp;

	/* Instantiate the OutFactory */
	outFactory = CrFwOutFactoryMake();

	/* Initialize and Configure OutFactory and check success */
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Allocate a Sample 1 OutComponent instance */
	outCmp = CrFwOutFactoryMakeOutCmp(50,1,0,0);
	if (!CrFwOutCmpIsInLoaded(outCmp))
		return 0;

	/* Set up enable, repeat and ready check of sample OutComponent */
	CrFwOutCmpSample1SetEnableFlag(0);
	CrFwOutCmpSample1SetReadyFlag(1);
	CrFwOutCmpSample1SetRepeatFlag(0);

	/* Execute the sample OutComponent and check it is aborted */
	CrFwCmpExecute(outCmp);
	if (!CrFwOutCmpIsInAborted(outCmp))
		return 0;

	/* Release the OutComponent */
	CrFwOutFactoryReleaseOutCmp(outCmp);

	/* Allocate another Sample 1 OutComponent instance */
	outCmp = CrFwOutFactoryMakeOutCmp(50,1,0,0);
	if (!CrFwOutCmpIsInLoaded(outCmp))
		return 0;

	/* Set up enable, repeat and ready check of sample OutComponent */
	CrFwOutCmpSample1SetEnableFlag(0);
	CrFwOutCmpSample1SetReadyFlag(0);
	CrFwOutCmpSample1SetRepeatFlag(0);

	/* Execute the sample OutComponent and check it is aborted */
	CrFwCmpExecute(outCmp);
	if (!CrFwOutCmpIsInAborted(outCmp))
		return 0;

	/* Release the OutComponent */
	CrFwOutFactoryReleaseOutCmp(outCmp);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutCmpTestCase3() {
	FwSmDesc_t outFactory, outCmp;
	CrFwCounterU2_t errRepPosLocal;

	/* Reset error reporting interface */
	CrFwRepErrStubReset();

	/* Instantiate the OutFactory */
	outFactory = CrFwOutFactoryMake();

	/* Initialize and Configure OutFactory and check success */
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Allocate a Sample1 OutComponent instance */
	outCmp = CrFwOutFactoryMakeOutCmp(50,1,0,0);
	if (!CrFwOutCmpIsInLoaded(outCmp))
		return 0;

	/* Set up enable, repeat and ready check of sample OutComponent */
	CrFwOutCmpSample1SetEnableFlag(1);
	CrFwOutCmpSample1SetReadyFlag(1);
	CrFwOutCmpSample1SetRepeatFlag(0);

	/* Set destination to an invalid value */
	CrFwOutCmpSetDest(outCmp, 99);

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Execute and terminate the sample OutComponent and check it is terminated */
	CrFwCmpExecute(outCmp);
	CrFwOutCmpTerminate(outCmp);
	if (!CrFwOutCmpIsInTerminated(outCmp))
		return 0;

	/* Check generation of error report */
	if (CrFwRepErrStubGetPos() != errRepPosLocal+1)
		return 0;
	if (CrFwRepErrStubGetErrCode(errRepPosLocal) != crOutCmpSendPcktInvDest)
		return 0;
	if (CrFwRepErrStubGetTypeId(errRepPosLocal) != CR_FW_OUTCMP_TYPE)
		return 0;
	if (CrFwRepErrStubGetInstanceId(errRepPosLocal) != CrFwCmpGetInstanceId(outCmp))
		return 0;

	/* Check and reset application error code */
	if (CrFwGetAppErrCode() != crOutStreamUndefDest)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);

	/* Release the OutComponent */
	CrFwOutFactoryReleaseOutCmp(outCmp);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutCmpTestCase4() {
	FwSmDesc_t outFactory, outCmp;
	CrFwCounterU2_t errRepPosLocal;
	CrFwDestSrc_t dest;
	CrFwPckt_t pckt;
	CrFwBool_t acceptAck, startAck, progressAck, termAck;
	unsigned char counter = 90;
	CrFwTimeStamp_t curTimeStamp;
	CrFwTime_t curTime;
	CrFwTimeCyc_t cycTime;

	/* Reset error reporting interface */
	CrFwRepErrStubReset();

	/* Start, initialize and reset OutStream to which OutComponent will be sent (just to clear effect of previous tests) */
	dest = 2;
	FwSmStart(CrFwOutStreamGet(dest));
	CrFwCmpInit(CrFwOutStreamGet(dest));
	CrFwCmpReset(CrFwOutStreamGet(dest));
	if (!CrFwCmpIsInConfigured(CrFwOutStreamGet(dest)))
		return 0;

	/* Configure OutStream to hold packets in its internal packet queue */
	CrFwOutStreamStubSetHandoverFlag(0);

	/* Instantiate the OutFactory */
	outFactory = CrFwOutFactoryMake();

	/* Initialize and Configure OutFactory and check success */
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Retrieve a Sample1 OutComponent instance */
	outCmp = CrFwOutFactoryMakeOutCmp(50,1,0,0);
	if (!CrFwOutCmpIsInLoaded(outCmp))
		return 0;

	/* Set the Sample1 OutComponent acknowledge level */
	acceptAck = 0;
	startAck = 1;
	progressAck = 0;
	termAck = 1;
	CrFwOutCmpSetAckLevel(outCmp, acceptAck, startAck, progressAck, termAck);

	/* Get the packet associated to the Sample1 OutComponent */
	pckt = CrFwOutCmpSample1GetPckt(outCmp);

	/* Set up enable, repeat and ready check of sample OutComponent */
	CrFwOutCmpSample1SetEnableFlag(1);
	CrFwOutCmpSample1SetReadyFlag(1);
	CrFwOutCmpSample1SetRepeatFlag(0);

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Set destination of OutComponent */
	CrFwOutCmpSetDest(outCmp, dest);

	/* Set Sample1 Counter */
	CrFwOutCmpSample1SetCounter(counter);

	/* Retrieve the current time in all its 3 formats and verify that they are equivalent */
	curTimeStamp = CrFwGetCurrentTimeStamp();
	curTime = CrFwGetCurrentTime();
	cycTime = CrFwGetCurrentCycTime();
	if (curTime != CrFwTimeStampToStdTime(curTimeStamp))
		return 0;

	if (curTimeStamp != CrFwStdTimeToTimeStamp(curTime))
		return 0;

	if (cycTime != curTimeStamp)
		return 0;

	/* Execute and terminate the sample OutComponent and check it is terminated */
	CrFwCmpExecute(outCmp);
	CrFwOutCmpTerminate(outCmp);
	if (!CrFwOutCmpIsInTerminated(outCmp))
		return 0;

	/* Check that time stamp is correctly set */
	if (CrFwOutCmpGetTimeStamp(outCmp) != curTime+1)
		return 0;

	/* Check that no error report was generated */
	if (CrFwRepErrStubGetPos() != errRepPosLocal)
		return 0;

	/* Check that number of pending out-going packets in OutStream has increased */
	if (CrFwOutStreamGetNOfPendingPckts(CrFwOutStreamGet(dest)) != 1)
		return 0;

	/* Check that the OutComponent state was correctly serialized to its packet */
	if (CrFwPcktGetServType(pckt) != 50)
		return 0;
	if (CrFwPcktGetServSubType(pckt) != 1)
		return 0;
	if (CrFwPcktGetDiscriminant(pckt) != 0)
		return 0;
	if (CrFwPcktGetCmdRepId(pckt) != CrFwCmpGetInstanceId(outCmp))
		return 0;
	if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
		return 0;
	if (CrFwPcktGetDest(pckt) != dest)
		return 0;
	if (CrFwPcktIsAcceptAck(pckt) != 0)
		return 0;
	if (CrFwPcktIsStartAck(pckt) != 1)
		return 0;
	if (CrFwPcktIsProgressAck(pckt) != 0)
		return 0;
	if (CrFwPcktIsTermAck(pckt) != 1)
		return 0;
	if (CrFwPcktGetCrc(pckt) != 0xFFFF)
	    return 0;
	if (pckt[CrFwPcktGetMaxLength()-3] != counter+1)
		return 0;

	/* Reset the OutStream (this will also release the OutComponent packet) */
	CrFwCmpReset(CrFwOutStreamGet(dest));

	/* Release the OutComponent */
	CrFwOutFactoryReleaseOutCmp(outCmp);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutCmpTestCase5() {
	FwSmDesc_t outFactory, outCmp;
	CrFwCounterU2_t errRepPosLocal;
	CrFwDestSrc_t dest;
	CrFwPckt_t pckt;
	CrFwBool_t acceptAck, startAck, progressAck, termAck;
	unsigned char counter = 89;

	/* Reset error reporting interface */
	CrFwRepErrStubReset();

	/* Start, initialize and reset OutStream to which OutComponent will be sent (just to clear effect of previous tests) */
	dest = 2;
	FwSmStart(CrFwOutStreamGet(dest));
	CrFwCmpInit(CrFwOutStreamGet(dest));
	CrFwCmpReset(CrFwOutStreamGet(dest));
	if (!CrFwCmpIsInConfigured(CrFwOutStreamGet(dest)))
		return 0;

	/* Configure OutStream to hold packets in its internal packet queue */
	CrFwOutStreamStubSetHandoverFlag(0);

	/* Instantiate the OutFactory */
	outFactory = CrFwOutFactoryMake();

	/* Initialize and Configure OutFactory and check success */
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Retrieve a Sample1 OutComponent instance */
	outCmp = CrFwOutFactoryMakeOutCmp(50,1,0,0);
	if (!CrFwOutCmpIsInLoaded(outCmp))
		return 0;

	/* Set the Sample1 OutComponent acknowledge level */
	acceptAck = 1;
	startAck = 0;
	progressAck = 1;
	termAck = 0;
	CrFwOutCmpSetAckLevel(outCmp, acceptAck, startAck, progressAck, termAck);

	/* Get the packet associated to the Sample1 OutComponent */
	pckt = CrFwOutCmpSample1GetPckt(outCmp);

	/* Set up enable, repeat and ready check of sample OutComponent */
	CrFwOutCmpSample1SetEnableFlag(1);
	CrFwOutCmpSample1SetReadyFlag(0);
	CrFwOutCmpSample1SetRepeatFlag(0);

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Set destination of OutComponent */
	CrFwOutCmpSetDest(outCmp, dest);

	/* Set Sample1 Counter */
	CrFwOutCmpSample1SetCounter(counter);

	/* Execute/terminate the sample OutComponent and check it is left pending */
	CrFwCmpExecute(outCmp);
	CrFwOutCmpTerminate(outCmp);
	if (!CrFwOutCmpIsInPending(outCmp))
		return 0;

	/* Execute it again and check that it remains pending */
	CrFwCmpExecute(outCmp);
	CrFwOutCmpTerminate(outCmp);
	CrFwCmpExecute(outCmp);
	CrFwOutCmpTerminate(outCmp);
	if (!CrFwOutCmpIsInPending(outCmp))
		return 0;

	/* Configure the ready check to return "ready" */
	CrFwOutCmpSample1SetReadyFlag(1);

	/* Execute the sample OutComponent and check it is terminated */
	CrFwCmpExecute(outCmp);
	CrFwOutCmpTerminate(outCmp);
	if (!CrFwOutCmpIsInTerminated(outCmp))
		return 0;

	/* Check that no error report was generated */
	if (CrFwRepErrStubGetPos() != errRepPosLocal)
		return 0;

	/* Check that number of pending packets in OutStream has increased */
	if (CrFwOutStreamGetNOfPendingPckts(CrFwOutStreamGet(dest)) != 1)
		return 0;

	/* Check that the OutComponent state was correctly serialized to its packet */
	if (CrFwPcktGetServType(pckt) != 50)
		return 0;
	if (CrFwPcktGetServSubType(pckt) != 1)
		return 0;
	if (CrFwPcktGetDiscriminant(pckt) != 0)
		return 0;
	if (CrFwPcktGetCmdRepId(pckt) != CrFwCmpGetInstanceId(outCmp))
		return 0;
	if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
		return 0;
	if (CrFwPcktGetDest(pckt) != dest)
		return 0;
	if (CrFwPcktIsAcceptAck(pckt) != 1)
		return 0;
	if (CrFwPcktIsStartAck(pckt) != 0)
		return 0;
	if (CrFwPcktIsProgressAck(pckt) != 1)
		return 0;
	if (CrFwPcktIsTermAck(pckt) != 0)
		return 0;
    if (CrFwPcktGetCrc(pckt) != 0xFFFF)
        return 0;
	if (pckt[CrFwPcktGetMaxLength()-3] != counter + 1)
		return 0;

	/* Reset the OutStream */
	CrFwCmpReset(CrFwOutStreamGet(dest));

	/* Release the OutComponent */
	CrFwOutFactoryReleaseOutCmp(outCmp);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutCmpTestCase6() {
	FwSmDesc_t outFactory, outCmp1, outCmp2;
	CrFwCounterU2_t errRepPosLocal;
	CrFwDestSrc_t dest;
	CrFwPckt_t pckt;
	CrFwBool_t acceptAck, startAck, progressAck, termAck;

	/* Reset error reporting interface */
	CrFwRepErrStubReset();

	/* Start, initialize and reset OutStream to which OutComponent will be sent (just to clear effect of previous tests) */
	dest = 2;
	FwSmStart(CrFwOutStreamGet(dest));
	CrFwCmpInit(CrFwOutStreamGet(dest));
	CrFwCmpReset(CrFwOutStreamGet(dest));
	if (!CrFwCmpIsInConfigured(CrFwOutStreamGet(dest)))
		return 0;

	/* Configure OutStream to hold packets in its internal packet queue */
	CrFwOutStreamStubSetHandoverFlag(0);

	/* Instantiate the OutFactory */
	outFactory = CrFwOutFactoryMake();

	/* Initialize and Configure OutFactory and check success */
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Retrieve two OutComponent instances */
	outCmp1 = CrFwOutFactoryMakeOutCmp(5,1,2,0);
	outCmp2 = CrFwOutFactoryMakeOutCmp(25,3,0,0);
	if (!CrFwOutCmpIsInLoaded(outCmp1))
		return 0;
	if (!CrFwOutCmpIsInLoaded(outCmp2))
		return 0;

	/* Set the acknowledge level of the second OutComponent */
	acceptAck = 0;
	startAck = 1;
	progressAck = 0;
	termAck = 1;
	CrFwOutCmpSetAckLevel(outCmp2, acceptAck, startAck, progressAck, termAck);

	/* Set destination of second OutComponent */
	CrFwOutCmpSetDest(outCmp2, dest);

	/* Get the packet associated to the second OutComponent */
	pckt = CrFwOutCmpSample1GetPckt(outCmp2);

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Disable the first type of OutComponent */
	CrFwOutRegistrySetEnable(5, 0, 0, 0);

	/* Disable the second type of OutComponent */
	CrFwOutRegistrySetEnable(25, 0, 0, 1);

	/* Execute/terminate the first OutComponent and check it is aborted */
	CrFwCmpExecute(outCmp1);
	CrFwOutCmpTerminate(outCmp1);
	if (!CrFwOutCmpIsInAborted(outCmp1))
		return 0;

	/* Execute the second OutComponent and check it is terminated */
	CrFwCmpExecute(outCmp2);
	CrFwOutCmpTerminate(outCmp2);
	if (!CrFwOutCmpIsInTerminated(outCmp2))
		return 0;

	/* Check that no error report was generated */
	if (CrFwRepErrStubGetPos() != errRepPosLocal)
		return 0;

	/* Check that number of pending OutComponents in OutStream has increased */
	if (CrFwOutStreamGetNOfPendingPckts(CrFwOutStreamGet(dest)) != 1)
		return 0;

	/* Check that the state of the second OutComponent was correctly serialized to its packet */
	if (CrFwPcktGetServType(pckt) != 25)
		return 0;
	if (CrFwPcktGetServSubType(pckt) != 3)
		return 0;
	if (CrFwPcktGetDiscriminant(pckt) != 0)
		return 0;
	if (CrFwPcktGetCmdRepId(pckt) != CrFwCmpGetInstanceId(outCmp2))
		return 0;
	if (CrFwPcktGetCmdRepType(pckt) != crRepType)
		return 0;
	if (CrFwPcktGetDest(pckt) != dest)
		return 0;
	if (CrFwPcktIsAcceptAck(pckt) != 0)
		return 0;
	if (CrFwPcktIsStartAck(pckt) != 1)
		return 0;
	if (CrFwPcktIsProgressAck(pckt) != 0)
		return 0;
	if (CrFwPcktIsTermAck(pckt) != 1)
		return 0;

	/* Reset the OutStream (this will also release the OutComponent packet) */
	CrFwCmpReset(CrFwOutStreamGet(dest));

	/* Release the two OutComponent */
	CrFwOutFactoryReleaseOutCmp(outCmp1);
	CrFwOutFactoryReleaseOutCmp(outCmp2);

	/* Check that no components are allocated in the OutFactory */
	if (CrFwOutFactoryGetNOfAllocatedOutCmp() > 0)
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
CrFwBool_t CrFwOutCmpTestCase7() {
	FwSmDesc_t outFactory, outCmp;
	CrFwDestSrc_t dest;
	CrFwPckt_t pckt;
	unsigned char counter = 22;

	/* Reset error reporting interface */
	CrFwRepErrStubReset();

	/* Start, initialize and reset OutStream to which OutComponent will be sent (just to clear effect of previous tests) */
	dest = 2;
	FwSmStart(CrFwOutStreamGet(dest));
	CrFwCmpInit(CrFwOutStreamGet(dest));
	CrFwCmpReset(CrFwOutStreamGet(dest));
	if (!CrFwCmpIsInConfigured(CrFwOutStreamGet(dest)))
		return 0;

	/* Configure OutStream to hold packets in its internal packet queue */
	CrFwOutStreamStubSetHandoverFlag(0);

	/* Instantiate the OutFactory */
	outFactory = CrFwOutFactoryMake();

	/* Initialize and Configure OutFactory and check success */
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Allocate a Sample 1 OutComponent instance */
	outCmp = CrFwOutFactoryMakeOutCmp(50,1,0,0);
	if (!CrFwOutCmpIsInLoaded(outCmp))
		return 0;

	/* Set destination of OutComponent */
	CrFwOutCmpSetDest(outCmp, dest);

	/* Set Sample1 Counter */
	CrFwOutCmpSample1SetCounter(counter);

	/* Get the packet associated to the Sample1 OutComponent */
	pckt = CrFwOutCmpSample1GetPckt(outCmp);

	/* Set up enable, repeat and ready check of sample OutComponent */
	CrFwOutCmpSample1SetEnableFlag(1);
	CrFwOutCmpSample1SetReadyFlag(1);
	CrFwOutCmpSample1SetRepeatFlag(1);

	/* Execute/terminate the sample OutComponent and check it is in PENDING */
	CrFwCmpExecute(outCmp);
	CrFwOutCmpTerminate(outCmp);
	if (!CrFwOutCmpIsInPending(outCmp))
		return 0;

	/* Check that the OutComponent was updated */
	if (pckt[CrFwPcktGetMaxLength()-3] != counter+1)
		return 0;

	/* Execute/terminate the sample OutComponent and check it is still in PENDING */
	CrFwCmpExecute(outCmp);
	CrFwOutCmpTerminate(outCmp);
	if (!CrFwOutCmpIsInPending(outCmp))
		return 0;

	/* Check that the OutComponent was updated */
	if (pckt[CrFwPcktGetMaxLength()-3] != counter+2)
		return 0;

	/* Set up repeat check of sample OutComponent to return "no repeat" */
	CrFwOutCmpSample1SetRepeatFlag(0);

	/* Execute/terminate the sample OutComponent and check it is still in TERMINATED */
	CrFwCmpExecute(outCmp);
	CrFwOutCmpTerminate(outCmp);
	if (!CrFwOutCmpIsInTerminated(outCmp))
		return 0;

	/* Check that the OutComponent was updated */
	if (pckt[CrFwPcktGetMaxLength()-3] != counter+3)
		return 0;

	/* Reset the OutStream (this will also release the OutComponent packet) */
	CrFwCmpReset(CrFwOutStreamGet(dest));

	/* Release the OutComponent */
	CrFwOutFactoryReleaseOutCmp(outCmp);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutCmpTestCase8() {
	FwSmDesc_t outFactory, outCmp;
	CrFwDestSrc_t dest;
	unsigned char counter = 22;

	/* Reset error reporting interface */
	CrFwRepErrStubReset();

	/* Set destination to an invalid value */
	dest = 100;

	/* Instantiate the OutFactory */
	outFactory = CrFwOutFactoryMake();

	/* Initialize and Configure OutFactory and check success */
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Allocate a Sample 1 OutComponent instance */
	outCmp = CrFwOutFactoryMakeOutCmp(50,1,0,0);
	if (!CrFwOutCmpIsInLoaded(outCmp))
		return 0;

	/* Set destination of OutComponent */
	CrFwOutCmpSetDest(outCmp, dest);

	/* Set Sample1 Counter */
	CrFwOutCmpSample1SetCounter(counter);

	/* Set up enable, repeat and ready check of sample OutComponent */
	CrFwOutCmpSample1SetEnableFlag(1);
	CrFwOutCmpSample1SetReadyFlag(1);
	CrFwOutCmpSample1SetRepeatFlag(1);

	/* Execute/terminate the sample OutComponent and check it is in TERMINATED */
	CrFwCmpExecute(outCmp);
	CrFwOutCmpTerminate(outCmp);
	if (!CrFwOutCmpIsInTerminated(outCmp))
		return 0;

	/* Reset and reconfigure sample OutComponent */
	CrFwCmpReset(outCmp);
	if (!CrFwOutCmpIsInLoaded(outCmp))
		return 0;
	CrFwOutCmpSample1SetEnableFlag(1);
	CrFwOutCmpSample1SetReadyFlag(0);
	CrFwOutCmpSample1SetRepeatFlag(1);

	/* Execute/terminate the sample OutComponent twice and check it remains in PENDING */
	CrFwCmpExecute(outCmp);
	CrFwOutCmpTerminate(outCmp);
	CrFwCmpExecute(outCmp);
	CrFwOutCmpTerminate(outCmp);
	if (!CrFwOutCmpIsInPending(outCmp))
		return 0;

	/* Reconfigure sample OutComponent to be ready */
	CrFwOutCmpSample1SetReadyFlag(1);

	/* Execute/terminate the sample OutComponent and check it is in TERMINATED */
	CrFwCmpExecute(outCmp);
	CrFwOutCmpTerminate(outCmp);
	if (!CrFwOutCmpIsInTerminated(outCmp))
		return 0;

	/* Release the OutComponent */
	CrFwOutFactoryReleaseOutCmp(outCmp);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check and reset application error code */
	if (CrFwGetAppErrCode() != crOutStreamUndefDest)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutCmpTestCase9() {
	FwSmDesc_t outFactory, outCmp;
	CrFwDestSrc_t dest;
	unsigned char counter = 22;

	/* Reset error reporting interface */
	CrFwRepErrStubReset();

	/* Start, initialize and reset OutStream to which OutComponent will be sent (just to clear effect of previous tests) */
	dest = 2;
	FwSmStart(CrFwOutStreamGet(dest));
	CrFwCmpInit(CrFwOutStreamGet(dest));
	CrFwCmpReset(CrFwOutStreamGet(dest));
	if (!CrFwCmpIsInConfigured(CrFwOutStreamGet(dest)))
		return 0;

	/* Instantiate the OutFactory */
	outFactory = CrFwOutFactoryMake();

	/* Initialize and Configure OutFactory and check success */
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Allocate a Sample 1 OutComponent instance */
	outCmp = CrFwOutFactoryMakeOutCmp(50,1,0,0);
	if (!CrFwOutCmpIsInLoaded(outCmp))
		return 0;

	/* Set destination of OutComponent */
	CrFwOutCmpSetDest(outCmp, dest);

	/* Set Sample1 Counter */
	CrFwOutCmpSample1SetCounter(counter);

	/* Set up enable, repeat and ready check of sample OutComponent */
	CrFwOutCmpSample1SetEnableFlag(1);
	CrFwOutCmpSample1SetReadyFlag(0);
	CrFwOutCmpSample1SetRepeatFlag(1);

	/* Execute/terminate the sample OutComponent and check it is in PENDING */
	CrFwCmpExecute(outCmp);
	CrFwOutCmpTerminate(outCmp);
	if (!CrFwOutCmpIsInPending(outCmp))
		return 0;

	/* Set up enable, repeat and ready check of sample OutComponent */
	CrFwOutCmpSample1SetEnableFlag(0);
	CrFwOutCmpSample1SetReadyFlag(0);
	CrFwOutCmpSample1SetRepeatFlag(1);

	/* Execute/terminate the sample OutComponent and check it is in ABORTED */
	CrFwCmpExecute(outCmp);
	CrFwOutCmpTerminate(outCmp);
	if (!CrFwOutCmpIsInAborted(outCmp))
		return 0;

	/* Reset and reconfigure sample OutComponent */
	CrFwCmpReset(outCmp);
	if (!CrFwOutCmpIsInLoaded(outCmp))
		return 0;
	CrFwOutCmpSample1SetEnableFlag(1);
	CrFwOutCmpSample1SetReadyFlag(0);
	CrFwOutCmpSample1SetRepeatFlag(1);

	/* Execute/terminate the sample OutComponent and check it is in PENDING */
	CrFwCmpExecute(outCmp);
	CrFwOutCmpTerminate(outCmp);
	if (!CrFwOutCmpIsInPending(outCmp))
		return 0;

	/* Set up enable, repeat and ready check of sample OutComponent */
	CrFwOutCmpSample1SetEnableFlag(0);
	CrFwOutCmpSample1SetReadyFlag(1);
	CrFwOutCmpSample1SetRepeatFlag(1);

	/* Execute/terminate the sample OutComponent and check it is in ABORTED */
	CrFwCmpExecute(outCmp);
	CrFwOutCmpTerminate(outCmp);
	if (!CrFwOutCmpIsInAborted(outCmp))
		return 0;

	/* Release the OutComponent */
	CrFwOutFactoryReleaseOutCmp(outCmp);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}
