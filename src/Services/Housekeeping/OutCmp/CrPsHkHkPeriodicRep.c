/**
 * @file CrPsHkHkPeriodicRep.c
 * @ingroup CrIaServices
 * @authors FW Profile code generator, P&P Software GmbH, 2015; Institute for Astrophysics, 2015-2016
 *
 * @brief Implementation of the Periodic Housekeeping Report (3,25) out-going report packet.
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

#include "CrPsHkHkPeriodicRep.h"

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


CrFwBool_t CrPsHkHkPeriodicRepEnableCheck(FwSmDesc_t smDesc)
{
  unsigned char sid, rdlSid, rdlSlot;
  CrFwBool_t rdlEnabled;

  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  CrFwDiscriminant_t  disc;

  /* The enable status is read from the isEnabled field of the Report Definition corresponding to the report’s SID */

  DEBUGP_3("CrPsHkHkPeriodicRepEnableCheck: TBD \n");

  cmpData	        = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt		        = cmpSpecificData->pckt;
  disc            = CrFwPcktGetDiscriminant(pckt);

  /* Get the SID: discriminant for HK is the SID */
  sid = (unsigned char) disc;
  printf("CrPsHkHkPeriodicRepEnableCheck: SID = %d \n", sid);

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {

      rdlSid = getDpsidItem(rdlSlot);
      printf("SID in RDL[%d] = %d\n", rdlSlot, rdlSid);
      
      if (sid == rdlSid)
        break;
    }

  /* TODO: sid not found in list */
  if (rdlSlot == HK_N_REP_DEF)
    {
      DEBUGP("SID %d not found!\n", sid);
      /*SendTcStartRepFail(pckt, ACK_SID_NOT_USED, 0, (unsigned short)sid);*/ /* TODO: send TM(1,2)? */
      return 0;
    }

  /* Read the Enable status */
  rdlEnabled = getDpisEnabledItem(rdlSlot);
  printf("isEnabled in RDL[%d] = %d\n", rdlSlot, rdlEnabled);

  return rdlEnabled;
}

CrFwBool_t CrPsHkHkPeriodicRepReadyCheck(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  CrFwDiscriminant_t  disc;
  prDataHkRepReadyCheck_t prData;
  unsigned char sid;

  CRFW_UNUSED(smDesc);

  /* Run the procedure Ready Check of HkRep Report of figure 9.5 */

  DEBUGP_3("CrPsHkHkPeriodicRepReadyCheck: TBD \n");

  cmpData         = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;
  disc            = CrFwPcktGetDiscriminant(pckt);

  /* Get the SID: discriminant for HK is the SID */
  sid = (unsigned char) disc;
  printf("CrPsHkHkPeriodicRepReadyCheck: SID = %d \n", sid);

  /* Set prData of procedure   */
  /* initial setting of prData */
  prData.smDesc = smDesc;
  prData.sid = sid;
  FwPrSetData(prDescHkRepReadyCheck, &prData);

  FwPrExecute(prDescHkRepReadyCheck);

  cmpData = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  printf("CrPsHkHkPeriodicRepReadyCheck: outcome = %d \n", cmpData->outcome);

  return cmpData->outcome;
}


CrFwBool_t CrPsHkHkPeriodicRepRepeatCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Report is always repeated */

  DEBUGP_3("CrPsHkHkPeriodicRepRepeatCheck:  \n");

  return 1;
}


void CrPsHkHkPeriodicRepUpdateAction(FwSmDesc_t smDesc)
{
  unsigned char sid, rdlSid, rdlSlot;

  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  CrFwDiscriminant_t  disc;

  unsigned short dataItemId;
  uint32_t ParamVal;

  /* Load the value of the simply-commutated data items from the data pool 
   * and that of the super-commutated data items from the Sampling Buffer 
   * associated to the report’s SID according to the Report Definition. */

  DEBUGP_3("CrPsHkHkPeriodicRepUpdateAction: TBD \n");

  /* Get packet and discriminant */
  cmpData	        = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt		        = cmpSpecificData->pckt;
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
