/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the OutStream Component (see <code>CrFwOutStream.h</code>).
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

#ifndef CRFW_OUTSTREAM_TESTCASES_H_
#define CRFW_OUTSTREAM_TESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmCore.h"

/**
 * Test the initialization and packet queue (PQ) management of the OutStream.
 * The following actions are performed in this test:
 * - Attempt to instantiate an OutStream with an illegal identifier and check that the operation
 *   fails.
 * - Instantiate one OutStream twice and check that the same instance is returned on both
 *   occasions.
 * - Check that the OutStream is correctly configured.
 * - Initialize and configure the OutStream and bring its state machine to state CONFIGURED-READY
 * - Check that the OutStream sequence counters and PQ size are correct
 * - Configure the Packet Hand-Over Operation to return "hand-over failed", send a packet
 *   to the OutStream and check that the PQ state is correctly updated and that the
 *   OutStream goes to state BUFFERING.
 * - Send the same packet multiple times until the PQ is full and check that its state
 *   is as expected.
 * - Send one more packet and check that an error report is generated.
 * In all cases, the packet is configured to belong to the first group associated
 * to the OutStream.
 * .
 * @verify Error Report: crOutStreamPQFull
 * @verify Application Error: crOutStreamIllId
 * @verify Base SM Transition: IPS->CREATED
 * @verify Base SM Transition: CREATED->INITIALIZED
 * @verify Base SM Transition: INITIALIZED->CONFIGURED
 * @verify Base SM Transition: CONFIGURED->FPS
 * @verify OutStream SM Transition: IPS->READY
 * @verify OutStream SM Transition: READY->BUFFERING
 * @verify OutStream SM Transition: BUFFERING->BUFFERING
 * @verify OutStream SM Transition: Enqueue Action with PQ Not Full
 * @verify OutStream SM Transition: Enqueue Action with PQ Full
 * @verify Initialization Procedure: Initialization Action Successful
 * @verify Initialization Procedure: Initialization Check Successful
 * @verify Reset Procedure: Configuration Action Successful
 * @verify Reset Procedure: Configuration Check Successful
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutStreamTestCase1();

/**
 * Test the OutStream with overridden initialization check and initialization action.
 * The following actions are performed in this test:
 * - Verify that initialization of OutStream only succeeds when both the initialization
 *   check and the initialization action succeed.
 * - Verify that configuration of OutStream only succeeds when both the configuration
 *   check and the configuration action succeed.
 * - Verify that a reset of a configured OutStream fails if the configuration check fails.
 * .
 * After this test has run, the second OutStream component may no longer be usable.
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
CrFwBool_t CrFwOutStreamTestCase2();

/**
 * Test the packet flushing functionality of an OutStream for a packet originating from the
 * host application (as opposed to a re-routed packet).
 * The following actions are performed in this test:
 * - The first OutStream is started and the Packet Hand-Over Operation
 *   is configured to return "hand-over successful".
 * - It is checked that the destination assigned to the OutStream is correctly
 *   reported by the OutStream
 * - A packet is sent to the OutStream and it is checked that it is successfully
 *   flushed.
 * - The Packet Hand-Over Operation is configured to return "hand-over failed",
 *   two packets are sent to the OutStream, and it is checked that they are
 *   buffered.
 * - The packet factory is configured to be empty and then a packet is sent to the
 *   OutStream and it is checked that error <code>::crOutStreamNoMorePckt</code> is raised.
 * - The ConnectionAvailable signal is sent to the OutStream and it is checked that
 *   the packet queue remains unchanged.
 * - The Packet Hand-Over Operation is configured to return "hand-over successful",
 *   the ConnectionAvailable signal is sent again to the OutStream and it is
 *   checked that the packet queue is successfully flushed.
 * - The Packet Hand-Over Operation is configured to return "hand-over failed",
 *   the packet factory is configured to be empty, and then a packet is sent to the
 *   OutStream and it is checked that error <code>::crOutStreamNoMorePckt</code> is raised.
 * - The OutStream is reset and it is checked that its state is correctly reset
 * In all cases, the packets sent to an OutStream are configured to belong to the
 * first group associated to the OutStream.
 * .
 * @verify Base SM Transition: IPS->CREATED
 * @verify Base SM Transition: CREATED->INITIALIZED
 * @verify Base SM Transition: INITIALIZED->CONFIGURED
 * @verify Base SM Transition: CONFIGURED->CONFIGURED
 * @verify OutStream SM Transition: IPS->READY
 * @verify OutStream SM Transition: READY->BUFFERING
 * @verify OutStream SM Transition: BUFFERING->READY
 * @verify OutStream SM Transition: Enqueue Action with No More Packets Available
 * @verify OutStream SM Transition: Enqueue Action with PQ Not Full
 * @verify OutStream SM Transition: Flush Packet Queue Action with Middleware Accepting Packet
 * @verify OutStream SM Transition: Flush Packet Queue Action with Middleware Rejecting Packet
 * @verify OutStream SM Transition: Flush Packet Queue Action with Packet Originating in Application
 * @verify OutStream SM Transition: Flush Packet Queue Action with Legal Packet Group
 * @verify OutStream SM Transition: Send or Enqueue Action with No More Packets Available
 * @verify OutStream SM Transition: Send or Enqueue Action with Middleware Accepting Packet
 * @verify OutStream SM Transition: Send or Enqueue Action with Middleware Rejecting Packet
 * @verify OutStream SM Transition: Send or Enqueue Action with Packet Originating in Application
 * @verify OutStream SM Transition: Send or Enqueue Action with Legal Packet Group
 * @verify OutStream SM Transition: Flush Packet Queue Action with Illegal Group Report
 * @verify OutStream SM Transition: Send or Enqueue Action with Illegal Group Report
 * @verify Initialization Procedure: Initialization Action Successful
 * @verify Initialization Procedure: Initialization Check Successful
 * @verify Reset Procedure: Configuration Action Successful
 * @verify Reset Procedure: Configuration Check Successful
 * @verify Application Error: crOutStreamUndefDest
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutStreamTestCase3();

/**
 * Test the registry functionality of an OutStream.
 * The following actions are performed in this test:
 * - The OutStreams are made by their factory function and associated to their
 *   destinations.
 * - The same OutStreams are retrieved from their destinations.
 * - An attempt is made to retrieve an OutStream from an illegal destination.
 * .
 * @verify Application Error: crOutStreamUndefDest
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutStreamTestCase4();

/**
 * Test the Shutdown Operation of an OutStream.
 * The following actions are performed in this test:
 * - Bring an OutStream to its CONFIGURED state
 * - Shut down the OutStream and check that the new Shutdown Operation is executed.
 * .
 * @verify Base SM Transition: IPS->CREATED
 * @verify Base SM Transition: CREATED->INITIALIZED
 * @verify Base SM Transition: INITIALIZED->CONFIGURED
 * @verify Base SM Transition: CONFIGURED->FPS
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutStreamTestCase5();

/**
 * Test the packet flushing functionality of an OutStream for a re-routed packet
 * (as opposed to a packet originating from the host application).
 * The following actions are performed in this test:
 * - The first OutStream is started and the Packet Hand-Over Operation
 *   is configured to return "hand-over successful".
 * - A packet is sent to the OutStream and it is checked that it is successfully
 *   flushed and that its sequence counter is not modified.
 * - The Packet Hand-Over Operation is configured to return "hand-over failed",
 *   two packets are sent to the OutStream, and it is checked that they are
 *   buffered.
 * - The ConnectionAvailable signal is sent to the OutStream and it is checked that
 *   the packet queue is successfully flushed.
 * - The OutStream is reset and it is checked that its state is correctly reset
 * .
 * @verify Base SM Transition: IPS->CREATED
 * @verify Base SM Transition: CREATED->INITIALIZED
 * @verify Base SM Transition: INITIALIZED->CONFIGURED
 * @verify Base SM Transition: CONFIGURED->CONFIGURED
 * @verify OutStream SM Transition: IPS->READY
 * @verify OutStream SM Transition: READY->BUFFERING
 * @verify OutStream SM Transition: BUFFERING->READY
 * @verify OutStream SM Transition: Enqueue Action with PQ Not Full
 * @verify OutStream SM Transition: Flush Packet Queue Action with Middleware Accepting Packet
 * @verify OutStream SM Transition: Flush Packet Queue Action with Middleware Rejecting Packet
 * @verify OutStream SM Transition: Flush Packet Queue Action with Packet not Originating in Application
 * @verify OutStream SM Transition: Send or Enqueue Action with Packet not Originating in Application
 * @verify Initialization Procedure: Initialization Action Successful
 * @verify Initialization Procedure: Initialization Check Successful
 * @verify Reset Procedure: Configuration Action Successful
 * @verify Reset Procedure: Configuration Check Successful
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutStreamTestCase6();

/**
 * Test the management of the sequence counters for different groups.
 * The following actions are performed in this test:
 * - The second OutStream (which must be configured to have more than one destination/source
 *   group) is started and its Packet Hand-Over Operation is configured to return "hand-over successful".
 * - It is checked that the number of groups assigned to the OutStream is
 *   greater than 1
 * - Two packets belonging to, respectively, the first and second groups are sent to the
 *   OutStream and it is checked that they are successfully flushed and that their sequence counter
 *   is successfully incremented.
 * - Two more packets belonging to, respectively, the first and second groups are sent to the
 *   OutStream and it is checked that they are successfully flushed and that their sequence counter
 *   is successfully incremented.
 * - A packet belonging to a non-existent group is sent to the OutStream and it is checked
 *   that it is successfully flushed but that an error report is raised.
 * - The Packet Hand-Over Operation is configured to return "hand-over failed",
 *   three packets belonging to, respectively, the first, second and a non-existent group are
 *   sent to the OutStream, and it is checked that they are buffered.
 * - The ConnectionAvailable signal is sent to the OutStream and it is checked that
 *   the packet queue remains unchanged.
 * - The Packet Hand-Over Operation is configured to return "hand-over successful",
 *   the ConnectionAvailable signal is sent again to the OutStream and it is
 *   checked that the packet queue is successfully flushed and that one error report for the
 *   illegal group is created.
 * - The OutStream is reset and it is checked that its state is correctly reset
 * .
 * @verify Base SM Transition: IPS->CREATED
 * @verify Base SM Transition: CREATED->INITIALIZED
 * @verify Base SM Transition: INITIALIZED->CONFIGURED
 * @verify Base SM Transition: CONFIGURED->CONFIGURED
 * @verify OutStream SM Transition: IPS->READY
 * @verify OutStream SM Transition: READY->BUFFERING
 * @verify OutStream SM Transition: BUFFERING->READY
 * @verify OutStream SM Transition: Flush Packet Queue Action with Illegal Group Report
 * @verify OutStream SM Transition: Send or Enqueue Action with Illegal Group Report
 * @verify Initialization Procedure: Initialization Action Successful
 * @verify Initialization Procedure: Initialization Check Successful
 * @verify Reset Procedure: Configuration Action Successful
 * @verify Reset Procedure: Configuration Check Successful
 * @verify Error Report: crOutStreamIllGroup
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutStreamTestCase7();

#endif /* CRFW_OUTSTREAM_TESTCASES_H_ */
