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
/*#include "OutCmp/CrFwOutCmp.h"*/
#include <OutLoader/CrFwOutLoader.h>
#include <CrFwCmpData.h>

/* FwProfile includes */
#include <FwProfile/FwSmConfig.h>

#include <CrPsUtilities.h>
#include <Services/General/CrPsConstants.h>

#include <stdio.h>

/* ------------------------------------------------------------------------------------ */
CrFwBool_t CrPsTestAreYouAliveConnectionReadyCheck(FwSmDesc_t __attribute__((unused)) smDesc)
{
  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;

  /* Return 'command is ready' */

  printf("CrPsTestAreYouAliveConnectionReadyCheck()\n");

  /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* Send Request Verification Acceptance Successful out-going report */
  SendReqVerifAccSuccRep(inPckt);

  return 1; /*always True*/
}

/* ------------------------------------------------------------------------------------ */
void CrPsTestAreYouAliveConnectionStartAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t* inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;

  printf("CrPsTestAreYouAliveConnectionStartAction()\n");

  /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* Send Request Verification Start Successful out-going report */
  SendReqVerifStartSuccRep(inPckt);

  inData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsTestAreYouAliveConnectionProgressAction(FwSmDesc_t smDesc)
{
  FwSmDesc_t       rep;
  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;
  CrFwDestSrc_t    source;

  printf("CrPsTestAreYouAliveConnectionProgressAction()\n");

  /* Get in packet */
  inData          = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inData->outcome = 0;
  inSpecificData  = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt          = inSpecificData->pckt;

  /* Create out component */
  rep = CrFwOutFactoryMakeOutCmp(CRPS_TEST, CRPS_TEST_AREYOUALIVE_CONNECTION_REP, 0, 0);

  /* Set out component parameters */
  source = CrFwPcktGetSrc(inPckt);
  CrFwOutCmpSetDest(rep, source);

  CrFwOutLoaderLoad(rep);

  /* Send Request Verification Progress Successful out-going report */
  SendReqVerifProgSuccRep(inPckt);

  inData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsTestAreYouAliveConnectionTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;

  printf("CrPsTestAreYouAliveConnectionTerminationAction()\n");

  /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* Send Request Verification Termination Successful out-going report */
  SendReqVerifTermSuccRep(inPckt);

  inData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsTestAreYouAliveConnectionAbortAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t* inData;

  printf("CrPsTestAreYouAliveConnectionAbortAction()\n");
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inData->outcome = 1;

  return;
}
