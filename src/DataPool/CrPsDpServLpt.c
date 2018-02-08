/**
 * @file CrPsDpServLpt.c
 * @ingroup Serv13
 * @ingroup DataPool
 *
 * @brief Interface for accessing data pool items.
 *
 * @note This file was generated on 2017-11-22 12:47:43
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

#include "CrPsDpServLpt.h"
#include <CrPsUserConstants.h>

DpServLptParams_t dpServLptParams ;
DpServLptVars_t dpServLptVars ;

/**
 * Initialises ServLpt
 */
void initDpServLpt(void)
{
  uint32_t i, j;

  static CrPsTimeOut_t initlptTimeOut[LPT_N_BUF];
  for (i=0;i<LPT_N_BUF;i++)
  {
    initlptTimeOut[i] = LPT_UP_TIMEOUT;
  }

  static CrPsTid_t initlargeMsgTransId[LPT_N_BUF];
  for (i=0;i<LPT_N_BUF;i++)
  {
    initlargeMsgTransId[i] = 0;
  }

  static CrPsFailCode_t initlptFailCode[LPT_N_BUF];
  for (i=0;i<LPT_N_BUF;i++)
  {
    initlptFailCode[i] = 0;
  }

  static CrPsSize_t initlptRemSize[LPT_N_BUF];
  for (i=0;i<LPT_N_BUF;i++)
  {
    initlptRemSize[i] = 0;
  }

  static CrPsSize_t initlptSize[LPT_N_BUF];
  for (i=0;i<LPT_N_BUF;i++)
  {
    initlptSize[i] = 0;
  }

  static CrPsDestSrc_t initlptSrc[LPT_N_BUF];
  for (i=0;i<LPT_N_BUF;i++)
  {
    initlptSrc[i] = 0;
  }

  static CrFwTimeStamp_t initlptTime[LPT_N_BUF];
  for (i=0;i<LPT_N_BUF;i++)
  {
    for (j=0;j<6;j++)
    {
      initlptTime[i].t[j] = 0;
    }
  }

  static CrFwCounterU4_t initpartSeqNmb[LPT_N_BUF];
  for (i=0;i<LPT_N_BUF;i++)
  {
    initpartSeqNmb[i] = 0;
  }

  memcpy(dpServLptParams.lptTimeOut, initlptTimeOut, sizeof(dpServLptParams.lptTimeOut));
  memcpy(dpServLptVars.largeMsgTransId, initlargeMsgTransId, sizeof(dpServLptVars.largeMsgTransId));
  memcpy(dpServLptVars.lptFailCode, initlptFailCode, sizeof(dpServLptVars.lptFailCode));
  memcpy(dpServLptVars.lptRemSize, initlptRemSize, sizeof(dpServLptVars.lptRemSize));
  memcpy(dpServLptVars.lptSize, initlptSize, sizeof(dpServLptVars.lptSize));
  memcpy(dpServLptVars.lptSrc, initlptSrc, sizeof(dpServLptVars.lptSrc));
  memcpy(dpServLptVars.lptTime, initlptTime, sizeof(dpServLptVars.lptTime));
  dpServLptVars.nOfDownlinks = 0;
  dpServLptVars.nOfUplinks = 0;
  memcpy(dpServLptVars.partSeqNmb, initpartSeqNmb, sizeof(dpServLptVars.partSeqNmb));
}
