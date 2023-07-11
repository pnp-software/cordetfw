/**
 * @file
 * @ingroup crConfigGroup
 * User-modifiable parameters for the InStream components (see <code>CrFwInStream.h</code>).
 * This file defines all the user-modifiable parameters for the InStream.
 * Users will normally have to modify this file as part of framework instantiation process.
 *
 * The parameters defined in this file determine the configuration of the InStream Components.
 * The value of these parameters cannot be changed dynamically.
 *
 * The default values defined in this file are those used for the testing of the
 * CORDET Framework.
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#ifndef CR_FW_INSTREAM_USERPAR_H_
#define CR_FW_INSTREAM_USERPAR_H_

/* Include framework files */
#include "InStream/CrFwInStream.h"
#include "BaseCmp/CrFwResetProc.h"
/* Include test suite files */
#include "CrFwInStreamStub.h"
#include "CrFwInStreamSocket.h"
#include "CrFwClientSocket.h"
#include "CrFwServerSocket.h"

/**
 * The number of InStream components in the application.
 * The value of this constant must be smaller than the range of the <code>::CrFwCounterU1_t</code>
 * integer type.
 *
 * The number of InStream components defined in this file is the one used for the test cases
 * of <code>CrFwInStreamTestCases.h</code>.
 */
#define CR_FW_NOF_INSTREAM 7

/**
 * The sizes of the packet queues in the InStream components.
 * Each InStream has one packet queue.
 * This constant defines the size of the packet queue of the i-th InStream.
 * The size of the packet queue represents the maximum number of packets which
 * may remain pending in the packet queue.
 * The size of a packet queue must be a positive integer (i.e. it is not legal
 * to define a zero-size packet queue).
 *
 * The packet queue sizes defined in this file are those used for the test cases
 * of <code>CrFwInStreamTestCases.h</code>.
 */
#define CR_FW_INSTREAM_PQSIZE {3,3,3,3,5,6,7}

/**
 * The number of groups managed by the InStream components.
 * The number of groups must be a positive integer.
 *
 * The number of groups defined in this file are those used for the test cases
 * of <code>CrFwInStreamTestCases.h</code>.
 */
#define CR_FW_INSTREAM_NOF_GROUPS 2

/**
 * The number of distinct sources from which the InStream components
 * may receive packets.
 * The number of sources must be a positive integer.
 *
 * The number of sources defined in this file are those used for the test cases
 * of <code>CrFwInStreamTestCases.h</code>.
 */
#define CR_FW_INSTREAM_NOF_SRCS 8

/**
 * The association of sources to InStreams.
 * An InStream is responsible for managing incoming commands or reports  
 * from one or more sources.
 * Each element of this array consists of a pair (source, inStreamId)
 * where inStreamId is the identifier of the InStream correponding
 * to source 'source'.
 * The value of the InStreamId must be smaller than CR_FW_NOF_INSTREAM.
 * This is checked by the <code>::CrFwAuxInStreamConfigCheck</code> function.
 *
 * The size of this array must be equal to <code>#CR_FW_INSTREAM_NOF_SRCS</code>.
 */
#define CR_FW_INSTREAM_SRC_PAIRS   {{1,0},\
							    	{2,1},\
							  		{3,2},\
							  		{4,3},\
							  		{5,4},\
							  		{6,0},\
							  		{7,5},\
							  		{10,6}}

/**
 * The functions implementing  the Packet Collect Operations of the InStream components.
 * Each InStream component needs to be able to collect a packet from the middleware.
 * The function implementing this packet collect operation is one of the
 * adaptation points of the framework.
 * This array defines the packet collect operations for the InStream.
 * The items in the arrays must be function pointers of type:
 * <code>::CrFwPcktCollect_t</code>.
 *
 * The packet collection operations defined in this file are the ones provided
 * by the InStream stub of <code>CrFwInStreamStub.h</code> and by the
 * socket-based InStream of <code>CrFwInStreamSocket.h</code>.
 */
#define CR_FW_INSTREAM_PCKTCOLLECT {&CrFwInStreamStubPcktCollect,  \
									&CrFwInStreamStubPcktCollect,  \
									&CrFwInStreamStubPcktCollect,  \
									&CrFwInStreamStubPcktCollect,  \
									&CrFwInStreamSocketPcktCollect, \
								    &CrFwClientSocketPcktCollect, \
									&CrFwServerSocketPcktCollect}

