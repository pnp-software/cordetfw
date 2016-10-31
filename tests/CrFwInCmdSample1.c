/**
 * @file
 * @ingroup crTestSuiteGroup
 * Implementation of the Sample 1 InCommand.
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
#include "InCmd/CrFwInCmd.h"
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

/** The Validity Flag. */
static CrFwBool_t validityFlag;

/** The Ready Flag. */
static CrFwBool_t readyFlag;

/** The Start Action Outcome. */
static CrFwOutcome_t startOutcome;

/** The Progress Action Outcome. */
static CrFwOutcome_t progressOutcome;

/** The Abort Action Outcome. */
static CrFwOutcome_t abortOutcome;

/** The Termination Action Outcome. */
static CrFwOutcome_t terminationOutcome;

/** The Start Action Counter. */
static CrFwCounterU1_t startCounter = 0;

/** The Progress Action Counter. */
static CrFwCounterU1_t progressCounter = 0;

/** The Termination Action Counter. */
static CrFwCounterU1_t terminationCounter = 0;

/** The abort Action Counter. */
static CrFwCounterU1_t abortCounter = 0;

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInCmdSample1ValidityCheck(FwPrDesc_t prDesc) {
	(void)(prDesc);
	return validityFlag;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1SetValidityFlag(CrFwBool_t flag) {
	validityFlag = flag;
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInCmdSample1ReadyCheck(FwSmDesc_t smDesc) {
	(void)(smDesc);
	return readyFlag;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1SetReadyFlag(CrFwBool_t flag) {
	readyFlag = flag;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1StartAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	cmpData->outcome = startOutcome;
	startCounter++;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1SetStartActionOutcome(CrFwOutcome_t outcome) {
	startOutcome = outcome;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwInCmdSample1GetStartActionCounter() {
	return startCounter;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1ProgressAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	cmpData->outcome = progressOutcome;
	progressCounter++;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1SetProgressActionOutcome(CrFwOutcome_t outcome) {
	progressOutcome = outcome;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwInCmdSample1GetProgressActionCounter() {
	return progressCounter;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1AbortAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	cmpData->outcome = abortOutcome;
	abortCounter++;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1SetAbortActionOutcome(CrFwOutcome_t outcome) {
	abortOutcome = outcome;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwInCmdSample1GetAbortActionCounter() {
	return abortCounter;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1TerminationAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	cmpData->outcome = terminationOutcome;
	terminationCounter++;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInCmdSample1SetTerminationActionOutcome(CrFwOutcome_t outcome) {
	terminationOutcome = outcome;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwInCmdSample1GetTerminationActionCounter() {
	return terminationCounter;

}

