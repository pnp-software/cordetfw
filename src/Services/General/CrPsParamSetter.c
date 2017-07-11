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

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifAccSuccParamSetTcPacketId(FwSmDesc_t smDesc, unsigned short tcPacketId)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 0] = (tcPacketId >> 8) & 0xff;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 1] = (tcPacketId & 0xFF);
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServReqVerifAccSuccParamSetTcPacketSeqCtrl(FwSmDesc_t smDesc, unsigned short tcPacketSeqCtrl)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 2] = (tcPacketSeqCtrl >> 8) & 0xff;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 3] = (tcPacketSeqCtrl & 0xFF);
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsServTestOnBoardConnectParamSetAppId(FwSmDesc_t smDesc, unsigned short appId)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 0] = (appId >> 8) & 0xff;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + 1] = (appId & 0xFF);
  return;
}

/* ------------------------------------------------------------------------------------ */
/**
 * Generic setter
 * Set data at specific position in data segment of PUS packet
 */
void CrPsSetUCharValue(FwSmDesc_t smDesc, unsigned char ucharValue, unsigned int pos)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + pos] = ucharValue;
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsSetUShortValue(FwSmDesc_t smDesc, unsigned short ushortValue, unsigned int pos)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + pos] = (ushortValue >> 8) & 0xff;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + pos + 1] = (ushortValue & 0xFF);
  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsSetUIntValue(FwSmDesc_t smDesc, unsigned int uintValue, unsigned int pos)
{
  CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  CrFwOutCmpData_t* cmpSpecificData = (CrFwOutCmpData_t*)(cmpData->cmpSpecificData);

  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + pos] = ( uintValue >> 24) & 0xff;
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + pos + 1] = ((uintValue >> 16) & 0xFF);
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + pos + 2] = ((uintValue >> 8 ) & 0xFF);
  cmpSpecificData->pckt[OFFSET_PAR_LENGTH_OUT_REP_PCKT + pos + 3] = ( uintValue & 0xFF);

  return;
}
