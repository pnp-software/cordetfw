/**
 * @file CrPsLptTestCases.c
 *
 * Implementation of test cases for Service Components.
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

#include "CrFwRepErrStub.h"
#include "CrFwInStreamSocket.h"
#include "CrFwClientSocket.h"
#include "CrFwServerSocket.h"
#include "CrFwOutStreamSocket.h"
#include "CrFwInStreamTestCases.h"
#include "CrFwRepInCmdOutcomeStub.h"
#include "CrFwInStreamStub.h"
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
#include <Services/General/CrPsPktServLpt.h>
#include <Services/General/CrPsPktServLptSupp.h>
#include <DataPool/CrPsDpServLpt.h>
#include "CrPsUserConstants.h"

/* Include system files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "CrPsDebug.h"


/* TODO: Abort Up transfer */
/* TODO: start downtransfair when statemachine is not INACTIVE*/
/* TODO: start CrPsLptDownLastRepEnableCheck when tatemachine is in state CrPsLpt_DOWN_TRANSFER*/ 
/* TODO: start CrPsLptDownInterRepRepeatCheck when etDplptRemSizeItem(LptBufferId) < CR_FW_MAX_PCKT_LENGTH - 26)*/






/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsLptTestCase1()
{
  /* Check Service 13 */
  FwSmDesc_t inFactory, outFactory, outManager, outCmp, inCmd;
  CrFwPckt_t pckt;
  CrFwCmpData_t *cmpData;

  /* Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines */
  DEBUGP_TS13("Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines \n");
  CrPsInitServLpt();

  /* Instantiate the OutFactory, InFactory and OutManager*/
  DEBUGP_TS13("Instantiate the OutFactory, InFactory and OutManager  \n");
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
  DEBUGP_TS13("Initialize and Configure OutFactory, InFactory and Outmanager and check success \n");
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
  DEBUGP_TS13("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Create a 13,1 OutComponent to get outcome success*/
  DEBUGP_TS13("Allocating a 13,1 OutComponent \n");
  outCmp = CrFwOutFactoryMakeOutCmp(13,1,0,80);

  /*run the Enable Check and Update Action */
  CrPsLptDownFirstRepEnableCheck(outCmp);

  CrPsLptDownFirstRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  
  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Create a 13,2 OutComponent to get outcome success*/
  DEBUGP_TS13("Allocating a 13,2 OutComponent \n");
  outCmp = CrFwOutFactoryMakeOutCmp(13,2,0,80);

  /*run the Enable Check and Update Action */
  CrPsLptDownInterRepEnableCheck(outCmp);

  CrPsLptDownInterRepRepeatCheck(outCmp);

  CrPsLptDownInterRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  
  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

    /* Create a 13,3 OutComponent to get outcome success*/
  DEBUGP_TS13("Allocating a 13,3 OutComponent \n");
  outCmp = CrFwOutFactoryMakeOutCmp(13,3,0,80);

  setDplptRemSizeItem(0, 10);

  /*run the Enable Check and Update Action */
  CrPsLptDownLastRepEnableCheck(outCmp);

  CrPsLptDownLastRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  
  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Allocate a 13,9 Packet */
  DEBUGP_TS13("Allocating a 13,9 Packet \n");
  pckt = CrFwPcktMake(80);
  clearPacket(pckt, 80);
  CrFwPcktRelease(pckt);
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
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpFirstCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpFirstCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);
  
  /* Allocate a 13,10 Packet */
  DEBUGP_TS13("Allocating a 13,10 Packet \n");
  pckt = CrFwPcktMake(80);
  clearPacket(pckt, 80);
  CrFwPcktRelease(pckt);
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
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpInterCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpInterCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);
  
  /* Allocate a 13,11 Packet */
  DEBUGP_TS13("Allocating a 13,11 Packet \n");
  pckt = CrFwPcktMake(80);
  clearPacket(pckt, 80);
  CrFwPcktRelease(pckt);
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
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpLastCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpLastCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Create a 13,16 OutComponent to get outcome success*/
  DEBUGP_TS13("Allocating a 13,16 OutComponent \n");
  outCmp = CrFwOutFactoryMakeOutCmp(13,16,0,80);

  /*run the Enable Check and Update Action */
  CrPsLptUpAbortRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  
  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

 /* Allocate a 13,129 Packet */
  DEBUGP_TS13("Allocating a 13,129 Packet \n");
  pckt = CrFwPcktMake(80);
  clearPacket(pckt, 80);
  CrFwPcktRelease(pckt);
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
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptStartDownCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptStartDownCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

 /* Allocate a 13,130 Packet */
  DEBUGP_TS13("Allocating a 13,130 Packet \n");
  pckt = CrFwPcktMake(80);
  clearPacket(pckt, 80);
  CrFwPcktRelease(pckt);
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
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptAbortDownCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptAbortDownCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check application errors */
  DEBUGP_TS13("Check application errors\n");
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  return 1;
}




