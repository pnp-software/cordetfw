/**
 * @file
 *
 * Implementation of test cases for InReport component.
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
#include "CrFwInRepTestCases.h"
/* Include FW Profile files */
#include "FwProfile/FwSmConstants.h"
#include "FwProfile/FwSmConfig.h"
#include "FwProfile/FwSmCore.h"
#include "FwProfile/FwPrConfig.h"
#include "FwProfile/FwPrCore.h"
#include "FwProfile/FwPrConstants.h"
/* Include framework files */
#include "CrFwOutRegistryUserPar.h"
#include "OutRegistry/CrFwOutRegistry.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "InRep/CrFwInRep.h"
#include "InFactory/CrFwInFactory.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include configuration files */
#include "CrFwRepErrStub.h"
#include "CrFwInFactoryUserPar.h"
#include "CrFwCmpData.h"

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInRepTestCase1() {
	FwSmDesc_t InFactory, inRep1, inRep2;
	CrFwPckt_t pckt1, pckt2;
	CrFwInRepData_t* inRepSpecificData;
	CrFwCmpData_t* inRepData;


	/* Instantiate the InFactory */
	InFactory = CrFwInFactoryMake();

	/* Initialize and Configure InFactory and check success */
	CrFwCmpInit(InFactory);
	CrFwCmpReset(InFactory);
	if (!CrFwCmpIsInConfigured(InFactory))
		return 0;

	/* Allocate two InReports */
	pckt1 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt1,5);
	CrFwPcktSetServSubType(pckt1,1);
	CrFwPcktSetDiscriminant(pckt1,1);
	CrFwPcktSetCmdRepId(pckt1,111);
	CrFwPcktSetSrc(pckt1,11);
	CrFwPcktSetGroup(pckt1,88);
	CrFwPcktSetAckLevel(pckt1,1,0,1,0);
	CrFwPcktSetSeqCnt(pckt1,1111);
	inRep1 = CrFwInFactoryMakeInRep(pckt1);

	pckt2 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt2,5);
	CrFwPcktSetServSubType(pckt2,1);
	CrFwPcktSetDiscriminant(pckt2,2);
	CrFwPcktSetCmdRepId(pckt2,222);
	CrFwPcktSetSrc(pckt2,22);
	CrFwPcktSetGroup(pckt2,89);
	CrFwPcktSetAckLevel(pckt2,0,1,0,1);
	CrFwPcktSetSeqCnt(pckt2,2222);
	inRep2 = CrFwInFactoryMakeInRep(pckt2);

	/* Check the instance identifiers and the type identifier */
	if (CrFwCmpGetInstanceId(inRep1) != 111)
		return 0;
	if (CrFwCmpGetInstanceId(inRep2) != 222)
		return 0;
	if (CrFwCmpGetTypeId(inRep1) != CR_FW_INREPORT_TYPE)
		return 0;
	if (CrFwCmpGetTypeId(inRep2) != CR_FW_INREPORT_TYPE)
		return 0;

	/* Check correct configuration */
	if (FwSmCheck(inRep1) != 1)
		return 0;
	if (FwSmCheck(inRep2) != 1)
		return 0;

	/* Check InReport state */
	if (!CrFwCmpIsInConfigured(inRep1))
		return 0;

	/* Check the parameter area */
	inRepData = (CrFwCmpData_t*)FwSmGetData(inRep1);
	inRepSpecificData = (CrFwInRepData_t*)inRepData->cmpSpecificData;
	if (CrFwInRepGetParLength(inRep1) != CrFwPcktGetParLength(inRepSpecificData->pckt))
		return 0;
	if (CrFwInRepGetParStart(inRep1) != CrFwPcktGetParStart(inRepSpecificData->pckt))
		return 0;

	/* Check type, sub-type and discriminant */
	if (CrFwInRepGetServType(inRep1) != 5)
		return 0;
	if (CrFwInRepGetServType(inRep2) != 5)
		return 0;

	if (CrFwInRepGetServSubType(inRep1) != 1)
		return 0;
	if (CrFwInRepGetServSubType(inRep2) != 1)
		return 0;

	if (CrFwInRepGetDiscriminant(inRep1) != 1)
		return 0;
	if (CrFwInRepGetDiscriminant(inRep2) != 2)
		return 0;

	/* Check source and sequence counter*/
	if (CrFwInRepGetSrc(inRep1) != 11)
		return 0;
	if (CrFwInRepGetSrc(inRep2) != 22)
		return 0;
	if (CrFwInRepGetSeqCnt(inRep1) != 1111)
		return 0;
	if (CrFwInRepGetSeqCnt(inRep2) != 2222)
		return 0;
	if (CrFwInRepGetGroup(inRep1) != 88)
		return 0;
	if (CrFwInRepGetGroup(inRep2) != 89)
		return 0;

	/* Release the InReports */
	CrFwInFactoryReleaseInRep(inRep1);
	CrFwInFactoryReleaseInRep(inRep2);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInRepTestCase2() {
	FwSmDesc_t InFactory, inRep;
	CrFwPckt_t pckt;

	/* Instantiate the InFactory */
	InFactory = CrFwInFactoryMake();

	/* Initialize and Configure InFactory and check success */
	CrFwCmpInit(InFactory);
	CrFwCmpReset(InFactory);
	if (!CrFwCmpIsInConfigured(InFactory))
		return 0;

	/* Allocate the Sample1 InReport */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,40);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwInRepSample1SetValidityFlag(0);	/* Validity Check will fail */
	inRep = CrFwInFactoryMakeInRep(pckt);

	/* Check InReport state */
	if (!CrFwCmpIsInInitialized(inRep))
		return 0;

	/* Release the InReports */
	CrFwInFactoryReleaseInRep(inRep);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInRepTestCase3() {
	FwSmDesc_t InFactory, inRep;
	CrFwPckt_t pckt;
	CrFwCounterU1_t updCnt;

	/* Instantiate the InFactory */
	InFactory = CrFwInFactoryMake();

	/* Initialize and Configure InFactory and check success */
	CrFwCmpInit(InFactory);
	CrFwCmpReset(InFactory);
	if (!CrFwCmpIsInConfigured(InFactory))
		return 0;

	/* Allocate the Sample1 InReport */
	pckt = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt,40);
	CrFwPcktSetServSubType(pckt,1);
	CrFwPcktSetDiscriminant(pckt,0);
	CrFwInRepSample1SetValidityFlag(1);	/* Validity Check will succeed */
	updCnt = CrFwInRepSample1GetUpdateActionCounter();
	inRep = CrFwInFactoryMakeInRep(pckt);

	/* Check InReport state */
	if (!CrFwCmpIsInConfigured(inRep))
		return 0;

	/* Execute InReport and check that Update Action is executed */
	CrFwCmpExecute(inRep);
	if (CrFwInRepSample1GetUpdateActionCounter() != updCnt+1)
		return 0;

	/* Execute InReport again and check that Update Action is not executed */
	CrFwCmpExecute(inRep);
	if (CrFwInRepSample1GetUpdateActionCounter() != updCnt+1)
		return 0;

	/* Release the InReports */
	CrFwInFactoryReleaseInRep(inRep);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

