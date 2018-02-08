/**
 * @file CrPsGetSetTestCases.c
 * @ingroup PUSTestsuite
 *
 * @brief Implementation of the test cases for all Getter and Setter components.
 *
 * @author Christian Reimers <christian.reimersy@univie.ac.at>
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

/* Include system files */
#include <unistd.h>
#include <stdlib.h>

/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include configuration files */

/* Include framework files */
#include "CrFwCmpData.h"
#include "InStream/CrFwInStream.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutFactory/CrFwOutFactory.h"
#include "InFactory/CrFwInFactory.h"
#include "Pckt/CrFwPckt.h"

#include "CrFwTime.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"

#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServTest.h>
#include <DataPool/CrPsDpServReqVerif.h>
#include <DataPool/CrPsDpServHk.h>
#include <DataPool/CrPsDpServEvt.h>
#include <DataPool/CrPsDpServLpt.h>

#include <Services/General/CrPsPktServReqVerif.h>
#include <Services/General/CrPsPktServReqVerifSupp.h>
#include <Services/General/CrPsPktServTest.h>
#include <Services/General/CrPsPktServHk.h>
#include <Services/General/CrPsPktServHkSupp.h>
#include <Services/General/CrPsPktServEvt.h>
#include <Services/General/CrPsPktServEvtSupp.h>
#include <Services/General/CrPsPktServLpt.h>
#include <Services/General/CrPsPktServLptSupp.h>
#include <Services/General/CrPsPktUtil.h>
#include <Services/General/CrPsConstants.h>

#define MAX_CHAR 255
#define MAX_SHORT 65535
#define MAX_INT 4294967295u
#define MIN_VAL 0

/* ---------------------------------------------------------------------------------------------*/

CrFwBool_t CrPsPcktGetSetTestCase1()
{

  CrFwPckt_t pckt, pckt2, pckt3, pckt4;
  uint8_t  tim[6], timi[6];
  char    *pstart;
  uint16_t pcktsize = 30;
  CrFwTimeStamp_t timstp,timstpi;

  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /*test all TC header Getter and Setter*/
  setTcHeaderPcktVersionNmb(pckt, 0);
  if (getTcHeaderPcktVersionNmb(pckt) != 0) 
    return 0; 

  setTcHeaderPcktVersionNmb(pckt, 7);
  if (getTcHeaderPcktVersionNmb(pckt) != 7) 
    return 0;

  setTcHeaderPcktType(pckt, 0);
  if (getTcHeaderPcktType(pckt) != 0) 
    return 0; 
  setTcHeaderPcktType(pckt, 1);
  if (getTcHeaderPcktType(pckt) != 1) 
    return 0; 

  setTcHeaderSecHeaderFlag(pckt, 0);
  if (getTcHeaderSecHeaderFlag(pckt) != 0) 
    return 0; 
  setTcHeaderSecHeaderFlag(pckt, 1);
  if (getTcHeaderSecHeaderFlag(pckt) != 1) 
    return 0; 

  setTcHeaderAPID(pckt, 0);
  if (getTcHeaderAPID(pckt) != 0) 
    return 0; 
  setTcHeaderAPID(pckt, 2047);
  if (getTcHeaderAPID(pckt) != 2047) 
    return 0; 

  setTcHeaderSeqFlags(pckt, 0);
  if (getTcHeaderSeqFlags(pckt) != 0) 
    return 0; 
  setTcHeaderSeqFlags(pckt, 3);
  if (getTcHeaderSeqFlags(pckt) != 3) 
    return 0; 

  setTcHeaderSeqCount(pckt, 0);
  if (getTcHeaderSeqCount(pckt) != 0) 
    return 0; 
  setTcHeaderSeqCount(pckt, 16383);
  if (getTcHeaderSeqCount(pckt) != 16383) 
    return 0; 

  setTcHeaderPcktDataLen(pckt, 0);
  if (getTcHeaderPcktDataLen(pckt) != 0) 
    return 0; 
  setTcHeaderPcktDataLen(pckt, MAX_SHORT);
  if (getTcHeaderPcktDataLen(pckt) != MAX_SHORT) 
    return 0; 

  setTcHeaderPUSVersion(pckt, 0);
  if (getTcHeaderPUSVersion(pckt) != 0) 
    return 0; 
  setTcHeaderPUSVersion(pckt, 15);
  if (getTcHeaderPUSVersion(pckt) != 15) 
    return 0; 

  setTcHeaderAckAccFlag(pckt, 0);
  if (getTcHeaderAckAccFlag(pckt) != 0) 
    return 0; 
  setTcHeaderAckAccFlag(pckt, 1);
  if (getTcHeaderAckAccFlag(pckt) != 1) 
    return 0; 

  setTcHeaderAckStartFlag(pckt, 0);
  if (getTcHeaderAckStartFlag(pckt) != 0) 
    return 0; 
  setTcHeaderAckStartFlag(pckt, 1);
  if (getTcHeaderAckStartFlag(pckt) != 1) 
    return 0; 

  setTcHeaderAckProgFlag(pckt, 0);
  if (getTcHeaderAckProgFlag(pckt) != 0) 
    return 0; 
  setTcHeaderAckProgFlag(pckt, 1);
  if (getTcHeaderAckProgFlag(pckt) != 1) 
    return 0; 

  setTcHeaderAckTermFlag(pckt, 0);
  if (getTcHeaderAckTermFlag(pckt) != 0) 
    return 0; 
  setTcHeaderAckTermFlag(pckt, 1);
  if (getTcHeaderAckTermFlag(pckt) != 1) 
    return 0; 

  setTcHeaderServType(pckt, 0);
  if (getTcHeaderServType(pckt) != 0) 
    return 0; 
  setTcHeaderServType(pckt, MAX_CHAR);
  if (getTcHeaderServType(pckt) != MAX_CHAR) 
    return 0; 

  setTcHeaderServSubType(pckt, 0);
  if (getTcHeaderServSubType(pckt) != 0) 
    return 0; 
  setTcHeaderServSubType(pckt, MAX_CHAR);
  if (getTcHeaderServSubType(pckt) != MAX_CHAR) 
    return 0; 

  setTcHeaderSrcId(pckt, 0);
  if (getTcHeaderSrcId(pckt) != 0) 
    return 0; 

  setTcHeaderSrcId(pckt, MAX_CHAR);
  if (getTcHeaderSrcId(pckt) != MAX_CHAR) 
    return 0; 

  /*release packet and create a new one!*/
  CrFwPcktRelease(pckt);

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt2 = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /*test all TM header Getter and Setter*/
  setTmHeaderPcktVersionNmb(pckt2, 0);
  if (getTmHeaderPcktVersionNmb(pckt2) != 0) 
    return 0; 
  setTmHeaderPcktVersionNmb(pckt, 7);
  if (getTmHeaderPcktVersionNmb(pckt2) != 7) 
    return 0; 

  setTmHeaderPcktType(pckt2, 0);
  if (getTmHeaderPcktType(pckt2) != 0) 
    return 0; 
  setTmHeaderPcktType(pckt2, 1);
  if (getTmHeaderPcktType(pckt2) != 1) 
    return 0; 

  setTmHeaderSecHeaderFlag(pckt2, 0);
  if (getTmHeaderSecHeaderFlag(pckt2) != 0) 
    return 0; 
  setTmHeaderSecHeaderFlag(pckt2, 1);
  if (getTmHeaderSecHeaderFlag(pckt2) != 1) 
    return 0; 

  setTmHeaderAPID(pckt2, 0);
  if (getTmHeaderAPID(pckt2) != 0) 
    return 0; 
  setTmHeaderAPID(pckt2, 2047);
  if (getTmHeaderAPID(pckt2) != 2047) 
    return 0; 

  setTmHeaderSeqFlags(pckt2, 0);
  if (getTmHeaderSeqFlags(pckt2) != 0) 
    return 0; 
  setTmHeaderSeqFlags(pckt2, 3);
  if (getTmHeaderSeqFlags(pckt2) != 3) 
    return 0; 

  setTmHeaderSeqCount(pckt2, 0);
  if (getTmHeaderSeqCount(pckt2) != 0) 
    return 0; 
  setTmHeaderSeqCount(pckt2, 16383);
  if (getTmHeaderSeqCount(pckt2) != 16383) 
    return 0; 

  setTmHeaderPcktDataLen(pckt2, 0);
  if (getTmHeaderPcktDataLen(pckt2) != 0) 
    return 0; 
  setTmHeaderPcktDataLen(pckt2, MAX_SHORT);
  if (getTmHeaderPcktDataLen(pckt2) != MAX_SHORT) 
    return 0; 

  setTmHeaderPUSVersion(pckt2, 0);
  if (getTmHeaderPUSVersion(pckt2) != 0) 
    return 0; 
  setTmHeaderPUSVersion(pckt2, 15);
  if (getTmHeaderPUSVersion(pckt2) != 15) 
    return 0; 

  setTmHeaderSpaceTimeRefStatus(pckt2, 0);
  if (getTmHeaderSpaceTimeRefStatus(pckt2) != 0) 
    return 0; 
  setTmHeaderSpaceTimeRefStatus(pckt2, 15);
  if (getTmHeaderSpaceTimeRefStatus(pckt2) != 15) 
    return 0; 

  setTmHeaderServType(pckt2, 0);
  if (getTmHeaderServType(pckt2) != 0) 
    return 0; 
  setTmHeaderServType(pckt2, MAX_CHAR);
  if (getTmHeaderServType(pckt2) != MAX_CHAR) 
    return 0; 

  setTmHeaderServSubType(pckt2, 0);
  if (getTmHeaderServSubType(pckt2) != 0) 
    return 0; 
  setTmHeaderServSubType(pckt2, MAX_CHAR);
  if (getTmHeaderServSubType(pckt2) != MAX_CHAR) 
    return 0; 

  setTmHeaderDestId(pckt2, 0);
  if (getTmHeaderDestId(pckt2) != 0) 
    return 0; 
  setTmHeaderDestId(pckt2, MAX_CHAR);
  if (getTmHeaderDestId(pckt2) != MAX_CHAR) 
    return 0; 

  tim[0] = 0;
  tim[1] = 0;
  tim[2] = 0;
  tim[3] = 0;
  tim[4] = 0;
  tim[5] = 0;

  setTmHeaderTime(pckt2, tim);
  getTmHeaderTime(pckt2, timi);
  if (memcmp(tim, timi, sizeof(tim))) 
    return 0; 

  tim[0] = MAX_CHAR;
  tim[1] = MAX_CHAR;
  tim[2] = MAX_CHAR;
  tim[3] = MAX_CHAR;
  tim[4] = MAX_CHAR;
  tim[5] = MAX_CHAR;

  setTmHeaderTime(pckt2, tim);
  getTmHeaderTime(pckt2, timi);
  if (memcmp(tim, timi, sizeof(tim))) 
    return 0; 

  /*release packet and create a new one!*/
  CrFwPcktRelease(pckt2);

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt3 = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  CrFwPcktSetCmdRepType(pckt3,crCmdType);
  if (CrFwPcktGetCmdRepType(pckt3) != crCmdType) 
    return 0;

  if (CrFwPcktGetLength(pckt3) != pcktsize) 
    return 0;

  /*functions not used!!*/
  CrFwPcktSetCmdRepId(pckt3,1);
  if (CrFwPcktGetCmdRepId(pckt3) != 0) 
    return 0;

  CrFwPcktSetSeqCnt(pckt3,0);
  if (CrFwPcktGetSeqCnt(pckt3) != 0) 
    return 0;

  CrFwPcktSetServType(pckt3,17);
  if (CrFwPcktGetServType(pckt3) != 17) 
    return 0;

  CrFwPcktSetServSubType(pckt3,1);
  if (CrFwPcktGetServSubType(pckt3) != 1) 
    return 0;

  CrFwPcktSetDiscriminant(pckt3,0);
  if (CrFwPcktGetDiscriminant(pckt3) != 0) 
    return 0; 

  CrFwPcktSetSrc(pckt3,12);
  if (CrFwPcktGetSrc(pckt3) != 12) 
    return 0;
  
  CrFwPcktSetAckLevel(pckt3,1,0,0,0);
  if (CrFwPcktIsAcceptAck(pckt3) != 1) 
    return 0;
  if (CrFwPcktIsStartAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsProgressAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsTermAck(pckt3) != 0) 
    return 0;


  CrFwPcktSetAckLevel(pckt3,0,1,0,0);
  if (CrFwPcktIsAcceptAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsStartAck(pckt3) != 1) 
    return 0;
  if (CrFwPcktIsProgressAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsTermAck(pckt3) != 0) 
    return 0;


  CrFwPcktSetAckLevel(pckt3,0,0,1,0);
  if (CrFwPcktIsAcceptAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsStartAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsProgressAck(pckt3) != 1) 
    return 0;
  if (CrFwPcktIsTermAck(pckt3) != 0) 
    return 0;


  CrFwPcktSetAckLevel(pckt3,0,0,0,1);
  if (CrFwPcktIsAcceptAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsStartAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsProgressAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsTermAck(pckt3) != 1) 
    return 0;

  CrFwPcktSetGroup(pckt3,2);
  if (CrFwPcktGetGroup(pckt3) != 2) 
    return 0;

  CrFwPcktSetSeqCtrl(pckt3, 0);
  if (CrFwPcktGetSeqCtrl(pckt3) != 0)
    return 0;

  CrFwPcktSetApid(pckt3, 0);
  if (CrFwPcktGetApid(pckt3) != 0)
    return 0;



  /*release packet and create a new one!*/
  CrFwPcktRelease(pckt3);

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt4 = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  CrFwPcktSetCmdRepType(pckt4,crRepType);
  if (CrFwPcktGetCmdRepType(pckt4) != crRepType) 
    return 0;

  if (CrFwPcktGetLength(pckt4) != pcktsize) 
    return 0;

  /*functions not used!!*/
  CrFwPcktSetCmdRepId(pckt4,1);
  if (CrFwPcktGetCmdRepId(pckt4) != 0) 
    return 0;

  CrFwPcktSetSeqCnt(pckt4,0);
  if (CrFwPcktGetSeqCnt(pckt4) != 0) 
    return 0;

  timstp.t[0] = MAX_CHAR;
  timstp.t[1] = MAX_CHAR;
  timstp.t[2] = MAX_CHAR;
  timstp.t[3] = MAX_CHAR;
  timstp.t[4] = MAX_CHAR;
  timstp.t[5] = MAX_CHAR;
  
  CrFwPcktSetTimeStamp(pckt4,timstp);
  timstpi = CrFwPcktGetTimeStamp(pckt4);

  if (memcmp(&timstp, &timstpi, sizeof(timstp))) 
    return 0; 

  CrFwPcktSetServType(pckt4,17);
  if (CrFwPcktGetServType(pckt4) != 17) 
    return 0;

  CrFwPcktSetServSubType(pckt4,2);
  if (CrFwPcktGetServSubType(pckt4) != 2) 
    return 0;

  CrFwPcktSetDiscriminant(pckt4,44);
  if (CrFwPcktGetDiscriminant(pckt4) != 0) 
    return 0; 

  CrFwPcktSetDest(pckt4,13);
  if (CrFwPcktGetDest(pckt4) != 13) 
    return 0;

  CrFwPcktSetGroup(pckt4,2);
  if (CrFwPcktGetGroup(pckt4) != 2) 
    return 0;

  CrFwPcktSetSeqCtrl(pckt4, 0);
  if (CrFwPcktGetSeqCtrl(pckt4) != 0)
    return 0;

  CrFwPcktSetApid(pckt4, 0);
  if (CrFwPcktGetApid(pckt4) != 0)
    return 0;


/*TBD remove if it works*/
  pstart = CrFwPcktGetParStart(pckt4);
  CRFW_UNUSED(pstart);
  /*release packet and create a new one!*/
  CrFwPcktRelease(pckt4);

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  return 1;   
}

