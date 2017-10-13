/**
 * \file
 *
 * Implementation of TM(5,2) EvtRep2.
 *
 * \note This file was generated on 2017-09-19 12:36:09
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsSpcEvtRep2.h"
#include "CrPsDebug.h"

/**
 * Enable check of TM(5,2) EvtRep2.
 * Update service 5 observable nOfDetectedEvt x (’x’ is the event
 * severity level) and then retrieve the enable status from the Our-
 * Registry as a function of the report type, sub-type and discrimi-
 * nant
 * \param smDesc The state machine descriptor.
 * \return The enable check result.
 */
CrFwBool_t CrPsEvtRep2EnableCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_5("CrPsEvtRep2EnableCheck");
  return 1;
}

/**
 * Ready check of TM(5,2) EvtRep2.
 * Report is always ready
 * \param smDesc The state machine descriptor.
 * \return The ready check result.
 */
CrFwBool_t CrPsEvtRep2ReadyCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_5("CrPsEvtRep2ReadyCheck");
  return 1;
}

/**
 * Repeat check of TM(5,2) EvtRep2.
 * Report is never repeated
 * \param smDesc The state machine descriptor.
 * \return The repeat check result.
 */
CrFwBool_t CrPsEvtRep2RepeatCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_5("CrPsEvtRep2RepeatCheck");
  return 1;
}

/**
 * Update action of TM(5,2) EvtRep2.
 * Update service 5 observables: nOfGenEvtRep x, lastEvtEid i,
 * lastEvtTime x (’x’ is the event severity level). Note that the pa-
 * rameter values are set by the application which creates the event
 * report at the time it creates the event report.
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtRep2UpdateAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_5("CrPsEvtRep2UpdateAction");
  return ;
}
