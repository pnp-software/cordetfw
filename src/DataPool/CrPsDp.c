/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-10-03 10:29:40
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsDp.h"

#include "CrPsDpServTest.h"
#include "CrPsDpHk.h"
#include "CrPsDpServReqVerif.h"
#include "CrPsDpEvt.h"


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
  {(void*)&dpHkParams.debugVarAddr, sizeof(dpHkParams.debugVarAddr)},
  {(void*)&dpHkParams.dest, sizeof(dpHkParams.dest)},
  {(void*)&dpHkParams.isEnabled, sizeof(dpHkParams.isEnabled)},
  {(void*)&dpHkParams.sid, sizeof(dpHkParams.sid)},
  {(void*)&dpServTestParams.AreYouAliveTimeOut, sizeof(dpServTestParams.AreYouAliveTimeOut)},
  {(void*)&dpServTestParams.OnBoardConnectDestLst, sizeof(dpServTestParams.OnBoardConnectDestLst)}
};

static DpMetaInfoEntry_t dpMetaInfoVars[] = {
  {(void*)&dpEvtVars.isEidEnabled, sizeof(dpEvtVars.isEidEnabled)},
  {(void*)&dpEvtVars.lastEvtEid_1, sizeof(dpEvtVars.lastEvtEid_1)},
  {(void*)&dpEvtVars.lastEvtEid_2, sizeof(dpEvtVars.lastEvtEid_2)},
  {(void*)&dpEvtVars.lastEvtEid_3, sizeof(dpEvtVars.lastEvtEid_3)},
  {(void*)&dpEvtVars.lastEvtEid_4, sizeof(dpEvtVars.lastEvtEid_4)},
  {(void*)&dpEvtVars.lastEvtTime_1, sizeof(dpEvtVars.lastEvtTime_1)},
  {(void*)&dpEvtVars.lastEvtTime_2, sizeof(dpEvtVars.lastEvtTime_2)},
  {(void*)&dpEvtVars.lastEvtTime_3, sizeof(dpEvtVars.lastEvtTime_3)},
  {(void*)&dpEvtVars.lastEvtTime_4, sizeof(dpEvtVars.lastEvtTime_4)},
  {(void*)&dpEvtVars.nOfDetectedEvts_1, sizeof(dpEvtVars.nOfDetectedEvts_1)},
  {(void*)&dpEvtVars.nOfDetectedEvts_2, sizeof(dpEvtVars.nOfDetectedEvts_2)},
  {(void*)&dpEvtVars.nOfDetectedEvts_3, sizeof(dpEvtVars.nOfDetectedEvts_3)},
  {(void*)&dpEvtVars.nOfDetectedEvts_4, sizeof(dpEvtVars.nOfDetectedEvts_4)},
  {(void*)&dpEvtVars.nOfDisabledEid_1, sizeof(dpEvtVars.nOfDisabledEid_1)},
  {(void*)&dpEvtVars.nOfDisabledEid_2, sizeof(dpEvtVars.nOfDisabledEid_2)},
  {(void*)&dpEvtVars.nOfDisabledEid_3, sizeof(dpEvtVars.nOfDisabledEid_3)},
  {(void*)&dpEvtVars.nOfDisabledEid_4, sizeof(dpEvtVars.nOfDisabledEid_4)},
  {(void*)&dpEvtVars.nOfGenEvtRep_1, sizeof(dpEvtVars.nOfGenEvtRep_1)},
  {(void*)&dpEvtVars.nOfGenEvtRep_2, sizeof(dpEvtVars.nOfGenEvtRep_2)},
  {(void*)&dpEvtVars.nOfGenEvtRep_3, sizeof(dpEvtVars.nOfGenEvtRep_3)},
  {(void*)&dpEvtVars.nOfGenEvtRep_4, sizeof(dpEvtVars.nOfGenEvtRep_4)},
  {(void*)&dpHkVars.cycleCnt, sizeof(dpHkVars.cycleCnt)},
  {(void*)&dpHkVars.debugVar, sizeof(dpHkVars.debugVar)},
  {(void*)&dpHkVars.sampleBufId, sizeof(dpHkVars.sampleBufId)},
  {(void*)&dpServReqVerifVars.failCodeAccFailed, sizeof(dpServReqVerifVars.failCodeAccFailed)},
  {(void*)&dpServReqVerifVars.failCodePrgrFailed, sizeof(dpServReqVerifVars.failCodePrgrFailed)},
  {(void*)&dpServReqVerifVars.failCodeStartFailed, sizeof(dpServReqVerifVars.failCodeStartFailed)},
  {(void*)&dpServReqVerifVars.failCodeTermFailed, sizeof(dpServReqVerifVars.failCodeTermFailed)},
  {(void*)&dpServReqVerifVars.invDestRerouting, sizeof(dpServReqVerifVars.invDestRerouting)},
  {(void*)&dpServReqVerifVars.nOfAccFailed, sizeof(dpServReqVerifVars.nOfAccFailed)},
  {(void*)&dpServReqVerifVars.nOfPrgrFailed, sizeof(dpServReqVerifVars.nOfPrgrFailed)},
  {(void*)&dpServReqVerifVars.nOfReroutingFailed, sizeof(dpServReqVerifVars.nOfReroutingFailed)},
  {(void*)&dpServReqVerifVars.nOfStartFailed, sizeof(dpServReqVerifVars.nOfStartFailed)},
  {(void*)&dpServReqVerifVars.nOfTermFailed, sizeof(dpServReqVerifVars.nOfTermFailed)},
  {(void*)&dpServReqVerifVars.pcktIdAccFailed, sizeof(dpServReqVerifVars.pcktIdAccFailed)},
  {(void*)&dpServReqVerifVars.pcktIdPrgrFailed, sizeof(dpServReqVerifVars.pcktIdPrgrFailed)},
  {(void*)&dpServReqVerifVars.pcktIdReroutingFailed, sizeof(dpServReqVerifVars.pcktIdReroutingFailed)},
  {(void*)&dpServReqVerifVars.pcktIdStartFailed, sizeof(dpServReqVerifVars.pcktIdStartFailed)},
  {(void*)&dpServReqVerifVars.pcktIdTermFailed, sizeof(dpServReqVerifVars.pcktIdTermFailed)},
  {(void*)&dpServReqVerifVars.stepPrgrFailed, sizeof(dpServReqVerifVars.stepPrgrFailed)},
  {(void*)&dpServReqVerifVars.verFailData, sizeof(dpServReqVerifVars.verFailData)},
  {(void*)&dpServTestVars.AreYouAliveSrc, sizeof(dpServTestVars.AreYouAliveSrc)},
  {(void*)&dpServTestVars.OnBoardConnectDest, sizeof(dpServTestVars.OnBoardConnectDest)}
};

