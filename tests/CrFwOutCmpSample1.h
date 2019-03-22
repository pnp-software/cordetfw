/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Sample OutComponent used in the Test Suite.
 * An OutComponent is defined by defining the functions which override its
 * adaptation points, namely (see <code>CrFwOutCmp.h</code>):
 * - The Enable Check Operation
 * - The Ready Check Operation
 * - The Serialize Operation
 * .
 * This module defines three functions which implement the above operations.
 * These functions are associated to a specific kind of OutComponent in
 * the initializer <code>#CR_FW_OUTCMP_INIT_KIND_DESC</code>.
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

#ifndef CRFW_OUTCMP_SAMPL1_H_
#define CRFW_OUTCMP_SAMPL1_H_

/* Include framework components */
#include "CrFwConstants.h"
/* Include FW Profile components */
#include "FwSmCore.h"

/**
 * Implementation of the Enable Check Operation for the Sample 1 OutComponent.
 * This function returns the value of an internal flag (the Enable Flag)
 * whose value is set through function <code>::CrFwOutCmpSample1SetEnableFlag</code>.
 * @param smDesc the descriptor of the OutComponent state machine
 * @return the value of the Enable Flag
 */
CrFwBool_t CrFwOutCmpSample1EnableCheck(FwSmDesc_t smDesc);

/**
 * Implementation of the Ready Check Operation for the Sample 1 OutComponent.
 * This function returns the value of an internal flag (the Ready Flag)
 * whose value is set through function <code>::CrFwOutCmpSample1SetReadyFlag</code>.
 * @param smDesc the descriptor of the OutComponent state machine
 * @return the value of the Ready Flag
 */
CrFwBool_t CrFwOutCmpSample1ReadyCheck(FwSmDesc_t smDesc);

/**
 * Implementation of the Repeat Check Operation for the Sample 1 OutComponent.
 * This function returns the value of an internal flag (the Repeat Flag)
 * whose value is set through function <code>::CrFwOutCmpSample1SetRepeatFlag</code>.
 * @param smDesc the descriptor of the OutComponent state machine
 * @return the value of the Repeat Flag
 */
CrFwBool_t CrFwOutCmpSample1RepeatCheck(FwSmDesc_t smDesc);

/**
 * Implementation of the Update Operation for the Sample 1 OutComponent.
 * This function increments the value of Sample 1 Counter by 1.
 * The value of the Sample 1 Counter is set through function
 * <code>::CrFwOutCmpSample1SetCounter</code>.
 * @param smDesc the descriptor of the OutComponent state machine
 * @return the value of the Repeat Flag
 */
void CrFwOutCmpSample1UpdateAction(FwSmDesc_t smDesc);

/**
 * Implementation of the Serialize Operation for the Sample 1 OutComponent.
 * This function calls the default serialization function (<code>::CrFwOutCmpDefSerialize</code>)
 * and then sets byte N-2 of the packet associated to the OutComponent
 * equal to the value of the Sample 1 Counter (N is the packet's length; the
 * last two bytes are used for the CRC).
 * The value of the Sample 1 Counter is set through function
 * <code>::CrFwOutCmpSample1SetCounter</code>.
 * @param smDesc the descriptor of the OutComponent state machine
 * @return the value of the Enable Flag
 */
void CrFwOutCmpSample1Serialize(FwSmDesc_t smDesc);

/**
 * Return the packet associated to the Sample 1 OutComponent.
 * This function is useful to check the effects of the OutComponent serialization.
 * Note that, at some stage, the packet will be released and the pointer
 * returned by this function will therefore become invalid.
 * @param smDesc the descriptor of the OutComponent state machine
 * @return the packet associated to the OutComponent
 */
CrFwPckt_t CrFwOutCmpSample1GetPckt(FwSmDesc_t smDesc);

/**
 * Set the value of Enable Flag (see <code>::CrFwOutCmpSample1EnableCheck</code>).
 * @param flag the Enable Flag
 */
void CrFwOutCmpSample1SetEnableFlag(CrFwBool_t flag);

/**
 * Set the value of Ready Flag (see <code>::CrFwOutCmpSample1ReadyCheck</code>).
 * @param flag the Ready Flag
 */
void CrFwOutCmpSample1SetReadyFlag(CrFwBool_t flag);

/**
 * Set the value of Repeat Flag (see <code>::CrFwOutCmpSample1RepeatCheck</code>).
 * @param flag the Repeat Flag
 */
void CrFwOutCmpSample1SetRepeatFlag(CrFwBool_t flag);

/**
 * Set the value of Sample 1 Counter (see <code>::CrFwOutCmpSample1Serialize</code>).
 * @param cnt the counter
 */
void CrFwOutCmpSample1SetCounter(unsigned char cnt);

#endif /* CRFW_OUTCMP_SAMPL1_H_ */
