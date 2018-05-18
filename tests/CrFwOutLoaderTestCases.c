/**
 * @file
 *
 * Implementation of test cases for OutLoader component.
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
#include "CrFwOutLoaderTestCases.h"
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
#include "OutLoader/CrFwOutLoader.h"
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
CrFwBool_t CrFwOutLoaderTestCase1() {
	FwSmDesc_t outManager1, outLoader, outFactory, outLoader2;
	FwSmDesc_t outCmp, outCmp1, outCmp2, outCmp3, outCmp4;
	CrFwOutFactoryPoolIndex_t n;

	/* Instantiate the OutLoader */
	outLoader = CrFwOutLoaderMake();

	/* Check current state of OutLoader */
	if (!CrFwCmpIsInCreated(outLoader))
		return 0;

	/* Initialize and Configure OutLoader and check success */
	CrFwCmpInit(outLoader);
	if (!CrFwCmpIsInInitialized(outLoader))
		return 0;
	CrFwCmpReset(outLoader);
	if (!CrFwCmpIsInConfigured(outLoader))
		return 0;

	/* Instantiate OutLoader a second time and check that it is the same as the first instance */
	outLoader2 = CrFwOutLoaderMake();
	if (outLoader != outLoader2)
		return 0;

	/* Check Instance and Type Identifiers */
	if (CrFwCmpGetInstanceId(outLoader) != 0)
		return 0;
	if (CrFwCmpGetTypeId(outLoader) != CR_FW_OUTLOADER_TYPE)
		return 0;

	/* Initialize and Configure OutManager and check success */
	outManager1 = CrFwOutManagerMake(0);
	CrFwCmpInit(outManager1);
	CrFwCmpReset(outManager1);
	if (!CrFwCmpIsInConfigured(outManager1))
		return 0;

	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	/* Initialize and Configure OutFactory and check success */
	outFactory = CrFwOutFactoryMake();
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Allocate an OutComponent */
	outCmp = CrFwOutFactoryMakeOutCmp(1,1,0,0);

	/* Check that there are no pending OutComponents in OutManager */
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager1) != 0)
		return 0;

	/* Load OutComponent in OutLoader and check success */
	if (CrFwOutLoaderLoad(outCmp) != 1)
		return 0;
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager1) != 1)
		return 0;

	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	/* Fill up the OutManager so that its POCL becomes full
	 * (we assume the POCL to have a size of 4, see: CR_FW_NOF_OUTMANAGER) */
	outCmp1 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	outCmp2 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	outCmp3 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	CrFwOutManagerLoad(outManager1, outCmp1);
	CrFwOutManagerLoad(outManager1, outCmp2);
	CrFwOutManagerLoad(outManager1, outCmp3);

	/* Create one more OutComponent and attempt to load it and then verify
	 * that the attempt fails and the OutComponent is released */
	outCmp4 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	n = CrFwOutFactoryGetNOfAllocatedOutCmp();
	if (CrFwOutLoaderLoad(outCmp4) != 0)
		return 0;
	if (CrFwOutFactoryGetNOfAllocatedOutCmp() != (n-1))
		return 0;

	/* Reset OutManager */
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


