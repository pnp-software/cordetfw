/**
 * @file CrPsParamSetter.c
 * @ingroup CrPsServicesGeneral
 *
 * @brief Implementation of the setter operations for all parameters of all out-going packets.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsParamSetter.h"

#include "CrPsConstants.h"

#include "CrFwCmpData.h"
#include "FwSmConfig.h"

#include <string.h>
#include <stdio.h>
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"


/* ------------------------------------------------------------------------------------ */
/* TODO: use fast version of PutNBits32 instead of this slow function */
void PutBit8 (unsigned char value, unsigned int bitOffset, unsigned char *dest)
{
  unsigned int bytepos, bitpos;
  unsigned char destval, mask;

  bytepos = bitOffset >> 3; /* division by 8 */
  bitpos = bitOffset - 8*bytepos;

  /* shape a mask with the required bit set true */
  mask = 1 << (7-bitpos);

  /* get the destination byte and clear the bit */
  destval = dest[bytepos];
  destval &= ~mask;

  /* set bit if the value was true */
  if (value)
    destval |= mask;

  /* write it back */
  dest[bytepos] = destval;

  return;
}

/* ------------------------------------------------------------------------------------ */
void PutNBits8 (unsigned int value, unsigned int bitOffset, unsigned int nbits, unsigned char *dest)
{
  unsigned int i;
  unsigned char bitvalue;

  for (i=0; i<nbits; i++)
    {
      bitvalue = (unsigned char)((value >> (nbits - 1 - i)) & 1);
      PutBit8 (bitvalue, bitOffset + i, dest);
    }

  return;
}

/* ==================================================================================== */
void CrPsServReqVerifAccSuccParamSetTcPacketId(FwSmDesc_t smDesc, unsigned short tcPacketId)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 0] = (tcPacketId >> 8) & 0xFF;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 1] = (tcPacketId & 0xFF);
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifAccSuccParamSetTcPacketSeqCtrl(FwSmDesc_t smDesc, unsigned short tcPacketSeqCtrl)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 2] = (tcPacketSeqCtrl >> 8) & 0xFF;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 3] = (tcPacketSeqCtrl & 0xFF);
  return;
}

/* ==================================================================================== */
void CrPsServTestOnBoardConnectParamSetAppId(FwSmDesc_t smDesc, unsigned short appId)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 0] = (appId >> 8) & 0xFF;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 1] = (appId & 0xFF);
  return;
}

/* ==================================================================================== */
void CrPsServReqVerifAccFailParamSetPacketId(FwSmDesc_t smDesc, unsigned short packetId)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 0] = (packetId >> 8) & 0xFF;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 1] = (packetId & 0xFF);
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifAccFailParamSetFailureCode(FwSmDesc_t smDesc, unsigned short failureCode)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 2] = (failureCode >> 8) & 0xFF;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 3] = (failureCode & 0xFF);
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifAccFailParamSetType(FwSmDesc_t smDesc, unsigned char type)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 4] = type;
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifAccFailParamSetSubtype(FwSmDesc_t smDesc, unsigned char subType)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 5] = subType;
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifAccFailParamSetDiscriminant(FwSmDesc_t smDesc, unsigned char discriminant)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 6] = discriminant;
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifAccFailParamSetVerFailData(FwSmDesc_t smDesc, unsigned int verFailData)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 7] = ( verFailData >> 24) & 0xFF;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 8] = ((verFailData >> 16) & 0xFF);
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 9] = ((verFailData >> 8 ) & 0xFF);
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10] = ( verFailData & 0xFF);

  return;
}

/* ==================================================================================== */
void CrPsServReqVerifVerSuccParamSetPacketId(FwSmDesc_t smDesc, unsigned short packetId)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 0] = (packetId >> 8) & 0xFF;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 1] = (packetId & 0xFF);
  return;
}

/* ==================================================================================== */
void CrPsServReqVerifVerFailParamSetPacketId(FwSmDesc_t smDesc, unsigned short packetId)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 0] = (packetId >> 8) & 0xFF;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 1] = (packetId & 0xFF);
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifVerFailParamSetFailureCode(FwSmDesc_t smDesc, unsigned short failureCode)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 2] = (failureCode >> 8) & 0xFF;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 3] = (failureCode & 0xFF);
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifVerFailParamSetType(FwSmDesc_t smDesc, unsigned char type)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 4] = type;
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifVerFailParamSetSubtype(FwSmDesc_t smDesc, unsigned char subType)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 5] = subType;
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifVerFailParamSetDiscriminant(FwSmDesc_t smDesc, unsigned char discriminant)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 6] = discriminant;
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifVerFailParamSetVerFailData(FwSmDesc_t smDesc, unsigned int verFailData)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 7] = ( verFailData >> 24) & 0xFF;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 8] = ((verFailData >> 16) & 0xFF);
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 9] = ((verFailData >> 8 ) & 0xFF);
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10] = ( verFailData & 0xFF);

  return;
}

