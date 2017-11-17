/**
 * @file
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
#include <CrPsUtilitiesServEvt.h>
#include <CrPsUtilitiesServReqVerif.h>
#include "config/CrFwOutFactoryUserPar.h"
#include <Services/EventReporting/OutCmp/CrPsEvtRep.h>
#include <Services/EventReporting/OutCmp/CrPsEvtRepDisabledRep.h>
#include <Services/EventReporting/InCmd/CrPsEvtEnableCmd.h>
#include <Services/EventReporting/InCmd/CrPsEvtDisableCmd.h>
#include <Services/EventReporting/InCmd/CrPsEvtRepDisabledCmd.h>
#include <Services/General/CrPsPktServEvt.h>
#include <Services/General/CrPsPktServEvtSupp.h>

/* Include system files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "CrPsDebug.h"

#define TESTNMB 10

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsEvtTestCase1()
{
  /* Check Service 5 */
  FwSmDesc_t inFactory, outFactory, outManager, inCmd, outCmp, outCmpArr[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];
  CrFwCmpData_t *outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  CrFwPckt_t pckt;
  CrPsNumberU4_t nmbr;
  CrFwCmpData_t *cmpData;
  uint32_t i;

  /* Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines */
  DEBUGP_TS5("Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines \n");
  CrPsInitServEvt();

  /* Instantiate the OutFactory, InFactory and OutManager*/
  DEBUGP_TS5("Instantiate the OutFactory, InFactory and OutManager  \n");
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
  DEBUGP_TS5("Initialize and Configure OutFactory, InFactory and Outmanager and check success \n");
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
  DEBUGP_TS5("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Create a 5,1 Packet to get outcome success*/
  DEBUGP_TS5("Allocating a 5,1 Packet \n");
  outCmp = CrFwOutFactoryMakeOutCmp(5,1,1,80);

  /*run the Enable Check and Update Action and check for change of datapool variable*/
  nmbr = getDpnOfDetectedEvts_1();
  CrPsEvtRepEnableCheck(outCmp);
  if (getDpnOfDetectedEvts_1() == nmbr)
    return 0;

  nmbr = getDpnOfGenEvtRep_1();
  CrPsEvtRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  DEBUGP_TS5("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  if (getDpnOfGenEvtRep_1() == nmbr)
    return 0;
  
  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Create a 5,2 Packet to get outcome success*/
  DEBUGP_TS5("Allocating a 5,2 Packet \n");
  outCmp = CrFwOutFactoryMakeOutCmp(5,2,1,80);

  /*run the Enable Check and Update Action and check for change of datapool variable*/
  nmbr = getDpnOfDetectedEvts_2();
  CrPsEvtRepEnableCheck(outCmp);
  if (getDpnOfDetectedEvts_2() == nmbr)
    return 0;

  nmbr = getDpnOfGenEvtRep_2();
  CrPsEvtRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  DEBUGP_TS5("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  if (getDpnOfGenEvtRep_2() == nmbr)
    return 0;

  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Create a 5,3 Packet to get outcome success*/
  DEBUGP_TS5("Allocating a 5,3 Packet \n");
  outCmp = CrFwOutFactoryMakeOutCmp(5,3,1,80);

  /*run the Enable Check and Update Action and check for change of datapool variable*/
  nmbr = getDpnOfDetectedEvts_3();
  CrPsEvtRepEnableCheck(outCmp);
  if (getDpnOfDetectedEvts_3() == nmbr)
    return 0;

  nmbr = getDpnOfGenEvtRep_3();
  CrPsEvtRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  DEBUGP_TS5("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  if (getDpnOfGenEvtRep_3() == nmbr)
    return 0;

  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Create a 5,4 Packet to get outcome success*/
  DEBUGP_TS5("Allocating a 5,4 Packet \n");
  outCmp = CrFwOutFactoryMakeOutCmp(5,4,1,80);

  /*run the Enable Check and Update Action and check for change of datapool variable*/
  nmbr = getDpnOfDetectedEvts_4();
  CrPsEvtRepEnableCheck(outCmp);
  if (getDpnOfDetectedEvts_4() == nmbr)
    return 0;

  nmbr = getDpnOfGenEvtRep_4();
  CrPsEvtRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  DEBUGP_TS5("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  if (getDpnOfGenEvtRep_4() == nmbr)
    return 0;

  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Create a 5,8 Packet to trigger an error and get coverage*/
  DEBUGP_TS5("Allocating a 5,8 Packet \n");
  outCmp = CrFwOutFactoryMakeOutCmp(5,8,0,80);

  /*run the Enable Check and update Action for coverage */
  CrPsEvtRepEnableCheck(outCmp);
  CrPsEvtRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  DEBUGP_TS5("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Allocate a 5,5 Packet to get outcome success all valid EID's*/
  DEBUGP_TS5("Allocating a 5,5 Packet \n");
  pckt = CrFwPcktMake(80);
  clearPacket(pckt, 80);
  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,5);
  CrFwPcktSetServSubType(pckt,5);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 

  setEvtEnableCmdN(pckt, 5);
  setEvtEnableCmdEventIdItem(pckt, 1, 1);
  setEvtEnableCmdEventIdItem(pckt, 2, 2);
  setEvtEnableCmdEventIdItem(pckt, 3, 3);
  setEvtEnableCmdEventIdItem(pckt, 4, 4);
  setEvtEnableCmdEventIdItem(pckt, 5, 5);

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* manually set datapool values of disabled EID's */
  setDpnOfDisabledEid_1(TESTNMB);
  setDpnOfDisabledEid_2(TESTNMB);
  setDpnOfDisabledEid_3(TESTNMB);
  setDpnOfDisabledEid_4(TESTNMB);

  /* run the start action, the progress action and the termination action */
  CrPsEvtEnableCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS5("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsEvtEnableCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS5("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsEvtEnableCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS5("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Check if Datapool Values change accordingly */
  if (getDpnOfDisabledEid_1() != TESTNMB-2)
    return 0;
  if (getDpnOfDisabledEid_2() != TESTNMB-1)
    return 0;
  if (getDpnOfDisabledEid_3() != TESTNMB-1)
    return 0;
  if (getDpnOfDisabledEid_4() != TESTNMB-1)
    return 0;

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Allocate a 5,5 Packet to get outcome failure only wrong EID's*/
  DEBUGP_TS5("Allocating a 5,5 Packet \n");
  pckt = CrFwPcktMake(80);
  clearPacket(pckt, 80);
  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,5);
  CrFwPcktSetServSubType(pckt,5);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 

  setEvtEnableCmdN(pckt, 5);
  setEvtEnableCmdEventIdItem(pckt, 1, 10);
  setEvtEnableCmdEventIdItem(pckt, 2, 20);
  setEvtEnableCmdEventIdItem(pckt, 3, 30);
  setEvtEnableCmdEventIdItem(pckt, 4, 40);
  setEvtEnableCmdEventIdItem(pckt, 5, 50);

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  CrPsEvtEnableCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS5("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != VER_EID_START_FD)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Get the Data from the out Manager (there is only one Component) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];
  
  /* Check if there is a 3,25 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 4)
    return 0;
  if (CrFwOutCmpGetDiscriminant(outCmp) != VER_ILL_EID)
    return 0;

  /*Release the OutComponent and reset the outmanager*/
  CrFwOutFactoryReleaseOutCmp(outCmp);
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;
  
  /*Check if an OutComponent Release Error occures*/
  if (CrFwGetAppErrCode() != crOutCmpRelErr)
    return 0;

  /*Reset application error Corde*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Allocate a 5,6 Packet to get outcome success*/
  DEBUGP_TS5("Allocating a 5,6 Packet \n");
  pckt = CrFwPcktMake(80);
  clearPacket(pckt, 80);
  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,5);
  CrFwPcktSetServSubType(pckt,6);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 

  setEvtDisableCmdN(pckt, 5);
  setEvtDisableCmdEventIdItem(pckt, 1, 1);
  setEvtDisableCmdEventIdItem(pckt, 2, 2);
  setEvtDisableCmdEventIdItem(pckt, 3, 3);
  setEvtDisableCmdEventIdItem(pckt, 4, 4);
  setEvtDisableCmdEventIdItem(pckt, 5, 5);

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  CrPsEvtDisableCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS5("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsEvtDisableCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS5("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsEvtDisableCmdTerminationAction(inCmd);  
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  DEBUGP_TS5("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check if Datapool Values change accordingly */
  if (getDpnOfDisabledEid_1() != TESTNMB)
    return 0;
  if (getDpnOfDisabledEid_2() != TESTNMB)
    return 0;
  if (getDpnOfDisabledEid_3() != TESTNMB)
    return 0;
  if (getDpnOfDisabledEid_4() != TESTNMB)
    return 0;

  /* Allocate a 5,7 Packet to get outcome success*/
  DEBUGP_TS5("Allocating a 5,7 Packet \n");
  pckt = CrFwPcktMake(80);
  clearPacket(pckt, 80);
  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,5);
  CrFwPcktSetServSubType(pckt,7);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  CrPsEvtRepDisabledCmdStartAction(inCmd);
    DEBUGP_TS5("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsEvtRepDisabledCmdProgressAction(inCmd);
    DEBUGP_TS5("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  CrPsEvtRepDisabledCmdTerminationAction(inCmd);
    DEBUGP_TS5("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Get the Data from the out Manager (there is only one Component) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];
  
  /* Check if there is a 3,25 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 5)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 8)
    return 0;

  /*Release the OutComponent and reset the outmanager*/
  CrFwOutFactoryReleaseOutCmp(outCmp);
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;
  
  /*Check if an OutComponent Release Error occures*/
  if (CrFwGetAppErrCode() != crOutCmpRelErr)
    return 0;

  /*Reset application error Corde*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Allocate a 5,7 Packet to get outcome Outfactory Failure*/
  DEBUGP_TS5("Allocating a 5,7 Packet \n");
  pckt = CrFwPcktMake(80);
  clearPacket(pckt, 80);
  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,5);
  CrFwPcktSetServSubType(pckt,7);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Fill the outfactory so that an Error could occur (leave one free slot) */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
  {
    outCmpArr[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
  }

  CrPsEvtRepDisabledCmdStartAction(inCmd);
    DEBUGP_TS5("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 0)
  {
    return 0;
  }

  /*Check if an OutComponent allocation Error occures*/
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /*Reset application error Corde*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Release all outcomponents, that have been created to fill the outfactory */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
  { 
    CrFwOutFactoryReleaseOutCmp(outCmpArr[i]);
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);


  /* Allocate a 5,7 Packet to trigger an error in the enable start procedure*/
  DEBUGP_TS5("Allocating a 5,7 Packet \n");
  pckt = CrFwPcktMake(80);
  clearPacket(pckt, 80);
  CrFwPcktRelease(pckt);
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,5);
  CrFwPcktSetServSubType(pckt,7);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0); 

  setEvtEnableCmdN(pckt, 5);
  setEvtEnableCmdEventIdItem(pckt, 1, 1);
  setEvtEnableCmdEventIdItem(pckt, 2, 2);
  setEvtEnableCmdEventIdItem(pckt, 3, 3);
  setEvtEnableCmdEventIdItem(pckt, 4, 4);
  setEvtEnableCmdEventIdItem(pckt, 5, 5);

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  CrPsEvtEnableCmdStartAction(inCmd);
  DEBUGP_TS5("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != VER_EID_START_FD)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Create a 5,8 Packet to get outcome success*/
  DEBUGP_TS5("Allocating a 5,8 Packet \n");
  outCmp = CrFwOutFactoryMakeOutCmp(5,8,0,80);

  /*run the Update Action and check for outcome = success*/
  CrPsEvtRepDisabledRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  DEBUGP_TS3("Outcome = %d \n", cmpData->outcome);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
  
  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Reset OutManager and check that all OutComponents are unloaded and released */
  DEBUGP_TS5("Reset OutManager and check that all OutComponents are unloaded and released \n");
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  /* Reset the OutFactory */
  DEBUGP_TS5("Reset the OutFactory and check that no OutComponents are allocated \n");
  CrFwCmpReset(outFactory);  
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Reset the InFactory and check that no InCommands are allocated */
  DEBUGP_TS5("Reset the InFactory and check that no InCommands are allocated \n");
  CrFwCmpReset(inFactory);
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check application errors */
  DEBUGP_TS5("Check application errors\n");
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  return 1;
}

