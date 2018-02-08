/**
 * @file CrPsServiceVeriTestCase.c
 * @ingroup PUSTestsuite
 *
 * @brief Implementation of test cases for the Request Verification Service Components.
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
/* Include configuration files */
#include "CrFwInStreamUserPar.h" /* TODO: CrPsInStreamUserPar.h" */
#include "CrFwOutRegistryUserPar.h" /* TODO: CrPsOutRegistryUserPar.h */
#include "CrFwOutFactoryUserPar.h"
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

#include <CrPsUtilitiesServReqVerif.h>
#include <Services/General/CrPsConstants.h>
#include <CrPsPkt.h>
#include "DataPool/CrPsDpServReqVerif.h"

/* Include system files */
#include <stdlib.h>
#include <unistd.h>


/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsServVeriTestCase1()
{
  /* Check Service 1 */
  unsigned short i;
  FwSmDesc_t inFactory, outFactory, outManager, inCmd, outCmp, outCmpArr[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP], inRep, inManager;
  CrFwPckt_t pckt, pckt2;
  CrFwCmpData_t* outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  unsigned short ACK_WRONG_CHKSM = 1002, pcktID;

  /* run all getters for the procedure descriptors */
  CrPsInitServReqVerif();
  CrPsExecServReqVerif();

  /* Instantiate the OutFactory, InFactory, OutManager */
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

  /* Allocate a 17,1 Packet */
  pckt = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,1);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetCmdRepType(pckt, crCmdType);
  CrFwPcktSetCmdRepId(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,0);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,1,1,1,1);
  CrFwPcktSetSeqCnt(pckt,2);
  
  /* Getting the Packet ID so that we can check that in the datapool later */
  pcktID = getTmHeaderAPID(pckt);

  /* Check if number of Allocated Packets now is 1 */
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0 */
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

  /* Successful Acceptance Verification Report*/
  /* Standard Check Service (1,1) */
  SendReqVerifAccSuccRep(inCmd, CRPS_REQVERIF_ACC_SUCC);

  /* Check if number of Allocated OutComponents = 1*/
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager = 1*/
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 1)
    return 0;

  /* Get the Data from the out Manager */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[CrFwOutManagerGetNOfLoadedOutCmp(outManager)-1];

  /* Check if there is a 1,1 Report waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 1)
    return 0;

  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check that all DataPool Variables concerning (1,2) are initially 0 */
  if (getDpfailCodeAccFailed() != 0)
    return 0;
  if (getDpnOfAccFailed() != 0)
    return 0;
  if (getDppcktIdAccFailed() != 0)
    return 0;

  /* Failed Acceptance Verificatin Report */
  /* Standard Check Service (1,2) */
  SendReqVerifAccFailRep(inCmd, CRPS_REQVERIF_ACC_FAIL);

  /* Check if number of Allocated OutComponents = 1*/
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager = 2*/
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 2)
    return 0;

  /* Check that all DataPool Variables concerning (1,2) are updated */
  if (getDpfailCodeAccFailed() != 2) /* TODO ist es richtig dass hier 2 rein gehört als failure code ??*/
    return 0;
  if (getDpnOfAccFailed() != 1)
    return 0;
  if (getDppcktIdAccFailed() != pcktID)
    return 0;

  /* Get the Data from the out Manager */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[CrFwOutManagerGetNOfLoadedOutCmp(outManager)-1];
  
  /* Check if there is a 1,2 Report waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 2)
    return 0;

  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /*Successful Start of Execution Verification Report*/
  /*Standard Check Service (1,3)*/
  SendReqVerifAccSuccRep(inCmd, CRPS_REQVERIF_START_SUCC);

  /* Check if number of Allocated OutComponents = 1*/
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager = 3*/
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 3)
    return 0;

  /* Get the Data from the out Manager */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[CrFwOutManagerGetNOfLoadedOutCmp(outManager)-1];

  /* Check if there is a 1,3 Report waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 3)
    return 0;

  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check that all DataPool Variables concerning (1,4) are initially 0 */
  if (getDpfailCodeStartFailed() != 0)
    return 0;
  if (getDpnOfStartFailed() != 0)
    return 0;
  if (getDppcktIdStartFailed() != 0)
    return 0;

  /* Failed Start of Execution Verification Report */
  /* Standard Check Service (1,4) */
  SendReqVerifCmdFailRep(inCmd, CRPS_REQVERIF_START_FAIL, ACK_WRONG_CHKSM);

  /* Check if number of Allocated OutComponents = 1*/
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager = 4*/
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 4)
    return 0;

  /* Check that all DataPool Variables concerning (1.4) are updated */
  if (getDpfailCodeStartFailed() != ACK_WRONG_CHKSM)
    return 0;
  if (getDpnOfStartFailed() != 1)
    return 0;
  if (getDppcktIdStartFailed() != pcktID)
    return 0;

  /* Get the Data from the out Manager */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[CrFwOutManagerGetNOfLoadedOutCmp(outManager)-1];
  
  /* Check if there is a 1,4 Report waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 4)
    return 0;

  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;
 
  /* Successful Progress of Execution Verification Report */
  /* Standard Check Service (1,5) */
  SendReqVerifPrgrSuccRep(inCmd, CRPS_REQVERIF_PROG_SUCC);

  /* Check if number of Allocated OutComponents = 1*/
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager = 5*/
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 5)
    return 0;

  /* Get the Data from the out Manager */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[CrFwOutManagerGetNOfLoadedOutCmp(outManager)-1];

  /* Check if there is a 1.5 Report waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 5)
    return 0;

  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check that all DataPool Variables concerning (1,6) are initially 0 */
  if (getDpfailCodePrgrFailed() != 0)
    return 0;
  if (getDpnOfPrgrFailed() != 0)
    return 0;
  if (getDppcktIdPrgrFailed() != 0)
    return 0;
  if (getDpstepPrgrFailed() != 0)
    return 0;

  /* Failed Progress of Execution Verification Report */
  /* Standard Check Service (1,6) */
  SendReqVerifPrgrFailRep(inCmd, CRPS_REQVERIF_PROG_FAIL, ACK_WRONG_CHKSM);

  /* Check if number of Allocated OutComponents = 1*/
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager = 6*/
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 6)
    return 0;

  /* Check that all DataPool Variables concerning (1.6) are updated */
  if (getDpfailCodePrgrFailed() != ACK_WRONG_CHKSM)
    return 0;
  if (getDpnOfPrgrFailed() != 1)
    return 0;
  if (getDppcktIdPrgrFailed() != pcktID)
    return 0;
  if (getDpstepPrgrFailed() != 6)
    return 0;

  /* Get the Data from the out Manager */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[CrFwOutManagerGetNOfLoadedOutCmp(outManager)-1];
  
  /* Check if there is a 1,6 Report waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 6)
    return 0;

  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Successful Completion of Execution Verification Report */
  /* Standard Check Service (1,7) */
  SendReqVerifAccSuccRep(inCmd, CRPS_REQVERIF_TERM_SUCC); //(1,7)
  
  /* Check if number of Allocated OutComponents = 1*/
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager = 7*/
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 7)
    return 0;

  /* Get the Data from the out Manager */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[CrFwOutManagerGetNOfLoadedOutCmp(outManager)-1];
  
  /* Check if there is a 1.7 Report waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 7)
    return 0;

  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check that all DataPool Variables concerning (1,8) are initially 0 */
  if (getDpfailCodeTermFailed() != 0)
    return 0;
  if (getDpnOfTermFailed() != 0)
    return 0;
  if (getDppcktIdTermFailed() != 0)
    return 0;

  /* Failed Completion of Execution Verification Report */
  /* Standard Check Service (1,8) */
  SendReqVerifCmdFailRep(inCmd, CRPS_REQVERIF_TERM_FAIL, ACK_WRONG_CHKSM);

  /* Check if number of Allocated OutComponents = 1*/
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager = 8*/
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 8)
    return 0;

  /* Check that all DataPool Variables concerning (1,8) are updated */
  if (getDpfailCodeTermFailed() != ACK_WRONG_CHKSM)
    return 0;
  if (getDpnOfTermFailed() != 1)
    return 0;
  if (getDppcktIdTermFailed() != pcktID)
    return 0;

  /* Get the Data from the out Manager */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[CrFwOutManagerGetNOfLoadedOutCmp(outManager)-1];
  
  /* Check if there is a 1.8 Report waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 8)
    return 0;

  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check that all DataPool Variables concerning (1,10) are initially 0 */
  if (getDpinvDestRerouting() != 0)
    return 0;
  if (getDpnOfReroutingFailed() != 0)
    return 0;
  if (getDppcktIdReroutingFailed() != 0)
    return 0;

  /* Failed Rerouting Verification Report */
  /* Standard Check Service (1,10) */
  SendReqVerifPcktReroutFailRep(inCmd, ACK_WRONG_CHKSM);

  /* Check if number of Allocated OutComponents = 1*/
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager = 9*/
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 9)
    return 0;

  /* Check that all DataPool Variables concerning (1.10) are updated */
  if (getDpinvDestRerouting() != ACK_WRONG_CHKSM)
    return 0;
  if (getDpnOfReroutingFailed() != 1)
    return 0;
  if (getDppcktIdReroutingFailed() != pcktID)
    return 0;

  /* Get the Data from the out Manager */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[CrFwOutManagerGetNOfLoadedOutCmp(outManager)-1];
  
  /* Check if there is a 1,10 Report waitig in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 10)
    return 0;
  
  /* Checking OutComponent Desicions of the Guards (1,2 and 1,10) */
  /* Extended Check Service (1,2) for an OutComponent (no 1,2 should be created!) */
  SendReqVerifAccFailRep(outCmp, CRPS_REQVERIF_ACC_FAIL);

  /* Check if number of loaded OutComponents in the OutManager stays at 9 */
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 9)
    return 0;

  /* Extended Check Service (1,10) for an OutComponent (no 1,10 should be created!) */
  SendReqVerifPcktReroutFailRep(outCmp, ACK_WRONG_CHKSM);

  /* Check if number of loaded OutComponents in the OutManager stays at 9 */
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 9)
    return 0;

  /* Release the OutComponent */
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Checking REPORT Desicions of the Guards (1,2 and 1,10) */
  /* allocate an 17,2 in Report */
  pckt2 = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt2,17);
  CrFwPcktSetServSubType(pckt2,2);
  CrFwPcktSetDiscriminant(pckt2,0);
  CrFwPcktSetAckLevel(pckt2, 0,0,0,0);
  CrFwPcktSetSrc(pckt2,0);
  CrFwPcktSetDest(pckt2,0);

  /* Check if number of Allocated Packets now is 2*/
  if (CrFwPcktGetNOfAllocated() != 2)
    return 0;

  /* Check if number of Allocated InReports now is 0 */
  if (CrFwInFactoryGetNOfAllocatedInRep() != 0)
    return 0;

  /* create an InReport from pckt2 (17,2) */
  inRep = CrFwInFactoryMakeInRep(pckt2);

  /* Check if number of Allocated InReports now is 1 */
  if (CrFwInFactoryGetNOfAllocatedInRep() != 1)
    return 0;

  /* Extended Check Service (1,2) for an InReport (no 1,2 should be created!) */
  SendReqVerifAccFailRep(inRep, CRPS_REQVERIF_ACC_FAIL);

  /* Check if number of Allocated OutComponents = 0*/
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager stays at 9 */
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 9)
    return 0;

  /* Extended Check Service (1,10) for an InReport (no 1,10 should be created!) */
  SendReqVerifPcktReroutFailRep(inRep, ACK_WRONG_CHKSM);

  /* Check if number of Allocated OutComponents = 0*/
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager stays at 9*/
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 9)
    return 0;

  /*Fill the outfactory so that an Error could occur (leave no free slot)*/
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
  {
    outCmpArr[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
  }

  /* Check if no Application Error has occured*/
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /*Extended Check Service (1,1) no free slots in the OutFactory! Application Error should be 10*/
  SendReqVerifAccSuccRep(inCmd, CRPS_REQVERIF_ACC_SUCC);

  /* Check if Application Error 10 has occured (An OutComponent allocation request has failed)*/
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /* Set the Application Error to 0 and check it*/
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;
  
  /*Extended Check Service (1,2) no free slots i the OutFactory! Application Error should be 10*/
  SendReqVerifAccFailRep(inCmd, CRPS_REQVERIF_ACC_FAIL);

  /* Check if Application Error 10 has occured (An OutComponent allocation request has failed)*/
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /* Set the Application Error to 0 and check it*/
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;
 
  /*Extended Check Service (1,3) no free slots i the OutFactory! Application Error should be 10*/
  SendReqVerifAccSuccRep(inCmd, CRPS_REQVERIF_START_SUCC);

  /* Check if Application Error 10 has occured (An OutComponent allocation request has failed)*/
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /* Set the Application Error to 0 and check it*/
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;
 
  /*Extended Check Service (1,4) no free slots i the OutFactory! Application Error should be 10*/
  SendReqVerifCmdFailRep(inCmd, CRPS_REQVERIF_START_FAIL, ACK_WRONG_CHKSM);

  /* Check if Application Error 10 has occured (An OutComponent allocation request has failed)*/
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /* Set the Application Error to 0 and check it*/
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /*Extended Check Service (1,5) no free slots i the OutFactory! Application Error should be 10*/
  SendReqVerifPrgrSuccRep(inCmd, CRPS_REQVERIF_PROG_SUCC);

  /* Check if Application Error 10 has occured (An OutComponent allocation request has failed)*/
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /* Set the Application Error to 0 and check it*/
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /*Extended Check Service (1,6) no free slots i the OutFactory! Application Error should be 10*/
  SendReqVerifPrgrFailRep(inCmd, CRPS_REQVERIF_PROG_FAIL, ACK_WRONG_CHKSM);

  /* Check if Application Error 10 has occured (An OutComponent allocation request has failed)*/
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /* Set the Application Error to 0 and check it*/
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /*Extended Check Service (1,7) no free slots i the OutFactory! Application Error should be 10*/
  SendReqVerifAccSuccRep(inCmd, CRPS_REQVERIF_TERM_SUCC);

  /* Check if Application Error 10 has occured (An OutComponent allocation request has failed)*/
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /* Set the Application Error to 0 and check it*/
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /*Extended Check Service (1,8) no free slots i the OutFactory! Application Error should be 10*/
  SendReqVerifCmdFailRep(inCmd, CRPS_REQVERIF_TERM_FAIL, ACK_WRONG_CHKSM);

  /* Check if Application Error 10 has occured (An OutComponent allocation request has failed)*/
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /* Set the Application Error to 0 and check it*/
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /*Extended Check Service (1,10) no free slots i the OutFactory! Application Error should be 10*/
  SendReqVerifPcktReroutFailRep(inCmd, ACK_WRONG_CHKSM);

  /* Check if Application Error 10 has occured (An OutComponent allocation request has failed)*/
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /* Release all outcomponents, that have been created to fill the outfactory */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
  {
    CrFwOutFactoryReleaseOutCmp(outCmpArr[i]);
  }

  /* Set the Application Error to 0 and check it*/
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Reset OutManager and check that all OutComponents are unloaded and released */
  CrFwCmpReset(outManager);
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

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

  /* Check datapool entries */
  if (getDpfailCodeAccFailed() != 2)
    return 0;
  if (getDpnOfAccFailed() != 1)
    return 0;
  if (getDppcktIdAccFailed() != pcktID)
    return 0;
  if (getDpfailCodeStartFailed() != ACK_WRONG_CHKSM)
    return 0;
  if (getDpnOfStartFailed() != 1)
    return 0;
  if (getDppcktIdStartFailed() != pcktID)
    return 0;
  if (getDpfailCodePrgrFailed() != ACK_WRONG_CHKSM)
    return 0;
  if (getDpnOfPrgrFailed() != 1)
    return 0;
  if (getDppcktIdPrgrFailed() != pcktID)
    return 0;
  if (getDpstepPrgrFailed() != 6)
    return 0;
  if (getDpfailCodeTermFailed() != ACK_WRONG_CHKSM)
    return 0;
  if (getDpnOfTermFailed() != 1)
    return 0;
  if (getDppcktIdTermFailed() != pcktID)
    return 0;
  if (getDpinvDestRerouting() != ACK_WRONG_CHKSM)
    return 0;
  if (getDpnOfReroutingFailed() != 1)
    return 0;
  if (getDppcktIdReroutingFailed() != pcktID)
    return 0;
  
  return 1;
}