/* ==================================================================================== */
void CrPsServReqVerifPrgrSuccParamSetPacketId(FwSmDesc_t smDesc, unsigned short packetId)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 0] = (packetId >> 8) & 0xFF;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 1] = (packetId & 0xFF);
  return;
}

void CrPsServReqVerifPrgrSuccParamSetStepId(FwSmDesc_t smDesc, unsigned short stepId)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 2] = (stepId >> 8) & 0xFF;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 3] = (stepId & 0xFF);
  return;
}

/* ==================================================================================== */
void CrPsServReqVerifPrgrFailParamSetPacketId(FwSmDesc_t smDesc, unsigned short packetId)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 0] = (packetId >> 8) & 0xFF;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 1] = (packetId & 0xFF);
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifPrgrFailParamSetStepId(FwSmDesc_t smDesc, unsigned short stepId)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 2] = (stepId >> 8) & 0xFF;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 3] = (stepId & 0xFF);
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifPrgrFailParamSetFailureCode(FwSmDesc_t smDesc, unsigned short failureCode)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 4] = (failureCode >> 8) & 0xFF;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 5] = (failureCode & 0xFF);
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifPrgrFailParamSetType(FwSmDesc_t smDesc, unsigned char type)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 6] = type;
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifPrgrFailParamSetSubtype(FwSmDesc_t smDesc, unsigned char subType)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 7] = subType;
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifPrgrFailParamSetDiscriminant(FwSmDesc_t smDesc, unsigned char discriminant)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 8] = discriminant;
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifPrgrFailParamSetVerFailData(FwSmDesc_t smDesc, unsigned int verFailData)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 9] = ( verFailData >> 24) & 0xFF;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10] = ((verFailData >> 16) & 0xFF);
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 11] = ((verFailData >> 8 ) & 0xFF);
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 12] = ( verFailData & 0xFF);

  return;
}

/* ==================================================================================== */
/**
 * Generic setter
 * Set data at specific position in data segment of PUS packet
 */
