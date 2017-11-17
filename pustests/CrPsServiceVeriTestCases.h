/**
 * @file
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

#ifndef CRPS_SERVICE_VERI_TESTCASES_H_
#define CRPS_SERVICE_VERI_TESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"

/**
 * Test the Service 1 Request Verification
 *
 * The following actions are performed in this test:
 *
 * - Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines
 * - Initializing OutFactory, InFactory, OutManager and InManager
 * - Check OutFactory, InFactory, OutManager and InManager are configured
 * - Check that the number of allocated Packets is initially 0
 * - Allocate a 17.1 packet
 * - Check that the number of allocated Packets is 1
 * - Check that the number of allocated inCommands is initially 0
 * - make an inCommand out of the packet
 * - Check that the number of allocated InCommands is 1
 * - Check if the inCommand ist correctly generated
 * - Check the inCommand (Type, Service Type and Service Subtype) and that it is in ACCEPTED state
 * - Check that the number of allocated OutComponents is initially 0
 * - Create a (1,1) Report
 * - Check if number of Allocated OutComponents = 1
 * - Check that there is one loaded OutComponent in the OutManager
 * - Get the Data from the out Manager
 * - Check if there is a 1,1 Report waitig in the OutManager (loaded)
 * - Release the OutComponent
 * - Check if number of Allocated OutComponents now is 0
 * - Check that all DataPool Variables concerning (1,2) are initially 0 
 * - Create a (1,2) Report
 * - Check if number of Allocated OutComponents = 1
 * - Check that there are two loaded OutComponents in the OutManager
 * - Check that all DataPool Variables concerning (1,2) are updated 
 * - Get the Data from the out Manager
 * - Check if there is a 1,2 Report waitig in the OutManager (loaded)
 * - Release the OutComponent
 * - Check if number of Allocated OutComponents now is 0
 * - Create a (1,3) Report
 * - Check if number of Allocated OutComponents = 1
 * - Check that there are 3 loaded OutComponents in the OutManager
 * - Get the Data from the out Manager
 * - Check if there is a 1,3 Report waitig in the OutManager (loaded)
 * - Release the OutComponent
 * - Check if number of Allocated OutComponents now is 0
 * - Check that all DataPool Variables concerning (1,4) are initially 0
 * - Create a (1,4) Report
 * - Check if number of Allocated OutComponents = 1
 * - Check that there are 4 loaded OutComponents in the OutManager
 * - Check that all DataPool Variables concerning (1,4) are updated
 * - Get the Data from the out Manager
 * - Check if there is a 1,4 Report waitig in the OutManager (loaded)
 * - Release the OutComponent
 * - Check if number of Allocated OutComponents now is 0
 * - Create a (1,5) Report
 * - Check if number of Allocated OutComponents = 1
 * - Check that there are 5 loaded OutComponents in the OutManager
 * - Get the Data from the out Manager
 * - Check if there is a 1,5 Report waitig in the OutManager (loaded)
 * - Release the OutComponent
 * - Check if number of Allocated OutComponents now is 0
 * - Check that all DataPool Variables concerning (1,6) are initially 0
 * - Create a (1,6) Report
 * - Check if number of Allocated OutComponents = 1
 * - Check that there are 6 loaded OutComponents in the OutManager
 * - Check that all DataPool Variables concerning (1,6) are updated
 * - Get the Data from the out Manager
 * - Check if there is a 1,6 Report waitig in the OutManager (loaded)
 * - Release the OutComponent
 * - Check if number of Allocated OutComponents now is 0
 * - Create a (1,7) Report
 * - Check if number of Allocated OutComponents = 1
 * - Check that there are 7 loaded OutComponents in the OutManager
 * - Get the Data from the out Manager
 * - Check if there is a 1,7 Report waitig in the OutManager (loaded)
 * - Release the OutComponent
 * - Check if number of Allocated OutComponents now is 0
 * - Check that all DataPool Variables concerning (1,8) are initially 0
 * - Create a (1,8) Report
 * - Check if number of Allocated OutComponents = 1
 * - Check that there are 8 loaded OutComponents in the OutManager
 * - Check that all DataPool Variables concerning (1,8) are updated
 * - Get the Data from the out Manager
 * - Check if there is a 1,8 Report waitig in the OutManager (loaded)
 * - Release the OutComponent
 * - Check if number of Allocated OutComponents now is 0
 * - Check that all DataPool Variables concerning (1,10) are initially 0
 * - Create a (1,10) Report
 * - Check if number of Allocated OutComponents = 1
 * - Check that there are 9 loaded OutComponents in the OutManager
 * - Check that all DataPool Variables concerning (1,10) are updated
 * - Get the Data from the out Manager
 * - Check if there is a 1,10 Report waitig in the OutManager (loaded)
 * - Checking OutComponent Desicions of the Guards (1,2 and 1,10)
 * - Extended Check Service (1,2) for an OutComponent (no 1,2 should be created!)
 * - Check if number of loaded OutComponents in the OutManager stays at 9
 * - Extended Check Service (1,10) for an OutComponent (no 1,10 should be created!)
 * - Check if number of loaded OutComponents in the OutManager stays at 9
 * - Release the OutComponent
 * - Check if number of Allocated OutComponents now is 0
 * - Checking REPORT Desicions of the Guards (1,2 and 1,10)
 * - allocate an 17,2 in Report
 * - Check if number of Allocated Packets now is 2
 * - Check if number of Allocated InReports now is 0
 * - Create an InReport from pckt2 (17,2)
 * - Check if number of Allocated InReports now is 1 
 * - Extended Check Service (1,2) for an InReport (no 1,2 should be created!)
 * - Check if number of Allocated OutComponents = 0
 * - Check if number of loaded OutComponents in the OutManager stays at 9
 * - Extended Check Service (1,10) for an InReport (no 1,10 should be created!)
 * - Check if number of Allocated OutComponents = 0
 * - Check if number of loaded OutComponents in the OutManager stays at 9
 * - Fill the outfactory so that an Error could occur (leave no free slot)
 * - Check if no Application Error has occured
 * - Extended Check Service (1,1 - 1.10) no free slots i the OutFactory! Application Error should be 10
 * - Check if Application Error 10 has occured (An OutComponent allocation request has failed)*
 * - Set the Application Error to 0 and check it
 * - Reset OutManager and check that all OutComponents are unloaded and released
 * - Reset InManager and check that all InComponents are unloaded and released
 * - Reset the OutFactory and check that no OutComponents are allocated
 * - Reset the InFactory and check that no InCommands are allocated
 * - Check application errors
 *
 * 
 * @verify initialize all PUS Extension components 
 * @verify creation of OutFactory, InFactory, OutManager and InManager
 * @verify allocating 17.3 packet
 * @verify creating InCommand
 * @verify creating and verifying all Service 1 subservices
 * @verify check that all DataPool Variables concerning the Fail-Reports were correctly updated
 * @verify trying to creat a Service 1.2 and 1.10 Report from an OutComponent
 * @verify trying to creat a Service 1.2 and 1.10 Report from an InReport
 * @verify fill the OutFactory
 * @verify trying to creat and verify all Service 1 subservices with a full outFactory (they will produce application errors)
 * @verify resetting the OutFactory, InFactory, OutManager and InManager
 */
CrFwBool_t CrPsServVeriTestCase1();


#endif /* CRPS_SERVICE_VERI_TESTCASES_H_ */
