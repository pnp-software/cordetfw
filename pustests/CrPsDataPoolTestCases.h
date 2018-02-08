/**
 * @file CrPsDataPoolTestCases.h
 * @ingroup PUSTestsuite
 *
 * @brief Declaration of the test cases for the Datapool Component.
 *
 * @author Christian Reimers <christian.reimersy@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 *
 * last modification: 22.01.2018
 * 
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#ifndef CRPS_DATAPOOL_TESTCASES_H_
#define CRPS_DATAPOOL_TESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"

/**
 * Test the generic Datapool Getter an Setter
 *
 * The following actions are performed in this test:
 * - Getting the size of the Datapool, the number of Parameters and Variables
 * - Loop over all Parameters and 
 * - set them to 0, the maximum value and a random number and check
 * - that the get function returns the right value
 * - try to set a wrong entry and look if the function returns wrong values
 *
 * @verify that the generic Setter (setDpValue) can set all Datapool entries correctly
 * @verify that the generic Getter (getDpValue) returns the correct value
 * @verify that either the generic Getter or Getter returns 0 if one uses a wrong ID 
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsDataPoolTestCase1();

/**
 * Test the Service 17 Are-You-Alive Test Connection
 *
 * The following actions are performed in this test:
 * - use the Setter and Getter for the Datapool entry for Service 17
 * - set each Entry to 0 and its maximal value depending on its type
 * - check if the right getter returns the correct value
 *
 * @verify that the initialization function is used to initially set all Service 17 Datapool entries
 * @verify that all Getter and Setter functions for Serive 17 Datapool entries are used
 * @verify that all this Getters and Setters work with the minimum and maximum value of the Datapool entries
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsDataPoolTestCase2();

/**
 * Test the Service 1 Request Verificationl
 *
 * The following actions are performed in this test:
 * - use the Setter and Getter for the Datapool entry for Service 1
 * - set each Entry to 0 and its maximal value depending on its type
 * - check if the right getter returns the correct value
 *
 * @verify that the initialization function is used to initially set all Service 1 Datapool entries
 * @verify that all Getter and Setter functions for Serive 1 Datapool entries are used
 * @verify that all this Getters and Setters work with the minimum and maximum value of the Datapool entries
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsDataPoolTestCase3();

/**
 * Test the Service 3 Housekeeping 
 *
 * The following actions are performed in this test:
 * - use the Setter and Getter for the Datapool entry for Service 3
 * - set each Entry to 0 and its maximal value depending on its type
 * - check if the right getter returns the correct value
 *
 * @verify that the initialization function is used to initially set all Service 3 Datapool entries
 * @verify that all Getter and Setter functions for Serive 3 Datapool entries are used
 * @verify that all this Getters and Setters work with the minimum and maximum value of the Datapool entries
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsDataPoolTestCase4();

/**
 * Test the Service 5 Event reporting 
 *
 * The following actions are performed in this test:
 * - use the Setter and Getter for the Datapool entry for Service 5
 * - set each Entry to 0 and its maximal value depending on its type
 * - check if the right getter returns the correct value
 *
 * @verify that the initialization function is used to initially set all Service 5 Datapool entries
 * @verify that all Getter and Setter functions for Serive 5 Datapool entries are used
 * @verify that all this Getters and Setters work with the minimum and maximum value of the Datapool entries
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsDataPoolTestCase5();

/**
 * Test the Service 13 Large Packet Transfer 
 *
 * The following actions are performed in this test:
 * - use the Setter and Getter for the Datapool entry for Service 13
 * - set each Entry to 0 and its maximal value depending on its type
 * - check if the right getter returns the correct value
 *
 * @verify that the initialization function is used to initially set all Service 13 Datapool entries
 * @verify that all Getter and Setter functions for Serive 5 Datapool entries are used
 * @verify that all this Getters and Setters work with the minimum and maximum value of the Datapool entries
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsDataPoolTestCase6();



#endif /* CRPS_DATAPOOL_TESTCASES_H_ */


