/**
 * @file
 *
 * Implementation of InReport Execution Procedure.
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
/* Configuration Files */
#include "CrFwCmpData.h"
/* Framework Files */
#include "CrFwInRepExecProc.h"
#include "CrFwInRep.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* FW Profile Files */
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"

/**
 * Function implementing the action of the single node in the Report Execution Procedure.
 * @param prDesc the procedure descriptor
 */
static void CwFwInRepExecAction(FwPrDesc_t prDesc);

/*-----------------------------------------------------------------------------------------*/
FwPrDesc_t CrFwInRepExecProcMake() {
	const FwPrCounterS1_t nOfANodes = 1;	/* Number of action nodes */
	const FwPrCounterS1_t nOfDNodes = 0;	/* Number of decision nodes */
	const FwPrCounterS1_t nOfFlows = 2;		/* Number of control flows */
	const FwPrCounterS1_t nOfActions = 1;	/* Number of actions */
	const FwPrCounterS1_t nOfGuards = 0;	/* Number of guards */
	const FwPrCounterS1_t N1 = 1;			/* Identifier of first action node */
	FwPrDesc_t execProc;

	/* Create the execution procedure */
	execProc = FwPrCreate(nOfANodes, nOfDNodes, nOfFlows, nOfActions, nOfGuards);

	/* Configure the initialization procedure */
	FwPrAddActionNode(execProc, N1, &CwFwInRepExecAction);
	FwPrAddFlowIniToAct(execProc, N1, NULL);
	FwPrAddFlowActToFin(execProc, N1, NULL);

	return execProc;
}

/* ----------------------------------------------------------------------------------------------------------------- */
static void CwFwInRepExecAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwInRepData_t* cmpSpecificData = (CrFwInRepData_t*)(cmpData->cmpSpecificData);

	cmpSpecificData->updateAction(prDesc);
	return;
}




