/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Interface for a server socket to be used by InStreams and OutStreams.
 * This module defines the functions through which the InStreams and OutStreams control the socket
 * in order to receive packets (InStream) or to send them (OutStream).
 * These functions are used to customize the InStreams (see <code>CrFwInStreamUserPar.h</code>)
 * and the OutStreams (see <code>CrFwInStreamUserPar.h</code>) which interact with the socket.
 * More precisely:
 * - Function <code>::CrFwServerSocketInitAction</code> should be used as the initialization
 *   action for the InStreams and OutStreams.
 * - Function <code>::CrFwServerSocketInitCheck</code> should be used as the initialization
 *   check action for the InStreams and OutStreams.
 * - Function <code>::CrFwServerSocketConfigAction</code> should be used as the configuration
 *   action for the InStreams and OutStreams.
 * - Function <code>::CrFwServerSocketShutdownAction</code> should be used as the shutdown
 *   action for the InStreams and OutStreams.
 * - Function <code>::CrFwServerSocketPcktCollect</code> should be used as the Packet Collect
 *   operation for the InStreams.
 * - Function <code>::CrFwServerSocketIsPcktAvail</code> should be used as the Packet Available
 *   Check operation for the InStreams.
 * - Function <code>::CrFwServerSocketPcktHandover</code> should be used as the Packet Hand-Over
 *   operation for the OutStreams.
 * .
 * The functions in this module should be accessed in mutual exclusion.
 * Compliance with this constraint is not enforced and is therefore under the responsibility
 * of the caller.
 *
 * The socket controlled by this module is built as a server socket using the Internet domain
 * and the TCP protocol.
 * It is designed to work with the client socket of <code>CrFwClientSocket.h</code>.
 *
 * The socket must be initialized with the port number for its socket (this is defined through
 * functions <code>::CrFwClientSocketSetPort</code>.
 *
 * In the initialization process of this module, a socket is bound and listening starts on it.
 * A thread is then spawned which waits for incoming connections from a matching client socket.
 * When the incoming connection has been accepted, the socket is ready to complete
 * its configuration.
 *
 * The socket assumes a polling approach for incoming packets: function
 * <code>::CrFwServerSocketPoll</code> should be called periodically
 * by an external scheduler.
 * This function performs a non-blocking read on the socket to check whether a packet
 * is available at the socket.
 * If a packet is available, the function retrieves its source and forwards it to
 * the associated InStream by calling function <code>::CrFwInStreamPcktAvail</code>
 * on the InStream to signal the arrival of a new packet.
 * This causes all pending packets from that source to be collected by the InStream and
 * stored in its Packet Queue.
 *
 * The implementation of this module assumes that, at each read operation, an entire
 * packet is received.
 * The situation where the packet is split into fragments during the transmission
 * process is not handled.
 * In practice, this socket is intended for the case where the socket is local
 * to the host platform (i.e. where the host name is "localhost" and both sender
 * and receiver of a packet are located on the same platform).
 *
 * Packets which are read from the socket are stored in a buffer (the <i>Read Buffer</i>).
 * This is an array of bytes whose size is equal to the maximum size of a
 * middleware packet.
 * The Read Buffer can be either "full" (if its first byte is different from zero)
 * or "empty" (if its first byte has been cleared).
 *
 * The packet hand-over operation for OutStreams is implemented in function
 * <code>::CrFwServerSocketPcktHandover</code> which performs a non-blocking write
 * to the socket.
 *
 * If an error is encountered while performing a system call, this module uses function
 * <code>perror</code> to print an error message and, if the error was encountered
 * in the initialization or configuration action, it sets the outcome of the action
 * to 0 ("failure") and returns.
 *
 * This module assumes that the maximum length of a packet is smaller than 256 bytes.
 * Compliance with this constraint is verified in the Initialization Check.
 *
 * <b>Mode of Use of a Server Socket Module</b>
 *
 * This interface may be controlled jointly by multiple InStreams and/or OutStreams.
 * Its socket is initialized when the first of the these components is initialized
 * (the initialization of the other InStreams/OutStreams has no effect).
 * The socket is reset whenever one of the InStreams/OutStreams is reset.
 * The socket is shut down whenever one of the InStreams/OutStreams is shut down
 * (the shutdown of the other InStreams/OutStreams has no effect).
 *
 * After creation, the user must define the port number for the socket.
 * This is done through function <code>::CrFwServerSocketSetPort</code>.
 * After this is done, the socket can be initialized and configured.
 * During the initialization process, a thread is spawned which waits for a client socket
 * to be connected to it.
 * The server socket can only be successfully configured after this thread has accepted the
 * connection from the client socket.
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

#ifndef CRFW_SERVERSOCKET_H_
#define CRFW_SERVERSOCKET_H_

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
 * Initialization action for the server socket.
 * If the server socket has already been initialized, this function calls the
 * Initialization Action of the base InStream/OutStream and then returns.
 * If the server socket has not yet been initialized, this action:
 * - creates and binds the socket
 * - start listening on the socket
 * - spawns a thread which waits for an incoming connection from a matching client socket
 * - execute the Initialization Action of the base InStream/OutStream
 * .
 * The function sets the outcome to "success" if all these operations are successful.
 * @param prDesc the initialization procedure descriptor.
 */
void CrFwServerSocketInitAction(FwPrDesc_t prDesc);

/**
 * Initialization check for the server socket.
 * The check is successful if the port number has been set to a value larger than 2000.
 * @param prDesc the initialization procedure descriptor.
 */
void CrFwServerSocketInitCheck(FwPrDesc_t prDesc);

/**
 * Configuration check for the server socket.
 * The check is successful if the connection from the matching client socket has been successfully
 * accepted.
 * @param prDesc the initialization procedure descriptor.
 */
void CrFwServerSocketConfigCheck(FwPrDesc_t prDesc);

/**
 * Shutdown action for the server socket.
 * If the server socket has already been shut down, this function calls the
 * Shutdown Action of the base InStream/OutStream and then returns.
 * If the client socket has not yet been shut down, this action executes
 * the Shutdown Action of the base OutStream/InStream and then closes the socket.
 * @param smDesc the OutStream State Machine descriptor (this parameter
 * is not used).
 */
void CrFwServerSocketShutdownAction(FwSmDesc_t smDesc);

/**
 * Function implementing the hand-over operation for the server socket.
 * This function performs a non-blocking write on the socket and, if it succeeds,
 * it returns 1; otherwise, it returns 0.
 * @param pckt the packet to be written to the socket
 * @return 1 if the packet was successfully written to the socket; 0 otherwise.
 */
CrFwBool_t CrFwServerSocketPcktHandover(CrFwPckt_t pckt);

/**
 * Configuration action for the server socket.
 * This action clears the Read Buffer and executes the Configuration Action of
 * the base InStream/OutStream.
 * @param prDesc the configuration procedure descriptor.
 */
void CrFwServerSocketConfigAction(FwPrDesc_t prDesc);

/**
 * Poll the server socket to check whether a new packet has arrived.
 * This function should be called periodically by an external scheduler.
 * If there is a pending packet (i.e. of the Read Buffer is full), its source
 * is determined, and then function <code>::CrFwInStreamPcktAvail</code> is
 * called on the InStream associated to that packet source.
 * If there is no pending packet (i.e. if the Read Buffer is empty),
 * a non-blocking read is performed on the socket to check whether a packet
 * is available at the socket.
 * If a packet is available, it is placed into the Read Buffer, its source
 * is determined, and then function <code>::CrFwInStreamPcktAvail</code> is
 * called on the InStream associated to that packet source.
 * In a realistic implementation, the source of the incoming packet would
 * be determined from the packet itself (which holds its source in its
 * header).
 * This implementation is intended for use with the test cases of
 * <code>CrFwSocketTestCase.h</code> and the incoming packets are
 * routed to the 7-th InStream.
 */
void CrFwServerSocketPoll();

/**
 * Function implementing the Packet Collect Operation for the server socket.
 * If the packet in the Read Buffer has a source attribute equal to
 * <code>pcktSrc</code>, this function:
 * - creates a packet instance through a call to <code>CrFwPcktMake</code>
 * - copies the content of the Read Buffer into the newly created packet instance
 * - clears the Read Buffer
 * - returns the packet instance
 * .
 * If the Read Buffer holds a packet from a source other then
 * <code>pcktSrc</code>, this function returns NULL.
 * Note that the logic of the server socket module guarantees that the Read Buffer
 * will always be full when this function is called.
 * @param pcktSrc the source associated to the InStream
 * @return the packet
 */
CrFwPckt_t CrFwServerSocketPcktCollect(CrFwDestSrc_t pcktSrc);

/**
 * Function implementing the Packet Available Check Operation for the server socket.
 * This function implements the following logic:
 * - The function begins by checking the Read Buffer.
 * - If it is full and the source attribute of the packet it contains is equal
 *   to <code>packetSource</code>, the function returns 1.
 * - If the Read Buffer is not full or it is full but the source attribute of the
 *   packet it contains is not equal to <code>packetSource</code>, the function
 *   performs a non-blocking read on the socket.
 * - If the read operation returns nothing or returns a packet with a source
 *   attribute other than <code>packetSource</code>, the function returns 0.
 * - If the read operation returns a packet with a source attribute equal to
 *   <code>packetSource</code>, the function stores it in the
 *   Read Buffer and then returns 1.
 * .
 * @param pcktSrc the source associated to the InStream
 * @return the value of a predefined flag
 */
CrFwBool_t CrFwServerSocketIsPcktAvail(CrFwDestSrc_t pcktSrc);

/**
 * Set the port number for the socket.
 * The port number must be an integer greater than 2000.
 * @param n the port number.
 */
void CrFwServerSocketSetPort(unsigned short n);

#endif /* CRFW_SERVERSOCKET_H_ */
