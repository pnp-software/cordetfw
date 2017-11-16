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

#include <CrPsUtilitiesServTest.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServTest.h>
#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServTest.h>

#include <stdio.h>
#include <stdlib.h>
#include "CrPsDebug.h"

unsigned short timeOut_cnt;

void CrPsTestOnBoardConnectionStartAction(FwSmDesc_t smDesc) 
{
  CrFwCmpData_t       *cmpDataStart;
  CrFwInCmdData_t     *cmpSpecificData;
  CrFwPckt_t           inPckt;
  CrPsApid_t           appId;
  prDataStartAction_t *prDataStartActionPtr;

  /* Run the procedure Start Action of OnBoardConnectCmd Command (see figure 13.1 in PP-DF-COR-003) */

  /* Get in packet */
  cmpDataStart    = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpDataStart->cmpSpecificData;
  inPckt          = cmpSpecificData->pckt;

  /* set timeout counter to 0 */
  timeOut_cnt = 0;

  /* TODO: not in specifications */
  /* get Application ID */
  appId = getOnBoardConnectCmdAppId(inPckt);
  
  /* store in data pool */
  setDpOnBoardConnectDest(appId);

  /* Run the procedure */
  FwPrRun(prDescServTestOnBoardConnStart);

  /* Get procedure parameters */
  prDataStartActionPtr = FwPrGetData(prDescServTestOnBoardConnStart);

  /*Setting the Outcome*/
  cmpDataStart->outcome = prDataStartActionPtr->outcome;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsTestOnBoardConnectionProgressAction(FwSmDesc_t smDesc) 
{
  CrFwCmpData_t      *cmpDataPrgr;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          inPckt;
  CrFwDestSrc_t       srcId;
  prDataPrgrAction_t *prDataPrgrActionPtr;
  
  /* Run the procedure Progress Action of OnBoardConnectCmd Command (see figure 13.2 in PP-DF-COR-003) */
  
  /* Get in packet */
  cmpDataPrgr     = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpDataPrgr->cmpSpecificData;
  inPckt          = cmpSpecificData->pckt;

  /* Get the InCmd source and set it in the prData */
  srcId = CrFwPcktGetSrc(inPckt);

  /* Set prData of procedure */
  prDataPrgrActionPtr = FwPrGetData(prDescServTestOnBoardConnPrgr);
  prDataPrgrActionPtr->source = srcId;
  prDataPrgrActionPtr->stepId = timeOut_cnt;
  FwPrSetData(prDescServTestOnBoardConnPrgr, prDataPrgrActionPtr);

  /* Run the procedure */
  FwPrRun(prDescServTestOnBoardConnPrgr);
  
  /* Get procedure parameters */
  prDataPrgrActionPtr = FwPrGetData(prDescServTestOnBoardConnPrgr);

  /* Set the Outcome*/
  cmpDataPrgr->outcome = prDataPrgrActionPtr->outcome;

  /* Increment timeout counter */
  timeOut_cnt++;
  
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsTestOnBoardConnectionTerminationAction(FwSmDesc_t smDesc) 
{
  CrFwCmpData_t      *inData;
  prDataPrgrAction_t *prDataPrgrActionPtr;
  unsigned short      outcome;

  /* Set action outcome to 'success' if the (17,4) report was issued and to 'failure' otherwise */
  
  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  
  /* Get procedure parameters */
  prDataPrgrActionPtr = (prDataPrgrAction_t*) FwPrGetData(prDescServTestOnBoardConnPrgr);

  /* Get the Outcome*/
  outcome = prDataPrgrActionPtr->outcome;
  
  if (outcome == 1)
    {
      inData->outcome = 1;
    }
  else if ((outcome == 0) || (outcome > 2))
    {
      inData->outcome = 0;
    }
 
  return;
}
