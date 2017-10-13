/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the InLoader Component (see <code>CrFwInLoader.h</code>).
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
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

#ifndef CRFW_INLOADER_TESTCASES_H_
#define CRFW_INLOADER_TESTCASES_H_

#include "CrFwConstants.h"
#include "CrFwUserConstants.h"

/**
 * Test implementation of the function which checks the legality of a destination and
 * returns the re-routing destination (adaptation points A7.2.2-9 and A7.2.2-11).
 * This test implementation can be configured to return either zero (to signify that the argument
 * destination is invalid) or a positive integer (to represent a re-routing destination).
 * This function must conform to the prototype defined by <code>::CrFwInLoaderGetReroutingDest_t</code>.
 * @param pcktDest the packet destination.
 * @return the re-routing destination or zero if the argument destination is illegal.
 */
CrFwDestSrc_t CrFwInLoaderTestCaseGetReroutingDestination(CrFwDestSrc_t pcktDest);

/**
 * Check the configuration of a newly created InLoader.
 * The following actions are performed in this test:
 * - The InLoader is created and it is checked that it is in state CREATED.
 * - The InLoader is initialized and reset and it is checked that it is in state CONFIGURED.
 * - The instance identifier and the type identifier of the InLoader is checked.
 * - The first of the two default implementations of the function which checks the legality of a destination
 *   and returns the re-routing destination (<code>::CrFwInLoaderDefGetReroutingDestination</code>)
 *   is checked.
 * - The second of the two default implementations of the function which checks the legality of a
 *   destination and returns the re-routing destination (<code>::CrFwInLoaderDefNoRerouting</code>)
 *   is checked.
 * - The default implementation of the function which selects the InManager to which an
 *   incoming InReport or InCommand must be loaded (<code>::CrFwInLoaderDefGetInManager</code>)
 *   is checked.
 * .
 * @verify Base Component SM Transition: IPS->CREATED
 * @verify Base Component SM Transition: CREATED->INITIALIZED
 * @verify Base Component SM Transition: INITIALIZED->CONFIGURED
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInLoaderTestCase1();

/**
 * Check the execution function of an InLoader for the case where there are no pending packet
 * in the InStream.
 * The following actions are performed in this test:
 * - The InLoader is created, initialized and configured.
 * - An InStream is created, initialized and configured to have no pending packets.
 * - The function which checks the validity of a destination is configured to return: "destination
 *   invalid".
 * - The InStream is loaded in the InLoader and then the InLoader is executed.
 * - It is checked that the InLoader returns without taking any further action (this is done
 *   by checking that no report is generated for the "invalid destination").
 * .
 * @verify InLoader Execution Procedure: No Packet Returned by InStream
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInLoaderTestCase2();

/**
 * Check the execution function of an InLoader for the case where the packet destination is invalid.
 * The following actions are performed in this test:
 * - The InLoader is created, initialized and configured.
 * - An InStream is created, initialized and configured to have one pending packet.
 * - The function which checks the validity of a destination is configured to return: "destination
 *   invalid".
 * - The InStream is loaded in the InLoader and then the InLoader is executed.
 * - It is checked that the InLoader releases the packet and reports that the packet destination is
 *   invalid.
 * .
 * @verify InLoader Execution Procedure: Packet Destination is Invalid
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInLoaderTestCase3();


/**
 * Check the execution function of an InLoader for the case where the packet must be re-routed
 * to another destination.
 * The following actions are performed in this test:
 * - The InLoader is created, initialized and configured.
 * - An InStream is created, initialized and configured to have one pending packet.
 * - An OutStream is created, initialized and configured.
 * - The function which checks the validity of a destination is configured to return the destination
 *   associated to the OutStream.
 * - The InStream is loaded in the InLoader and then the InLoader is executed.
 * - It is checked that the packet is loaded into the OutStream.
 * .
 * @verify InLoader Execution Procedure: Packet Destination is Valid && Packet Destination is not the Host Application
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInLoaderTestCase4();

/**
 * Check the execution function of an InLoader for the case where the packet destination is the
 * host application but the packet type is invalid.
 * The following actions are performed in this test:
 * - The InLoader is created, initialized and configured.
 * - The InFactory is created, initialized and configured.
 * - An InStream is created, initialized and configured to have one pending packet representing an
 *   InReport with an invalid type.
 * - The function which checks the validity of a destination is configured to return the host application
 *   as a destination.
 * - The InStream is loaded in the InLoader and then the InLoader is executed.
 * - It is checked that no InReport components are allocated; that an acceptance failure error report is
 *   generated; and that the application code is set to <code>::crIllInRepKind</code>.
 * - The same actions as above are repeated when the packet in the InStream is an InCommand.
 * .
 * @verify InLoader Execution Procedure: Packet Destination is Valid && Packet Destination is the Host Application
 * @verify InLoader Load Command/Report Procedure: Packet Type is Invalid
 * @verify Application Error: crIllInRepKind
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInLoaderTestCase5();

/**
 * Check the execution function of an InLoader for the case where the packet destination is the
 * host application, the packet type is valid but the make operation fails.
 * The following actions are performed in this test:
 * - The InLoader is created, initialized and configured.
 * - The InFactory is created, initialized and it is configured to have no more spare InReport
 *   components.
 * - An InStream is created, initialized and configured to have one pending packet representing a
 *   valid InReport.
 * - The function which checks the validity of a destination is configured to return the host application
 *   as a destination.
 * - The InStream is loaded in the InLoader and then the InLoader is executed.
 * - It is checked that no InReport components are allocated; that an acceptance failure report is
 *   generated; and that the application code is set to <code>::crInRepAllocationFail</code>.
 * - The same actions as above are repeated when the packet in the InStream is an InCommand.
 * .
 * @verify InLoader Execution Procedure: Packet Destination is Valid && Packet Destination is the Host Application
 * @verify InLoader Load Command/Report Procedure: Packet Type is Valid
 * @verify InLoader Load Command/Report Procedure: Make Operation Fails
 * @verify Application Error: crInRepAllocationFail
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInLoaderTestCase6();

/**
 * Check the execution function of an InLoader for the case where the packet destination is the
 * host application, the packet type is valid but the InReport/InCommand component fails its
 * validity check (it does not enter state CONFIGURED).
 * The following actions are performed in this test:
 * - The InLoader is created, initialized and configured.
 * - The InFactory is created, initialized and is configured.
 * - An InStream is created, initialized and configured to have one pending packet representing a
 *   valid Sample 1 InReport.
 * - The Sample 1 InReport is configured to fail its validity check.
 * - The function which checks the validity of a destination is configured to return the host application
 *   as a destination.
 * - The InStream is loaded in the InLoader and then the InLoader is executed.
 * - It is checked that no InReport components are allocated and that an acceptance failure report is
 *   generated.
 * - The same actions as above are repeated when the packet in the InStream is an InCommand.
 * .
 * @verify InLoader Execution Procedure: Packet Destination is Valid && Packet Destination is the Host Application
 * @verify InLoader Load Command/Report Procedure: Packet Type is Valid
 * @verify InLoader Load Command/Report Procedure: Make Operation returns an InCmd/InRep
 * @verify InLoader Load Command/Report Procedure: InCmd/InRep is not in State CONFIGURED
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInLoaderTestCase7();

/**
 * Check the execution function of an InLoader for the case where the packet destination is the
 * host application, the packet type is valid, the InReport/InCommand component is successfully
 * configured but the load operation in the InManager fails.
 * The following actions are performed in this test:
 * - The InLoader is created, initialized and configured.
 * - The InFactory is created, initialized and is configured.
 * - The InManager for InReports is created, initialized and is configured to be full.
 * - An InStream is created, initialized and configured to have one pending packet representing a
 *   valid Sample 1 InReport.
 * - The Sample 1 InReport is configured to pass its validity check.
 * - The function which checks the validity of a destination is configured to return the host application
 *   as a destination.
 * - The InStream is loaded in the InLoader and then the InLoader is executed.
 * - It is checked that an acceptance failure report is generated and that the application code is
 *   set to <code>::crInManagerPcrlFull</code>.
 * - The same actions as above are repeated when the packet in the InStream is an InCommand.
 * .
 * @verify InLoader Execution Procedure: Packet Destination is Valid && Packet Destination is the Host Application
 * @verify InLoader Load Command/Report Procedure: Packet Type is Valid
 * @verify InLoader Load Command/Report Procedure: Make Operation returns an InCmd/InRep
 * @verify InLoader Load Command/Report Procedure: InCmd/InRep is in State CONFIGURED
 * @verify InLoader Load Command/Report Procedure: Load Operation Failed
 * @verify Application Error: crInManagerPcrlFull
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInLoaderTestCase8();

/**
 * Check the execution function of an InLoader for the case where the packet destination is the
 * host application, the packet type is valid, the InReport/InCommand component is successfully
 * configured, the load operation in the InManager succeeds and the loaded component is an
 * InReport.
 * The following actions are performed in this test:
 * - The InLoader is created, initialized and configured.
 * - The InFactory is created, initialized and is configured.
 * - The InManager for InReports is created, initialized and is configured to be empty.
 * - An InStream is created, initialized and configured to have one pending packet representing a
 *   valid Sample 1 InReport.
 * - The Sample 1 InReport is configured to pass its validity check.
 * - The function which checks the validity of a destination is configured to return the host application
 *   as a destination.
 * - The InStream is loaded in the InLoader and then the InLoader is executed.
 * - It is checked that no acceptance failure report is generated and that the InReport has been loaded
 *   in the InManager.
 * .
 * @verify InLoader Execution Procedure: Packet Destination is Valid && Packet Destination is the Host Application
 * @verify InLoader Load Command/Report Procedure: Packet Type is Valid
 * @verify InLoader Load Command/Report Procedure: Make Operation returns an InCmd/InRep
 * @verify InLoader Load Command/Report Procedure: InCmd/InRep is in State CONFIGURED
 * @verify InLoader Load Command/Report Procedure: Load Operation Succeeded
 * @verify InLoader Load Command/Report Procedure: Component Being Loaded is an InReport
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInLoaderTestCase9();

/**
 * Check the execution function of an InLoader for the case where the packet destination is the
 * host application, the packet type is valid, the InReport/InCommand component is successfully
 * configured the load operation in the InManager succeeds and the loaded component is an
 * InCommand for which no acknowledgement of acceptance is required.
 * The following actions are performed in this test:
 * - The InLoader is created, initialized and configured.
 * - The InFactory is created, initialized and is configured.
 * - The InManager for InCommands is created, initialized and is configured to be empty.
 * - An InStream is created, initialized and configured to have one pending packet representing a
 *   valid Sample 1 InCommand.
 * - The Sample 1 InCommand is configured to pass its validity check and not to require acknowledgement
 *   of acceptance.
 * - The function which checks the validity of a destination is configured to return the host application
 *   as a destination.
 * - The InStream is loaded in the InLoader and then the InLoader is executed.
 * - It is checked that neither acceptance nfailure report nor acceptance successful report is generated
 *   and that the InCommand has been loaded in the InManager.
 * .
 * @verify InLoader Execution Procedure: Packet Destination is Valid && Packet Destination is the Host Application
 * @verify InLoader Load Command/Report Procedure: Packet Type is Valid
 * @verify InLoader Load Command/Report Procedure: Make Operation returns an InCmd/InRep
 * @verify InLoader Load Command/Report Procedure: InCmd/InRep is in State CONFIGURED
 * @verify InLoader Load Command/Report Procedure: Load Operation Succeeded
 * @verify InLoader Load Command/Report Procedure: Component Being Loaded is an InCommand && No Acknowledgement of Acceptance is Required
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInLoaderTestCase10();

/**
 * Check the execution function of an InLoader for the case where the packet destination is the
 * host application, the packet type is valid, the InReport/InCommand component is successfully
 * configured the load operation in the InManager succeeds and the loaded component is an
 * InCommand for which acknowledgement of acceptance is required.
 * The following actions are performed in this test:
 * - The InLoader is created, initialized and configured.
 * - The InFactory is created, initialized and is configured.
 * - The InManager for InCommands is created, initialized and is configured to be empty.
 * - An InStream is created, initialized and configured to have one pending packet representing a
 *   valid Sample 1 InCommand.
 * - The Sample 1 InCommand is configured to pass its validity check and to require acknowledgement
 *   of acceptance.
 * - The function which checks the validity of a destination is configured to return the host application
 *   as a destination.
 * - The InStream is loaded in the InLoader and then the InLoader is executed.
 * - It is checked that an acceptance successful report is generated
 *   and that the InCommand has been loaded in the InManager.
 * .
 * @verify InLoader Execution Procedure: Packet Destination is Valid && Packet Destination is the Host Application
 * @verify InLoader Load Command/Report Procedure: Packet Type is Valid
 * @verify InLoader Load Command/Report Procedure: Make Operation returns an InCmd/InRep
 * @verify InLoader Load Command/Report Procedure: InCmd/InRep is in State CONFIGURED
 * @verify InLoader Load Command/Report Procedure: Load Operation Succeeded
 * @verify InLoader Load Command/Report Procedure: Component Being Loaded is an InCommand && Acknowledgement of Acceptance is Required
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInLoaderTestCase11();


#endif /* CRFW_INLOADER_TESTCASES_H_ */
