/**
 * @file CrPsHkHkOneShotRep.c
 * @ingroup CrIaServices
 * @authors FW Profile code generator, P&P Software GmbH, 2015; Institute for Astrophysics, 2015-2016
 *
 * @brief Implementation of the One-Shot Housekeeping Report (response to command (3,27)) out-going report packet.
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
 */

#include "CrPsHkHkOneShotRep.h"

/* CrFramework includes */
#include "OutCmp/CrFwOutCmp.h"
#include "CrFwCmpData.h"
#include "Pckt/CrFwPckt.h"

/* FwProfile includes */
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwSmConfig.h"

#include <CrPsUserConstants.h>
#include <CrPsUtilities.h>
#include <DataPool/CrPsDpHk.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktHk.h> 
#include "CrPsDebug.h"

#include <stdlib.h>
#include <stdio.h>


CrFwBool_t CrPsHkHkOneShotRepEnableCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  /* Report is always enabled */

  DEBUGP_3("CrPsHkHkOneShotRepEnableCheck: \n");

  return 1;
}

CrFwBool_t CrPsHkHkOneShotRepReadyCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Report is always ready */

  DEBUGP_3("CrPsHkHkOneShotRepReadyCheck:  \n");

  return 1;
}



CrFwBool_t CrPsHkHkOneShotRepRepeatCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Report is never repeated */

  DEBUGP_3("CrPsHkHkOneShotRepRepeatCheck:  \n");

  return 0;
}


void CrPsHkHkOneShotRepUpdateAction(FwSmDesc_t smDesc)
{
  unsigned char sid, rdlSid, rdlSlot;

  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  CrFwDiscriminant_t  disc;

  unsigned short dataItemId;
  uint32_t ParamVal;  

  /* Load the value of the simply-commutated data items from the data pool 
   * and that of the super-commutated data items from the Sampling Buffer associated to the report’s SID 
   * according to the Report Definition. */

  DEBUGP_3("CrPsHkHkOneShotRepUpdateAction: TBD \n");

  /* Get packet and discriminant */
  cmpData         = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;
  disc            = CrFwPcktGetDiscriminant(pckt);

  /* Set SID equal to discriminant */
  sid = (unsigned char) disc;

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {

      rdlSid = getDpsidItem(rdlSlot);
      printf("SID in RDL[%d] = %d\n", rdlSlot, rdlSid);

      if (sid == rdlSid)
        break;
    }

  /* TODO: get array of data items and go through all of them */
  dataItemId = getDplstIdItem(rdlSlot);
  printf("CrPsHkHkPeriodicRepUpdateAction: dataItemId = %d\n", dataItemId);

  /* TODO: get value of data item */
  ParamVal = (uint32_t)dataItemId;

  /* put value of data item in TM packet */
  /* TODO: should be specific setter for PeriodicHkRep */
  setHkOneShotHkRepParamVal(pckt, ParamVal);

  cmpData->outcome = 1;

  return;
}