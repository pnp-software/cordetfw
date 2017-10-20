/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-10-13 12:48:17
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsDpServEvt.h"

DpServEvtVars_t dpServEvtVars ;

/**
 * Initialises ServEvt
 */
void initDpServEvt(void)
{
  static const uint8_t initisEidEnabled[3] = {0,0,0};

  memcpy(dpServEvtVars.isEidEnabled, initisEidEnabled, sizeof(dpServEvtVars.isEidEnabled));
  dpServEvtVars.lastEvtEid_1 = 0;
  dpServEvtVars.lastEvtEid_2 = 0;
  dpServEvtVars.lastEvtEid_3 = 0;
  dpServEvtVars.lastEvtEid_4 = 0;
  dpServEvtVars.lastEvtTime_1 = 0;
  dpServEvtVars.lastEvtTime_2 = 0;
  dpServEvtVars.lastEvtTime_3 = 0;
  dpServEvtVars.lastEvtTime_4 = 0;
  dpServEvtVars.nOfDetectedEvts_1 = 0;
  dpServEvtVars.nOfDetectedEvts_2 = 0;
  dpServEvtVars.nOfDetectedEvts_3 = 0;
  dpServEvtVars.nOfDetectedEvts_4 = 0;
  dpServEvtVars.nOfDisabledEid_1 = 0;
  dpServEvtVars.nOfDisabledEid_2 = 0;
  dpServEvtVars.nOfDisabledEid_3 = 0;
  dpServEvtVars.nOfDisabledEid_4 = 0;
  dpServEvtVars.nOfGenEvtRep_1 = 0;
  dpServEvtVars.nOfGenEvtRep_2 = 0;
  dpServEvtVars.nOfGenEvtRep_3 = 0;
  dpServEvtVars.nOfGenEvtRep_4 = 0;
}
