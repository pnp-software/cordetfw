/**
 * @file CrPsLptDownLastRep.c
 * @ingroup Serv13
 * @ingroup OutCmp
 *
 * @brief Implementation of TM(13,3) LptDownLastRep.
 *
 * @note This file was generated on 2017-11-22 12:47:43
 *
 * @author PnP Generator
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * 
 * last modification: 22.01.2018
 * 
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#include "CrPsLptDownLastRep.h"

/* CrFramework includes */
#include "OutCmp/CrFwOutCmp.h"
#include "CrFwCmpData.h"
#include "Pckt/CrFwPckt.h"

/* FwProfile includes */
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwSmConfig.h"

#include <CrPsUtilitiesServLpt.h>
#include <DataPool/CrPsDpServLpt.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServLpt.h>
#include <Services/General/CrPsPktServLptSupp.h>
#include <Services/LargePacketTransfer/StateMachines/CrPsLptCreate.h>

/**
 * Enable check of TM(13,3) LptDownLastRep.
 * Report is enabled if the LPT State Machine is in state DOWN_TRANSFER
 * \param smDesc The state machine descriptor.
 * \return The enable check result.
 */
CrFwBool_t CrPsLptDownLastRepEnableCheck(FwSmDesc_t smDesc)
{
  uint16_t sm_state;

  CRFW_UNUSED(smDesc);

  sm_state = FwSmGetCurState(getSmDescLpt());
  if (sm_state == CrPsLpt_DOWN_TRANSFER)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/**
 * Update action of TM(13,3) LptDownLastRep.
 * Load the last part of the large packet from the LPT Buffer, set the
 * transaction identifier equal to largeMsgTransId; set the partnumber equal
 * to partSeqNmb
 * \param smDesc The state machine descriptor.
 */
void CrPsLptDownLastRepUpdateAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwOutCmpData_t   *cmpSpecificData;
  CrFwPckt_t          pckt;
  uint32_t           *lptMemStartAddr;
  uint32_t            LptBufferId;
  CrPsSize_t          partSize, partSize_prev, lptRemSize;
  CrPsTid_t           Tid;
  CrPsNumberU4_t      PartSeqNmb;

  cmpData         = (CrFwCmpData_t    *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwOutCmpData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  LptBufferId = DownTransferLptBufferId;
  
  /* set the transaction identifier equal to largeMsgTransId */
  Tid = getDplargeMsgTransIdItem(LptBufferId);
  setLptDownLastRepTid(pckt, Tid);

  /* set the partnumber equal to partSeqNmb */
  PartSeqNmb = getDppartSeqNmbItem(LptBufferId);
  setLptDownLastRepPartSeqNmb(pckt, PartSeqNmb);

  /* Load the first part of the large packet from the LPT Buffer */
  lptMemStartAddr = getLptMemStartAddr(LptBufferId); /* Adaptation Point */
  partSize = getDplptRemSizeItem(LptBufferId);
  partSize_prev = (CR_FW_MAX_PCKT_LENGTH - (sizeof(TmHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t) + CRC_LENGTH));
  setLptDownLastRepPart(pckt, (uint8_t *)lptMemStartAddr + (PartSeqNmb-1)*partSize_prev, partSize);

  /* decrement lptRemSize by partSize */
  lptRemSize = getDplptRemSizeItem(LptBufferId) - partSize; /* should be always zero */
  setDplptRemSizeItem(LptBufferId, lptRemSize);

  return;
}
