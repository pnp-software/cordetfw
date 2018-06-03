/**
 * @file
 * Implementation of utility functions.
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
/* Include framework files */
#include "CrFwConstants.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "BaseCmp/CrFwInitProc.h"
#include "BaseCmp/CrFwResetProc.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmDCreate.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
/* Include configuration files */
#include "CrFwCmpData.h"

/** The application error code. */
static CrFwAppErrCode_t appErrCode = crNoAppErr;

/*-----------------------------------------------------------------------------------------*/
CrFwAppErrCode_t CrFwGetAppErrCode() {
	return appErrCode;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwSetAppErrCode(CrFwAppErrCode_t errCode) {
	appErrCode = errCode;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwSetPrOutcome(FwPrDesc_t prDesc, CrFwOutcome_t outcome) {
	CrFwCmpData_t* prData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	prData->outcome = outcome;
}

/*-----------------------------------------------------------------------------------------*/
FwPrBool_t CrFwIsPrOutcomeOne(FwPrDesc_t prDesc) {
	CrFwCmpData_t* prData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	return (prData->outcome);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwSetSmOutcome(FwSmDesc_t smDesc, CrFwOutcome_t outcome) {
	CrFwCmpData_t* smData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	smData->outcome = outcome;
}

/*-----------------------------------------------------------------------------------------*/
FwSmBool_t CrFwIsSmOutcomeZero(FwSmDesc_t smDesc) {
	CrFwCmpData_t* smData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	return (smData->outcome == 0);
}


/*-----------------------------------------------------------------------------------------*/
FwSmBool_t CrFwIsSmOutcomeOne(FwSmDesc_t smDesc) {
	CrFwCmpData_t* smData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	return (smData->outcome == 1);
}

/*-----------------------------------------------------------------------------------------*/
FwSmBool_t CrFwIsSmOutcomeTwo(FwSmDesc_t smDesc) {
	CrFwCmpData_t* smData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	return (smData->outcome == 2);
}

/*-----------------------------------------------------------------------------------------*/
FwPrBool_t CrFwWaitOnePrCycle(FwPrDesc_t prDesc) {
	if (FwPrGetNodeExecCnt(prDesc) > 0)
		return 1;
	else
		return 0;
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwPrCheckAlwaysTrue(FwPrDesc_t prDesc) {
	CRFW_UNUSED(prDesc);
	return 1;
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwSmCheckAlwaysTrue(FwSmDesc_t smDesc) {
	CRFW_UNUSED(smDesc);
	return 1;
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwSmCheckAlwaysFalse(FwSmDesc_t smDesc) {
	CRFW_UNUSED(smDesc);
	return 0;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPrEmptyAction(FwPrDesc_t prDesc) {
	CRFW_UNUSED(prDesc);
	return;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwSmEmptyAction(FwSmDesc_t smDesc) {
	CRFW_UNUSED(smDesc);
	return;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCmdRepKindIndex_t CrFwFindCmdRepKindIndex(CrFwCmdRepKindKey_t* cmdRepKindArray,
        CrFwCmdRepKindIndex_t length, CrFwCmdRepKindKey_t targetKey) {

	CrFwCmdRepKindIndex_t pos_lower, pos_upper, pos_half;

	pos_lower = 0;
	pos_upper = (CrFwCmdRepKindIndex_t)(length-1);

	while (pos_lower < pos_upper) {
		pos_half = (CrFwCmdRepKindIndex_t)(pos_lower+(pos_upper-pos_lower)/2);
		if (pos_half == pos_lower)
			break;
		if (targetKey > cmdRepKindArray[pos_half]) {
			pos_lower = pos_half;
		} else if (targetKey < cmdRepKindArray[pos_half]) {
			pos_upper = pos_half;
		} else
			return pos_half;
	}

	if (targetKey == cmdRepKindArray[pos_lower])
		return pos_lower;

	if (targetKey == cmdRepKindArray[pos_upper])
		return pos_upper;

	return length;
}
