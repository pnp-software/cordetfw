/**
 * @file
 * @ingroup crOpenIfGroup
 * Interface for reporting the outcome of the processing of an InCommand.
 * The InCommand arrives at the framework interface as a packet.
 * Its processing can have one of the following outcomes:
 * - Creation Failure: the InCommand cannot be created because there aren't
 *   enough memory resources
 * - Load Failure: the InCommand cannot be loaded in its InManager because
 *   the InManager's queue is full
 * - Acceptance Failure: the command has failed its Acceptance Check
 * - Acceptance Success: the command has been accepted
 * - Start Failure: the Start Action of the command has failed
 * - Start Success: the Start Action of the command has been successful
 * - Progress Failure: the Progress Action of the command has failed
 * - Progress Success: the Progress Action of the command has been successful
 * - Termination Failure: the Termination Action of the command has failed
 * - Termination Success: the Termination Action of the command has been successful
 * .
 * The command outcome is reported either by the InLoader or by the InCommand itself.
 * This interface declares functions through which these components can report the
 * outcome of an InCommand.
 *
 * The InCommand outcome report generated by the functions declared in this file
 * is defined by the following attributes:
 * - The outcome type: a positive integer which identifies the type of
 *   outcome.
 * - The instance identifier: the instance identifier of the InCommand whose
 *   outcome is being reported.
 * - The service type: the service type of the InCommand whose
 *   outcome is being reported.
 * - The service sub-type: the service sub-type of the InCommand whose
 *   outcome is being reported.
 * - The discriminant: the discriminant of the InCommand whose
 *   outcome is being reported.
 * - The failure code: an integer parameter which identifies the type of failure
 *   (only applicable for 'failed' outcomes).
 * - The InCommand component representing the command whose outcome is being reported
 * - The packet carrying the InCommand (only for the case that the InCommand could not
 *   be created).
 * .
 * In general, the implementation of this interface is entirely application-specific
 * but a simple default implementation is provided in <code>CrFwInCmdOutcome.c</code>.
 * This default implementation is primarily intended for testing and demonstration
 * purposes.
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

#ifndef CRFW_REPINCMDOUTCOME_H_
#define CRFW_REPINCMDOUTCOME_H_

/* Include Framework Files */
#include "CrFwConstants.h"
/* Include Configuration Files */
#include "CrFwUserConstants.h"

/**
 * Enumerated type for the outcome of the processing of an incoming command.
 * An incoming command goes through several processing stages.
 * At the end of each stage, an outcome report is generated by either function
 * <code>::CrFwRepInCmdOutcome</code> or <code>::CrFwRepInCmdOutcomeCreFail</code>.
 * The outcome of the processing of the incoming command is determined as follows:
 * - The InLoader (see <code>CrFwBaseCmp.h</code>) receives the packet encapsulating the
 *   incoming command and attempts to create an InCommand component to hold the command.
 *   If the attempt fails (either because there are not enough resources to build the
 *   InCommand or because its type/sub-type/discriminant are not recognized), the
 *   processing of the InCommand is terminated with outcome "Creation Failure"
 * - If the InCommand was successfully created, the InLoader checks whether the InCommand
 *   was successfully configured. If this is not the case (because its content was invalid),
 *   its processing is terminated with outcome "Acceptance Failure".
 * - If the InCommand was successfully configured, the InLoader attempts to load it in an
 *   InManager (see <code>CrFwInManager.h</code>). If the load operation fails, the
 *   processing of the InCommand is terminaed with outcome "Load Failure".
 *   If, instead, the load operation succeeds, the outcome report "Acceptance Success"
 *   is generated.
 * - When the execution of the InCommand starts, the InCommand performs a Start Check
 *   for the InCommand (see <code>CrFwInCmd.h</code>). Depending on the success or failure
 *   of this Start Check, an outcome of either "Start Success" or "Start Failure" is generated
 *   by the InCommand component.
 * - When the execution of a step of the InCommand is completed, an outcome of either
 *   "Progress Success" or "Progress Failure" is generated by the InCommand component.
 * - When the execution of a the InCommand has terminated, an outcome of either
 *   "Termination Success" or "Termination Failure" is generated by the InCommand component.
 * .
 */
typedef enum {
	/** Acceptance failure */
	crCmdAckAccFail = 1,
	/** Acceptance success */
	crCmdAckAccSucc = 2,
	/** Start failure */
	crCmdAckStrFail = 3,
	/** Start success */
	crCmdAckStrSucc = 4,
	/** Progress failure */
	crCmdAckPrgFail = 5,
	/** Progress success */
	crCmdAckPrgSucc = 6,
	/** Termination failure */
	crCmdAckTrmFail = 7,
	/** Termination success */
	crCmdAckTrmSucc = 8,
	/** Creation failure */
	crCmdAckCreFail = 9,
	/** Load failure */
	crCmdAckLdFail = 10
} CrFwRepInCmdOutcome_t;

/**
 * Report the outcome of the processing of an InCommand.
 * The last parameter of this function is the InCommand whose outcome is being reported.
 * This is a pointer variable. The owner of the pointer is the caller of the function.
 * The function can use it in read-only mode to access the values of the command parameters.
 *
 * @param outcome the outcome of the InCommand processing
 * @param instanceId the instance identifier of the InCommand
 * @param servType the service type of the InCommand
 * @param servSubType the service sub-type of the InCommand
 * @param disc the discriminant of the InCommand
 * @param failCode the failure code (don't care in case of a "successful" outcome)
 * @param inCmd the InCommand component whose outcome is being reported
 */
void CrFwRepInCmdOutcome(CrFwRepInCmdOutcome_t outcome, CrFwInstanceId_t instanceId, CrFwServType_t servType,
                         CrFwServSubType_t servSubType, CrFwDiscriminant_t disc, CrFwOutcome_t failCode, FwSmDesc_t inCmd);

/**
 * Report the a "creation failure" outcome for the processing of a packet carrying an InCommand.
 * The "creation failure" outcome is declared when a packet carrying an InCommand is received
 * but it is not possible to create an InCommand component to encapsulate it.
 * The failure to create the InCommand may be due either to a lack of resources in the application or to
 * the fact that the command kind as given by its [type, sub-type, discriminant] is illegal.
 * The last parameter of this function is the packet which carries the incoming command for which no InCommand
 * component could be created.
 * This is a pointer variable. The owner of the pointer is the caller of the function.
 * The function can use it in read-only mode to access the values of the command parameters.
 *
 * @param outcome the outcome of the packet processing (always equal to crCmdAckCreFail in
 *                this version of the framework)
 * @param failCode the failure code
 * @param pckt the packet carrying the InCommand
 */
void CrFwRepInCmdOutcomeCreFail(CrFwRepInCmdOutcome_t outcome, CrFwOutcome_t failCode, CrFwPckt_t pckt);

#endif /* CRFW_REPINCMDOUTCOME_H_ */
