/**
 * @file CrPsPkt.h
 * @ingroup PUSTestsuite
 * @ingroup PUSTestconfig 
 *
 * @brief Packet header definitions.
 *
 * @note This file was generated on 2017-10-13 12:48:17
 * @author PnP Generator
 *
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

#ifndef CRPSPKT_H_
#define CRPSPKT_H_

#include "CrFwUserConstants.h"
#include "CrPsUserConstants.h"
#include "Pckt/CrFwPckt.h"

/**
 * Structure for TcHeader
 */
typedef struct __attribute__((packed)) _TcHeader_t {
  /**
   * Spacer block.
   */
  uint8_t block_5[2];

  /**
   * Spacer block.
   */
  uint8_t block_18[2];

  /**
   * (16 bit)
   */
  CrFwPcktLength_t PcktDataLen;
  
  /**
   * Spacer block.
   */
  uint8_t block_55[1];

  /**
   * Service Type (8 bit)
   */
  CrFwServType_t ServType;
  
  /**
   * Service Sub Type (8 bit)
   */
  CrFwServSubType_t ServSubType;
  
  /**
   * Source ID (16 bit)
   */
  CrFwDestSrc_t SrcId;
  
} TcHeader_t ;

/**
 * Structure for TmHeader
 */
typedef struct __attribute__((packed)) _TmHeader_t {
  /**
   * Spacer block.
   */
  uint8_t block_5[2];

  /**
   * Spacer block.
   */
  uint8_t block_18[2];

  /**
   * (16 bit)
   */
  CrFwPcktLength_t PcktDataLen;
  
  /**
   * Spacer block.
   */
  uint8_t block_52[1];

  /**
   * Service Type (8 bit)
   */
  CrFwServType_t ServType;
  
  /**
   * Service Sub Type (8 bit)
   */
  CrFwServSubType_t ServSubType;
  
  /**
   * Destination ID (16bit)
   */
  CrFwDestSrc_t DestId;
  
  /**
   * character array 6xchars
   */
  CrFwTimeStamp_t Time;
  
} TmHeader_t ;

/**
 * Get "PcktVersionNmb" from "TcHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktVersionNmb".
 */
static inline Three_Bit_t getTcHeaderPcktVersionNmb(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 13;
  t &= 0x7;
  return (Three_Bit_t)t;
}

/**
 * Set "PcktVersionNmb" in "TcHeader" packet.
 * \param p Pointer to the packet.
 * \param PcktVersionNmb Value of "PcktVersionNmb" to be set in packet.
 */
static inline void setTcHeaderPcktVersionNmb(void* p, Three_Bit_t PcktVersionNmb)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktVersionNmb << 13);
  s &= (uint16_t)0xe000;
  (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xe000;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[0], &t, sizeof(t));
}

/**
 * Get "PcktType" from "TcHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktType".
 */
static inline One_Bit_t getTcHeaderPcktType(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 12;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "PcktType" in "TcHeader" packet.
 * \param p Pointer to the packet.
 * \param PcktType Value of "PcktType" to be set in packet.
 */
static inline void setTcHeaderPcktType(void* p, One_Bit_t PcktType)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktType << 12);
  s &= (uint16_t)0x1000;
  (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x1000;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[0], &t, sizeof(t));
}

/**
 * Get "SecHeaderFlag" from "TcHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "SecHeaderFlag".
 */
static inline One_Bit_t getTcHeaderSecHeaderFlag(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 11;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "SecHeaderFlag" in "TcHeader" packet.
 * \param p Pointer to the packet.
 * \param SecHeaderFlag Value of "SecHeaderFlag" to be set in packet.
 */
static inline void setTcHeaderSecHeaderFlag(void* p, One_Bit_t SecHeaderFlag)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SecHeaderFlag << 11);
  s &= (uint16_t)0x800;
  (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x800;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[0], &t, sizeof(t));
}

