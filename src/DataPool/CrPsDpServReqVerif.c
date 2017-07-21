/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-07-24 16:05:36
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
   dpServReqVerif = (DpServReqVerif_t){
      .failCodeAccFailed = 0,
      .failCodePrgrFailed = 0,
      .failCodeStartFailed = 0,
      .failCodeTermFailed = 0,
      .invDestRerouting = 0,
      .nOfAccFailed = 0,
      .nOfPrgrFailed = 0,
      .nOfReroutingFailed = 0,
      .nOfStartFailed = 0,
      .nOfTermFailed = 0,
      .pcktIdAccFailed = 0,
      .pcktIdPrgrFailed = 0,
      .pcktIdReroutingFailed = 0,
      .pcktIdStartFailed = 0,
      .pcktIdTermFailed = 0,
      .stepPrgrFailed = 0,
      .verFailData = 0
   };
}
