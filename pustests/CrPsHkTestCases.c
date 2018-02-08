/**
 * @file CrPsHkTestCases.h
 * @ingroup PUSTestsuite
 *
 * @brief Implementation of the test cases for the Housekeepint Service components.
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
#include <CrPsUtilitiesServHk.h>
#include <CrPsUtilitiesServReqVerif.h>
#include "config/CrFwOutFactoryUserPar.h"
#include <Services/Housekeeping/InCmd/CrPsHkCreateCmd.h>
#include <Services/Housekeeping/InCmd/CrPsHkDeleteCmd.h>
#include <Services/Housekeeping/InCmd/CrPsHkEnableCmd.h>
#include <Services/Housekeeping/InCmd/CrPsHkDisableCmd.h>
#include <Services/Housekeeping/InCmd/CrPsHkRepStructCmd.h>
#include <Services/Housekeeping/InCmd/CrPsHkOneShotCmd.h>

#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServHk.h>

#include <Services/General/CrPsPktServHk.h>
#include <Services/General/CrPsPktServHkSupp.h>

/* Include system files */
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#define datapool8bit_ID       54   /* there is non yet (DpIdOnBoardConnectDest .. CrPsDestSrc_t)*/
#define datapool16bit_ID      53   /* DpIdAreYouAliveSrc        .. CrPsDestSrc_t */  
#define datapool32bit_ID       6   /* DpIdAreYouAliveTimeOut    .. CrPsTimeOut_t */
#define datapool8bitarray_ID   3   /* DpIdisEnabled             .. CrPsFlag_t Array */
#define datapool16bitarray_ID  7   /* DpIdOnBoardConnectDestLst .. CrPsDestSrc_t Array */
#define datapool32bitarray_ID 29   /* DpIdcycleCnt              .. CrFwCounterU4_t Array */

#define datapool32bit_IDa     41   /* DpIdnOfAccFailed          .. CrFwCounterU4_t */
#define datapool32bit_IDb     42   /* DpIdnOfPrgrFailed         .. CrFwCounterU4_t */
#define datapool32bit_IDc     43   /* DpIdnOfReroutingFailed    .. CrFwCounterU4_t */
#define datapool32bit_IDd     44   /* DpIdnOfStartFailed        .. CrFwCounterU4_t */
#define datapool32bit_IDe     45   /* DpIdnOfTermFailed         .. CrFwCounterU4_t */


