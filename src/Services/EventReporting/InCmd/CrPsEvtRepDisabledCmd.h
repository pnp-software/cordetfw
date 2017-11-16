/**
 * \file
 *
 * Implementation of TC(5,7) EvtRepDisabledCmd.
 *
 * \note This file was generated on 2017-09-19 12:36:09
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSSPCEVTREPDISABLEDCMD_H_
#define CRPSSPCEVTREPDISABLEDCMD_H_

#include "CrPsDpTypes.h"

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Start action of TC(5,7) EvtRepDisabledCmd.
 * Retrieve (5,8) report from OutFactory and set action outcome
 * to “success’ if retrieval succeeds. If the retrieval fails, generate
 * error report OUTFACTORY FAILED and set outcome of Start
 * Action to ’failed’
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtRepDisabledCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(5,7) EvtRepDisabledCmd.
 * Configure the (5,8) report with a destination equal to the source
 * of the (5,7) command, load it in the OutLoader, and set the
 * action outcome to ’completed’
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtRepDisabledCmdProgressAction(FwSmDesc_t smDesc);

/**
 * Termination action of TC(5,7) EvtRepDisabledCmd.
 * Set action outcome to ’success’
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtRepDisabledCmdTerminationAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSSPCEVTREPDISABLEDCMD_H */