/**
 * Get "APID" from "TcHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "APID".
 */
static inline Eleven_Bit_t getTcHeaderAPID(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x7ff;
  return (Eleven_Bit_t)t;
}

/**
 * Set "APID" in "TcHeader" packet.
 * \param p Pointer to the packet.
 * \param APID Value of "APID" to be set in packet.
 */
static inline void setTcHeaderAPID(void* p, Eleven_Bit_t APID)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)APID << 16);
  s &= (uint32_t)0x7ff0000;
  (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x7ff0000;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[0], &t, sizeof(t));
}

/**
 * Get "SeqFlags" from "TcHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqFlags".
 */
static inline Two_Bit_t getTcHeaderSeqFlags(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[2], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 14;
  t &= 0x3;
  return (Two_Bit_t)t;
}

/**
 * Set "SeqFlags" in "TcHeader" packet.
 * \param p Pointer to the packet.
 * \param SeqFlags Value of "SeqFlags" to be set in packet.
 */
static inline void setTcHeaderSeqFlags(void* p, Two_Bit_t SeqFlags)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SeqFlags << 14);
  s &= (uint16_t)0xc000;
  (void)memcpy(&t, &((uint8_t*)p)[2], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xc000;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[2], &t, sizeof(t));
}

/**
 * Get "SeqCount" from "TcHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqCount".
 */
static inline FourTeen_Bit_t getTcHeaderSeqCount(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[2], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x3fff;
  return (FourTeen_Bit_t)t;
}

/**
 * Set "SeqCount" in "TcHeader" packet.
 * \param p Pointer to the packet.
 * \param SeqCount Value of "SeqCount" to be set in packet.
 */
static inline void setTcHeaderSeqCount(void* p, FourTeen_Bit_t SeqCount)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)SeqCount << 16);
  s &= (uint32_t)0x3fff0000;
  (void)memcpy(&t, &((uint8_t*)p)[2], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x3fff0000;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[2], &t, sizeof(t));
}

/**
 * Get "PcktDataLen" from "TcHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktDataLen".
 */
static inline CrFwPcktLength_t getTcHeaderPcktDataLen(void* p)
{
  TcHeader_t* t;
  t = (TcHeader_t*)p;
  return __builtin_bswap16(t->PcktDataLen);
}

/**
 * Set "PcktDataLen" in "TcHeader" packet.
 * \param p Pointer to the packet.
 * \param PcktDataLen Value of "PcktDataLen" to be set in packet.
 */
static inline void setTcHeaderPcktDataLen(void* p, CrFwPcktLength_t PcktDataLen)
{
  TcHeader_t* t;
  t = (TcHeader_t*)p;
  t->PcktDataLen = __builtin_bswap16(PcktDataLen);
}

/**
 * Get "PUSVersion" from "TcHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "PUSVersion".
 */
static inline Four_Bit_t getTcHeaderPUSVersion(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 12;
  t &= 0xf;
  return (Four_Bit_t)t;
}

/**
 * Set "PUSVersion" in "TcHeader" packet.
 * \param p Pointer to the packet.
 * \param PUSVersion Value of "PUSVersion" to be set in packet.
 */
static inline void setTcHeaderPUSVersion(void* p, Four_Bit_t PUSVersion)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PUSVersion << 12);
  s &= (uint16_t)0xf000;
  (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xf000;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[6], &t, sizeof(t));
}

/**
 * Get "AckAccFlag" from "TcHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "AckAccFlag".
 */
static inline One_Bit_t getTcHeaderAckAccFlag(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 11;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "AckAccFlag" in "TcHeader" packet.
 * \param p Pointer to the packet.
 * \param AckAccFlag Value of "AckAccFlag" to be set in packet.
 */
static inline void setTcHeaderAckAccFlag(void* p, One_Bit_t AckAccFlag)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)AckAccFlag << 11);
  s &= (uint16_t)0x800;
  (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x800;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[6], &t, sizeof(t));
}

