/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-08-22 17:43:36
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsDpServTest.h"
#include <stdlib.h>
#include <string.h>

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
