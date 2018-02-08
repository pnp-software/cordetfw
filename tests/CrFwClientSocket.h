/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Interface for a client socket to be used by InStreams and OutStreams.
 * This module defines the functions through which the InStreams and OutStreams control the socket
 * in order to receive packets (InStream) or to send them (OutStream).
 * These functions are used to customize the InStreams (see <code>CrFwInStreamUserPar.h</code>)
 * and the OutStreams (see <code>CrFwInStreamUserPar.h</code>) which interact with the socket.
 * More precisely:
 * - Function <code>::CrFwClientSocketInitAction</code> should be used as the initialization
 *   action for the InStreams and OutStreams.
 * - Function <code>::CrFwClientSocketInitCheck</code> should be used as the initialization
 *   check action for the InStreams and OutStreams.
 * - Function <code>::CrFwClientSocketConfigAction</code> should be used as the configuration
 *   action for the InStreams and OutStreams.
 * - Function <code>::CrFwClientSocketShutdownAction</code> should be used as the shutdown
 *   action for the InStreams and OutStreams.
 * - Function <code>::CrFwClientSocketPcktCollect</code> should be used as the Packet Collect
 *   operation for the InStreams.
 * - Function <code>::CrFwClientSocketIsPcktAvail</code> should be used as the Packet Available
 *   Check operation for the InStreams.
 * - Function <code>::CrFwClientSocketPcktHandover</code> should be used as the Packet Hand-Over
 *   operation for the OutStreams.
 * .
 * The functions in this module should be accessed in mutual exclusion.
 * Compliance with this constraint is not enforced and is therefore under the responsibility
 * of the caller.
 *
 * The socket controlled by this module is built as a client socket using the Internet domain
 * and the TCP protocol.
 * It is designed to work with the server socket of <code>CrFwServerSocket.h</code>.
 *
 * The socket must be initialized with the port number and with the host name for
 * its socket (these are defined through functions <code>::CrFwClientSocketSetPort</code> and
 * <code>::CrFwClientSocketSetHost</code>).
 *
 * The socket assumes a polling approach for incoming packets: function
 * <code>::CrFwClientSocketPoll</code> should be called periodically
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
 * <code>::CrFwClientSocketPcktHandover</code> which performs a non-blocking write
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
 * <b>Mode of Use of a Client Socket Module</b>
 *
 * This module may be controlled jointly by multiple InStreams and/or OutStreams.
 * Its socket is initialized when the first of the these components is initialized
 * (the initialization of the other InStreams/OutStreams has no effect).
 * The socket is reset whenever one of the InStreams/OutStreams is reset.
 * The socket is shut down whenever one of the InStreams/OutStreams is shut down
 * (the shutdown of the other InStreams/OutStreams has no effect).
 *
 * This client socket should only be initialized after its server socket has completed
 * its initialization.
 *
 * After the client socket has completed its configuration, users should periodically
 * call function <code>::CrFwClientSocketPoll</code> to poll the socket for any
 * incoming packets.
 *
 * If the server socket is closed, a call to the socket read operation in the client
 * socket (i.e. a call to <code>::CrFwClientSocketPoll</code>)
 * will result in the last packet sent by the server socket being read from the socket.
 * Hence, correct operation requires that the client socket be shutdown before server
 * socket.
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

#ifndef CRFW_CLIENTSOCKET_H_
#define CRFW_CLIENTSOCKET_H_

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
 * Initialization action for the client socket.
 * If the client socket has already been initialized, this function calls the
 * Initialization Action of the base InStream/OutStream and then returns.
 * If the client socket has not yet been initialized, this action:
 * - creates the Read Buffer;
 * - creates and connects the socket as a non-blocking socket;
 * - executes the Initialization Action of the base InStream/OutStream;
 * - sets the outcome to "success" if the previous operations are successful.
 * .
 * @param prDesc the initialization procedure descriptor.
 */
void CrFwClientSocketInitAction(FwPrDesc_t prDesc);

/**
 * Shutdown action for the client socket.
 * If the client socket has already been shut down, this function calls the
 * Shutdown Action of the base InStream/OutStream and then returns.
 * If the client socket has not yet been shut down, this action executes
 * the Shutdown Action of the base InStream/OutStream, releases the Read Buffer,
 * and closes the socket.
 * @param smDesc the InStream or OutStream State Machine descriptor.
 */
void CrFwClientSocketShutdownAction(FwSmDesc_t smDesc);

/**
 * Initialization check for the client socket.
 * The check is successful if: the maximum length of a packet (as retrieved from
 * <code>::CrFwPcktGetMaxLength</code>) is smaller than 256; and the port number
 * and server host name have been set.
 * @param prDesc the initialization procedure descriptor.
 */
void CrFwClientSocketInitCheck(FwPrDesc_t prDesc);

/**
 * Configuration action for the client socket.
 * This action clears the Read Buffer and executes the Configuration Action of
 * the base InStream (function <code>::CrFwInStreamDefConfigAction</code>)
 * @param prDesc the configuration procedure descriptor.
 */
void CrFwClientSocketConfigAction(FwPrDesc_t prDesc);

/**
 * Poll the client socket to check whether a new packet has arrived.
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
 * <code>CrFwSocketTestCase.h</code> and then the incoming packets are
 * routed to the 6-th InStream.
 */
void CrFwClientSocketPoll();

/**
 * Function implementing the Packet Collect Operation for the client socket.
 * If the packet in the Read Buffer has a source attribute equal to
 * <code>pcktSrc</code>, this function:
 * - creates a packet instance through a call to <code>CrFwPcktMake</code>
 * - copies the content of the Read Buffer into the newly created packet instance
 * - clears the Read Buffer
 * - returns the packet instance
 * .
 * If the Read Buffer holds a packet from a source other then
 * <code>pcktSrc</code>, this function returns NULL.
 * Note that the logic of the client socket module guarantees that the Read Buffer
 * will always be full when this function is called.
 * @param pcktSrc the source associated to the InStream
 * @return the packet
 */
CrFwPckt_t CrFwClientSocketPcktCollect(CrFwDestSrc_t pcktSrc);

/**
 * Function implementing the Packet Available Check Operation for the client socket.
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
CrFwBool_t CrFwClientSocketIsPcktAvail(CrFwDestSrc_t pcktSrc);

/**
 * Function implementing the hand-over operation for the client socket.
 * This function performs a non-blocking write on the socket and, if it succeeds,
 * it returns 1; otherwise, it returns 0.
 * @param pckt the packet to be written to the socket
 * @return 1 if the packet was successfully written to the socket; 0 otherwise.
 */
CrFwBool_t CrFwClientSocketPcktHandover(CrFwPckt_t pckt);

/**
 * Set the port number for the socket.
 * The port number must be an integer greater than 2000.
 * @param n the port number.
 */
void CrFwClientSocketSetPort(unsigned short n);

/**
 * Set the host name of the server.
 * If a local socket is being created, the host name should be set to
 * "localhost".
 * @param name the host number.
 */
void CrFwClientSocketSetHost(char* name);

#endif /* CRFW_CLIENTSOCKET_H_ */