void CrPsSetUCharValue(FwSmDesc_t smDesc, unsigned char ucharValue, unsigned int pos)
{
    CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
    /*error if the Type does not match*/
    if((CrFwCmpGetTypeId(smDesc) != CR_FW_OUTCMP_TYPE) && (CrFwCmpGetTypeId(smDesc) != CR_FW_INREPORT_TYPE) && (CrFwCmpGetTypeId(smDesc) != CR_FW_INCOMMAND_TYPE))
    {
        printf("ERROR: smDesc TypeId does not match!! \n");
        return;
    }  
    
    if(CrFwCmpGetTypeId(smDesc) == CR_FW_OUTCMP_TYPE) /*OutComponent*/
    {
      pos=pos+OFFSET_PAR_LENGTH_OUT_REP_PCKT;
      CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
      if(pos > (unsigned int)(CrFwPcktGetLength(cmpSpecificData->pckt))-3)
      {
          printf("ERROR: The position is outside the package!! \n");
          return;
      }
      printf("CrFwPcktGetMaxLength: %d \n",CrFwPcktGetMaxLength(cmpSpecificData->pckt));
      printf("CrFwPcktGetLength: %d \n",CrFwPcktGetLength(cmpSpecificData->pckt));
      printf("CrFwPcktGetParLength: %d \n",CrFwPcktGetParLength(cmpSpecificData->pckt));
      cmpSpecificData->pckt[pos] = ucharValue;
    }
    
    if(CrFwCmpGetTypeId(smDesc) == CR_FW_INREPORT_TYPE) /*InReport*/
    {
      pos=pos+OFFSET_PAR_LENGTH_OUT_REP_PCKT;
      CrFwInRepData_t* cmpSpecificData = (CrFwInRepData_t*)(cmpData->cmpSpecificData);
      if(pos>(unsigned int)CrFwPcktGetLength(cmpSpecificData->pckt)-3)
      {
          printf("ERROR: The position is outside the package!! \n");
          return;
      }
      printf("CrFwPcktGetMaxLength: %d \n",CrFwPcktGetMaxLength(cmpSpecificData->pckt));
      printf("CrFwPcktGetLength: %d \n",CrFwPcktGetLength(cmpSpecificData->pckt));
      printf("CrFwPcktGetParLength: %d \n",CrFwPcktGetParLength(cmpSpecificData->pckt));
      cmpSpecificData->pckt[pos] = ucharValue;
    }
    
    if(CrFwCmpGetTypeId(smDesc) == CR_FW_INCOMMAND_TYPE) /*InCommand*/
    {
      pos=pos+OFFSET_PAR_LENGTH_IN_CMD_PCKT;
      CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
      if(pos>(unsigned int)CrFwPcktGetLength(cmpSpecificData->pckt)-3)
      {
          printf("ERROR: The position is outside the package!! \n");
          return;
      }
      printf("CrFwPcktGetMaxLength: %d \n",CrFwPcktGetMaxLength(cmpSpecificData->pckt));
      printf("CrFwPcktGetLength: %d \n",CrFwPcktGetLength(cmpSpecificData->pckt));
      printf("CrFwPcktGetParLength: %d \n",CrFwPcktGetParLength(cmpSpecificData->pckt));
      cmpSpecificData->pckt[pos] = ucharValue;
    }    
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsSetUShortValue(FwSmDesc_t smDesc, unsigned short ushortValue, unsigned int pos)
{
    CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
    /*error if the Type does not match*/
    if((CrFwCmpGetTypeId(smDesc) != CR_FW_OUTCMP_TYPE) && (CrFwCmpGetTypeId(smDesc) != CR_FW_INREPORT_TYPE) && (CrFwCmpGetTypeId(smDesc) != CR_FW_INCOMMAND_TYPE))
    {
        printf("ERROR: smDesc TypeId does not match!! \n");
        return;
    } 
  
    if(CrFwCmpGetTypeId(smDesc) == CR_FW_OUTCMP_TYPE) /*OutComponent*/
    {
      pos=pos+OFFSET_PAR_LENGTH_OUT_REP_PCKT;
      CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
      if(pos > (unsigned int)(CrFwPcktGetLength(cmpSpecificData->pckt))-3)
      {
          printf("ERROR: The position is outside the package!! \n");
          return;
      }
      printf("CrFwPcktGetMaxLength: %d \n",CrFwPcktGetMaxLength(cmpSpecificData->pckt));
      printf("CrFwPcktGetLength: %d \n",CrFwPcktGetLength(cmpSpecificData->pckt));
      printf("CrFwPcktGetParLength: %d \n",CrFwPcktGetParLength(cmpSpecificData->pckt));
      cmpSpecificData->pckt[pos] = ((ushortValue >> 8 ) & 0xFF);
      cmpSpecificData->pckt[pos + 1] = ( ushortValue & 0xFF);
    }
    
    if(CrFwCmpGetTypeId(smDesc) == CR_FW_INREPORT_TYPE) /*InReport*/
    {
      pos=pos+OFFSET_PAR_LENGTH_OUT_REP_PCKT;
      CrFwInRepData_t* cmpSpecificData = (CrFwInRepData_t*)(cmpData->cmpSpecificData);
      if(pos>(unsigned int)CrFwPcktGetLength(cmpSpecificData->pckt)-3)
      {
          printf("ERROR: The position is outside the package!! \n");
          return;
      }
      printf("CrFwPcktGetMaxLength: %d \n",CrFwPcktGetMaxLength(cmpSpecificData->pckt));
      printf("CrFwPcktGetLength: %d \n",CrFwPcktGetLength(cmpSpecificData->pckt));
      printf("CrFwPcktGetParLength: %d \n",CrFwPcktGetParLength(cmpSpecificData->pckt));
      cmpSpecificData->pckt[pos] = ((ushortValue >> 8 ) & 0xFF);
      cmpSpecificData->pckt[pos + 1] = ( ushortValue & 0xFF);
    }
    
    if(CrFwCmpGetTypeId(smDesc) == CR_FW_INCOMMAND_TYPE) /*InCommand*/
    {
      pos=pos+OFFSET_PAR_LENGTH_IN_CMD_PCKT;
      CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
      if(pos>(unsigned int)CrFwPcktGetLength(cmpSpecificData->pckt)-3)
      {
          printf("ERROR: The position is outside the package!! \n");
          return;
      }
      printf("CrFwPcktGetMaxLength: %d \n",CrFwPcktGetMaxLength(cmpSpecificData->pckt));
      printf("CrFwPcktGetLength: %d \n",CrFwPcktGetLength(cmpSpecificData->pckt));
      printf("CrFwPcktGetParLength: %d \n",CrFwPcktGetParLength(cmpSpecificData->pckt));
      cmpSpecificData->pckt[pos] = ((ushortValue >> 8 ) & 0xFF);
      cmpSpecificData->pckt[pos + 1] = ( ushortValue & 0xFF);
    }  
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsSetUIntValue(FwSmDesc_t smDesc, unsigned int uintValue, unsigned int pos)
{
    CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
    /*error if the Type does not match*/
    if((CrFwCmpGetTypeId(smDesc) != CR_FW_OUTCMP_TYPE) && (CrFwCmpGetTypeId(smDesc) != CR_FW_INREPORT_TYPE) && (CrFwCmpGetTypeId(smDesc) != CR_FW_INCOMMAND_TYPE))
    {
        printf("ERROR: smDesc TypeId does not match!! \n");
        return;
    }
    
    if(CrFwCmpGetTypeId(smDesc) == CR_FW_OUTCMP_TYPE) /*OutComponent*/
    {
      pos=pos+OFFSET_PAR_LENGTH_OUT_REP_PCKT;
      CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
      if(pos > (unsigned int)(CrFwPcktGetLength(cmpSpecificData->pckt))-3)
      {
          printf("ERROR: The position is outside the package!! \n");
          return;
      }
      printf("CrFwPcktGetMaxLength: %d \n",CrFwPcktGetMaxLength(cmpSpecificData->pckt));
      printf("CrFwPcktGetLength: %d \n",CrFwPcktGetLength(cmpSpecificData->pckt));
      printf("CrFwPcktGetParLength: %d \n",CrFwPcktGetParLength(cmpSpecificData->pckt));
      cmpSpecificData->pckt[pos] = ( uintValue >> 24) & 0xff;
      cmpSpecificData->pckt[pos + 1] = ((uintValue >> 16) & 0xFF);
      cmpSpecificData->pckt[pos + 2] = ((uintValue >> 8 ) & 0xFF);
      cmpSpecificData->pckt[pos + 3] = ( uintValue & 0xFF);
    }
    
    if(CrFwCmpGetTypeId(smDesc) == CR_FW_INREPORT_TYPE) /*InReport*/
    {
      pos=pos+OFFSET_PAR_LENGTH_OUT_REP_PCKT;
      CrFwInRepData_t* cmpSpecificData = (CrFwInRepData_t*)(cmpData->cmpSpecificData);
      if(pos>(unsigned int)CrFwPcktGetLength(cmpSpecificData->pckt)-3)
      {
          printf("ERROR: The position is outside the package!! \n");
          return;
      }
      printf("CrFwPcktGetMaxLength: %d \n",CrFwPcktGetMaxLength(cmpSpecificData->pckt));
      printf("CrFwPcktGetLength: %d \n",CrFwPcktGetLength(cmpSpecificData->pckt));
      printf("CrFwPcktGetParLength: %d \n",CrFwPcktGetParLength(cmpSpecificData->pckt));
      cmpSpecificData->pckt[pos] = ( uintValue >> 24) & 0xff;
      cmpSpecificData->pckt[pos + 1] = ((uintValue >> 16) & 0xFF);
      cmpSpecificData->pckt[pos + 2] = ((uintValue >> 8 ) & 0xFF);
      cmpSpecificData->pckt[pos + 3] = ( uintValue & 0xFF);
    }
    
    
    if(CrFwCmpGetTypeId(smDesc) == CR_FW_INCOMMAND_TYPE) /*InCommand*/
    {
      pos=pos+OFFSET_PAR_LENGTH_IN_CMD_PCKT;
      CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
      if(pos>(unsigned int)CrFwPcktGetLength(cmpSpecificData->pckt)-3)
      {
          printf("ERROR: The position is outside the package!! \n");
          return;
      }
      printf("CrFwPcktGetMaxLength: %d \n",CrFwPcktGetMaxLength(cmpSpecificData->pckt));
      printf("CrFwPcktGetLength: %d \n",CrFwPcktGetLength(cmpSpecificData->pckt));
      printf("CrFwPcktGetParLength: %d \n",CrFwPcktGetParLength(cmpSpecificData->pckt));
      cmpSpecificData->pckt[pos] = ( uintValue >> 24) & 0xff;
      cmpSpecificData->pckt[pos + 1] = ((uintValue >> 16) & 0xFF);
      cmpSpecificData->pckt[pos + 2] = ((uintValue >> 8 ) & 0xFF);
      cmpSpecificData->pckt[pos + 3] = ( uintValue & 0xFF);
    }

  return;
}
