/**
 * @file
 * Header file to define all invariant publicly available constants and types for the CORDET Framework.
 * The invariant constants and types are those which are not intended to be
 * modified by the user during the framework instantiation process.
 * User-configurable constant and types are defined in <code>CrFwUserConstants.h</code>.
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

#ifndef CRFW_CONSTANTS_H_
#define CRFW_CONSTANTS_H_

#include "FwPrConstants.h"
#include "FwSmConstants.h"
#include "CrFwUserConstants.h"

/** A macro that can be used to specify that a function parameter is not used */
#define CRFW_UNUSED(x) (void)(x);

/** Type used for boolean values (1 represent "true" and 0 represents "false"). */
typedef int CrFwBool_t;

/** Type for the index of a command or report in the InRegistry or OutRegistry. */
typedef unsigned short CrFwCmdRepIndex_t;

/** Type for packets (see <code>CrFwPckt.h</code>). Packets are treated as arrays of bytes. */
typedef char* CrFwPckt_t;

/** Enumerated type for command and reports */
typedef enum {
	/** Command type */
	crCmdType = 1,
	/** Report type */
	crRepType = 2
} CrFwCmdRepType_t;

/**
 * Type for a pointer to a function implementing the Update Action Operation for
 * an InReport.
 * The Update Action Operation is one of the adaptation points of the framework.
 * A function which implements this operation takes the descriptor of the
 * Execution Procedure of the InReport as an argument and returns <code>void</code>.
 *
 * The packet holding the InReport can be retrieved as follows from the Execution
 * Procedure descriptor prDesc:
 * <pre>
 *     CrFwCmpData_t* cmpData = FwPrGetData(prDesc);
 *     CrFwInRepData_t* inRepData = (CrFwInRepData_t*)(cmpData->cmpSpecificData);
 *     CrFwPckt_t pckt = inRepData->pckt;
 * </pre>
 */
typedef void (*CrFwInRepUpdateAction_t)(FwPrDesc_t);

/**
 * Type for a pointer to a function implementing the Validity Check Operation for
 * an InReport.
 * The Validity Check Operation is one of the adaptation points of the framework.
 * The Validity Check Operation is called when an InReport is reset (i.e. it is
 * called from the Reset Procedure of the InReport).
 * It returns true if the data in the InReport are valid and false otherwise.
 *
 * A function which implements this operation takes the  descriptor of the
 * Reset Procedure of the InReport as an argument and returns true if the data in
 * the InReport packet are valid and returns false otherwise.
 *
 * The packet holding the InReport can be retrieved as follows from the Execution
 * Procedure descriptor prDesc:
 * <pre>
 *     CrFwCmpData_t* cmpData = FwPrGetData(prDesc);
 *     CrFwInRepData_t* inRepData = (CrFwInRepData_t*)(cmpData->cmpSpecificData);
 *     CrFwPckt_t pckt = inRepData->pckt;
 * </pre>
 */
typedef CrFwBool_t (*CrFwInRepValidityCheck_t)(FwPrDesc_t);

/**
 * Type for a pointer to a function implementing the Validity Check Operation for
 * an InCommand.
 * The Validity Check Operation is one of the adaptation points of the framework.
 * This operation is executed when the InCommand is reset.
 * It determines whether the InCommand reset was successful or not
 * (see <code>::CrFwInCmdConfigCheck</code>).
 *
 * A function which implements this operation takes as argument the descriptor
 * of the InCommand's reset procedure and returns true if
 * the data in the InCommand packet are valid and returns false otherwise.
 * The packet holding the InCommand can be retrieved as follows from the descriptor
 * of the InCommand's Reset Procedure prDesc:
 * <pre>
 *     CrFwCmpData_t* cmpData = FwPrGetData(prDesc);
 *     CrFwInRepData_t* inCmdData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
 *     CrFwPckt_t pckt = inCmdpData->pckt;
 * </pre>
 * Alternatively, the packet can also be retrieved using
 * function <code>::CrFwInCmdGetPcktFromPrDesc</code>.
 */
typedef CrFwBool_t (*CrFwInCmdValidityCheck_t)(FwPrDesc_t);

/**
 * Type for a pointer to a function implementing the Ready Check Operation for an
 * InCommand.
 * The Ready Check Operation is one of the adaptation points of the framework.
 * A function which implements this operation takes the InCommand descriptor
 * as an argument and returns true if the command is ready to start execution and
 * false otherwise.
 */
typedef CrFwBool_t (*CrFwInCmdReadyCheck_t)(FwSmDesc_t);

/**
 * Type for a pointer to a function implementing the Start Action Operation for
 * an InCommand.
 * The Start Action Operation is one of the adaptation points of the framework.
 * A function which implements this operation takes the InCommand descriptor
 * as an argument and returns <code>void</code>.
 * The Start Action has an outcome which it records in field <code>outcome</code>
 * of <code>::CrFwCmpData_t</code>.
 * The outcome is either '1' (to signify that the action was successful) or
 * an integer different from '1' (to signify that the action failed --
 * in this case the outcome is a code which identifies the reason for the failure).
 * The success outcome of an InCommand is accessed with functions
 * <code>::CrFwSetSmOutcome</code> and <code>::CrFwGetSmOutcome</code>.
 */
typedef void (*CrFwInCmdStartAction_t)(FwSmDesc_t);

/**
 * Type for a pointer to a function implementing the Progress Action Operation for
 * an InCommand.
 * The Progress Action Operation is one of the adaptation points of the framework.
 * A function which implements this operation takes the InCommand descriptor
 * as an argument and returns <code>void</code>.
 *
 * The Progress Action has two outcomes: the <i>Completion Outcome</i> and the
 * <i>Success Outcome</i>.
 * The Completion Outcome is a boolean which indicates whether the progress action
 * is "completed" (to signify that no more executions of the Progress Action are
 * needed) or "not completed" (to signify that the Progress Action must be executed
 * again).
 * The Completion Outcome of an InCommand is accessed with functions
 * <code>::CrFwInCmdSetProgressActionCompleted</code> and
 * <code>::CrFwInCmdIsProgressActionCompleted</code>.
 *
 * The success outcome is either '1' (to signify that the execution of the progress step has
 * been successful), or an integer different from '1' (to signify that the progress step failed
 *  -- in this case the outcome is a code which identifies the reason for the failure).
 * The success outcome of an InCommand is accessed with functions
 * <code>::CrFwSetSmOutcome</code> and <code>::CrFwGetSmOutcome</code>.
 */
typedef void (*CrFwInCmdProgressAction_t)(FwSmDesc_t);

/**
 * Type for a pointer to a function implementing the Termination Action Operation for
 * an InCommand.
 * The Termination Action Operation is one of the adaptation points of the framework.
 * A function which implements this operation takes the InCommand descriptor
 * as an argument and returns <code>void</code>.
 * The Termination Action has an outcome which it records in field <code>outcome</code>
 * of <code>::CrFwCmpData_t</code>.
 * The outcome is either '1' (to signify that the action was successful) or
 * an integer different from '1' (to signify that the action failed --
 * in this case the outcome is a code which identifies the reason for the failure).
 * The success outcome of an InCommand is accessed with functions
 * <code>::CrFwSetSmOutcome</code> and <code>::CrFwGetSmOutcome</code>.
 */
typedef void (*CrFwInCmdTerminationAction_t)(FwSmDesc_t);

/**
 * Type for a pointer to a function implementing the Abort Action Operation for
 * an InCommand.
 * The Abort Action Operation is one of the adaptation points of the framework.
 * A function which implements this operation takes the InCommand descriptor
 * as an argument and returns <code>void</code>.
 */
typedef void (*CrFwInCmdAbortAction_t)(FwSmDesc_t);

/**
 * Type for a pointer to a function implementing the Enable Check Operation for an
 * OutComponent.
 * The Enable Check Operation is one of the adaptation points of the framework.
 * A function which implements this operation takes the OutComponent descriptor
 * as an argument and returns true if the packet encapsulated by the OutComponent
 * is enabled and false otherwise.
 */
typedef CrFwBool_t (*CrFwOutCmpEnableCheck_t)(FwSmDesc_t);

/**
 * Type for a pointer to a function implementing the Ready Check Operation for an
 * OutComponent.
 * The Ready Check Operation is one of the adaptation points of the framework.
 * A function which implements this operation takes the OutComponent descriptor
 * as an argument and returns true if the packet encapsulated by the OutComponent
 * is ready to be sent out and false otherwise.
 */
