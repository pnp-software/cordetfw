/**
 * @file CrPsDpServEvt.c
 * @ingroup Serv5
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

#include "CrPsDpServEvt.h"

DpServEvtVars_t dpServEvtVars ;

/**
 * Initialises ServEvt
 */
void initDpServEvt(void)
{
  uint32_t i;

  static CrPsFlag_t initisEidEnabled[EVT_N_EID];
  for (i=0;i<EVT_N_EID;i++)
  {
    initisEidEnabled[i] = 0;
  }

  memcpy(dpServEvtVars.isEidEnabled, initisEidEnabled, sizeof(dpServEvtVars.isEidEnabled));
  dpServEvtVars.lastEvtEid_1 = 0;
  dpServEvtVars.lastEvtEid_2 = 0;
  dpServEvtVars.lastEvtEid_3 = 0;
  dpServEvtVars.lastEvtEid_4 = 0;
  for (i=0;i<6;i++)
  {
    dpServEvtVars.lastEvtTime_1.t[i] = 0; 
    dpServEvtVars.lastEvtTime_2.t[i] = 0; 
    dpServEvtVars.lastEvtTime_3.t[i] = 0; 
    dpServEvtVars.lastEvtTime_4.t[i] = 0; 
  }
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
