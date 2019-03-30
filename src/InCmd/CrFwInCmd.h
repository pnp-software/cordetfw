/**
 * @file
 * @ingroup inMngGroup
 * Definition of the InCommand Component of the framework.
 *
 * An InCommand encapsulates an incoming command in a service provider application.
 * The InCommand is responsible for storing the attributes of an incoming command
 * and for executing the conditional checks and actions associated to the command.
 * The behaviour of an InCommand is defined by the InCommand State Machine
 * (see figure below) embedded within state CONFIGURED of a Base Component State
 * Machine.
 *
 * <b>Mode of Use of an InCommand Component</b>
 *
 * InCommands are created dynamically by the InLoader when it processes an incoming
 * packet which holds a command.
 * The InCommand component is created through a call to the factory function
 * <code>::CrFwInFactoryMakeInCmd</code>.
 * The InLoader loads the InCommand into an InManager who is then responsible for
 * executing it and, eventually, for returning it to the InFactory.
 *
 * An InCommand encapsulates an incoming command of a certain kind.
 * The "kind" of an incoming command is defined by the triplet:
 * [service type, service sub-type, discriminant].
 * InCommands are adapted to a certain incoming command kind by modifying one
 * or more of the following:
 * - The Validity Check Operation
 * - The Ready Check Operation
 * - The Start Action Operation
 * - The Progress Action Operation
 * - The Termination Action Operation
 * - The Abort Action Operation
 * .
 * These operations are statically defined for each kind of InCommand in
 * <code>CrFwInFactoryUserPar.h</code>.
 *
 * This header file defines default values for all configurable operations listed
 * above with the exception of the Configuration Check Operation for which the
 * default is the function <code>::CrFwBaseCmpDefConfigCheck</code>.
 *
 * @image html InCommand.png
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

#ifndef CRFW_INCMD_H_
#define CRFW_INCMD_H_

/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwPrConstants.h"
/* Include configuration files */
#include "Pckt/CrFwPcktQueue.h"
#include "CrFwUserConstants.h"
/* Include framework files */
#include "CrFwConstants.h"

/**
 * Return the base InCommand from which all other InCommands are derived.
 * The base InCommand is a singleton.
 * The first time it is called, this function creates and configures the base InCommand instance.
 * Subsequent calls return this same instance.
 * This function is only intended to be used by the InFactory (see <code>CrFwInFactory.h</code>)
 * and should not be used by applications.
 * @return the singleton instance of the base InCommand
 */
FwSmDesc_t CrFwInCmdMakeBase();

/**
 * Send command Terminate to the argument InCommand.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 */
void CrFwInCmdTerminate(FwSmDesc_t smDesc);

/**
 * Return true if the argument InCommand is in state ACCEPTED.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return 1 if the argument InCommand is in state CONFIGURED, sub-state
 * ACCEPTED; 0 otherwise
 */
CrFwBool_t CrFwInCmdIsInAccepted(FwSmDesc_t smDesc);

/**
 * Return true if the argument InCommand is in state PROGRESS.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return 1 if the argument InCommand is in state CONFIGURED, sub-state
 * PROGRESS; 0 otherwise
 */
CrFwBool_t CrFwInCmdIsInProgress(FwSmDesc_t smDesc);

/**
 * Return true if the argument InCommand is in state TERMINATED.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return 1 if the argument InCommand is in state CONFIGURED, sub-state
 * TERMINATED; 0 otherwise
 */
CrFwBool_t CrFwInCmdIsInTerminated(FwSmDesc_t smDesc);

/**
 * Return true if the argument InCommand is in state ABORTED.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return 1 if the argument InCommand is in state CONFIGURED, sub-state
 * ABORTED; 0 otherwise
 */
CrFwBool_t CrFwInCmdIsInAborted(FwSmDesc_t smDesc);

/**
 * Configuration check for an InCommand.
 * This function executes the Validity Check of the InCommand and sets the
 * action outcome to 1 if the Validity Check returns true and sets it to
 * zero if it returns false.
 * This function is only intended to be used by the InFactory (see <code>CrFwInFactory.h</code>)
 * and should not be used by applications.
 * @param prDesc the descriptor of the InCommand Configuration Procedure
 */
