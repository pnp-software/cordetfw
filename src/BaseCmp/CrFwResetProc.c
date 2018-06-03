/**
 * @file
 *
 * Implementation of Component Reset Procedure.
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
#include "CrFwResetProc.h"
#include "CrFwBaseCmp.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "CrFwCmpData.h"

/** The singleton instance of the CRP. */
static FwPrDesc_t resetPrDesc = NULL;

/*-----------------------------------------------------------------------------------------*/
void CrFwBaseCmpDefConfigCheck(FwPrDesc_t prDesc) {
	CrFwSetPrOutcome(prDesc, 1);
	return;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwBaseCmpDefConfigAction(FwPrDesc_t prDesc) {
	CrFwSetPrOutcome(prDesc, 1);
	return;
}

/*-----------------------------------------------------------------------------------------*/
FwPrDesc_t CrFwCmpGetResetProc() {
	FwPrCounterS1_t nOfANodes = 2;	/* Number of action nodes */
	FwPrCounterS1_t nOfDNodes = 1;	/* Number of decision nodes */
	FwPrCounterS1_t nOfFlows = 5;		/* Number of control flows */
	FwPrCounterS1_t nOfActions = 2;	/* Number of actions */
	FwPrCounterS1_t nOfGuards = 1;	/* Number of guards */
	FwPrCounterS1_t N1 = 1;			/* Identifier of first action node */
	FwPrCounterS1_t N2 = 2;			/* Identifier of second action node */
	FwPrCounterS1_t D1 = 1;			/* Identifier of first decision node */

	if (resetPrDesc != NULL)
		return resetPrDesc;

	/* Create the initialization procedure */
	resetPrDesc = FwPrCreate(nOfANodes, nOfDNodes, nOfFlows, nOfActions, nOfGuards);

	/* Configure the initialization procedure */
	FwPrAddActionNode(resetPrDesc, N1, &CrFwBaseCmpDefConfigCheck);
	FwPrAddActionNode(resetPrDesc, N2, &CrFwBaseCmpDefConfigAction);
	FwPrAddDecisionNode(resetPrDesc, D1, 2);
	FwPrAddFlowIniToAct(resetPrDesc, N1, NULL);
	FwPrAddFlowActToDec(resetPrDesc, N1, D1, NULL);
	FwPrAddFlowDecToAct(resetPrDesc, D1, N2, &CrFwIsPrOutcomeOne);
	FwPrAddFlowDecToFin(resetPrDesc, D1, NULL);	/* Else branch */
	FwPrAddFlowActToFin(resetPrDesc, N2, NULL);

	return resetPrDesc;
}





