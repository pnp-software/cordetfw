/**
 * @file CrPsDpServTest.c
 * @ingroup Serv17
 * @ingroup DataPool
 *
 * @brief Interface for accessing data pool items.
 *
 * @note This file was generated on 2017-10-13 12:48:17
 * @author PnP Generator
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * 
 * last modification: 22.01.2018
 * 
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
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
