/**
 * \file CrPsPktServReqVerif.h
 *
 * Interface for accessing fields in packets of service "ServReqVerif".
 *
 * \note This file was generated on 2017-10-17 15:38:24
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSPKTSERVREQVERIF_H_
#define CRPSPKTSERVREQVERIF_H_

#include "CrFwUserConstants.h"

#include "CrPsDpTypes.h"
#include "CrPsUserConstants.h"

#include "CrPsPkt.h"
/**
 * Structure for VerSuccessAccRep
 */
typedef struct __attribute__((packed)) _VerSuccessAccRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Copy of the PACKET ID fields of the command being reported on
   */
  CrFwTypeId_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  CrPsSeqCtrl_t TcPacketSeqCtrl;
  
} VerSuccessAccRep_t ;

/**
 * Structure for VerFailedAccRep
 */
typedef struct __attribute__((packed)) _VerFailedAccRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * The failure idetification code.
   */
  CrPsFailCode_t TcFailureCode;
  
  /**
   * Copy of the PACKET ID fields of the command being reported on
   */
  CrFwTypeId_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  CrPsSeqCtrl_t TcPacketSeqCtrl;
  
  /**
   * Packet type from the received TC
   */
  CrFwServType_t TcType;
  
  /**
   * Packet sub-type from the received TC
   */
  CrFwServSubType_t TcSubtype;
  
  /**
   * Discriminant from the received TC
   */
  CrFwDiscriminant_t TcDisc;
  
  /**
   * The failure Data
   */
  CrPsFailData_t TcFailureData;
  
} VerFailedAccRep_t ;

/**
 * Structure for VerSuccessStartRep
 */
typedef struct __attribute__((packed)) _VerSuccessStartRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Copy of the PACKET ID fields of the command being reported on
   */
  CrFwTypeId_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  CrPsSeqCtrl_t TcPacketSeqCtrl;
  
} VerSuccessStartRep_t ;

/**
 * Structure for VerFailedStartRep
 */
typedef struct __attribute__((packed)) _VerFailedStartRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * The failure idetification code.
   */
  CrPsFailCode_t TcFailureCode;
  
  /**
   * Copy of the PACKET ID fields of the command being reported on
   */
  CrFwTypeId_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  CrPsSeqCtrl_t TcPacketSeqCtrl;
  
  /**
   * Packet type from the received TC
   */
  CrFwServType_t TcType;
  
  /**
   * Packet sub-type from the received TC
   */
  CrFwServSubType_t TcSubtype;
  
  /**
   * Discriminant from the received TC
   */
  CrFwDiscriminant_t TcDisc;
  
  /**
   * The failure Data
   */
  CrPsFailData_t TcFailureData;
  
} VerFailedStartRep_t ;

/**
 * Structure for VerSuccessPrgrRep
 */
typedef struct __attribute__((packed)) _VerSuccessPrgrRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Copy of the PACKET ID fields of the command being reported on
   */
  CrFwTypeId_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  CrPsSeqCtrl_t TcPacketSeqCtrl;
  
  /**
   * Step ID
   */
  CrPsStepId_t StepId;
  
} VerSuccessPrgrRep_t ;

/**
 * Structure for VerFailedPrgrRep
 */
typedef struct __attribute__((packed)) _VerFailedPrgrRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * The failure idetification code.
   */
  CrPsFailCode_t TcFailureCode;
  
  /**
   * Copy of the PACKET ID fields of the command being reported on
   */
  CrFwTypeId_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  CrPsSeqCtrl_t TcPacketSeqCtrl;
  
  /**
   * Step ID
   */
  CrPsStepId_t StepId;
  
  /**
   * Packet type from the received TC
   */
  CrFwServType_t TcType;
  
  /**
   * Packet sub-type from the received TC
   */
  CrFwServSubType_t TcSubtype;
  
  /**
   * Discriminant from the received TC
   */
  CrFwDiscriminant_t TcDisc;
  
  /**
   * The failure Data
   */
  CrPsFailData_t TcFailureData;
  
} VerFailedPrgrRep_t ;

