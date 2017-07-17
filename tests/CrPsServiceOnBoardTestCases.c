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
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "Services/Test/InCmd/CrPsTestOnBoardConnection.h"
#include "Services/Test/OutCmp/CrPsTestOnBoardConnectionRep.h"
#include "Services/Test/Procedures/CrPsCmd17s3StartCreate.h"
#include "Services/Test/Procedures/CrPsCmd17s3PrgrCreate.h"
#include "Services/General/CrPsConstants.h"
#include "Services/General/CrPsParamSetter.h"
#include "DataPool/CrPsDpServTest.h"
#include "CrPsUtilities.h"
/* Include system files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "config/CrFwOutFactoryUserPar.h"

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsServTestOnBoardTestCase1()
{
  /* Check OutCmp Generation to Ground */
  /* NEIN hier probier ich  jetzt nochmal das incmd 17.1 zu testen (aus CrFwIncmdTestCases) */
  
  FwSmDesc_t inFactory, outFactory, outManager, inCmd, inCmd2;
  FwPrDesc_t prDesc = FwPrCreate(
                        9,	/* N_ANODES - The number of action nodes */
                        3,	/* N_DNODES - The number of decision nodes */
                        16,	/* N_FLOWS - The number of control flows */
                        9,	/* N_ACTIONS - The number of actions */
                        6	/* N_GUARDS - The number of guards */
                      );
    
    
  CrFwPckt_t pckt, pckt2;
  unsigned short failcode, wpp, wpv, appId, timeout;
  failcode = 1;
  wpp = 1;
  wpv = 1;
  appId=2;

  printf("checking ---CrPsTestOnBoardConnection.c---\n");


  /**
   * Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines
   */
  CrPsInit();

  /**
   * Instantiate all application-specific components, e.g. data pool entries
   */
  setDpOnBoardConnectDestLstItem(1, 0);
  
  CrPsInitApp(appId);
  CrPsInitApp(5);


  /* Instantiate the InFactory */
  inFactory = CrFwInFactoryMake();
  /* Instantiate the OutFactory */
  outFactory = CrFwOutFactoryMake();

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
  
  /* Check component type */
  if (CrFwCmpGetInstanceId(outFactory) != 0)
    return 0;
  if (CrFwCmpGetTypeId(outFactory) != CR_FW_OUTFACTORY_TYPE)
    return 0;

  /* Initialize and Configure OutManager and check success */

  /* Instantiate the first OutManager */
  outManager = CrFwOutManagerMake(0);  /* HIER MUSS ICH 2 NEHMEN WEIL ICH DEN OUT MANAGER NICHT RICHTIG SCHLIEßEN KANN !!!*/

  /* Initialize and Configure OutManager and check success */
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  if (!CrFwCmpIsInConfigured(outManager))
    return 0;    

  /* Allocate the Sample1 InCommand */
  pckt = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetCmdRepId(pckt,40);
  CrFwPcktSetSrc(pckt,1);
  CrFwPcktSetDest(pckt,1);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt, 1, 1, 1, 1);	/* all acknowledgement of success */
  CrFwPcktSetSeqCnt(pckt,2);
  pckt[OFFSET_PAR_LENGTH_IN_CMD_PCKT + 0] = (appId >> 8) & 0xff;
  pckt[OFFSET_PAR_LENGTH_IN_CMD_PCKT + 1] = (appId & 0xFF);
  
  
  /*ein falsches paket erzeugen damit wir eine coverage haben*/
  pckt2 = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt2,17);
  CrFwPcktSetServSubType(pckt2,3);
  CrFwPcktSetDiscriminant(pckt2,0);  
  CrFwPcktSetCmdRepId(pckt2,40);
  CrFwPcktSetSrc(pckt2,1);
  CrFwPcktSetDest(pckt2,1);
  CrFwPcktSetGroup(pckt2,1);
  CrFwPcktSetAckLevel(pckt2, 1, 1, 1, 1);	/* all acknowledgement of success */
  CrFwPcktSetSeqCnt(pckt2,2);

    /*this function is otherwise not called*/
    if (CrPsTestOnBoardConnectionStartG2(prDesc) == 0)
      return 0;
    if (CrPsTestOnBoardConnectionStartG3(prDesc) == 1)
      return 0;


  inCmd = CrFwInFactoryMakeInCmd(pckt);
  /*for coverage*/
  CrPsTestOnBoardConnectionStartN3(prDesc);


  /* Check InCommand state */
  if (!CrFwCmpIsInConfigured(inCmd))
    return 0;
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0;

  if (CrFwRepInCmdOutcomeStubGetPos() != 0)
    return 0;  
  
  
  printf("SendReqVerifAccSuccRep(pckt)\n");
  SendReqVerifAccSuccRep(pckt);
  
  printf("SendReqVerifAccFailRep(pckt, failcode)\n");
  SendReqVerifAccFailRep(pckt,failcode);
  printf("Failcode: %d\n",failcode);
  
  printf("SendReqVerifStartSuccRep(pckt)\n");
  SendReqVerifStartSuccRep(pckt);
  
  printf("SendReqVerifStartFailRep(pckt, failcode, wpp, wpv)\n");
  SendReqVerifStartFailRep(pckt, failcode, wpp, wpv);
  printf("Failcode: %d wpp: %d wpv: %d\n",failcode, wpp, wpv);
  
  printf("SendReqVerifProgSuccRep(pckt)\n");
  SendReqVerifProgSuccRep(pckt);
  
  printf("SendReqVerifProgFailRep(pckt, failcode, wpp, wpv)\n");
  SendReqVerifProgFailRep(pckt, failcode, wpp, wpv);
  printf("Failcode: %d wpp: %d wpv: %d\n",failcode, wpp, wpv);
  
  printf("SendReqVerifTermSuccRep(pckt)\n");
  SendReqVerifTermSuccRep(pckt);
  
  printf("SendReqVerifTermFailRep(pckt, failcode, wpp, wpv)\n");
  SendReqVerifTermFailRep(pckt, failcode, wpp, wpv);
  printf("Failcode: %d wpp: %d wpv: %d\n",failcode, wpp, wpv);
 
  

  CrFwCmpExecute(inCmd); 


  CrPsExec();

  
  FwPrExecute(prDescServTestOnBoardConnStart);
  CrPsTestOnBoardConnectionPrgrN1(prDesc);
  
  appId = getDpAreYouAliveSrc();
  setDpAreYouAliveSrc(7);
  if(CrPsTestOnBoardConnectionPrgrG11(prDesc) == 0)
      return 0;
  setDpAreYouAliveSrc(appId);
  
  
  timeout = getDpAreYouAliveTimeOut();
  setDpAreYouAliveTimeOut(100);
  if(CrPsTestOnBoardConnectionPrgrG13(prDesc) == 1)
      return 0;
  
  setDpAreYouAliveTimeOut(timeout);
  
  CrFwCmpExecute(inCmd); 

  CrFwCmpExecute(inCmd); 

  CrFwCmpExecute(inCmd); 
  
  CrFwCmpExecute(inCmd); 

  CrFwCmpExecute(inCmd); 
 
  CrFwCmpExecute(inCmd); 
  
  CrFwCmpExecute(inCmd); 
  
  CrFwCmpExecute(inCmd); 
 
  CrFwCmpExecute(inCmd); 
 
  CrFwCmpExecute(inCmd); /*hier wird das timeout erreicht und fehlercode 11*/
   
        CrFwSetAppErrCode(crNoAppErr);

  CrFwCmpExecute(inCmd); 

        CrFwSetAppErrCode(crNoAppErr);
   
    
      /*N10*/
      /*call teh N10 release function for coverage (an error 11 is created*/
  CrPsTestOnBoardConnectionStartN10(prDesc);

          CrFwSetAppErrCode(crNoAppErr);

          
  CrPsTestOnBoardConnectionPrgrN4(prDesc);
        
  CrFwSetAppErrCode(crNoAppErr);
         

  /*falsches paket*/
  inCmd2 = CrFwInFactoryMakeInCmd(pckt2);

  /* Check InCommand state */
  if (!CrFwCmpIsInConfigured(inCmd2))
    return 0;
  if (!CrFwInCmdIsInAccepted(inCmd2))
    return 0;
  

  CrFwCmpExecute(inCmd2); 

  CrPsExec();
  
  CrPsTestOnBoardConnectionTerminationAction(inCmd);
  CrPsTestOnBoardConnectionAbortAction(inCmd);

  CrFwCmpReset(outManager);
  
  /* Release the InCommands */

  	/* Shutdown the InFactory and check that no InCommands are allocated */
	CrFwCmpShutdown(inFactory);
	if (CrFwCmpIsStarted(inFactory) != 0)
		return 0;
	if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
		return 0;

	/* Restart and initialize the InFactory */
	FwSmStart(inFactory);
	CrFwCmpInit(inFactory);

	CrFwCmpReset(outFactory);  
        CrFwCmpShutdown(outFactory);
	if (CrFwCmpIsStarted(outFactory) != 0)
		return 0;
	if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
		return 0;

	/* Restart OutFactory */
	FwSmStart(outFactory);
  
  /* Check that there are no allocated packets */
 if (CrFwPcktGetNOfAllocated() != 0)
    return 0;
 
  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;


  printf("successfully checked ---CrPsTestOnBoardConnection.c---\n");
  return 1;
}


