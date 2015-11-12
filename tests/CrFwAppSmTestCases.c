/**
 * @file
 *
 * Implementation of test cases for the Application State Machine.
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
#include "CrFwAppSmTestCases.h"
/* Include FW Profile files */
#include "FwProfile/FwSmConstants.h"
#include "FwProfile/FwSmConfig.h"
#include "FwProfile/FwSmSCreate.h"
#include "FwProfile/FwSmCore.h"
#include "FwProfile/FwPrConfig.h"
#include "FwProfile/FwPrCore.h"
#include "FwProfile/FwPrConstants.h"
/* Include framework files */
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "AppStartUp/CrFwAppSm.h"
#include "AppStartUp/CrFwAppResetProc.h"
#include "AppStartUp/CrFwAppShutdownProc.h"
#include "AppStartUp/CrFwAppStartUpProc.h"
/* Include configuration files */
#include "CrFwAppSmUserPar.h"

/* Dummy state machine to be embedded in state START-UP of the Application State Machine */
FW_SM_INST_NOCPS(startUpEsmDesc, 1, 1, 0, 0)

/* Dummy state machine to be embedded in state NORMAL of the Application State Machine */
FW_SM_INST_NOCPS(normalEsmDesc, 1, 1, 0, 0)

/* Dummy state machine to be embedded in state RESET of the Application State Machine */
FW_SM_INST_NOCPS(resetEsmDesc, 1, 1, 0, 0)

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwAppSmTestCase1() {
	FwSmDesc_t appSm;

	/* Initialize and configure embedded state machines */
	FwSmInit(&startUpEsmDesc);
	FwSmAddState(&startUpEsmDesc, 1, 0, NULL, NULL, NULL, NULL);	/* 1 state with no out-going transitions */
	FwSmAddTransIpsToSta(&startUpEsmDesc, 1, NULL);

	FwSmInit(&normalEsmDesc);
	FwSmAddState(&normalEsmDesc, 1, 0, NULL, NULL, NULL, NULL);	/* 1 state with no out-going transitions */
	FwSmAddTransIpsToSta(&normalEsmDesc, 1, NULL);

	FwSmInit(&resetEsmDesc);
	FwSmAddState(&resetEsmDesc, 1, 0, NULL, NULL, NULL, NULL);	/* 1 state with no out-going transitions */
	FwSmAddTransIpsToSta(&resetEsmDesc, 1, NULL);


	/* Instantiate the Application State Machine (ASM) */
	appSm = CrFwAppSmMake();

	/* Check that ASM has not yet been started */
	if (CrFwAppSmIsStarted())
		return 0;

	/* Check ASM configuration */
	if (FwSmCheck(appSm) != 1)
		return 0;

	/* Attempt to instantiate the ASM a second time */
	if (appSm != CrFwAppSmMake())
		return 0;

	/* Check embedded SMs */
	if (CrFwAppSmGetEsmStartUp() != &startUpEsmDesc)
		return 0;
	if (CrFwAppSmGetEsmNormal() != &normalEsmDesc)
		return 0;
	if (CrFwAppSmGetEsmReset() != &resetEsmDesc)
		return 0;
	if (CrFwAppSmGetEsmShutdown() != NULL)
		return 0;

	/* Start ASM */
	CrFwAppSmStart();
	if (!CrFwAppSmIsInStartUp())
		return 0;
	if (!FwPrIsStarted(CrFwAppSmGetAppStartUpProc()))
		return 0;

	/* Execute the ASM -- ASM should remain in START_UP */
	CrFwAppSmExecute();
	if (!CrFwAppSmIsInStartUp())
		return 0;

	/* Execute the Start-Up Procedure twice */
	FwPrExecute(CrFwAppSmGetAppStartUpProc());
	FwPrExecute(CrFwAppSmGetAppStartUpProc());
	if (FwPrIsStarted(CrFwAppSmGetAppStartUpProc()))
		return 0;

	/* Execute the ASM -- ASM should be in NORMAL */
	CrFwAppSmExecute();
	if (!CrFwAppSmIsInNormal())
		return 0;

	/* Reset the ASM -- ASM should enter RESET */
	CrFwAppSmReset();
	if (!CrFwAppSmIsInReset())
		return 0;
	if (!FwPrIsStarted(CrFwAppSmGetAppResetProc()))
		return 0;

	/* Execute the Reset Procedure twice */
	FwPrExecute(CrFwAppSmGetAppResetProc());
	FwPrExecute(CrFwAppSmGetAppResetProc());
	if (FwPrIsStarted(CrFwAppSmGetAppResetProc()))
		return 0;

	/* Execute the ASM -- ASM should be in NORMAL */
	CrFwAppSmExecute();
	if (!CrFwAppSmIsInNormal())
		return 0;

	/* Shutdown the ASM -- ASM should enter SHUTDOWN */
	CrFwAppSmShutdown();
	if (!CrFwAppSmIsInShutdown())
		return 0;
	if (!FwPrIsStarted(CrFwAppSmGetAppShutdownProc()))
		return 0;

	/* Execute the Shutdown Procedure twice */
	FwPrExecute(CrFwAppSmGetAppShutdownProc());
	FwPrExecute(CrFwAppSmGetAppShutdownProc());
	if (FwPrIsStarted(CrFwAppSmGetAppShutdownProc()))
		return 0;

	/* Execute the ASM -- ASM should be stopped */
	CrFwAppSmExecute();
	if (CrFwAppSmIsStarted())
		return 0;

	return 1;
}

FwSmDesc_t CrFwAppSmTestCasesGetStartUpEsm() {
	return &startUpEsmDesc;
}

FwSmDesc_t CrFwAppSmTestCasesGetNormalEsm()  {
	return &normalEsmDesc;
}

FwSmDesc_t CrFwAppSmTestCasesGetResetEsm()  {
	return &resetEsmDesc;
}