typedef CrFwBool_t (*CrFwOutCmpReadyCheck_t)(FwSmDesc_t);

/**
 * Type for a pointer to a function implementing the Repeat Check Operation for an
 * OutComponent.
 * The Repeat Check Operation is one of the adaptation points of the framework.
 * A function which implements this operation takes the OutComponent descriptor
 * as an argument and returns true if the OutComponent must be sent to its destination
 * again and false otherwise.
 */
typedef CrFwBool_t (*CrFwOutCmpRepeatCheck_t)(FwSmDesc_t);

/**
 * Type for a pointer to a function implementing the Update Operation for an
 * OutComponent.
 * This operation is one of the adaptation points of the framework.
 * The operation updates the data which the OutComponent must carry to its
 * destination.
 * A function which implements this operation takes the OutComponent descriptor
 * as an argument and returns void.
 */
typedef void (*CrFwOutCmpUpdate_t)(FwSmDesc_t);

/**
 * Type for a pointer to a function implementing the Serialize Operation for an
 * OutComponent.
 * This operation serializes the OutComponent to the packet associated to the
 * OutComponent (see <code>::CrFwOutCmpData_t</code>).
 * A function which implements this operation takes the OutComponent descriptor
 * as an argument and returns void.
 */
typedef void (*CrFwOutCmpSerialize_t)(FwSmDesc_t);

/**
 * Type for a pointer to a function implementing the Packet Collect Operation of
 * an InStream.
 * The Packet Collect Operation is one of the adaptation points of the framework.
 * A function which implements this operation takes the packet source as its argument and
 * returns a packet collected from the middleware interface associated to the packet
 * source or NULL if no packet could be collected.
 * The packet returned by this function must be created through function
 * <code>::CrFwPcktMake</code> (release of the packet is the responsibility of the
 * user of the InStream).
 *
 * If there is a need to verify whether a packet is available for collection through
 * the Packet Collect Operation, this can be done using the Packet Available Check Operation.
 *
 */
typedef CrFwPckt_t (*CrFwPcktCollect_t)(CrFwDestSrc_t);

/**
 * Type for a pointer to a function implementing the Packet Available Check Operation
 * of an InStream.
 * The Packet Available Check Operation is one of the adaptation points of the framework.
 * A function which implements this operation takes the packet source as its argument and
 * returns 1 if a new packet is available at the middleware interface associated to the packet
 * source or 0 if no packet is available.
 * Hence, a return value of 1 implies that a call to the Packet Collect Operation will return
 * one packet.
 */
typedef CrFwBool_t (*CrFwPcktAvailCheck_t)(CrFwDestSrc_t);

/**
 * Type for a pointer to a function implementing the Packet Hand-Over Operation of
 * an OutStream.
 * The Packet Hand-Over Operation is one of the adaptation points of the framework.
 * A function which implements this operation takes the packet to be handed over
 * to the middleware as an argument and returns either 1 if the hand-over was successful
 * or 0 if the hand-over failed.
 *
 * The function must not modify the content of the packet.
 * The argument of the function is a pointer to the packet.
 * This pointer is "owned" by the caller and the function should not use after it has
 * returned.
 */
typedef CrFwBool_t (*CrFwPcktHandover_t)(CrFwPckt_t pckt);

/** Descriptor for a Packet Queue (PQ) in an OutStream or InStream. */
struct CrFwPcktQueue {
	/** The list of packets in the PQ. */
	CrFwPckt_t* pckt;
	/** The size of the PQ (the same as the size of the <code>pckt</code> array) */
	CrFwCounterU1_t size;
	/** The index of the oldest item in the PQ */
	CrFwCounterU1_t oldestItem;
	/** Index of the next free slot in the PQ. */
	CrFwCounterU1_t nextFreeItem;
	/** Flag indicating whether the PQ is empty */
	CrFwBool_t isEmpty;
};

/** Type used in the framework to represent a packet queue */
typedef struct CrFwPcktQueue* CrFwPcktQueue_t;

/**
 * InReport kind descriptor type.
 * An application supports a number of InReport kinds.
 * An instance of this type describes one of the InReport kinds supported by an application.
 */
typedef struct {
	/** The service type */
	CrFwServType_t servType;
	/** The service sub-type */
	CrFwServSubType_t servSubType;
	/** The discriminant value (or zero if no discriminant for this type/sub-type) */
	CrFwDiscriminant_t discriminant;
	/** The pointer to the function implementing the Update Action Operation */
	CrFwInRepUpdateAction_t updateAction;
	/** The pointer to the function implementing the Validity Check Operation */
	CrFwInRepValidityCheck_t isValid;
} CrFwInRepKindDesc_t;

/**
 * InCommand kind descriptor type.
 * An application supports a number of InCommand kinds.
 * An instance of this type describes one of the InCommand kinds supported by an application.
 */
typedef struct {
	/** The service type */
	CrFwServType_t servType;
	/** The service sub-type */
	CrFwServSubType_t servSubType;
	/** The discriminant value (or zero if no discriminant for this type/sub-type) */
	CrFwDiscriminant_t discriminant;
	/** The pointer to the function implementing the Validity Check Operation */
	CrFwInCmdValidityCheck_t isValid;
	/** The pointer to the function implementing the Ready Check Operation */
	CrFwInCmdReadyCheck_t isReady;
	/** The pointer to the function implementing the Start Action Operation */
	CrFwInCmdStartAction_t startAction;
	/** The pointer to the function implementing the Progress Action Operation */
	CrFwInCmdProgressAction_t progressAction;
	/** The pointer to the function implementing the Termination Action Operation */
	CrFwInCmdTerminationAction_t terminationAction;
	/** The pointer to the function implementing the Abort Action Operation */
	CrFwInCmdAbortAction_t abortAction;
} CrFwInCmdKindDesc_t;

/**
 * OutComponent kind descriptor type.
 * An application supports a number of OutComponent kinds.
 * An instance of this type describes one of the OutComponent kinds supported by an application.
 */
typedef struct {
	/** The service type */
	CrFwServType_t servType;
	/** The service sub-type */
	CrFwServSubType_t servSubType;
	/** The discriminant value (or zero if no discriminant for this type/sub-type) */
	CrFwDiscriminant_t discriminant;
	/** The command/report type of the out-going command or report */
	CrFwCmdRepType_t cmdRepType;
	/** The length of the packet attached to the OutComponent */
	CrFwPcktLength_t pcktLength;
	/** The pointer to the function implementing the Enable Check Operation */
	CrFwOutCmpEnableCheck_t isEnabled;
	/** The pointer to the function implementing the Ready Check Operation */
	CrFwOutCmpReadyCheck_t isReady;
	/** The pointer to the function implementing the Ready Check Operation */
	CrFwOutCmpRepeatCheck_t isRepeat;
	/** The pointer to the function implementing the Update Operation */
	CrFwOutCmpUpdate_t update;
	/** The pointer to the function implementing the Serialize Operation */
	CrFwOutCmpSerialize_t serialize;
} CrFwOutCmpKindDesc_t;

/**
 * Service descriptor type.
 * An application supports a number of service types and, for each service type, it supports
 * a number of sub-types.
 * An instance of this type describes one of the [service type, service sub-type] pairs supported
 * by an application together with a range of discriminant associated to them.
 */
typedef struct {
	/** The service type */
	CrFwServType_t servType;
	/** The service sub-type */
	CrFwServSubType_t servSubType;
	/** The lower bound of a range of discriminant values (or zero if no discriminant for this type/sub-type) */
	CrFwDiscriminant_t lowerBoundDisc;
    /** The upper bound of a range of discriminant values (or zero if no discriminant for this type/sub-type) */
    CrFwDiscriminant_t upperBoundDisc;
	/** Index of the next service type or zero when this is the last service type */
	CrFwCmdRepIndex_t nextServType;
	/** Number of discriminant values for this [type, sub-type] pair in the next row */
	CrFwBool_t isServTypeEnabled;
	/** The enable state for the service sub-type (see <code>CrFwOutRegistry.h</code>) */
	CrFwBool_t isServSubTypeEnabled;
	/**
	 * The enable state for the discriminants in the range [lowerBoundDisc,lowerBoundDisc].
	 * This is intended to be an array of bits such that each bit represents a discriminant
	 * value within the range [lowerBoundDisc,lowerBoundDisc].
	 * If the bit is equal to 1, the discriminant value is enabled; otherwise it is disabled.
	 */
	unsigned char* isDiscriminantEnabled;
} CrFwServDesc_t;

