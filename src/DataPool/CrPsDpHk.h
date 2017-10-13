/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-10-06 18:28:46
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSDPHK_H_
#define CRPSDPHK_H_

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
   * Array of HK_N_REP_DEF elements. The I-th element is the SID of the I-th
   * Report Definition in the RDL
   */
  uint16_t sid[HK_N_REP_DEF];
} DpHkParams_t;

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
  uint16_t lstId[HK_MAX_N_ITEMS];
  /**
   * Max N rep
   */
  uint16_t lstNSampRep[HK_MAX_N_REP];
  /**
   * max N group
   */
  uint16_t lstSampleRep[HK_MAX_N_GR];
  /**
   * max ximple
   */
  uint16_t nSimple[HK_MAX_N_SIMPLE];
  /**
   * Array of HK_N_REP_DEF elements. The I-th element is the identifier of the
   * Sampling Buffer for the I-th Report Definition in the RDL
   */
  uint16_t sampleBufId[HK_N_REP_DEF];
} DpHkVars_t;

extern DpHkParams_t dpHkParams;
extern DpHkVars_t dpHkVars;

/**
 * Initialises Hk
 */
void initDpHk(void);

/**
 * Gets the datapool array debugVarAddr
 * \return The datapool array debugVarAddr
 */
static inline uint32_t* getDpdebugVarAddrArray()
{
  return &dpHkParams.debugVarAddr[0];
}

/**
 * Gets the value of the i-th element in the datapool array debugVarAddr
 * \param i Index variable
 * \return The i-th element in the datapool array debugVarAddr
 */
static inline uint32_t getDpdebugVarAddrItem(int i)
{
  return dpHkParams.debugVarAddr[i];
}

/**
 * Sets the value of the i-th element in the datapool array debugVarAddr
 * \param i Index variable
 * \param debugVarAddr The value to be stored into the i-th element of
 * datapool array debugVarAddr.
 */
static inline void setDpdebugVarAddrItem(int i, uint32_t debugVarAddr)
{
  dpHkParams.debugVarAddr[i] = debugVarAddr;
}

/**
 * Gets the datapool array dest
 * \return The datapool array dest
 */
static inline uint16_t* getDpdestArray()
{
  return &dpHkParams.dest[0];
}

/**
 * Gets the value of the i-th element in the datapool array dest
 * \param i Index variable
 * \return The i-th element in the datapool array dest
 */
static inline uint16_t getDpdestItem(int i)
{
  return dpHkParams.dest[i];
}

/**
 * Sets the value of the i-th element in the datapool array dest
 * \param i Index variable
 * \param dest The value to be stored into the i-th element of datapool array
 * dest.
 */
static inline void setDpdestItem(int i, uint16_t dest)
{
  dpHkParams.dest[i] = dest;
}

/**
 * Gets the datapool array isEnabled
 * \return The datapool array isEnabled
 */
static inline uint8_t* getDpisEnabledArray()
{
  return &dpHkParams.isEnabled[0];
}

/**
 * Gets the value of the i-th element in the datapool array isEnabled
 * \param i Index variable
 * \return The i-th element in the datapool array isEnabled
 */
static inline uint8_t getDpisEnabledItem(int i)
{
  return dpHkParams.isEnabled[i];
}

/**
 * Sets the value of the i-th element in the datapool array isEnabled
 * \param i Index variable
 * \param isEnabled The value to be stored into the i-th element of datapool
 * array isEnabled.
 */
static inline void setDpisEnabledItem(int i, uint8_t isEnabled)
{
  dpHkParams.isEnabled[i] = isEnabled;
}

/**
 * Gets the datapool array sid
 * \return The datapool array sid
 */
static inline uint16_t* getDpsidArray()
{
  return &dpHkParams.sid[0];
}

/**
 * Gets the value of the i-th element in the datapool array sid
 * \param i Index variable
 * \return The i-th element in the datapool array sid
 */
static inline uint16_t getDpsidItem(int i)
{
  return dpHkParams.sid[i];
}

/**
 * Sets the value of the i-th element in the datapool array sid
 * \param i Index variable
 * \param sid The value to be stored into the i-th element of datapool array
 * sid.
 */
static inline void setDpsidItem(int i, uint16_t sid)
{
  dpHkParams.sid[i] = sid;
}

/**
 * Gets the datapool array cycleCnt
 * \return The datapool array cycleCnt
 */
static inline uint32_t* getDpcycleCntArray()
{
  return &dpHkVars.cycleCnt[0];
}

/**
 * Gets the value of the i-th element in the datapool array cycleCnt
 * \param i Index variable
 * \return The i-th element in the datapool array cycleCnt
 */
static inline uint32_t getDpcycleCntItem(int i)
{
  return dpHkVars.cycleCnt[i];
}

/**
 * Sets the value of the i-th element in the datapool array cycleCnt
 * \param i Index variable
 * \param cycleCnt The value to be stored into the i-th element of datapool
 * array cycleCnt.
 */