/**
 * The functions implementing the Packet Available Check Operations of the InStream
 * components.
 * Each InStream component needs to be able to check whether the middleware is in
 * state WAITING (no packet is available for collection) or PCKT_AVAIL (a packet is
 * available for collection).
 * The functions which query the middleware to check whether a packet is available
 * or not is one of the adaptation points of the framework.
 * This array defines the Packet Available Check Operations for the InStream.
 * The items in the array must be function pointers of type:
 * <code>::CrFwPcktAvailCheck_t</code>.
 *
 * The packet available check operations defined in this file are the ones provided
 * by the InStream stub of <code>CrFwInStreamStub.h</code> and by the
 * socket-based InStream of <code>CrFwInStreamSocket.h</code>.
 */
#define CR_FW_INSTREAM_PCKTAVAILCHECK {&CrFwInStreamStubIsPcktAvail,  \
									   &CrFwInStreamStubIsPcktAvail,  \
									   &CrFwInStreamStubIsPcktAvail,  \
									   &CrFwInStreamStubIsPcktAvail,  \
									   &CrFwInStreamSocketIsPcktAvail, \
								       &CrFwClientSocketIsPcktAvail, \
									   &CrFwServerSocketIsPcktAvail}

/**
 * The functions implementing the Initialization Check of the InStream components.
 * The InStream components are derived from the Base Component and they therefore
 * inherit its Initialization Procedure (see <code>CrFwInitProc.h</code>).
 * The initialization procedure must be configured with two actions:
 * the Initialization Action and the Initialization Check.
 * This constant defines the functions implementing the Initialization Checks
 * for the the InStream components.
 * The items in the array must be function pointers of type:
 * <code>FwPrAction_t</code>.
 *
 * Function <code>::CrFwBaseCmpDefInitCheck</code> can be used as a default
 * implementation for this function.
 *
 * The Initialization Check functions defined for the first 3 InStreams are
 * the default Initialization Check functions <code>::CrFwBaseCmpDefInitCheck</code>
 * offered by the base component.
 * The fourth Initialization Check is defined in the stub InStream of
 * <code>CrFwInStreamStub.h</code> and it is used to verify initialization check failures.
 * The last Initialization Check is defined in the Socket-Based InStream of
 * <code>CrFwInStreamSocket.h</code>.
 * Applications may need to use different functions which also cover
 * the initialization of the middleware.
 */
#define CR_FW_INSTREAM_INITCHECK {&CrFwBaseCmpDefInitCheck, \
								  &CrFwBaseCmpDefInitCheck, \
								  &CrFwBaseCmpDefInitCheck, \
	                              &CrFwInStreamStubDummyCheck, \
	                              &CrFwInStreamSocketInitCheck, \
								  &CrFwClientSocketInitCheck, \
								  &CrFwServerSocketInitCheck}

/**
 * The functions implementing the Initialization Action of the InStream components.
 * The InStream components are derived from the Base Component and they therefore
 * inherit its Initialization Procedure (see <code>CrFwInitProc.h</code>).
 * The initialization procedure must be configured with two actions:
 * the Initialization Action and the Initialization Check.
 * This constant defines the functions implementing the Initialization Actions
 * for the the InStream components.
 * The items in the array must be function pointers of type:
 * <code>FwPrAction_t</code>.
 *
 * Function <code>::CrFwInStreamDefInitAction</code> can be used as a default
 * implementation for this function.
 * This function initializes the internal data structures for the InStream.
 * An application-specific Initialization Action should therefore include a call
 * to this function.
 *
 * The first three Initialization Action functions defined in this file are the default
 * Initialization Action functions <code>::CrFwInStreamDefInitAction</code>
 * offered by the InStream component.
 * The fourth Initialization Action is defined in the stub InStream of
 * <code>CrFwInStreamStub.h</code> and it is used to verify initialization failures.
 * The last Initialization Action is defined in the Socket-Based InStream of
 * <code>CrFwInStreamSocket.h</code>.
 * Applications may need to use different functions which also include
 * the initialization of the middleware.
 */
#define CR_FW_INSTREAM_INITACTION {&CrFwInStreamDefInitAction, \
								   &CrFwInStreamDefInitAction, \
								   &CrFwInStreamDefInitAction, \
	                               &CrFwInStreamStubInitAction, \
	                               &CrFwInStreamSocketInitAction, \
								   &CrFwClientSocketInitAction, \
								   &CrFwServerSocketInitAction}

