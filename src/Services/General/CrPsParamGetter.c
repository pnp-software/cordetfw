/**
 * @file CrPsParamGetter.c
 * @ingroup CrPsServicesGeneral
 *
 * @brief Implementation of the getter operations for all parameters of all in-coming packets.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 * 
 */

#include "CrPsParamGetter.h"

#include "CrPsConstants.h"
#include "CrFwCmpData.h"
#include "FwSmConfig.h"
#include <string.h>
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include <stdio.h>

#define GET_UCHAR_FROM_PCKT(from) ((unsigned char)(pckt[from]))

#define GET_USHORT_FROM_PCKT(from) ( (((unsigned char)(pckt[from])) << 8) | ((unsigned char)(pckt[from+1])) )

#define GET_UINT_FROM_PCKT(from) ( (((unsigned char)(pckt[from])) << 24) | (((unsigned char)(pckt[from+1])) << 16) | (((unsigned char)(pckt[from+2])) << 8) | ((unsigned char)(pckt[from+3])) )

/* ------------------------------------------------------------------------------------ */
void CrPsServTestOnBoardConnectParamGetAppId(unsigned short * appId, CrFwPckt_t pckt)
{
  *appId = GET_USHORT_FROM_PCKT(OFFSET_PAR_LENGTH_IN_CMD_PCKT + 0);
  return;
}

   
unsigned int CrPsGetUIntValue(FwSmDesc_t smDesc, unsigned int pos)
{
  CrFwPckt_t pckt;
  CrFwCmpData_t* cmpData;
  CrFwOutCmpData_t* cmpSpecificDataOutCmp;
  CrFwInRepData_t*  cmpSpecificDataInRep;
  CrFwInCmdData_t*  cmpSpecificDataInCmd;

  cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  /*error if the Type does not match*/
  if((CrFwCmpGetTypeId(smDesc) != CR_FW_OUTCMP_TYPE) && (CrFwCmpGetTypeId(smDesc) != CR_FW_INREPORT_TYPE) && (CrFwCmpGetTypeId(smDesc) != CR_FW_INCOMMAND_TYPE))
    {
      printf("ERROR: smDesc TypeId does not match!! \n");
      return 0;
    }
  
  if(CrFwCmpGetTypeId(smDesc) == CR_FW_OUTCMP_TYPE) /*OutComponent*/
    {
      pos=pos+OFFSET_PAR_LENGTH_OUT_REP_PCKT;
      cmpSpecificDataOutCmp = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
      pckt = cmpSpecificDataOutCmp->pckt;
      if(pos>(unsigned int)CrFwPcktGetLength(pckt)-3)
        {
          printf("ERROR: The position is outside the package!! \n");
          return 0;
        }
      return GET_UINT_FROM_PCKT(pos);
    }
  if(CrFwCmpGetTypeId(smDesc) == CR_FW_INREPORT_TYPE) /*InReport*/
    {
      pos=pos+OFFSET_PAR_LENGTH_OUT_REP_PCKT;
      cmpSpecificDataInRep = (CrFwInRepData_t*)(cmpData->cmpSpecificData);
      pckt = cmpSpecificDataInRep->pckt;
      if(pos>(unsigned int)CrFwPcktGetLength(pckt)-3)
        {
          printf("ERROR: The position is outside the package!! \n");
          return 0;
        }
      return GET_UINT_FROM_PCKT(pos);
    }
  if(CrFwCmpGetTypeId(smDesc) == CR_FW_INCOMMAND_TYPE) /*InCommand*/
    {
      pos=pos+OFFSET_PAR_LENGTH_IN_CMD_PCKT;
      cmpSpecificDataInCmd = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
      pckt = cmpSpecificDataInCmd->pckt;
      if(pos>(unsigned int)CrFwPcktGetLength(pckt)-3)
        {
          printf("ERROR: The position is outside the package!! \n");
          return 0;
        }   
      return GET_UINT_FROM_PCKT(pos);
    }   
  return 0;
}

