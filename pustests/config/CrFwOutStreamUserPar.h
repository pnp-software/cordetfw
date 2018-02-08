/**
 * @file CrFwOutStreamUserPar.h
 * @ingroup PUSTestsuite
 * @ingroup PUSTestconfig 
 * User-modifiable parameters for the OutStream components (see <code>CrFwOutStream.h</code>).
 * This file defines all the user-modifiable parameters for the OutStream.
 * Users will normally have to modify this file as part of framework instantiation process.
 *
 * The parameters defined in this file determine the configuration of the OutStream Components.
 * The value of these parameters cannot be changed dynamically.
 *
 * The default values defined in this file are those used for the testing of the
 * CORDET Framework.
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * @author Christian Reimers <christian.reimers@univie.ac.at>
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

#ifndef CR_FW_OUTSTREAM_USERPAR_H_
#define CR_FW_OUTSTREAM_USERPAR_H_

/* Include framework files */
#include "OutStream/CrFwOutStream.h"
#include "BaseCmp/CrFwResetProc.h"
/* Include test suite files */
#include "CrFwOutStreamStub.h"
#include "CrFwOutStreamSocket.h"
#include "CrFwClientSocket.h"
#include "CrFwServerSocket.h"

/**
 * The number of OutStream components in the application.
 * Normally, an application should instantiate one OutStream component for each
 * destination to which a report or a command may be sent.
 * The value of this constant must be smaller than the range of the <code>::CrFwCounterU1_t</code>
 * integer type.
 */
#define CR_FW_NOF_OUTSTREAM 7

/**
 * The sizes of the packet queues in the OutStream component.
 * Each OutStream has one packet queue.
 * This constant defines the size of the packet queue of the i-th OutStream.
 * The size of the packet queue represents the maximum number of packets which
 * may remain pending in the packet queue.
 * The size of a packet queue must be a positive integer (i.e. it is not legal
 * to define a zero-size packet queue).
 *
 * The packet sizes defined in this file are those used for the test cases
 * of <code>CrFwOutStreamTestCases.h</code>.
 */
#define CR_FW_OUTSTREAM_PQSIZE {3,3,3,3,5,5,5}

/**
 * The destinations of the OutStream components.
 * The destination of an OutStream is the middleware node to which the OutStream
 * sends its packet.
 * Each OutStream has one (and only one) destination associated to it.
 * A destination is defined by a non-negative integer.
 * This array defines the destination of the i-th OutStream.
 *
 * The destinations defined in this file are those used for the test cases
 * of <code>CrFwOutStreamTestCases.h</code>.
 */
#define CR_FW_OUTSTREAM_DEST {1,2,3,4,5,6,7}

/**
 * The number of groups of the OutStream components.
 * The number of groups must be a positive integer.
 * This array defines the number of groups of the i-th OutStream.
 *
 * The number of groups defined in this file are those used for the test cases
 * of <code>CrFwOutStreamTestCases.h</code>.
 */
#define CR_FW_OUTSTREAM_NOF_GROUPS {1,2,1,1,1,1,1}

/**
 * The functions implementing the packet hand-over operations of the OutStream components.
 * Each OutStream component needs to be able to hand-over a packet to the middleware.
 * The function implementing this packet hand-over operation is one of the
 * adaptation points of the framework.
 * This array defines the packet hand-over operations for the OutStream.
 * The items in the arrays must be function pointers of type:
 * <code>::CrFwPcktHandover_t</code>.
 * No default is defined at framework level for this function.
 *
 * The packet handover functions defined in this file are those used for the test cases
 * of <code>CrFwOutStreamTestCases.h</code>.
 */
#define CR_FW_OUTSTREAM_PCKTHANDOVER {&CrFwOutStreamStubPcktHandover, \
									  &CrFwOutStreamStubPcktHandover, \
									  &CrFwOutStreamStubPcktHandover, \
									  &CrFwOutStreamStubPcktHandover, \
									  &CrFwOutStreamSocketPcktHandover, \
									  &CrFwClientSocketPcktHandover, \
									  &CrFwServerSocketPcktHandover}

/**
 * The functions implementing the Initialization Check of the OutStream components.
 * The OutStream components are derived from the Base Component and they therefore
 * inherit its Initialization Procedure (see <code>CrFwInitProc.h</code>).
 * The initialization procedure must be configured with two actions:
 * the Initialization Action and the Initiation Check.
 * This constant defines the functions implementing the Initialization Checks
 * for the the OutStream components.
 * The items in the array must be function pointers of type:
 * <code>FwPrAction_t</code>.
 * Function <code>::CrFwBaseCmpDefInitCheck</code> can be used as a default
 * implementation for this function.
 */