/**
 * Structure for VerSuccessTermRep
 */
typedef struct __attribute__((packed)) _VerSuccessTermRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Copy of the PACKET ID fields of the command being reported on
   */
  CrFwTypeId_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  CrPsSeqCtrl_t TcPacketSeqCtrl;
  
} VerSuccessTermRep_t ;

/**
 * Structure for VerFailedTermRep
 */
typedef struct __attribute__((packed)) _VerFailedTermRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * The failure idetification code.
   */
  CrPsFailCode_t TcFailureCode;
  
  /**
   * Copy of the PACKET ID fields of the command being reported on
   */
  CrFwTypeId_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  CrPsSeqCtrl_t TcPacketSeqCtrl;
  
  /**
   * Packet type from the received TC
   */
  CrFwServType_t TcType;
  
  /**
   * Packet sub-type from the received TC
   */
  CrFwServSubType_t TcSubtype;
  
  /**
   * Discriminant from the received TC
   */
  CrFwDiscriminant_t TcDisc;
  
  /**
   * The failure Data
   */
  CrPsFailData_t TcFailureData;
  
} VerFailedTermRep_t ;

/**
 * Structure for VerFailedRoutingRep
 */
typedef struct __attribute__((packed)) _VerFailedRoutingRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * The failure idetification code.
   */
  CrPsFailCode_t TcFailureCode;
  
  /**
   * Copy of the PACKET ID fields of the command being reported on
   */
  CrFwTypeId_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  CrPsSeqCtrl_t TcPacketSeqCtrl;
  
  /**
   * Packet type from the received TC
   */
  CrFwServType_t TcType;
  
  /**
   * Packet sub-type from the received TC
   */
  CrFwServSubType_t TcSubtype;
  
  /**
   * Discriminant from the received TC
   */
  CrFwDiscriminant_t TcDisc;
  
  /**
   * invalid Destination for Rerouting Failure
   */
  CrPsDestSrc_t invDest;
  
} VerFailedRoutingRep_t ;

/**
 * Get "TcPacketId" from "VerSuccessAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline CrFwTypeId_t getVerSuccessAccRepTcPacketId(void* p)
{
  VerSuccessAccRep_t* t;
  t = (VerSuccessAccRep_t*)p;
  return __builtin_bswap16(t->TcPacketId);
}

/**
 * Set "TcPacketId" in "VerSuccessAccRep" packet.
 * \param p Pointer to the packet.
 * \param TcPacketId Value of "TcPacketId" to be set in packet.
 */
static inline void setVerSuccessAccRepTcPacketId(void* p, CrFwTypeId_t TcPacketId)
{
  VerSuccessAccRep_t* t;
  t = (VerSuccessAccRep_t*)p;
  t->TcPacketId = __builtin_bswap16(TcPacketId);
}

/**
 * Get "TcPacketSeqCtrl" from "VerSuccessAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketSeqCtrl".
 */
static inline CrPsSeqCtrl_t getVerSuccessAccRepTcPacketSeqCtrl(void* p)
{
  VerSuccessAccRep_t* t;
  t = (VerSuccessAccRep_t*)p;
  return __builtin_bswap16(t->TcPacketSeqCtrl);
}

/**
 * Set "TcPacketSeqCtrl" in "VerSuccessAccRep" packet.
 * \param p Pointer to the packet.
 * \param TcPacketSeqCtrl Value of "TcPacketSeqCtrl" to be set in packet.
 */
static inline void setVerSuccessAccRepTcPacketSeqCtrl(void* p, CrPsSeqCtrl_t TcPacketSeqCtrl)
{
  VerSuccessAccRep_t* t;
  t = (VerSuccessAccRep_t*)p;
  t->TcPacketSeqCtrl = __builtin_bswap16(TcPacketSeqCtrl);
}

/**
 * Get "TcFailureCode" from "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcFailureCode".
 */
