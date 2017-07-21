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
/* Include configuration files */
#include "CrFwInStreamUserPar.h" /* TODO: CrPsInStreamUserPar.h" */
#include "CrFwOutRegistryUserPar.h" /* TODO: CrPsOutRegistryUserPar.h */
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
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "Services/Test/InCmd/CrPsTestAreYouAliveConnection.h"
#include "Services/Test/OutCmp/CrPsTestAreYouAliveConnectionRep.h"
#include "Services/Test/InRep/CrPsTestAreYouAliveConnectInRep.h"
#include "DataPool/CrPsDpServTest.h"

/* Include system files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsServTestConnTestCase1()
{
  /* Check InCmd from Ground */

/*  FwSmDesc_t inFactory, inCmd1;*/
  FwSmDesc_t inFactory;
  CrFwPckt_t pckt1;
/*  CrFwInCmdData_t* inCmdSpecificData;
  CrFwCmpData_t* inCmdData;*/

  /*Initialize the DataPool entries for the Test Service*/
  initDpServTest();

  /* Instantiate the InFactory */
  printf("Instantiate the InFactory\n");
  inFactory = CrFwInFactoryMake();
    
  /* Initialize and Configure InFactory and check success */
  printf("Initialize the InFactory\n");
  CrFwCmpInit(inFactory);
  printf("Reset the InFactory\n");
  CrFwCmpReset(inFactory);
  printf("Check configuration of the InFactory\n");
  if (!CrFwCmpIsInConfigured(inFactory))
    return 0;
  
  /* Allocate one TC(17,1) InCommand */
  printf("Allocate one TC(17,1) InCommand\n");
  pckt1 = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt1,17);
  CrFwPcktSetServSubType(pckt1,1);
  CrFwPcktSetDiscriminant(pckt1,0);
  CrFwPcktSetCmdRepId(pckt1,111); /* TBD */
  CrFwPcktSetSrc(pckt1,0);
  CrFwPcktSetGroup(pckt1,1); /* TBD */
  CrFwPcktSetAckLevel(pckt1,1,0,1,0);
  CrFwPcktSetSeqCnt(pckt1,1111);
  printf("CrFwITest case Pusext_ServVeri_TestCase1 ran successfully ...nFactoryMakeInCmd(pckt1)\n");
/*  inCmd1 = CrFwInFactoryMakeInCmd(pckt1);*/

  /* Check the instance identifiers and the type identifier */
  printf("Check the instance identifiers and the type identifier\n");
/*  if (CrFwCmpGetInstanceId(inCmd1) != 111)*/ /* TBD */
    /*return 0;
  if (CrFwCmpGetTypeId(inCmd1) != CR_FW_INCOMMAND_TYPE)
    return 0;*/

  /* Check correct configuration */
  printf("Check correct configuration\n");
/*  if (FwSmCheck(inCmd1) != 1)
    return 0;*/

  /* Check InCommand state */
  printf("Check InCommand state\n");
