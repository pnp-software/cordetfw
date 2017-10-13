/**
 * \file
 *
 * Interface for accessing fields in packets of service "Hk".
 *
 * \note This file was generated on 2017-09-25 14:26:59
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSPKTHK_H_
#define CRPSPKTHK_H_

#include "CrPsDpTypes.h"

#include "CrPsPkt.h"
/**
 * Structure for HkCreateHkParCmd
 */
typedef struct __attribute__((packed, aligned(1))) _HkCreateHkParCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * Housekeeping Parameter Report Structure ID (enumerated)
   */
  uint8_t HKRepStrucID;
  
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
  uint8_t N1ParamID;
  
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
  uint8_t N2ParamID;
  
} HkCreateHkParCmd_t;

/**
 * Structure for HkCreateDiagParCmd
 */
typedef struct __attribute__((packed, aligned(1))) _HkCreateDiagParCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * Diagnostic Parameter Report Structure ID (enumerated)
   */
  uint8_t DiagRepStrucID;
  
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
  uint8_t N1ParamID;
  
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
  uint8_t N2ParamID;
  
} HkCreateDiagParCmd_t;

/**
 * Structure for HkDeleteHkParCmd
 */
typedef struct __attribute__((packed, aligned(1))) _HkDeleteHkParCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * ?? N
   */
  uint32_t N;
  
  /**
   * Housekeeping Parameter Report Structure ID (enumerated)
   */
  uint8_t HKRepStrucID;
  
} HkDeleteHkParCmd_t;

/**
 * Structure for HkDeleteDiagParCmd
 */
typedef struct __attribute__((packed, aligned(1))) _HkDeleteDiagParCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * ?? N
   */
  uint32_t N;
  
  /**
   * Diagnostic Parameter Report Structure ID (enumerated)
   */
  uint8_t DiagRepStrucID;
  
} HkDeleteDiagParCmd_t;

/**
 * Structure for HkEnableHkParCmd
 */
typedef struct __attribute__((packed, aligned(1))) _HkEnableHkParCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * ?? N
   */
  uint32_t N;
  
  /**
   * Housekeeping Parameter Report Structure ID (enumerated)
   */
  uint8_t HKRepStrucID;
  
} HkEnableHkParCmd_t;

/**
 * Structure for HkDisableHkParCmd
 */
typedef struct __attribute__((packed, aligned(1))) _HkDisableHkParCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * ?? N
   */
  uint32_t N;
  
  /**
   * Housekeeping Parameter Report Structure ID (enumerated)
   */
  uint8_t HKRepStrucID;
  
} HkDisableHkParCmd_t;

/**
 * Structure for HkEnableDiagParCmd
 */
typedef struct __attribute__((packed, aligned(1))) _HkEnableDiagParCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * ?? N
   */
  uint32_t N;
  
  /**
   * Diagnostic Parameter Report Structure ID (enumerated)
   */
  uint8_t DiagRepStrucID;
  
} HkEnableDiagParCmd_t;

/**
 * Structure for HkDisableDiagParCmd
 */
typedef struct __attribute__((packed, aligned(1))) _HkDisableDiagParCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * ?? N
   */
  uint32_t N;
  
  /**
   * Diagnostic Parameter Report Structure ID (enumerated)
   */
  uint8_t DiagRepStrucID;
  
} HkDisableDiagParCmd_t;

/**
 * Structure for HkRepStructHkParCmd
 */
typedef struct __attribute__((packed, aligned(1))) _HkRepStructHkParCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * ?? N
   */
  uint32_t N;
  
  /**
   * Housekeeping Parameter Report Structure ID (enumerated)
   */
  uint8_t HKRepStrucID;
  
} HkRepStructHkParCmd_t;

/**
 * Structure for HkRepStructHkParRep
 */
typedef struct __attribute__((packed, aligned(1))) _HkRepStructHkParRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Housekeeping Parameter Report Structure ID (enumerated)
   */
  uint8_t HKRepStrucID;
  
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
  uint8_t N1ParamID;
  
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
  uint8_t N2ParamID;
  
} HkRepStructHkParRep_t;

/**
 * Structure for HkRepStructDiagParCmd
 */
typedef struct __attribute__((packed, aligned(1))) _HkRepStructDiagParCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * ?? N
   */
  uint32_t N;
  
  /**
   * Diagnostic Parameter Report Structure ID (enumerated)
   */
  uint8_t DiagRepStrucID;
  
} HkRepStructDiagParCmd_t;

/**
 * Structure for HkRepStructDiagParRep
 */
typedef struct __attribute__((packed, aligned(1))) _HkRepStructDiagParRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Diagnostic Parameter Report Structure ID (enumerated)
   */
  uint8_t DiagRepStrucID;
  
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
  uint8_t N1ParamID;
  
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
  uint8_t N2ParamID;
  
} HkRepStructDiagParRep_t;

/**
 * Structure for HkOneShotHkRep
 */
typedef struct __attribute__((packed, aligned(1))) _HkOneShotHkRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Housekeeping Parameter Report Structure ID (enumerated)
   */
  uint8_t HKRepStrucID;
  
  /**
   * Parameter Value
   */
  uint32_t ParamVal;
  
} HkOneShotHkRep_t;

/**
 * Structure for HkOneShotDiagRep
 */
typedef struct __attribute__((packed, aligned(1))) _HkOneShotDiagRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Diagnostic Parameter Report Structure ID (enumerated)
   */
  uint8_t DiagRepStrucID;
  
  /**
   * Parameter Value
   */
  uint32_t ParamVal;
  
} HkOneShotDiagRep_t;

/**
 * Structure for HkOneShotHkCmd
 */
typedef struct __attribute__((packed, aligned(1))) _HkOneShotHkCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * ?? N
   */
  uint32_t N;
  
  /**
   * Housekeeping Parameter Report Structure ID (enumerated)
   */
  uint8_t HKRepStrucID;
  
} HkOneShotHkCmd_t;

/**
 * Structure for HkOneShotDiagCmd
 */
