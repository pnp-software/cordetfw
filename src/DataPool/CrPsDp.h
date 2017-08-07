/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-08-07 09:38:54
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#include <stdio.h>

typedef enum {
  /* Parameters */
  DpIdParamsLowest = 0,
  DpIdParamsHighest = 1,
  DpIdAreYouAliveTimeOut = 0,
  DpIdOnBoardConnectDestLst = 1,
  /* Variables */
  DpIdVarsLowest = 2,
  DpIdVarsHighest = 20,
  DpIdfailCodeAccFailed = 2,
  DpIdfailCodePrgrFailed = 3,
  DpIdfailCodeStartFailed = 4,
  DpIdfailCodeTermFailed = 5,
  DpIdinvDestRerouting = 6,
  DpIdnOfAccFailed = 7,
  DpIdnOfPrgrFailed = 8,
  DpIdnOfReroutingFailed = 9,
  DpIdnOfStartFailed = 10,
  DpIdnOfTermFailed = 11,
  DpIdpcktIdAccFailed = 12,
  DpIdpcktIdPrgrFailed = 13,
  DpIdpcktIdReroutingFailed = 14,
  DpIdpcktIdStartFailed = 15,
  DpIdpcktIdTermFailed = 16,
  DpIdstepPrgrFailed = 17,
  DpIdverFailData = 18,
  DpIdAreYouAliveSrc = 19,
  DpIdOnBoardConnectDest = 20
} DatapoolId_t;

/**
 * Get the value of a datapool item by identifier.
 * \param id The datapool item identifier
 * \param dest The address of the target variable where the value gets copied
 * to.
 * \return 0 when id denotes a valid identifier; -1 otherwise.
 */
extern int getDpValue(DatapoolId_t id, void* dest);
/**
 * Set the value of a datapool item by identifier
 * \param id The datapool item identifier
 * \param src The address of the source variable where the value gets copied
 * from.
 * \return 0 when id denotes a valid identifier; -1 otherwise.
 */
extern int setDpValue(DatapoolId_t id, const void* src);
/**
 * Get the size of a datapool item by identifier.
 * \param id The datapool item identifier
 * \param size The address where the size of the datapool item is written to.
 * \return 0 when id denotes a valid identifier; -1 otherwise.
 */
extern int getDpSize(DatapoolId_t id, size_t* size);
