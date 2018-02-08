/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Interface for the Socket-Based OutStream.
 * The socket-based OutStream is an OutStream (see <code>CrFwOutStream.h</code>) which
 * uses sockets to send the command and report packets.
 * This component is built as a server socket using the Internet domain and the TCP
 * protocol.
 *
 * This component is only intended for test and demo purposes.
 * It does not cover contingencies and has not been verified to the same level as
 * the framework components.
 *
 * This OutStream is designed to work with the Socket-Based InStream of
 * <code>CrFwInStreamSocket.h</code> which performs the function of socket client.
 *
 * In its initialization process, the OutStream creates, binds and starts listening on
 * the socket.
 * It then spawns a threads which waits for incoming connection from a matching
 * InStream.
 * When the incoming connection has been accepted, the OutStream is ready to complete
 * its configuration.
 *
 * The packet hand-over operation is implemented in function
 * <code>::CrFwOutStreamSocketPcktHandover</code> which performs a non-blocking write
 * to the socket.
 *
 * If the OutStream encounters an error during a system call, it uses <code>perror</code>
 * to print the error message.
 * If the error was encountered in the initialization or configuration action, it sets the
 * outcome of the action to 0 ("failure") and returns.
 *
 * This OutStream assumes that the maximum length of a packet is smaller than 256.
 * Compliance with this constraint is verified in the Initialization Check.
 *
 * <b>Mode of Use of a Socket-Based OutStream Component</b>
 *
 * After creation, the OutStream user must define the port number for the OutStream.
 * This is done through function <code>::CrFwOutStreamSocketSetPort</code>.
 * After this is done, the OutStream can be initialized and configured.
 * During the initialization process, the OutStream spawns a thread which waits for
 * its InStream to be connected to it.
 * The OutStream can only be successfully configured after this thread has accepted the
 * connection from the InStream.
 *
 * The OutStream must complete its initialization before its InStream is initialized.
 *
 * After the OutStream has completed its configuration, users can send packets to it
 * for transmission to the InStream through calls to <code>::CrFwOutStreamSend</code>.
 * If the socket connection remains open and if the rate at which send requests are
 * made is not too high (i.e. if it does not flood the socket connection), the user
 * can continue to make send requests.
 * If a send request fails because the write operation to the socket has failed,
 * the user can call <code>::CrFwOutStreamConnectionAvail</code> to put the OutStream
 * back in its READY state and to attempt a resumption of the packet sending process.
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

#ifndef CRFW_OUTSTREAMSOCKET_H_
#define CRFW_OUTSTREAMSOCKET_H_

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
 * Initialization action for the socket-based OutStream.
 * This action:
 * - creates and binds the socket
 * - start listening on the socket
 * - spawns a thread which waits for an incoming connection from a matching InStream
 * - execute the Initialization Action of the base OutStream (function
 *   <code>::CrFwOutStreamDefInitAction</code>)
 * .
 * The function sets the outcome to "success" if all these operations are successful.
 * @param prDesc the initialization procedure descriptor.
 */
void CrFwOutStreamSocketInitAction(FwPrDesc_t prDesc);

/**
 * Initialization check for the socket-based OutStream.
 * The check is successful if the port number has been set to a value larger than 2000.
 * @param prDesc the initialization procedure descriptor.
 */
void CrFwOutStreamSocketInitCheck(FwPrDesc_t prDesc);

/**
 * Configuration check for the socket-based OutStream.
 * The check is successful if the connection from the matching InStream has been successfully
 * accepted.
 * @param prDesc the initialization procedure descriptor.
 */
void CrFwOutStreamSocketConfigCheck(FwPrDesc_t prDesc);

/**
 * Shutdown action for the socket-based OutStream.
 * This action executes the Shutdown Action of the base OutStream (function
 *   <code>::CrFwOutStreamDefShutdownAction</code>) and then closes the socket.
 * @param smDesc the OutStream State Machine descriptor (this parameter
 * is not used).
 */
void CrFwOutStreamSocketShutdownAction(FwSmDesc_t smDesc);

/**
 * Function implementing the hand-over operation for the socket-based OutStream.
 * This function performs a non-blocking write on the socket and, if it succeeds,
 * it returns 1; otherwise, it returns 0.
 * @param pckt the packet to be written to the socket
 * @return 1 if the packet was successfully written to the socket; 0 otherwise.
 */
CrFwBool_t CrFwOutStreamSocketPcktHandover(CrFwPckt_t pckt);

/**
 * Set the port number for the socket.
 * The port number must be an integer greater than 2000.
 * @param n the port number.
 */
void CrFwOutStreamSocketSetPort(unsigned short n);

#endif /* CRFW_OUTSTREAMSOCKET_H_ */
