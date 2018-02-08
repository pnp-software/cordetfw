/**
 * @file CrPsHkTestCases.h
 * @ingroup PUSTestsuite
 *
 * @brief Declaration of the test cases for the Housekeeping Service components.
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

#ifndef CRPS_HK_TESTCASES_H_
#define CRPS_HK_TESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"

/**
 * Test the Service 3 Housekeeping Service Part 1
 *    Test all the 3,1 and 3,2 actions and procedures
 *
 * The following actions are performed in this test:
 *
 * - run all getters for the procedure descriptors
 * - Instantiate all relevant CORDET Framework PUS Extension components
 * - manually delete all the SID's from the DataPool
 * - Initializing OutFactory, InFactory and OutManager
 * - Check that OutFactory, InFactory and OutManager are configured
 * - Check that the number of allocated Packets is initially 0
 * - Allocate a 3,1 Packet with correct packet content (SID = 3), create an InCmd
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Run the Start Action and check that the outcome == success
 * - Check the OutManager (3,25 should be waiting), then release the OutCmp and reset the OutManager
 * - Run the Progress Action and check that the outcome == success
 * - Run the Termination Action and check that the outcome == success and release the InCmd
 * - Check if the SID is now in the Datapool
 * - Allocate a 3,1 Packet with correct packet content but (SID = 0),  create an InCmd 
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Run the Start Action and check that the outcome == VER_RDL_CONSTR -> SID Not valid!
 * - release the inCmd and check for errors
 * - manually delete the SID from the DataPool
 * - Allocate a 3,2 Packet with correct packet content (SID = 3), create an InCmd
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Run the Start Action and check that the outcome == success
 * - Check the OutManager (3,26 should be waiting), then release the OutCmp and reset the OutManager
 * - Run the Progress Action and check that the outcome == success
 * - Run the Termination Action and check that the outcome == success and release the InCmd
 * - Check if the SID is now in the Datapool
 * - Allocate the a 3,1 Packet (SID = 3) to trigger an Error! (SID in USE)
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Run the Start Action and check that the outcome == VER_SID_IN_USE -> SID is already in the Datapool!
 * - release the inCmd and check for errors
 * - manually set all sid's in the Datapool
 * - Allocate the a 3,1 Packet (SID = 3) to trigger an Error! ( all RDL-Slots are in use )
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Run the Start Action and check that the outcome == VER_FULL_RDL -> there are already HK_N_REP_DEF sid's in the Datapool!
 * - release the inCmd and check for errors
 * - Allocate a 3,1 Packet to trigger an Error! (Error in the Construction) min. one constraint from table 9.1 is not satisfied
 * - the N1 value in the packet is bigger than HK_N_REP_DEF
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Run the Start Action and check that the outcome == VER_RDL_CONSTR -> the content of the packet is not valid!
 * - release the inCmd and check for errors
 * - Allocate a 3,1 Packet to trigger an Error! The same data item identifier appears twice
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Run the Start Action and check that the outcome == VER_DUPL_DI -> there is a parameter ID duplicated within the packet!
 * - release the inCmd and check for errors
 * - manually delete all the SID's from the DataPool
 * - Allocate a 3,1 Packet to trigger an Error! (OutFactory full)
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Fill the outfactory so that an Error could occur (leave only one free slot)
 * - Run the Start Action and check that the outcome == VER_REP_CR_FD -> OutFactory full!
 * - release all outComponents and release the inCmd and check for errors
 * - Allocate a 3,1 Packet to trigger an Error! VER_OUTLOADER_FD
 * - TODO: NOT IMPLEMENTED YET
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Run the Start Action and check that the outcome == VER_OUTLOADER_FD
 * - release the inCmd and check for errors
 * - TODO: NOT IMPLEMENTED YET
 *
 *
 * @verify initialize all PUS Extension components and Applications
 * @verify creation of OutFactory, InFactory and OutManager
 * @verify allocating a 3,1 packet and run the start, progress and termination actions 
 * @verify check that the outcome is set to success and that a 3,25 packet is generated and the SID is in the Datapool
 * @verify allocating a 3,1 packet but with a wrong SID. run the start action
 * @verify check that the outcome is set to VER_RDL_CONSTR (no valid sid)
 * @verify allocating a 3,2 packet and run the start, progress and termination actions 
 * @verify check that the outcome is set to success and that a 3,26 packet is generated and the SID is in the Datapool
 * @verify allocating a 3,1 packet but with the same SID as the previous packet and run the start action
 * @verify check that the outcome is set to VER_SID_IN_USE
 * @verify allocating a 3,1 packet and fill the RDL then run the start action
 * @verify check that the outcome is set to VER_FULL_RDL
 * @verify allocating a 3,1 packet but set one parameter in the packet to a wrong value then run the start action
 * @verify check that the outcome is set to VER_RDL_CONSTR
 * @verify allocating a 3,1 packet but set one parameter twice to the same value then run the start action
 * @verify check that the outcome is set to VER_DUPL_DI
 * @verify allocating a 3,1 packet and fill the outFactory with outComponents then run the start action
 * @verify check that the outcome is set to VER_REP_CR_FD
 * @verify allocating a 3,1 packet TODO trigger Outloader Error TODO then run the start action
 * @verify check that the outcome is set to TODO
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsHkTestCase1();

/**
 * Test the Service 3 Housekeeping Service
 *    Test all the 3,3 3,4 3,5 3,6 3,7 and 3,8 actions and procedures
 *
 * The following actions are performed in this test:
 *
 * - Instantiate all relevant CORDET Framework PUS Extension components
 * - manually delete all the SID's from the DataPool
 * - Initializing OutFactory, InFactory and OutManager
 * - Check that OutFactory, InFactory and OutManager are configured
 * - Check that the number of allocated Packets is initially 0
 * - manually set a SID in the Datapool
 * - Allocate a 3,3 Packet with correct packet content, create an InCmd
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Run the Start Action and check that the outcome == success
 * - Run the Progress Action and check that the outcome == success
 * - Run the Termination Action and check that the outcome == success
 * - check if the SID is now gone in the Datapool and release the InCmd
 * - manually set a SID in the Datapool
 * - Allocate a 3,4 Packet with correct packet content, create an InCmd
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Run the Start Action and check that the outcome == success
 * - Run the Progress Action and check that the outcome == success
 * - Run the Termination Action and check that the outcome == success
 * - check if the SID is now gone in the Datapool and release the InCmd
 * - Allocate a 3,3 Packet with correct packet content, create an InCmd
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Run the Start Action and check that the outcome == VER_S3S_START_FD
 * - release the InCmd and check if there is a 1,4 with a discriminant (VER_ILL_SID) is waiting in the OutManager
 * - release the OutComponent and reset the OutManager then check for application errors
 * - manually set a SID in the Datapool and enable the sid
 * - Allocate a 3,3 Packet with correct packet content, create an InCmd
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Run the Start Action and check that the outcome == VER_S3S_START_FD
 * - release the InCmd and check if there is a 1,4 with a discriminant (VER_ENABLED_SID) is waiting in the OutManager
 * - release the OutComponent and reset the OutManager then check for application errors
 * - manually set a SID in the Datapool and disable it
 * - Allocate a 3,5 Packet with correct packet content, create an InCmd
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Run the Start Action and check that the outcome == success
 * - Run the Progress Action and check that the outcome == success
 * - Run the Termination Action and check that the outcome == success
 * - check if the SID is now enabled in the Datapool and release the InCmd
 * - manually set a SID in the Datapool and disable it
 * - Allocate a 3,7 Packet with correct packet content, create an InCmd
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Run the Start Action and check that the outcome == success
 * - Run the Progress Action and check that the outcome == success
 * - Run the Termination Action and check that the outcome == success
 * - check if the SID is now enabled in the Datapool and release the InCmd
 * - manually delete a SID in the Datapool
 * - Allocate a 3,5 Packet with a wrong SID, create an InCmd
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Run the Start Action and check that the outcome == VER_SID_START_FD
 * - release the InCmd and check if there is a 1,4 with a discriminant (VER_ILL_SID) is waiting in the OutManager
 * - release the OutComponent and reset the OutManager then check for application errors
 * - manually set a SID in the Datapool and enable the SID
 * - Allocate a 3,6 Packet with correct packet content, create an InCmd
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Run the Start Action and check that the outcome == success
 * - Run the Progress Action and check that the outcome == success
 * - Run the Termination Action and check that the outcome == success
 * - check if the SID is now disabled in the Datapool and release the InCmd
 * - manually set a SID in the Datapool and enable the SID
 * - Allocate a 3,8 Packet with correct packet content, create an InCmd
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Run the Start Action and check that the outcome == success
 * - Run the Progress Action and check that the outcome == success
 * - Run the Termination Action and check that the outcome == success
 * - check if the SID is now disabled in the Datapool and release the InCmd
 * - manually delete a SID in the Datapool
 * - Allocate a 3,6 Packet with a wrong SID, create an InCmd
 * - Check if an InCmd is created and it is of correct type, Servtype and ServSubType.
 * - Run the Start Action and check that the outcome == VER_SID_START_FD
 * - release the InCmd and check if there is a 1,4 with a discriminant (VER_ILL_SID) is waiting in the OutManager
 * - release the OutComponent and reset the OutManager then check for application errors
 *
 *
 * @verify initialize all PUS Extension components and Applications
 * @verify creation of OutFactory, InFactory and OutManager
 * @verify allocating a 3,3 packet and run the start, progress and termination actions
 * @verify check that the outcome is set to success and that the SID that was set is now gone in the Datapool
 * @verify allocating a 3,4 packet and run the start, progress and termination actions
 * @verify check that the outcome is set to success and that the SID that was set is now gone in the Datapool
 * @verify allocating a 3,3 packet and run the start action (there is now no SID in the Datapool)
 * @verify check that the outcome is set to VER_S3S_START_FD and a 1,4 packet with discriminant VER_ILL_SID is created
 * @verify allocating a 3,3 packet and run the start action (there is now a SID in the Datapool but it is enabled)
 * @verify check that the outcome is set to VER_S3S_START_FD and a 1,4 packet with discriminant VER_ENABLED_SID is created
 * @verify allocating a 3,5 packet and run the start, progress and termination actions
 * @verify check that the outcome is set to success and that the SID that was disabled is now enabled in the Datapool
 * @verify allocating a 3,7 packet and run the start, progress and termination actions
 * @verify check that the outcome is set to success and that the SID that was disabled is now enabled in the Datapool
 * @verify allocating a 3,5 packet with a wrong SID and run the start action
 * @verify check that the outcome is set to VER_SID_START_FD and a 1,4 packet with discriminant VER_ILL_SID is created
 * @verify allocating a 3,6 packet and run the start, progress and termination actions
 * @verify check that the outcome is set to success and that the SID that was enabled is now disabled in the Datapool
 * @verify allocating a 3,8 packet and run the start, progress and termination actions
 * @verify check that the outcome is set to success and that the SID that was enabled is now disabled in the Datapool
 * @verify allocating a 3,6 packet with a wrong SID and run the start action
 * @verify check that the outcome is set to VER_SID_START_FD and a 1,4 packet with discriminant VER_ILL_SID is created
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsHkTestCase2();

/**
 * Test the Service 3 Housekeeping service
 *    Test all the 3,9 3,11 3,27 and 3,28 actions and procedures
 *
 * The following actions are performed in this test:
 *
 * - Instantiate all relevant CORDET Framework PUS Extension components
 * - manually delete all the SID's from the DataPool
 * - Initializing OutFactory, InFactory and OutManager
 * - Check that OutFactory, InFactory and OutManager are configured
 * - Check that the number of allocated Packets is initially 0
 * - manually set a SID and create a RDL in the Datapool
 * - Allocate a 3,9 Packet with correct packet content, create an InCmd
 * - Run the Start Action and check that the outcome == success
 * - Run the Progress Action and check that the outcome == 2
 * - Run the Termination Action and check that the outcome == 2
 * - Run the Progress Action and check that the outcome == success
 * - Run the Termination Action and check that the outcome == success
 * - release the InCmd and check that no InCmd's are allocated
 * - Check the OutManager (a 3,10 should be waiting), then release the OutCmp and reset the OutManager
 * - Allocate a 3,11 Packet with correct packet content, create an InCmd
 * - Run the Start Action and check that the outcome == success
 * - Run the Progress Action and check that the outcome == 2
 * - Run the Termination Action and check that the outcome == 2
 * - Run the Progress Action and check that the outcome == success
 * - Run the Termination Action and check that the outcome == success
 * - release the InCmd and check that no InCmd's are allocated
 * - Check the OutManager (a 3,12 should be waiting), then release the OutCmp and reset the OutManager
 * - Allocate a 3,9 Packet with correct packet content, create an InCmd
 * - manually fill the OutFactory to trigger an Error
 * - Run the Start Action and check that the outcome == success
 * - Run the Progress Action and check that the outcome == success
 * - check if the application error is set to crOutCmpAllocationFail
 * - Run the Termination Action and check that the outcome == success
 * - release the InCmd and check that no InCmd's are allocated
 * - release the OutComponents from the OutFactory
 * - Allocate a 3,27 Packet with correct packet content, create an InCmd
 * - Run the Termination Action early and check that the outcome == 0
 * - Run the Start Action and check that the outcome == success
 * - Run the Progress Action and check that the outcome == success
 * - Run the Termination Action and check that the outcome == success
 * - release the InCmd and check that no InCmd's are allocated
 * - Allocate a 3,28 Packet with correct packet content, create an InCmd
 * - Run the Start Action and check that the outcome == success
 * - Run the Progress Action and check that the outcome == success
 * - Run the Termination Action and check that the outcome == success
 * - release the InCmd and check that no InCmd's are allocated
 * - Allocate a 3,1 Packet but with the content of a 3,27, create an InCmd
 * - Run the Start Action and check that the outcome == success
 * - this id sone to follow the default branch of the switch that checks the subservicetype
 * - release the InCmd and check that no InCmd's are allocated
 * 
 * 
 * @verify initialize all PUS Extension components and Applications
 * @verify creation of OutFactory, InFactory and OutManager
 * @verify allocating a 3,9 packet and run the start, progress and termination actions
 * @verify check that the outcome is set to success and that a 3,10 packet is created
 * @verify allocating a 3,11 packet and run the start, progress and termination actions
 * @verify check that the outcome is set to success and that a 3,12 packet is created
 * @verify allocating a 3,9 packet, fill the outfactory to trigger an error and run the start action
 * @verify check that the outcome is set to success and that the application error is set to crOutCmpAllocationFail
 * @verify allocating a 3,27 packet and run the start, progress and termination actions
 * @verify check that the outcome is set to success
 * @verify allocating a 3,28 packet and run the start, progress and termination actions
 * @verify check that the outcome is set to success
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsHkTestCase3();

/**
 * Test the Service 3 Housekeeping service
 *    Test all the 3,10 3,12 3,25 and 3,26 actions and procedures
 *
 * The following actions are performed in this test:
 *
 * - Instantiate all relevant CORDET Framework PUS Extension components
 * - manually delete all the SID's from the DataPool
 * - Initializing OutFactory, InFactory and OutManager
 * - Check that OutFactory, InFactory and OutManager are configured
 * - Check that the number of allocated Packets is initially 0
 * - manually set a SID and create a RDL in the Datapool
 * - Create a 3,25 Outcomponent with SID = 1
 * - run the EnableCheck and check if the outcome == success
 * - run the ReadyCheck and check if the outcome == success
 * - run the UpdateAction and check if the outcome == success
 * - Create a 3,10 Outcomponent with SID = 1
 * - run the UpdateAction and check if the outcome == success
 * - Create a 3,26 Outcomponent with SID = 3
 * - run the EnableCheck and check if the outcome == success
 * - run the ReadyCheck and check if the outcome == success
 * - run the UpdateAction and check if the outcome == success
 * - Create a 3,12 Outcomponent with SID = 3
 * - run the UpdateAction and check if the outcome == success
 * - Create a 3,25 Outcomponent with SID = 2 (wrong SID)
 * - run the EnableCheck and check if the outcome == success
 * - run the ReadyCheck and check if the outcome == success
 * - run the UpdateAction and check if the outcome == success
 * - Create a 3,10 Outcomponent with SID = 2 (wrong SID)
 * - run the UpdateAction and check if the outcome == success
 * - manually disable a SID in the Datapool
 * - Create a 3,25 Outcomponent with SID = 2 (wrong SID)
 * - run the EnableCheck and check if the outcome == success
 * - run the ReadyCheck and check if the outcome == 0
 * - reset the OutManager, OutFactory and inFactory and check for application errors 
 *
 *
 * @verify initialize all PUS Extension components and Applications
 * @verify creation of OutFactory, InFactory and OutManager
 * @verify allocating a 3,25 packet and run the enable check, ready check and update action
 * @verify check that the outcome is set to success
 * @verify allocating a 3,10 packet and run the update action
 * @verify check that the outcome is set to success
 * @verify allocating a 3,26 packet and run the enable check, ready check and update action
 * @verify check that the outcome is set to success
 * @verify allocating a 3,12 packet and run the update action
 * @verify check that the outcome is set to success
 * @verify allocating a 3,25 packet with an invalid SID and run the enable check, ready check and update action
 * @verify check that the outcome is set to success
 * @verify allocating a 3,10 packet with an invalid SID and run the update action
 * @verify check that the outcome is set to success
 * @verify allocating a 3,25 packet with a disabled SID and run the enable checkand ready check
 * @verify check that the outcome is set to 0
 * @verify reset OutManager, OutFactory and inFactory and check for application errors
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsHkTestCase4();

#endif /* CRPS_HK_TESTCASES_H_ */
