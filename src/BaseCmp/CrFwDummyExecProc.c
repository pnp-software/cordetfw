/**
 * @file
 *
 * Implementation of Dummy Component Execution Procedure.
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

#include <stdlib.h>
#include "CrFwInitProc.h"
#include "CrFwBaseCmp.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* FW Profile Files */
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"

/** The singleton instance of the CIP. */
static FwPrDesc_t dummyExecPrDesc = NULL;

/* ----------------------------------------------------------------------------------------------------------------- */
void CwFwBaseCmpDummyExecAction(FwPrDesc_t prDesc) {
	CRFW_UNUSED(prDesc);
	return;
}

/*-----------------------------------------------------------------------------------------*/
FwPrDesc_t CrFwBaseCmpGetDummyExecProc() {
	const FwPrCounterS1_t nOfANodes = 1;	/* Number of action nodes */
	const FwPrCounterS1_t nOfDNodes = 0;	/* Number of decision nodes */
	const FwPrCounterS1_t nOfFlows = 2;		/* Number of control flows */
	const FwPrCounterS1_t nOfActions = 1;	/* Number of actions */
	const FwPrCounterS1_t nOfGuards = 1;	/* Number of guards */
	const FwPrCounterS1_t N1 = 1;			/* Identifier of first action node */

	if (dummyExecPrDesc != NULL)
		return dummyExecPrDesc;

	/* Create the execution procedure */
	dummyExecPrDesc = FwPrCreate(nOfANodes, nOfDNodes, nOfFlows, nOfActions, nOfGuards);

	/* Configure the initialization procedure */
	FwPrAddActionNode(dummyExecPrDesc, N1, &CwFwBaseCmpDummyExecAction);
	FwPrAddFlowIniToAct(dummyExecPrDesc, N1, NULL);
	FwPrAddFlowActToAct(dummyExecPrDesc, N1, N1, &CrFwWaitOnePrCycle);

	return dummyExecPrDesc;
}





