/**
 * @file
 *
 * Implementation of Component Initialization Procedure.
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

#include <stdlib.h>
/* Include framework files */
#include "CrFwInitProc.h"
#include "CrFwBaseCmp.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include configuration files */
#include "CrFwCmpData.h"
/* Include FW Profile files */
#include "FwProfile/FwPrConstants.h"
#include "FwProfile/FwPrDCreate.h"
#include "FwProfile/FwPrConfig.h"
#include "FwProfile/FwPrCore.h"

/** The singleton instance of the CIP. */
static FwPrDesc_t initPrDesc = NULL;

/*-----------------------------------------------------------------------------------------*/
void CrFwBaseCmpDefInitCheck(FwPrDesc_t prDesc) {
	CrFwCmpData_t* prData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	prData->outcome = 1;
	return;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwBaseCmpDefInitAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* prData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	prData->outcome = 1;
	return;
}

/*-----------------------------------------------------------------------------------------*/
FwPrDesc_t CrFwCmpGetInitProc() {
	const FwPrCounterS1_t nOfANodes = 2;	/* Number of action nodes */
	const FwPrCounterS1_t nOfDNodes = 1;	/* Number of decision nodes */
	const FwPrCounterS1_t nOfFlows = 5;		/* Number of control flows */
	const FwPrCounterS1_t nOfActions = 2;	/* Number of actions */
	const FwPrCounterS1_t nOfGuards = 1;	/* Number of guards */
	const FwPrCounterS1_t N1 = 1;			/* Identifier of first action node */
	const FwPrCounterS1_t N2 = 2;			/* Identifier of second action node */
	const FwPrCounterS1_t D1 = 1;			/* Identifier of first decision node */

	if (initPrDesc != NULL)
		return initPrDesc;

	/* Create the initialization procedure */
	initPrDesc = FwPrCreate(nOfANodes, nOfDNodes, nOfFlows, nOfActions, nOfGuards);

	/* Configure the initialization procedure */
	FwPrAddActionNode(initPrDesc, N1, &CrFwBaseCmpDefInitCheck);
	FwPrAddActionNode(initPrDesc, N2, &CrFwBaseCmpDefInitAction);
	FwPrAddDecisionNode(initPrDesc, D1, 2);
	FwPrAddFlowIniToAct(initPrDesc, N1, NULL);
	FwPrAddFlowActToDec(initPrDesc, N1, D1, NULL);
	FwPrAddFlowDecToAct(initPrDesc, D1, N2, &CrFwIsPrOutcomeOne);
	FwPrAddFlowDecToFin(initPrDesc, D1, NULL);	/* Else branch */
	FwPrAddFlowActToFin(initPrDesc, N2, NULL);

	return initPrDesc;
}





