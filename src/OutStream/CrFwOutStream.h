/**
 * @file
 * @ingroup outMngGroup
 * Definition of the OutStream component.
 *
 * An application will normally instantiate one OutStream Component for
 * each report or command destination.
 * An OutStream is implemented by the OutStream State Machine (see figures below)
 * embedded within state CONFIGURED of a Base State Machine.
 *
 * This header file defines a function to create and access the OutStream attached to a
 * certain command or report destination.
 * This header file therefore also defines the interface to the OutStreamRegistry
 * component of the CORDET Framework.
 *
 * An application can instantiate several OutStream Components.
 * Each OutStream instance has an identifier which uniquely identifies it
 * within the set of OutStream Components.
 * This identifier is an integer in the range 0 to: <code>#CR_FW_NOF_OUTSTREAM</code>-1.
 *
 * <b>Mode of Use of an OutStream Component</b>
 *
 * The configuration of the OutStream components is defined statically in
 * <code>CrFwOutStreamUserPar.h</code>.
 *
 * An OutStream component is created with function <code>::CrFwOutStreamMake</code>.
 * After being created, the OutStream must be initialized and reset.
 * This is done with functions <code>::CrFwCmpInit</code> and <code>::CrFwCmpReset</code>.
 * Nominally, after being initialized and reset the OutStream State Machine should be
 * in state CONFIGURED (this can be checked by verifying that function <code>FwSmGetCurState</code>
 * returns CR_FW_BASE_STATE_CONFIGURED).
 *
 * After it has been configured, an OutStream can process two transition commands:
 * - A Send command to send a packet (representing either a command or a report)
 *   to the middleware connection attached to the OutStream.
 *   This command is sent through function <code>::CrFwOutStreamSend</code>.
 * - A ConnectionAvailable command to signal the ability of the middleware to send
 *   a new packet to its destination. This command is sent with the
 *   the <code>::CrFwOutStreamConnectionAvail</code> function.
 * .
 * If at the time the Send command is received, the middleware is not ready to receive
 * the packet, the packet is stored in Packet Queue.
 * The next attempt to send it out will be made when command ConnectionAvailable is sent.
 *
 * @image html OutStream.png
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

#ifndef CRFW_OUT_STREAM_H_
#define CRFW_OUT_STREAM_H_

/* Include FW Profile Files */
#include "FwProfile/FwSmConstants.h"
#include "FwProfile/FwPrConstants.h"
/* Include Configuration Files */
#include "Pckt/CrFwPcktQueue.h"
#include "CrFwUserConstants.h"
/* Include Framework Files */
#include "CrFwConstants.h"

/**
 * Factory function to retrieve the i-th OutStream State Machine instance.
 * The first time this function is called with a certain value of the argument i, it
 * creates the i-th OutStream State Machine instance.
 * Subsequent calls returns the same instance.
 *
 * The OutStream identifier i must be in the range: [0, <code>#CR_FW_NOF_OUTSTREAM</code>-1].
 * If the identifier is out of range, the function returns NULL and sets the application
 * error code to: <code>::crOutStreamIllId</code>.
 *
 * The first time this function is called with a certain value of i, it returns an
 * OutStream State Machine which has been started but which still needs to be initialized and
 * configured.
 * @param outStreamId the identifier of the Base State Machine of the OutStream
 * @return the descriptor of the OutStream State Machine or NULL
 * if the state machine could not be created or if the identifier i is out of range.
 */
FwSmDesc_t CrFwOutStreamMake(CrFwInstanceId_t outStreamId);

/**
 * Return true if the argument OutStream is in state READY.
 * @param smDesc the descriptor of the Base State Machine of the OutStream
 * @return 1 if the argument InCommand is in state CONFIGURED, sub-state
 * READY; 0 otherwise
 */
CrFwBool_t CrFwOutStreamIsInReady(FwSmDesc_t smDesc);

/**
 * Return true if the argument OutStream is in state BUFFERING.
 * @param smDesc the descriptor of the Base State Machine of the OutStream
 * @return 1 if the argument InCommand is in state CONFIGURED, sub-state
 * BUFFERING; 0 otherwise
 */
CrFwBool_t CrFwOutStreamIsInBuffering(FwSmDesc_t smDesc);

/**
 * Getter function for the OutStream corresponding to the argument destination.
 * Nominally, each OutStream is associated to a certain destination.
 * The binding between an OutStream and its destination is done statically in the
 * configuration file <code>CrFwOutStreamUserPar.h</code>.
 *
 * If the value of the destination argument is illegal (i.e. if no
 * OutStream has been bound to it), this function returns NULL and sets the
 * application error code to: <code>::crOutStreamUndefDest</code>.
 *
 * This function should only be called after all OutStreams have been built through
 * calls to function <code>::CrFwOutStreamMake</code>.
 * If this pre-condition is not satisfied, execution of this function could result
 * in an access to a NULL pointer.
 * @param dest the destination associated to the OutStream
 * @return the descriptor of the OutStream State Machine or NULL
 * if the argument destination was illegal or no OutStream had been bound to it.
 */
FwSmDesc_t CrFwOutStreamGet(CrFwDestSrc_t dest);

/**
 * Send a packet to the OutStream.
 * This function hands over the argument packet to the OutStream and then it sends
 * command "Send" to its state machine.
 * This causes the OutStream to try to send the packet to the destination associated
 * to the OutStream.
 * If the middleware is not ready to accept the packet, then a copy of the packet
 * is made and is stored in the OutStream's Packet Queue from where it will be sent to
 * the middleware at a later time.
 * If the packet copy cannot be done because no more free packets
 * are available, error <code>::crOutStreamNoMorePckt</code> is generated.
 * If the Packet Queue is full, the packet is released and error
 * <code>::crOutStreamPQFull</code> is generated.
 *
 * If packet cannot be sent to the middleware  (or to make a copy of the packet and buffer the copy internally
 * if the middleware is currently not available).
 *
 * The argument <code>pckt</code> is a pointer to the out-going packet.
 * This pointer is "owned" by the caller of function <code>CrFwOutStreamSend</code>
 * who remains responsible for releasing it when it is no longer needed.
 * The function only uses the pointer during its execution.
 * @param smDesc the descriptor of the OutStream State Machine.
 * @param pckt the packet to be sent by the OutStream
 */
void CrFwOutStreamSend(FwSmDesc_t smDesc, CrFwPckt_t pckt);

/**
 * Signal that the out-going middleware connection has become available.
 * This function sends the ConnectionAvailable command to the OutStream State Machine.
 * @param smDesc the descriptor of the OutStream State Machine.
 */
void CrFwOutStreamConnectionAvail(FwSmDesc_t smDesc);

/**
 * Default configuration action for an OutStream.
 * This function resets the packet queue of the OutStream.
 *
 * Configuration actions have an outcome (see <code>CrFwResetProc.h</code>).
 * The outcome of this configuration action is always "success".
 *
 * This function should never be directly called by the end-application.
 * It is declared as a public function so that it may be used in application-specific
 * Configuration Actions.
 * @param prDesc the descriptor of the Reset Procedure of the OutStream
 */
void CrFwOutStreamDefConfigAction(FwPrDesc_t prDesc);

/**
 * Default initialization action for an OutStream.
 * This function: (a) allocates the memory for the packet queue of the OutStream;
 * (b) allocates the memory for the array holding the sequence counters for the
 * groups attached to the OutStream; and
 * (c) initializes all data structures implementing the OutStream.
 * Initialization actions have an outcome (see <code>CrFwResetProc.h</code>).
 * The situation of where the memory allocation fails is not handled and
 * therefore the outcome of this configuration action is always "success".
 *
 * This function should never be directly called by the end-application.
 * It is declared as a public function so that it may be used in application-specific
 * Initialization Actions.
 * @param prDesc the descriptor of the Initialization Procedure of the OutStream
 */
void CrFwOutStreamDefInitAction(FwPrDesc_t prDesc);

/**
 * Default shutdown action for an OutStream.
 * This function releases the memory allocated to the packet queue of the OutStream
 * and releases the memory allocated to the array holding the sequence counters.
 *
 * This function should never be directly called by the end-application.
 * It is declared as a public function so that it may be used in application-specific
 * Shutdown Actions.
 * @param smDesc the descriptor of the OutStream State Machine
 */
void CrFwOutStreamDefShutdownAction(FwSmDesc_t smDesc);

/**
 * Get the destination for an OutStream.
 * @param smDesc the descriptor of the OutStream State Machine.
 * @return dest the destination associated to the OutStream
 */
CrFwDestSrc_t CrFwOutStreamGetDest(FwSmDesc_t smDesc);

/**
 * Return the value of the sequence counter for one of the groups
 * maintained by an OutStream.
 * The group identifier is passed as an argument to the function call.
 * No check is performed on the validity of the group identifier.
 * @param smDesc the descriptor of the OutStream State Machine.
 * @param group the identifier of the group
 * @return the OutStream sequence counter
 */
CrFwSeqCnt_t CrFwOutStreamGetSeqCnt(FwSmDesc_t smDesc, CrFwGroup_t group);

/**
 * Return the number of packets currently in the packet queue of an OutStream.
 * @param smDesc the descriptor of the OutStream State Machine.
 * @return the number of packets currently in the packet queue of the OutStream.
 */
CrFwCounterU1_t CrFwOutStreamGetNOfPendingPckts(FwSmDesc_t smDesc);

/**
 * Return the number of groups associated to the OutStream.
 * @param smDesc the descriptor of the OutStream State Machine.
 * @return the number of groups associated to the OutStream.
 */
CrFwGroup_t CrFwOutStreamGetNOfGroups(FwSmDesc_t smDesc);

/**
 * Return the size of the packet queue of the OutStream.
 * @param smDesc the descriptor of the OutStream State Machine.
 * @return the size of the packet queue of the OutStream.
 */
CrFwCounterU1_t CrFwOutStreamGetPcktQueueSize(FwSmDesc_t smDesc);

#endif /* CRFW_OUT_STREAM_H_ */
