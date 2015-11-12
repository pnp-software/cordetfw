/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the OutRegistry Component (see <code>CrFwOutRegistry.h</code>).
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

#ifndef CRFW_OUTREGISTRY_TESTCASES_H_
#define CRFW_OUTREGISTRY_TESTCASES_H_

/**
 * Test the creation and configuration of the OutRegistry singleton component.
 * The following actions are performed in this test:
 * - Create the OutRegistry singleton twice and check that the same component is returned
 *   in both cases.
 * - Initialize and configure OutRegistry and check that it is in state CONFIGURED.
 * - Check the correctness of the OutRegistry component type identifier and instance identifier.
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
CrFwBool_t CrFwOutRegistryTestCase1();

/**
 * Test the functions to manipulate the type, sub-type and index of an out-going command
 * or report.
 * The following actions are performed in this test:
 * - Get the type and sub-type corresponding to a set of index values
 * - Get the index value corresponding to several sets of [type, sub-type] pairs.
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutRegistryTestCase2();

/**
 * Test the functions to set and read the enable status of an OutComponent without a
 * discriminant.
 * The following actions are performed in this test:
 * - An OutComponent is created and it is checked that it is initially enabled
 * - The Service Type of the created component is disabled and then it is checked
 *   that the OutComponent is disabled.
 * - The Service Type of the created component is enabled and its Service Subtype
 *   is disabled, and then it is checked that the OutComponent is disabled.
 * .
 * @verify Enable State Determination Procedure: Service Type is Disabled
 * @verify Enable State Determination Procedure: Service Type is Enabled
 * @verify Enable State Determination Procedure: Service Sub-Type is Disabled
 * @verify Enable State Determination Procedure: Service Sub-Type is Enabled
 * @verify Enable State Determination Procedure: Out-Going Cmd/Rep has no Discriminant
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutRegistryTestCase3();

/**
 * Test the functions to set and read the enable status of an OutComponent with a
 * discriminant.
 * The following actions are performed in this test:
 * - An OutComponent is created and it is checked that it is initially enabled
 * - The Service Type of the created component is disabled and then it is checked
 *   that the OutComponent is disabled.
 * - The Service Type of the created component is enabled and its Service Subtype
 *   is disabled, and then it is checked that the OutComponent is disabled.
 * - The Service Type and Subtype of the created component are enabled, its
 *   discriminant is disabled, and then i is checked that the OutComponent is
 *   disabled.
 * .
 * @verify Enable State Determination Procedure: Service Type is Disabled
 * @verify Enable State Determination Procedure: Service Type is Enabled
 * @verify Enable State Determination Procedure: Service Sub-Type is Disabled
 * @verify Enable State Determination Procedure: Service Sub-Type is Enabled
 * @verify Enable State Determination Procedure: Out-Going Cmd/Rep has Discriminant
 * @verify Enable State Determination Procedure: Discriminant is Disabled
 * @verify Enable State Determination Procedure: Discriminant is Enabled
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutRegistryTestCase4();

/**
 * Test the non-interference of the setting of the enable status for two different
 * discriminant values.
 * The following actions are performed in this test:
 * - Two OutComponents are created with the same type and sub-type but with different
 *   discriminants.
 * - The two discriminant values are enabled and disabled individually and it is
 *   checked that the enable state of the two OutComponents is correctly reported.
 * .
 * @verify Enable State Determination Procedure: Service Type is Enabled
 * @verify Enable State Determination Procedure: Service Sub-Type is Enabled
 * @verify Enable State Determination Procedure: Out-Going Cmd/Rep has Discriminant
 * @verify Enable State Determination Procedure: Discriminant is Disabled
 * @verify Enable State Determination Procedure: Discriminant is Enabled
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutRegistryTestCase5();

/**
 * Test the response of the OutRegistry to an attempt to disable a non-existent kind
 * of OutComponent.
 * The following actions are performed in this test:
 * - An attempt is made to disable a non-existent service type and it is checked
 *   the application error code is set.
 * - An attempt is made to disable a non-existent service sub-type and it is checked
 *   the application error code is set.
 * - An attempt is made to disable a non-existent discriminant and it is checked
 *   the application error code is set.
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutRegistryTestCase6();

/**
 * Test the ability of the OutRegistry to track the state of an OutComponent.
 * The following actions are performed in this test:
 * - Three OutComponents are created and the OutRegistry is asked to track their
 *   state.
 * - It is checked that the OutComponent are initially reported by the OutRegistry
 *   to be in state PENDING.
 * - The OutRegistry is asked to report the state of a non-existent OutComponent and
 *   it is checked that the correct value is returned by the OutRegistry.
 * - The state of the OutComponent is updated and it is checked that the new state
 *   is correctly reported by the OutRegistry.
 * - One of the OutComponents is released and then re-created and added again to the
 *   OutRegistry a total of (CR_FW_OUTREGISTRY_N) times; it is checked that the other
 *   two OutComponents are no longer tracked by the OutRegistry.
 * .
 * @verify Registry Start Tracking Procedure: Branch "Registry is Not Full"
 * @verify Registry Start Tracking Procedure: Branch "Registry is Full"
 * @verify Registry Update Procedure: Branch "Component is being tracked in Registry"
 * @verify Registry Update Procedure: Branch "Component is not being tracked in Registry"
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutRegistryTestCase7();

/**
 * Test the shutdown service of the OutRegistry.
 * The following actions are performed in this test:
 * - Three OutComponents are created and the OutRegistry is asked to track their
 *   state.
 * - Two services are disabled.
 * - The OutRegistry is shutdown and it is checked that OutRegistry is STOPPED.
 * .
 * @verify Base SM Transition: CONFIGURED->FPS
 * @verify Enable State Determination Procedure: Service Type is Enabled
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutRegistryTestCase8();

/**
 * Test the reset service of the OutRegistry.
 * The following actions are performed in this test:
 * - Three OutComponents are created and the OutRegistry is asked to track their
 *   state.
 * - Two services are disabled.
 * - The OutRegistry is reset and it is checked that the three components are
 *   no longer tracked and that the two services are enabled.
 * .
 * @verify Base SM Transition: CONFIGURED->CONFIGURED
 * @verify Enable State Determination Procedure: Service Type is Enabled
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutRegistryTestCase9();

#endif /* CRFW_OUTREGISTRY_TESTCASES_H_ */
