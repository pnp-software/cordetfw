/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the socket-based InStream and OutStream Components
 * (see <code>CrFwInStreamSocket.h</code> and <code>CrFwOutStreamSocket.h</code>).
 *
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

#ifndef CRFW_SOCKET_TESTCASES_H_
#define CRFW_SOCKET_TESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"

/**
 * Test the initialization and configuration of the socket-based InStream and
 * OutStream.
 * The following actions are performed in this test:
 * - The Socket-Based InStream and OutStream are created, initialized and configured
 *   and it is checked that both enter state CONFIGURED.
 * - A packet is sent to the OutStream and it is checked that it is correctly received
 *   by the InStream.
 * - Several packets are sent to the OutStream and then the InStream is polled and it
 *   is checked that all packets are correctly received.
 * - The InStream is polled without any packet having been sent by the OutStream and it is
 *   checked that nothing is returned.
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwSocketTestCase1();

/**
 * Test the initialization and configuration of the client and server sockets of
 * <code>CrFwClientSocket.h</code> and <code>CrFwServerSocket.h</code>.
 * The configuration of the client and server sockets is as follows (see
 * <code>CrFwInStreamUserPar.h</code> and <code>CrFwOutStreamUserPar.h</code>):
 * - InStream6 and OutStream6 are attached to the client socket
 * - InStream7 and OutStream7 are attached to the server socket
 * - The client socket is designed to route incoming packets to InStream6
 * - The server socket is designed to route incoming packets to InStream7
 * .
 * The following actions are performed in this test:
 * - The InStream and OutStreams 6 and 7 which use the <code>CrFwClientSocket.h</code>
 *   and <code>CrFwServerSocket.h</code> are created.
 * - The server socket is initialized (by initializing an InStream or OutStream attached to
 *   it), then the client socket is initialized (by initializing an InStream or
 *   OutStream attached to it), and then both are configured (by configuring the
 *   InStreams and OutStream.
 * - A packet is sent from the server socket (OutStream7) to the client socket
 *   (InStream6) and it is checked that it is correctly received.
 * - A packet is sent from the client socket (OutStream6) to the server socket
 *   (InStream7) and it is checked that it is correctly received.
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwSocketTestCase2();

/**
 * Test the sending and receiving of multiple packets through client and server sockets of
 * <code>CrFwClientSocket.h</code> and <code>CrFwServerSocket.h</code>.
 * The configuration of the client and server sockets is as follows (see
 * <code>CrFwInStreamUserPar.h</code> and <code>CrFwOutStreamUserPar.h</code>):
 * - InStream6 and OutStream6 are attached to the client socket
 * - InStream7 and OutStream7 are attached to the server socket
 * - The client socket is designed to route incoming packets to InStream6
 * - The server socket is designed to route incoming packets to InStream7
 * .
 * The following actions are performed in this test:
 * - The InStream and OutStreams 6 and 7 which use the <code>CrFwClientSocket.h</code>
 *   and <code>CrFwServerSocket.h</code> are created, initialized and configured.
 * - Several packets are sent from the server socket (OutStream7) to the client socket
 *   (InStream6) and it is checked that they are correctly received.
 * - Several packets are sent from the client socket (OutStream6) to the server socket
 *   (InStream7) and it is checked that they are correctly received.
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwSocketTestCase3();

/**
 * Test the interleaved sending and receiving of multiple packets through client and
 * server sockets of <code>CrFwClientSocket.h</code> and <code>CrFwServerSocket.h</code>.
 * The configuration of the client and server sockets is as follows (see
 * <code>CrFwInStreamUserPar.h</code> and <code>CrFwOutStreamUserPar.h</code>):
 * - InStream6 and OutStream6 are attached to the client socket
 * - InStream7 and OutStream7 are attached to the server socket
 * - The client socket is designed to route incoming packets to InStream6
 * - The server socket is designed to route incoming packets to InStream7
 * .
 * The following actions are performed in this test:
 * - The InStream and OutStreams 6 and 7 which use the <code>CrFwClientSocket.h</code>
 *   and <code>CrFwServerSocket.h</code> are created, initialized and configured.
 * - Several packets are sent from the server socket (OutStream7) to the client socket
 *   (InStream6) and from the client socket (OutStream6) to the server socket (InStream7);
 *   the sending operation through the two sockets are interleaved.
 * - It is checked that all packets are correctly received.
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwSocketTestCase4();

#endif /* CRFW_SOCKET_TESTCASES_H_ */
