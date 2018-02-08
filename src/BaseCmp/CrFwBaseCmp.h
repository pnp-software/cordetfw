/**
 * @file
 * @ingroup baseCmpGroup
 * Definition of Base Component.
 * A Base Component implements the behaviour of the Base State Machine
 * (see figures below).
 *
 * All components used in the framework are derived from the Base Component
 * (i.e. all framework components are implemented by state machines which are
 * derived from the Base State Machine).
 * Hence, all framework components inherit the behaviour of the Base
 * State Machine.
 *
 * The Base State Machine is a singleton.
 * This header file defines the operation to create and access this singleton
 * instance.
 *
 * A Base State Machine responds to three transition commands: Init,
 * Reset and Shutdown.
 * This header file defines functions to send these three commands to a Base Component
 * or to one of its derived components.
 *
 * The Base State Machine uses three procedures, the
 * Component Initialization Procedure, the Component Reset Procedure,
 * and the Component Execution Procedure.
 * The first two procedures are defined in <code>CrFwInitProc.h</code> and
 * <code>CrFwResetProc</code>.
 * The third procedure is defined as a dummy in <code>CrFwExecProc.h</code>.
 *
 * The Base Component defines the Instance Identifier and Type Identifier
 * attributes.
 * The Type Identifier identifies the type of a component.
 * The Instance Identifier identifies an instance within a type.
 * This module defines the functions to access the type and instance identifier of
 * a Base Component or of a component derived from a Base Component.
 *
 * @image html BaseSM.png
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

#ifndef CRFW_BASE_CMP_H_
#define CRFW_BASE_CMP_H_

/* Include FW Profile Files */
#include "FwSmConstants.h"
#include "FwPrConstants.h"
/* Include Framework Files */
#include "CrFwConstants.h"
/* Include Configuration Files */
#include "CrFwUserConstants.h"

/**
 * Retrieve the singleton instance of the Base State Machine.
 * The Base State Machine is a singleton.
 * The first time this function is called, it creates the Base State Machine.
 * Subsequently, it always returns the same instance.
 *
 * The first time this function is called, it returns the Base State Machine
 * in state STOPPED.
 * @return the descriptor of the Base State Machine or NULL
 * if the state machine could not be created.
 */
FwSmDesc_t CrFwBaseCmpMake();

/**
 * Initialize a framework component.
 * This function sends command Init to a Base State Machine.
 * This function can be used either on a Base State Machine or on a state
 * machine that has been derived from a Base State Machine.
 * @param smDesc the descriptor of the Base State Machine to be initialized.
 */
void CrFwCmpInit(FwSmDesc_t smDesc);

/**
 * Reset a framework component.
 * This function sends command Reset to a Base State Machine.
 * This function can be used either on a Base State Machine or on a state
 * machine that has been derived from a Base State Machine.
 * @param smDesc the descriptor of the Base State Machine to be reset.
 */
void CrFwCmpReset(FwSmDesc_t smDesc);

/**
 * Shutdown a framework component.
 * This function sends command Shutdown to a Base State Machine.
 * This function can be used either on a Base State Machine or on a state
 * machine that has been derived from a Base State Machine.
 * @param smDesc the descriptor of the Base State Machine to be shutdown.
 */
void CrFwCmpShutdown(FwSmDesc_t smDesc);

/**
 * Execute a framework component.
 * This function sends command Execute to a Base State Machine.
 * This function can be used either on a Base State Machine or on a state
 * machine that has been derived from a Base State Machine.
 * @param smDesc the descriptor of the Base State Machine to be executed.
 */
void CrFwCmpExecute(FwSmDesc_t smDesc);

/**
 * Function which performs the Shutdown Action for the Base State Machine.
 * This implementation of the Shutdown Action returns without doing anything.
 *
 * This action is an adaptation point of the framework.
 * Components which extend the Base Component may want to override this function
 * to implement their own shutdown behaviour.
 * @param smDesc the descriptor of the Base State Machine.
 */
