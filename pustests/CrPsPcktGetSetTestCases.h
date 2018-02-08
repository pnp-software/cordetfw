/**
 * @file CrPsGetSetTestCases.h
 * @ingroup PUSTestsuite
 *
 * @brief Declaration of the test cases for all Getter and Setter components.
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

#ifndef CRPS_PCKTGETSET_TESTCASES_H_
#define CRPS_PCKTGETSET_TESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
/* TODO hier header file gscheit beschreiben !!*/
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

/* TODO either include this into testcase 2 or make a testcase for every service*/
CrFwBool_t CrPsPcktGetSetTestCase3();

/* TODO either include this into testcase 2 or make a testcase for every service*/
CrFwBool_t CrPsPcktGetSetTestCase4();


#endif /* CRPS_PCKTGETSET_TESTCASES_H_ */