static inline CrPsFailCode_t getVerFailedAccRepTcFailureCode(void* p)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  return __builtin_bswap16(t->TcFailureCode);
}

/**
 * Set "TcFailureCode" in "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \param TcFailureCode Value of "TcFailureCode" to be set in packet.
 */
static inline void setVerFailedAccRepTcFailureCode(void* p, CrPsFailCode_t TcFailureCode)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  t->TcFailureCode = __builtin_bswap16(TcFailureCode);
}

/**
 * Get "TcPacketId" from "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline CrFwTypeId_t getVerFailedAccRepTcPacketId(void* p)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  return __builtin_bswap16(t->TcPacketId);
}

/**
 * Set "TcPacketId" in "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \param TcPacketId Value of "TcPacketId" to be set in packet.
 */
static inline void setVerFailedAccRepTcPacketId(void* p, CrFwTypeId_t TcPacketId)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  t->TcPacketId = __builtin_bswap16(TcPacketId);
}

/**
 * Get "TcPacketSeqCtrl" from "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketSeqCtrl".
 */
static inline CrPsSeqCtrl_t getVerFailedAccRepTcPacketSeqCtrl(void* p)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  return __builtin_bswap16(t->TcPacketSeqCtrl);
}

/**
 * Set "TcPacketSeqCtrl" in "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \param TcPacketSeqCtrl Value of "TcPacketSeqCtrl" to be set in packet.
 */
static inline void setVerFailedAccRepTcPacketSeqCtrl(void* p, CrPsSeqCtrl_t TcPacketSeqCtrl)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  t->TcPacketSeqCtrl = __builtin_bswap16(TcPacketSeqCtrl);
}

/**
 * Get "TcType" from "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcType".
 */
static inline CrFwServType_t getVerFailedAccRepTcType(void* p)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  return t->TcType;
}

/**
 * Set "TcType" in "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \param TcType Value of "TcType" to be set in packet.
 */
static inline void setVerFailedAccRepTcType(void* p, CrFwServType_t TcType)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  t->TcType = TcType;
}

/**
 * Get "TcSubtype" from "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcSubtype".
 */
static inline CrFwServSubType_t getVerFailedAccRepTcSubtype(void* p)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  return t->TcSubtype;
}

/**
 * Set "TcSubtype" in "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \param TcSubtype Value of "TcSubtype" to be set in packet.
 */
static inline void setVerFailedAccRepTcSubtype(void* p, CrFwServSubType_t TcSubtype)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  t->TcSubtype = TcSubtype;
}

/**
 * Get "TcDisc" from "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcDisc".
 */
static inline CrFwDiscriminant_t getVerFailedAccRepTcDisc(void* p)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  return t->TcDisc;
}

/**
 * Set "TcDisc" in "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \param TcDisc Value of "TcDisc" to be set in packet.
 */
static inline void setVerFailedAccRepTcDisc(void* p, CrFwDiscriminant_t TcDisc)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  t->TcDisc = TcDisc;
}

/**
 * Get "TcFailureData" from "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcFailureData".
 */
static inline CrPsFailData_t getVerFailedAccRepTcFailureData(void* p)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  return __builtin_bswap32(t->TcFailureData);
}

/**
 * Set "TcFailureData" in "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \param TcFailureData Value of "TcFailureData" to be set in packet.
 */
static inline void setVerFailedAccRepTcFailureData(void* p, CrPsFailData_t TcFailureData)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  t->TcFailureData = __builtin_bswap32(TcFailureData);
}

/**
 * Get "TcPacketId" from "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline CrFwTypeId_t getVerSuccessStartRepTcPacketId(void* p)
{
  VerSuccessStartRep_t* t;
  t = (VerSuccessStartRep_t*)p;
  return __builtin_bswap16(t->TcPacketId);
}

/**
 * Set "TcPacketId" in "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \param TcPacketId Value of "TcPacketId" to be set in packet.
 */
