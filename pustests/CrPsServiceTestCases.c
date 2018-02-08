/**
 * @file CrPsServiceTestCases.c
 * @ingroup PUSTestsuite
 *
 * @brief Implementation of test cases for the Test Service Components.
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
#include "Services/Test/InCmd/CrPsTestAreYouAliveConnection.h"
#include "Services/Test/OutCmp/CrPsTestAreYouAliveConnectionRep.h"
#include "Services/Test/InRep/CrPsTestAreYouAliveConnectInRep.h"
#include "Services/Test/InCmd/CrPsTestOnBoardConnection.h"
#include "Services/Test/Procedures/CrPsCmd17s3StartCreate.h"
#include "Services/Test/Procedures/CrPsCmd17s3PrgrCreate.h"
#include "DataPool/CrPsDpServTest.h"
#include <Services/General/CrPsPktServTest.h>
#include <CrPsUtilitiesServTest.h>
#include <CrPsUtilitiesServReqVerif.h>
#include "config/CrFwOutFactoryUserPar.h"

/* Include system files */
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsServTestConnTestCase1()
{
  /* Check 17,1 and 17,2 */
  FwSmDesc_t inFactory, outFactory, outManager, inCmd, outCmp, outCmpArr[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];
  CrFwPckt_t pckt;
  CrFwCmpData_t* outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  uint16_t i;
  
  /* run all getters for the procedure descriptors*/
  CrPsInitServTest();
  CrPsExecServTest();
  CrPsInitServReqVerif();

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

  /* Initialize and Configure OutFactory and check success */
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;
  
  /* Initialize and Configure InFactory and check success */
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  if (!CrFwCmpIsInConfigured(inFactory))
    return 0;

  /* Initialize and Configure OutManager and check success */
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  if (!CrFwCmpIsInConfigured(outManager))
    return 0; 

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a 17,1 Packet */
  pckt = CrFwPcktMake(20);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,1);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,2);  

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 17,1 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 17)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 1)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Check if number of Allocated OutComponents = 0*/
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Execute the InCommand  */
  CrFwCmpExecute(inCmd); 
  
  /*check that the InCommand is in PROGRESS state*/
  if (!CrFwInCmdIsInProgress(inCmd))
    return 0;  

  /* Check if number of Allocated Packets now is 2*/
  if (CrFwPcktGetNOfAllocated() != 2)
    return 0;

  /* Check if number of Allocated OutComponents now is 1 */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /*Get the Data from the out Manager (there is only one Component)*/
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];

  /*Check if there is a 17,2 Report waitig in the OutManager*/
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 17)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 2)
    return 0;

  /*Terminate the InCommand*/
  CrFwInCmdTerminate(inCmd); 

  /*Check if the InCommand is in TERMINATED state*/
  if (!CrFwInCmdIsInTerminated(inCmd))
    return 0;

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Execute the OutComponent (17,2) */
  CrFwCmpExecute(outCmp); 

  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a 17,1 Packet */
  pckt = CrFwPcktMake(20);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,1);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,1,1,1,1);  
  CrFwPcktSetSeqCnt(pckt,2);  

  /*Creating an InCommand out of the 17,1 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Fill the outfactory so that an Error could occur (leave one free slot) */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
  {
    outCmpArr[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
  }

  /* Execute the InCommand  */
  CrFwCmpExecute(inCmd); 

  /* Check application errors */
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /*Reset application error Code*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Release all outcomponents, that have been created to fill the outfactory */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
  { 
    CrFwOutFactoryReleaseOutCmp(outCmpArr[i]);
  }

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Reset OutManager and check that all OutComponents are unloaded and released */
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;
  
  /*Here the ErrorCode gets 11, because there are no outcomponents in the OutManager*/
  CrFwSetAppErrCode(crNoAppErr);

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

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrPsServTestConnTestCase2()
{
  /* Check 17,3 and 17,4 */
  FwSmDesc_t inFactory, inManager, outFactory, outManager, inCmd, outCmp, outCmp1, inRep1;
  CrFwPckt_t pckt, pckt2;
  CrFwCmpData_t* outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  CrPsApid_t appId;
  appId = 60;

  /* Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines */
  CrPsInitServTest();
  CrPsInitServReqVerif();
  /*Initialize Applications  */
  CrPsInitServTestApp(appId);
  CrPsInitServTestApp(200);

  /* Instantiate the OutFactory, InFactory, OutManager and inManager */
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

  inManager = CrFwInManagerMake(0);
  if (inManager == NULL)
    return 0;
  if (FwSmCheckRec(inManager) != smSuccess)
    return 0;
  
  /* Initialize and Configure OutFactory and check success */
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;
  
  /* Initialize and Configure InFactory and check success */
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  if (!CrFwCmpIsInConfigured(inFactory))
    return 0;

  /* Initialize and Configure OutManager and check success */
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  if (!CrFwCmpIsInConfigured(outManager))
    return 0; 

  /* Initialize and Configure InManager and check success */
  CrFwCmpInit(inManager);
  CrFwCmpReset(inManager);
  if (!CrFwCmpIsInConfigured(inManager))
    return 0; 

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a 17,3 Packet with a wrong AppId*/
  pckt = CrFwPcktMake(20);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetSrc(pckt,3);
  CrFwPcktSetDest(pckt,3);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);
  CrFwPcktSetSeqCnt(pckt,2);

  /*give the Packet a wrong appId so the process fails*/
  appId = 88;
  setOnBoardConnectCmdAppId(pckt, appId);
  appId = 60;

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 17,3 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 17)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 3)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Check if number of Allocated OutComponents = 0*/
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Execute the InCommand  */
  /* The inCommand has no Parameter for the Destination set so it should abort!*/
  CrFwCmpExecute(inCmd); 

  /*Check that the InCommand is in the State ABORTED*/
  if (!CrFwInCmdIsInAborted(inCmd))
    return 0; 

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check if number of Allocated Packets now is 1 - a Request Verification (1,4) should be in the Outmanager */
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check that there is one Packet Pending in the OutManager - Request Verification (1,4) */
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager is 1 - Request Verification (1,4)*/
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 1)
    return 0;

  /* Get the Data from the out Manager (there is only one Component) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];

  /* Check if there is a 1,4 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 4)
    return 0;

  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Reset the OutManager (this should clear the POCL and release all OutComponents) */
  CrFwCmpReset(outManager);

  /* Check and reset application error code */
  if (CrFwGetAppErrCode() != crOutCmpRelErr)
   return 0;
  CrFwSetAppErrCode(crNoAppErr);
  if (!CrFwCmpIsInConfigured(outManager))
    return 0;
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 0)
    return 0;

  /* Check if number of Allocated OutComponents now is 0 */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check if number of Allocated Packets now is 0 */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a 17,3 Packet */
  pckt = CrFwPcktMake(20);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,2);

  /*give the Packet a correct appId so the process should success*/
  setOnBoardConnectCmdAppId(pckt, appId);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 17,3 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Check if number of Allocated InCommands now in the InFactory is 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;
  
  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 17)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 3)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Check if number of Allocated OutComponents = 0*/
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Execute the InCommand  */
  /* The inCommand has now a correct Parameter for the Destination */
  CrFwCmpExecute(inCmd); 

  /* Check if now 3 Packets are Allocated
   * one InCommand we just created and executed
   * one InCommand (17,1) to the application that was specified in the parameter of the 17,3 packet
   * and a Packet holding the 17,4 Report is allocated (outManager Pending)
   */
  if (CrFwPcktGetNOfAllocated() != 3)
    return 0;

  /* Check if number of Allocated InCommands in the InFactory stays at 1 */
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager is 1 */
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 1)
    return 0;

  /* Get the Data from the out Manager (there is only one Component) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];

  /* Check if there is a 17,1 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 17)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 1)
    return 0;

  /* Check that there is one Packet Pending in the OutManager */
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 1)
    return 0;

  /* allocate an 17,2 in Report */
  pckt2 = CrFwPcktMake(20);
  CrFwPcktSetServType(pckt2,17);
  CrFwPcktSetServSubType(pckt2,2);
  CrFwPcktSetDiscriminant(pckt2,0);
  CrFwPcktSetDest(pckt2,10);
  CrFwPcktSetSrc(pckt2,appId);

  /* Check if number of Allocated Packets now is 4*/
  if (CrFwPcktGetNOfAllocated() != 4)
    return 0;
  
  /* Check that there are no InReports in the InFactory*/
  if (CrFwInFactoryGetNOfAllocatedInRep() != 0)
    return 0;

  /*Create an InReport from pckt2 (17.2)*/
  inRep1 = CrFwInFactoryMakeInRep(pckt2);

  /* Check if number of Allocated InReports in the InFactory now is 1*/
  if (CrFwInFactoryGetNOfAllocatedInRep() != 1)
    return 0;

  /* Check that there are no Packets Pending or Loaded in the InManager*/
  if (CrFwInManagerGetNOfPendingInCmp(inManager) != 0)
    return 0;
  if (CrFwInManagerGetNOfLoadedInCmp(inManager) != 0)
    return 0;

  /*Load the InReport into the InManager*/
  CrFwInManagerLoad(inManager, inRep1);

  /* Check is now one Pending (inCmd)(17,3) and one Loaded (inRep)(17,2) Packets in the InManager*/
  if (CrFwInManagerGetNOfPendingInCmp(inManager) != 1)
    return 0;
  if (CrFwInManagerGetNOfLoadedInCmp(inManager) != 1)
    return 0;

  /*Execute the InManager*/
  CrFwCmpExecute(inManager); 

  /* Check that there is now no Pending but one Loaded (inCmd)(17,3) Packets in the InManager*/
  if (CrFwInManagerGetNOfPendingInCmp(inManager) != 0)
    return 0;
  if (CrFwInManagerGetNOfLoadedInCmp(inManager) != 1)
    return 0;

  /* Check that there is one Pending and one Loaded Packet in the OutManager */
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 1)
    return 0;
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 1)
    return 0;
  
  /*Execute the InCommand*/
  CrFwCmpExecute(inCmd); 

  /* 17,4 now in the OutManager*/
  /* Check that there are now two Pending and two Loaded Packets in the OutManager */
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 2)
    return 0;
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 2)
    return 0;

  /*Terminate the InCommand*/
  CrFwInCmdTerminate(inCmd); 

  /* Get the Information from the OutManager (there are two Component!) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];
  outCmp1 = outManagerCSData->pocl[1];

  /*Check if there is a 17,1 Command waitig in the OutManager (loaded)*/
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 2)
    return 0;
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 17)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 1)
    return 0;

  /* Execute the OutComponent (17,1) */
  CrFwCmpExecute(outCmp); 
  
  /* Check and reset application error code (i think because there is no outstream defined) */
  CrFwSetAppErrCode(crNoAppErr);

  /* Check if there is a 17,4 Command waitig in the OutManager (loaded)*/
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 2)
    return 0;
  if (CrFwCmpGetTypeId(outCmp1) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp1) != 17)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp1) != 4)
    return 0;

  /* Execute the OutComponent (17,4) */
  CrFwCmpExecute(outCmp1); 

  /* Check that there are 3 allocated packets */
  if (CrFwPcktGetNOfAllocated() != 3)
    return 0;

  /* Release the (17,3) InCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check that now there are only 2 allocated packets */
  if (CrFwPcktGetNOfAllocated() != 2)
    return 0;

  /* Check that there are no Allocated InCommands in the InFactory*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Release the (17,2) InReport*/
  CrFwInFactoryReleaseInRep(inRep1);
  CrFwSetAppErrCode(crNoAppErr);

  /* Check that now there are only 2 allocated packets */
  if (CrFwPcktGetNOfAllocated() != 2)
    return 0;

  /* Release the (17,1) Outcomponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check that now there is only 1 allocated packet */
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Release the (17,4) OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp1);

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Reset OutManager and check that all OutComponents are unloaded and released */
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  CrFwSetAppErrCode(crNoAppErr);

  /* Reset InManager and check that all InComponents are unloaded and released */
  CrFwCmpReset(inManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(inManager) != 0)
    return 0;
  
  /* Reset the OutFactory and check that no OutComponents are allocated */
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

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrPsServTestConnTestCase3()
{
  /* Service 17 exceptional cases */
  FwSmDesc_t inFactory, inManager, outFactory, outManager, inCmd, outCmp1, outCmp[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];
  FwPrDesc_t prDesc;
  CrFwPckt_t pckt;
  CrFwCmpData_t* outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  CrPsApid_t appId;
  unsigned short timeout;
  CrFwCounterU4_t i;
  
  appId=60;
  prDesc = NULL;
  
  /*Initialize Applications Applications (10 are Available) */
  /*To test the whole Code i will try to initialize 11 Aplications*/
  CrPsInitServTestApp(201);
  CrPsInitServTestApp(202);
  CrPsInitServTestApp(203);
  CrPsInitServTestApp(204);
  CrPsInitServTestApp(205);
  CrPsInitServTestApp(206);
  CrPsInitServTestApp(207);
  CrPsInitServTestApp(208);
  CrPsInitServTestApp(209);

  /* Instantiate the OutFactory, InFactory, OutManager and inManager */
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

  inManager = CrFwInManagerMake(0);
  if (inManager == NULL)
    return 0;
  if (FwSmCheckRec(inManager) != smSuccess)
    return 0;
  
  /* Initialize and Configure OutFactory and check success */
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;
  
  /* Initialize and Configure InFactory and check success */
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  if (!CrFwCmpIsInConfigured(inFactory))
    return 0;

  /* Initialize and Configure OutManager and check success */
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  if (!CrFwCmpIsInConfigured(outManager))
    return 0; 

  /* Initialize and Configure InManager and check success */
  CrFwCmpInit(inManager);
  CrFwCmpReset(inManager);
  if (!CrFwCmpIsInConfigured(inManager))
    return 0; 

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a 17,3 Packet */
  pckt = CrFwPcktMake(20);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetSrc(pckt,1);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,2);
  setOnBoardConnectCmdAppId(pckt, appId);

  /* make an inCommand out of the packet */
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Check if number of Allocated InCommands now in the InFactory is 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 17)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 3)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0;

  /* Fill the outfactory so that an Error could occur (leave one free slot) */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-2;i++)
  {
    outCmp[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
  }
  
  /* Execute the InCommand  */
  /* If the OutFactory is full it should fail !!!*/
  CrFwCmpExecute(inCmd); 

  /* Release all outcomponents, that have been created to fill the outfactory */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-2;i++)
  { 
    CrFwOutFactoryReleaseOutCmp(outCmp[i]);
  }

  /* Here the ErrorCode gets 10*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Release the original inCmd */
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Get the Information from the OutManager (there are two Component!) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp1 = outManagerCSData->pocl[0];
  
  /* Check if there is a 1,4 Command waitig in the OutManager */
  if (CrFwCmpGetTypeId(outCmp1) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp1) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp1) != 4)
    return 0;

  /*Release the (1,4) Outcomponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp1);

  /* Reset OutManager and check that all OutComponents are unloaded and released */
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

 /* Check if number of Allocated Packets now is 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocating a 17,3 Packet */
  pckt = CrFwPcktMake(20);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetSrc(pckt,1);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,2);

  setOnBoardConnectCmdAppId(pckt, appId);
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Fill the outfactory so that an Error could occur */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
  {
    outCmp[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
  }

  /* Execute the InCommand  */
  /* If the OutFactory is full it should fail, there is also no place for a 1,4 to be generated !!!*/
  CrFwCmpExecute(inCmd); 

  /* Release all outcomponents, that have been created to fill the outfactory */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
  {
    CrFwOutFactoryReleaseOutCmp(outCmp[i]);
  }

  /*Here the ErrorCode gets 10*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Release the original inCmd */
  CrFwInFactoryReleaseInCmd(inCmd);

 /* Check if number of Allocated Packets now is 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocating a 17,3 Packet */
  pckt = CrFwPcktMake(20);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,3); 
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetSrc(pckt,1);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  setOnBoardConnectCmdAppId(pckt, appId);

  /* make an inCommand out of the packet */
  inCmd = CrFwInFactoryMakeInCmd(pckt);
  
  /* Execute the InCommand  */
  CrFwCmpExecute(inCmd); 

  /*Check if now 3 Packets are Allocated
   * one InCommand we just created and executed)
   * one InCommand (17.1) to the application that was specified in the parameter of the 17.3 packet
   * and a Packet holding the 17.4 Report is allocated (outManagerPending)
   */
  if (CrFwPcktGetNOfAllocated() != 3)
    return 0;

  /* Check if number of Allocated InCommands in the InFactory stays at 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /*Trigger a Timeout by executing the incommand as often as the value in the datapool specifies*/
  for (i=1;i<=getDpAreYouAliveTimeOut();i++)
  {
    CrFwCmpExecute(inCmd);
  }

  /* for coverace call - CrPsTestOnBoardConnectionTerminationAction so the else will be executed*/  
  CrPsTestOnBoardConnectionTerminationAction(inCmd);
  
  /* for coverage call - CrPsTestOnBoardConnectionStartN3 */
  CrPsTestOnBoardConnectionStartN3(prDesc);

  /* Set the Timeout Variable in the Datapool to 100 to trigger an error */
  timeout = getDpAreYouAliveTimeOut();
  setDpAreYouAliveTimeOut(100);

  /* for coverage call - CrPsTestOnBoardConnectionPrgrG13 */
  if(CrPsTestOnBoardConnectionPrgrG13(prDesc) == 1)
      return 0;

  setDpAreYouAliveTimeOut(timeout);

  FwPrExecute(getPrDescServTestOnBoardConnStart());

  /* call the N10 release function for coverage (an error 11 is created) */
  CrPsTestOnBoardConnectionStartN10(prDesc);

    /* Release the original inCmd */
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Reset OutManager and check that all OutComponents are unloaded and released */
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  CrFwSetAppErrCode(crNoAppErr);

  /* Reset InManager and check that all InComponents are unloaded and released */
  CrFwCmpReset(inManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(inManager) != 0)
    return 0;

  /* Reset the OutFactory */
  CrFwCmpReset(outFactory);  
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Reset the InFactory and check that no InCommands are allocated */
  CrFwCmpReset(inFactory);
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Here the ErrorCode gets 6*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  return 1;
}


