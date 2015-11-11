/**
 * @file
 *
 * Implementation of Dummy Component Execution Procedure.
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
#include "CrFwInitProc.h"
#include "CrFwBaseCmp.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* FW Profile Files */
#include "FwProfile/FwPrConstants.h"
#include "FwProfile/FwPrDCreate.h"
#include "FwProfile/FwPrConfig.h"
#include "FwProfile/FwPrCore.h"

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





