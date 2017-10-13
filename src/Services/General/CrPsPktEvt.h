/**
 * \file
 *
 * Interface for accessing fields in packets of service "Evt".
 *
 * \note This file was generated on 2017-09-25 14:26:59
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSPKTEVT_H_
#define CRPSPKTEVT_H_

#include "CrPsDpTypes.h"

#include "CrPsPkt.h"
/**
 * Structure for EvtRep1
 */
typedef struct __attribute__((packed, aligned(1))) _EvtRep1_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Event Definition ID (enumerated)
   */
  uint8_t EventD;
  
  /**
   * Auxiliary Data
   */
  uint32_t AuxData;
  
} EvtRep1_t;

/**
 * Structure for EvtRep2
 */
typedef struct __attribute__((packed, aligned(1))) _EvtRep2_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Event Definition ID (enumerated)
   */
  uint8_t EventD;
  
  /**
   * Auxiliary Data
   */
  uint32_t AuxData;
  
} EvtRep2_t;

/**
 * Structure for EvtRep3
 */
typedef struct __attribute__((packed, aligned(1))) _EvtRep3_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Event Definition ID (enumerated)
   */
  uint8_t EventD;
  
  /**
   * Auxiliary Data
   */
  uint32_t AuxData;
  
} EvtRep3_t;

/**
 * Structure for EvtRep4
 */
typedef struct __attribute__((packed, aligned(1))) _EvtRep4_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Event Definition ID (enumerated)
   */
  uint8_t EventD;
  
  /**
   * Auxiliary Data
   */
  uint32_t AuxData;
  
} EvtRep4_t;

/**
 * Structure for EvtEnableCmd
 */
typedef struct __attribute__((packed, aligned(1))) _EvtEnableCmd_t {
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
  uint8_t EventD;
  
} EvtEnableCmd_t;

/**
 * Structure for EvtDisableCmd
 */
typedef struct __attribute__((packed, aligned(1))) _EvtDisableCmd_t {
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
  uint8_t EventD;
  
} EvtDisableCmd_t;

/**
 * Structure for EvtRepDisabledCmd
 */
typedef struct __attribute__((packed, aligned(1))) _EvtRepDisabledCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

} EvtRepDisabledCmd_t;

/**
 * Structure for EvtRepDisabledRep
 */
typedef struct __attribute__((packed, aligned(1))) _EvtRepDisabledRep_t {
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
  uint8_t EventD;
  
} EvtRepDisabledRep_t;

/**
 * Get "EventD" from "EvtRep1" packet.
 * \param p Pointer to the packet.
 * \return Value of "EventD".
 */
static inline uint8_t getEvtRep1EventD(void* p)
{
  EvtRep1_t* t;
  t = (EvtRep1_t*)p;
  return t->EventD;
}

/**
 * Set "EventD" in "EvtRep1" packet.
 * \param p Pointer to the packet.
 * \param EventD Value of "EventD" to be set in packet.
 */
static inline void setEvtRep1EventD(void* p, uint8_t EventD)
{
  EvtRep1_t* t;
  t = (EvtRep1_t*)p;
  t->EventD = EventD;
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
  return t->AuxData;
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
  t->AuxData = AuxData;
}

/**
 * Get "EventD" from "EvtRep2" packet.
 * \param p Pointer to the packet.
 * \return Value of "EventD".
 */
static inline uint8_t getEvtRep2EventD(void* p)
{
  EvtRep2_t* t;
  t = (EvtRep2_t*)p;
  return t->EventD;
}

/**
 * Set "EventD" in "EvtRep2" packet.
 * \param p Pointer to the packet.
 * \param EventD Value of "EventD" to be set in packet.
 */
static inline void setEvtRep2EventD(void* p, uint8_t EventD)
{
  EvtRep2_t* t;
  t = (EvtRep2_t*)p;
  t->EventD = EventD;
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
  return t->AuxData;
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
  t->AuxData = AuxData;
}

/**
 * Get "EventD" from "EvtRep3" packet.
 * \param p Pointer to the packet.
 * \return Value of "EventD".
 */
static inline uint8_t getEvtRep3EventD(void* p)
{
  EvtRep3_t* t;
  t = (EvtRep3_t*)p;
  return t->EventD;
}

/**
 * Set "EventD" in "EvtRep3" packet.
 * \param p Pointer to the packet.
 * \param EventD Value of "EventD" to be set in packet.
 */
static inline void setEvtRep3EventD(void* p, uint8_t EventD)
{
  EvtRep3_t* t;
  t = (EvtRep3_t*)p;
  t->EventD = EventD;
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
  return t->AuxData;
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
  t->AuxData = AuxData;
}

/**
 * Get "EventD" from "EvtRep4" packet.
 * \param p Pointer to the packet.
 * \return Value of "EventD".
 */
static inline uint8_t getEvtRep4EventD(void* p)
{
  EvtRep4_t* t;
  t = (EvtRep4_t*)p;
  return t->EventD;
}

/**
 * Set "EventD" in "EvtRep4" packet.
 * \param p Pointer to the packet.
 * \param EventD Value of "EventD" to be set in packet.
 */
static inline void setEvtRep4EventD(void* p, uint8_t EventD)
{
  EvtRep4_t* t;
  t = (EvtRep4_t*)p;
  t->EventD = EventD;
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
  return t->AuxData;
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
  t->AuxData = AuxData;
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
  return t->N;
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
  t->N = N;
}

/**
 * Get "EventD" from "EvtEnableCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "EventD".
 */
static inline uint8_t getEvtEnableCmdEventD(void* p)
{
  EvtEnableCmd_t* t;
  t = (EvtEnableCmd_t*)p;
  return t->EventD;
}

/**
 * Set "EventD" in "EvtEnableCmd" packet.
 * \param p Pointer to the packet.
 * \param EventD Value of "EventD" to be set in packet.
 */
static inline void setEvtEnableCmdEventD(void* p, uint8_t EventD)
{
  EvtEnableCmd_t* t;
  t = (EvtEnableCmd_t*)p;
  t->EventD = EventD;
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
  return t->N;
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
  t->N = N;
}

/**
 * Get "EventD" from "EvtDisableCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "EventD".
 */
static inline uint8_t getEvtDisableCmdEventD(void* p)
{
  EvtDisableCmd_t* t;
  t = (EvtDisableCmd_t*)p;
  return t->EventD;
}

/**
 * Set "EventD" in "EvtDisableCmd" packet.
 * \param p Pointer to the packet.
 * \param EventD Value of "EventD" to be set in packet.
 */
static inline void setEvtDisableCmdEventD(void* p, uint8_t EventD)
{
  EvtDisableCmd_t* t;
  t = (EvtDisableCmd_t*)p;
  t->EventD = EventD;
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
  return t->N;
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
  t->N = N;
}

/**
 * Get "EventD" from "EvtRepDisabledRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "EventD".
 */
static inline uint8_t getEvtRepDisabledRepEventD(void* p)
{
  EvtRepDisabledRep_t* t;
  t = (EvtRepDisabledRep_t*)p;
  return t->EventD;
}

/**
 * Set "EventD" in "EvtRepDisabledRep" packet.
 * \param p Pointer to the packet.
 * \param EventD Value of "EventD" to be set in packet.
 */
static inline void setEvtRepDisabledRepEventD(void* p, uint8_t EventD)
{
  EvtRepDisabledRep_t* t;
  t = (EvtRepDisabledRep_t*)p;
  t->EventD = EventD;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSPKTEVT_H */
