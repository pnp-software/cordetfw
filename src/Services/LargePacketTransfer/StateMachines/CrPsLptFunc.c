/**
 * @file CrPsLptFunc.c
 * @ingroup Serv13
 * @ingroup statemachines
 *
 * @brief To each Large Packet Transfer Buffer, an instance of this state machine is associated
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Nov 26 2017 12:16:43
 
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

/** CrPsLpt function definitions */
#include "CrPsLptCreate.h"

/* CrFramework includes */
#include "Pckt/CrFwPckt.h"
#include "OutFactory/CrFwOutFactory.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"
#include "CrFwCmpData.h"

/** FW Profile function definitions */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"

#include <CrPsUtilitiesServLpt.h>
#include <DataPool/CrPsDpServLpt.h>
#include <Services/General/CrPsConstants.h>
#include <CrPsRepErr.h>

#include <time.h>
#include <stdlib.h>

CrFwBool_t FirstPartFlag, SecondPartFlag, LastPartFlag;
uint32_t LptBufferId;


/* ----------------------------------------------------------------------------------------------------------------- */

/** Entry Action for the state DOWN_TRANSFER. */
void CrPsLptDownTransferEntryAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);


  LptBufferId = DownTransferLptBufferId;

  /* nOfDownLinks++ */
  setDpnOfDownlinks(getDpnOfDownlinks()+1);

  /* partSeqNmb = 1 */
  setDppartSeqNmbItem(LptBufferId, 1);

  /* lptRemSize = lptSize */
  setDplptRemSizeItem(LptBufferId, getDplptSizeItem(LptBufferId));

  /* Set Flag_2, Flag_3 and Flag_4 to True */
  FirstPartFlag = 1;
  SecondPartFlag = 1;
  LastPartFlag = 1;

  return;
}

/** Exit Action for the state DOWN_TRANSFER. */
void CrPsLptDownTransferExitAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  LptBufferId = DownTransferLptBufferId;

  /* Increment largeMsgTransId by LPT\_N\_BUF; */
  setDplargeMsgTransIdItem(LptBufferId, getDplargeMsgTransIdItem(LptBufferId) + LPT_N_BUF);

  /* nOfDownLinks-- */
  setDpnOfDownlinks(getDpnOfDownlinks()-1);

  return;
}

/** Do Action for the state DOWN_TRANSFER. */
void CrPsLptDownTransferDoAction(FwSmDesc_t smDesc)
{
  FwSmDesc_t rep;

  CRFW_UNUSED(smDesc);

  LptBufferId = DownTransferLptBufferId;

  /* if (partSeqNmb==1 && Flag_2) {
       Load (13,1) report with lptDest as destination; 
       Flag_2 = False; } */
  if ((getDppartSeqNmbItem(LptBufferId) == 1) && FirstPartFlag)
    {
      rep = (FwSmDesc_t) CrFwOutFactoryMakeOutCmp(CRPS_LPT, CRPS_LPT_DOWNFIRST_REP, 0, CR_FW_MAX_PCKT_LENGTH);
      if (rep == NULL)
        {
          CrPsRepErr(crOutfactoryFail, CRPS_LPT, CRPS_LPT_DOWNFIRST_REP, 0);
        }
      else
        {
          CrFwOutCmpSetDest(rep, getDplptSrcItem(LptBufferId));
          CrFwOutLoaderLoad(rep);
          FirstPartFlag = 0;
        }
    }
  /* elseif ((partSeqNmb==2 && lptRemSize > partSize && Flag_3) {
       Load (13,2) report with lptDest as destination;
       Flag_3 = False; } */
  else if ((getDppartSeqNmbItem(LptBufferId) == 2) && (getDplptRemSizeItem(LptBufferId) > CR_FW_MAX_PCKT_LENGTH - (sizeof(TmHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t) + CRC_LENGTH)) && SecondPartFlag)
    {
      rep = (FwSmDesc_t) CrFwOutFactoryMakeOutCmp(CRPS_LPT, CRPS_LPT_DOWNINTER_REP, 0, CR_FW_MAX_PCKT_LENGTH);
      if (rep == NULL)
        {
          CrPsRepErr(crOutfactoryFail, CRPS_LPT, CRPS_LPT_DOWNINTER_REP, 0);
        }
      else
        {
          CrFwOutCmpSetDest(rep, getDplptSrcItem(LptBufferId));
          CrFwOutLoaderLoad(rep);
          SecondPartFlag = 0;
        }
    }
  /* elseif (lptRemSize <= partSize && Flag_4) {
       Load (13,3) report with lptDest as destination; 
       Flag_4 = False; } */
  else if ((getDplptRemSizeItem(LptBufferId) <= CR_FW_MAX_PCKT_LENGTH - (sizeof(TmHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t) + CRC_LENGTH)) && LastPartFlag)
    {
      rep = (FwSmDesc_t) CrFwOutFactoryMakeOutCmp(CRPS_LPT, CRPS_LPT_DOWNLAST_REP, 0, sizeof(TmHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t) + CRC_LENGTH + getDplptRemSizeItem(LptBufferId));
      if (rep == NULL)
        {
          CrPsRepErr(crOutfactoryFail, CRPS_LPT, CRPS_LPT_DOWNLAST_REP, 0);
        }
      else
        {
          CrFwOutCmpSetDest(rep, getDplptSrcItem(LptBufferId));
          CrFwOutLoaderLoad(rep);
          LastPartFlag = 0;
        }
    }

  return;
}