/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsServTestOnBoardTestCase2()
{
  /* Check OutCmp Generation to Ground */
  /* NEIN hier probier ich  jetzt nochmal das incmd 17.1 zu testen (aus CrFwIncmdTestCases) */
  
  FwSmDesc_t inFactory, outFactory, outManager, inCmd;
  CrFwPckt_t pckt;
  unsigned short appId;
  unsigned int i;
  FwSmDesc_t outCmpArray[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];
        
  printf("checking ---CrPsTestOnBoardConnection.c---\n");
  appId=2;

  /**
   * Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines
   */
  CrPsInit();

  /**
   * Instantiate all application-specific components, e.g. data pool entries
   */
  setDpOnBoardConnectDestLstItem(1, 0);
  
  CrPsInitApp(appId);
  CrPsInitApp(5);


  /* Instantiate the InFactory */
  inFactory = CrFwInFactoryMake();
  /* Instantiate the OutFactory */
  outFactory = CrFwOutFactoryMake();

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
  
  /* Check component type */
  if (CrFwCmpGetInstanceId(outFactory) != 0)
    return 0;
  if (CrFwCmpGetTypeId(outFactory) != CR_FW_OUTFACTORY_TYPE)
    return 0;

  /* Initialize and Configure OutManager and check success */

  /* Instantiate the first OutManager */
  outManager = CrFwOutManagerMake(0);  /* HIER MUSS ICH 2 NEHMEN WEIL ICH DEN OUT MANAGER NICHT RICHTIG SCHLIEßEN KANN !!!*/

  /* Initialize and Configure OutManager and check success */
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  if (!CrFwCmpIsInConfigured(outManager))
    return 0;    

  /* Allocate the Sample1 InCommand */
  pckt = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetCmdRepId(pckt,40);
  CrFwPcktSetSrc(pckt,1);
  CrFwPcktSetDest(pckt,1);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt, 1, 1, 1, 1);	/* all acknowledgement of success */
  CrFwPcktSetSeqCnt(pckt,2);
  pckt[OFFSET_PAR_LENGTH_IN_CMD_PCKT + 0] = (appId >> 8) & 0xff;
  pckt[OFFSET_PAR_LENGTH_IN_CMD_PCKT + 1] = (appId & 0xFF);

  inCmd = CrFwInFactoryMakeInCmd(pckt);
