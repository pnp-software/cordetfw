/**
 * @file
 *
 * Implementation of test cases for InFactory component.
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
#include "CrFwInFactoryTestCases.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include framework files */
#include "CrFwOutRegistryUserPar.h"
#include "InRegistry/CrFwInRegistry.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "InFactory/CrFwInFactory.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include configuration files */
#include "CrFwRepErrStub.h"
#include "CrFwInFactoryUserPar.h"
#include "CrFwCmpData.h"

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInFactoryTestCase1() {
	FwSmDesc_t inFactory1, inFactory2;

	/* Instantiate the InFactory */
	inFactory1 = CrFwInFactoryMake();
	if (inFactory1 == NULL)
		return 0;

	/* Instantiate it again and check that same component is returned */
	inFactory2 = CrFwInFactoryMake();
	if (inFactory1 != inFactory2)
		return 0;

	/* Check configuration of InFactory */
	if (FwSmCheckRec(inFactory1) != smSuccess)
		return 0;

	/* Initialize and Configure InFactory and check success */
	CrFwCmpInit(inFactory1);
	CrFwCmpReset(inFactory1);
	if (!CrFwCmpIsInConfigured(inFactory1))
		return 0;

	/* Check component type */
	if (CrFwCmpGetInstanceId(inFactory1) != 0)
		return 0;
	if (CrFwCmpGetTypeId(inFactory1) != CR_FW_INFACTORY_TYPE)
		return 0;

	/* Check initial number of allocated InCommands */
	if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
		return 0;

	/* Check maximum number of InCommands which can be allocated */
	if (CrFwInFactoryGetMaxNOfInCmd() != CR_FW_INFACTORY_MAX_NOF_INCMD)
		return 0;

	/* Check initial number of allocated InReports */
	if (CrFwInFactoryGetNOfAllocatedInRep() != 0)
		return 0;

	/* Check maximum number of InReports which can be allocated */
	if (CrFwInFactoryGetMaxNOfInRep() != CR_FW_INFACTORY_MAX_NOF_INREP)
		return 0;

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwInFactoryTestCase2() {
	FwSmDesc_t inFactory, inCmd;
	CrFwPckt_t inCmdPckt;
	CrFwCounterU2_t i;
	FwSmDesc_t inCmdArray[CR_FW_INFACTORY_MAX_NOF_INCMD];

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();
	if (inFactory == NULL)
		return 0;

	/* Initialize and configure the InFactory */
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* attempt to retrieve an InCommand with undefined service type */
	inCmdPckt = CrFwPcktMake(100);
	CrFwPcktSetServType(inCmdPckt,6);
	CrFwPcktSetServSubType(inCmdPckt,1);
	CrFwPcktSetDiscriminant(inCmdPckt,1);
	inCmd = CrFwInFactoryMakeInCmd(inCmdPckt);
	if (inCmd != NULL)
		return 0;
	if (CrFwGetAppErrCode() != crIllInCmdKind)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);
	CrFwPcktRelease(inCmdPckt);

	/* attempt to retrieve an InCommand with undefined service sub-type */
	inCmdPckt = CrFwPcktMake(100);
	CrFwPcktSetServType(inCmdPckt,8);
	CrFwPcktSetServSubType(inCmdPckt,13);
	CrFwPcktSetDiscriminant(inCmdPckt,1);
	inCmd = CrFwInFactoryMakeInCmd(inCmdPckt);
	if (inCmd != NULL)
		return 0;
	if (CrFwGetAppErrCode() != crIllInCmdKind)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);
	CrFwPcktRelease(inCmdPckt);

	/* attempt to retrieve an InCommand with undefined discriminant */
	inCmdPckt = CrFwPcktMake(40);
	CrFwPcktSetServType(inCmdPckt,8);
	CrFwPcktSetServSubType(inCmdPckt,1);
	CrFwPcktSetDiscriminant(inCmdPckt,3);
	inCmd = CrFwInFactoryMakeInCmd(inCmdPckt);
	if (inCmd != NULL)
		return 0;
	if (CrFwGetAppErrCode() != crIllInCmdKind)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);
	CrFwPcktRelease(inCmdPckt);

	/* attempt to retrieve an InCommand with illegal length */
	inCmdPckt = CrFwPcktMake(41);
	CrFwPcktSetServType(inCmdPckt,8);
	CrFwPcktSetServSubType(inCmdPckt,1);
	CrFwPcktSetDiscriminant(inCmdPckt,2);
	inCmd = CrFwInFactoryMakeInCmd(inCmdPckt);
	if (inCmd != NULL)
		return 0;
	if (CrFwGetAppErrCode() != crIllInCmdLen)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);
	CrFwPcktRelease(inCmdPckt);
	
	/* Create CR_FW_INFACTORY_MAX_NOF_INCMD InCommand and then attempt to create one more */
	for (i=0; i<CR_FW_INFACTORY_MAX_NOF_INCMD; i++) {
		inCmdPckt = CrFwPcktMake(100);
		CrFwPcktSetServType(inCmdPckt,8);
		CrFwPcktSetServSubType(inCmdPckt,1);
		CrFwPcktSetDiscriminant(inCmdPckt,1);
		inCmdArray[i] = CrFwInFactoryMakeInCmd(inCmdPckt);
		if (inCmdArray[i]==NULL)
			return 0;
	}

	inCmdPckt = CrFwPcktMake(100);
	CrFwPcktSetServType(inCmdPckt,8);
	CrFwPcktSetServSubType(inCmdPckt,1);
	CrFwPcktSetDiscriminant(inCmdPckt,1);
	inCmd = CrFwInFactoryMakeInCmd(inCmdPckt);
	if (inCmd != NULL)
		return 0;
	if (CrFwGetAppErrCode() != crInCmdAllocationFail)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);
	CrFwPcktRelease(inCmdPckt);

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

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwInFactoryTestCase3() {
	FwSmDesc_t inFactory;
	FwSmDesc_t inCmd1, inCmd2, inCmd3;
	CrFwPckt_t pckt1, pckt2, pckt3;

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();
	if (inFactory == NULL)
		return 0;

	/* Initialize and Reset the InFactory */
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate three InCommands */
	pckt1 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt1,8);
	CrFwPcktSetServSubType(pckt1,1);
	CrFwPcktSetDiscriminant(pckt1,1);
	CrFwPcktSetCmdRepId(pckt1,101);
	inCmd1 = CrFwInFactoryMakeInCmd(pckt1);

	pckt2 = CrFwPcktMake(40);
	CrFwPcktSetServType(pckt2,8);
	CrFwPcktSetServSubType(pckt2,1);
	CrFwPcktSetDiscriminant(pckt2,2);
	CrFwPcktSetCmdRepId(pckt2,102);
	inCmd2 = CrFwInFactoryMakeInCmd(pckt2);

	pckt3 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt3,8);
	CrFwPcktSetServSubType(pckt3,1);
	CrFwPcktSetDiscriminant(pckt3,1);
	CrFwPcktSetCmdRepId(pckt3,103);
	inCmd3 = CrFwInFactoryMakeInCmd(pckt3);
	if (CrFwCmpGetInstanceId(inCmd1) != 101)
		return 0;
	if (CrFwCmpGetInstanceId(inCmd2) != 102)
		return 0;
	if (CrFwCmpGetInstanceId(inCmd3) != 103)
		return 0;
	if (CrFwInFactoryGetNOfAllocatedInCmd() != 3)
		return 0;

	/* Reset the InFactory and check that no InCommands are allocated */
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;
	if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
		return 0;

	/* Allocate three InCommands */
	pckt1 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt1,8);
	CrFwPcktSetServSubType(pckt1,1);
	CrFwPcktSetDiscriminant(pckt1,1);
	inCmd1 = CrFwInFactoryMakeInCmd(pckt1);

	pckt2 = CrFwPcktMake(40);
	CrFwPcktSetServType(pckt2,8);
	CrFwPcktSetServSubType(pckt2,1);
	CrFwPcktSetDiscriminant(pckt2,2);
	inCmd2 = CrFwInFactoryMakeInCmd(pckt2);

	pckt3 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt3,8);
	CrFwPcktSetServSubType(pckt3,1);
	CrFwPcktSetDiscriminant(pckt3,1);
	inCmd3 = CrFwInFactoryMakeInCmd(pckt3);
	if (CrFwInFactoryGetNOfAllocatedInCmd() != 3)
		return 0;

	/* Shutdown the InFactory and check that no InCommands are allocated */
	CrFwCmpShutdown(inFactory);
	if (CrFwCmpIsStarted(inFactory) != 0)
		return 0;
	if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
		return 0;

	/* Restart and initialize the InFactory */
	FwSmStart(inFactory);
	CrFwCmpInit(inFactory);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwInFactoryTestCase4() {
	FwSmDesc_t inFactory;
	FwSmDesc_t inCmd1, inCmd2, inCmd3;
	CrFwPckt_t pckt1, pckt2, pckt3;

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();
	if (inFactory == NULL)
		return 0;

	/* Reset the InFactory */
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate three InCommands */
	pckt1 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt1,8);
	CrFwPcktSetServSubType(pckt1,1);
	CrFwPcktSetDiscriminant(pckt1,1);
	inCmd1 = CrFwInFactoryMakeInCmd(pckt1);

	pckt2 = CrFwPcktMake(40);
	CrFwPcktSetServType(pckt2,8);
	CrFwPcktSetServSubType(pckt2,1);
	CrFwPcktSetDiscriminant(pckt2,2);
	inCmd2 = CrFwInFactoryMakeInCmd(pckt2);

	pckt3 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt3,8);
	CrFwPcktSetServSubType(pckt3,1);
	CrFwPcktSetDiscriminant(pckt3,1);
	inCmd3 = CrFwInFactoryMakeInCmd(pckt3);
	if (CrFwInFactoryGetNOfAllocatedInCmd() != 3)
		return 0;

	/* Release one of the InCommands */
	CrFwInFactoryReleaseInCmd(inCmd2);
	if (CrFwInFactoryGetNOfAllocatedInCmd() != 2)
		return 0;

	/* Attempt to release the InCommand a second time */
	CrFwInFactoryReleaseInCmd(inCmd2);
	if (CrFwInFactoryGetNOfAllocatedInCmd() != 2)
		return 0;
	if (CrFwGetAppErrCode() != crInCmdRelErr)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);

	/* Release the other two InCommands */
	CrFwInFactoryReleaseInCmd(inCmd1);
	CrFwInFactoryReleaseInCmd(inCmd3);
	if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
		return 0;

	/* Reset the InFactory */
	CrFwCmpReset(inFactory);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}


