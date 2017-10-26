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
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServHk.h>
#include <Services/General/CrPsPktServHkSupp.h>
#include <CrPsDebug.h>

#include <stdlib.h>
#include <stdio.h>


void CrPsHkRepStructRepUpdateAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  CrFwDiscriminant_t  disc;

  CrFwCounterU4_t       i, j;
  CrPsSid_t             sid, rdlSid, rdlSlot;
  CrPsStatus_t          PeriodicGenActionStatus = 1;
  CrPsCollectInterval_t CollectionInterval;
  CrFwCounterU4_t       N1, N2, NFA;
  CrPsParamId_t         N1ParamId, N2ParamId;
  CrPsRepNum_t          SCSampleRepNum;
  CrFwCounterU4_t       offset;

  /* Load the SID definition from the RDL */

  /* Get packet and discriminant */
  cmpData	        = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt		        = cmpSpecificData->pckt;
  disc            = CrFwPcktGetDiscriminant(pckt);

  /* Set SID equal to discriminant */
  sid = (CrPsSid_t) disc;
  setHkRepStructRepRepStrucId(pckt, sid); /* TODO: check if necessary */

  /* set RDL information in out-going report packet */
  /* Get report structure ID (SID) and set in out-going report packet */
  setHkRepStructRepRepStrucId(pckt, sid);

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {
      rdlSid = getDpsidItem(rdlSlot);
 
      if (sid == rdlSid)
        break;
    }  

  /* Get periodic generation action status and set in out-going report packet */
  setHkRepStructRepPeriodicGenActionStatus(pckt, PeriodicGenActionStatus);

  /* Get collection interval and set in out-going report packet */
  CollectionInterval = getDpperiodItem(rdlSlot);
  setHkRepStructRepCollectionInterval(pckt, CollectionInterval);

  /* Get N1 and set in out-going report packet */
  N1 = getDpnSimpleItem(rdlSlot);
  setHkRepStructRepN1(pckt, N1);

  /* Get N1 parameter IDs and set them in out-going report packet */
  for (i=0; i<N1; i++)
    {
      N1ParamId = getDplstIdItem(rdlSlot*HK_MAX_N_ITEMS + i);
      setHkRepStructRepN1ParamIdItem(pckt, i+1, N1ParamId);
    }

  /* Get NFA and set in out-going report packet */
  NFA = getNFA(rdlSlot);
  setHkRepStructRepNFA(pckt, NFA);

  offset = 0;

  for (i=0; i<NFA; i++)
    {
      /* Get sample repition number and set in out-going report packet */
      SCSampleRepNum = getDplstSampleRepItem(rdlSlot*HK_MAX_N_GR + i);
      setHkRepStructRepSCSampleRepNumItem(pckt, i+1, SCSampleRepNum);

      /* Get N2 and set in out-going report packet */
      N2 = getDplstNSampRepItem(rdlSlot*HK_MAX_N_GR + i);
      setHkRepStructRepN2(pckt, i+1, N2);

      /* Get N2 parameter IDs and set them in out-going report packet */
      for (j=0; j<N2; j++)
        {
          N2ParamId = getDplstIdItem(rdlSlot*HK_MAX_N_ITEMS + N1 + offset + j);
          setHkRepStructRepN2ParamIdItem(pckt, i+1, j+1, N2ParamId);
        }

      /* update offset */
      offset += N2;
    }  

  return;
}