CrFwBool_t CrPsLptTestCase2()
{
  /* Check Service 13 */
  FwSmDesc_t inFactory, outFactory, outManager, inCmd, outCmp, outCmpArr[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];
  CrFwCmpData_t *outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  CrFwPckt_t pckt;
  CrFwCmpData_t *cmpData;
  uint32_t i, PartSeqNmb;

  /* Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines */
  DEBUGP_TS13("Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines \n");
  CrPsInitServLpt();
  /* Instantiate the OutFactory, InFactory and OutManager*/
  DEBUGP_TS13("Instantiate the OutFactory, InFactory and OutManager  \n");
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
  DEBUGP_TS13("Initialize and Configure OutFactory, InFactory and Outmanager and check success \n");
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
  DEBUGP_TS13("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

 /* Allocate a 13,129 Packet */
  DEBUGP_TS13("Allocating a 13,129 Packet \n");
  pckt = CrFwPcktMake(80);
  clearPacket(pckt, 80);
  CrFwPcktRelease(pckt);
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
  printf("asdfasdf\n");
  /* Fill the outfactory so that an Error could occur (leave one free slot) */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
  {
    outCmpArr[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
  }

  /* Execute the inCmd */
  CrFwCmpExecute(inCmd); 
  CrPsExecServLptSm();

printf("asdfasdf\n");
  /*Check if an OutComponent allocation Error occures*/
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;
printf("asdfasdf\n");
  /*Reset application error Corde*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Release all outcomponents, that have been created to fill the outfactory */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
  { 
    CrFwOutFactoryReleaseOutCmp(outCmpArr[i]);
  }

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

 /* Fill the outfactory so that an Error could occur (leave one free slot) */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-2;i++)
  {
    outCmpArr[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
  }

  /* Execute the inCmd */
  CrFwCmpExecute(outCmp); 
  CrPsExecServLptSm();

  PartSeqNmb = getDppartSeqNmbItem(0);
  PartSeqNmb-=1;
  setDppartSeqNmbItem(0, PartSeqNmb);

  /*Check if an OutComponent allocation Error occures*/
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /*Reset application error Corde*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Release all outcomponents, that have been created to fill the outfactory */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-2;i++)
  { 
    CrFwOutFactoryReleaseOutCmp(outCmpArr[i]);
  }

  /* Execute the OutComponent */
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
  
  /* Execute the OutComponent */
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

  /* Execute the OutComponent */
  CrFwCmpExecute(outCmp); 
  CrPsExecServLptSm();

  /* Get the Data from the out Manager (there is only one Component) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[2];
 
  /* Check if there is a 13,1 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 13)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 3)
    return 0;

  /* Execute the OutComponent */
  CrFwCmpExecute(outCmp); 

  /* Allocate a 13,130 Packet */
  DEBUGP_TS13("Allocating a 13,130 Packet \n");
  pckt = CrFwPcktMake(80);
  clearPacket(pckt, 80);
  CrFwPcktRelease(pckt);
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
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptAbortDownCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptAbortDownCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

 /* Allocate a 13,129 Packet */
  DEBUGP_TS13("Allocating a 13,129 Packet \n");
  pckt = CrFwPcktMake(80);
  clearPacket(pckt, 80);
  CrFwPcktRelease(pckt);
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
  
  /* Execute the OutComponent */
  CrFwCmpExecute(outCmp); 
  CrPsExecServLptSm();
  
  /* Execute the OutComponent */
  CrFwCmpExecute(outCmp); 
  CrPsExecServLptSm();

  /* Fill the outfactory so that an Error could occur (leave one free slot) */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-6;i++)
  {
    outCmpArr[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
  }

  /* Execute the inCmd */
  CrFwCmpExecute(outCmp); 
  CrPsExecServLptSm();

  /*Check if an OutComponent allocation Error occures*/
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /*Reset application error Corde*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Release all outcomponents, that have been created to fill the outfactory */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-6;i++)
  { 
    CrFwOutFactoryReleaseOutCmp(outCmpArr[i]);
  }


  /* Check application errors */
  DEBUGP_TS13("Check application errors\n");
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Reset OutManager and check that all OutComponents are unloaded and released */
  DEBUGP_TS13("Reset OutManager and check that all OutComponents are unloaded and released \n");
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  /* Reset the OutFactory */
  DEBUGP_TS13("Reset the OutFactory and check that no OutComponents are allocated \n");
  CrFwCmpReset(outFactory);  
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Reset the InFactory and check that no InCommands are allocated */
  DEBUGP_TS13("Reset the InFactory and check that no InCommands are allocated \n");
  CrFwCmpReset(inFactory);
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check application errors */
  DEBUGP_TS13("Check application errors\n");
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  return 1;
}