/** Entry Action for the state UP_TRANSFER. */
void CrPsLptUpTransferEntryAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  LptBufferId = UpTransferLptBufferId;

  /* nOfUpLinks++ */
  setDpnOfUplinks(getDpnOfUplinks()+1);

  /* lptFailCode = NO_FAIL */
  setDplptFailCodeItem(LptBufferId, LPT_FAILCODE_NO_FAIL);

  return;
}

/** Do Action for the state UP_TRANSFER. */
void CrPsLptUpTransferDoAction(FwSmDesc_t smDesc)
{
  CrPsTimeOut_t timeOut;
  CrFwTimeStamp_t ts;
  time_t coarse_prev, coarse_now;
  uint16_t fine_prev, fine_now;

  CRFW_UNUSED(smDesc);

  LptBufferId = UpTransferLptBufferId;

  /* if (Flag_1) lptFailCode = TIME_OUT */
  /* Flag_1 is true if the time since the last up-transfer 
     command (as given by lptTime) is larger than lptTimeOut */

  timeOut =  getDplptTimeOutItem(LptBufferId);

  ts = getDplptTimeItem(LptBufferId);
  coarse_prev = (ts.t[0] << 24) | (ts.t[1] << 16) | (ts.t[2] << 8) | ts.t[3];
  fine_prev =  (ts.t[4] << 7) | (ts.t[5] & 0xfe);

  ts = CrFwGetCurrentTimeServer();
  coarse_now = (ts.t[0] << 24) | (ts.t[1] << 16) | (ts.t[2] << 8) | ts.t[3];
  fine_now =  (ts.t[4] << 7) | (ts.t[5] & 0xfe);

  if ((int)(coarse_now - coarse_prev) > (int)timeOut)
    {
      /* lptFailCode = TIME_OUT */
      setDplptFailCodeItem(LptBufferId, LPT_FAILCODE_TIME_OUT);
    }
    
  CRFW_UNUSED(fine_prev);
  CRFW_UNUSED(fine_now);
  return;
}

/** Exit Action for the state UP_TRANSFER. */
void CrPsLptUpTransferExitAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* nOfUpLinks-- */
  setDpnOfUplinks(getDpnOfUplinks()-1);

  return;
}

/** Action on the transition from DOWN_TRANSFER to INACTIVE. */
void CrPsLptGenerateAbortEvent(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Generate event EVT_DOWN_ABORT */
  CrPsRepErr(EVT_DOWN_ABORT, 13, 0, 0);

  return;
}

/** Guard on the transition from DOWN_TRANSFER to INACTIVE. */
FwSmBool_t CrPsLptIsTransferFinished(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* [ Transfer is finished ] */

  LptBufferId = DownTransferLptBufferId;

  if (getDplptRemSizeItem(LptBufferId) == 0)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/** Action on the transition from UP_TRANSFER to INACTIVE. */
void CrPsLptLoadReport(FwSmDesc_t smDesc)
{
  FwSmDesc_t rep;

  CRFW_UNUSED(smDesc);

  /* Load (13,16) report */

  rep = (FwSmDesc_t) CrFwOutFactoryMakeOutCmp(CRPS_LPT, CRPS_LPT_UPABORT_REP, 0, sizeof(TmHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t));
  if (rep == NULL)
    {
      /* TM(13,16) OUTFACTORY_FAIL */
      CrPsRepErr(crOutfactoryFail, CRPS_LPT, CRPS_LPT_UPABORT_REP, 0);
    }
  else
    {
      CrFwOutCmpSetDest(rep, 1);
      CrFwOutLoaderLoad(rep);
    }

  return;
}

/** Guard on the transition from UP_TRANSFER to INACTIVE. */
FwSmBool_t CrPsLptIsFailed(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  LptBufferId = UpTransferLptBufferId;

  /* [ lptFailCode != NO_FAIL ] */
  if (getDplptFailCodeItem(LptBufferId) != LPT_FAILCODE_NO_FAIL)
    return 1;
  else
    return 0;
}

/** Action on the transition from Initial State to INACTIVE. */
void CrPsLptInitialization(FwSmDesc_t smDesc)
{
  uint32_t i;

  CRFW_UNUSED(smDesc);

  /* Initialize largeMsgTransId */
  for (i=0; i<LPT_N_BUF; i++)
    {
      setDplargeMsgTransIdItem(i, 0);
    }

  return;
}

/* ----------------------------------------------------------------------------------------------------------------- */

