/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the OutManager Component (see <code>CrFwOutManager.h</code>).
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

#ifndef CRFW_OUTMANAGER_TESTCASES_H_
#define CRFW_OUTMANAGER_TESTCASES_H_

#include "CrFwConstants.h"

/**
 * Check the configuration of a newly created OutManager.
 * The following actions are performed in this test:
 * - The first OutManager is created and it is checked that it is in state CREATED.
 * - The OutManager is initialized and reset and it is checked that in state CONFIGURED.
 * - The instance identifier and the type identifier of the OutManager is checked.
 * - It is checked that the POCL is empty and has the expected size.
 * - It is checked that the counter of loaded OutComponents is equal to zero.
 * - An attempt is made to create an OutManager with an illegal identifier and it is
 *   verified that this results in the application error code being set.
 * .
 * @verify Base Component SM Transition: IPS->CREATED
 * @verify Base Component SM Transition: CREATED->INITIALIZED
 * @verify Base Component SM Transition: INITIALIZED->CONFIGURED
 * @verify Application Error: crOutManagerIllId
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutManagerTestCase1();

/**
 * Check the load function of an OutManager.
 * The following actions are performed in this test:
 * - The second OutManager is created, initialized and configured.
 * - The OutFactory is created, initialized and configured.
 * - The instance identifier of the OutManager is checked.
 * - OutComponents are loaded into the OutManager and it is checked that the number of loaded
 *   OutComponents is correctly reported.
 * - When the number of loaded OutComponents exceeds the size of the OutManager's POCL, it is checked
 *   that the correct error report is generated.
 * - The OutManager is reset and it is checked that the POCL is cleared.
 * .
 * @verify Base Component SM Transition: CONFIGURED->CONFIGURED
 * @verify OutManager Load Procedure: POCL is full
 * @verify OutManager Load Procedure: POCL is not full
 * @verify Error Report: crOutManagerPcrlFull
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutManagerTestCase2();

/**
 * Check the execution function of an OutManager with one single OutComponent loaded.
 * The following actions are performed in this test:
 * - An OutManager is created, initialized and configured.
 * - The OutRegistry is created, initialized and configured.
 * - The OutFactory is created, initialized and configured.
 * - The empty OutManager is executed twice.
 * - One instance of the Sample 1 OutComponent is created and it is loaded in the OutManager.
 * - The Sample OutComponent is configured not to be enabled.
 * - The OutManager is repeatedly executed and it is checked that the execution is
 *   propagated to the OutComponent.
 * - The Sample OutComponent is configured to be ready but not enabled.
 * - The OutManager is executed and it is checked that the OutComponent is
 *   unloaded and that the OutRegistry correctly tracks its change of state.
 * .
 * @verify OutManager Execution Procedure: i is smaller or equal to number of items in POCL
 * @verify OutManager Execution Procedure: i is greater than the number of items in POCL
 * @verify OutManager Execution Procedure: outCmp is in state PENDING
 * @verify OutManager Execution Procedure: outCmp is not in state PENDING
 * @verify OutManager Load Procedure: POCL is not full
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutManagerTestCase3();

/**
 * Check the execution function of an OutManager with several OutComponents loaded.
 * The following actions are performed in this test:
 * - An OutManager is created, initialized and configured.
 * - The OutRegistry is created, initialized and configured.
 * - The OutFactory is created, initialized and configured.
 * - The first OutStream is created, initialized and configured.
 * - Two instances of Sample 1 OutComponents and two instances of "standard" OutComponents
 *   with default enable and ready checks are created.
 * - The destination of all OutComponent instances is set to be the same as the destination
 *   of the first OutStream (this is important when the OutComponents enter state TERMINATED
 *   and need a valid destination).
 * - The Sample OutComponents are configured to be enabled not to be ready.
 * - The OutManager is repeatedly executed and it is checked that the execution is
 *   propagated to the OutComponents.
 * - The Sample OutComponent is configured to be ready but not enabled.
 * - The OutManager is executed and it is checked that the standard OutComponents are
 *   unloaded while the Sample OutComponents remain pending.
 * - It is checked that the OutRegistry correctly tracks the change of state in the
 *   OutComponents.
 * - The OutManager is shutdown and it is checked that all pending OutComponents are
 *   released.
 * - The OutManager is restarted and brought to its CONFIGURED state.
 * - It is checked that the counter of loaded OutComponents is correctly updated.
 * .
 * @verify OutManager Execution Procedure: i is smaller or equal to number of items in POCL
 * @verify OutManager Execution Procedure: i is greater than the number of items in POCL
 * @verify OutManager Execution Procedure: outCmp is in state PENDING
 * @verify OutManager Execution Procedure: outCmp is not in state PENDING
 * @verify OutManager Load Procedure: POCL is not full
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutManagerTestCase4();



#endif /* CRFW_OUTMANAGER_TESTCASES_H_ */
