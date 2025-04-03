/**
 * @file
 * @ingroup outMngGroup
 * Definition of the OutStream component.
 *
 * An application instantiates one or more OutStreams to represent the logical
 * connections through which reports or commands are sent to their destination.
 * An OutStream is implemented by the OutStream State Machine (see figures below)
 * embedded within state CONFIGURED of a Base State Machine.
 *
 * This header file defines a function to create and access the OutStream attached to a
 * certain command or report destination.
 * This header file therefore also defines the interface to the OutStreamRegistry
 * component of the CORDET Framework.
 *
 * An application can instantiate several OutStream Components.
 * Each OutStream component is associated to one or more destinations. 
 * The mapping from the destinations to the OutStreams is in parameter
 * <code>#CR_FW_OUTSTREAM_DEST_PAIRS</code>.
 * 
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
 * An OutStream maintains counters of packets which have been successfully handed over to the
 * middleware since the OutStream was last reset and of the total number of bytes which
 * have been successfully handed over to the middleware.
 * These counters can be accessed through functions 
 * <code>::CrFwOutStreamGetNOfHandedOverBytes</code> and 
 * <code>::CrFwOutStreamGetNOfHandedOverPckts</code>.
 *
 * @image html OutStream.png
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

#ifndef CRFW_OUT_STREAM_H_
#define CRFW_OUT_STREAM_H_

/* Include FW Profile Files */
#include "FwSmConstants.h"
#include "FwPrConstants.h"
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
 * The OutStream identifier outStreamId must be in the range: 
 * [0, <code>#CR_FW_NOF_OUTSTREAM</code>-1].
 * If the identifier is out of range, the function returns NULL and sets the application
 * error code to: <code>::crOutStreamIllId</code>.
 *
 * The first time this function is called with a certain value of i, it returns an
 * OutStream State Machine which has been started but which still needs to be initialized and
 * configured.
 * 
 * The first time this function is called, it builds the DTS_SET by calling 
 * the function <code>#CR_FW_OUTSTREAM_SET_DTS</code>.
 * The number of elements in the DTS_SET is then used to allocate the memory
 * for the array holding the type counters (since there is one type counter for
 * each element of DTS_SET).
 * 
 * @param outStreamId the identifier of the Base State Machine of the OutStream
 * @return the descriptor of the OutStream State Machine or NULL
 * if the state machine could not be created or if the identifier outStreamId 
 * is out of range.
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
 * An OutStream is associated to one or more destinations.
 * The binding between an OutStream and its destinations is done statically in the
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
 * Return the i-th destination associated to the argument outStream.
 * The value of i must be in the range 1 to N with N being the number of
 * destinations associated to the outStream as returned by function
 * <code>::CrFwOutStreamGetNOfDest</code>.
 * If this constraint is violated, the return value of the function is
 * unpredictable.
 * 
 * The binding between an OutStream and its destinations is done statically in the
 * array <code>#CR_FW_OUTSTREAM_DEST_PAIRS</code>.
 * The first destination associated to the outStream is the destination
 * in the first pair of <code>#CR_FW_OUTSTREAM_DEST_PAIRS</code> whicih is
 * associated to the outStream; the second destination associated to it
 * is the destination in the second pair; etc.
 * 
 * This function may only be called after the outStream has been initialized.
 * 
 * @param outStream the outStream
 * @param i the index of the desired destination (starting from 1)
 * @return the i-th destination of the outStream  
 */
CrFwDestSrc_t CrFwOutStreamGetDest(FwSmDesc_t outStream, CrFwCounterU1_t i);

/**
 * Return the number of destinations associated to the argument outStream.
 * The binding between an OutStream and its destinations is done statically in the
 * array <code>#CR_FW_OUTSTREAM_DEST_PAIRS</code>.
 * This function may only be called after the outStream has been initialized.
 * @param outStream the outStream
 * @return the number of destinations associated to the outStream  
 */
CrFwCounterU1_t CrFwOutStreamGetNOfDest(FwSmDesc_t outStream);

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
 * When a packet is successfully sent to the middleware, the counters of handed-over
 * bytes and handed-over packets are incremented accordingly.
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
 * This function resets the packet queue of the OutStream and the counters
 * of handed over bytes and packets.
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
 * This function allocates the memory for the packet queue of the OutStream
 * and for the array holding the destinations associated to the outStream,
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
 * This function resets the packet queue  and the counters
 * of handed over bytes and packets and then it releases the memory allocated 
 * to the packet queue and to the array holding the destinations associated 
 * to the outStream.
 *
 * This function should never be directly called by the end-application.
 * It is declared as a public function so that it may be used in application-specific
 * Shutdown Actions.
 * @param smDesc the descriptor of the OutStream State Machine
 */
void CrFwOutStreamDefShutdownAction(FwSmDesc_t smDesc);

/**
 * Default implementation of Set DST Function for the OutStreams.
 * The Set DTS Function is responsible for defining the DTS_SET.
 * The DTS_SET defines the triplets (destination,type,sub-type) 
 * for which the OutStream maintain a type counter.
 * 
 * The Set DTS function computes and returns:
 * - The number of type counters to be managed by the OutStreams
 * - The array of destination-type keys for which type counters
 *   must be maintained
 * .
 * This default implementation builds DTS_SET by collecting all 
 * the types and sub-types (t,s) of the out-going reports defined in
 * <code>#CR_FW_OUTCMP_INIT_KIND_DESC</code> and then building all
 * triplets for the case of the destination ID being equal to 1.
 * 
 * This function allocates the memory for array 
 * <code>#outStreamDestTypeKey</code> using malloc. 
 * It is therefore only suitable for use during
 * the application initialization phase.
 * 
 * @param pNofTypeCounter pointer to variable holding the number of 
 * type counters (i.e. the number of triplets (d,t,s) in DTS_SET)
 * @param destTypeKey pointer to array of products d*t*s for all
 * triplets (d,t,s) in DTS_SET  arranged in increasing order
 */
void CrFwOutStreamDefSetDTS(CrFwCounterU2_t* pNofTypeCounter,
                            CrFwDestTypeKey_t** destTypeKey);

/**
 * Return the value of the sequence counter for one of the groups
 * maintained by the OutStreams.
 * The group identifier is passed as an argument to the function call.
 * No check is performed on the validity of the group identifier.
 * @param group the identifier of the group
 * @return the OutStream sequence counter
 */
CrFwSeqCnt_t CrFwOutStreamGetSeqCnt(CrFwGroup_t group);

/**
 * Sets the value of the sequence counter for one of the groups
 * maintained by the OutStreams.
 * The group identifier is passed as an argument to the function call.
 * No check is performed on the validity of the group identifier.
 * @param group the identifier of the group
 * @param seqCnt the OutStream sequence counter
 */
void CrFwOutStreamSetSeqCnt(CrFwGroup_t group, CrFwSeqCnt_t seqCnt);

/**
 * Return the number of packets currently in the packet queue of an OutStream.
 * @param smDesc the descriptor of the OutStream State Machine.
 * @return the number of packets currently in the packet queue of the OutStream.
 */
CrFwCounterU1_t CrFwOutStreamGetNOfPendingPckts(FwSmDesc_t smDesc);

/**
 * Return the number of groups associated to the OutStreams.
 * @return the number of groups associated to the OutStreams.
 */
CrFwGroup_t CrFwOutStreamGetNOfGroups();

/**
 * Return the size of the packet queue of the OutStream.
 * @param smDesc the descriptor of the OutStream State Machine.
 * @return the size of the packet queue of the OutStream.
 */
CrFwCounterU1_t CrFwOutStreamGetPcktQueueSize(FwSmDesc_t smDesc);

/**
 * Return the number of bytes which the OutStream successfully handed over 
 * to the middleware since it was last reset.
 * @param smDesc the descriptor of the OutStream State Machine.
 * @return the number of bytes which the OutStream successfully handed over 
 * to the middleware since it was last reset.
 */
CrFwCounterU3_t CrFwOutStreamGetNOfHandedOverBytes(FwSmDesc_t smDesc);

/**
 * Return the number of packets which the OutStream successfully handed over 
 * to the middleware since it was last reset.
 * @param smDesc the descriptor of the OutStream State Machine.
 * @return the number of packets which the OutStream successfully handed over 
 * to the middleware since it was last reset.
 */
CrFwCounterU3_t CrFwOutStreamGetNOfHandedOverPckts(FwSmDesc_t smDesc);

/**
 * Return the number of type counters maintained by the OutStreams.
 * @return the number of type counters maintained by the OutStreams.
 */
CrFwCounterU2_t CrFwOutStreamGetNOfTypeCounters();

/**
 * Return the current type counter for a (destination, type, sub-type)
 * triplet or zero if the triplet is not in DTS_SET.
 * The value returned by this function is the type counter which 
 * the OutStream will allocate to the next out-going packet with
 * the argument destination, type and sub-type.
 * If the (destination, type, sub-type) is not in DTS_SET, then
 * zero is returned.
 * 
 * This function may only be called after the DTS_SET has been built.
 * The DTS_SET is built the first time function 
 * <code>::CrFwOutStreamMake</code> is called.
 * 
 * @param dest the packet destination
 * @param servType the packet service type
 * @param servSubType the packet service sub-type
 * @return the type counter for the argument (destination, type,
 *         sub-type) triplet.
 */
CrFwTypeCnt_t CrFwOutStreamGetTypeCounter(CrFwDestSrc_t dest, 
                                          CrFwServType_t servType,
                                          CrFwServSubType_t servSubType);
 
/**
 * Check whether the (destination, type, sub-type) triplet is in 
 * DTS_SET.
 * 
 * This function may only be called after the DTS_SET has been built.
 * The DTS_SET is built the first time function 
 * <code>::CrFwOutStreamMake</code> is called.
 * 
 * @param dest the packet destination
 * @param servType the packet service type
 * @param servSubType the packet service sub-type
 * @return the number of type counters maintained by the OutStreams.
 */
CrFwBool_t CrFwOutStreamIsInDtsSet(CrFwDestSrc_t dest, 
                                   CrFwServType_t servType,
                                   CrFwServSubType_t servSubType);

#endif /* CRFW_OUT_STREAM_H_ */
