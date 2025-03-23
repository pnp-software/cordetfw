/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the InFactory Component (see <code>CrFwInFactory.h</code>).
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

#ifndef CRFW_INFACTORY_TESTCASES_H_
#define CRFW_INFACTORY_TESTCASES_H_

#include "CrFwConstants.h"

/**
 * Test the creation and configuration of the InFactory singleton component.
 * The following actions are performed in this test:
 * - Create the InFactory singleton twice and check that the same component is returned
 *   in both cases.
 * - Initialize and configure InFactory and check that it is in state CONFIGURED.
 * - Check the correctness of the InFactory component type identifier and instance identifier.
 * - Check that the number of allocated InCommands is initially equal to zero
 * - Check that the maximum number of InCommands which can be allocated is correct
 * - Check that the number of allocated InReports is initially equal to zero
 * - Check that the maximum number of InReports which can be allocated is correct
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
CrFwBool_t CrFwInFactoryTestCase1();

/**
 * Test the InCommand creation service in non-nominal situations where the
 * creation fails.
 * The following actions are performed in this test:
 * - Attempt to retrieve an InCommand of an undefined service type (i.e. a service type
 *   which is not defined in <code>CrFwInFactoryUserPar.h</code>).
 * - Attempt to retrieve an InCommand of an undefined service sub-type (i.e. a service sub-type
 *   which is not defined in <code>CrFwInFactoryUserPar.h</code>).
 * - Attempt to retrieve an InCommand of an undefined discriminant (i.e. a discriminant
 *   which is not defined in <code>CrFwInFactoryUserPar.h</code>).
 * - Attempt to retrieve an InCommand with an illegal length
 * - Create <code>#CR_FW_INFACTORY_MAX_NOF_INCMD</code> InCommands and then
 *   attempt to create one more InCommand (this should fail because at most
 *   <code>#CR_FW_INFACTORY_MAX_NOF_INCMD</code> InCommands can be created.
 * .
 * @verify Application Error: crIllInCmdKind
 * @verify Application Error: crInCmdAllocationFail
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInFactoryTestCase2();

/**
 * Test the InCommand part of the Reset and Shutdown functions of the InFactory component.
 * The following actions are performed in this test:
 * - Reset the InFactory and then allocate three InCommands.
 * - Check the correct allocation of the instance identifiers of the InCommands.
 * - Reset the InFactory and check that no InCommands are any longer allocated.
 * - Allocate three InCommands from the InFactory and check that the number of allocated
 *   InCommands is three.
 * - Shutdown the InFactory and check that no InCommands are any longer allocated.
 * - Check the state of the InFactory and then re-start it.
 * .
 * @verify Base SM Transition: CONFIGURED->FPS
 * @verify Base SM Transition: CONFIGURED->CONFIGURED
 * @verify Reset Procedure: Configuration Action Successful
 * @verify Reset Procedure: Configuration Check Successful
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInFactoryTestCase3();

/**
 * Test the InCommand part of the Release function of the InFactory component.
 * The following actions are performed in this test:
 * - Allocate an InCommand and then release it and check that the number of allocated
 *   InCommands is correctly updated.
 * - Attempt to release an InCommand twice and check that an application error is raised
 *   and that the number of allocated InCommands remains unchanged.
 * .
 * @verify Application Error: crInCmdRelErr
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInFactoryTestCase4();

/**
 * Test the InReport creation service in non-nominal situations where the
 * creation fails.
 * The following actions are performed in this test:
 * - Attempt to retrieve an InReport of an undefined service type (i.e. a service type
 *   which is not defined in <code>CrFwInFactoryUserPar.h</code>).
 * - Attempt to retrieve an InReport of an undefined service sub-type (i.e. a service sub-type
 *   which is not defined in <code>CrFwInFactoryUserPar.h</code>).
 * - Attempt to retrieve an InReport of an undefined discriminant (i.e. a discriminant
 *   which is not defined in <code>CrFwInFactoryUserPar.h</code>).
 * - Attempt to retrieve an InReport with an illegal length (i.e. a length
 *   which is not defined in <code>CrFwInFactoryUserPar.h</code>).
 * - Create <code>#CR_FW_INFACTORY_MAX_NOF_INREP</code> InReports and then
 *   attempt to create one more InReport (this should fail because at most
 *   <code>#CR_FW_INFACTORY_MAX_NOF_INREP</code> InReports can be created.
 * .
 * @verify Application Error: crIllInRepKind
 * @verify Application Error: crInRepAllocationFail
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInFactoryTestCase5();

/**
 * Test the InReport part of the Reset and Shutdown functions of the InFactory component.
 * The following actions are performed in this test:
 * - Reset the InFactory and then allocate three InReports.
 * - Reset the InFactory and check that no InReports are any longer allocated.
 * - Allocate three InReports from the InFactory and check that the number of allocated
 *   InReports is equal to 3.
 * - Shutdown the InFactory and check that no InReports are any longer allocated.
 * - Check the state of the InFactory and then re-start it.
 * .
 * @verify Base SM Transition: CONFIGURED->FPS
 * @verify Base SM Transition: CONFIGURED->CONFIGURED
 * @verify Reset Procedure: Configuration Action Successful
 * @verify Reset Procedure: Configuration Check Successful
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInFactoryTestCase6();

/**
 * Test the InReport part of the Release function of the InFactory component.
 * The following actions are performed in this test:
 * - Allocate an InReport and then release it and check that the number of allocated
 *   InReports is correctly updated.
 * - Attempt to release an InReport twice and check that an application error is raised
 *   and that the number of allocated InReports remains unchanged.
 * .
 * @verify Application Error: crInRepRelErr
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInFactoryTestCase7();

#endif /* CRFW_INFACTORY_TESTCASES_H_ */
