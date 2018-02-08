/**
 * @file
 *
 * Implementation of test cases for Base Component.
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
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include Framework Files */
#include "BaseCmp/CrFwBaseCmp.h"
#include "BaseCmp/CrFwInitProc.h"
#include "BaseCmp/CrFwResetProc.h"
#include "BaseCmp/CrFwDummyExecProc.h"
#include "CrFwBaseCmpTestCases.h"
/* Include Configuration Files */
#include "CrFwCmpData.h"
#include "CrFwUserConstants.h"

CrFwBool_t CrFwBaseCmpTestCase1() {
	FwSmDesc_t baseCmp;
	FwPrDesc_t initProc, resetProc, execProc;
	CrFwCmpData_t baseCmpData;

	/* Create base component and its procedures */
	baseCmp = CrFwBaseCmpMake();
	if (CrFwCmpIsStarted(baseCmp) == 1)
		return 0;

	initProc = CrFwCmpGetInitProc();
	if (FwPrIsStarted(initProc) == 1)
		return 0;

	resetProc = CrFwCmpGetResetProc();
	if (FwPrIsStarted(resetProc) == 1)
		return 0;

	execProc = CrFwBaseCmpGetDummyExecProc();
	if (FwPrIsStarted(execProc) == 1)
		return 0;

	/* Attach procedures to base component */
	baseCmpData.initProc = initProc;
	baseCmpData.resetProc = resetProc;
	baseCmpData.execProc = execProc;
	FwSmSetData(baseCmp, &baseCmpData);
	FwPrSetData(initProc, &baseCmpData);
	FwPrSetData(resetProc, &baseCmpData);

	/* Check configuration of Base Component and its procedures */
	if (FwSmCheck(baseCmp) != smSuccess)
		return 0;
	if (FwPrCheck(initProc) != prSuccess)
		return 0;
	if (FwPrCheck(resetProc) != prSuccess)
		return 0;
	if (FwPrCheck(execProc) != prSuccess)
		return 0;

	/* Start and command base component into state CONFIGURED */
	FwSmStart(baseCmp);
	if (CrFwCmpIsStarted(baseCmp) != 1)
		return 0;
	if (!CrFwCmpIsInCreated(baseCmp))
		return 0;

	CrFwCmpInit(baseCmp);
	if (!CrFwCmpIsInInitialized(baseCmp))
		return 0;

	CrFwCmpReset(baseCmp);
	if (!CrFwCmpIsInConfigured(baseCmp))
		return 0;

	/* Shutdown base component */
	CrFwCmpShutdown(baseCmp);
	if (CrFwCmpIsStarted(baseCmp) == 1)
		return 0;

	/* Detach procedures from Base Component instance and bring it back to state STOPPED */
	FwSmStop(baseCmp);
	FwSmSetData(baseCmp, NULL);

	return 1;
}
