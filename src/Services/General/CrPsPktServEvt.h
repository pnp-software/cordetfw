/**
 * \file
 *
 * Interface for accessing fields in packets of service "ServEvt".
 *
 * \note This file was generated on 2017-10-13 16:11:59
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSPKTSERVEVT_H_
#define CRPSPKTSERVEVT_H_

#include "CrPsDpTypes.h"

#include "CrPsPkt.h"
/**
 * Structure for EvtRep1
 */
typedef struct __attribute__((packed)) _EvtRep1_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Event Definition ID (enumerated)
   */
  uint8_t EventId;
  
  /**
   * Auxiliary Data
   */
  uint32_t AuxData;
  
} EvtRep1_t ;

/**
 * Structure for EvtRep2
 */
typedef struct __attribute__((packed)) _EvtRep2_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Event Definition ID (enumerated)
   */
  uint8_t EventId;
  
  /**
   * Auxiliary Data
   */
  uint32_t AuxData;
  
} EvtRep2_t ;

/**
 * Structure for EvtRep3
 */
typedef struct __attribute__((packed)) _EvtRep3_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Event Definition ID (enumerated)
   */
  uint8_t EventId;
  
  /**
   * Auxiliary Data
   */
  uint32_t AuxData;
  
} EvtRep3_t ;

/**
 * Structure for EvtRep4
 */
typedef struct __attribute__((packed)) _EvtRep4_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Event Definition ID (enumerated)
   */
  uint8_t EventId;
  
  /**
   * Auxiliary Data
   */
  uint32_t AuxData;
  
} EvtRep4_t ;

/**
 * Structure for EvtEnableCmd
 */
typedef struct __attribute__((packed)) _EvtEnableCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * Capable of containing the [0, +2^32 -1] range
   */
  uint32_t N;
  
  /**
   * Event Definition ID (enumerated)
   */
  uint8_t EventId;
  
} EvtEnableCmd_t ;

/**
 * Structure for EvtDisableCmd
 */
typedef struct __attribute__((packed)) _EvtDisableCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * Capable of containing the [0, +2^32 -1] range
   */
  uint32_t N;
  
  /**
   * Event Definition ID (enumerated)
   */
  uint8_t EventId;
  
} EvtDisableCmd_t ;

/**
 * Structure for EvtRepDisabledCmd
 */
typedef struct __attribute__((packed)) _EvtRepDisabledCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

} EvtRepDisabledCmd_t ;

/**
 * Structure for EvtRepDisabledRep
 */
typedef struct __attribute__((packed)) _EvtRepDisabledRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Capable of containing the [0, +2^32 -1] range
   */
  uint32_t N;
  
  /**
   * Event Definition ID (enumerated)
   */
  uint8_t EventId;
  
} EvtRepDisabledRep_t ;

/**
 * Get "EventId" from "EvtRep1" packet.
 * \param p Pointer to the packet.
 * \return Value of "EventId".
 */
static inline uint8_t getEvtRep1EventId(void* p)
{
  EvtRep1_t* t;
  t = (EvtRep1_t*)p;
  return t->EventId;
}

/**
 * Set "EventId" in "EvtRep1" packet.
 * \param p Pointer to the packet.
 * \param EventId Value of "EventId" to be set in packet.
 */
static inline void setEvtRep1EventId(void* p, uint8_t EventId)
{
  EvtRep1_t* t;
  t = (EvtRep1_t*)p;
  t->EventId = EventId;
}

/**
 * Get "AuxData" from "EvtRep1" packet.
 * \param p Pointer to the packet.
 * \return Value of "AuxData".
 */
static inline uint32_t getEvtRep1AuxData(void* p)
{
  EvtRep1_t* t;
  t = (EvtRep1_t*)p;
  return __builtin_bswap32(t->AuxData);
}

/**
 * Set "AuxData" in "EvtRep1" packet.
 * \param p Pointer to the packet.
 * \param AuxData Value of "AuxData" to be set in packet.
 */
static inline void setEvtRep1AuxData(void* p, uint32_t AuxData)
{
  EvtRep1_t* t;
  t = (EvtRep1_t*)p;
  t->AuxData = __builtin_bswap32(AuxData);
}

/**
 * Get "EventId" from "EvtRep2" packet.
 * \param p Pointer to the packet.
 * \return Value of "EventId".
 */
static inline uint8_t getEvtRep2EventId(void* p)
{
  EvtRep2_t* t;
  t = (EvtRep2_t*)p;
  return t->EventId;
}

/**
 * Set "EventId" in "EvtRep2" packet.
 * \param p Pointer to the packet.
 * \param EventId Value of "EventId" to be set in packet.
 */
static inline void setEvtRep2EventId(void* p, uint8_t EventId)
{
  EvtRep2_t* t;
  t = (EvtRep2_t*)p;
  t->EventId = EventId;
}

/**
 * Get "AuxData" from "EvtRep2" packet.
 * \param p Pointer to the packet.
 * \return Value of "AuxData".
 */
static inline uint32_t getEvtRep2AuxData(void* p)
{
  EvtRep2_t* t;
  t = (EvtRep2_t*)p;
  return __builtin_bswap32(t->AuxData);
}

/**
 * Set "AuxData" in "EvtRep2" packet.
 * \param p Pointer to the packet.
 * \param AuxData Value of "AuxData" to be set in packet.
 */
static inline void setEvtRep2AuxData(void* p, uint32_t AuxData)
{
  EvtRep2_t* t;
  t = (EvtRep2_t*)p;
  t->AuxData = __builtin_bswap32(AuxData);
}

/**
 * Get "EventId" from "EvtRep3" packet.
 * \param p Pointer to the packet.
 * \return Value of "EventId".
 */
static inline uint8_t getEvtRep3EventId(void* p)
{
  EvtRep3_t* t;
  t = (EvtRep3_t*)p;
  return t->EventId;
}

/**
 * Set "EventId" in "EvtRep3" packet.
 * \param p Pointer to the packet.
 * \param EventId Value of "EventId" to be set in packet.
 */
static inline void setEvtRep3EventId(void* p, uint8_t EventId)
{
  EvtRep3_t* t;
  t = (EvtRep3_t*)p;
  t->EventId = EventId;
}

/**
 * Get "AuxData" from "EvtRep3" packet.
 * \param p Pointer to the packet.
 * \return Value of "AuxData".
 */
static inline uint32_t getEvtRep3AuxData(void* p)
{
  EvtRep3_t* t;
  t = (EvtRep3_t*)p;
  return __builtin_bswap32(t->AuxData);
}

/**
 * Set "AuxData" in "EvtRep3" packet.
 * \param p Pointer to the packet.
 * \param AuxData Value of "AuxData" to be set in packet.
 */
static inline void setEvtRep3AuxData(void* p, uint32_t AuxData)
{
  EvtRep3_t* t;
  t = (EvtRep3_t*)p;
  t->AuxData = __builtin_bswap32(AuxData);
}

/**
 * Get "EventId" from "EvtRep4" packet.
 * \param p Pointer to the packet.
 * \return Value of "EventId".
 */
static inline uint8_t getEvtRep4EventId(void* p)
{
  EvtRep4_t* t;
  t = (EvtRep4_t*)p;
  return t->EventId;
}

/**
 * Set "EventId" in "EvtRep4" packet.
 * \param p Pointer to the packet.
 * \param EventId Value of "EventId" to be set in packet.
 */
static inline void setEvtRep4EventId(void* p, uint8_t EventId)
{
  EvtRep4_t* t;
  t = (EvtRep4_t*)p;
  t->EventId = EventId;
}

/**
 * Get "AuxData" from "EvtRep4" packet.
 * \param p Pointer to the packet.
 * \return Value of "AuxData".
 */
static inline uint32_t getEvtRep4AuxData(void* p)
{
  EvtRep4_t* t;
  t = (EvtRep4_t*)p;
  return __builtin_bswap32(t->AuxData);
}

/**
 * Set "AuxData" in "EvtRep4" packet.
 * \param p Pointer to the packet.
 * \param AuxData Value of "AuxData" to be set in packet.
 */
static inline void setEvtRep4AuxData(void* p, uint32_t AuxData)
{
  EvtRep4_t* t;
  t = (EvtRep4_t*)p;
  t->AuxData = __builtin_bswap32(AuxData);
}

/**
 * Get "N" from "EvtEnableCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N".
 */
static inline uint32_t getEvtEnableCmdN(void* p)
{
  EvtEnableCmd_t* t;
  t = (EvtEnableCmd_t*)p;
  return __builtin_bswap32(t->N);
}

/**
 * Set "N" in "EvtEnableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of "N" to be set in packet.
 */
static inline void setEvtEnableCmdN(void* p, uint32_t N)
{
  EvtEnableCmd_t* t;
  t = (EvtEnableCmd_t*)p;
  t->N = __builtin_bswap32(N);
}

/**
 * Get "EventId" from "EvtEnableCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "EventId".
 */
static inline uint8_t getEvtEnableCmdEventId(void* p)
{
  EvtEnableCmd_t* t;
  t = (EvtEnableCmd_t*)p;
  return t->EventId;
}

/**
 * Set "EventId" in "EvtEnableCmd" packet.
 * \param p Pointer to the packet.
 * \param EventId Value of "EventId" to be set in packet.
 */
static inline void setEvtEnableCmdEventId(void* p, uint8_t EventId)
{
  EvtEnableCmd_t* t;
  t = (EvtEnableCmd_t*)p;
  t->EventId = EventId;
}

/**
 * Get "N" from "EvtDisableCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N".
 */
static inline uint32_t getEvtDisableCmdN(void* p)
{
  EvtDisableCmd_t* t;
  t = (EvtDisableCmd_t*)p;
  return __builtin_bswap32(t->N);
}

/**
 * Set "N" in "EvtDisableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of "N" to be set in packet.
 */
static inline void setEvtDisableCmdN(void* p, uint32_t N)
{
  EvtDisableCmd_t* t;
  t = (EvtDisableCmd_t*)p;
  t->N = __builtin_bswap32(N);
}

/**
 * Get "EventId" from "EvtDisableCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "EventId".
 */
static inline uint8_t getEvtDisableCmdEventId(void* p)
{
  EvtDisableCmd_t* t;
  t = (EvtDisableCmd_t*)p;
  return t->EventId;
}

/**
 * Set "EventId" in "EvtDisableCmd" packet.
 * \param p Pointer to the packet.
 * \param EventId Value of "EventId" to be set in packet.
 */
static inline void setEvtDisableCmdEventId(void* p, uint8_t EventId)
{
  EvtDisableCmd_t* t;
  t = (EvtDisableCmd_t*)p;
  t->EventId = EventId;
}

/**
 * Get "N" from "EvtRepDisabledRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "N".
 */
static inline uint32_t getEvtRepDisabledRepN(void* p)
{
  EvtRepDisabledRep_t* t;
  t = (EvtRepDisabledRep_t*)p;
  return __builtin_bswap32(t->N);
}

/**
 * Set "N" in "EvtRepDisabledRep" packet.
 * \param p Pointer to the packet.
 * \param N Value of "N" to be set in packet.
 */
static inline void setEvtRepDisabledRepN(void* p, uint32_t N)
{
  EvtRepDisabledRep_t* t;
  t = (EvtRepDisabledRep_t*)p;
  t->N = __builtin_bswap32(N);
}

/**
 * Get "EventId" from "EvtRepDisabledRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "EventId".
 */
static inline uint8_t getEvtRepDisabledRepEventId(void* p)
{
  EvtRepDisabledRep_t* t;
  t = (EvtRepDisabledRep_t*)p;
  return t->EventId;
}

/**
 * Set "EventId" in "EvtRepDisabledRep" packet.
 * \param p Pointer to the packet.
 * \param EventId Value of "EventId" to be set in packet.
 */
static inline void setEvtRepDisabledRepEventId(void* p, uint8_t EventId)
{
  EvtRepDisabledRep_t* t;
  t = (EvtRepDisabledRep_t*)p;
  t->EventId = EventId;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSPKTSERVEVT_H */
