/**
 * @file CrPsEvtTestCases.h
 * @ingroup PUSTestsuite
 *
 * @brief Declaration of the test cases for the Event Reporting Service components.
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

#ifndef CRPS_EVT_TESTCASES_H_
#define CRPS_EVT_TESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"

/**
 * Test the Service 5 EventReporting Service
 *
 * The following actions are performed in this test:
 *
 * - run the getter for EvtCmd5EidStart procedure descriptor
 * - Instantiate all relevant CORDET Framework PUS Extension components
 * - Initializing OutFactory, InFactory and OutManager
 * - Check that OutFactory, InFactory and OutManager are configured
 * - Check that the number of allocated Packets is initially 0
 * - create a 5,1 OutComponent
 * - get the Number of Detected Events from the Datapool
 * - run the Enable Check and check if the value in the datapool changes
 * - get the Number of Generated Events from the Datapool
 * - Run the Update Action and check that the outcome == success and the value in the datapool has changed
 * - release the OutComponent
 * - create a 5,2 OutComponent
 * - get the Number of Detected Events from the Datapool
 * - run the Enable Check and check if the value in the datapool changes
 * - get the Number of Generated Events from the Datapool
 * - Run the Update Action and check that the outcome == success and the value in the datapool has changed
 * - release the OutComponent
 * - create a 5,3 OutComponent
 * - get the Number of Detected Events from the Datapool
 * - run the Enable Check and check if the value in the datapool changes
 * - get the Number of Generated Events from the Datapool
 * - Run the Update Action and check that the outcome == success and the value in the datapool has changed
 * - release the OutComponent
 * - create a 5,4 OutComponent
 * - get the Number of Detected Events from the Datapool
 * - run the Enable Check and check if the value in the datapool changes
 * - get the Number of Generated Events from the Datapool
 * - Run the Update Action and check that the outcome == success and the value in the datapool has changed
 * - release the OutComponent
 * - create a 5,8 OutComponent with a wrong EID to trigger fullcoverage of the code
 * - run the Enable Check
 * - run the Update Action
 * - release the OutComponent
 * - set Datapool value of disabled EID's manually
 * - allocate a 5,5 packet and create an InCommand to enable EID's
 * - run the Start Action and check outcome == success
 * - run the Progress Action and check outcome == success
 * - run the Termination Action and check outcome == success
 * - check if the number of disabled EID's has changed accordingly
 * - allocate a 5,5 packet and create an InCommand to enable all EID's but the EID's are not valid
 * - run the Start Action and check if the outcome is set to VER_EID_START_FD
 * - release the InCommand and check if ther is on 1,4 packet waiting in the OutManager
 * - release the OutComponent and reset the OutManager
 * - allocate a 5,6 packet and create an InCommand to disable EID's
 * - run the Start Action and check outcome == success
 * - run the Progress Action and check outcome == success
 * - run the Termination Action and check outcome == success
 * - check if the number of disabled EID's has changed accordingly
 * - allocate a 5,7 packet and create an InCommand to generate a 5,8 report
 * - run the Start Action and check outcome == success
 * - run the Progress Action and check outcome == success
 * - run the Termination Action and check outcome == success
 * - check the OutManager if there is a 5,8 is waiting
 * - release the OutComponent and reset the OutManager
 * - allocate a 5,7 packet and create an InCommand to generate a 5,8 report
 * - fill the OutFactory and run the Start Action and check outcome == 0
 * - reset the application error and release the OutComponents and the InCommand
 * - allocate a 5,7 packet with a content of an 5,5 and create an InCommand
 * - run the start Action of the Event Enable Command to trigger an Error
 * - check if the outcome is set to VER_EID_START_FD
 * - release the InCommand
 * - create a 5,8 OutComponent
 * - run the Update Action and check outcome == success
 * - release the OutComponent
 * - reset the OutManager, OutFactory and InFactory and check for application errors
 *  
 * 
 * @verify initialize all PUS Extension components and Applications
 * @verify creation of OutFactory, InFactory and OutManager
 * @verify creation of a 5,1 to 5,4 Outcomponent
 * @verify check if the Enable Check and Update Action changes the datapool value and has outcome set to success
 * @verify start a 5,5 Event Enable Command and check that the values in the datapool change accordingly
 * @verify start a 5,5 Event Enable Command with invalid EventId's and check for the outcome = VER_EID_START_FD
 * @verify start a 5,6 Event Disable Command and check that the values in the datapool change accordingly
 * @verify allocating a 5,7 packet and run the start, progress and termination Action 
 * @verify and check if there is a 5,8 generated
 * @verify allocating a 5,7 packet fill the OutFactory and run the start Action to trigger an outcome = 0
 * @verify allocating a 5,7 packet with wrong content to trigger an error VER_EID_START_FD
 * @verify create a 5,8 Outcomponent run the Update Action and check outcome == success
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsEvtTestCase1();

#endif /* CRPS_EVT_TESTCASES_H_ */
