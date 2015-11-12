/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the Base Component (see <code>CrFwBaseCmp.h</code>).
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

#ifndef CRFW_BASECMP_TESTCASES_H_
#define CRFW_BASECMP_TESTCASES_H_

/**
 * Test the transitions in the Base Component state machine and its
 * Initialization and Reset Procedures.
 * The test performs the following actions:
 * - Instantiate the Base Component and check that initially it is in state STOPPED
 * - Instantiate the Initialization and Reset Procedures and check that initially they
 *   are in state STOPPED
 * - Configure the Base Component instance with the Initialization and Reset Procedure
 *   instances and with the Dummy Execution Procedure
 * - Check that the Base Component and its procedures are correctly initialized
 * - Start the Base Component SM then send it command INIT. This verifies the transition
 *   from CREATED to INITIALIZED.
 * - Send command RESET to the Base Component. This verifies the transition from
 *   INITIALIZED to CONFIGURED.
 * - Send command SHUTDOWN to the Base Component. This verifies the transition from
 *   CONFIGURED to Final Pseudo-State.
 * .
 * @verify Base SM Transition: IPS->CREATED
 * @verify Base SM Transition: CREATED->INITIALIZED
 * @verify Base SM Transition: INITIALIZED->CONFIGURED
 * @verify Base SM Transition: CONFIGURED->FPS
 * @verify Initialization Procedure: Initialization Action Successful
 * @verify Initialization Procedure: Initialization Check Successful
 * @verify Reset Procedure: Configuration Action Successful
 * @verify Reset Procedure: Configuration Check Successful
 *
 * @image html BaseSM.png
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwBaseCmpTestCase1();

#endif /* CRFW_BASECMP_TESTCASES_H_ */
