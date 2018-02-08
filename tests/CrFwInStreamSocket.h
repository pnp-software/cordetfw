/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Interface for the Socket-Based InStream.
 * The socket-based InStream is an InStream (see <code>CrFwInStream.h</code>) which
 * uses sockets to receive the command and report packets.
 * This component is built as a client socket using the Internet domain and the TCP
 * protocol.
 * This component is a singleton: it should not be instantiated more than once.
 *
 * This component is only intended for test and demo purposes.
 * It does not cover contingencies and has not been verified to the same level as
 * the framework components.
 *
 * This InStream is designed to work with the Socket-Based OutStream of
 * <code>CrFwOutStreamSocket.h</code> which performs the function of a socket server
 * and which is responsible for sending the command and report packets to the
 * InStream.
 *
 * The InStream must be initialized with the port number and with the host name.
 *
 * As part of its initialization, this InStream creates and connects a socket.
 * The InStream assumes a polling approach towards the middleware.
 * Function <code>::CrFwInStreamSocketPoll</code> should be called periodically
 * by an external scheduler.
 * This function performs a non-blocking read on the socket to check whether a packet
 * is available at the socket.
 * If a packet is available, the function calls function <code>::CrFwInStreamPcktAvail</code>
 * on the InStream to signal the arrival of a new packet.
 * This causes all pending packets to be collected by the InStream and stored in
 * its Packet Queue from which the application can retrieve them using function
 * <code>::CrFwInStreamGetPckt</code>.
 *
 * The InStream assumes that at each read operation, an entire packet is received.
 * The situation where the packet is split into fragments during the transmission
 * process is not handled.
 * In practice, this InStream is intended for the case where the socket is local
 * to the host platform (i.e. where the host name is "localhost" and both InStream
 * and OutStream are located on the same platform).
 *
 * Packets which are read from the socket are stored in a buffer (the <i>Read Buffer</i>).
 * This is an array of bytes whose size is equal to the maximum size of a
 * middleware packet.
 * The Read Buffer can be either "full" (if its first byte is different from zero)
 * or "empty" (if its first byte has been cleared).
 *
 * If the InStream encounters an error while performing a system call, it uses function
 * <code>perror</code> to print an error message and, if the error was encountered
 * in the initialization or configuration action, it sets the outcome of the action
 * to 0 ("failure") and returns.
 *
 * This InStream assumes that the maximum length of a packet is smaller than 256.
 * Compliance with this constraint is verified in the Initialization Check.
 *
 * <b>Mode of Use of a Socket-Based InStream Component</b>
 *
 * After creation, the InStream user must define the port number and server host name
 * for the OutStream.
 * This is done through functions <code>::CrFwInStreamSocketSetPort</code> and
 * <code>::CrFwInStreamSocketSetHost</code>.
 * After this is done, the InStream can be initialized and configured.
 *
 * The InStream should only be initialized after its OutStream has completed its
 * initialization.
 *
 * After the InStream has completed its configuration, users should periodically
 * call function <code>::CrFwInStreamSocketPoll</code> to poll the socket for any
 * incoming packets.
 * Packets can be collected with function <code>::CrFwInStreamGetPckt</code>.
 *
 * If the server socket is closed (i.e. if the OutStream is shutdown), a call to the
 * socket read operation in the InStream (i.e. a call to <code>::CrFwInStreamSocketPoll</code>)
 * will result in the last packet sent by the OutStream being read from the socket.
 * Hence, correct operation requires that the InStream be shutdown before its OutStream.
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

#ifndef CRFW_INSTREAMSOCKET_H_
#define CRFW_INSTREAMSOCKET_H_

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
 * Initialization action for the socket-based InStream.
 * This action:
 * - creates the Read Buffer;
 * - creates and connects the socket as a non-blocking socket;
 * - executes the Initialization Action of the base InStream (function
 *   <code>::CrFwInStreamDefInitAction</code>)
 * - sets the outcome to "success" if the previous operations are successful.
 * .
 * @param prDesc the initialization procedure descriptor.
 */
void CrFwInStreamSocketInitAction(FwPrDesc_t prDesc);

/**
 * Shutdown action for the socket-based InStream.
 * This action executes the Shutdown Action of the base InStream (function
 * <code>::CrFwInStreamDefShutdownAction</code>), releases the Read Buffer, and
 * closes the socket.
 * @param smDesc the InStream State Machine descriptor (this parameter
 * is not used).
 */
void CrFwInStreamSocketShutdownAction(FwSmDesc_t smDesc);

/**
 * Initialization check for the socket-based InStream.
 * The check is successful if: the maximum length of a packet (as retrieved from
 * <code>::CrFwPcktGetMaxLength</code>) is smaller than 256; and the port number
 * and server host name have been set.
 * @param prDesc the initialization procedure descriptor.
 */
void CrFwInStreamSocketInitCheck(FwPrDesc_t prDesc);

/**
 * Configuration action for the socket-based InStream.
 * This action clears the Read Buffer and executes the the Configuration Action of
 * the base InStream (function <code>::CrFwInStreamDefConfigAction</code>)
 * @param prDesc the configuration procedure descriptor.
 */
void CrFwInStreamSocketConfigAction(FwPrDesc_t prDesc);

/**
 * Poll the socket to check whether a new packet has arrived.
 * This function should be called periodically by an external scheduler.
 * It performs a non-blocking read on the socket to check whether a packet
 * is available at the socket.
 * If a packet is available, it is placed into the Read Buffer and then function
 * <code>::CrFwInStreamPcktAvail</code> is called to signal the arrival of a new packet.
 * @param inStream the socket-based InStream
 */
void CrFwInStreamSocketPoll(FwSmDesc_t inStream);

/**
 * Function implementing the Packet Collect Operation for the socket-based InStream.
 * If the Read Buffer is full, this function:
 * - creates a packet instance through a call to <code>CrFwPcktMake</code>
 * - copies the content of the Read Buffer into the newly created packet instance
 * - clears the Read Buffer
 * - returns the packet instance
 * .
 * If the Read Buffer is empty, this function returns NULL.
 * Note that the logic of the socket-based InStream guarantees that the Read Buffer
 * will always be full when this function is called.
 * @param src the source associated to the InStream (not used in this stub)
 * @return the packet
 */
CrFwPckt_t CrFwInStreamSocketPcktCollect(CrFwDestSrc_t src);

/**
 * Function implementing the Packet Available Check Operation for the InStream.
 * This function implements the following logic:
 * - The function begins by checking the Read Buffer.
 * - If it is full, the function returns 1.
 * - If the Read Buffer is not full, the function performs a non-blocking read
 *   on the socket.
 * - If the read operation returns nothing, the function returns 0.
 * - If the read operation returns a packet, the function stores it in the
 *   Read Buffer and then returns 1.
 * .
 * @param src the source associated to the InStream (not used in this stub)
 * @return the value of a predefined flag
 */
CrFwBool_t CrFwInStreamSocketIsPcktAvail(CrFwDestSrc_t src);

/**
 * Set the port number for the socket.
 * The port number must be an integer greater than 2000.
 * @param n the port number.
 */
void CrFwInStreamSocketSetPort(unsigned short n);

/**
 * Set the host name of the server.
 * If a local socket is being created, the host name should be set to
 * "localhost".
 * @param name the host number.
 */
void CrFwInStreamSocketSetHost(char* name);

#endif /* CRFW_INSTREAMSOCKET_H_ */
