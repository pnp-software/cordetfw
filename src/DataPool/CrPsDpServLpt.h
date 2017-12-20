/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-11-22 12:47:43
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSDPSERVLpt_H_
#define CRPSDPSERVLpt_H_

#include "CrPsDpTypes.h"
#include <CrPsUserConstants.h>
#include <CrFwUserConstants.h>

/**
 * Type description
 */
typedef struct {
  /**
   * CrPsTimeOut_t TimeOut
   */
  CrPsTimeOut_t lptTimeOut[LPT_N_BUF];
} DpServLptParams_t;

/**
 * Type description
 */
typedef struct {
  /**
   * CrPsTid_t Array of LPT_N_BUF elements. The I-th element holds the large
   * message transaction identifier associated to the packet in the I-th LPT
   * Buffer
   */
  CrPsTid_t largeMsgTransId[LPT_N_BUF];
  /**
   * CrPsFailCode_t Array of LPT_N_BUF elements. The I-th element holds the
   * failure code for the up-transfer to the LPT Buffer
   */
  CrPsFailCode_t lptFailCode[LPT_N_BUF];
  /**
   * CrPsSize_t Array of LPT_N_BUF elements. The I-th element holds the
   * remaining size of the large packet in the I-th LPT Buffer (the part of
   * the large packet not yet down-transferred)
   */
  CrPsSize_t lptRemSize[LPT_N_BUF];
  /**
   * CrPsSize_t Array of LPT_N_BUF elements. The I-th element holds the size
   * of the large packet in the I-th LPT Buffer
   */
  CrPsSize_t lptSize[LPT_N_BUF];
  /**
   * CrPsDestSrc_t Array of LPT_N_BUF elements. The I-th element holds the
   * source for the currently on-going large packet up-transfer to the LPT
   * Buffer
   */
  CrPsDestSrc_t lptSrc[LPT_N_BUF];
  /**
   * CrFwTimeStamp_t Array of LPT_N_BUF elements. The I-th element holds the
   * time when the last up-transfer command to the LPT Buffer was received
   */
  CrFwTimeStamp_t lptTime[LPT_N_BUF];
  /**
   * conteru4_t Number of on-going down-link transfers
   */
  CrFwCounterU4_t nOfDownlinks;
  /**
   * conteru4_t Number of on-going up-link transfers
   */
  CrFwCounterU4_t nOfUplinks;
  /**
   * conteru4_t Array of LPT_N_BUF elements. The I-th element holds the part
   * sequence number for the currently on-going large packet transfer to/from
   * the LPT Buffer
   */
  CrFwCounterU4_t partSeqNmb[LPT_N_BUF];
} DpServLptVars_t;

extern DpServLptParams_t dpServLptParams;
extern DpServLptVars_t dpServLptVars;

/**
 * Initialises ServLpt
 */
void initDpServLpt(void);

/**
 * Gets the datapool array lptTimeOut
 * \return The datapool array lptTimeOut
 */
static inline CrPsTimeOut_t* getDplptTimeOutArray()
{
  return &dpServLptParams.lptTimeOut[0];
}

/**
 * Gets the value of the i-th element in the datapool array lptTimeOut
 * \param i Index variable
 * \return The i-th element in the datapool array lptTimeOut
 */
static inline CrPsTimeOut_t getDplptTimeOutItem(int i)
{
  return dpServLptParams.lptTimeOut[i];
}

/**
 * Sets the value of the i-th element in the datapool array lptTimeOut
 * \param i Index variable
 * \param lptTimeOut The value to be stored into the i-th element of datapool
 * array lptTimeOut.
 */
static inline void setDplptTimeOutItem(int i, CrPsTimeOut_t lptTimeOut)
{
  dpServLptParams.lptTimeOut[i] = lptTimeOut;
}

/**
 * Gets the datapool array largeMsgTransId
 * \return The datapool array largeMsgTransId
 */
static inline CrPsTid_t* getDplargeMsgTransIdArray()
{
  return &dpServLptVars.largeMsgTransId[0];
}

/**
 * Gets the value of the i-th element in the datapool array largeMsgTransId
 * \param i Index variable
 * \return The i-th element in the datapool array largeMsgTransId
 */
static inline CrPsTid_t getDplargeMsgTransIdItem(int i)
{
  return dpServLptVars.largeMsgTransId[i];
}

/**
 * Sets the value of the i-th element in the datapool array largeMsgTransId
 * \param i Index variable
 * \param largeMsgTransId The value to be stored into the i-th element of
 * datapool array largeMsgTransId.
 */
static inline void setDplargeMsgTransIdItem(int i, CrPsTid_t largeMsgTransId)
{
  dpServLptVars.largeMsgTransId[i] = largeMsgTransId;
}

/**
 * Gets the datapool array lptFailCode
 * \return The datapool array lptFailCode
 */
static inline CrPsFailCode_t* getDplptFailCodeArray()
{
  return &dpServLptVars.lptFailCode[0];
}

/**
 * Gets the value of the i-th element in the datapool array lptFailCode
 * \param i Index variable
 * \return The i-th element in the datapool array lptFailCode
 */
static inline CrPsFailCode_t getDplptFailCodeItem(int i)
{
  return dpServLptVars.lptFailCode[i];
}

/**
 * Sets the value of the i-th element in the datapool array lptFailCode
 * \param i Index variable
 * \param lptFailCode The value to be stored into the i-th element of datapool
 * array lptFailCode.
 */
static inline void setDplptFailCodeItem(int i, CrPsFailCode_t lptFailCode)
{
  dpServLptVars.lptFailCode[i] = lptFailCode;
}