CrFwBool_t CrPsPcktGetSetTestCase2()
{
  CrFwPckt_t pckt;
  unsigned int i, j, a;
  unsigned short pcktsize = 100;

  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 17.1 packet*/
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 17);
  CrFwPcktSetServSubType(pckt, 1);
  CrFwPcktSetDiscriminant(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 17)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 1)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  /* Check 17.2 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 17);
  CrFwPcktSetServSubType(pckt, 2);
  CrFwPcktSetDiscriminant(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 17)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 2)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  /* Check 17.3 packet*/
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 17);
  CrFwPcktSetServSubType(pckt, 3);
  CrFwPcktSetDiscriminant(pckt, 0);
  setOnBoardConnectCmdAppId(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 17)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 3)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getOnBoardConnectCmdAppId(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setOnBoardConnectCmdAppId(pckt, MAX_SHORT);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getOnBoardConnectCmdAppId(pckt) != MAX_SHORT)
    return 0;

  /* Check 17.4 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 17);
  CrFwPcktSetServSubType(pckt, 4);
  CrFwPcktSetDiscriminant(pckt, 0);
  setOnBoardConnectRepDest(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 17)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 4)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getOnBoardConnectRepDest(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setOnBoardConnectRepDest(pckt, MAX_SHORT);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getOnBoardConnectRepDest(pckt) != MAX_SHORT)
    return 0;

  /* Check 1.1 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 1);
  CrFwPcktSetServSubType(pckt, 1);
  CrFwPcktSetDiscriminant(pckt, 0);
  setVerSuccessAccRepPcktVersionNmb(pckt, 0);
  setVerSuccessAccRepPcktType(pckt, 0);
  setVerSuccessAccRepSecHeaderFlag(pckt, 0);
  setVerSuccessAccRepAPID(pckt, 0);
  setVerSuccessAccRepSeqFlags(pckt, 0);
  setVerSuccessAccRepSeqCount(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 1)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 1)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerSuccessAccRepPcktVersionNmb(pckt) != 0)
    return 0;
  if (getVerSuccessAccRepPcktType(pckt) != 0)
    return 0;
  if (getVerSuccessAccRepSecHeaderFlag(pckt) != 0)
    return 0;
  if (getVerSuccessAccRepAPID(pckt) != 0)
    return 0;
  if (getVerSuccessAccRepSeqFlags(pckt) != 0)
    return 0;
  if (getVerSuccessAccRepSeqCount(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setVerSuccessAccRepPcktVersionNmb(pckt, 7);
  setVerSuccessAccRepPcktType(pckt, 1);
  setVerSuccessAccRepSecHeaderFlag(pckt, 1);
  setVerSuccessAccRepAPID(pckt, 2047);
  setVerSuccessAccRepSeqFlags(pckt, 3);
  setVerSuccessAccRepSeqCount(pckt, 16383);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerSuccessAccRepPcktVersionNmb(pckt) != 7)
    return 0;
  if (getVerSuccessAccRepPcktType(pckt) != 1)
    return 0;
  if (getVerSuccessAccRepSecHeaderFlag(pckt) != 1)
    return 0;
  if (getVerSuccessAccRepAPID(pckt) != 2047)
    return 0;
  if (getVerSuccessAccRepSeqFlags(pckt) != 3)
    return 0;
  if (getVerSuccessAccRepSeqCount(pckt) != 16383)
    return 0;

  setVerSuccessAccRepRid(pckt, 0);
  if (getVerSuccessAccRepRid(pckt) != 0)
    return 0;

  setVerSuccessAccRepRid(pckt, MAX_INT);
  if (getVerSuccessAccRepRid(pckt) != MAX_INT)
    return 0;

  /* Check 1.2 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 1);
  CrFwPcktSetServSubType(pckt, 2);
  CrFwPcktSetDiscriminant(pckt, 0);
  setVerFailedAccRepPcktVersionNmb(pckt, 0);
  setVerFailedAccRepPcktType(pckt, 0);
  setVerFailedAccRepSecHeaderFlag(pckt, 0);
  setVerFailedAccRepAPID(pckt, 0);
  setVerFailedAccRepSeqFlags(pckt, 0);
  setVerFailedAccRepSeqCount(pckt, 0);
  setVerFailedAccRepFailureCode(pckt, 0);
  setVerFailedAccRepFailureData(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 1)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 2)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerFailedAccRepPcktVersionNmb(pckt) != 0)
    return 0;
  if (getVerFailedAccRepPcktType(pckt) != 0)
    return 0;
  if (getVerFailedAccRepSecHeaderFlag(pckt) != 0)
    return 0;
  if (getVerFailedAccRepAPID(pckt) != 0)
    return 0;
  if (getVerFailedAccRepSeqFlags(pckt) != 0)
    return 0;
  if (getVerFailedAccRepSeqCount(pckt) != 0)
    return 0;
  if (getVerFailedAccRepFailureCode(pckt) != 0)
    return 0;
  if (getVerFailedAccRepFailureData(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setVerFailedAccRepPcktVersionNmb(pckt, 7);
  setVerFailedAccRepPcktType(pckt, 1);
  setVerFailedAccRepSecHeaderFlag(pckt, 1);
  setVerFailedAccRepAPID(pckt, 2047);
  setVerFailedAccRepSeqFlags(pckt, 3);
  setVerFailedAccRepSeqCount(pckt, 16383);
  setVerFailedAccRepFailureCode(pckt, MAX_SHORT);
  setVerFailedAccRepFailureData(pckt, MAX_INT);

  if (CrFwPcktGetDiscriminant(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedAccRepPcktVersionNmb(pckt) != 7)
    return 0;
  if (getVerFailedAccRepPcktType(pckt) != 1)
    return 0;
  if (getVerFailedAccRepSecHeaderFlag(pckt) != 1)
    return 0;
  if (getVerFailedAccRepAPID(pckt) != 2047)
    return 0;
  if (getVerFailedAccRepSeqFlags(pckt) != 3)
    return 0;
  if (getVerFailedAccRepSeqCount(pckt) != 16383)
    return 0;
  if (getVerFailedAccRepFailureCode(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedAccRepFailureData(pckt) != MAX_INT)
    return 0;  

  setVerFailedAccRepRid(pckt, 0);
  if (getVerFailedAccRepRid(pckt) != 0)
    return 0;

  setVerFailedAccRepRid(pckt, MAX_INT);
  if (getVerFailedAccRepRid(pckt) != MAX_INT)
    return 0;

  /* Check 1.3 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 1);
  CrFwPcktSetServSubType(pckt, 3);
  CrFwPcktSetDiscriminant(pckt, 0);
  setVerSuccessStartRepPcktVersionNmb(pckt, 0);
  setVerSuccessStartRepPcktType(pckt, 0);
  setVerSuccessStartRepSecHeaderFlag(pckt, 0);
  setVerSuccessStartRepAPID(pckt, 0);
  setVerSuccessStartRepSeqFlags(pckt, 0);
  setVerSuccessStartRepSeqCount(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 1)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 3)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerSuccessStartRepPcktVersionNmb(pckt) != 0)
    return 0;
  if (getVerSuccessStartRepPcktType(pckt) != 0)
    return 0;
  if (getVerSuccessStartRepSecHeaderFlag(pckt) != 0)
    return 0;
  if (getVerSuccessStartRepAPID(pckt) != 0)
    return 0;
  if (getVerSuccessStartRepSeqFlags(pckt) != 0)
    return 0;
  if (getVerSuccessStartRepSeqCount(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setVerSuccessStartRepPcktVersionNmb(pckt, 7);
  setVerSuccessStartRepPcktType(pckt, 1);
  setVerSuccessStartRepSecHeaderFlag(pckt, 1);
  setVerSuccessStartRepAPID(pckt, 2047);
  setVerSuccessStartRepSeqFlags(pckt, 3);
  setVerSuccessStartRepSeqCount(pckt, 16383);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerSuccessStartRepPcktVersionNmb(pckt) != 7)
    return 0;
  if (getVerSuccessStartRepPcktType(pckt) != 1)
    return 0;
  if (getVerSuccessStartRepSecHeaderFlag(pckt) != 1)
    return 0;
  if (getVerSuccessStartRepAPID(pckt) != 2047)
    return 0;
  if (getVerSuccessStartRepSeqFlags(pckt) != 3)
    return 0;
  if (getVerSuccessStartRepSeqCount(pckt) != 16383)
    return 0;

  setVerSuccessStartRepRid(pckt, 0);
  if (getVerSuccessStartRepRid(pckt) != 0)
    return 0;

  setVerSuccessStartRepRid(pckt, MAX_INT);
  if (getVerSuccessStartRepRid(pckt) != MAX_INT)
    return 0;

  /* Check 1.4 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 1);
  CrFwPcktSetServSubType(pckt, 4);
  CrFwPcktSetDiscriminant(pckt, 0);
  setVerFailedStartRepPcktVersionNmb(pckt, 0);
  setVerFailedStartRepPcktType(pckt, 0);
  setVerFailedStartRepSecHeaderFlag(pckt, 0);
  setVerFailedStartRepAPID(pckt, 0);
  setVerFailedStartRepSeqFlags(pckt, 0);
  setVerFailedStartRepSeqCount(pckt, 0);
  setVerFailedStartRepFailureCode(pckt, 0);
  setVerFailedStartRepFailureData(pckt, 0);   

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 1)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 4)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerFailedStartRepPcktVersionNmb(pckt) != 0)
    return 0;
  if (getVerFailedStartRepPcktType(pckt) != 0)
    return 0;
  if (getVerFailedStartRepSecHeaderFlag(pckt) != 0)
    return 0;
  if (getVerFailedStartRepAPID(pckt) != 0)
    return 0;
  if (getVerFailedStartRepSeqFlags(pckt) != 0)
    return 0;
  if (getVerFailedStartRepSeqCount(pckt) != 0)
    return 0;
  if (getVerFailedStartRepFailureCode(pckt) != 0)
    return 0;
  if (getVerFailedStartRepFailureData(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setVerFailedStartRepPcktVersionNmb(pckt, 7);
  setVerFailedStartRepPcktType(pckt, 1);
  setVerFailedStartRepSecHeaderFlag(pckt, 1);
  setVerFailedStartRepAPID(pckt, 2047);
  setVerFailedStartRepSeqFlags(pckt, 3);
  setVerFailedStartRepSeqCount(pckt, 16383);
  setVerFailedStartRepFailureCode(pckt, MAX_SHORT);
  setVerFailedStartRepFailureData(pckt, MAX_INT);

  if (CrFwPcktGetDiscriminant(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedStartRepPcktVersionNmb(pckt) != 7)
    return 0;
  if (getVerFailedStartRepPcktType(pckt) != 1)
    return 0;
  if (getVerFailedStartRepSecHeaderFlag(pckt) != 1)
    return 0;
  if (getVerFailedStartRepAPID(pckt) != 2047)
    return 0;
  if (getVerFailedStartRepSeqFlags(pckt) != 3)
    return 0;
  if (getVerFailedStartRepSeqCount(pckt) != 16383)
    return 0;
  if (getVerFailedStartRepFailureCode(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedStartRepFailureData(pckt) != MAX_INT)
    return 0; 

  setVerFailedStartRepRid(pckt, 0);
  if (getVerFailedStartRepRid(pckt) != 0)
    return 0;

  setVerFailedStartRepRid(pckt, MAX_INT);
  if (getVerFailedStartRepRid(pckt) != MAX_INT)
    return 0;

  /* Check 1.5 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 1);
  CrFwPcktSetServSubType(pckt, 5);
  CrFwPcktSetDiscriminant(pckt, 0);
  setVerSuccessPrgrRepPcktVersionNmb(pckt, 0);
  setVerSuccessPrgrRepPcktType(pckt, 0);
  setVerSuccessPrgrRepSecHeaderFlag(pckt, 0);
  setVerSuccessPrgrRepAPID(pckt, 0);
  setVerSuccessPrgrRepSeqFlags(pckt, 0);
  setVerSuccessPrgrRepSeqCount(pckt, 0);
  setVerSuccessPrgrRepStepId(pckt, 0);    

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 1)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 5)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerSuccessPrgrRepPcktVersionNmb(pckt) != 0)
    return 0;
  if (getVerSuccessPrgrRepPcktType(pckt) != 0)
    return 0;
  if (getVerSuccessPrgrRepSecHeaderFlag(pckt) != 0)
    return 0;
  if (getVerSuccessPrgrRepAPID(pckt) != 0)
    return 0;
  if (getVerSuccessPrgrRepSeqFlags(pckt) != 0)
    return 0;
  if (getVerSuccessPrgrRepSeqCount(pckt) != 0)
    return 0;
  if (getVerSuccessPrgrRepStepId(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setVerSuccessPrgrRepPcktVersionNmb(pckt, 7);
  setVerSuccessPrgrRepPcktType(pckt, 1);
  setVerSuccessPrgrRepSecHeaderFlag(pckt, 1);
  setVerSuccessPrgrRepAPID(pckt, 2047);
  setVerSuccessPrgrRepSeqFlags(pckt, 3);
  setVerSuccessPrgrRepSeqCount(pckt, 16383);
  setVerSuccessPrgrRepStepId(pckt, MAX_INT);  
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerSuccessPrgrRepPcktVersionNmb(pckt) != 7)
    return 0;
  if (getVerSuccessPrgrRepPcktType(pckt) != 1)
    return 0;
  if (getVerSuccessPrgrRepSecHeaderFlag(pckt) != 1)
    return 0;
  if (getVerSuccessPrgrRepAPID(pckt) != 2047)
    return 0;
  if (getVerSuccessPrgrRepSeqFlags(pckt) != 3)
    return 0;
  if (getVerSuccessPrgrRepSeqCount(pckt) != 16383)
    return 0;
  if (getVerSuccessPrgrRepStepId(pckt) != MAX_INT)
    return 0;

  setVerSuccessPrgrRepRid(pckt, 0);
  if (getVerSuccessPrgrRepRid(pckt) != 0)
    return 0;

  setVerSuccessPrgrRepRid(pckt, MAX_INT);
  if (getVerSuccessPrgrRepRid(pckt) != MAX_INT)
    return 0;

  /* Check 1.6 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 1);
  CrFwPcktSetServSubType(pckt, 6);
  CrFwPcktSetDiscriminant(pckt, 0);
  setVerFailedPrgrRepPcktVersionNmb(pckt, 0);
  setVerFailedPrgrRepPcktType(pckt, 0);
  setVerFailedPrgrRepSecHeaderFlag(pckt, 0);
  setVerFailedPrgrRepAPID(pckt, 0);
  setVerFailedPrgrRepSeqFlags(pckt, 0);
  setVerFailedPrgrRepSeqCount(pckt, 0);
  setVerFailedPrgrRepStepId(pckt, 0);
  setVerFailedPrgrRepFailureCode(pckt, 0);
  setVerFailedPrgrRepFailureData(pckt, 0);
  
  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 1)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 6)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerFailedPrgrRepPcktVersionNmb(pckt) != 0)
    return 0;
  if (getVerFailedPrgrRepPcktType(pckt) != 0)
    return 0;
  if (getVerFailedPrgrRepSecHeaderFlag(pckt) != 0)
    return 0;
  if (getVerFailedPrgrRepAPID(pckt) != 0)
    return 0;
  if (getVerFailedPrgrRepSeqFlags(pckt) != 0)
    return 0;
  if (getVerFailedPrgrRepSeqCount(pckt) != 0)
    return 0;
  if (getVerFailedPrgrRepStepId(pckt) != 0)
    return 0;
  if (getVerFailedPrgrRepFailureCode(pckt) != 0)
    return 0;
  if (getVerFailedPrgrRepFailureData(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setVerFailedPrgrRepPcktVersionNmb(pckt, 7);
  setVerFailedPrgrRepPcktType(pckt, 1);
  setVerFailedPrgrRepSecHeaderFlag(pckt, 1);
  setVerFailedPrgrRepAPID(pckt, 2047);
  setVerFailedPrgrRepSeqFlags(pckt, 3);
  setVerFailedPrgrRepSeqCount(pckt, 16383);
  setVerFailedPrgrRepStepId(pckt, MAX_INT);
  setVerFailedPrgrRepFailureCode(pckt, MAX_SHORT);
  setVerFailedPrgrRepFailureData(pckt, MAX_INT);
    
  if (CrFwPcktGetDiscriminant(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedPrgrRepPcktVersionNmb(pckt) != 7)
    return 0;
  if (getVerFailedPrgrRepPcktType(pckt) != 1)
    return 0;
  if (getVerFailedPrgrRepSecHeaderFlag(pckt) != 1)
    return 0;
  if (getVerFailedPrgrRepAPID(pckt) != 2047)
    return 0;
  if (getVerFailedPrgrRepSeqFlags(pckt) != 3)
    return 0;
  if (getVerFailedPrgrRepSeqCount(pckt) != 16383)
    return 0;
  if (getVerFailedPrgrRepStepId(pckt) != MAX_INT)
    return 0;
  if (getVerFailedPrgrRepFailureCode(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedPrgrRepFailureData(pckt) != MAX_INT)
    return 0;

  setVerFailedPrgrRepRid(pckt, 0);
  if (getVerFailedPrgrRepRid(pckt) != 0)
    return 0;

  setVerFailedPrgrRepRid(pckt, MAX_INT);
  if (getVerFailedPrgrRepRid(pckt) != MAX_INT)
    return 0;

  /* Check 1.7 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 1);
  CrFwPcktSetServSubType(pckt, 7);
  CrFwPcktSetDiscriminant(pckt, 0);
  setVerSuccessTermRepPcktVersionNmb(pckt, 0);
  setVerSuccessTermRepPcktType(pckt, 0);
  setVerSuccessTermRepSecHeaderFlag(pckt, 0);
  setVerSuccessTermRepAPID(pckt, 0);
  setVerSuccessTermRepSeqFlags(pckt, 0);
  setVerSuccessTermRepSeqCount(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 1)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 7)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerSuccessTermRepPcktVersionNmb(pckt) != 0)
    return 0;
  if (getVerSuccessTermRepPcktType(pckt) != 0)
    return 0;
  if (getVerSuccessTermRepSecHeaderFlag(pckt) != 0)
    return 0;
  if (getVerSuccessTermRepAPID(pckt) != 0)
    return 0;
  if (getVerSuccessTermRepSeqFlags(pckt) != 0)
    return 0;
  if (getVerSuccessTermRepSeqCount(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setVerSuccessTermRepPcktVersionNmb(pckt, 7);
  setVerSuccessTermRepPcktType(pckt, 1);
  setVerSuccessTermRepSecHeaderFlag(pckt, 1);
  setVerSuccessTermRepAPID(pckt, 2047);
  setVerSuccessTermRepSeqFlags(pckt, 3);
  setVerSuccessTermRepSeqCount(pckt, 16383);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerSuccessTermRepPcktVersionNmb(pckt) != 7)
    return 0;
  if (getVerSuccessTermRepPcktType(pckt) != 1)
    return 0;
  if (getVerSuccessTermRepSecHeaderFlag(pckt) != 1)
    return 0;
  if (getVerSuccessTermRepAPID(pckt) != 2047)
    return 0;
  if (getVerSuccessTermRepSeqFlags(pckt) != 3)
    return 0;
  if (getVerSuccessTermRepSeqCount(pckt) != 16383)
    return 0;;

  setVerSuccessTermRepRid(pckt, 0);
  if (getVerSuccessTermRepRid(pckt) != 0)
    return 0;

  setVerSuccessTermRepRid(pckt, MAX_INT);
  if (getVerSuccessTermRepRid(pckt) != MAX_INT)
    return 0;

  /* Check 1.8 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 1);
  CrFwPcktSetServSubType(pckt, 8);
  CrFwPcktSetDiscriminant(pckt, 0);
  setVerFailedTermRepPcktVersionNmb(pckt, 0);
  setVerFailedTermRepPcktType(pckt, 0);
  setVerFailedTermRepSecHeaderFlag(pckt, 0);
  setVerFailedTermRepAPID(pckt, 0);
  setVerFailedTermRepSeqFlags(pckt, 0);
  setVerFailedTermRepSeqCount(pckt, 0);
  setVerFailedTermRepFailureCode(pckt, 0);
  setVerFailedTermRepFailureData(pckt, 0);
  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 1)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 8)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerFailedTermRepPcktVersionNmb(pckt) != 0)
    return 0;
  if (getVerFailedTermRepPcktType(pckt) != 0)
    return 0;
  if (getVerFailedTermRepSecHeaderFlag(pckt) != 0)
    return 0;
  if (getVerFailedTermRepAPID(pckt) != 0)
    return 0;
  if (getVerFailedTermRepSeqFlags(pckt) != 0)
    return 0;
  if (getVerFailedTermRepSeqCount(pckt) != 0)
    return 0;
  if (getVerFailedTermRepFailureCode(pckt) != 0)
    return 0;
  if (getVerFailedTermRepFailureData(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setVerFailedTermRepPcktVersionNmb(pckt, 7);
  setVerFailedTermRepPcktType(pckt, 1);
  setVerFailedTermRepSecHeaderFlag(pckt, 1);
  setVerFailedTermRepAPID(pckt, 2047);
  setVerFailedTermRepSeqFlags(pckt, 3);
  setVerFailedTermRepSeqCount(pckt, 16383);
  setVerFailedTermRepFailureCode(pckt, MAX_SHORT);
  setVerFailedTermRepFailureData(pckt, MAX_INT);
  if (CrFwPcktGetDiscriminant(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedTermRepPcktVersionNmb(pckt) != 7)
    return 0;
  if (getVerFailedTermRepPcktType(pckt) != 1)
    return 0;
  if (getVerFailedTermRepSecHeaderFlag(pckt) != 1)
    return 0;
  if (getVerFailedTermRepAPID(pckt) != 2047)
    return 0;
  if (getVerFailedTermRepSeqFlags(pckt) != 3)
    return 0;
  if (getVerFailedTermRepSeqCount(pckt) != 16383)
    return 0;
  if (getVerFailedTermRepFailureCode(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedTermRepFailureData(pckt) != MAX_INT)
    return 0;

  setVerFailedTermRepRid(pckt, 0);
  if (getVerFailedTermRepRid(pckt) != 0)
    return 0;

  setVerFailedTermRepRid(pckt, MAX_INT);
  if (getVerFailedTermRepRid(pckt) != MAX_INT)
    return 0;

  /* Check 1.10 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 1);
  CrFwPcktSetServSubType(pckt, 10);
  CrFwPcktSetDiscriminant(pckt, 0);
  setVerFailedRoutingRepPcktVersionNmb(pckt, 0);
  setVerFailedRoutingRepPcktType(pckt, 0);
  setVerFailedRoutingRepSecHeaderFlag(pckt, 0);
  setVerFailedRoutingRepAPID(pckt, 0);
  setVerFailedRoutingRepSeqFlags(pckt, 0);
  setVerFailedRoutingRepSeqCount(pckt, 0);
  setVerFailedRoutingRepFailureCode(pckt, 0);
  setVerFailedRoutingRepFailureData(pckt, 0);  

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 1)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 10)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerFailedRoutingRepPcktVersionNmb(pckt) != 0)
    return 0;
  if (getVerFailedRoutingRepPcktType(pckt) != 0)
    return 0;
  if (getVerFailedRoutingRepSecHeaderFlag(pckt) != 0)
    return 0;
  if (getVerFailedRoutingRepAPID(pckt) != 0)
    return 0;
  if (getVerFailedRoutingRepSeqFlags(pckt) != 0)
    return 0;
  if (getVerFailedRoutingRepSeqCount(pckt) != 0)
    return 0;
  if (getVerFailedRoutingRepFailureCode(pckt) != 0)
    return 0;
  if (getVerFailedRoutingRepFailureData(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setVerFailedRoutingRepPcktVersionNmb(pckt, 7);
  setVerFailedRoutingRepPcktType(pckt, 1);
  setVerFailedRoutingRepSecHeaderFlag(pckt, 1);
  setVerFailedRoutingRepAPID(pckt, 2047);
  setVerFailedRoutingRepSeqFlags(pckt, 3);
  setVerFailedRoutingRepSeqCount(pckt, 16383);
  setVerFailedRoutingRepFailureCode(pckt, MAX_SHORT);
  setVerFailedRoutingRepFailureData(pckt, MAX_INT);
  if (CrFwPcktGetDiscriminant(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedRoutingRepPcktVersionNmb(pckt) != 7)
    return 0;
  if (getVerFailedRoutingRepPcktType(pckt) != 1)
    return 0;
  if (getVerFailedRoutingRepSecHeaderFlag(pckt) != 1)
    return 0;
  if (getVerFailedRoutingRepAPID(pckt) != 2047)
    return 0;
  if (getVerFailedRoutingRepSeqFlags(pckt) != 3)
    return 0;
  if (getVerFailedRoutingRepSeqCount(pckt) != 16383)
    return 0;
  if (getVerFailedRoutingRepFailureCode(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedRoutingRepFailureData(pckt) != MAX_INT)
    return 0;

  setVerFailedRoutingRepRid(pckt, 0);
  if (getVerFailedRoutingRepRid(pckt) != 0)
    return 0;

  setVerFailedRoutingRepRid(pckt, MAX_INT);
  if (getVerFailedRoutingRepRid(pckt) != MAX_INT)
    return 0;

/* Service 3: Housekeeping Service */
  /*It is easier to test each getter or setter not the whole packet*/

  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(pcktsize);

  /* Check 3,1 packet*/

  CrFwPcktSetCmdRepType(pckt,crCmdType);
  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;

  CrFwPcktSetServType(pckt, 3);
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;

  CrFwPcktSetServSubType(pckt, 1);
  if (CrFwPcktGetServSubType(pckt) != 1)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != MAX_CHAR)
    return 0;

  CrFwPcktSetDiscriminant(pckt, 0);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setHkCreateCmdRepStrucId(pckt, MAX_CHAR);
  if (getHkCreateCmdRepStrucId(pckt) != MAX_CHAR)
    return 0;

  setHkCreateCmdRepStrucId(pckt, 0);
  if (getHkCreateCmdRepStrucId(pckt) != 0)
    return 0;

  setHkCreateCmdCollectionInterval(pckt, MAX_INT);
  if (getHkCreateCmdCollectionInterval(pckt) != MAX_INT)
    return 0;
  
  setHkCreateCmdCollectionInterval(pckt, 0);
  if (getHkCreateCmdCollectionInterval(pckt) != 0)
    return 0;

  setHkCreateCmdN1(pckt, MAX_INT); 
  if (getHkCreateCmdN1(pckt) != MAX_INT)
    return 0;

  setHkCreateCmdN1(pckt, 0); 
  if (getHkCreateCmdN1(pckt) != 0)
    return 0;
  
  a=sizeof(TcHeader_t);
  a=a+9;
  setHkCreateCmdRepStrucId(pckt, 0);
  setHkCreateCmdCollectionInterval(pckt, MAX_INT);

  setHkCreateCmdN1(pckt, 4);
  for (i=1;i<=4;i++)
  {
    a=a+2;
    setHkCreateCmdN1ParamIdItem(pckt, i, MAX_SHORT);
  }
  a=a+4;
  setHkCreateCmdNFA(pckt, 4);
  for (i=1;i<=4;i++)
  {
    a=a+8;
    setHkCreateCmdSCSampleRepNumItem(pckt, i, MAX_INT);
    setHkCreateCmdN2(pckt, i, 4);
    for (j=1;j<=4;j++)
    {
      a=a+2;
      setHkCreateCmdN2ParamIdItem(pckt, i, j, MAX_SHORT);
    }
  }

  if (a != getHkPcktSize(pckt))
    return 0;

  if (getHkCreateCmdRepStrucId(pckt) != 0)
    return 0;
  if (getHkCreateCmdCollectionInterval(pckt) != MAX_INT)
    return 0;
  if (getHkCreateCmdN1(pckt) != 4)
    return 0;
  for (i=1;i<=4;i++)
  {
    if (getHkCreateCmdN1ParamIdItem(pckt, i) != MAX_SHORT)
      return 0;
  } 
  if (getHkCreateCmdNFA(pckt) != 4)
    return 0;
  for (i=1;i<=4;i++)
  {
    if (getHkCreateCmdSCSampleRepNumItem(pckt, i) != MAX_INT)
      return 0;
    if (getHkCreateCmdN2(pckt, i) !=4 )
      return 0;
    for (j=1;j<=4;j++)
    {
      if (getHkCreateCmdN2ParamIdItem(pckt, i, j) !=MAX_SHORT)
        return 0;
    }      
  }

  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(pcktsize);

  /* Check 3,3 packet*/

  CrFwPcktSetCmdRepType(pckt,crCmdType);
  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;

  CrFwPcktSetServType(pckt, 3);
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;

  CrFwPcktSetServSubType(pckt, 3);
  if (CrFwPcktGetServSubType(pckt) != 3)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, 0);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setHkDeleteCmdN(pckt, MAX_INT); 
  if (getHkDeleteCmdN(pckt) != MAX_INT)
    return 0;  

  setHkDeleteCmdN(pckt, 0); 
  if (getHkDeleteCmdN(pckt) != 0)
    return 0;  

  a=sizeof(TcHeader_t) + 4;
  setHkDeleteCmdN(pckt, 50); 
  for (i=1;i<=50;i++)
  {
    a+=1;
    setHkDeleteCmdRepStrucIdItem(pckt, i, MAX_CHAR);
  }

  if (a != getHkPcktSize(pckt))
    return 0;
  if (getHkDeleteCmdN(pckt) != 50)
    return 0;
  for (i=1;i<=50;i++)
  {
    if (getHkDeleteCmdRepStrucIdItem(pckt, i) !=MAX_CHAR)
      return 0;
  }

  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(pcktsize);

  /* Check 3,5 packet*/

  CrFwPcktSetCmdRepType(pckt,crCmdType);
  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;

  CrFwPcktSetServType(pckt, 3);
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;

  CrFwPcktSetServSubType(pckt, 5);
  if (CrFwPcktGetServSubType(pckt) != 5)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, 0);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setHkEnableCmdN(pckt, MAX_INT); 
  if (getHkEnableCmdN(pckt) != MAX_INT)
    return 0;  

  setHkEnableCmdN(pckt, 0); 
  if (getHkEnableCmdN(pckt) != 0)
    return 0;  

  a=sizeof(TcHeader_t) + 4;
  setHkEnableCmdN(pckt, 50); 
  for (i=1;i<=50;i++)
  {
    a+=1;
    setHkEnableCmdRepStrucIdItem(pckt, i, MAX_CHAR);
  }

  if (a != getHkPcktSize(pckt))
    return 0;
  if (getHkEnableCmdN(pckt) != 50)
    return 0;
  for (i=1;i<=50;i++)
  {
    if (getHkEnableCmdRepStrucIdItem(pckt, i) !=MAX_CHAR)
      return 0;
  }

  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(pcktsize);


  /* Check 3,6 packet*/

  CrFwPcktSetCmdRepType(pckt,crCmdType);
  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;

  CrFwPcktSetServType(pckt, 3);
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;

  CrFwPcktSetServSubType(pckt, 6);
  if (CrFwPcktGetServSubType(pckt) != 6)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, 0);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setHkDisableCmdN(pckt, MAX_INT); 
  if (getHkDisableCmdN(pckt) != MAX_INT)
    return 0;  

  setHkDisableCmdN(pckt, 0); 
  if (getHkDisableCmdN(pckt) != 0)
    return 0;  

  a=sizeof(TcHeader_t) + 4;
  setHkDisableCmdN(pckt, 50); 
  for (i=1;i<=50;i++)
  {
    a+=1;
    setHkDisableCmdRepStrucIdItem(pckt, i, MAX_CHAR);
  }

  if (a != getHkPcktSize(pckt))
    return 0;
  if (getHkDisableCmdN(pckt) != 50)
    return 0;
  for (i=1;i<=50;i++)
  {
    if (getHkDisableCmdRepStrucIdItem(pckt, i) !=MAX_CHAR)
      return 0;
  }

  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(pcktsize);


  /* Check 3,9 packet*/

  CrFwPcktSetCmdRepType(pckt,crCmdType);
  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;

  CrFwPcktSetServType(pckt, 3);
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;

  CrFwPcktSetServSubType(pckt, 9);
  if (CrFwPcktGetServSubType(pckt) != 9)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, 0);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setHkRepStructCmdN(pckt, MAX_INT); 
  if (getHkRepStructCmdN(pckt) != MAX_INT)
    return 0;  

  setHkRepStructCmdN(pckt, 0); 
  if (getHkRepStructCmdN(pckt) != 0)
    return 0;  

  a=sizeof(TcHeader_t) + 4;
  setHkRepStructCmdN(pckt, 50); 
  for (i=1;i<=50;i++)
  {
    a+=1;
    setHkRepStructCmdRepStrucIdItem(pckt, i, MAX_CHAR);
  }

  if (a != getHkPcktSize(pckt))
    return 0;
  if (getHkRepStructCmdN(pckt) != 50)
    return 0;
  for (i=1;i<=50;i++)
  {
    if (getHkRepStructCmdRepStrucIdItem(pckt, i) !=MAX_CHAR)
      return 0;
  }

  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(pcktsize);


