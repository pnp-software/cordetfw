/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-10-13 12:48:17
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServTest.h>
#include <DataPool/CrPsDpServHk.h>
#include <DataPool/CrPsDpServReqVerif.h>
#include <DataPool/CrPsDpServEvt.h>
#include <DataPool/CrPsDpServLpt.h>
#include <CrPsUserConstants.h>


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
  /**
   * The number of array elements.
   */
  unsigned int nElements;
  /**
   * The length of a single array element.
   */
  size_t elementLength;
} DpMetaInfoEntry_t;

/**
 *
 * Array of \ref _DpMetaInfoEntry_t to hold the meta information of all
 * datapool entries.
 */
static DpMetaInfoEntry_t dpMetaInfoParams[] = {
  {(void*)&dpServHkParams.debugVarAddr, sizeof(dpServHkParams.debugVarAddr), HK_N_DEBUG_VAR, sizeof(dpServHkParams.debugVarAddr[0])},
  {(void*)&dpServHkParams.dest, sizeof(dpServHkParams.dest), HK_N_REP_DEF, sizeof(dpServHkParams.dest[0])},
  {(void*)&dpServHkParams.isEnabled, sizeof(dpServHkParams.isEnabled), HK_N_REP_DEF, sizeof(dpServHkParams.isEnabled[0])},
  {(void*)&dpServHkParams.period, sizeof(dpServHkParams.period), HK_N_REP_DEF, sizeof(dpServHkParams.period[0])},
  {(void*)&dpServHkParams.sid, sizeof(dpServHkParams.sid), HK_N_REP_DEF, sizeof(dpServHkParams.sid[0])},
  {(void*)&dpServLptParams.lptTimeOut, sizeof(dpServLptParams.lptTimeOut), LPT_N_BUF, sizeof(dpServLptParams.lptTimeOut[0])},
  {(void*)&dpServTestParams.AreYouAliveTimeOut, sizeof(dpServTestParams.AreYouAliveTimeOut), 1, sizeof(dpServTestParams.AreYouAliveTimeOut)},
  {(void*)&dpServTestParams.OnBoardConnectDestLst, sizeof(dpServTestParams.OnBoardConnectDestLst), TEST_MAX_APP, sizeof(dpServTestParams.OnBoardConnectDestLst[0])}
};

