/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-10-13 12:48:17
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSDPSERVHK_H_
#define CRPSDPSERVHK_H_

#include "CrPsDpTypes.h"
#include "CrPsUserConstants.h"

/**
 * Type description
 */
typedef struct {
  /**
   * Array of HK_N_DEBUG_VAR elements. The I-th element is the address of the
   * I-th debug variable
   */
  uint32_t debugVarAddr[HK_N_DEBUG_VAR];
  /**
   * Array of HK_N_REP_DEF elements. The I-th element is the destination of
   * the I-th Report Definition in the RDL
   */
  uint16_t dest[HK_N_REP_DEF];
  /**
   * Array of HK_N_REP_DEF elements. The I-th element is the enable status of
   * the I-th Report Definition in the RDL
   */
  uint8_t isEnabled[HK_N_REP_DEF];
  /**
   * Collection period in units of HK_COLLECT_PER
   */
  uint32_t period[HK_N_REP_DEF];
  /**
   * Array of HK_N_REP_DEF elements. The I-th element is the SID of the I-th
   * Report Definition in the RDL
   */
  uint16_t sid[HK_N_REP_DEF];
} DpServHkParams_t;

/**
 * Type description
 */
typedef struct {
  /**
   * Array of HK_N_REP_DEF elements. The I-th element is the cycle counter for
   * the I-th Report Definitions in the RDL
   */
  uint32_t cycleCnt[HK_N_REP_DEF];
  /**
   * Array of HK_N_DEBUG_VAR elements. The I-th element is the value of the
   * I-th debug variable
   */
  uint32_t debugVar[HK_N_DEBUG_VAR];
  /**
   * Max N Items
   */
  uint16_t lstId[HK_N_REP_DEF*HK_MAX_N_ITEMS];
  /**
   * Max N rep; nRep[1..nGroup]
   */
  uint16_t lstNSampRep[HK_N_REP_DEF*HK_MAX_N_GR];
  /**
   * max N group; rep[1..nGroup]
   */
  uint16_t lstSampleRep[HK_N_REP_DEF*HK_MAX_N_GR];
  /**
   * max ximple
   */
  uint16_t nSimple[HK_N_REP_DEF];
  /**
   * Array of HK_N_REP_DEF elements. The I-th element is the identifier of the
   * Sampling Buffer for the I-th Report Definition in the RDL
   */
  uint16_t sampleBufId[HK_N_REP_DEF];
} DpServHkVars_t;

extern DpServHkParams_t dpServHkParams;
extern DpServHkVars_t dpServHkVars;

/*Sampling Buffer */
extern uint32_t SampleBuffer[HK_MAX_REP][HK_MAX_N_REP][HK_MAX_N_GR][HK_N_SAMP_BUF];

/**
 * Initialises ServHk
 */
void initDpServHk(void);


/**
 * Gets a Datapool Buffer Element
 * \return an Element of the Buffer
 */
static inline uint32_t getDpBufferElement(uint32_t i, uint32_t j, uint32_t k, uint32_t l)
{
  return SampleBuffer[i][j][k][l];
}

/**
 * Sets a Datapool Buffer Element
 * \return an Element of the Buffer
 */
static inline void setDpBufferElement(uint32_t i, uint32_t j, uint32_t k, uint32_t l, uint32_t t)
{
  SampleBuffer[i][j][k][l] = t;
}


static inline uint16_t getDplstSampleRepItem(int i);

/**
 * Gets the number of super-commutated groups (NFA) 
 * from number of sample repetition numbers (rep[])
 * \return Number of super-commutated groups (NFA)
 */
static inline uint32_t getNFA(int i)
{
  int k;
  uint32_t curSCSampleRepNum;

  for (k=0; k<HK_MAX_N_GR; k++)
    {
      curSCSampleRepNum = getDplstSampleRepItem(i*HK_MAX_N_GR+k);
      if (curSCSampleRepNum == 0)
        break;
    }

  return k;
}

/**
 * Gets the datapool array debugVarAddr
 * \return The datapool array debugVarAddr
 */
static inline uint32_t* getDpdebugVarAddrArray()
{
  return &dpServHkParams.debugVarAddr[0];
}

/**
 * Gets the value of the i-th element in the datapool array debugVarAddr
 * \param i Index variable
 * \return The i-th element in the datapool array debugVarAddr
 */
static inline uint32_t getDpdebugVarAddrItem(int i)
{
  return dpServHkParams.debugVarAddr[i];
}

