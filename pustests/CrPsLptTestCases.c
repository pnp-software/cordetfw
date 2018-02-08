/**
 * @file CrPsLptTestCases.c
 * @ingroup PUSTestsuite
 *
 * @brief Implementation of the test cases for the Large Packet Transfer Service components.
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

/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
/* Include framework files */
#include "CrFwCmpData.h"
#include "OutRegistry/CrFwOutRegistry.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "InCmd/CrFwInCmd.h"
#include "InFactory/CrFwInFactory.h"
#include "OutFactory/CrFwOutFactory.h"
#include "InLoader/CrFwInLoader.h"
#include "OutLoader/CrFwOutLoader.h"
#include "InLoader/CrFwInLoader.h"
#include "CrFwTime.h"

#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include <CrPsUtilitiesServLpt.h>
#include <CrPsUtilitiesServReqVerif.h>
#include "config/CrFwOutFactoryUserPar.h"
#include <Services/LargePacketTransfer/InCmd/CrPsLptUpFirstCmd.h>
#include <Services/LargePacketTransfer/InCmd/CrPsLptUpInterCmd.h>
#include <Services/LargePacketTransfer/InCmd/CrPsLptUpLastCmd.h>
#include <Services/LargePacketTransfer/InCmd/CrPsLptStartDownCmd.h>
#include <Services/LargePacketTransfer/InCmd/CrPsLptAbortDownCmd.h>
#include <Services/LargePacketTransfer/OutCmp/CrPsLptDownFirstRep.h>
#include <Services/LargePacketTransfer/OutCmp/CrPsLptDownInterRep.h>
#include <Services/LargePacketTransfer/OutCmp/CrPsLptDownLastRep.h>
#include <Services/LargePacketTransfer/StateMachines/CrPsLptCreate.h>
#include <Services/LargePacketTransfer/Procedures/CrPsLptUpCmdStartCreate.h>
#include <Services/General/CrPsPktServLpt.h>
#include <Services/General/CrPsPktServLptSupp.h>
#include <DataPool/CrPsDpServLpt.h>
#include "CrPsUserConstants.h"
#include "CrPsPkt.h" /* for data structures TmHeader_t and TcHeader_t */

/* Include system files */
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

/** The maximum size in number of bytes of a packet */
#define LPTSIZE 4000

