/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-08-22 17:43:36
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include <stdlib.h>
#include <string.h>

#include "CrPsDp.h"

#include "CrPsDpServTest.h"
#include "CrPsDpHk.h"
#include "CrPsDpServReqVerif.h"

/**
 * Structure to hold the location and size information of a datapool entry.
 */
typedef struct _DpMetaInfoEntry_t {
  /**
   * The address of the datapool entry.
   */
  void* addr;
  /**
   * The length in bytes of the datapool entry.
   */
  size_t length;
} DpMetaInfoEntry_t;

/**
 *
 * Array of \ref _DpMetaInfoEntry_t to hold the meta information of all
 * datapool entries.
 */
static DpMetaInfoEntry_t dpMetaInfoParams[] = {
  {(void*)&dpHk.debugVarAddr, sizeof(dpHk.debugVarAddr)},
  {(void*)&dpHk.dest, sizeof(dpHk.dest)},
  {(void*)&dpHk.isEnabledPar, sizeof(dpHk.isEnabledPar)},
  {(void*)&dpHk.sid, sizeof(dpHk.sid)},
  {(void*)&dpServTest.AreYouAliveTimeOut, sizeof(dpServTest.AreYouAliveTimeOut)},
  {(void*)&dpServTest.OnBoardConnectDestLst, sizeof(dpServTest.OnBoardConnectDestLst)}
};

static DpMetaInfoEntry_t dpMetaInfoVars[] = {
  {(void*)&dpHk.cycleCnt, sizeof(dpHk.cycleCnt)},
  {(void*)&dpHk.debugVar, sizeof(dpHk.debugVar)},
  {(void*)&dpHk.isEnabledVar, sizeof(dpHk.isEnabledVar)},
  {(void*)&dpHk.sampleBufId, sizeof(dpHk.sampleBufId)},
  {(void*)&dpServReqVerif.failCodeAccFailed, sizeof(dpServReqVerif.failCodeAccFailed)},
  {(void*)&dpServReqVerif.failCodePrgrFailed, sizeof(dpServReqVerif.failCodePrgrFailed)},
  {(void*)&dpServReqVerif.failCodeStartFailed, sizeof(dpServReqVerif.failCodeStartFailed)},
  {(void*)&dpServReqVerif.failCodeTermFailed, sizeof(dpServReqVerif.failCodeTermFailed)},
  {(void*)&dpServReqVerif.invDestRerouting, sizeof(dpServReqVerif.invDestRerouting)},
  {(void*)&dpServReqVerif.nOfAccFailed, sizeof(dpServReqVerif.nOfAccFailed)},
  {(void*)&dpServReqVerif.nOfPrgrFailed, sizeof(dpServReqVerif.nOfPrgrFailed)},
  {(void*)&dpServReqVerif.nOfReroutingFailed, sizeof(dpServReqVerif.nOfReroutingFailed)},
  {(void*)&dpServReqVerif.nOfStartFailed, sizeof(dpServReqVerif.nOfStartFailed)},
  {(void*)&dpServReqVerif.nOfTermFailed, sizeof(dpServReqVerif.nOfTermFailed)},
  {(void*)&dpServReqVerif.pcktIdAccFailed, sizeof(dpServReqVerif.pcktIdAccFailed)},
  {(void*)&dpServReqVerif.pcktIdPrgrFailed, sizeof(dpServReqVerif.pcktIdPrgrFailed)},
  {(void*)&dpServReqVerif.pcktIdReroutingFailed, sizeof(dpServReqVerif.pcktIdReroutingFailed)},
  {(void*)&dpServReqVerif.pcktIdStartFailed, sizeof(dpServReqVerif.pcktIdStartFailed)},
  {(void*)&dpServReqVerif.pcktIdTermFailed, sizeof(dpServReqVerif.pcktIdTermFailed)},
  {(void*)&dpServReqVerif.stepPrgrFailed, sizeof(dpServReqVerif.stepPrgrFailed)},
  {(void*)&dpServReqVerif.verFailData, sizeof(dpServReqVerif.verFailData)},
  {(void*)&dpServTest.AreYouAliveSrc, sizeof(dpServTest.AreYouAliveSrc)},
  {(void*)&dpServTest.OnBoardConnectDest, sizeof(dpServTest.OnBoardConnectDest)}
};

static DpMetaInfoEntry_t* getMetaInfo(ParameterId_t id)
{
  DpMetaInfoEntry_t* p;
  p = NULL;
  if (id >= DpIdParamsLowest && id <= DpIdParamsHighest)
  {
    p = &dpMetaInfoParams[id-DpIdParamsLowest];
  }
  else if (id >= DpIdVarsLowest && id <= DpIdVarsHighest)
  {
    p = &dpMetaInfoVars[id-DpIdVarsLowest];
  }
  return p;
}

/**
 * Get the value of a datapool item by identifier.
 * \param id The datapool item identifier
 * \param dest The address of the target variable where the value gets copied
 * to.
 * \return 0 when id denotes a valid identifier; -1 otherwise.
 */
int getDpValue(ParameterId_t id, void* dest)
{
  DpMetaInfoEntry_t* entry;
  entry = getMetaInfo(id);
  if (entry == NULL)
  {
    return -1;
  }
  (void)memcpy(dest, entry->addr, entry->length);
  return 0;
}

/**
 * Set the value of a datapool item by identifier
 * \param id The datapool item identifier
 * \param src The address of the source variable where the value gets copied
 * from.
 * \return 0 when id denotes a valid identifier; -1 otherwise.
 */
int setDpValue(ParameterId_t id, const void* src)
{
  DpMetaInfoEntry_t* entry;
  entry = getMetaInfo(id);
  if (entry == NULL)
  {
    return -1;
  }
  (void)memcpy(entry->addr, src, entry->length);
  return 0;
}
/**
 * Get the size of a datapool item by identifier.
 * \param id The datapool item identifier
 * \return The size of the datapool item.
 */
int getDpSize(ParameterId_t id, size_t* size)
{
  DpMetaInfoEntry_t* entry;
  entry = getMetaInfo(id);
  if (entry == NULL)
  {
    return -1;
  }
  (void)memcpy(size, &entry->length, sizeof(size_t));
  return 0;
}
