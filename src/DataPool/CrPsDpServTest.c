/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-08-07 09:38:54
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#include <string.h>
#include "CrPsDpServTest.h"

DpServTest_t dpServTest ;

/**
 * Initialises ServTest
 */
void initDpServTest(void)
{
  static const uint16_t initOnBoardConnectDestLst[10] = {0,0,0,0,0,0,0,0,0,0};

  dpServTest.AreYouAliveTimeOut = 10;
  memcpy(dpServTest.OnBoardConnectDestLst, initOnBoardConnectDestLst, sizeof(dpServTest.OnBoardConnectDestLst));
  dpServTest.AreYouAliveSrc = 0;
  dpServTest.OnBoardConnectDest = 0;
}