/* Check 3,10 packet*/

  CrFwPcktSetCmdRepType(pckt,crRepType);
  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;

  CrFwPcktSetServType(pckt, 3);
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;

  CrFwPcktSetServSubType(pckt, 10);
  if (CrFwPcktGetServSubType(pckt) != 10)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != MAX_CHAR)
    return 0;

  CrFwPcktSetDiscriminant(pckt, 0);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setHkRepStructRepRepStrucId(pckt, MAX_CHAR);
  if (getHkRepStructRepRepStrucId(pckt) != MAX_CHAR)
    return 0;

  setHkRepStructRepRepStrucId(pckt, 0);
  if (getHkRepStructRepRepStrucId(pckt) != 0)
    return 0;

  setHkRepStructRepPeriodicGenActionStatus(pckt, MAX_CHAR);
  if (getHkRepStructRepPeriodicGenActionStatus(pckt) != MAX_CHAR)
    return 0;
  
  setHkRepStructRepPeriodicGenActionStatus(pckt, 0);
  if (getHkRepStructRepPeriodicGenActionStatus(pckt) != 0)
    return 0;

  setHkRepStructRepCollectionInterval(pckt, MAX_INT);
  if (getHkRepStructRepCollectionInterval(pckt) != MAX_INT)
    return 0;
  
  setHkRepStructRepCollectionInterval(pckt, 0);
  if (getHkRepStructRepCollectionInterval(pckt) != 0)
    return 0;

  setHkRepStructRepN1(pckt, MAX_INT); 
  if (getHkRepStructRepN1(pckt) != MAX_INT)
    return 0;

  setHkRepStructRepN1(pckt, 0); 
  if (getHkRepStructRepN1(pckt) != 0)
    return 0;
 
  a=sizeof(TmHeader_t);
  a=a+10;
  setHkRepStructRepRepStrucId(pckt, 0);
  setHkRepStructRepCollectionInterval(pckt, MAX_INT);

  setHkRepStructRepN1(pckt, 4);

  for (i=1;i<=4;i++)
  {
    a=a+2;
    setHkRepStructRepN1ParamIdItem(pckt, i, MAX_SHORT);

  }
  a=a+4;
  setHkRepStructRepNFA(pckt, 3);
  for (i=1;i<=3;i++)
  {
    a=a+8;
    setHkRepStructRepSCSampleRepNumItem(pckt, i, MAX_INT);
    setHkRepStructRepN2(pckt, i, 4);
    for (j=1;j<=4;j++)
    {
      a=a+2;
      setHkRepStructRepN2ParamIdItem(pckt, i, j, MAX_SHORT);
    }
  }

  if (a != getHkPcktSize(pckt))
    return 0;

  if (getHkRepStructRepRepStrucId(pckt) != 0)
    return 0;
  if (getHkRepStructRepCollectionInterval(pckt) != MAX_INT)
    return 0;
  if (getHkRepStructRepN1(pckt) != 4)
    return 0;
  for (i=1;i<=4;i++)
  {
    if (getHkRepStructRepN1ParamIdItem(pckt, i) != MAX_SHORT)
      return 0;
  } 
  if (getHkRepStructRepNFA(pckt) != 3)
    return 0;
  for (i=1;i<=3;i++)
  {
    if (getHkRepStructRepSCSampleRepNumItem(pckt, i) != MAX_INT)
      return 0;
    if (getHkRepStructRepN2(pckt, i) !=4 )
      return 0;
    for (j=1;j<=4;j++)
    {
      if (getHkRepStructRepN2ParamIdItem(pckt, i, j) !=MAX_SHORT)
        return 0;
    }      
  }

  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(pcktsize);

  /* Prepare the Datapool */
  setDpsidItem(0,0);
  setDpnSimpleItem(0,1);
  setDplstIdItem(0, 1);


  /* Check 3,25 packet*/

  CrFwPcktSetCmdRepType(pckt,crRepType);
  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;

  CrFwPcktSetServType(pckt, 3);
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;

  CrFwPcktSetServSubType(pckt, 25);
  if (CrFwPcktGetServSubType(pckt) != 25)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != MAX_CHAR)
    return 0;

  CrFwPcktSetDiscriminant(pckt, 0);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setHkRepRepStrucId(pckt, MAX_CHAR); 
  if (getHkRepRepStrucId(pckt) != MAX_CHAR)
    return 0;  

  setHkRepRepStrucId(pckt, 0); 
  if (getHkRepRepStrucId(pckt) != 0)
    return 0;  

  setHkRepParamVal(pckt, MAX_INT); 
  if (getHkRepParamVal(pckt) != MAX_INT)
    return 0;  

  setHkRepParamVal(pckt, 0); 
  if (getHkRepParamVal(pckt) != 0)
    return 0;  
  
  a = sizeof(TmHeader_t) + getDpSize(1) + 1;
  if (getHkPcktSize(pckt) != a)
    return 0;

  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(pcktsize);

  /* Check 3.27 packet*/

  CrFwPcktSetCmdRepType(pckt,crCmdType);
  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;

  CrFwPcktSetServType(pckt, 3);
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;

  CrFwPcktSetServSubType(pckt, 27);
  if (CrFwPcktGetServSubType(pckt) != 27)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, 0);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setHkOneShotCmdN(pckt, MAX_INT); 
  if (getHkOneShotCmdN(pckt) != MAX_INT)
    return 0;  

  setHkOneShotCmdN(pckt, 0); 
  if (getHkOneShotCmdN(pckt) != 0)
    return 0;  

  a=sizeof(TcHeader_t) + 4;
  setHkOneShotCmdN(pckt, 50); 
  for (i=1;i<=50;i++)
  {
    a+=1;
    setHkOneShotCmdRepStrucIdItem(pckt, i, MAX_CHAR);
  }

  if (a != getHkPcktSize(pckt))
    return 0;
  if (getHkOneShotCmdN(pckt) != 50)
    return 0;
  for (i=1;i<=50;i++)
  {
    if (getHkOneShotCmdRepStrucIdItem(pckt, i) !=MAX_CHAR)
      return 0;
  }

  /* Create a 13,130 packet to test an impossible situation */

  CrFwPcktSetCmdRepType(pckt,crCmdType);
  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;

  CrFwPcktSetServType(pckt, 13);
  if (CrFwPcktGetServType(pckt) != 13)
    return 0;

  CrFwPcktSetServSubType(pckt, 130);
  if (CrFwPcktGetServSubType(pckt) != 130)
    return 0;

  CrFwPcktSetDiscriminant(pckt, 0);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  if (getHkPcktSize(pckt)!=0)
    return 0;

  CrFwPcktRelease(pckt);
  return 1;
}







