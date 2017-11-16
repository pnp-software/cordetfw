/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-10-13 12:48:17
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsDpServTest.h"

DpServTestParams_t dpServTestParams ;
DpServTestVars_t dpServTestVars ;

/**
 * Initialises ServTest
 */
void initDpServTest(void)
{
  uint32_t i;

  static CrPsDestSrc_t initOnBoardConnectDestLst[TEST_MAX_APP];
  for (i=0;i<TEST_MAX_APP;i++)
  {
    initOnBoardConnectDestLst[i] = 0;
  }

  dpServTestParams.AreYouAliveTimeOut = 10;
  memcpy(dpServTestParams.OnBoardConnectDestLst, initOnBoardConnectDestLst, sizeof(dpServTestParams.OnBoardConnectDestLst));
  dpServTestVars.AreYouAliveSrc = 0;
  dpServTestVars.OnBoardConnectDest = 0;
}
