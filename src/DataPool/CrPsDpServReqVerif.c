/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-10-13 12:48:17
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsDpServReqVerif.h"

DpServReqVerifVars_t dpServReqVerifVars ;

/**
 * Initialises ServReqVerif
 */
void initDpServReqVerif(void)
{
  dpServReqVerifVars.failCodeAccFailed = 0;
  dpServReqVerifVars.failCodePrgrFailed = 0;
  dpServReqVerifVars.failCodeStartFailed = 0;
  dpServReqVerifVars.failCodeTermFailed = 0;
  dpServReqVerifVars.invDestRerouting = 0;
  dpServReqVerifVars.nOfAccFailed = 0;
  dpServReqVerifVars.nOfPrgrFailed = 0;
  dpServReqVerifVars.nOfReroutingFailed = 0;
  dpServReqVerifVars.nOfStartFailed = 0;
  dpServReqVerifVars.nOfTermFailed = 0;
  dpServReqVerifVars.pcktIdAccFailed = 0;
  dpServReqVerifVars.pcktIdPrgrFailed = 0;
  dpServReqVerifVars.pcktIdReroutingFailed = 0;
  dpServReqVerifVars.pcktIdStartFailed = 0;
  dpServReqVerifVars.pcktIdTermFailed = 0;
  dpServReqVerifVars.stepPrgrFailed = 0;
  dpServReqVerifVars.verFailData = 0;
}