static uint8_t memArray2set[LPTSIZE*2]; /* NOTE: *2 because GCOV needs it wo work properly */
static uint8_t memArray2get[LPTSIZE*2];

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsLptTestCase1()
{
  /* Check Service 13 (all standard functions to return outcome = 1) */
  FwSmDesc_t inFactory, outFactory, outManager, outCmp, inCmd;
  CrFwPckt_t pckt;
  CrFwCmpData_t *cmpData;

  /* Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines */
  CrPsInitServLpt();
  CrPsExecServLpt();

  /* Instantiate the OutFactory, InFactory and OutManager*/
  outFactory = CrFwOutFactoryMake();
  if (outFactory == NULL)
    return 0;
  if (FwSmCheckRec(outFactory) != smSuccess)
    return 0;

  inFactory = CrFwInFactoryMake();
  if (inFactory == NULL)
    return 0;
  if (FwSmCheckRec(inFactory) != smSuccess)
    return 0;

  outManager = CrFwOutManagerMake(0);
  if (outManager == NULL)
    return 0;
  if (FwSmCheckRec(outManager) != smSuccess)
    return 0;

  /* Initialize and Configure OutFactory, InFactory and Outmanager and check success */
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;
  
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  if (!CrFwCmpIsInConfigured(inFactory))
    return 0;

  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  if (!CrFwCmpIsInConfigured(outManager))
    return 0; 

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Create a 13,1 OutComponent to get outcome success*/
  outCmp = CrFwOutFactoryMakeOutCmp(13,1,0,80);

  /*run the Enable Check and Update Action */
  CrPsLptDownFirstRepEnableCheck(outCmp);

  CrPsLptDownFirstRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  
  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Create a 13,2 OutComponent to get outcome success*/
  outCmp = CrFwOutFactoryMakeOutCmp(13,2,0,80);

  /*run the Enable Check and Update Action */
  CrPsLptDownInterRepEnableCheck(outCmp);

  CrPsLptDownInterRepRepeatCheck(outCmp);

  CrPsLptDownInterRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  
  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

    /* Create a 13,3 OutComponent to get outcome success*/
  outCmp = CrFwOutFactoryMakeOutCmp(13,3,0,80);

  setDplptRemSizeItem(0, 10);

  /*run the Enable Check and Update Action */
  CrPsLptDownLastRepEnableCheck(outCmp);

  CrPsLptDownLastRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  
  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Allocate a 13,9 Packet */
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,13);
  CrFwPcktSetServSubType(pckt,9);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 
  setLptUpFirstCmdTid(pckt, 0);
  setLptUpFirstCmdPartSeqNmb(pckt, 1);
  setLptUpFirstCmdPart(pckt, 1, 4);

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* run the start action, the progress action and the termination action */
  CrPsLptUpFirstCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpFirstCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpFirstCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);
  
  /* Allocate a 13,10 Packet */
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,13);
  CrFwPcktSetServSubType(pckt,10);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 
  setLptUpInterCmdTid(pckt, 0);
  setLptUpInterCmdPartSeqNmb(pckt, 2);
  setLptUpInterCmdPart(pckt, 1, 4);

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* run the start action, the progress action and the termination action */
  CrPsLptUpInterCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpInterCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpInterCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);
  
  /* Allocate a 13,11 Packet */
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,13);
  CrFwPcktSetServSubType(pckt,11);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 
  setLptUpLastCmdTid(pckt, 0);
  setLptUpLastCmdPartSeqNmb(pckt, 3);
  setLptUpLastCmdPart(pckt, 1, 4);
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* run the start action, the progress action and the termination action */
  CrPsLptUpLastCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpLastCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpLastCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Create a 13,16 OutComponent to get outcome success*/
  outCmp = CrFwOutFactoryMakeOutCmp(13,16,0,80);

  /*run the Enable Check and Update Action */
  CrPsLptUpAbortRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  
  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

 /* Allocate a 13,129 Packet */
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,13);
  CrFwPcktSetServSubType(pckt,129);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* run the start action, the progress action and the termination action */
  CrPsLptStartDownCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptStartDownCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptStartDownCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

 /* Allocate a 13,130 Packet */
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,13);
  CrFwPcktSetServSubType(pckt,130);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* run the start action, the progress action and the termination action */
  CrPsLptAbortDownCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptAbortDownCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptAbortDownCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Reset OutManager and check that all OutComponents are unloaded and released */
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  /* Reset the OutFactory */
  CrFwCmpReset(outFactory);  
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Reset the InFactory and check that no InCommands are allocated */
  CrFwCmpReset(inFactory);
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  return 1;
}



