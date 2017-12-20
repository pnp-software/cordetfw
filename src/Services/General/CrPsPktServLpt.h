/**
 * \file
 *
 * Interface for accessing fields in packets of service "ServLPT".
 *
 * \note This file was generated on 2017-11-22 12:47:43
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSPKTSERVLPT_H_
#define CRPSPKTSERVLPT_H_

#include "CrPsDpTypes.h"
#include <CrPsUserConstants.h>

#include "CrPsPkt.h"
/**
 * Structure for LptDownFirstRep
 */
typedef struct __attribute__((packed)) _LptDownFirstRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Capable of containing the [0, +2^32 -1] range
   */
  CrPsTid_t Tid;
  
  /**
   * Capable of containing the [0, +2^32 -1] range
   */
  CrPsNumberU4_t PartSeqNmb;
  
  /**
   * CrPsPart_t
   */
  CrPsPart_t Part;
  
} LptDownFirstRep_t ;

/**
 * Structure for LptDownInterRep
 */
typedef struct __attribute__((packed)) _LptDownInterRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Capable of containing the [0, +2^32 -1] range
   */
  CrPsTid_t Tid;
  
  /**
   * Capable of containing the [0, +2^32 -1] range
   */
  CrPsNumberU4_t PartSeqNmb;
  
  /**
   * CrPsPart_t
   */
  CrPsPart_t Part;
  
} LptDownInterRep_t ;

/**
 * Structure for LptDownLastRep
 */
typedef struct __attribute__((packed)) _LptDownLastRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Capable of containing the [0, +2^32 -1] range
   */
  CrPsTid_t Tid;
  
  /**
   * Capable of containing the [0, +2^32 -1] range
   */
  CrPsNumberU4_t PartSeqNmb;
  
  /**
   * CrPsPart_t
   */
  CrPsPart_t Part;
  
} LptDownLastRep_t ;

/**
 * Structure for LptUpFirstCmd
 */
typedef struct __attribute__((packed)) _LptUpFirstCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * Capable of containing the [0, +2^32 -1] range
   */
  CrPsTid_t Tid;
  
  /**
   * Capable of containing the [0, +2^32 -1] range
   */
  CrPsNumberU4_t PartSeqNmb;
  
  /**
   * CrPsPart_t
   */
  CrPsPart_t Part;
  
} LptUpFirstCmd_t ;

/**
 * Structure for LptUpInterCmd
 */
typedef struct __attribute__((packed)) _LptUpInterCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * Capable of containing the [0, +2^32 -1] range
   */
  CrPsTid_t Tid;
  
  /**
   * Capable of containing the [0, +2^32 -1] range
   */
  CrPsNumberU4_t PartSeqNmb;
  
  /**
   * CrPsPart_t
   */
  CrPsPart_t Part;
  
} LptUpInterCmd_t ;

/**
 * Structure for LptUpLastCmd
 */
typedef struct __attribute__((packed)) _LptUpLastCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * Capable of containing the [0, +2^32 -1] range
   */
  CrPsTid_t Tid;
  
  /**
   * Capable of containing the [0, +2^32 -1] range
   */
  CrPsNumberU4_t PartSeqNmb;
  
  /**
   * CrPsPart_t
   */
  CrPsPart_t Part;
  
} LptUpLastCmd_t ;

/**
 * Structure for LptUpAbortRep
 */
typedef struct __attribute__((packed)) _LptUpAbortRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Capable of containing the [0, +2^32 -1] range
   */
  CrPsTid_t Tid;
  
  /**
   * CrPsFailReason_t
   */
  CrPsFailReason_t FailReason;
  
} LptUpAbortRep_t ;

/**
 * Structure for LptStartDownCmd
 */
typedef struct __attribute__((packed)) _LptStartDownCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * Capable of containing the [0, +2^32 -1] range
   */
  CrPsTid_t Tid;
  
} LptStartDownCmd_t ;

/**
 * Structure for LptAbortDownCmd
 */
typedef struct __attribute__((packed)) _LptAbortDownCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * Capable of containing the [0, +2^32 -1] range
   */
  CrPsTid_t Tid;
  
} LptAbortDownCmd_t ;

/**
 * Get "Tid" from "LptDownFirstRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "Tid".
 */
static inline CrPsTid_t getLptDownFirstRepTid(void* p)
{
  LptDownFirstRep_t* t;
  t = (LptDownFirstRep_t*)p;
  return __builtin_bswap32(t->Tid);
}

/**
 * Set "Tid" in "LptDownFirstRep" packet.
 * \param p Pointer to the packet.
 * \param Tid Value of "Tid" to be set in packet.
 */
static inline void setLptDownFirstRepTid(void* p, CrPsTid_t Tid)
{
  LptDownFirstRep_t* t;
  t = (LptDownFirstRep_t*)p;
  t->Tid = __builtin_bswap32(Tid);
}

/**
 * Get "PartSeqNmb" from "LptDownFirstRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PartSeqNmb".
 */
static inline CrPsNumberU4_t getLptDownFirstRepPartSeqNmb(void* p)
{
  LptDownFirstRep_t* t;
  t = (LptDownFirstRep_t*)p;
  return __builtin_bswap32(t->PartSeqNmb);
}

/**
 * Set "PartSeqNmb" in "LptDownFirstRep" packet.
 * \param p Pointer to the packet.
 * \param PartSeqNmb Value of "PartSeqNmb" to be set in packet.
 */
static inline void setLptDownFirstRepPartSeqNmb(void* p, CrPsNumberU4_t PartSeqNmb)
{
  LptDownFirstRep_t* t;
  t = (LptDownFirstRep_t*)p;
  t->PartSeqNmb = __builtin_bswap32(PartSeqNmb);
}

/**
 * Get "Tid" from "LptDownInterRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "Tid".
 */
static inline CrPsTid_t getLptDownInterRepTid(void* p)
{
  LptDownInterRep_t* t;
  t = (LptDownInterRep_t*)p;
  return __builtin_bswap32(t->Tid);
}

/**
 * Set "Tid" in "LptDownInterRep" packet.
 * \param p Pointer to the packet.
 * \param Tid Value of "Tid" to be set in packet.
 */
static inline void setLptDownInterRepTid(void* p, CrPsTid_t Tid)
{
  LptDownInterRep_t* t;
  t = (LptDownInterRep_t*)p;
  t->Tid = __builtin_bswap32(Tid);
}

/**
 * Get "PartSeqNmb" from "LptDownInterRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PartSeqNmb".
 */
static inline CrPsNumberU4_t getLptDownInterRepPartSeqNmb(void* p)
{
  LptDownInterRep_t* t;
  t = (LptDownInterRep_t*)p;
  return __builtin_bswap32(t->PartSeqNmb);
}

/**
 * Set "PartSeqNmb" in "LptDownInterRep" packet.
 * \param p Pointer to the packet.
 * \param PartSeqNmb Value of "PartSeqNmb" to be set in packet.
 */
static inline void setLptDownInterRepPartSeqNmb(void* p, CrPsNumberU4_t PartSeqNmb)
{
  LptDownInterRep_t* t;
  t = (LptDownInterRep_t*)p;
  t->PartSeqNmb = __builtin_bswap32(PartSeqNmb);
}

/**
 * Get "Tid" from "LptDownLastRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "Tid".
 */
static inline CrPsTid_t getLptDownLastRepTid(void* p)
{
  LptDownLastRep_t* t;
  t = (LptDownLastRep_t*)p;
  return __builtin_bswap32(t->Tid);
}

/**
 * Set "Tid" in "LptDownLastRep" packet.
 * \param p Pointer to the packet.
 * \param Tid Value of "Tid" to be set in packet.
 */
static inline void setLptDownLastRepTid(void* p, CrPsTid_t Tid)
{
  LptDownLastRep_t* t;
  t = (LptDownLastRep_t*)p;
  t->Tid = __builtin_bswap32(Tid);
}

/**
 * Get "PartSeqNmb" from "LptDownLastRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PartSeqNmb".
 */
static inline CrPsNumberU4_t getLptDownLastRepPartSeqNmb(void* p)
{
  LptDownLastRep_t* t;
  t = (LptDownLastRep_t*)p;
  return __builtin_bswap32(t->PartSeqNmb);
}

