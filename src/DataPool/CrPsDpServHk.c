/**
 * @file CrPsDpServHk.c
 * @ingroup Serv3
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

#include "CrPsDpServHk.h"

DpServHkParams_t dpServHkParams ;
DpServHkVars_t dpServHkVars ;

/**
 * Initialises ServHk
 */
void initDpServHk(void)
{
  uint32_t i;

  static CrPsAddr_t initdebugVarAddr[HK_N_DEBUG_VAR];
  for (i=0;i<HK_N_DEBUG_VAR;i++)
  {
    initdebugVarAddr[i] = 0;
  }

  static CrPsDestSrc_t initdest[HK_N_REP_DEF];
  for (i=0;i<HK_N_REP_DEF;i++)
  {
    initdest[i] = 0;
  }

  static CrPsFlag_t initisEnabled[HK_N_REP_DEF];
  for (i=0;i<HK_N_REP_DEF;i++)
  {
    initisEnabled[i] = 0;
  }

  static CrPsPeriod_t initperiod[HK_N_REP_DEF];
  for (i=0;i<HK_N_REP_DEF;i++)
  {
    initperiod[i] = 0;
  }

  static CrPsSid_t initsid[HK_N_REP_DEF];
  for (i=0;i<HK_N_REP_DEF;i++)
  {
    initsid[i] = 0;
  }

  static CrFwCounterU4_t initcycleCnt[HK_N_REP_DEF];
  for (i=0;i<HK_N_REP_DEF;i++)
  {
    initcycleCnt[i] = 0;
  }

  static CrPsValueU4_t initdebugVar[HK_N_DEBUG_VAR];
  for (i=0;i<HK_N_DEBUG_VAR;i++)
  {
    initdebugVar[i] = 0;
  }

  static CrPsParamId_t initlstId[HK_N_REP_DEF*HK_MAX_N_ITEMS];
  for (i=0;i<HK_N_REP_DEF*HK_MAX_N_ITEMS;i++)
  {
    initlstId[i] = 0;
  }

  static CrPsNumberU2_t initlstNSampRep[HK_N_REP_DEF*HK_MAX_N_GR];
  for (i=0;i<HK_N_REP_DEF*HK_MAX_N_GR;i++)
  {
    initlstNSampRep[i] = 0;
  }

  static CrPsRepetition_t initlstSampleRep[HK_N_REP_DEF*HK_MAX_N_GR];
  for (i=0;i<HK_N_REP_DEF*HK_MAX_N_GR;i++)
  {
    initlstSampleRep[i] = 0;
  }

  static CrPsNumberU2_t initnSimple[HK_N_REP_DEF];
  for (i=0;i<HK_MAX_N_SIMPLE;i++)
  {
    initnSimple[i] = 0;
  }

  static CrPsParamId_t initsampleBufId[HK_N_REP_DEF];
  for (i=0;i<HK_N_REP_DEF;i++)
  {
    initsampleBufId[i] = 0;
  }

  memcpy(dpServHkParams.debugVarAddr, initdebugVarAddr, sizeof(dpServHkParams.debugVarAddr));
  memcpy(dpServHkParams.dest, initdest, sizeof(dpServHkParams.dest));
  memcpy(dpServHkParams.isEnabled, initisEnabled, sizeof(dpServHkParams.isEnabled));
  memcpy(dpServHkParams.period, initperiod, sizeof(dpServHkParams.period));
  memcpy(dpServHkParams.sid, initsid, sizeof(dpServHkParams.sid));
  memcpy(dpServHkVars.cycleCnt, initcycleCnt, sizeof(dpServHkVars.cycleCnt));
  memcpy(dpServHkVars.debugVar, initdebugVar, sizeof(dpServHkVars.debugVar));
  memcpy(dpServHkVars.lstId, initlstId, sizeof(dpServHkVars.lstId));
  memcpy(dpServHkVars.lstNSampRep, initlstNSampRep, sizeof(dpServHkVars.lstNSampRep));
  memcpy(dpServHkVars.lstSampleRep, initlstSampleRep, sizeof(dpServHkVars.lstSampleRep));
  memcpy(dpServHkVars.nSimple, initnSimple, sizeof(dpServHkVars.nSimple));
  memcpy(dpServHkVars.sampleBufId, initsampleBufId, sizeof(dpServHkVars.sampleBufId));
}
