/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the InStream Component (see <code>CrFwInStream.h</code>).
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

#ifndef CRFW_INSTREAM_TESTCASES_H_
#define CRFW_INSTREAM_TESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwProfile/FwSmConstants.h"

/**
 * Test the initialization and packet queue (PQ) management of the InStream.
 * The following actions are performed in this test:
 * - Attempt to instantiate an InStream with an illegal identifier and check that the operation
 *   fails.
 * - Instantiate one InStream twice and check that the same instance is returned on both
 *   occasions.
 * - Check that the InStream State Machine is correctly configured.
 * - Initialize and reset the InStream and check that the component enters state CONFIGURED
 * - Configure the Packet Available Check Operation to return "no packet available" and check that,
 *   at instantiation, the InStream enters state WAITING
 * - Check the function to get an InStream as a function of the packet source
 * .
 * @verify Application Error: crInStreamIllId
 * @verify Base SM Transition: IPS->CREATED
 * @verify Base SM Transition: CREATED->INITIALIZED
 * @verify Base SM Transition: INITIALIZED->CONFIGURED
 * @verify InStream SM Transition: IPS->WAITING
 * @verify Initialization Procedure: Initialization Action Successful
 * @verify Initialization Procedure: Initialization Check Successful
 * @verify Reset Procedure: Configuration Action Successful
 * @verify Reset Procedure: Configuration Check Successful
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInStreamTestCase1();

/**
 * Test the collection of packets from an InStream.
 * This test must be executed as a follow-on to <code>::CrFwInStreamTestCase1</code>.
 * The following actions are performed in this test:
 * - It is verified that the first InStream is in state CONFIGURED and WAITING.
 * - The stub functions are set up to simulate a situation where two packets have
 *   arrived.
 * - The PACKET_AVAILABLE command is sent to the InStream and it is verified that a
 *   transition is made to PCKT_AVAIL.
 * - The GET_PCKT command is sent to the InStream and it is verified that a packet
 *   is returned and the InStream remains in PCKT_AVAIL.
 * - The GET_PCKT command is sent to the InStream and it is verified that a packet
 *   is returned and the InStream moves to WAITING.
 * .
 * @verify InStream SM Transition: WAITING->PCKT_AVAIL
 * @verify InStream SM Transition: PCKT_AVAIL->PCKT_AVAIL (through CPS)
 * @verify InStream SM Transition: PCKT_AVAIL->WAITING
 * @verify Packet Collect Procedure: Flag_1 is true; PQ is not full; MW is in state PCKT_AVAIL
 * @verify Packet Collect Procedure: Flag_1 is true; PQ is not full; MW is not in state PCKT_AVAIL
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInStreamTestCase2();

/**
 * Test the self-transition on state PCKT_AVAIL and the shutdown of an InStream.
 * This test must be executed as a follow-on to <code>::CrFwInStreamTestCase2</code>.
 * The following actions are performed in this test:
 * - It is verified that the first InStream is in state CONFIGURED and WATING.
 * - The stub functions are set up to simulate a situation where one packet has
 *   arrived.
 * - The PACKET_AVAILABLE command is sent to the InStream and it is verified that a
 *   transition is made to PCKT_AVAIL.
 * - The stub functions are set up to simulate a situation where one more packet has
 *   arrived.
 * - The PACKET_AVAILABLE command is sent again to the InStream and it is verified that
 *   the InStream remains in PCKT_AVAIL and that its packet queue contains two items.
 * - The InStream is shutdown and it is verified that its packet queue and its sequence
 *   counter are reset.
 * .
 * @verify InStream SM Transition: WAITING->PCKT_AVAIL
 * @verify InStream SM Transition: PCKT_AVAIL->PCKT_AVAIL (self-transition)
 * @verify Base SM Transition: CONFIGURED->FPS
 * @verify Packet Collect Procedure: Flag_1 is true; PQ is not full; MW is in state PCKT_AVAIL
 * @verify Packet Collect Procedure: Flag_1 is true; PQ is not full; MW is not in state PCKT_AVAIL
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInStreamTestCase3();

/**
 * Test the error reporting functionalities of an InStream.
 * This test must be executed as a follow-on to <code>::CrFwInStreamTestCase3</code>.
 * The following actions are performed in this test:
 * - The first InStream is obtained from its factory method and it is started and
 *   configured.
 * - It is verified that the first InStream is in state CONFIGURED and WAITING.
 * - The stub functions are set up to simulate a situation where one packet has
 *   arrived and the packet's destination is the host application (i.e. the packet
 *   is not being re-routed).
 * - The PACKET_AVAILABLE command is sent to the InStream and it is verified that a
 *   transition is made to PCKT_AVAIL.
 * - The stub functions are set up to simulate a situation where one more packet for the
 *   host applicaton has arrived and where the sequence counter of the packet is wrong.
 * - The PACKET_AVAILABLE command is sent again to the InStream and it is verified that
 *   the InStream remains in PCKT_AVAIL, that its packet queue contains two items and
 *   that a "sequence counter error" is generated.
 * - The stub functions are set up to simulate a situation where one in transit packet
 *   has arrived and where the sequence counter of the packet is wrong.
 * - The PACKET_AVAILABLE command is sent again to the InStream and it is verified that
 *   the InStream remains in PCKT_AVAIL, that its packet queue contains three items and
 *   that no "sequence counter error" is generated.
 * - The stub functions are set up to simulate a situation where N packets for the host
 *   application have arrived (with N being one greater than the packet queue size)
 *   which have incorrect sequence counters.
 * - The PACKET_AVAILABLE command is sent again to the InStream and it is verified that
 *   the InStream remains in PCKT_AVAIL, that its packet queue is full, and
 *   that a "packet queue full error" is generated.
 * .
 * @verify Error Report: crInStreamPQFull
 * @verify Error Report: crInStreamSCErr
 * @verify Base SM Transition: IPS->CREATED
 * @verify Base SM Transition: CREATED->INITIALIZED
 * @verify Base SM Transition: INITIALIZED->CONFIGURED
 * @verify InStream SM Transition: IPS->WAITING
 * @verify InStream SM Transition: WAITING->PCKT_AVAIL
 * @verify InStream SM Transition: PCKT_AVAIL->PCKT_AVAIL (self-transition)
 * @verify Base SM Transition: CONFIGURED->CONFIGURED
 * @verify Packet Collect Procedure: Flag_1 is false
 * @verify Packet Collect Procedure: PQ is full
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInStreamTestCase4();

/**
 * Test the InStream with checks and actions which may be configured to succeed or fail.
 * The following actions are performed in this test:
 * - Verify that the function to get the source associated to an InStream is correctly
 *   implemented
 * - Verify that initialization of an InStream only succeeds when both the initialization
 *   check and the initialization action succeed.
 * - Verify that configuration of an InStream only succeeds when both the configuration
 *   check and the configuration action succeed.
 * - Verify that a reset of a configured InStream fails if the configuration check fails.
 * .
 * After this test has run, the second InStream component may no longer be usable.
 * @verify Application Error: crNotInStream
 * @verify Base SM Transition: IPS->CREATED
 * @verify Base SM Transition: CREATED->CREATED
 * @verify Base SM Transition: CREATED->INITIALIZED
 * @verify Base SM Transition: INITIALIZED->INITIALIZED
 * @verify Base SM Transition: INITIALIZED->CONFIGURED
 * @verify Base SM Transition: CONFIGURED->INITIALIZED
 * @verify Initialization Procedure: Initialization Action Successful
 * @verify Initialization Procedure: Initialization Check Successful
 * @verify Initialization Procedure: Initialization Action Failed
 * @verify Initialization Procedure: Initialization Check Failed
 * @verify Reset Procedure: Configuration Action Successful
 * @verify Reset Procedure: Configuration Action Failed
 * @verify Reset Procedure: Configuration Check Successful
 * @verify Reset Procedure: Configuration Check Failed
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInStreamTestCase5();

/**
 * Test the function to override the Shutdown Operation of an InStream
 * and to verify entry into PCKT_AVAIL at start-up.
 * The following actions are performed in this test:
 * - The stub functions are set up to simulate a situation where one packet has
 *   arrived.
 * - Bring the second InStream to its CONFIGURED state and check that it
 *   is in state PCKT_AVAIL
 * - Shut down the InStream and check that the Shutdown Operation is executed.
 * .
 * @verify Base SM Transition: IPS->CREATED
 * @verify Base SM Transition: CREATED->INITIALIZED
 * @verify Base SM Transition: INITIALIZED->CONFIGURED
 * @verify Base SM Transition: CONFIGURED->FPS
 * @verify InStream SM Transition: IPS->PCKT_AVAIL
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInStreamTestCase6();

/**
 * Test the management of groups by the InStream.
 * This test assumes that the third InStream has been configured (in <code>CrFwInStreamUserPar.h</code>
 * to have two groups.
 * The following actions are performed in this test:
 * - The third InStream is obtained from its factory method and it is started and
 *   configured.
 * - The stub functions are set up to simulate a situation where three packets belonging
 *   to the first and second group have arrived.
 * - The PACKET_AVAILABLE command is sent to the InStream and it is verified that a
 *   transition is made to PCKT_AVAIL.
 * - The GET_PCKT command is sent three times to the InStream and it is verified that the three packets
 *   are returned, that the InStream remains in PCKT_AVAIL, and that the sequence counters
 *   are correctly incremented.
 * - The stub functions are set up to simulate a situation where three packets have arrived of which
 *   one belongs to a non-existent group.
 * - The PACKET_AVAILABLE command is sent to the InStream and it is verified that a
 *   transition is made to PCKT_AVAIL.
 * - The GET_PCKT command is sent three times to the InStream and it is verified that the three packets
 *   are returned, that the InStream remains in PCKT_AVAIL, that the sequence counters
 *   are correctly incremented, and that an error report is triggered by the packet with the incorrect
 *   group.
 * .
 * @verify InStream SM Transition: WAITING->PCKT_AVAIL
 * @verify InStream SM Transition: PCKT_AVAIL->PCKT_AVAIL (through CPS)
 * @verify InStream SM Transition: PCKT_AVAIL->WAITING
 * @verify Packet Collect Procedure: Flag_1 is true; PQ is not full; MW is in state PCKT_AVAIL
 * @verify Packet Collect Procedure: Flag_1 is true; PQ is not full; MW is not in state PCKT_AVAIL
 * @verify Error Report: crInStreamIllGroup
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInStreamTestCase7();

#endif /* CRFW_INSTREAM_TESTCASES_H_ */
