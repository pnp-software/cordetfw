/**
 * \file
 *
 * Implementation of TC(5,6) EvtDisableCmd.
 *
 * \note This file was generated on 2017-09-19 12:36:09
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSSPCEVTDISABLECMD_H_
#define CRPSSPCEVTDISABLECMD_H_

#include "CrPsDpTypes.h"

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Acceptance check of TC(5,6) EvtDisableCmd.
 *
 * \param smDesc The state machine descriptor.
 * \return The acceptance check result.
 */
CrFwBool_t CrPsEvtDisableCmdAcceptanceCheck(FwSmDesc_t smDesc);

/**
 * Ready check of TC(5,6) EvtDisableCmd.
 * Return “command is ready’
 * \param smDesc The state machine descriptor.
 * \return The ready check result.
 */
CrFwBool_t CrPsEvtDisableCmdReadyCheck(FwSmDesc_t smDesc);

/**
 * Start action of TC(5,6) EvtDisableCmd.
 * Run the procedure Start Action of Multi-EID Command of
 * figure 10.1
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtDisableCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(5,6) EvtDisableCmd.
 * For each valid EID found by the Start Action of the command:
 * set the corresponding element of the array isEidEnabled to false
 * and then increment nDisabledEid x (’x’ is the severity level of
 * the EID). Set the action outcome to ’completed’.
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtDisableCmdProgressAction(FwSmDesc_t smDesc);

/**
 * Termination action of TC(5,6) EvtDisableCmd.
 * Set action outcome to ’success’
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtDisableCmdTerminationAction(FwSmDesc_t smDesc);

/**
 * Abort action of TC(5,6) EvtDisableCmd.
 * Do nothing
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtDisableCmdAbortAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSSPCEVTDISABLECMD_H */
