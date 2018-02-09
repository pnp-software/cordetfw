/**
 * @file CrPsLptUpInterCmd.c
 * @ingroup Serv13
 * @ingroup InCmd
 *
 * @brief Implementation of TC(13,10) LptUpInterCmd.
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

#include "CrPsLptUpInterCmd.h"

/* CrFramework includes */
#include <Pckt/CrFwPckt.h>
#include <OutFactory/CrFwOutFactory.h>
#include <OutCmp/CrFwOutCmp.h>
#include <OutLoader/CrFwOutLoader.h>
#include <CrFwCmpData.h>

/* FwProfile includes */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"

#include <CrPsUtilitiesServLpt.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServLpt.h>
#include <Services/General/CrPsPktServLptSupp.h>
#include <Services/LargePacketTransfer/StateMachines/CrPsLptCreate.h>
#include <CrPsUserConstants.h>
#include <DataPool/CrPsDpServLpt.h>

#include <time.h>


/**
 * Start action of TC(13,10) LptUpInterCmd.
 * Run the Procedure Up-Transfer Start Action of Figure ??
 * \param smDesc The state machine descriptor.
 */
void CrPsLptUpInterCmdStartAction(FwSmDesc_t smDesc)
{
  /* Set prData of procedure   */
  /* initial setting of prData */
  FwPrSetData(getPrDescLptUpCmdStart(), smDesc);

  FwPrRun(getPrDescLptUpCmdStart());

  return;
}

/**
 * Progress action of TC(13,10) LptUpInterCmd.
 * Copy the up-transfer data to LPT Buffer and increment lptSize by the amount
 * of copied data; set lptTime to the current time; set patSeqNmb to the part
 * sequence number carried by the command
 * \param smDesc The state machine descriptor.
 */
void CrPsLptUpInterCmdProgressAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t        *cmpData;
  CrFwInCmdData_t      *cmpSpecificData;
  CrFwPckt_t            pckt;
  uint32_t              dataSize, pos;
  uint32_t             *lptMemStartAddr;
  CrPsNumberU4_t        PartSeqNmb;
  CrPsSize_t            partSize;
  CrFwTimeStamp_t       ts;
  time_t                coarse;
  uint16_t              fine;
  CrPsTid_t             Tid;
  uint32_t              LptBufferId;

  /* Get inPckt */
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  Tid = getLptUpInterCmdTid(pckt);
  LptBufferId = Tid % LPT_N_BUF;

  /* Get packet size and calculate amount of data */
  dataSize = CrFwPcktGetLength(pckt) - (sizeof(TcHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t) + CRC_LENGTH);

  /* Get PartSeqNum to determine memory address */
  PartSeqNmb = getLptUpInterCmdPartSeqNmb(pckt);

  /* Copy the up-transfer data to LPT Buffer */
  lptMemStartAddr = getLptMemStartAddr(LptBufferId);
  partSize = (CR_FW_MAX_PCKT_LENGTH - (sizeof(TcHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t) + CRC_LENGTH));
  pos = sizeof(TcHeader_t)+sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t);
  memcpy((uint8_t *)lptMemStartAddr + (PartSeqNmb-1)*partSize, &((uint8_t*)pckt)[pos], dataSize);

  /* Increment lptSize by the amount of copied data */
  setDplptSizeItem(LptBufferId, getDplptSizeItem(LptBufferId) + (CrPsSize_t)dataSize);

  /* Set lptTime to the current time */
  ts = CrFwGetCurrentTimeServer();
  coarse = (ts.t[0] << 24) | (ts.t[1] << 16) | (ts.t[2] << 8) | ts.t[3];
  fine =  (ts.t[4] << 7) | (ts.t[5] & 0xfe);
  setDplptTimeItem(LptBufferId, ts);

  /* Set patSeqNmb to the part sequence number carried by the command */
  setDppartSeqNmbItem(LptBufferId, PartSeqNmb);

  cmpData->outcome = 1;

  /*TODO*/
  CRFW_UNUSED(coarse);
  CRFW_UNUSED(fine);

  return;
}

/**
 * Termination action of TC(13,10) LptUpInterCmd.
 * Set action outcome to 'success'
 * \param smDesc The state machine descriptor.
 */
void CrPsLptUpInterCmdTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t *inData;

  /* Set action outcome to 'success' */

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}
