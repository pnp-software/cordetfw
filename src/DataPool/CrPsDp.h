/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-10-03 10:29:40
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSDP_H_
#define CRPSDP_H_

#include "CrPsDpTypes.h"

enum {
  /* Parameters */
  DpIdParamsLowest = 1,
  DpIdParamsHighest = 6,
  DpIddebugVarAddr = 1,
  DpIddest = 2,
  DpIdisEnabled = 3,
  DpIdsid = 4,
  DpIdAreYouAliveTimeOut = 5,
  DpIdOnBoardConnectDestLst = 6,
  /* Variables */
  DpIdVarsLowest = 7,
  DpIdVarsHighest = 49,
  DpIdisEidEnabled = 7,
  DpIdlastEvtEid_1 = 8,
  DpIdlastEvtEid_2 = 9,
  DpIdlastEvtEid_3 = 10,
  DpIdlastEvtEid_4 = 11,
  DpIdlastEvtTime_1 = 12,
  DpIdlastEvtTime_2 = 13,
  DpIdlastEvtTime_3 = 14,
  DpIdlastEvtTime_4 = 15,
  DpIdnOfDetectedEvts_1 = 16,
  DpIdnOfDetectedEvts_2 = 17,
  DpIdnOfDetectedEvts_3 = 18,
  DpIdnOfDetectedEvts_4 = 19,
  DpIdnOfDisabledEid_1 = 20,
  DpIdnOfDisabledEid_2 = 21,
  DpIdnOfDisabledEid_3 = 22,
  DpIdnOfDisabledEid_4 = 23,
  DpIdnOfGenEvtRep_1 = 24,
  DpIdnOfGenEvtRep_2 = 25,
  DpIdnOfGenEvtRep_3 = 26,
  DpIdnOfGenEvtRep_4 = 27,
  DpIdcycleCnt = 28,
  DpIddebugVar = 29,
  DpIdsampleBufId = 30,
  DpIdfailCodeAccFailed = 31,
  DpIdfailCodePrgrFailed = 32,
  DpIdfailCodeStartFailed = 33,
  DpIdfailCodeTermFailed = 34,
  DpIdinvDestRerouting = 35,
  DpIdnOfAccFailed = 36,
  DpIdnOfPrgrFailed = 37,
  DpIdnOfReroutingFailed = 38,
  DpIdnOfStartFailed = 39,
  DpIdnOfTermFailed = 40,
  DpIdpcktIdAccFailed = 41,
  DpIdpcktIdPrgrFailed = 42,
  DpIdpcktIdReroutingFailed = 43,
  DpIdpcktIdStartFailed = 44,
  DpIdpcktIdTermFailed = 45,
  DpIdstepPrgrFailed = 46,
  DpIdverFailData = 47,
  DpIdAreYouAliveSrc = 48,
  DpIdOnBoardConnectDest = 49
};

/**
 * Get the value of a datapool item by identifier.
 * \param id The datapool item identifier
 * \param dest The address of the target variable where the value gets copied
 * to.
 * \return Number of bytes copied. 0 if id is invalid.
 */
extern int getDpValue(ParameterId_t id, void* dest);
/**
 * Set the value of a datapool item by identifier
 * \param id The datapool item identifier
 * \param src The address of the source variable where the value gets copied
 * from.
 * \return Number of bytes copied. 0 if id is invalid.
 */
extern int setDpValue(ParameterId_t id, const void* src);
/**
 * Get the size of a datapool item by identifier.
 * \param id The datapool item identifier
 * \return The size of the datapool parameter. 0 if id is invalid.
 */
extern int getDpSize(ParameterId_t id);
/**
 * Get the size of a datapool parameter by identifier.
 * \param id The datapool parameter identifier
 * \return The size of the datapool parameter. 0 if id is invalid.
 */
extern int getDpParamSize(ParameterId_t id);
/**
 * Get the size of a datapool variable by identifier.
 * \param id The datapool variable identifier
 * \return The size of the datapool variable. 0 if id is invalid.
 */
extern int getDpVarSize(ParameterId_t id);

/*----------------------------------------------------------------------------*/
#endif /* CRPSDP_H */
