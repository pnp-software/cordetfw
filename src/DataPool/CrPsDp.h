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
  DpIdParamsHighest = 8,
  DpIddebugVarAddr = 1,
  DpIddest = 2,
  DpIdisEnabled = 3,
  DpIdperiod = 4,
  DpIdsid = 5,
  DpIdlptTimeOut = 6,
  DpIdAreYouAliveTimeOut = 7,
  DpIdOnBoardConnectDestLst = 8,
  /* Variables */
  DpIdVarsLowest = 9,
  DpIdVarsHighest = 64,
  DpIdisEidEnabled = 9,
  DpIdlastEvtEid_1 = 10,
  DpIdlastEvtEid_2 = 11,
  DpIdlastEvtEid_3 = 12,
  DpIdlastEvtEid_4 = 13,
  DpIdlastEvtTime_1 = 14,
  DpIdlastEvtTime_2 = 15,
  DpIdlastEvtTime_3 = 16,
  DpIdlastEvtTime_4 = 17,
  DpIdnOfDetectedEvts_1 = 18,
  DpIdnOfDetectedEvts_2 = 19,
  DpIdnOfDetectedEvts_3 = 20,
  DpIdnOfDetectedEvts_4 = 21,
  DpIdnOfDisabledEid_1 = 22,
  DpIdnOfDisabledEid_2 = 23,
  DpIdnOfDisabledEid_3 = 24,
  DpIdnOfDisabledEid_4 = 25,
  DpIdnOfGenEvtRep_1 = 26,
  DpIdnOfGenEvtRep_2 = 27,
  DpIdnOfGenEvtRep_3 = 28,
  DpIdnOfGenEvtRep_4 = 29,
  DpIdcycleCnt = 30,
  DpIddebugVar = 31,
  DpIdlstId = 32,
  DpIdlstNSampRep = 33,
  DpIdlstSampleRep = 34,
  DpIdnSimple = 35,
  DpIdsampleBufId = 36,
  DpIdlargeMsgTransId = 37,
  DpIdlptFailCode = 38,
  DpIdlptRemSize = 39,
  DpIdlptSize = 40,
  DpIdlptSrc = 41,
  DpIdlptTime = 42,
  DpIdnOfDownlinks = 43,
  DpIdnOfUplinks = 44,
  DpIdpartSeqNmb = 45,
  DpIdfailCodeAccFailed = 46,
  DpIdfailCodePrgrFailed = 47,
  DpIdfailCodeStartFailed = 48,
  DpIdfailCodeTermFailed = 49,
  DpIdinvDestRerouting = 50,
  DpIdnOfAccFailed = 51,
  DpIdnOfPrgrFailed = 52,
  DpIdnOfReroutingFailed = 53,
  DpIdnOfStartFailed = 54,
  DpIdnOfTermFailed = 55,
  DpIdpcktIdAccFailed = 56,
  DpIdpcktIdPrgrFailed = 57,
  DpIdpcktIdReroutingFailed = 58,
  DpIdpcktIdStartFailed = 59,
  DpIdpcktIdTermFailed = 60,
  DpIdstepPrgrFailed = 61,
  DpIdverFailData = 62,
  DpIdAreYouAliveSrc = 63,
  DpIdOnBoardConnectDest = 64
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