void CrFwBaseCmpDefShutdownAction(FwSmDesc_t smDesc);

/**
 * Return the descriptor of the Initialization Procedure of the argument component.
 * Each component derived from the Base Component has an Initialization Procedure.
 * This function returns the descriptor of the Initialization Procedure of the
 * argument component.
 * @param smDesc the descriptor of the Base State Machine.
 * @return the descriptor of the Initialization Procedure
 */
FwPrDesc_t CrFwCmpGetInitPr(FwSmDesc_t smDesc);

/**
 * Return the descriptor of the Reset Procedure of the argument component.
 * Each component derived from the Base Component has a Reset Procedure.
 * This function returns the descriptor of the Reset Procedure of the
 * argument component.
 * @param smDesc the descriptor of the Base State Machine.
 * @return the descriptor of the Reset Procedure
 */
FwPrDesc_t CrFwCmpGetResetPr(FwSmDesc_t smDesc);

/**
 * Return the descriptor of the Execution Procedure of the argument component.
 * Each component derived from the Base Component has an Execution Procedure.
 * This function returns the descriptor of the Execution Procedure of the
 * argument component.
 * @param smDesc the descriptor of the Base State Machine.
 * @return the descriptor of the Reset Procedure
 */
FwPrDesc_t CrFwCmpGetExecPr(FwSmDesc_t smDesc);

/**
 * Return the instance identifier of the argument component.
 * Each component derived from the Base Component has an Instance Identifier
 * which identifies a certain instance of a component within all instances of
 * the same type.
 * This function returns the value of the Instance Identifier.
 * @param smDesc the descriptor of the Base State Machine.
 * @return the instance identifier
 */
CrFwInstanceId_t CrFwCmpGetInstanceId(FwSmDesc_t smDesc);

/**
 * Return the type identifier of the argument component.
 * Each component belongs to a type.
 * This function returns the value of the Type Identifier.
 * @param smDesc the descriptor of the Base State Machine.
 * @return the instance identifier
 */
CrFwTypeId_t CrFwCmpGetTypeId(FwSmDesc_t smDesc);

/**
 * Return true if the state machine of the argument component has been started.
 * This function checks whether the Base State Machine has been started.
 * This function can be used either on a Base State Machine or on a state
 * machine that has been derived from a Base State Machine.
 * @param smDesc the descriptor of the Base State Machine.
 * @return 1 if the argument state machine has been started; 0 otherwise
 */
CrFwBool_t CrFwCmpIsStarted(FwSmDesc_t smDesc);

/**
 * Return true if the argument component is in state CREATED.
 * This function checks whether the Base State Machine is in state CREATED.
 * This function can be used either on a Base State Machine or on a state
 * machine that has been derived from a Base State Machine.
 * @param smDesc the descriptor of the Base State Machine.
 * @return 1 if the argument state machine is in state CREATED; 0 otherwise
 */
CrFwBool_t CrFwCmpIsInCreated(FwSmDesc_t smDesc);

/**
 * Return true if the argument component is in state INITIALIZED.
 * This function checks whether the Base State Machine is in state INITIALIZED.
 * This function can be used either on a Base State Machine or on a state
 * machine that has been derived from a Base State Machine.
 * @param smDesc the descriptor of the Base State Machine.
 * @return 1 if the argument state machine is in state INITIALIZED; 0 otherwise
 */
CrFwBool_t CrFwCmpIsInInitialized(FwSmDesc_t smDesc);

/**
 * Return true if the argument component is in state CONFIGURED.
 * This function checks whether the Base State Machine is in state CONFIGURED.
 * This function can be used either on a Base State Machine or on a state
 * machine that has been derived from a Base State Machine.
 * @param smDesc the descriptor of the Base State Machine.
 * @return 1 if the argument state machine is in state CONFIGURED; 0 otherwise
 */
CrFwBool_t CrFwCmpIsInConfigured(FwSmDesc_t smDesc);

#endif /* CRFW_BASE_CMP_H_ */
