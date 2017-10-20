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
  static const uint16_t initOnBoardConnectDestLst[10] = {0,0,0,0,0,0,0,0,0,0};

  dpServTestParams.AreYouAliveTimeOut = 10;
  memcpy(dpServTestParams.OnBoardConnectDestLst, initOnBoardConnectDestLst, sizeof(dpServTestParams.OnBoardConnectDestLst));
  dpServTestVars.AreYouAliveSrc = 0;
  dpServTestVars.OnBoardConnectDest = 0;
}
