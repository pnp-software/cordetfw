/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-10-03 10:29:40
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsDpEvt.h"

DpEvtVars_t dpEvtVars;

/**
 * Initialises Evt
 */
void initDpEvt(void)
{
  static const uint8_t initisEidEnabled[3] = {0,0,0};

  memcpy(dpEvtVars.isEidEnabled, initisEidEnabled, sizeof(dpEvtVars.isEidEnabled));
  dpEvtVars.lastEvtEid_1 = 0;
  dpEvtVars.lastEvtEid_2 = 0;
  dpEvtVars.lastEvtEid_3 = 0;
  dpEvtVars.lastEvtEid_4 = 0;
  dpEvtVars.lastEvtTime_1 = 0;
  dpEvtVars.lastEvtTime_2 = 0;
  dpEvtVars.lastEvtTime_3 = 0;
  dpEvtVars.lastEvtTime_4 = 0;
  dpEvtVars.nOfDetectedEvts_1 = 0;
  dpEvtVars.nOfDetectedEvts_2 = 0;
  dpEvtVars.nOfDetectedEvts_3 = 0;
  dpEvtVars.nOfDetectedEvts_4 = 0;
  dpEvtVars.nOfDisabledEid_1 = 0;
  dpEvtVars.nOfDisabledEid_2 = 0;
  dpEvtVars.nOfDisabledEid_3 = 0;
  dpEvtVars.nOfDisabledEid_4 = 0;
  dpEvtVars.nOfGenEvtRep_1 = 0;
  dpEvtVars.nOfGenEvtRep_2 = 0;
  dpEvtVars.nOfGenEvtRep_3 = 0;
  dpEvtVars.nOfGenEvtRep_4 = 0;
}
