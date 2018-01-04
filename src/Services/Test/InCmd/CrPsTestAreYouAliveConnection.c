/**
 * @file CrPsTestAreYouAliveConnection.c
 *
 * Implementation of the Perform Connection Test in-coming command packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsTestAreYouAliveConnection.h"

/* CrFramework includes */
#include <Pckt/CrFwPckt.h>
#include <OutFactory/CrFwOutFactory.h>
#include <OutCmp/CrFwOutCmp.h>
#include <OutLoader/CrFwOutLoader.h>
#include <CrFwCmpData.h>

/* FwProfile includes */
#include <FwSmConfig.h>

#include <CrPsUtilitiesServTest.h>
#include <Services/General/CrPsConstants.h>

#include <stdio.h>
#include "CrPsDebug.h"

FwSmDesc_t rep;


void CrPsTestAreYouAliveConnectionStartAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t* inData;

  /* Retrieve (17,2) report from OutFactory and set action outcome
     to \success' if retrieval succeeds. If the retrieval fails, generate
     error report OUTFACTORY FAILED and set outcome of Start
     Action to 'failed' */

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  /* Create out component */
  rep = CrFwOutFactoryMakeOutCmp(CRPS_TEST, CRPS_TEST_AREYOUALIVE_CONNECTION_REP, 0, 0);

  if (rep != NULL)
    {
      inData->outcome = 1;
    }
  else
    {
      /* TM(17,2) OUTFACTORY_FAIL */
      CrPsRepErr(crOutfactoryFail, CRPS_TEST, CRPS_TEST_AREYOUALIVE_CONNECTION_REP, 0);

      inData->outcome = 0;
    }

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsTestAreYouAliveConnectionProgressAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;
  CrFwDestSrc_t    source;

  /* Configure the (17,2) report with a destination equal to the
     source of the (17,1) command, load it in the OutLoader, and
     set action outcome to 'completed' */

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

/* ------------------------------------------------------------------------------------ */
void CrPsTestAreYouAliveConnectionTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t*   inData;

  /* Set action outcome to 'success' */

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