CrFwBool_t CrPsLptTestCase3()
{
  /* Check Service 13 */
  FwSmDesc_t inFactory, outFactory, outManager, inCmd;
  CrFwPckt_t pckt;
  CrFwCmpData_t *cmpData;

  /* Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines */
  DEBUGP_TS13("Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines \n");
  CrPsInitServLpt();
  /* Instantiate the OutFactory, InFactory and OutManager*/
  DEBUGP_TS13("Instantiate the OutFactory, InFactory and OutManager  \n");
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
  DEBUGP_TS13("Initialize and Configure OutFactory, InFactory and Outmanager and check success \n");
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
  DEBUGP_TS13("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a 13,9 Packet */
  DEBUGP_TS13("Allocating a 13,9 Packet \n");
  pckt = CrFwPcktMake(1000);
  clearPacket(pckt, 1000);
  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(1000);
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

  setLptUpFirstCmdTid(pckt, 0);
  setLptUpFirstCmdPartSeqNmb(pckt, 1);
  setLptUpFirstCmdPart(pckt, 1, 4);



  /* run the start action, the progress action and the termination action */
  CrPsLptUpFirstCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpFirstCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpFirstCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

//  CrFwCmpExecute(inCmd);
  CrPsExecServLptSm();

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);
  
  /* Allocate a 13,10 Packet */
  DEBUGP_TS13("Allocating a 13,10 Packet \n");
  pckt = CrFwPcktMake(80);
  clearPacket(pckt, 80);
  CrFwPcktRelease(pckt);
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
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpInterCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpInterCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsExecServLptSm();

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);
  
  /* Allocate a 13,11 Packet */
  DEBUGP_TS13("Allocating a 13,11 Packet \n");
  pckt = CrFwPcktMake(80);
  clearPacket(pckt, 80);
  CrFwPcktRelease(pckt);
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
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpLastCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsLptUpLastCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS13("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsExecServLptSm();


  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);



  return 1;
}
