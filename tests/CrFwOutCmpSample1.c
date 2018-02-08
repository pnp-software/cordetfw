/**
 * @file
 * @ingroup crTestSuiteGroup
 * Implementation of the Sample 1 OutComponent.
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
#include "OutCmp/CrFwOutCmp.h"
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

/** The Enable Flag. */
static CrFwBool_t enableFlag = 0;

/** The Ready Flag. */
static CrFwBool_t readyFlag = 0;

/** The Repeat Flag. */
static CrFwBool_t repeatFlag = 0;

/** The Sample 1 Counter. */
static unsigned char counter;

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutCmpSample1EnableCheck(FwSmDesc_t smDesc) {
	(void)(smDesc);
	return enableFlag;
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutCmpSample1ReadyCheck(FwSmDesc_t smDesc) {
	(void)(smDesc);
	return readyFlag;
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutCmpSample1RepeatCheck(FwSmDesc_t smDesc) {
	(void)(smDesc);
	return repeatFlag;
}

void CrFwOutCmpSample1UpdateAction(FwSmDesc_t smDesc) {
	(void)(smDesc);
	counter++;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwOutCmpSample1Serialize(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)cmpData->cmpSpecificData;
	CrFwOutCmpDefSerialize(smDesc);
	cmpSpecificData->pckt[CrFwPcktGetMaxLength()-1] = (char)counter;
}

/*-----------------------------------------------------------------------------------------*/
CrFwPckt_t CrFwOutCmpSample1GetPckt(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)cmpData->cmpSpecificData;
	return (cmpSpecificData->pckt);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwOutCmpSample1SetEnableFlag(CrFwBool_t flag) {
	enableFlag = flag;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwOutCmpSample1SetReadyFlag(CrFwBool_t flag) {
	readyFlag = flag;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwOutCmpSample1SetRepeatFlag(CrFwBool_t flag) {
	repeatFlag = flag;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwOutCmpSample1SetCounter(unsigned char cnt) {
	counter = cnt;
}

