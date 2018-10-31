/**
 * @file
 * @ingroup outMngGroup
 * Definition of the OutRegistry Component.
 *
 * An OutRegistry acts as a registry for out-going commands or reports (namely for
 * commands or reports which have been loaded into an OutManager).
 * The OutRegistry is responsible for:
 * - keeping track of an out-going command's or report's state
 * - storing the enable state of out-going commands or reports
 * - storing the link between the index of an out-going command or report and its
 *   service type and sub-type
 * .
 * The index of an out-going command or report is a positive integer in the range
 * from 0 to <code>::CR_FW_OUTREGISTRY_NSERV</code>-1.
 * <code>::CR_FW_OUTREGISTRY_NSERV</code> is the total number of out-going service
 * types and sub-types in an application.
 * The index of an out-going command or report uniquely identifies the command's
 * or report's type and sub-type.
 *
 * The set of out-going service types and sub-types supported by an application
 * is specified in <code>CrFwOutRegistryUserPar.h</code>.
 *
 * The framework internally uses the index as a more efficient way of identifying
 * a pair [service type, service sub-type] for an out-going command or report.
 * The OutRegistry offers a function which allows the service type and service sub-type
 * associated to a certain index to be retrieved.
 *
 * The OutRegistry is a singleton component which is implemented as an extension
 * of the Base Component of <code>CrFwBaseCmp.h</code>.
 *
 * The OutRegistry maintains a list of the last N commands or reports to have been
 * loaded in an OutManager.
 * The OutRegistry maintains the state of each such command or report.
 * The command's or report's state in the OutRegistry can have one of the following values:
 * - PENDING: the command or report is waiting to be sent
 * - ABORTED: the command or report was aborted because it was disabled when it was loaded
 * - TERMINATED: the command or report has been passed to the OutStream
 * .
 * The value of N (the maximum number of items which can be tracked by the OutRegistry)
 * is fixed and is an initialization parameter.
 *
 * The OutRegistry uses the instance identifier of the OutComponent encapsulating
 * the out-going report or command as the key through which the out-going command or report
 * state is tracked.
 *
 * The OutRegistry stores the enable state of out-going commands and reports.
 * The enable state of out-going command and reports can be controlled at three levels:
 * - At the level of the service type (all commands or reports of a certain type are disabled)
 * - At the level of the service sub-type (all commands or reports matching a certain
 *   [type, sub-type] pair are disabled)
 * - At the level of the discriminant (all commands or reports matching a certain
 *   [type, sub-type, discriminant] triplet are enabled or disabled)
 * .
 * The enable state of a particular out-going command or report is derived from these three
 * enable levels by running the Enable State Determination Procedure shown in the
 * figure below.
 * The OutRegistry offers functions through which all three levels of enable state
 * can be controlled and through which the enable state of a specific out-going
 * command or report can be determined.
 * By default, the enable state for all kinds of reports or commands is set to:
 * "enabled".
 *
 * <b>Mode of Use of an OutRegistry Component</b>
 *
 * The configuration of the OutRegistry component is defined statically in
 * <code>CrFwOutRegistryUserPar.h</code>.
 *
 * The OutRegistry component is a "final" component that does not normally need
 * to be extended.
 *
 * An OutRegistry component is created with function <code>::CrFwOutRegistryMake</code>.
 * After being created, the OutRegistry must be initialized and reset.
 * This is done with functions <code>::CrFwCmpInit</code> and <code>::CrFwCmpReset</code>.
 * Nominally, after being initialized and reset the OutRegistry State Machine should be
 * in state CONFIGURED (this can be checked by verifying that function <code>FwSmGetCurState</code>
 * returns CR_FW_BASE_STATE_CONFIGURED).
 *
 * @image html EnableStateDetermination.png
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

#ifndef CRFW_OUTREGISTRY_H_
#define CRFW_OUTREGISTRY_H_

/* Include configuration files */
#include "CrFwOutRegistryUserPar.h"
#include "CrFwUserConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwPrConstants.h"
/* Include framework files */
#include "CrFwConstants.h"

