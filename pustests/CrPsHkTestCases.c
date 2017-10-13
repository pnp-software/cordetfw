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
#include "CrPsUtilities.h"
#include "config/CrFwOutFactoryUserPar.h"

/* Include system files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "CrPsDebug.h"

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase1()
{
  /* Check Service 3 */
  FwSmDesc_t inFactory, outFactory, outManager, inCmd, outCmp;
  CrFwPckt_t pckt;
  CrFwCmpData_t* outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  
  /* Instantiate the OutFactory, InFactory and OutManager*/
  DEBUGP_TS3("Instantiate the OutFactory, InFactory and OutManager  \n");
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
  DEBUGP_TS3("Initialize and Configure OutFactory and check success \n");
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;
  
    /* Initialize and Configure InFactory and check success */
  DEBUGP_TS3("Initialize and Configure InFactory and check success \n");
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  if (!CrFwCmpIsInConfigured(inFactory))
    return 0;

  /* Initialize and Configure OutManager and check success */
  DEBUGP_TS3("Initialize and Configure OutManager and check success  \n");
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  if (!CrFwCmpIsInConfigured(outManager))
    return 0; 

  /* Check if number of Allocated Packets = 0*/
  DEBUGP_TS3("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a 17.1 Packet */
  DEBUGP_TS3("Allocating a 17.1 Packet \n");
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
  DEBUGP_TS3("Check if one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  DEBUGP_TS3("Check if no inCommands are allocated \n");
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 17.1 packet*/
  DEBUGP_TS3("Create an InCommand out of the 17.1 packet \n");
  
  DEBUGP_TS3("CrFwPcktGetServType %d\n", CrFwPcktGetServType(pckt) );
  DEBUGP_TS3("CrFwPcktGetServSubType %d\n", CrFwPcktGetServSubType(pckt));
  DEBUGP_TS3("CrFwPcktGetDiscriminant %d\n", CrFwPcktGetDiscriminant(pckt));

  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  DEBUGP_TS3("Check if one InCommand is allocated \n");
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  DEBUGP_TS3("Check the type identifier (CR_FW_INCOMMAND_TYPE) \n");
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  DEBUGP_TS3("Check the type and subtype of the InCommand\n");
  if (CrFwInCmdGetServType(inCmd) != 17)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 1)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  DEBUGP_TS3("check that the InCommand is in ACCEPTED state  \n");
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Check if number of Allocated OutComponents = 0*/
  DEBUGP_TS3("Check if no OutComponents are allocated \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Execute the InCommand  */
  DEBUGP_TS3("Execute the InCommand  \n");
  CrFwCmpExecute(inCmd); 
  
  /*check that the InCommand is in PROGRESS state*/
  DEBUGP_TS3("check that the InCommand is in PROGRESS state  \n");
  if (!CrFwInCmdIsInProgress(inCmd))
    return 0;  

  /* Check if number of Allocated Packets now is 2*/
  DEBUGP_TS3("Check if there are two packets allocated \n");
  if (CrFwPcktGetNOfAllocated() != 2)
    return 0;

  /* Check if number of Allocated OutComponents now is 1 */
  DEBUGP_TS3("Check if one OutComponent is now allocated \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /*Get the Data from the out Manager (there is only one Component)*/
  DEBUGP_TS3("Get the Information from the OutManager (there is one Component!) \n");
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];

  /*Check if there is a 17.2 Report waitig in the OutManager*/
  DEBUGP_TS3("Check if there is a 17.2 Report waitig in the OutManager \n"); 
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 17)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 2)
    return 0;

  

  /*Release the OutComponent*/
  DEBUGP_TS3("Release the OutComponent\n");
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  DEBUGP_TS3("Check if number of Allocated OutComponents now is 0  \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check that there are no allocated packets */
  DEBUGP_TS3("Check that there are no allocated packets\n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  DEBUGP_TS3("Check application errors");
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Reset OutManager and check that all OutComponents are unloaded and released */
  DEBUGP_TS3("Reset OutManager and check that all OutComponents are unloaded and released \n");
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  /*Here the ErrorCode gets 11*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Reset the OutFactory */
  DEBUGP_TS3("Reset the OutFactory and check that no OutComponents are allocated \n");
  CrFwCmpReset(outFactory);  
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Reset the InFactory and check that no InCommands are allocated */
  DEBUGP_TS3("Reset the InFactory and check that no InCommands are allocated \n");
  CrFwCmpReset(inFactory);
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check application errors */
  DEBUGP_TS3("Check application errors\n");
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase2()
{
  

  return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase3()
{
  


  return 1;
}


