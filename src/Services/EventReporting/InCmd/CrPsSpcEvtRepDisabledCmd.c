/**
 * \file
 *
 * Implementation of TC(5,7) EvtRepDisabledCmd.
 *
 * \note This file was generated on 2017-09-19 12:36:09
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsSpcEvtRepDisabledCmd.h"
#include "CrPsDebug.h"

/**
 * Acceptance check of TC(5,7) EvtRepDisabledCmd.
 *
 * \param smDesc The state machine descriptor.
 * \return The acceptance check result.
 */
CrFwBool_t CrPsEvtRepDisabledCmdAcceptanceCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_5("CrPsEvtRepDisabledCmdAcceptanceCheck");
  return 1;
}

/**
 * Ready check of TC(5,7) EvtRepDisabledCmd.
 * Return “command is ready’
 * \param smDesc The state machine descriptor.
 * \return The ready check result.
 */
CrFwBool_t CrPsEvtRepDisabledCmdReadyCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_5("CrPsEvtRepDisabledCmdReadyCheck");
  return 1;
}

/**
 * Start action of TC(5,7) EvtRepDisabledCmd.
 * Retrieve (5,8) report from OutFactory and set action outcome
 * to “success’ if retrieval succeeds. If the retrieval fails, generate
 * error report OUTFACTORY FAILED and set outcome of Start
 * Action to ’failed’
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtRepDisabledCmdStartAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_5("CrPsEvtRepDisabledCmdStartAction");
  return ;
}

/**
 * Progress action of TC(5,7) EvtRepDisabledCmd.
 * Configure the (5,8) report with a destination equal to the source
 * of the (5,7) command, load it in the OutLoader, and set the
 * action outcome to ’completed’
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtRepDisabledCmdProgressAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_5("CrPsEvtRepDisabledCmdProgressAction");
  return ;
}

/**
 * Termination action of TC(5,7) EvtRepDisabledCmd.
 * Set action outcome to ’success’
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtRepDisabledCmdTerminationAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_5("CrPsEvtRepDisabledCmdTerminationAction");
  return ;
}

/**
 * Abort action of TC(5,7) EvtRepDisabledCmd.
 * Do nothing
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtRepDisabledCmdAbortAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_5("CrPsEvtRepDisabledCmdAbortAction");
  return ;
}