/** Type for the data describing an InManager */
typedef struct InManagerData {
	/** Pending Command/Report List (PCRL) for the InManager. */
	FwSmDesc_t* pcrl;
	/** Number of successfully loaded InReports and InCommands  */
	CrFwCounterU2_t nOfLoadedInCmp;
	/** Number of InReports and InCommands currently in PCRL */
	CrFwCounterU1_t nOfInCmpInPcrl;
	/**
	 * Next free position in the PCRL.
	 * This is the position at which the next InReport/InCommand loaded into the InManager
	 * will be inserted in the PCRL.
	 * If the PCRL is full, this field is equal to the PCRL size.
	 */
	CrFwCounterU1_t nextFreePcrlPos;
} CrFwInManagerData_t;

/** Type for the data describing an OutManager */
typedef struct OutManagerData {
	/** Pending OutComponent List (POCL) for the OutManager. */
	FwSmDesc_t* pocl;
	/** Number of successfully loaded OutComponents */
	CrFwCounterU2_t nOfLoadedOutCmp;
	/** Number of OutComponents currently in POCL */
	CrFwCounterU1_t nOfOutCmpInPocl;
	/**
	 * Next free position in the POCL.
	 * This is the position at which the next OutComponent loaded into the OutManager
	 * will be inserted in the POCL.
	 * If the POCL is full, this field is equal to the POCL size.
	 */
	CrFwCounterU1_t nextFreePoclPos;
} CrFwOutManagerData_t;

/** Type for the data describing an InLoader */
typedef struct InLoaderData {
	/** InStream from which packets are to be retrieved in the next execution cycle. */
	FwSmDesc_t inStream;
} CrFwInLoaderData_t;

/** Type for the data describing an InStream */
typedef struct InStreamData {
	/** Source associated to the InStream. */
	CrFwDestSrc_t src;
	/** Packet queue associated to the InStream. */
	struct CrFwPcktQueue pcktQueue;
	/** Array holding sequence counters for the groups associated to the InStream */
	CrFwSeqCnt_t* seqCnt;
	/** Function which implements the Packet Collect Operation. */
	CrFwPcktCollect_t collectPckt;
	/** Function which implements the Packet Available Check Operation. */
	CrFwPcktAvailCheck_t isPcktAvail;
	/** The last packet to have been collected from the middleware */
	CrFwPckt_t pckt;
} CrFwInStreamData_t;

/** Type for the data describing an OutStream */
typedef struct OutStreamData {
	/** Destination associated to the OutStream. */
	CrFwDestSrc_t dest;
	/** Packet queue associated to the OutStream. */
	struct CrFwPcktQueue pcktQueue;
	/** Array holding sequence counters for the groups associated to the OutStream */
	CrFwSeqCnt_t* seqCnt;
	/** Function which hands over a packet from the OutStream to the middleware. */
	CrFwPcktHandover_t handoverPckt;
	/** The packet to be sent out */
	CrFwPckt_t pckt;
} CrFwOutStreamData_t;

/** Type for the data describing an InCommand */
typedef struct InCmdData {
	/**
	 * Index of the position in the pool of pre-allocated InCommands in the InFactory
	 * to which the InComponent has been allocated
	 */
	CrFwInFactoryPoolIndex_t factoryPoolIndex;
	/**
	 * Index through which an InCommand is tracked by the InRegistry
	 * (see <code>CrFwInRegistry.h</code>)
	 */
	CrFwTrackingIndex_t trackingIndex;
	/** Function which implements the Configuration Check for the InCommand */
	CrFwInCmdValidityCheck_t isValid;
	/** Function which implements the Ready Check for the InCommand */
	CrFwInCmdReadyCheck_t isReady;
	/** Function which implements the Start Action for the InCommand */
	CrFwInCmdStartAction_t startAction;
	/** Function which implements the Progress Action for the InCommand */
	CrFwInCmdProgressAction_t progressAction;
	/** Function which implements the Termination Action for the InCommand */
	CrFwInCmdTerminationAction_t terminationAction;
	/** Function which implements the Abort Action for the InCommand */
	CrFwInCmdAbortAction_t abortAction;
	/** The progress step identifier **/
	CrFwProgressStepId_t progressStepId;
	/**
	 * Flag indicating whether the progress action has been completed.
	 * An InCommand sets the flag to false at entry in the PROGRESS state.
	 * The progress action must set it to true when all progress steps have
	 * been completed.
	 */
	CrFwBool_t isProgressActionCompleted;
    /** Number of progress steps which failed **/
	CrFwExecStepId_t nOfProgressFailure;
	/** Packet holding the InCommand */
	CrFwPckt_t pckt;
} CrFwInCmdData_t;