/** Enumerated type for the state of an out-going command or report tracked by the OutRegistry */
typedef enum {
	/** No entry yet in OutRegistry */
	crOutRegistryNoEntry = 0,
	/** Out-going command or report is pending (waiting to be sent) */
	crOutRegistryPending = 1,
	/** Out-going command or report has been aborted */
	crOutRegistryAborted = 2,
	/** Out-going command or report has been passed to the OutStream */
	crOutRegistryTerminated = 3,
	/** Out-going command or report is not tracked */
	crOutRegistryNotTracked = 4
} CrFwOutRegistryCmdRepState_t;

/**
 * Factory function for the singleton instance of the OutRegistry.
 * The first time this function is called, it creates and configures the OutRegistry.
 * Subsequent calls returns the same singleton instance.
 * The first time this function is called, it returns the OutRegistry in state CREATED.
 *
 * If the creation or the configuration of the OutRegistry fails, the function
 * returns NULL.
 * @return singleton instance of the OutRegistry or NULL if the creation or configuration
 * of the OutRegistry failed.
 */
FwSmDesc_t CrFwOutRegistryMake();

/**
 * Get the service type of the argument command or report index.
 * For out-going commands or reports the index uniquely identifies a pair:
 * [service type, service sub-type].
 * This function returns the service type corresponding to a certain index value.
 * If the index value is out of range (i.e. if it is greater than
 * <code>::CR_FW_OUTREGISTRY_NSERV</code>-1), the behaviour of this function is
 * undefined.
 * @param cmdRepIndex the command or report index
 * @return the service type corresponding to the command or report index
 */
CrFwServType_t CrFwOutRegistryGetServType(CrFwCmdRepIndex_t cmdRepIndex);

/**
 * Get the service sub-type of the argument command or report index.
 * For out-going commands or reports the index uniquely identifies a pair:
 * [service type, service sub-type].
 * This function returns the service sub-type corresponding to a certain index value.
 * If the index value is out of range (i.e. if it is greater than
 * <code>::CR_FW_OUTREGISTRY_NSERV</code>-1), the behaviour of this function is
 * undefined.
 * @param cmdRepIndex the command or report index
 * @return the service type corresponding to the command or report index
 */
CrFwServSubType_t CrFwOutRegistryGetServSubType(CrFwCmdRepIndex_t cmdRepIndex);

/**
 * Get the lower bound of the argument command or report index.
 * For out-going commands or reports the index uniquely identifies a pair:
 * [service type, service sub-type].
 * This function returns the lower discriminant value corresponding to a certain index value.
 * If the index value is out of range (i.e. if it is greater than
 * <code>::CR_FW_OUTREGISTRY_NSERV</code>-1), the behaviour of this function is
 * undefined.
 * @param cmdRepIndex the command or report index
 * @return the lower discriminant bound corresponding to the command or report index
 */
CrFwDiscriminant_t CrFwOutRegistryGetLowerDiscriminant(CrFwCmdRepIndex_t cmdRepIndex);

/**
 * Get the upper bound of the argument command or report index.
 * For out-going commands or reports the index uniquely identifies a pair:
 * [service type, service sub-type].
 * This function returns the upper discriminant value corresponding to a certain index value.
 * If the index value is out of range (i.e. if it is greater than
 * <code>::CR_FW_OUTREGISTRY_NSERV</code>-1), the behaviour of this function is
 * undefined.
 * @param cmdRepIndex the command or report index
 * @return the upper discriminant bound corresponding to the command or report index
 */
CrFwDiscriminant_t CrFwOutRegistryGetUpperDiscriminant(CrFwCmdRepIndex_t cmdRepIndex);

/**
 * Get the index corresponding to the argument [service type, service sub-type] of an out-going
 * command or report.
 * For out-going commands or reports the index uniquely identifies a pair:
 * [service type, service sub-type].
 * This function returns the index corresponding to a specific [service type, service sub-type]
 * pair.
 * If either of the two arguments has an illegal value (i.e. if it has a value which does
 * not correspond to any [service type, service sub-type] declared in the initializer
 * of the service descriptor <code>::CR_FW_OUTREGISTRY_INIT_SERV_DESC</code>.),
 * the function returns CR_FW_OUTREGISTRY_NSERV.
 * @param servType the service type
 * @param servSubType the service sub-type
 * @return cmdRepIndex the command or report index or CR_FW_OUTREGISTRY_NSERV if the
 * specified [type, sub-type] does not exist
 */
