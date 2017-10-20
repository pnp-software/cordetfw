/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-10-13 12:48:17
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSDP_H_
#define CRPSDP_H_

#include "CrPsDpTypes.h"

enum {
  /* Parameters */
  DpIdParamsLowest = 1,
  DpIdParamsHighest = 7,
  DpIddebugVarAddr = 1,
  DpIddest = 2,
  DpIdisEnabled = 3,
  DpIdperiod = 4,
  DpIdsid = 5,
  DpIdAreYouAliveTimeOut = 6,
  DpIdOnBoardConnectDestLst = 7,
  /* Variables */
  DpIdVarsLowest = 8,
  DpIdVarsHighest = 54,
  DpIdisEidEnabled = 8,
  DpIdlastEvtEid_1 = 9,
  DpIdlastEvtEid_2 = 10,
  DpIdlastEvtEid_3 = 11,
  DpIdlastEvtEid_4 = 12,
  DpIdlastEvtTime_1 = 13,
  DpIdlastEvtTime_2 = 14,
  DpIdlastEvtTime_3 = 15,
  DpIdlastEvtTime_4 = 16,
  DpIdnOfDetectedEvts_1 = 17,
  DpIdnOfDetectedEvts_2 = 18,
  DpIdnOfDetectedEvts_3 = 19,
  DpIdnOfDetectedEvts_4 = 20,
  DpIdnOfDisabledEid_1 = 21,
  DpIdnOfDisabledEid_2 = 22,
  DpIdnOfDisabledEid_3 = 23,
  DpIdnOfDisabledEid_4 = 24,
  DpIdnOfGenEvtRep_1 = 25,
  DpIdnOfGenEvtRep_2 = 26,
  DpIdnOfGenEvtRep_3 = 27,
  DpIdnOfGenEvtRep_4 = 28,
  DpIdcycleCnt = 29,
  DpIddebugVar = 30,
  DpIdlstId = 31,
  DpIdlstNSampRep = 32,
  DpIdlstSampleRep = 33,
  DpIdnSimple = 34,
  DpIdsampleBufId = 35,
  DpIdfailCodeAccFailed = 36,
  DpIdfailCodePrgrFailed = 37,
  DpIdfailCodeStartFailed = 38,
  DpIdfailCodeTermFailed = 39,
  DpIdinvDestRerouting = 40,
  DpIdnOfAccFailed = 41,
  DpIdnOfPrgrFailed = 42,
  DpIdnOfReroutingFailed = 43,
  DpIdnOfStartFailed = 44,
  DpIdnOfTermFailed = 45,
  DpIdpcktIdAccFailed = 46,
  DpIdpcktIdPrgrFailed = 47,
  DpIdpcktIdReroutingFailed = 48,
  DpIdpcktIdStartFailed = 49,
  DpIdpcktIdTermFailed = 50,
  DpIdstepPrgrFailed = 51,
  DpIdverFailData = 52,
  DpIdAreYouAliveSrc = 53,
  DpIdOnBoardConnectDest = 54
};

/**
 * Get the value of a datapool item by identifier.
 * \param id The datapool item identifier
 * \param dest The address of the target variable where the value gets copied
 * to.
 * \return Number of bytes copied. 0 if id is invalid.
 */
extern size_t getDpValue(ParameterId_t id, void* dest);
/**
 * Get the value of a datapool item plus meta information by identifier.
 * \param id The datapool item identifier
 * \param dest The address of the target variable where the value gets copied
 * to.
 * \param pElementLength Pointer to where the element size is copied to.
 * \param pNElements Pointer to where the number of elements is copied
 * to.\return Number of bytes copied. 0 if id is invalid.
 */
extern size_t getDpValueEx(ParameterId_t id, void* dest, size_t* pElementLength, unsigned int* pNElements);
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
extern size_t getDpSize(ParameterId_t id);
/**
 * Get the size of a datapool parameter by identifier.
 * \param id The datapool parameter identifier
 * \return The size of the datapool parameter. 0 if id is invalid.
 */
extern size_t getDpParamSize(ParameterId_t id);
/**
 * Get the size of a datapool variable by identifier.
 * \param id The datapool variable identifier
 * \return The size of the datapool variable. 0 if id is invalid.
 */
extern size_t getDpVarSize(ParameterId_t id);

/*----------------------------------------------------------------------------*/
#endif /* CRPSDP_H */
