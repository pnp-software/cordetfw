/**
 * @file
 *
 * Implementation of test cases for OutManager component.
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
#include "CrFwOutManagerTestCases.h"
#include "CrFwOutStreamStub.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include framework files */
#include "OutRegistry/CrFwOutRegistry.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutStream/CrFwOutStream.h"
#include "OutFactory/CrFwOutFactory.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include configuration files */
#include "CrFwOutRegistryUserPar.h"
#include "CrFwOutManagerUserPar.h"
#include "CrFwRepErrStub.h"
#include "CrFwOutFactoryUserPar.h"
#include "CrFwCmpData.h"

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutManagerTestCase1() {
	FwSmDesc_t outManager1, outManagerIll;

	/* Instantiate the first OutManager */
	outManager1 = CrFwOutManagerMake(0);

	/* Check current state of OutManager */
	if (!CrFwCmpIsInCreated(outManager1))
		return 0;

	/* Initialize and Configure OutManager and check success */
	CrFwCmpInit(outManager1);
	if (!CrFwCmpIsInInitialized(outManager1))
		return 0;
	CrFwCmpReset(outManager1);
	if (!CrFwCmpIsInConfigured(outManager1))
		return 0;

	/* Check Instance and Type Identifiers */
	if (CrFwCmpGetInstanceId(outManager1) != 0)
		return 0;
	if (CrFwCmpGetTypeId(outManager1) != CR_FW_OUTMANAGER_TYPE)
		return 0;

	/* Check POCL */
	if (CrFwOutManagerGetPOCLSize(outManager1) != 3)
		return 0;
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager1) != 0)
		return 0;

	/* Check counter of loaded OutComponents */
	if (CrFwOutManagerGetNOfLoadedOutCmp(outManager1) != 0)
		return 0;

	/* Attempt to instantiate an OutManager with an illegal identifier */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;
	outManagerIll = CrFwOutManagerMake(CR_FW_NOF_OUTMANAGER);
	if (outManagerIll != NULL)
		return 0;
	if (CrFwGetAppErrCode() != crOutManagerIllId)
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
CrFwBool_t CrFwOutManagerTestCase2() {
	FwSmDesc_t outManager2, outFactory;
	FwSmDesc_t outCmp1, outCmp2, outCmp3, outCmp4, outCmp5;
	CrFwCounterU2_t errRepPosLocal;

	/* Instantiate the second OutManager */
	outManager2 = CrFwOutManagerMake(1);

	/* Initialize and Configure OutManager and check success */
	CrFwCmpInit(outManager2);
	CrFwCmpReset(outManager2);
	if (!CrFwCmpIsInConfigured(outManager2))
		return 0;

	/* Check Instance Identifiers */
	if (CrFwCmpGetInstanceId(outManager2) != 1)
		return 0;

	/* Initialize and Configure OutFactory and check success */
	outFactory = CrFwOutFactoryMake();
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Create and load four OutComponents (this should fill the OutManager */
	outCmp1 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	CrFwOutManagerLoad(outManager2, outCmp1);
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager2) != 1)
		return 0;

	outCmp2 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	CrFwOutManagerLoad(outManager2, outCmp2);
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager2) != 2)
		return 0;

	outCmp3 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	CrFwOutManagerLoad(outManager2, outCmp3);
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager2) != 3)
		return 0;

	outCmp4 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	CrFwOutManagerLoad(outManager2, outCmp4);
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager2) != 4)
		return 0;

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* Create and load the fifth OutComponent (this overflows the POCL) */
	outCmp5 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	CrFwOutManagerLoad(outManager2, outCmp5);
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager2) != 4)
		return 0;

	/* Check that an error report has been generated */
	if (CrFwRepErrStubGetPos() != errRepPosLocal+1)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crOutManagerPoclFull)
		return 0;
	if (CrFwRepErrStubGetTypeId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != CR_FW_OUTMANAGER_TYPE)
		return 0;
	if (CrFwRepErrStubGetInstanceId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != 1)
		return 0;

	/* Reset the OutManager (this should clear the POCL and release all loaded OutComponents) */
	CrFwCmpReset(outManager2);
	if (!CrFwCmpIsInConfigured(outManager2))
		return 0;
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager2) != 0)
		return 0;
	if (CrFwPcktGetNOfAllocated() != 0)
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
CrFwBool_t CrFwOutManagerTestCase3() {
	FwSmDesc_t outManager1, outRegistry, outFactory;
	FwSmDesc_t sampleOutCmp;
	FwSmCounterU3_t execCnt;

	/* Instantiate the first OutManager */
	outManager1 = CrFwOutManagerMake(0);

	/* Initialize and Configure OutManager and check success */
	CrFwCmpInit(outManager1);
	CrFwCmpReset(outManager1);
	if (!CrFwCmpIsInConfigured(outManager1))
		return 0;

	/* Initialize and Configure OutRegistry and check success */
	outRegistry = CrFwOutRegistryMake();
	CrFwCmpInit(outRegistry);
	CrFwCmpReset(outRegistry);
	if (!CrFwCmpIsInConfigured(outRegistry))
		return 0;

	/* Execute the empty OutManager */
	CrFwCmpExecute(outManager1);
	CrFwCmpExecute(outManager1);

	/* Initialize and Configure OutFactory and check success */
	outFactory = CrFwOutFactoryMake();
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Allocate a Sample 1 OutComponent instance */
	sampleOutCmp = CrFwOutFactoryMakeOutCmp(50,1,0,0);
	if (!CrFwOutCmpIsInLoaded(sampleOutCmp))
		return 0;

	/* Set up enable and ready check of sample OutComponent */
	CrFwOutCmpSample1SetEnableFlag(0);
	CrFwOutCmpSample1SetReadyFlag(0);

	/* Load Sample OutComponent in OutManager */
	CrFwOutManagerLoad(outManager1, sampleOutCmp);
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager1) != 1)
		return 0;

	/* Store execution counter of Sample OutComponent */
	execCnt = FwSmGetExecCnt(sampleOutCmp);

	/* Execute the OutManager */
	CrFwCmpExecute(outManager1);	/* this causes the Sample OutComponent to enter ABORTED and be unloaded */
	CrFwCmpExecute(outManager1);

	/* Check that execution was propagated to Sample OutComponent */
	if (FwSmGetExecCnt(sampleOutCmp) !=  execCnt+1)
		return 0;
	if (FwSmGetStateExecCnt(sampleOutCmp) != 1)
		return 0;
	if (!CrFwOutCmpIsInAborted(sampleOutCmp))
		return 0;
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager1) != 0)
		return 0;
	if (CrFwOutRegistryGetState(CrFwCmpGetInstanceId(sampleOutCmp)) != crOutRegistryAborted)
		return 0;

	/* Check that Sample OutComponent was released by OutManager */
	if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
		return 0;

	/* Re-allocate, re-load Sample OutComponent in OutManager, and re-register is with OutRegistry */
	sampleOutCmp = CrFwOutFactoryMakeOutCmp(50,1,0,0);
	CrFwCmpReset(sampleOutCmp);
	if (!CrFwOutCmpIsInLoaded(sampleOutCmp))
		return 0;
	CrFwOutManagerLoad(outManager1, sampleOutCmp);
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager1) != 1)
		return 0;

	/* Make Sample OutComponent enabled but not ready */
	CrFwOutCmpSample1SetEnableFlag(1);
	CrFwOutCmpSample1SetReadyFlag(0);

	/* Execute the OutManager twice */
	CrFwCmpExecute(outManager1);
	CrFwCmpExecute(outManager1);

	/* Check that execution was propagated to Sample OutComponent */
	if (!CrFwOutCmpIsInPending(sampleOutCmp))
		return 0;
	if (FwSmGetStateExecCnt(sampleOutCmp) != 2)
		return 0;

	/* Check that Sample OutComponent is still loaded */
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager1) != 1)
		return 0;
	if (CrFwOutRegistryGetState(CrFwCmpGetInstanceId(sampleOutCmp)) != crOutRegistryPending)
		return 0;

	/* Reset OutManager (this causes the pending OutComponent to be released) */
	CrFwCmpReset(outManager1);

	/* Check that there are no allocated OutComponents */
	if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
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
CrFwBool_t CrFwOutManagerTestCase4() {
	FwSmDesc_t outManager4, outRegistry, outFactory, outStream1;
	FwSmDesc_t sampleOutCmp1, sampleOutCmp2, stdOutCmp1, stdOutCmp2, stdOutCmp3, stdOutCmp4;

	/* Instantiate the second OutManager */
	outManager4 = CrFwOutManagerMake(3);

	/* Initialize and Configure OutManager and check success */
	CrFwCmpInit(outManager4);
	CrFwCmpReset(outManager4);
	if (!CrFwCmpIsInConfigured(outManager4))
		return 0;

	/* Initialize and Configure OutRegistry and check success */
	outRegistry = CrFwOutRegistryMake();
	CrFwCmpInit(outRegistry);
	CrFwCmpReset(outRegistry);
	if (!CrFwCmpIsInConfigured(outRegistry))
		return 0;

	/* Initialize and Configure OutFactory and check success */
	outFactory = CrFwOutFactoryMake();
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Initialize and Configure the first OutStream  */
	outStream1 = CrFwOutStreamMake(0);
	FwSmStart(outStream1);	/* just in case it had been stopped in some other test case */
	CrFwCmpInit(outStream1);
	CrFwCmpReset(outStream1);
	if (!CrFwCmpIsInConfigured(outStream1))
		return 0;

	/* Allocate the OutComponent instances */
	sampleOutCmp1 = CrFwOutFactoryMakeOutCmp(50,1,0,0);
	sampleOutCmp2 = CrFwOutFactoryMakeOutCmp(50,1,0,0);
	stdOutCmp1 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	stdOutCmp2 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	stdOutCmp3 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	stdOutCmp4 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	if (!CrFwOutCmpIsInLoaded(sampleOutCmp1))
		return 0;
	if (!CrFwOutCmpIsInLoaded(sampleOutCmp2))
		return 0;
	if (!CrFwOutCmpIsInLoaded(stdOutCmp1))
		return 0;
	if (!CrFwOutCmpIsInLoaded(stdOutCmp2))
		return 0;
	if (!CrFwOutCmpIsInLoaded(stdOutCmp3))
		return 0;
	if (!CrFwOutCmpIsInLoaded(stdOutCmp4))
		return 0;

	/* Set destination of OutComponents to be the same as the destination of the OutStream */
	CrFwOutCmpSetDest(sampleOutCmp1, CrFwOutStreamGetDest(outStream1));
	CrFwOutCmpSetDest(sampleOutCmp2, CrFwOutStreamGetDest(outStream1));
	CrFwOutCmpSetDest(stdOutCmp1, CrFwOutStreamGetDest(outStream1));
	CrFwOutCmpSetDest(stdOutCmp2, CrFwOutStreamGetDest(outStream1));
	CrFwOutCmpSetDest(stdOutCmp3, CrFwOutStreamGetDest(outStream1));
	CrFwOutCmpSetDest(stdOutCmp4, CrFwOutStreamGetDest(outStream1));

	/* Set up enable and ready check of the sample OutComponents */
	CrFwOutCmpSample1SetEnableFlag(1);
	CrFwOutCmpSample1SetReadyFlag(0);

	/* Load OutComponents in OutManager */
	CrFwOutManagerLoad(outManager4, sampleOutCmp1);
	CrFwOutManagerLoad(outManager4, stdOutCmp1);
	CrFwOutManagerLoad(outManager4, sampleOutCmp2);
	CrFwOutManagerLoad(outManager4, stdOutCmp2);
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager4) != 4)
		return 0;
	if (CrFwOutManagerGetNOfLoadedOutCmp(outManager4) != 4)
		return 0;

	/* Execute the OutManager twice */
	CrFwCmpExecute(outManager4);
	CrFwCmpExecute(outManager4);

	/* Check that execution was propagated to Sample OutComponent */
	if (!CrFwOutCmpIsInPending(sampleOutCmp1))
		return 0;
	if (!CrFwOutCmpIsInPending(sampleOutCmp2))
		return 0;
	if (!CrFwOutCmpIsInTerminated(stdOutCmp1))
		return 0;
	if (!CrFwOutCmpIsInTerminated(stdOutCmp2))
		return 0;

	/* Check that Sample OutComponents are still loaded */
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager4) != 2)
		return 0;
	if (CrFwOutRegistryGetState(CrFwCmpGetInstanceId(sampleOutCmp1)) != crOutRegistryPending)
		return 0;
	if (CrFwOutRegistryGetState(CrFwCmpGetInstanceId(sampleOutCmp2)) != crOutRegistryPending)
		return 0;
	if (CrFwOutRegistryGetState(CrFwCmpGetInstanceId(stdOutCmp1)) != crOutRegistryTerminated)
		return 0;
	if (CrFwOutRegistryGetState(CrFwCmpGetInstanceId(stdOutCmp2)) != crOutRegistryTerminated)
		return 0;
	if (CrFwOutManagerGetNOfLoadedOutCmp(outManager4) != 4)
		return 0;

	/* Load the third and fourth standard OutComponent */
	CrFwOutManagerLoad(outManager4, stdOutCmp3);
	CrFwOutManagerLoad(outManager4, stdOutCmp4);
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager4) != 4)
		return 0;
	if (CrFwOutManagerGetNOfLoadedOutCmp(outManager4) != 6)
		return 0;

	/* Execute the OutManager once */
	CrFwCmpExecute(outManager4);

	/* Check that Sample OutComponents are still loaded */
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager4) != 2)
		return 0;
	if (CrFwOutRegistryGetState(CrFwCmpGetInstanceId(sampleOutCmp1)) != crOutRegistryPending)
		return 0;
	if (CrFwOutRegistryGetState(CrFwCmpGetInstanceId(sampleOutCmp2)) != crOutRegistryPending)
		return 0;
	if (CrFwOutRegistryGetState(CrFwCmpGetInstanceId(stdOutCmp3)) != crOutRegistryTerminated)
		return 0;
	if (CrFwOutRegistryGetState(CrFwCmpGetInstanceId(stdOutCmp4)) != crOutRegistryTerminated)
		return 0;
	if (CrFwOutManagerGetNOfLoadedOutCmp(outManager4) != 6)
		return 0;

	/* Check that the Standard OutComponents have been released */
	if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 2)
		return 0;

	/* Shut down OutManager and check that all OutComponents are unloaded and released */
	CrFwCmpShutdown(outManager4);
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager4) != 0)
		return 0;

	/* Shutdown the OutStream to force all its pending packets to be released */
	CrFwCmpShutdown(outStream1);

	/* Check that Sample OutComponents have been released */
	if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
		return 0;

	/* Bring OutManager back to state CONFIGURED */
	FwSmStart(outManager4);
	CrFwCmpInit(outManager4);
	CrFwCmpReset(outManager4);
	if (!CrFwCmpIsInConfigured(outManager4))
		return 0;

	if (CrFwOutManagerGetNOfLoadedOutCmp(outManager4) != 0)
		return 0;

	if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
		return 0;

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