/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase1() /*for the Create command*/
{
  /* Check Service 3 */
  FwSmDesc_t inFactory, outFactory, outManager, inCmd, outCmp, outCmpArr[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];
  CrFwPckt_t pckt;
  CrFwCmpData_t *cmpData;
  CrFwCmpData_t *outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  uint32_t i;

  /* Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines */
  CrPsInitServReqVerif();  
  CrPsInitServHk();
  CrPsExecServHk();

  /* manually delete all sid's in the Datapool*/ 
  for (i = 0; i < HK_N_REP_DEF; i++)
  {
    setDpsidItem(i, 0);
  }

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

  /* Allocate a 3,1 Packet to get outcome success*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,1);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkCreateCmdCollectionInterval(pckt, 4);  
  setHkCreateCmdN1(pckt, 1);
  setHkCreateCmdN1ParamIdItem(pckt, 1, datapool16bit_ID);
  setHkCreateCmdNFA(pckt, 2);
  setHkCreateCmdSCSampleRepNumItem(pckt, 1, 2);
  setHkCreateCmdN2(pckt, 1, 3);
  setHkCreateCmdN2ParamIdItem(pckt, 1, 1, datapool32bit_IDa);
  setHkCreateCmdN2ParamIdItem(pckt, 1, 2, datapool32bit_IDb);
  setHkCreateCmdN2ParamIdItem(pckt, 1, 3, datapool32bit_IDc);

  setHkCreateCmdSCSampleRepNumItem(pckt, 2, 2);
  setHkCreateCmdN2(pckt, 2, 3);
  setHkCreateCmdN2ParamIdItem(pckt, 2, 1, datapool32bit_ID);
  setHkCreateCmdN2ParamIdItem(pckt, 2, 2, datapool8bitarray_ID);
  setHkCreateCmdN2ParamIdItem(pckt, 2, 3, datapool32bitarray_ID);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,1 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 1)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start Action of the 3,1 command and check the outcome = success */
  CrPsHkCreateCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Get the Data from the out Manager (there is only one Component) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];
  
  /* Check if there is a 3,25 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 3)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 25)
    return 0;
  if (CrFwOutCmpGetDiscriminant(outCmp) != 3)
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

  /* Call the Progress Action of the 3,1 command and check the outcome = success */
  CrPsHkCreateCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome !=1)
  {
    return 0;
  }

  /* Call the Termination Action of the 3,1 command and check the outcome = success */
  CrPsHkCreateCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome !=1)
  {
    return 0;
  }

 /*Check if SID is now in the Datapool */
  if (getDpsidItem(0) != 3)
    return 0;

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Allocate a 3,1 Packet with a wrong sid (0)  to get outcome VER_RDL_CONSTR */
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,1);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkCreateCmdCollectionInterval(pckt, 4);  
  setHkCreateCmdN1(pckt, 1);
  setHkCreateCmdN1ParamIdItem(pckt, 1, datapool16bit_ID);
  setHkCreateCmdNFA(pckt, 2);
  setHkCreateCmdSCSampleRepNumItem(pckt, 1, 2);
  setHkCreateCmdN2(pckt, 1, 3);
  setHkCreateCmdN2ParamIdItem(pckt, 1, 1, datapool32bit_IDa);
  setHkCreateCmdN2ParamIdItem(pckt, 1, 2, datapool32bit_IDb);
  setHkCreateCmdN2ParamIdItem(pckt, 1, 3, datapool32bit_IDc);

  setHkCreateCmdSCSampleRepNumItem(pckt, 2, 2);
  setHkCreateCmdN2(pckt, 2, 3);
  setHkCreateCmdN2ParamIdItem(pckt, 2, 1, datapool32bit_ID);
  setHkCreateCmdN2ParamIdItem(pckt, 2, 2, datapool8bitarray_ID);
  setHkCreateCmdN2ParamIdItem(pckt, 2, 3, datapool32bitarray_ID);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,1 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 1)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start Action of the 3,1 command and check the outcome = VER_RDL_CONSTR because of the wrong SID*/
  CrPsHkCreateCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != VER_RDL_CONSTR) 
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /*manually delete the sid*/
  setDpsidItem(0, 0);

  /* Allocate a 3,2 Packet to get outcome success*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,2);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkCreateCmdCollectionInterval(pckt, 4);  
  setHkCreateCmdN1(pckt, 1);
  setHkCreateCmdN1ParamIdItem(pckt, 1, datapool16bit_ID);
  setHkCreateCmdNFA(pckt, 2);
  setHkCreateCmdSCSampleRepNumItem(pckt, 1, 2);
  setHkCreateCmdN2(pckt, 1, 3);
  setHkCreateCmdN2ParamIdItem(pckt, 1, 1, datapool32bit_IDa);
  setHkCreateCmdN2ParamIdItem(pckt, 1, 2, datapool32bit_IDb);
  setHkCreateCmdN2ParamIdItem(pckt, 1, 3, datapool32bit_IDc);

  setHkCreateCmdSCSampleRepNumItem(pckt, 2, 2);
  setHkCreateCmdN2(pckt, 2, 3);
  setHkCreateCmdN2ParamIdItem(pckt, 2, 1, datapool32bit_ID);
  setHkCreateCmdN2ParamIdItem(pckt, 2, 2, datapool8bitarray_ID);
  setHkCreateCmdN2ParamIdItem(pckt, 2, 3, datapool32bitarray_ID);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,2 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 2)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start Action  of the 3.2 command and check the outcome = success */
  CrPsHkCreateCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Get the Data from the out Manager (there is only one Component) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];
  
  /* Check if there is a 3,25 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 3)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 26)
    return 0;
  if (CrFwOutCmpGetDiscriminant(outCmp) != 3)
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

  /* Call the Progress Action of the 3,2 command and check the outcome = success */
  CrPsHkCreateCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Call the Termination Action of the 3,2 command and check the outcome = success */
  CrPsHkCreateCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /*Check if SID is now in the Datapool */
  if (getDpsidItem(0) != 3)
    return 0;

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Allocate the a 3,1 Packet to trigger an Error! (SID in USE)*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,1);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkCreateCmdCollectionInterval(pckt, 4);  
  setHkCreateCmdN1(pckt, 1);
  setHkCreateCmdN1ParamIdItem(pckt, 1, datapool16bit_ID);
  setHkCreateCmdNFA(pckt, 0);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,1 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 1)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start Action of the 3,1 command and check the outcome = VER_SID_IN_USE, because this sid is already in the database */
  CrPsHkCreateCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != VER_SID_IN_USE) /* SID in USE*/
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* manually set all sid's in the Datapool*/
  for (i = 0; i < HK_N_REP_DEF; i++)
    {
      setDpsidItem(i, i+1);
    }

  /* Allocate the same 3,1 Packet to trigger an Error! (Full RDL) no slot available*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,1);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkCreateCmdCollectionInterval(pckt, 4);  
  setHkCreateCmdN1(pckt, 1);
  setHkCreateCmdN1ParamIdItem(pckt, 1, datapool16bit_ID);
  setHkCreateCmdNFA(pckt, 0);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,1 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 1)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start Action of the 3,1 command and check the outcome = VER_FULL_RDL because now all SIDS where set in the DataPool */
  CrPsHkCreateCmdStartAction(inCmd);

  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != VER_FULL_RDL) 
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* manually set all sid's in the Datapool to 0 */
  for (i = 0; i < HK_N_REP_DEF; i++)
    {
      setDpsidItem(i, 0);
    }

  /* Allocate a 3,1 Packet to trigger an Error! (Error in the Construction) min. one constraint from table 9.1 is not satisfied*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,1);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkCreateCmdCollectionInterval(pckt, 4);  
  setHkCreateCmdN1(pckt, HK_N_REP_DEF+2);
  setHkCreateCmdN1ParamIdItem(pckt, 1, datapool16bit_ID);
  setHkCreateCmdNFA(pckt, 0);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,1 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 1)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 
  
  /* Call the Start Action of the 3,1 command and check the outcome = VER_RDL_CONSTR Error in the Construction of the RDL */
  CrPsHkCreateCmdStartAction(inCmd);    
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != VER_RDL_CONSTR) 
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Allocate a 3,1 Packet to trigger an Error! The same data item identifier appears twice*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,1);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkCreateCmdCollectionInterval(pckt, 4);  
  setHkCreateCmdN1(pckt, 2);
  setHkCreateCmdN1ParamIdItem(pckt, 1, datapool16bit_ID);
  setHkCreateCmdN1ParamIdItem(pckt, 2, datapool16bit_ID);
  setHkCreateCmdNFA(pckt, 0);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,1 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 1)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start Action of the 3,1 command and check the outcome = VER_DUPL_DI because the parameter id exists 2 times in the packet */
  CrPsHkCreateCmdStartAction(inCmd);    
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != VER_DUPL_DI) 
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* manually set all sid's in the Datapool to 0*/
  for (i = 0; i < HK_N_REP_DEF; i++)
  {
    setDpsidItem(i, 0);
  }

  /* Allocate a 3,1 Packet to trigger an Error! (OutFactory full)*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,1);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkCreateCmdCollectionInterval(pckt, 4);  
  setHkCreateCmdN1(pckt, 1);
  setHkCreateCmdN1ParamIdItem(pckt, 1, datapool16bit_ID);
  setHkCreateCmdNFA(pckt, 0);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,1 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 1)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Fill the outfactory so that an Error could occur (leave one free slot) */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
  {
    outCmpArr[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
  }

  /* Call the Start Action of the 3,1 command and check the outcome = VER_REP_CR_FD  the Outfactory cannot create on more component */
  CrPsHkCreateCmdStartAction(inCmd);    
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != VER_REP_CR_FD) 
  {
    return 0;
  }

  /* Release all outcomponents, that have been created to fill the outfactory */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
  { 
    CrFwOutFactoryReleaseOutCmp(outCmpArr[i]);
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /*Reset application error Corde*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Allocate a 3,1 Packet to trigger an Error! VER_OUTLOADER_FD .. but this is not implemented now*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,1);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkCreateCmdCollectionInterval(pckt, 4);  
  setHkCreateCmdN1(pckt, 2); 
  setHkCreateCmdN1ParamIdItem(pckt, 1, datapool16bit_ID);
  setHkCreateCmdN1ParamIdItem(pckt, 2, datapool16bit_ID);
  setHkCreateCmdNFA(pckt, 0);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,1 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 1)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* TODO: triger else guard of G6 to get Error: VER_OUTLOADER_FD */
  CrPsHkCreateCmdStartAction(inCmd);    

  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != VER_DUPL_DI)  /*TODO: VER_OUTLOADER_FD */
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase2() /*for the Delete, Enable and Disable commands*/
{
  /* Check Service 3*/
  FwSmDesc_t inFactory, outFactory, outManager, inCmd, outCmp;
  CrFwPckt_t pckt;
  CrFwCmpData_t *cmpData;
  CrFwCmpData_t *outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  uint32_t i;

  /* Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines */
  CrPsInitServReqVerif();  
  CrPsInitServHk();

  /* manually delete all sid's in the Datapool*/ /*TODO remove after the init function does this*/
  for (i = 0; i < HK_N_REP_DEF; i++)
  {
    setDpsidItem(i, 0);
  }

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

  /* Initialize and Configure OutFactory, InFactory and OutManager and check success */
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

  /* manually set a sid in the Datapool and check if it is reset by the 3,3 command*/
  setDpsidItem(0, 3);
  setDpisEnabledItem(0,0);

  /* Allocate a 3,3 Packet to get outcome success*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkDeleteCmdN(pckt, 2);
  setHkDeleteCmdRepStrucIdItem(pckt, 1, 1);
  setHkDeleteCmdRepStrucIdItem(pckt, 1, 3);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,3 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 3)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start, progress and termination Action of the 3,3 command and check the outcome = success */
  CrPsHkDeleteCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsHkDeleteCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsHkDeleteCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /*Check if SID is now gone in the Datapool */
  if (getDpsidItem(0) != 0)
    return 0;

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* manually set a sid in the Datapool and check if it is reset by the 3,4 command*/
  setDpsidItem(0, 3);

  /* Allocate a 3,4 Packet to get outcome success*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,4);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkDeleteCmdN(pckt, 2);
  setHkDeleteCmdRepStrucIdItem(pckt, 1, 1);
  setHkDeleteCmdRepStrucIdItem(pckt, 1, 3);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,4 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 4)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start, progress and termination Action of the 3,4 command and check the outcome = success */
  CrPsHkDeleteCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsHkDeleteCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsHkDeleteCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /*Check if SID is now gone in the Datapool */
  if (getDpsidItem(0) != 0)
    return 0;

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Allocate a 3,3 Packet to get Error All SID's are invalid and a 1,4 is created! */
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkDeleteCmdN(pckt, 1);
  setHkDeleteCmdRepStrucIdItem(pckt, 1, 3);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,3 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 3)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start Action of the 3,3 command and check the outcome = VER_S3S_START_FD -> all Sids are invalid */
  CrPsHkDeleteCmdStartAction(inCmd);

  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != VER_S3S_START_FD)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
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
  if (CrFwOutCmpGetDiscriminant(outCmp) != VER_ILL_SID)
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

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* manually set a sid in the Datapool*/
  setDpsidItem(0, 3);
  setDpisEnabledItem(0,1);

  /* Allocate a 3,3 Packet to get Error one cannot delete an enabled sid !*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkDeleteCmdN(pckt, 1);
  setHkDeleteCmdRepStrucIdItem(pckt, 1, 3);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,3 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 3)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start Action of the 3,3 command and check the outcome = VER_S3S_START_FD -> SID is enabled */
  CrPsHkDeleteCmdStartAction(inCmd);

  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != VER_S3S_START_FD)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
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
  if (CrFwOutCmpGetDiscriminant(outCmp) != VER_ENABLED_SID)
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

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* manually set a sid in the Datapool*/
  setDpsidItem(0, 3);
  setDpsidItem(1, 1);
  setDpisEnabledItem(0,0);
  setDpisEnabledItem(1,0);

  /* Allocate a 3,5 Packet to get outcome success and enable a SID*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,5);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkEnableCmdN(pckt, 2);
  setHkEnableCmdRepStrucIdItem(pckt, 1, 3);
  setHkEnableCmdRepStrucIdItem(pckt, 2, 1);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,5 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 5)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start, progress and termination Action of the 3,5 command and check the outcome = success */
  CrPsHkEnableCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsHkEnableCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsHkEnableCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /*Check if SID is enabled in the Datapool */
  if (getDpisEnabledItem(0) != 1)
    return 0;

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

