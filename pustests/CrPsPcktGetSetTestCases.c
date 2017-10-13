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
#include <Services/General/CrPsPktHk.h>
#include <Services/General/CrPsPktEvt.h>
#include <CrPsDebug.h>


#define MAX_CHAR 255
#define MAX_SHORT 65535
#define MAX_INT 4294967295
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
  debugPacket(pckt, pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /*test all TC header Getter and Setter*/
  setTcHeaderPcktVersionNmb(pckt, 0);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderPcktVersionNmb(): %d \n", getTcHeaderPcktVersionNmb(pckt));
  if (getTcHeaderPcktVersionNmb(pckt) != 0) 
    return 0; 

  setTcHeaderPcktVersionNmb(pckt, 7);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderPcktVersionNmb(): %d \n", getTcHeaderPcktVersionNmb(pckt));
  if (getTcHeaderPcktVersionNmb(pckt) != 7) 
    return 0;

  setTcHeaderPcktType(pckt, 0);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderPcktType(): %d \n", getTcHeaderPcktType(pckt));
  if (getTcHeaderPcktType(pckt) != 0) 
    return 0; 
  setTcHeaderPcktType(pckt, 1);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderPcktType(): %d \n", getTcHeaderPcktType(pckt));
  if (getTcHeaderPcktType(pckt) != 1) 
    return 0; 

  setTcHeaderSecHeaderFlag(pckt, 0);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderSecHeaderFlag(): %d \n", getTcHeaderSecHeaderFlag(pckt));
  if (getTcHeaderSecHeaderFlag(pckt) != 0) 
    return 0; 
  setTcHeaderSecHeaderFlag(pckt, 1);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderSecHeaderFlag(): %d \n", getTcHeaderSecHeaderFlag(pckt));
  if (getTcHeaderSecHeaderFlag(pckt) != 1) 
    return 0; 

  setTcHeaderAPID(pckt, 0);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderAPID(): %d \n", getTcHeaderAPID(pckt));
  if (getTcHeaderAPID(pckt) != 0) 
    return 0; 
  setTcHeaderAPID(pckt, 2047);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderAPID(): %d \n", getTcHeaderAPID(pckt));
  if (getTcHeaderAPID(pckt) != 2047) 
    return 0; 

  setTcHeaderSeqFlags(pckt, 0);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderSeqFlags(): %d \n", getTcHeaderSeqFlags(pckt));
  if (getTcHeaderSeqFlags(pckt) != 0) 
    return 0; 
  setTcHeaderSeqFlags(pckt, 3);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderSeqFlags(): %d \n", getTcHeaderSeqFlags(pckt));
  if (getTcHeaderSeqFlags(pckt) != 3) 
    return 0; 

  setTcHeaderSeqCount(pckt, 0);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderSeqCount(): %d \n", getTcHeaderSeqCount(pckt));
  if (getTcHeaderSeqCount(pckt) != 0) 
    return 0; 
  setTcHeaderSeqCount(pckt, 16383);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderSeqCount(): %d \n", getTcHeaderSeqCount(pckt));
  if (getTcHeaderSeqCount(pckt) != 16383) 
    return 0; 

  setTcHeaderPcktDataLen(pckt, 0);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderPcktDataLen(): %d \n", getTcHeaderPcktDataLen(pckt));
  if (getTcHeaderPcktDataLen(pckt) != 0) 
    return 0; 
  setTcHeaderPcktDataLen(pckt, MAX_SHORT);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderPcktDataLen(): %d \n", getTcHeaderPcktDataLen(pckt));
  if (getTcHeaderPcktDataLen(pckt) != MAX_SHORT) 
    return 0; 

  setTcHeaderPUSVersion(pckt, 0);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderPUSVersion(): %d \n", getTcHeaderPUSVersion(pckt));
  if (getTcHeaderPUSVersion(pckt) != 0) 
    return 0; 
  setTcHeaderPUSVersion(pckt, 15);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderPUSVersion(): %d \n", getTcHeaderPUSVersion(pckt));
  if (getTcHeaderPUSVersion(pckt) != 15) 
    return 0; 

  setTcHeaderAckAccFlag(pckt, 0);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderAckAccFlag(): %d \n", getTcHeaderAckAccFlag(pckt));
  if (getTcHeaderAckAccFlag(pckt) != 0) 
    return 0; 
  setTcHeaderAckAccFlag(pckt, 1);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderAckAccFlag(): %d \n", getTcHeaderAckAccFlag(pckt));
  if (getTcHeaderAckAccFlag(pckt) != 1) 
    return 0; 

  setTcHeaderAckStartFlag(pckt, 0);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderAckStartFlag(): %d \n", getTcHeaderAckStartFlag(pckt));
  if (getTcHeaderAckStartFlag(pckt) != 0) 
    return 0; 
  setTcHeaderAckStartFlag(pckt, 1);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderAckStartFlag(): %d \n", getTcHeaderAckStartFlag(pckt));
  if (getTcHeaderAckStartFlag(pckt) != 1) 
    return 0; 

  setTcHeaderAckProgFlag(pckt, 0);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderAckProgFlag(): %d \n", getTcHeaderAckProgFlag(pckt));
  if (getTcHeaderAckProgFlag(pckt) != 0) 
    return 0; 
  setTcHeaderAckProgFlag(pckt, 1);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderAckProgFlag(): %d \n", getTcHeaderAckProgFlag(pckt));
  if (getTcHeaderAckProgFlag(pckt) != 1) 
    return 0; 

  setTcHeaderAckTermFlag(pckt, 0);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderAckTermFlag(): %d \n", getTcHeaderAckTermFlag(pckt));
  if (getTcHeaderAckTermFlag(pckt) != 0) 
    return 0; 
  setTcHeaderAckTermFlag(pckt, 1);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderAckTermFlag(): %d \n", getTcHeaderAckTermFlag(pckt));
  if (getTcHeaderAckTermFlag(pckt) != 1) 
    return 0; 

  setTcHeaderServType(pckt, 0);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderServType(): %d \n", getTcHeaderServType(pckt));
  if (getTcHeaderServType(pckt) != 0) 
    return 0; 
  setTcHeaderServType(pckt, MAX_CHAR);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderServType(): %d \n", getTcHeaderServType(pckt));
  if (getTcHeaderServType(pckt) != MAX_CHAR) 
    return 0; 

  setTcHeaderServSubType(pckt, 0);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderServSubType(): %d \n", getTcHeaderServSubType(pckt));
  if (getTcHeaderServSubType(pckt) != 0) 
    return 0; 
  setTcHeaderServSubType(pckt, MAX_CHAR);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderServSubType(): %d \n", getTcHeaderServSubType(pckt));
  if (getTcHeaderServSubType(pckt) != MAX_CHAR) 
    return 0; 

  setTcHeaderSrcId(pckt, 0);
  debugPacket(pckt, pcktsize);
  DEBUGP_TSGS("getTcHeaderSrcId(): %d \n", getTcHeaderSrcId(pckt));
  if (getTcHeaderSrcId(pckt) != 0) 
    return 0; 

  setTcHeaderSrcId(pckt, MAX_CHAR);
  debugPacket(pckt, pcktsize);
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
  debugPacket(pckt2, pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /*test all TM header Getter and Setter*/
  setTmHeaderPcktVersionNmb(pckt2, 0);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderPcktVersionNmb(): %d \n", getTmHeaderPcktVersionNmb(pckt2));
  if (getTmHeaderPcktVersionNmb(pckt2) != 0) 
    return 0; 
  setTmHeaderPcktVersionNmb(pckt, 7);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderPcktVersionNmb(): %d \n", getTmHeaderPcktVersionNmb(pckt2));
  if (getTmHeaderPcktVersionNmb(pckt2) != 7) 
    return 0; 

  setTmHeaderPcktType(pckt2, 0);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderPcktType(): %d \n", getTmHeaderPcktType(pckt2));
  if (getTmHeaderPcktType(pckt2) != 0) 
    return 0; 
  setTmHeaderPcktType(pckt2, 1);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderPcktType(): %d \n", getTmHeaderPcktType(pckt2));
  if (getTmHeaderPcktType(pckt2) != 1) 
    return 0; 

  setTmHeaderSecHeaderFlag(pckt2, 0);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderSecHeaderFlag(): %d \n", getTmHeaderSecHeaderFlag(pckt2));
  if (getTmHeaderSecHeaderFlag(pckt2) != 0) 
    return 0; 
  setTmHeaderSecHeaderFlag(pckt2, 1);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderSecHeaderFlag(): %d \n", getTmHeaderSecHeaderFlag(pckt2));
  if (getTmHeaderSecHeaderFlag(pckt2) != 1) 
    return 0; 

  setTmHeaderAPID(pckt2, 0);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderAPID(): %d \n", getTmHeaderAPID(pckt2));
  if (getTmHeaderAPID(pckt2) != 0) 
    return 0; 
  setTmHeaderAPID(pckt2, 2047);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderAPID(): %d \n", getTmHeaderAPID(pckt2));
  if (getTmHeaderAPID(pckt2) != 2047) 
    return 0; 

  setTmHeaderSeqFlags(pckt2, 0);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderSeqFlags(): %d \n", getTmHeaderSeqFlags(pckt2));
  if (getTmHeaderSeqFlags(pckt2) != 0) 
    return 0; 
  setTmHeaderSeqFlags(pckt2, 3);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderSeqFlags(): %d \n", getTmHeaderSeqFlags(pckt2));
  if (getTmHeaderSeqFlags(pckt2) != 3) 
    return 0; 

  setTmHeaderSeqCount(pckt2, 0);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderSeqCount(): %d \n", getTmHeaderSeqCount(pckt2));
  if (getTmHeaderSeqCount(pckt2) != 0) 
    return 0; 
  setTmHeaderSeqCount(pckt2, 16383);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderSeqCount(): %d \n", getTmHeaderSeqCount(pckt2));
  if (getTmHeaderSeqCount(pckt2) != 16383) 
    return 0; 

  setTmHeaderPcktDataLen(pckt2, 0);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderPcktDataLen(): %d \n", getTmHeaderPcktDataLen(pckt2));
  if (getTmHeaderPcktDataLen(pckt2) != 0) 
    return 0; 
  setTmHeaderPcktDataLen(pckt2, MAX_SHORT);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderPcktDataLen(): %d \n", getTmHeaderPcktDataLen(pckt2));
  if (getTmHeaderPcktDataLen(pckt2) != MAX_SHORT) 
    return 0; 

  setTmHeaderPUSVersion(pckt2, 0);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderPUSVersion(): %d \n", getTmHeaderPUSVersion(pckt2));
  if (getTmHeaderPUSVersion(pckt2) != 0) 
    return 0; 
  setTmHeaderPUSVersion(pckt2, 15);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderPUSVersion(): %d \n", getTmHeaderPUSVersion(pckt2));
  if (getTmHeaderPUSVersion(pckt2) != 15) 
    return 0; 

  setTmHeaderSpaceTimeRefStatus(pckt2, 0);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderSpaceTimeRefStatus(): %d \n", getTmHeaderSpaceTimeRefStatus(pckt2));
  if (getTmHeaderSpaceTimeRefStatus(pckt2) != 0) 
    return 0; 
  setTmHeaderSpaceTimeRefStatus(pckt2, 15);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderSpaceTimeRefStatus(): %d \n", getTmHeaderSpaceTimeRefStatus(pckt2));
  if (getTmHeaderSpaceTimeRefStatus(pckt2) != 15) 
    return 0; 

  setTmHeaderServType(pckt2, 0);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderServType(): %d \n", getTmHeaderServType(pckt2));
  if (getTmHeaderServType(pckt2) != 0) 
    return 0; 
  setTmHeaderServType(pckt2, MAX_CHAR);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderServType(): %d \n", getTmHeaderServType(pckt2));
  if (getTmHeaderServType(pckt2) != MAX_CHAR) 
    return 0; 

  setTmHeaderServSubType(pckt2, 0);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderServSubType(): %d \n", getTmHeaderServSubType(pckt2));
  if (getTmHeaderServSubType(pckt2) != 0) 
    return 0; 
  setTmHeaderServSubType(pckt2, MAX_CHAR);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderServSubType(): %d \n", getTmHeaderServSubType(pckt2));
  if (getTmHeaderServSubType(pckt2) != MAX_CHAR) 
    return 0; 

  setTmHeaderDestId(pckt2, 0);
  debugPacket(pckt2, pcktsize);
  DEBUGP_TSGS("getTmHeaderDestId(): %d \n", getTmHeaderDestId(pckt2));
  if (getTmHeaderDestId(pckt2) != 0) 
    return 0; 
  setTmHeaderDestId(pckt2, MAX_CHAR);
  debugPacket(pckt2, pcktsize);
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
  debugPacket(pckt2, pcktsize);
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
  debugPacket(pckt2, pcktsize);
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
  debugPacket(pckt3, pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  CrFwPcktSetCmdRepType(pckt3,crCmdType);
  debugPacket(pckt3, pcktsize);
  DEBUGP_TSGS("CrFwPcktGetCmdRepType(pckt3) %d \n", CrFwPcktGetCmdRepType(pckt3));
  if (CrFwPcktGetCmdRepType(pckt3) != crCmdType) 
    return 0;

  DEBUGP_TSGS("CrFwPcktGetLength(pckt3) %d \n", CrFwPcktGetLength(pckt3));
  if (CrFwPcktGetLength(pckt3) != pcktsize) 
    return 0;

  /*functions not used!!*/
  CrFwPcktSetCmdRepId(pckt3,1);
  debugPacket(pckt3, pcktsize);
  DEBUGP_TSGS("CrFwPcktGetCmdRepId(pckt3) %d \n", CrFwPcktGetCmdRepId(pckt3));
  if (CrFwPcktGetCmdRepId(pckt3) != 0) 
    return 0;

  CrFwPcktSetSeqCnt(pckt3,0);
  debugPacket(pckt3, pcktsize);
  DEBUGP_TSGS("CrFwPcktGetSeqCnt(pckt3) %d \n", CrFwPcktGetSeqCnt(pckt3));
  if (CrFwPcktGetSeqCnt(pckt3) != 0) 
    return 0;

  CrFwPcktSetServType(pckt3,17);
  debugPacket(pckt3, pcktsize);
  DEBUGP_TSGS("CrFwPcktGetServType(pckt3) %d \n", CrFwPcktGetServType(pckt3));
  if (CrFwPcktGetServType(pckt3) != 17) 
    return 0;

  CrFwPcktSetServSubType(pckt3,1);
  debugPacket(pckt3, pcktsize);
  DEBUGP_TSGS("CrFwPcktGetServSubType(pckt3) %d \n", CrFwPcktGetServSubType(pckt3));
  if (CrFwPcktGetServSubType(pckt3) != 1) 
    return 0;

  CrFwPcktSetDiscriminant(pckt3,0);
  debugPacket(pckt3, pcktsize);
  DEBUGP_TSGS("CrFwPcktGetDiscriminant(pckt3) %d \n", CrFwPcktGetDiscriminant(pckt3));
  if (CrFwPcktGetDiscriminant(pckt3) != 0) 
    return 0; 

  CrFwPcktSetSrc(pckt3,12);
  debugPacket(pckt3, pcktsize);
  DEBUGP_TSGS("CrFwPcktGetSrc(pckt3) %d \n", CrFwPcktGetSrc(pckt3));
  if (CrFwPcktGetSrc(pckt3) != 12) 
    return 0;
  
  CrFwPcktSetAckLevel(pckt3,1,0,0,0);
  debugPacket(pckt3, pcktsize);
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
  debugPacket(pckt3, pcktsize);
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
  debugPacket(pckt3, pcktsize);
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
  debugPacket(pckt3, pcktsize);
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
  debugPacket(pckt3, pcktsize);
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
  debugPacket(pckt4, pcktsize);

  /* Check if there now one packet is allocated*/
  DEBUGP_TSGS("Check if there now one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  CrFwPcktSetCmdRepType(pckt4,crRepType);
  debugPacket(pckt4, pcktsize);
  DEBUGP_TSGS("CrFwPcktGetCmdRepType(pckt4) %d \n", CrFwPcktGetCmdRepType(pckt4));
  if (CrFwPcktGetCmdRepType(pckt4) != crRepType) 
    return 0;

  DEBUGP_TSGS("CrFwPcktGetLength(pckt4) %d \n", CrFwPcktGetLength(pckt4));
  if (CrFwPcktGetLength(pckt4) != pcktsize) 
    return 0;

  /*functions not used!!*/
  CrFwPcktSetCmdRepId(pckt4,1);
  debugPacket(pckt4, pcktsize);
  DEBUGP_TSGS("CrFwPcktGetCmdRepId(pckt4) %d \n", CrFwPcktGetCmdRepId(pckt4));
  if (CrFwPcktGetCmdRepId(pckt4) != 0) 
    return 0;

  CrFwPcktSetSeqCnt(pckt4,0);
  debugPacket(pckt4, pcktsize);
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
  debugPacket(pckt4, pcktsize);
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
  debugPacket(pckt4, pcktsize);
  DEBUGP_TSGS("CrFwPcktGetServType(pckt4) %d \n", CrFwPcktGetServType(pckt4));
  if (CrFwPcktGetServType(pckt4) != 17) 
    return 0;

  CrFwPcktSetServSubType(pckt4,2);
  debugPacket(pckt4, pcktsize);
  DEBUGP_TSGS("CrFwPcktGetServSubType(pckt4) %d \n", CrFwPcktGetServSubType(pckt4));
  if (CrFwPcktGetServSubType(pckt4) != 2) 
    return 0;

  CrFwPcktSetDiscriminant(pckt4,44);
  debugPacket(pckt4, pcktsize);
  DEBUGP_TSGS("CrFwPcktGetDiscriminant(pckt4) %d \n", CrFwPcktGetDiscriminant(pckt4));
  if (CrFwPcktGetDiscriminant(pckt4) != 0) 
    return 0; 

  CrFwPcktSetDest(pckt4,13);
  debugPacket(pckt4, pcktsize);
  DEBUGP_TSGS("CrFwPcktGetDest(pckt4) %d \n", CrFwPcktGetDest(pckt4));
  if (CrFwPcktGetDest(pckt4) != 13) 
    return 0;

  CrFwPcktSetGroup(pckt4,2);
  debugPacket(pckt4, pcktsize);
  DEBUGP_TSGS("CrFwPcktGetGroup(pckt4) %d \n", CrFwPcktGetGroup(pckt4));
  if (CrFwPcktGetGroup(pckt4) != 2) 
    return 0;

  DEBUGP_TSGS("CrFwPcktGetParStart(pckt4) %p \n", CrFwPcktGetParStart(pckt4));
  DEBUGP_TSGS("CrFwPcktGetParLength(pckt4) %d \n", CrFwPcktGetParLength(pckt4));

/*TBD remove if it works*/
  printf("pcktsize: %d \n", pcktsize);
  DEBUGP_TSGS("CrFwPcktGetLength(pckt4) %d \n", CrFwPcktGetLength(pckt4));
  printf("tmheader: %lu \n", sizeof(TmHeader_t));
  pstart = CrFwPcktGetParStart(pckt4);
  printf("pcktstart: %i \n", *pstart);
  printf("pcktsize: %d \n", pcktsize);
  printf("pcktsize: %d \n", pcktsize);

  /*release packet and create a new one!*/
  CrFwPcktRelease(pckt4);

  /* Check if number of Allocated Packets = 0*/
  DEBUGP_TSGS("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;


DEBUGP_TSGS("--------------------------------------\n");

DEBUGP_TSGS("--------------------------------------\n");

  return 1;   
}

CrFwBool_t CrPsPcktGetSetTestCase2()
{

  CrFwPckt_t pckt;
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
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 17)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 1)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  debugPacket(pckt, pcktsize);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  /* Check 17.2 packet*/
  DEBUGP_TSGS("Check 17.2 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 17);
  CrFwPcktSetServSubType(pckt, 2);
  CrFwPcktSetDiscriminant(pckt, 0);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 17)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 2)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  debugPacket(pckt, pcktsize);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  /* Check 17.3 packet*/
  DEBUGP_TSGS("Check 17.3 packet \n");
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 17);
  CrFwPcktSetServSubType(pckt, 3);
  CrFwPcktSetDiscriminant(pckt, 0);
  setOnBoardConnectCmdAppId(pckt, 0);
  debugPacket(pckt, pcktsize);

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
  debugPacket(pckt, pcktsize);
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
  debugPacket(pckt, pcktsize);

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
  debugPacket(pckt, pcktsize);
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
  debugPacket(pckt, pcktsize);

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
  debugPacket(pckt, pcktsize);
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
  debugPacket(pckt, pcktsize);

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
  debugPacket(pckt, pcktsize);
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
  debugPacket(pckt, pcktsize);

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
  debugPacket(pckt, pcktsize);
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
  debugPacket(pckt, pcktsize);

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
  debugPacket(pckt, pcktsize);
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
  debugPacket(pckt, pcktsize);

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
  debugPacket(pckt, pcktsize);
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
  debugPacket(pckt, pcktsize);

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
  debugPacket(pckt, pcktsize);
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
  debugPacket(pckt, pcktsize);

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
  debugPacket(pckt, pcktsize);
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
  debugPacket(pckt, pcktsize);

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
  debugPacket(pckt, pcktsize);
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
  debugPacket(pckt, pcktsize);

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
  debugPacket(pckt, pcktsize);
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


  /* Check 3.1 packet*/
  DEBUGP_TSGS("Check 3.1 packet \n");
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 3);
  CrFwPcktSetServSubType(pckt, 1);
  CrFwPcktSetDiscriminant(pckt, 0);
  setHkCreateHkParCmdHKRepStrucID(pckt, 0);
  setHkCreateHkParCmdCollectionInterval(pckt, 0);
  setHkCreateHkParCmdN1(pckt, 0); 
  setHkCreateHkParCmdN1ParamID(pckt, 0);
  setHkCreateHkParCmdNFA(pckt, 0);
  setHkCreateHkParCmdSCSampleRepNum(pckt, 0);
  setHkCreateHkParCmdN2(pckt, 0);
  setHkCreateHkParCmdN2ParamID(pckt, 0);   
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 1)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkCreateHkParCmdHKRepStrucID(pckt) != 0)
    return 0;
  if (getHkCreateHkParCmdCollectionInterval(pckt) != 0)
    return 0;
  if (getHkCreateHkParCmdN1(pckt) != 0)
    return 0;
  if (getHkCreateHkParCmdN1ParamID(pckt) != 0)
    return 0;
  if (getHkCreateHkParCmdNFA(pckt) != 0)
    return 0;
  if (getHkCreateHkParCmdSCSampleRepNum(pckt) != 0)
    return 0;
  if (getHkCreateHkParCmdN2(pckt) != 0)
    return 0;
  if (getHkCreateHkParCmdN2ParamID(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setHkCreateHkParCmdHKRepStrucID(pckt, MAX_CHAR);
  setHkCreateHkParCmdCollectionInterval(pckt, MAX_INT);
  setHkCreateHkParCmdN1(pckt, MAX_INT);
  setHkCreateHkParCmdN1ParamID(pckt, MAX_CHAR);
  setHkCreateHkParCmdNFA(pckt, MAX_INT);  
  setHkCreateHkParCmdSCSampleRepNum(pckt, MAX_INT); 
  setHkCreateHkParCmdN2(pckt, MAX_INT);
  setHkCreateHkParCmdN2ParamID(pckt, MAX_CHAR);
  debugPacket(pckt, pcktsize);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkCreateHkParCmdHKRepStrucID(pckt) != MAX_CHAR)
    return 0;
  if (getHkCreateHkParCmdCollectionInterval(pckt) != MAX_INT)
    return 0;
  if (getHkCreateHkParCmdN1(pckt) != MAX_INT)
    return 0;
  if (getHkCreateHkParCmdN1ParamID(pckt) != MAX_CHAR)
    return 0;
  if (getHkCreateHkParCmdNFA(pckt) != MAX_INT)
    return 0;
  if (getHkCreateHkParCmdSCSampleRepNum(pckt) != MAX_INT)
    return 0;
  if (getHkCreateHkParCmdN2(pckt) != MAX_INT)
    return 0;
  if (getHkCreateHkParCmdN2ParamID(pckt) != MAX_CHAR)
    return 0;

  /* Check 3.2 packet*/
  DEBUGP_TSGS("Check 3.2 packet \n");
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 3);
  CrFwPcktSetServSubType(pckt, 2);
  CrFwPcktSetDiscriminant(pckt, 0);
  setHkCreateDiagParCmdDiagRepStrucID(pckt, 0);
  setHkCreateDiagParCmdCollectionInterval(pckt, 0);
  setHkCreateDiagParCmdN1(pckt, 0); 
  setHkCreateDiagParCmdN1ParamID(pckt, 0);
  setHkCreateDiagParCmdNFA(pckt, 0);
  setHkCreateDiagParCmdSCSampleRepNum(pckt, 0);
  setHkCreateDiagParCmdN2(pckt, 0);
  setHkCreateDiagParCmdN2ParamID(pckt, 0);   
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 2)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkCreateDiagParCmdDiagRepStrucID(pckt) != 0)
    return 0;
  if (getHkCreateDiagParCmdCollectionInterval(pckt) != 0)
    return 0;
  if (getHkCreateDiagParCmdN1(pckt) != 0)
    return 0;
  if (getHkCreateDiagParCmdN1ParamID(pckt) != 0)
    return 0;
  if (getHkCreateDiagParCmdNFA(pckt) != 0)
    return 0;
  if (getHkCreateDiagParCmdSCSampleRepNum(pckt) != 0)
    return 0;
  if (getHkCreateDiagParCmdN2(pckt) != 0)
    return 0;
  if (getHkCreateDiagParCmdN2ParamID(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setHkCreateDiagParCmdDiagRepStrucID(pckt, MAX_CHAR);
  setHkCreateDiagParCmdCollectionInterval(pckt, MAX_INT);
  setHkCreateDiagParCmdN1(pckt, MAX_INT);
  setHkCreateDiagParCmdN1ParamID(pckt, MAX_CHAR);
  setHkCreateDiagParCmdNFA(pckt, MAX_INT);  
  setHkCreateDiagParCmdSCSampleRepNum(pckt, MAX_INT); 
  setHkCreateDiagParCmdN2(pckt, MAX_INT);
  setHkCreateDiagParCmdN2ParamID(pckt, MAX_CHAR);
  debugPacket(pckt, pcktsize);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkCreateDiagParCmdDiagRepStrucID(pckt) != MAX_CHAR)
    return 0;
  if (getHkCreateDiagParCmdCollectionInterval(pckt) != MAX_INT)
    return 0;
  if (getHkCreateDiagParCmdN1(pckt) != MAX_INT)
    return 0;
  if (getHkCreateDiagParCmdN1ParamID(pckt) != MAX_CHAR)
    return 0;
  if (getHkCreateDiagParCmdNFA(pckt) != MAX_INT)
    return 0;
  if (getHkCreateDiagParCmdSCSampleRepNum(pckt) != MAX_INT)
    return 0;
  if (getHkCreateDiagParCmdN2(pckt) != MAX_INT)
    return 0;
  if (getHkCreateDiagParCmdN2ParamID(pckt) != MAX_CHAR)
    return 0;

  /* Check 3.3 packet*/
  DEBUGP_TSGS("Check 3.3 packet \n");
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 3);
  CrFwPcktSetServSubType(pckt, 3);
  CrFwPcktSetDiscriminant(pckt, 0);
  setHkDeleteHkParCmdN(pckt, 0);
  setHkDeleteHkParCmdHKRepStrucID(pckt, 0); 
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 3)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkDeleteHkParCmdN(pckt) != 0)
    return 0;
  if (getHkDeleteHkParCmdHKRepStrucID(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setHkDeleteHkParCmdN(pckt, MAX_INT);
  setHkDeleteHkParCmdHKRepStrucID(pckt, MAX_CHAR);

  debugPacket(pckt, pcktsize);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkDeleteHkParCmdN(pckt) != MAX_INT)
    return 0;
  if (getHkDeleteHkParCmdHKRepStrucID(pckt) != MAX_CHAR)
    return 0;

  /* Check 3.4 packet*/
  DEBUGP_TSGS("Check 3.4 packet \n");
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 3);
  CrFwPcktSetServSubType(pckt, 4);
  CrFwPcktSetDiscriminant(pckt, 0);
  setHkDeleteDiagParCmdN(pckt, 0);
  setHkDeleteDiagParCmdDiagRepStrucID(pckt, 0); 
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 4)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkDeleteDiagParCmdN(pckt) != 0)
    return 0;
  if (getHkDeleteDiagParCmdDiagRepStrucID(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setHkDeleteDiagParCmdN(pckt, MAX_INT);
  setHkDeleteDiagParCmdDiagRepStrucID(pckt, MAX_CHAR);

  debugPacket(pckt, pcktsize);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkDeleteDiagParCmdN(pckt) != MAX_INT)
    return 0;
  if (getHkDeleteDiagParCmdDiagRepStrucID(pckt) != MAX_CHAR)
    return 0;

  /* Check 3.5 packet*/
  DEBUGP_TSGS("Check 3.5 packet \n");
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 3);
  CrFwPcktSetServSubType(pckt, 5);
  CrFwPcktSetDiscriminant(pckt, 0);
  setHkEnableHkParCmdN(pckt, 0);
  setHkEnableHkParCmdHKRepStrucID(pckt, 0); 
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 5)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkEnableHkParCmdN(pckt) != 0)
    return 0;
  if (getHkEnableHkParCmdHKRepStrucID(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setHkEnableHkParCmdN(pckt, MAX_INT);
  setHkEnableHkParCmdHKRepStrucID(pckt, MAX_CHAR);

  debugPacket(pckt, pcktsize);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkEnableHkParCmdN(pckt) != MAX_INT)
    return 0;
  if (getHkEnableHkParCmdHKRepStrucID(pckt) != MAX_CHAR)
    return 0;

  /* Check 3.6 packet*/
  DEBUGP_TSGS("Check 3.6 packet \n");
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 3);
  CrFwPcktSetServSubType(pckt, 6);
  CrFwPcktSetDiscriminant(pckt, 0);
  setHkDisableHkParCmdN(pckt, 0);
  setHkDisableHkParCmdHKRepStrucID(pckt, 0); 
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 6)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkDisableHkParCmdN(pckt) != 0)
    return 0;
  if (getHkDisableHkParCmdHKRepStrucID(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setHkDisableHkParCmdN(pckt, MAX_INT);
  setHkDisableHkParCmdHKRepStrucID(pckt, MAX_CHAR);

  debugPacket(pckt, pcktsize);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkDisableHkParCmdN(pckt) != MAX_INT)
    return 0;
  if (getHkDisableHkParCmdHKRepStrucID(pckt) != MAX_CHAR)
    return 0;

  /* Check 3.7 packet*/
  DEBUGP_TSGS("Check 3.7 packet \n");
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 3);
  CrFwPcktSetServSubType(pckt, 7);
  CrFwPcktSetDiscriminant(pckt, 0);
  setHkEnableDiagParCmdN(pckt, 0);
  setHkEnableDiagParCmdDiagRepStrucID(pckt, 0); 
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 7)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkEnableDiagParCmdN(pckt) != 0)
    return 0;
  if (getHkEnableDiagParCmdDiagRepStrucID(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setHkEnableDiagParCmdN(pckt, MAX_INT);
  setHkEnableDiagParCmdDiagRepStrucID(pckt, MAX_CHAR);

  debugPacket(pckt, pcktsize);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkEnableDiagParCmdN(pckt) != MAX_INT)
    return 0;
  if (getHkEnableDiagParCmdDiagRepStrucID(pckt) != MAX_CHAR)
    return 0;

  /* Check 3.8 packet*/
  DEBUGP_TSGS("Check 3.8 packet \n");
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 3);
  CrFwPcktSetServSubType(pckt, 8);
  CrFwPcktSetDiscriminant(pckt, 0);
  setHkDisableDiagParCmdN(pckt, 0);
  setHkDisableDiagParCmdDiagRepStrucID(pckt, 0); 
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 8)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkDisableDiagParCmdN(pckt) != 0)
    return 0;
  if (getHkDisableDiagParCmdDiagRepStrucID(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setHkDisableDiagParCmdN(pckt, MAX_INT);
  setHkDisableDiagParCmdDiagRepStrucID(pckt, MAX_CHAR);

  debugPacket(pckt, pcktsize);
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkDisableDiagParCmdN(pckt) != MAX_INT)
    return 0;
  if (getHkDisableDiagParCmdDiagRepStrucID(pckt) != MAX_CHAR)
    return 0;

  /* Check 3.9 packet*/
  DEBUGP_TSGS("Check 3.9 packet \n");
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 3);
  CrFwPcktSetServSubType(pckt, 9);
  CrFwPcktSetDiscriminant(pckt, 0);
  setHkRepStructHkParCmdN(pckt, 0);
  setHkRepStructHkParCmdHKRepStrucID(pckt, 0);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 9)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkRepStructHkParCmdN(pckt) != 0)
    return 0;
  if (getHkRepStructHkParCmdHKRepStrucID(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setHkRepStructHkParCmdN(pckt, MAX_INT);
  setHkRepStructHkParCmdHKRepStrucID(pckt, MAX_CHAR);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkRepStructHkParCmdN(pckt) != MAX_INT)
    return 0;
  if (getHkRepStructHkParCmdHKRepStrucID(pckt) != MAX_CHAR)
    return 0;

/* Check 3.10 packet*/
  DEBUGP_TSGS("Check 3.10 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 3);
  CrFwPcktSetServSubType(pckt, 10);
  CrFwPcktSetDiscriminant(pckt, 0);
  setHkRepStructHkParRepHKRepStrucID(pckt, 0);
  setHkRepStructHkParRepPeriodicGenActionStatus(pckt, 0);
  setHkRepStructHkParRepCollectionInterval(pckt, 0);
  setHkRepStructHkParRepN1(pckt, 0);
  setHkRepStructHkParRepN1ParamID(pckt, 0);
  setHkRepStructHkParRepNFA(pckt, 0);
  setHkRepStructHkParRepSCSampleRepNum(pckt, 0);
  setHkRepStructHkParRepN2(pckt, 0);
  setHkRepStructHkParRepN2ParamID(pckt, 0);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 10)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkRepStructHkParRepHKRepStrucID(pckt) != 0)
    return 0;
  if (getHkRepStructHkParRepPeriodicGenActionStatus(pckt) != 0)
    return 0;
  if (getHkRepStructHkParRepCollectionInterval(pckt) != 0)
    return 0;
  if (getHkRepStructHkParRepN1(pckt) != 0)
    return 0;
  if (getHkRepStructHkParRepN1ParamID(pckt) != 0)
    return 0;
  if (getHkRepStructHkParRepNFA(pckt) != 0)
    return 0;
  if (getHkRepStructHkParRepSCSampleRepNum(pckt) != 0)
    return 0;
  if (getHkRepStructHkParRepN2(pckt) != 0)
    return 0;
  if (getHkRepStructHkParRepN2ParamID(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  setHkRepStructHkParRepHKRepStrucID(pckt, MAX_CHAR);
  setHkRepStructHkParRepPeriodicGenActionStatus(pckt, MAX_CHAR);
  setHkRepStructHkParRepCollectionInterval(pckt, MAX_INT);
  setHkRepStructHkParRepN1(pckt, MAX_INT);
  setHkRepStructHkParRepN1ParamID(pckt, MAX_CHAR);
  setHkRepStructHkParRepNFA(pckt, MAX_INT);
  setHkRepStructHkParRepSCSampleRepNum(pckt, MAX_INT);
  setHkRepStructHkParRepN2(pckt, MAX_INT);
  setHkRepStructHkParRepN2ParamID(pckt, MAX_CHAR);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetDiscriminant(pckt) != MAX_CHAR)
    return 0;
  if (getHkRepStructHkParRepHKRepStrucID(pckt) != MAX_CHAR)
    return 0;
  if (getHkRepStructHkParRepPeriodicGenActionStatus(pckt) != MAX_CHAR)
    return 0;
  if (getHkRepStructHkParRepCollectionInterval(pckt) != MAX_INT)
    return 0;
  if (getHkRepStructHkParRepN1(pckt) != MAX_INT)
    return 0;
  if (getHkRepStructHkParRepN1ParamID(pckt) != MAX_CHAR)
    return 0;
  if (getHkRepStructHkParRepNFA(pckt) != MAX_INT)
    return 0;
  if (getHkRepStructHkParRepSCSampleRepNum(pckt) != MAX_INT)
    return 0;
  if (getHkRepStructHkParRepN2(pckt) != MAX_INT)
    return 0;
  if (getHkRepStructHkParRepN2ParamID(pckt) != MAX_CHAR)
    return 0;

  /* Check 3.11 packet*/
  DEBUGP_TSGS("Check 3.11 packet \n");
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 3);
  CrFwPcktSetServSubType(pckt, 11);
  CrFwPcktSetDiscriminant(pckt, 0);
  setHkRepStructDiagParCmdN(pckt, 0);
  setHkRepStructDiagParCmdDiagRepStrucID(pckt, 0);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 11)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkRepStructDiagParCmdN(pckt) != 0)
    return 0;
  if (getHkRepStructDiagParCmdDiagRepStrucID(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_SHORT);
  setHkRepStructDiagParCmdN(pckt, MAX_INT);
  setHkRepStructDiagParCmdDiagRepStrucID(pckt, MAX_CHAR);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkRepStructDiagParCmdN(pckt) != MAX_INT)
    return 0;
  if (getHkRepStructDiagParCmdDiagRepStrucID(pckt) != MAX_CHAR)
    return 0;