CrFwCmdRepIndex_t CrFwOutRegistryGetCmdRepIndex(CrFwServType_t servType, CrFwServSubType_t servSubType);

/**
 * Set the enable state of a set of out-going commands or reports.
 * The enable state of out-going command and reports can be controlled at three levels:
 * - At the level of the service type (all commands or reports of a certain type are disabled)
 * - At the level of the service sub-type (all commands or reports matching a certain
 *   [type, sub-type] pair are disabled)
 * - At the level of the discriminant (all commands or reports matching a certain
 *   [type, sub-type, discriminant] triplet are enabled or disabled)
 * .
 * This function allows all three enable levels to be set according to the logic
 * in the activity diagram shown below.
 * Use of illegal values for the function parameters results in the application error code
 * being set to: <code>#crIllServType</code> (if the service type is illegal), or to
 * <code>#crIllServSubType</code> (if the service sub-type is illegal), or to
 * <code>#crIllDiscriminant</code> (if the discriminant value is illegal).
 * A service type or sub-type or a discriminant value are illegal if they are not covered
 * in the list of [type, sub-types, discriminant] in the <code>CrFwOutRegistryUserPar.h</code>
 * (see <code>::CR_FW_OUTREGISTRY_INIT_SERV_DESC</code>).
 * @image html EnableCmdRep.png
 * @param servType the service type
 * @param servSubType the service type
 * @param discriminant the discriminant
 * @param isEnabled the enable state (1 means enabled and 0 means disabled)
 */
void CrFwOutRegistrySetEnable(CrFwServType_t servType, CrFwServSubType_t servSubType,
                              CrFwDiscriminant_t discriminant, CrFwBool_t isEnabled);

/**
 * Query the enable status of an out-going command or report.
 * If the argument does not represent an out-going command or report (i.e. if it is not
 * a component of type OutComponent), the behaviour of the function is undefined.
 * The enable state of an out-going command or report is determined by running the
 * Enable State Determination Procedure shown in the figure.
 * @image html EnableStateDetermination.png
 * @param outCmp the out-going command or report as an OutComponent
 * @return the enable state of the specified command or report (1 means enabled and 0
 * means disabled)
 */
CrFwBool_t CrFwOutRegistryIsEnabled(FwSmDesc_t outCmp);

/**
 * Ask the OutRegistry to start tracking an out-going command or report.
 * The OutRegistry tracks the state of the last N out-going command or reports
 * to have been loaded with this function.
 * Initially, when this function is called, the out-going command or report is
 * placed in state PENDING.
 * This function runs the procedure in the left-hand
 * side of the activity diagram shown in the figure.
 * @image html RegistryStartTrackingAndUpdate.png
 * @param outCmp the out-going command or report to be tracked
 */
void CrFwOutRegistryStartTracking(FwSmDesc_t outCmp);

/**
 * Ask the OutRegistry to update the state of an out-going command or report.
 * If the argument component is not tracked by the OutRegistry (perhaps because
 * too many OutComponents have been added to the list of tracked components),
 * nothing is done.
 * This function runs the procedure in the right-hand
 * side of the activity diagram shown in the figure.
 * @image html RegistryStartTrackingAndUpdate.png
 * @param outCmp the out-going command or report to be tracked
 * @param newState the new state of the out-going command or report
 */
void CrFwOutRegistryUpdateState(FwSmDesc_t outCmp, CrFwOutRegistryCmdRepState_t newState);

/**
 * Query the OutRegistry for the state of an out-going command or report.
 * If the specified index does not correspond to any command or report being
 * tracked by the OutRegistry, a value of <code>::crOutRegistryNotTracked</code>
 * is returned.
 * This function searches all locations in the InRegistry in sequence until it
 * finds the out-going command or report.
 * @param cmdRepId the instance identifier of the out-going command or report.
 * @return the state of the out-going command or report (or <code>::crOutRegistryNotTracked</code>
 * if the command or report is not tracked)
 */
CrFwOutRegistryCmdRepState_t CrFwOutRegistryGetState(CrFwInstanceId_t cmdRepId);

#endif /* CRFW_OUTREGISTRY_H_ */