/* manually set a sid in the Datapool*/
  setDpsidItem(0, 3);
  setDpisEnabledItem(0,0);

  /* Allocate a 3,7 Packet to get outcome success and enable a SID*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,7);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkEnableCmdN(pckt, 2);
  setHkEnableCmdRepStrucIdItem(pckt, 1, 3);
  setHkEnableCmdRepStrucIdItem(pckt, 2, 1);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,7 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 7)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start, progress and termination Action of the 3,7 command and check the outcome = success */
  CrPsHkEnableCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome !=1)
  {
    return 0;
  }

  CrPsHkEnableCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome !=1)
  {
    return 0;
  }

  CrPsHkEnableCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome !=1)
  {
    return 0;
  }

  /*Check if SID is enabled in the Datapool */
  if (getDpisEnabledItem(0) != 1)
    return 0;

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* manually delete a sid in the Datapool*/
  setDpsidItem(0, 0);
  setDpisEnabledItem(0,0);

  /* Allocate a 3,5 Packet to get outcome VER_SID_START_FD .. wrong SID (sid not in RDL)*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,5);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkEnableCmdN(pckt, 1);
  setHkEnableCmdRepStrucIdItem(pckt, 1, 3);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,5 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 5)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start Action of the 3,5 command and check the outcome = VER_S3S_START_FD -> VER_ILL_SID -> sid is not in RDL*/
  CrPsHkEnableCmdStartAction(inCmd);

  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != VER_SID_START_FD)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
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
  if (CrFwOutCmpGetDiscriminant(outCmp) != VER_ILL_SID)
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

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* manually set a sid in the Datapool*/
  setDpsidItem(0, 3);
  setDpisEnabledItem(0,1);

  /* Allocate a 3,6 Packet to get outcome success*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,6);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkDisableCmdN(pckt, 2);
  setHkDisableCmdRepStrucIdItem(pckt, 1, 3);
  setHkDisableCmdRepStrucIdItem(pckt, 2, 1);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,6 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 6)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start, progress and termination Action of the 3,6 command and check the outcome = success */
  CrPsHkDisableCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsHkDisableCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsHkDisableCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /*Check if SID is disabled in the Datapool */
  if (getDpisEnabledItem(0) != 0)
    return 0;

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

 /* manually set a sid in the Datapool*/
  setDpsidItem(0, 3);
  setDpisEnabledItem(0,1);

  /* Allocate a 3,8 Packet to get outcome success*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,8);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkDisableCmdN(pckt, 2);
  setHkDisableCmdRepStrucIdItem(pckt, 1, 3);
  setHkDisableCmdRepStrucIdItem(pckt, 2, 1);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,8 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 8)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start, progress and termination Action of the 3,8 command and check the outcome = success */
  CrPsHkDisableCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsHkDisableCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsHkDisableCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /*Check if SID is disabled in the Datapool */
  if (getDpisEnabledItem(0) != 0)
    return 0;

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* manually delete a sid in the Datapool*/
  setDpsidItem(0, 0);
  setDpisEnabledItem(0,0);

  /* Allocate a 3,6 Packet to get outcome failed*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,6);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkEnableCmdN(pckt, 1);
  setHkEnableCmdRepStrucIdItem(pckt, 1, 3);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,6 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 6)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start Action of the 3,6 command and check the outcome = VER_S3S_START_FD -> VER_ILL_SID -> sid is not in RDL*/
  CrPsHkDisableCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != VER_SID_START_FD)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
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
  if (CrFwOutCmpGetDiscriminant(outCmp) != VER_ILL_SID)
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

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase3() /*for the Structure Rep and OneShor commands*/
{
    /* Check Service 3 */
  FwSmDesc_t inFactory, outFactory, outManager, inCmd, outCmp, outCmpArr[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];
  CrFwPckt_t pckt;
  CrFwCmpData_t *cmpData;
  CrFwCmpData_t *outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  uint32_t i;

  /* Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines */
  CrPsInitServReqVerif();  
  CrPsInitServHk();

  /* manually delete all sid's in the Datapool*/ /*TODO remove after the init function does this*/
  for (i = 0; i < HK_N_REP_DEF; i++)
  {
    setDpsidItem(i, 0);
  }

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

  /* Initialize and Configure OutFactory, InFactory and OutManager and check success */
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

  /* manually set a sid in the Datapool*/
  setDpsidItem(0, 1);
  setDpsidItem(1, 3);
  setDpsidItem(2, 0);

  /*SID 1*/
  setDpperiodItem(0, 8);
  setDpisEnabledItem(0,1);
  setDpnSimpleItem(0, 0); /*N1*/
  setDplstSampleRepItem(0, 4);
  setDplstNSampRepItem(0, 3);
  setDplstIdItem(0, datapool32bit_ID);
  setDplstIdItem(1, datapool16bit_ID);
  setDplstIdItem(2, datapool8bit_ID);

  /*SID 3*/
  setDpperiodItem(1, 8);
  setDpisEnabledItem(1,1);
  setDpnSimpleItem(1, 3); /*N1*/
  setDplstIdItem(HK_MAX_N_ITEMS + 0, datapool32bitarray_ID);
  setDplstIdItem(HK_MAX_N_ITEMS + 1, datapool16bitarray_ID);
  setDplstIdItem(HK_MAX_N_ITEMS + 2, datapool8bitarray_ID);
  setDplstSampleRepItem(HK_MAX_N_GR, 2);
  setDplstNSampRepItem(HK_MAX_N_GR, 2); /*N2*/
  setDplstIdItem(HK_MAX_N_ITEMS + 3, datapool32bit_ID);
  setDplstIdItem(HK_MAX_N_ITEMS + 4, datapool16bit_ID);
  setDplstIdItem(HK_MAX_N_ITEMS + 5, datapool8bit_ID);

  /* Allocate a 3,9 Packet to get outcome success*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,9);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkRepStructCmdN(pckt, 2);
  setHkRepStructCmdRepStrucIdItem(pckt, 1, 1);
  setHkRepStructCmdRepStrucIdItem(pckt, 2, 3);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,9 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 9)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start progress and termination Action of the 3,9 command and check the outcome = continue and then success */
  CrPsHkRepStructCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsHkRepStructCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 2) /*CONTINUE*/
  {
    return 0;
  }
  
  CrPsHkRepStructCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 2) /*CONTINUE*/
  {
    return 0;
  }

  CrPsHkRepStructCmdProgressAction(inCmd);
  if (cmpData->outcome != 1) /*SUCCESS*/
  {
    return 0;
  }

  CrPsHkRepStructCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1) /*SUCCESS*/
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Get the Data from the out Manager (there is only one Component) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];

  /* Check if there is a 3,10 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 3)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 10)
    return 0;
  
  /*Release the OutComponent and reset the OutManager*/
  CrFwOutFactoryReleaseOutCmp(outCmp);
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  /*Check if an OutComponent Release Error occures*/
  if (CrFwGetAppErrCode() != crOutCmpRelErr)
    return 0;

  /*Reset application error Corde*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Allocate a 3,11 Packet to get outcome success*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,11);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkRepStructCmdN(pckt, 2);
  setHkRepStructCmdRepStrucIdItem(pckt, 1, 1);
  setHkRepStructCmdRepStrucIdItem(pckt, 2, 3);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,9 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 11)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start progress and termination Action of the 3,9 command and check the outcome = continue and then success */
  CrPsHkRepStructCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1) /*SUCCESS*/
  {
    return 0;
  }

  CrPsHkRepStructCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 2) /*CONTINUE*/
  {
    return 0;
  }
  
  CrPsHkRepStructCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 2) /*CONTINUE*/
  {
    return 0;
  }

  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  CrPsHkRepStructCmdProgressAction(inCmd);
  if (cmpData->outcome != 1) /*SUCCESS*/
  {
    return 0;
  }

  CrPsHkRepStructCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome !=1) /*SUCCESS*/
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Get the Data from the out Manager (there is only one Component) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];

  /* Check if there is a 3,12 Command waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 3)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 12)
    return 0;

  /*Release the OutComponent and Reset the OutManager*/
  CrFwOutFactoryReleaseOutCmp(outCmp);
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  /*Check if an OutComponent Release Error occures*/
  if (CrFwGetAppErrCode() != crOutCmpRelErr)
    return 0;

  /*Reset application error Corde*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Allocate a 3,9 Packet to get OutFactory Fail*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,9);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,3);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkRepStructCmdN(pckt, 1);
  setHkRepStructCmdRepStrucIdItem(pckt, 1, 3);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,9 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 9)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Fill the outfactory so that an Error could occur (leave one free slot) */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
  {
    outCmpArr[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
  }

  CrPsHkRepStructCmdStartAction(inCmd);

  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsHkRepStructCmdProgressAction(inCmd);

  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1) /*SUCCESS*/
  {
    return 0;
  }

  /* Check Application Error! (crOutCmpAllocationFail) */
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /* Reset the Application Error */
  CrFwSetAppErrCode(crNoAppErr);

  CrPsHkRepStructCmdTerminationAction(inCmd);

  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Release all outcomponents, that have been created to fill the outfactory */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
  { 
    CrFwOutFactoryReleaseOutCmp(outCmpArr[i]);
  }

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Allocate a 3,27 Packet to get outcome success*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,27);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkOneShotCmdN(pckt, 2);
  setHkOneShotCmdRepStrucIdItem(pckt, 1, 1);
  setHkOneShotCmdRepStrucIdItem(pckt, 2, 3);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,27 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 27)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Termination Action early to get outcome = 0 */
  CrPsHkOneShotCmdTerminationAction(inCmd);

  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 0)
  {
    return 0;
  }

  /* Call the Start progress and termination Action of the 3,27 command and check the outcome = success */
  CrPsHkOneShotCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsHkOneShotCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsHkOneShotCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;


  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Allocate a 3,28 Packet to get outcome success*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,28);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkOneShotCmdN(pckt, 2);
  setHkOneShotCmdRepStrucIdItem(pckt, 1, 1);
  setHkOneShotCmdRepStrucIdItem(pckt, 2, 3);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,28 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 28)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start progress and termination Action of the 3,27 command and check the outcome = success */
  CrPsHkOneShotCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsHkOneShotCmdProgressAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsHkOneShotCmdTerminationAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;


  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Allocate a 3,1 Packet to trigger an error*/
  pckt = CrFwPcktMake(80);
  CrFwPcktSetServType(pckt,3);
  CrFwPcktSetServSubType(pckt,1);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,0);  

  setHkOneShotCmdN(pckt, 2);
  setHkOneShotCmdRepStrucIdItem(pckt, 1, 1);
  setHkOneShotCmdRepStrucIdItem(pckt, 2, 3);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 3,1 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 3)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 1)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Call the Start Action of the 3,27 command and check the outcome ?? */
  CrPsHkOneShotCmdStartAction(inCmd);
  cmpData = (CrFwCmpData_t*) FwSmGetData(inCmd);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  return 1;
}


