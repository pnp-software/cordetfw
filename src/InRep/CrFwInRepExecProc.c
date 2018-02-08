/**
 * @file
 *
 * Implementation of InReport Execution Procedure.
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




