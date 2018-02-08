/**
 * @file CrPsPktServReqVerif.h
 * @ingroup Serv1
 * @ingroup pktgetset
 *
 * @brief Interface for accessing fields in packets of service "ServReqVerif".
 *
 * @note This file was generated on 2017-10-17 15:38:24
 * @author PnP Generator
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * 
 * last modification: 22.01.2018
 * 
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#ifndef CRPSPKTSERVREQVERIF_H_
#define CRPSPKTSERVREQVERIF_H_

#include "CrFwUserConstants.h"
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
   * Spacer block.
   */
  uint8_t block_5[2];

  /**
   * Spacer block.
   */
  uint8_t block_18[2];

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
   * Spacer block.
   */
  uint8_t block_5[2];

  /**
   * Spacer block.
   */
  uint8_t block_18[2];

  /**
   * The failure idetification code.
   */
  CrPsFailCode_t FailureCode;
  
  /**
   * The failure Data
   */
  CrPsFailData_t FailureData;
  
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
   * Spacer block.
   */
  uint8_t block_5[2];

  /**
   * Spacer block.
   */
  uint8_t block_18[2];

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
   * Spacer block.
   */
  uint8_t block_5[2];

  /**
   * Spacer block.
   */
  uint8_t block_18[2];

  /**
   * The failure idetification code.
   */
  CrPsFailCode_t FailureCode;
  
  /**
   * The failure Data
   */
  CrPsFailData_t FailureData;
  
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
   * Spacer block.
   */
  uint8_t block_5[2];

  /**
   * Spacer block.
   */
  uint8_t block_18[2];

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
   * Spacer block.
   */
  uint8_t block_5[2];

  /**
   * Spacer block.
   */
  uint8_t block_18[2];

  /**
   * Step ID
   */
  CrPsStepId_t StepId;
  
  /**
   * The failure idetification code.
   */
  CrPsFailCode_t FailureCode;
  
  /**
   * The failure Data
   */
  CrPsFailData_t FailureData;
  
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
   * Spacer block.
   */
  uint8_t block_5[2];

  /**
   * Spacer block.
   */
  uint8_t block_18[2];

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
   * Spacer block.
   */
  uint8_t block_5[2];

  /**
   * Spacer block.
   */
  uint8_t block_18[2];

  /**
   * The failure idetification code.
   */
  CrPsFailCode_t FailureCode;
  
  /**
   * The failure Data
   */
  CrPsFailData_t FailureData;
  
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
   * Spacer block.
   */
  uint8_t block_5[2];

  /**
   * Spacer block.
   */
  uint8_t block_18[2];

  /**
   * The failure idetification code.
   */
  CrPsFailCode_t FailureCode;
  
  /**
   * The failure Data
   */
  CrPsFailData_t FailureData;
  
} VerFailedRoutingRep_t ;

/**
 * Get "PcktVersionNmb" from "VerSuccessAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktVersionNmb".
 */
static inline Three_Bit_t getVerSuccessAccRepPcktVersionNmb(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 13;
  t &= 0x7;
  return (Three_Bit_t)t;
}

/**
 * Set "PcktVersionNmb" in "VerSuccessAccRep" packet.
 * \param p Pointer to the packet.
 * \param PcktVersionNmb Value of "PcktVersionNmb" to be set in packet.
 */
static inline void setVerSuccessAccRepPcktVersionNmb(void* p, Three_Bit_t PcktVersionNmb)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktVersionNmb << 13);
  s &= (uint16_t)0xe000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xe000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "PcktType" from "VerSuccessAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktType".
 */
static inline One_Bit_t getVerSuccessAccRepPcktType(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 12;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "PcktType" in "VerSuccessAccRep" packet.
 * \param p Pointer to the packet.
 * \param PcktType Value of "PcktType" to be set in packet.
 */
static inline void setVerSuccessAccRepPcktType(void* p, One_Bit_t PcktType)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktType << 12);
  s &= (uint16_t)0x1000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x1000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "SecHeaderFlag" from "VerSuccessAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SecHeaderFlag".
 */
static inline One_Bit_t getVerSuccessAccRepSecHeaderFlag(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 11;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "SecHeaderFlag" in "VerSuccessAccRep" packet.
 * \param p Pointer to the packet.
 * \param SecHeaderFlag Value of "SecHeaderFlag" to be set in packet.
 */
static inline void setVerSuccessAccRepSecHeaderFlag(void* p, One_Bit_t SecHeaderFlag)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SecHeaderFlag << 11);
  s &= (uint16_t)0x800ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x800ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "APID" from "VerSuccessAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "APID".
 */
static inline Eleven_Bit_t getVerSuccessAccRepAPID(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x7ff;
  return (Eleven_Bit_t)t;
}

/**
 * Set "APID" in "VerSuccessAccRep" packet.
 * \param p Pointer to the packet.
 * \param APID Value of "APID" to be set in packet.
 */
static inline void setVerSuccessAccRepAPID(void* p, Eleven_Bit_t APID)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)APID << 16);
  s &= (uint32_t)0x7ff0000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x7ff0000ull;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "SeqFlags" from "VerSuccessAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqFlags".
 */
static inline Two_Bit_t getVerSuccessAccRepSeqFlags(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 14;
  t &= 0x3;
  return (Two_Bit_t)t;
}

/**
 * Set "SeqFlags" in "VerSuccessAccRep" packet.
 * \param p Pointer to the packet.
 * \param SeqFlags Value of "SeqFlags" to be set in packet.
 */
static inline void setVerSuccessAccRepSeqFlags(void* p, Two_Bit_t SeqFlags)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SeqFlags << 14);
  s &= (uint16_t)0xc000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xc000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)+2], &t, sizeof(t));
}

/**
 * Get "SeqCount" from "VerSuccessAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqCount".
 */
static inline FourTeen_Bit_t getVerSuccessAccRepSeqCount(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x3fff;
  return (FourTeen_Bit_t)t;
}

/**
 * Set "SeqCount" in "VerSuccessAccRep" packet.
 * \param p Pointer to the packet.
 * \param SeqCount Value of "SeqCount" to be set in packet.
 */
static inline void setVerSuccessAccRepSeqCount(void* p, FourTeen_Bit_t SeqCount)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)SeqCount << 16);
  s &= (uint32_t)0x3fff0000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x3fff0000ull;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)+2], &t, sizeof(t));
}

/**
 * Get "PcktVersionNmb" from "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktVersionNmb".
 */
static inline Three_Bit_t getVerFailedAccRepPcktVersionNmb(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 13;
  t &= 0x7;
  return (Three_Bit_t)t;
}

/**
 * Set "PcktVersionNmb" in "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \param PcktVersionNmb Value of "PcktVersionNmb" to be set in packet.
 */
static inline void setVerFailedAccRepPcktVersionNmb(void* p, Three_Bit_t PcktVersionNmb)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktVersionNmb << 13);
  s &= (uint16_t)0xe000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xe000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "PcktType" from "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktType".
 */
static inline One_Bit_t getVerFailedAccRepPcktType(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 12;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "PcktType" in "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \param PcktType Value of "PcktType" to be set in packet.
 */
static inline void setVerFailedAccRepPcktType(void* p, One_Bit_t PcktType)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktType << 12);
  s &= (uint16_t)0x1000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x1000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "SecHeaderFlag" from "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SecHeaderFlag".
 */
static inline One_Bit_t getVerFailedAccRepSecHeaderFlag(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 11;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "SecHeaderFlag" in "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \param SecHeaderFlag Value of "SecHeaderFlag" to be set in packet.
 */
static inline void setVerFailedAccRepSecHeaderFlag(void* p, One_Bit_t SecHeaderFlag)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SecHeaderFlag << 11);
  s &= (uint16_t)0x800ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x800ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "APID" from "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "APID".
 */
static inline Eleven_Bit_t getVerFailedAccRepAPID(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x7ff;
  return (Eleven_Bit_t)t;
}

/**
 * Set "APID" in "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \param APID Value of "APID" to be set in packet.
 */
static inline void setVerFailedAccRepAPID(void* p, Eleven_Bit_t APID)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)APID << 16);
  s &= (uint32_t)0x7ff0000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x7ff0000ull;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "SeqFlags" from "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqFlags".
 */
static inline Two_Bit_t getVerFailedAccRepSeqFlags(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 14;
  t &= 0x3;
  return (Two_Bit_t)t;
}

/**
 * Set "SeqFlags" in "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \param SeqFlags Value of "SeqFlags" to be set in packet.
 */
static inline void setVerFailedAccRepSeqFlags(void* p, Two_Bit_t SeqFlags)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SeqFlags << 14);
  s &= (uint16_t)0xc000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xc000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)+2], &t, sizeof(t));
}

/**
 * Get "SeqCount" from "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqCount".
 */
static inline FourTeen_Bit_t getVerFailedAccRepSeqCount(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x3fff;
  return (FourTeen_Bit_t)t;
}

/**
 * Set "SeqCount" in "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \param SeqCount Value of "SeqCount" to be set in packet.
 */
static inline void setVerFailedAccRepSeqCount(void* p, FourTeen_Bit_t SeqCount)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)SeqCount << 16);
  s &= (uint32_t)0x3fff0000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x3fff0000ull;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)+2], &t, sizeof(t));
}

/**
 * Get "FailureCode" from "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "FailureCode".
 */
static inline CrPsFailCode_t getVerFailedAccRepFailureCode(void* p)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  return __builtin_bswap16(t->FailureCode);
}

/**
 * Set "FailureCode" in "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \param FailureCode Value of "FailureCode" to be set in packet.
 */
static inline void setVerFailedAccRepFailureCode(void* p, CrPsFailCode_t FailureCode)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  t->FailureCode = __builtin_bswap16(FailureCode);
}

/**
 * Get "FailureData" from "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "FailureData".
 */
static inline CrPsFailData_t getVerFailedAccRepFailureData(void* p)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  return __builtin_bswap32(t->FailureData);
}

/**
 * Set "FailureData" in "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \param FailureData Value of "FailureData" to be set in packet.
 */
static inline void setVerFailedAccRepFailureData(void* p, CrPsFailData_t FailureData)
{
  VerFailedAccRep_t* t;
  t = (VerFailedAccRep_t*)p;
  t->FailureData = __builtin_bswap32(FailureData);
}

/**
 * Get "PcktVersionNmb" from "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktVersionNmb".
 */
static inline Three_Bit_t getVerSuccessStartRepPcktVersionNmb(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 13;
  t &= 0x7;
  return (Three_Bit_t)t;
}

/**
 * Set "PcktVersionNmb" in "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \param PcktVersionNmb Value of "PcktVersionNmb" to be set in packet.
 */
static inline void setVerSuccessStartRepPcktVersionNmb(void* p, Three_Bit_t PcktVersionNmb)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktVersionNmb << 13);
  s &= (uint16_t)0xe000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xe000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "PcktType" from "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktType".
 */
static inline One_Bit_t getVerSuccessStartRepPcktType(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 12;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "PcktType" in "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \param PcktType Value of "PcktType" to be set in packet.
 */
static inline void setVerSuccessStartRepPcktType(void* p, One_Bit_t PcktType)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktType << 12);
  s &= (uint16_t)0x1000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x1000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "SecHeaderFlag" from "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SecHeaderFlag".
 */
static inline One_Bit_t getVerSuccessStartRepSecHeaderFlag(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 11;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "SecHeaderFlag" in "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \param SecHeaderFlag Value of "SecHeaderFlag" to be set in packet.
 */
static inline void setVerSuccessStartRepSecHeaderFlag(void* p, One_Bit_t SecHeaderFlag)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SecHeaderFlag << 11);
  s &= (uint16_t)0x800ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x800ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "APID" from "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "APID".
 */
static inline Eleven_Bit_t getVerSuccessStartRepAPID(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x7ff;
  return (Eleven_Bit_t)t;
}

/**
 * Set "APID" in "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \param APID Value of "APID" to be set in packet.
 */
static inline void setVerSuccessStartRepAPID(void* p, Eleven_Bit_t APID)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)APID << 16);
  s &= (uint32_t)0x7ff0000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x7ff0000ull;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "SeqFlags" from "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqFlags".
 */
static inline Two_Bit_t getVerSuccessStartRepSeqFlags(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 14;
  t &= 0x3;
  return (Two_Bit_t)t;
}

/**
 * Set "SeqFlags" in "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \param SeqFlags Value of "SeqFlags" to be set in packet.
 */
static inline void setVerSuccessStartRepSeqFlags(void* p, Two_Bit_t SeqFlags)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SeqFlags << 14);
  s &= (uint16_t)0xc000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xc000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)+2], &t, sizeof(t));
}

/**
 * Get "SeqCount" from "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqCount".
 */
static inline FourTeen_Bit_t getVerSuccessStartRepSeqCount(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x3fff;
  return (FourTeen_Bit_t)t;
}

/**
 * Set "SeqCount" in "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \param SeqCount Value of "SeqCount" to be set in packet.
 */
static inline void setVerSuccessStartRepSeqCount(void* p, FourTeen_Bit_t SeqCount)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)SeqCount << 16);
  s &= (uint32_t)0x3fff0000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x3fff0000ull;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)+2], &t, sizeof(t));
}

/**
 * Get "PcktVersionNmb" from "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktVersionNmb".
 */
static inline Three_Bit_t getVerFailedStartRepPcktVersionNmb(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 13;
  t &= 0x7;
  return (Three_Bit_t)t;
}

/**
 * Set "PcktVersionNmb" in "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \param PcktVersionNmb Value of "PcktVersionNmb" to be set in packet.
 */
static inline void setVerFailedStartRepPcktVersionNmb(void* p, Three_Bit_t PcktVersionNmb)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktVersionNmb << 13);
  s &= (uint16_t)0xe000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xe000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "PcktType" from "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktType".
 */
static inline One_Bit_t getVerFailedStartRepPcktType(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 12;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "PcktType" in "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \param PcktType Value of "PcktType" to be set in packet.
 */
static inline void setVerFailedStartRepPcktType(void* p, One_Bit_t PcktType)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktType << 12);
  s &= (uint16_t)0x1000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x1000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "SecHeaderFlag" from "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SecHeaderFlag".
 */
static inline One_Bit_t getVerFailedStartRepSecHeaderFlag(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 11;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "SecHeaderFlag" in "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \param SecHeaderFlag Value of "SecHeaderFlag" to be set in packet.
 */
static inline void setVerFailedStartRepSecHeaderFlag(void* p, One_Bit_t SecHeaderFlag)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SecHeaderFlag << 11);
  s &= (uint16_t)0x800ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x800ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "APID" from "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "APID".
 */
static inline Eleven_Bit_t getVerFailedStartRepAPID(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x7ff;
  return (Eleven_Bit_t)t;
}

/**
 * Set "APID" in "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \param APID Value of "APID" to be set in packet.
 */
static inline void setVerFailedStartRepAPID(void* p, Eleven_Bit_t APID)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)APID << 16);
  s &= (uint32_t)0x7ff0000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x7ff0000ull;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "SeqFlags" from "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqFlags".
 */
static inline Two_Bit_t getVerFailedStartRepSeqFlags(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 14;
  t &= 0x3;
  return (Two_Bit_t)t;
}

/**
 * Set "SeqFlags" in "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \param SeqFlags Value of "SeqFlags" to be set in packet.
 */
static inline void setVerFailedStartRepSeqFlags(void* p, Two_Bit_t SeqFlags)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SeqFlags << 14);
  s &= (uint16_t)0xc000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xc000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)+2], &t, sizeof(t));
}

/**
 * Get "SeqCount" from "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqCount".
 */
static inline FourTeen_Bit_t getVerFailedStartRepSeqCount(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x3fff;
  return (FourTeen_Bit_t)t;
}

/**
 * Set "SeqCount" in "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \param SeqCount Value of "SeqCount" to be set in packet.
 */
static inline void setVerFailedStartRepSeqCount(void* p, FourTeen_Bit_t SeqCount)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)SeqCount << 16);
  s &= (uint32_t)0x3fff0000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x3fff0000ull;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)+2], &t, sizeof(t));
}

/**
 * Get "FailureCode" from "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "FailureCode".
 */
static inline CrPsFailCode_t getVerFailedStartRepFailureCode(void* p)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  return __builtin_bswap16(t->FailureCode);
}

/**
 * Set "FailureCode" in "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \param FailureCode Value of "FailureCode" to be set in packet.
 */
static inline void setVerFailedStartRepFailureCode(void* p, CrPsFailCode_t FailureCode)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  t->FailureCode = __builtin_bswap16(FailureCode);
}

/**
 * Get "FailureData" from "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "FailureData".
 */
static inline CrPsFailData_t getVerFailedStartRepFailureData(void* p)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  return __builtin_bswap32(t->FailureData);
}

/**
 * Set "FailureData" in "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \param FailureData Value of "FailureData" to be set in packet.
 */
static inline void setVerFailedStartRepFailureData(void* p, CrPsFailData_t FailureData)
{
  VerFailedStartRep_t* t;
  t = (VerFailedStartRep_t*)p;
  t->FailureData = __builtin_bswap32(FailureData);
}

/**
 * Get "PcktVersionNmb" from "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktVersionNmb".
 */
static inline Three_Bit_t getVerSuccessPrgrRepPcktVersionNmb(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 13;
  t &= 0x7;
  return (Three_Bit_t)t;
}

/**
 * Set "PcktVersionNmb" in "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param PcktVersionNmb Value of "PcktVersionNmb" to be set in packet.
 */
static inline void setVerSuccessPrgrRepPcktVersionNmb(void* p, Three_Bit_t PcktVersionNmb)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktVersionNmb << 13);
  s &= (uint16_t)0xe000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xe000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "PcktType" from "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktType".
 */
static inline One_Bit_t getVerSuccessPrgrRepPcktType(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 12;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "PcktType" in "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param PcktType Value of "PcktType" to be set in packet.
 */
static inline void setVerSuccessPrgrRepPcktType(void* p, One_Bit_t PcktType)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktType << 12);
  s &= (uint16_t)0x1000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x1000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "SecHeaderFlag" from "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SecHeaderFlag".
 */
static inline One_Bit_t getVerSuccessPrgrRepSecHeaderFlag(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 11;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "SecHeaderFlag" in "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param SecHeaderFlag Value of "SecHeaderFlag" to be set in packet.
 */
static inline void setVerSuccessPrgrRepSecHeaderFlag(void* p, One_Bit_t SecHeaderFlag)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SecHeaderFlag << 11);
  s &= (uint16_t)0x800ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x800ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "APID" from "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "APID".
 */
static inline Eleven_Bit_t getVerSuccessPrgrRepAPID(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x7ff;
  return (Eleven_Bit_t)t;
}

/**
 * Set "APID" in "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param APID Value of "APID" to be set in packet.
 */
static inline void setVerSuccessPrgrRepAPID(void* p, Eleven_Bit_t APID)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)APID << 16);
  s &= (uint32_t)0x7ff0000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x7ff0000ull;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "SeqFlags" from "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqFlags".
 */
static inline Two_Bit_t getVerSuccessPrgrRepSeqFlags(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 14;
  t &= 0x3;
  return (Two_Bit_t)t;
}

/**
 * Set "SeqFlags" in "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param SeqFlags Value of "SeqFlags" to be set in packet.
 */
static inline void setVerSuccessPrgrRepSeqFlags(void* p, Two_Bit_t SeqFlags)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SeqFlags << 14);
  s &= (uint16_t)0xc000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xc000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)+2], &t, sizeof(t));
}

/**
 * Get "SeqCount" from "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqCount".
 */
static inline FourTeen_Bit_t getVerSuccessPrgrRepSeqCount(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x3fff;
  return (FourTeen_Bit_t)t;
}

/**
 * Set "SeqCount" in "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param SeqCount Value of "SeqCount" to be set in packet.
 */
static inline void setVerSuccessPrgrRepSeqCount(void* p, FourTeen_Bit_t SeqCount)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)SeqCount << 16);
  s &= (uint32_t)0x3fff0000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x3fff0000ull;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)+2], &t, sizeof(t));
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
 * Get "PcktVersionNmb" from "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktVersionNmb".
 */
static inline Three_Bit_t getVerFailedPrgrRepPcktVersionNmb(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 13;
  t &= 0x7;
  return (Three_Bit_t)t;
}

/**
 * Set "PcktVersionNmb" in "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param PcktVersionNmb Value of "PcktVersionNmb" to be set in packet.
 */
static inline void setVerFailedPrgrRepPcktVersionNmb(void* p, Three_Bit_t PcktVersionNmb)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktVersionNmb << 13);
  s &= (uint16_t)0xe000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xe000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "PcktType" from "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktType".
 */
static inline One_Bit_t getVerFailedPrgrRepPcktType(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 12;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "PcktType" in "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param PcktType Value of "PcktType" to be set in packet.
 */
static inline void setVerFailedPrgrRepPcktType(void* p, One_Bit_t PcktType)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktType << 12);
  s &= (uint16_t)0x1000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x1000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "SecHeaderFlag" from "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SecHeaderFlag".
 */
static inline One_Bit_t getVerFailedPrgrRepSecHeaderFlag(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 11;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "SecHeaderFlag" in "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param SecHeaderFlag Value of "SecHeaderFlag" to be set in packet.
 */
static inline void setVerFailedPrgrRepSecHeaderFlag(void* p, One_Bit_t SecHeaderFlag)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SecHeaderFlag << 11);
  s &= (uint16_t)0x800ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x800ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "APID" from "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "APID".
 */
static inline Eleven_Bit_t getVerFailedPrgrRepAPID(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x7ff;
  return (Eleven_Bit_t)t;
}

/**
 * Set "APID" in "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param APID Value of "APID" to be set in packet.
 */
static inline void setVerFailedPrgrRepAPID(void* p, Eleven_Bit_t APID)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)APID << 16);
  s &= (uint32_t)0x7ff0000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x7ff0000ull;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "SeqFlags" from "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqFlags".
 */
static inline Two_Bit_t getVerFailedPrgrRepSeqFlags(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 14;
  t &= 0x3;
  return (Two_Bit_t)t;
}

/**
 * Set "SeqFlags" in "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param SeqFlags Value of "SeqFlags" to be set in packet.
 */
static inline void setVerFailedPrgrRepSeqFlags(void* p, Two_Bit_t SeqFlags)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SeqFlags << 14);
  s &= (uint16_t)0xc000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xc000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)+2], &t, sizeof(t));
}

/**
 * Get "SeqCount" from "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqCount".
 */
static inline FourTeen_Bit_t getVerFailedPrgrRepSeqCount(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x3fff;
  return (FourTeen_Bit_t)t;
}

/**
 * Set "SeqCount" in "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param SeqCount Value of "SeqCount" to be set in packet.
 */
static inline void setVerFailedPrgrRepSeqCount(void* p, FourTeen_Bit_t SeqCount)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)SeqCount << 16);
  s &= (uint32_t)0x3fff0000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x3fff0000ull;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)+2], &t, sizeof(t));
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
 * Get "FailureCode" from "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "FailureCode".
 */
static inline CrPsFailCode_t getVerFailedPrgrRepFailureCode(void* p)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  return __builtin_bswap16(t->FailureCode);
}

/**
 * Set "FailureCode" in "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param FailureCode Value of "FailureCode" to be set in packet.
 */
static inline void setVerFailedPrgrRepFailureCode(void* p, CrPsFailCode_t FailureCode)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  t->FailureCode = __builtin_bswap16(FailureCode);
}

/**
 * Get "FailureData" from "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "FailureData".
 */
static inline CrPsFailData_t getVerFailedPrgrRepFailureData(void* p)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  return __builtin_bswap32(t->FailureData);
}

/**
 * Set "FailureData" in "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param FailureData Value of "FailureData" to be set in packet.
 */
static inline void setVerFailedPrgrRepFailureData(void* p, CrPsFailData_t FailureData)
{
  VerFailedPrgrRep_t* t;
  t = (VerFailedPrgrRep_t*)p;
  t->FailureData = __builtin_bswap32(FailureData);
}

/**
 * Get "PcktVersionNmb" from "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktVersionNmb".
 */
static inline Three_Bit_t getVerSuccessTermRepPcktVersionNmb(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 13;
  t &= 0x7;
  return (Three_Bit_t)t;
}

/**
 * Set "PcktVersionNmb" in "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \param PcktVersionNmb Value of "PcktVersionNmb" to be set in packet.
 */
static inline void setVerSuccessTermRepPcktVersionNmb(void* p, Three_Bit_t PcktVersionNmb)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktVersionNmb << 13);
  s &= (uint16_t)0xe000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xe000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "PcktType" from "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktType".
 */
static inline One_Bit_t getVerSuccessTermRepPcktType(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 12;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "PcktType" in "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \param PcktType Value of "PcktType" to be set in packet.
 */
static inline void setVerSuccessTermRepPcktType(void* p, One_Bit_t PcktType)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktType << 12);
  s &= (uint16_t)0x1000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x1000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "SecHeaderFlag" from "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SecHeaderFlag".
 */
static inline One_Bit_t getVerSuccessTermRepSecHeaderFlag(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 11;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "SecHeaderFlag" in "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \param SecHeaderFlag Value of "SecHeaderFlag" to be set in packet.
 */
static inline void setVerSuccessTermRepSecHeaderFlag(void* p, One_Bit_t SecHeaderFlag)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SecHeaderFlag << 11);
  s &= (uint16_t)0x800ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x800ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "APID" from "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "APID".
 */
static inline Eleven_Bit_t getVerSuccessTermRepAPID(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x7ff;
  return (Eleven_Bit_t)t;
}

/**
 * Set "APID" in "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \param APID Value of "APID" to be set in packet.
 */
static inline void setVerSuccessTermRepAPID(void* p, Eleven_Bit_t APID)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)APID << 16);
  s &= (uint32_t)0x7ff0000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x7ff0000ull;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "SeqFlags" from "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqFlags".
 */
static inline Two_Bit_t getVerSuccessTermRepSeqFlags(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 14;
  t &= 0x3;
  return (Two_Bit_t)t;
}

/**
 * Set "SeqFlags" in "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \param SeqFlags Value of "SeqFlags" to be set in packet.
 */
static inline void setVerSuccessTermRepSeqFlags(void* p, Two_Bit_t SeqFlags)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SeqFlags << 14);
  s &= (uint16_t)0xc000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xc000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)+2], &t, sizeof(t));
}

/**
 * Get "SeqCount" from "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqCount".
 */
static inline FourTeen_Bit_t getVerSuccessTermRepSeqCount(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x3fff;
  return (FourTeen_Bit_t)t;
}

/**
 * Set "SeqCount" in "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \param SeqCount Value of "SeqCount" to be set in packet.
 */
static inline void setVerSuccessTermRepSeqCount(void* p, FourTeen_Bit_t SeqCount)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)SeqCount << 16);
  s &= (uint32_t)0x3fff0000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x3fff0000ull;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)+2], &t, sizeof(t));
}

/**
 * Get "PcktVersionNmb" from "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktVersionNmb".
 */
static inline Three_Bit_t getVerFailedTermRepPcktVersionNmb(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 13;
  t &= 0x7;
  return (Three_Bit_t)t;
}

/**
 * Set "PcktVersionNmb" in "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \param PcktVersionNmb Value of "PcktVersionNmb" to be set in packet.
 */
static inline void setVerFailedTermRepPcktVersionNmb(void* p, Three_Bit_t PcktVersionNmb)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktVersionNmb << 13);
  s &= (uint16_t)0xe000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xe000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "PcktType" from "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktType".
 */
static inline One_Bit_t getVerFailedTermRepPcktType(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 12;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "PcktType" in "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \param PcktType Value of "PcktType" to be set in packet.
 */
static inline void setVerFailedTermRepPcktType(void* p, One_Bit_t PcktType)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktType << 12);
  s &= (uint16_t)0x1000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x1000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "SecHeaderFlag" from "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SecHeaderFlag".
 */
static inline One_Bit_t getVerFailedTermRepSecHeaderFlag(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 11;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "SecHeaderFlag" in "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \param SecHeaderFlag Value of "SecHeaderFlag" to be set in packet.
 */
static inline void setVerFailedTermRepSecHeaderFlag(void* p, One_Bit_t SecHeaderFlag)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SecHeaderFlag << 11);
  s &= (uint16_t)0x800ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x800ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "APID" from "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "APID".
 */
static inline Eleven_Bit_t getVerFailedTermRepAPID(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x7ff;
  return (Eleven_Bit_t)t;
}

/**
 * Set "APID" in "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \param APID Value of "APID" to be set in packet.
 */
static inline void setVerFailedTermRepAPID(void* p, Eleven_Bit_t APID)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)APID << 16);
  s &= (uint32_t)0x7ff0000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x7ff0000ull;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "SeqFlags" from "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqFlags".
 */
static inline Two_Bit_t getVerFailedTermRepSeqFlags(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 14;
  t &= 0x3;
  return (Two_Bit_t)t;
}

/**
 * Set "SeqFlags" in "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \param SeqFlags Value of "SeqFlags" to be set in packet.
 */
static inline void setVerFailedTermRepSeqFlags(void* p, Two_Bit_t SeqFlags)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SeqFlags << 14);
  s &= (uint16_t)0xc000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xc000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)+2], &t, sizeof(t));
}

/**
 * Get "SeqCount" from "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqCount".
 */
static inline FourTeen_Bit_t getVerFailedTermRepSeqCount(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x3fff;
  return (FourTeen_Bit_t)t;
}

/**
 * Set "SeqCount" in "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \param SeqCount Value of "SeqCount" to be set in packet.
 */
static inline void setVerFailedTermRepSeqCount(void* p, FourTeen_Bit_t SeqCount)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)SeqCount << 16);
  s &= (uint32_t)0x3fff0000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x3fff0000ull;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)+2], &t, sizeof(t));
}

/**
 * Get "FailureCode" from "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "FailureCode".
 */
static inline CrPsFailCode_t getVerFailedTermRepFailureCode(void* p)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  return __builtin_bswap16(t->FailureCode);
}

/**
 * Set "FailureCode" in "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \param FailureCode Value of "FailureCode" to be set in packet.
 */
static inline void setVerFailedTermRepFailureCode(void* p, CrPsFailCode_t FailureCode)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  t->FailureCode = __builtin_bswap16(FailureCode);
}

/**
 * Get "FailureData" from "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "FailureData".
 */
static inline CrPsFailData_t getVerFailedTermRepFailureData(void* p)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  return __builtin_bswap32(t->FailureData);
}

/**
 * Set "FailureData" in "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \param FailureData Value of "FailureData" to be set in packet.
 */
static inline void setVerFailedTermRepFailureData(void* p, CrPsFailData_t FailureData)
{
  VerFailedTermRep_t* t;
  t = (VerFailedTermRep_t*)p;
  t->FailureData = __builtin_bswap32(FailureData);
}

