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

#ifndef CRPS_PCKTGETSET_TESTCASES_H_
#define CRPS_PCKTGETSET_TESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"

/**
 * Test the Getter and Setter for all Packet Headers (Tm and Tc Header)
 *
 * The following actions are performed in this test:
 * - Setting all header fields to 0
 * - Get all header fields and confirm that they are 0
 * - Setting all Header Fields to its maximum value
 * - Get all header fields and confirm that they are set to the maximum value
 * - Set a specific TC Packet
 * - Try all Getters and Setters that may not work because they are for TM Packets
 * - Set a specific TM Packet
 * - Try all Getters and Setters that may not work because they are for TC Packets
 *
 *
 * @verify the functions to get and set values for TmHeader and TcHeader
 * @verify all Getters and Setters work properly 
 * @verify that all Getters return a Value
 * @verify that all Getter and Setter functions are called at least once with all possible if-paths
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsPcktGetSetTestCase1();


/**
 * Test the Getter and Setter for all Packets (Service 17, Service 1, Service 3, Service 5)
 *
 * The following actions are performed in this test:
 * - Create a packet of each packettype for all services
 * - Setting all packet fields to 0
 * - Get all packet fields and confirm that they are 0
 * - Setting all packet Fields to its maximum value
 * - Get all packet fields and confirm that they are set to the maximum value
 *
 * 
 * @verify the functions to get and set values for all Packets
 * @verify that for each packet all Getters and Setters work as they should do
 * @verify that all Getters return a Value
 * @verify that all Getter and Setter functions are called at least once
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsPcktGetSetTestCase2();


#endif /* CRPS_PCKTGETSET_TESTCASES_H_ */