static inline void setDpcycleCntItem(int i, uint32_t cycleCnt)
{
  dpHkVars.cycleCnt[i] = cycleCnt;
}

/**
 * Gets the datapool array debugVar
 * \return The datapool array debugVar
 */
static inline uint32_t* getDpdebugVarArray()
{
  return &dpHkVars.debugVar[0];
}

/**
 * Gets the value of the i-th element in the datapool array debugVar
 * \param i Index variable
 * \return The i-th element in the datapool array debugVar
 */
static inline uint32_t getDpdebugVarItem(int i)
{
  return dpHkVars.debugVar[i];
}

/**
 * Sets the value of the i-th element in the datapool array debugVar
 * \param i Index variable
 * \param debugVar The value to be stored into the i-th element of datapool
 * array debugVar.
 */
static inline void setDpdebugVarItem(int i, uint32_t debugVar)
{
  dpHkVars.debugVar[i] = debugVar;
}

/**
 * Gets the datapool array lstId
 * \return The datapool array lstId
 */
static inline uint16_t* getDplstIdArray()
{
  return &dpHkVars.lstId[0];
}

/**
 * Gets the value of the i-th element in the datapool array lstId
 * \param i Index variable
 * \return The i-th element in the datapool array lstId
 */
static inline uint16_t getDplstIdItem(int i)
{
  return dpHkVars.lstId[i];
}

/**
 * Sets the value of the i-th element in the datapool array lstId
 * \param i Index variable
 * \param lstId The value to be stored into the i-th element of datapool array
 * lstId.
 */
static inline void setDplstIdItem(int i, uint16_t lstId)
{
  dpHkVars.lstId[i] = lstId;
}

/**
 * Gets the datapool array lstNSampRep
 * \return The datapool array lstNSampRep
 */
static inline uint16_t* getDplstNSampRepArray()
{
  return &dpHkVars.lstNSampRep[0];
}

/**
 * Gets the value of the i-th element in the datapool array lstNSampRep
 * \param i Index variable
 * \return The i-th element in the datapool array lstNSampRep
 */
static inline uint16_t getDplstNSampRepItem(int i)
{
  return dpHkVars.lstNSampRep[i];
}

/**
 * Sets the value of the i-th element in the datapool array lstNSampRep
 * \param i Index variable
 * \param lstNSampRep The value to be stored into the i-th element of datapool
 * array lstNSampRep.
 */
static inline void setDplstNSampRepItem(int i, uint16_t lstNSampRep)
{
  dpHkVars.lstNSampRep[i] = lstNSampRep;
}

/**
 * Gets the datapool array lstSampleRep
 * \return The datapool array lstSampleRep
 */
static inline uint16_t* getDplstSampleRepArray()
{
  return &dpHkVars.lstSampleRep[0];
}

/**
 * Gets the value of the i-th element in the datapool array lstSampleRep
 * \param i Index variable
 * \return The i-th element in the datapool array lstSampleRep
 */
static inline uint16_t getDplstSampleRepItem(int i)
{
  return dpHkVars.lstSampleRep[i];
}

/**
 * Sets the value of the i-th element in the datapool array lstSampleRep
 * \param i Index variable
 * \param lstSampleRep The value to be stored into the i-th element of
 * datapool array lstSampleRep.
 */
static inline void setDplstSampleRepItem(int i, uint16_t lstSampleRep)
{
  dpHkVars.lstSampleRep[i] = lstSampleRep;
}

/**
 * Gets the datapool array nSimple
 * \return The datapool array nSimple
 */
static inline uint16_t* getDpnSimpleArray()
{
  return &dpHkVars.nSimple[0];
}

/**
 * Gets the value of the i-th element in the datapool array nSimple
 * \param i Index variable
 * \return The i-th element in the datapool array nSimple
 */
static inline uint16_t getDpnSimpleItem(int i)
{
  return dpHkVars.nSimple[i];
}

/**
 * Sets the value of the i-th element in the datapool array nSimple
 * \param i Index variable
 * \param nSimple The value to be stored into the i-th element of datapool
 * array nSimple.
 */
static inline void setDpnSimpleItem(int i, uint16_t nSimple)
{
  dpHkVars.nSimple[i] = nSimple;
}

/**
 * Gets the datapool array sampleBufId
 * \return The datapool array sampleBufId
 */
static inline uint16_t* getDpsampleBufIdArray()
{
  return &dpHkVars.sampleBufId[0];
}

/**
 * Gets the value of the i-th element in the datapool array sampleBufId
 * \param i Index variable
 * \return The i-th element in the datapool array sampleBufId
 */
static inline uint16_t getDpsampleBufIdItem(int i)
{
  return dpHkVars.sampleBufId[i];
}

/**
 * Sets the value of the i-th element in the datapool array sampleBufId
 * \param i Index variable
 * \param sampleBufId The value to be stored into the i-th element of datapool
 * array sampleBufId.
 */
static inline void setDpsampleBufIdItem(int i, uint16_t sampleBufId)
{
  dpHkVars.sampleBufId[i] = sampleBufId;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSDPHK_H */