/** Type for the data describing an InReport */
typedef struct InRepData {
	/**
	 * Index of the position in the pool of pre-allocated InReports in the InFactory
	 * to which the InComponent has been allocated
	 */
	CrFwInFactoryPoolIndex_t factoryPoolIndex;
	/**
	 * Index through which an InReport is tracked by the InRegistry
	 * (see <code>CrFwInRegistry.h</code>)
	 */
	CrFwTrackingIndex_t trackingIndex;
	/** Function which implements the Validity Check for the InReport */
	CrFwInRepValidityCheck_t isValid;
	/** Function which implements the Update Action for the InReport */
	CrFwInRepUpdateAction_t updateAction;
	/** Packet holding the InReport */
	CrFwPckt_t pckt;
} CrFwInRepData_t;

/** Type for the data describing an OutComponent */
typedef struct OutCmpData {
	/** Index of out-going command or report (see <code>CrFwOutRegistry.h</code>) */
	CrFwCmdRepIndex_t index;
	/**
	 * Index of the position in the pool of pre-allocated OutComponents in the OutFactory
	 * to which the OutComponent has been allocated
	 */
	CrFwOutFactoryPoolIndex_t factoryPoolIndex;
	/**
	 * Index through which an out-going command or report is tracked by the OutRegistry
	 * (see <code>CrFwOutRegistry.h</code>)
	 */
	CrFwTrackingIndex_t trackingIndex;
	/** Function which implements the Enable Check for the out-going command or report */
	CrFwOutCmpEnableCheck_t isEnabled;
	/** Function which implements the Ready Check for the out-going command or report */
	CrFwOutCmpReadyCheck_t isReady;
	/** Function which implements the Repeat Check for the out-going command or report */
	CrFwOutCmpRepeatCheck_t isRepeat;
	/** Function which implements the Update Operation for the out-going command or report */
	CrFwOutCmpUpdate_t update;
	/** Function which implements the Serialization Operation for the out-going command or report */
	CrFwOutCmpSerialize_t serialize;
	/** Packet to which the out-going command or report is serialized */
	CrFwPckt_t pckt;
} CrFwOutCmpData_t;

/** Type identifier for the OutStream components */
#define CR_FW_OUTSTREAM_TYPE 1

/** Type identifier for the InStream components */
#define CR_FW_INSTREAM_TYPE 2

/** Type identifier for the OutComponent components */
#define CR_FW_OUTCMP_TYPE 3

/** Type identifier for the OutRegistry component */
#define CR_FW_OUTREGISTRY_TYPE 4

/** Type identifier for the OutFactory component */
#define CR_FW_OUTFACTORY_TYPE 5

/** Type identifier for the OutManager component */
#define CR_FW_OUTMANAGER_TYPE 6

/** Type identifier for the OutLoader component */
#define CR_FW_OUTLOADER_TYPE 7

/** Type identifier for the InFactory component */
#define CR_FW_INFACTORY_TYPE 8

/** Type identifier for the InReport component */
#define CR_FW_INREPORT_TYPE 9

/** Type identifier for the InCommand component */
#define CR_FW_INCOMMAND_TYPE 10

/** Type identifier for the OutRegistry component */
#define CR_FW_INREGISTRY_TYPE 11

/** Type identifier for the InManager component */
#define CR_FW_INMANAGER_TYPE 12

/** Type identifier for the InLoader component */
#define CR_FW_INLOADER_TYPE 13

