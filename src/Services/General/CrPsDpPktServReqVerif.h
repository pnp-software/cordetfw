/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-08-22 17:43:36
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSDPPKTSERVREQVERIF_H_
#define CRPSDPPKTSERVREQVERIF_H_

#include <Services/General/CrPsConstants.h>

/**
 * Structure for packet VerSuccessAccRep - 0
 */
typedef struct __attribute__((packed, aligned(4))) _VerSuccessAccRep0_t {
  /**
   * Header spacer.
   */
  uint8_t __header[OFFSET_PAR_LENGTH_OUT_REP_PCKT];

  /**
   * Discriminant
   */
  uint16_t Discriminant;
  
  /**
   * Copy of the PACKET ID fields of the command being reported on
   */
  uint16_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  uint16_t TcPacketSeqCtrl;
  
} VerSuccessAccRep0_t;

/**
 * Structure for packet VerFailedAccRep - 0
 */
typedef struct __attribute__((packed, aligned(4))) _VerFailedAccRep0_t {
  /**
   * Header spacer.
   */
  uint8_t __header[OFFSET_PAR_LENGTH_OUT_REP_PCKT];

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
  
} VerFailedAccRep0_t;

/**
 * Structure for packet VerSuccessStartRep - 0
 */
typedef struct __attribute__((packed, aligned(4))) _VerSuccessStartRep0_t {
  /**
   * Header spacer.
   */
  uint8_t __header[OFFSET_PAR_LENGTH_OUT_REP_PCKT];

  /**
   * Discriminant
   */
  uint16_t Discriminant;
  
  /**
   * Copy of the PACKET ID fields of the command being reported on
   */
  uint16_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  uint16_t TcPacketSeqCtrl;
  
} VerSuccessStartRep0_t;

/**
 * Structure for packet VerFailedStartRep - 0
 */
typedef struct __attribute__((packed, aligned(4))) _VerFailedStartRep0_t {
  /**
   * Header spacer.
   */
  uint8_t __header[OFFSET_PAR_LENGTH_OUT_REP_PCKT];

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
  
} VerFailedStartRep0_t;

/**
 * Structure for packet VerSuccessPrgrRep - 0
 */
typedef struct __attribute__((packed, aligned(4))) _VerSuccessPrgrRep0_t {
  /**
   * Header spacer.
   */
  uint8_t __header[OFFSET_PAR_LENGTH_OUT_REP_PCKT];

  /**
   * Discriminant
   */
  uint16_t Discriminant;
  
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
  
} VerSuccessPrgrRep0_t;

/**
 * Structure for packet VerFailedPrgrRep - 0
 */
typedef struct __attribute__((packed, aligned(4))) _VerFailedPrgrRep0_t {
  /**
   * Header spacer.
   */
  uint8_t __header[OFFSET_PAR_LENGTH_OUT_REP_PCKT];

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
  
} VerFailedPrgrRep0_t;

/**
 * Structure for packet VerSuccessTermRep - 0
 */
typedef struct __attribute__((packed, aligned(4))) _VerSuccessTermRep0_t {
  /**
   * Header spacer.
   */
  uint8_t __header[OFFSET_PAR_LENGTH_OUT_REP_PCKT];

  /**
   * Discriminant
   */
  uint16_t Discriminant;
  
  /**
   * Copy of the PACKET ID fields of the command being reported on
   */
  uint16_t TcPacketId;
  
  /**
   * Copy of the PACKET SEQUENCE CONTROL fields of the received command
   */
  uint16_t TcPacketSeqCtrl;
  
} VerSuccessTermRep0_t;

/**
 * Structure for packet VerFailedTermRep
 */
typedef struct __attribute__((packed, aligned(4))) _VerFailedTermRep_t {
  /**
   * Header spacer.
   */
  uint8_t __header[OFFSET_PAR_LENGTH_OUT_REP_PCKT];

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
  
} VerFailedTermRep_t;

/**
 * Structure for packet VerFailedRoutingRep - 0
 */
typedef struct __attribute__((packed, aligned(4))) _VerFailedRoutingRep0_t {
  /**
   * Header spacer.
   */
  uint8_t __header[OFFSET_PAR_LENGTH_OUT_REP_PCKT];

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
   * invalid Destination for Rerouting Failure
   */
  uint16_t invDest;
  
} VerFailedRoutingRep0_t;

/**
 * Get "Discriminant" from "VerSuccessAccRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "Discriminant".
 */
static inline uint16_t getVerSuccessAccRep0Discriminant(void* p)
{
  VerSuccessAccRep0_t* t;
  t = (VerSuccessAccRep0_t*)p;
  return t->Discriminant;
}

/**
 * Set "Discriminant" in "VerSuccessAccRep - 0" packet.
 * \param p Pointer to the packet.
 * \param Discriminant Value of "Discriminant" to be set in packet.
 */
static inline void setVerSuccessAccRep0Discriminant(void* p, uint16_t Discriminant)
{
  VerSuccessAccRep0_t* t;
  t = (VerSuccessAccRep0_t*)p;
  t->Discriminant = Discriminant;
}

/**
 * Get "TcPacketId" from "VerSuccessAccRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline uint16_t getVerSuccessAccRep0TcPacketId(void* p)
{
  VerSuccessAccRep0_t* t;
  t = (VerSuccessAccRep0_t*)p;
  return t->TcPacketId;
}

/**
 * Set "TcPacketId" in "VerSuccessAccRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcPacketId Value of "TcPacketId" to be set in packet.
 */
static inline void setVerSuccessAccRep0TcPacketId(void* p, uint16_t TcPacketId)
{
  VerSuccessAccRep0_t* t;
  t = (VerSuccessAccRep0_t*)p;
  t->TcPacketId = TcPacketId;
}

/**
 * Get "TcPacketSeqCtrl" from "VerSuccessAccRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketSeqCtrl".
 */
static inline uint16_t getVerSuccessAccRep0TcPacketSeqCtrl(void* p)
{
  VerSuccessAccRep0_t* t;
  t = (VerSuccessAccRep0_t*)p;
  return t->TcPacketSeqCtrl;
}

/**
 * Set "TcPacketSeqCtrl" in "VerSuccessAccRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcPacketSeqCtrl Value of "TcPacketSeqCtrl" to be set in packet.
 */
static inline void setVerSuccessAccRep0TcPacketSeqCtrl(void* p, uint16_t TcPacketSeqCtrl)
{
  VerSuccessAccRep0_t* t;
  t = (VerSuccessAccRep0_t*)p;
  t->TcPacketSeqCtrl = TcPacketSeqCtrl;
}

/**
 * Get "TcFailureCode" from "VerFailedAccRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcFailureCode".
 */
static inline uint16_t getVerFailedAccRep0TcFailureCode(void* p)
{
  VerFailedAccRep0_t* t;
  t = (VerFailedAccRep0_t*)p;
  return t->TcFailureCode;
}

/**
 * Set "TcFailureCode" in "VerFailedAccRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcFailureCode Value of "TcFailureCode" to be set in packet.
 */
static inline void setVerFailedAccRep0TcFailureCode(void* p, uint16_t TcFailureCode)
{
  VerFailedAccRep0_t* t;
  t = (VerFailedAccRep0_t*)p;
  t->TcFailureCode = TcFailureCode;
}

/**
 * Get "TcPacketId" from "VerFailedAccRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline uint16_t getVerFailedAccRep0TcPacketId(void* p)
{
  VerFailedAccRep0_t* t;
  t = (VerFailedAccRep0_t*)p;
  return t->TcPacketId;
}

/**
 * Set "TcPacketId" in "VerFailedAccRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcPacketId Value of "TcPacketId" to be set in packet.
 */
static inline void setVerFailedAccRep0TcPacketId(void* p, uint16_t TcPacketId)
{
  VerFailedAccRep0_t* t;
  t = (VerFailedAccRep0_t*)p;
  t->TcPacketId = TcPacketId;
}

/**
 * Get "TcPacketSeqCtrl" from "VerFailedAccRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketSeqCtrl".
 */
static inline uint16_t getVerFailedAccRep0TcPacketSeqCtrl(void* p)
{
  VerFailedAccRep0_t* t;
  t = (VerFailedAccRep0_t*)p;
  return t->TcPacketSeqCtrl;
}

/**
 * Set "TcPacketSeqCtrl" in "VerFailedAccRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcPacketSeqCtrl Value of "TcPacketSeqCtrl" to be set in packet.
 */
static inline void setVerFailedAccRep0TcPacketSeqCtrl(void* p, uint16_t TcPacketSeqCtrl)
{
  VerFailedAccRep0_t* t;
  t = (VerFailedAccRep0_t*)p;
  t->TcPacketSeqCtrl = TcPacketSeqCtrl;
}

/**
 * Get "TcType" from "VerFailedAccRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcType".
 */
static inline uint8_t getVerFailedAccRep0TcType(void* p)
{
  VerFailedAccRep0_t* t;
  t = (VerFailedAccRep0_t*)p;
  return t->TcType;
}

/**
 * Set "TcType" in "VerFailedAccRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcType Value of "TcType" to be set in packet.
 */
static inline void setVerFailedAccRep0TcType(void* p, uint8_t TcType)
{
  VerFailedAccRep0_t* t;
  t = (VerFailedAccRep0_t*)p;
  t->TcType = TcType;
}

/**
 * Get "TcSubtype" from "VerFailedAccRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcSubtype".
 */
static inline uint8_t getVerFailedAccRep0TcSubtype(void* p)
{
  VerFailedAccRep0_t* t;
  t = (VerFailedAccRep0_t*)p;
  return t->TcSubtype;
}

/**
 * Set "TcSubtype" in "VerFailedAccRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcSubtype Value of "TcSubtype" to be set in packet.
 */
static inline void setVerFailedAccRep0TcSubtype(void* p, uint8_t TcSubtype)
{
  VerFailedAccRep0_t* t;
  t = (VerFailedAccRep0_t*)p;
  t->TcSubtype = TcSubtype;
}

/**
 * Get "Discriminant" from "VerSuccessStartRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "Discriminant".
 */
static inline uint16_t getVerSuccessStartRep0Discriminant(void* p)
{
  VerSuccessStartRep0_t* t;
  t = (VerSuccessStartRep0_t*)p;
  return t->Discriminant;
}

/**
 * Set "Discriminant" in "VerSuccessStartRep - 0" packet.
 * \param p Pointer to the packet.
 * \param Discriminant Value of "Discriminant" to be set in packet.
 */
static inline void setVerSuccessStartRep0Discriminant(void* p, uint16_t Discriminant)
{
  VerSuccessStartRep0_t* t;
  t = (VerSuccessStartRep0_t*)p;
  t->Discriminant = Discriminant;
}

/**
 * Get "TcPacketId" from "VerSuccessStartRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline uint16_t getVerSuccessStartRep0TcPacketId(void* p)
{
  VerSuccessStartRep0_t* t;
  t = (VerSuccessStartRep0_t*)p;
  return t->TcPacketId;
}

/**
 * Set "TcPacketId" in "VerSuccessStartRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcPacketId Value of "TcPacketId" to be set in packet.
 */
static inline void setVerSuccessStartRep0TcPacketId(void* p, uint16_t TcPacketId)
{
  VerSuccessStartRep0_t* t;
  t = (VerSuccessStartRep0_t*)p;
  t->TcPacketId = TcPacketId;
}

/**
 * Get "TcPacketSeqCtrl" from "VerSuccessStartRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketSeqCtrl".
 */
static inline uint16_t getVerSuccessStartRep0TcPacketSeqCtrl(void* p)
{
  VerSuccessStartRep0_t* t;
  t = (VerSuccessStartRep0_t*)p;
  return t->TcPacketSeqCtrl;
}

/**
 * Set "TcPacketSeqCtrl" in "VerSuccessStartRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcPacketSeqCtrl Value of "TcPacketSeqCtrl" to be set in packet.
 */
static inline void setVerSuccessStartRep0TcPacketSeqCtrl(void* p, uint16_t TcPacketSeqCtrl)
{
  VerSuccessStartRep0_t* t;
  t = (VerSuccessStartRep0_t*)p;
  t->TcPacketSeqCtrl = TcPacketSeqCtrl;
}

/**
 * Get "TcFailureCode" from "VerFailedStartRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcFailureCode".
 */
static inline uint16_t getVerFailedStartRep0TcFailureCode(void* p)
{
  VerFailedStartRep0_t* t;
  t = (VerFailedStartRep0_t*)p;
  return t->TcFailureCode;
}

/**
 * Set "TcFailureCode" in "VerFailedStartRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcFailureCode Value of "TcFailureCode" to be set in packet.
 */
static inline void setVerFailedStartRep0TcFailureCode(void* p, uint16_t TcFailureCode)
{
  VerFailedStartRep0_t* t;
  t = (VerFailedStartRep0_t*)p;
  t->TcFailureCode = TcFailureCode;
}

/**
 * Get "TcPacketId" from "VerFailedStartRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline uint16_t getVerFailedStartRep0TcPacketId(void* p)
{
  VerFailedStartRep0_t* t;
  t = (VerFailedStartRep0_t*)p;
  return t->TcPacketId;
}

/**
 * Set "TcPacketId" in "VerFailedStartRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcPacketId Value of "TcPacketId" to be set in packet.
 */
static inline void setVerFailedStartRep0TcPacketId(void* p, uint16_t TcPacketId)
{
  VerFailedStartRep0_t* t;
  t = (VerFailedStartRep0_t*)p;
  t->TcPacketId = TcPacketId;
}

/**
 * Get "TcPacketSeqCtrl" from "VerFailedStartRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketSeqCtrl".
 */
static inline uint16_t getVerFailedStartRep0TcPacketSeqCtrl(void* p)
{
  VerFailedStartRep0_t* t;
  t = (VerFailedStartRep0_t*)p;
  return t->TcPacketSeqCtrl;
}

/**
 * Set "TcPacketSeqCtrl" in "VerFailedStartRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcPacketSeqCtrl Value of "TcPacketSeqCtrl" to be set in packet.
 */
static inline void setVerFailedStartRep0TcPacketSeqCtrl(void* p, uint16_t TcPacketSeqCtrl)
{
  VerFailedStartRep0_t* t;
  t = (VerFailedStartRep0_t*)p;
  t->TcPacketSeqCtrl = TcPacketSeqCtrl;
}

/**
 * Get "TcType" from "VerFailedStartRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcType".
 */
static inline uint8_t getVerFailedStartRep0TcType(void* p)
{
  VerFailedStartRep0_t* t;
  t = (VerFailedStartRep0_t*)p;
  return t->TcType;
}

/**
 * Set "TcType" in "VerFailedStartRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcType Value of "TcType" to be set in packet.
 */
static inline void setVerFailedStartRep0TcType(void* p, uint8_t TcType)
{
  VerFailedStartRep0_t* t;
  t = (VerFailedStartRep0_t*)p;
  t->TcType = TcType;
}

/**
 * Get "TcSubtype" from "VerFailedStartRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcSubtype".
 */
static inline uint8_t getVerFailedStartRep0TcSubtype(void* p)
{
  VerFailedStartRep0_t* t;
  t = (VerFailedStartRep0_t*)p;
  return t->TcSubtype;
}

/**
 * Set "TcSubtype" in "VerFailedStartRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcSubtype Value of "TcSubtype" to be set in packet.
 */
static inline void setVerFailedStartRep0TcSubtype(void* p, uint8_t TcSubtype)
{
  VerFailedStartRep0_t* t;
  t = (VerFailedStartRep0_t*)p;
  t->TcSubtype = TcSubtype;
}

/**
 * Get "Discriminant" from "VerSuccessPrgrRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "Discriminant".
 */
static inline uint16_t getVerSuccessPrgrRep0Discriminant(void* p)
{
  VerSuccessPrgrRep0_t* t;
  t = (VerSuccessPrgrRep0_t*)p;
  return t->Discriminant;
}

/**
 * Set "Discriminant" in "VerSuccessPrgrRep - 0" packet.
 * \param p Pointer to the packet.
 * \param Discriminant Value of "Discriminant" to be set in packet.
 */
static inline void setVerSuccessPrgrRep0Discriminant(void* p, uint16_t Discriminant)
{
  VerSuccessPrgrRep0_t* t;
  t = (VerSuccessPrgrRep0_t*)p;
  t->Discriminant = Discriminant;
}

/**
 * Get "TcPacketId" from "VerSuccessPrgrRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline uint16_t getVerSuccessPrgrRep0TcPacketId(void* p)
{
  VerSuccessPrgrRep0_t* t;
  t = (VerSuccessPrgrRep0_t*)p;
  return t->TcPacketId;
}

/**
 * Set "TcPacketId" in "VerSuccessPrgrRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcPacketId Value of "TcPacketId" to be set in packet.
 */
static inline void setVerSuccessPrgrRep0TcPacketId(void* p, uint16_t TcPacketId)
{
  VerSuccessPrgrRep0_t* t;
  t = (VerSuccessPrgrRep0_t*)p;
  t->TcPacketId = TcPacketId;
}

/**
 * Get "TcPacketSeqCtrl" from "VerSuccessPrgrRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketSeqCtrl".
 */
static inline uint16_t getVerSuccessPrgrRep0TcPacketSeqCtrl(void* p)
{
  VerSuccessPrgrRep0_t* t;
  t = (VerSuccessPrgrRep0_t*)p;
  return t->TcPacketSeqCtrl;
}

/**
 * Set "TcPacketSeqCtrl" in "VerSuccessPrgrRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcPacketSeqCtrl Value of "TcPacketSeqCtrl" to be set in packet.
 */
static inline void setVerSuccessPrgrRep0TcPacketSeqCtrl(void* p, uint16_t TcPacketSeqCtrl)
{
  VerSuccessPrgrRep0_t* t;
  t = (VerSuccessPrgrRep0_t*)p;
  t->TcPacketSeqCtrl = TcPacketSeqCtrl;
}

/**
 * Get "StepId" from "VerSuccessPrgrRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "StepId".
 */
static inline uint32_t getVerSuccessPrgrRep0StepId(void* p)
{
  VerSuccessPrgrRep0_t* t;
  t = (VerSuccessPrgrRep0_t*)p;
  return t->StepId;
}

/**
 * Set "StepId" in "VerSuccessPrgrRep - 0" packet.
 * \param p Pointer to the packet.
 * \param StepId Value of "StepId" to be set in packet.
 */
static inline void setVerSuccessPrgrRep0StepId(void* p, uint32_t StepId)
{
  VerSuccessPrgrRep0_t* t;
  t = (VerSuccessPrgrRep0_t*)p;
  t->StepId = StepId;
}

/**
 * Get "TcFailureCode" from "VerFailedPrgrRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcFailureCode".
 */
static inline uint16_t getVerFailedPrgrRep0TcFailureCode(void* p)
{
  VerFailedPrgrRep0_t* t;
  t = (VerFailedPrgrRep0_t*)p;
  return t->TcFailureCode;
}

/**
 * Set "TcFailureCode" in "VerFailedPrgrRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcFailureCode Value of "TcFailureCode" to be set in packet.
 */
static inline void setVerFailedPrgrRep0TcFailureCode(void* p, uint16_t TcFailureCode)
{
  VerFailedPrgrRep0_t* t;
  t = (VerFailedPrgrRep0_t*)p;
  t->TcFailureCode = TcFailureCode;
}

/**
 * Get "TcPacketId" from "VerFailedPrgrRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline uint16_t getVerFailedPrgrRep0TcPacketId(void* p)
{
  VerFailedPrgrRep0_t* t;
  t = (VerFailedPrgrRep0_t*)p;
  return t->TcPacketId;
}

/**
 * Set "TcPacketId" in "VerFailedPrgrRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcPacketId Value of "TcPacketId" to be set in packet.
 */
static inline void setVerFailedPrgrRep0TcPacketId(void* p, uint16_t TcPacketId)
{
  VerFailedPrgrRep0_t* t;
  t = (VerFailedPrgrRep0_t*)p;
  t->TcPacketId = TcPacketId;
}

/**
 * Get "TcPacketSeqCtrl" from "VerFailedPrgrRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketSeqCtrl".
 */
static inline uint16_t getVerFailedPrgrRep0TcPacketSeqCtrl(void* p)
{
  VerFailedPrgrRep0_t* t;
  t = (VerFailedPrgrRep0_t*)p;
  return t->TcPacketSeqCtrl;
}

/**
 * Set "TcPacketSeqCtrl" in "VerFailedPrgrRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcPacketSeqCtrl Value of "TcPacketSeqCtrl" to be set in packet.
 */
static inline void setVerFailedPrgrRep0TcPacketSeqCtrl(void* p, uint16_t TcPacketSeqCtrl)
{
  VerFailedPrgrRep0_t* t;
  t = (VerFailedPrgrRep0_t*)p;
  t->TcPacketSeqCtrl = TcPacketSeqCtrl;
}