/**
 * Sets the value of the i-th element in the datapool array debugVarAddr
 * \param i Index variable
 * \param debugVarAddr The value to be stored into the i-th element of
 * datapool array debugVarAddr.
 */
static inline void setDpdebugVarAddrItem(int i, uint32_t debugVarAddr)
{
  dpServHkParams.debugVarAddr[i] = debugVarAddr;
}

/**
 * Gets the datapool array dest
 * \return The datapool array dest
 */
static inline uint16_t* getDpdestArray()
{
  return &dpServHkParams.dest[0];
}

/**
 * Gets the value of the i-th element in the datapool array dest
 * \param i Index variable
 * \return The i-th element in the datapool array dest
 */
static inline uint16_t getDpdestItem(int i)
{
  return dpServHkParams.dest[i];
}

/**
 * Sets the value of the i-th element in the datapool array dest
 * \param i Index variable
 * \param dest The value to be stored into the i-th element of datapool array
 * dest.
 */
static inline void setDpdestItem(int i, uint16_t dest)
{
  dpServHkParams.dest[i] = dest;
}

/**
 * Gets the datapool array isEnabled
 * \return The datapool array isEnabled
 */
static inline uint8_t* getDpisEnabledArray()
{
  return &dpServHkParams.isEnabled[0];
}

/**
 * Gets the value of the i-th element in the datapool array isEnabled
 * \param i Index variable
 * \return The i-th element in the datapool array isEnabled
 */
static inline uint8_t getDpisEnabledItem(int i)
{
  return dpServHkParams.isEnabled[i];
}

/**
 * Sets the value of the i-th element in the datapool array isEnabled
 * \param i Index variable
 * \param isEnabled The value to be stored into the i-th element of datapool
 * array isEnabled.
 */
static inline void setDpisEnabledItem(int i, uint8_t isEnabled)
{
  dpServHkParams.isEnabled[i] = isEnabled;
}

/**
 * Gets the datapool array period
 * \return The datapool array period
 */
static inline uint32_t* getDpperiodArray()
{
  return &dpServHkParams.period[0];
}

/**
 * Gets the value of the i-th element in the datapool array period
 * \param i Index variable
 * \return The i-th element in the datapool array period
 */
static inline uint32_t getDpperiodItem(int i)
{
  return dpServHkParams.period[i];
}

/**
 * Sets the value of the i-th element in the datapool array period
 * \param i Index variable
 * \param period The value to be stored into the i-th element of datapool
 * array period.
 */
static inline void setDpperiodItem(int i, uint32_t period)
{
  dpServHkParams.period[i] = period;
}

/**
 * Gets the datapool array sid
 * \return The datapool array sid
 */
static inline uint16_t* getDpsidArray()
{
  return &dpServHkParams.sid[0];
}

/**
 * Gets the value of the i-th element in the datapool array sid
 * \param i Index variable
 * \return The i-th element in the datapool array sid
 */
static inline uint16_t getDpsidItem(int i)
{
  return dpServHkParams.sid[i];
}

/**
 * Sets the value of the i-th element in the datapool array sid
 * \param i Index variable
 * \param sid The value to be stored into the i-th element of datapool array
 * sid.
 */
static inline void setDpsidItem(int i, uint16_t sid)
{
  dpServHkParams.sid[i] = sid;
}

/**
 * Gets the datapool array cycleCnt
 * \return The datapool array cycleCnt
 */
static inline uint32_t* getDpcycleCntArray()
{
  return &dpServHkVars.cycleCnt[0];
}

/**
 * Gets the value of the i-th element in the datapool array cycleCnt
 * \param i Index variable
 * \return The i-th element in the datapool array cycleCnt
 */
static inline uint32_t getDpcycleCntItem(int i)
{
  return dpServHkVars.cycleCnt[i];
}

/**
 * Sets the value of the i-th element in the datapool array cycleCnt
 * \param i Index variable
 * \param cycleCnt The value to be stored into the i-th element of datapool
 * array cycleCnt.
 */
static inline void setDpcycleCntItem(int i, uint32_t cycleCnt)
{
  dpServHkVars.cycleCnt[i] = cycleCnt;
}

/**
 * Gets the datapool array debugVar
 * \return The datapool array debugVar
 */
static inline uint32_t* getDpdebugVarArray()
{
  return &dpServHkVars.debugVar[0];
}

/**
 * Gets the value of the i-th element in the datapool array debugVar
 * \param i Index variable
 * \return The i-th element in the datapool array debugVar
 */
static inline uint32_t getDpdebugVarItem(int i)
{
  return dpServHkVars.debugVar[i];
}

