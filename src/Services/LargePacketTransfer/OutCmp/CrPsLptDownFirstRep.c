/**
 * \file
 *
 * Implementation of TM(13,1) LptDownFirstRep.
 *
 * \note This file was generated on 2017-11-22 12:47:43
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsLptDownFirstRep.h"

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
 * Enable check of TM(13,1) LptDownFirstRep.
 * Report is enabled if the LPT State Machine is in state DOWN_TRANSFER
 * \param smDesc The state machine descriptor.
 * \return The enable check result.
 */
CrFwBool_t CrPsLptDownFirstRepEnableCheck(FwSmDesc_t smDesc)
{
  unsigned short sm_state;

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
 * Update action of TM(13,1) LptDownFirstRep.
 * Load the first part of the large packet from the LPT Buffer; set the
 * transaction identifier equal to largeMsgTransId ; set the partnumber equal
 * to partSeqNmb ; increment partSeqNmb ; and decrement lptRemSize by partSize
 * \param smDesc The state machine descriptor.
 */
void CrPsLptDownFirstRepUpdateAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t    *cmpData;
  CrFwOutCmpData_t *cmpSpecificData;
  CrFwPckt_t        pckt;
  unsigned int     *lptMemStartAddr;
  unsigned int      LptBufferId;
  CrPsSize_t        partSize, lptRemSize;
  CrPsTid_t         Tid;
  CrPsNumberU4_t    PartSeqNmb;

  cmpData         = (CrFwCmpData_t    *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwOutCmpData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  LptBufferId = DownTransferLptBufferId;

  /* set the transaction identifier equal to largeMsgTransId */
  Tid = getDplargeMsgTransIdItem(LptBufferId);
  setLptDownFirstRepTid(pckt, Tid);

  /* set the partnumber equal to partSeqNmb */
  PartSeqNmb = getDppartSeqNmbItem(LptBufferId);
  setLptDownFirstRepPartSeqNmb(pckt, PartSeqNmb);

  /* Load the first part of the large packet from the LPT Buffer */
  lptMemStartAddr = getLptMemStartAddr(LptBufferId); /* Adaptation Point */
  partSize = (CR_FW_MAX_PCKT_LENGTH - (sizeof(TcHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t) + CRC_LENGTH));
  setLptDownFirstRepPart(pckt, (unsigned char *)lptMemStartAddr, partSize);

  /* increment partSeqNmb */
  PartSeqNmb++;
  setDppartSeqNmbItem(LptBufferId, PartSeqNmb);

  /* decrement lptRemSize by partSize */
  lptRemSize = getDplptRemSizeItem(LptBufferId) - partSize;
  setDplptRemSizeItem(LptBufferId, lptRemSize);

  return;
}
