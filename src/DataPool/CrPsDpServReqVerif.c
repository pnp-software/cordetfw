/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-08-07 09:38:54
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsDpServReqVerif.h"

DpServReqVerif_t dpServReqVerif ;

/**
 * Initialises ServReqVerif
 */
void initDpServReqVerif(void)
{
  dpServReqVerif.failCodeAccFailed = 0;
  dpServReqVerif.failCodePrgrFailed = 0;
  dpServReqVerif.failCodeStartFailed = 0;
  dpServReqVerif.failCodeTermFailed = 0;
  dpServReqVerif.invDestRerouting = 0;
  dpServReqVerif.nOfAccFailed = 0;
  dpServReqVerif.nOfPrgrFailed = 0;
  dpServReqVerif.nOfReroutingFailed = 0;
  dpServReqVerif.nOfStartFailed = 0;
  dpServReqVerif.nOfTermFailed = 0;
  dpServReqVerif.pcktIdAccFailed = 0;
  dpServReqVerif.pcktIdPrgrFailed = 0;
  dpServReqVerif.pcktIdReroutingFailed = 0;
  dpServReqVerif.pcktIdStartFailed = 0;
  dpServReqVerif.pcktIdTermFailed = 0;
  dpServReqVerif.stepPrgrFailed = 0;
  dpServReqVerif.verFailData = 0;
}
