/**
 * \file CrPsPktServHkSupp.h
 *
 * Interface for accessing fields in packets of service "ServHk".
 *
 * \author C. Reimers and M. Rockenbauer 24.10.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */
#ifndef CRPSPKTSERVHKSUPP_H_
#define CRPSPKTSERVHKSUPP_H_

#include "Services/General/CrPsPktUtil.h"


/**
 * Get the offset of the "SCSampleRepNum" field in a HkCreate packet.
 * The offset depend on the "NFA" Value.
 * \param p Pointer to the packet.
 * \param NFA Value
 * \return the offset of the "NFA" th. "SCSampleRepNum" field.
 */
static inline uint32_t getHkCreateCmdOffsetSCS(void* p, uint32_t NFA)
{
  uint32_t pos, n2val, i, N1;
  HkCreateCmd_t t;

  N1 = getHkCreateCmdN1(p);

  pos = sizeof(t.Header)+sizeof(t.RepStrucId)+sizeof(t.CollectionInterval)+sizeof(t.N1)+(sizeof(t.N1ParamId)*N1) + sizeof(t.NFA);
  for (i=1;i<NFA;i++)
    {
      pos = pos + sizeof(t.SCSampleRepNum);
      n2val = getPcktInt(p, pos);
      pos = pos + sizeof(t.N2) + n2val*sizeof(t.N2ParamId);
    }
  return pos;
}

/**
 * Get the offset of the "N2" field in a HkCreate packet.
 * The offset depend on the "NFA" Value.
 * \param p Pointer to the packet.
 * \param NFA Value
 * \return the offset of the "NFA" th. "N2" field.
 */
static inline uint32_t getHkCreateCmdOffsetN2(void* p, uint32_t NFA)
{
  HkCreateCmd_t t;
  return getHkCreateCmdOffsetSCS(p, NFA)+sizeof(t.SCSampleRepNum);
}

/**
 * Get the offset of the "N2ParamId" field in a HkCreate packet.
 * The offset depend on the "NFA" and the N2 Value.
 * \param p Pointer to the packet.
 * \param NFA Value
 * \param N2 Value
 * \return the offset of the "NFA" th. Group and the "N2" th. N2ParamId field.
 */
static inline uint32_t getHkCreateCmdOffsetN2ParamId(void* p, uint32_t NFA, uint32_t N2)
{
  HkCreateCmd_t t;
  if (N2>0)
  {
    N2 = N2-1;
  }
  return getHkCreateCmdOffsetN2(p, NFA) + sizeof(t.N2) + N2*sizeof(t.N2ParamId);
}

/**
 * Get "NFA" from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "NFA".
 */
static inline uint32_t getHkCreateCmdNFA(void* p)
{
  uint32_t pos;
  uint32_t ret;
  HkCreateCmd_t t;

  pos = sizeof(t.Header)+sizeof(t.RepStrucId)+sizeof(t.CollectionInterval)+sizeof(t.N1)+(sizeof(t.N1ParamId)*getHkCreateCmdN1(p));
  memcpy(&ret, &((uint8_t*)p)[pos], sizeof(t.NFA));
  return __builtin_bswap32(ret);
}

/**
 * Set "NFA" in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param src Value of "NFA" to be set in packet.
 */
static inline void setHkCreateCmdNFA(void* p, uint32_t src)
{
  uint32_t pos;
  HkCreateCmd_t t;
  pos = sizeof(t.Header)+sizeof(t.RepStrucId)+sizeof(t.CollectionInterval)+sizeof(t.N1)+(sizeof(t.N1ParamId)*getHkCreateCmdN1(p));
  src = __builtin_bswap32(src);
  memcpy(&((uint8_t*)p)[pos], &src, sizeof(src));
}

/**
 * Get pointer to "N1ParamId" array from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \return Pointer to the start of the N1ParamId array.
 */
static inline uint16_t* getHkCreateCmdN1ParamIdArray(void* p)
{
  HkCreateCmd_t* t;
  t = (HkCreateCmd_t*)p;
  return &t->N1ParamId;
}

/**
 * Get "N1ParamId" array from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param dest Pointer to memory location where array data are copied to.
 */
static inline void getHkCreateCmdN1ParamId(void* p, void* dest)
{
  HkCreateCmd_t* t;
  t = (HkCreateCmd_t*)p;
  memcpy(dest, &t->N1ParamId, sizeof(t->N1ParamId)*getHkCreateCmdN1(p));
}

/**
 * Set "N1ParamId" array in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param src Pointer to memory location from where array data are copied.
 */
static inline void setHkCreateCmdN1ParamId(void* p, const void* src)
{
  HkCreateCmd_t* t;
  t = (HkCreateCmd_t*)p;
  memcpy(&t->N1ParamId, src, sizeof(t->N1ParamId)*getHkCreateCmdN1(p));
}

/**
 * Get "N1ParamId" arrayItem from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of ParamIdArray Item.
 * \return N1ParamId Array Item Value.
 */
static inline uint16_t getHkCreateCmdN1ParamIdItem(void* p, uint32_t N)
{
  uint16_t ret;
  uint32_t pos;
  HkCreateCmd_t t;
  if(N>0)
    {
      N=N-1;
    }
  pos = sizeof(t.Header)+sizeof(t.RepStrucId)+sizeof(t.CollectionInterval)+sizeof(t.N1)+(sizeof(t.N1ParamId)*N);
  memcpy(&ret, &((uint8_t*)p)[pos], sizeof(t.N1ParamId));
  return __builtin_bswap16(ret);
}

/**
 * Set "N1ParamId" arrayItem in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of the "N" th ParamIdArray Item.
 * \param src Variable from where arrayItem data are copied.
 */
static inline void setHkCreateCmdN1ParamIdItem(void* p, uint32_t N, uint16_t src)
{
  uint32_t pos;
  HkCreateCmd_t t;
  if(N>0)
    {
      N=N-1;
    }
  pos = sizeof(t.Header)+sizeof(t.RepStrucId)+sizeof(t.CollectionInterval)+sizeof(t.N1)+(sizeof(t.N1ParamId)*N);
  src = __builtin_bswap16(src);
  memcpy(&((uint8_t*)p)[pos], &src, sizeof(t.N1ParamId));
}

/**
 * Get "N2" from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \return Value of "N2".
 */
static inline uint32_t getHkCreateCmdN2(void* p, uint32_t NFA)
{
  uint32_t ret;
  HkCreateCmd_t t;
  memcpy(&ret, &((uint8_t*)p)[getHkCreateCmdOffsetN2(p, NFA)], sizeof(t.N2));
  return __builtin_bswap32(ret);
}

/**
 * Set "N2" in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param N2 Value of "N2" to be set in packet.
 */
static inline void setHkCreateCmdN2(void* p, uint32_t NFA, uint32_t N2)
{
  HkCreateCmd_t t;
  N2 = __builtin_bswap32(N2);
  memcpy(&((uint8_t*)p)[getHkCreateCmdOffsetN2(p, NFA)], &N2, sizeof(t.N2));
}

/**
 * Get "SCSampleRepNum" from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \return Value of "SCSampleRepNum".
 */
static inline uint32_t getHkCreateCmdSCSampleRepNumItem(void* p, uint32_t NFA)
{
  uint32_t ret;
  HkCreateCmd_t t;
  memcpy(&ret, &((uint8_t*)p)[getHkCreateCmdOffsetSCS(p, NFA)], sizeof(t.SCSampleRepNum));
  return __builtin_bswap32(ret);
}

/**
 * Set "SCSampleRepNum" in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param src Value of "SCSampleRepNum" to be set in packet.
 */
static inline void setHkCreateCmdSCSampleRepNumItem(void* p, uint32_t NFA, uint32_t src)
{
  HkCreateCmd_t t;
  src = __builtin_bswap32(src);
  memcpy(&((uint8_t*)p)[getHkCreateCmdOffsetSCS(p, NFA)], &src, sizeof(t.SCSampleRepNum));
}

/**
 * Get "N2ParamID" from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param N2 Value of the "N2" th Item.
 * \return Value of "N2ParamID".
 */
static inline uint16_t getHkCreateCmdN2ParamIdItem(void* p, uint32_t NFA, uint32_t N2)
{
  uint16_t ret;
  HkCreateCmd_t t;
  memcpy(&ret, &((uint8_t*)p)[getHkCreateCmdOffsetN2ParamId(p, NFA, N2)], sizeof(t.N2ParamId));
  return __builtin_bswap16(ret);
}

/**
 * Set "N2ParamID" in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param N2 Value of the "N2" th Item.
 * \param src Value of "N2ParamID" to be set in packet.
 */
static inline void setHkCreateCmdN2ParamIdItem(void* p, uint32_t NFA, uint32_t N2, uint16_t src)
{
  HkCreateCmd_t t;
  src = __builtin_bswap16(src);
  memcpy(&((uint8_t*)p)[getHkCreateCmdOffsetN2ParamId(p, NFA, N2)], &src, sizeof(t.N2ParamId));
}

/**
 * Get pointer to "N1ParamId" array from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \return Pointer to the start of the N1ParamId array.
 */
static inline uint8_t* getHkCreateCmdN2ParamIdArray(void* p, uint32_t NFA)
{
  HkCreateCmd_t t;
  return &((uint8_t*)p)[getHkCreateCmdOffsetN2(p, NFA) + sizeof(t.N2)];
}

/**
 * Get "N1ParamId" array from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param dest Pointer to memory location where array data are copied to.
 * \param NFA Value of the "NFA" th Group.
 */
static inline void getHkCreateCmdN2ParamId(void* p, void* dest, uint32_t NFA)
{
  HkCreateCmd_t t;
  memcpy(dest, &((uint8_t*)p)[getHkCreateCmdOffsetN2(p, NFA) + sizeof(t.N2)], sizeof(t.N2ParamId)*getHkCreateCmdN2(p, NFA));
}

/**
 * Set "N1ParamId" array in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param src Pointer to memory location from where array data are copied.
 * \param NFA Value of the "NFA" th Group.
 */
static inline void setHkCreateCmdN2ParamId(void* p, const void* src, uint32_t NFA)
{
  HkCreateCmd_t t;
  memcpy(&((uint8_t*)p)[getHkCreateCmdOffsetN2(p, NFA) + sizeof(t.N2)], src, sizeof(t.N2ParamId)*getHkCreateCmdN2(p, NFA));
}


/**
 * Get the offset of the "SCSampleRepNum" field in a HkRepStruct packet.
 * The offset depend on the "NFA" Value.
 * \param p Pointer to the packet.
 * \param NFA Value
 * \return the offset of the "NFA" th. "SCSampleRepNum" field.
 */
static inline uint32_t getHkRepStructRepOffsetSCS(void* p, uint32_t NFA)
{
  uint32_t pos, n2val, i, N1;
  HkRepStructRep_t t;

  N1 = getHkRepStructRepN1(p);
  pos = sizeof(t.Header)+sizeof(t.RepStrucId)+sizeof(t.CollectionInterval)+sizeof(t.N1)+sizeof(t.N1ParamId)*N1 + sizeof(t.NFA);
  
  for (i=1;i<NFA;i++)
    {
      pos = pos + sizeof(t.SCSampleRepNum);
      n2val = getPcktInt(p, pos);
      pos = pos + sizeof(t.N2) + n2val*sizeof(t.N2ParamId);
    }
  return pos;
}

/**
 * Get the offset of the "N2" field in a HkRepStruct packet.
 * The offset depend on the "NFA" Value.
 * \param p Pointer to the packet.
 * \param NFA Value
 * \return the offset of the "NFA" th. "N2" field.
 */
static inline uint32_t getHkRepStructRepOffsetN2(void* p, uint32_t NFA)
{
  HkRepStructRep_t t;
  return getHkRepStructRepOffsetSCS(p, NFA)+sizeof(t.SCSampleRepNum);
}

/**
 * Get the offset of the "N2ParamId" field in a HkCreate packet.
 * The offset depend on the "NFA" and the N2 Value.
 * \param p Pointer to the packet.
 * \param NFA Value
 * \param N2 Value
 * \return the offset of the "NFA" th. Group and the "N2" th. N2ParamId field.
 */
static inline uint32_t getHkRepStructRepOffsetN2ParamId(void* p, uint32_t NFA, uint32_t N2)
{
  HkRepStructRep_t t;
  if (N2>0)
  {
    N2 = N2-1;
  }
  return getHkRepStructRepOffsetN2(p, NFA) + sizeof(t.N2) + N2*sizeof(t.N2ParamId);
}

/**
 * Get "NFA" from "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "NFA".
 */                    
static inline uint32_t getHkRepStructRepNFA(void* p)
{
  uint32_t pos;
  uint32_t ret;
  HkRepStructRep_t t;
  pos = sizeof(t.Header)+sizeof(t.RepStrucId)+sizeof(t.CollectionInterval)+sizeof(t.N1)+sizeof(t.N1ParamId)*getHkRepStructRepN1(p);
  memcpy(&ret, &((uint8_t*)p)[pos], sizeof(t.NFA));
  return __builtin_bswap32(ret);
}

/**
 * Set "NFA" in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param src Value of "NFA" to be set in packet.
 */
static inline void setHkRepStructRepNFA(void* p, uint32_t src)
{
  uint32_t pos;
  HkRepStructRep_t t;
  pos = sizeof(t.Header)+sizeof(t.RepStrucId)+sizeof(t.CollectionInterval)+sizeof(t.N1)+sizeof(t.N1ParamId)*getHkRepStructRepN1(p);
  src = __builtin_bswap32(src);
  memcpy(&((uint8_t*)p)[pos], &src, sizeof(src));
}

/**
 * Get pointer to "N1ParamId" array from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \return Pointer to the start of the N1ParamId array.
 */
static inline uint16_t* getHkRepStructRepN1ParamIdArray(void* p)
{
  HkRepStructRep_t* t;
  t = (HkRepStructRep_t*)p;
  return &t->N1ParamId;
}

/**
 * Get "N1ParamId" array from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param dest Pointer to memory location where array data are copied to.
 */
static inline void getHkRepStructRepN1ParamId(void* p, void* dest)
{
  HkRepStructRep_t* t;
  t = (HkRepStructRep_t*)p;
  memcpy(dest, &t->N1ParamId, sizeof(t->N1ParamId)*getHkRepStructRepN1(p));
}

/**
 * Set "N1ParamId" array in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param src Pointer to memory location from where array data are copied.
 */
static inline void setHkRepStructRepN1ParamId(void* p, const void* src)
{
  HkRepStructRep_t* t;
  t = (HkRepStructRep_t*)p;
  memcpy(&t->N1ParamId, src, sizeof(t->N1ParamId)*getHkRepStructRepN1(p));
}

/**
 * Get "N1ParamId" arrayItem from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param N Number of ParamIdArray Item.
 * \return N2ParamId "N" th Array Item Value.
 */
static inline uint16_t getHkRepStructRepN1ParamIdItem(void* p, uint32_t N)
{
  uint16_t ret;
  uint32_t pos;
  HkRepStructRep_t t;
  if(N>0)
    {
      N=N-1;
    }
  pos = sizeof(t.Header)+sizeof(t.RepStrucId)+sizeof(t.CollectionInterval)+sizeof(t.N1)+sizeof(t.N1ParamId)*N;
  memcpy(&ret, &((uint8_t*)p)[pos], sizeof(t.N1ParamId));
  return __builtin_bswap16(ret);
}

/**
 * Set "N1ParamId" arrayItem in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param N Number of ParamIdArray Item.
 * \param src Variable from where arrayItem data are copied.
 */
static inline void setHkRepStructRepN1ParamIdItem(void* p, uint32_t N, uint16_t src)
{
  uint32_t pos;
  HkRepStructRep_t t;
  if(N>0)
    {
      N=N-1;
    }
  pos = sizeof(t.Header)+sizeof(t.RepStrucId)+sizeof(t.CollectionInterval)+sizeof(t.N1)+sizeof(t.N1ParamId)*N;
  src = __builtin_bswap16(src);
  memcpy(&((uint8_t*)p)[pos], &src, sizeof(t.N1ParamId));
}

/**
 * Get "N2" from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \return Value of "N2".
 */
static inline uint32_t getHkRepStructRepN2(void* p, uint32_t NFA)
{
  uint32_t ret;
  HkRepStructRep_t t;
  memcpy(&ret, &((uint8_t*)p)[getHkRepStructRepOffsetN2(p, NFA)], sizeof(t.N2));
  return __builtin_bswap32(ret);
}

/**
 * Set "N2" in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param N2 Value of "N2" to be set in packet.
 */
static inline void setHkRepStructRepN2(void* p, uint32_t NFA, uint32_t N2)
{
  HkRepStructRep_t t;
  N2 = __builtin_bswap32(N2);
  memcpy(&((uint8_t*)p)[getHkRepStructRepOffsetN2(p, NFA)], &N2, sizeof(t.N2));
}

/**
 * Get "SCSampleRepNum" from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \return Value of "SCSampleRepNum".
 */
static inline uint32_t getHkRepStructRepSCSampleRepNumItem(void* p, uint32_t NFA)
{
  uint32_t ret;
  HkRepStructRep_t t;
  memcpy(&ret, &((uint8_t*)p)[getHkRepStructRepOffsetSCS(p, NFA)], sizeof(t.SCSampleRepNum));
  return __builtin_bswap32(ret);
}

/**
 * Set "SCSampleRepNum" in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param src Value of "SCSampleRepNum" to be set in packet.
 */
static inline void setHkRepStructRepSCSampleRepNumItem(void* p, uint32_t NFA, uint32_t src)
{
  HkRepStructRep_t t;
  src = __builtin_bswap32(src);
  memcpy(&((uint8_t*)p)[getHkRepStructRepOffsetSCS(p, NFA)], &src, sizeof(t.SCSampleRepNum));
}

/**
 * Get "N2ParamID" from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param N2 Value of the "N2" th Item.
 * \return Value of "N2ParamID".
 */
static inline uint16_t getHkRepStructRepN2ParamIdItem(void* p, uint32_t NFA, uint32_t N2)
{
  uint16_t ret;
  HkRepStructRep_t t;
  memcpy(&ret, &((uint8_t*)p)[getHkRepStructRepOffsetN2ParamId(p, NFA, N2)], sizeof(t.N2ParamId));
  return __builtin_bswap16(ret);
}

/**
 * Set "N2ParamID" in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param N2 Value of the "N2" th Item.
 * \param src Value of "N2ParamID" to be set in packet.
 */
static inline void setHkRepStructRepN2ParamIdItem(void* p, uint32_t NFA, uint32_t N2, uint16_t src)
{
  HkRepStructRep_t t;
  src = __builtin_bswap16(src);
  memcpy(&((uint8_t*)p)[getHkRepStructRepOffsetN2ParamId(p, NFA, N2)], &src, sizeof(t.N2ParamId));
}

/**
 * Get pointer to "N1ParamId" array from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \return Pointer to the start of the N1ParamId array.
 */
static inline uint8_t* getHkRepStructRepN2ParamIdArray(void* p, uint32_t NFA)
{
  HkRepStructRep_t t;
  return &((uint8_t*)p)[getHkRepStructRepOffsetN2(p, NFA) + sizeof(t.N2)];
}

/**
 * Get "N1ParamId" array from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param dest Pointer to memory location where array data are copied to.
 * \param NFA Value of the "NFA" th Group.
 */
static inline void getHkRepStructRepN2ParamId(void* p, void* dest, uint32_t NFA)
{
  HkRepStructRep_t t;
  memcpy(dest, &((uint8_t*)p)[getHkRepStructRepOffsetN2(p, NFA) + sizeof(t.N2)], sizeof(t.N2ParamId)*getHkRepStructRepN2(p, NFA));
}

/**
 * Set "N1ParamId" array in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param src Pointer to memory location from where array data are copied.
 * \param NFA Value of the "NFA" th Group.
 */
static inline void setHkRepStructRepN2ParamId(void* p, const void* src, uint32_t NFA)
{
  HkRepStructRep_t t;
  memcpy(&((uint8_t*)p)[getHkRepStructRepOffsetN2(p, NFA) + sizeof(t.N2)], src, sizeof(t.N2ParamId)*getHkRepStructRepN2(p, NFA));
}


/**
 * Get "RepStrucId" from "HkDeleteCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \return Value of "RepStrucId" the "N" th Item of the array.
 */
static inline uint8_t getHkDeleteCmdRepStrucIdItem(void* p, uint32_t N)
{
  uint8_t dest;
  HkDeleteCmd_t t;
  memcpy(&dest, &((uint8_t*)p)[sizeof(t)-1+sizeof(t.RepStrucId)*N], sizeof(t.RepStrucId));
  return dest;
}

/**
 * Set "RepStrucId" in "HkDeleteCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of ParamIdArray Item.
 * \param RepStrucId Value of "RepStrucId" to be set in packet.
 */
static inline void setHkDeleteCmdRepStrucIdItem(void* p, uint32_t N, uint8_t RepStrucId)
{
  HkDeleteCmd_t t;
  memcpy(&((uint8_t*)p)[sizeof(t)-1+sizeof(t.RepStrucId)*N], &RepStrucId, sizeof(t.RepStrucId));  
}

/**
 * Get "RepStrucId" from "HkEnableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of ParamIdArray Item.
 * \return Value of "RepStrucId" the "N" th Item of the array.
 */
static inline uint8_t getHkEnableCmdRepStrucIdItem(void* p, uint32_t N)
{
  uint8_t dest;
  HkEnableCmd_t t;
  memcpy(&dest, &((uint8_t*)p)[sizeof(t)-1+sizeof(t.RepStrucId)*N], sizeof(t.RepStrucId));
  return dest;
}

/**
 * Set "RepStrucId" in "HkEnableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \param RepStrucId Value of "RepStrucId" to be set in packet.
 */
static inline void setHkEnableCmdRepStrucIdItem(void* p, uint32_t N, uint8_t RepStrucId)
{
  HkEnableCmd_t t;
  memcpy(&((uint8_t*)p)[sizeof(t)-1+sizeof(t.RepStrucId)*N], &RepStrucId, sizeof(t.N));
}

/**
 * Get "RepStrucId" from "HkDisableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \return Value of "RepStrucId" the "N" th Item of the array.
 */
static inline uint8_t getHkDisableCmdRepStrucIdItem(void* p, uint32_t N)
{
  uint8_t dest;
  HkDisableCmd_t t;
  memcpy(&dest, &((uint8_t*)p)[sizeof(t)-1+sizeof(t.RepStrucId)*N], sizeof(t.RepStrucId));
  return dest;
}

/**
 * Set "RepStrucId" in "HkDisableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \param RepStrucId Value of "RepStrucId" to be set in packet.
 */
static inline void setHkDisableCmdRepStrucIdItem(void* p, uint32_t N, uint8_t RepStrucId)
{
  HkDisableCmd_t t;
  memcpy(&((uint8_t*)p)[sizeof(t)-1+sizeof(t.RepStrucId)*N], &RepStrucId, sizeof(t.N));
}

/**
 * Get "RepStrucId" from "HkRepStructCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \return Value of "RepStrucId" the "N" th Item of the array.
 */
static inline uint8_t getHkRepStructCmdRepStrucIdItem(void* p, uint32_t N)
{
  uint8_t dest;
  HkRepStructCmd_t t;
  memcpy(&dest, &((uint8_t*)p)[sizeof(t)-1+sizeof(t.RepStrucId)*N], sizeof(t.RepStrucId));
  return dest;
}

/**
 * Set "RepStrucId" in "HkRepStructCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \param RepStrucId Value of "RepStrucId" to be set in packet.
 */
static inline void setHkRepStructCmdRepStrucIdItem(void* p, uint32_t N, uint8_t RepStrucId)
{
  HkRepStructCmd_t t;
  memcpy(&((uint8_t*)p)[sizeof(t)-1+sizeof(t.RepStrucId)*N], &RepStrucId, sizeof(t.N));
}

/**
 * Get "RepStrucId" from "HkOneShotCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \return Value of "RepStrucId" the "N" th Item of the array.
 */
static inline uint8_t getHkOneShotCmdRepStrucIdItem(void* p, uint32_t N)
{
  uint8_t dest;
  HkOneShotCmd_t t;
  memcpy(&dest, &((uint8_t*)p)[sizeof(t)-1+sizeof(t.RepStrucId)*N], sizeof(t.RepStrucId));
  return dest;
}

/**
 * Set "RepStrucId" in "HkOneShotCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \param RepStrucId Value of "RepStrucId" to be set in packet.
 */
static inline void setHkOneShotCmdRepStrucIdItem(void* p, uint32_t N, uint8_t RepStrucId)
{
  HkOneShotCmd_t t;
  memcpy(&((uint8_t*)p)[sizeof(t)-1+sizeof(t.RepStrucId)*N], &RepStrucId, sizeof(t.N));
}

/**
 * Get the size of a Housekeeping packet.
 * \param p Pointer to the packet.
 * \return the size of the packet in bytes.
 */
static inline size_t getHk3_1PcktSize(void* p)
{
  size_t s;
  uint32_t j, k, N1, NFA, N2;
  HkCreateCmd_t t;

  s=sizeof(t.Header) + sizeof(t.RepStrucId) + sizeof(t.CollectionInterval) + sizeof(t.N1);
  N1 = getHkCreateCmdN1(p);
  for(j=1;j<=N1;j++)
  {
    s+=sizeof(t.N1ParamId);
  }
  s+=sizeof(t.NFA);
  NFA = getHkCreateCmdNFA(p);
  for(j=1;j<=NFA;j++)
  {
    s+=sizeof(t.SCSampleRepNum) + sizeof(t.N2);
    N2 = getHkCreateCmdN2(p,j);
    for(k=1;k<=N2;k++)
    {
      s+=sizeof(t.N2ParamId);
    }
  }
  return s;
}

/*----------------------------------------------------------------------------*/
#endif /* CRPSPKTSERVHKSUPP_H */