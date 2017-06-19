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

#include <string.h>

#define GET_UCHAR_FROM_PCKT(from) ((unsigned char)(pckt[from]))

#define GET_USHORT_FROM_PCKT(from) ( (((unsigned char)(pckt[from])) << 8) | ((unsigned char)(pckt[from+1])) )

#define GET_UINT_FROM_PCKT(from) ( (((unsigned char)(pckt[from])) << 24) | (((unsigned char)(pckt[from+1])) << 16) | (((unsigned char)(pckt[from+2])) << 8) | ((unsigned char)(pckt[from+3])) )

/* ------------------------------------------------------------------------------------ */
void CrPsServTestOnBoardConnectParamGetAppId(unsigned short * appId, CrFwPckt_t pckt)
{
  *appId = GET_USHORT_FROM_PCKT(OFFSET_PAR_LENGTH_IN_CMD_PCKT + 0);
  return;
}
