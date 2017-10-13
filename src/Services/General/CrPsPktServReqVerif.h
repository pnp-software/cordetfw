/**
 * \file
 *
 * Interface for accessing fields in packets of service "ServReqVerif".
 *
 * \note This file was generated on 2017-10-04 15:13:20
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSPKTSERVREQVERIF_H_
#define CRPSPKTSERVREQVERIF_H_

#include "CrPsDpTypes.h"

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
  uint16_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  uint16_t TcPacketSeqCtrl;
  
} VerSuccessAccRep_t __attribute__((aligned(4)));

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
  uint16_t TcFailureCode;
  
  /**
   * Copy of the PACKET ID fields of the command being reported on
   */
  uint16_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  uint16_t TcPacketSeqCtrl;
  
  /**
   * Packet type from the received TC
   */
  uint8_t TcType;
  
  /**
   * Packet sub-type from the received TC
   */
  uint8_t TcSubtype;
  
  /**
   * Discriminant from the received TC
   */
  uint8_t TcDisc;
  
} VerFailedAccRep_t __attribute__((aligned(4)));

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
  uint16_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  uint16_t TcPacketSeqCtrl;
  
} VerSuccessStartRep_t __attribute__((aligned(4)));

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
  uint16_t TcFailureCode;
  
  /**
   * Copy of the PACKET ID fields of the command being reported on
   */
  uint16_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  uint16_t TcPacketSeqCtrl;
  
  /**
   * Packet type from the received TC
   */
  uint8_t TcType;
  
  /**
   * Packet sub-type from the received TC
   */
  uint8_t TcSubtype;
  
  /**
   * Discriminant from the received TC
   */
  uint8_t TcDisc;
  
} VerFailedStartRep_t __attribute__((aligned(4)));

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
  uint16_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  uint16_t TcPacketSeqCtrl;
  
  /**
   * Step ID
   */
  uint32_t StepId;
  
} VerSuccessPrgrRep_t __attribute__((aligned(4)));

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
  uint16_t TcFailureCode;
  
  /**
   * Copy of the PACKET ID fields of the command being reported on
   */
  uint16_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  uint16_t TcPacketSeqCtrl;
  
  /**
   * Step ID
   */
  uint32_t StepId;
  
  /**
   * Packet type from the received TC
   */
  uint8_t TcType;
  
  /**
   * Packet sub-type from the received TC
   */
  uint8_t TcSubtype;
  
  /**
   * Discriminant from the received TC
   */
  uint8_t TcDisc;
  
} VerFailedPrgrRep_t __attribute__((aligned(4)));

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
  uint16_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  uint16_t TcPacketSeqCtrl;
  
} VerSuccessTermRep_t __attribute__((aligned(4)));

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
  uint16_t TcFailureCode;
  
  /**
   * Copy of the PACKET ID fields of the command being reported on
   */
  uint16_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  uint16_t TcPacketSeqCtrl;
  
  /**
   * Packet type from the received TC
   */
  uint8_t TcType;
  
  /**
   * Packet sub-type from the received TC
   */
  uint8_t TcSubtype;
  
  /**
   * Discriminant from the received TC
   */
  uint8_t TcDisc;
  
} VerFailedTermRep_t __attribute__((aligned(4)));

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
  uint16_t TcFailureCode;
  
  /**
   * Copy of the PACKET ID fields of the command being reported on
   */
  uint16_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  uint16_t TcPacketSeqCtrl;
  
  /**
   * Packet type from the received TC
   */
  uint8_t TcType;
  
  /**
   * Packet sub-type from the received TC
   */
  uint8_t TcSubtype;
  
  /**
   * Discriminant from the received TC
   */
  uint8_t TcDisc;
  
  /**
   * invalid Destination for Rerouting Failure
   */
  uint16_t invDest;
  
} VerFailedRoutingRep_t __attribute__((aligned(4)));

