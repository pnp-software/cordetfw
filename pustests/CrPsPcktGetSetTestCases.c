/**
 * @file
 *
 * Implementation of test cases for DataPool Components.
 *
 * @author Christian Reimers <christian.reimersy@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * @copyright Department of Astrophysics, University of Vienna, 2017, All Rights Reserved
 *
 * This file is part of CORDET Framework.
 *
 * CORDET Framework is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CORDET Framework is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CORDET Framework.  If not, see <http://www.gnu.org/licenses/>.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#include <stdlib.h>
#include "CrFwRepErrStub.h"
#include "CrFwInStreamSocket.h"
#include "CrFwClientSocket.h"
#include "CrFwServerSocket.h"
#include "CrFwOutStreamSocket.h"
#include "CrFwInStreamTestCases.h"
#include "CrFwInStreamStub.h"
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
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include system files */
#include <stdio.h>
#include <unistd.h>

#include <CrFwOutCmpSample1.h>
#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServTest.h>
#include <Services/General/CrPsPktServReqVerif.h>
#include <Services/General/CrPsPktServTest.h>
#include <Services/General/CrPsPktServHk.h>
#include <Services/General/CrPsPktServHkSupp.h>
#include <Services/General/CrPsPktServEvt.h>
#include <Services/General/CrPsPktServEvtSupp.h>
#include <Services/General/CrPsPktServLpt.h>
#include <Services/General/CrPsPktServLptSupp.h>
#include <Services/General/CrPsPktUtil.h>
#include <CrPsDebug.h>

#define MAX_CHAR 255
#define MAX_SHORT 65535
#define MAX_INT 4294967295u
#define MIN_VAL 0


/* ---------------------------------------------------------------------------------------------*/

CrFwBool_t CrPsPcktGetSetTestCase1()
{

  CrFwPckt_t pckt, pckt2, pckt3, pckt4;
  unsigned char tim[6], timi[6];
  char * pstart;
  unsigned short pcktsize = 30;
  CrFwTimeStamp_t timstp,timstpi;

  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /*test all TC header Getter and Setter*/
  setTcHeaderPcktVersionNmb(pckt, 0);
  DEBUGP_TSGS("getTcHeaderPcktVersionNmb(): %d \n", getTcHeaderPcktVersionNmb(pckt));
  if (getTcHeaderPcktVersionNmb(pckt) != 0) 
    return 0; 

  setTcHeaderPcktVersionNmb(pckt, 7);
  DEBUGP_TSGS("getTcHeaderPcktVersionNmb(): %d \n", getTcHeaderPcktVersionNmb(pckt));
  if (getTcHeaderPcktVersionNmb(pckt) != 7) 
    return 0;

  setTcHeaderPcktType(pckt, 0);
  DEBUGP_TSGS("getTcHeaderPcktType(): %d \n", getTcHeaderPcktType(pckt));
  if (getTcHeaderPcktType(pckt) != 0) 
    return 0; 
  setTcHeaderPcktType(pckt, 1);
  DEBUGP_TSGS("getTcHeaderPcktType(): %d \n", getTcHeaderPcktType(pckt));
  if (getTcHeaderPcktType(pckt) != 1) 
    return 0; 

  setTcHeaderSecHeaderFlag(pckt, 0);
  DEBUGP_TSGS("getTcHeaderSecHeaderFlag(): %d \n", getTcHeaderSecHeaderFlag(pckt));
  if (getTcHeaderSecHeaderFlag(pckt) != 0) 
    return 0; 
  setTcHeaderSecHeaderFlag(pckt, 1);
  DEBUGP_TSGS("getTcHeaderSecHeaderFlag(): %d \n", getTcHeaderSecHeaderFlag(pckt));
  if (getTcHeaderSecHeaderFlag(pckt) != 1) 
    return 0; 

  setTcHeaderAPID(pckt, 0);
  DEBUGP_TSGS("getTcHeaderAPID(): %d \n", getTcHeaderAPID(pckt));
  if (getTcHeaderAPID(pckt) != 0) 
    return 0; 
  setTcHeaderAPID(pckt, 2047);
  DEBUGP_TSGS("getTcHeaderAPID(): %d \n", getTcHeaderAPID(pckt));
  if (getTcHeaderAPID(pckt) != 2047) 
    return 0; 

  setTcHeaderSeqFlags(pckt, 0);
  DEBUGP_TSGS("getTcHeaderSeqFlags(): %d \n", getTcHeaderSeqFlags(pckt));
  if (getTcHeaderSeqFlags(pckt) != 0) 
    return 0; 
  setTcHeaderSeqFlags(pckt, 3);
  DEBUGP_TSGS("getTcHeaderSeqFlags(): %d \n", getTcHeaderSeqFlags(pckt));
  if (getTcHeaderSeqFlags(pckt) != 3) 
    return 0; 

  setTcHeaderSeqCount(pckt, 0);
  DEBUGP_TSGS("getTcHeaderSeqCount(): %d \n", getTcHeaderSeqCount(pckt));
  if (getTcHeaderSeqCount(pckt) != 0) 
    return 0; 
  setTcHeaderSeqCount(pckt, 16383);
  DEBUGP_TSGS("getTcHeaderSeqCount(): %d \n", getTcHeaderSeqCount(pckt));
  if (getTcHeaderSeqCount(pckt) != 16383) 
    return 0; 

  setTcHeaderPcktDataLen(pckt, 0);
  DEBUGP_TSGS("getTcHeaderPcktDataLen(): %d \n", getTcHeaderPcktDataLen(pckt));
  if (getTcHeaderPcktDataLen(pckt) != 0) 
    return 0; 
  setTcHeaderPcktDataLen(pckt, MAX_SHORT);
  DEBUGP_TSGS("getTcHeaderPcktDataLen(): %d \n", getTcHeaderPcktDataLen(pckt));
  if (getTcHeaderPcktDataLen(pckt) != MAX_SHORT) 
    return 0; 

  setTcHeaderPUSVersion(pckt, 0);
  DEBUGP_TSGS("getTcHeaderPUSVersion(): %d \n", getTcHeaderPUSVersion(pckt));
  if (getTcHeaderPUSVersion(pckt) != 0) 
    return 0; 
  setTcHeaderPUSVersion(pckt, 15);
  DEBUGP_TSGS("getTcHeaderPUSVersion(): %d \n", getTcHeaderPUSVersion(pckt));
  if (getTcHeaderPUSVersion(pckt) != 15) 
    return 0; 

  setTcHeaderAckAccFlag(pckt, 0);
  DEBUGP_TSGS("getTcHeaderAckAccFlag(): %d \n", getTcHeaderAckAccFlag(pckt));
  if (getTcHeaderAckAccFlag(pckt) != 0) 
    return 0; 
  setTcHeaderAckAccFlag(pckt, 1);
  DEBUGP_TSGS("getTcHeaderAckAccFlag(): %d \n", getTcHeaderAckAccFlag(pckt));
  if (getTcHeaderAckAccFlag(pckt) != 1) 
    return 0; 

  setTcHeaderAckStartFlag(pckt, 0);
  DEBUGP_TSGS("getTcHeaderAckStartFlag(): %d \n", getTcHeaderAckStartFlag(pckt));
  if (getTcHeaderAckStartFlag(pckt) != 0) 
    return 0; 
  setTcHeaderAckStartFlag(pckt, 1);
  DEBUGP_TSGS("getTcHeaderAckStartFlag(): %d \n", getTcHeaderAckStartFlag(pckt));
  if (getTcHeaderAckStartFlag(pckt) != 1) 
    return 0; 

  setTcHeaderAckProgFlag(pckt, 0);
  DEBUGP_TSGS("getTcHeaderAckProgFlag(): %d \n", getTcHeaderAckProgFlag(pckt));
  if (getTcHeaderAckProgFlag(pckt) != 0) 
    return 0; 
  setTcHeaderAckProgFlag(pckt, 1);
  DEBUGP_TSGS("getTcHeaderAckProgFlag(): %d \n", getTcHeaderAckProgFlag(pckt));
  if (getTcHeaderAckProgFlag(pckt) != 1) 
    return 0; 

  setTcHeaderAckTermFlag(pckt, 0);
  DEBUGP_TSGS("getTcHeaderAckTermFlag(): %d \n", getTcHeaderAckTermFlag(pckt));
  if (getTcHeaderAckTermFlag(pckt) != 0) 
    return 0; 
  setTcHeaderAckTermFlag(pckt, 1);
  DEBUGP_TSGS("getTcHeaderAckTermFlag(): %d \n", getTcHeaderAckTermFlag(pckt));
  if (getTcHeaderAckTermFlag(pckt) != 1) 
    return 0; 

  setTcHeaderServType(pckt, 0);
  DEBUGP_TSGS("getTcHeaderServType(): %d \n", getTcHeaderServType(pckt));
  if (getTcHeaderServType(pckt) != 0) 
    return 0; 
  setTcHeaderServType(pckt, MAX_CHAR);
  DEBUGP_TSGS("getTcHeaderServType(): %d \n", getTcHeaderServType(pckt));
  if (getTcHeaderServType(pckt) != MAX_CHAR) 
    return 0; 

  setTcHeaderServSubType(pckt, 0);
  DEBUGP_TSGS("getTcHeaderServSubType(): %d \n", getTcHeaderServSubType(pckt));
  if (getTcHeaderServSubType(pckt) != 0) 
    return 0; 
  setTcHeaderServSubType(pckt, MAX_CHAR);
  DEBUGP_TSGS("getTcHeaderServSubType(): %d \n", getTcHeaderServSubType(pckt));
  if (getTcHeaderServSubType(pckt) != MAX_CHAR) 
    return 0; 

  setTcHeaderSrcId(pckt, 0);
  DEBUGP_TSGS("getTcHeaderSrcId(): %d \n", getTcHeaderSrcId(pckt));
  if (getTcHeaderSrcId(pckt) != 0) 
    return 0; 

  setTcHeaderSrcId(pckt, MAX_CHAR);
  DEBUGP_TSGS("getTcHeaderSrcId(): %d \n", getTcHeaderSrcId(pckt));
  if (getTcHeaderSrcId(pckt) != MAX_CHAR) 
    return 0; 

  /*release packet and create a new one!*/
  CrFwPcktRelease(pckt);

  /* Check if number of Allocated Packets = 0*/
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt2 = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /*test all TM header Getter and Setter*/
  setTmHeaderPcktVersionNmb(pckt2, 0);
  DEBUGP_TSGS("getTmHeaderPcktVersionNmb(): %d \n", getTmHeaderPcktVersionNmb(pckt2));
  if (getTmHeaderPcktVersionNmb(pckt2) != 0) 
    return 0; 
  setTmHeaderPcktVersionNmb(pckt, 7);
  DEBUGP_TSGS("getTmHeaderPcktVersionNmb(): %d \n", getTmHeaderPcktVersionNmb(pckt2));
  if (getTmHeaderPcktVersionNmb(pckt2) != 7) 
    return 0; 

  setTmHeaderPcktType(pckt2, 0);
  DEBUGP_TSGS("getTmHeaderPcktType(): %d \n", getTmHeaderPcktType(pckt2));
  if (getTmHeaderPcktType(pckt2) != 0) 
    return 0; 
  setTmHeaderPcktType(pckt2, 1);
  DEBUGP_TSGS("getTmHeaderPcktType(): %d \n", getTmHeaderPcktType(pckt2));
  if (getTmHeaderPcktType(pckt2) != 1) 
    return 0; 

  setTmHeaderSecHeaderFlag(pckt2, 0);
  DEBUGP_TSGS("getTmHeaderSecHeaderFlag(): %d \n", getTmHeaderSecHeaderFlag(pckt2));
  if (getTmHeaderSecHeaderFlag(pckt2) != 0) 
    return 0; 
  setTmHeaderSecHeaderFlag(pckt2, 1);
  DEBUGP_TSGS("getTmHeaderSecHeaderFlag(): %d \n", getTmHeaderSecHeaderFlag(pckt2));
  if (getTmHeaderSecHeaderFlag(pckt2) != 1) 
    return 0; 

  setTmHeaderAPID(pckt2, 0);
  DEBUGP_TSGS("getTmHeaderAPID(): %d \n", getTmHeaderAPID(pckt2));
  if (getTmHeaderAPID(pckt2) != 0) 
    return 0; 
  setTmHeaderAPID(pckt2, 2047);
  DEBUGP_TSGS("getTmHeaderAPID(): %d \n", getTmHeaderAPID(pckt2));
  if (getTmHeaderAPID(pckt2) != 2047) 
    return 0; 

  setTmHeaderSeqFlags(pckt2, 0);
  DEBUGP_TSGS("getTmHeaderSeqFlags(): %d \n", getTmHeaderSeqFlags(pckt2));
  if (getTmHeaderSeqFlags(pckt2) != 0) 
    return 0; 
  setTmHeaderSeqFlags(pckt2, 3);
  DEBUGP_TSGS("getTmHeaderSeqFlags(): %d \n", getTmHeaderSeqFlags(pckt2));
  if (getTmHeaderSeqFlags(pckt2) != 3) 
    return 0; 

  setTmHeaderSeqCount(pckt2, 0);
  DEBUGP_TSGS("getTmHeaderSeqCount(): %d \n", getTmHeaderSeqCount(pckt2));
  if (getTmHeaderSeqCount(pckt2) != 0) 
    return 0; 
  setTmHeaderSeqCount(pckt2, 16383);
  DEBUGP_TSGS("getTmHeaderSeqCount(): %d \n", getTmHeaderSeqCount(pckt2));
  if (getTmHeaderSeqCount(pckt2) != 16383) 
    return 0; 

  setTmHeaderPcktDataLen(pckt2, 0);
  DEBUGP_TSGS("getTmHeaderPcktDataLen(): %d \n", getTmHeaderPcktDataLen(pckt2));
  if (getTmHeaderPcktDataLen(pckt2) != 0) 
    return 0; 
  setTmHeaderPcktDataLen(pckt2, MAX_SHORT);
  DEBUGP_TSGS("getTmHeaderPcktDataLen(): %d \n", getTmHeaderPcktDataLen(pckt2));
  if (getTmHeaderPcktDataLen(pckt2) != MAX_SHORT) 
    return 0; 

  setTmHeaderPUSVersion(pckt2, 0);
  DEBUGP_TSGS("getTmHeaderPUSVersion(): %d \n", getTmHeaderPUSVersion(pckt2));
  if (getTmHeaderPUSVersion(pckt2) != 0) 
    return 0; 
  setTmHeaderPUSVersion(pckt2, 15);
  DEBUGP_TSGS("getTmHeaderPUSVersion(): %d \n", getTmHeaderPUSVersion(pckt2));
  if (getTmHeaderPUSVersion(pckt2) != 15) 
    return 0; 

  setTmHeaderSpaceTimeRefStatus(pckt2, 0);
  DEBUGP_TSGS("getTmHeaderSpaceTimeRefStatus(): %d \n", getTmHeaderSpaceTimeRefStatus(pckt2));
  if (getTmHeaderSpaceTimeRefStatus(pckt2) != 0) 
    return 0; 
  setTmHeaderSpaceTimeRefStatus(pckt2, 15);
  DEBUGP_TSGS("getTmHeaderSpaceTimeRefStatus(): %d \n", getTmHeaderSpaceTimeRefStatus(pckt2));
  if (getTmHeaderSpaceTimeRefStatus(pckt2) != 15) 
    return 0; 

  setTmHeaderServType(pckt2, 0);
  DEBUGP_TSGS("getTmHeaderServType(): %d \n", getTmHeaderServType(pckt2));
  if (getTmHeaderServType(pckt2) != 0) 
    return 0; 
  setTmHeaderServType(pckt2, MAX_CHAR);
  DEBUGP_TSGS("getTmHeaderServType(): %d \n", getTmHeaderServType(pckt2));
  if (getTmHeaderServType(pckt2) != MAX_CHAR) 
    return 0; 

  setTmHeaderServSubType(pckt2, 0);
  DEBUGP_TSGS("getTmHeaderServSubType(): %d \n", getTmHeaderServSubType(pckt2));
  if (getTmHeaderServSubType(pckt2) != 0) 
    return 0; 
  setTmHeaderServSubType(pckt2, MAX_CHAR);
  DEBUGP_TSGS("getTmHeaderServSubType(): %d \n", getTmHeaderServSubType(pckt2));
  if (getTmHeaderServSubType(pckt2) != MAX_CHAR) 
    return 0; 

  setTmHeaderDestId(pckt2, 0);
  DEBUGP_TSGS("getTmHeaderDestId(): %d \n", getTmHeaderDestId(pckt2));
  if (getTmHeaderDestId(pckt2) != 0) 
    return 0; 
  setTmHeaderDestId(pckt2, MAX_CHAR);
  DEBUGP_TSGS("getTmHeaderDestId(): %d \n", getTmHeaderDestId(pckt2));
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
  DEBUGP_TSGS("timi(1): %d \n", timi[0]);
  DEBUGP_TSGS("timi(2): %d \n", timi[1]);
  DEBUGP_TSGS("timi(3): %d \n", timi[2]);
  DEBUGP_TSGS("timi(4): %d \n", timi[3]);
  DEBUGP_TSGS("timi(5): %d \n", timi[4]);
  DEBUGP_TSGS("timi(6): %d \n", timi[5]);
  DEBUGP_TSGS("timi: %s \n", timi);
  DEBUGP_TSGS("tim: %s \n", tim);
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
  DEBUGP_TSGS("timi(1): %d \n", timi[0]);
  DEBUGP_TSGS("timi(2): %d \n", timi[1]);
  DEBUGP_TSGS("timi(3): %d \n", timi[2]);
  DEBUGP_TSGS("timi(4): %d \n", timi[3]);
  DEBUGP_TSGS("timi(5): %d \n", timi[4]);
  DEBUGP_TSGS("timi(6): %d \n", timi[5]);
  if (memcmp(tim, timi, sizeof(tim))) 
    return 0; 

  /*release packet and create a new one!*/
  CrFwPcktRelease(pckt2);

  /* Check if number of Allocated Packets = 0*/
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt3 = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  CrFwPcktSetCmdRepType(pckt3,crCmdType);
  DEBUGP_TSGS("CrFwPcktGetCmdRepType(pckt3) %d \n", CrFwPcktGetCmdRepType(pckt3));
  if (CrFwPcktGetCmdRepType(pckt3) != crCmdType) 
    return 0;

  DEBUGP_TSGS("CrFwPcktGetLength(pckt3) %d \n", CrFwPcktGetLength(pckt3));
  if (CrFwPcktGetLength(pckt3) != pcktsize) 
    return 0;

  /*functions not used!!*/
  CrFwPcktSetCmdRepId(pckt3,1);
  DEBUGP_TSGS("CrFwPcktGetCmdRepId(pckt3) %d \n", CrFwPcktGetCmdRepId(pckt3));
  if (CrFwPcktGetCmdRepId(pckt3) != 0) 
    return 0;

  CrFwPcktSetSeqCnt(pckt3,0);
  DEBUGP_TSGS("CrFwPcktGetSeqCnt(pckt3) %d \n", CrFwPcktGetSeqCnt(pckt3));
  if (CrFwPcktGetSeqCnt(pckt3) != 0) 
    return 0;

  CrFwPcktSetServType(pckt3,17);
  DEBUGP_TSGS("CrFwPcktGetServType(pckt3) %d \n", CrFwPcktGetServType(pckt3));
  if (CrFwPcktGetServType(pckt3) != 17) 
    return 0;

  CrFwPcktSetServSubType(pckt3,1);
  DEBUGP_TSGS("CrFwPcktGetServSubType(pckt3) %d \n", CrFwPcktGetServSubType(pckt3));
  if (CrFwPcktGetServSubType(pckt3) != 1) 
    return 0;

  CrFwPcktSetDiscriminant(pckt3,0);
  DEBUGP_TSGS("CrFwPcktGetDiscriminant(pckt3) %d \n", CrFwPcktGetDiscriminant(pckt3));
  if (CrFwPcktGetDiscriminant(pckt3) != 0) 
    return 0; 

  CrFwPcktSetSrc(pckt3,12);
  DEBUGP_TSGS("CrFwPcktGetSrc(pckt3) %d \n", CrFwPcktGetSrc(pckt3));
  if (CrFwPcktGetSrc(pckt3) != 12) 
    return 0;
  
  CrFwPcktSetAckLevel(pckt3,1,0,0,0);
  DEBUGP_TSGS("CrFwPcktIsAcceptAck(pckt3) %d \n", CrFwPcktIsAcceptAck(pckt3));
  if (CrFwPcktIsAcceptAck(pckt3) != 1) 
    return 0;
  if (CrFwPcktIsStartAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsProgressAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsTermAck(pckt3) != 0) 
    return 0;


  CrFwPcktSetAckLevel(pckt3,0,1,0,0);
  DEBUGP_TSGS("CrFwPcktIsStartAck(pckt3) %d \n", CrFwPcktIsStartAck(pckt3));
  if (CrFwPcktIsAcceptAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsStartAck(pckt3) != 1) 
    return 0;
  if (CrFwPcktIsProgressAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsTermAck(pckt3) != 0) 
    return 0;


  CrFwPcktSetAckLevel(pckt3,0,0,1,0);
  DEBUGP_TSGS("CrFwPcktIsProgressAck(pckt3) %d \n", CrFwPcktIsProgressAck(pckt3));
  if (CrFwPcktIsAcceptAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsStartAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsProgressAck(pckt3) != 1) 
    return 0;
  if (CrFwPcktIsTermAck(pckt3) != 0) 
    return 0;


  CrFwPcktSetAckLevel(pckt3,0,0,0,1);
  DEBUGP_TSGS("CrFwPcktIsTermAck(pckt3) %d \n", CrFwPcktIsTermAck(pckt3));
  if (CrFwPcktIsAcceptAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsStartAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsProgressAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsTermAck(pckt3) != 1) 
    return 0;

  CrFwPcktSetGroup(pckt3,2);
  DEBUGP_TSGS("CrFwPcktGetGroup(pckt3) %d \n", CrFwPcktGetGroup(pckt3));
  if (CrFwPcktGetGroup(pckt3) != 2) 
    return 0;

  DEBUGP_TSGS("CrFwPcktGetParStart(pckt3) %p \n", CrFwPcktGetParStart(pckt3));
  DEBUGP_TSGS("CrFwPcktGetParLength(pckt3) %d \n", CrFwPcktGetParLength(pckt3));

  /*release packet and create a new one!*/
  CrFwPcktRelease(pckt3);

  /* Check if number of Allocated Packets = 0*/
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt4 = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  CrFwPcktSetCmdRepType(pckt4,crRepType);
  DEBUGP_TSGS("CrFwPcktGetCmdRepType(pckt4) %d \n", CrFwPcktGetCmdRepType(pckt4));
  if (CrFwPcktGetCmdRepType(pckt4) != crRepType) 
    return 0;

  DEBUGP_TSGS("CrFwPcktGetLength(pckt4) %d \n", CrFwPcktGetLength(pckt4));
  if (CrFwPcktGetLength(pckt4) != pcktsize) 
    return 0;

  /*functions not used!!*/
  CrFwPcktSetCmdRepId(pckt4,1);
  DEBUGP_TSGS("CrFwPcktGetCmdRepId(pckt4) %d \n", CrFwPcktGetCmdRepId(pckt4));
  if (CrFwPcktGetCmdRepId(pckt4) != 0) 
    return 0;

  CrFwPcktSetSeqCnt(pckt4,0);
  DEBUGP_TSGS("CrFwPcktGetSeqCnt(pckt4) %d \n", CrFwPcktGetSeqCnt(pckt4));
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
  DEBUGP_TSGS("timi(1): %d \n", timstpi.t[0]);
  DEBUGP_TSGS("timi(2): %d \n", timstpi.t[1]);
  DEBUGP_TSGS("timi(3): %d \n", timstpi.t[2]);
  DEBUGP_TSGS("timi(4): %d \n", timstpi.t[3]);
  DEBUGP_TSGS("timi(5): %d \n", timstpi.t[4]);
  DEBUGP_TSGS("timi(6): %d \n", timstpi.t[5]);

  if (memcmp(&timstp, &timstpi, sizeof(timstp))) 
    return 0; 

  CrFwPcktSetServType(pckt4,17);
  DEBUGP_TSGS("CrFwPcktGetServType(pckt4) %d \n", CrFwPcktGetServType(pckt4));
  if (CrFwPcktGetServType(pckt4) != 17) 
    return 0;

  CrFwPcktSetServSubType(pckt4,2);
  DEBUGP_TSGS("CrFwPcktGetServSubType(pckt4) %d \n", CrFwPcktGetServSubType(pckt4));
  if (CrFwPcktGetServSubType(pckt4) != 2) 
    return 0;

  CrFwPcktSetDiscriminant(pckt4,44);
  DEBUGP_TSGS("CrFwPcktGetDiscriminant(pckt4) %d \n", CrFwPcktGetDiscriminant(pckt4));
  if (CrFwPcktGetDiscriminant(pckt4) != 0) 
    return 0; 

  CrFwPcktSetDest(pckt4,13);
  DEBUGP_TSGS("CrFwPcktGetDest(pckt4) %d \n", CrFwPcktGetDest(pckt4));
  if (CrFwPcktGetDest(pckt4) != 13) 
    return 0;

  CrFwPcktSetGroup(pckt4,2);
  DEBUGP_TSGS("CrFwPcktGetGroup(pckt4) %d \n", CrFwPcktGetGroup(pckt4));
  if (CrFwPcktGetGroup(pckt4) != 2) 
    return 0;

  DEBUGP_TSGS("CrFwPcktGetParStart(pckt4) %p \n", CrFwPcktGetParStart(pckt4));
  DEBUGP_TSGS("CrFwPcktGetParLength(pckt4) %d \n", CrFwPcktGetParLength(pckt4));

/*TBD remove if it works*/
  DEBUGP_TSGS("pcktsize: %d \n", pcktsize);
  DEBUGP_TSGS("CrFwPcktGetLength(pckt4) %d \n", CrFwPcktGetLength(pckt4));
  DEBUGP_TSGS("tmheader: %lu \n", sizeof(TmHeader_t));
  pstart = CrFwPcktGetParStart(pckt4);
  DEBUGP_TSGS("pcktstart: %i \n", *pstart);
  DEBUGP_TSGS("pcktsize: %d \n", pcktsize);
  DEBUGP_TSGS("pcktsize: %d \n", pcktsize);
  CRFW_UNUSED(pstart);
  /*release packet and create a new one!*/
  CrFwPcktRelease(pckt4);

  /* Check if number of Allocated Packets = 0*/
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
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
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 17.1 packet*/
  DEBUGP_TSGS("Check 17.1 packet \n");
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
  DEBUGP_TSGS("Check 17.2 packet \n");
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
  DEBUGP_TSGS("Check 17.3 packet \n");
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
  DEBUGP_TSGS("Check 17.4 packet \n");
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
  DEBUGP_TSGS("Check 1.1 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 1);
  CrFwPcktSetServSubType(pckt, 1);
  CrFwPcktSetDiscriminant(pckt, 0);
  setVerSuccessAccRepTcPacketId(pckt, 0);
  setVerSuccessAccRepTcPacketSeqCtrl(pckt, 0);  

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 1)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 1)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerSuccessAccRepTcPacketId(pckt) != 0)
    return 0;
  if (getVerSuccessAccRepTcPacketSeqCtrl(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setVerSuccessAccRepTcPacketId(pckt, MAX_SHORT);
  setVerSuccessAccRepTcPacketSeqCtrl(pckt, MAX_SHORT);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerSuccessAccRepTcPacketId(pckt) != MAX_SHORT)
    return 0;
  if (getVerSuccessAccRepTcPacketSeqCtrl(pckt) != MAX_SHORT)
    return 0;

  /* Check 1.2 packet*/
  DEBUGP_TSGS("Check 1.2 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 1);
  CrFwPcktSetServSubType(pckt, 2);
  CrFwPcktSetDiscriminant(pckt, 0);
  setVerFailedAccRepTcFailureCode(pckt, 0);
  setVerFailedAccRepTcPacketId(pckt, 0);
  setVerFailedAccRepTcPacketSeqCtrl(pckt, 0);  
  setVerFailedAccRepTcType(pckt, 0);
  setVerFailedAccRepTcSubtype(pckt, 0);
  setVerFailedAccRepTcDisc(pckt, 0);   

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 1)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 2)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerFailedAccRepTcFailureCode(pckt) != 0)
    return 0;
  if (getVerFailedAccRepTcPacketId(pckt) != 0)
    return 0;
  if (getVerFailedAccRepTcPacketSeqCtrl(pckt) != 0)
    return 0;
  if (getVerFailedAccRepTcType(pckt) != 0)
    return 0;
  if (getVerFailedAccRepTcSubtype(pckt) != 0)
    return 0;
  if (getVerFailedAccRepTcDisc(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setVerFailedAccRepTcFailureCode(pckt, MAX_SHORT);
  setVerFailedAccRepTcPacketId(pckt, MAX_SHORT);
  setVerFailedAccRepTcPacketSeqCtrl(pckt, MAX_SHORT);
  setVerFailedAccRepTcType(pckt, MAX_CHAR);
  setVerFailedAccRepTcSubtype(pckt, MAX_CHAR);  
  setVerFailedAccRepTcDisc(pckt, MAX_CHAR); 
  if (CrFwPcktGetDiscriminant(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedAccRepTcFailureCode(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedAccRepTcPacketId(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedAccRepTcPacketSeqCtrl(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedAccRepTcType(pckt) != MAX_CHAR)
    return 0;
  if (getVerFailedAccRepTcSubtype(pckt) != MAX_CHAR)
    return 0;
  if (getVerFailedAccRepTcDisc(pckt) != MAX_CHAR)
    return 0;

  /* Check 1.3 packet*/
  DEBUGP_TSGS("Check 1.3 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 1);
  CrFwPcktSetServSubType(pckt, 3);
  CrFwPcktSetDiscriminant(pckt, 0);
  setVerSuccessStartRepTcPacketId(pckt, 0);
  setVerSuccessStartRepTcPacketSeqCtrl(pckt, 0);  

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 1)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 3)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerSuccessStartRepTcPacketId(pckt) != 0)
    return 0;
  if (getVerSuccessStartRepTcPacketSeqCtrl(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setVerSuccessStartRepTcPacketId(pckt, MAX_SHORT);
  setVerSuccessStartRepTcPacketSeqCtrl(pckt, MAX_SHORT);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerSuccessStartRepTcPacketId(pckt) != MAX_SHORT)
    return 0;
  if (getVerSuccessStartRepTcPacketSeqCtrl(pckt) != MAX_SHORT)
    return 0;

  /* Check 1.4 packet*/
  DEBUGP_TSGS("Check 1.4 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 1);
  CrFwPcktSetServSubType(pckt, 4);
  CrFwPcktSetDiscriminant(pckt, 0);
  setVerFailedStartRepTcFailureCode(pckt, 0);
  setVerFailedStartRepTcPacketId(pckt, 0);
  setVerFailedStartRepTcPacketSeqCtrl(pckt, 0);  
  setVerFailedStartRepTcType(pckt, 0);
  setVerFailedStartRepTcSubtype(pckt, 0);
  setVerFailedStartRepTcDisc(pckt, 0);   

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 1)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 4)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerFailedStartRepTcFailureCode(pckt) != 0)
    return 0;
  if (getVerFailedStartRepTcPacketId(pckt) != 0)
    return 0;
  if (getVerFailedStartRepTcPacketSeqCtrl(pckt) != 0)
    return 0;
  if (getVerFailedStartRepTcType(pckt) != 0)
    return 0;
  if (getVerFailedStartRepTcSubtype(pckt) != 0)
    return 0;
  if (getVerFailedStartRepTcDisc(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setVerFailedStartRepTcFailureCode(pckt, MAX_SHORT);
  setVerFailedStartRepTcPacketId(pckt, MAX_SHORT);
  setVerFailedStartRepTcPacketSeqCtrl(pckt, MAX_SHORT);
  setVerFailedStartRepTcType(pckt, MAX_CHAR);
  setVerFailedStartRepTcSubtype(pckt, MAX_CHAR);  
  setVerFailedStartRepTcDisc(pckt, MAX_CHAR); 
  if (CrFwPcktGetDiscriminant(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedStartRepTcFailureCode(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedStartRepTcPacketId(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedStartRepTcPacketSeqCtrl(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedStartRepTcType(pckt) != MAX_CHAR)
    return 0;
  if (getVerFailedStartRepTcSubtype(pckt) != MAX_CHAR)
    return 0;
  if (getVerFailedStartRepTcDisc(pckt) != MAX_CHAR)
    return 0;

  /* Check 1.5 packet*/
  DEBUGP_TSGS("Check 1.5 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 1);
  CrFwPcktSetServSubType(pckt, 5);
  CrFwPcktSetDiscriminant(pckt, 0);
  setVerSuccessPrgrRepTcPacketId(pckt, 0);
  setVerSuccessPrgrRepTcPacketSeqCtrl(pckt, 0);  
  setVerSuccessPrgrRepStepId(pckt, 0);    

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 1)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 5)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerSuccessPrgrRepTcPacketId(pckt) != 0)
    return 0;
  if (getVerSuccessPrgrRepTcPacketSeqCtrl(pckt) != 0)
    return 0;
  if (getVerSuccessPrgrRepStepId(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setVerSuccessPrgrRepTcPacketId(pckt, MAX_SHORT);
  setVerSuccessPrgrRepTcPacketSeqCtrl(pckt, MAX_SHORT);
  setVerSuccessPrgrRepStepId(pckt, MAX_INT);  
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerSuccessPrgrRepTcPacketId(pckt) != MAX_SHORT)
    return 0;
  if (getVerSuccessPrgrRepTcPacketSeqCtrl(pckt) != MAX_SHORT)
    return 0;
  if (getVerSuccessPrgrRepStepId(pckt) != MAX_INT)
    return 0;

  /* Check 1.6 packet*/
  DEBUGP_TSGS("Check 1.6 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 1);
  CrFwPcktSetServSubType(pckt, 6);
  CrFwPcktSetDiscriminant(pckt, 0);
  setVerFailedPrgrRepTcFailureCode(pckt, 0);
  setVerFailedPrgrRepTcPacketId(pckt, 0);
  setVerFailedPrgrRepTcPacketSeqCtrl(pckt, 0);
  setVerFailedPrgrRepStepId(pckt, 0);  
  setVerFailedPrgrRepTcType(pckt, 0);
  setVerFailedPrgrRepTcSubtype(pckt, 0);
  setVerFailedPrgrRepTcDisc(pckt, 0);   

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 1)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 6)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerFailedPrgrRepTcFailureCode(pckt) != 0)
    return 0;
  if (getVerFailedPrgrRepTcPacketId(pckt) != 0)
    return 0;
  if (getVerFailedPrgrRepTcPacketSeqCtrl(pckt) != 0)
    return 0;
  if (getVerFailedPrgrRepStepId(pckt) != 0)
    return 0;
  if (getVerFailedPrgrRepTcType(pckt) != 0)
    return 0;
  if (getVerFailedPrgrRepTcSubtype(pckt) != 0)
    return 0;
  if (getVerFailedPrgrRepTcDisc(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setVerFailedPrgrRepTcFailureCode(pckt, MAX_SHORT);
  setVerFailedPrgrRepTcPacketId(pckt, MAX_SHORT);
  setVerFailedPrgrRepTcPacketSeqCtrl(pckt, MAX_SHORT);
  setVerFailedPrgrRepStepId(pckt, MAX_INT);
  setVerFailedPrgrRepTcType(pckt, MAX_CHAR);
  setVerFailedPrgrRepTcSubtype(pckt, MAX_CHAR);  
  setVerFailedPrgrRepTcDisc(pckt, MAX_CHAR); 
  if (CrFwPcktGetDiscriminant(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedPrgrRepTcFailureCode(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedPrgrRepTcPacketId(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedPrgrRepTcPacketSeqCtrl(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedPrgrRepStepId(pckt) != MAX_INT)
    return 0;;

  if (getVerFailedPrgrRepTcType(pckt) != MAX_CHAR)
    return 0;
  if (getVerFailedPrgrRepTcSubtype(pckt) != MAX_CHAR)
    return 0;
  if (getVerFailedPrgrRepTcDisc(pckt) != MAX_CHAR)
    return 0;

  /* Check 1.7 packet*/
  DEBUGP_TSGS("Check 1.7 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 1);
  CrFwPcktSetServSubType(pckt, 7);
  CrFwPcktSetDiscriminant(pckt, 0);
  setVerSuccessTermRepTcPacketId(pckt, 0);
  setVerSuccessTermRepTcPacketSeqCtrl(pckt, 0);   

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 1)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 7)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerSuccessTermRepTcPacketId(pckt) != 0)
    return 0;
  if (getVerSuccessTermRepTcPacketSeqCtrl(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setVerSuccessTermRepTcPacketId(pckt, MAX_SHORT);
  setVerSuccessTermRepTcPacketSeqCtrl(pckt, MAX_SHORT);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerSuccessTermRepTcPacketId(pckt) != MAX_SHORT)
    return 0;
  if (getVerSuccessTermRepTcPacketSeqCtrl(pckt) != MAX_SHORT)
    return 0;

  /* Check 1.8 packet*/
  DEBUGP_TSGS("Check 1.8 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 1);
  CrFwPcktSetServSubType(pckt, 8);
  CrFwPcktSetDiscriminant(pckt, 0);
  setVerFailedTermRepTcFailureCode(pckt, 0);
  setVerFailedTermRepTcPacketId(pckt, 0);
  setVerFailedTermRepTcPacketSeqCtrl(pckt, 0); 
  setVerFailedTermRepTcType(pckt, 0);
  setVerFailedTermRepTcSubtype(pckt, 0);
  setVerFailedTermRepTcDisc(pckt, 0);   

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 1)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 8)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerFailedTermRepTcFailureCode(pckt) != 0)
    return 0;
  if (getVerFailedTermRepTcPacketId(pckt) != 0)
    return 0;
  if (getVerFailedTermRepTcPacketSeqCtrl(pckt) != 0)
    return 0;
  if (getVerFailedTermRepTcType(pckt) != 0)
    return 0;
  if (getVerFailedTermRepTcSubtype(pckt) != 0)
    return 0;
  if (getVerFailedTermRepTcDisc(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setVerFailedTermRepTcFailureCode(pckt, MAX_SHORT);
  setVerFailedTermRepTcPacketId(pckt, MAX_SHORT);
  setVerFailedTermRepTcPacketSeqCtrl(pckt, MAX_SHORT);
  setVerFailedTermRepTcType(pckt, MAX_CHAR);
  setVerFailedTermRepTcSubtype(pckt, MAX_CHAR);  
  setVerFailedTermRepTcDisc(pckt, MAX_CHAR); 
  if (CrFwPcktGetDiscriminant(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedTermRepTcFailureCode(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedTermRepTcPacketId(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedTermRepTcPacketSeqCtrl(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedTermRepTcType(pckt) != MAX_CHAR)
    return 0;
  if (getVerFailedTermRepTcSubtype(pckt) != MAX_CHAR)
    return 0;
  if (getVerFailedTermRepTcDisc(pckt) != MAX_CHAR)
    return 0;

  /* Check 1.10 packet*/
  DEBUGP_TSGS("Check 1.10 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 1);
  CrFwPcktSetServSubType(pckt, 10);
  CrFwPcktSetDiscriminant(pckt, 0);
  setVerFailedRoutingRepTcFailureCode(pckt, 0);
  setVerFailedRoutingRepTcPacketId(pckt, 0);
  setVerFailedRoutingRepTcPacketSeqCtrl(pckt, 0); 
  setVerFailedRoutingRepTcType(pckt, 0);
  setVerFailedRoutingRepTcSubtype(pckt, 0);
  setVerFailedRoutingRepTcDisc(pckt, 0);
  setVerFailedRoutingRepinvDest(pckt, 0);   

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 1)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 10)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getVerFailedRoutingRepTcFailureCode(pckt) != 0)
    return 0;
  if (getVerFailedRoutingRepTcPacketId(pckt) != 0)
    return 0;
  if (getVerFailedRoutingRepTcPacketSeqCtrl(pckt) != 0)
    return 0;
  if (getVerFailedRoutingRepTcType(pckt) != 0)
    return 0;
  if (getVerFailedRoutingRepTcSubtype(pckt) != 0)
    return 0;
  if (getVerFailedRoutingRepTcDisc(pckt) != 0)
    return 0;
  if (getVerFailedRoutingRepinvDest(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setVerFailedRoutingRepTcFailureCode(pckt, MAX_SHORT);
  setVerFailedRoutingRepTcPacketId(pckt, MAX_SHORT);
  setVerFailedRoutingRepTcPacketSeqCtrl(pckt, MAX_SHORT);
  setVerFailedRoutingRepTcType(pckt, MAX_CHAR);
  setVerFailedRoutingRepTcSubtype(pckt, MAX_CHAR);  
  setVerFailedRoutingRepTcDisc(pckt, MAX_CHAR); 
  setVerFailedRoutingRepinvDest(pckt, MAX_SHORT);
  if (CrFwPcktGetDiscriminant(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedRoutingRepTcFailureCode(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedRoutingRepTcPacketId(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedRoutingRepTcPacketSeqCtrl(pckt) != MAX_SHORT)
    return 0;
  if (getVerFailedRoutingRepTcType(pckt) != MAX_CHAR)
    return 0;
  if (getVerFailedRoutingRepTcSubtype(pckt) != MAX_CHAR)
    return 0;
  if (getVerFailedRoutingRepTcDisc(pckt) != MAX_CHAR)
    return 0;
  if (getVerFailedRoutingRepinvDest(pckt) != MAX_SHORT)
    return 0;

/* Service 3: Housekeeping Service */
  /*It is easier to test each getter or setter not the whole packet*/

  clearPacket(pckt, pcktsize);
  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(pcktsize);

  /* Check 3,1 packet*/
  DEBUGP_TSGS("Check 3,1 or 3,2 packet \n");

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

  clearPacket(pckt, pcktsize);
  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(pcktsize);

  /* Check 3,3 packet*/
  DEBUGP_TSGS("Check 3,3 or 3,4 packet \n");

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

  clearPacket(pckt, pcktsize);
  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(pcktsize);

  /* Check 3,5 packet*/
  DEBUGP_TSGS("Check 3,5 or 3,7 packet \n");

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

  clearPacket(pckt, pcktsize);
  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(pcktsize);


  /* Check 3,6 packet*/
  DEBUGP_TSGS("Check 3,6 or 3,8 packet \n");

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

  clearPacket(pckt, pcktsize);
  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(pcktsize);


  /* Check 3,9 packet*/
  DEBUGP_TSGS("Check 3,9 or 3,11 packet \n");

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

  clearPacket(pckt, pcktsize);
  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(pcktsize);


/* Check 3,10 packet*/
  DEBUGP_TSGS("Check 3,10 or 3,12 packet \n");

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

  clearPacket(pckt, pcktsize);
  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(pcktsize);

  /* Check 3,25 packet*/
  DEBUGP_TSGS("Check 3,25 or 3,26 packet \n");

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

  /*TODO ein Packet aufbauen und testen*/
  
  clearPacket(pckt, pcktsize);
  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(pcktsize);

  /* Check 3.27 packet*/
  DEBUGP_TSGS("Check 3,27 or 3,28 packet \n");

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
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 5,1 packet*/
  DEBUGP_TSGS("Check 5,1 packet \n");
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
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 5,2 packet*/
  DEBUGP_TSGS("Check 5,2 packet \n");
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
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 5,3 packet*/
  DEBUGP_TSGS("Check 5,3 packet \n");
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
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 5,4 packet*/
  DEBUGP_TSGS("Check 5,4 packet \n");
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
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 5,5 packet*/
  DEBUGP_TSGS("Check 5,5 packet \n");
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
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 5,6 packet*/
  DEBUGP_TSGS("Check 5,6 packet \n");
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
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 5,8 packet*/
  DEBUGP_TSGS("Check 5,8 packet \n");
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
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 13,1 packet*/
  DEBUGP_TSGS("Check 13,1 packet \n");
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
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 13,2 packet*/
  DEBUGP_TSGS("Check 13,2 packet \n");
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
/*
  for (i=0;i<=parts;i++)
  {
    setLptDownInterRepPart(pckt, MIN_VAL, i);
    if (getLptDownInterRepPart(pckt, i) != MIN_VAL)
      return 0;
    setLptDownInterRepPart(pckt, MAX_SHORT, i);
    if (getLptDownInterRepPart(pckt, i) != MAX_SHORT)
      return 0;    
  }
*/
  CrFwPcktRelease(pckt);

  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 13,3 packet*/
  DEBUGP_TSGS("Check 13,3 packet \n");
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
/*
  for (i=0;i<=parts;i++)
  {
    setLptDownLastRepPart(pckt, MIN_VAL, i);
    if (getLptDownLastRepPart(pckt, i) != MIN_VAL)
      return 0;
    setLptDownLastRepPart(pckt, MAX_SHORT, i);
    if (getLptDownLastRepPart(pckt, i) != MAX_SHORT)
      return 0;    
  }
*/
  CrFwPcktRelease(pckt);

  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Check if number of Allocated Packets = 0*/
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 13,9 packet*/
  DEBUGP_TSGS("Check 13,9 packet \n");
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
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 13,10 packet*/
  DEBUGP_TSGS("Check 13,10 packet \n");
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
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 13,11 packet*/
  DEBUGP_TSGS("Check 13,11 packet \n");
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
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 13,16 packet*/
  DEBUGP_TSGS("Check 13,16 packet \n");
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
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 13,129 packet*/
  DEBUGP_TSGS("Check 13,129 packet \n");
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
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  DEBUGP_TSGS("Allocating a Packet \n");
  pckt = CrFwPcktMake(pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check 13,130 packet*/
  DEBUGP_TSGS("Check 13,130 packet \n");
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
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  return 1;
}