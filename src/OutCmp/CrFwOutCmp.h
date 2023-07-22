/**
 * @file
 * @ingroup outMngGroup
 * Definition of the OutComponent Component of the framework.
 *
 * An OutComponent encapsulates an out-going command or an out-going report.
 * The OutComponent is responsible for serializing the out-going command or report
 * to a packet and sending the packet to an OutStream for dispatching to its
 * destination.
 * The behaviour of an OutComponent is defined by the OutComponent State Machine
 * embedded in the CONFIGURED state of the Base State Machine and
 * by the Send Packet Procedure (see figures below).
 *
 * <b>Mode of Use of an OutComponent Component</b>
 *
 * Applications create OutComponents dynamically through calls to the factory
 * function <code>::CrFwOutFactoryMakeOutCmp</code>.
 * OutComponents thus returned are expected to be in state CREATED (if this
 * is not the case - perhaps because the OutComponent's configuration action
 * has failed to complete successfully - the OutComponent will remain permanently
 * pending and will never be sent to its destination).
 *
 * An OutComponent is used to encapsulate an out-going command or report of
 * a certain kind.
 * The "kind" of an out-going command or report is defined by the triplet:
 * [service type, service sub-type, discriminant].
 * OutComponents are adapted to a certain kind of out-going report or command
 * by modifying one or more of the following:
 * - The Enable Check Operation
 * - The Ready Check Operation
 * - The Repeat Check Operation
 * - The Update Action Operation
 * - The Serialize Operation
 * .
 * These operations are statically defined for each kind of OutComponent in
 * <code>CrFwOutFactoryUserPar.h</code>.
 *
 * This header file defines default values for all configurable operations listed
 * above.
 * The default implementations for the Enable Check, Ready Check and Repeat Check will
 * often be suitable for many kinds of out-going reports or commands but
 * dedicated implementations of the Serialize and Update Action will probably have to
 * be provided for application-specific out-going reports or commands.
 *
 * @image html OutComponent.png
 * <center>-</center>
 * @image html SendPacket.png
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

#ifndef CRFW_OUTCMP_H_
#define CRFW_OUTCMP_H_

/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwPrConstants.h"
/* Include configuration files */
#include "Pckt/CrFwPcktQueue.h"
#include "CrFwUserConstants.h"
/* Include framework files */
#include "OutRegistry/CrFwOutRegistry.h"
#include "CrFwConstants.h"

/**
 * Return the base OutComponent from which all other OutComponents are derived.
 * The base OutComponent is a singleton.
 * The first time it is called, this function creates and configures the base OutComponent instance.
 * Subsequent calls return this same instance.
 * This function is only intended to be used by the OutFactory (see <code>CrFwOutFactory.h</code>)
 * and should not be used by applications.
 * @return the singleton instance of the base OutComponent
 */
FwSmDesc_t CrFwOutCmpMakeBase();

/**
 * Send command Terminate to the argument OutComponent.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 */
void CrFwOutCmpTerminate(FwSmDesc_t smDesc);

/**
 * Return true if the argument OutComponent is in state LOADED.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @return 1 if the argument OutComponent is in state CONFIGURED, sub-state
 * LOADED; 0 otherwise
 */
CrFwBool_t CrFwOutCmpIsInLoaded(FwSmDesc_t smDesc);

/**
 * Return true if the argument OutComponent is in state ABORTED.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @return 1 if the argument OutComponent is in state CONFIGURED, sub-state
 * ABORTED; 0 otherwise
 */
CrFwBool_t CrFwOutCmpIsInAborted(FwSmDesc_t smDesc);

/**
 * Return true if the argument OutComponent is in state PENDING.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @return 1 if the argument OutComponent is in state CONFIGURED, sub-state
 * PENDING; 0 otherwise
 */
CrFwBool_t CrFwOutCmpIsInPending(FwSmDesc_t smDesc);

/**
 * Return true if the argument OutComponent is in state TERMINATED.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @return 1 if the argument OutComponent is in state CONFIGURED, sub-state
 * TERMINATED; 0 otherwise
 */
CrFwBool_t CrFwOutCmpIsInTerminated(FwSmDesc_t smDesc);

/**
 * Default implementation of the Enable Check Operation for an OutComponent.
 * This function retrieves the enable status of the OutComponent from the OutRegistry
 * (see <code>::CrFwOutRegistryIsEnabled</code>).
 *
 * This function should never be directly called by the end-application.
 * It is declared as a public function so that it may be used in application-specific
 * Enable Check Operations.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent.
 * @return 1 if the OutComponent is enabled, 0 if it is not enabled.
 */
