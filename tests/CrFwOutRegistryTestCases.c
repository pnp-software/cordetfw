/**
 * @file
 *
 * Implementation of test cases for OutRegistry Component.
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
#include "CrFwOutRegistryUserPar.h"
#include "OutRegistry/CrFwOutRegistry.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "OutFactory/CrFwOutFactory.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include configuration files */
#include "CrFwRepErrStub.h"
#include "CrFwOutRegistryTestCases.h"
#include "CrFwCmpData.h"

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutRegistryTestCase1() {
	FwSmDesc_t outRegistry1, outRegistry2;
	CrFwCmpData_t* outRegistryData;

	/* Instantiate the OutRegistry */
	outRegistry1 = CrFwOutRegistryMake();
	if (outRegistry1 == NULL)
		return 0;

	/* Instantiate it again and check that same component is returned */
	outRegistry2 = CrFwOutRegistryMake();
	if (outRegistry1 != outRegistry2)
		return 0;

	/* Check configuration of OutRegistry */
	if (FwSmCheckRec(outRegistry1) != smSuccess)
		return 0;

	/* Initialize outRegistry and check success */
	if (!CrFwCmpIsInCreated(outRegistry1))
		return 0;

	CrFwCmpInit(outRegistry1);
	if (!CrFwCmpIsInInitialized(outRegistry1))
		return 0;

	/* Reset OutRegistry */
	CrFwCmpReset(outRegistry1);
	if (!CrFwCmpIsInConfigured(outRegistry1))
		return 0;

	/* Check component type */
	outRegistryData = (CrFwCmpData_t*)FwSmGetData(outRegistry1);
	if (outRegistryData->instanceId != 0)
		return 0;
	if (outRegistryData->typeId != CR_FW_OUTREGISTRY_TYPE)
		return 0;

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutRegistryTestCase2() {

	if (CrFwOutRegistryGetServType(0) != 1)
		return 0;

	if (CrFwOutRegistryGetServType(8) != 25)
		return 0;

	if (CrFwOutRegistryGetServType(4) != 5)
		return 0;

	if (CrFwOutRegistryGetServSubType(0) != 1)
		return 0;

	if (CrFwOutRegistryGetServSubType(8) != 3)
		return 0;

	if (CrFwOutRegistryGetServSubType(4) != 1)
		return 0;

	if (CrFwOutRegistryGetCmdRepIndex(56,3) != CR_FW_OUTREGISTRY_NSERV)
		return 0;

	if (CrFwOutRegistryGetCmdRepIndex(24,3) != CR_FW_OUTREGISTRY_NSERV)
		return 0;

	if (CrFwOutRegistryGetCmdRepIndex(1,23) != CR_FW_OUTREGISTRY_NSERV)
		return 0;

	if (CrFwOutRegistryGetCmdRepIndex(1,3) != CR_FW_OUTREGISTRY_NSERV)
		return 0;

	if (CrFwOutRegistryGetCmdRepIndex(1,7) != 2)
		return 0;

	if (CrFwOutRegistryGetCmdRepIndex(1,1) != 0)
		return 0;

	if (CrFwOutRegistryGetCmdRepIndex(1,8) != 3)
		return 0;

	if (CrFwOutRegistryGetCmdRepIndex(25,3) != 8)
		return 0;

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutRegistryTestCase3() {
	FwSmDesc_t outRegistry, outFactory, outCmp;

	/* Instantiate the OutRegistry */
	outRegistry = CrFwOutRegistryMake();
	if (outRegistry == NULL)
		return 0;

	/* Initialize and configure outRegistry */
	CrFwCmpInit(outRegistry);
	CrFwCmpReset(outRegistry);
	if (!CrFwCmpIsInConfigured(outRegistry))
		return 0;

	/* Instantiate the OutFactory */
	outFactory = CrFwOutFactoryMake();
	if (outFactory == NULL)
		return 0;

	/* Check configuration of OutFactory */
	if (FwSmCheckRec(outFactory) != smSuccess)
		return 0;

	/* Initialize OutFactory and check success */
	if (!CrFwCmpIsInCreated(outFactory))
		return 0;

	CrFwCmpInit(outFactory);
	if (!CrFwCmpIsInInitialized(outFactory))
		return 0;

	/* Reset OutFactory */
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Retrieve an OutComponent from the OutFactory (see CrFwOutRegistryUserPar.h) */
	outCmp = CrFwOutFactoryMakeOutCmp(50,1,0,0);

	/* Check that OutComponent is enabled */
	if (CrFwOutRegistryIsEnabled(outCmp) != 1)
		return 0;

	/* Disable OutComponent's service type and check OutComponent's enable state */
	CrFwOutRegistrySetEnable(50,0,0,0);
	if (CrFwOutRegistryIsEnabled(outCmp) != 0)
		return 0;

	/* Reset enable state */
	CrFwOutRegistrySetEnable(50,0,0,1);
	if (CrFwOutRegistryIsEnabled(outCmp) != 1)
		return 0;

	/* Disable OutComponent's service sub-type and check OutComponent's enable state */
	CrFwOutRegistrySetEnable(50,1,0,0);
	if (CrFwOutRegistryIsEnabled(outCmp) != 0)
		return 0;

	/* Reset enable state */
	CrFwOutRegistrySetEnable(50,1,0,1);
	if (CrFwOutRegistryIsEnabled(outCmp) != 1)
		return 0;

	/* Release OutComponent */
	CrFwOutFactoryReleaseOutCmp(outCmp);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutRegistryTestCase4() {
	FwSmDesc_t outRegistry, outFactory, outCmp;

	/* Instantiate the OutRegistry */
	outRegistry = CrFwOutRegistryMake();
	if (outRegistry == NULL)
		return 0;

	/* Initialize and configure OutRegistry */
	CrFwCmpInit(outRegistry);
	CrFwCmpReset(outRegistry);
	if (!CrFwCmpIsInConfigured(outRegistry))
		return 0;

	/* Instantiate the OutFactory */
	outFactory = CrFwOutFactoryMake();
	if (outFactory == NULL)
		return 0;

	/* Initialize and configure OutFactory */
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Retrieve an OutComponent from the OutFactory (see CrFwOutRegistryUserPar.h and CrFwOutFactoryUserPar.h) */
	outCmp = CrFwOutFactoryMakeOutCmp(1,2,2,0);

	/* Check that OutComponent is enabled */
	if (CrFwOutRegistryIsEnabled(outCmp) != 1)
		return 0;

	/* Disable OutComponent's service type and check OutComponent's enable state */
	CrFwOutRegistrySetEnable(1,0,0,0);
	if (CrFwOutRegistryIsEnabled(outCmp) != 0)
		return 0;

	/* Reset enable state */
	CrFwOutRegistrySetEnable(1,0,0,1);
	if (CrFwOutRegistryIsEnabled(outCmp) != 1)
		return 0;

	/* Disable OutComponent's service sub-type and check OutComponent's enable state */
	CrFwOutRegistrySetEnable(1,2,0,0);
	if (CrFwOutRegistryIsEnabled(outCmp) != 0)
		return 0;

	/* Reset enable state */
	CrFwOutRegistrySetEnable(1,2,0,1);
	if (CrFwOutRegistryIsEnabled(outCmp) != 1)
		return 0;

	/* Disable OutComponent's discriminant and check OutComponent's enable state */
	CrFwOutRegistrySetEnable(1,2,2,0);
	if (CrFwOutRegistryIsEnabled(outCmp) != 0)
		return 0;

	/* Reset enable state */
	CrFwOutRegistrySetEnable(1,2,2,1);
	if (CrFwOutRegistryIsEnabled(outCmp) != 1)
		return 0;

	/* Release OutComponent */
	CrFwOutFactoryReleaseOutCmp(outCmp);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutRegistryTestCase5() {
	FwSmDesc_t outRegistry, outFactory, outCmp1, outCmp2;

	/* Instantiate the OutRegistry */
	outRegistry = CrFwOutRegistryMake();
	if (outRegistry == NULL)
		return 0;

	/* Initialize and configure OutRegistry */
	CrFwCmpInit(outRegistry);
	CrFwCmpReset(outRegistry);
	if (!CrFwCmpIsInConfigured(outRegistry))
		return 0;

	/* Instantiate the OutFactory */
	outFactory = CrFwOutFactoryMake();
	if (outFactory == NULL)
		return 0;

	/* Initialize and configure OutFactory */
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Retrieve two OutComponents from the OutFactory (see CrFwOutRegistryUserPar.h and CrFwOutFactoryUserPar.h) */
	outCmp1 = CrFwOutFactoryMakeOutCmp(5,3,30,0);
	outCmp2 = CrFwOutFactoryMakeOutCmp(5,3,31,0);

	/* Check that OutComponents are enabled */
	if (CrFwOutRegistryIsEnabled(outCmp1) != 1)
		return 0;
	if (CrFwOutRegistryIsEnabled(outCmp2) != 1)
		return 0;

	/* Disable the first OutComponent */
	CrFwOutRegistrySetEnable(5,3,30,0);
	if (CrFwOutRegistryIsEnabled(outCmp1) != 0)
		return 0;
	if (CrFwOutRegistryIsEnabled(outCmp2) != 1)
		return 0;

	/* Disable the second OutComponent */
	CrFwOutRegistrySetEnable(5,3,30,1);
	CrFwOutRegistrySetEnable(5,3,31,0);
	if (CrFwOutRegistryIsEnabled(outCmp1) != 1)
		return 0;
	if (CrFwOutRegistryIsEnabled(outCmp2) != 0)
		return 0;

	/* Disable both OutComponents */
	CrFwOutRegistrySetEnable(5,3,30,0);
	CrFwOutRegistrySetEnable(5,3,31,0);
	if (CrFwOutRegistryIsEnabled(outCmp1) != 0)
		return 0;
	if (CrFwOutRegistryIsEnabled(outCmp2) != 0)
		return 0;

	/* Enable both OutComponents */
	CrFwOutRegistrySetEnable(5,3,30,1);
	CrFwOutRegistrySetEnable(5,3,31,1);
	if (CrFwOutRegistryIsEnabled(outCmp1) != 1)
		return 0;
	if (CrFwOutRegistryIsEnabled(outCmp2) != 1)
		return 0;

	/* Release OutComponents */
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

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutRegistryTestCase6() {
	FwSmDesc_t outRegistry;

	/* Instantiate the OutRegistry */
	outRegistry = CrFwOutRegistryMake();
	if (outRegistry == NULL)
		return 0;

	/* Initialize and configure OutRegistry */
	CrFwCmpInit(outRegistry);
	CrFwCmpReset(outRegistry);
	if (!CrFwCmpIsInConfigured(outRegistry))
		return 0;

	/* Disable non-existent service types */
	CrFwOutRegistrySetEnable(4,0,0,0);
	if (CrFwGetAppErrCode() != crIllServType)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);
	CrFwOutRegistrySetEnable(150,0,0,0);
	if (CrFwGetAppErrCode() != crIllServType)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);

	/* Disable non-existent service sub-type */
	CrFwOutRegistrySetEnable(25,2,0,0);
	if (CrFwGetAppErrCode() != crIllServSubType)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);
	CrFwOutRegistrySetEnable(25,4,0,0);
	if (CrFwGetAppErrCode() != crIllServSubType)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);

	/* Disable non-existent discriminant value */
	CrFwOutRegistrySetEnable(5,4,41,0);
	if (CrFwGetAppErrCode() != crIllDiscriminant)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutRegistryTestCase7() {
	FwSmDesc_t outRegistry, outFactory, outCmp1, outCmp2, outCmp3;
	CrFwCounterU2_t i;
	CrFwCmpData_t* cmpData;

	/* Instantiate the OutRegistry */
	outRegistry = CrFwOutRegistryMake();
	if (outRegistry == NULL)
		return 0;

	/* Initialize and configure OutRegistry */
	CrFwCmpInit(outRegistry);
	CrFwCmpReset(outRegistry);
	if (!CrFwCmpIsInConfigured(outRegistry))
		return 0;

	/* Instantiate the OutFactory */
	outFactory = CrFwOutFactoryMake();
	if (outFactory == NULL)
		return 0;

	/* Initialize and configure OutFactory */
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Retrieve three OutComponents from the OutFactory (see CrFwOutRegistryUserPar.h and CrFwOutFactoryUserPar.h) */
	outCmp1 = CrFwOutFactoryMakeOutCmp(5,3,30,0);
	outCmp2 = CrFwOutFactoryMakeOutCmp(5,3,31,0);
	outCmp3 = CrFwOutFactoryMakeOutCmp(5,3,31,0);

	CrFwOutRegistryStartTracking(outCmp1);
	CrFwOutRegistryStartTracking(outCmp2);
	CrFwOutRegistryStartTracking(outCmp3);

	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp1);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryPending)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp2);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryPending)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp3);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryPending)
		return 0;

	CrFwOutRegistryUpdateState(outCmp2, crOutRegistryAborted);
	CrFwOutRegistryUpdateState(outCmp1, crOutRegistryTerminated);
	CrFwOutRegistryUpdateState(outCmp3, crOutRegistryAborted);

	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp1);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryTerminated)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp2);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryAborted)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp3);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryAborted)
		return 0;

	for (i=0; i<CR_FW_OUTREGISTRY_N; i++) {
		CrFwOutFactoryReleaseOutCmp(outCmp1);
		outCmp1 = CrFwOutFactoryMakeOutCmp(5,3,30,0);
		CrFwOutRegistryStartTracking(outCmp1);
	}

	CrFwOutRegistryUpdateState(outCmp3, crOutRegistryTerminated);

	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp1);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryPending)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp2);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryNotTracked)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp3);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryNotTracked)
		return 0;

	/* Release all OutComponents */
	CrFwOutFactoryReleaseOutCmp(outCmp1);
	CrFwOutFactoryReleaseOutCmp(outCmp2);
	CrFwOutFactoryReleaseOutCmp(outCmp3);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutRegistryTestCase8() {
	FwSmDesc_t outRegistry, outFactory, outCmp1, outCmp2, outCmp3;
	CrFwCmpData_t* cmpData;

	/* Instantiate the OutRegistry */
	outRegistry = CrFwOutRegistryMake();
	if (outRegistry == NULL)
		return 0;

	/* Initialize and configure OutRegistry */
	CrFwCmpInit(outRegistry);
	CrFwCmpReset(outRegistry);
	if (!CrFwCmpIsInConfigured(outRegistry))
		return 0;

	/* Instantiate the OutFactory */
	outFactory = CrFwOutFactoryMake();
	if (outFactory == NULL)
		return 0;

	/* Initialize and configure OutFactory */
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Retrieve three OutComponents from the OutFactory (see CrFwOutRegistryUserPar.h and CrFwOutFactoryUserPar.h) */
	outCmp1 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	outCmp2 = CrFwOutFactoryMakeOutCmp(25,3,0,0);
	outCmp3 = CrFwOutFactoryMakeOutCmp(5,4,3,0);

	CrFwOutRegistryStartTracking(outCmp1);
	CrFwOutRegistryStartTracking(outCmp2);
	CrFwOutRegistryStartTracking(outCmp3);

	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp1);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryPending)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp2);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryPending)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp3);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryPending)
		return 0;

	/* Disable service 1, service (5,1) and service (5,4,3) */
	CrFwOutRegistrySetEnable(1,0,0,0);
	CrFwOutRegistrySetEnable(25,3,0,0);
	CrFwOutRegistrySetEnable(5,4,3,0);

	if (CrFwOutRegistryIsEnabled(outCmp1) == 1)
		return 0;
	if (CrFwOutRegistryIsEnabled(outCmp2) == 1)
		return 0;
	if (CrFwOutRegistryIsEnabled(outCmp3) == 1)
		return 0;

	/* Shutdown OutRegistry and check success */
	CrFwCmpShutdown(outRegistry);
	if (CrFwCmpIsStarted(outRegistry) == 1)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp1);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryNotTracked)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp2);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryNotTracked)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp3);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryNotTracked)
		return 0;

	/* Release all OutComponents */
	CrFwOutFactoryReleaseOutCmp(outCmp1);
	CrFwOutFactoryReleaseOutCmp(outCmp2);
	CrFwOutFactoryReleaseOutCmp(outCmp3);

	/* Restart the OutRegistry */
	FwSmStart(outRegistry);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutRegistryTestCase9() {
	FwSmDesc_t outRegistry, outFactory, outCmp1, outCmp2, outCmp3;
	CrFwCmpData_t* cmpData;

	/* Instantiate the OutRegistry */
	outRegistry = CrFwOutRegistryMake();
	if (outRegistry == NULL)
		return 0;

	/* Initialize and configure OutRegistry */
	CrFwCmpInit(outRegistry);
	CrFwCmpReset(outRegistry);
	if (!CrFwCmpIsInConfigured(outRegistry))
		return 0;

	/* Instantiate the OutFactory */
	outFactory = CrFwOutFactoryMake();
	if (outFactory == NULL)
		return 0;

	/* Initialize and configure OutFactory */
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Retrieve three OutComponents from the OutFactory (see CrFwOutRegistryUserPar.h and CrFwOutFactoryUserPar.h) */
	outCmp1 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	outCmp2 = CrFwOutFactoryMakeOutCmp(25,3,0,0);
	outCmp3 = CrFwOutFactoryMakeOutCmp(5,4,3,0);

	CrFwOutRegistryStartTracking(outCmp1);
	CrFwOutRegistryStartTracking(outCmp2);
	CrFwOutRegistryStartTracking(outCmp3);

	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp1);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryPending)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp2);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryPending)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp3);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryPending)
		return 0;

	/* Disable service 1, service (5,1) and service (5,4,3) */
	CrFwOutRegistrySetEnable(1,0,0,0);
	CrFwOutRegistrySetEnable(25,3,0,0);
	CrFwOutRegistrySetEnable(5,4,3,0);

	if (CrFwOutRegistryIsEnabled(outCmp1) == 1)
		return 0;
	if (CrFwOutRegistryIsEnabled(outCmp2) == 1)
		return 0;
	if (CrFwOutRegistryIsEnabled(outCmp3) == 1)
		return 0;

	/* Reset OutRegistry and check success */
	CrFwCmpReset(outRegistry);
	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp1);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryNotTracked)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp2);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryNotTracked)
		return 0;
	cmpData = (CrFwCmpData_t*)FwSmGetData(outCmp3);
	if (CrFwOutRegistryGetState(cmpData->instanceId) != crOutRegistryNotTracked)
		return 0;
	if (CrFwOutRegistryIsEnabled(outCmp1) != 1)
		return 0;
	if (CrFwOutRegistryIsEnabled(outCmp2) != 1)
		return 0;
	if (CrFwOutRegistryIsEnabled(outCmp3) != 1)
		return 0;

	/* Release all OutComponents */
	CrFwOutFactoryReleaseOutCmp(outCmp1);
	CrFwOutFactoryReleaseOutCmp(outCmp2);
	CrFwOutFactoryReleaseOutCmp(outCmp3);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

