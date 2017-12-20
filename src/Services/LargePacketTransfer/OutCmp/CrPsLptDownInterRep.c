/**
 * \file
 *
 * Implementation of TM(13,2) LptDownInterRep.
 *
 * \note This file was generated on 2017-11-22 12:47:43
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsLptDownInterRep.h"

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
 * Enable check of TM(13,2) LptDownInterRep.
 * Report is enabled if the LPT State Machine is in state DOWN_TRANSFER
 * \param smDesc The state machine descriptor.
 * \return The enable check result.
 */
CrFwBool_t CrPsLptDownInterRepEnableCheck(FwSmDesc_t smDesc)
{
  unsigned short sm_state;

  CRFW_UNUSED(smDesc);

  sm_state = FwSmGetCurState(smDescLpt);
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
 * Repeat check of TM(13,2) LptDownInterRep.
 * Report is repeated as long as lptRemSize is greater than partSize
 * \param smDesc The state machine descriptor.
 * \return The repeat check result.
 */
CrFwBool_t CrPsLptDownInterRepRepeatCheck(FwSmDesc_t smDesc)
{
  unsigned int LptBufferId;

  CRFW_UNUSED(smDesc);

  LptBufferId = DownTransferLptBufferId;

  if (getDplptRemSizeItem(LptBufferId) > CR_FW_MAX_PCKT_LENGTH - (sizeof(TmHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t) + CRC_LENGTH))
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/**
 * Update action of TM(13,2) LptDownInterRep.
 * Load the next part of the large packet from the LPT Buffer; set the
 * transaction identifier equal to largeMsgTransId; set the part number equal
 * to partSeqNmb; increase partSeqNmb; and decrement lptRemSize by partSize
 * \param smDesc The state machine descriptor.
 */
void CrPsLptDownInterRepUpdateAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwOutCmpData_t   *cmpSpecificData;
  CrFwPckt_t          pckt;
  unsigned int* lptMemStartAddr;

  unsigned int LptBufferId;
  CrPsSize_t partSize, lptRemSize;
  CrPsTid_t Tid;
  CrPsNumberU4_t PartSeqNmb;

  cmpData         = (CrFwCmpData_t    *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwOutCmpData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  LptBufferId = DownTransferLptBufferId;

  /* set the transaction identifier equal to largeMsgTransId */
  Tid = getDplargeMsgTransIdItem(LptBufferId);
  setLptDownInterRepTid(pckt, Tid);

  /* set the partnumber equal to partSeqNmb */
  PartSeqNmb = getDppartSeqNmbItem(LptBufferId);
  setLptDownInterRepPartSeqNmb(pckt, PartSeqNmb);

  /* Load the first part of the large packet from the LPT Buffer */
  lptMemStartAddr = getLptMemStartAddr(LptBufferId); /* Adaptation Point */
  partSize = (CR_FW_MAX_PCKT_LENGTH - (sizeof(TmHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t) + CRC_LENGTH));
  /*setLptDownInterRepPart(pckt, (unsigned char *)&(lptMemStartAddr[(PartSeqNmb-1)*partSize]), partSize);*/
  setLptDownFirstRepPart(pckt, (unsigned char *)lptMemStartAddr + (PartSeqNmb-1)*partSize, partSize);

  /* increment partSeqNmb */
  PartSeqNmb++;
  setDppartSeqNmbItem(LptBufferId, PartSeqNmb);

  /* decrement lptRemSize by partSize */
  lptRemSize = getDplptRemSizeItem(LptBufferId) - partSize;
  setDplptRemSizeItem(LptBufferId, lptRemSize);

  return;
}