CrFwBool_t CrPsLptTestCase2()
{
  /* Check Service 13 Up-Transfer */
  FwSmDesc_t inFactory, outFactory, outManager, inCmd;
  CrFwPckt_t pckt;
  CrFwCmpData_t *cmpData;
  uint8_t* memptr;
  uint32_t i, partsize, o, LptBuffer;
  LptBuffer = 0;

  /* fill the memory Array with random Numbers for the Up-Transfer */
  for (i=0;i<LPTSIZE;i++)
  {
    memArray2set[i] = rand() % 255;
  }

  /* Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines */
  CrPsInitServLpt();

  /* Instantiate the OutFactory, InFactory and OutManager*/
  outFactory = CrFwOutFactoryMake();
  if (outFactory == NULL)
    return 0;
  if (FwSmCheckRec(outFactory) != smSuccess)
    return 0;

  inFactory = CrFwInFactoryMake();
  if (inFactory == NULL)
    return 0;
  if (FwSmCheckRec(inFactory) != smSuccess)
    return 0;

  outManager = CrFwOutManagerMake(0);
  if (outManager == NULL)
    return 0;
  if (FwSmCheckRec(outManager) != smSuccess)
    return 0;

  /* Initialize and Configure OutFactory, InFactory and Outmanager and check success */
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;
  
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  if (!CrFwCmpIsInConfigured(inFactory))
    return 0;

  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  if (!CrFwCmpIsInConfigured(outManager))
    return 0; 

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a 13,9 Packet */
  pckt = CrFwPcktMake(CR_FW_MAX_PCKT_LENGTH);
  CrFwPcktSetServType(pckt,13);
  CrFwPcktSetServSubType(pckt,9);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Set the Packet data content */
  setLptUpFirstCmdTid(pckt, LptBuffer);
  setLptUpFirstCmdPartSeqNmb(pckt, 1);
  memptr = &memArray2set[0];
  o=(sizeof(TcHeader_t)+sizeof(CrPsTid_t)+sizeof(CrPsNumberU4_t));
  partsize = CR_FW_MAX_PCKT_LENGTH - o - CRC_LENGTH;
  memcpy(&((uint8_t*)pckt)[o], memptr, partsize);
  
  /* run the start action, the progress action and the termination action */
  CrPsLptUpFirstCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpFirstCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpFirstCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Execute the Statemachine */
  CrPsExecServLptSm();

  /* Release the inCommand */
  CrFwInFactoryReleaseInCmd(inCmd);
  
  /*LOOP !!!! i = 1 to ??*/
  for (i=1;i<LPTSIZE;i++)
  {
    /* Allocate a 13,10 Packet */
    pckt = CrFwPcktMake(CR_FW_MAX_PCKT_LENGTH);
    CrFwPcktSetServType(pckt,13);
    CrFwPcktSetServSubType(pckt,10);
    CrFwPcktSetCmdRepType(pckt,crCmdType);
    CrFwPcktSetDiscriminant(pckt,0);
    CrFwPcktSetSrc(pckt,0);
    CrFwPcktSetDest(pckt,10);
    CrFwPcktSetGroup(pckt,1);
    CrFwPcktSetAckLevel(pckt,0,0,0,0);  
    CrFwPcktSetSeqCnt(pckt,0); 

    setLptUpInterCmdTid(pckt, LptBuffer);
    setLptUpInterCmdPartSeqNmb(pckt, i+1);
    memptr = &memArray2set[partsize * i];
    o=(sizeof(TcHeader_t)+sizeof(CrPsTid_t)+sizeof(CrPsNumberU4_t));
    partsize = CR_FW_MAX_PCKT_LENGTH - o - CRC_LENGTH;
    memcpy(&((uint8_t*)pckt)[o], memptr, partsize);

    inCmd = CrFwInFactoryMakeInCmd(pckt);

    /* run the start action, the progress action and the termination action */
    CrPsLptUpInterCmdStartAction(inCmd);
    cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
    if (cmpData->outcome != 1)
    {
      return 0;
    }
    CrPsLptUpInterCmdProgressAction(inCmd);
    cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
    if (cmpData->outcome != 1)
    {
      return 0;
    }
    CrPsLptUpInterCmdTerminationAction(inCmd);
    cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
    if (cmpData->outcome != 1)
    {
      return 0;
    }

    /* Execute the Statemachine */
    CrPsExecServLptSm();

    /* Release the inCommand */
    CrFwInFactoryReleaseInCmd(inCmd);
    if ((partsize*(i+2)) >= (LPTSIZE))
    {
      /*end LOOP !!! when to few data left (break) */
      break;
    }
  }

  i+=1;
  
  /* Allocate a 13,11 Packet */
  pckt = CrFwPcktMake(CR_FW_MAX_PCKT_LENGTH);
  CrFwPcktSetServType(pckt,13);
  CrFwPcktSetServSubType(pckt,11);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 

  setLptUpLastCmdTid(pckt, LptBuffer);
  setLptUpLastCmdPartSeqNmb(pckt, i+1);
    
  memptr = &memArray2set[partsize * i];
  o=(sizeof(TcHeader_t)+sizeof(CrPsTid_t)+sizeof(CrPsNumberU4_t));
  partsize = LPTSIZE - partsize*i;
  memcpy(&((uint8_t*)pckt)[o], memptr, partsize);
   
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* run the start action, the progress action and the termination action */
  CrPsLptUpLastCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpLastCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpLastCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Execute the Statemachine */
  CrPsExecServLptSm();

  /* Release the inCommand */
  CrFwInFactoryReleaseInCmd(inCmd);

  /* get the Data from the Buffer */
  memcpy(&memArray2get, (uint8_t*)getLptMemStartAddr(LptBuffer), getLptMemSize(LptBuffer));

  /* Check if the Data is stored in the Buffer correctly*/
  if (memcmp(memArray2set, memArray2get, LPTSIZE))
  {
    return 0;
  }

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Reset OutManager and check that all OutComponents are unloaded and released */
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  /* Reset the OutFactory */
  CrFwCmpReset(outFactory);  
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Reset the InFactory and check that no InCommands are allocated */
  CrFwCmpReset(inFactory);
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  return 1;
}