typedef struct __attribute__((packed, aligned(1))) _HkOneShotDiagCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * ?? N
   */
  uint32_t N;
  
  /**
   * Diagnostic Parameter Report Structure ID (enumerated)
   */
  uint8_t DiagRepStrucID;
  
} HkOneShotDiagCmd_t;

/**
 * Get "HKRepStrucID" from "HkCreateHkParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "HKRepStrucID".
 */
static inline uint8_t getHkCreateHkParCmdHKRepStrucID(void* p)
{
  HkCreateHkParCmd_t* t;
  t = (HkCreateHkParCmd_t*)p;
  return t->HKRepStrucID;
}

/**
 * Set "HKRepStrucID" in "HkCreateHkParCmd" packet.
 * \param p Pointer to the packet.
 * \param HKRepStrucID Value of "HKRepStrucID" to be set in packet.
 */
static inline void setHkCreateHkParCmdHKRepStrucID(void* p, uint8_t HKRepStrucID)
{
  HkCreateHkParCmd_t* t;
  t = (HkCreateHkParCmd_t*)p;
  t->HKRepStrucID = HKRepStrucID;
}

/**
 * Get "CollectionInterval" from "HkCreateHkParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "CollectionInterval".
 */
static inline uint32_t getHkCreateHkParCmdCollectionInterval(void* p)
{
  HkCreateHkParCmd_t* t;
  t = (HkCreateHkParCmd_t*)p;
  return t->CollectionInterval;
}

/**
 * Set "CollectionInterval" in "HkCreateHkParCmd" packet.
 * \param p Pointer to the packet.
 * \param CollectionInterval Value of "CollectionInterval" to be set in
 * packet.
 */
static inline void setHkCreateHkParCmdCollectionInterval(void* p, uint32_t CollectionInterval)
{
  HkCreateHkParCmd_t* t;
  t = (HkCreateHkParCmd_t*)p;
  t->CollectionInterval = CollectionInterval;
}

/**
 * Get "N1" from "HkCreateHkParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N1".
 */
static inline uint32_t getHkCreateHkParCmdN1(void* p)
{
  HkCreateHkParCmd_t* t;
  t = (HkCreateHkParCmd_t*)p;
  return t->N1;
}

/**
 * Set "N1" in "HkCreateHkParCmd" packet.
 * \param p Pointer to the packet.
 * \param N1 Value of "N1" to be set in packet.
 */
static inline void setHkCreateHkParCmdN1(void* p, uint32_t N1)
{
  HkCreateHkParCmd_t* t;
  t = (HkCreateHkParCmd_t*)p;
  t->N1 = N1;
}

/**
 * Get "N1ParamID" from "HkCreateHkParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N1ParamID".
 */
static inline uint8_t getHkCreateHkParCmdN1ParamID(void* p)
{
  HkCreateHkParCmd_t* t;
  t = (HkCreateHkParCmd_t*)p;
  return t->N1ParamID;
}

/**
 * Set "N1ParamID" in "HkCreateHkParCmd" packet.
 * \param p Pointer to the packet.
 * \param N1ParamID Value of "N1ParamID" to be set in packet.
 */
static inline void setHkCreateHkParCmdN1ParamID(void* p, uint8_t N1ParamID)
{
  HkCreateHkParCmd_t* t;
  t = (HkCreateHkParCmd_t*)p;
  t->N1ParamID = N1ParamID;
}

/**
 * Get "NFA" from "HkCreateHkParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "NFA".
 */
static inline uint32_t getHkCreateHkParCmdNFA(void* p)
{
  HkCreateHkParCmd_t* t;
  t = (HkCreateHkParCmd_t*)p;
  return t->NFA;
}

/**
 * Set "NFA" in "HkCreateHkParCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of "NFA" to be set in packet.
 */
static inline void setHkCreateHkParCmdNFA(void* p, uint32_t NFA)
{
  HkCreateHkParCmd_t* t;
  t = (HkCreateHkParCmd_t*)p;
  t->NFA = NFA;
}

/**
 * Get "SCSampleRepNum" from "HkCreateHkParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "SCSampleRepNum".
 */
static inline uint32_t getHkCreateHkParCmdSCSampleRepNum(void* p)
{
  HkCreateHkParCmd_t* t;
  t = (HkCreateHkParCmd_t*)p;
  return t->SCSampleRepNum;
}

/**
 * Set "SCSampleRepNum" in "HkCreateHkParCmd" packet.
 * \param p Pointer to the packet.
 * \param SCSampleRepNum Value of "SCSampleRepNum" to be set in packet.
 */
static inline void setHkCreateHkParCmdSCSampleRepNum(void* p, uint32_t SCSampleRepNum)
{
  HkCreateHkParCmd_t* t;
  t = (HkCreateHkParCmd_t*)p;
  t->SCSampleRepNum = SCSampleRepNum;
}

/**
 * Get "N2" from "HkCreateHkParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N2".
 */
static inline uint32_t getHkCreateHkParCmdN2(void* p)
{
  HkCreateHkParCmd_t* t;
  t = (HkCreateHkParCmd_t*)p;
  return t->N2;
}

/**
 * Set "N2" in "HkCreateHkParCmd" packet.
 * \param p Pointer to the packet.
 * \param N2 Value of "N2" to be set in packet.
 */
static inline void setHkCreateHkParCmdN2(void* p, uint32_t N2)
{
  HkCreateHkParCmd_t* t;
  t = (HkCreateHkParCmd_t*)p;
  t->N2 = N2;
}

/**
 * Get "N2ParamID" from "HkCreateHkParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N2ParamID".
 */
static inline uint8_t getHkCreateHkParCmdN2ParamID(void* p)
{
  HkCreateHkParCmd_t* t;
  t = (HkCreateHkParCmd_t*)p;
  return t->N2ParamID;
}

/**
 * Set "N2ParamID" in "HkCreateHkParCmd" packet.
 * \param p Pointer to the packet.
 * \param N2ParamID Value of "N2ParamID" to be set in packet.
 */
static inline void setHkCreateHkParCmdN2ParamID(void* p, uint8_t N2ParamID)
{
  HkCreateHkParCmd_t* t;
  t = (HkCreateHkParCmd_t*)p;
  t->N2ParamID = N2ParamID;
}

/**
 * Get "DiagRepStrucID" from "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "DiagRepStrucID".
 */
static inline uint8_t getHkCreateDiagParCmdDiagRepStrucID(void* p)
{
  HkCreateDiagParCmd_t* t;
  t = (HkCreateDiagParCmd_t*)p;
  return t->DiagRepStrucID;
}

/**
 * Set "DiagRepStrucID" in "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \param DiagRepStrucID Value of "DiagRepStrucID" to be set in packet.
 */
static inline void setHkCreateDiagParCmdDiagRepStrucID(void* p, uint8_t DiagRepStrucID)
{
  HkCreateDiagParCmd_t* t;
  t = (HkCreateDiagParCmd_t*)p;
  t->DiagRepStrucID = DiagRepStrucID;
}

/**
 * Get "CollectionInterval" from "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "CollectionInterval".
 */
static inline uint32_t getHkCreateDiagParCmdCollectionInterval(void* p)
{
  HkCreateDiagParCmd_t* t;
  t = (HkCreateDiagParCmd_t*)p;
  return t->CollectionInterval;
}

/**
 * Set "CollectionInterval" in "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \param CollectionInterval Value of "CollectionInterval" to be set in
 * packet.
 */
static inline void setHkCreateDiagParCmdCollectionInterval(void* p, uint32_t CollectionInterval)
{
  HkCreateDiagParCmd_t* t;
  t = (HkCreateDiagParCmd_t*)p;
  t->CollectionInterval = CollectionInterval;
}

/**
 * Get "N1" from "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N1".
 */
static inline uint32_t getHkCreateDiagParCmdN1(void* p)
{
  HkCreateDiagParCmd_t* t;
  t = (HkCreateDiagParCmd_t*)p;
  return t->N1;
}

/**
 * Set "N1" in "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \param N1 Value of "N1" to be set in packet.
 */
static inline void setHkCreateDiagParCmdN1(void* p, uint32_t N1)
{
  HkCreateDiagParCmd_t* t;
  t = (HkCreateDiagParCmd_t*)p;
  t->N1 = N1;
}

/**
 * Get "N1ParamID" from "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N1ParamID".
 */
static inline uint8_t getHkCreateDiagParCmdN1ParamID(void* p)
{
  HkCreateDiagParCmd_t* t;
  t = (HkCreateDiagParCmd_t*)p;
  return t->N1ParamID;
}

/**
 * Set "N1ParamID" in "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \param N1ParamID Value of "N1ParamID" to be set in packet.
 */
static inline void setHkCreateDiagParCmdN1ParamID(void* p, uint8_t N1ParamID)
{
  HkCreateDiagParCmd_t* t;
  t = (HkCreateDiagParCmd_t*)p;
  t->N1ParamID = N1ParamID;
}

/**
 * Get "NFA" from "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "NFA".
 */
static inline uint32_t getHkCreateDiagParCmdNFA(void* p)
{
  HkCreateDiagParCmd_t* t;
  t = (HkCreateDiagParCmd_t*)p;
  return t->NFA;
}

/**
 * Set "NFA" in "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of "NFA" to be set in packet.
 */
static inline void setHkCreateDiagParCmdNFA(void* p, uint32_t NFA)
{
  HkCreateDiagParCmd_t* t;
  t = (HkCreateDiagParCmd_t*)p;
  t->NFA = NFA;
}

/**
 * Get "SCSampleRepNum" from "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "SCSampleRepNum".
 */
static inline uint32_t getHkCreateDiagParCmdSCSampleRepNum(void* p)
{
  HkCreateDiagParCmd_t* t;
  t = (HkCreateDiagParCmd_t*)p;
  return t->SCSampleRepNum;
}

/**
 * Set "SCSampleRepNum" in "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \param SCSampleRepNum Value of "SCSampleRepNum" to be set in packet.
 */
static inline void setHkCreateDiagParCmdSCSampleRepNum(void* p, uint32_t SCSampleRepNum)
{
  HkCreateDiagParCmd_t* t;
  t = (HkCreateDiagParCmd_t*)p;
  t->SCSampleRepNum = SCSampleRepNum;
}

/**
 * Get "N2" from "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N2".
 */
static inline uint32_t getHkCreateDiagParCmdN2(void* p)
{
  HkCreateDiagParCmd_t* t;
  t = (HkCreateDiagParCmd_t*)p;
  return t->N2;
}

/**
 * Set "N2" in "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \param N2 Value of "N2" to be set in packet.
 */
static inline void setHkCreateDiagParCmdN2(void* p, uint32_t N2)
{
  HkCreateDiagParCmd_t* t;
  t = (HkCreateDiagParCmd_t*)p;
  t->N2 = N2;
}

/**
 * Get "N2ParamID" from "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N2ParamID".
 */
static inline uint8_t getHkCreateDiagParCmdN2ParamID(void* p)
{
  HkCreateDiagParCmd_t* t;
  t = (HkCreateDiagParCmd_t*)p;
  return t->N2ParamID;
}

/**
 * Set "N2ParamID" in "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \param N2ParamID Value of "N2ParamID" to be set in packet.
 */
static inline void setHkCreateDiagParCmdN2ParamID(void* p, uint8_t N2ParamID)
{
  HkCreateDiagParCmd_t* t;
  t = (HkCreateDiagParCmd_t*)p;
  t->N2ParamID = N2ParamID;
}

/**
 * Get "N" from "HkDeleteHkParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N".
 */
static inline uint32_t getHkDeleteHkParCmdN(void* p)
{
  HkDeleteHkParCmd_t* t;
  t = (HkDeleteHkParCmd_t*)p;
  return t->N;
}

/**
 * Set "N" in "HkDeleteHkParCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of "N" to be set in packet.
 */
static inline void setHkDeleteHkParCmdN(void* p, uint32_t N)
{
  HkDeleteHkParCmd_t* t;
  t = (HkDeleteHkParCmd_t*)p;
  t->N = N;
}

/**
 * Get "HKRepStrucID" from "HkDeleteHkParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "HKRepStrucID".
 */
static inline uint8_t getHkDeleteHkParCmdHKRepStrucID(void* p)
{
  HkDeleteHkParCmd_t* t;
  t = (HkDeleteHkParCmd_t*)p;
  return t->HKRepStrucID;
}

/**
 * Set "HKRepStrucID" in "HkDeleteHkParCmd" packet.
 * \param p Pointer to the packet.
 * \param HKRepStrucID Value of "HKRepStrucID" to be set in packet.
 */
static inline void setHkDeleteHkParCmdHKRepStrucID(void* p, uint8_t HKRepStrucID)
{
  HkDeleteHkParCmd_t* t;
  t = (HkDeleteHkParCmd_t*)p;
  t->HKRepStrucID = HKRepStrucID;
}

/**
 * Get "N" from "HkDeleteDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N".
 */
static inline uint32_t getHkDeleteDiagParCmdN(void* p)
{
  HkDeleteDiagParCmd_t* t;
  t = (HkDeleteDiagParCmd_t*)p;
  return t->N;
}

/**
 * Set "N" in "HkDeleteDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of "N" to be set in packet.
 */
static inline void setHkDeleteDiagParCmdN(void* p, uint32_t N)
{
  HkDeleteDiagParCmd_t* t;
  t = (HkDeleteDiagParCmd_t*)p;
  t->N = N;
}

/**
 * Get "DiagRepStrucID" from "HkDeleteDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "DiagRepStrucID".
 */
static inline uint8_t getHkDeleteDiagParCmdDiagRepStrucID(void* p)
{
  HkDeleteDiagParCmd_t* t;
  t = (HkDeleteDiagParCmd_t*)p;
  return t->DiagRepStrucID;
}

/**
 * Set "DiagRepStrucID" in "HkDeleteDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \param DiagRepStrucID Value of "DiagRepStrucID" to be set in packet.
 */
static inline void setHkDeleteDiagParCmdDiagRepStrucID(void* p, uint8_t DiagRepStrucID)
{
  HkDeleteDiagParCmd_t* t;
  t = (HkDeleteDiagParCmd_t*)p;
  t->DiagRepStrucID = DiagRepStrucID;
}

/**
 * Get "N" from "HkEnableHkParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N".
 */
static inline uint32_t getHkEnableHkParCmdN(void* p)
{
  HkEnableHkParCmd_t* t;
  t = (HkEnableHkParCmd_t*)p;
  return t->N;
}

/**
 * Set "N" in "HkEnableHkParCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of "N" to be set in packet.
 */
static inline void setHkEnableHkParCmdN(void* p, uint32_t N)
{
  HkEnableHkParCmd_t* t;
  t = (HkEnableHkParCmd_t*)p;
  t->N = N;
}

/**
 * Get "HKRepStrucID" from "HkEnableHkParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "HKRepStrucID".
 */
static inline uint8_t getHkEnableHkParCmdHKRepStrucID(void* p)
{
  HkEnableHkParCmd_t* t;
  t = (HkEnableHkParCmd_t*)p;
  return t->HKRepStrucID;
}

/**
 * Set "HKRepStrucID" in "HkEnableHkParCmd" packet.
 * \param p Pointer to the packet.
 * \param HKRepStrucID Value of "HKRepStrucID" to be set in packet.
 */
static inline void setHkEnableHkParCmdHKRepStrucID(void* p, uint8_t HKRepStrucID)
{
  HkEnableHkParCmd_t* t;
  t = (HkEnableHkParCmd_t*)p;
  t->HKRepStrucID = HKRepStrucID;
}

/**
 * Get "N" from "HkDisableHkParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N".
 */
static inline uint32_t getHkDisableHkParCmdN(void* p)
{
  HkDisableHkParCmd_t* t;
  t = (HkDisableHkParCmd_t*)p;
  return t->N;
}

/**
 * Set "N" in "HkDisableHkParCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of "N" to be set in packet.
 */
static inline void setHkDisableHkParCmdN(void* p, uint32_t N)
{
  HkDisableHkParCmd_t* t;
  t = (HkDisableHkParCmd_t*)p;
  t->N = N;
}

/**
 * Get "HKRepStrucID" from "HkDisableHkParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "HKRepStrucID".
 */
static inline uint8_t getHkDisableHkParCmdHKRepStrucID(void* p)
{
  HkDisableHkParCmd_t* t;
  t = (HkDisableHkParCmd_t*)p;
  return t->HKRepStrucID;
}

/**
 * Set "HKRepStrucID" in "HkDisableHkParCmd" packet.
 * \param p Pointer to the packet.
 * \param HKRepStrucID Value of "HKRepStrucID" to be set in packet.
 */
static inline void setHkDisableHkParCmdHKRepStrucID(void* p, uint8_t HKRepStrucID)
{
  HkDisableHkParCmd_t* t;
  t = (HkDisableHkParCmd_t*)p;
  t->HKRepStrucID = HKRepStrucID;
}

/**
 * Get "N" from "HkEnableDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N".
 */
static inline uint32_t getHkEnableDiagParCmdN(void* p)
{
  HkEnableDiagParCmd_t* t;
  t = (HkEnableDiagParCmd_t*)p;
  return t->N;
}

/**
 * Set "N" in "HkEnableDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of "N" to be set in packet.
 */
static inline void setHkEnableDiagParCmdN(void* p, uint32_t N)
{
  HkEnableDiagParCmd_t* t;
  t = (HkEnableDiagParCmd_t*)p;
  t->N = N;
}

/**
 * Get "DiagRepStrucID" from "HkEnableDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "DiagRepStrucID".
 */
static inline uint8_t getHkEnableDiagParCmdDiagRepStrucID(void* p)
{
  HkEnableDiagParCmd_t* t;
  t = (HkEnableDiagParCmd_t*)p;
  return t->DiagRepStrucID;
}

/**
 * Set "DiagRepStrucID" in "HkEnableDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \param DiagRepStrucID Value of "DiagRepStrucID" to be set in packet.
 */
static inline void setHkEnableDiagParCmdDiagRepStrucID(void* p, uint8_t DiagRepStrucID)
{
  HkEnableDiagParCmd_t* t;
  t = (HkEnableDiagParCmd_t*)p;
  t->DiagRepStrucID = DiagRepStrucID;
}

/**
 * Get "N" from "HkDisableDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N".
 */
static inline uint32_t getHkDisableDiagParCmdN(void* p)
{
  HkDisableDiagParCmd_t* t;
  t = (HkDisableDiagParCmd_t*)p;
  return t->N;
}

/**
 * Set "N" in "HkDisableDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of "N" to be set in packet.
 */
static inline void setHkDisableDiagParCmdN(void* p, uint32_t N)
{
  HkDisableDiagParCmd_t* t;
  t = (HkDisableDiagParCmd_t*)p;
  t->N = N;
}

/**
 * Get "DiagRepStrucID" from "HkDisableDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "DiagRepStrucID".
 */
static inline uint8_t getHkDisableDiagParCmdDiagRepStrucID(void* p)
{
  HkDisableDiagParCmd_t* t;
  t = (HkDisableDiagParCmd_t*)p;
  return t->DiagRepStrucID;
}

/**
 * Set "DiagRepStrucID" in "HkDisableDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \param DiagRepStrucID Value of "DiagRepStrucID" to be set in packet.
 */
static inline void setHkDisableDiagParCmdDiagRepStrucID(void* p, uint8_t DiagRepStrucID)
{
  HkDisableDiagParCmd_t* t;
  t = (HkDisableDiagParCmd_t*)p;
  t->DiagRepStrucID = DiagRepStrucID;
}

/**
 * Get "N" from "HkRepStructHkParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N".
 */
static inline uint32_t getHkRepStructHkParCmdN(void* p)
{
  HkRepStructHkParCmd_t* t;
  t = (HkRepStructHkParCmd_t*)p;
  return t->N;
}

/**
 * Set "N" in "HkRepStructHkParCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of "N" to be set in packet.
 */
static inline void setHkRepStructHkParCmdN(void* p, uint32_t N)
{
  HkRepStructHkParCmd_t* t;
  t = (HkRepStructHkParCmd_t*)p;
  t->N = N;
}

/**
 * Get "HKRepStrucID" from "HkRepStructHkParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "HKRepStrucID".
 */
static inline uint8_t getHkRepStructHkParCmdHKRepStrucID(void* p)
{
  HkRepStructHkParCmd_t* t;
  t = (HkRepStructHkParCmd_t*)p;
  return t->HKRepStrucID;
}

/**
 * Set "HKRepStrucID" in "HkRepStructHkParCmd" packet.
 * \param p Pointer to the packet.
 * \param HKRepStrucID Value of "HKRepStrucID" to be set in packet.
 */
static inline void setHkRepStructHkParCmdHKRepStrucID(void* p, uint8_t HKRepStrucID)
{
  HkRepStructHkParCmd_t* t;
  t = (HkRepStructHkParCmd_t*)p;
  t->HKRepStrucID = HKRepStrucID;
}

/**
 * Get "HKRepStrucID" from "HkRepStructHkParRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "HKRepStrucID".
 */
static inline uint8_t getHkRepStructHkParRepHKRepStrucID(void* p)
{
  HkRepStructHkParRep_t* t;
  t = (HkRepStructHkParRep_t*)p;
  return t->HKRepStrucID;
}

/**
 * Set "HKRepStrucID" in "HkRepStructHkParRep" packet.
 * \param p Pointer to the packet.
 * \param HKRepStrucID Value of "HKRepStrucID" to be set in packet.
 */
static inline void setHkRepStructHkParRepHKRepStrucID(void* p, uint8_t HKRepStrucID)
{
  HkRepStructHkParRep_t* t;
  t = (HkRepStructHkParRep_t*)p;
  t->HKRepStrucID = HKRepStrucID;
}

/**
 * Get "PeriodicGenActionStatus" from "HkRepStructHkParRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PeriodicGenActionStatus".
 */
static inline uint8_t getHkRepStructHkParRepPeriodicGenActionStatus(void* p)
{
  HkRepStructHkParRep_t* t;
  t = (HkRepStructHkParRep_t*)p;
  return t->PeriodicGenActionStatus;
}

/**
 * Set "PeriodicGenActionStatus" in "HkRepStructHkParRep" packet.
 * \param p Pointer to the packet.
 * \param PeriodicGenActionStatus Value of "PeriodicGenActionStatus" to be set
 * in packet.
 */
static inline void setHkRepStructHkParRepPeriodicGenActionStatus(void* p, uint8_t PeriodicGenActionStatus)
{
  HkRepStructHkParRep_t* t;
  t = (HkRepStructHkParRep_t*)p;
  t->PeriodicGenActionStatus = PeriodicGenActionStatus;
}

/**
 * Get "CollectionInterval" from "HkRepStructHkParRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "CollectionInterval".
 */
static inline uint32_t getHkRepStructHkParRepCollectionInterval(void* p)
{
  HkRepStructHkParRep_t* t;
  t = (HkRepStructHkParRep_t*)p;
  return t->CollectionInterval;
}

/**
 * Set "CollectionInterval" in "HkRepStructHkParRep" packet.
 * \param p Pointer to the packet.
 * \param CollectionInterval Value of "CollectionInterval" to be set in
 * packet.
 */
static inline void setHkRepStructHkParRepCollectionInterval(void* p, uint32_t CollectionInterval)
{
  HkRepStructHkParRep_t* t;
  t = (HkRepStructHkParRep_t*)p;
  t->CollectionInterval = CollectionInterval;
}

/**
 * Get "N1" from "HkRepStructHkParRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "N1".
 */
static inline uint32_t getHkRepStructHkParRepN1(void* p)
{
  HkRepStructHkParRep_t* t;
  t = (HkRepStructHkParRep_t*)p;
  return t->N1;
}

/**
 * Set "N1" in "HkRepStructHkParRep" packet.
 * \param p Pointer to the packet.
 * \param N1 Value of "N1" to be set in packet.
 */
static inline void setHkRepStructHkParRepN1(void* p, uint32_t N1)
{
  HkRepStructHkParRep_t* t;
  t = (HkRepStructHkParRep_t*)p;
  t->N1 = N1;
}

/**
 * Get "N1ParamID" from "HkRepStructHkParRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "N1ParamID".
 */
static inline uint8_t getHkRepStructHkParRepN1ParamID(void* p)
{
  HkRepStructHkParRep_t* t;
  t = (HkRepStructHkParRep_t*)p;
  return t->N1ParamID;
}

/**
 * Set "N1ParamID" in "HkRepStructHkParRep" packet.
 * \param p Pointer to the packet.
 * \param N1ParamID Value of "N1ParamID" to be set in packet.
 */
static inline void setHkRepStructHkParRepN1ParamID(void* p, uint8_t N1ParamID)
{
  HkRepStructHkParRep_t* t;
  t = (HkRepStructHkParRep_t*)p;
  t->N1ParamID = N1ParamID;
}

/**
 * Get "NFA" from "HkRepStructHkParRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "NFA".
 */
static inline uint32_t getHkRepStructHkParRepNFA(void* p)
{
  HkRepStructHkParRep_t* t;
  t = (HkRepStructHkParRep_t*)p;
  return t->NFA;
}

/**
 * Set "NFA" in "HkRepStructHkParRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of "NFA" to be set in packet.
 */
static inline void setHkRepStructHkParRepNFA(void* p, uint32_t NFA)
{
  HkRepStructHkParRep_t* t;
  t = (HkRepStructHkParRep_t*)p;
  t->NFA = NFA;
}

/**
 * Get "SCSampleRepNum" from "HkRepStructHkParRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SCSampleRepNum".
 */
static inline uint32_t getHkRepStructHkParRepSCSampleRepNum(void* p)
{
  HkRepStructHkParRep_t* t;
  t = (HkRepStructHkParRep_t*)p;
  return t->SCSampleRepNum;
}

/**
 * Set "SCSampleRepNum" in "HkRepStructHkParRep" packet.
 * \param p Pointer to the packet.
 * \param SCSampleRepNum Value of "SCSampleRepNum" to be set in packet.
 */
static inline void setHkRepStructHkParRepSCSampleRepNum(void* p, uint32_t SCSampleRepNum)
{
  HkRepStructHkParRep_t* t;
  t = (HkRepStructHkParRep_t*)p;
  t->SCSampleRepNum = SCSampleRepNum;
}

/**
 * Get "N2" from "HkRepStructHkParRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "N2".
 */
static inline uint32_t getHkRepStructHkParRepN2(void* p)
{
  HkRepStructHkParRep_t* t;
  t = (HkRepStructHkParRep_t*)p;
  return t->N2;
}

/**
 * Set "N2" in "HkRepStructHkParRep" packet.
 * \param p Pointer to the packet.
 * \param N2 Value of "N2" to be set in packet.
 */
static inline void setHkRepStructHkParRepN2(void* p, uint32_t N2)
{
  HkRepStructHkParRep_t* t;
  t = (HkRepStructHkParRep_t*)p;
  t->N2 = N2;
}

/**
 * Get "N2ParamID" from "HkRepStructHkParRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "N2ParamID".
 */
static inline uint8_t getHkRepStructHkParRepN2ParamID(void* p)
{
  HkRepStructHkParRep_t* t;
  t = (HkRepStructHkParRep_t*)p;
  return t->N2ParamID;
}

/**
 * Set "N2ParamID" in "HkRepStructHkParRep" packet.
 * \param p Pointer to the packet.
 * \param N2ParamID Value of "N2ParamID" to be set in packet.
 */
static inline void setHkRepStructHkParRepN2ParamID(void* p, uint8_t N2ParamID)
{
  HkRepStructHkParRep_t* t;
  t = (HkRepStructHkParRep_t*)p;
  t->N2ParamID = N2ParamID;
}

/**
 * Get "N" from "HkRepStructDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N".
 */
static inline uint32_t getHkRepStructDiagParCmdN(void* p)
{
  HkRepStructDiagParCmd_t* t;
  t = (HkRepStructDiagParCmd_t*)p;
  return t->N;
}

/**
 * Set "N" in "HkRepStructDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of "N" to be set in packet.
 */
static inline void setHkRepStructDiagParCmdN(void* p, uint32_t N)
{
  HkRepStructDiagParCmd_t* t;
  t = (HkRepStructDiagParCmd_t*)p;
  t->N = N;
}

/**
 * Get "DiagRepStrucID" from "HkRepStructDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "DiagRepStrucID".
 */
static inline uint8_t getHkRepStructDiagParCmdDiagRepStrucID(void* p)
{
  HkRepStructDiagParCmd_t* t;
  t = (HkRepStructDiagParCmd_t*)p;
  return t->DiagRepStrucID;
}

/**
 * Set "DiagRepStrucID" in "HkRepStructDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \param DiagRepStrucID Value of "DiagRepStrucID" to be set in packet.
 */
static inline void setHkRepStructDiagParCmdDiagRepStrucID(void* p, uint8_t DiagRepStrucID)
{
  HkRepStructDiagParCmd_t* t;
  t = (HkRepStructDiagParCmd_t*)p;
  t->DiagRepStrucID = DiagRepStrucID;
}

/**
 * Get "DiagRepStrucID" from "HkRepStructDiagParRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "DiagRepStrucID".
 */
static inline uint8_t getHkRepStructDiagParRepDiagRepStrucID(void* p)
{
  HkRepStructDiagParRep_t* t;
  t = (HkRepStructDiagParRep_t*)p;
  return t->DiagRepStrucID;
}

/**
 * Set "DiagRepStrucID" in "HkRepStructDiagParRep" packet.
 * \param p Pointer to the packet.
 * \param DiagRepStrucID Value of "DiagRepStrucID" to be set in packet.
 */
static inline void setHkRepStructDiagParRepDiagRepStrucID(void* p, uint8_t DiagRepStrucID)
{
  HkRepStructDiagParRep_t* t;
  t = (HkRepStructDiagParRep_t*)p;
  t->DiagRepStrucID = DiagRepStrucID;
}

/**
 * Get "PeriodicGenActionStatus" from "HkRepStructDiagParRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "PeriodicGenActionStatus".
 */
static inline uint8_t getHkRepStructDiagParRepPeriodicGenActionStatus(void* p)
{
  HkRepStructDiagParRep_t* t;
  t = (HkRepStructDiagParRep_t*)p;
  return t->PeriodicGenActionStatus;
}

/**
 * Set "PeriodicGenActionStatus" in "HkRepStructDiagParRep" packet.
 * \param p Pointer to the packet.
 * \param PeriodicGenActionStatus Value of "PeriodicGenActionStatus" to be set
 * in packet.
 */
static inline void setHkRepStructDiagParRepPeriodicGenActionStatus(void* p, uint8_t PeriodicGenActionStatus)
{
  HkRepStructDiagParRep_t* t;
  t = (HkRepStructDiagParRep_t*)p;
  t->PeriodicGenActionStatus = PeriodicGenActionStatus;
}

/**
 * Get "CollectionInterval" from "HkRepStructDiagParRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "CollectionInterval".
 */
static inline uint32_t getHkRepStructDiagParRepCollectionInterval(void* p)
{
  HkRepStructDiagParRep_t* t;
  t = (HkRepStructDiagParRep_t*)p;
  return t->CollectionInterval;
}

/**
 * Set "CollectionInterval" in "HkRepStructDiagParRep" packet.
 * \param p Pointer to the packet.
 * \param CollectionInterval Value of "CollectionInterval" to be set in
 * packet.
 */
static inline void setHkRepStructDiagParRepCollectionInterval(void* p, uint32_t CollectionInterval)
{
  HkRepStructDiagParRep_t* t;
  t = (HkRepStructDiagParRep_t*)p;
  t->CollectionInterval = CollectionInterval;
}

/**
 * Get "N1" from "HkRepStructDiagParRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "N1".
 */
static inline uint32_t getHkRepStructDiagParRepN1(void* p)
{
  HkRepStructDiagParRep_t* t;
  t = (HkRepStructDiagParRep_t*)p;
  return t->N1;
}

/**
 * Set "N1" in "HkRepStructDiagParRep" packet.
 * \param p Pointer to the packet.
 * \param N1 Value of "N1" to be set in packet.
 */
static inline void setHkRepStructDiagParRepN1(void* p, uint32_t N1)
{
  HkRepStructDiagParRep_t* t;
  t = (HkRepStructDiagParRep_t*)p;
  t->N1 = N1;
}

/**
 * Get "N1ParamID" from "HkRepStructDiagParRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "N1ParamID".
 */
static inline uint8_t getHkRepStructDiagParRepN1ParamID(void* p)
{
  HkRepStructDiagParRep_t* t;
  t = (HkRepStructDiagParRep_t*)p;
  return t->N1ParamID;
}

/**
 * Set "N1ParamID" in "HkRepStructDiagParRep" packet.
 * \param p Pointer to the packet.
 * \param N1ParamID Value of "N1ParamID" to be set in packet.
 */
static inline void setHkRepStructDiagParRepN1ParamID(void* p, uint8_t N1ParamID)
{
  HkRepStructDiagParRep_t* t;
  t = (HkRepStructDiagParRep_t*)p;
  t->N1ParamID = N1ParamID;
}

/**
 * Get "NFA" from "HkRepStructDiagParRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "NFA".
 */
static inline uint32_t getHkRepStructDiagParRepNFA(void* p)
{
  HkRepStructDiagParRep_t* t;
  t = (HkRepStructDiagParRep_t*)p;
  return t->NFA;
}

/**
 * Set "NFA" in "HkRepStructDiagParRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of "NFA" to be set in packet.
 */
static inline void setHkRepStructDiagParRepNFA(void* p, uint32_t NFA)
{
  HkRepStructDiagParRep_t* t;
  t = (HkRepStructDiagParRep_t*)p;
  t->NFA = NFA;
}

/**
 * Get "SCSampleRepNum" from "HkRepStructDiagParRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "SCSampleRepNum".
 */
static inline uint32_t getHkRepStructDiagParRepSCSampleRepNum(void* p)
{
  HkRepStructDiagParRep_t* t;
  t = (HkRepStructDiagParRep_t*)p;
  return t->SCSampleRepNum;
}

/**
 * Set "SCSampleRepNum" in "HkRepStructDiagParRep" packet.
 * \param p Pointer to the packet.
 * \param SCSampleRepNum Value of "SCSampleRepNum" to be set in packet.
 */
static inline void setHkRepStructDiagParRepSCSampleRepNum(void* p, uint32_t SCSampleRepNum)
{
  HkRepStructDiagParRep_t* t;
  t = (HkRepStructDiagParRep_t*)p;
  t->SCSampleRepNum = SCSampleRepNum;
}

/**
 * Get "N2" from "HkRepStructDiagParRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "N2".
 */
static inline uint32_t getHkRepStructDiagParRepN2(void* p)
{
  HkRepStructDiagParRep_t* t;
  t = (HkRepStructDiagParRep_t*)p;
  return t->N2;
}

/**
 * Set "N2" in "HkRepStructDiagParRep" packet.
 * \param p Pointer to the packet.
 * \param N2 Value of "N2" to be set in packet.
 */
static inline void setHkRepStructDiagParRepN2(void* p, uint32_t N2)
{
  HkRepStructDiagParRep_t* t;
  t = (HkRepStructDiagParRep_t*)p;
  t->N2 = N2;
}

/**
 * Get "N2ParamID" from "HkRepStructDiagParRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "N2ParamID".
 */
static inline uint8_t getHkRepStructDiagParRepN2ParamID(void* p)
{
  HkRepStructDiagParRep_t* t;
  t = (HkRepStructDiagParRep_t*)p;
  return t->N2ParamID;
}

/**
 * Set "N2ParamID" in "HkRepStructDiagParRep" packet.
 * \param p Pointer to the packet.
 * \param N2ParamID Value of "N2ParamID" to be set in packet.
 */
static inline void setHkRepStructDiagParRepN2ParamID(void* p, uint8_t N2ParamID)
{
  HkRepStructDiagParRep_t* t;
  t = (HkRepStructDiagParRep_t*)p;
  t->N2ParamID = N2ParamID;
}

/**
 * Get "HKRepStrucID" from "HkOneShotHkRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "HKRepStrucID".
 */
static inline uint8_t getHkOneShotHkRepHKRepStrucID(void* p)
{
  HkOneShotHkRep_t* t;
  t = (HkOneShotHkRep_t*)p;
  return t->HKRepStrucID;
}

/**
 * Set "HKRepStrucID" in "HkOneShotHkRep" packet.
 * \param p Pointer to the packet.
 * \param HKRepStrucID Value of "HKRepStrucID" to be set in packet.
 */
static inline void setHkOneShotHkRepHKRepStrucID(void* p, uint8_t HKRepStrucID)
{
  HkOneShotHkRep_t* t;
  t = (HkOneShotHkRep_t*)p;
  t->HKRepStrucID = HKRepStrucID;
}

/**
 * Get "ParamVal" from "HkOneShotHkRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "ParamVal".
 */
static inline uint32_t getHkOneShotHkRepParamVal(void* p)
{
  HkOneShotHkRep_t* t;
  t = (HkOneShotHkRep_t*)p;
  return t->ParamVal;
}

/**
 * Set "ParamVal" in "HkOneShotHkRep" packet.
 * \param p Pointer to the packet.
 * \param ParamVal Value of "ParamVal" to be set in packet.
 */
static inline void setHkOneShotHkRepParamVal(void* p, uint32_t ParamVal)
{
  HkOneShotHkRep_t* t;
  t = (HkOneShotHkRep_t*)p;
  t->ParamVal = ParamVal;
}

/**
 * Get "DiagRepStrucID" from "HkOneShotDiagRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "DiagRepStrucID".
 */
static inline uint8_t getHkOneShotDiagRepDiagRepStrucID(void* p)
{
  HkOneShotDiagRep_t* t;
  t = (HkOneShotDiagRep_t*)p;
  return t->DiagRepStrucID;
}

/**
 * Set "DiagRepStrucID" in "HkOneShotDiagRep" packet.
 * \param p Pointer to the packet.
 * \param DiagRepStrucID Value of "DiagRepStrucID" to be set in packet.
 */
static inline void setHkOneShotDiagRepDiagRepStrucID(void* p, uint8_t DiagRepStrucID)
{
  HkOneShotDiagRep_t* t;
  t = (HkOneShotDiagRep_t*)p;
  t->DiagRepStrucID = DiagRepStrucID;
}

/**
 * Get "ParamVal" from "HkOneShotDiagRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "ParamVal".
 */
static inline uint32_t getHkOneShotDiagRepParamVal(void* p)
{
  HkOneShotDiagRep_t* t;
  t = (HkOneShotDiagRep_t*)p;
  return t->ParamVal;
}

/**
 * Set "ParamVal" in "HkOneShotDiagRep" packet.
 * \param p Pointer to the packet.
 * \param ParamVal Value of "ParamVal" to be set in packet.
 */
static inline void setHkOneShotDiagRepParamVal(void* p, uint32_t ParamVal)
{
  HkOneShotDiagRep_t* t;
  t = (HkOneShotDiagRep_t*)p;
  t->ParamVal = ParamVal;
}

/**
 * Get "N" from "HkOneShotHkCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N".
 */
static inline uint32_t getHkOneShotHkCmdN(void* p)
{
  HkOneShotHkCmd_t* t;
  t = (HkOneShotHkCmd_t*)p;
  return t->N;
}

/**
 * Set "N" in "HkOneShotHkCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of "N" to be set in packet.
 */
static inline void setHkOneShotHkCmdN(void* p, uint32_t N)
{
  HkOneShotHkCmd_t* t;
  t = (HkOneShotHkCmd_t*)p;
  t->N = N;
}

/**
 * Get "HKRepStrucID" from "HkOneShotHkCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "HKRepStrucID".
 */
static inline uint8_t getHkOneShotHkCmdHKRepStrucID(void* p)
{
  HkOneShotHkCmd_t* t;
  t = (HkOneShotHkCmd_t*)p;
  return t->HKRepStrucID;
}

/**
 * Set "HKRepStrucID" in "HkOneShotHkCmd" packet.
 * \param p Pointer to the packet.
 * \param HKRepStrucID Value of "HKRepStrucID" to be set in packet.
 */
static inline void setHkOneShotHkCmdHKRepStrucID(void* p, uint8_t HKRepStrucID)
{
  HkOneShotHkCmd_t* t;
  t = (HkOneShotHkCmd_t*)p;
  t->HKRepStrucID = HKRepStrucID;
}

/**
 * Get "N" from "HkOneShotDiagCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "N".
 */
static inline uint32_t getHkOneShotDiagCmdN(void* p)
{
  HkOneShotDiagCmd_t* t;
  t = (HkOneShotDiagCmd_t*)p;
  return t->N;
}

/**
 * Set "N" in "HkOneShotDiagCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of "N" to be set in packet.
 */
static inline void setHkOneShotDiagCmdN(void* p, uint32_t N)
{
  HkOneShotDiagCmd_t* t;
  t = (HkOneShotDiagCmd_t*)p;
  t->N = N;
}

/**
 * Get "DiagRepStrucID" from "HkOneShotDiagCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "DiagRepStrucID".
 */
static inline uint8_t getHkOneShotDiagCmdDiagRepStrucID(void* p)
{
  HkOneShotDiagCmd_t* t;
  t = (HkOneShotDiagCmd_t*)p;
  return t->DiagRepStrucID;
}

/**
 * Set "DiagRepStrucID" in "HkOneShotDiagCmd" packet.
 * \param p Pointer to the packet.
 * \param DiagRepStrucID Value of "DiagRepStrucID" to be set in packet.
 */
static inline void setHkOneShotDiagCmdDiagRepStrucID(void* p, uint8_t DiagRepStrucID)
{
  HkOneShotDiagCmd_t* t;
  t = (HkOneShotDiagCmd_t*)p;
  t->DiagRepStrucID = DiagRepStrucID;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSPKTHK_H */
