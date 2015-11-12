/**
 * @file
 *
 * Implementation of test cases for OutLoader component.
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
#include "CrFwOutLoaderTestCases.h"
/* Include FW Profile files */
#include "FwProfile/FwSmConstants.h"
#include "FwProfile/FwSmConfig.h"
#include "FwProfile/FwSmCore.h"
#include "FwProfile/FwPrConfig.h"
#include "FwProfile/FwPrCore.h"
#include "FwProfile/FwPrConstants.h"
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
	FwSmDesc_t outManager1, outLoader, outCmp, outFactory, outLoader2;

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
	CrFwOutLoaderLoad(outCmp);
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager1) != 1)
		return 0;

	if (CrFwGetAppErrCode() != crNoAppErr)
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


