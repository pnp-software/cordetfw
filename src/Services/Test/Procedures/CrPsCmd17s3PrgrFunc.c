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

#include <DataPool/CrPsDataPool.h>
#include <DataPool/DpServTest.h>

#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsParamSetter.h>
#include <Services/Test/InCmd/CrPsTestOnBoardConnection.h> /* for global handles */

#include <stdio.h>


/* ------------------------------------------------------------------------------------ */
/* Action for node N1. */
void CrPsTestOnBoardConnectionPrgrN1(FwPrDesc_t __attribute__((unused)) prDesc)
{
  CrFwDestSrc_t destId;
  unsigned short appId;

  /* Configure the (17,4) report with a destination equal to the source of the (17,3),
     load it in the Outloader and set action outcome to 'completed' */

  /* The (17,4) report has been retrieved from the OutFactory by the Start Action of the (17,3) */

  printf("CrPsTestOnBoardConnectionPrgrN1()\n");

  /* Get application ID with which the test was performed */
  appId = getDpAreYouAliveSrc();

  /* Set out component parameters */
  CrPsServTestOnBoardConnectParamSetAppId(rep, appId);

  destId = 0; /* GRD, TODO: equal to the source of the (17,3) */
  CrFwOutCmpSetDest(rep, (CrFwDestSrc_t)destId);

  CrFwOutLoaderLoad(rep);

  /* set action outcome to 'completed' */

  /*cmpDataPrgr->outcome = 1;*/
  outcomePrgr = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N2. */
void CrPsTestOnBoardConnectionPrgrN2(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Set action outcome to 'continue' */

  printf("CrPsTestOnBoardConnectionPrgrN2()\n");

  /*cmpDataPrgr->outcome = 2;*/
  outcomePrgr = 2;

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N3. */
void CrPsTestOnBoardConnectionPrgrN3(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Set action outcome to 'completed' */
  /* TODO: should be failed? (reached timeout) */

  printf("CrPsTestOnBoardConnectionPrgrN3()\n");

  /*cmpDataPrgr->outcome = 1;*/
  outcomePrgr = 4;

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N4. */
void CrPsTestOnBoardConnectionPrgrN4(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Release (17,4) report */

  /* The (17,4) report has been retrieved from the OutFactory by the Start Action of the (17,3) */

  printf("CrPsTestOnBoardConnectionPrgrN4()\n");

  CrFwOutFactoryReleaseOutCmp(rep);

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/* Guard on the Control Flow from DECISION1 to N1. */
FwPrBool_t CrPsTestOnBoardConnectionPrgrG11(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /*FwPrCounterU3_t execCnt, nodeExecCnt;*/
  Time currentTime;
  unsigned short appId;
  int timeOut;

  /* [ (areYouAliveSrc > 0) &&
       (time elapsed since command execution started smaller than areYouAliveTimeOut) ] */

  printf("CrPsTestOnBoardConnectionPrgrG11()\n");

  /* Get areYouAliveSrc from data pool */
  appId = getDpAreYouAliveSrc();

  /* Get areYouAliveTimeOut from data pool */
  timeOut = getDpAreYouAliveTimeOut();

  /* get current time stamp */
  if (clock_gettime(CLOCK_MONOTONIC, &currentTime) == -1)
    {
      perror("clock_gettime error");
      return -1;
    }
  printf("CrPsTestOnBoardConnectionPrgrG11(): appId = %d, startTime = %ld, currentTime = %ld, timeOut = %d\n", appId, startTime.tv_sec, currentTime.tv_sec, timeOut);

  if (appId > 0 && (currentTime.tv_sec-startTime.tv_sec) < timeOut)
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
FwPrBool_t CrPsTestOnBoardConnectionPrgrG12(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /*FwPrCounterU3_t execCnt, nodeExecCnt;*/
  Time currentTime;
  unsigned short appId;
  int timeOut;

  /* [ (areYouAliveSrc == 0) &&
        (time elapsed since command execution started smaller than areYouAliveTimeOut) ] */

  printf("CrPsTestOnBoardConnectionPrgrG12()\n");

  /* Get areYouAliveSrc from data pool */
  appId = getDpAreYouAliveSrc();

  /* Get areYouAliveTimeOut from data pool */
  timeOut = getDpAreYouAliveTimeOut();

  /* get current time stamp */
  if (clock_gettime(CLOCK_MONOTONIC, &currentTime) == -1)
    {
      perror("clock_gettime error");
      return -1;
    }
  printf("CrPsTestOnBoardConnectionPrgrG12(): appId = %d, startTime = %ld, currentTime = %ld, timeOut = %d\n", appId, startTime.tv_sec, currentTime.tv_sec, timeOut);

  if (appId == 0 && (currentTime.tv_sec-startTime.tv_sec) < timeOut)
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
FwPrBool_t CrPsTestOnBoardConnectionPrgrG13(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /*FwPrCounterU3_t execCnt, nodeExecCnt;*/
  Time currentTime;
  int timeOut;

  /* [ (time elapsed since command execution started equal or greater than areYouAliveTimeOut) ] */

  printf("CrPsTestOnBoardConnectionPrgrG13()\n");

  /* Get areYouAliveTimeOut from data pool */
  timeOut = getDpAreYouAliveTimeOut();

  /* get current time stamp */
  if (clock_gettime(CLOCK_MONOTONIC, &currentTime) == -1)
    {
      perror("clock_gettime error");
      return -1;
    }
  printf("CrPsTestOnBoardConnectionPrgrG13(): startTime = %ld, currentTime = %ld, timeOut = %d\n", startTime.tv_sec, currentTime.tv_sec, timeOut);

  if ((currentTime.tv_sec-startTime.tv_sec) >= timeOut)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}
