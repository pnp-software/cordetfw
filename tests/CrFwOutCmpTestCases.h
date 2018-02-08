/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the OutComponent Component (see <code>CrFwOutCmp.h</code>).
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

#ifndef CRFW_OUTCMP_TESTCASES_H_
#define CRFW_OUTCMP_TESTCASES_H_

#include "CrFwConstants.h"

/**
 * Check the configuration of a newly created OutComponent.
 * The following actions are performed in this test:
 * - The OutFactory is reset and then two OutComponents are retrieved from the OutFactory
 *   and it is checked that their instance identifier and type identifier are correct.
 * - It is checked that the OutComponents are initially in state CONFIGURED.
 * - The configuration check is performed on one of the OutComponents and it is verified that
 *   it is successful
 * - It is checked that the service type and sub-type and the discriminant value of the
 *   OutComponent are correct.
 * - It is checked that the default value of the OutComponent group is correct.
 * - The destination of the OutComponent is set and then read back.
 * - The discriminant of the OutComponent is set and then read back.
 * - The group of the OutComponent is set and then read back.
 * - The time stamp of the OutComponent is set and then read back.
 * - The acknowledge levels are set and then read back.
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutCmpTestCase1();

/**
 * Check the abort function of an OutComponent.
 * The following actions are performed in this test:
 * - The OutFactory is reset and then one Sample1 OutComponent (see <code>CrFwOutCmpSample1.h</code>) is
 *   retrieved from the OutFactory.
 * - The Enable Check of the sample OutComponent is configured to return "not enabled", the ready
 *   check is configured to return "ready", and the repeat check is configured to return "no repeat".
 * - The sample OutComponent is sent the Execute and Terminate commands and it is checked that it
 *   enters state ABORTED.
 * - The sample OutComponent is released and then a new instance of the same sample OutComponent
 *   is retrieved from the OutFactory.
 * - The Enable Check of the sample OutComponent is configured to return "not enabled" and the ready
 *   check is configured to return "not ready".
 * - The sample OutComponent is sent the Execute and Terminate commands and it is checked that it
 *   enters state ABORTED.
 * .
 * @verify OutComponent SM Transition: IPS->LOADED
 * @verify OutComponent SM Transition: LOADED->CPS1
 * @verify OutComponent SM Transition: CPS1->ABORTED
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutCmpTestCase2();

/**
 * Check the execution of a "ready" OutComponent with an invalid destination.
 * The following actions are performed in this test:
 * - The OutFactory is reset and then one Sample1 OutComponent (see <code>CrFwOutCmpSample1.h</code>) is
 *   retrieved from the OutFactory.
 * - The Enable Check of the sample OutComponent is configured to return "enabled", the ready
 *   check is configured to return "ready", and the repeat check is configured to return "no repeat".
 * - The Destination of the sample OutComponent is set to an invalid value (a value to which no
 *   OutStream is associated)
 * - The sample OutComponent is sent the Execute and Terminate commands and it is checked that
 *   it enters state TERMINATED.
 * - It is checked that the error report "invalid OutComponent destination"
 *   (<code>#crOutCmpSendPcktInvDest</code>) is generated.
 * .
 * @verify OutComponent SM Transition: IPS->LOADED
 * @verify OutComponent SM Transition: LOADED->CPS1
 * @verify OutComponent SM Transition: CPS1->PENDING
 * @verify OutComponent SM Transition: PENDING->TERMINATED
 * @verify Send Packet Procedure: OutStreamRegistry returns nothing
 * @verify Error Report: crOutCmpSendPcktInvDest
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutCmpTestCase3();

/**
 * Check the execution of a "ready" OutComponent with a valid destination.
 * The following actions are performed in this test:
 * - The OutFactory is reset and then one Sample1 OutComponent (see <code>CrFwOutCmpSample1.h</code>) is
 *   retrieved from the OutFactory.
 * - The Enable Check of the sample OutComponent is configured to return "enabled", the ready
 *   check is configured to return "ready", and the repeat check is configured to return "no repeat".
 * - The Destination of the sample OutComponent is set to an valid value (a value to which an
 *   OutStream is associated)
 * - The sample OutComponent is sent the Execute and Terminate commands and it is checked that
 *   it enters state TERMINATED and that its time stamp has been correctly set.
 * - It is checked that: (a) no error reports are generated; (b) the number of pending packets
 *   in the OutStream has incremented by one; (c) the Serialize Operation of the OutComponent
 *   has been called and has written the correct data to the packet associated to the OutComponent.
 * .
 * @verify OutComponent SM Transition: IPS->LOADED
 * @verify OutComponent SM Transition: LOADED->CPS1
 * @verify OutComponent SM Transition: CPS1->PENDING
 * @verify OutComponent SM Transition: PENDING->TERMINATED
 * @verify Send Packet Procedure: OutStreamRegistry returns an OutStream
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutCmpTestCase4();

/**
 * Check the execution of a "pending" OutComponent with a valid destination.
 * The following actions are performed in this test:
 * - The OutFactory is reset and then one Sample1 OutComponent (see <code>CrFwOutCmpSample1.h</code>) is
 *   retrieved from the OutFactory.
 * - The Enable Check of the sample OutComponent is configured to return "enabled", the ready
 *   check is configured to return "not ready", and the repeat check is configured to return "no repeat".
 * - The Destination of the sample OutComponent is set to an invalid value (a value to which an
 *   OutStream is associated)
 * - The sample OutComponent is sent the Execute and Terminate commands and it is checked that
 *   it enters state PENDING.
 * - The sample OutComponent is sent the Execute and Terminate commands two more times and it is
 *   checked that it remains in state PENDING.
 * - The ready check is configured to return "ready" and then the sample OutComponent is sent the
 *   Execute and Terminate commands again.
 * - It is checked that the sample OutComponent is in state TERMINATED and that the OutComponent
 *   has been serialized to the OutStream
 * .
 * @verify OutComponent SM Transition: IPS->LOADED
 * @verify OutComponent SM Transition: LOADED->CPS1
 * @verify OutComponent SM Transition: CPS1->PENDING
 * @verify OutComponent SM Transition: PENDING->TERMINATED
 * @verify Send Packet Procedure: OutStreamRegistry returns an OutStream
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutCmpTestCase5();

/**
 * Check the default Enable Check Operation and Ready Check Operation of an OutComponent.
 * The following actions are performed in this test:
 * - The OutFactory is reset and then two OutComponents of different types are retrieved from
 *   the OutFactory (the OutComponents are chosen to use the default implementation of the Enable
 *   Check Operation, see <code>CrFwOutFactoryUserPar.h</code>).
 * - The OutRegistry is configured to disable the first OutComponent and to enable the second
 *   OutComponent.
 * - The second OutComponent is given a valid destination (i.e. a destination for which an OutStream
 *   is defined in <code>CrFwOutStreamUserPar.h</code>).
 * - Both OutComponents are sent the Execute and Terminate commands and it is checked that the
 *   first one enters state ABORTED whereas the second one enters state TERMINATED.
 * - It is checked that the second OutComponent was correctly serialized to the OutStream.
 * .
 * @verify OutComponent SM Transition: IPS->LOADED
 * @verify OutComponent SM Transition: LOADED->CPS1
 * @verify OutComponent SM Transition: CPS1->ABORTED
 * @verify OutComponent SM Transition: CPS1->PENDING
 * @verify OutComponent SM Transition: PENDING->TERMINATED
 * @verify Send Packet Procedure: OutStreamRegistry returns an OutStream
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutCmpTestCase6();

/**
 * Check the execution of a "repeat" OutComponent.
 * The following actions are performed in this test:
 * - The OutFactory is reset and then one Sample1 OutComponent (see <code>CrFwOutCmpSample1.h</code>) is
 *   retrieved from the OutFactory.
 * - The Enable Check of the sample OutComponent is configured to return "enabled", the ready
 *   check is configured to return "ready", and the repeat check is configured to return "repeat".
 * - The sample OutComponent is sent the Execute and Terminate commands and it is checked that
 *   it enters state PENDING.
 * - The sample OutComponent is sent the Execute and Terminate commands again and it is checked that
 *   it is still in state PENDING and that the OutComponent has been updated twice.
 * - The Repeat Check of the sample OutComponent is configured to return "no repeat".
 * - The sample OutComponent is sent the Execute and Terminate commands and it is checked that
 *   it enters state TERMINATED and that the OutComponent has been updated one more time.
 * .
 * @verify OutComponent SM Transition: IPS->LOADED
 * @verify OutComponent SM Transition: LOADED->CPS1
 * @verify OutComponent SM Transition: CPS1->PENDING
 * @verify OutComponent SM Transition: PENDING->TERMINATED
 * @verify Send Packet Procedure: OutStreamRegistry returns an OutStream
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutCmpTestCase7();

/**
 * Check the execution of a "repeat" OutComponent with an invalid destination.
 * The following actions are performed in this test:
 * - The OutFactory is reset and then one Sample1 OutComponent (see <code>CrFwOutCmpSample1.h</code>) is
 *   retrieved from the OutFactory.
 * - The Enable Check of the sample OutComponent is configured to return "enabled", the ready
 *   check is configured to return "ready", and the repeat check is configured to return "repeat".
 * - The destination of the OutComponent is set to an invalid value.
 * - The sample OutComponent is sent the Execute and Terminate commands and it is checked that
 *   it enters state TERMINATED.
 * - The sample OutComponent is reset and then it is re-configured such that its Enable Check returns
 *   "enabled", the ready check returns "not ready", and the repeat check returns "repeat".
 * - The sample OutComponent is sent the Execute and Terminate commands twice and it is checked that
 *   it remains in state PENDING.
 * - The sample OutComponent is reset and then it is re-configured such that its Enable Check returns
 *   "enabled", the ready check returns "ready", and the repeat check returns "repeat".
 * - The sample OutComponent is sent the Execute and Terminate commands twice and it is checked that
 *   it enters state TERMINATED.
 * .
 * @verify OutComponent SM Transition: IPS->LOADED
 * @verify OutComponent SM Transition: LOADED->CPS1
 * @verify OutComponent SM Transition: CPS1->PENDING
 * @verify OutComponent SM Transition: PENDING->TERMINATED
 * @verify Send Packet Procedure: OutStreamRegistry returns nothing
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutCmpTestCase8();

/**
 * Check the transition from state PENDING to state ABORTED.
 * The following actions are performed in this test:
 * - The OutFactory is reset and then one Sample1 OutComponent (see <code>CrFwOutCmpSample1.h</code>) is
 *   retrieved from the OutFactory.
 * - The Enable Check of the sample OutComponent is configured to return "enabled", the ready
 *   check is configured to return "not ready", and the repeat check is configured to return "repeat".
 * - The destination of the OutComponent is set to an valid value.
 * - The sample OutComponent is sent the Execute and Terminate commands and it is checked that
 *   it is in state PENDING.
 * - The Enable Check is configured to return "not enabled", the ready check is configured to return "not ready",
 *   and the repeat check is configured to return "repeat".
 * - The sample OutComponent is sent the Execute and Terminate commands and it is checked that
 *   it is in state ABORTED.
 * - The sample OutComponent is reset and then it is re-configured such that its Enable Check returns
 *   "enabled", the ready check returns "not ready", and the repeat check returns "repeat".
 * - The sample OutComponent is sent the Execute and Terminate commands twice and it is checked that
 *   it remains in state PENDING.
 * - The sample OutComponent is reset and then it is re-configured such that its Enable Check returns
 *   "not enabled", the ready check returns "ready", and the repeat check returns "repeat".
 * - The sample OutComponent is sent the Execute and Terminate commands twice and it is checked that
 *   it enters state ABORTED.
 * .
 * @verify OutComponent SM Transition: IPS->LOADED
 * @verify OutComponent SM Transition: LOADED->CPS1
 * @verify OutComponent SM Transition: CPS1->PENDING
 * @verify OutComponent SM Transition: PENDING->ABORTED
 * @verify Send Packet Procedure: OutStreamRegistry returns valid destination
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutCmpTestCase9();

#endif /* CRFW_OUTCMP_TESTCASES_H_ */