/*--------------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase4() /*for all the reports*/
{
    /* Check Service 3 */
  FwSmDesc_t inFactory, outFactory, outManager, outCmp;
  CrFwCmpData_t *cmpData;
  uint32_t i;

  /* Instantiate all relevant CORDET Framework PUS Extension components, e.g. all the procedures and state machines */
  CrPsInitServReqVerif();  
  CrPsInitServHk();

  /* manually delete all sid's in the Datapool*/ 
  for (i = 0; i < HK_N_REP_DEF; i++)
  {
    setDpsidItem(i, 0);
  }

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

  /* Initialize and Configure OutFactory, InFactory and OutManager and check success */
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

  /* manually set a sid in the Datapool*/
  setDpsidItem(0, 1);
  setDpsidItem(1, 3);
  setDpsidItem(2, 0);

  /*SID 1*/
  setDpperiodItem(0, 8);
  setDpisEnabledItem(0,1);
  setDpnSimpleItem(0, 0); /*N1*/
  setDplstSampleRepItem(0, 4);
  setDplstNSampRepItem(0, 3);
  setDplstIdItem(0, datapool32bit_ID);
  setDplstIdItem(1, datapool16bit_ID);
  setDplstIdItem(2, datapool8bit_ID);

  /*SID 3*/
  setDpperiodItem(1, 8);
  setDpisEnabledItem(1,1);
  setDpnSimpleItem(1, 3); /*N1*/
  setDplstIdItem(HK_MAX_N_ITEMS + 0, datapool32bitarray_ID);
  setDplstIdItem(HK_MAX_N_ITEMS + 1, datapool16bitarray_ID);
  setDplstIdItem(HK_MAX_N_ITEMS + 2, datapool8bitarray_ID);
  setDplstSampleRepItem(HK_MAX_N_GR, 2);
  setDplstNSampRepItem(HK_MAX_N_GR, 2); /*N2*/
  setDplstIdItem(HK_MAX_N_ITEMS + 3, datapool32bit_ID);
  setDplstIdItem(HK_MAX_N_ITEMS + 4, datapool16bit_ID);
  setDplstIdItem(HK_MAX_N_ITEMS + 5, datapool8bit_ID);

  /* Create a 3,25 Packet to test the housekeeping report and the report structure report with SID = 1*/
  outCmp = CrFwOutFactoryMakeOutCmp(3,25,1,80);
  CrPsHkRepEnableCheck(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
    
  CrPsHkRepReadyCheck(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  if (cmpData->outcome != 1)
  {
    return 0;
  }
    
  CrPsHkRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  outCmp = CrFwOutFactoryMakeOutCmp(3,10,1,80);  
  CrPsHkRepStructRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Create a 3,26 Packet to test the housekeeping report and the report structure report with SID = 3 for more coverage*/
  outCmp = CrFwOutFactoryMakeOutCmp(3,26,3,80);

  CrPsHkRepEnableCheck(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  if (cmpData->outcome !=1)
  {
    return 0;
  }

  CrPsHkRepReadyCheck(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  if (cmpData->outcome !=1)
  {
    return 0;
  }

  CrPsHkRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  if (cmpData->outcome !=1)
  {
    return 0;
  }
  
  outCmp = CrFwOutFactoryMakeOutCmp(3,12,3,80);  
  CrPsHkRepStructRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  if (cmpData->outcome !=1)
  {
    return 0;
  }
    
  /* Create a 3,25 Packet to test the housekeeping report and the report structure report with SID = 2 to trigger an error (sid does not exist)*/
  outCmp = CrFwOutFactoryMakeOutCmp(3,25,2,80);

  CrPsHkRepEnableCheck(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsHkRepReadyCheck(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  CrPsHkRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  outCmp = CrFwOutFactoryMakeOutCmp(3,10,2,80);  
  CrPsHkRepStructRepUpdateAction(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  if (cmpData->outcome != 1)
  {
    return 0;
  }

  /* Disable a SID so the readycheck fails*/
  setDpisEnabledItem(1,0);

  /* Create a 3,25 Packet to test the housekeeping report for the readycheck to fail!*/
  outCmp = CrFwOutFactoryMakeOutCmp(3,25,3,80);

  CrPsHkRepEnableCheck(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  if (cmpData->outcome !=1)
  {
    return 0;
  }

  CrPsHkRepReadyCheck(outCmp);
  cmpData = (CrFwCmpData_t*) FwSmGetData(outCmp);
  if (cmpData->outcome !=0)
  {
    return 0;
  }

  /* call the ready check again for some coverage */
  CrPsHkRepReadyCheck(outCmp);
  CrPsHkRepReadyCheck(outCmp);
  CrPsHkRepReadyCheck(outCmp);
  CrPsHkRepReadyCheck(outCmp);
  CrPsHkRepReadyCheck(outCmp);
  CrPsHkRepReadyCheck(outCmp);
  CrPsHkRepReadyCheck(outCmp);
  CrPsHkRepReadyCheck(outCmp);

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