/**
 * Get "TcType" from "VerFailedPrgrRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcType".
 */
static inline uint8_t getVerFailedPrgrRep0TcType(void* p)
{
  VerFailedPrgrRep0_t* t;
  t = (VerFailedPrgrRep0_t*)p;
  return t->TcType;
}

/**
 * Set "TcType" in "VerFailedPrgrRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcType Value of "TcType" to be set in packet.
 */
static inline void setVerFailedPrgrRep0TcType(void* p, uint8_t TcType)
{
  VerFailedPrgrRep0_t* t;
  t = (VerFailedPrgrRep0_t*)p;
  t->TcType = TcType;
}

/**
 * Get "TcSubtype" from "VerFailedPrgrRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcSubtype".
 */
static inline uint8_t getVerFailedPrgrRep0TcSubtype(void* p)
{
  VerFailedPrgrRep0_t* t;
  t = (VerFailedPrgrRep0_t*)p;
  return t->TcSubtype;
}

/**
 * Set "TcSubtype" in "VerFailedPrgrRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcSubtype Value of "TcSubtype" to be set in packet.
 */
static inline void setVerFailedPrgrRep0TcSubtype(void* p, uint8_t TcSubtype)
{
  VerFailedPrgrRep0_t* t;
  t = (VerFailedPrgrRep0_t*)p;
  t->TcSubtype = TcSubtype;
}

/**
 * Get "Discriminant" from "VerSuccessTermRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "Discriminant".
 */
static inline uint16_t getVerSuccessTermRep0Discriminant(void* p)
{
  VerSuccessTermRep0_t* t;
  t = (VerSuccessTermRep0_t*)p;
  return t->Discriminant;
}

/**
 * Set "Discriminant" in "VerSuccessTermRep - 0" packet.
 * \param p Pointer to the packet.
 * \param Discriminant Value of "Discriminant" to be set in packet.
 */
static inline void setVerSuccessTermRep0Discriminant(void* p, uint16_t Discriminant)
{
  VerSuccessTermRep0_t* t;
  t = (VerSuccessTermRep0_t*)p;
  t->Discriminant = Discriminant;
}

/**
 * Get "TcPacketId" from "VerSuccessTermRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline uint16_t getVerSuccessTermRep0TcPacketId(void* p)
{
  VerSuccessTermRep0_t* t;
  t = (VerSuccessTermRep0_t*)p;
  return t->TcPacketId;
}

/**
 * Set "TcPacketId" in "VerSuccessTermRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcPacketId Value of "TcPacketId" to be set in packet.
 */
static inline void setVerSuccessTermRep0TcPacketId(void* p, uint16_t TcPacketId)
{
  VerSuccessTermRep0_t* t;
  t = (VerSuccessTermRep0_t*)p;
  t->TcPacketId = TcPacketId;
}

/**
 * Get "TcPacketSeqCtrl" from "VerSuccessTermRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketSeqCtrl".
 */
static inline uint16_t getVerSuccessTermRep0TcPacketSeqCtrl(void* p)
{
  VerSuccessTermRep0_t* t;
  t = (VerSuccessTermRep0_t*)p;
  return t->TcPacketSeqCtrl;
}

/**
 * Set "TcPacketSeqCtrl" in "VerSuccessTermRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcPacketSeqCtrl Value of "TcPacketSeqCtrl" to be set in packet.
 */