static inline void setVerSuccessStartRepTcPacketId(void* p, CrFwTypeId_t TcPacketId)
{
  VerSuccessStartRep_t* t;
  t = (VerSuccessStartRep_t*)p;
  t->TcPacketId = __builtin_bswap16(TcPacketId);
}

/**
 * Get "TcPacketSeqCtrl" from "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketSeqCtrl".
 */
static inline CrPsSeqCtrl_t getVerSuccessStartRepTcPacketSeqCtrl(void* p)
{
  VerSuccessStartRep_t* t;
  t = (VerSuccessStartRep_t*)p;
  return __builtin_bswap16(t->TcPacketSeqCtrl);
}

/**
 * Set "TcPacketSeqCtrl" in "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \param TcPacketSeqCtrl Value of "TcPacketSeqCtrl" to be set in packet.
 */
static inline void setVerSuccessStartRepTcPacketSeqCtrl(void* p, CrPsSeqCtrl_t TcPacketSeqCtrl)
{
  VerSuccessStartRep_t* t;
  t = (VerSuccessStartRep_t*)p;
  t->TcPacketSeqCtrl = __builtin_bswap16(TcPacketSeqCtrl);
}

/**
 * Get "TcFailureCode" from "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcFailureCode".
 */
static inline CrPsFailCode_t getVerFailedStartRepTcFailureCode(void* p)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  return __builtin_bswap16(t->TcFailureCode);
}

/**
 * Set "TcFailureCode" in "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \param TcFailureCode Value of "TcFailureCode" to be set in packet.
 */
static inline void setVerFailedStartRepTcFailureCode(void* p, CrPsFailCode_t TcFailureCode)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  t->TcFailureCode = __builtin_bswap16(TcFailureCode);
}

/**
 * Get "TcPacketId" from "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline CrFwTypeId_t getVerFailedStartRepTcPacketId(void* p)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  return __builtin_bswap16(t->TcPacketId);
}

/**
 * Set "TcPacketId" in "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \param TcPacketId Value of "TcPacketId" to be set in packet.
 */
static inline void setVerFailedStartRepTcPacketId(void* p, CrFwTypeId_t TcPacketId)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  t->TcPacketId = __builtin_bswap16(TcPacketId);
}

/**
 * Get "TcPacketSeqCtrl" from "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketSeqCtrl".
 */
static inline CrPsSeqCtrl_t getVerFailedStartRepTcPacketSeqCtrl(void* p)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  return __builtin_bswap16(t->TcPacketSeqCtrl);
}

/**
 * Set "TcPacketSeqCtrl" in "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \param TcPacketSeqCtrl Value of "TcPacketSeqCtrl" to be set in packet.
 */
static inline void setVerFailedStartRepTcPacketSeqCtrl(void* p, CrPsSeqCtrl_t TcPacketSeqCtrl)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  t->TcPacketSeqCtrl = __builtin_bswap16(TcPacketSeqCtrl);
}

/**
 * Get "TcType" from "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcType".
 */
static inline CrFwServType_t getVerFailedStartRepTcType(void* p)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  return t->TcType;
}

/**
 * Set "TcType" in "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \param TcType Value of "TcType" to be set in packet.
 */
static inline void setVerFailedStartRepTcType(void* p, CrFwServType_t TcType)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  t->TcType = TcType;
}

/**
 * Get "TcSubtype" from "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcSubtype".
 */
static inline CrFwServSubType_t getVerFailedStartRepTcSubtype(void* p)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  return t->TcSubtype;
}

/**
 * Set "TcSubtype" in "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \param TcSubtype Value of "TcSubtype" to be set in packet.
 */
static inline void setVerFailedStartRepTcSubtype(void* p, CrFwServSubType_t TcSubtype)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  t->TcSubtype = TcSubtype;
}

/**
 * Get "TcDisc" from "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcDisc".
 */
static inline CrFwDiscriminant_t getVerFailedStartRepTcDisc(void* p)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  return t->TcDisc;
}

/**
 * Set "TcDisc" in "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \param TcDisc Value of "TcDisc" to be set in packet.
 */
static inline void setVerFailedStartRepTcDisc(void* p, CrFwDiscriminant_t TcDisc)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  t->TcDisc = TcDisc;
}

/**
 * Get "TcFailureData" from "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcFailureData".
 */
static inline CrPsFailData_t getVerFailedStartRepTcFailureData(void* p)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  return __builtin_bswap32(t->TcFailureData);
}

/**
 * Set "TcFailureData" in "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \param TcFailureData Value of "TcFailureData" to be set in packet.
 */
static inline void setVerFailedStartRepTcFailureData(void* p, CrPsFailData_t TcFailureData)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  t->TcFailureData = __builtin_bswap32(TcFailureData);
}

/**
 * Get "TcPacketId" from "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline CrFwTypeId_t getVerSuccessPrgrRepTcPacketId(void* p)
{
  VerSuccessPrgrRep_t* t;
  t = (VerSuccessPrgrRep_t*)p;
  return __builtin_bswap16(t->TcPacketId);
}

/**
 * Set "TcPacketId" in "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param TcPacketId Value of "TcPacketId" to be set in packet.
 */
static inline void setVerSuccessPrgrRepTcPacketId(void* p, CrFwTypeId_t TcPacketId)
{
  VerSuccessPrgrRep_t* t;
  t = (VerSuccessPrgrRep_t*)p;
  t->TcPacketId = __builtin_bswap16(TcPacketId);
}

/**
 * Get "TcPacketSeqCtrl" from "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketSeqCtrl".
 */
static inline CrPsSeqCtrl_t getVerSuccessPrgrRepTcPacketSeqCtrl(void* p)
{
  VerSuccessPrgrRep_t* t;
  t = (VerSuccessPrgrRep_t*)p;
  return __builtin_bswap16(t->TcPacketSeqCtrl);
}

/**
 * Set "TcPacketSeqCtrl" in "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param TcPacketSeqCtrl Value of "TcPacketSeqCtrl" to be set in packet.
 */
static inline void setVerSuccessPrgrRepTcPacketSeqCtrl(void* p, CrPsSeqCtrl_t TcPacketSeqCtrl)
{
  VerSuccessPrgrRep_t* t;
  t = (VerSuccessPrgrRep_t*)p;
  t->TcPacketSeqCtrl = __builtin_bswap16(TcPacketSeqCtrl);
}

/**
 * Get "StepId" from "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "StepId".
 */
static inline CrPsStepId_t getVerSuccessPrgrRepStepId(void* p)
{
  VerSuccessPrgrRep_t* t;
  t = (VerSuccessPrgrRep_t*)p;
  return __builtin_bswap32(t->StepId);
}

/**
 * Set "StepId" in "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param StepId Value of "StepId" to be set in packet.
 */
static inline void setVerSuccessPrgrRepStepId(void* p, CrPsStepId_t StepId)
{
  VerSuccessPrgrRep_t* t;
  t = (VerSuccessPrgrRep_t*)p;
  t->StepId = __builtin_bswap32(StepId);
}

/**
 * Get "TcFailureCode" from "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcFailureCode".
 */
static inline CrPsFailCode_t getVerFailedPrgrRepTcFailureCode(void* p)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  return __builtin_bswap16(t->TcFailureCode);
}

/**
 * Set "TcFailureCode" in "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param TcFailureCode Value of "TcFailureCode" to be set in packet.
 */
static inline void setVerFailedPrgrRepTcFailureCode(void* p, CrPsFailCode_t TcFailureCode)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  t->TcFailureCode = __builtin_bswap16(TcFailureCode);
}

/**
 * Get "TcPacketId" from "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline CrFwTypeId_t getVerFailedPrgrRepTcPacketId(void* p)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  return __builtin_bswap16(t->TcPacketId);
}

/**
 * Set "TcPacketId" in "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param TcPacketId Value of "TcPacketId" to be set in packet.
 */
static inline void setVerFailedPrgrRepTcPacketId(void* p, CrFwTypeId_t TcPacketId)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  t->TcPacketId = __builtin_bswap16(TcPacketId);
}

/**
 * Get "TcPacketSeqCtrl" from "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketSeqCtrl".
 */
static inline CrPsSeqCtrl_t getVerFailedPrgrRepTcPacketSeqCtrl(void* p)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  return __builtin_bswap16(t->TcPacketSeqCtrl);
}

/**
 * Set "TcPacketSeqCtrl" in "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param TcPacketSeqCtrl Value of "TcPacketSeqCtrl" to be set in packet.
 */
static inline void setVerFailedPrgrRepTcPacketSeqCtrl(void* p, CrPsSeqCtrl_t TcPacketSeqCtrl)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  t->TcPacketSeqCtrl = __builtin_bswap16(TcPacketSeqCtrl);
}

/**
 * Get "StepId" from "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "StepId".
 */
static inline CrPsStepId_t getVerFailedPrgrRepStepId(void* p)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  return __builtin_bswap32(t->StepId);
}

/**
 * Set "StepId" in "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param StepId Value of "StepId" to be set in packet.
 */
static inline void setVerFailedPrgrRepStepId(void* p, CrPsStepId_t StepId)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  t->StepId = __builtin_bswap32(StepId);
}

/**
 * Get "TcType" from "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcType".
 */
static inline CrFwServType_t getVerFailedPrgrRepTcType(void* p)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  return t->TcType;
}

/**
 * Set "TcType" in "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param TcType Value of "TcType" to be set in packet.
 */
static inline void setVerFailedPrgrRepTcType(void* p, CrFwServType_t TcType)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  t->TcType = TcType;
}

/**
 * Get "TcSubtype" from "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcSubtype".
 */
static inline CrFwServSubType_t getVerFailedPrgrRepTcSubtype(void* p)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  return t->TcSubtype;
}

/**
 * Set "TcSubtype" in "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param TcSubtype Value of "TcSubtype" to be set in packet.
 */
static inline void setVerFailedPrgrRepTcSubtype(void* p, CrFwServSubType_t TcSubtype)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  t->TcSubtype = TcSubtype;
}

/**
 * Get "TcDisc" from "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcDisc".
 */
static inline CrFwDiscriminant_t getVerFailedPrgrRepTcDisc(void* p)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  return t->TcDisc;
}

/**
 * Set "TcDisc" in "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param TcDisc Value of "TcDisc" to be set in packet.
 */
static inline void setVerFailedPrgrRepTcDisc(void* p, CrFwDiscriminant_t TcDisc)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  t->TcDisc = TcDisc;
}

/**
 * Get "TcFailureData" from "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcFailureData".
 */
static inline CrPsFailData_t getVerFailedPrgrRepTcFailureData(void* p)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  return __builtin_bswap32(t->TcFailureData);
}

/**
 * Set "TcFailureData" in "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param TcFailureData Value of "TcFailureData" to be set in packet.
 */
static inline void setVerFailedPrgrRepTcFailureData(void* p, CrPsFailData_t TcFailureData)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  t->TcFailureData = __builtin_bswap32(TcFailureData);
}

/**
 * Get "TcPacketId" from "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline CrFwTypeId_t getVerSuccessTermRepTcPacketId(void* p)
{
  VerSuccessTermRep_t* t;
  t = (VerSuccessTermRep_t*)p;
  return __builtin_bswap16(t->TcPacketId);
}

/**
 * Set "TcPacketId" in "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \param TcPacketId Value of "TcPacketId" to be set in packet.
 */
static inline void setVerSuccessTermRepTcPacketId(void* p, CrFwTypeId_t TcPacketId)
{
  VerSuccessTermRep_t* t;
  t = (VerSuccessTermRep_t*)p;
  t->TcPacketId = __builtin_bswap16(TcPacketId);
}

/**
 * Get "TcPacketSeqCtrl" from "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketSeqCtrl".
 */
