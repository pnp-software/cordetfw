/**
 * @file CrPsPcktUtilities.c
 * @ingroup CrIaDemo
 *
 * 
 *
 * @author C. Reimers and M. Rockenbauer 19.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

/* Includes */

/* for CR_FW_PCAT_SEM_TC */
#include "CrFwUserConstants.h"
#include "CrPsPcktUtilities.h"


#include <BaseCmp/CrFwBaseCmp.h>
#include <Pckt/CrFwPckt.h>
#include <UtilityFunctions/CrFwUtilityFunctions.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <arpa/inet.h>


/* ------------------------------------------------------------------------------------ */
CrFwDestSrc_t CrFwPcktGetPid(CrFwPckt_t pckt)
{
  char pid0, pid1;
  pid0 = (pckt[OFFSET_ID_FIELD] & PID0_MASK);
  pid1 = (pckt[OFFSET_ID_FIELD + 1] & PID1_MASK) >> PID1_SHIFT;
  return ((pid0 << 4) | pid1);
}