static DpMetaInfoEntry_t dpMetaInfoVars[] = {
  {(void*)&dpServEvtVars.isEidEnabled, sizeof(dpServEvtVars.isEidEnabled), EVT_N_EID, sizeof(dpServEvtVars.isEidEnabled[0])},
  {(void*)&dpServEvtVars.lastEvtEid_1, sizeof(dpServEvtVars.lastEvtEid_1), 1, sizeof(dpServEvtVars.lastEvtEid_1)},
  {(void*)&dpServEvtVars.lastEvtEid_2, sizeof(dpServEvtVars.lastEvtEid_2), 1, sizeof(dpServEvtVars.lastEvtEid_2)},
  {(void*)&dpServEvtVars.lastEvtEid_3, sizeof(dpServEvtVars.lastEvtEid_3), 1, sizeof(dpServEvtVars.lastEvtEid_3)},
  {(void*)&dpServEvtVars.lastEvtEid_4, sizeof(dpServEvtVars.lastEvtEid_4), 1, sizeof(dpServEvtVars.lastEvtEid_4)},
  {(void*)&dpServEvtVars.lastEvtTime_1, sizeof(dpServEvtVars.lastEvtTime_1), 1, sizeof(dpServEvtVars.lastEvtTime_1)},
  {(void*)&dpServEvtVars.lastEvtTime_2, sizeof(dpServEvtVars.lastEvtTime_2), 1, sizeof(dpServEvtVars.lastEvtTime_2)},
  {(void*)&dpServEvtVars.lastEvtTime_3, sizeof(dpServEvtVars.lastEvtTime_3), 1, sizeof(dpServEvtVars.lastEvtTime_3)},
  {(void*)&dpServEvtVars.lastEvtTime_4, sizeof(dpServEvtVars.lastEvtTime_4), 1, sizeof(dpServEvtVars.lastEvtTime_4)},
  {(void*)&dpServEvtVars.nOfDetectedEvts_1, sizeof(dpServEvtVars.nOfDetectedEvts_1), 1, sizeof(dpServEvtVars.nOfDetectedEvts_1)},
  {(void*)&dpServEvtVars.nOfDetectedEvts_2, sizeof(dpServEvtVars.nOfDetectedEvts_2), 1, sizeof(dpServEvtVars.nOfDetectedEvts_2)},
  {(void*)&dpServEvtVars.nOfDetectedEvts_3, sizeof(dpServEvtVars.nOfDetectedEvts_3), 1, sizeof(dpServEvtVars.nOfDetectedEvts_3)},
  {(void*)&dpServEvtVars.nOfDetectedEvts_4, sizeof(dpServEvtVars.nOfDetectedEvts_4), 1, sizeof(dpServEvtVars.nOfDetectedEvts_4)},
  {(void*)&dpServEvtVars.nOfDisabledEid_1, sizeof(dpServEvtVars.nOfDisabledEid_1), 1, sizeof(dpServEvtVars.nOfDisabledEid_1)},
  {(void*)&dpServEvtVars.nOfDisabledEid_2, sizeof(dpServEvtVars.nOfDisabledEid_2), 1, sizeof(dpServEvtVars.nOfDisabledEid_2)},
  {(void*)&dpServEvtVars.nOfDisabledEid_3, sizeof(dpServEvtVars.nOfDisabledEid_3), 1, sizeof(dpServEvtVars.nOfDisabledEid_3)},
  {(void*)&dpServEvtVars.nOfDisabledEid_4, sizeof(dpServEvtVars.nOfDisabledEid_4), 1, sizeof(dpServEvtVars.nOfDisabledEid_4)},
  {(void*)&dpServEvtVars.nOfGenEvtRep_1, sizeof(dpServEvtVars.nOfGenEvtRep_1), 1, sizeof(dpServEvtVars.nOfGenEvtRep_1)},
  {(void*)&dpServEvtVars.nOfGenEvtRep_2, sizeof(dpServEvtVars.nOfGenEvtRep_2), 1, sizeof(dpServEvtVars.nOfGenEvtRep_2)},
  {(void*)&dpServEvtVars.nOfGenEvtRep_3, sizeof(dpServEvtVars.nOfGenEvtRep_3), 1, sizeof(dpServEvtVars.nOfGenEvtRep_3)},
  {(void*)&dpServEvtVars.nOfGenEvtRep_4, sizeof(dpServEvtVars.nOfGenEvtRep_4), 1, sizeof(dpServEvtVars.nOfGenEvtRep_4)},
  {(void*)&dpServHkVars.cycleCnt, sizeof(dpServHkVars.cycleCnt), HK_N_REP_DEF, sizeof(dpServHkVars.cycleCnt[0])},
  {(void*)&dpServHkVars.debugVar, sizeof(dpServHkVars.debugVar), HK_N_DEBUG_VAR, sizeof(dpServHkVars.debugVar[0])},
  {(void*)&dpServHkVars.lstId, sizeof(dpServHkVars.lstId), HK_N_REP_DEF*HK_MAX_N_ITEMS, sizeof(dpServHkVars.lstId[0])},
  {(void*)&dpServHkVars.lstNSampRep, sizeof(dpServHkVars.lstNSampRep), HK_N_REP_DEF*HK_MAX_N_GR, sizeof(dpServHkVars.lstNSampRep[0])},
  {(void*)&dpServHkVars.lstSampleRep, sizeof(dpServHkVars.lstSampleRep), HK_N_REP_DEF*HK_MAX_N_GR, sizeof(dpServHkVars.lstSampleRep[0])},
  {(void*)&dpServHkVars.nSimple, sizeof(dpServHkVars.nSimple), HK_N_REP_DEF, sizeof(dpServHkVars.nSimple[0])},
  {(void*)&dpServHkVars.sampleBufId, sizeof(dpServHkVars.sampleBufId), HK_N_REP_DEF, sizeof(dpServHkVars.sampleBufId[0])},
  {(void*)&dpServLptVars.largeMsgTransId, sizeof(dpServLptVars.largeMsgTransId), LPT_N_BUF, sizeof(dpServLptVars.largeMsgTransId[0])},
  {(void*)&dpServLptVars.lptFailCode, sizeof(dpServLptVars.lptFailCode), LPT_N_BUF, sizeof(dpServLptVars.lptFailCode[0])},
  {(void*)&dpServLptVars.lptRemSize, sizeof(dpServLptVars.lptRemSize), LPT_N_BUF, sizeof(dpServLptVars.lptRemSize[0])},
  {(void*)&dpServLptVars.lptSize, sizeof(dpServLptVars.lptSize), LPT_N_BUF, sizeof(dpServLptVars.lptSize[0])},
  {(void*)&dpServLptVars.lptSrc, sizeof(dpServLptVars.lptSrc), LPT_N_BUF, sizeof(dpServLptVars.lptSrc[0])},
  {(void*)&dpServLptVars.lptTime, sizeof(dpServLptVars.lptTime), LPT_N_BUF, sizeof(dpServLptVars.lptTime[0])},
  {(void*)&dpServLptVars.nOfDownlinks, sizeof(dpServLptVars.nOfDownlinks), 1, sizeof(dpServLptVars.nOfDownlinks)},
  {(void*)&dpServLptVars.nOfUplinks, sizeof(dpServLptVars.nOfUplinks), 1, sizeof(dpServLptVars.nOfUplinks)},
  {(void*)&dpServLptVars.partSeqNmb, sizeof(dpServLptVars.partSeqNmb), LPT_N_BUF, sizeof(dpServLptVars.partSeqNmb[0])},
  {(void*)&dpServReqVerifVars.failCodeAccFailed, sizeof(dpServReqVerifVars.failCodeAccFailed), 1, sizeof(dpServReqVerifVars.failCodeAccFailed)},
  {(void*)&dpServReqVerifVars.failCodePrgrFailed, sizeof(dpServReqVerifVars.failCodePrgrFailed), 1, sizeof(dpServReqVerifVars.failCodePrgrFailed)},
  {(void*)&dpServReqVerifVars.failCodeStartFailed, sizeof(dpServReqVerifVars.failCodeStartFailed), 1, sizeof(dpServReqVerifVars.failCodeStartFailed)},
  {(void*)&dpServReqVerifVars.failCodeTermFailed, sizeof(dpServReqVerifVars.failCodeTermFailed), 1, sizeof(dpServReqVerifVars.failCodeTermFailed)},
  {(void*)&dpServReqVerifVars.invDestRerouting, sizeof(dpServReqVerifVars.invDestRerouting), 1, sizeof(dpServReqVerifVars.invDestRerouting)},
  {(void*)&dpServReqVerifVars.nOfAccFailed, sizeof(dpServReqVerifVars.nOfAccFailed), 1, sizeof(dpServReqVerifVars.nOfAccFailed)},
  {(void*)&dpServReqVerifVars.nOfPrgrFailed, sizeof(dpServReqVerifVars.nOfPrgrFailed), 1, sizeof(dpServReqVerifVars.nOfPrgrFailed)},
  {(void*)&dpServReqVerifVars.nOfReroutingFailed, sizeof(dpServReqVerifVars.nOfReroutingFailed), 1, sizeof(dpServReqVerifVars.nOfReroutingFailed)},
  {(void*)&dpServReqVerifVars.nOfStartFailed, sizeof(dpServReqVerifVars.nOfStartFailed), 1, sizeof(dpServReqVerifVars.nOfStartFailed)},
  {(void*)&dpServReqVerifVars.nOfTermFailed, sizeof(dpServReqVerifVars.nOfTermFailed), 1, sizeof(dpServReqVerifVars.nOfTermFailed)},
  {(void*)&dpServReqVerifVars.pcktIdAccFailed, sizeof(dpServReqVerifVars.pcktIdAccFailed), 1, sizeof(dpServReqVerifVars.pcktIdAccFailed)},
  {(void*)&dpServReqVerifVars.pcktIdPrgrFailed, sizeof(dpServReqVerifVars.pcktIdPrgrFailed), 1, sizeof(dpServReqVerifVars.pcktIdPrgrFailed)},
  {(void*)&dpServReqVerifVars.pcktIdReroutingFailed, sizeof(dpServReqVerifVars.pcktIdReroutingFailed), 1, sizeof(dpServReqVerifVars.pcktIdReroutingFailed)},
  {(void*)&dpServReqVerifVars.pcktIdStartFailed, sizeof(dpServReqVerifVars.pcktIdStartFailed), 1, sizeof(dpServReqVerifVars.pcktIdStartFailed)},
  {(void*)&dpServReqVerifVars.pcktIdTermFailed, sizeof(dpServReqVerifVars.pcktIdTermFailed), 1, sizeof(dpServReqVerifVars.pcktIdTermFailed)},
  {(void*)&dpServReqVerifVars.stepPrgrFailed, sizeof(dpServReqVerifVars.stepPrgrFailed), 1, sizeof(dpServReqVerifVars.stepPrgrFailed)},
  {(void*)&dpServReqVerifVars.verFailData, sizeof(dpServReqVerifVars.verFailData), 1, sizeof(dpServReqVerifVars.verFailData)},
  {(void*)&dpServTestVars.AreYouAliveSrc, sizeof(dpServTestVars.AreYouAliveSrc), 1, sizeof(dpServTestVars.AreYouAliveSrc)},
  {(void*)&dpServTestVars.OnBoardConnectDest, sizeof(dpServTestVars.OnBoardConnectDest), 1, sizeof(dpServTestVars.OnBoardConnectDest)}
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
size_t getDpValue(ParameterId_t id, void* dest)
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
 * Get the value of a datapool item plus meta information by identifier.
 * \param id The datapool item identifier
 * \param dest The address of the target variable where the value gets copied
 * to.
 * \param pElementLength Pointer to where the element size is copied to.
 * \param pNElements Pointer to where the number of elements is copied
 * to.\return Number of bytes copied. 0 if id is invalid.
 */
size_t getDpValueEx(ParameterId_t id, void* dest, size_t* pElementLength, unsigned int* pNElements)
{
  DpMetaInfoEntry_t* entry;
  entry = getMetaInfo(id);
  if (entry == NULL)
  {
    return 0;
  }
  (void)memcpy(dest, entry->addr, entry->length);
  *pElementLength = entry->elementLength;
  *pNElements = entry->nElements;
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
 * \return The size of the datapool parameter. 0 if id is invalid.
 */
size_t getDpSize(ParameterId_t id)
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
size_t getDpParamSize(ParameterId_t id)
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
size_t getDpVarSize(ParameterId_t id)
{
  DpMetaInfoEntry_t* entry;
  entry = getMetaInfoVar(id);
  if (entry == NULL)
  {
    return 0;
  }
  return entry->length;
}
