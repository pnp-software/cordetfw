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
#include "Services/Test/InCmd/CrPsTestAreYouAliveConnection.h"
#include "Services/Test/OutCmp/CrPsTestAreYouAliveConnectionRep.h"
#include "Services/Test/InRep/CrPsTestAreYouAliveConnectInRep.h"
#include "Services/Test/InCmd/CrPsTestOnBoardConnection.h"
#include "Services/Test/OutCmp/CrPsTestOnBoardConnectionRep.h"
#include "Services/Test/Procedures/CrPsCmd17s3StartCreate.h"
#include "Services/Test/Procedures/CrPsCmd17s3PrgrCreate.h"
#include "DataPool/CrPsDpServTest.h"
#include "CrPsUtilities.h"
#include "config/CrFwOutFactoryUserPar.h"

/* Include system files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsServTestConnTestCase1()
{
  /* Check 17.1 and 17.2 */
  FwSmDesc_t inFactory, outFactory, outManager, inCmd, outCmp;
  CrFwPckt_t pckt;
  CrFwCmpData_t* outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  
  /* Instantiate the OutFactory, InFactory and OutManager*/
  printf("Instantiate the OutFactory, InFactory and OutManager  \n");
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
  printf("Initialize and Configure OutFactory and check success \n");
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;
  
    /* Initialize and Configure InFactory and check success */
  printf("Initialize and Configure InFactory and check success \n");
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  if (!CrFwCmpIsInConfigured(inFactory))
    return 0;

  /* Initialize and Configure OutManager and check success */
  printf("Initialize and Configure OutManager and check success  \n");
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  if (!CrFwCmpIsInConfigured(outManager))
    return 0; 

  /* Check if number of Allocated Packets = 0*/
  printf("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a 17.1 Packet */
  printf("Allocating a 17.1 Packet \n");
  pckt = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,1);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetCmdRepId(pckt,0);
  CrFwPcktSetSrc(pckt,1);
  CrFwPcktSetDest(pckt,1);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  /* all acknowledgement of success */
  CrFwPcktSetSeqCnt(pckt,2);  

  /* Check if number of Allocated Packets now is 1*/
  printf("Check if one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  printf("Check if no inCommands are allocated \n");
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 17.1 packet*/
  printf("Create an InCommand out of the 17.1 packet \n");
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  printf("Check if one InCommand is allocated \n");
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  printf("Check the type identifier (CR_FW_INCOMMAND_TYPE) \n");
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  printf("Check the type and subtype of the InCommand\n");
  if (CrFwInCmdGetServType(inCmd) != 17)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 1)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  printf("check that the InCommand is in ACCEPTED state  \n");
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Check if number of Allocated OutComponents = 0*/
  printf("Check if no OutComponents are allocated \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Execute the InCommand  */
  printf("Execute the InCommand  \n");
  CrFwCmpExecute(inCmd); 
  
  /*check that the InCommand is in PROGRESS state*/
  printf("check that the InCommand is in PROGRESS state  \n");
  if (!CrFwInCmdIsInProgress(inCmd))
    return 0;  

  /* Check if number of Allocated Packets now is 2*/
  printf("Check if there are two packets allocated \n");
  if (CrFwPcktGetNOfAllocated() != 2)
    return 0;

  /* Check if number of Allocated OutComponents now is 1 */
  printf("Check if one OutComponent is now allocated \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /*Get the Data from the out Manager (there is only one Component)*/
  printf("Get the Information from the OutManager (there is one Component!) \n");
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];

  /*Check if there is a 17.2 Report waitig in the OutManager*/
  printf("Check if there is a 17.2 Report waitig in the OutManager \n"); 
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 17)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 2)
    return 0;

  /* Call the Abort Action (There is nothing to check, because this Action does nothing!)*/
  printf("Call the Abort Action (There is nothing to check, because this Action does nothing!) \n");
  CrPsTestAreYouAliveConnectionAbortAction(inCmd);

  /* Send command Terminate to InCommand */
  printf("Send command Terminate to InCommand\n");
  CrFwInCmdTerminate(inCmd);

  /*Check if the InCommand is in TERMINATED state*/
  printf("Check if the InCommand is in TERMINATED state \n");
  if (!CrFwInCmdIsInTerminated(inCmd))
    return 0;

  /*Release the InCommand */
  printf("Release the InCommand\n");
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check if number of Allocated Packets now is 1*/
  printf("Check if one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /*Check if number of Allocated InCommands is now 0*/
  printf("Check if number of Allocated InCommands is now 0 \n");
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Execute the OutComponent (17.2) */
  printf("Execute the OutComponent (17.2) \n");
  CrFwCmpExecute(outCmp); 

  /* Check and reset application error code (because there is no outstream defined */
  printf("Check and reset application error code (because there is no outstream defined \n");
  if (CrFwGetAppErrCode() != crOutStreamUndefDest)
   return 0;
  CrFwSetAppErrCode(crNoAppErr);

  /*Check if Repeatcheck always returns 0*/
  printf("Check if Repeatcheck always returns 0  \n");
  if (CrPsTestAreYouAliveConnectionRepRepeatCheck(outCmp) != 0)
      return 0;

  /*Release the OutComponent*/
  printf("Release the OutComponent\n");
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  printf("Check if number of Allocated OutComponents now is 0  \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check that there are no allocated packets */
  printf("Check that there are no allocated packets\n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  printf("Check application errors");
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Reset OutManager and check that all OutComponents are unloaded and released */
  printf("Reset OutManager and check that all OutComponents are unloaded and released \n");
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  /*Here the ErrorCode gets 11*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Reset the OutFactory */
  printf("Reset the OutFactory and check that no OutComponents are allocated \n");
  CrFwCmpReset(outFactory);  
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Reset the InFactory and check that no InCommands are allocated */
  printf("Reset the InFactory and check that no InCommands are allocated \n");
  CrFwCmpReset(inFactory);
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check application errors */
  printf("Check application errors\n");
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrPsServTestConnTestCase2()
{
  /* Check 17.3 and 17.4 */
  FwSmDesc_t inFactory, inManager, outFactory, outManager, inCmd, outCmp, outCmp1, inRep1;
  CrFwPckt_t pckt, pckt2;
  CrFwCmpData_t* outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  unsigned short appId;
  appId = 2;

  /* Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines */
  printf("Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines");
  CrPsInit();
  /*Initialize Applications  */
  printf("Initialize Applications");
  CrPsInitApp(appId);
  CrPsInitApp(200);

  /* Instantiate the OutFactory, InFactory, OutManager and inManager */
  printf("Instantiate the OutFactory, InFactory, OutManager and inManager  \n");
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
  printf("Initialize and Configure OutFactory and check success \n");
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;
  
    /* Initialize and Configure InFactory and check success */
  printf("Initialize and Configure InFactory and check success \n");
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  if (!CrFwCmpIsInConfigured(inFactory))
    return 0;

  /* Initialize and Configure OutManager and check success */
  printf("Initialize and Configure OutManager and check success  \n");
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  if (!CrFwCmpIsInConfigured(outManager))
    return 0; 

  /* Initialize and Configure InManager and check success */
  printf("Initialize and Configure InManager and check success  \n");
  CrFwCmpInit(inManager);
  CrFwCmpReset(inManager);
  if (!CrFwCmpIsInConfigured(inManager))
    return 0; 

  /* Check if number of Allocated Packets = 0*/
  printf("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a 17.3 Packet with a wrong AppId*/
  printf("Allocating a 17.3 Packet with a wrong AppId\n");
  pckt = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetCmdRepId(pckt,0);
  CrFwPcktSetSrc(pckt,3);
  CrFwPcktSetDest(pckt,3);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  /* all acknowledgement of success */
  CrFwPcktSetSeqCnt(pckt,2);
  /*give the Packet a wrong appId so the process fails*/
  appId = 88;
  pckt[OFFSET_PAR_LENGTH_IN_CMD_PCKT + 0] = (appId >> 8) & 0xff;
  pckt[OFFSET_PAR_LENGTH_IN_CMD_PCKT + 1] = (appId & 0xFF);
  appId = 2;

  /* Check if number of Allocated Packets now is 1*/
  printf("Check if one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  printf("Check if no inCommands are allocated \n");
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 17.3 packet*/
  printf("Create an InCommand out of the 17.3 packet \n");
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  printf("Check if one InCommand is allocated \n");
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  printf("Check the type identifier (CR_FW_INCOMMAND_TYPE) \n");
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  printf("Check the type and subtype of the InCommand\n");
  if (CrFwInCmdGetServType(inCmd) != 17)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 3)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  printf("check that the InCommand is in ACCEPTED state  \n");
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Check if number of Allocated OutComponents = 0*/
  printf("Check if no OutComponents are allocated \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Execute the InCommand  */
  /* The inCommand has no Parameter for the Destination set so it should abort!*/
  printf("Execute the InCommand  \n");
  CrFwCmpExecute(inCmd); 

  /*Check that the InCommand is in the State ABORTED*/
  printf("Check that the InCommand is in the State ABORTED \n");
  if (!CrFwInCmdIsInAborted(inCmd))
    return 0; 

  /* Release the inCommand*/
  printf("Release the inCommand \n");
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check if number of Allocated Packets now is 0*/
  printf("Check if number of Allocated Packets now is 0 \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a 17.3 Packet */
  printf("Allocating a 17.3 Packet \n");
  pckt = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetCmdRepId(pckt,0);
  CrFwPcktSetSrc(pckt,1);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  /* all acknowledgement of success */
  CrFwPcktSetSeqCnt(pckt,2);
  pckt[OFFSET_PAR_LENGTH_IN_CMD_PCKT + 0] = (appId >> 8) & 0xff;
  pckt[OFFSET_PAR_LENGTH_IN_CMD_PCKT + 1] = (appId & 0xFF);
  inCmd = CrFwInFactoryMakeInCmd(pckt);

   /* Check if number of Allocated InCommands now in the InFactory is 1*/
  printf("Check if number of Allocated InCommands now in the InFactory is 1 \n");
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check if number of Allocated InFactory InCommands now is 1*/
  printf("Check if number of Allocated InFactory InCommands now is 1 \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;
  
  /* Check the type identifier */
  printf("Check the type identifier (CR_FW_INCOMMAND_TYPE) \n");
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  printf("Check the type and subtype of the InCommand\n");
  if (CrFwInCmdGetServType(inCmd) != 17)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 3)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  printf("check that the InCommand is in ACCEPTED state  \n");
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Check if number of Allocated OutComponents = 0*/
  printf("Check if no OutComponents are allocated \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Execute the InCommand  */
  /* The inCommand has now a correct Parameter for the Destination */
  printf("Execute the InCommand  \n");
  CrFwCmpExecute(inCmd); 

/* Check if now 3 Packets are Allocated
 * one InCommand we just created and executed)
 * one InCommand (17.1) to the application that was specified in the parameter of the 17.3 packet
 * and a Packet holding the 17.4 Report is allocated (outManager Pending)
 */
  /* Check if number of Allocated Packets now is 3 */
  printf("Check if number of Allocated Packets now is 3 \n");
  if (CrFwPcktGetNOfAllocated() != 3)
    return 0;

  /* Check if number of Allocated InCommands in the InFactory stays at 1 */
  printf("Check if number of Allocated InCommands in the InFactory stays at 1 \n");
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager is 1 */
  printf("Check if number of loaded OutComponents in the OutManager is 1 \n");
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 1)
    return 0;

  /* Get the Data from the out Manager (there is only one Component) */
  printf("Get the Information from the OutManager (there is one Component!) \n");
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];

  /* Check if there is a 17.1 Command waitig in the OutManager (loaded) */
  printf("Check if there is a 17.1 Command waitig in the OutManager (loaded) \n"); 
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 17)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 1)
    return 0;

  /* Check that there is one Packet Pending in the OutManager */
  printf("Check that there is one Packet Pending in the OutManager \n"); 
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 1)
    return 0;

  /* allocate an 17.2 in Report */
  printf("allocate an 17.2 in Report \n"); 
  pckt2 = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt2,17);
  CrFwPcktSetServSubType(pckt2,2);
  CrFwPcktSetDiscriminant(pckt2,0);
  CrFwPcktSetSrc(pckt2,appId);
  CrFwPcktSetDest(pckt2,10);

  /* Check if number of Allocated Packets now is 4*/
  printf("Check if number of Allocated Packets now is 4 \n");
  if (CrFwPcktGetNOfAllocated() != 4)
    return 0;
  
  /* Check that there are no InReports in the InFactory*/
  printf("Check that there are no InReports in the InFactory \n");
  if (CrFwInFactoryGetNOfAllocatedInRep() != 0)
    return 0;
  
  /*Create an InReport from pckt2 (17.2)*/
  printf("Create an InReport from pckt2 (17.2) \n");
  inRep1 = CrFwInFactoryMakeInRep(pckt2);

  /* Check if number of Allocated InReports in the InFactory now is 1*/
  printf("Check if number of Allocated InReports in the InFactory now is 1 \n");
  if (CrFwInFactoryGetNOfAllocatedInRep() != 1)
    return 0;

  /* Check that there are no Packets Pending or Loaded in the InManager*/
  printf("Check that there are no Packets Pending or Loaded in the InManager \n");
  if (CrFwInManagerGetNOfPendingInCmp(inManager) != 0)
    return 0;
  if (CrFwInManagerGetNOfLoadedInCmp(inManager) != 0)
    return 0;

  /*Load the InReport into the InManager*/
  printf("Load the InReport into the InManager\n");
  CrFwInManagerLoad(inManager, inRep1);

  /* Check is now one Pending (inCmd)(17.3) and one Loaded (inRep)(17.2) Packets in the InManager*/
  printf("Check is now one Pending (inCmd)(17.3) and one Loaded (inRep)(17.2) Packets in the InManager \n");
  if (CrFwInManagerGetNOfPendingInCmp(inManager) != 1)
    return 0;
  if (CrFwInManagerGetNOfLoadedInCmp(inManager) != 1)
    return 0;

  /*Execute the InManager*/
  printf("Execute the InManager\n");
  CrFwCmpExecute(inManager); 
  /*InRep disappears ???*/

  /* Check that there is now no Pending but one Loaded (inCmd)(17.3) Packets in the InManager*/
  printf("Check that there is now no Pending but one Loaded (inCmd)(17.3) Packets in the InManager\n");
  if (CrFwInManagerGetNOfPendingInCmp(inManager) != 0)
    return 0;
  if (CrFwInManagerGetNOfLoadedInCmp(inManager) != 1)
    return 0;

  /* Check that there is one Pending and one Loaded Packet in the OutManager */
  printf("Check that there is one Pending and one Loaded Packet in the OutManager \n");
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 1)
    return 0;
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 1)
    return 0;

  /* Execute the InCommand  */
  printf("Execute the InCommand  \n");
  CrFwCmpExecute(inCmd); 
  /*17.4 now in the OutManager*/
  
  /* Check that there are now two Pending and two Loaded Packets in the OutManager */
  printf("Check that there are now two Pending and two Loaded Packets in the OutManager \n");
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 2)
    return 0;
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 2)
    return 0;

  /* Get the Information from the OutManager (there are two Component!) */
  printf("Get the Information from the OutManager (there are two Component!) \n");
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];
  outCmp1 = outManagerCSData->pocl[1];

  /*Check if there is a 17.1 Command waitig in the OutManager (loaded)*/
  printf("Check if there is a 17.1 Command waitig in the OutManager (loaded) \n"); 
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 2)
    return 0;
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 17)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 1)
    return 0;

  /* Execute the OutComponent (17.2) */
  printf("Execute the OutComponent (17.2) \n");
  CrFwCmpExecute(outCmp); 

  /* Check and reset application error code (because there is no outstream defined) */
  printf("Check and reset application error code (because there is no outstream defined) \n");
  if (CrFwGetAppErrCode() != crOutStreamUndefDest)
   return 0;
  CrFwSetAppErrCode(crNoAppErr);

  /*Check if Repeatcheck always returns 0*/
  printf("Check if Repeatcheck always returns 0  \n");
  if (CrPsTestAreYouAliveConnectionRepRepeatCheck(outCmp) != 0)
      return 0;

  /*Check if there is a 17.4 Command waitig in the OutManager (loaded)*/
  printf("Check if there is a 17.4 Command waitig in the OutManager (loaded) \n"); 
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 2)
    return 0;
  if (CrFwCmpGetTypeId(outCmp1) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp1) != 17)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp1) != 4)
    return 0;

  /* Execute the OutComponent (17.4) */
  printf("Execute the OutComponent (17.4) \n");
  CrFwCmpExecute(outCmp1); 

  /* Check and reset application error code (because there is no outstream defined) */
  printf("Check and reset application error code (because there is no outstream defined)  \n");
  if (CrFwGetAppErrCode() != crOutStreamUndefDest)
   return 0;
  CrFwSetAppErrCode(crNoAppErr);

  /*Check if Repeatcheck always returns 0*/
  printf("Check if Repeatcheck always returns 0  \n");
  if (CrPsTestOnBoardConnectionRepRepeatCheck(outCmp1) != 0)
      return 0;

  /* Call the Abort Action (There is nothing to check, because this Action does nothing!)*/
  printf("Call the Abort Action (There is nothing to check, because this Action does nothing!) \n");
  CrPsTestOnBoardConnectionAbortAction(inCmd);

  /* Send command Terminate to InCommand */
  printf("Send command Terminate to InCommand\n");
  CrFwInCmdTerminate(inCmd);

  /*Check if the InCommand is in TERMINATED state*/
  printf("Check if the InCommand is in TERMINATED state \n");
  if (!CrFwInCmdIsInTerminated(inCmd))
    return 0;

  /* Check that there are 3 allocated packets */
  printf("Check that there are 3 allocated packets\n");
  if (CrFwPcktGetNOfAllocated() != 3)
    return 0;

  /*Release the (17.3) InCommand*/
  printf("Release the (17.3) InCommand\n");
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check that now there are only 2 allocated packets */
  printf("Check that now there are only 2 allocated packets\n");
  if (CrFwPcktGetNOfAllocated() != 2)
    return 0;

  /* Check that there are no Allocated InCommands in the InFactory*/
  printf("Check that there are no Allocated InCommands in the InFactory \n");
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Release the (17.2) InReport*/
  printf("Release the (17.2) InReport\n");
  CrFwInFactoryReleaseInRep(inRep1);
  printf("CrFwGetAppErrCode %d \n",CrFwGetAppErrCode());
  CrFwSetAppErrCode(crNoAppErr);
  printf("CrFwGetAppErrCode %d \n",CrFwGetAppErrCode());
  /*inrep already released ???*/

  /* Check that now there are only 2 allocated packets */
  printf("Check that now there are only 2 allocated packets\n");
  if (CrFwPcktGetNOfAllocated() != 2)
    return 0;

  /*Release the (17.1) Outcomponent*/
  printf("Release the (17.1) Outcomponent\n");
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check that now there is only 1 allocated packet */
  printf("Check that now there is only 1 allocated packet\n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /*Release the (17.4) OutComponent*/
  printf("Release the (17.4) OutComponent\n");
  CrFwOutFactoryReleaseOutCmp(outCmp1);

  /* Check that there are no allocated packets */
  printf("Check that there are no allocated packets\n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  printf("Check application errors");
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Reset OutManager and check that all OutComponents are unloaded and released */
  printf("Reset OutManager and check that all OutComponents are unloaded and released \n");
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  /*Here the ErrorCode gets 11 ???*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Reset InManager and check that all InComponents are unloaded and released */
  printf("Reset InManager and check that all InComponents are unloaded and released \n");
  CrFwCmpReset(inManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(inManager) != 0)
    return 0;
  
  /* Reset the OutFactory and check that no OutComponents are allocated */
  printf("Reset the OutFactory and check that no OutComponents are allocated \n");
  CrFwCmpReset(outFactory);  
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;
  
  /* Reset the InFactory and check that no InCommands are allocated */
  printf("Reset the InFactory and check that no InCommands are allocated \n");
  CrFwCmpReset(inFactory);
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check application errors */
  printf("Check application errors \n");
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrPsServTestConnTestCase3()
{
  /* Service 17 exceptional cases */
  /* ??? prDesc ??? */
  FwSmDesc_t inFactory, inManager, outFactory, outManager, inCmd, outCmp[100];
  FwPrDesc_t prDesc;
  CrFwPckt_t pckt;
  unsigned short appId, timeout, maxoutfactory;
  unsigned int i;
  appId=2;
  prDesc = NULL;
  
  /*Initialize Applications Applications (10 are Available) */
  /*To test the whole Code i will try to initialize 11 Aplications*/
  CrPsInitApp(201);
  CrPsInitApp(202);
  CrPsInitApp(203);
  CrPsInitApp(204);
  CrPsInitApp(205);
  CrPsInitApp(206);
  CrPsInitApp(207);
  CrPsInitApp(208);
  CrPsInitApp(209);


/* Instantiate the OutFactory, InFactory, OutManager and inManager */
  printf("Instantiate the OutFactory, InFactory, OutManager and inManager  \n");
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
  printf("Initialize and Configure OutFactory and check success \n");
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;
  
    /* Initialize and Configure InFactory and check success */
  printf("Initialize and Configure InFactory and check success \n");
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  if (!CrFwCmpIsInConfigured(inFactory))
    return 0;

  /* Initialize and Configure OutManager and check success */
  printf("Initialize and Configure OutManager and check success  \n");
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  if (!CrFwCmpIsInConfigured(outManager))
    return 0; 

  /* Initialize and Configure InManager and check success */
  printf("Initialize and Configure InManager and check success  \n");
  CrFwCmpInit(inManager);
  CrFwCmpReset(inManager);
  if (!CrFwCmpIsInConfigured(inManager))
    return 0; 

  /* Check if number of Allocated Packets = 0*/
  printf("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a 17.3 Packet */
  printf("Allocating a 17.3 Packet \n");
  pckt = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetCmdRepId(pckt,0);
  CrFwPcktSetSrc(pckt,1);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  /* all acknowledgement of success */
  CrFwPcktSetSeqCnt(pckt,2);
  pckt[OFFSET_PAR_LENGTH_IN_CMD_PCKT + 0] = (appId >> 8) & 0xff;
  pckt[OFFSET_PAR_LENGTH_IN_CMD_PCKT + 1] = (appId & 0xFF);
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Check if number of Allocated InCommands now in the InFactory is 1*/
  printf("Check if number of Allocated InCommands now in the InFactory is 1 \n");
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check if number of Allocated Packets now is 1*/
  printf("Check if number of Allocated Packets now is 1 \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check type and sub-type of the InCommand*/
  printf("Check the type and subtype of the InCommand\n");
  if (CrFwInCmdGetServType(inCmd) != 17)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 3)
    return 0; 

  /*fill the outfactory !!*/
  printf("Fill the outfactory so that an Error could occur (leave one free slot) \n");
  maxoutfactory = 8; 
  for (i=0;i<=maxoutfactory;i++)
  {
    outCmp[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
  }
  
  /* Execute the InCommand  */
  /* If the OutFactory is full it should fail !!!*/
  printf("Execute the InCommand  \n");
  CrFwCmpExecute(inCmd); 

  /* Release all outcomponents, that have been created to fill the outfactory */
  printf("Release all outcomponents, that have been created to fill the outfactory \n");
  for (i=0;i<=maxoutfactory;i++)
  { 
    CrFwOutFactoryReleaseOutCmp(outCmp[i]);
  }

  /*Here the ErrorCode gets 10*/
  CrFwSetAppErrCode(crNoAppErr);
  
  /* Release the original inCmd */
  printf("Release the original inCmd \n"); 
  CrFwInFactoryReleaseInCmd(inCmd);

 /* Check if number of Allocated Packets now is 0*/
  printf("Check if number of Allocated Packets now is 0 \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocating a 17.3 Packet */
  printf("Allocating a new 17.3 Packet \n");
  pckt = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetCmdRepId(pckt,0);
  CrFwPcktSetSrc(pckt,1);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  /* all acknowledgement of success */
  CrFwPcktSetSeqCnt(pckt,2);
  pckt[OFFSET_PAR_LENGTH_IN_CMD_PCKT + 0] = (appId >> 8) & 0xff;
  pckt[OFFSET_PAR_LENGTH_IN_CMD_PCKT + 1] = (appId & 0xFF);
  printf("CrFwGetAppErrCode %d \n", CrFwGetAppErrCode());
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*fill the outfactory !!*/
  printf("Fill the outfactory so that an Error could occur \n");
  maxoutfactory = 9; 
  for (i=0;i<=maxoutfactory;i++)
  {
    outCmp[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
  }

  /* Execute the InCommand  */
  /* If the OutFactory is full it should fail !!!*/
  printf("Execute the InCommand  \n");
  CrFwCmpExecute(inCmd); 

  /* Release all outcomponents, that have been created to fill the outfactory */
  printf("Release all outcomponents, that have been created to fill the outfactory \n");
  for (i=0;i<=maxoutfactory;i++)
  {
        printf("i: %d \n",i);
    CrFwOutFactoryReleaseOutCmp(outCmp[i]);
  }
  
  /*Here the ErrorCode gets 10*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Release the original inCmd */
  printf("Release the original inCmd \n"); 
  CrFwInFactoryReleaseInCmd(inCmd);

 /* Check if number of Allocated Packets now is 0*/
  printf("Check if number of Allocated Packets now is 0 \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocating a 17.3 Packet */
  printf("Allocating a new 17.3 Packet \n");
  pckt = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetCmdRepId(pckt,0);
  CrFwPcktSetSrc(pckt,1);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  /* all acknowledgement of success */
  CrFwPcktSetSeqCnt(pckt,2);
  pckt[OFFSET_PAR_LENGTH_IN_CMD_PCKT + 0] = (appId >> 8) & 0xff;
  pckt[OFFSET_PAR_LENGTH_IN_CMD_PCKT + 1] = (appId & 0xFF);
  inCmd = CrFwInFactoryMakeInCmd(pckt);
  
  /* Execute the InCommand  */
  printf("Execute the InCommand  \n");
  CrFwCmpExecute(inCmd); 

  /*Check if now 3 Packets are Allocated
   * one InCommand we just created and executed)
   * one InCommand (17.1) to the application that was specified in the parameter of the 17.3 packet
   * and a Packet holding the 17.4 Report is allocated (outManagerPending)
   */
  /* Check if number of Allocated Packets now is 3*/
  printf("CrFwPcktGetNOfAllocated: %d \n",CrFwPcktGetNOfAllocated());
  printf("Check if number of Allocated Packets now is 3 \n");
  if (CrFwPcktGetNOfAllocated() != 3)
    return 0;

  /* Check if number of Allocated InCommands in the InFactory stays at 1*/
  printf("Check if number of Allocated InCommands in the InFactory stays at 1 \n");
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /*Trigger a Timeout by executing the incommand as often as the value in the datapool specifies*/
  printf("Trigger a Timeout by executing the incommand as often as the value in the datapool specifies \n");
  for (i=1;i<=getDpAreYouAliveTimeOut();i++)
  {
    CrFwCmpExecute(inCmd);
  }
  /* for coverage call - CrPsTestOnBoardConnectionStartN3 */
  printf("for coverage call - CrPsTestOnBoardConnectionStartN3 \n");
  CrPsTestOnBoardConnectionStartN3(prDesc);

  /* Set the Timeout Variable in the Datapool to 100 to trigger an error */
  printf("Set the Timeout Variable in the Datapool to 100 to trigger an error  \n");
  timeout = getDpAreYouAliveTimeOut();
  setDpAreYouAliveTimeOut(100);
  printf("for coverage call - CrPsTestOnBoardConnectionPrgrG13 \n");
  if(CrPsTestOnBoardConnectionPrgrG13(prDesc) == 1)
      return 0;
  setDpAreYouAliveTimeOut(timeout);
  FwPrExecute(prDescServTestOnBoardConnStart);

  /*N10*/
  /*call the N10 release function for coverage (an error 11 is created*/
  printf("for coverage call - CrPsTestOnBoardConnectionStartN10 \n");
  CrPsTestOnBoardConnectionStartN10(prDesc);

  /* Reset OutManager and check that all OutComponents are unloaded and released */
  printf("Reset OutManager and check that all OutComponents are unloaded and released \n");
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  /*Here the ErrorCode gets 11 ???*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Reset InManager and check that all InComponents are unloaded and released */
  printf("Reset InManager and check that all InComponents are unloaded and released \n");
  CrFwCmpReset(inManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(inManager) != 0)
    return 0;

  /* Reset the OutFactory */
  printf("Reset the OutFactory and check that no OutComponents are allocated \n");
  CrFwCmpReset(outFactory);  
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Reset the InFactory and check that no InCommands are allocated */
  printf("Reset the InFactory and check that no InCommands are allocated \n");
  CrFwCmpReset(inFactory);
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Here the ErrorCode gets 6*/
  CrFwSetAppErrCode(crNoAppErr);
  /* Check application errors */
  printf("Check application errors \n");
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;


  return 1;
}