/**
 * Get "AckStartFlag" from "TcHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "AckStartFlag".
 */
static inline One_Bit_t getTcHeaderAckStartFlag(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 10;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "AckStartFlag" in "TcHeader" packet.
 * \param p Pointer to the packet.
 * \param AckStartFlag Value of "AckStartFlag" to be set in packet.
 */
static inline void setTcHeaderAckStartFlag(void* p, One_Bit_t AckStartFlag)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)AckStartFlag << 10);
  s &= (uint16_t)0x400;
  (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x400;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[6], &t, sizeof(t));
}

/**
 * Get "AckProgFlag" from "TcHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "AckProgFlag".
 */
static inline One_Bit_t getTcHeaderAckProgFlag(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 9;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "AckProgFlag" in "TcHeader" packet.
 * \param p Pointer to the packet.
 * \param AckProgFlag Value of "AckProgFlag" to be set in packet.
 */
static inline void setTcHeaderAckProgFlag(void* p, One_Bit_t AckProgFlag)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)AckProgFlag << 9);
  s &= (uint16_t)0x200;
  (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x200;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[6], &t, sizeof(t));
}

/**
 * Get "AckTermFlag" from "TcHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "AckTermFlag".
 */
static inline One_Bit_t getTcHeaderAckTermFlag(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 8;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "AckTermFlag" in "TcHeader" packet.
 * \param p Pointer to the packet.
 * \param AckTermFlag Value of "AckTermFlag" to be set in packet.
 */
static inline void setTcHeaderAckTermFlag(void* p, One_Bit_t AckTermFlag)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)AckTermFlag << 8);
  s &= (uint16_t)0x100;
  (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x100;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[6], &t, sizeof(t));
}

/**
 * Get "ServType" from "TcHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "ServType".
 */
static inline CrFwServType_t getTcHeaderServType(void* p)
{
  TcHeader_t* t;
  t = (TcHeader_t*)p;
  return t->ServType;
}

/**
 * Set "ServType" in "TcHeader" packet.
 * \param p Pointer to the packet.
 * \param ServType Value of "ServType" to be set in packet.
 */
static inline void setTcHeaderServType(void* p, CrFwServType_t ServType)
{
  TcHeader_t* t;
  t = (TcHeader_t*)p;
  t->ServType = ServType;
}

/**
 * Get "ServSubType" from "TcHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "ServSubType".
 */
static inline CrFwServSubType_t getTcHeaderServSubType(void* p)
{
  TcHeader_t* t;
  t = (TcHeader_t*)p;
  return t->ServSubType;
}

/**
 * Set "ServSubType" in "TcHeader" packet.
 * \param p Pointer to the packet.
 * \param ServSubType Value of "ServSubType" to be set in packet.
 */
static inline void setTcHeaderServSubType(void* p, CrFwServSubType_t ServSubType)
{
  TcHeader_t* t;
  t = (TcHeader_t*)p;
  t->ServSubType = ServSubType;
}

/**
 * Get "SrcId" from "TcHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "SrcId".
 */
static inline CrFwDestSrc_t getTcHeaderSrcId(void* p)
{
  TcHeader_t* t;
  t = (TcHeader_t*)p;
  return t->SrcId;
}

/**
 * Set "SrcId" in "TcHeader" packet.
 * \param p Pointer to the packet.
 * \param SrcId Value of "SrcId" to be set in packet.
 */
static inline void setTcHeaderSrcId(void* p, CrFwDestSrc_t SrcId)
{
  TcHeader_t* t;
  t = (TcHeader_t*)p;
  t->SrcId = SrcId;
}

/**
 * Get "PcktVersionNmb" from "TmHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktVersionNmb".
 */
static inline Three_Bit_t getTmHeaderPcktVersionNmb(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 13;
  t &= 0x7;
  return (Three_Bit_t)t;
}

/**
 * Set "PcktVersionNmb" in "TmHeader" packet.
 * \param p Pointer to the packet.
 * \param PcktVersionNmb Value of "PcktVersionNmb" to be set in packet.
 */
static inline void setTmHeaderPcktVersionNmb(void* p, Three_Bit_t PcktVersionNmb)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktVersionNmb << 13);
  s &= (uint16_t)0xe000;
  (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xe000;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[0], &t, sizeof(t));
}

/**
 * Get "PcktType" from "TmHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktType".
 */
static inline One_Bit_t getTmHeaderPcktType(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 12;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "PcktType" in "TmHeader" packet.
 * \param p Pointer to the packet.
 * \param PcktType Value of "PcktType" to be set in packet.
 */
static inline void setTmHeaderPcktType(void* p, One_Bit_t PcktType)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PcktType << 12);
  s &= (uint16_t)0x1000;
  (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x1000;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[0], &t, sizeof(t));
}

/**
 * Get "SecHeaderFlag" from "TmHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "SecHeaderFlag".
 */
static inline One_Bit_t getTmHeaderSecHeaderFlag(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 11;
  t &= 0x1;
  return (One_Bit_t)t;
}

/**
 * Set "SecHeaderFlag" in "TmHeader" packet.
 * \param p Pointer to the packet.
 * \param SecHeaderFlag Value of "SecHeaderFlag" to be set in packet.
 */
static inline void setTmHeaderSecHeaderFlag(void* p, One_Bit_t SecHeaderFlag)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SecHeaderFlag << 11);
  s &= (uint16_t)0x800;
  (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0x800;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[0], &t, sizeof(t));
}

/**
 * Get "APID" from "TmHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "APID".
 */
static inline Eleven_Bit_t getTmHeaderAPID(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x7ff;
  return (Eleven_Bit_t)t;
}

/**
 * Set "APID" in "TmHeader" packet.
 * \param p Pointer to the packet.
 * \param APID Value of "APID" to be set in packet.
 */
static inline void setTmHeaderAPID(void* p, Eleven_Bit_t APID)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)APID << 16);
  s &= (uint32_t)0x7ff0000;
  (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x7ff0000;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[0], &t, sizeof(t));
}

/**
 * Get "SeqFlags" from "TmHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqFlags".
 */
static inline Two_Bit_t getTmHeaderSeqFlags(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[2], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 14;
  t &= 0x3;
  return (Two_Bit_t)t;
}

/**
 * Set "SeqFlags" in "TmHeader" packet.
 * \param p Pointer to the packet.
 * \param SeqFlags Value of "SeqFlags" to be set in packet.
 */
static inline void setTmHeaderSeqFlags(void* p, Two_Bit_t SeqFlags)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SeqFlags << 14);
  s &= (uint16_t)0xc000;
  (void)memcpy(&t, &((uint8_t*)p)[2], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xc000;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[2], &t, sizeof(t));
}

/**
 * Get "SeqCount" from "TmHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "SeqCount".
 */
static inline FourTeen_Bit_t getTmHeaderSeqCount(void* p)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[2], sizeof(t));
  t = __builtin_bswap32(t);
  t >>= 16;
  t &= 0x3fff;
  return (FourTeen_Bit_t)t;
}

/**
 * Set "SeqCount" in "TmHeader" packet.
 * \param p Pointer to the packet.
 * \param SeqCount Value of "SeqCount" to be set in packet.
 */
static inline void setTmHeaderSeqCount(void* p, FourTeen_Bit_t SeqCount)
{
  uint32_t s;
  uint32_t t;
  s = ((uint32_t)SeqCount << 16);
  s &= (uint32_t)0x3fff0000;
  (void)memcpy(&t, &((uint8_t*)p)[2], sizeof(t));
  t = __builtin_bswap32(t);
  t &= (uint32_t)~0x3fff0000;
  t |= s;
  t = __builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[2], &t, sizeof(t));
}

/**
 * Get "PcktDataLen" from "TmHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "PcktDataLen".
 */
static inline CrFwPcktLength_t getTmHeaderPcktDataLen(void* p)
{
  TmHeader_t* t;
  t = (TmHeader_t*)p;
  return __builtin_bswap16(t->PcktDataLen);
}

/**
 * Set "PcktDataLen" in "TmHeader" packet.
 * \param p Pointer to the packet.
 * \param PcktDataLen Value of "PcktDataLen" to be set in packet.
 */
static inline void setTmHeaderPcktDataLen(void* p, CrFwPcktLength_t PcktDataLen)
{
  TmHeader_t* t;
  t = (TmHeader_t*)p;
  t->PcktDataLen = __builtin_bswap16(PcktDataLen);
}

/**
 * Get "PUSVersion" from "TmHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "PUSVersion".
 */
static inline Four_Bit_t getTmHeaderPUSVersion(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 12;
  t &= 0xf;
  return (Four_Bit_t)t;
}

/**
 * Set "PUSVersion" in "TmHeader" packet.
 * \param p Pointer to the packet.
 * \param PUSVersion Value of "PUSVersion" to be set in packet.
 */
static inline void setTmHeaderPUSVersion(void* p, Four_Bit_t PUSVersion)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)PUSVersion << 12);
  s &= (uint16_t)0xf000;
  (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xf000;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[6], &t, sizeof(t));
}

/**
 * Get "SpaceTimeRefStatus" from "TmHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "SpaceTimeRefStatus".
 */
static inline Four_Bit_t getTmHeaderSpaceTimeRefStatus(void* p)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
  t = __builtin_bswap16(t);
  t >>= 8;
  t &= 0xf;
  return (Four_Bit_t)t;
}

/**
 * Set "SpaceTimeRefStatus" in "TmHeader" packet.
 * \param p Pointer to the packet.
 * \param SpaceTimeRefStatus Value of "SpaceTimeRefStatus" to be set in
 * packet.
 */
static inline void setTmHeaderSpaceTimeRefStatus(void* p, Four_Bit_t SpaceTimeRefStatus)
{
  uint16_t s;
  uint16_t t;
  s = ((uint16_t)SpaceTimeRefStatus << 8);
  s &= (uint16_t)0xf00;
  (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
  t = __builtin_bswap16(t);
  t &= (uint16_t)~0xf00;
  t |= s;
  t = __builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[6], &t, sizeof(t));
}

/**
 * Get "ServType" from "TmHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "ServType".
 */
static inline CrFwServType_t getTmHeaderServType(void* p)
{
  TmHeader_t* t;
  t = (TmHeader_t*)p;
  return t->ServType;
}

/**
 * Set "ServType" in "TmHeader" packet.
 * \param p Pointer to the packet.
 * \param ServType Value of "ServType" to be set in packet.
 */
static inline void setTmHeaderServType(void* p, CrFwServType_t ServType)
{
  TmHeader_t* t;
  t = (TmHeader_t*)p;
  t->ServType = ServType;
}

/**
 * Get "ServSubType" from "TmHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "ServSubType".
 */
static inline CrFwServType_t getTmHeaderServSubType(void* p)
{
  TmHeader_t* t;
  t = (TmHeader_t*)p;
  return t->ServSubType;
}

/**
 * Set "ServSubType" in "TmHeader" packet.
 * \param p Pointer to the packet.
 * \param ServSubType Value of "ServSubType" to be set in packet.
 */
static inline void setTmHeaderServSubType(void* p, CrFwServType_t ServSubType)
{
  TmHeader_t* t;
  t = (TmHeader_t*)p;
  t->ServSubType = ServSubType;
}

/**
 * Get "DestId" from "TmHeader" packet.
 * \param p Pointer to the packet.
 * \return Value of "DestId".
 */
static inline CrFwDestSrc_t getTmHeaderDestId(void* p)
{
  TmHeader_t* t;
  t = (TmHeader_t*)p;
  return t->DestId;
}

/**
 * Set "DestId" in "TmHeader" packet.
 * \param p Pointer to the packet.
 * \param DestId Value of "DestId" to be set in packet.
 */
static inline void setTmHeaderDestId(void* p, CrFwDestSrc_t DestId)
{
  TmHeader_t* t;
  t = (TmHeader_t*)p;
  t->DestId = DestId;
}

/**
 * Get pointer to "Time" array from "TmHeader" packet.
 * \param p Pointer to the packet.
 * \return Pointer to the start of the Time array.
 */
static inline uint8_t* getTmHeaderTimeArray(void* p)
{
  TmHeader_t* t;
  t = (TmHeader_t*)p;
  return &t->Time.t[0];
}

/**
 * Get "Time" array from "TmHeader" packet.
 * \param p Pointer to the packet.
 * \param dest Pointer to memory location where array data are copied to.
 */
static inline void getTmHeaderTime(void* p, void* dest)
{
  TmHeader_t* t;
  t = (TmHeader_t*)p;
  memcpy(dest, &t->Time.t[0], sizeof(t->Time));
}

/**
 * Set "Time" array in "TmHeader" packet.
 * \param p Pointer to the packet.
 * \param src Pointer to memory location from where array data are copied.
 */
static inline void setTmHeaderTime(void* p, const void* src)
{
  TmHeader_t* t;
  t = (TmHeader_t*)p;
  memcpy(&t->Time.t[0], src, sizeof(t->Time));
}


/**/
static inline CrPsSeqCtrl_t CrFwPcktGetSeqCtrl(CrFwPckt_t pckt)
{
	uint32_t seqflags, seqcount;

	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		seqflags = getTmHeaderSeqFlags(pckt);
		seqcount = getTmHeaderSeqCount(pckt);
	}
	else
	{
		seqflags = getTcHeaderSeqFlags(pckt);
		seqcount = getTcHeaderSeqCount(pckt);
	}
	
	return ((seqflags << 14) & 0xc000) | (seqcount & 0x3fff);
}

/**/
static inline void CrFwPcktSetSeqCtrl(CrFwPckt_t pckt, CrPsSeqCtrl_t psc)
{
	uint32_t seqflags, seqcount;

	seqflags = ((psc & 0xc000)>>14)&0x0003;
	seqcount = psc & 0x3fff;

	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		setTmHeaderSeqFlags(pckt, seqflags);
		setTmHeaderSeqCount(pckt, seqcount);
	}
	else
	{
		setTmHeaderSeqFlags(pckt, seqflags);
		setTmHeaderSeqCount(pckt, seqcount);
	}

	return;
}

/**/
static inline CrPsApid_t CrFwPcktGetApid(CrFwPckt_t pckt)
{
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		return getTmHeaderAPID(pckt);
	}
	else
	{
		return getTcHeaderAPID(pckt);
	}
}

/**/
static inline void CrFwPcktSetApid(CrFwPckt_t pckt, CrPsApid_t apid)
{
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		setTmHeaderAPID(pckt, apid);
	}
	else
	{
		setTcHeaderAPID(pckt, apid);
	}
}


/**
 * Getter for the RequestId from a packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
static inline CrPsRid_t getPcktRid(void* p)
{
  CrPsRid_t ret;
  memcpy(&ret, &((uint8_t*)p)[0], sizeof(CrPsRid_t));
  return __builtin_bswap32(ret);
}

/**
 * Setter for the RequestId from a packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
static inline void setPcktRid(void* p, CrPsRid_t Rid)
{
  Rid = __builtin_bswap32(Rid);
  memcpy(&((uint8_t*)p)[0], &Rid, sizeof(CrPsRid_t));
}

/*----------------------------------------------------------------------------*/
#endif /* CRPSPKT_H */