/**
 * Set "PartSeqNmb" in "LptDownLastRep" packet.
 * \param p Pointer to the packet.
 * \param PartSeqNmb Value of "PartSeqNmb" to be set in packet.
 */
static inline void setLptDownLastRepPartSeqNmb(void* p, CrPsNumberU4_t PartSeqNmb)
{
  LptDownLastRep_t* t;
  t = (LptDownLastRep_t*)p;
  t->PartSeqNmb = __builtin_bswap32(PartSeqNmb);
}

/**
 * Get "Tid" from "LptUpFirstCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "Tid".
 */
static inline CrPsTid_t getLptUpFirstCmdTid(void* p)
{
  LptUpFirstCmd_t* t;
  t = (LptUpFirstCmd_t*)p;
  return __builtin_bswap32(t->Tid);
}

/**
 * Set "Tid" in "LptUpFirstCmd" packet.
 * \param p Pointer to the packet.
 * \param Tid Value of "Tid" to be set in packet.
 */
static inline void setLptUpFirstCmdTid(void* p, CrPsTid_t Tid)
{
  LptUpFirstCmd_t* t;
  t = (LptUpFirstCmd_t*)p;
  t->Tid = __builtin_bswap32(Tid);
}

/**
 * Get "PartSeqNmb" from "LptUpFirstCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "PartSeqNmb".
 */
static inline CrPsNumberU4_t getLptUpFirstCmdPartSeqNmb(void* p)
{
  LptUpFirstCmd_t* t;
  t = (LptUpFirstCmd_t*)p;
  return __builtin_bswap32(t->PartSeqNmb);
}

/**
 * Set "PartSeqNmb" in "LptUpFirstCmd" packet.
 * \param p Pointer to the packet.
 * \param PartSeqNmb Value of "PartSeqNmb" to be set in packet.
 */
static inline void setLptUpFirstCmdPartSeqNmb(void* p, CrPsNumberU4_t PartSeqNmb)
{
  LptUpFirstCmd_t* t;
  t = (LptUpFirstCmd_t*)p;
  t->PartSeqNmb = __builtin_bswap32(PartSeqNmb);
}

/**
 * Get "Tid" from "LptUpInterCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "Tid".
 */
static inline CrPsTid_t getLptUpInterCmdTid(void* p)
{
  LptUpInterCmd_t* t;
  t = (LptUpInterCmd_t*)p;
  return __builtin_bswap32(t->Tid);
}

/**
 * Set "Tid" in "LptUpInterCmd" packet.
 * \param p Pointer to the packet.
 * \param Tid Value of "Tid" to be set in packet.
 */
static inline void setLptUpInterCmdTid(void* p, CrPsTid_t Tid)
{
  LptUpInterCmd_t* t;
  t = (LptUpInterCmd_t*)p;
  t->Tid = __builtin_bswap32(Tid);
}

/**
 * Get "PartSeqNmb" from "LptUpInterCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "PartSeqNmb".
 */
static inline CrPsNumberU4_t getLptUpInterCmdPartSeqNmb(void* p)
{
  LptUpInterCmd_t* t;
  t = (LptUpInterCmd_t*)p;
  return __builtin_bswap32(t->PartSeqNmb);
}

/**
 * Set "PartSeqNmb" in "LptUpInterCmd" packet.
 * \param p Pointer to the packet.
 * \param PartSeqNmb Value of "PartSeqNmb" to be set in packet.
 */
static inline void setLptUpInterCmdPartSeqNmb(void* p, CrPsNumberU4_t PartSeqNmb)
{
  LptUpInterCmd_t* t;
  t = (LptUpInterCmd_t*)p;
  t->PartSeqNmb = __builtin_bswap32(PartSeqNmb);
}

/**
 * Get "Tid" from "LptUpLastCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "Tid".
 */
static inline CrPsTid_t getLptUpLastCmdTid(void* p)
{
  LptUpLastCmd_t* t;
  t = (LptUpLastCmd_t*)p;
  return __builtin_bswap32(t->Tid);
}

/**
 * Set "Tid" in "LptUpLastCmd" packet.
 * \param p Pointer to the packet.
 * \param Tid Value of "Tid" to be set in packet.
 */
static inline void setLptUpLastCmdTid(void* p, CrPsTid_t Tid)
{
  LptUpLastCmd_t* t;
  t = (LptUpLastCmd_t*)p;
  t->Tid = __builtin_bswap32(Tid);
}

/**
 * Get "PartSeqNmb" from "LptUpLastCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "PartSeqNmb".
 */
static inline CrPsNumberU4_t getLptUpLastCmdPartSeqNmb(void* p)
{
  LptUpLastCmd_t* t;
  t = (LptUpLastCmd_t*)p;
  return __builtin_bswap32(t->PartSeqNmb);
}

/**
 * Set "PartSeqNmb" in "LptUpLastCmd" packet.
 * \param p Pointer to the packet.
 * \param PartSeqNmb Value of "PartSeqNmb" to be set in packet.
 */
static inline void setLptUpLastCmdPartSeqNmb(void* p, CrPsNumberU4_t PartSeqNmb)
{
  LptUpLastCmd_t* t;
  t = (LptUpLastCmd_t*)p;
  t->PartSeqNmb = __builtin_bswap32(PartSeqNmb);
}

/**
 * Get "Tid" from "LptUpAbortRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "Tid".
 */
static inline CrPsTid_t getLptUpAbortRepTid(void* p)
{
  LptUpAbortRep_t* t;
  t = (LptUpAbortRep_t*)p;
  return __builtin_bswap32(t->Tid);
}

/**
 * Set "Tid" in "LptUpAbortRep" packet.
 * \param p Pointer to the packet.
 * \param Tid Value of "Tid" to be set in packet.
 */
static inline void setLptUpAbortRepTid(void* p, CrPsTid_t Tid)
{
  LptUpAbortRep_t* t;
  t = (LptUpAbortRep_t*)p;
  t->Tid = __builtin_bswap32(Tid);
}

/**
 * Get "FailReason" from "LptUpAbortRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "FailReason".
 */
static inline CrPsFailReason_t getLptUpAbortRepFailReason(void* p)
{
  LptUpAbortRep_t* t;
  t = (LptUpAbortRep_t*)p;
  return __builtin_bswap32(t->FailReason);
}

/**
 * Set "FailReason" in "LptUpAbortRep" packet.
 * \param p Pointer to the packet.
 * \param FailReason Value of "FailReason" to be set in packet.
 */
static inline void setLptUpAbortRepFailReason(void* p, CrPsFailReason_t FailReason)
{
  LptUpAbortRep_t* t;
  t = (LptUpAbortRep_t*)p;
  t->FailReason = __builtin_bswap32(FailReason);
}

/**
 * Get "Tid" from "LptStartDownCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "Tid".
 */
static inline CrPsTid_t getLptStartDownCmdTid(void* p)
{
  LptStartDownCmd_t* t;
  t = (LptStartDownCmd_t*)p;
  return __builtin_bswap32(t->Tid);
}

/**
 * Set "Tid" in "LptStartDownCmd" packet.
 * \param p Pointer to the packet.
 * \param Tid Value of "Tid" to be set in packet.
 */
static inline void setLptStartDownCmdTid(void* p, CrPsTid_t Tid)
{
  LptStartDownCmd_t* t;
  t = (LptStartDownCmd_t*)p;
  t->Tid = __builtin_bswap32(Tid);
}

/**
 * Get "Tid" from "LptAbortDownCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "Tid".
 */
static inline CrPsTid_t getLptAbortDownCmdTid(void* p)
{
  LptAbortDownCmd_t* t;
  t = (LptAbortDownCmd_t*)p;
  return __builtin_bswap32(t->Tid);
}

/**
 * Set "Tid" in "LptAbortDownCmd" packet.
 * \param p Pointer to the packet.
 * \param Tid Value of "Tid" to be set in packet.
 */
static inline void setLptAbortDownCmdTid(void* p, CrPsTid_t Tid)
{
  LptAbortDownCmd_t* t;
  t = (LptAbortDownCmd_t*)p;
  t->Tid = __builtin_bswap32(Tid);
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSPKTSERVLPT_H */