printf("CrFwGetAppErrCode %d \n",CrFwGetAppErrCode());
  /* Check InCommand state */
  if (!CrFwCmpIsInConfigured(inCmd))
    return 0;
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0;

  printf("CrFwGetAppErrCode %d \n",CrFwGetAppErrCode());
  printf("CrFwOutFactoryGetMaxNOfOutCmp %d \n",CrFwOutFactoryGetMaxNOfOutCmp());

  /*outfactory zumüllen !!!*/
  	/* Create CR_FW_OUTFACTORY_MAX_NOF_OUTCMP OutComponent and then attempt to create one more */
	for (i=0; i<9; i++) {
		outCmpArray[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
                printf("i: %d \n",i);
		if (outCmpArray[i]==NULL)
			return 0;
	}

	CrFwCmpExecute(inCmd);

  printf("test\n");
  printf("CrFwGetAppErrCode %d \n",CrFwGetAppErrCode());

    CrFwSetAppErrCode(crNoAppErr);
      CrFwCmpExecute(inCmd);
  printf("test\n");
printf("CrFwGetAppErrCode %d \n",CrFwGetAppErrCode());
  CrPsExec();
printf("CrFwGetAppErrCode %d \n",CrFwGetAppErrCode());
    CrFwSetAppErrCode(crNoAppErr);
  /* Release the InCommands */
  CrFwInFactoryReleaseInCmd(inCmd);
	for (i=0; i<9; i++)
		CrFwOutFactoryReleaseOutCmp(outCmpArray[i]);
  CrFwCmpReset(outManager);
printf("CrFwGetAppErrCode %d \n",CrFwGetAppErrCode());
/* Shutdown the InFactory and check that no InCommands are allocated */
	CrFwCmpShutdown(inFactory);
	if (CrFwCmpIsStarted(inFactory) != 0)
		return 0;
printf("CrFwGetAppErrCode %d \n",CrFwGetAppErrCode());
	if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
		return 0;
printf("CrFwGetAppErrCode %d \n",CrFwGetAppErrCode());
	/* Restart and initialize the InFactory */
	FwSmStart(inFactory);
	CrFwCmpInit(inFactory);
	CrFwCmpReset(outFactory);  
        CrFwCmpShutdown(outFactory);
 printf("CrFwGetAppErrCode %d \n",CrFwGetAppErrCode());
	if (CrFwCmpIsStarted(outFactory) != 0)
		return 0;
printf("CrFwGetAppErrCode %d \n",CrFwGetAppErrCode());
	if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
		return 0;
printf("CrFwGetAppErrCode %d \n",CrFwGetAppErrCode());
	/* Restart OutFactory */
	FwSmStart(outFactory);
printf("CrFwGetAppErrCode %d \n",CrFwGetAppErrCode());
  /* Check that there are no allocated packets */
 if (CrFwPcktGetNOfAllocated() != 0)
    return 0;
printf("CrFwGetAppErrCode %d \n",CrFwGetAppErrCode());
  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;


  printf("successfully checked ---CrPsTestOnBoardConnection.c---\n");
  return 1;
  
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsServTestOnBoardTestCase3()
{
  FwSmDesc_t outFactory, outCmp;
  printf("checking ---CrPsTestOnBoardConnectionRep.c---\n");
  
  /* Instantiate the OutFactory */
  outFactory = CrFwOutFactoryMake();

  /* Initialize and Configure OutFactory and check success */
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;

  /* Allocate two OutComponents */
  outCmp = CrFwOutFactoryMakeOutCmp(17,4,0,0);

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
  
  CrFwCmpExecute(outCmp);
    
      /* Check and reset application error code */
  if (CrFwGetAppErrCode() != crOutStreamUndefDest)
   return 0;
  CrFwSetAppErrCode(crNoAppErr);
  
  /*Check if Repeatcheck always returns 0*/
  if (CrPsTestOnBoardConnectionRepRepeatCheck(outCmp) != 0)
      return 0;
  
  /* Release the OutComponents */
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;
  
  printf("successfully checked ---CrPsTestOnBoardConnectionRep.c---\n");       
  return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsServTestOnBoardTestCase4()
{
  /*Free*/
  return 1;
}
/* ---------------------------------------------------------------------------------------------*/