static inline void setVerSuccessTermRep0TcPacketSeqCtrl(void* p, uint16_t TcPacketSeqCtrl)
{
  VerSuccessTermRep0_t* t;
  t = (VerSuccessTermRep0_t*)p;
  t->TcPacketSeqCtrl = TcPacketSeqCtrl;
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
  return t->TcFailureCode;
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
  t->TcFailureCode = TcFailureCode;
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
  return t->TcPacketId;
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
  t->TcPacketId = TcPacketId;
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
  return t->TcPacketSeqCtrl;
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
  t->TcPacketSeqCtrl = TcPacketSeqCtrl;
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
 * Get "TcFailureCode" from "VerFailedRoutingRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcFailureCode".
 */
static inline uint16_t getVerFailedRoutingRep0TcFailureCode(void* p)
{
  VerFailedRoutingRep0_t* t;
  t = (VerFailedRoutingRep0_t*)p;
  return t->TcFailureCode;
}

/**
 * Set "TcFailureCode" in "VerFailedRoutingRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcFailureCode Value of "TcFailureCode" to be set in packet.
 */
static inline void setVerFailedRoutingRep0TcFailureCode(void* p, uint16_t TcFailureCode)
{
  VerFailedRoutingRep0_t* t;
  t = (VerFailedRoutingRep0_t*)p;
  t->TcFailureCode = TcFailureCode;
}

/**
 * Get "TcPacketId" from "VerFailedRoutingRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketId".
 */
static inline uint16_t getVerFailedRoutingRep0TcPacketId(void* p)
{
  VerFailedRoutingRep0_t* t;
  t = (VerFailedRoutingRep0_t*)p;
  return t->TcPacketId;
}

/**
 * Set "TcPacketId" in "VerFailedRoutingRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcPacketId Value of "TcPacketId" to be set in packet.
 */
static inline void setVerFailedRoutingRep0TcPacketId(void* p, uint16_t TcPacketId)
{
  VerFailedRoutingRep0_t* t;
  t = (VerFailedRoutingRep0_t*)p;
  t->TcPacketId = TcPacketId;
}

/**
 * Get "TcPacketSeqCtrl" from "VerFailedRoutingRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcPacketSeqCtrl".
 */
static inline uint16_t getVerFailedRoutingRep0TcPacketSeqCtrl(void* p)
{
  VerFailedRoutingRep0_t* t;
  t = (VerFailedRoutingRep0_t*)p;
  return t->TcPacketSeqCtrl;
}

/**
 * Set "TcPacketSeqCtrl" in "VerFailedRoutingRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcPacketSeqCtrl Value of "TcPacketSeqCtrl" to be set in packet.
 */
static inline void setVerFailedRoutingRep0TcPacketSeqCtrl(void* p, uint16_t TcPacketSeqCtrl)
{
  VerFailedRoutingRep0_t* t;
  t = (VerFailedRoutingRep0_t*)p;
  t->TcPacketSeqCtrl = TcPacketSeqCtrl;
}

/**
 * Get "TcType" from "VerFailedRoutingRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcType".
 */
static inline uint8_t getVerFailedRoutingRep0TcType(void* p)
{
  VerFailedRoutingRep0_t* t;
  t = (VerFailedRoutingRep0_t*)p;
  return t->TcType;
}

/**
 * Set "TcType" in "VerFailedRoutingRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcType Value of "TcType" to be set in packet.
 */
static inline void setVerFailedRoutingRep0TcType(void* p, uint8_t TcType)
{
  VerFailedRoutingRep0_t* t;
  t = (VerFailedRoutingRep0_t*)p;
  t->TcType = TcType;
}

/**
 * Get "TcSubtype" from "VerFailedRoutingRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "TcSubtype".
 */
static inline uint8_t getVerFailedRoutingRep0TcSubtype(void* p)
{
  VerFailedRoutingRep0_t* t;
  t = (VerFailedRoutingRep0_t*)p;
  return t->TcSubtype;
}

/**
 * Set "TcSubtype" in "VerFailedRoutingRep - 0" packet.
 * \param p Pointer to the packet.
 * \param TcSubtype Value of "TcSubtype" to be set in packet.
 */
static inline void setVerFailedRoutingRep0TcSubtype(void* p, uint8_t TcSubtype)
{
  VerFailedRoutingRep0_t* t;
  t = (VerFailedRoutingRep0_t*)p;
  t->TcSubtype = TcSubtype;
}

/**
 * Get "invDest" from "VerFailedRoutingRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "invDest".
 */
static inline uint16_t getVerFailedRoutingRep0invDest(void* p)
{
  VerFailedRoutingRep0_t* t;
  t = (VerFailedRoutingRep0_t*)p;
  return t->invDest;
}

/**
 * Set "invDest" in "VerFailedRoutingRep - 0" packet.
 * \param p Pointer to the packet.
 * \param invDest Value of "invDest" to be set in packet.
 */
static inline void setVerFailedRoutingRep0invDest(void* p, uint16_t invDest)
{
  VerFailedRoutingRep0_t* t;
  t = (VerFailedRoutingRep0_t*)p;
  t->invDest = invDest;
}

#endif /* CRPSDPPKTSERVREQVERIF_H */
