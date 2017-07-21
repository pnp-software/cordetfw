/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-07-24 16:05:36
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsDpServTest.h"

DpServTest_t dpServTest ;

/**
 * Initialises ServTest
 */
void initDpServTest(void)
{
   dpServTest = (DpServTest_t){
      .AreYouAliveTimeOut = 10,
      .OnBoardConnectDestLst = {0,0,0,0,0,0,0,0,0,0},
      .AreYouAliveSrc = 0,
      .OnBoardConnectDest = 0
   };
}
