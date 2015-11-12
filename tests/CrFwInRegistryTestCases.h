/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the InRegistry Component (see <code>CrFwInRegistry.h</code>).
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

#ifndef CRFW_INREGISTRY_TESTCASES_H_
#define CRFW_INREGISTRY_TESTCASES_H_

/**
 * Test the creation and configuration of the InRegistry singleton component.
 * The following actions are performed in this test:
 * - Create the InRegistry singleton twice and check that the same component is returned
 *   in both cases.
 * - Initialize and configure InRegistry and check that it is in state CONFIGURED.
 * - Check the correctness of the InRegistry component type identifier and instance identifier.
 * .
 * @verify Base SM Transition: IPS->CREATED
 * @verify Base SM Transition: CREATED->INITIALIZED
 * @verify Base SM Transition: INITIALIZED->CONFIGURED
 * @verify Initialization Procedure: Initialization Action Successful
 * @verify Initialization Procedure: Initialization Check Successful
 * @verify Reset Procedure: Configuration Action Successful
 * @verify Reset Procedure: Configuration Check Successful
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInRegistryTestCase1();

/**
 * Test the ability of the InRegistry to track the state of an incoming command or report.
 * The following actions are performed in this test:
 * - Two InReports and one InCommand are created and the InRegistry is asked to track their
 *   state.
 * - It is checked that the incoming components are initially reported by the InRegistry
 *   to be in state PENDING.
 * - The InRegistry is asked to report the state of a non-existent component and
 *   it is checked that the correct value is returned by the InRegistry.
 * - The state of the InReports is updated and it is checked that the new state
 *   is correctly reported by the InRegistry.
 * - The state of the InCommand is updated and it is checked that the new state
 *   is correctly reported by the InRegistry.
 * - One of the InReports is released and then re-created and added again to the
 *   InRegistry a total of (CR_FW_INREGISTRY_N) times; it is checked that the other
 *   InReport and the InCommand are no longer tracked by the InRegistry.
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInRegistryTestCase2();

/**
 * Test the shutdown service of the InRegistry.
 * The following actions are performed in this test:
 * - Three InCommands are created and the InRegistry is asked to track their
 *   state.
 * - The InRegistry is shutdown and it is checked that InRegistry is STOPPED.
 * .
 * @verify Base SM Transition: CONFIGURED->FPS
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInRegistryTestCase3();

/**
 * Test the reset service of the InRegistry.
 * The following actions are performed in this test:
 * - Three OutComponents are created and the InRegistry is asked to track their
 *   state.
 * - Two services are disabled.
 * - The InRegistry is reset and it is checked that the three components are
 *   no longer tracked and that the two services are enabled.
 * .
 * @verify Base SM Transition: CONFIGURED->CONFIGURED
 * @verify Enable State Determination Procedure: Service Type is Enabled
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInRegistryTestCase4();

#endif /* CRFW_INREGISTRY_TESTCASES_H_ */