/**
 * Sets the value of the i-th element in the datapool array debugVar
 * \param i Index variable
 * \param debugVar The value to be stored into the i-th element of datapool
 * array debugVar.
 */
static inline void setDpdebugVarItem(int i, uint32_t debugVar)
{
  dpServHkVars.debugVar[i] = debugVar;
}

/**
 * Gets the datapool array lstId
 * \return The datapool array lstId
 */
static inline uint16_t* getDplstIdArray()
{
  return &dpServHkVars.lstId[0];
}

/**
 * Gets the value of the i-th element in the datapool array lstId
 * \param i Index variable
 * \return The i-th element in the datapool array lstId
 */
static inline uint16_t getDplstIdItem(int i)
{
  return dpServHkVars.lstId[i];
}

/**
 * Sets the value of the i-th element in the datapool array lstId
 * \param i Index variable
 * \param lstId The value to be stored into the i-th element of datapool array
 * lstId.
 */
static inline void setDplstIdItem(int i, uint16_t lstId)
{
  dpServHkVars.lstId[i] = lstId;
}

/**
 * Gets the datapool array lstNSampRep
 * \return The datapool array lstNSampRep
 */
static inline uint16_t* getDplstNSampRepArray()
{
  return &dpServHkVars.lstNSampRep[0];
}

/**
 * Gets the value of the i-th element in the datapool array lstNSampRep
 * \param i Index variable
 * \return The i-th element in the datapool array lstNSampRep
 */
static inline uint16_t getDplstNSampRepItem(int i)
{
  return dpServHkVars.lstNSampRep[i];
}

/**
 * Sets the value of the i-th element in the datapool array lstNSampRep
 * \param i Index variable
 * \param lstNSampRep The value to be stored into the i-th element of datapool
 * array lstNSampRep.
 */
static inline void setDplstNSampRepItem(int i, uint16_t lstNSampRep)
{
  dpServHkVars.lstNSampRep[i] = lstNSampRep;
}

/**
 * Gets the datapool array lstSampleRep
 * \return The datapool array lstSampleRep
 */
static inline uint16_t* getDplstSampleRepArray()
{
  return &dpServHkVars.lstSampleRep[0];
}

/**
 * Gets the value of the i-th element in the datapool array lstSampleRep
 * \param i Index variable
 * \return The i-th element in the datapool array lstSampleRep
 */
static inline uint16_t getDplstSampleRepItem(int i)
{
  return dpServHkVars.lstSampleRep[i];
}

/**
 * Sets the value of the i-th element in the datapool array lstSampleRep
 * \param i Index variable
 * \param lstSampleRep The value to be stored into the i-th element of
 * datapool array lstSampleRep.
 */
static inline void setDplstSampleRepItem(int i, uint16_t lstSampleRep)
{
  dpServHkVars.lstSampleRep[i] = lstSampleRep;
}

/**
 * Gets the datapool array nSimple
 * \return The datapool array nSimple
 */
static inline uint16_t* getDpnSimpleArray()
{
  return &dpServHkVars.nSimple[0];
}

/**
 * Gets the value of the i-th element in the datapool array nSimple
 * \param i Index variable
 * \return The i-th element in the datapool array nSimple
 */
static inline uint16_t getDpnSimpleItem(int i)
{
  return dpServHkVars.nSimple[i];
}

/**
 * Sets the value of the i-th element in the datapool array nSimple
 * \param i Index variable
 * \param nSimple The value to be stored into the i-th element of datapool
 * array nSimple.
 */
static inline void setDpnSimpleItem(int i, uint16_t nSimple)
{
  dpServHkVars.nSimple[i] = nSimple;
}

/**
 * Gets the datapool array sampleBufId
 * \return The datapool array sampleBufId
 */
static inline uint16_t* getDpsampleBufIdArray()
{
  return &dpServHkVars.sampleBufId[0];
}

/**
 * Gets the value of the i-th element in the datapool array sampleBufId
 * \param i Index variable
 * \return The i-th element in the datapool array sampleBufId
 */
static inline uint16_t getDpsampleBufIdItem(int i)
{
  return dpServHkVars.sampleBufId[i];
}

/**
 * Sets the value of the i-th element in the datapool array sampleBufId
 * \param i Index variable
 * \param sampleBufId The value to be stored into the i-th element of datapool
 * array sampleBufId.
 */
static inline void setDpsampleBufIdItem(int i, uint16_t sampleBufId)
{
  dpServHkVars.sampleBufId[i] = sampleBufId;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSDPSERVHK_H */
