/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-08-22 17:43:36
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSDP_H_
#define CRPSDP_H_


#include <stdio.h> /* brauche ich für size_t */
typedef unsigned int ParameterId_t; /* brauche ich auch */


enum {
  /* Parameters */
  DpIdParamsLowest = 1,
  DpIdParamsHighest = 6,
  DpIddebugVarAddr = 1,
  DpIddest = 2,
  DpIdisEnabledPar = 3,
  DpIdsid = 4,
  DpIdAreYouAliveTimeOut = 5,
  DpIdOnBoardConnectDestLst = 6,
  /* Variables */
  DpIdVarsLowest = 7,
  DpIdVarsHighest = 29,
  DpIdcycleCnt = 7,
  DpIddebugVar = 8,
  DpIdisEnabledVar = 9,
  DpIdsampleBufId = 10,
  DpIdfailCodeAccFailed = 11,
  DpIdfailCodePrgrFailed = 12,
  DpIdfailCodeStartFailed = 13,
  DpIdfailCodeTermFailed = 14,
  DpIdinvDestRerouting = 15,
  DpIdnOfAccFailed = 16,
  DpIdnOfPrgrFailed = 17,
  DpIdnOfReroutingFailed = 18,
  DpIdnOfStartFailed = 19,
  DpIdnOfTermFailed = 20,
  DpIdpcktIdAccFailed = 21,
  DpIdpcktIdPrgrFailed = 22,
  DpIdpcktIdReroutingFailed = 23,
  DpIdpcktIdStartFailed = 24,
  DpIdpcktIdTermFailed = 25,
  DpIdstepPrgrFailed = 26,
  DpIdverFailData = 27,
  DpIdAreYouAliveSrc = 28,
  DpIdOnBoardConnectDest = 29
};

/**
 * Get the value of a datapool item by identifier.
 * \param id The datapool item identifier
 * \param dest The address of the target variable where the value gets copied
 * to.
 * \return 0 when id denotes a valid identifier; -1 otherwise.
 */
extern int getDpValue(ParameterId_t id, void* dest);
/**
 * Set the value of a datapool item by identifier
 * \param id The datapool item identifier
 * \param src The address of the source variable where the value gets copied
 * from.
 * \return 0 when id denotes a valid identifier; -1 otherwise.
 */
extern int setDpValue(ParameterId_t id, const void* src);
/**
 * Get the size of a datapool item by identifier.
 * \param id The datapool item identifier
 * \param size The address where the size of the datapool item is written to.
 * \return 0 when id denotes a valid identifier; -1 otherwise.
 */
extern int getDpSize(ParameterId_t id, size_t* size);
#endif /* CRPSDP_H */
