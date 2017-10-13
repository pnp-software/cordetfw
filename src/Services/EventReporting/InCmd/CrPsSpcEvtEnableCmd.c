/**
 * \file
 *
 * Implementation of TC(5,5) EvtEnableCmd.
 *
 * \note This file was generated on 2017-09-19 12:36:09
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsSpcEvtEnableCmd.h"
#include "CrPsDebug.h"

/**
 * Acceptance check of TC(5,5) EvtEnableCmd.
 *
 * \param smDesc The state machine descriptor.
 * \return The acceptance check result.
 */
CrFwBool_t CrPsEvtEnableCmdAcceptanceCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_5("CrPsEvtEnableCmdAcceptanceCheck");
  return 1;
}

/**
 * Ready check of TC(5,5) EvtEnableCmd.
 * Return “command is ready’
 * \param smDesc The state machine descriptor.
 * \return The ready check result.
 */
CrFwBool_t CrPsEvtEnableCmdReadyCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_5("CrPsEvtEnableCmdReadyCheck");
  return 1;
}

/**
 * Start action of TC(5,5) EvtEnableCmd.
 * Run the procedure Start Action of Multi-EID Command of
 * figure 10.1
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtEnableCmdStartAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_5("CrPsEvtEnableCmdStartAction");
  return ;
}

/**
 * Progress action of TC(5,5) EvtEnableCmd.
 * For each valid EID found by the Start Action of the command:
 * set the corresponding element of the array isEidEnabled to true
 * and then decrement nDisabledEid x (’x’ is the severity level of
 * the EID). Set the action outcome to ’completed’.
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtEnableCmdProgressAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_5("CrPsEvtEnableCmdProgressAction");
  return ;
}

/**
 * Termination action of TC(5,5) EvtEnableCmd.
 * Set action outcome to ’success’
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtEnableCmdTerminationAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_5("CrPsEvtEnableCmdTerminationAction");
  return ;
}

/**
 * Abort action of TC(5,5) EvtEnableCmd.
 * Do nothing
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtEnableCmdAbortAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_5("CrPsEvtEnableCmdAbortAction");
  return ;
}