/**
 * Get "TcPacketId" from "VerSuccessAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline uint16_t getVerSuccessAccRepTcPacketId(void* p)
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
static inline void setVerSuccessAccRepTcPacketId(void* p, uint16_t TcPacketId)
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
static inline uint16_t getVerSuccessAccRepTcPacketSeqCtrl(void* p)
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
static inline void setVerSuccessAccRepTcPacketSeqCtrl(void* p, uint16_t TcPacketSeqCtrl)
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
static inline uint16_t getVerFailedAccRepTcFailureCode(void* p)
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
static inline void setVerFailedAccRepTcFailureCode(void* p, uint16_t TcFailureCode)
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
static inline uint16_t getVerFailedAccRepTcPacketId(void* p)
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
static inline void setVerFailedAccRepTcPacketId(void* p, uint16_t TcPacketId)
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
static inline uint16_t getVerFailedAccRepTcPacketSeqCtrl(void* p)
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
static inline void setVerFailedAccRepTcPacketSeqCtrl(void* p, uint16_t TcPacketSeqCtrl)
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
static inline uint8_t getVerFailedAccRepTcType(void* p)
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
static inline void setVerFailedAccRepTcType(void* p, uint8_t TcType)
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
static inline uint8_t getVerFailedAccRepTcSubtype(void* p)
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
static inline void setVerFailedAccRepTcSubtype(void* p, uint8_t TcSubtype)
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
static inline uint8_t getVerFailedAccRepTcDisc(void* p)
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
static inline void setVerFailedAccRepTcDisc(void* p, uint8_t TcDisc)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  t->TcDisc = TcDisc;
}

/**
 * Get "TcPacketId" from "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline uint16_t getVerSuccessStartRepTcPacketId(void* p)
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
static inline void setVerSuccessStartRepTcPacketId(void* p, uint16_t TcPacketId)
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
static inline uint16_t getVerSuccessStartRepTcPacketSeqCtrl(void* p)
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
static inline void setVerSuccessStartRepTcPacketSeqCtrl(void* p, uint16_t TcPacketSeqCtrl)
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
static inline uint16_t getVerFailedStartRepTcFailureCode(void* p)
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
static inline void setVerFailedStartRepTcFailureCode(void* p, uint16_t TcFailureCode)
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
static inline uint16_t getVerFailedStartRepTcPacketId(void* p)
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
static inline void setVerFailedStartRepTcPacketId(void* p, uint16_t TcPacketId)
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
static inline uint16_t getVerFailedStartRepTcPacketSeqCtrl(void* p)
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
static inline void setVerFailedStartRepTcPacketSeqCtrl(void* p, uint16_t TcPacketSeqCtrl)
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
static inline uint8_t getVerFailedStartRepTcType(void* p)
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
static inline void setVerFailedStartRepTcType(void* p, uint8_t TcType)
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
static inline uint8_t getVerFailedStartRepTcSubtype(void* p)
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
static inline void setVerFailedStartRepTcSubtype(void* p, uint8_t TcSubtype)
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
static inline uint8_t getVerFailedStartRepTcDisc(void* p)
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
static inline void setVerFailedStartRepTcDisc(void* p, uint8_t TcDisc)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  t->TcDisc = TcDisc;
}

/**
 * Get "TcPacketId" from "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline uint16_t getVerSuccessPrgrRepTcPacketId(void* p)
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
static inline void setVerSuccessPrgrRepTcPacketId(void* p, uint16_t TcPacketId)
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
static inline uint16_t getVerSuccessPrgrRepTcPacketSeqCtrl(void* p)
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
static inline void setVerSuccessPrgrRepTcPacketSeqCtrl(void* p, uint16_t TcPacketSeqCtrl)
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
static inline uint32_t getVerSuccessPrgrRepStepId(void* p)
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
static inline void setVerSuccessPrgrRepStepId(void* p, uint32_t StepId)
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
static inline uint16_t getVerFailedPrgrRepTcFailureCode(void* p)
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
static inline void setVerFailedPrgrRepTcFailureCode(void* p, uint16_t TcFailureCode)
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
static inline uint16_t getVerFailedPrgrRepTcPacketId(void* p)
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
static inline void setVerFailedPrgrRepTcPacketId(void* p, uint16_t TcPacketId)
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
static inline uint16_t getVerFailedPrgrRepTcPacketSeqCtrl(void* p)
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
static inline void setVerFailedPrgrRepTcPacketSeqCtrl(void* p, uint16_t TcPacketSeqCtrl)
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
static inline uint32_t getVerFailedPrgrRepStepId(void* p)
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
static inline void setVerFailedPrgrRepStepId(void* p, uint32_t StepId)
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
static inline uint8_t getVerFailedPrgrRepTcType(void* p)
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
static inline void setVerFailedPrgrRepTcType(void* p, uint8_t TcType)
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
static inline uint8_t getVerFailedPrgrRepTcSubtype(void* p)
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
static inline void setVerFailedPrgrRepTcSubtype(void* p, uint8_t TcSubtype)
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
static inline uint8_t getVerFailedPrgrRepTcDisc(void* p)
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
static inline void setVerFailedPrgrRepTcDisc(void* p, uint8_t TcDisc)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  t->TcDisc = TcDisc;
}

/**
 * Get "TcPacketId" from "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline uint16_t getVerSuccessTermRepTcPacketId(void* p)
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
static inline void setVerSuccessTermRepTcPacketId(void* p, uint16_t TcPacketId)
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
static inline uint16_t getVerSuccessTermRepTcPacketSeqCtrl(void* p)
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
static inline void setVerSuccessTermRepTcPacketSeqCtrl(void* p, uint16_t TcPacketSeqCtrl)
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
static inline uint16_t getVerFailedTermRepTcFailureCode(void* p)
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
static inline void setVerFailedTermRepTcFailureCode(void* p, uint16_t TcFailureCode)
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
static inline uint16_t getVerFailedTermRepTcPacketId(void* p)
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
static inline void setVerFailedTermRepTcPacketId(void* p, uint16_t TcPacketId)
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
static inline uint16_t getVerFailedTermRepTcPacketSeqCtrl(void* p)
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
static inline void setVerFailedTermRepTcPacketSeqCtrl(void* p, uint16_t TcPacketSeqCtrl)
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
static inline uint8_t getVerFailedTermRepTcType(void* p)
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
static inline void setVerFailedTermRepTcType(void* p, uint8_t TcType)
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
static inline uint8_t getVerFailedTermRepTcSubtype(void* p)
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
static inline void setVerFailedTermRepTcSubtype(void* p, uint8_t TcSubtype)
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
static inline uint8_t getVerFailedTermRepTcDisc(void* p)
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
static inline void setVerFailedTermRepTcDisc(void* p, uint8_t TcDisc)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  t->TcDisc = TcDisc;
}

/**
 * Get "TcFailureCode" from "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcFailureCode".
 */