CrFwBool_t CrPsLptTestCase3()
{
  /* Check Service 13 Down-Link*/
  FwSmDesc_t inFactory, outFactory, outManager, inCmd, outCmp, outCmpArr[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];
  CrFwCmpData_t *outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  CrFwPckt_t pckt;
  CrFwCmpData_t *cmpData;
  CrFwCmpData_t *outCmpData;
  CrFwOutCmpData_t* cmpSpecificData;
  uint32_t i, PartSeqNmb, o, partsize, lptRemSize, LptBufferId;
  LptBufferId = 0;
  
  /* empty the memory Array for getting the data from the Buffer (so i have to refill it with the contents of the incomming packets) */
  for (i=0;i<LPTSIZE;i++)
  {
    memArray2get[i] = 0;
  }

  /* Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines */
  CrPsInitServLpt();

  /* Instantiate the OutFactory, InFactory and OutManager*/
  outFactory = CrFwOutFactoryMake();
  if (outFactory == NULL)
    return 0;
  if (FwSmCheckRec(outFactory) != smSuccess)
    return 0;

  inFactory = CrFwInFactoryMake();
  if (inFactory == NULL)
    return 0;
  if (FwSmCheckRec(inFactory) != smSuccess)
    return 0;

  outManager = CrFwOutManagerMake(0);
  if (outManager == NULL)
    return 0;
  if (FwSmCheckRec(outManager) != smSuccess)
    return 0;

  /* Initialize and Configure OutFactory, InFactory and Outmanager and check success */
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;
  
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  if (!CrFwCmpIsInConfigured(inFactory))
    return 0;

  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  if (!CrFwCmpIsInConfigured(outManager))
    return 0; 

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a 13,129 Packet */
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,13);
  CrFwPcktSetServSubType(pckt,129);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 
  setLptStartDownCmdTid(pckt, LptBufferId);

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Fill the outfactory so that an Error could occur (leave one free slot) */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
  {
    outCmpArr[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
  }

  /* Execute the inCmd and the Statemachine */
  CrFwCmpExecute(inCmd); 
  CrPsExecServLptSm();

  /* Check if an OutComponent allocation error occures */
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /* Reset application error Code */
  CrFwSetAppErrCode(crNoAppErr);

  /* Release all outcomponents, that have been created to fill the outfactory */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
  { 
    CrFwOutFactoryReleaseOutCmp(outCmpArr[i]);
  }

  /* Execute the inCmd and the Statemachine again to successfully create an 13,1 */
  CrFwCmpExecute(inCmd); 
  CrPsExecServLptSm();

  /* Release the inCommand */
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Get the Data from the out Manager */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];
  outCmpData = (CrFwCmpData_t*)FwSmGetData(outCmp);
  cmpSpecificData = (CrFwOutCmpData_t*)(outCmpData->cmpSpecificData);

  /* Check if there is a 13,1 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 13)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 1)
    return 0;

  /* Fill the outfactory so that an error could occur (leave one free slot) */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-2;i++)
  {
    outCmpArr[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
  }

  /* Get the PartSeqNmb and lptRemSize to reset it after the next packet fails*/
  PartSeqNmb = getDppartSeqNmbItem(LptBufferId);
  lptRemSize = getDplptRemSizeItem(LptBufferId);

  /* Execute the outCmp and the Statemachine */
  CrFwCmpExecute(outCmp); 
  CrPsExecServLptSm();

  /* Correct the PartSeqNmb and the lptRemSize - subtract the values of the failed packet*/
  setDppartSeqNmbItem(LptBufferId, PartSeqNmb);
  setDplptRemSizeItem(LptBufferId, lptRemSize);
  
  /*Check if an OutComponent allocation error occures*/
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /*Reset application error Corde*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Release all outcomponents, that have been created to fill the outfactory */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-2;i++)
  { 
    CrFwOutFactoryReleaseOutCmp(outCmpArr[i]);
  }

  /* Execute the OutComponent and the Statemachine */
  CrFwCmpExecute(outCmp); 

  CrPsExecServLptSm();
  
  /* get the data from the outCmp (1st Packet)*/
  o=(sizeof(TmHeader_t)+sizeof(CrPsTid_t)+sizeof(CrPsNumberU4_t));
  partsize = CrFwPcktGetLength(cmpSpecificData->pckt) - o - CRC_LENGTH;
  memcpy(&memArray2get[0], &((uint8_t*)cmpSpecificData->pckt)[o], partsize);

  /* Get the Data from the out Manager */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[1];
  outCmpData = (CrFwCmpData_t*)FwSmGetData(outCmp);
  cmpSpecificData = (CrFwOutCmpData_t*)(outCmpData->cmpSpecificData);

  /* Check if there is a 13,1 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 13)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 2)
    return 0;
  
  /* Execute the OutComponent and the Statemachine */
  CrFwCmpExecute(outCmp); 
  if (CrPsLptDownInterRepRepeatCheck(outCmp) != 1)
    return 0;
  CrPsExecServLptSm();

  /* get the data from the outCmp (2nd Packet)*/
  memcpy(&memArray2get[partsize], &((uint8_t*)cmpSpecificData->pckt)[o], partsize);

  /* Execute the OutComponent and the Statemachine */
  CrFwCmpExecute(outCmp); 
  if (CrPsLptDownInterRepRepeatCheck(outCmp) != 1)
    return 0;
  CrPsExecServLptSm();
  
  /* get the data from the outCmp (3rd Packet)*/
  memcpy(&memArray2get[partsize*2], &((uint8_t*)cmpSpecificData->pckt)[o], partsize);  

  CrFwCmpExecute(outCmp); 
  if (CrPsLptDownInterRepRepeatCheck(outCmp) != 0)
    return 0;
  CrPsExecServLptSm();
  
  /* get the data from the outCmp (4th Packet)*/
  memcpy(&memArray2get[partsize*3], &((uint8_t*)cmpSpecificData->pckt)[o], partsize);  

  /* Get the Data from the out Manager */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[2];
  outCmpData = (CrFwCmpData_t*)FwSmGetData(outCmp);
  cmpSpecificData = (CrFwOutCmpData_t*)(outCmpData->cmpSpecificData);

  /* Check if there is a 13,1 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 13)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 3)
    return 0;

  CrFwCmpExecute(outCmp); 

  /* get the data from the outCmp (last Packet)*/
  memcpy(&memArray2get[partsize*4], &((uint8_t*)cmpSpecificData->pckt)[o], (CrFwPcktGetLength(cmpSpecificData->pckt) - o - CRC_LENGTH));

  /* Test the memory */
  /* Check if the Data is stored in the Buffer correctly*/
  if (memcmp(memArray2set, memArray2get, LPTSIZE))
  {
    return 0;
  }

  /* Allocate a 13,130 Packet */
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,13);
  CrFwPcktSetServSubType(pckt,130);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 
  /* set TID = 0  TODO*/

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* run the start action, the progress action and the termination action */
  CrPsLptAbortDownCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptAbortDownCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptAbortDownCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Allocate a 13,129 Packet */
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,13);
  CrFwPcktSetServSubType(pckt,129);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 
  setLptStartDownCmdTid(pckt, LptBufferId);

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  CrFwCmpExecute(inCmd); 
  CrPsExecServLptSm();

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Get the Data from the out Manager (there is only one Component) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];
  
  /* Check if there is a 13,1 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 13)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 1)
    return 0;

  /* Execute the inCmd */
  CrFwCmpExecute(outCmp); 
  CrPsExecServLptSm();

  /* Get the Data from the out Manager (there is only one Component) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[1];

  /* Check if there is a 13,1 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 13)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 2)
    return 0;
  
  /* Execute the OutComponent and the Statemachine */
  CrFwCmpExecute(outCmp); 
  CrPsExecServLptSm();
  
  /* Execute the OutComponent and the Śtatemachine */
  CrFwCmpExecute(outCmp); 
  CrPsExecServLptSm();

  /* Fill the outfactory so that an Error could occur (leave one free slot) */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-6;i++)
  {
    outCmpArr[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
  }

  /* Execute the outCmp and the Statemachine */
  CrFwCmpExecute(outCmp); 
  CrPsExecServLptSm();

  /* Check if an OutComponent allocation error occures */
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /* Reset application error Corde */
  CrFwSetAppErrCode(crNoAppErr);

  /* Release all outcomponents, that have been created to fill the outfactory */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-6;i++)
  { 
    CrFwOutFactoryReleaseOutCmp(outCmpArr[i]);
  }

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Reset OutManager and check that all OutComponents are unloaded and released */
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  /* Reset the OutFactory */
  CrFwCmpReset(outFactory);  
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Reset the InFactory and check that no InCommands are allocated */
  CrFwCmpReset(inFactory);
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  return 1;
}

