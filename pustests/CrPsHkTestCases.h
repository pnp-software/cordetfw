/**
 * @file CrPsServiceTestCases.h
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the Service Components
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

#ifndef CRPS_HK_TESTCASES_H_
#define CRPS_HK_TESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"

/**
 * Test the Service 3 Housekeeping Service
 *
 * The following actions are performed in this test:
 *
 * - Initializing OutFactory, InFactory and OutManager
 * - Check that OutFactory, InFactory and OutManager are configured
 * - Check that the number of allocated Packets is initially 0
 * - Allocate a TBD
 *  
 * 
 * @verify TBD
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsHkTestCase1();

/**
 * Test the Service 3 Housekeeping Service
 *
 * The following actions are performed in this test:
 *
 * - TBD
 *
 * 
 * @verify TBD
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsHkTestCase2();

/**
 * Test the Service 3 Housekeeping service
 *
 * The following actions are performed in this test:
 *
 * - TBD
 * - 
 * - 
 * @verify TBD
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsHkTestCase3();

#endif /* CRPS_HK_TESTCASES_H_ */
