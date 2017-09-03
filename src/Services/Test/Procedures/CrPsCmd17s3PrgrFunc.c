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

/* Framework function definitions */
#include "OutFactory/CrFwOutFactory.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"
#include "CrFwCmpData.h"

#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServTest.h>
#include <Services/General/CrPsDpPktServTest.h>
#include <Services/General/CrPsConstants.h>
#include <Services/Test/InCmd/CrPsTestOnBoardConnection.h> /* for global handles */
#include <stdio.h>


/* ------------------------------------------------------------------------------------ */
/* Action for node N1. */
void CrPsTestOnBoardConnectionPrgrN1(FwPrDesc_t prDesc)
{
  CrFwDestSrc_t destId;
  unsigned short appId;
  prDataPrgrAction_t* prDataPrgrActionPtr;

  /* Configure the (17,4) report with a destination equal to the source of the (17,3),
     load it in the Outloader and set action outcome to 'completed' */

  /* The (17,4) report has been retrieved from the OutFactory by the Start Action of the (17,3) */
  /*printf("CrPsTestOnBoardConnectionPrgrN1()\n");*/

  /* Get application ID with which the test was performed */
  appId = getDpAreYouAliveSrc();

  /* Set out component parameters */
  setOnBoardConnectRep0Dest(rep, appId);

  /* Get the source of the InCmd from prData and set the destination equal to the source of the (17,3) */
  prDataPrgrActionPtr = FwPrGetData(prDesc);
  destId = prDataPrgrActionPtr->source;
  CrFwOutCmpSetDest(rep, destId); /*so wars in meiner Datei*/

  /* Load the (17,4) report in the Outloader */
  CrFwOutLoaderLoad(rep);

  /* Set action outcome to 'completed' */
  prDataPrgrActionPtr->outcome = 1;
  prDataPrgrActionPtr->stepId = 5;
  FwPrSetData(prDesc, prDataPrgrActionPtr);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N2. */
void CrPsTestOnBoardConnectionPrgrN2(FwPrDesc_t prDesc)
{
  prDataPrgrAction_t* prDataPrgrActionPtr;

  /* Set action outcome to 'continue' */
  /*printf("CrPsTestOnBoardConnectionPrgrN2()\n");*/

  prDataPrgrActionPtr = FwPrGetData(prDesc);

  prDataPrgrActionPtr->outcome = 2;
  FwPrSetData(prDesc, prDataPrgrActionPtr);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N3. */
void CrPsTestOnBoardConnectionPrgrN3(FwPrDesc_t prDesc)
{
  prDataPrgrAction_t* prDataPrgrActionPtr;

  /* Set action outcome to 'failed' */
  /*printf("CrPsTestOnBoardConnectionPrgrN3()\n");*/

  prDataPrgrActionPtr = FwPrGetData(prDesc);

  prDataPrgrActionPtr->outcome = 4;
  FwPrSetData(prDesc, prDataPrgrActionPtr);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N4. */
void CrPsTestOnBoardConnectionPrgrN4(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* Release (17,4) report */
  /* The (17,4) report has been retrieved from the OutFactory by the Start Action of the (17,3) */
  /*printf("CrPsTestOnBoardConnectionPrgrN4()\n");*/

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
  unsigned short appId;
  int timeOut;

  /* [ (areYouAliveSrc > 0) &&
       (time elapsed since command execution started smaller than areYouAliveTimeOut) ] */
  /*printf("CrPsTestOnBoardConnectionPrgrG11()\n");*/

  /* Get areYouAliveSrc from data pool */
  appId = getDpAreYouAliveSrc();

  /* Get areYouAliveTimeOut from data pool */
  timeOut = getDpAreYouAliveTimeOut();

  /*printf("CrPsTestOnBoardConnectionPrgrG11(): appId = %d, timeOut_cnt = %d, timeOut = %d\n", appId, timeOut_cnt, timeOut);*/

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
  unsigned short appId;
  int timeOut;

  /* [ (areYouAliveSrc == 0) &&
        (time elapsed since command execution started smaller than areYouAliveTimeOut) ] */
  /*printf("CrPsTestOnBoardConnectionPrgrG12()\n");*/

  /* Get areYouAliveSrc from data pool */
  appId = getDpAreYouAliveSrc();

  /* Get areYouAliveTimeOut from data pool */
  timeOut = getDpAreYouAliveTimeOut();

  /*printf("CrPsTestOnBoardConnectionPrgrG11(): appId = %d, timeOut_cnt = %d, timeOut = %d\n", appId, timeOut_cnt, timeOut);*/

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
  int timeOut;

  /* [ (time elapsed since command execution started equal or greater than areYouAliveTimeOut) ] */
  /*printf("CrPsTestOnBoardConnectionPrgrG13()\n");*/

  /* Get areYouAliveTimeOut from data pool */
  timeOut = getDpAreYouAliveTimeOut();

  /*printf("CrPsTestOnBoardConnectionPrgrG11(): timeOut_cnt = %d, timeOut = %d\n", timeOut_cnt, timeOut);*/

  if (timeOut_cnt >= timeOut)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}
