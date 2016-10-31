/**
 * @file
 *
 * Implementation of InReport component.
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
/* Include configuration files */
#include "CrFwCmpData.h"
/* Include framework files */
#include "CrFwConstants.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "InRep/CrFwInRep.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "BaseCmp/CrFwInitProc.h"
#include "BaseCmp/CrFwResetProc.h"
#include "BaseCmp/CrFwDummyExecProc.h"
#include "OutFactory/CrFwOutFactory.h"
#include "Pckt/CrFwPckt.h"
/* Include FW Profile files */
#include "FwPrConfig.h"
#include "FwPrDCreate.h"
#include "FwSmConfig.h"
#include "FwSmDCreate.h"
#include "FwPrCore.h"

/* --------------------------------------------------------------------------------- */
CrFwDestSrc_t CrFwInRepGetSrc(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInRepData_t* cmpSpecificData = (CrFwInRepData_t*)(cmpData->cmpSpecificData);

	return CrFwPcktGetSrc(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwGroup_t CrFwInRepGetGroup(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInRepData_t* cmpSpecificData = (CrFwInRepData_t*)(cmpData->cmpSpecificData);

	return CrFwPcktGetGroup(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwServType_t CrFwInRepGetServType(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInRepData_t* cmpSpecificData = (CrFwInRepData_t*)(cmpData->cmpSpecificData);

	return CrFwPcktGetServType(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwServType_t CrFwInRepGetServSubType(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInRepData_t* cmpSpecificData = (CrFwInRepData_t*)(cmpData->cmpSpecificData);

	return CrFwPcktGetServSubType(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwDiscriminant_t CrFwInRepGetDiscriminant(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInRepData_t* cmpSpecificData = (CrFwInRepData_t*)(cmpData->cmpSpecificData);

	return CrFwPcktGetDiscriminant(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwSeqCnt_t CrFwInRepGetSeqCnt(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInRepData_t* cmpSpecificData = (CrFwInRepData_t*)(cmpData->cmpSpecificData);

	return CrFwPcktGetSeqCnt(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
char* CrFwInRepGetParStart(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInRepData_t* cmpSpecificData = (CrFwInRepData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetParStart(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwPcktLength_t CrFwInRepGetParLength(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInRepData_t* cmpSpecificData = (CrFwInRepData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetParLength(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
void CrFwInRepConfigCheck(FwPrDesc_t prDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwInRepData_t* cmpSpecificData = (CrFwInRepData_t*)(cmpData->cmpSpecificData);

	if (cmpSpecificData->isValid(prDesc) == 1)
		cmpData->outcome = 1;
	else
		cmpData->outcome = 0;
}

