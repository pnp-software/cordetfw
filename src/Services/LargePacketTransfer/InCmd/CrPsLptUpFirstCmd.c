/**
 * \file
 *
 * Implementation of TC(13,9) LptUpFirstCmd.
 *
 * \note This file was generated on 2017-11-22 12:47:43
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsLptUpFirstCmd.h"

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

unsigned int UpTransferLptBufferId;


/**
 * Start action of TC(13,9) LptUpFirstCmd.
 * Determine the identifier of the LPT Buffer for the up-transfer by
 * computing: (x MOD LPT_N_BUF) where `x' is the Large Message Transaction
 * Identifier. Set action outcome to 'success' if the Part Sequence Number is
 * equal to 1 and the LPT State Machine is in state INACTIVE; otherwise set
 * the action outcome to `failure'
 * \param smDesc The state machine descriptor.
 */
void CrPsLptUpFirstCmdStartAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t        *cmpData;
  CrFwInCmdData_t      *cmpSpecificData;
  CrFwPckt_t            pckt;
  CrPsTid_t Tid;
  unsigned int LptBufferId;
  CrPsNumberU4_t PartSeqNmb;

  /* Get inPckt */
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  Tid = getLptUpFirstCmdTid(pckt);

  LptBufferId = Tid % LPT_N_BUF;

  /* Set UpTransferLptBufferId for current Up Transfer */
  UpTransferLptBufferId = LptBufferId;

  PartSeqNmb = getLptUpFirstCmdPartSeqNmb(pckt);

  return;
}

/**
 * Progress action of TC(13,9) LptUpFirstCmd.
 * Send command StartUpTransfer to LPT State Machine; copy the up-transfer
 * data to LPT Buffer and set lptSize to be equal to the amount of copied data;
 * set lptTime to the current time; set partSeqNmb to 1; set lptSrc to the
 * source of the command
 * \param smDesc The state machine descriptor.
 */
void CrPsLptUpFirstCmdProgressAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t        *cmpData;
  CrFwInCmdData_t      *cmpSpecificData;
  CrFwPckt_t            pckt;
  unsigned int dataSize, pos;
  unsigned int *lptMemStartAddr;
  unsigned int LptBufferId;
  CrFwTimeStamp_t ts;
  time_t coarse;
  unsigned short fine;

  /* Send command StartUpTransfer to LPT State Machine */
  FwSmMakeTrans(getSmDescLpt(), StartUpTransfer);

  LptBufferId = UpTransferLptBufferId;

  /* Get inPckt */
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get packet size and calculate amount of data */
  dataSize = CrFwPcktGetLength(pckt) - (sizeof(TcHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t) + CRC_LENGTH);

  /* Copy the up-transfer data to LPT Buffer */
  lptMemStartAddr = getLptMemStartAddr(LptBufferId);
  pos = sizeof(TcHeader_t)+sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t);
  memcpy((unsigned char *)lptMemStartAddr, &((uint8_t*)pckt)[pos], dataSize);

  /* Set lptSize to be equal to the amount of copied data */
  setDplptSizeItem(LptBufferId, (CrPsSize_t)dataSize);

  /* Set lptTime to the current time */
  ts = CrFwGetCurrentTimeServer();
  coarse = (ts.t[0] << 24) | (ts.t[1] << 16) | (ts.t[2] << 8) | ts.t[3];
  fine =  (ts.t[4] << 7) | (ts.t[5] & 0xfe);
  setDplptTimeItem(LptBufferId, ts);

  /* Set partSeqNmb to 1 */
  setDppartSeqNmbItem(LptBufferId, 1);

  /* Set lptSrc to the source of the command */
  setDplptSrcItem(LptBufferId, CrFwPcktGetSrc(pckt));

  return;
}

/**
 * Termination action of TC(13,9) LptUpFirstCmd.
 * Set action outcome to 'success'
 * \param smDesc The state machine descriptor.
 */
void CrPsLptUpFirstCmdTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t *inData;

  /* Set action outcome to 'success' */

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