/** Type identifier for the Application State Machine */
#define CR_FW_APP_TYPE 14

/* -------------------------------------------------------------------------------------------------- */

/** Maximum number of transition commands defined on a framework component or framework state machine */
#define CR_FW_MAX_NOF_TRANS_CMDS 4

/** State identifier for state CREATED in the Base State Machine. */
#define CR_FW_BASE_STATE_CREATED 1

/** State identifier for state INITIALIZED in the Base State Machine. */
#define CR_FW_BASE_STATE_INITIALIZED 2

/** State identifier for state CONFIGURED in the Base State Machine. */
#define CR_FW_BASE_STATE_CONFIGURED 3

/** Identifier for transition command "Init" in the Base State Machine. */
#define CR_FW_BASE_TR_INIT 1

/** Identifier for transition command "Reset" in the Base State Machine. */
#define CR_FW_BASE_TR_RESET 2

/** Identifier for transition command "Shutdown" in the Base State Machine. */
#define CR_FW_BASE_TR_SHUTDOWN 3

/** State identifier for state ACCEPTED in the InCommand State Machine. */
#define CR_FW_INCMD_STATE_ACCEPTED 1

/** State identifier for state PROGRESS in the InCommand State Machine. */
#define CR_FW_INCMD_STATE_PROGRESS 2

/** State identifier for state TERMINATED in the InCommand State Machine. */
#define CR_FW_INCMD_STATE_TERMINATED 3

/** State identifier for state ABORTED in the InCommand State Machine. */
#define CR_FW_INCMD_STATE_ABORTED 4

/** Identifier for transition command "Terminate" in the InCommand State Machine. */
#define CR_FW_INCMD_TR_TERMINATE CR_FW_INCOMMAND_TYPE*CR_FW_MAX_NOF_TRANS_CMDS+0

/** State identifier for state WAITING in the InStream State Machine. */
#define CR_FW_INSTREAM_STATE_WAITING 1

/** State identifier for state PCKT_AVAIL in the InStream State Machine. */
#define CR_FW_INSTREAM_STATE_PCKT_AVAIL 2

/** Identifier for transition command "GetPacket" in the InStream State Machine. */
#define CR_FW_INSTREAM_TR_GET_PCKT CR_FW_INSTREAM_TYPE*CR_FW_MAX_NOF_TRANS_CMDS+0

/** Identifier for transition command "PacketAvailable" in the InStream State Machine. */
#define CR_FW_INSTREAM_TR_PACKET_AVAILABLE CR_FW_INSTREAM_TYPE*CR_FW_MAX_NOF_TRANS_CMDS+1

/** State identifier for state LOADED in the OutComponent State Machine. */
#define CR_FW_OUTCMP_STATE_LOADED 1

/** State identifier for state ABORTED in the OutComponent State Machine. */
#define CR_FW_OUTCMP_STATE_ABORTED 2

/** State identifier for state PENDING in the OutComponent State Machine. */
#define CR_FW_OUTCMP_STATE_PENDING 3

/** State identifier for state TERMINATED the OutComponent State Machine. */
#define CR_FW_OUTCMP_STATE_TERMINATED 4

/** Identifier for transition command "Terminate" in the OutComponent State Machine. */
#define CR_FW_OUTCMP_TR_TERMINATE CR_FW_OUTCMP_TYPE*CR_FW_MAX_NOF_TRANS_CMDS+0

/** State identifier for state READY in the OutStream State Machine. */
#define CR_FW_OUTSTREAM_STATE_READY 1

/** State identifier for state INITIALIZED in the OutStream State Machine. */
#define CR_FW_OUTSTREAM_STATE_BUFFERING 2

/** Identifier for transition command "Send" in the OutStream State Machine. */
#define CR_FW_OUTSTREAM_TR_SEND CR_FW_OUTSTREAM_TYPE*CR_FW_MAX_NOF_TRANS_CMDS+0

/** Identifier for transition command "Reset" in the OutStream State Machine. */
#define CR_FW_OUTSTREAM_TR_CONNECTION_AVAILABLE CR_FW_OUTSTREAM_TYPE*CR_FW_MAX_NOF_TRANS_CMDS+1

#endif /* CRFW_CONSTANTS_H_ */