/**
 * Gets the datapool array lptRemSize
 * \return The datapool array lptRemSize
 */
static inline CrPsSize_t* getDplptRemSizeArray()
{
  return &dpServLptVars.lptRemSize[0];
}

/**
 * Gets the value of the i-th element in the datapool array lptRemSize
 * \param i Index variable
 * \return The i-th element in the datapool array lptRemSize
 */
static inline CrPsSize_t getDplptRemSizeItem(int i)
{
  return dpServLptVars.lptRemSize[i];
}

/**
 * Sets the value of the i-th element in the datapool array lptRemSize
 * \param i Index variable
 * \param lptRemSize The value to be stored into the i-th element of datapool
 * array lptRemSize.
 */
static inline void setDplptRemSizeItem(int i, CrPsSize_t lptRemSize)
{
  dpServLptVars.lptRemSize[i] = lptRemSize;
}

/**
 * Gets the datapool array lptSize
 * \return The datapool array lptSize
 */
static inline CrPsSize_t* getDplptSizeArray()
{
  return &dpServLptVars.lptSize[0];
}

/**
 * Gets the value of the i-th element in the datapool array lptSize
 * \param i Index variable
 * \return The i-th element in the datapool array lptSize
 */
static inline CrPsSize_t getDplptSizeItem(int i)
{
  return dpServLptVars.lptSize[i];
}

/**
 * Sets the value of the i-th element in the datapool array lptSize
 * \param i Index variable
 * \param lptSize The value to be stored into the i-th element of datapool
 * array lptSize.
 */
static inline void setDplptSizeItem(int i, CrPsSize_t lptSize)
{
  dpServLptVars.lptSize[i] = lptSize;
}

/**
 * Gets the datapool array lptSrc
 * \return The datapool array lptSrc
 */
static inline CrPsDestSrc_t* getDplptSrcArray()
{
  return &dpServLptVars.lptSrc[0];
}

/**
 * Gets the value of the i-th element in the datapool array lptSrc
 * \param i Index variable
 * \return The i-th element in the datapool array lptSrc
 */
static inline CrPsDestSrc_t getDplptSrcItem(int i)
{
  return dpServLptVars.lptSrc[i];
}

/**
 * Sets the value of the i-th element in the datapool array lptSrc
 * \param i Index variable
 * \param lptSrc The value to be stored into the i-th element of datapool
 * array lptSrc.
 */
static inline void setDplptSrcItem(int i, CrPsDestSrc_t lptSrc)
{
  dpServLptVars.lptSrc[i] = lptSrc;
}

/**
 * Gets the datapool array lptTime
 * \return The datapool array lptTime
 */
static inline CrFwTimeStamp_t* getDplptTimeArray()
{
  return &dpServLptVars.lptTime[0];
}

/**
 * Gets the value of the i-th element in the datapool array lptTime
 * \param i Index variable
 * \return The i-th element in the datapool array lptTime
 */
static inline CrFwTimeStamp_t getDplptTimeItem(int i)
{
  return dpServLptVars.lptTime[i];
}

/**
 * Sets the value of the i-th element in the datapool array lptTime
 * \param i Index variable
 * \param lptTime The value to be stored into the i-th element of datapool
 * array lptTime.
 */
static inline void setDplptTimeItem(int i, CrFwTimeStamp_t lptTime)
{
  dpServLptVars.lptTime[i] = lptTime;
}

/**
 * Gets the value of the datapool item nOfDownlinks
 * \return The value of datapool item nOfDownlinks
 */
static inline CrFwCounterU4_t getDpnOfDownlinks()
{
  return dpServLptVars.nOfDownlinks;
}

/**
 * Sets the value of the datapool item nOfDownlinks
 * \param nOfDownlinks The value to be stored into the datapool item
 * nOfDownlinks.
 */
static inline void setDpnOfDownlinks(CrFwCounterU4_t nOfDownlinks)
{
  dpServLptVars.nOfDownlinks = nOfDownlinks;
}

/**
 * Gets the value of the datapool item nOfUplinks
 * \return The value of datapool item nOfUplinks
 */
static inline CrFwCounterU4_t getDpnOfUplinks()
{
  return dpServLptVars.nOfUplinks;
}

/**
 * Sets the value of the datapool item nOfUplinks
 * \param nOfUplinks The value to be stored into the datapool item nOfUplinks.
 */
static inline void setDpnOfUplinks(CrFwCounterU4_t nOfUplinks)
{
  dpServLptVars.nOfUplinks = nOfUplinks;
}

/**
 * Gets the datapool array partSeqNmb
 * \return The datapool array partSeqNmb
 */
static inline CrFwCounterU4_t* getDppartSeqNmbArray()
{
  return &dpServLptVars.partSeqNmb[0];
}

/**
 * Gets the value of the i-th element in the datapool array partSeqNmb
 * \param i Index variable
 * \return The i-th element in the datapool array partSeqNmb
 */
static inline CrFwCounterU4_t getDppartSeqNmbItem(int i)
{
  return dpServLptVars.partSeqNmb[i];
}

/**
 * Sets the value of the i-th element in the datapool array partSeqNmb
 * \param i Index variable
 * \param partSeqNmb The value to be stored into the i-th element of datapool
 * array partSeqNmb.
 */
static inline void setDppartSeqNmbItem(int i, CrFwCounterU4_t partSeqNmb)
{
  dpServLptVars.partSeqNmb[i] = partSeqNmb;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSDPSERVLpt_H */