/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwInFactoryTestCase5() {
	FwSmDesc_t inFactory, inRep;
	CrFwPckt_t inRepPckt;
	CrFwCounterU2_t i;
	FwSmDesc_t inRepArray[CR_FW_INFACTORY_MAX_NOF_INREP];

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();
	if (inFactory == NULL)
		return 0;

	/* Initialize and configure the InFactory */
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* attempt to retrieve an InReport with undefined service type */
	inRepPckt = CrFwPcktMake(100);
	CrFwPcktSetServType(inRepPckt,6);
	CrFwPcktSetServSubType(inRepPckt,1);
	CrFwPcktSetDiscriminant(inRepPckt,1);
	inRep = CrFwInFactoryMakeInRep(inRepPckt);
	if (inRep != NULL)
		return 0;
	if (CrFwGetAppErrCode() != crIllInRepKind)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);
	CrFwPcktRelease(inRepPckt);

	/* attempt to retrieve an InReport with undefined service sub-type */
	inRepPckt = CrFwPcktMake(100);
	CrFwPcktSetServType(inRepPckt,5);
	CrFwPcktSetServSubType(inRepPckt,13);
	CrFwPcktSetDiscriminant(inRepPckt,1);
	inRep = CrFwInFactoryMakeInRep(inRepPckt);
	if (inRep != NULL)
		return 0;
	if (CrFwGetAppErrCode() != crIllInRepKind)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);
	CrFwPcktRelease(inRepPckt);

	/* attempt to retrieve an InReport with undefined discriminant */
	inRepPckt = CrFwPcktMake(100);
	CrFwPcktSetServType(inRepPckt,5);
	CrFwPcktSetServSubType(inRepPckt,1);
	CrFwPcktSetDiscriminant(inRepPckt,4);
	inRep = CrFwInFactoryMakeInRep(inRepPckt);
	if (inRep != NULL)
		return 0;
	if (CrFwGetAppErrCode() != crIllInRepKind)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);
	CrFwPcktRelease(inRepPckt);

	/* attempt to retrieve an InReport with an illegal length */
	inRepPckt = CrFwPcktMake(51);
	CrFwPcktSetServType(inRepPckt,5);
	CrFwPcktSetServSubType(inRepPckt,1);
	CrFwPcktSetDiscriminant(inRepPckt,3);
	inRep = CrFwInFactoryMakeInRep(inRepPckt);
	if (inRep != NULL)
		return 0;
	if (CrFwGetAppErrCode() != crIllInRepLen)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);
	CrFwPcktRelease(inRepPckt);

	/* Create CR_FW_INFACTORY_MAX_NOF_INREP InReport and then attempt to create one more */
	for (i=0; i<CR_FW_INFACTORY_MAX_NOF_INREP; i++) {
		inRepPckt = CrFwPcktMake(100);
		CrFwPcktSetServType(inRepPckt,5);
		CrFwPcktSetServSubType(inRepPckt,1);
		CrFwPcktSetDiscriminant(inRepPckt,1);
		inRepArray[i] = CrFwInFactoryMakeInRep(inRepPckt);
		if (inRepArray[i]==NULL)
			return 0;
	}

	inRepPckt = CrFwPcktMake(100);
	CrFwPcktSetServType(inRepPckt,5);
	CrFwPcktSetServSubType(inRepPckt,1);
	CrFwPcktSetDiscriminant(inRepPckt,1);
	inRep = CrFwInFactoryMakeInRep(inRepPckt);
	if (inRep != NULL)
		return 0;
	if (CrFwGetAppErrCode() != crInRepAllocationFail)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);
	CrFwPcktRelease(inRepPckt);

	/* Release all InReports */
	for (i=0; i<CR_FW_INFACTORY_MAX_NOF_INREP; i++)
		CrFwInFactoryReleaseInRep(inRepArray[i]);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwInFactoryTestCase6() {
	FwSmDesc_t inFactory;
	FwSmDesc_t inRep1, inRep2, inRep3;
	CrFwPckt_t pckt1, pckt2, pckt3;

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();
	if (inFactory == NULL)
		return 0;

	/* Reset the InFactory */
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate three InReports */
	pckt1 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt1,5);
	CrFwPcktSetServSubType(pckt1,1);
	CrFwPcktSetDiscriminant(pckt1,1);
	CrFwPcktSetCmdRepId(pckt1, 101);
	inRep1 = CrFwInFactoryMakeInRep(pckt1);

	pckt2 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt2,5);
	CrFwPcktSetServSubType(pckt2,1);
	CrFwPcktSetDiscriminant(pckt2,2);
	CrFwPcktSetCmdRepId(pckt2, 102);
	inRep2 = CrFwInFactoryMakeInRep(pckt2);

	pckt3 = CrFwPcktMake(50);
	CrFwPcktSetServType(pckt3,5);
	CrFwPcktSetServSubType(pckt3,1);
	CrFwPcktSetDiscriminant(pckt3,3);
	CrFwPcktSetCmdRepId(pckt3, 103);
	inRep3 = CrFwInFactoryMakeInRep(pckt3);
	if (CrFwCmpGetInstanceId(inRep1) != 101)
		return 0;
	if (CrFwCmpGetInstanceId(inRep2) != 102)
		return 0;
	if (CrFwCmpGetInstanceId(inRep3) != 103)
		return 0;
	if (CrFwInFactoryGetNOfAllocatedInRep() != 3)
		return 0;

	/* Reset the InFactory and check that no InReports are allocated */
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;
	if (CrFwInFactoryGetNOfAllocatedInRep() != 0)
		return 0;

	/* Allocate three InReports */
	pckt1 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt1,5);
	CrFwPcktSetServSubType(pckt1,1);
	CrFwPcktSetDiscriminant(pckt1,1);
	inRep1 = CrFwInFactoryMakeInRep(pckt1);

	pckt2 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt2,5);
	CrFwPcktSetServSubType(pckt2,1);
	CrFwPcktSetDiscriminant(pckt2,2);
	inRep2 = CrFwInFactoryMakeInRep(pckt2);

	pckt3 = CrFwPcktMake(50);
	CrFwPcktSetServType(pckt3,5);
	CrFwPcktSetServSubType(pckt3,1);
	CrFwPcktSetDiscriminant(pckt3,3);
	inRep3 = CrFwInFactoryMakeInRep(pckt3);
	if (CrFwInFactoryGetNOfAllocatedInRep() != 3)
		return 0;

	/* Shutdown the InFactory and check that no InReports are allocated */
	CrFwCmpShutdown(inFactory);
	if (CrFwCmpIsStarted(inFactory) != 0)
		return 0;
	if (CrFwInFactoryGetNOfAllocatedInRep() != 0)
		return 0;

	/* Restart and initialize the InFactory */
	FwSmStart(inFactory);
	CrFwCmpInit(inFactory);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwInFactoryTestCase7() {
	FwSmDesc_t inFactory;
	FwSmDesc_t inRep1, inRep2, inRep3;
	CrFwPckt_t pckt1, pckt2, pckt3;

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();
	if (inFactory == NULL)
		return 0;

	/* Reset the InFactory */
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Allocate three InReports */
	pckt1 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt1,5);
	CrFwPcktSetServSubType(pckt1,1);
	CrFwPcktSetDiscriminant(pckt1,1);
	inRep1 = CrFwInFactoryMakeInRep(pckt1);

	pckt2 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt2,5);
	CrFwPcktSetServSubType(pckt2,1);
	CrFwPcktSetDiscriminant(pckt2,2);
	inRep2 = CrFwInFactoryMakeInRep(pckt2);

	pckt3 = CrFwPcktMake(50);
	CrFwPcktSetServType(pckt3,5);
	CrFwPcktSetServSubType(pckt3,1);
	CrFwPcktSetDiscriminant(pckt3,3);
	inRep3 = CrFwInFactoryMakeInRep(pckt3);
	if (CrFwInFactoryGetNOfAllocatedInRep() != 3)
		return 0;

	/* Release one of the InReports */
	CrFwInFactoryReleaseInRep(inRep2);
	if (CrFwInFactoryGetNOfAllocatedInRep() != 2)
		return 0;

	/* Attempt to release the InReport a second time */
	CrFwInFactoryReleaseInRep(inRep2);
	if (CrFwInFactoryGetNOfAllocatedInRep() != 2)
		return 0;
	if (CrFwGetAppErrCode() != crInRepRelErr)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);

	/* Release the other InReports */
	CrFwInFactoryReleaseInRep(inRep1);
	CrFwInFactoryReleaseInRep(inRep3);

	/* Reset the InFactory */
	CrFwCmpReset(inFactory);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}