CrFwBool_t CrFwOutCmpDefEnableCheck(FwSmDesc_t smDesc);

/**
 * Default implementation of the Serialize Operation for an OutComponent.
 * This implementation writes to the packet encapsulated in the OutComponent all the
 * following attributes of the out-going report or command:
 * - The command or report identifier (this is set equal to the instance identifier
 *   of the OutComponent)
 * .
 * This function should never be directly called by the end-application.
 * It is declared as a public function so that it may be used in application-specific
 * Serialize Operations.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent.
 */
void CrFwOutCmpDefSerialize(FwSmDesc_t smDesc);

/**
 * Return the destination of the OutComponent.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @return the destination of the OutComponent
 */
CrFwDestSrc_t CrFwOutCmpGetDest(FwSmDesc_t smDesc);

/**
 * Set the destination of the OutComponent.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @param dest the destination of the OutComponent
 */
void CrFwOutCmpSetDest(FwSmDesc_t smDesc, CrFwDestSrc_t dest);

/**
 * Return the group of the OutComponent.
 * By default, the group of an OutComponent is set when the OutComponent is created
 * by function <code>::CrFwOutFactoryMakeOutCmp</code> but its value can be overridden
 * with function <code>::CrFwOutCmpSetGroup</code>.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @return the group of the OutComponent
 */
CrFwGroup_t CrFwOutCmpGetGroup(FwSmDesc_t smDesc);

/**
 * Set the group of the OutComponent.
 * By default, the group of an OutComponent is set when the OutComponent is created
 * by function <code>::CrFwOutFactoryMakeOutCmp</code> but its value can be overridden
 * with this function.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @param group the group
 */
void CrFwOutCmpSetGroup(FwSmDesc_t smDesc, CrFwGroup_t group);

/**
 * Return the time stamp attribute of the OutComponent.
 * By default, the time stamp is set when the OutComponent is loaded into the OutLoader
 * (see <code>::CrFwOutLoaderLoad</code>) but its value can be overridden with
 * function <code>::CrFwOutCmpSetTimeStamp</code>.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @return the time stamp attribute of the OutComponent
 */
CrFwTimeStamp_t CrFwOutCmpGetTimeStamp(FwSmDesc_t smDesc);

/**
 * Set the time stamp attribute of the OutComponent.
 * By default, the time stamp is set when the OutComponent is loaded into the OutLoader
 * (see <code>::CrFwOutLoaderLoad</code>).
 * This function can be used to override this default setting.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @param timeStamp the time stamp of the OutComponent
 */
void CrFwOutCmpSetTimeStamp(FwSmDesc_t smDesc, CrFwTimeStamp_t timeStamp);

/**
 * Return the source of the OutComponent.
 * The source of the OutComponent is set when the OutComponent is
 * created by function <code>::CrFwOutFactoryMakeOutCmp</code> and cannot be changed
 * afterwards.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @return the source of the OutComponent
 */
CrFwDestSrc_t CrFwOutCmpGetSrc(FwSmDesc_t smDesc);

/**
 * Return the type of the OutComponent.
 * The type of the OutComponent is set when the OutComponent is
 * created by function <code>::CrFwOutFactoryMakeOutCmp</code> and cannot be changed
 * afterwards.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @return the type of the OutComponent
 */
CrFwServType_t CrFwOutCmpGetServType(FwSmDesc_t smDesc);

/**
 * Return the sub-type of the OutComponent.
 * The sub-type of the OutComponent is set when the OutComponent is
 * created by function <code>::CrFwOutFactoryMakeOutCmp</code> and cannot be changed
 * afterwards.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @return the sub-type of the OutComponent
 */
CrFwServType_t CrFwOutCmpGetServSubType(FwSmDesc_t smDesc);

/**
 * Return the discriminant of the OutComponent.
 * The discriminant of the OutComponent is set when the OutComponent is
 * created by function <code>::CrFwOutFactoryMakeOutCmp</code> but
 * can subsequently be changed through function
 * <code>::CrFwOutCmpSetDiscriminant</code>.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @return the discriminant of the OutComponent
 */
CrFwDiscriminant_t CrFwOutCmpGetDiscriminant(FwSmDesc_t smDesc);

/**
 * Set the discriminant of the OutComponent.
 * The default value of the discriminant of the OutComponent is set when the OutComponent
 * is created by function <code>::CrFwOutFactoryMakeOutCmp</code>.
 * This function allows this default value to be changed.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @param discriminant the discriminant of the OutComponent
 */