unsigned short CrPsGetUShortValue(FwSmDesc_t smDesc, unsigned int pos)
{
  CrFwPckt_t pckt;
  CrFwCmpData_t* cmpData;
  CrFwOutCmpData_t* cmpSpecificDataOutCmp;
  CrFwInRepData_t*  cmpSpecificDataInRep;
  CrFwInCmdData_t*  cmpSpecificDataInCmd;

  cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  /*error if the Type does not match*/
  if((CrFwCmpGetTypeId(smDesc) != CR_FW_OUTCMP_TYPE) && (CrFwCmpGetTypeId(smDesc) != CR_FW_INREPORT_TYPE) && (CrFwCmpGetTypeId(smDesc) != CR_FW_INCOMMAND_TYPE))
    {
      printf("ERROR: smDesc TypeId does not match!! \n");
      return 0;
    }
  
  if(CrFwCmpGetTypeId(smDesc) == CR_FW_OUTCMP_TYPE) /*OutComponent*/
    {
      pos=pos+OFFSET_PAR_LENGTH_OUT_REP_PCKT;
      cmpSpecificDataOutCmp = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
      pckt = cmpSpecificDataOutCmp->pckt;
      if(pos>(unsigned int)CrFwPcktGetLength(pckt)-3)
        {
          printf("ERROR: The position is outside the package!! \n");
          return 0;
        }
      return GET_USHORT_FROM_PCKT(pos);
  }
  if(CrFwCmpGetTypeId(smDesc) == CR_FW_INREPORT_TYPE) /*InReport*/
  {
    pos=pos+OFFSET_PAR_LENGTH_OUT_REP_PCKT;
    cmpSpecificDataInRep = (CrFwInRepData_t*)(cmpData->cmpSpecificData);
    pckt = cmpSpecificDataInRep->pckt;
    if(pos>(unsigned int)CrFwPcktGetLength(pckt)-3)
    {
      printf("ERROR: The position is outside the package!! \n");
      return 0;
    }
    return GET_USHORT_FROM_PCKT(pos);
  }
  if(CrFwCmpGetTypeId(smDesc) == CR_FW_INCOMMAND_TYPE) /*InCommand*/
  {
    pos=pos+OFFSET_PAR_LENGTH_IN_CMD_PCKT;
    cmpSpecificDataInCmd = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
    pckt = cmpSpecificDataInCmd->pckt;
    if(pos>(unsigned int)CrFwPcktGetLength(pckt)-3)
    {
      printf("ERROR: The position is outside the package!! \n");
      return 0;
    }   
    return GET_USHORT_FROM_PCKT(pos);
  }   
   return 0;
}

unsigned char CrPsGetUCharValue(FwSmDesc_t smDesc, unsigned int pos)
{
  CrFwPckt_t pckt;
  CrFwCmpData_t* cmpData;
  CrFwOutCmpData_t* cmpSpecificDataOutCmp;
  CrFwInRepData_t*  cmpSpecificDataInRep;
  CrFwInCmdData_t*  cmpSpecificDataInCmd;

  cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  /*error if the Type does not match*/
  if((CrFwCmpGetTypeId(smDesc) != CR_FW_OUTCMP_TYPE) && (CrFwCmpGetTypeId(smDesc) != CR_FW_INREPORT_TYPE) && (CrFwCmpGetTypeId(smDesc) != CR_FW_INCOMMAND_TYPE))
  {
      printf("ERROR: smDesc TypeId does not match!! \n");
      return 0;
  }
  
  if(CrFwCmpGetTypeId(smDesc) == CR_FW_OUTCMP_TYPE) /*OutComponent*/
  {
    pos=pos+OFFSET_PAR_LENGTH_OUT_REP_PCKT;
    cmpSpecificDataOutCmp = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);
    pckt = cmpSpecificDataOutCmp->pckt;
    printf(":::: %u ::: \n",(unsigned int)CrFwPcktGetLength(pckt)-3);
    printf("---- %u --- \n",pos);

    if(pos>(unsigned int)CrFwPcktGetLength(pckt)-3)
    {
      printf("ERROR: The position is outside the package!! \n");
      return 0;
    }
    return GET_UCHAR_FROM_PCKT(pos);
  }
  if(CrFwCmpGetTypeId(smDesc) == CR_FW_INREPORT_TYPE) /*InReport*/
  {
    pos=pos+OFFSET_PAR_LENGTH_OUT_REP_PCKT;
    cmpSpecificDataInRep = (CrFwInRepData_t*)(cmpData->cmpSpecificData);
    pckt = cmpSpecificDataInRep->pckt;
    if(pos>(unsigned int)CrFwPcktGetLength(pckt)-3)
    {
      printf("ERROR: The position is outside the package!! \n");
      return 0;
    }
    return GET_UCHAR_FROM_PCKT(pos);
  }
  if(CrFwCmpGetTypeId(smDesc) == CR_FW_INCOMMAND_TYPE) /*InCommand*/
  {
    pos=pos+OFFSET_PAR_LENGTH_IN_CMD_PCKT;
    cmpSpecificDataInCmd = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
    pckt = cmpSpecificDataInCmd->pckt;
    if(pos>(unsigned int)CrFwPcktGetLength(pckt)-3)
    {
      printf("ERROR: The position is outside the package!! \n");
      return 0;
    }   
    return GET_UCHAR_FROM_PCKT(pos);
  }   
   return 0;
}
