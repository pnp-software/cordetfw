/**
 * @file CrPsLptTestCases.h
 * @ingroup PUSTestsuite
 *
 * @brief Declaration of the test cases for the Large Packet Transfer Service components.
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

#ifndef CRPS_LPT_TESTCASES_H_
#define CRPS_LPT_TESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"

/**
 * Check Service 13 (all standard functions to return outcome = 1)
 *
 * The following actions are performed in this test:
 *
 * - Instantiate all relevant CORDET Framework PUS Extension components
 * - Initializing OutFactory, InFactory and OutManager
 * - Check that OutFactory, InFactory and OutManager are configured
 * - Check that the number of allocated Packets is initially 0
 * - create a 13,1 Outcomponent
 * - run the Enable Check and Update Action and check for outcome 1
 * - release the 13,1 Outcomponent
 * - create a 13,2 Outcomponent
 * - run the Enable Check, Repeat Check and Update Action and check for outcome 1
 * - release the 13,2 Outcomponent
 * - create a 13,3 Outcomponent
 * - run the Enable Check and Update Action and check for outcome 1
 * - release the 13,3 Outcomponent
 * - Allocate a 13,9 packet and create an InCmd
 * - run the Start Action, the Progress Action and the Termination Action and check for outcome 1
 * - release the 13,9 Incommand
 * - Allocate a 13,10 packet and create an InCmd
 * - run the Start Action, the Progress Action and the Termination Action and check for outcome 1
 * - release the 13,10 Incommand
 * - Allocate a 13,11 packet and create an InCmd
 * - run the Start Action, the Progress Action and the Termination Action and check for outcome 1
 * - release the 13,11 Incommand
 * - create a 13,16 Outcomponent
 * - run the Update Action and check for outcome 1
 * - release the 13,16 Outcomponent
 * - Allocate a 13,129 packet and create an InCmd
 * - run the Start Action, the Progress Action and the Termination Action and check for outcome 1
 * - release the 13,129 Incommand
 * - Allocate a 13,130 packet and create an InCmd
 * - run the Start Action, the Progress Action and the Termination Action and check for outcome 1
 * - release the 13,130 Incommand
 * - check for application errors
 * - reset the OutManager, OutFactory and inFactory and check again for application errors 
 *
 * 
 * @verify initialize all PUS Extension components and Applications
 * @verify creation of OutFactory, InFactory and OutManager
 * @verify check all standard functions of the 13,1 Component
 * @verify check all standard functions of the 13,2 Component
 * @verify check all standard functions of the 13,3 Component
 * @verify check all standard functions of the 13,9 Component
 * @verify check all standard functions of the 13,10 Component
 * @verify check all standard functions of the 13,11 Component
 * @verify check all standard functions of the 13,16 Component
 * @verify check all standard functions of the 13,129 Component
 * @verify check all standard functions of the 13,130 Component
 * @verify Reset the OutManager, OutFactory and InFactory and check for application errors
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsLptTestCase1();

/**
 * Test the Service 13 EventReporting Service Up-Transfer
 *
 * The following actions are performed in this test:
 *
 * - Create and fill a memory Array with random Numbers for the Up-Transfer
 * - Instantiate all relevant CORDET Framework PUS Extension components
 * - Initializing OutFactory, InFactory and OutManager
 * - Check that OutFactory, InFactory and OutManager are configured
 * - Check that the number of allocated Packets is initially 0
 * - Allocate a 13,9 Packet, create an inCmd and fill in the Data
 * - run the start action, the progress action and the termination action
 * - Execute the Statemachine and release the inCmd
 * - Allocate a 13,10 Packet, create an inCmd and fill in the Data
 * - run the start action, the progress action and the termination action
 * - Execute the Statemachine and release the inCmd
 * - Loop over the 13,10 Packet until there is only data left for one packet
 * - Allocate a 13,11 Packet, create an inCmd and fill in the Data
 * - run the start action, the progress action and the termination action
 * - Execute the Statemachine and release the inCmd
 * - get the Data from the Buffer and check if the Data is stored correctly
 * - reset the OutManager, OutFactory and inFactory and check for application errors 
 *  
 * 
 * @verify initialize all PUS Extension components and Applications
 * @verify creation of OutFactory, InFactory and OutManager
 * @verify Create a 13,9 Packet and check that all actions have outcome 0
 * @verify Create several 13,10 Packet and check that all actions have outcome 0
 * @verify Create a 13,11 Packet and check that all actions have outcome 0
 * @verify get the Data from the Buffer and check if the data was sent and stored correctly to the buffer
 * @verify that no application error occures
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsLptTestCase2();

/**
 * Test the Service 13 EventReporting Service Down-Transfer
 *
 * The following actions are performed in this test:
 *
 * - Create and fill a memory Array with random Numbers for the Up-Transfer
 * - Instantiate all relevant CORDET Framework PUS Extension components
 * - Initializing OutFactory, InFactory and OutManager
 * - Check that OutFactory, InFactory and OutManager are configured
 * - Check that the number of allocated Packets is initially 0
 * - Allocate a 13,129 Packet, create an inCmd 
 * - Fill the outfactory so that an error could occur
 * - Execute the inCmd and the Statemachine
 * - Check if an OutComponent allocation error occures
 * - reset the application error code
 * - Release all outcomponents, that have been created to fill the outfactory
 * - Execute the inCmd and the Statemachine again to successfully create an 13,1
 * - Release the inCommand, geht the data from the out Manaager and check if a 13,1 is waiting
 * - again fill the outfactory and execut the 13,1 to trigger an error
 * - Execute the OutCmp and the Statemachine
 * - Check if an OutComponent allocation error is created
 * - then reset the application error code and some values in the datapool
 * - now again execute the OutComponent and the Statemachine to successfully create a 13,2 OutComponent
 * - gather the Data from Packet 13,1 and 13,2 then repeat until all 
 * - then repeat executing the OutComponent and Statemachine until all Data is received
 * - Test the memory and check if the data that was sent in the test 1 is the same that is received now
 * - Allocate a 13,130 Packet and create an InCmd
 * - run the start action, the progress action and the termination action
 * - release the InCmd
 * - Allocate a 13,129 Packet and create an InCmd
 * - execute the InCmd and the Statemachine
 * - release the InCmd
 * - check if a 13,1 is waiting in the Outmanager
 * - execute the OutCmp and the Statemachine
 * - check if a 13,2 is waiting in the Outmanager
 * - execute the OutCmp and the Statemachine twice so that all data is received except for one last packet
 * - fill the Outfactory to trigger an error
 * - execute the OutCmp and the Statemachine
 * - Check if an OutComponent allocation error occures
 * - reset the application error and release the OutComponents
 * - again check for application errors
 * - reset the OutManager, OutFactory and inFactory and check for application errors 
 *
 * 
 * @verify initialize all PUS Extension components and Applications
 * @verify creation of OutFactory, InFactory and OutManager
 * @verify Create a 13,129 Packet and execute it
 * @verify Check that a application error is created when the OutFactory has no free slot
 * @verify execute the 13,129 again and check if a 13,1 is created
 * @verify fill the OutFactory again and check if an error occures when executing the 13,1 OutComponent
 * @verify execute it again and check if an 13,2 is created
 * @verify after all packets are triggered check if the content is correct
 * @verify Allocate a 13,130 Packet and create an InCmd 
 * @verify run the start action, the progress action and the termination action
 * @verify release the InCmd
 * @verify again execute an 13,129 inCmd to trigger an error when a 13,3 should be created
 * @verify check that the OutComponent allocation error is created and reset the error code
 * @verify Reset the OutManager, OutFactory and InFactory and check for application errors
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsLptTestCase3();



/**
 * Test the Service 13 EventReporting Service other stuff
 *
 * The following actions are performed in this test:
 *
 * - Create and fill a memory Array with random Numbers for the Up-Transfer
 * - Instantiate all relevant CORDET Framework PUS Extension components
 * - Initializing OutFactory, InFactory and OutManager
 * - Check that OutFactory, InFactory and OutManager are configured
 * - Check that the number of allocated Packets is initially 0
 

 * - Fill the outfactory so that an error could occur
 * - Execute the inCmd and the Statemachine
 * - Check if an OutComponent allocation error occures
 * - reset the application error code
 * - Release all outcomponents, that have been created to fill the outfactory
 * - reset the application error and release the OutComponents
 * - again check for application errors
 * - reset the OutManager, OutFactory and inFactory and check for application errors 
 *
 * 
 * @verify initialize all PUS Extension components and Applications
 * @verify creation of OutFactory, InFactory and OutManager

 * @verify Check that a application error is created when the OutFactory has no free slot

 * @verify Reset the OutManager, OutFactory and InFactory and check for application errors
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsLptTestCase4();


#endif /* CRPS_LPT_TESTCASES_H_ */
