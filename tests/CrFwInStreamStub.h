/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Interface for the InStream stub.
 * The InStream stub is used in the CORDET Test Suite to verify the implementation
 * of the InStream component (see <code>CrFwInStream.h</code>).
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

#ifndef CRFW_INSTREAMSTUB_H_
#define CRFW_INSTREAMSTUB_H_

/* Include Framework Files */
#include "CrFwConstants.h"
/* Include Configuration Files */
#include "CrFwUserConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"

/**
 * Stub function implementing the packet collect operation for the InStream
 * (see <code>CrFwInStream.h</code>).
 * This stub manages a counter (the packet collection counter) which is
 * decremented every time the function is called.
 * The value of the packet collection counter can be set with function
 * <code>::CrFwInStreamStubSetPcktCollectionCnt</code>.
 * This stub creates and returns a packet.
 * The packet is unconfigured other than for the following fields:
 * - its group which is set to a value controllable with
 *   function <code>::CrFwInStreamStubSetPcktGroup</code>.
 * - its sequence counter field which is set to a value controllable with
 *   function <code>::CrFwInStreamStubSetPcktSeqCnt</code>.
 * - its service type, sub-type and discriminant which are set to the values
 *   loaded with function <code>::CrFwInStreamStubSetPcktType</code>.
 * - its destination which is set to the value
 *   loaded with function <code>::CrFwInStreamStubSetPcktDest</code>.
 * - its command/report type which is set to the value
 *   loaded with function <code>::CrFwInStreamStubSetPcktCmdRepType</code>.
 * - its command/report identifier which is set to the value
 *   loaded with function <code>::CrFwInStreamStubSetPcktCmdRepId</code>.
 * .
 * @param src the source associated to the InStream (not used in this stub)
 * @return the packet
 */
CrFwPckt_t CrFwInStreamStubPcktCollect(CrFwDestSrc_t src);

/**
 * Stub function implementing the packet available check operation for the InStream
 * (see <code>CrFwInStream.h</code>).
 * This stub returns true if the packet collection counter is greater
 * than zero.
 * @param src the source associated to the InStream (not used in this stub)
 * @return the value of a predefined flag
 */
CrFwBool_t CrFwInStreamStubIsPcktAvail(CrFwDestSrc_t src);

/**
 * Stub function implementing the shutdown operation for an InStream
 * (see <code>CrFwInStream.h</code>).
 * This function increments a counter (the <code>shutdown counter</code>)
 * and then calls the default shutdown operation
 * (<code>::CrFwInStreamDefShutdownAction</code>).
 * @param smDesc the descriptor of the InStream state machine
 * @return the value of a predefined flag
 */
void CrFwInStreamStubShutdown(FwSmDesc_t smDesc);

/**
 * Dummy implementation of an initialization or configuration check.
 * The outcome of this implementation is given by the value of a settable flag
 * (the check flag) whose value is set through function <code>::CrFwInStreamStubSetCheckFlag</code>.
 * @param prDesc the initialization or configuration procedure descriptor (this parameter
 * is not used).
 */
void CrFwInStreamStubDummyCheck(FwPrDesc_t prDesc);

/**
 * Set the value of the check flag which determines the outcome of the dummy check of
 * <code>::CrFwInStreamStubDummyCheck</code>.
 * @param flag the value of the check flag
 */
void CrFwInStreamStubSetCheckFlag(CrFwBool_t flag);

/**
 * Dummy implementation of an initialization action.
 * The outcome of this action is given by the value of the <code>actionFlag</code>
 * whose value is set through function <code>::CrFwInStreamStubSetActionFlag</code>.
 *
 * Like all application-specific InStream Initialization Actions, this function
 * also calls the default OutStream Initialization Action (<code>::CrFwInStreamDefInitAction</code>)
 * to ensure that default initialization actions are performed.
 * The <code>::CrFwInStreamDefInitAction</code> function dynamically allocates
 * memory for an internal InStream data structure. In order to avoid memory
 * leaks, function <code>::CrFwInStreamDefInitAction</code> is only called if
 * the InStream data structure has not yet been initialized.
 *
 * @param prDesc the initialization or configuration procedure descriptor (this parameter
 * is not used).
 */