/* Check 3.12 packet*/
  DEBUGP_TSGS("Check 3.12 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 3);
  CrFwPcktSetServSubType(pckt, 12);
  CrFwPcktSetDiscriminant(pckt, 0);
  setHkRepStructDiagParRepDiagRepStrucID(pckt, 0);
  setHkRepStructDiagParRepPeriodicGenActionStatus(pckt, 0);
  setHkRepStructDiagParRepCollectionInterval(pckt, 0);
  setHkRepStructDiagParRepN1(pckt, 0);
  setHkRepStructDiagParRepN1ParamID(pckt, 0);
  setHkRepStructDiagParRepNFA(pckt, 0);
  setHkRepStructDiagParRepSCSampleRepNum(pckt, 0);
  setHkRepStructDiagParRepN2(pckt, 0);
  setHkRepStructDiagParRepN2ParamID(pckt, 0);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 12)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkRepStructDiagParRepDiagRepStrucID(pckt) != 0)
    return 0;
  if (getHkRepStructDiagParRepPeriodicGenActionStatus(pckt) != 0)
    return 0;
  if (getHkRepStructDiagParRepCollectionInterval(pckt) != 0)
    return 0;
  if (getHkRepStructDiagParRepN1(pckt) != 0)
    return 0;
  if (getHkRepStructDiagParRepN1ParamID(pckt) != 0)
    return 0;
  if (getHkRepStructDiagParRepNFA(pckt) != 0)
    return 0;
  if (getHkRepStructDiagParRepSCSampleRepNum(pckt) != 0)
    return 0;
  if (getHkRepStructDiagParRepN2(pckt) != 0)
    return 0;
  if (getHkRepStructDiagParRepN2ParamID(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  setHkRepStructDiagParRepDiagRepStrucID(pckt, MAX_CHAR);
  setHkRepStructDiagParRepPeriodicGenActionStatus(pckt, MAX_CHAR);
  setHkRepStructDiagParRepCollectionInterval(pckt, MAX_INT);
  setHkRepStructDiagParRepN1(pckt, MAX_INT);
  setHkRepStructDiagParRepN1ParamID(pckt, MAX_CHAR);
  setHkRepStructDiagParRepNFA(pckt, MAX_INT);
  setHkRepStructDiagParRepSCSampleRepNum(pckt, MAX_INT);
  setHkRepStructDiagParRepN2(pckt, MAX_INT);
  setHkRepStructDiagParRepN2ParamID(pckt, MAX_CHAR);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetDiscriminant(pckt) != MAX_CHAR)
    return 0;
  if (getHkRepStructDiagParRepDiagRepStrucID(pckt) != MAX_CHAR)
    return 0;
  if (getHkRepStructDiagParRepPeriodicGenActionStatus(pckt) != MAX_CHAR)
    return 0;
  if (getHkRepStructDiagParRepCollectionInterval(pckt) != MAX_INT)
    return 0;
  if (getHkRepStructDiagParRepN1(pckt) != MAX_INT)
    return 0;
  if (getHkRepStructDiagParRepN1ParamID(pckt) != MAX_CHAR)
    return 0;
  if (getHkRepStructDiagParRepNFA(pckt) != MAX_INT)
    return 0;
  if (getHkRepStructDiagParRepSCSampleRepNum(pckt) != MAX_INT)
    return 0;
  if (getHkRepStructDiagParRepN2(pckt) != MAX_INT)
    return 0;
  if (getHkRepStructDiagParRepN2ParamID(pckt) != MAX_CHAR)
    return 0;

/* Check 3.25 packet*/
  DEBUGP_TSGS("Check 3.25 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 3);
  CrFwPcktSetServSubType(pckt, 25);
  CrFwPcktSetDiscriminant(pckt, 0);
  setHkOneShotHkRepHKRepStrucID(pckt, 0);
  setHkOneShotHkRepParamVal(pckt, 0);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 25)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkOneShotHkRepHKRepStrucID(pckt) != 0)
    return 0;
  if (getHkOneShotHkRepParamVal(pckt) != 0)
    return 0;


  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  setHkOneShotHkRepHKRepStrucID(pckt, MAX_CHAR);
  setHkOneShotHkRepParamVal(pckt, MAX_INT);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetDiscriminant(pckt) != MAX_CHAR)
    return 0;
  if (getHkOneShotHkRepHKRepStrucID(pckt) != MAX_CHAR)
    return 0;
  if (getHkOneShotHkRepParamVal(pckt) != MAX_INT)
    return 0;