/**
 * The functions implementing the Configuration Check of the InStream components.
 * The InStream components are derived from the Base Component and they therefore
 * inherit its Reset Procedure (see <code>CrFwResetProc.h</code>).
 * The reset procedure must be configured with two actions:
 * the Configuration Action and the Configuration Check.
 * This constant defines the functions implementing the Configuration Checks
 * for the the InStream components.
 * The items in the array must be function pointers of type:
 * <code>FwPrAction_t</code>.
 *
 * Function <code>::CrFwBaseCmpDefConfigCheck</code> can be used as a default
 * implementation for this function.
 *
 * The Configuration Check functions defined in this file are the default
 * Configuration Check functions <code>::CrFwBaseCmpDefConfigCheck</code>
 * offered by the Base Component with the exception of
 * the fourth Configuration Check which is defined in the test suite as a dummy
 * check to verify configuration failures.
 * Applications may need to use different functions which also cover
 * the configuration of the middleware.
 */
#define CR_FW_INSTREAM_CONFIGCHECK {&CrFwBaseCmpDefConfigCheck, \
								    &CrFwBaseCmpDefConfigCheck, \
								    &CrFwBaseCmpDefConfigCheck, \
	                                &CrFwInStreamStubDummyCheck, \
	                                &CrFwBaseCmpDefConfigCheck, \
								    &CrFwBaseCmpDefConfigCheck, \
								    &CrFwServerSocketConfigCheck}

/**
 * The functions implementing the Configuration Action of the InStream components.
 * The InStream components are derived from the Base Component and they therefore
 * inherit its Reset Procedure (see <code>CrFwResetProc.h</code>).
 * The reset procedure must be configured with two actions:
 * the Configuration Action and the Configuration Check.
 * This constant defines the functions implementing the Configuration Actions
 * for the the InStream components.
 * The items in the array must be function pointers of type:
 * <code>FwPrAction_t</code>.
 *
 * Function <code>::CrFwInStreamDefConfigAction</code> can be used as a default
 * implementation for this function.
 * This function initializes the internal data structures for the InStream.
 * An application-specific Configuration Action should therefore include a call
 * to this function.
 *
 * The first three Configuration Action functions defined in this file are the default
 * Configuration Action functions <code>::CrFwInStreamDefConfigAction</code>
 * offered by the InStream component.
 * The fourth Configuration Action which is defined in the stub InStream of
 * <code>CrFwInStreamStub.h</code> and it is used to verify initialization failures.
 * The last Configuration Action is defined in the Socket-Based InStream of
 * <code>CrFwInStreamSocket.h</code>.
 * Applications may need to use different functions which also cover
 * the configuration of the middleware.
 */
#define CR_FW_INSTREAM_CONFIGACTION {&CrFwInStreamDefConfigAction, \
								     &CrFwInStreamDefConfigAction, \
								     &CrFwInStreamDefConfigAction, \
	                                 &CrFwInStreamStubConfigAction, \
	                                 &CrFwInStreamSocketConfigAction, \
								     &CrFwClientSocketConfigAction, \
								     &CrFwServerSocketConfigAction}

/**
 * The functions implementing the Shutdown Action of the InStream components.
 * The InStream components are derived from the Base Component and they therefore
 * inherit its Shutdown Action (see <code>CrFwBaseCmp.h</code>).
 * This constant defines the shutdown functions for the the InStream components.
 * The items in the array must be function pointers of type:
 * <code>FwSmAction_t</code>.
 *
 * Function <code>::CrFwInStreamDefShutdownAction</code> can be used as a default
 * implementation for this function.
 * This function initializes the internal data structures for the InStream.
 * An application-specific Shutdown Action should therefore include a call
 * to this function.
 *
 * The first, the third and the fourth Shutdown Action functions defined
 * in this file are the default
 * Shutdown Action functions <code>::CrFwInStreamDefShutdownAction</code>
 * offered by the InStream component.
 * The second shutdown action is defined in the stub InStream of
 * <code>CrFwInStreamStub.h</code> and it is used to verify initialization failures.
 * The last Shutdown Action is defined in the Socket-Based InStream of
 * <code>CrFwInStreamSocket.h</code>.
 * Applications may need to use different functions which also cover
 * the shutdown of the middleware.
 */
#define CR_FW_INSTREAM_SHUTDOWNACTION {&CrFwInStreamDefShutdownAction, \
							     	   &CrFwInStreamStubShutdown, \
							     	   &CrFwInStreamDefShutdownAction, \
									   &CrFwInStreamDefShutdownAction, \
									   &CrFwInStreamSocketShutdownAction, \
								       &CrFwClientSocketShutdownAction, \
								       &CrFwServerSocketShutdownAction}

#endif /* CR_FW_INSTREAM_USERPAR_H_ */