/*  if (!CrFwCmpIsInConfigured(inCmd1))
    return 0;*/

  /* TBW */

  /* Release the InCommand */
  printf("Release the InCommand\n");
  CrFwPcktRelease(pckt1);
  
  /* Check that there are no allocated packets */
  printf("Check that there are no allocated packets\n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  printf("Check application errors\n");
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;


  return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsServTestConnTestCase2()
{
  /* Check OutCmp Generation to Ground */
  /* NEIN hier probier ich  jetzt nochmal das incmd 17.1 zu testen (aus CrFwIncmdTestCases) */
  
  FwSmDesc_t inFactory, inCmd;
  FwSmDesc_t outFactory, outManager;
  CrFwPckt_t pckt;
  
  
  printf("checking ---CrPsTestAreYouAliveConnection.c---\n");
 
  printf("Instantiate the OutFactory  \n");
  /* Instantiate the OutFactory */
  outFactory = CrFwOutFactoryMake();

  printf("Instantiate the InFactory \n");
  /* Instantiate the InFactory */
  inFactory = CrFwInFactoryMake();

  printf("Initialize and Configure InFactory and check success \n");
  /* Initialize and Configure InFactory and check success */
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  if (!CrFwCmpIsInConfigured(inFactory))
    return 0;
  
  printf("Initialize and Configure OutFactory and check success \n");
    /* Initialize and Configure OutFactory and check success */
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;
  
   printf("Check component type of the OutFactory \n");  	
  /* Check component type of the OutFactory */
  if (CrFwCmpGetInstanceId(outFactory) != 0)
    return 0;
  if (CrFwCmpGetTypeId(outFactory) != CR_FW_OUTFACTORY_TYPE)
    return 0;
  
  /* Initialize and Configure OutManager and check success */
  printf("Instantiate the OutManager \n");
  /* Instantiate the OutManager */
  outManager = CrFwOutManagerMake(0);
  printf("Check current state of OutManager\n");
  /* Check current state of OutManager */
  if (!CrFwCmpIsInCreated(outManager))
    return 0;
  
  printf("Initialize and Configure OutManager and check success  \n");
  /* Initialize and Configure OutManager and check success */
  CrFwCmpInit(outManager);
  if (!CrFwCmpIsInInitialized(outManager))
    return 0;
  CrFwCmpReset(outManager);
  if (!CrFwCmpIsInConfigured(outManager))
    return 0;    
  
  /* Allocate the Sample1 InCommand */
  pckt = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,1);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetCmdRepId(pckt,0);
  CrFwPcktSetSrc(pckt,1);
  CrFwPcktSetDest(pckt,1);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt, 1, 1, 1, 1);	/* all acknowledgement of success */
  CrFwPcktSetSeqCnt(pckt,2);  
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Check InCommand state */
  if (!CrFwCmpIsInConfigured(inCmd))
    return 0;
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0;
  if (CrFwRepInCmdOutcomeStubGetPos() != 0)
    return 0;  

  CrFwCmpExecute(inCmd); 
  /* Execute InCommand check that it stays in PROGRESS */
  if (!CrFwInCmdIsInProgress(inCmd))
    return 0;
  
  if (CrFwRepInCmdOutcomeStubGetPos() != 2)
    return 0;

  /* Send command Terminate to InCommand and check that TERMINATED is entered */
  CrFwInCmdTerminate(inCmd);
  if (!CrFwInCmdIsInTerminated(inCmd))
    return 0;

  if (CrFwRepInCmdOutcomeStubGetPos() != 3)
    return 0;
  if (CrFwRepInCmdOutcomeStubGetOutcome(0) != crCmdAckStrSucc)
    return 0;
  if (CrFwRepInCmdOutcomeStubGetOutcome(1) != crCmdAckPrgSucc)
    return 0;
  if (CrFwRepInCmdOutcomeStubGetOutcome(2) != crCmdAckTrmSucc)
    return 0;  

  CrPsTestAreYouAliveConnectionAbortAction(inCmd);
  
  /* Release the InCommands */
  CrFwInFactoryReleaseInCmd(inCmd);
  CrFwRepInCmdOutcomeStubReset();
  CrFwCmpReset(outManager);
 
  /* Shutdown the InFactory and check that no InCommands are allocated */
  CrFwCmpShutdown(inFactory);
  if (CrFwCmpIsStarted(inFactory) != 0)
    return 0;
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

 
  /* Restart and initialize the InFactory */
  FwSmStart(inFactory);
  CrFwCmpInit(inFactory);
        
  /* Shutdown the OutFactory */
  CrFwCmpReset(outFactory);  
  CrFwCmpShutdown(outFactory);
  if (CrFwCmpIsStarted(outFactory) != 0)
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;
  
    /* Restart and initialize the OutFactory */
  FwSmStart(outFactory);
  CrFwCmpInit(outFactory);

  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;
        
  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;
  
  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;
  
    /* Initialize and Configure InFactory and check success */
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  if (!CrFwCmpIsInConfigured(inFactory))
    return 0;
 
      /* Initialize and Configure OutFactory and check success */
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;
  
      /* Initialize and Configure OutManager and check success */
        CrFwCmpReset(outManager);
  if (!CrFwCmpIsInConfigured(outManager))
    return 0; 
  
  	/* Shut down OutManager and check that all OutComponents are unloaded and released */
	CrFwCmpShutdown(outManager);
	if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
		return 0;

	/* Check that Sample OutComponents have been released */
	if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
		return 0;

	/* Bring OutManager back to state CONFIGURED */
	FwSmStart(outManager);
	CrFwCmpInit(outManager);
	CrFwCmpReset(outManager);
	if (!CrFwCmpIsInConfigured(outManager))
		return 0;
  
  
  
  printf("successfully checked ---CrPsTestAreYouAliveConnection.c---\n");
  return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsServTestConnTestCase3()
{
    /*-----CrPsTestAreYouAliveConnectionInRep ---- */
/*dummy test to get coverage*/
/*expand this test to check all code segments*/
  CrFwPckt_t pckt;
  FwSmDesc_t InFactory, inRep;

  printf("checking ---CrPsTestAreYouAliveConnectInRep.c---\n");
    
  /* Instantiate the InFactory */
  InFactory = CrFwInFactoryMake();

  /* Initialize and Configure InFactory and check success */
  CrFwCmpInit(InFactory);
  CrFwCmpReset(InFactory);
  if (!CrFwCmpIsInConfigured(InFactory))
    return 0;

  pckt = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,2);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetCmdRepId(pckt,0);
  CrFwPcktSetSrc(pckt,1);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt, 1, 1, 1, 1);	/* all acknowledgement of success */
  CrFwPcktSetSeqCnt(pckt,2);
  inRep = CrFwInFactoryMakeInRep(pckt);
  
  /* Check the instance identifiers and the type identifier */
  if (CrFwCmpGetInstanceId(inRep) != 0)
    return 0;

  /* Check correct configuration */
  if (FwSmCheck(inRep) != 1)
    return 0;

  /* Check InReport state */
  if (!CrFwCmpIsInConfigured(inRep))
    return 0;
 
  CrFwCmpExecute(inRep);     
  
  /* Release the InReports */
  CrFwInFactoryReleaseInRep(inRep);

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

        
  printf("successfully checked ---CrPsTestAreYouAliveConnectInRep.c---\n");
  return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsServTestConnTestCase4()
{
  FwSmDesc_t outFactory, outCmp;
  printf("checking ---CrPsTestAreYouAliveConnectionRep.c---\n");
        
  /* Instantiate the OutFactory */
  outFactory = CrFwOutFactoryMake();

  /* Initialize and Configure OutFactory and check success */
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;

  /* Allocate two OutComponents */
  outCmp = CrFwOutFactoryMakeOutCmp(17,2,0,0);

  /* Perform a configuration check on one of the OutComponents */
  if (FwSmCheckRec(outCmp) != smSuccess)
    return 0;

  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
 
  /* Check OutComponent state */
  if (!CrFwCmpIsInConfigured(outCmp))
    return 0;
  if (!CrFwOutCmpIsInLoaded(outCmp))
    return 0;
  
    /* Initialize and Configure OutFactory and check success */
  CrFwCmpExecute(outCmp); 
  	
  /* Check and reset application error code */
  if (CrFwGetAppErrCode() != crOutStreamUndefDest)
   return 0;
  CrFwSetAppErrCode(crNoAppErr);
  
  /*Check if Repeatcheck always returns 0*/
  if (CrPsTestAreYouAliveConnectionRepRepeatCheck(outCmp) != 0)
      return 0;
  
  /* Release the OutComponents */
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;
  
  printf("successfully checked ---CrPsTestAreYouAliveConnectionRep.c---\n");       
  return 1;
}

/* ---------------------------------------------------------------------------------------------*/

