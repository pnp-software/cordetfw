/**
 * @file CrPsServiceTestCases.h
 * @ingroup PUSTestsuite
 *
 * @brief Declaration of the test cases for the Test Service Components.
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

#ifndef CRPS_SERVICE_TESTCASES_H_
#define CRPS_SERVICE_TESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"

/**
 * Test the Service 17 Are-You-Alive Test Connection
 *
 * The following actions are performed in this test:
 *
 * - run all getters for the procedure descriptors
 * - Initializing OutFactory, InFactory and OutManager
 * - Check that OutFactory, InFactory and OutManager are configured
 * - Check that the number of allocated Packets is initially 0
 * - Allocate a 17,1 packet 
 * - Check that the number of allocated Packets now is 1
 * - Check that the number of allocated inCommands is initially 0
 * - make an inCommand out of the packet
 * - Check that the number of allocated InCommands is 1
 * - Check if the inCommand ist correctly generated
 * - Check the inCommand (Type, ServicevType and Service Subtype) and that it is in ACCEPTED state
 * - Check that the number of allocated OutComponents is initially 0
 * - Execute the inCommand
 * - Check that the inCommand enters PROGRESS state
 * - Check that there are now 2 Packets allocated
 * - Check that the number of outComponents is 1
 * - Check if there is a 17,2 generated in the OutManager
 * - Abort the InCommand manually
 * - Terminate the inCommand manually
 * - Check that the InCommand is in the state Terminated
 * - Release InCommand 
 * - Check if there is only 1 allocated packet left 
 * - Check if there is no InCommand in the InFactory
 * - Execute the outComponent (17,2)
 * - release the outComponent and Check number of allocated Packets and OutComponents
 * - Allocate a 17,1 packet 
 * - make an inCommand out of the packet
 * - Check that the number of allocated InCommands is 1
 * - Fill the outfactory so that an Error could occur
 * - Execute the inCommand
 * - Check application errors -> CrOutCmpAllocationFail
 * - reset the application error code
 * - release all OutComponents and the InCommand
 * - Reset the outManager, outFactory and in Factory and check again if an application error occures
 *  
 * 
 * @verify creation of OutFactory, InFactory and OutManager
 * @verify allocating 17,1 packet
 * @verify creating InCommand
 * @verify executing the InCommand
 * @verify service 17 will create a 17,2 Report
 * @verify executing the 17,2 Report
 * @verify creating 17,1 InCommand
 * @verify executing the InCommand while the OutFactory is full -> trigger an crOutCmpAllocationFail error
 * @verify releasing all allocated packets
 * @verify resetting the OutFactory, InFactory and OutManager
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsServTestConnTestCase1();

/**
 * Test the Service 17 On-Board Connection Test
 *
 * The following actions are performed in this test:
 *
 * - Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines
 * - Initialize Applications
 * - Initializing OutFactory, InFactory, OutManager and InManager
 * - Check OutFactory, InFactory, OutManager and InManager are configured
 * - Check that the number of allocated Packets is initially 0
 * - Allocate a 17,3 packet with a non valid application ID
 * - Check that the number of allocated Packets is 1
 * - Check that the number of allocated inCommands is initially 0
 * - make an inCommand out of the packet
 * - Check that the number of allocated InCommands is 1
 * - Check if the inCommand ist correctly generated
 * - Check the inCommand (Type, Service Type and Service Subtype) and that it is in ACCEPTED state
 * - Check that the number of allocated OutComponents is initially 0
 * - Execute the inCommand
 * - Check that the inCommand is in the state ABORTED
 * - Release the inCommand
 * - Check if number of Allocated Packets now is 1 - a Request Verification (1,4) should be in the Outmanager
 * - Check that there is one Packet Pending in the OutManager - Request Verification (1,4)
 * - Check if number of loaded OutComponents in the OutManager is 1 - Request Verification (1,4)
 * - Get the Data from the out Manager (there is only one Component)
 * - Check if there is a 1,4 Command waitig in the OutManager (loaded)
 * - Release the OutComponent
 * - Check that no packets are allocated
 * - Allocate a 17,3 packet now with a valid application ID
 * - Check that the number of allocated Packets is 1
 * - make an inCommand out of the packet
 * - Check that the number of allocated InCommands is 1
 * - Check if the inCommand ist correctly generated
 * - Check the inCommand (Type, Service Type and Service Subtype) and that it is in ACCEPTED state
 * - Check that the number of allocated OutComponents is initially 0
 * - Execute the inCommand - 2 new packets should be allocated (a 17,1 in the OutManager) and a 17,4 
 * - Check if number of Allocated Packets now is 3
 * - Check if number of Allocated InCommands in the InFactory stays at 1
 * - Check if number of loaded OutComponents in the OutManager is 1 
 * - Get the Data from the out Manager
 * - Check if there is a 17,1 Command waitig in the OutManager (loaded)
 * - Check that there is one Packet Pending in the OutManager
 * - allocate a 17,2 Packet
 * - Check if number of Allocated Packets now is 4 
 * - Check that there are no InReports in the InFactory
 * - Create an InReport (17,2) out of the allocated packet
 * - Check if number of Allocated InReports in the InFactory now is 1
 * - Check that there are no Packets Pending or Loaded in the InManager
 * - Load the InReport into the InManager
 * - Check is now one Pending (inCmd)(17,3) and one Loaded (inRep)(17,2) Packets in the InManager
 * - Execute the InManager
 * - Check that there is now no Pending but one Loaded (inCmd)(17,3) Packets in the InManager
 * - Check that there is one Pending and one Loaded Packet in the OutManager
 * - Execute the InCommand 
 * - Check that there are now two Pending and two Loaded Packets in the OutManager
 * - Terminate the InCommand
 * - Get the Information from the OutManager (there are two Component!)
 * - Check if there is a 17,1 Command waitig in the OutManager (loaded)
 * - Execute the OutComponent (17,1)
 * - Check if Repeatcheck always returns 0
 * - Check if there is a 17,4 Command waitig in the OutManager (loaded)
 * - Execute the OutComponent (17,4)
 * - Check if Repeatcheck always returns 0
 * - Call the Abort Action (There is nothing to check, because this Action does nothing!)
 * - Check that there are 3 allocated packets
 * - Release the (17,3) InCommand
 * - Check that there are 2 allocated packets
 * - Check that there are no Allocated InCommands in the InFactory
 * - Release the (17,2) InReport
 * - Check that now there are only 2 allocated packets
 * - Release the (17,1) Outcomponent
 * - Check that now there is only 1 allocated packet
 * - Release the (17,4) OutComponent
 * - Check that there are no allocated packets
 * - Check application errors
 * - Reset OutManager and check that all OutComponents are unloaded and released
 * - Reset InManager and check that all InComponents are unloaded and released
 * - Reset the OutFactory and check that no OutComponents are allocated
 * - Reset the InFactory and check that no InCommands are allocated
 * - Check application errors
 *
 * 
 * @verify initialize all PUS Extension components and Applications
 * @verify creation of OutFactory, InFactory, OutManager and InManager
 * @verify allocating 17,3 packet
 * @verify creating InCommand
 * @verify executing the InCommand (one with wrong appId and one with correct appId)
 * @verify check that a 17,1 will be generated
 * @verify allocate and execute a 17,2 report
 * @verify check that a 17,4 will be generated
 * @verify execute the 17,4
 * @verify releasing all allocated packets
 * @verify resetting the OutFactory, InFactory, OutManager and InManager
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsServTestConnTestCase2();

/**
 * Test the Service 17 exceptional cases
 *
 * The following actions are performed in this test:
 *
 * - Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines
 * - Initialize Applications
 * - Initializing OutFactory, InFactory, OutManager and InManager
 * - Check OutFactory, InFactory, OutManager and InManager are configured
 * - Check that the number of allocated Packets is initially 0
 * - Allocate a 17,3 packet 
 * - make an inCommand out of the packet
 * - Check that the number of allocated InCommands is 1
 * - Check that the number of allocated Packets is 1
 * - Check if the inCommand ist correctly generated
 * - Check the inCommand (Type, Service Type and Service Subtype) and that it is in ACCEPTED state
 * - Fill the outfactory so that an Error could occur (leave one free slot)
 * - Execute the InCommand - the outfactory is full (except of one free slot) so the error should occur when the second packet will be allocated
 * - Check if there is a 1,4 Command waitig in the OutManager
 * - Release all outcomponents, that have been created to fill the outfactory 
 * - Release the original inCmd
 * - Check if number of Allocated Packets now is 0
 * - Allocating a new 17.3 Packet
 * - make an inCommand out of the packet
 * - Fill the outfactory so that an Error could occur
 * - Execute the InCommand - If the OutFactory is full it should fail, there is also no place for a 1,4 to be generated
 * - Release all outcomponents, that have been created to fill the outfactory 
 * - Release the original inCmd
 * - Check if number of Allocated Packets now is 0
 * - Allocating a new 17.3 Packet
 * - make an inCommand out of the packet
 * - Execute the InCommand 
 * - Check if number of Allocated Packets now is 3
 * - Check if number of Allocated InCommands in the InFactory stays at 1 
 * - Trigger a Timeout by executing the incommand as often as the value in the datapool specifies
 * - for coverage call - the Termination Action and the CrPsTestOnBoardConnectionStartN3 procedure
 * - Set the Timeout Variable in the Datapool to 100 to trigger an error 
 * - for coverage and to trigger the error call - CrPsTestOnBoardConnectionPrgrG13 
 * - for coverage call - CrPsTestOnBoardConnectionStartN10 and execute  prDescServTestOnBoardConnStart 
 * - Release the original inCmd
 * - Reset OutManager and check that all OutComponents are unloaded and released
 * - Reset InManager and check that all InComponents are unloaded and released
 * - Reset the OutFactory and check that no OutComponents are allocated
 * - Reset the InFactory and check that no InCommands are allocated
 * - Check application errors
 * 
 * 
 * @verify initialize all PUS Extension components and Applications
 * @verify creation of OutFactory, InFactory, OutManager and InManager
 * @verify allocating 17.3 packet
 * @verify creating InCommand
 * @verify executing the InCommand (with a full OutFactory so we can check errors)
 * @verify execute the InCommand so often that a timeout occurs
 * @verify releasing all allocated packets
 * @verify resetting the OutFactory, InFactory, OutManager and InManager
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsServTestConnTestCase3();

#endif /* CRPS_SERVICE_TESTCASES_H_ */
