/**
 * @file
 * @ingroup crConfigGroup
 * User-modifiable parameters for the OutStream components (see <code>CrFwOutStream.h</code>).
 * This file defines all the user-modifiable parameters for the OutStream.
 * Users will normally have to modify this file as part of the framework instantiation process.
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
 * This file is part of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
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
 * An application must have at least one OutStream but it can also have more.
 * The value of this constant must be smaller than the range of the 
 * <code>::CrFwCounterU1_t</code> integer type.
 */
#define CR_FW_NOF_OUTSTREAM 7

/**
 * Number of destinations for out-going packets.
 * The destinations are specified in <code>#CR_FW_OUTSTREAM_DEST_PAIRS</code>.
*/
#define CR_FW_OUTSTREAM_NOF_DEST 8

/**
 * The association of destinations to OutStreams.
 * An OutStream is responsible for routing commands or reports to one or 
 * more destinations.
 * Each element of this array consists of a pair (dest, outStreamId)
 * where outStreamId is the identifier of the OutStream correponding
 * to destination dest.
 * The value of the outStreamId must be smaller than CR_FW_NOF_OUTSTREAM.
 * This is checked by the <code>::CrFwAuxOutStreamConfigCheck</code> function.
 *
 * The size of this array must be equal to <code>#CR_FW_OUTSTREAM_NOF_DEST</code>.
 * 
 * @AP OSR-07: Get OutStream Operation of OutStreamRegistry 
 * @AP OST-15: Association of Packet Destinations to their OutStreams 
 */
#define CR_FW_OUTSTREAM_DEST_PAIRS 	{{1,0},\
							  		 {2,0},\
							  		 {3,2},\
							  		 {4,3},\
							  		 {5,4},\
							  		 {6,5},\
							  		 {7,6},\
							  		 {8,1}}

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
 * 
 * @AP OST-01: Packet Queue Size for OutStream 
 */
#define CR_FW_OUTSTREAM_PQSIZE {3,3,3,3,5,5,5}

/**
 * The number of groups managed by the OutStream components.
 * The number of groups must be a positive integer.
 * The packet group identifiers are non-negative integers in increasing
 * order starting at zero (i.e. they are: 0, 1, 2, ...CR_FW_OUTSTREAM_NOF_GROUPS-1).
 * Thus, only packet group identifiers smaller than CR_FW_OUTSTREAM_NOF_GROUPS
 * are legal.
 * If a packet with an illegal group attribute is passed to an OutStream, 
 * the error condition <code>#crOutStreamIllGroup</code> is declared.
 *
 * The number of groups defined in this file are those used for the test cases
 * of <code>CrFwOutStreamTestCases.h</code>.
 */
#define CR_FW_OUTSTREAM_NOF_GROUPS 2

/**
 * Pointer to Set DTS function which populates the DTS_SET for the OutStreams.
 * The DTS_SET set holds the triplets (d,t,s) where d is a destination identifier,
 * t is a service type and s is a service sub-type. 
 * The elements of DTS_SET are those for which the OutStreams maintain a type counter.
 * 
 * A default value of the Set DTS function is provided by function 
 * <code>#CrFwOutStreamDefSetDTS</code>.
 * The Set DTS function must be a function pointers of type:
 * <code>::CrFwSetDst_t</code>.
 * 
 * @AP OST-11: Type Counter Set DST_SET
 */
#define CR_FW_OUTSTREAM_SET_DTS &CrFwOutStreamDefSetDTS

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
 * 
 * @AP OST-08: Packet Hand-Over Operation of OutStream 
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
 * 
 * @AP OST-03: Initialization Action in Initialization Procedure of OutStream 
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
 * 
 * @AP OST-04: Configuration Check in Reset Procedure of OutStream 
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
 * 
 * @AP OST-05: Configuration Action in Reset Procedure of OutStream 
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
 * 
 * @AP OST-06: Shutdown Action in OutStream 
 */
#define CR_FW_OUTSTREAM_SHUTDOWNACTION {&CrFwOutStreamDefShutdownAction, \
							     	   &CrFwOutStreamStubShutdown, \
							     	   &CrFwOutStreamDefShutdownAction, \
									   &CrFwOutStreamDefShutdownAction, \
									   &CrFwOutStreamSocketShutdownAction, \
								       &CrFwClientSocketShutdownAction, \
								       &CrFwServerSocketShutdownAction}

#endif /* CR_FW_OUTSTREAM_USERPAR_H_ */