/* Check 3.26 packet*/
  DEBUGP_TSGS("Check 3.26 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 3);
  CrFwPcktSetServSubType(pckt, 26);
  CrFwPcktSetDiscriminant(pckt, 0);
  setHkOneShotDiagRepDiagRepStrucID(pckt, 0);
  setHkOneShotDiagRepParamVal(pckt, 0);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 26)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkOneShotDiagRepDiagRepStrucID(pckt) != 0)
    return 0;
  if (getHkOneShotDiagRepParamVal(pckt) != 0)
    return 0;


  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  setHkOneShotDiagRepDiagRepStrucID(pckt, MAX_CHAR);
  setHkOneShotDiagRepParamVal(pckt, MAX_INT);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetDiscriminant(pckt) != MAX_CHAR)
    return 0;
  if (getHkOneShotDiagRepDiagRepStrucID(pckt) != MAX_CHAR)
    return 0;
  if (getHkOneShotDiagRepParamVal(pckt) != MAX_INT)
    return 0;

/* Check 3.27 packet*/
  DEBUGP_TSGS("Check 3.27 packet \n");
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 3);
  CrFwPcktSetServSubType(pckt, 27);
  CrFwPcktSetDiscriminant(pckt, 0);
  setHkOneShotHkCmdN(pckt, 0);
  setHkOneShotHkCmdHKRepStrucID(pckt, 0);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 27)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkOneShotHkCmdN(pckt) != 0)
    return 0;
  if (getHkOneShotHkCmdHKRepStrucID(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  setHkOneShotHkCmdN(pckt, MAX_INT);
  setHkOneShotHkCmdHKRepStrucID(pckt, MAX_CHAR);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetDiscriminant(pckt) != MAX_CHAR)
    return 0;
  if (getHkOneShotHkCmdN(pckt) != MAX_INT)
    return 0;
  if (getHkOneShotHkCmdHKRepStrucID(pckt) != MAX_CHAR)
    return 0;

/* Check 3.28 packet*/
  DEBUGP_TSGS("Check 3.28 packet \n");
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 3);
  CrFwPcktSetServSubType(pckt, 28);
  CrFwPcktSetDiscriminant(pckt, 0);
  setHkOneShotDiagCmdN(pckt, 0);
  setHkOneShotDiagCmdDiagRepStrucID(pckt, 0);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 3)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 28)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getHkOneShotDiagCmdN(pckt) != 0)
    return 0;
  if (getHkOneShotDiagCmdDiagRepStrucID(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  setHkOneShotDiagCmdN(pckt, MAX_INT);
  setHkOneShotDiagCmdDiagRepStrucID(pckt, MAX_CHAR);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetDiscriminant(pckt) != MAX_CHAR)
    return 0;
  if (getHkOneShotDiagCmdN(pckt) != MAX_INT)
    return 0;
  if (getHkOneShotDiagCmdDiagRepStrucID(pckt) != MAX_CHAR)
    return 0;

/* Check 5.1 packet*/
  DEBUGP_TSGS("Check 5.1 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 5);
  CrFwPcktSetServSubType(pckt, 1);
  CrFwPcktSetDiscriminant(pckt, 0);
  setEvtRep1EventD(pckt, 0);
  setEvtRep1AuxData(pckt, 0);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 5)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 1)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getEvtRep1EventD(pckt) != 0)
    return 0;
  if (getEvtRep1AuxData(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  setEvtRep1EventD(pckt, MAX_CHAR);
  setEvtRep1AuxData(pckt, MAX_INT);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetDiscriminant(pckt) != MAX_CHAR)
    return 0;
  if (getEvtRep1EventD(pckt) != MAX_CHAR)
    return 0;
  if (getEvtRep1AuxData(pckt) != MAX_INT)
    return 0;

/* Check 5.2 packet*/
  DEBUGP_TSGS("Check 5.2 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 5);
  CrFwPcktSetServSubType(pckt, 2);
  CrFwPcktSetDiscriminant(pckt, 0);
  setEvtRep2EventD(pckt, 0);
  setEvtRep2AuxData(pckt, 0);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 5)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 2)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getEvtRep2EventD(pckt) != 0)
    return 0;
  if (getEvtRep2AuxData(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  setEvtRep2EventD(pckt, MAX_CHAR);
  setEvtRep2AuxData(pckt, MAX_INT);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetDiscriminant(pckt) != MAX_CHAR)
    return 0;
  if (getEvtRep2EventD(pckt) != MAX_CHAR)
    return 0;
  if (getEvtRep2AuxData(pckt) != MAX_INT)
    return 0;

/* Check 5.3 packet*/
  DEBUGP_TSGS("Check 5.3 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 5);
  CrFwPcktSetServSubType(pckt, 3);
  CrFwPcktSetDiscriminant(pckt, 0);
  setEvtRep3EventD(pckt, 0);
  setEvtRep3AuxData(pckt, 0);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 5)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 3)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getEvtRep3EventD(pckt) != 0)
    return 0;
  if (getEvtRep3AuxData(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  setEvtRep3EventD(pckt, MAX_CHAR);
  setEvtRep3AuxData(pckt, MAX_INT);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetDiscriminant(pckt) != MAX_CHAR)
    return 0;
  if (getEvtRep3EventD(pckt) != MAX_CHAR)
    return 0;
  if (getEvtRep3AuxData(pckt) != MAX_INT)
    return 0;

/* Check 5.4 packet*/
  DEBUGP_TSGS("Check 5.4 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 5);
  CrFwPcktSetServSubType(pckt, 4);
  CrFwPcktSetDiscriminant(pckt, 0);
  setEvtRep4EventD(pckt, 0);
  setEvtRep4AuxData(pckt, 0);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 5)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 4)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getEvtRep4EventD(pckt) != 0)
    return 0;
  if (getEvtRep4AuxData(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  setEvtRep4EventD(pckt, MAX_CHAR);
  setEvtRep4AuxData(pckt, MAX_INT);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetDiscriminant(pckt) != MAX_CHAR)
    return 0;
  if (getEvtRep4EventD(pckt) != MAX_CHAR)
    return 0;
  if (getEvtRep4AuxData(pckt) != MAX_INT)
    return 0;

/* Check 5.5 packet*/
  DEBUGP_TSGS("Check 5.5 packet \n");
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 5);
  CrFwPcktSetServSubType(pckt, 5);
  CrFwPcktSetDiscriminant(pckt, 0);
  setEvtEnableCmdN(pckt, 0);
  setEvtEnableCmdEventD(pckt, 0);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 5)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 5)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getEvtEnableCmdN(pckt) != 0)
    return 0;
  if (getEvtEnableCmdEventD(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  setEvtEnableCmdN(pckt, MAX_INT);
  setEvtEnableCmdEventD(pckt, MAX_CHAR);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getEvtEnableCmdN(pckt) != MAX_INT)
    return 0;
  if (getEvtEnableCmdEventD(pckt) != MAX_CHAR)
    return 0;

/* Check 5.6 packet*/
  DEBUGP_TSGS("Check 5.6 packet \n");
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 5);
  CrFwPcktSetServSubType(pckt, 6);
  CrFwPcktSetDiscriminant(pckt, 0);
  setEvtDisableCmdN(pckt, 0);
  setEvtDisableCmdEventD(pckt, 0);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 5)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 6)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getEvtDisableCmdN(pckt) != 0)
    return 0;
  if (getEvtDisableCmdEventD(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  setEvtDisableCmdN(pckt, MAX_INT);
  setEvtDisableCmdEventD(pckt, MAX_CHAR);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getEvtDisableCmdN(pckt) != MAX_INT)
    return 0;
  if (getEvtDisableCmdEventD(pckt) != MAX_CHAR)
    return 0;

/* Check 5.7 packet*/
  DEBUGP_TSGS("Check 5.7 packet \n");
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt, 5);
  CrFwPcktSetServSubType(pckt, 7);
  CrFwPcktSetDiscriminant(pckt, 0);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crCmdType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 5)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 7)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;

/* Check 5.8 packet*/
  DEBUGP_TSGS("Check 5.8 packet \n");
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt, 5);
  CrFwPcktSetServSubType(pckt, 8);
  CrFwPcktSetDiscriminant(pckt, 0);
  setEvtRepDisabledRepN(pckt, 0);
  setEvtRepDisabledRepEventD(pckt, 0);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetCmdRepType(pckt) != crRepType)
    return 0;
  if (CrFwPcktGetServType(pckt) != 5)
    return 0;
  if (CrFwPcktGetServSubType(pckt) != 8)
    return 0;
  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getEvtRepDisabledRepN(pckt) != 0)
    return 0;
  if (getEvtRepDisabledRepEventD(pckt) != 0)
    return 0;

  CrFwPcktSetDiscriminant(pckt, MAX_CHAR);
  setEvtRepDisabledRepN(pckt, MAX_INT);
  setEvtRepDisabledRepEventD(pckt, MAX_CHAR);
  debugPacket(pckt, pcktsize);

  if (CrFwPcktGetDiscriminant(pckt) != 0)
    return 0;
  if (getEvtRepDisabledRepN(pckt) != MAX_INT)
    return 0;
  if (getEvtRepDisabledRepEventD(pckt) != MAX_CHAR)
    return 0;


  return 1;
}