void CrFwInStreamStubInitAction(FwPrDesc_t prDesc);

/**
 * Dummy implementation of a configuration action.
 * The outcome of this action is given by the value of the <code>actionFlag</code>
 * whose value is set through function <code>::CrFwInStreamStubSetActionFlag</code>.
 *
 * Like all application-specific InStream Configuration Actions, this function
 * also calls the default InStream Configuration Action.
 *
 * @param prDesc the initialization or configuration procedure descriptor (this parameter
 * is not used).
 */
void CrFwInStreamStubConfigAction(FwPrDesc_t prDesc);

/**
 * Set the value of the action flag which determines the outcome of the initialization
 * or configuration action.
 * @param flag the action flag
 */
void CrFwInStreamStubSetActionFlag(CrFwBool_t flag);

/**
 * Set the value of the packet collection counter which defines the number of packets
 * available at the middleware interface (see <code>::CrFwInStreamStubPcktCollect</code>).
 * @param cnt the value of the packet collection counter
 */
void CrFwInStreamStubSetPcktCollectionCnt(CrFwCounterU1_t cnt);

/**
 * Set the value of the sequence counter of the next packet collected
 * (see <code>::CrFwInStreamStubPcktCollect</code>).
 * @param cnt the value of the packet sequence counter
 */
void CrFwInStreamStubSetPcktSeqCnt(CrFwSeqCnt_t cnt);

/**
 * Set the value of the group of the next packet collected
 * (see <code>::CrFwInStreamStubPcktCollect</code>).
 * @param group the value of the group
 */
void CrFwInStreamStubSetPcktGroup(CrFwGroup_t group);

/**
 * Set the value of the service type, sub-type and discriminant of the next packet collected
 * (see <code>::CrFwInStreamStubPcktCollect</code>).
 * @param servType the service type
 * @param servSubType the service sub-type
 * @param disc the discriminant
 */
void CrFwInStreamStubSetPcktType(CrFwServType_t servType, CrFwServSubType_t servSubType,
                                 CrFwDiscriminant_t disc);

/**
 * Get the value of the shutdown counter (see <code>::CrFwInStreamStubShutdown</code>).
 * @return the value of the packet sequence counter
 */
CrFwCounterU1_t CrFwInStreamStubGetShutdownCnt();

/**
 * Set the value of the destination of the next packet collected
 * (see <code>::CrFwInStreamStubPcktCollect</code>).
 * @param dest the packet destination
 */
void CrFwInStreamStubSetPcktDest(CrFwDestSrc_t dest);

/**
 * Set the value of the command or report identifier of the next packet collected
 * (see <code>::CrFwInStreamStubPcktCollect</code>).
 * @param id the command or report identifier
 */
void CrFwInStreamStubSetPcktCmdRepId(CrFwInstanceId_t id);

/**
 * Set the value of the acknowledge level of the next packet collected
 * (see <code>::CrFwInStreamStubPcktCollect</code>).
 * @param acc acknowledge level for command acceptance
 * @param str acknowledge level for command start
 * @param prg acknowledge level for command progress
 * @param trm acknowledge level for command termination
 */
void CrFwInStreamStubSetPcktAckLevel(CrFwBool_t acc, CrFwBool_t str, CrFwBool_t prg, CrFwBool_t trm);

/**
 * Set the type (command or report) of the next packet collected
 * (see <code>::CrFwInStreamStubPcktCollect</code>).
 * @param cmdRepType the command or report type
 */
void CrFwInStreamStubSetPcktCmdRepType(CrFwCmdRepType_t cmdRepType);

#endif /* CRFW_INSTREAMSTUB_H_ */
