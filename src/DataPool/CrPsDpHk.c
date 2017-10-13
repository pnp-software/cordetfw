/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-10-06 18:28:46
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsDpHk.h"


DpHkParams_t dpHkParams ;
DpHkVars_t dpHkVars ;

/**
 * Initialises Hk
 */
void initDpHk(void)
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

  static uint16_t initsampleBufId[HK_N_REP_DEF];
  for (i=0;i<HK_N_REP_DEF;i++)
  {
    initsampleBufId[i] = 0;
  }

  static uint16_t initlstId[HK_MAX_N_ITEMS];
  for (i=0;i<HK_MAX_N_ITEMS;i++)
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



  memcpy(dpHkParams.debugVarAddr, initdebugVarAddr, sizeof(dpHkParams.debugVarAddr));
  memcpy(dpHkParams.dest, initdest, sizeof(dpHkParams.dest));
  memcpy(dpHkParams.isEnabled, initisEnabled, sizeof(dpHkParams.isEnabled));
  memcpy(dpHkParams.sid, initsid, sizeof(dpHkParams.sid));
  memcpy(dpHkVars.cycleCnt, initcycleCnt, sizeof(dpHkVars.cycleCnt));
  memcpy(dpHkVars.debugVar, initdebugVar, sizeof(dpHkVars.debugVar));
  memcpy(dpHkVars.lstId, initlstId, sizeof(dpHkVars.lstId));
  memcpy(dpHkVars.lstNSampRep, initlstNSampRep, sizeof(dpHkVars.lstNSampRep));
  memcpy(dpHkVars.lstSampleRep, initlstSampleRep, sizeof(dpHkVars.lstSampleRep));
  memcpy(dpHkVars.nSimple, initnSimple, sizeof(dpHkVars.nSimple));
  memcpy(dpHkVars.sampleBufId, initsampleBufId, sizeof(dpHkVars.sampleBufId));
}
