/**
 * @file
 * @ingroup crTestSuiteGroup
 * Implementation of the Sample 1 OutComponent.
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
#include "OutCmp/CrFwOutCmp.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "BaseCmp/CrFwInitProc.h"
#include "BaseCmp/CrFwResetProc.h"
#include "BaseCmp/CrFwDummyExecProc.h"
#include "OutFactory/CrFwOutFactory.h"
#include "Pckt/CrFwPckt.h"
/* Include FW Profile files */
#include "FwProfile/FwPrConfig.h"
#include "FwProfile/FwPrDCreate.h"
#include "FwProfile/FwSmConfig.h"
#include "FwProfile/FwSmDCreate.h"
#include "FwProfile/FwPrCore.h"

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

