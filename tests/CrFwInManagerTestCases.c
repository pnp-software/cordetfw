/**
 * @file
 *
 * Implementation of test cases for InManager component.
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

#include <stdio.h>
#include <stdlib.h>
#include "CrFwInManagerTestCases.h"
#include "CrFwInCmdSample1.h"
#include "CrFwInRepSample1.h"
/* Include FW Profile files */
#include "FwProfile/FwSmConstants.h"
#include "FwProfile/FwSmConfig.h"
#include "FwProfile/FwSmCore.h"
#include "FwProfile/FwPrConfig.h"
#include "FwProfile/FwPrCore.h"
#include "FwProfile/FwPrConstants.h"
/* Include framework files */
#include "InRegistry/CrFwInRegistry.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "InRep/CrFwInRep.h"
#include "InCmd/CrFwInCmd.h"
#include "InFactory/CrFwInFactory.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include configuration files */
#include "CrFwInRegistryUserPar.h"
#include "CrFwInManagerUserPar.h"
#include "CrFwRepErrStub.h"
#include "CrFwOutFactoryUserPar.h"
#include "CrFwCmpData.h"

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInManagerTestCase1() {
	FwSmDesc_t inManager1, inManagerIll;

	/* Instantiate the first InManager */
	inManager1 = CrFwInManagerMake(0);

	/* Check current state of InManager */
	if (!CrFwCmpIsInCreated(inManager1))
		return 0;

	/* Initialize and Configure InManager and check success */
	CrFwCmpInit(inManager1);
	if (!CrFwCmpIsInInitialized(inManager1))
		return 0;
	CrFwCmpReset(inManager1);
	if (!CrFwCmpIsInConfigured(inManager1))
		return 0;

	/* Check Instance and Type Identifiers */
	if (CrFwCmpGetInstanceId(inManager1) != 0)
		return 0;
	if (CrFwCmpGetTypeId(inManager1) != CR_FW_INMANAGER_TYPE)
		return 0;

	/* Check PCRL */
	if (CrFwInManagerGetPCRLSize(inManager1) != 3)
		return 0;
	if (CrFwInManagerGetNOfPendingInCmp(inManager1) != 0)
		return 0;

	/* Check number of loaded InReports/InCommands */
	if (CrFwInManagerGetNOfLoadedInCmp(inManager1) != 0)
		return 0;

	/* Attempt to instantiate an InManager with an illegal identifier */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;
	inManagerIll = CrFwInManagerMake(CR_FW_NOF_INMANAGER);
	if (inManagerIll != NULL)
		return 0;
	if (CrFwGetAppErrCode() != crInManagerIllId)
		return 0;
	CrFwSetAppErrCode(crNoAppErr); 	/* reset application error code */

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInManagerTestCase2() {
	FwSmDesc_t inManager2, inFactory;
	FwSmDesc_t inRep1, inCmd1;
	CrFwPckt_t pckt1, pckt2;
	CrFwCounterU2_t i;
	CrFwCounterU2_t errRepPosLocal;
	CrFwBool_t loadOutcome;

	/* Instantiate the second InManager */
	inManager2 = CrFwInManagerMake(1);

	/* Initialize and Configure InManager and check success */
	CrFwCmpInit(inManager2);
	CrFwCmpReset(inManager2);
	if (!CrFwCmpIsInConfigured(inManager2))
		return 0;

	/* Check Instance Identifiers */
	if (CrFwCmpGetInstanceId(inManager2) != 1)
		return 0;

	/* Initialize and Configure factories and check success */
	inFactory = CrFwInFactoryMake();
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Create and load an InReport and an InCommand */
	pckt1 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt1,5);
	CrFwPcktSetServSubType(pckt1,1);
	CrFwPcktSetDiscriminant(pckt1,1);
	pckt2 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt2,8);
	CrFwPcktSetServSubType(pckt2,1);
	CrFwPcktSetDiscriminant(pckt2,1);
	inRep1 = CrFwInFactoryMakeInRep(pckt1);
	inCmd1 = CrFwInFactoryMakeInCmd(pckt2);

	loadOutcome = CrFwInManagerLoad(inManager2, inRep1);
	if (loadOutcome != 1)
		return 0;
	if (CrFwInManagerGetNOfPendingInCmp(inManager2) != 1)
		return 0;
	if (CrFwInManagerGetNOfLoadedInCmp(inManager2) != 1)
		return 0;

	loadOutcome = CrFwInManagerLoad(inManager2, inCmd1);
	if (loadOutcome != 1)
		return 0;
	if (CrFwInManagerGetNOfPendingInCmp(inManager2) != 2)
		return 0;
	if (CrFwInManagerGetNOfLoadedInCmp(inManager2) != 2)
		return 0;

	/* Fill up the InManager */
	for (i=2; i<CrFwInManagerGetPCRLSize(inManager2); i++) {
		pckt1 = CrFwPcktMake(100);
		CrFwPcktSetServType(pckt1,5);
		CrFwPcktSetServSubType(pckt1,1);
		CrFwPcktSetDiscriminant(pckt1,1);
		inRep1 = CrFwInFactoryMakeInRep(pckt1);
		CrFwInManagerLoad(inManager2, inRep1);
	}

	/* Check number of loaded InReports/InCommands */
	if (CrFwInManagerGetNOfLoadedInCmp(inManager2) != CrFwInManagerGetPCRLSize(inManager2))
		return 0;

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Create one more InCommand and overflow the PCRL */
	pckt1 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt1,8);
	CrFwPcktSetServSubType(pckt1,1);
	CrFwPcktSetDiscriminant(pckt1,1);
	inCmd1 = CrFwInFactoryMakeInCmd(pckt1);
	loadOutcome = CrFwInManagerLoad(inManager2, inCmd1);
	if (loadOutcome != 0)
		return 0;

	/* Check number of loaded InReports/InCommands */
	if (CrFwInManagerGetNOfLoadedInCmp(inManager2) != CrFwInManagerGetPCRLSize(inManager2))
		return 0;

	/* Check that an error report has been generated */
	if (CrFwRepErrStubGetPos() != errRepPosLocal+1)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crInManagerPcrlFull)
		return 0;
	if (CrFwRepErrStubGetTypeId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != CR_FW_INMANAGER_TYPE)
		return 0;
	if (CrFwRepErrStubGetInstanceId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != 1)
		return 0;

	/* Reset the InManager (this should clear the PCRL and release all loaded components) */
	CrFwCmpReset(inManager2);
	if (!CrFwCmpIsInConfigured(inManager2))
		return 0;
	if (CrFwInManagerGetNOfPendingInCmp(inManager2) != 0)
		return 0;
	if (CrFwPcktGetNOfAllocated() != 1)
		return 0;
	if (CrFwInManagerGetNOfLoadedInCmp(inManager2) != 0)
		return 0;

	/* Release the last InCommand */
	CrFwInFactoryReleaseInCmd(inCmd1);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInManagerTestCase3() {
	FwSmDesc_t inManager1, inRegistry, inFactory;
	FwSmDesc_t sampleInRep;
	FwSmCounterU3_t execCnt;
	CrFwPckt_t pckt;

	/* Instantiate the first InManager */
	inManager1 = CrFwInManagerMake(0);

	/* Initialize and Configure InManager and check success */
	CrFwCmpInit(inManager1);
	CrFwCmpReset(inManager1);
	if (!CrFwCmpIsInConfigured(inManager1))
		return 0;

	/* Initialize and Configure InRegistry and check success */
	inRegistry = CrFwInRegistryMake();
	CrFwCmpInit(inRegistry);
	CrFwCmpReset(inRegistry);
	if (!CrFwCmpIsInConfigured(inRegistry))
		return 0;

	/* Execute the empty InManager */
	CrFwCmpExecute(inManager1);
	CrFwCmpExecute(inManager1);

	/* Initialize and Configure InFactory and check success */
	inFactory = CrFwInFactoryMake();
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate a Sample 1 InReport instance */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,40);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwInRepSample1SetValidityFlag(1);	/* Validity Check will succeed */
	sampleInRep = CrFwInFactoryMakeInRep(pckt);

	/* Load Sample InCommand in InManager */
	CrFwInManagerLoad(inManager1, sampleInRep);
	if (CrFwInManagerGetNOfPendingInCmp(inManager1) != 1)
		return 0;

	/* Store execution counter of Sample InCommand */
	execCnt = FwSmGetExecCnt(sampleInRep);

	/* Execute the InManager */
	CrFwCmpExecute(inManager1);	/* this causes the Sample InReport to terminate */
	CrFwCmpExecute(inManager1);

	/* Check that execution was propagated to Sample InReport */
	if (FwSmGetExecCnt(sampleInRep) !=  execCnt+1)
		return 0;
	if (CrFwInManagerGetNOfPendingInCmp(inManager1) != 0)
		return 0;
	if (CrFwInRegistryGetState(CrFwCmpGetInstanceId(sampleInRep)) != crInRegistryTerminated)
		return 0;

	/* Check that Sample InReport was released by InManager */
	if (CrFwInFactoryGetNOfAllocatedInRep() != 0)
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
CrFwBool_t CrFwInManagerTestCase4() {
	FwSmDesc_t inManager1, inRegistry, inFactory;
	FwSmDesc_t sampleInCmd;
	FwSmCounterU3_t execCnt;
	CrFwPckt_t pckt;

	/* Instantiate the first InManager */
	inManager1 = CrFwInManagerMake(0);

	/* Initialize and Configure InManager and check success */
	CrFwCmpInit(inManager1);
	CrFwCmpReset(inManager1);
	if (!CrFwCmpIsInConfigured(inManager1))
		return 0;

	/* Initialize and Configure InRegistry and check success */
	inRegistry = CrFwInRegistryMake();
	CrFwCmpInit(inRegistry);
	CrFwCmpReset(inRegistry);
	if (!CrFwCmpIsInConfigured(inRegistry))
		return 0;

	/* Execute the empty InManager */
	CrFwCmpExecute(inManager1);
	CrFwCmpExecute(inManager1);

	/* Initialize and Configure InFactory and check success */
	inFactory = CrFwInFactoryMake();
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate a Sample 1 InCommand instance and configure it to remain pending*/
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwPcktSetAckLevel(pckt, 0, 0, 0, 0);			/* No acknowledgement of success */
	CrFwInCmdSample1SetValidityFlag(1);				/* Validity Check returns "valid" */
	CrFwInCmdSample1SetProgressActionOutcome(2);	/* Outcome of Progress Action is "continue" */
	CrFwInCmdSample1SetReadyFlag(1);				/* Outcome of Ready Check is "ready" */
	CrFwInCmdSample1SetStartActionOutcome(1);		/* Outcome of Start Action is "success" */
	CrFwInCmdSample1SetTerminationActionOutcome(1);	/* Outcome of Termination Action is "success" */
	sampleInCmd = CrFwInFactoryMakeInCmd(pckt);

	/* Load Sample InCommand in InManager */
	CrFwInManagerLoad(inManager1, sampleInCmd);
	if (CrFwInManagerGetNOfPendingInCmp(inManager1) != 1)
		return 0;

	/* Store execution counter of Sample InCommand */
	execCnt = FwSmGetExecCnt(sampleInCmd);

	/* Execute the InManager */
	CrFwCmpExecute(inManager1);	/* this causes the Sample InCommand to enter PROGRESS */
	CrFwCmpExecute(inManager1);

	/* Check that execution was propagated to Sample InCommand */
	if (FwSmGetExecCnt(sampleInCmd) !=  execCnt+2)
		return 0;
	if (!CrFwInCmdIsInProgress(sampleInCmd))
		return 0;
	if (CrFwInManagerGetNOfPendingInCmp(inManager1) != 1)
		return 0;
	if (CrFwInRegistryGetState(CrFwCmpGetInstanceId(sampleInCmd)) != crInRegistryPending)
		return 0;

	/* Configure InCommand to terminate */
	CrFwInCmdSample1SetProgressActionOutcome(1);	/* Outcome of Progress Action is "terminate" */

	/* Execute the InManager */
	CrFwCmpExecute(inManager1);	/* this causes the Sample InCommand to enter TERMINATE */
	CrFwCmpExecute(inManager1);

	/* Check that execution was propagated to Sample InCommand */
	if (FwSmGetExecCnt(sampleInCmd) !=  execCnt+3)
		return 0;
	if (!CrFwInCmdIsInTerminated(sampleInCmd))
		return 0;
	if (CrFwInManagerGetNOfPendingInCmp(inManager1) != 0)
		return 0;
	if (CrFwInRegistryGetState(CrFwCmpGetInstanceId(sampleInCmd)) != crInRegistryTerminated)
		return 0;

	/* Check that Sample InCommand was released by InManager */
	if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
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
CrFwBool_t CrFwInManagerTestCase5() {
	FwSmDesc_t inManager1, inRegistry, inFactory;
	FwSmDesc_t sampleInCmd;
	FwSmCounterU3_t execCnt;
	CrFwPckt_t pckt;

	/* Instantiate the first InManager */
	inManager1 = CrFwInManagerMake(0);

	/* Initialize and Configure InManager and check success */
	CrFwCmpInit(inManager1);
	CrFwCmpReset(inManager1);
	if (!CrFwCmpIsInConfigured(inManager1))
		return 0;

	/* Initialize and Configure InRegistry and check success */
	inRegistry = CrFwInRegistryMake();
	CrFwCmpInit(inRegistry);
	CrFwCmpReset(inRegistry);
	if (!CrFwCmpIsInConfigured(inRegistry))
		return 0;

	/* Execute the empty InManager */
	CrFwCmpExecute(inManager1);
	CrFwCmpExecute(inManager1);

	/* Initialize and Configure InFactory and check success */
	inFactory = CrFwInFactoryMake();
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate a Sample 1 InCommand instance and configure it to be aborted */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwPcktSetAckLevel(pckt, 0, 0, 0, 0);			/* No acknowledgement of success */
	CrFwInCmdSample1SetValidityFlag(1);				/* Validity Check returns "valid" */
	CrFwInCmdSample1SetProgressActionOutcome(2);	/* Outcome of Progress Action is "continue" */
	CrFwInCmdSample1SetReadyFlag(1);				/* Outcome of Ready Check is "ready" */
	CrFwInCmdSample1SetStartActionOutcome(0);		/* Outcome of Start Action is "failed" */
	CrFwInCmdSample1SetTerminationActionOutcome(1);	/* Outcome of Termination Action is "success" */
	sampleInCmd = CrFwInFactoryMakeInCmd(pckt);

	/* Load Sample InCommand in InManager */
	CrFwInManagerLoad(inManager1, sampleInCmd);
	if (CrFwInManagerGetNOfPendingInCmp(inManager1) != 1)
		return 0;

	/* Store execution counter of Sample InCommand */
	execCnt = FwSmGetExecCnt(sampleInCmd);

	/* Execute the InManager */
	CrFwCmpExecute(inManager1);	/* this causes the Sample InCommand to enter ABORTED */
	CrFwCmpExecute(inManager1);

	/* Check that execution was propagated to Sample InCommand */
	if (FwSmGetExecCnt(sampleInCmd) !=  execCnt+1)
		return 0;
	if (!CrFwInCmdIsInAborted(sampleInCmd))
		return 0;
	if (CrFwInManagerGetNOfPendingInCmp(inManager1) != 0)
		return 0;
	if (CrFwInRegistryGetState(CrFwCmpGetInstanceId(sampleInCmd)) != crInRegistryAborted)
		return 0;

	/* Check that Sample InCommand was released by InManager */
	if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
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
CrFwBool_t CrFwInManagerTestCase6() {
	FwSmDesc_t inManager2, inRegistry, inFactory;
	FwSmDesc_t sampleInCmd1, sampleInCmd2, inRep1, inRep2;
	CrFwPckt_t pckt;

	/* Instantiate an InManager */
	inManager2 = CrFwInManagerMake(1);

	/* Initialize and Configure InManager and check success */
	CrFwCmpInit(inManager2);
	CrFwCmpReset(inManager2);
	if (!CrFwCmpIsInConfigured(inManager2))
		return 0;

	/* Initialize and Configure InRegistry and check success */
	inRegistry = CrFwInRegistryMake();
	CrFwCmpInit(inRegistry);
	CrFwCmpReset(inRegistry);
	if (!CrFwCmpIsInConfigured(inRegistry))
		return 0;

	/* Initialize and Configure InFactory and check success */
	inFactory = CrFwInFactoryMake();
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate Sample 1 InCommand instances and configure them to remain pending */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwPcktSetAckLevel(pckt, 0, 0, 0, 0);			/* No acknowledgement of success */
	CrFwInCmdSample1SetValidityFlag(1);				/* Validity Check returns "valid" */
	CrFwInCmdSample1SetProgressActionOutcome(2);	/* Outcome of Progress Action is "continue" */
	CrFwInCmdSample1SetReadyFlag(1);				/* Outcome of Ready Check is "ready" */
	CrFwInCmdSample1SetStartActionOutcome(1);		/* Outcome of Start Action is "success" */
	CrFwInCmdSample1SetTerminationActionOutcome(1);	/* Outcome of Termination Action is "success" */
	sampleInCmd1 = CrFwInFactoryMakeInCmd(pckt);

	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwPcktSetAckLevel(pckt, 0, 0, 0, 0);			/* No acknowledgement of success */
	CrFwInCmdSample1SetValidityFlag(1);				/* Validity Check returns "valid" */
	CrFwInCmdSample1SetProgressActionOutcome(2);	/* Outcome of Progress Action is "continue" */
	CrFwInCmdSample1SetReadyFlag(1);				/* Outcome of Ready Check is "ready" */
	CrFwInCmdSample1SetStartActionOutcome(1);		/* Outcome of Start Action is "success" */
	CrFwInCmdSample1SetTerminationActionOutcome(1);	/* Outcome of Termination Action is "success" */
	sampleInCmd2 = CrFwInFactoryMakeInCmd(pckt);

	/* Allocate InReport instances */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,5);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,1);
	inRep1 = CrFwInFactoryMakeInRep(pckt);

	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,5);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,1);
	inRep2 = CrFwInFactoryMakeInRep(pckt);

	/* Load InCommands and InReports in InManager */
	CrFwInManagerLoad(inManager2, sampleInCmd1);
	CrFwInManagerLoad(inManager2, sampleInCmd2);
	CrFwInManagerLoad(inManager2, inRep1);
	CrFwInManagerLoad(inManager2, inRep2);
	if (CrFwInManagerGetNOfPendingInCmp(inManager2) != 4)
		return 0;
	if (CrFwInManagerGetNOfLoadedInCmp(inManager2) != 4)
		return 0;

	/* Execute the InManager */
	CrFwCmpExecute(inManager2);	/* this causes the InReports to be unloaded */
	CrFwCmpExecute(inManager2);

	/* Check that InReports were unloaded and released */
	if (CrFwInManagerGetNOfPendingInCmp(inManager2) != 2)
		return 0;
	if (CrFwInFactoryGetNOfAllocatedInRep() != 0)
		return 0;
	if (CrFwInFactoryGetNOfAllocatedInCmd() != 2)
		return 0;
	if (CrFwInManagerGetNOfLoadedInCmp(inManager2) != 4)
		return 0;

	/* Check tracking by InRegistry */
	if (CrFwInRegistryGetState(CrFwCmpGetInstanceId(inRep1)) != crInRegistryTerminated)
		return 0;
	if (CrFwInRegistryGetState(CrFwCmpGetInstanceId(inRep2)) != crInRegistryTerminated)
		return 0;
	if (CrFwInRegistryGetState(CrFwCmpGetInstanceId(sampleInCmd1)) != crInRegistryPending)
		return 0;
	if (CrFwInRegistryGetState(CrFwCmpGetInstanceId(sampleInCmd2)) != crInRegistryPending)
		return 0;

	/* Configure InCommands to be terminated */
	CrFwInCmdSample1SetProgressActionOutcome(1);	/* Outcome of Progress Action is "terminated" */

	/* Execute the InManager */
	CrFwCmpExecute(inManager2);	/* this causes the InCommands to be unloaded */

	/* Check that InCommands were unloaded and released */
	if (CrFwInManagerGetNOfPendingInCmp(inManager2) != 0)
		return 0;
	if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
		return 0;

	/* Check tracking by InRegistry */
	if (CrFwInRegistryGetState(CrFwCmpGetInstanceId(inRep1)) != crInRegistryTerminated)
		return 0;
	if (CrFwInRegistryGetState(CrFwCmpGetInstanceId(inRep2)) != crInRegistryTerminated)
		return 0;
	if (CrFwInRegistryGetState(CrFwCmpGetInstanceId(sampleInCmd1)) != crInRegistryTerminated)
		return 0;
	if (CrFwInRegistryGetState(CrFwCmpGetInstanceId(sampleInCmd2)) != crInRegistryTerminated)
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
CrFwBool_t CrFwInManagerTestCase7() {
	FwSmDesc_t inManager3, inRegistry, inFactory;
	FwSmDesc_t sampleInCmd1, sampleInCmd2, inRep1, inRep2;
	CrFwPckt_t pckt;

	/* Instantiate an InManager */
	inManager3 = CrFwInManagerMake(2);

	/* Initialize and Configure InManager and check success */
	CrFwCmpInit(inManager3);
	CrFwCmpReset(inManager3);
	if (!CrFwCmpIsInConfigured(inManager3))
		return 0;

	/* Initialize and Configure InRegistry and check success */
	inRegistry = CrFwInRegistryMake();
	CrFwCmpInit(inRegistry);
	CrFwCmpReset(inRegistry);
	if (!CrFwCmpIsInConfigured(inRegistry))
		return 0;

	/* Initialize and Configure InFactory and check success */
	inFactory = CrFwInFactoryMake();
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate Sample 1 InCommand instances and configure them to remain pending */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwPcktSetAckLevel(pckt, 0, 0, 0, 0);			/* No acknowledgement of success */
	CrFwInCmdSample1SetValidityFlag(1);				/* Validity Check returns "valid" */
	CrFwInCmdSample1SetProgressActionOutcome(2);	/* Outcome of Progress Action is "continue" */
	CrFwInCmdSample1SetReadyFlag(1);				/* Outcome of Ready Check is "ready" */
	CrFwInCmdSample1SetStartActionOutcome(1);		/* Outcome of Start Action is "success" */
	CrFwInCmdSample1SetTerminationActionOutcome(1);	/* Outcome of Termination Action is "success" */
	sampleInCmd1 = CrFwInFactoryMakeInCmd(pckt);

	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwPcktSetAckLevel(pckt, 0, 0, 0, 0);			/* No acknowledgement of success */
	CrFwInCmdSample1SetValidityFlag(1);				/* Validity Check returns "valid" */
	CrFwInCmdSample1SetProgressActionOutcome(2);	/* Outcome of Progress Action is "continue" */
	CrFwInCmdSample1SetReadyFlag(1);				/* Outcome of Ready Check is "ready" */
	CrFwInCmdSample1SetStartActionOutcome(1);		/* Outcome of Start Action is "success" */
	CrFwInCmdSample1SetTerminationActionOutcome(1);	/* Outcome of Termination Action is "success" */
	sampleInCmd2 = CrFwInFactoryMakeInCmd(pckt);

	/* Allocate InReport instances */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,5);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,1);
	inRep1 = CrFwInFactoryMakeInRep(pckt);

	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,5);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,1);
	inRep2 = CrFwInFactoryMakeInRep(pckt);

	/* Load InCommands and InReports in InManager */
	CrFwInManagerLoad(inManager3, sampleInCmd1);
	CrFwInManagerLoad(inManager3, sampleInCmd2);
	CrFwInManagerLoad(inManager3, inRep1);
	CrFwInManagerLoad(inManager3, inRep2);
	if (CrFwInManagerGetNOfPendingInCmp(inManager3) != 4)
		return 0;

	/* Reset the InManager */
	CrFwCmpReset(inManager3);

	/* Check that InReports and InCommands were unloaded and released */
	if (CrFwInManagerGetNOfPendingInCmp(inManager3) != 0)
		return 0;
	if (CrFwInFactoryGetNOfAllocatedInRep() != 0)
		return 0;
	if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
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
CrFwBool_t CrFwInManagerTestCase8() {
	FwSmDesc_t inManager3, inRegistry, inFactory;
	FwSmDesc_t sampleInCmd1, sampleInCmd2, inRep1, inRep2;
	CrFwPckt_t pckt;

	/* Instantiate an InManager */
	inManager3 = CrFwInManagerMake(2);

	/* Initialize and Configure InManager and check success */
	CrFwCmpInit(inManager3);
	CrFwCmpReset(inManager3);
	if (!CrFwCmpIsInConfigured(inManager3))
		return 0;

	/* Initialize and Configure InRegistry and check success */
	inRegistry = CrFwInRegistryMake();
	CrFwCmpInit(inRegistry);
	CrFwCmpReset(inRegistry);
	if (!CrFwCmpIsInConfigured(inRegistry))
		return 0;

	/* Initialize and Configure InFactory and check success */
	inFactory = CrFwInFactoryMake();
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate Sample 1 InCommand instances and configure them to remain pending */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwPcktSetAckLevel(pckt, 0, 0, 0, 0);			/* No acknowledgement of success */
	CrFwInCmdSample1SetValidityFlag(1);				/* Validity Check returns "valid" */
	CrFwInCmdSample1SetProgressActionOutcome(2);	/* Outcome of Progress Action is "continue" */
	CrFwInCmdSample1SetReadyFlag(1);				/* Outcome of Ready Check is "ready" */
	CrFwInCmdSample1SetStartActionOutcome(1);		/* Outcome of Start Action is "success" */
	CrFwInCmdSample1SetTerminationActionOutcome(1);	/* Outcome of Termination Action is "success" */
	sampleInCmd1 = CrFwInFactoryMakeInCmd(pckt);

	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,50);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwPcktSetAckLevel(pckt, 0, 0, 0, 0);			/* No acknowledgement of success */
	CrFwInCmdSample1SetValidityFlag(1);				/* Validity Check returns "valid" */
	CrFwInCmdSample1SetProgressActionOutcome(2);	/* Outcome of Progress Action is "continue" */
	CrFwInCmdSample1SetReadyFlag(1);				/* Outcome of Ready Check is "ready" */
	CrFwInCmdSample1SetStartActionOutcome(1);		/* Outcome of Start Action is "success" */
	CrFwInCmdSample1SetTerminationActionOutcome(1);	/* Outcome of Termination Action is "success" */
	sampleInCmd2 = CrFwInFactoryMakeInCmd(pckt);

	/* Allocate InReport instances */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,5);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,1);
	inRep1 = CrFwInFactoryMakeInRep(pckt);

	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,5);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,1);
	inRep2 = CrFwInFactoryMakeInRep(pckt);

	/* Load InCommands and InReports in InManager */
	CrFwInManagerLoad(inManager3, sampleInCmd1);
	CrFwInManagerLoad(inManager3, sampleInCmd2);
	CrFwInManagerLoad(inManager3, inRep1);
	CrFwInManagerLoad(inManager3, inRep2);
	if (CrFwInManagerGetNOfPendingInCmp(inManager3) != 4)
		return 0;

	/* Shutdown the InManager */
	CrFwCmpShutdown(inManager3);

	/* Check that InReports and InCommands were unloaded and released */
	if (CrFwInManagerGetNOfPendingInCmp(inManager3) != 0)
		return 0;
	if (CrFwInFactoryGetNOfAllocatedInRep() != 0)
		return 0;
	if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
		return 0;

	/* Re-start, initialize and reset the InManager */
	FwSmStart(inManager3);
	CrFwCmpInit(inManager3);
	CrFwCmpReset(inManager3);
	if (!CrFwCmpIsInConfigured(inManager3))
		return 0;

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}