#define CR_FW_OUTSTREAM_INITCHECK {&CrFwBaseCmpDefInitCheck, \
							 	   &CrFwBaseCmpDefInitCheck, \
								   &CrFwBaseCmpDefInitCheck, \
	                               &CrFwOutStreamStubDummyCheck, \
	                               &CrFwOutStreamSocketInitCheck, \
								   &CrFwClientSocketInitCheck, \
								   &CrFwServerSocketInitCheck}

/**
 * The functions implementing the Initialization Action of the OutStream components.
 * The OutStream components are derived from the Base Component and they therefore
 * inherit its Initialization Procedure (see <code>CrFwInitProc.h</code>).
 * The initialization procedure must be configured with two actions:
 * the Initialization Action and the Initialization Check.
 * This constant defines the functions implementing the Initialization Actions
 * for the the OutStream components.
 * The items in the array must be function pointers of type:
 * <code>FwPrAction_t</code>.
 *
 * Function <code>::CrFwOutStreamDefInitAction</code> can be used as a default
 * implementation for this function.
 * This function initializes the internal data structures for the OutStream.
 * An application-specific Initialization Action should therefore include a call
 * to this function.
 */
#define CR_FW_OUTSTREAM_INITACTION {&CrFwOutStreamDefInitAction, \
								   &CrFwOutStreamDefInitAction, \
								   &CrFwOutStreamDefInitAction, \
	                               &CrFwOutStreamStubInitAction, \
	                               &CrFwOutStreamSocketInitAction, \
								   &CrFwClientSocketInitAction, \
								   &CrFwServerSocketInitAction}

/**
 * The functions implementing the Configuration Check of the OutStream components.
 * The OutStream components are derived from the Base Component and they therefore
 * inherit its Reset Procedure (see <code>CrFwResetProc.h</code>).
 * The reset procedure must be configured with two actions:
 * the Configuration Action and the Configuration Check.
 * This constant defines the functions implementing the Configuration Checks
 * for the the OutStream components.
 * The items in the array must be function pointers of type:
 * <code>FwPrAction_t</code>.
 * Function <code>::CrFwBaseCmpDefConfigCheck</code> can be used as a default
 * implementation for this function.
 */
#define CR_FW_OUTSTREAM_CONFIGCHECK {&CrFwBaseCmpDefConfigCheck, \
								    &CrFwBaseCmpDefConfigCheck, \
								    &CrFwBaseCmpDefConfigCheck, \
	                                &CrFwOutStreamStubDummyCheck, \
	                                &CrFwOutStreamSocketConfigCheck, \
								    &CrFwBaseCmpDefConfigCheck, \
								    &CrFwServerSocketConfigCheck}

/**
 * The functions implementing the Configuration Action of the OutStream components.
 * The OutStream components are derived from the Base Component and they therefore
 * inherit its Reset Procedure (see <code>CrFwResetProc.h</code>).
 * The reset procedure must be configured with two actions:
 * the Configuration Action and the Configuration Check.
 * This constant defines the functions implementing the Configuration Actions
 * for the the OutStream components.
 * The items in the array must be function pointers of type:
 * <code>FwPrAction_t</code>.
 *
 * Function <code>::CrFwOutStreamDefConfigAction</code> can be used as a default
 * implementation for this function.
 * This function resets the internal data structures for the OutStream.
 * An application-specific Configuration Action should therefore include a call
 * to this function.
 */
#define CR_FW_OUTSTREAM_CONFIGACTION {&CrFwOutStreamDefConfigAction, \
								     &CrFwOutStreamDefConfigAction, \
								     &CrFwOutStreamDefConfigAction, \
	                                 &CrFwOutStreamStubConfigAction, \
	                                 &CrFwOutStreamDefConfigAction, \
								     &CrFwClientSocketConfigAction, \
								     &CrFwServerSocketConfigAction}

/**
 * The functions implementing the Shutdown Action of the OutStream components.
 * The OutStream components are derived from the Base Component and they therefore
 * inherit its Shutdown Action (see <code>CrFwBaseCmp.h</code>).
 * This constant defines the shutdown functions for the the OutStream components.
 * The items in the array must be function pointers of type:
 * <code>FwSmAction_t</code>.
 *
 * Function <code>::CrFwOutStreamDefShutdownAction</code> can be used as a default
 * implementation for this function.
 * This function releases the memory resources used by the OutStream.
 * An application-specific Shutdown Action should therefore include a call
 * to this function.
 */
#define CR_FW_OUTSTREAM_SHUTDOWNACTION {&CrFwOutStreamDefShutdownAction, \
							     	   &CrFwOutStreamStubShutdown, \
							     	   &CrFwOutStreamDefShutdownAction, \
									   &CrFwOutStreamDefShutdownAction, \
									   &CrFwOutStreamSocketShutdownAction, \
								       &CrFwClientSocketShutdownAction, \
								       &CrFwServerSocketShutdownAction}

#endif /* CR_FW_OUTSTREAM_USERPAR_H_ */
