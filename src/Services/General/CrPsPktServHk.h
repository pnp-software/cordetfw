/**
 * \file
 *
 * Interface for accessing fields in packets of service "ServHk".
 *
 * \note This file was generated on 2017-10-18 18:45:26
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSPKTSERVHK_H_
#define CRPSPKTSERVHK_H_

#include "CrPsDpTypes.h"

#include "CrPsPkt.h"
/**
 * Structure for HkCreateCmd
 */
typedef struct __attribute__((packed)) _HkCreateCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * Housekeeping or Diagnostic Parameter Report Structure ID (enumerated)
   */
  uint8_t RepStrucId;
  
  /**
   * Collection interval uint
   */
  uint32_t CollectionInterval;
  
  /**
   * ?? N1
   */
  uint32_t N1;
  
  /**
   * Parameter ID (repeated N1 Times)
   */
  uint16_t N1ParamId;
  
  /**
   * ?? NFA
   */
  uint32_t NFA;
  
  /**
   * Super Commutated Sample Repetition Number (repeated NFA times)
   */
  uint32_t SCSampleRepNum;
  
  /**
   * ?? N2
   */
  uint32_t N2;
  
  /**
   * Parameter ID (repeated NFA times) and (repeated N2 times)
   */
  uint16_t N2ParamId;
  
} HkCreateCmd_t ;

/**
 * Structure for HkDeleteCmd
 */
typedef struct __attribute__((packed)) _HkDeleteCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * ?? N
   */
  uint32_t N;
  
  /**
   * Housekeeping or Diagnostic Parameter Report Structure ID (enumerated)
   */
  uint8_t RepStrucId;
  
} HkDeleteCmd_t ;

/**
 * Structure for HkEnableCmd
 */
typedef struct __attribute__((packed)) _HkEnableCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * ?? N
   */
  uint32_t N;
  
  /**
   * Housekeeping or Diagnostic Parameter Report Structure ID (enumerated)
   */
  uint8_t RepStrucId;
  
} HkEnableCmd_t ;

/**
 * Structure for HkDisableCmd
 */
typedef struct __attribute__((packed)) _HkDisableCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * ?? N
   */
  uint32_t N;
  
  /**
   * Housekeeping or Diagnostic Parameter Report Structure ID (enumerated)
   */
  uint8_t RepStrucId;
  
} HkDisableCmd_t ;

/**
 * Structure for HkRepStructCmd
 */
typedef struct __attribute__((packed)) _HkRepStructCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * ?? N
   */
  uint32_t N;
  
  /**
   * Housekeeping or Diagnostic Parameter Report Structure ID (enumerated)
   */
  uint8_t RepStrucId;
  
} HkRepStructCmd_t ;

/**
 * Structure for HkRepStructRep
 */
typedef struct __attribute__((packed)) _HkRepStructRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Housekeeping or Diagnostic Parameter Report Structure ID (enumerated)
   */
  uint8_t RepStrucId;
  
  /**
   * Periodic Generation Action Status (enumerated)
   */
  uint8_t PeriodicGenActionStatus;
  
  /**
   * Collection interval uint
   */
  uint32_t CollectionInterval;
  
  /**
   * ?? N1
   */
  uint32_t N1;
  
  /**
   * Parameter ID (repeated N1 Times)
   */
  uint16_t N1ParamId;
  
  /**
   * ?? NFA
   */
  uint32_t NFA;
  
  /**
   * Super Commutated Sample Repetition Number (repeated NFA times)
   */
  uint32_t SCSampleRepNum;
  
  /**
   * ?? N2
   */
  uint32_t N2;
  
  /**
   * Parameter ID (repeated NFA times) and (repeated N2 times)
   */
  uint16_t N2ParamId;
  
} HkRepStructRep_t ;

/**
 * Structure for HkRep
 */
typedef struct __attribute__((packed)) _HkRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Housekeeping or Diagnostic Parameter Report Structure ID (enumerated)
   */
  uint8_t RepStrucId;
  
  /**
   * Parameter Value
   */
  uint32_t ParamVal;
  
} HkRep_t ;

/**
 * Structure for HkOneShotCmd
 */
typedef struct __attribute__((packed)) _HkOneShotCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * ?? N
   */
  uint32_t N;
  
  /**
   * Housekeeping or Diagnostic Parameter Report Structure ID (enumerated)
   */
  uint8_t RepStrucId;
  
} HkOneShotCmd_t ;

/**
 * Get "RepStrucId" from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "RepStrucId".
 */
static inline uint8_t getHkCreateCmdRepStrucId(void* p)
{
  HkCreateCmd_t* t;
  t = (HkCreateCmd_t*)p;
  return t->RepStrucId;
}

/**
 * Set "RepStrucId" in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param RepStrucId Value of "RepStrucId" to be set in packet.
 */
static inline void setHkCreateCmdRepStrucId(void* p, uint8_t RepStrucId)
{
  HkCreateCmd_t* t;
  t = (HkCreateCmd_t*)p;
  t->RepStrucId = RepStrucId;
}

/**
 * Get "CollectionInterval" from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "CollectionInterval".
 */
static inline uint32_t getHkCreateCmdCollectionInterval(void* p)
{
  HkCreateCmd_t* t;
  t = (HkCreateCmd_t*)p;
  return __builtin_bswap32(t->CollectionInterval);
}

/**
 * Set "CollectionInterval" in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param CollectionInterval Value of "CollectionInterval" to be set in
 * packet.
 */
static inline void setHkCreateCmdCollectionInterval(void* p, uint32_t CollectionInterval)
{
  HkCreateCmd_t* t;
  t = (HkCreateCmd_t*)p;
  t->CollectionInterval = __builtin_bswap32(CollectionInterval);
}

/**
 * Get "N1" from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N1".
 */
static inline uint32_t getHkCreateCmdN1(void* p)
{
  HkCreateCmd_t* t;
  t = (HkCreateCmd_t*)p;
  return __builtin_bswap32(t->N1);
}

/**
 * Set "N1" in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param N1 Value of "N1" to be set in packet.
 */
static inline void setHkCreateCmdN1(void* p, uint32_t N1)
{
  HkCreateCmd_t* t;
  t = (HkCreateCmd_t*)p;
  t->N1 = __builtin_bswap32(N1);
}

/**
 * Get "N" from "HkDeleteCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N".
 */
static inline uint32_t getHkDeleteCmdN(void* p)
{
  HkDeleteCmd_t* t;
  t = (HkDeleteCmd_t*)p;
  return __builtin_bswap32(t->N);
}

/**
 * Set "N" in "HkDeleteCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of "N" to be set in packet.
 */
static inline void setHkDeleteCmdN(void* p, uint32_t N)
{
  HkDeleteCmd_t* t;
  t = (HkDeleteCmd_t*)p;
  t->N = __builtin_bswap32(N);
}

/**
 * Get "N" from "HkEnableCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N".
 */
static inline uint32_t getHkEnableCmdN(void* p)
{
  HkEnableCmd_t* t;
  t = (HkEnableCmd_t*)p;
  return __builtin_bswap32(t->N);
}

/**
 * Set "N" in "HkEnableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of "N" to be set in packet.
 */
static inline void setHkEnableCmdN(void* p, uint32_t N)
{
  HkEnableCmd_t* t;
  t = (HkEnableCmd_t*)p;
  t->N = __builtin_bswap32(N);
}

/**
 * Get "N" from "HkDisableCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N".
 */
static inline uint32_t getHkDisableCmdN(void* p)
{
  HkDisableCmd_t* t;
  t = (HkDisableCmd_t*)p;
  return __builtin_bswap32(t->N);
}

/**
 * Set "N" in "HkDisableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of "N" to be set in packet.
 */
static inline void setHkDisableCmdN(void* p, uint32_t N)
{
  HkDisableCmd_t* t;
  t = (HkDisableCmd_t*)p;
  t->N = __builtin_bswap32(N);
}

/**
 * Get "N" from "HkRepStructCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N".
 */
static inline uint32_t getHkRepStructCmdN(void* p)
{
  HkRepStructCmd_t* t;
  t = (HkRepStructCmd_t*)p;
  return __builtin_bswap32(t->N);
}

/**
 * Set "N" in "HkRepStructCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of "N" to be set in packet.
 */
static inline void setHkRepStructCmdN(void* p, uint32_t N)
{
  HkRepStructCmd_t* t;
  t = (HkRepStructCmd_t*)p;
  t->N = __builtin_bswap32(N);
}

/**
 * Get "RepStrucId" from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "RepStrucId".
 */
static inline uint8_t getHkRepStructRepRepStrucId(void* p)
{
  HkRepStructRep_t* t;
  t = (HkRepStructRep_t*)p;
  return t->RepStrucId;
}

/**
 * Set "RepStrucId" in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param RepStrucId Value of "RepStrucId" to be set in packet.
 */
static inline void setHkRepStructRepRepStrucId(void* p, uint8_t RepStrucId)
{
  HkRepStructRep_t* t;
  t = (HkRepStructRep_t*)p;
  t->RepStrucId = RepStrucId;
}

/**
 * Get "PeriodicGenActionStatus" from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PeriodicGenActionStatus".
 */
static inline uint8_t getHkRepStructRepPeriodicGenActionStatus(void* p)
{
  HkRepStructRep_t* t;
  t = (HkRepStructRep_t*)p;
  return t->PeriodicGenActionStatus;
}

/**
 * Set "PeriodicGenActionStatus" in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param PeriodicGenActionStatus Value of "PeriodicGenActionStatus" to be set
 * in packet.
 */
static inline void setHkRepStructRepPeriodicGenActionStatus(void* p, uint8_t PeriodicGenActionStatus)
{
  HkRepStructRep_t* t;
  t = (HkRepStructRep_t*)p;
  t->PeriodicGenActionStatus = PeriodicGenActionStatus;
}

/**
 * Get "CollectionInterval" from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "CollectionInterval".
 */
static inline uint32_t getHkRepStructRepCollectionInterval(void* p)
{
  HkRepStructRep_t* t;
  t = (HkRepStructRep_t*)p;
  return __builtin_bswap32(t->CollectionInterval);
}

/**
 * Set "CollectionInterval" in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param CollectionInterval Value of "CollectionInterval" to be set in
 * packet.
 */
static inline void setHkRepStructRepCollectionInterval(void* p, uint32_t CollectionInterval)
{
  HkRepStructRep_t* t;
  t = (HkRepStructRep_t*)p;
  t->CollectionInterval = __builtin_bswap32(CollectionInterval);
}

/**
 * Get "N1" from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "N1".
 */
static inline uint32_t getHkRepStructRepN1(void* p)
{
  HkRepStructRep_t* t;
  t = (HkRepStructRep_t*)p;
  return __builtin_bswap32(t->N1);
}

/**
 * Set "N1" in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param N1 Value of "N1" to be set in packet.
 */
static inline void setHkRepStructRepN1(void* p, uint32_t N1)
{
  HkRepStructRep_t* t;
  t = (HkRepStructRep_t*)p;
  t->N1 = __builtin_bswap32(N1);
}

/**
 * Get "RepStrucId" from "HkRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "RepStrucId".
 */
static inline uint8_t getHkRepRepStrucId(void* p)
{
  HkRep_t* t;
  t = (HkRep_t*)p;
  return t->RepStrucId;
}

/**
 * Set "RepStrucId" in "HkRep" packet.
 * \param p Pointer to the packet.
 * \param RepStrucId Value of "RepStrucId" to be set in packet.
 */
static inline void setHkRepRepStrucId(void* p, uint8_t RepStrucId)
{
  HkRep_t* t;
  t = (HkRep_t*)p;
  t->RepStrucId = RepStrucId;
}

/**
 * Get "ParamVal" from "HkRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "ParamVal".
 */
static inline uint32_t getHkRepParamVal(void* p)
{
  HkRep_t* t;
  t = (HkRep_t*)p;
  return __builtin_bswap32(t->ParamVal);
}

/**
 * Set "ParamVal" in "HkRep" packet.
 * \param p Pointer to the packet.
 * \param ParamVal Value of "ParamVal" to be set in packet.
 */
static inline void setHkRepParamVal(void* p, uint32_t ParamVal)
{
  HkRep_t* t;
  t = (HkRep_t*)p;
  t->ParamVal = __builtin_bswap32(ParamVal);
}

/**
 * Get "N" from "HkOneShotCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N".
 */
static inline uint32_t getHkOneShotCmdN(void* p)
{
  HkOneShotCmd_t* t;
  t = (HkOneShotCmd_t*)p;
  return __builtin_bswap32(t->N);
}

/**
 * Set "N" in "HkOneShotCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of "N" to be set in packet.
 */
static inline void setHkOneShotCmdN(void* p, uint32_t N)
{
  HkOneShotCmd_t* t;
  t = (HkOneShotCmd_t*)p;
  t->N = __builtin_bswap32(N);
}



/*----------------------------------------------------------------------------*/
#endif /* CRPSPKTSERVHK_H */
