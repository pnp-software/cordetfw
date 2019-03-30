/**
 * @file
 *
 * Implementation of test cases for InCommand component.
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
#include "CrFwInCmdTestCases.h"
#include "CrFwRepInCmdOutcomeStub.h"
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
#include "InCmd/CrFwInCmd.h"
#include "InFactory/CrFwInFactory.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include configuration files */
#include "CrFwRepErrStub.h"
#include "CrFwInFactoryUserPar.h"
#include "CrFwCmpData.h"

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInCmdTestCase1() {
	FwSmDesc_t inFactory, inCmd1, inCmd2;
	CrFwPckt_t pckt1, pckt2;
	CrFwInCmdData_t* inCmdSpecificData;
	CrFwCmpData_t* inCmdData;
	CrFwCrc_t crc;

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();

	/* Initialize and Configure InFactory and check success */
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate two InCommands of which one has the correct CRC and one the incorrect CRC */
	pckt1 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt1,8);
	CrFwPcktSetServSubType(pckt1,1);
	CrFwPcktSetDiscriminant(pckt1,2);
	CrFwPcktSetCmdRepId(pckt1,111);
	CrFwPcktSetSrc(pckt1,11);
	CrFwPcktSetGroup(pckt1,88);
	CrFwPcktSetAckLevel(pckt1,1,0,1,0);
	CrFwPcktSetSeqCnt(pckt1,1111);
	crc = CrFwPcktComputeCrc(pckt1);
	CrFwPcktSetCrc(pckt1, crc);
	inCmd1 = CrFwInFactoryMakeInCmd(pckt1);

	pckt2 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt2,8);
	CrFwPcktSetServSubType(pckt2,1);
	CrFwPcktSetDiscriminant(pckt2,1);
	CrFwPcktSetCmdRepId(pckt2,222);
	CrFwPcktSetSrc(pckt2,22);
	CrFwPcktSetGroup(pckt2,89);
	CrFwPcktSetAckLevel(pckt2,0,1,0,1);
	CrFwPcktSetSeqCnt(pckt2,2222);
    crc = CrFwPcktComputeCrc(pckt2);
    CrFwPcktSetCrc(pckt2, crc-1);               /* pckt2 has an incorrect CRC */
	inCmd2 = CrFwInFactoryMakeInCmd(pckt2);

	/* Check the instance identifiers and the type identifier */
	if (CrFwCmpGetInstanceId(inCmd1) != 111)
		return 0;
	if (CrFwCmpGetInstanceId(inCmd2) != 222)
		return 0;
	if (CrFwCmpGetTypeId(inCmd1) != CR_FW_INCOMMAND_TYPE)
		return 0;
	if (CrFwCmpGetTypeId(inCmd2) != CR_FW_INCOMMAND_TYPE)
		return 0;

	/* Check correct configuration */
	if (FwSmCheck(inCmd1) != 1)
		return 0;
	if (FwSmCheck(inCmd2) != 1)
		return 0;

	/* Check InCommand state */
	if (!CrFwCmpIsInConfigured(inCmd1))
		return 0;
	if (!CrFwInCmdIsInAccepted(inCmd1))
		return 0;
    if (CrFwCmpIsInConfigured(inCmd2))      /* Cmd2 has an incorrect CRC */
        return 0;

	/* Check the parameter area */
	inCmdData = (CrFwCmpData_t*)FwSmGetData(inCmd1);
	inCmdSpecificData = (CrFwInCmdData_t*)inCmdData->cmpSpecificData;
	if (CrFwInCmdGetParLength(inCmd1) != CrFwPcktGetParLength(inCmdSpecificData->pckt))
		return 0;
	if (CrFwInCmdGetParStart(inCmd1) != CrFwPcktGetParStart(inCmdSpecificData->pckt))
		return 0;

	/* Check type, sub-type and discriminant */
	if (CrFwInCmdGetServType(inCmd1) != 8)
		return 0;
	if (CrFwInCmdGetServType(inCmd2) != 8)
		return 0;

	if (CrFwInCmdGetServSubType(inCmd1) != 1)
		return 0;
	if (CrFwInCmdGetServSubType(inCmd2) != 1)
		return 0;

	if (CrFwInCmdGetDiscriminant(inCmd1) != 2)
		return 0;
	if (CrFwInCmdGetDiscriminant(inCmd2) != 1)
		return 0;

	/* Check source and sequence counter*/
	if (CrFwInCmdGetSrc(inCmd1) != 11)
		return 0;
	if (CrFwInCmdGetSrc(inCmd2) != 22)
		return 0;
	if (CrFwInCmdGetSeqCnt(inCmd1) != 1111)
		return 0;
	if (CrFwInCmdGetSeqCnt(inCmd2) != 2222)
		return 0;
	if (CrFwInCmdGetGroup(inCmd1) != 88)
		return 0;
	if (CrFwInCmdGetGroup(inCmd2) != 89)
		return 0;

	/* Check acknowledge level set and read-back */
	if (CrFwInCmdIsAcceptAck(inCmd1) != 1)
		return 0;
	if (CrFwInCmdIsStartAck(inCmd1) != 0)
		return 0;
	if (CrFwInCmdIsProgressAck(inCmd1) != 1)
		return 0;
	if (CrFwInCmdIsTermAck(inCmd1) != 0)
		return 0;

	if (CrFwInCmdIsAcceptAck(inCmd2) != 0)
		return 0;
	if (CrFwInCmdIsStartAck(inCmd2) != 1)
		return 0;
	if (CrFwInCmdIsProgressAck(inCmd2) != 0)
		return 0;
	if (CrFwInCmdIsTermAck(inCmd2) != 1)
		return 0;

	/* Check progress step */
	if (CrFwInCmdGetProgressStepId(inCmd1) != 0)
		return 0;
	if (CrFwInCmdGetProgressStepId(inCmd2) != 0)
		return 0;

	/* Check default completion status */
	if (CrFwInCmdIsProgressActionCompleted(inCmd1) != 1)
	    return 0;
    if (CrFwInCmdIsProgressActionCompleted(inCmd2) != 1)
        return 0;

	/* Retrieve and check the packet holding the InCommand */
	if (CrFwInCmdGetPckt(inCmd1)!=pckt1)
		return 0;
	if (CrFwInCmdGetPckt(inCmd2)!=pckt2)
		return 0;

	/* Release the InCommands */
	CrFwInFactoryReleaseInCmd(inCmd1);
	CrFwInFactoryReleaseInCmd(inCmd2);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInCmdTestCase2() {
	FwSmDesc_t inFactory, inCmd;
	CrFwPckt_t pckt;
	CrFwCounterU1_t prgCnt, strCnt;

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();

	/* Initialize and Configure InFactory and check success */
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate the Sample1 InCommand */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwInCmdSample1SetValidityFlag(1);
	strCnt = CrFwInCmdSample1GetStartActionCounter();
	inCmd = CrFwInFactoryMakeInCmd(pckt);

	/* Check InCommand state */
	if (!CrFwCmpIsInConfigured(inCmd))
		return 0;
	if (!CrFwInCmdIsInAccepted(inCmd))
		return 0;

	/* Configure Ready Check to return "not ready" */
	CrFwInCmdSample1SetReadyFlag(0);

	/* Execute InCommand and check that it remains in ACCEPTED */
	CrFwCmpExecute(inCmd);
	if (!CrFwInCmdIsInAccepted(inCmd))
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt)
		return 0;

	/* Check that the command type set in the validity check is correct */
	if (CrFwInCmdSample1GetType() != 50)
	    return 0;

	/* Configure Ready Check to return "ready" */
	CrFwInCmdSample1SetReadyFlag(1);

	/* Configure Start Action to have "success" outcome */
	CrFwInCmdSample1SetStartActionOutcome(1);

	/* Execute InCommand and check that it enters PROGRESS */
	prgCnt = CrFwInCmdSample1GetProgressActionCounter();
	CrFwCmpExecute(inCmd);
	if (!CrFwInCmdIsInProgress(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+1)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;

	/* Release the InCommands */
	CrFwInFactoryReleaseInCmd(inCmd);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInCmdTestCase3() {
	FwSmDesc_t inFactory, inCmd;
	CrFwPckt_t pckt;
	CrFwCounterU1_t abrCnt;
	CrFwCounterU2_t cmdRepPos;

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();

	/* Initialize and Configure InFactory and check success */
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate the Sample1 InCommand */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwInCmdSample1SetValidityFlag(1);
	inCmd = CrFwInFactoryMakeInCmd(pckt);
	cmdRepPos = CrFwRepInCmdOutcomeStubGetPos();

	/* Check InCommand state */
	if (!CrFwCmpIsInConfigured(inCmd))
		return 0;
	if (!CrFwInCmdIsInAccepted(inCmd))
		return 0;

	/* Configure Ready Check to return "ready" */
	CrFwInCmdSample1SetReadyFlag(1);

	/* Configure Start Action to have "failed" outcome */
	CrFwInCmdSample1SetStartActionOutcome(11);

	/* Execute InCommand and check that it enters ABORTED */
	abrCnt = CrFwInCmdSample1GetAbortActionCounter();
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos)
		return 0;
	CrFwCmpExecute(inCmd);
	if (!CrFwInCmdIsInAborted(inCmd))
		return 0;
	if (CrFwInCmdSample1GetAbortActionCounter() != abrCnt+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetOutcome(cmdRepPos) != crCmdAckStrFail)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetFailCode(cmdRepPos) != 11)
		return 0;

	/* Execute InCommand again and check that it stays in ABORTED */
	CrFwCmpExecute(inCmd);
	if (!CrFwInCmdIsInAborted(inCmd))
		return 0;
	if (CrFwInCmdSample1GetAbortActionCounter() != abrCnt+1)
		return 0;

	/* Release the InCommands */
	CrFwInFactoryReleaseInCmd(inCmd);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInCmdTestCase4() {
	FwSmDesc_t inFactory, inCmd;
	CrFwPckt_t pckt;

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();

	/* Initialize and Configure InFactory and check success */
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate the Sample1 InCommand */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwInCmdSample1SetValidityFlag(0);	/* Validity Check will fail */
	inCmd = CrFwInFactoryMakeInCmd(pckt);

  	/* Check InCommand state */
	if (!CrFwCmpIsInInitialized(inCmd))
		return 0;

	/* Release the InCommands */
	CrFwInFactoryReleaseInCmd(inCmd);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInCmdTestCase5() {
	FwSmDesc_t inFactory, inCmd;
	CrFwPckt_t pckt;
	CrFwCounterU1_t prgCnt, strCnt;
	CrFwCounterU2_t cmdRepPos;

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();

	/* Initialize and Configure InFactory and check success */
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate and configure the Sample1 InCommand */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwPcktSetAckLevel(pckt, 0, 0, 0, 0);			/* No acknowledgement of success */
	CrFwInCmdSample1SetValidityFlag(1);				/* Validity Check returns "valid" */
	CrFwInCmdSample1SetProgressActionCompletionOutcome(0);	/* Completion Outcome is "not completed" */
	CrFwInCmdSample1SetProgressActionOutcome(1);    /* Progress action outcome is "success" */
	CrFwInCmdSample1SetReadyFlag(1);				/* Outcome of Ready Check is "ready" */
	CrFwInCmdSample1SetStartActionOutcome(1);		/* Outcome of Start Action is "success" */
	strCnt = CrFwInCmdSample1GetStartActionCounter();
	inCmd = CrFwInFactoryMakeInCmd(pckt);
	cmdRepPos = CrFwRepInCmdOutcomeStubGetPos();
	prgCnt = CrFwInCmdSample1GetProgressActionCounter();

	/* Check that InCommand is correctly configured */
	if (FwSmCheck(inCmd) != smSuccess)
	    return 0;

	/* Check InCommand state */
	if (!CrFwCmpIsInConfigured(inCmd))
		return 0;
	if (!CrFwInCmdIsInAccepted(inCmd))
		return 0;

	/* Execute InCommand and check that it enters PROGRESS */
	CrFwCmpExecute(inCmd);
	if (!CrFwInCmdIsInProgress(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+1)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos)
		return 0;

	/* Execute InCommand again and check that it stays in PROGRESS */
	CrFwCmpExecute(inCmd);
	if (!CrFwInCmdIsInProgress(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+2)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos)
		return 0;

	/* Send command Terminate to InCommand and check that it is ignored */
	CrFwInCmdTerminate(inCmd);
	if (!CrFwInCmdIsInProgress(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+2)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos)
		return 0;

	/* Release the InCommands */
	CrFwInFactoryReleaseInCmd(inCmd);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInCmdTestCase6() {
	FwSmDesc_t inFactory, inCmd;
	CrFwPckt_t pckt;
	CrFwCounterU1_t prgCnt, strCnt, terCnt;
	CrFwCounterU2_t cmdRepPos;

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();

	/* Initialize and Configure InFactory and check success */
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate and configure the Sample1 InCommand */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwPcktSetAckLevel(pckt, 0, 0, 0, 0);			/* No acknowledgement of success */
	CrFwInCmdSample1SetValidityFlag(1);				/* Validity Check returns "valid" */
    CrFwInCmdSample1SetProgressActionCompletionOutcome(0);  /* Completion Outcome is "not completed" */
    CrFwInCmdSample1SetProgressActionOutcome(1);    /* Progress action outcome is "success" */
	CrFwInCmdSample1SetReadyFlag(1);				/* Outcome of Ready Check is "ready" */
	CrFwInCmdSample1SetStartActionOutcome(1);		/* Outcome of Start Action is "success" */
	CrFwInCmdSample1SetTerminationActionOutcome(1);	/* Outcome of Termination Action is "success" */
	strCnt = CrFwInCmdSample1GetStartActionCounter();
	inCmd = CrFwInFactoryMakeInCmd(pckt);
	cmdRepPos = CrFwRepInCmdOutcomeStubGetPos();
	prgCnt = CrFwInCmdSample1GetProgressActionCounter();
	terCnt = CrFwInCmdSample1GetTerminationActionCounter();

	/* Check InCommand state */
	if (!CrFwCmpIsInConfigured(inCmd))
		return 0;
	if (!CrFwInCmdIsInAccepted(inCmd))
		return 0;

	/* Execute InCommand and check that it enters PROGRESS */
	CrFwCmpExecute(inCmd);
	if (!CrFwInCmdIsInProgress(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+1)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos)
		return 0;

	/* Configure Progress Action to return "completed" */
	if (CrFwInCmdSample1GetTerminationActionCounter() != terCnt)
		return 0;
	CrFwInCmdSample1SetProgressActionCompletionOutcome(1);	/* Completion outcome of Progress Action is "completed" */

	/* Execute InCommand again and check that it stays in PROGRESS */
	CrFwCmpExecute(inCmd);
	if (!CrFwInCmdIsInProgress(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+2)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos)
		return 0;

	/* Send command Terminate to InCommand and check that TERMINATED is entered */
	CrFwInCmdTerminate(inCmd);
	if (!CrFwInCmdIsInTerminated(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+2)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwInCmdSample1GetTerminationActionCounter() != terCnt+1)
		return 0;
	if (CrFwInCmdGetNOfProgressFailure(inCmd) != 0)
	    return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos)
		return 0;

	/* Check progress step */
	if (CrFwInCmdGetProgressStepId(inCmd) != 0)
		return 0;

	/* Release the InCommands */
	CrFwInFactoryReleaseInCmd(inCmd);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInCmdTestCase7() {
	FwSmDesc_t inFactory, inCmd;
	CrFwPckt_t pckt;
	CrFwCounterU1_t prgCnt, strCnt, terCnt, abrCnt;
	CrFwCounterU2_t cmdRepPos;

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();

	/* Initialize and Configure InFactory and check success */
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate and configure the Sample1 InCommand */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwPcktSetAckLevel(pckt, 0, 0, 0, 0);			/* No acknowledgement of success */
	CrFwInCmdSample1SetValidityFlag(1);				/* Validity Check returns "valid" */
    CrFwInCmdSample1SetProgressActionCompletionOutcome(0);  /* Completion Outcome is "not completed" */
    CrFwInCmdSample1SetProgressActionOutcome(22);   /* Progress action outcome is "failed" */
	CrFwInCmdSample1SetReadyFlag(1);				/* Outcome of Ready Check is "ready" */
	CrFwInCmdSample1SetStartActionOutcome(1);		/* Outcome of Start Action is "success" */
	CrFwInCmdSample1SetTerminationActionOutcome(10);/* Outcome of Termination Action is "failed" */
	strCnt = CrFwInCmdSample1GetStartActionCounter();
	inCmd = CrFwInFactoryMakeInCmd(pckt);
	cmdRepPos = CrFwRepInCmdOutcomeStubGetPos();
	prgCnt = CrFwInCmdSample1GetProgressActionCounter();
	terCnt = CrFwInCmdSample1GetTerminationActionCounter();
	abrCnt = CrFwInCmdSample1GetAbortActionCounter();

	/* Check InCommand state */
	if (!CrFwCmpIsInConfigured(inCmd))
		return 0;
	if (!CrFwInCmdIsInAccepted(inCmd))
		return 0;

	/* Execute InCommand and check that it enters PROGRESS */
	CrFwCmpExecute(inCmd);
	if (!CrFwInCmdIsInProgress(inCmd))
		return 0;
	if (CrFwGetSmOutcome(inCmd) != 22)
	    return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+1)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwInCmdGetNOfProgressFailure(inCmd) != 1)
	    return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos+1)
		return 0;
    if (CrFwRepInCmdOutcomeStubGetOutcome(cmdRepPos) != crCmdAckPrgFail)
        return 0;
    if (CrFwRepInCmdOutcomeStubGetFailCode(cmdRepPos) != 22)
        return 0;
    if (CrFwInCmdSample1GetTerminationActionCounter() != terCnt)
        return 0;

	/* Configure Progress Action to return "success" */
	CrFwInCmdSample1SetProgressActionOutcome(1);

	/* Execute InCommand again and check that it stays in PROGRESS */
	CrFwCmpExecute(inCmd);
	if (!CrFwInCmdIsInProgress(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+2)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwInCmdSample1GetAbortActionCounter() != abrCnt)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos+1)
		return 0;
    if (CrFwInCmdGetNOfProgressFailure(inCmd) != 1)
        return 0;

    /* Configure Progress Action to return "completed" */
    CrFwInCmdSample1SetProgressActionCompletionOutcome(1);

    /* Execute InCommand again and check that it stays in PROGRESS */
    CrFwCmpExecute(inCmd);
    if (!CrFwInCmdIsInProgress(inCmd))
        return 0;
    if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+3)
        return 0;
    if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
        return 0;
    if (CrFwInCmdSample1GetAbortActionCounter() != abrCnt)
        return 0;
    if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos+1)
        return 0;
    if (CrFwInCmdGetNOfProgressFailure(inCmd) != 1)
        return 0;

	/* Send command Terminate to InCommand and check that ABORTED is entered */
	CrFwInCmdTerminate(inCmd);
	if (!CrFwInCmdIsInAborted(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+3)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwInCmdSample1GetTerminationActionCounter() != terCnt+1)
		return 0;
	if (CrFwInCmdSample1GetAbortActionCounter() != abrCnt+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos+2)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetOutcome(cmdRepPos+1) != crCmdAckTrmFail)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetFailCode(cmdRepPos+1) != 10)
		return 0;

	/* Release the InCommands */
	CrFwInFactoryReleaseInCmd(inCmd);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInCmdTestCase8() {
	FwSmDesc_t inFactory, inCmd;
	CrFwPckt_t pckt;
	CrFwCounterU1_t prgCnt, strCnt, terCnt, abrCnt;
	CrFwCounterU2_t cmdRepPos;

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();

	/* Initialize and Configure InFactory and check success */
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate and configure the Sample1 InCommand */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwPcktSetAckLevel(pckt, 0, 0, 0, 0);			/* No acknowledgement of success */
	CrFwInCmdSample1SetValidityFlag(1);				/* Validity Check returns "valid" */
    CrFwInCmdSample1SetProgressActionCompletionOutcome(1);  /* Completion Outcome is "completed" */
    CrFwInCmdSample1SetProgressActionOutcome(1);   /* Progress action outcome is "success" */
	CrFwInCmdSample1SetReadyFlag(1);				/* Outcome of Ready Check is "ready" */
	CrFwInCmdSample1SetStartActionOutcome(1);		/* Outcome of Start Action is "success" */
	CrFwInCmdSample1SetTerminationActionOutcome(33);	/* Outcome of Termination Action is "failed" */
	strCnt = CrFwInCmdSample1GetStartActionCounter();
	inCmd = CrFwInFactoryMakeInCmd(pckt);
	cmdRepPos = CrFwRepInCmdOutcomeStubGetPos();
	prgCnt = CrFwInCmdSample1GetProgressActionCounter();
	terCnt = CrFwInCmdSample1GetTerminationActionCounter();
	abrCnt = CrFwInCmdSample1GetAbortActionCounter();

	/* Check InCommand state */
	if (!CrFwCmpIsInConfigured(inCmd))
		return 0;
	if (!CrFwInCmdIsInAccepted(inCmd))
		return 0;

	/* Execute InCommand and check that it enters PROGRESS */
	CrFwCmpExecute(inCmd);
	if (!CrFwInCmdIsInProgress(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+1)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos)
		return 0;

	/* Send command Terminate to InCommand and check that ABORTED is entered */
	CrFwInCmdTerminate(inCmd);
	if (!CrFwInCmdIsInAborted(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+1)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwInCmdSample1GetTerminationActionCounter() != terCnt+1)
		return 0;
	if (CrFwInCmdSample1GetAbortActionCounter() != abrCnt+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetOutcome(cmdRepPos) != crCmdAckTrmFail)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetFailCode(cmdRepPos) != 33)
		return 0;
    if (CrFwInCmdGetNOfProgressFailure(inCmd) != 0)
        return 0;

	/* Release the InCommands */
	CrFwInFactoryReleaseInCmd(inCmd);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInCmdTestCase9() {
	FwSmDesc_t inFactory, inCmd;
	CrFwPckt_t pckt;
	CrFwCounterU1_t prgCnt, strCnt;
	CrFwCounterU2_t cmdRepPos;

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();

	/* Initialize and Configure InFactory and check success */
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate and configure the Sample1 InCommand */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwPcktSetAckLevel(pckt, 0, 1, 0, 0);			/* Only acknowledge Start */
	CrFwInCmdSample1SetValidityFlag(1);				/* Validity Check returns "valid" */
    CrFwInCmdSample1SetProgressActionCompletionOutcome(0);  /* Completion Outcome is "not completed" */
    CrFwInCmdSample1SetProgressActionOutcome(1);   /* Progress action outcome is "success" */
	CrFwInCmdSample1SetReadyFlag(1);				/* Outcome of Ready Check is "ready" */
	CrFwInCmdSample1SetStartActionOutcome(1);		/* Outcome of Start Action is "success" */
	strCnt = CrFwInCmdSample1GetStartActionCounter();
	inCmd = CrFwInFactoryMakeInCmd(pckt);
	cmdRepPos = CrFwRepInCmdOutcomeStubGetPos();
	prgCnt = CrFwInCmdSample1GetProgressActionCounter();

	/* Check InCommand state */
	if (!CrFwCmpIsInConfigured(inCmd))
		return 0;
	if (!CrFwInCmdIsInAccepted(inCmd))
		return 0;

	/* Execute InCommand and check that it enters PROGRESS */
	CrFwCmpExecute(inCmd);
	if (!CrFwInCmdIsInProgress(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+1)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetOutcome(cmdRepPos) != crCmdAckStrSucc)
		return 0;

	/* Release the InCommands */
	CrFwInFactoryReleaseInCmd(inCmd);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInCmdTestCase10() {
	FwSmDesc_t inFactory, inCmd;
	CrFwPckt_t pckt;
	CrFwCounterU1_t prgCnt, strCnt;
	CrFwCounterU2_t cmdRepPos;
	CrFwProgressStepId_t progressStepId;

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();

	/* Initialize and Configure InFactory and check success */
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate and configure the Sample1 InCommand */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwPcktSetAckLevel(pckt, 0, 0, 1, 0);			/* Only acknowledge Progress */
	CrFwInCmdSample1SetValidityFlag(1);				/* Validity Check returns "valid" */
    CrFwInCmdSample1SetProgressActionCompletionOutcome(0);  /* Completion Outcome is "not completed" */
    CrFwInCmdSample1SetProgressActionOutcome(1);   /* Progress action outcome is "success" */
	CrFwInCmdSample1SetReadyFlag(1);				/* Outcome of Ready Check is "ready" */
	CrFwInCmdSample1SetStartActionOutcome(1);		/* Outcome of Start Action is "success" */
	strCnt = CrFwInCmdSample1GetStartActionCounter();
	inCmd = CrFwInFactoryMakeInCmd(pckt);
	cmdRepPos = CrFwRepInCmdOutcomeStubGetPos();
	prgCnt = CrFwInCmdSample1GetProgressActionCounter();
	progressStepId = CrFwInCmdGetProgressStepId(inCmd);
	CrFwInCmdSample1SetProgressStepFlag(0);

	/* Check InCommand state */
	if (!CrFwCmpIsInConfigured(inCmd))
		return 0;
	if (!CrFwInCmdIsInAccepted(inCmd))
		return 0;

	/* Execute InCommand and check that it enters PROGRESS */
	CrFwCmpExecute(inCmd);
	if (!CrFwInCmdIsInProgress(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+1)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos)
		return 0;
    if (CrFwInCmdGetProgressStepId(inCmd) != progressStepId)
        return 0;

	/* Execute InCommand again and check that it remains in PROGRESS */
	CrFwCmpExecute(inCmd);
	if (!CrFwInCmdIsInProgress(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+2)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos)
		return 0;
    if (CrFwInCmdGetProgressStepId(inCmd) != progressStepId)
        return 0;

	/* Reconfigure InCommand to complete a progress step and execute it again */
    CrFwInCmdSample1SetProgressStepFlag(1);
    CrFwCmpExecute(inCmd);
    if (!CrFwInCmdIsInProgress(inCmd))
        return 0;
    if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+3)
        return 0;
    if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
        return 0;
    if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos+1)
        return 0;
    if (CrFwRepInCmdOutcomeStubGetOutcome(cmdRepPos) != crCmdAckPrgSucc)
        return 0;
    if (CrFwInCmdGetProgressStepId(inCmd) != progressStepId+1)
        return 0;

    /* Execute InCommand again and check that it remains in PROGRESS */
    CrFwCmpExecute(inCmd);
    if (!CrFwInCmdIsInProgress(inCmd))
        return 0;
    if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+4)
        return 0;
    if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
        return 0;
    if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos+2)
        return 0;
    if (CrFwInCmdGetProgressStepId(inCmd) != progressStepId+2)
        return 0;

	/* Release the InCommands */
	CrFwInFactoryReleaseInCmd(inCmd);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInCmdTestCase11() {
	FwSmDesc_t inFactory, inCmd;
	CrFwPckt_t pckt;
	CrFwCounterU1_t prgCnt, strCnt, terCnt;
	CrFwCounterU2_t cmdRepPos;

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();

	/* Initialize and Configure InFactory and check success */
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate and configure the Sample1 InCommand */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwPcktSetAckLevel(pckt, 0, 0, 0, 1);			/* Acknowledge only termination */
	CrFwInCmdSample1SetValidityFlag(1);				/* Validity Check returns "valid" */
    CrFwInCmdSample1SetProgressActionCompletionOutcome(1);  /* Completion Outcome is "completed" */
    CrFwInCmdSample1SetProgressActionOutcome(1);   /* Progress action outcome is "success" */
	CrFwInCmdSample1SetReadyFlag(1);				/* Outcome of Ready Check is "ready" */
	CrFwInCmdSample1SetStartActionOutcome(1);		/* Outcome of Start Action is "success" */
	CrFwInCmdSample1SetTerminationActionOutcome(1);	/* Outcome of Termination Action is "success" */
	strCnt = CrFwInCmdSample1GetStartActionCounter();
	inCmd = CrFwInFactoryMakeInCmd(pckt);
	cmdRepPos = CrFwRepInCmdOutcomeStubGetPos();
	prgCnt = CrFwInCmdSample1GetProgressActionCounter();
	terCnt = CrFwInCmdSample1GetTerminationActionCounter();

	/* Check InCommand state */
	if (!CrFwCmpIsInConfigured(inCmd))
		return 0;
	if (!CrFwInCmdIsInAccepted(inCmd))
		return 0;

	/* Execute InCommand and check that it enters PROGRESS */
	CrFwCmpExecute(inCmd);
	if (!CrFwInCmdIsInProgress(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+1)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos)
		return 0;

	/* Configure Progress Action to return "completed" */
	if (CrFwInCmdSample1GetTerminationActionCounter() != terCnt)
		return 0;
	CrFwInCmdSample1SetProgressActionCompletionOutcome(1);	/* Completion Outcome of Progress Action is "completed" */

	/* Execute InCommand again and check that it stays in PROGRESS */
	CrFwCmpExecute(inCmd);
	if (!CrFwInCmdIsInProgress(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+2)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos)
		return 0;

	/* Send command Terminate to InCommand and check that TERMINATED is entered */
	CrFwInCmdTerminate(inCmd);
	if (!CrFwInCmdIsInTerminated(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+2)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwInCmdSample1GetTerminationActionCounter() != terCnt+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != cmdRepPos+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetOutcome(cmdRepPos) != crCmdAckTrmSucc)
		return 0;

	/* Release the InCommands */
	CrFwInFactoryReleaseInCmd(inCmd);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInCmdTestCase12() {
	FwSmDesc_t inFactory, inCmd;
	CrFwPckt_t pckt;
	CrFwCounterU1_t prgCnt, strCnt, terCnt;

	/* Reset the Interface reporting the InCommand outcomes */
	CrFwRepInCmdOutcomeStubReset();

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();

	/* Initialize and Configure InFactory and check success */
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate and configure the Sample1 InCommand */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwPcktSetAckLevel(pckt, 0, 1, 1, 1);			/* Acknowledge start, progress and termination */
	CrFwInCmdSample1SetValidityFlag(1);				/* Validity Check returns "valid" */
    CrFwInCmdSample1SetProgressActionCompletionOutcome(1);  /* Completion Outcome is "completed" */
    CrFwInCmdSample1SetProgressActionOutcome(1);   /* Progress action outcome is "success" */
	CrFwInCmdSample1SetReadyFlag(1);				/* Outcome of Ready Check is "ready" */
	CrFwInCmdSample1SetStartActionOutcome(1);		/* Outcome of Start Action is "success" */
	CrFwInCmdSample1SetTerminationActionOutcome(1);	/* Outcome of Termination Action is "success" */
	strCnt = CrFwInCmdSample1GetStartActionCounter();
	inCmd = CrFwInFactoryMakeInCmd(pckt);
	prgCnt = CrFwInCmdSample1GetProgressActionCounter();
	terCnt = CrFwInCmdSample1GetTerminationActionCounter();
	CrFwInCmdSample1SetProgressStepFlag(1);

	/* Check InCommand state */
	if (!CrFwCmpIsInConfigured(inCmd))
		return 0;
	if (!CrFwInCmdIsInAccepted(inCmd))
		return 0;

	/* Execute InCommand and check that it enters PROGRESS */
	CrFwCmpExecute(inCmd);
	if (!CrFwInCmdIsInProgress(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+1)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != 2)
		return 0;

	/* Send command Terminate to InCommand and check that TERMINATED is entered */
	CrFwInCmdTerminate(inCmd);
	if (!CrFwInCmdIsInTerminated(inCmd))
		return 0;
	if (CrFwInCmdSample1GetProgressActionCounter() != prgCnt+1)
		return 0;
	if (CrFwInCmdSample1GetStartActionCounter() != strCnt+1)
		return 0;
	if (CrFwInCmdSample1GetTerminationActionCounter() != terCnt+1)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetPos() != 3)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetOutcome(0) != crCmdAckStrSucc)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetOutcome(1) != crCmdAckPrgSucc)
		return 0;
	if (CrFwRepInCmdOutcomeStubGetOutcome(2) != crCmdAckTrmSucc)
		return 0;

	/* Check the parameters of the InCommand success reports */
	if (CrFwRepInCmdOutcomeStubGetInstanceId(0) != CrFwCmpGetInstanceId(inCmd))
		return 0;
	if (CrFwRepInCmdOutcomeStubGetServType(0) != CrFwInCmdGetServType(inCmd))
		return 0;
	if (CrFwRepInCmdOutcomeStubGetServSubType(0) != CrFwInCmdGetServSubType(inCmd))
		return 0;
	if (CrFwRepInCmdOutcomeStubGetDiscriminant(0) != CrFwInCmdGetDiscriminant(inCmd))
		return 0;

	/* Release the InCommands */
	CrFwInFactoryReleaseInCmd(inCmd);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}