void CrFwInCmdConfigCheck(FwPrDesc_t prDesc);

/**
 * Return the progress step identifier of the InCommand.
 * The progress step identifier is a non-negative integer which identifies the
 * current progress step of the InCommand.
 * A Progress Step is a set of logically related execution steps of the InCommand
 * which are executed in sequence.
 *
 * At framework level, the Progress Step Identifier is initialized to 0 and
 * is never updated afterwards.
 * Applications would normally set its initial value in the Start Action and
 * would increment its value in the Progress Action.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return the progress step
 */
CrFwProgressStepId_t CrFwInCmdGetProgressStepId(FwSmDesc_t smDesc);

/**
 * Set the progress step identifier of the InCommand.
 * This function would typically be used by the InCommand's Start Action to initialize
 * the progress step identifier and by the Progress Action to update its value.
 *
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @param stepId the step identifier
 */
void CrFwInCmdSetProgressStepId(FwSmDesc_t smDesc, CrFwProgressStepId_t stepId);

/**
 * Return the Completion Outcome of the progress action.
 * The progress action is executed in steps.
 * If the completion outcome is set to 0, then at least one more execution
 * step must be run before the progress action can be deemed to be completed.
 * If, instead, the completion outcome is set to 1,
 * then the most recently executed step was
 * the last step and the progress action is completed.
 *
 * At framework level, the Completion Outcome is initialized to 1 and
 * is never updated afterwards.
 * This means that, by default, the progress action of an incoming command is completed
 * in one single execution step.
 * Applications would normally set the Completiong Outcome in the Progress Action.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return the completion outcome
 */
CrFwBool_t CrFwInCmdIsProgressActionCompleted(FwSmDesc_t smDesc);

/**
 * Set the Completion Outcome of the progress action.
 * This function would typically be used by the InCommand's Progress Action.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @param progressActionCompleted the completion outcome
 */
void CrFwInCmdSetProgressActionCompleted(FwSmDesc_t smDesc, CrFwBool_t progressActionCompleted);

/**
 * Return the number of progress step failures.
 * A progress step failure occurs when the progress action is executed and it returns
 * with the outcome of "failed" (see <code>::CrFwInCmdProgressAction_t<.code>).
 * Normally, a progress step failure should only be reported at the end of a progress step.
 * but this constraint is not enforced by the framework.
 * It is the responsibility of the application to update the progress step identifier when
 * a progress step has failed.
 *
 * The number of progress steps which failed is initialized to zero when the InCommand is
 * instantiated and is incremented by 1 every time a progress step has a "failed" outcome.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return the number of progress steps which have failed.
 */
CrFwProgressStepId_t CrFwInCmdGetNOfProgressFailure(FwSmDesc_t smDesc);

/**
 * Return the source of the InCommand.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return the source of the InCommand
 */
CrFwDestSrc_t CrFwInCmdGetSrc(FwSmDesc_t smDesc);

/**
 * Return the group of the InCommand.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return the group of the InCommand
 */
CrFwGroup_t CrFwInCmdGetGroup(FwSmDesc_t smDesc);

/**
 * Return the type of the InCommand.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return the type of the InCommand
 */
CrFwServType_t CrFwInCmdGetServType(FwSmDesc_t smDesc);

/**
 * Return the sub-type of the InCommand.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return the sub-type of the InCommand
 */
CrFwServType_t CrFwInCmdGetServSubType(FwSmDesc_t smDesc);

/**
 * Return the discriminant of the InCommand.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return the discriminant of the InCommand
 */
CrFwDiscriminant_t CrFwInCmdGetDiscriminant(FwSmDesc_t smDesc);

/**
 * Return the acknowledge level for command acceptance for the command encapsulated in the
 * InCommand.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return 1 if command acceptance is to be acknowledged, 0 otherwise.
 */
CrFwBool_t CrFwInCmdIsAcceptAck(FwSmDesc_t smDesc);

/**
 * Return the acknowledge level for command start for the command encapsulated in the
 * InCommand.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return 1 if command start is to be acknowledged, 0 otherwise.
 */
CrFwBool_t CrFwInCmdIsStartAck(FwSmDesc_t smDesc);

/**
 * Return the acknowledge level for command progress for the command encapsulated in the
 * InCommand.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return 1 if command progress is to be acknowledged, 0 otherwise.
 */
CrFwBool_t CrFwInCmdIsProgressAck(FwSmDesc_t smDesc);

/**
 * Return the acknowledge level for command termination for the command encapsulated in the
 * InCommand.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return 1 if command termination is to be acknowledged, 0 otherwise.
 */
CrFwBool_t CrFwInCmdIsTermAck(FwSmDesc_t smDesc);

/**
 * Return the sequence counter of the InCommand.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return the sequence counter of the InCommand
 */
CrFwSeqCnt_t CrFwInCmdGetSeqCnt(FwSmDesc_t smDesc);

/**
 * Return the start address of the parameter area of the InCommand.
 * The InCommand is encapsulated in a packet.
 * The parameter area of the InCommand is the part of the packet which is reserved to the
 * storage of the parameters of the InCommand.
 * The parameter area consists of an uninterrupted sequence of bytes.
 * The size of the parameter area is returned by function <code>::CrFwInCmdGetParLength</code>.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return the start address of the InCommand parameter area.
 */
CrFwPckt_t CrFwInCmdGetParStart(FwSmDesc_t smDesc);

/**
 * Return the pointer to the packet which holds the InCommand.
 * The InCommand is encapsulated in a packet.
 * This function returns this packet.
 * The packet is only initialized if the InCommand has been correctly de-serialized.
 * This is normally the case if the InCommand has been successfully returned by the InFactory.
 * The length of the packet is stored in the packet itself and can be retrieved
 * with function <code>::CrFwPcktGetLength</code>.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return the pointer to the packet holding the InCommand.
 */
CrFwPckt_t CrFwInCmdGetPckt(FwSmDesc_t smDesc);

/**
 * Return the length in bytes of the parameter area of the InCommand.
 * The InCommand is encapsulated in a packet.
 * The parameter area of the InCommand is the part of the packet which is reserved to the
 * storage of the parameters of the InCommand.
 * The parameter area consists of an uninterrupted sequence of bytes.
 * The start address of the parameter area is returned by function <code>::CrFwInCmdGetParStart</code>.
 * @param smDesc the descriptor of the Base State Machine of the InCommand
 * @return the length in bytes of the InCommand parameter area
 */
CrFwPcktLength_t CrFwInCmdGetParLength(FwSmDesc_t smDesc);

/**
 * Convenience function to extract the InCommand's packet from the descriptor
 * of the InCommand's reset procedure.
 *
 * One situation where this function is useful is as follows.
 * One of the adaptation points of an InCommand is its Validity Check Operation.
 * The Validity Check Operation is implemented by a function of type
 * <code>::CrFwInRepValidityCheck_t</code>.
 * This function takes as an argument the descriptor of the InCommand's Reset Procedure.
 * Applications will often have to provide an implementation of this function
 * and, to do so, they will often need to access the packet holding the InCommand so
 * as to access the InCommand's parameters,
 * The present function offers an easy way to retrieve this packet.
 *
 * @param prDesc the descriptor of the InCommand's Reset Procedure
 * @return the packet holding the InCommand
 */
CrFwPckt_t CrFwInCmdGetPcktFromPrDesc(FwPrDesc_t prDesc);

/**
 * Default implementation of the validity check of an InCommand.
 * The validity check of an InCommand must conform to the <code>::CrFwInCmdValidityCheck_t</code>
 * function prototype.
 * This default implementation verifies the correctness of the CRC of the packet
 * which carries the command.
 * The CRC is processed using the CRC functions defined by interface
 * <code>::CrFwInPckt.h</code>.
 *
 * @param prDesc the descriptor of the InCommand's Reset Procedure
 * @return true if the CRC of the InCommand packet is correct
 */
CrFwBool_t CrFwInCmdDefValidityCheck(FwPrDesc_t prDesc);

#endif /* CRFW_INCMD_H_ */
