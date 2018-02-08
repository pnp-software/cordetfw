/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Sample InReport used in the Test Suite.
 * An InReport is defined by defining the functions which override its
 * adaptation points, namely (see <code>CrFwInRep.h</code>):
 * - The Validity Check Operation
 * - The Update Action Operation
 * .
 * This module defines functions which implement the above operations.
 * These functions are associated to a specific kind of InReport in
 * the initializer <code>#CR_FW_INREP_INIT_KIND_DESC</code>.
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

#ifndef CRFW_INREP_SAMPLE1_H_
#define CRFW_INREP_SAMPLE1_H_

/* Include configuration files */
#include "CrFwUserConstants.h"
/* Include framework components */
#include "CrFwConstants.h"
/* Include FW Profile components */
#include "FwSmCore.h"

/**
 * Implementation of the Validity Check Operation for the Sample 1 InReport.
 * This function returns the value of an internal flag (the Validity Flag)
 * whose value is set through function <code>::CrFwInRepSample1SetValidityFlag</code>.
 * @param prDesc the descriptor of the InReport reset procedure
 * @return the value of Validity Flag
 */
CrFwBool_t CrFwInRepSample1ValidityCheck(FwPrDesc_t prDesc);

/**
 * Set the value of the Validity Flag (see <code>::CrFwInRepSample1ValidityCheck</code>).
 * @param flag the value of the validity flag
 */
void CrFwInRepSample1SetValidityFlag(CrFwBool_t flag);

/**
 * Implementation of the Update Action Operation for the Sample 1 InReport.
 * This function sets the outcome to the value of an internal flag (the
 * Update Action Outcome) whose value is set through function
 * <code>::CrFwInRepSample1SetUpdateActionOutcome</code> and it increments
 * the value of a counter (the Update Action Counter) whose value
 * is read through function <code>::CrFwInRepSample1GetUpdateActionCounter</code>.
 * @param prDesc the descriptor of the InReport procedure
 */
void CrFwInRepSample1UpdateAction(FwPrDesc_t prDesc);

/**
 * Set the value of the Update Action Outcome (see <code>::CrFwInRepSample1UpdateAction</code>).
 * @param outcome the value of the Update Action Outcome
 */
void CrFwInRepSample1SetUpdateActionOutcome(CrFwOutcome_t outcome);

/**
 * Get the value of the Update Action Counter (see <code>::CrFwInRepSample1UpdateAction</code>).
 * @return the value of the Update Action Counter
 */
CrFwCounterU1_t CrFwInRepSample1GetUpdateActionCounter();


#endif /* CRFW_INREP_SAMPLE1_H_ */