CrFwBool_t CrPsLptTestCase4()
{
  /* Check Service 13 Down-Link*/
  FwSmDesc_t inFactory, outFactory, outManager, outCmp, outCmpArr[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP], inCmd;
  CrFwCmpData_t *outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  CrFwPckt_t pckt;
  uint32_t i;
  CrFwTimeStamp_t tim;
  uint32_t LptBufferId;
  LptBufferId = 0;
  tim.t[0]=255u;
  tim.t[1]=255u;
  tim.t[2]=255u;
  tim.t[3]=255u;
  tim.t[4]=255u;
  tim.t[5]=255u;

  /* Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines */
  CrPsInitServLpt();

  /* Instantiate the OutFactory, InFactory and OutManager*/
  outFactory = CrFwOutFactoryMake();
  if (outFactory == NULL)
    return 0;
  if (FwSmCheckRec(outFactory) != smSuccess)
    return 0;

  inFactory = CrFwInFactoryMake();
  if (inFactory == NULL)
    return 0;
  if (FwSmCheckRec(inFactory) != smSuccess)
    return 0;

  outManager = CrFwOutManagerMake(0);
  if (outManager == NULL)
    return 0;
  if (FwSmCheckRec(outManager) != smSuccess)
    return 0;

  /* Initialize and Configure OutFactory, InFactory and Outmanager and check success */
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;
  
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  if (!CrFwCmpIsInConfigured(inFactory))
    return 0;

  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  if (!CrFwCmpIsInConfigured(outManager))
    return 0; 

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  setDplptRemSizeItem(LptBufferId,0);
  if (CrPsLptIsTransferFinished(0) != 1)
    return 0;
  setDplptRemSizeItem(LptBufferId,2);
  if (CrPsLptIsTransferFinished(0) != 0)
    return 0;
  setDplptFailCodeItem(LptBufferId,1);
  if (CrPsLptIsFailed(0) != 1)
    return 0;
  setDplptFailCodeItem(LptBufferId,LPT_FAILCODE_NO_FAIL);
  if (CrPsLptIsFailed(0) != 0)
    return 0;

  setDplptTimeItem(LptBufferId, tim);
  CrPsLptUpTransferDoAction(0);
  if (getDplptFailCodeItem(LptBufferId) != LPT_FAILCODE_TIME_OUT)
    return 0;  

  /* Allocate a 13,10 Packet */
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,13);
  CrFwPcktSetServSubType(pckt,10);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 
  setLptUpInterCmdTid(pckt, 0);
  setLptUpInterCmdPartSeqNmb(pckt, 9);
  setLptUpInterCmdPart(pckt, 1, 4);

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  CrFwCmpExecute(inCmd);

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);
  
  /*look if there is an 13,16 waiting*/
  /* Get the Data from the out Manager (there is only one Component) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];

  /* Check if there is a 13,1 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 4)
    return 0;

  /* Allocate a 13,9 Packet */
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,13);
  CrFwPcktSetServSubType(pckt,9);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 
  setLptUpFirstCmdTid(pckt, 0);
  setLptUpFirstCmdPartSeqNmb(pckt, 1);
  setLptUpFirstCmdPart(pckt, 1, 4);

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  CrFwCmpExecute(inCmd);

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);
  