static inline CrPsSeqCtrl_t getVerSuccessTermRepTcPacketSeqCtrl(void* p)
{
  VerSuccessTermRep_t* t;
  t = (VerSuccessTermRep_t*)p;
  return __builtin_bswap16(t->TcPacketSeqCtrl);
}

/**
 * Set "TcPacketSeqCtrl" in "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \param TcPacketSeqCtrl Value of "TcPacketSeqCtrl" to be set in packet.
 */
static inline void setVerSuccessTermRepTcPacketSeqCtrl(void* p, CrPsSeqCtrl_t TcPacketSeqCtrl)
{
  VerSuccessTermRep_t* t;
  t = (VerSuccessTermRep_t*)p;
  t->TcPacketSeqCtrl = __builtin_bswap16(TcPacketSeqCtrl);
}

/**
 * Get "TcFailureCode" from "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcFailureCode".
 */
static inline CrPsFailCode_t getVerFailedTermRepTcFailureCode(void* p)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  return __builtin_bswap16(t->TcFailureCode);
}

/**
 * Set "TcFailureCode" in "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \param TcFailureCode Value of "TcFailureCode" to be set in packet.
 */
static inline void setVerFailedTermRepTcFailureCode(void* p, CrPsFailCode_t TcFailureCode)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  t->TcFailureCode = __builtin_bswap16(TcFailureCode);
}

/**
 * Get "TcPacketId" from "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline CrFwTypeId_t getVerFailedTermRepTcPacketId(void* p)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  return __builtin_bswap16(t->TcPacketId);
}

/**
 * Set "TcPacketId" in "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \param TcPacketId Value of "TcPacketId" to be set in packet.
 */
static inline void setVerFailedTermRepTcPacketId(void* p, CrFwTypeId_t TcPacketId)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  t->TcPacketId = __builtin_bswap16(TcPacketId);
}

/**
 * Get "TcPacketSeqCtrl" from "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketSeqCtrl".
 */
static inline CrPsSeqCtrl_t getVerFailedTermRepTcPacketSeqCtrl(void* p)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  return __builtin_bswap16(t->TcPacketSeqCtrl);
}

/**
 * Set "TcPacketSeqCtrl" in "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \param TcPacketSeqCtrl Value of "TcPacketSeqCtrl" to be set in packet.
 */
static inline void setVerFailedTermRepTcPacketSeqCtrl(void* p, CrPsSeqCtrl_t TcPacketSeqCtrl)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  t->TcPacketSeqCtrl = __builtin_bswap16(TcPacketSeqCtrl);
}

/**
 * Get "TcType" from "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcType".
 */
static inline CrFwServType_t getVerFailedTermRepTcType(void* p)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  return t->TcType;
}

/**
 * Set "TcType" in "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \param TcType Value of "TcType" to be set in packet.
 */
static inline void setVerFailedTermRepTcType(void* p, CrFwServType_t TcType)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  t->TcType = TcType;
}

/**
 * Get "TcSubtype" from "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcSubtype".
 */
static inline CrFwServSubType_t getVerFailedTermRepTcSubtype(void* p)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  return t->TcSubtype;
}

/**
 * Set "TcSubtype" in "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \param TcSubtype Value of "TcSubtype" to be set in packet.
 */
static inline void setVerFailedTermRepTcSubtype(void* p, CrFwServSubType_t TcSubtype)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  t->TcSubtype = TcSubtype;
}

/**
 * Get "TcDisc" from "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcDisc".
 */
static inline CrFwDiscriminant_t getVerFailedTermRepTcDisc(void* p)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  return t->TcDisc;
}

/**
 * Set "TcDisc" in "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \param TcDisc Value of "TcDisc" to be set in packet.
 */
static inline void setVerFailedTermRepTcDisc(void* p, CrFwDiscriminant_t TcDisc)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  t->TcDisc = TcDisc;
}

/**
 * Get "TcFailureData" from "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcFailureData".
 */
static inline CrPsFailData_t getVerFailedTermRepTcFailureData(void* p)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  return __builtin_bswap32(t->TcFailureData);
}