static inline uint16_t getVerFailedRoutingRepTcFailureCode(void* p)
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
static inline void setVerFailedRoutingRepTcFailureCode(void* p, uint16_t TcFailureCode)
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
static inline uint16_t getVerFailedRoutingRepTcPacketId(void* p)
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
static inline void setVerFailedRoutingRepTcPacketId(void* p, uint16_t TcPacketId)
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
static inline uint16_t getVerFailedRoutingRepTcPacketSeqCtrl(void* p)
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
static inline void setVerFailedRoutingRepTcPacketSeqCtrl(void* p, uint16_t TcPacketSeqCtrl)
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
static inline uint8_t getVerFailedRoutingRepTcType(void* p)
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
static inline void setVerFailedRoutingRepTcType(void* p, uint8_t TcType)
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
static inline uint8_t getVerFailedRoutingRepTcSubtype(void* p)
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
static inline void setVerFailedRoutingRepTcSubtype(void* p, uint8_t TcSubtype)
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
static inline uint8_t getVerFailedRoutingRepTcDisc(void* p)
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
static inline void setVerFailedRoutingRepTcDisc(void* p, uint8_t TcDisc)
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
static inline uint16_t getVerFailedRoutingRepinvDest(void* p)
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
static inline void setVerFailedRoutingRepinvDest(void* p, uint16_t invDest)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  t->invDest = __builtin_bswap16(invDest);
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSPKTSERVREQVERIF_H */
