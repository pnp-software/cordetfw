/**
 * \file CrPsPktServHkSupp.c
 *
 * Interface for accessing fields in packets of service "ServHk".
 *
 * \author C. Reimers and M. Rockenbauer 24.10.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include <Services/General/CrPsPktServHkSupp.h>
#include "Services/General/CrPsPktUtil.h"
#include "CrPsUserConstants.h"
#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServHk.h>
#include <Services/General/CrPsPktServHk.h>
#include <string.h>
#include <Pckt/CrFwPckt.h>


/**
 * Get the offset of the "SCSampleRepNum" field in a HkCreate packet.
 * The offset depend on the "NFA" Value.
 * \param p Pointer to the packet.
 * \param NFA Value
 * \return the offset of the "NFA" th. "SCSampleRepNum" field.
 */
CrPsRepNum_t getHkCreateCmdOffsetSCS(void* p, CrFwCounterU4_t NFA)
{
  uint32_t        pos, n2val;
  CrFwCounterU4_t N1, i;

  N1 = getHkCreateCmdN1(p);
  pos = sizeof(TcHeader_t)+sizeof(CrPsSid_t)+sizeof(CrPsCollectInterval_t)+sizeof(CrFwCounterU4_t)+(sizeof(CrPsParamId_t)*N1) + sizeof(CrFwCounterU4_t);
  for (i=1;i<NFA;i++)
    {
      pos += sizeof(CrPsRepNum_t);
      n2val = getPcktInt(p, pos);
      pos += sizeof(CrFwCounterU4_t) + n2val*sizeof(CrPsParamId_t);
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
uint32_t getHkCreateCmdOffsetN2(void* p, CrFwCounterU4_t NFA)
{
  return getHkCreateCmdOffsetSCS(p, NFA)+sizeof(CrPsRepNum_t);
}

/**
 * Get the offset of the "N2ParamId" field in a HkCreate packet.
 * The offset depend on the "NFA" and the N2 Value.
 * \param p Pointer to the packet.
 * \param NFA Value
 * \param N2 Value
 * \return the offset of the "NFA" th. Group and the "N2" th. N2ParamId field.
 */
uint32_t getHkCreateCmdOffsetN2ParamId(void* p, CrFwCounterU4_t NFA, CrFwCounterU4_t N2)
{
  if (N2>0)
  {
    N2 = N2-1;
  }
  return getHkCreateCmdOffsetN2(p, NFA) + sizeof(CrFwCounterU4_t) + N2*sizeof(CrPsParamId_t);
}

/**
 * Get "NFA" from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "NFA".
 */
CrFwCounterU4_t getHkCreateCmdNFA(void* p)
{
  uint32_t pos;
  CrFwCounterU4_t ret;

  pos = sizeof(TcHeader_t)+sizeof(CrPsSid_t)+sizeof(CrPsCollectInterval_t)+sizeof(CrFwCounterU4_t)+(sizeof(CrPsParamId_t)*getHkCreateCmdN1(p));
  memcpy(&ret, &((uint8_t*)p)[pos], sizeof(CrFwCounterU4_t));
  return __builtin_bswap32(ret);
}

/**
 * Set "NFA" in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of "NFA" to be set in packet.
 */
void setHkCreateCmdNFA(void* p, CrFwCounterU4_t NFA)
{
  uint32_t pos;

  pos = sizeof(TcHeader_t)+sizeof(CrPsSid_t)+sizeof(CrPsCollectInterval_t)+sizeof(CrFwCounterU4_t)+(sizeof(CrPsParamId_t)*getHkCreateCmdN1(p));
  NFA = __builtin_bswap32(NFA);
  memcpy(&((uint8_t*)p)[pos], &NFA, sizeof(NFA));
}

/**
 * Get "N1ParamId" arrayItem from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of ParamIdArray Item.
 * \return N1ParamId Array Item Value.
 */
CrPsParamId_t getHkCreateCmdN1ParamIdItem(void* p, CrFwCounterU4_t N)
{
  CrPsParamId_t ret;
  uint32_t pos;

  if(N>0)
    {
      N=N-1;
    }
  pos = sizeof(TcHeader_t)+sizeof(CrPsSid_t)+sizeof(CrPsCollectInterval_t)+sizeof(CrFwCounterU4_t)+(sizeof(CrPsParamId_t)*N);
  memcpy(&ret, &((uint8_t*)p)[pos], sizeof(CrPsParamId_t));
  return __builtin_bswap16(ret);
}

/**
 * Set "N1ParamId" arrayItem in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of the "N" th ParamIdArray Item.
 * \param N1ParamId Variable from where arrayItem data are copied.
 */
void setHkCreateCmdN1ParamIdItem(void* p, CrFwCounterU4_t N, CrPsParamId_t N1ParamId)
{
  uint32_t pos;

  if(N>0)
    {
      N=N-1;
    }
  pos = sizeof(TcHeader_t)+sizeof(CrPsSid_t)+sizeof(CrPsCollectInterval_t)+sizeof(CrFwCounterU4_t)+(sizeof(CrPsParamId_t)*N);
  N1ParamId = __builtin_bswap16(N1ParamId);
  memcpy(&((uint8_t*)p)[pos], &N1ParamId, sizeof(N1ParamId));
}

/**
 * Get "N2" from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \return Value of "N2".
 */
CrFwCounterU4_t getHkCreateCmdN2(void* p, CrFwCounterU4_t NFA)
{
  CrFwCounterU4_t ret;
  
  memcpy(&ret, &((uint8_t*)p)[getHkCreateCmdOffsetN2(p, NFA)], sizeof(CrFwCounterU4_t));
  return __builtin_bswap32(ret);
}

/**
 * Set "N2" in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param N2 Value of "N2" to be set in packet.
 */
void setHkCreateCmdN2(void* p, CrFwCounterU4_t NFA, CrFwCounterU4_t N2)
{
  N2 = __builtin_bswap32(N2);
  memcpy(&((uint8_t*)p)[getHkCreateCmdOffsetN2(p, NFA)], &N2, sizeof(CrFwCounterU4_t));
}

/**
 * Get "SCSampleRepNum" from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \return Value of "SCSampleRepNum".
 */
CrPsRepNum_t getHkCreateCmdSCSampleRepNumItem(void* p, CrFwCounterU4_t NFA)
{
  CrPsRepNum_t ret;

  memcpy(&ret, &((uint8_t*)p)[getHkCreateCmdOffsetSCS(p, NFA)], sizeof(CrPsRepNum_t));
  return __builtin_bswap32(ret);
}

/**
 * Set "SCSampleRepNum" in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param SCSampleRepNum Value of "SCSampleRepNum" to be set in packet.
 */
void setHkCreateCmdSCSampleRepNumItem(void* p, CrFwCounterU4_t NFA, CrPsRepNum_t SCSampleRepNum)
{
  SCSampleRepNum = __builtin_bswap32(SCSampleRepNum);
  memcpy(&((uint8_t*)p)[getHkCreateCmdOffsetSCS(p, NFA)], &SCSampleRepNum, sizeof(CrPsRepNum_t));
}

/**
 * Get "N2ParamID" from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param N2 Value of the "N2" th Item.
 * \return Value of "N2ParamID".
 */
CrPsParamId_t getHkCreateCmdN2ParamIdItem(void* p, CrFwCounterU4_t NFA, CrFwCounterU4_t N2)
{
  CrPsParamId_t ret;

  memcpy(&ret, &((uint8_t*)p)[getHkCreateCmdOffsetN2ParamId(p, NFA, N2)], sizeof(CrPsParamId_t));
  return __builtin_bswap16(ret);
}

/**
 * Set "N2ParamID" in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param N2 Value of the "N2" th Item.
 * \param N2ParamId Value of "N2ParamID" to be set in packet.
 */
void setHkCreateCmdN2ParamIdItem(void* p, CrFwCounterU4_t NFA, CrFwCounterU4_t N2, CrPsParamId_t N2ParamId)
{

  N2ParamId = __builtin_bswap16(N2ParamId);
  memcpy(&((uint8_t*)p)[getHkCreateCmdOffsetN2ParamId(p, NFA, N2)], &N2ParamId, sizeof(CrPsParamId_t));
}

/**
 * Get the offset of the "SCSampleRepNum" field in a HkRepStruct packet.
 * The offset depend on the "NFA" Value.
 * \param p Pointer to the packet.
 * \param NFA Value
 * \return the offset of the "NFA" th. "SCSampleRepNum" field.
 */
uint32_t getHkRepStructRepOffsetSCS(void* p, CrFwCounterU4_t NFA)
{
  uint32_t        pos, n2val;
  CrFwCounterU4_t i, N1;

  N1 = getHkRepStructRepN1(p);
  pos = sizeof(TmHeader_t)+sizeof(CrPsSid_t)+sizeof(CrPsStatus_t)+sizeof(CrPsCollectInterval_t)+sizeof(CrFwCounterU4_t)+sizeof(CrPsParamId_t)*N1 + sizeof(CrFwCounterU4_t);
  
  for (i=1;i<NFA;i++)
    {
      pos = pos + sizeof(CrPsRepNum_t);
      n2val = getPcktInt(p, pos);
      pos = pos + sizeof(CrFwCounterU4_t) + n2val*sizeof(CrPsParamId_t);
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
uint32_t getHkRepStructRepOffsetN2(void* p, CrFwCounterU4_t NFA)
{
  return getHkRepStructRepOffsetSCS(p, NFA)+sizeof(CrPsRepNum_t);
}

/**
 * Get the offset of the "N2ParamId" field in a HkCreate packet.
 * The offset depend on the "NFA" and the N2 Value.
 * \param p Pointer to the packet.
 * \param NFA Value
 * \param N2 Value
 * \return the offset of the "NFA" th. Group and the "N2" th. N2ParamId field.
 */
uint32_t getHkRepStructRepOffsetN2ParamId(void* p, CrFwCounterU4_t NFA, CrFwCounterU4_t N2)
{
  if (N2>0)
  {
    N2 = N2-1;
  }
  return getHkRepStructRepOffsetN2(p, NFA) + sizeof(CrFwCounterU4_t) + N2*sizeof(CrPsParamId_t);
}

/**
 * Get "NFA" from "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "NFA".
 */                    
CrFwCounterU4_t getHkRepStructRepNFA(void* p)
{
  uint32_t        pos;
  CrFwCounterU4_t ret;

  pos = sizeof(TmHeader_t)+sizeof(CrPsSid_t)+sizeof(CrPsStatus_t)+sizeof(CrPsCollectInterval_t)+sizeof(CrFwCounterU4_t)+sizeof(CrPsParamId_t)*getHkRepStructRepN1(p);
  memcpy(&ret, &((uint8_t*)p)[pos], sizeof(CrFwCounterU4_t));
  return __builtin_bswap32(ret);
}

/**
 * Set "NFA" in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param src Value of "NFA" to be set in packet.
 */
void setHkRepStructRepNFA(void* p, CrFwCounterU4_t src)
{
  uint32_t pos;

  pos = sizeof(TmHeader_t)+sizeof(CrPsSid_t)+sizeof(CrPsStatus_t)+sizeof(CrPsCollectInterval_t)+sizeof(CrFwCounterU4_t)+sizeof(CrPsParamId_t)*getHkRepStructRepN1(p);
  src = __builtin_bswap32(src);
  memcpy(&((uint8_t*)p)[pos], &src, sizeof(CrFwCounterU4_t));
}

/**
 * Get "N1ParamId" arrayItem from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param N Number of ParamIdArray Item.
 * \return N2ParamId "N" th Array Item Value.
 */
CrPsParamId_t getHkRepStructRepN1ParamIdItem(void* p, CrFwCounterU4_t N)
{
  CrPsParamId_t ret;
  uint32_t pos;

  if(N>0)
    {
      N=N-1;
    }
  pos = sizeof(TmHeader_t)+sizeof(CrPsSid_t)+sizeof(CrPsStatus_t)+sizeof(CrPsCollectInterval_t)+sizeof(CrFwCounterU4_t)+sizeof(CrPsParamId_t)*N;
  memcpy(&ret, &((uint8_t*)p)[pos], sizeof(CrPsParamId_t));
  return __builtin_bswap16(ret);
}

/**
 * Set "N1ParamId" arrayItem in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param N Number of ParamIdArray Item.
 * \param src Variable from where arrayItem data are copied.
 */
void setHkRepStructRepN1ParamIdItem(void* p, CrFwCounterU4_t N, CrPsParamId_t src)
{
  uint32_t pos;

  if(N>0)
    {
      N=N-1;
    }
  pos = sizeof(TmHeader_t)+sizeof(CrPsSid_t)+sizeof(CrPsStatus_t)+sizeof(CrPsCollectInterval_t)+sizeof(CrFwCounterU4_t)+sizeof(CrPsParamId_t)*N;
  src = __builtin_bswap16(src);
  memcpy(&((uint8_t*)p)[pos], &src, sizeof(CrPsParamId_t));
}

/**
 * Get "N2" from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \return Value of "N2".
 */
CrFwCounterU4_t getHkRepStructRepN2(void* p, CrFwCounterU4_t NFA)
{
  CrFwCounterU4_t ret;

  memcpy(&ret, &((uint8_t*)p)[getHkRepStructRepOffsetN2(p, NFA)], sizeof(CrFwCounterU4_t));
  return __builtin_bswap32(ret);
}

/**
 * Set "N2" in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param N2 Value of "N2" to be set in packet.
 */
void setHkRepStructRepN2(void* p, CrFwCounterU4_t NFA, CrFwCounterU4_t N2)
{

  N2 = __builtin_bswap32(N2);
  memcpy(&((uint8_t*)p)[getHkRepStructRepOffsetN2(p, NFA)], &N2, sizeof(CrFwCounterU4_t));
}

/**
 * Get "SCSampleRepNum" from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \return Value of "SCSampleRepNum".
 */
CrPsRepNum_t getHkRepStructRepSCSampleRepNumItem(void* p, CrFwCounterU4_t NFA)
{
  CrPsRepNum_t ret;

  memcpy(&ret, &((uint8_t*)p)[getHkRepStructRepOffsetSCS(p, NFA)], sizeof(CrPsRepNum_t));
  return __builtin_bswap32(ret);
}

/**
 * Set "SCSampleRepNum" in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param src Value of "SCSampleRepNum" to be set in packet.
 */
void setHkRepStructRepSCSampleRepNumItem(void* p, CrFwCounterU4_t NFA, CrPsRepNum_t src)
{
  src = __builtin_bswap32(src);
  memcpy(&((uint8_t*)p)[getHkRepStructRepOffsetSCS(p, NFA)], &src, sizeof(CrPsRepNum_t));
}

/**
 * Get "N2ParamID" from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param N2 Value of the "N2" th Item.
 * \return Value of "N2ParamID".
 */
CrPsParamId_t getHkRepStructRepN2ParamIdItem(void* p, CrFwCounterU4_t NFA, CrFwCounterU4_t N2)
{
  uint16_t ret;

  memcpy(&ret, &((uint8_t*)p)[getHkRepStructRepOffsetN2ParamId(p, NFA, N2)], sizeof(CrPsParamId_t));
  return __builtin_bswap16(ret);
}

/**
 * Set "N2ParamID" in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param N2 Value of the "N2" th Item.
 * \param src Value of "N2ParamID" to be set in packet.
 */
void setHkRepStructRepN2ParamIdItem(void* p, CrFwCounterU4_t NFA, CrFwCounterU4_t N2, CrPsParamId_t src)
{
  src = __builtin_bswap16(src);
  memcpy(&((uint8_t*)p)[getHkRepStructRepOffsetN2ParamId(p, NFA, N2)], &src, sizeof(CrPsParamId_t));
}

/**
 * Get "RepStrucId" from "HkDeleteCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \return Value of "RepStrucId" the "N" th Item of the array.
 */
CrPsSid_t getHkDeleteCmdRepStrucIdItem(void* p, CrFwCounterU4_t N)
{
  CrPsSid_t dest;

  memcpy(&dest, &((uint8_t*)p)[sizeof(TcHeader_t)-1+sizeof(CrFwCounterU4_t)+sizeof(CrPsSid_t)*N], sizeof(CrPsSid_t));
  return dest;
}

/**
 * Set "RepStrucId" in "HkDeleteCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of ParamIdArray Item.
 * \param RepStrucId Value of "RepStrucId" to be set in packet.
 */
void setHkDeleteCmdRepStrucIdItem(void* p, CrFwCounterU4_t N, CrPsSid_t RepStrucId)
{
  memcpy(&((uint8_t*)p)[sizeof(TcHeader_t)-1+sizeof(CrFwCounterU4_t)+sizeof(CrPsSid_t)*N], &RepStrucId, sizeof(CrPsSid_t));  
}

/**
 * Get "RepStrucId" from "HkEnableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of ParamIdArray Item.
 * \return Value of "RepStrucId" the "N" th Item of the array.
 */
CrPsSid_t getHkEnableCmdRepStrucIdItem(void* p, CrFwCounterU4_t N)
{
  CrPsSid_t dest;

  memcpy(&dest, &((uint8_t*)p)[sizeof(TcHeader_t)-1+sizeof(CrFwCounterU4_t)+sizeof(CrPsSid_t)*N], sizeof(CrPsSid_t));
  return dest;
}

/**
 * Set "RepStrucId" in "HkEnableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \param RepStrucId Value of "RepStrucId" to be set in packet.
 */
void setHkEnableCmdRepStrucIdItem(void* p, CrFwCounterU4_t N, CrPsSid_t RepStrucId)
{
  memcpy(&((uint8_t*)p)[sizeof(TcHeader_t)-1+sizeof(CrFwCounterU4_t)+sizeof(CrPsSid_t)*N], &RepStrucId, sizeof(CrFwCounterU4_t));
}

/**
 * Get "RepStrucId" from "HkDisableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \return Value of "RepStrucId" the "N" th Item of the array.
 */
CrPsSid_t getHkDisableCmdRepStrucIdItem(void* p, CrFwCounterU4_t N)
{
  CrPsSid_t dest;

  memcpy(&dest, &((uint8_t*)p)[sizeof(TcHeader_t)-1+sizeof(CrFwCounterU4_t)+sizeof(CrPsSid_t)*N], sizeof(CrPsSid_t));
  return dest;
}

/**
 * Set "RepStrucId" in "HkDisableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \param RepStrucId Value of "RepStrucId" to be set in packet.
 */
void setHkDisableCmdRepStrucIdItem(void* p, CrFwCounterU4_t N, CrPsSid_t RepStrucId)
{
  memcpy(&((uint8_t*)p)[sizeof(TcHeader_t)-1+sizeof(CrFwCounterU4_t)+sizeof(CrPsSid_t)*N], &RepStrucId, sizeof(CrFwCounterU4_t));
}

/**
 * Get "RepStrucId" from "HkRepStructCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \return Value of "RepStrucId" the "N" th Item of the array.
 */
CrPsSid_t getHkRepStructCmdRepStrucIdItem(void* p, CrFwCounterU4_t N)
{
  CrPsSid_t dest;

  memcpy(&dest, &((uint8_t*)p)[sizeof(TcHeader_t)-1+sizeof(CrFwCounterU4_t)+sizeof(CrPsSid_t)*N], sizeof(CrPsSid_t));
  return dest;
}

/**
 * Set "RepStrucId" in "HkRepStructCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \param RepStrucId Value of "RepStrucId" to be set in packet.
 */
void setHkRepStructCmdRepStrucIdItem(void* p, CrFwCounterU4_t N, CrPsSid_t RepStrucId)
{
  memcpy(&((uint8_t*)p)[sizeof(TcHeader_t)-1+sizeof(CrFwCounterU4_t)+sizeof(CrPsSid_t)*N], &RepStrucId, sizeof(CrFwCounterU4_t));
}

/**
 * Get "RepStrucId" from "HkOneShotCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \return Value of "RepStrucId" the "N" th Item of the array.
 */
CrPsSid_t getHkOneShotCmdRepStrucIdItem(void* p, CrFwCounterU4_t N)
{
  CrPsSid_t dest;

  memcpy(&dest, &((uint8_t*)p)[sizeof(TcHeader_t)-1+sizeof(CrFwCounterU4_t)+sizeof(CrPsSid_t)*N], sizeof(CrPsSid_t));
  return dest;
}

/**
 * Set "RepStrucId" in "HkOneShotCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \param RepStrucId Value of "RepStrucId" to be set in packet.
 */
void setHkOneShotCmdRepStrucIdItem(void* p, CrFwCounterU4_t N, CrPsSid_t RepStrucId)
{
  memcpy(&((uint8_t*)p)[sizeof(TcHeader_t)-1+sizeof(CrFwCounterU4_t)+sizeof(CrPsSid_t)*N], &RepStrucId, sizeof(CrFwCounterU4_t));
}


size_t getHkRepStructSize(CrPsSid_t sid)
{
  size_t          s;
  CrPsSid_t       rdlSid, rdlSlot;
  CrFwCounterU4_t N1, N2, NFA, i;

  s=sizeof(TmHeader_t) + sizeof(CrPsSid_t) + sizeof(CrPsStatus_t) + sizeof(CrPsCollectInterval_t) + sizeof(CrFwCounterU4_t) + sizeof(CrFwCounterU4_t) + 2;

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {
      rdlSid = getDpsidItem(rdlSlot);

      if (sid == rdlSid)
        break;
    }  

  N1 = getDpnSimpleItem(rdlSlot);
  s+=N1*sizeof(CrPsParamId_t);

  NFA = getNFA(rdlSlot);
  for(i=0;i<NFA;i++)
    {
      s+=sizeof(unsigned int) + sizeof(unsigned int);
      N2 = getDplstNSampRepItem(rdlSlot*HK_MAX_N_GR + i);
      s+=N2*sizeof(CrPsParamId_t);
    }

  return s;
}

#if 0
size_t getHkRepSizeFromDp(CrPsSid_t sid)
{
  size_t          s;
  CrPsSid_t       rdlSid, rdlSlot;
  CrFwCounterU4_t N1, N2, NFA, i, k;
  CrPsParamId_t   N1ParamId, N2ParamId;
  CrPsRepNum_t    SCSampleRepNum, j;
  unsigned int    offset;

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {
      rdlSid = getDpsidItem(rdlSlot);

      if (sid == rdlSid)
        break;
    }

  s=sizeof(TmHeader_t) + sizeof(CrPsSid_t) + 2;

  /* Get N1 (nSimple) from data pool, the number of simple commutated data items */
  N1 = getDpnSimpleItem(rdlSlot);

  if (N1!=0)
    {
      /* Get N1 parameter IDs and put the corresponding values in the out-going packet */ 
      for (i=0; i<N1; i++)
        {
          /* Get value for N1ParamId from data pool */ 
          N1ParamId = getDplstIdItem(rdlSlot*HK_MAX_N_ITEMS + i);
          s += getDpSize(N1ParamId);
        }
    }

  NFA = getNFA(rdlSlot);

  if (NFA!=0)
    {
      offset = 0;

      for (k=0; k<NFA; k++)
        {
          /* Get sample repetition number (rep[1..nGroup]) */
          SCSampleRepNum = getDplstSampleRepItem(rdlSlot*HK_MAX_N_GR + k);

          /* Get N2 (nRep[1..nGroup]) */
          N2 = getDplstNSampRepItem(rdlSlot*HK_MAX_N_GR + k);

          for (i=0; i<SCSampleRepNum; i++)
            {
              for (j=0; j<N2; j++)
                {
                  N2ParamId = getDplstIdItem(rdlSlot*HK_MAX_N_ITEMS + N1 + offset + j);

                  /* Set value in out-going packet */
                  s += getDpSize(N2ParamId);
                }
            }
          /* update offset */
          offset += N2;
        }
    }
  return s;
}
#endif

size_t getHkRepSizeFromPckt(void* p)
{
  size_t          s, N2ParamIdSize;
  CrFwCounterU4_t N1, NFA, N2, j, k;
  CrPsRepNum_t    SCSampleRepNum;
  CrPsParamId_t   N1ParamId, N2ParamId;  

  s=sizeof(TmHeader_t) + sizeof(CrPsSid_t) + 2;
  N1 = getHkCreateCmdN1(p);
  for(j=1;j<=N1;j++)
    {
      N1ParamId = getHkCreateCmdN1ParamIdItem(p, j);
      s+=getDpSize(N1ParamId);
    }
  NFA = getHkCreateCmdNFA(p);
  for(j=1;j<=NFA;j++)
    {
      SCSampleRepNum = getHkCreateCmdSCSampleRepNumItem(p,j);
      N2 = getHkCreateCmdN2(p,j);
      for(k=1;k<=N2;k++)
        {
          N2ParamId = getHkCreateCmdN2ParamIdItem(p, j, k);
          N2ParamIdSize = getDpSize(N2ParamId);
          s+=SCSampleRepNum*N2ParamIdSize;
        }
    }
  return s; 
}


/**
 * Get the size of a Housekeeping packet.
 * \param p Pointer to the packet.
 * \return the size of the packet in bytes.
 */
size_t getHkPcktSize(void* p)
{
  size_t            s;
  CrFwServSubType_t subserv;
  CrFwCounterU4_t   j, k, N, N1, NFA, N2;
  CrPsSid_t         sid, rdlSid, N1ParamId;
  CrFwCounterU1_t   rdlSlot;

  subserv = CrFwPcktGetServSubType(p);

  switch (subserv)
  {
    case 1:
    case 2:
      s=sizeof(TcHeader_t) + sizeof(CrPsSid_t) + sizeof(CrPsCollectInterval_t) + sizeof(CrFwCounterU4_t);
      N1 = getHkCreateCmdN1(p);
      for(j=1;j<=N1;j++)
      {
        s+=sizeof(CrPsParamId_t);
      }
      s+=sizeof(CrFwCounterU4_t);
      NFA = getHkCreateCmdNFA(p);
      for(j=1;j<=NFA;j++)
      {
        s+=sizeof(CrPsRepNum_t) + sizeof(CrFwCounterU4_t);
        N2 = getHkCreateCmdN2(p,j);
        for(k=1;k<=N2;k++)
        {
          s+=sizeof(CrPsParamId_t);
        }
      }
      return s;    
    case 3:
    case 4:
      s=sizeof(TcHeader_t) + sizeof(CrFwCounterU4_t);
      N = getHkDeleteCmdN(p);
      for(j=1;j<=N;j++)
      {
        s+=sizeof(CrPsSid_t);
      }
      return s;
    case 5:
    case 7:
      s=sizeof(TcHeader_t) + sizeof(CrFwCounterU4_t);
      N = getHkEnableCmdN(p);      
      for(j=1;j<=N;j++)
      {
        s+=sizeof(CrPsSid_t);
      }
      return s;
    case 6:
    case 8:
      N = getHkDisableCmdN(p);  
      s=sizeof(TcHeader_t) + sizeof(CrFwCounterU4_t);
      for(j=1;j<=N;j++)
      {
        s+=sizeof(CrPsSid_t);
      }
      return s;
    case 9:
    case 11:
      s=sizeof(TcHeader_t) + sizeof(CrFwCounterU4_t);
      N = getHkRepStructCmdN(p);      
      for(j=1;j<=N;j++)
      {
        s+=sizeof(CrPsSid_t);
      }
      return s;
    case 10:
    case 12:
      s=sizeof(TmHeader_t) + sizeof(CrPsSid_t) + sizeof(CrPsStatus_t) + sizeof(CrPsCollectInterval_t) + sizeof(CrFwCounterU4_t);
      N1 = getHkRepStructRepN1(p);
      for(j=1;j<=N1;j++)
      {
        s+=sizeof(CrPsParamId_t);
      }
      s+=sizeof(CrFwCounterU4_t);
      NFA = getHkRepStructRepNFA(p);
      for(j=1;j<=NFA;j++)
      {
        s+=sizeof(CrPsRepNum_t) + sizeof(CrFwCounterU4_t);
        N2 = getHkRepStructRepN2(p,j);
        for(k=1;k<=N2;k++)
        {
          s+=sizeof(CrPsParamId_t);
        }
      }
      return s; 
    case 25:
    case 26:
      s=sizeof(TmHeader_t) + sizeof(CrPsSid_t);
      sid = (CrPsSid_t )CrFwPcktGetDiscriminant(p);

      /* look for the slot */
      for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
        {
          rdlSid = getDpsidItem(rdlSlot);
          if (sid == rdlSid)
            break;
        }

      /* Get N1 (nSimple) from data pool, the number of simple commutated data items */
      N1 = getDpnSimpleItem(rdlSlot);
      if (N1!=0)
        {
          /* Get N1 parameter IDs and put the corresponding values in the out-going packet */ 
          for (j=0; j<N1; j++)
            {
              /* Get value for N1ParamId from data pool */ 
              N1ParamId = getDplstIdItem(rdlSlot*HK_MAX_N_ITEMS + j);
              s += getDpSize(N1ParamId);
            }
        }
      return s;
    case 27:
    case 28:
      s=sizeof(TcHeader_t) + sizeof(CrFwCounterU4_t);
      N = getHkRepStructCmdN(p);      
      for(j=1;j<=N;j++)
      {
        s+=sizeof(CrPsSid_t);
      }
      return s;           
    default:
      return 0;
  }
}

/*----------------------------------------------------------------------------*/

