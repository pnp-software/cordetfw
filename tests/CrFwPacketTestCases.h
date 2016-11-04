/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the default packet implementation of
 * <code>CrFwBaseCmp.h</code>.
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

#ifndef CRFW_PACKET_TESTCASES_H_
#define CRFW_PACKET_TESTCASES_H_

#include "CrFwConstants.h"

/**
 * Test the creation of a packet and the read and write operations
 * on its attributes.
 * The test performs the following actions:
 * - Attempt to create a packet with an illegal length (either greater
 *   than the allowed maximum or smaller than 1) and check
 *   that nothing is returned.
 * - Make a packet and check that its length is correctly set.
 * - Set and get all the pre-defined attributes of a packet.
 * .
 * @verify Application Error: crPcktAllocationFail
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwPacketTestCase1();

/**
 * Test the creation and release functions for a packet.
 * The test performs the following actions:
 * - It creates the maximum allowed number of packets.
 * - It verifies that the packet availability check returns false
 * - It attempts to create a new packet and checks that the attempt
 *   fails.
 * - It releases one packet, verifies that the packet availability check
 *   now returns true and then attempts to create the new packet
 *   and verifies that this time the attempt succeeds.
 * - It releases all created packets and then checks that the same
 *   number of packets can again be created.
 * - It verifies that the packet availability check returns false
 *   when the packet length is either negative or zero or
 *   greater than the allowed maximum.
 * .
 * @verify Application Error: crPcktAllocationFail
 * @verify Application Error: crPcktRelErr
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwPacketTestCase2();

/**
 * Test the packet queue functions which are not covered through other tests.
 * The test performs the following actions:
 * - It creates a packet queue and attempts to pop an item from the empty
 *   packet queue and to get the oldest item from the packet queue.
 * - It resets the empty packet queue.
 * - It pushes and pops and items from packet queue and verifies that they are
 *   managed in FIFO order
 * - It creates a situation where the oldest packet in the queue is behind
 *   the next free slot in the queue and then resets the packet queue
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwPacketQueueTestCase1();

#endif /* CRFW_BASECMP_TESTCASES_H_ */