void CrFwOutCmpSetDiscriminant(FwSmDesc_t smDesc, CrFwDiscriminant_t discriminant);

/**
 * Set the acknowledge level for the command encapsulated in the OutComponent.
 * This function should only be called on OutComponents which encapsulate an
 * out-going command (but no check is performed that this is actually the
 * case).
 * @param smDesc the descriptor of the Base State Machine of the OutComponent.
 * @param accept 1 if acknowledge of command acceptance is desired, 0 otherwise.
 * @param start 1 if acknowledge of command start is desired, 0 otherwise.
 * @param progress 1 if acknowledge of command progress is desired, 0 otherwise.
 * @param term 1 if acknowledge of command acceptance termination is desired, 0 otherwise.
 */
void CrFwOutCmpSetAckLevel(FwSmDesc_t smDesc, CrFwBool_t accept, CrFwBool_t start,
                           CrFwBool_t progress, CrFwBool_t term);

/**
 * Return the acknowledge level for command acceptance for the command encapsulated in the
 * OutComponent.
 * If the OutComponent does not hold a command, the behaviour of the function is undefined.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent.
 * @return 1 if command acceptance is to be acknowledged, 0 otherwise.
 */
CrFwBool_t CrFwOutCmpIsAcceptAck(FwSmDesc_t smDesc);

/**
 * Return the acknowledge level for command start for the command encapsulated in the
 * OutComponent.
 * If the OutComponent does not hold a command, the behaviour of the function is undefined.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent.
 * @return 1 if command start is to be acknowledged, 0 otherwise.
 */
CrFwBool_t CrFwOutCmpIsStartAck(FwSmDesc_t smDesc);

/**
 * Return the acknowledge level for command progress for the command encapsulated in the
 * OutComponent.
 * If the OutComponent does not hold a command, the behaviour of the function is undefined.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent.
 * @return 1 if command progress is to be acknowledged, 0 otherwise.
 */
CrFwBool_t CrFwOutCmpIsProgressAck(FwSmDesc_t smDesc);

/**
 * Return the acknowledge level for command termination for the command encapsulated in the
 * OutComponent.
 * If the OutComponent does not hold a command, the behaviour of the function is undefined.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent.
 * @return 1 if command termination is to be acknowledged, 0 otherwise.
 */
CrFwBool_t CrFwOutCmpIsTermAck(FwSmDesc_t smDesc);

/**
 * Return the start address of the parameter area of the OutComponent.
 * The OutComponent is encapsulated in a packet.
 * The parameter area of the OutComponent is the part of the packet which is reserved to the
 * storage of the parameters of the OutComponent.
 * The parameter area consists of an uninterrupted sequence of bytes.
 * The size of the parameter area is returned by function <code>::CrFwOutCmpGetParLength</code>.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @return the start address of the OutComponent parameter area.
 */
CrFwPckt_t CrFwOutCmpGetParStart(FwSmDesc_t smDesc);

/**
 * Return the length in bytes of the parameter area of the OutComponent.
 * The OutComponent is encapsulated in a packet.
 * The parameter area of the OutComponent is the part of the packet which is reserved to the
 * storage of the parameters of the OutComponent.
 * The parameter area consists of an uninterrupted sequence of bytes.
 * The start address of the parameter area is returned by function <code>::CrFwOutCmpGetParStart</code>.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @return the length in bytes of the OutComponent parameter area
 */
CrFwPcktLength_t CrFwOutCmpGetParLength(FwSmDesc_t smDesc);

/**
 * Return the length in bytes of the packet to which the OutComponent is serialized.
 * The length returned by this function covers both the packet header and the packet parameter area.
 * The length of the packet parameter area is returned by function <code>::CrFwOutCmpGetParLength</code>.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @return the length in bytes of the OutComponent packet
 */
CrFwPcktLength_t CrFwOutCmpGetLength(FwSmDesc_t smDesc);

/**
 * Return the pointer to the packet which holds the OutComponent.
 * The OutComponent is encapsulated in a packet.
 * This function returns this packet.
 * The packet is only initialized if the OutComponent has been correctly configured.
 * This is normally the case if the OutComponent has been successfully returned by the OutFactory.
 * The length of the packet is stored in the packet itself and can be retrieved
 * with function <code>::CrFwPcktGetLength</code>.
 * @param smDesc the descriptor of the Base State Machine of the OutComponent
 * @return the pointer to the packet holding the OutComponent.
 */
CrFwPckt_t CrFwOutCmpGetPckt(FwSmDesc_t smDesc);

#endif /* CRFW_OUTCMP_H_ */
