/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the DataPool Components
 *
 * @author Christian Reimers <christian.reimersy@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * @copyright Department of Astrophysics, University of Vienna, 2017, All Rights Reserved
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



#endif /* CRPS_DATAPOOL_TESTCASES_H_ */


