/**
 * @file
 *
 * Implementation of test cases for InRegistry Component.
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
/* Include FW Profile files */
#include "FwProfile/FwSmConstants.h"
#include "FwProfile/FwSmConfig.h"
#include "FwProfile/FwSmCore.h"
#include "FwProfile/FwPrConfig.h"
#include "FwProfile/FwPrCore.h"
#include "FwProfile/FwPrConstants.h"
/* Include framework files */
#include "CrFwInRegistryUserPar.h"
#include "InRegistry/CrFwInRegistry.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "InFactory/CrFwInFactory.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include configuration files */
#include "CrFwRepErrStub.h"
#include "CrFwInRegistryTestCases.h"
#include "CrFwCmpData.h"

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInRegistryTestCase1() {
	FwSmDesc_t inRegistry1, inRegistry2;
	CrFwCmpData_t* inRegistryData;

	/* Instantiate the InRegistry */
	inRegistry1 = CrFwInRegistryMake();
	if (inRegistry1 == NULL)
		return 0;

	/* Instantiate it again and check that same component is returned */
	inRegistry2 = CrFwInRegistryMake();
	if (inRegistry1 != inRegistry2)
		return 0;

	/* Check configuration of InRegistry */
	if (FwSmCheckRec(inRegistry1) != smSuccess)
		return 0;

	/* Initialize inRegistry and check success */
	if (!CrFwCmpIsInCreated(inRegistry1))
		return 0;

	CrFwCmpInit(inRegistry1);
	if (!CrFwCmpIsInInitialized(inRegistry1))
		return 0;

	/* Reset InRegistry */
	CrFwCmpReset(inRegistry1);
	if (!CrFwCmpIsInConfigured(inRegistry1))
		return 0;

	/* Check component type */
	inRegistryData = (CrFwCmpData_t*)FwSmGetData(inRegistry1);
	if (inRegistryData->instanceId != 0)
		return 0;
	if (inRegistryData->typeId != CR_FW_INREGISTRY_TYPE)
		return 0;

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwInRegistryTestCase2() {
	FwSmDesc_t inRegistry, inFactory, inRep1, inRep2, inCmd3;
	CrFwPckt_t pckt1, pckt2, pckt3;
	CrFwCounterU2_t i;
	CrFwCmpData_t* cmpData;

	/* Instantiate the InRegistry */
	inRegistry = CrFwInRegistryMake();
	if (inRegistry == NULL)
		return 0;

	/* Initialize and configure InRegistry */
	CrFwCmpInit(inRegistry);
	CrFwCmpReset(inRegistry);
	if (!CrFwCmpIsInConfigured(inRegistry))
		return 0;

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();
	if (inFactory == NULL)
		return 0;

	/* Initialize and configure factories */
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Retrieve three components from their factories */
	pckt1 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt1,5);
	CrFwPcktSetServSubType(pckt1,1);
	CrFwPcktSetDiscriminant(pckt1,1);
	pckt2 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt2,5);
	CrFwPcktSetServSubType(pckt2,1);
	CrFwPcktSetDiscriminant(pckt2,1);
	pckt3 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt3,8);
	CrFwPcktSetServSubType(pckt3,1);
	CrFwPcktSetDiscriminant(pckt3,1);
	inRep1 = CrFwInFactoryMakeInRep(pckt1);
	inRep2 = CrFwInFactoryMakeInRep(pckt2);
	inCmd3 = CrFwInFactoryMakeInCmd(pckt3);

	CrFwInRegistryStartTracking(inRep1);
	CrFwInRegistryStartTracking(inRep2);
	CrFwInRegistryStartTracking(inCmd3);

	cmpData = (CrFwCmpData_t*)FwSmGetData(inRep1);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryPending)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(inRep2);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryPending)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(inCmd3);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryPending)
		return 0;

	CrFwInRegistryUpdateState(inRep1, crInRegistryAborted);
	CrFwInRegistryUpdateState(inRep2, crInRegistryTerminated);
	CrFwInRegistryUpdateState(inCmd3, crInRegistryAborted);

	cmpData = (CrFwCmpData_t*)FwSmGetData(inRep1);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryAborted)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(inRep2);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryTerminated)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(inCmd3);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryAborted)
		return 0;

	for (i=0; i<CR_FW_INREGISTRY_N; i++) {
		CrFwInFactoryReleaseInRep(inRep1);
		pckt1 = CrFwPcktMake(100);
		CrFwPcktSetServType(pckt1,5);
		CrFwPcktSetServSubType(pckt1,1);
		CrFwPcktSetDiscriminant(pckt1,1);
		inRep1 = CrFwInFactoryMakeInRep(pckt1);
		CrFwInRegistryStartTracking(inRep1);
	}

	CrFwInRegistryUpdateState(inCmd3, crInRegistryTerminated);

	cmpData = (CrFwCmpData_t*)FwSmGetData(inRep1);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryPending)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(inRep2);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryNotTracked)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(inCmd3);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryNotTracked)
		return 0;

	/* Release all reports and commands */
	CrFwInFactoryReleaseInRep(inRep1);
	CrFwInFactoryReleaseInRep(inRep2);
	CrFwInFactoryReleaseInCmd(inCmd3);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwInRegistryTestCase3() {
	FwSmDesc_t inRegistry, inFactory, inRep1, inRep2, inCmd3;
	CrFwPckt_t pckt1, pckt2, pckt3;
	CrFwCmpData_t* cmpData;

	/* Instantiate the InRegistry */
	inRegistry = CrFwInRegistryMake();
	if (inRegistry == NULL)
		return 0;

	/* Initialize and configure InRegistry */
	CrFwCmpInit(inRegistry);
	CrFwCmpReset(inRegistry);
	if (!CrFwCmpIsInConfigured(inRegistry))
		return 0;

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();
	if (inFactory == NULL)
		return 0;

	/* Initialize and configure factories */
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Retrieve three OutComponents from the OutFactory (see CrFwInRegistryUserPar.h and CrFwOutFactoryUserPar.h) */
	pckt1 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt1,5);
	CrFwPcktSetServSubType(pckt1,1);
	CrFwPcktSetDiscriminant(pckt1,1);
	pckt2 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt2,5);
	CrFwPcktSetServSubType(pckt2,1);
	CrFwPcktSetDiscriminant(pckt2,1);
	pckt3 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt3,8);
	CrFwPcktSetServSubType(pckt3,1);
	CrFwPcktSetDiscriminant(pckt3,1);
	inRep1 = CrFwInFactoryMakeInRep(pckt1);
	inRep2 = CrFwInFactoryMakeInRep(pckt2);
	inCmd3 = CrFwInFactoryMakeInCmd(pckt3);

	CrFwInRegistryStartTracking(inRep1);
	CrFwInRegistryStartTracking(inRep2);
	CrFwInRegistryStartTracking(inCmd3);

	cmpData = (CrFwCmpData_t*)FwSmGetData(inRep1);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryPending)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(inRep2);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryPending)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(inCmd3);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryPending)
		return 0;

	/* Shutdown InRegistry and check success */
	CrFwCmpShutdown(inRegistry);
	if (CrFwCmpIsStarted(inRegistry) == 1)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(inRep1);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryNotTracked)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(inRep2);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryNotTracked)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(inCmd3);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryNotTracked)
		return 0;

	/* Release all reports and commands */
	CrFwInFactoryReleaseInRep(inRep1);
	CrFwInFactoryReleaseInRep(inRep2);
	CrFwInFactoryReleaseInCmd(inCmd3);

	/* Restart the InRegistry */
	FwSmStart(inRegistry);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwInRegistryTestCase4() {
	FwSmDesc_t inRegistry, inFactory, inRep1, inRep2, inCmd3;
	CrFwPckt_t pckt1, pckt2, pckt3;
	CrFwCmpData_t* cmpData;

	/* Instantiate the InRegistry */
	inRegistry = CrFwInRegistryMake();
	if (inRegistry == NULL)
		return 0;

	/* Initialize and configure InRegistry */
	CrFwCmpInit(inRegistry);
	CrFwCmpReset(inRegistry);
	if (!CrFwCmpIsInConfigured(inRegistry))
		return 0;

	/* Instantiate the InFactory */
	inFactory = CrFwInFactoryMake();
	if (inFactory == NULL)
		return 0;

	/* Initialize and configure factories */
	CrFwCmpInit(inFactory);
	CrFwCmpReset(inFactory);
	if (!CrFwCmpIsInConfigured(inFactory))
		return 0;

	/* Retrieve three OutComponents from the OutFactory (see CrFwInRegistryUserPar.h and CrFwOutFactoryUserPar.h) */
	pckt1 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt1,5);
	CrFwPcktSetServSubType(pckt1,1);
	CrFwPcktSetDiscriminant(pckt1,1);
	pckt2 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt2,5);
	CrFwPcktSetServSubType(pckt2,1);
	CrFwPcktSetDiscriminant(pckt2,1);
	pckt3 = CrFwPcktMake(100);
	CrFwPcktSetServType(pckt3,8);
	CrFwPcktSetServSubType(pckt3,1);
	CrFwPcktSetDiscriminant(pckt3,1);
	inRep1 = CrFwInFactoryMakeInRep(pckt1);
	inRep2 = CrFwInFactoryMakeInRep(pckt2);
	inCmd3 = CrFwInFactoryMakeInCmd(pckt3);

	CrFwInRegistryStartTracking(inRep1);
	CrFwInRegistryStartTracking(inRep2);
	CrFwInRegistryStartTracking(inCmd3);

	cmpData = (CrFwCmpData_t*)FwSmGetData(inRep1);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryPending)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(inRep2);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryPending)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(inCmd3);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryPending)
		return 0;

	/* Reset InRegistry and check success */
	CrFwCmpReset(inRegistry);
	cmpData = (CrFwCmpData_t*)FwSmGetData(inRep1);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryNotTracked)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(inRep2);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryNotTracked)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(inCmd3);
	if (CrFwInRegistryGetState(cmpData->instanceId) != crInRegistryNotTracked)
		return 0;

	/* Release all reports and commands */
	CrFwInFactoryReleaseInRep(inRep1);
	CrFwInFactoryReleaseInRep(inRep2);
	CrFwInFactoryReleaseInCmd(inCmd3);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

