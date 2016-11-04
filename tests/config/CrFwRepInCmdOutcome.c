/**
 * @file
 * @ingroup CrTestSuiteGroup
 *
 * Default implementation of the InCommand Outcome Reporting interface of
 * <code>CrFwRepInCmdOutcome.h</code>.
 * The implementation of this interface is one of the adaptation points of the
 * CORDET Framework.
 * This file provides a default implementation which is primarily intended to
 * support testing.
 * It is expected that applications will provide their own implementation.
 * Application will therefore normally replace this file with their own file
 * providing their application-specific implementation.
 *
 * This implementation stores the InCommand Outcome Reports in a pre-allocated array with
 * a fixed size.
 * The array is managed as a ring-buffer.
 * Functions are provide to let external components access the InCommand Outcome Report array.
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
/* Include Framework Files */
#include "CrFwConstants.h"
#include "CrFwRepInCmdOutcome.h"
/* Include Configuration Files */
#include "CrFwRepInCmdOutcomeStub.h"

/** The size of the InCommand Outcome Report array */
#define CR_FW_INCMD_OUTCOME_REP_ARRAY_SIZE 10

/** The structure for an InCommand Outcome Report. */
typedef struct {
	/** The outcome of the InCommand */
	CrFwRepInCmdOutcome_t outcome;
	/** The failure code (only meaningful for failure outcomes) */
	CrFwOutcome_t failCode;
	/** The service type of the InCommand whose outcome is being reported */
	CrFwServType_t servType;
	/** The service sub-type of the InCommand whose outcome is being reported */
	CrFwServSubType_t servSubType;
	/** The discriminant of the InCommand whose outcome is being reported */
	CrFwDiscriminant_t discriminant;
	/** The instance identifier of the InCommand whose outcome is being reported */
	CrFwInstanceId_t instanceId;
} CrFwInCmdOutcomeRep_t;

/** The InCommand Outcome Report array */
static CrFwInCmdOutcomeRep_t inCmdOutcomeRepArray[CR_FW_INCMD_OUTCOME_REP_ARRAY_SIZE];

/** The position in the InCommand Outcome Report array at which the next
 * InCommand Outcome Report will be written */
static CrFwCounterU2_t inCmdOutcomeRepPos = 0;

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU2_t CrFwRepInCmdOutcomeStubGetPos() {
	return inCmdOutcomeRepPos;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepInCmdOutcomeStubReset() {
	inCmdOutcomeRepPos = 0;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepInCmdOutcome(CrFwRepInCmdOutcome_t outcome, CrFwInstanceId_t instanceId, CrFwServType_t servType,
                         CrFwServSubType_t servSubType, CrFwDiscriminant_t disc, CrFwOutcome_t failCode, __attribute__((unused)) FwSmDesc_t inCmd) {

	inCmdOutcomeRepArray[inCmdOutcomeRepPos].outcome = outcome;
	inCmdOutcomeRepArray[inCmdOutcomeRepPos].instanceId = instanceId;
	inCmdOutcomeRepArray[inCmdOutcomeRepPos].failCode = failCode;
	inCmdOutcomeRepArray[inCmdOutcomeRepPos].servType = servType;
	inCmdOutcomeRepArray[inCmdOutcomeRepPos].servSubType = servSubType;
	inCmdOutcomeRepArray[inCmdOutcomeRepPos].discriminant = disc;

	inCmdOutcomeRepPos = (CrFwCounterU2_t)((inCmdOutcomeRepPos + 1) % CR_FW_INCMD_OUTCOME_REP_ARRAY_SIZE);
}

/*-----------------------------------------------------------------------------------------*/
CrFwRepInCmdOutcome_t CrFwRepInCmdOutcomeStubGetOutcome(CrFwCounterU2_t repPos) {
	return inCmdOutcomeRepArray[repPos].outcome;
}

/*-----------------------------------------------------------------------------------------*/
CrFwOutcome_t CrFwRepInCmdOutcomeStubGetFailCode(CrFwCounterU2_t repPos) {
	return inCmdOutcomeRepArray[repPos].failCode;
}

/*-----------------------------------------------------------------------------------------*/
CrFwInstanceId_t CrFwRepInCmdOutcomeStubGetInstanceId(CrFwCounterU2_t repPos) {
	return inCmdOutcomeRepArray[repPos].instanceId;
}

/*-----------------------------------------------------------------------------------------*/
CrFwServType_t CrFwRepInCmdOutcomeStubGetServType(CrFwCounterU2_t repPos) {
	return inCmdOutcomeRepArray[repPos].servType;
}

/*-----------------------------------------------------------------------------------------*/
CrFwServSubType_t CrFwRepInCmdOutcomeStubGetServSubType(CrFwCounterU2_t repPos) {
	return inCmdOutcomeRepArray[repPos].servSubType;
}

/*-----------------------------------------------------------------------------------------*/
CrFwDiscriminant_t CrFwRepInCmdOutcomeStubGetDiscriminant(CrFwCounterU2_t repPos) {
	return inCmdOutcomeRepArray[repPos].discriminant;
}