CrFwBool_t CrPsPcktGetSetTestCase3()
{
  CrFwPckt_t pckt;
  unsigned int i, a;
  unsigned short pcktsize = 100;

  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 5,1 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 5);
  CrFwPcktSetServSubType(pckt, 1);
  CrFwPcktSetDiscriminant(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 5)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 1)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != MAX_CHAR)
    return 0;

  setEvtRep1EventId(pckt, MIN_VAL);
  if (getEvtRep1EventId(pckt) != MIN_VAL)
    return 0;
  setEvtRep1EventId(pckt, MAX_CHAR);
  if (getEvtRep1EventId(pckt) != MAX_CHAR)
    return 0;

  setEvtRep1AuxData(pckt, MIN_VAL);
  if (getEvtRep1AuxData(pckt) != MIN_VAL)
    return 0;
  setEvtRep1AuxData(pckt, MAX_INT);
  if (getEvtRep1AuxData(pckt) != MAX_INT)
    return 0;

  CrFwPcktRelease(pckt);

  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 5,2 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 5);
  CrFwPcktSetServSubType(pckt, 2);
  CrFwPcktSetDiscriminant(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 5)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 2)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != MAX_CHAR)
    return 0;

  setEvtRep2EventId(pckt, MIN_VAL);
  if (getEvtRep2EventId(pckt) != MIN_VAL)
    return 0;
  setEvtRep2EventId(pckt, MAX_CHAR);
  if (getEvtRep2EventId(pckt) != MAX_CHAR)
    return 0;

  setEvtRep2AuxData(pckt, MIN_VAL);
  if (getEvtRep2AuxData(pckt) != MIN_VAL)
    return 0;
  setEvtRep2AuxData(pckt, MAX_INT);
  if (getEvtRep2AuxData(pckt) != MAX_INT)
    return 0;

  CrFwPcktRelease(pckt);

  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 5,3 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 5);
  CrFwPcktSetServSubType(pckt, 3);
  CrFwPcktSetDiscriminant(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 5)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 3)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != MAX_CHAR)
    return 0;

  setEvtRep3EventId(pckt, MIN_VAL);
  if (getEvtRep3EventId(pckt) != MIN_VAL)
    return 0;
  setEvtRep3EventId(pckt, MAX_CHAR);
  if (getEvtRep3EventId(pckt) != MAX_CHAR)
    return 0;

  setEvtRep3AuxData(pckt, MIN_VAL);
  if (getEvtRep3AuxData(pckt) != MIN_VAL)
    return 0;
  setEvtRep3AuxData(pckt, MAX_INT);
  if (getEvtRep3AuxData(pckt) != MAX_INT)
    return 0;

  CrFwPcktRelease(pckt);

  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 5,4 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 5);
  CrFwPcktSetServSubType(pckt, 4);
  CrFwPcktSetDiscriminant(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 5)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 4)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != MAX_CHAR)
    return 0;

  setEvtRep4EventId(pckt, MIN_VAL);
  if (getEvtRep4EventId(pckt) != MIN_VAL)
    return 0;
  setEvtRep4EventId(pckt, MAX_CHAR);
  if (getEvtRep4EventId(pckt) != MAX_CHAR)
    return 0;

  setEvtRep4AuxData(pckt, MIN_VAL);
  if (getEvtRep4AuxData(pckt) != MIN_VAL)
    return 0;
  setEvtRep4AuxData(pckt, MAX_INT);
  if (getEvtRep4AuxData(pckt) != MAX_INT)
    return 0;

  CrFwPcktRelease(pckt);

  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 5,5 packet*/
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 5);
  CrFwPcktSetServSubType(pckt, 5);
  CrFwPcktSetDiscriminant(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 5)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 5)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  a=10;
  setEvtEnableCmdN(pckt, MIN_VAL);
  if (getEvtEnableCmdN(pckt) != MIN_VAL)
    return 0;
  setEvtEnableCmdN(pckt, MAX_INT);
  if (getEvtEnableCmdN(pckt) != MAX_INT)
    return 0;
  setEvtEnableCmdN(pckt, a);
  if (getEvtEnableCmdN(pckt) != a)
    return 0;

  for (i=1;i<a;i++)
  {
    setEvtEnableCmdEventIdItem(pckt, a, MIN_VAL);
    if (getEvtEnableCmdEventIdItem(pckt, a) != MIN_VAL)
      return 0;
    setEvtEnableCmdEventIdItem(pckt, a, MAX_CHAR);
    if (getEvtEnableCmdEventIdItem(pckt, a) != MAX_CHAR)
      return 0;
  }

  CrFwPcktRelease(pckt);

  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 5,6 packet*/
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 5);
  CrFwPcktSetServSubType(pckt, 6);
  CrFwPcktSetDiscriminant(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 5)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 6)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setEvtDisableCmdN(pckt, MIN_VAL);
  if (getEvtDisableCmdN(pckt) != MIN_VAL)
    return 0;
  setEvtDisableCmdN(pckt, MAX_INT);
  if (getEvtDisableCmdN(pckt) != MAX_INT)
    return 0;
  setEvtDisableCmdN(pckt, a);
  if (getEvtDisableCmdN(pckt) != a)
    return 0;

  a=3;
  for (i=1;i<a;i++)
  {
    setEvtDisableCmdEventIdItem(pckt, a, MIN_VAL);
    if (getEvtDisableCmdEventIdItem(pckt, a) != MIN_VAL)
      return 0;
    setEvtDisableCmdEventIdItem(pckt, a, MAX_CHAR);
    if (getEvtDisableCmdEventIdItem(pckt, a) != MAX_CHAR)
      return 0;
  }

  CrFwPcktRelease(pckt);

  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 5,8 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 5);
  CrFwPcktSetServSubType(pckt, 8);
  CrFwPcktSetDiscriminant(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 5)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 8)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setEvtRepDisabledRepN(pckt, MIN_VAL);
  if (getEvtRepDisabledRepN(pckt) != MIN_VAL)
    return 0;
  setEvtRepDisabledRepN(pckt, MAX_INT);
  if (getEvtRepDisabledRepN(pckt) != MAX_INT)
    return 0;
  setEvtRepDisabledRepN(pckt, a);
  if (getEvtRepDisabledRepN(pckt) != a)
    return 0;

  a=3;
  for (i=1;i<a;i++)
  {
    setEvtRepDisabledRepEventIdItem(pckt, a, MIN_VAL);
    if (getEvtRepDisabledRepEventIdItem(pckt, a) != MIN_VAL)
      return 0;
    setEvtRepDisabledRepEventIdItem(pckt, a, MAX_CHAR);
    if (getEvtRepDisabledRepEventIdItem(pckt, a) != MAX_CHAR)
      return 0;
  }

  CrFwPcktRelease(pckt);

  return 1;
}


