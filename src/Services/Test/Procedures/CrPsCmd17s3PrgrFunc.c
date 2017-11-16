/**
 * @file CrPsCmd17s3PrgrFunc.c
 * @ingroup CrIaDemo
 *
 * ???
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

/** CrPsCmd17s3Prgr function definitions */
#include "CrPsCmd17s3PrgrCreate.h"
#include "CrPsCmd17s3StartCreate.h" /* including global variables: rep */

/** FW Profile function definitions */
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwSmConfig.h"

/* Framework function definitions */
#include "OutFactory/CrFwOutFactory.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"
#include "CrFwCmpData.h"

#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServTest.h>
#include <Services/General/CrPsPktServTest.h>
#include <Services/General/CrPsConstants.h>
#include <Services/Test/InCmd/CrPsTestOnBoardConnection.h> /* for global handles */
#include <stdio.h>
#include "CrPsDebug.h"


/* ------------------------------------------------------------------------------------ */
/* Action for node N1. */
void CrPsTestOnBoardConnectionPrgrN1(FwPrDesc_t prDesc)
{
  CrFwDestSrc_t       destId;
  CrPsApid_t          appId;
  FwSmDesc_t          rep;
  prDataPrgrAction_t *prDataPrgrActionPtr;
  CrFwCmpData_t      *cmpDataStart;
  CrFwOutCmpData_t   *cmpSpecificData;
  CrFwPckt_t          pckt;

  /* Configure the (17,4) report with a destination equal to the source of the (17,3),
     load it in the Outloader and set action outcome to 'completed' */

  /* The (17,4) report has been retrieved from the OutFactory by the Start Action of the (17,3) */

  /* Get application ID with which the test was performed */
  appId = getDpAreYouAliveSrc();

  /* Get the source and rep identifier of the InCmd from prData and set the destination equal to the source of the (17,3) */
  prDataPrgrActionPtr = FwPrGetData(prDesc);
  destId = prDataPrgrActionPtr->source;
  rep    = prDataPrgrActionPtr->smDesc;

  /* Get TM(17,4) packet */
  cmpDataStart    = (CrFwCmpData_t   *) FwSmGetData(rep);
  cmpSpecificData = (CrFwOutCmpData_t *) cmpDataStart->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Set out component parameters */
  setOnBoardConnectRepDest(pckt, appId);

  /* Set destination */
  CrFwOutCmpSetDest(rep, destId);

  /* Load the (17,4) report in the Outloader */
  CrFwOutLoaderLoad(rep);

  /* Set action outcome to 'completed' */
  prDataPrgrActionPtr->outcome = 1;
  FwPrSetData(prDesc, prDataPrgrActionPtr);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N2. */
void CrPsTestOnBoardConnectionPrgrN2(FwPrDesc_t prDesc)
{
  prDataPrgrAction_t *prDataPrgrActionPtr;

  /* Set action outcome to 'continue' */

  prDataPrgrActionPtr = FwPrGetData(prDesc);

  prDataPrgrActionPtr->outcome = 2;
  FwPrSetData(prDesc, prDataPrgrActionPtr);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N3. */
void CrPsTestOnBoardConnectionPrgrN3(FwPrDesc_t prDesc)
{
  prDataPrgrAction_t *prDataPrgrActionPtr;

  /* Set action outcome to 'failed' */

  prDataPrgrActionPtr = FwPrGetData(prDesc);

  prDataPrgrActionPtr->outcome = 4;
  FwPrSetData(prDesc, prDataPrgrActionPtr);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N4. */
void CrPsTestOnBoardConnectionPrgrN4(FwPrDesc_t prDesc)
{
  FwSmDesc_t          rep;
  prDataPrgrAction_t *prDataPrgrActionPtr;

  CRFW_UNUSED(prDesc);

  /* Release (17,4) report */
  /* The (17,4) report has been retrieved from the OutFactory by the Start Action of the (17,3) */

  /* Get the rep identifier from prData */
  prDataPrgrActionPtr = FwPrGetData(prDesc);
  rep = prDataPrgrActionPtr->smDesc;

  CrFwOutFactoryReleaseOutCmp(rep);

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/* Guard on the Control Flow from DECISION1 to N1. */
FwPrBool_t CrPsTestOnBoardConnectionPrgrG11(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  CrPsApid_t appId;
  int        timeOut;

  /* [ (areYouAliveSrc > 0) &&
       (time elapsed since command execution started smaller than areYouAliveTimeOut) ] */

  /* Get areYouAliveSrc from data pool */
  appId = getDpAreYouAliveSrc();

  /* Get areYouAliveTimeOut from data pool */
  timeOut = getDpAreYouAliveTimeOut();

  if (appId > 0 && timeOut_cnt < timeOut)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/* ------------------------------------------------------------------------------------ */
/* Guard on the Control Flow from DECISION1 to N2. */
FwPrBool_t CrPsTestOnBoardConnectionPrgrG12(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  /*FwPrCounterU3_t execCnt, nodeExecCnt;*/
  CrPsApid_t appId;
  int        timeOut;

  /* [ (areYouAliveSrc == 0) &&
        (time elapsed since command execution started smaller than areYouAliveTimeOut) ] */

  /* Get areYouAliveSrc from data pool */
  appId = getDpAreYouAliveSrc();

  /* Get areYouAliveTimeOut from data pool */
  timeOut = getDpAreYouAliveTimeOut();

  if (appId == 0 && timeOut_cnt < timeOut)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/* ------------------------------------------------------------------------------------ */
/* Guard on the Control Flow from DECISION1 to N3. */
FwPrBool_t CrPsTestOnBoardConnectionPrgrG13(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  /*FwPrCounterU3_t execCnt, nodeExecCnt;*/
  int timeOut; /* TODO ... welcher Typ ?? */

  /* [ (time elapsed since command execution started equal or greater than areYouAliveTimeOut) ] */

  /* Get areYouAliveTimeOut from data pool */
  timeOut = getDpAreYouAliveTimeOut();

  if (timeOut_cnt >= timeOut)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}