/**
 * Get "PcktVersionNmb" from "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktVersionNmb".
 */
static inline Three_Bit_t getVerFailedRoutingRepPcktVersionNmb(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 13;
  t &= 0x7;
  return (Three_Bit_t)t;
}

/**
 * Set "PcktVersionNmb" in "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \param PcktVersionNmb Value of "PcktVersionNmb" to be set in packet.
 */
static inline void setVerFailedRoutingRepPcktVersionNmb(void* p, Three_Bit_t PcktVersionNmb)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktVersionNmb << 13);
  s &= (uint16_t)0xe000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xe000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "PcktType" from "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktType".
 */
static inline One_Bit_t getVerFailedRoutingRepPcktType(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 12;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "PcktType" in "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \param PcktType Value of "PcktType" to be set in packet.
 */
static inline void setVerFailedRoutingRepPcktType(void* p, One_Bit_t PcktType)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktType << 12);
  s &= (uint16_t)0x1000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x1000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "SecHeaderFlag" from "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SecHeaderFlag".
 */
static inline One_Bit_t getVerFailedRoutingRepSecHeaderFlag(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 11;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "SecHeaderFlag" in "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \param SecHeaderFlag Value of "SecHeaderFlag" to be set in packet.
 */
static inline void setVerFailedRoutingRepSecHeaderFlag(void* p, One_Bit_t SecHeaderFlag)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SecHeaderFlag << 11);
  s &= (uint16_t)0x800ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x800ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "APID" from "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "APID".
 */
static inline Eleven_Bit_t getVerFailedRoutingRepAPID(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x7ff;
  return (Eleven_Bit_t)t;
}

/**
 * Set "APID" in "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \param APID Value of "APID" to be set in packet.
 */
static inline void setVerFailedRoutingRepAPID(void* p, Eleven_Bit_t APID)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)APID << 16);
  s &= (uint32_t)0x7ff0000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x7ff0000ull;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &t, sizeof(t));
}

/**
 * Get "SeqFlags" from "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqFlags".
 */
static inline Two_Bit_t getVerFailedRoutingRepSeqFlags(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 14;
  t &= 0x3;
  return (Two_Bit_t)t;
}

/**
 * Set "SeqFlags" in "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \param SeqFlags Value of "SeqFlags" to be set in packet.
 */
static inline void setVerFailedRoutingRepSeqFlags(void* p, Two_Bit_t SeqFlags)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SeqFlags << 14);
  s &= (uint16_t)0xc000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xc000ull;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)+2], &t, sizeof(t));
}

/**
 * Get "SeqCount" from "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqCount".
 */
static inline FourTeen_Bit_t getVerFailedRoutingRepSeqCount(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x3fff;
  return (FourTeen_Bit_t)t;
}

/**
 * Set "SeqCount" in "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \param SeqCount Value of "SeqCount" to be set in packet.
 */
static inline void setVerFailedRoutingRepSeqCount(void* p, FourTeen_Bit_t SeqCount)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)SeqCount << 16);
  s &= (uint32_t)0x3fff0000ull;
  (void)memcpy(&t, &((uint8_t*)p)[sizeof(TmHeader_t)+2], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x3fff0000ull;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)+2], &t, sizeof(t));
}

/**
 * Get "FailureCode" from "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "FailureCode".
 */
static inline CrPsFailCode_t getVerFailedRoutingRepFailureCode(void* p)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  return __builtin_bswap16(t->FailureCode);
}

/**
 * Set "FailureCode" in "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \param FailureCode Value of "FailureCode" to be set in packet.
 */
static inline void setVerFailedRoutingRepFailureCode(void* p, CrPsFailCode_t FailureCode)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  t->FailureCode = __builtin_bswap16(FailureCode);
}

/**
 * Get "FailureData" from "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "FailureData".
 */
static inline CrPsFailData_t getVerFailedRoutingRepFailureData(void* p)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  return __builtin_bswap32(t->FailureData);
}

/**
 * Set "FailureData" in "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \param FailureData Value of "FailureData" to be set in packet.
 */
static inline void setVerFailedRoutingRepFailureData(void* p, CrPsFailData_t FailureData)
{
  VerFailedRoutingRep_t* t;
  t = (VerFailedRoutingRep_t*)p;
  t->FailureData = __builtin_bswap32(FailureData);
}



/*----------------------------------------------------------------------------*/
#endif /* CRPSPKTSERVREQVERIF_H */