CrFwBool_t CrPsPcktGetSetTestCase4()
{
  CrFwPckt_t pckt;
  unsigned int i;
  unsigned short pcktsize = 100;
  unsigned short parts = 5;

  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 13,1 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 13);
  CrFwPcktSetServSubType(pckt, 1);
  CrFwPcktSetDiscriminant(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 13)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 1)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setLptDownFirstRepTid(pckt, MIN_VAL);
  if (getLptDownFirstRepTid(pckt) != MIN_VAL)
    return 0;
  setLptDownFirstRepTid(pckt, MAX_INT);
  if (getLptDownFirstRepTid(pckt) != MAX_INT)
    return 0;

  setLptDownFirstRepPartSeqNmb(pckt, MIN_VAL);
  if (getLptDownFirstRepPartSeqNmb(pckt) != MIN_VAL)
    return 0;
  setLptDownFirstRepPartSeqNmb(pckt, MAX_INT);
  if (getLptDownFirstRepPartSeqNmb(pckt) != MAX_INT)
    return 0;

  CrFwPcktRelease(pckt);

  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 13,2 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 13);
  CrFwPcktSetServSubType(pckt, 2);
  CrFwPcktSetDiscriminant(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 13)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 2)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setLptDownInterRepTid(pckt, MIN_VAL);
  if (getLptDownInterRepTid(pckt) != MIN_VAL)
    return 0;
  setLptDownInterRepTid(pckt, MAX_INT);
  if (getLptDownInterRepTid(pckt) != MAX_INT)
    return 0;

  setLptDownInterRepPartSeqNmb(pckt, MIN_VAL);
  if (getLptDownInterRepPartSeqNmb(pckt) != MIN_VAL)
    return 0;
  setLptDownInterRepPartSeqNmb(pckt, MAX_INT);
  if (getLptDownInterRepPartSeqNmb(pckt) != MAX_INT)
    return 0;

  CrFwPcktRelease(pckt);

  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 13,3 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 13);
  CrFwPcktSetServSubType(pckt, 3);
  CrFwPcktSetDiscriminant(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 13)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 3)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setLptDownLastRepTid(pckt, MIN_VAL);
  if (getLptDownLastRepTid(pckt) != MIN_VAL)
    return 0;
  setLptDownLastRepTid(pckt, MAX_INT);
  if (getLptDownLastRepTid(pckt) != MAX_INT)
    return 0;

  setLptDownLastRepPartSeqNmb(pckt, MIN_VAL);
  if (getLptDownLastRepPartSeqNmb(pckt) != MIN_VAL)
    return 0;
  setLptDownLastRepPartSeqNmb(pckt, MAX_INT);
  if (getLptDownLastRepPartSeqNmb(pckt) != MAX_INT)
    return 0;

  CrFwPcktRelease(pckt);

  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 13,9 packet*/
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 13);
  CrFwPcktSetServSubType(pckt, 9);
  CrFwPcktSetDiscriminant(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 13)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 9)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setLptUpFirstCmdTid(pckt, MIN_VAL);
  if (getLptUpFirstCmdTid(pckt) != MIN_VAL)
    return 0;
  setLptUpFirstCmdTid(pckt, MAX_INT);
  if (getLptUpFirstCmdTid(pckt) != MAX_INT)
    return 0;

  setLptUpFirstCmdPartSeqNmb(pckt, MIN_VAL);
  if (getLptUpFirstCmdPartSeqNmb(pckt) != MIN_VAL)
    return 0;
  setLptUpFirstCmdPartSeqNmb(pckt, MAX_INT);
  if (getLptUpFirstCmdPartSeqNmb(pckt) != MAX_INT)
    return 0;

  for (i=0;i<=parts;i++)
  {
    setLptUpFirstCmdPart(pckt, MIN_VAL, i);
    if (getLptUpFirstCmdPart(pckt, i) != MIN_VAL)
      return 0;
    setLptUpFirstCmdPart(pckt, MAX_SHORT, i);
    if (getLptUpFirstCmdPart(pckt, i) != MAX_SHORT)
      return 0;    
  }

  CrFwPcktRelease(pckt);

  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 13,10 packet*/
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 13);
  CrFwPcktSetServSubType(pckt, 10);
  CrFwPcktSetDiscriminant(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 13)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 10)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setLptUpInterCmdTid(pckt, MIN_VAL);
  if (getLptUpInterCmdTid(pckt) != MIN_VAL)
    return 0;
  setLptUpInterCmdTid(pckt, MAX_INT);
  if (getLptUpInterCmdTid(pckt) != MAX_INT)
    return 0;

  setLptUpInterCmdPartSeqNmb(pckt, MIN_VAL);
  if (getLptUpInterCmdPartSeqNmb(pckt) != MIN_VAL)
    return 0;
  setLptUpInterCmdPartSeqNmb(pckt, MAX_INT);
  if (getLptUpInterCmdPartSeqNmb(pckt) != MAX_INT)
    return 0;

  for (i=0;i<=parts;i++)
  {
    setLptUpInterCmdPart(pckt, MIN_VAL, i);
    if (getLptUpInterCmdPart(pckt, i) != MIN_VAL)
      return 0;
    setLptUpInterCmdPart(pckt, MAX_SHORT, i);
    if (getLptUpInterCmdPart(pckt, i) != MAX_SHORT)
      return 0;    
  }

  CrFwPcktRelease(pckt);

  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 13,11 packet*/
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 13);
  CrFwPcktSetServSubType(pckt, 11);
  CrFwPcktSetDiscriminant(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 13)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 11)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setLptUpLastCmdTid(pckt, MIN_VAL);
  if (getLptUpLastCmdTid(pckt) != MIN_VAL)
    return 0;
  setLptUpLastCmdTid(pckt, MAX_INT);
  if (getLptUpLastCmdTid(pckt) != MAX_INT)
    return 0;

  setLptUpLastCmdPartSeqNmb(pckt, MIN_VAL);
  if (getLptUpLastCmdPartSeqNmb(pckt) != MIN_VAL)
    return 0;
  setLptUpLastCmdPartSeqNmb(pckt, MAX_INT);
  if (getLptUpLastCmdPartSeqNmb(pckt) != MAX_INT)
    return 0;

  for (i=0;i<=parts;i++)
  {
    setLptUpLastCmdPart(pckt, MIN_VAL, i);
    if (getLptUpLastCmdPart(pckt, i) != MIN_VAL)
      return 0;
    setLptUpLastCmdPart(pckt, MAX_SHORT, i);
    if (getLptUpLastCmdPart(pckt, i) != MAX_SHORT)
      return 0;    
  }

  CrFwPcktRelease(pckt);

  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 13,16 packet*/
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 13);
  CrFwPcktSetServSubType(pckt, 16);
  CrFwPcktSetDiscriminant(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 13)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 16)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setLptUpAbortRepTid(pckt, MIN_VAL);
  if (getLptUpAbortRepTid(pckt) != MIN_VAL)
    return 0;
  setLptUpAbortRepTid(pckt, MAX_INT);
  if (getLptUpAbortRepTid(pckt) != MAX_INT)
    return 0;

  setLptUpAbortRepFailReason(pckt, MIN_VAL);
  if (getLptUpAbortRepFailReason(pckt) != MIN_VAL)
    return 0;
  setLptUpAbortRepFailReason(pckt, MAX_INT);
  if (getLptUpAbortRepFailReason(pckt) != MAX_INT)
    return 0;

  CrFwPcktRelease(pckt);

  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 13,129 packet*/
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 13);
  CrFwPcktSetServSubType(pckt, 129);
  CrFwPcktSetDiscriminant(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 13)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 129)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setLptStartDownCmdTid(pckt, MIN_VAL);
  if (getLptStartDownCmdTid(pckt) != MIN_VAL)
    return 0;
  setLptStartDownCmdTid(pckt, MAX_INT);
  if (getLptStartDownCmdTid(pckt) != MAX_INT)
    return 0;

  CrFwPcktRelease(pckt);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 13,130 packet*/
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 13);
  CrFwPcktSetServSubType(pckt, 130);
  CrFwPcktSetDiscriminant(pckt, 0);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 13)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 130)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  setLptAbortDownCmdTid(pckt, MIN_VAL);
  if (getLptAbortDownCmdTid(pckt) != MIN_VAL)
    return 0;
  setLptAbortDownCmdTid(pckt, MAX_INT);
  if (getLptAbortDownCmdTid(pckt) != MAX_INT)
    return 0;

  CrFwPcktRelease(pckt);

  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  return 1;
}

