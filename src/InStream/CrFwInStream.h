/**
 * @file
 * @ingroup inMngGroup
 * Definition of the InStream component.
 *
 * An InStream is responsible for managing the collection of packets (representing
 * incoming reports or incoming commands) from one or more packet sources.
 * An InStream is implemented by the InStream State Machine (see figures below)
 * embedded within state CONFIGURED of a Base State Machine.
 *
 * The InStream State Machine has two states. State PCKT_AVAIL represents a situation
 * where one or more packets have been collected from the middleware and are waiting
 * to be processed by the application.
 * State WAITING represents a situation where no packets are pending in the InStream.
 * The packets in the InStream are stored in a <i>Packet Queue</i>.
 *
 * An application can instantiate several InStream Components.
 * Each InStream instance has an identifier which uniquely identifies it
 * within the set of InStream Components.
 * This identifier is an integer in the range 0 to: <code>#CR_FW_NOF_INSTREAM</code>-1.
 *
 * <b>Mode of Use of an InStream Component</b>
 *
 * The configuration of the InStream components is defined statically in
 * <code>CrFwInStreamUserPar.h</code>.
 *
 * An InStream component is created with function <code>::CrFwInStreamMake</code>.
 * After being created, the InStream must be initialized and reset.
 * This is done with functions <code>::CrFwCmpInit</code> and <code>::CrFwCmpReset</code>.
 * Nominally, after being initialized and reset the InStream State Machine should be
 * in state CONFIGURED (this can be checked by verifying that function <code>FwSmGetCurState</code>
 * returns CR_FW_BASE_STATE_CONFIGURED).
 *
 * After it has been configured, an InStream can process two transition commands:
 * - A GetPacket command to retrieve one packet (representing either a command or a report)
 *   from the InStream's Packet Queue. The GetPacket command returns packets in the order in
 *   which they were collected from the middleware.
 *   This command is sent through function <code>::CrFwInStreamGetPckt</code>.
 * - A PacketAvailable command to check whether any packets are available at the middleware
 *   interface and, if they are available, to collect them and store them in the InStream's Packet
 *   Queue. This command is sent with the <code>::CrFwInStreamPcktAvail</code> function.
 * .
 * @image html InStream.png
 * The InStream State Machine runs the Packet Collect Procedure shown in the following figure:
 * @image html PacketCollect.png
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

#ifndef CRFW_INSTREAM_H_
#define CRFW_INSTREAM_H_

/* Include FW Profile Files */
#include "FwSmConstants.h"
#include "FwPrConstants.h"
/* Include Configuration Files */
#include "Pckt/CrFwPcktQueue.h"
#include "CrFwUserConstants.h"
/* Include Framework Files */
#include "CrFwConstants.h"

/**
 * Factory function to retrieve the i-th InStream State Machine instance.
 * The first time this function is called with a certain value of the argument i, it
 * creates the i-th InStream State Machine instance.
 * Subsequent calls returns the same instance.
 *
 * The InStream identifier i must be in the range: [0, <code>#CR_FW_NOF_INSTREAM</code>-1].
 * If the identifier is out of range, the function returns NULL and sets the application
 * error code to: <code>::crInStreamIllId</code>.
 *
 * The first time this function is called with a certain value of i, it returns an
 * InStream State Machine which has been started but which must still be initialized
 * and configured.
 * @param inStreamId the identifier of the InStream
 * @return the descriptor of the Base State Machine of the InStream or NULL
 * if the state machine could not be created or if the identifier i is out of range.
 */
FwSmDesc_t CrFwInStreamMake(CrFwInstanceId_t inStreamId);

/**
 * Getter function for the InStream corresponding to the argument source.
 * Nominally, each InStream is associated to one or more packet sources.
 * The binding between an InStream and its source is done statically in the
 * configuration file <code>CrFwInStreamUserPar.h</code>.
 *
 * If the value of the source argument is illegal (i.e. if no
 * InStream has been bound to it), this function returns NULL and sets the
 * application error code to: <code>::crInStreamUndefDest</code>.
 *
 * This function should only be called after all InStreams have been built through
 * calls to function <code>::CrFwInStreamMake</code>.
 * If this pre-condition is not satisfied, execution of this function could result
 * in an access to a NULL pointer.
 * @param src the packet source associated to the InStream
 * @return the descriptor of the InStream State Machine or NULL
 * if the argument source was illegal or no InStream had been bound to it.
 */
FwSmDesc_t CrFwInStreamGet(CrFwDestSrc_t src);

/**
 * Retrieve a packet from the InStream.
 * This function sends the GetPacket command to the InStream State Machine.
 * If, at the time the function is called, the InStream is in state PCKT_AVAIL (i.e. if
 * the InStream is configured and its packet queue is not empty), the function
 * returns the oldest packet currently in the Packet Queue of the InStream; otherwise, the
 * function return NULL.
 * @param smDesc the descriptor of the Base State Machine of the InStream.
 * @return pckt the oldest packet in the packet queue or NULL if there is no packet in
 * the packet queue.
 */
CrFwPckt_t CrFwInStreamGetPckt(FwSmDesc_t smDesc);

/**
 * Query the middleware for available packets and collect them if they are available.
 * This function sends the PacketAvailable command to the InStream State Machine.
 * This command may be sent to the InStream by the middleware to signal
 * the arrival of a new packet at the connection controlled by the InStream or
 * it may be sent to poll the middleware and check whether any packets are
 * available. If packets are available at the middleware, they are collected
 * and stored in the InStream's Packet Queue.
 * @param smDesc the descriptor of the Base State Machine of the InStream.
 */
void CrFwInStreamPcktAvail(FwSmDesc_t smDesc);

/**
 * Return true if the argument InStream is in state WAITING.
 * @param smDesc the descriptor of the Base State Machine of the InStream.
 * @return 1 if the argument InStream is in state CONFIGURED, sub-state WAITING;
 * 0 otherwise.
 */
CrFwBool_t CrFwInStreamIsInWaiting(FwSmDesc_t smDesc);

/**
 * Return true if the argument InStream is in state PCKT_AVAIL.
 * @param smDesc the descriptor of the Base State Machine of the InStream.
 * @return 1 if the argument InStream is in state CONFIGURED, sub-state PCKT_AVAIL;
 * 0 otherwise.
 */
CrFwBool_t CrFwInStreamIsInPcktAvail(FwSmDesc_t smDesc);

/**
 * Default configuration action for an InStream.
 * This function resets the packet queue of the InStream and resets the
 * expected sequence counters associated to the InStreams to zero.
 * Configuration actions have an outcome (see <code>CrFwResetProc.h</code>).
 * The outcome of this configuration action is always: "success".
 *
 * This function should never be directly called by the end-application.
 * It is declared as a public function so that it may be used in application-specific
 * Configuration Actions.
 * @param prDesc the descriptor of the Reset Procedure of the InStream
 */
void CrFwInStreamDefConfigAction(FwPrDesc_t prDesc);

/**
 * Default initialization action for an InStream.
 * This function allocates the memory for the packet queue of the InStream
 * and for the array holding the sources associated to the InStream.
 * Initialization actions have an outcome (see <code>CrFwResetProc.h</code>).
 * The situation of where the memory allocation fails is not handled and
 * therefore the outcome of this configuration action is always "success".
 *
 * This function should never be directly called by the end-application.
 * It is declared as a public function so that it may be used in application-specific
 * Initialization Actions.
 * @param prDesc the descriptor of the Initialization Procedure of the InStream
 */
void CrFwInStreamDefInitAction(FwPrDesc_t prDesc);

/**
 * Default shutdown action for an InStream.
 * This function releases the memory allocated to the packet queue of the InStream
 * and to the array holding the sources of the InStream.
 *
 * This function should never be directly called by the end-application.
 * It is declared as a public function so that it may be used in application-specific
 * Shutdown Actions.
 * @param smDesc the descriptor of the InStream State Machine
 */
void CrFwInStreamDefShutdownAction(FwSmDesc_t smDesc);

/**
 * Return the value of the sequence counter of the last packet successfully
 * collected by the InStreams for the argument group.
 * If no packet has yet been collected for that group after the InStream was reset, the
 * sequence counter returned by the function is set equal to zero.
 * @param group the identifier of the group
 * @return the InStream sequence counter
 */
CrFwSeqCnt_t CrFwInStreamGetSeqCnt(CrFwGroup_t group);

/**
 * Overwrites the sequence counter value of the last packet for a group.
 * Can be used to update the expected sequence counter value for the next
 * packet.
 * @param group the identifier of the group
 * @param seqCnt the InStream sequence counter
 */
void CrFwInStreamSetSeqCnt(CrFwGroup_t group, CrFwSeqCnt_t seqCnt);

/**
 * Return the number of packets currently in the packet queue of an InStream.
 * @param smDesc the descriptor of the InStream State Machine
 * @return the number of packets currently in the packet queue of the InStream.
 */
CrFwCounterU1_t CrFwInStreamGetNOfPendingPckts(FwSmDesc_t smDesc);

/**
 * Return the number of groups managed by the InStreams.
 * @return the number of groups associated to the InStream.
 */
CrFwGroup_t CrFwInStreamGetNOfGroups();

/**
 * Return the size of the packet queue of the InStream.
 * @param smDesc the descriptor of the InStream State Machine
 * @return the size of the packet queue of the InStream.
 */
CrFwCounterU1_t CrFwInStreamGetPcktQueueSize(FwSmDesc_t smDesc);

/**
 * Get the i-th packet source of the argument InStream.
 * An InStream can receive packets from one or more sources.
 * A source has an identifier of type <code>::CrFwDestSrc_t</code>.
 * The association between packet sources and InStream is done
 * statically in <code>#CR_FW_INSTREAM_SRC_PAIRS</code>.
 * The value of i must be between 1 and the number of packets
 * sources associated to the argument InStream (as returned
 * by function <code>#CrFwInStreamGetNOfSrc</code>).
 * If this constraint is violated, the return value of the function
 * is indeterminate.
 * This function may only be called after the argument InStream
 * has been initialized.
 * @param smDesc the descriptor of the Base State Machine of the InStream.
 * @param i the index of the source (starting from 1)
 * @return src the source associated to the OutStream
 */
CrFwDestSrc_t CrFwInStreamGetSrc(FwSmDesc_t smDesc, CrFwCounterU1_t i);

/**
 * Get the number of packet sources of the argument InStream.
 * An InStream can receive packets from one or more sources.
 * A source has an identifier of type <code>::CrFwDestSrc_t</code>.
 * The association between packet sources and InStream is done
 * statically in <code>#CR_FW_INSTREAM_SRC_PAIRS</code>.
 * This function may only be called after the argument InStream
 * has been initialized.
 * @param smDesc the descriptor of the Base State Machine of the InStream.
 * @return src the source associated to the OutStream
 */CrFwCounterU1_t CrFwInStreamGetNOfSrc(FwSmDesc_t smDesc);

#endif /* CRFW_INSTREAM_H_ */
