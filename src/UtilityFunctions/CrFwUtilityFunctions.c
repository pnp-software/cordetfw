/**
 * @file
 * Implementation of utility functions.
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
FwPrBool_t CrFwIsPrOutcomeOne(FwPrDesc_t prDesc) {
	CrFwCmpData_t* prData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	return (prData->outcome);
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
	pos_half = length/2;
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