/* Allocate a 13,129 Packet */
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,13);
  CrFwPcktSetServSubType(pckt,129);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  CrFwCmpExecute(inCmd);

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*look if there is an 13,16 waiting*/
  /* Get the Data from the out Manager (there is only one Component) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[1];

  /* Check if there is a 13,1 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 4)
    return 0;

  /* Allocate a 13,10 Packet */
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,13);
  CrFwPcktSetServSubType(pckt,10);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 
  setLptUpInterCmdTid(pckt, 0);
  setLptUpInterCmdPartSeqNmb(pckt, 19);
  setLptUpInterCmdPart(pckt, 1, 4);

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  CrFwCmpExecute(inCmd);

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*look if there is an 13,16 waiting*/
  /* Get the Data from the out Manager (there is only one Component) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[2];

  /* Check if there is a 13,1 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 4)
    return 0;

  /* Allocate a 13,130 Packet */
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,13);
  CrFwPcktSetServSubType(pckt,130);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  CrFwCmpExecute(inCmd);

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*look if there is an 13,16 waiting*/
  /* Get the Data from the out Manager (there is only one Component) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[3];

  /* Check if there is a 13,1 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 4)
    return 0;

  /* Execute the CrPsLptLoadReport Function */
  CrPsLptLoadReport(0);

  /*look if there is an 13,16 waiting*/
  /* Get the Data from the out Manager (there is only one Component) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[4];

  /* Check if there is a 13,1 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 13)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 16)
    return 0;

  /* Fill the outfactory so that an Error could occur (leave one free slot) */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-4;i++)
  {
    outCmpArr[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
  }

  /* Execute the CrPsLptLoadReport Function */
  CrPsLptLoadReport(0);

  /* Check if an OutComponent allocation error occures */
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /* Reset application error Corde */
  CrFwSetAppErrCode(crNoAppErr);

  CRFW_UNUSED(outCmpArr);

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Reset OutManager and check that all OutComponents are unloaded and released */
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  /* Reset the OutFactory */
  CrFwCmpReset(outFactory);  
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Reset the InFactory and check that no InCommands are allocated */
  CrFwCmpReset(inFactory);
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Create a 13,1 OutComponent to get outcome success*/
  outCmp = CrFwOutFactoryMakeOutCmp(13,1,0,80);

  /*run the Enable Check and Update Action */
  CrPsLptDownFirstRepEnableCheck(outCmp);
  CrPsLptDownFirstRepUpdateAction(outCmp);
  
  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Create a 13,3 OutComponent to get outcome success*/
  outCmp = CrFwOutFactoryMakeOutCmp(13,3,0,80);

  setDplptRemSizeItem(0, 10);

  /*run the Enable Check and Update Action */
  CrPsLptDownLastRepEnableCheck(outCmp);

  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Reset OutManager and check that all OutComponents are unloaded and released */
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  /* Reset the OutFactory */
  CrFwCmpReset(outFactory);  
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Reset the InFactory and check that no InCommands are allocated */
  CrFwCmpReset(inFactory);
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  return 1;
}