/**
 * Set "TcFailureData" in "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \param TcFailureData Value of "TcFailureData" to be set in packet.
 */
static inline void setVerFailedTermRepTcFailureData(void* p, CrPsFailData_t TcFailureData)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  t->TcFailureData = __builtin_bswap32(TcFailureData);
}

/**
 * Get "TcFailureCode" from "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcFailureCode".
 */
static inline CrPsFailCode_t getVerFailedRoutingRepTcFailureCode(void* p)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  return __builtin_bswap16(t->TcFailureCode);
}

/**
 * Set "TcFailureCode" in "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \param TcFailureCode Value of "TcFailureCode" to be set in packet.
 */
static inline void setVerFailedRoutingRepTcFailureCode(void* p, CrPsFailCode_t TcFailureCode)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  t->TcFailureCode = __builtin_bswap16(TcFailureCode);
}

/**
 * Get "TcPacketId" from "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline CrFwTypeId_t getVerFailedRoutingRepTcPacketId(void* p)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  return __builtin_bswap16(t->TcPacketId);
}

/**
 * Set "TcPacketId" in "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \param TcPacketId Value of "TcPacketId" to be set in packet.
 */
static inline void setVerFailedRoutingRepTcPacketId(void* p, CrFwTypeId_t TcPacketId)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  t->TcPacketId = __builtin_bswap16(TcPacketId);
}

/**
 * Get "TcPacketSeqCtrl" from "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketSeqCtrl".
 */
static inline CrPsSeqCtrl_t getVerFailedRoutingRepTcPacketSeqCtrl(void* p)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  return __builtin_bswap16(t->TcPacketSeqCtrl);
}

/**
 * Set "TcPacketSeqCtrl" in "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \param TcPacketSeqCtrl Value of "TcPacketSeqCtrl" to be set in packet.
 */
static inline void setVerFailedRoutingRepTcPacketSeqCtrl(void* p, CrPsSeqCtrl_t TcPacketSeqCtrl)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  t->TcPacketSeqCtrl = __builtin_bswap16(TcPacketSeqCtrl);
}

/**
 * Get "TcType" from "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcType".
 */
static inline CrFwServType_t getVerFailedRoutingRepTcType(void* p)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  return t->TcType;
}

/**
 * Set "TcType" in "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \param TcType Value of "TcType" to be set in packet.
 */
static inline void setVerFailedRoutingRepTcType(void* p, CrFwServType_t TcType)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  t->TcType = TcType;
}

/**
 * Get "TcSubtype" from "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcSubtype".
 */
static inline CrFwServSubType_t getVerFailedRoutingRepTcSubtype(void* p)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  return t->TcSubtype;
}

/**
 * Set "TcSubtype" in "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \param TcSubtype Value of "TcSubtype" to be set in packet.
 */
static inline void setVerFailedRoutingRepTcSubtype(void* p, CrFwServSubType_t TcSubtype)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  t->TcSubtype = TcSubtype;
}

/**
 * Get "TcDisc" from "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcDisc".
 */
static inline CrFwDiscriminant_t getVerFailedRoutingRepTcDisc(void* p)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  return t->TcDisc;
}

/**
 * Set "TcDisc" in "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \param TcDisc Value of "TcDisc" to be set in packet.
 */
static inline void setVerFailedRoutingRepTcDisc(void* p, CrFwDiscriminant_t TcDisc)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  t->TcDisc = TcDisc;
}

/**
 * Get "invDest" from "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "invDest".
 */
static inline CrPsDestSrc_t getVerFailedRoutingRepinvDest(void* p)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  return __builtin_bswap16(t->invDest);
}

/**
 * Set "invDest" in "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \param invDest Value of "invDest" to be set in packet.
 */
static inline void setVerFailedRoutingRepinvDest(void* p, CrPsDestSrc_t invDest)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  t->invDest = __builtin_bswap16(invDest);
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSPKTSERVREQVERIF_H */
