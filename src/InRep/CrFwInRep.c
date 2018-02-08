/**
 * @file
 *
 * Implementation of InReport component.
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

