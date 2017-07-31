/**
 * @file CrPsTestOnBoardConnection.c
 *
 * Implementation of the Perform Connection Test in-coming command packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsTestOnBoardConnection.h"

/* CrFramework includes */
#include "Pckt/CrFwPckt.h"
#include "OutFactory/CrFwOutFactory.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"
#include "CrFwCmpData.h"

/* FwProfile includes */
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwSmConfig.h"

#include <CrPsUtilities.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsParamGetter.h>

#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServTest.h>

#include <stdio.h>

/* global handles */
unsigned short timeOut_cnt;


/* ------------------------------------------------------------------------------------ */
CrFwBool_t CrPsTestOnBoardConnectionReadyCheck(FwSmDesc_t __attribute__((unused)) smDesc) 
{
  /* Return 'command is ready' */
  printf("CrPsTestOnBoardConnectionReadyCheck()\n");

  /* Send Request Verification Acceptance Successful out-going report */
  SendReqVerifAccSuccRep(smDesc, CRPS_REQVERIF_ACC_SUCC);

  return 1; /* always True */
}

/* ------------------------------------------------------------------------------------ */
void CrPsTestOnBoardConnectionStartAction(FwSmDesc_t __attribute__((unused)) smDesc) 
{
  CrFwCmpData_t* cmpDataStart;
  CrFwInCmdData_t* cmpSpecificData;
  CrFwPckt_t inPckt;
  unsigned short appId;
  prDataStartAction_t* prDataStartActionPtr;

  /* Run the procedure Start Action of OnBoardConnectCmd Command (see figure 13.1 in PP-DF-COR-003) */

  printf("CrPsTestOnBoardConnectionStartAction()\n");

  /* Get in packet */
  cmpDataStart    = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpDataStart->cmpSpecificData;
  inPckt          = cmpSpecificData->pckt;

  /* set timeout counter to 0 */
  timeOut_cnt = 0;

  /* TODO: not in specifications */
  /* get Application ID */
  CrPsServTestOnBoardConnectParamGetAppId(&appId, inPckt);
  printf("CrPsTestOnBoardConnectionStartAction(): appId = %d\n", appId);

  /* store in data pool */
  setDpOnBoardConnectDest(appId);

  /* TODO: remove; TEST: re-read and print */
  printf("CrPsTestOnBoardConnectionStartAction(): appId in DP = %d\n", getDpOnBoardConnectDest());

  /* Run the procedure */
  FwPrRun(prDescServTestOnBoardConnStart);

  /* Get procedure parameters */
  prDataStartActionPtr = FwPrGetData(prDescServTestOnBoardConnStart);

  /*Setting the Outcome*/
  cmpDataStart->outcome = prDataStartActionPtr->outcome;
 
  printf("CrPsTestOnBoardConnectionStartAction(): cmpDataStart->outcome = %d\n", cmpDataStart->outcome);

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsTestOnBoardConnectionProgressAction(FwSmDesc_t __attribute__((unused)) smDesc) 
{
  CrFwCmpData_t* cmpDataPrgr;
  CrFwInCmdData_t* cmpSpecificData;
  CrFwPckt_t inPckt;
  CrFwDestSrc_t srcId;
  prDataPrgrAction_t* prDataPrgrActionPtr;
  prDataPrgrAction_t prDataPrgrAction;

  /* Run the procedure Progress Action of OnBoardConnectCmd Command (see figure 13.2 in PP-DF-COR-003) */

  printf("CrPsTestOnBoardConnectionProgressAction()\n");

  /* Get in packet */
  cmpDataPrgr     = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpDataPrgr->cmpSpecificData;
  inPckt          = cmpSpecificData->pckt;

  /* Get the InCmd source and set it in the prData */
  srcId = CrFwPcktGetSrc(inPckt);
  prDataPrgrAction.source = srcId;
  FwPrSetData(prDescServTestOnBoardConnPrgr, &prDataPrgrAction);

  /* Run the procedure */
  FwPrRun(prDescServTestOnBoardConnPrgr);

  /* Get procedure parameters */
  prDataPrgrActionPtr = FwPrGetData(prDescServTestOnBoardConnPrgr);

  /* Set the Outcome*/
  cmpDataPrgr->outcome = prDataPrgrActionPtr->outcome;

  /* Increment timeout counter */
  timeOut_cnt++;

  printf("CrPsTestOnBoardConnectionProgressAction(): cmpDataPrgr->outcome = %d\n", cmpDataPrgr->outcome);

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsTestOnBoardConnectionTerminationAction(FwSmDesc_t __attribute__((unused)) smDesc) 
{
  /* Set action outcome to 'success' */

  CrFwCmpData_t* inData;
 
  printf("CrPsTestOnBoardConnectionTerminationAction()\n");

  FwPrStop(prDescServTestOnBoardConnPrgr); /* TODO: to be investigated, why this is needed */

  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inData->outcome = 1;
 
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsTestOnBoardConnectionAbortAction(FwSmDesc_t __attribute__((unused)) smDesc) 
{
  /* Do nothing */

  printf("CrPsTestOnBoardConnectionAbortAction()\n");

  return;
}
