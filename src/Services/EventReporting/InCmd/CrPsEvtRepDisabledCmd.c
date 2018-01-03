/**
 * \file
 *
 * Implementation of TC(5,7) EvtRepDisabledCmd.
 *
 * \note This file was generated on 2017-09-19 12:36:09
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsEvtRepDisabledCmd.h"

/* CrFramework includes */
#include <Pckt/CrFwPckt.h>
#include <OutFactory/CrFwOutFactory.h>
#include <OutCmp/CrFwOutCmp.h>
#include <OutLoader/CrFwOutLoader.h>
#include <CrFwCmpData.h>

/* FwProfile includes */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"

#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServEvt.h>
#include <Services/General/CrPsPktServEvtSupp.h>
#include "CrPsDebug.h"

static FwSmDesc_t rep;


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
  CrFwCmpData_t *cmpData;

  /* Get cmp data */
  cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  rep = CrFwOutFactoryMakeOutCmp(CRPS_EVT, CRPS_EVT_REPDISABLED_REP, 0, getEvtRepDisabledSize());

  if (rep != NULL)
    {
      cmpData->outcome = 1;
    }
  else
    {
      /* TM(5,8) OUTFACTORY_FAIL */
      CrPsRepErr(crOutfactoryFail, CRPS_EVT, CRPS_EVT_REPDISABLED_REP, 0);

      cmpData->outcome = 0;
    }

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
  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;
  CrFwDestSrc_t    source;

  /* Get in packet */
  inData          = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData  = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt          = inSpecificData->pckt;

  /* Set out component parameters */
  source = CrFwPcktGetSrc(inPckt);
  CrFwOutCmpSetDest(rep, source);

  /* load the report in the OutLoader */
  CrFwOutLoaderLoad(rep);

  inData->outcome = 1;

  return;
}

/**
 * Termination action of TC(5,7) EvtRepDisabledCmd.
 * Set action outcome to ’success’
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtRepDisabledCmdTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t *inData;

  /* Set action outcome to 'success' */

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;
  return ;
}