static DpMetaInfoEntry_t* getMetaInfoParam(ParameterId_t id)
{
  DpMetaInfoEntry_t* p;
  p = NULL;
  if (id >= DpIdParamsLowest && id <= DpIdParamsHighest)
  {
    p = &dpMetaInfoParams[id-DpIdParamsLowest];
  }
  return p;
}

static DpMetaInfoEntry_t* getMetaInfoVar(ParameterId_t id)
{
  DpMetaInfoEntry_t* p;
  p = NULL;
  if (id >= DpIdVarsLowest && id <= DpIdVarsHighest)
  {
    p = &dpMetaInfoVars[id-DpIdVarsLowest];
  }
  return p;
}

static DpMetaInfoEntry_t* getMetaInfo(ParameterId_t id)
{
  DpMetaInfoEntry_t* p;
  p = getMetaInfoParam(id);
  if (p == NULL)
  {
    p = getMetaInfoVar(id);
  }
  return p;
}

/**
 * Get the value of a datapool item by identifier.
 * \param id The datapool item identifier
 * \param dest The address of the target variable where the value gets copied
 * to.
 * \return Number of bytes copied. 0 if id is invalid.
 */
int getDpValue(ParameterId_t id, void* dest)
{
  DpMetaInfoEntry_t* entry;
  entry = getMetaInfo(id);
  if (entry == NULL)
  {
    return 0;
  }
  (void)memcpy(dest, entry->addr, entry->length);
  return entry->length;
}

/**
 * Set the value of a datapool item by identifier
 * \param id The datapool item identifier
 * \param src The address of the source variable where the value gets copied
 * from.
 * \return Number of bytes copied. 0 if id is invalid.
 */
int setDpValue(ParameterId_t id, const void* src)
{
  DpMetaInfoEntry_t* entry;
  entry = getMetaInfo(id);
  if (entry == NULL)
  {
    return 0;
  }
  (void)memcpy(entry->addr, src, entry->length);
  return entry->length;
}

/**
 * Get the size of a datapool item by identifier.
 * \param id The datapool item identifier
 * \return The size of the datapool item. 0 if id is invalid.
 */
int getDpSize(ParameterId_t id)
{
  DpMetaInfoEntry_t* entry;
  entry = getMetaInfo(id);
  if (entry == NULL)
  {
    return 0;
  }
  return entry->length;
}

/**
 * Get the size of a datapool parameter by identifier.
 * \param id The datapool parameter identifier
 * \return The size of the datapool parameter. 0 if id is invalid.
 */
int getDpParamSize(ParameterId_t id)
{
  DpMetaInfoEntry_t* entry;
  entry = getMetaInfoParam(id);
  if (entry == NULL)
  {
    return 0;
  }
  return entry->length;
}

/**
 * Get the size of a datapool variable by identifier.
 * \param id The datapool variable identifier
 * \return The size of the datapool variable. 0 if id is invalid.
 */
int getDpVarSize(ParameterId_t id)
{
  DpMetaInfoEntry_t* entry;
  entry = getMetaInfoVar(id);
  if (entry == NULL)
  {
    return 0;
  }
  return entry->length;
}
