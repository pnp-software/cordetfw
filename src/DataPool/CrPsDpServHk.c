/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-10-13 12:48:17
 * \author PnP Generator
 * \copyright (c) Copyright
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

  static uint32_t initdebugVarAddr[HK_N_DEBUG_VAR];
  for (i=0;i<HK_N_DEBUG_VAR;i++)
  {
    initdebugVarAddr[i] = 0;
  }

  static uint16_t initdest[HK_N_REP_DEF];
  for (i=0;i<HK_N_REP_DEF;i++)
  {
    initdest[i] = 0;
  }

  static uint8_t initisEnabled[HK_N_REP_DEF];
  for (i=0;i<HK_N_REP_DEF;i++)
  {
    initisEnabled[i] = 0;
  }

  static uint32_t initperiod[HK_N_REP_DEF];
  for (i=0;i<HK_N_REP_DEF;i++)
  {
    initperiod[i] = 0;
  }

  static uint16_t initsid[HK_N_REP_DEF];
  for (i=0;i<HK_N_REP_DEF;i++)
  {
    initsid[i] = 0;
  }

  static uint32_t initcycleCnt[HK_N_REP_DEF];
  for (i=0;i<HK_N_REP_DEF;i++)
  {
    initcycleCnt[i] = 0;
  }

  static uint32_t initdebugVar[HK_N_DEBUG_VAR];
  for (i=0;i<HK_N_DEBUG_VAR;i++)
  {
    initdebugVar[i] = 0;
  }

  static uint16_t initlstId[HK_MAX_N_ITEMS*HK_MAX_SID];
  for (i=0;i<HK_MAX_N_ITEMS*HK_MAX_SID;i++)
  {
    initlstId[i] = 0;
  }

  static uint16_t initlstNSampRep[HK_MAX_N_REP];
  for (i=0;i<HK_MAX_N_REP;i++)
  {
    initlstNSampRep[i] = 0;
  }

  static uint16_t initlstSampleRep[HK_MAX_N_GR];
  for (i=0;i<HK_MAX_N_GR;i++)
  {
    initlstSampleRep[i] = 0;
  }

  static uint16_t initnSimple[HK_MAX_N_SIMPLE];
  for (i=0;i<HK_MAX_N_SIMPLE;i++)
  {
    initnSimple[i] = 0;
  }

  static uint16_t initsampleBufId[HK_N_REP_DEF];
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