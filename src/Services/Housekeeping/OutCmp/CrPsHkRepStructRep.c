/**
 * @file CrPsHkRepStructRep.c
 * @ingroup CrIaServices
 * @authors FW Profile code generator, P&P Software GmbH, 2015; Institute for Astrophysics, 2015-2016
 *
 * @brief Implementation of the Housekeeping Structure Report (3,10) out-going report packet.
 *
 * @copyright
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * SERVICE 3,10 and 3,12
 */

#include "CrPsHkRepStructRep.h"

#include <FwPrConfig.h>
#include <FwSmConfig.h>

#include <OutCmp/CrFwOutCmp.h>
#include <Pckt/CrFwPckt.h>

#include <CrFwCmpData.h>

#include <CrPsUserConstants.h>
#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServHk.h>
#include <Services/General/CrPsPktServHk.h> 
#include <CrPsDebug.h>

#include <stdlib.h>
#include <stdio.h>


CrFwBool_t CrPsHkRepStructRepEnableCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Report is always enabled */

  DEBUGP_3("CrPsHkRepStructRepEnableCheck: Report is always enabled \n");

  return 1;
}

void CrPsHkRepStructRepUpdateAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  CrFwDiscriminant_t  disc;
  unsigned char sid;
  unsigned char rdlSid, rdlSlot;

  /* Load the SID definition from the RDL */

  DEBUGP_3("CrPsHkRepStructRepUpdateAction: Load the SID definition from the RDL \n");

  /* Get packet and discriminant */
  cmpData	        = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt		        = cmpSpecificData->pckt;
  disc            = CrFwPcktGetDiscriminant(pckt);

  /* Set SID equal to discriminant */
  sid = (unsigned char) disc;
  setHkRepStructRepRepStrucId(pckt, sid); /* TODO: check if necessary */

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {
      rdlSid = getDpsidItem(rdlSlot);
      printf("SID in RDL[%d] = %d\n", rdlSlot, rdlSid);

      if (sid == rdlSid)
        break;
    }  

  /* TODO: CrPsCmd3s9PrgrN5 */
  

  return;
}