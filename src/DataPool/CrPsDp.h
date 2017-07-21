/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-07-24 16:05:36
 * \author PnP Generator
 * \copyright (c) Copyright
 */

typedef enum {
   DpIdAreYouAliveTimeOut = 0,
   DpIdOnBoardConnectDestLst = 1,
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
 */
extern void getDpValue(DatapoolId_t id, void* dest);
/**
 * Set the value of a datapool item by identifier
 * \param id The datapool item identifier
 * \param src The address of the source variable where the value gets copied
 * from.
 */
extern void setDpValue(DatapoolId_t id, const void* src);
