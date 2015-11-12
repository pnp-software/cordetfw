/**
 * @file
 *
 * Implementation of OutStream stub.
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
#include "CrFwOutStreamStub.h"
#include "CrFwRepErrStub.h"
/* Include configuration files */
#include "CrFwOutStreamUserPar.h"
#include "CrFwCmpData.h"
/* Include FW Profile files */
#include "FwProfile/FwSmConstants.h"
#include "FwProfile/FwSmConfig.h"
#include "FwProfile/FwSmCore.h"
#include "FwProfile/FwPrConfig.h"
#include "FwProfile/FwPrCore.h"
#include "FwProfile/FwPrConstants.h"
/* Include framework files */
#include "OutStream/CrFwOutStream.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "Pckt/CrFwPckt.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"

/** Counter incremented every time the packet hand-over operation is called */
static CrFwCounterU1_t pcktHandOverCnt = 0;

/** Return value of the packet hand-over operation */
static CrFwBool_t pcktHandOverFlag = 1;

/** Outcome of dummy check */
static CrFwBool_t checkFlag = 1;

/** Outcome of dummy action */
static CrFwBool_t actionFlag = 1;

/** Counter incremented by stub Shutdown Operation */
static CrFwCounterU1_t shutdownCnt = 0;

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutStreamStubPcktHandover(CrFwPckt_t pckt) {
	(void)(pckt);
	pcktHandOverCnt++;
	return pcktHandOverFlag;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwOutStreamStubGetHandoverCnt() {
	return pcktHandOverCnt;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwOutStreamStubGetShutdownCnt() {
	return shutdownCnt;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamStubSetHandoverFlag(CrFwBool_t flag) {
	pcktHandOverFlag = flag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamStubDummyCheck(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	outStreamData->outcome = (CrFwOutcome_t)checkFlag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamStubSetCheckFlag(CrFwBool_t flag) {
	checkFlag = flag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamStubInitAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	if (cmpSpecificData->seqCnt == NULL)
		CrFwOutStreamDefInitAction(prDesc);
	outStreamBaseData->outcome = (CrFwOutcome_t)actionFlag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamStubConfigAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwOutStreamDefConfigAction(prDesc);
	outStreamData->outcome = (CrFwOutcome_t)actionFlag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamStubSetActionFlag(CrFwBool_t flag) {
	actionFlag = flag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamStubShutdown(FwSmDesc_t smDesc) {
	shutdownCnt++;
	CrFwOutStreamDefShutdownAction(smDesc);
}
