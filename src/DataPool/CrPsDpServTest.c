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
   dpServTest.AreYouAliveTimeOut = 10;
   dpServTest.OnBoardConnectDestLst[0] = 0;
   dpServTest.OnBoardConnectDestLst[1] = 0;
   dpServTest.OnBoardConnectDestLst[2] = 0;
   dpServTest.OnBoardConnectDestLst[3] = 0;
   dpServTest.OnBoardConnectDestLst[4] = 0;
   dpServTest.OnBoardConnectDestLst[5] = 0;
   dpServTest.OnBoardConnectDestLst[6] = 0;
   dpServTest.OnBoardConnectDestLst[7] = 0;
   dpServTest.OnBoardConnectDestLst[8] = 0;
   dpServTest.OnBoardConnectDestLst[9] = 0;
   dpServTest.AreYouAliveSrc = 0;
   dpServTest.OnBoardConnectDest = 0;
}
