/**
 * @file CrPsUtilities.c
 *
 * Implementation of the utility functions of the CORDET Framework PUS Extension
 *
 * @author code generator
 * edited: Christian Reimers
 * 25.05.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsUtilities.h"
#include "Pckt/CrFwPckt.h"     /* --- interface to adaptation point CrFwPckt --- */
#include "CrPsPcktUtilities.h" /* --- interface to adaptation point CrFwPckt for CrFwPcktGetPid() --- */

/* CrFramework includes */
#include <OutFactory/CrFwOutFactory.h>
#include <OutLoader/CrFwOutLoader.h>
#include <CrFwCmpData.h>

/* FwProfile includes */
#include <FwPrCore.h>
#include <FwPrConfig.h>
#include <FwSmConfig.h>

#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsParamSetter.h>
#include <Services/Test/Procedures/CrPsCmd17s3StartCreate.h>
#include <Services/Test/Procedures/CrPsCmd17s3PrgrCreate.h>
#include <Services/RequestVerification/Procedures/CrPsPcktReroutingFailCreate.h>
#include <Services/RequestVerification/Procedures/CrPsPcktAccFailCreate.h>
#include <Services/RequestVerification/Procedures/CrPsCmdVerSuccCreate.h>
#include <Services/RequestVerification/Procedures/CrPsCmdVerFailCreate.h>
#include <Services/RequestVerification/Procedures/CrPsCmdPrgrSuccCreate.h>
#include <Services/RequestVerification/Procedures/CrPsCmdPrgrFailCreate.h>

#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServTest.h>

#include <stdio.h>
#include <stdlib.h>

/* global handles for the procedures */
FwPrDesc_t prDescServTestOnBoardConnStart, prDescServTestOnBoardConnPrgr;
FwPrDesc_t prDescServReqVerifPcktReroutFail, prDescServReqVerifPcktAccFail;
FwPrDesc_t prDescServReqVerifCmdVerSucc, prDescServReqVerifCmdVerFail;
FwPrDesc_t prDescServReqVerifCmdPrgrSucc, prDescServReqVerifCmdPrgrFail;


/**
 * Initialization of CORDET Framework PUS Extension application-specific components
 */
void CrPsInitApp(unsigned short onBoardTestConnectAppId)
{
  unsigned short destId;
  unsigned int i, pos;

  printf("CrPsInitApp(%d): Mult = %d\n", onBoardTestConnectAppId, 10);

  /*************************************************************/
  /* Service Test On-Board Connection Data Pool Initialization */
  /*************************************************************/
  for (i=0; i<10; i++)
    {
      pos = i;
      destId = getDpOnBoardConnectDestLstItem(pos);
      printf("CrPsInitApp(): got destId %d at slot %d from data pool\n", destId, i);
      if (destId == 0) /* got empty#include <> slot */
        {
          printf("CrPsInitApp(): new slot for appId found: pos = %d\n", pos);
          setDpOnBoardConnectDestLstItem(pos, onBoardTestConnectAppId);
          return;
        }
    }

  printf("CrPsInitApp(): no empty slot found!\n");
  return;
}

/**
 * Initialization of CORDET Framework PUS Extension components
 */
int CrPsInit()
{
  printf("CrPsInit()\n");

  /***********************************************************************/
  /* Initialization of Data Pool variables and parameter                 */
  /***********************************************************************/
  setDpAreYouAliveTimeOut(10);

  /***********************************************************************/
  /* Service Test On-Board Connection Start Procedure                    */
  /***********************************************************************/
  prDescServTestOnBoardConnStart = CrPsCmd17s3StartCreate(NULL);
  if (FwPrCheck(prDescServTestOnBoardConnStart) != prSuccess)
    {
      printf("Service Test On-Board Connection Start PR is NOT properly configured ... FAILURE\n");
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Test On-Board Connection Progress Procedure                 */
  /***********************************************************************/
  prDescServTestOnBoardConnPrgr = CrPsCmd17s3PrgrCreate(NULL);
  if (FwPrCheck(prDescServTestOnBoardConnPrgr) != prSuccess)
    {
      printf("Service Test On-Board Connection Progress PR is NOT properly configured ... FAILURE\n");
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Request Verification Packet Rerouting Failure Procedure     */
  /***********************************************************************/
  prDescServReqVerifPcktReroutFail = CrPsPcktReroutingFailCreate(NULL);
  if (FwPrCheck(prDescServReqVerifPcktReroutFail) != prSuccess)
    {
      printf("Service Request Verification Packet Rerouting Failure PR is NOT properly configured ... FAILURE\n");
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Request Verification Packet Acceptance Failure Procedure    */
  /***********************************************************************/
  prDescServReqVerifPcktAccFail = CrPsPcktAccFailCreate(NULL);
  if (FwPrCheck(prDescServReqVerifPcktAccFail) != prSuccess)
    {
      printf("Service Request Verification Packet Acceptance Failure PR is NOT properly configured ... FAILURE\n");
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Request Verification Command Verification Success Procedure */
  /***********************************************************************/
  prDescServReqVerifCmdVerSucc = CrPsCmdVerSuccCreate(NULL);
  if (FwPrCheck(prDescServReqVerifCmdVerSucc) != prSuccess)
    {
      printf("Service Request Verification Command Verification Success PR is NOT properly configured ... FAILURE\n");
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Request Verification Command Verification Failure Procedure */
  /***********************************************************************/
  prDescServReqVerifCmdVerFail = CrPsCmdVerFailCreate(NULL);
  if (FwPrCheck(prDescServReqVerifCmdVerFail) != prSuccess)
    {
      printf("Service Request Verification Command Verification Failure PR is NOT properly configured ... FAILURE\n");
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Request Verification Command Progress Success Procedure     */
  /***********************************************************************/
  prDescServReqVerifCmdPrgrSucc = CrPsCmdPrgrSuccCreate(NULL);
  if (FwPrCheck(prDescServReqVerifCmdPrgrSucc) != prSuccess)
    {
      printf("Service Request Verification Command Progress Success PR is NOT properly configured ... FAILURE\n");
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Request Verification Command Progress Failure Procedure     */
  /***********************************************************************/
  prDescServReqVerifCmdPrgrFail = CrPsCmdPrgrFailCreate(NULL);
  if (FwPrCheck(prDescServReqVerifCmdPrgrFail) != prSuccess)
    {
      printf("Service Request Verification Command Progress Failure PR is NOT properly configured ... FAILURE\n");
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}

/**
 * Execution of CORDET Framework PUS Extension components
 */
void CrPsExec()
{
  printf("CrPsExec()\n");

  FwPrExecute(prDescServTestOnBoardConnStart);
  /*FwPrExecute(prDescServTestOnBoardConnPrgr);*/

  return;
}

/**
 * Generate a Request Verification Acceptance/Start/Termination Successful out-going report.
 * @return nothing
 */
void SendReqVerifAccSuccRep(FwSmDesc_t smDesc, unsigned short reqVerifAccSuccType)
{
  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;

  CrFwBool_t isAckFlag;
  prData_t prData;

  /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  if (reqVerifAccSuccType == CRPS_REQVERIF_ACC_SUCC)
    {
      isAckFlag = CrFwPcktIsAcceptAck(inPckt);
    }
  else if (reqVerifAccSuccType == CRPS_REQVERIF_START_SUCC)
    {
      isAckFlag = CrFwPcktIsStartAck(inPckt);
    }
  else if (reqVerifAccSuccType == CRPS_REQVERIF_TERM_SUCC)
    {
      isAckFlag = CrFwPcktIsTermAck(inPckt);
    }
  else
    {
      isAckFlag = 0;
    }

  if (isAckFlag == 1)
    {
      prData.smDesc = smDesc;
      prData.ushortParam1 = reqVerifAccSuccType;
      FwPrSetData(prDescServReqVerifCmdVerSucc, &prData);
      FwPrRun(prDescServReqVerifCmdVerSucc);
    }

  return;
}

/**
 * Generate a Request Verification Acceptance Failed out-going report.
 * @return nothing
 */
void SendReqVerifAccFailRep(FwSmDesc_t smDesc, unsigned short tcFailureCode)
{
  prData_t prData;

  prData.smDesc = smDesc;
  prData.ushortParam1 = tcFailureCode;
  FwPrSetData(prDescServReqVerifPcktAccFail, &prData);
  FwPrRun(prDescServReqVerifPcktAccFail);

  return;
}


/**
 * Generate a Request Verification Start/Termination Failed out-going report.
 * @return nothing
 */
void SendReqVerifCmdFailRep(FwSmDesc_t smDesc, unsigned short reqVerifCmdFailType, unsigned short tcFailureCode)
{
  prData_t prData;

  prData.smDesc = smDesc;
  prData.ushortParam1 = tcFailureCode;
  prData.ushortParam2 = reqVerifCmdFailType;
  FwPrSetData(prDescServReqVerifCmdVerFail, &prData);
  FwPrRun(prDescServReqVerifCmdVerFail);

  return;
}

/**
 * Generate a Request Verification Progress Successful out-going report.
 * @return nothing
 */
void SendReqVerifPrgrSuccRep(FwSmDesc_t smDesc, unsigned short stepIdentifier)
{
  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;

  CrFwBool_t isAckFlag;
  prData_t prData;

  /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  isAckFlag = CrFwPcktIsProgressAck(inPckt);

  if (isAckFlag == 1)
    {
      prData.smDesc = smDesc;
      prData.ushortParam1 = stepIdentifier;
      FwPrSetData(prDescServReqVerifCmdPrgrSucc, &prData);
      FwPrRun(prDescServReqVerifCmdPrgrSucc);
    }

  return;
}

void SendReqVerifPrgrFailRep(FwSmDesc_t smDesc, unsigned short stepIdentifier, unsigned short tcFailureCode)
{
  prData_t prData;

  prData.smDesc = smDesc;
  prData.ushortParam1 = stepIdentifier;
  prData.ushortParam2 = tcFailureCode;
  FwPrSetData(prDescServReqVerifCmdPrgrFail, &prData);
  FwPrRun(prDescServReqVerifCmdPrgrFail);

  return;
}

void SendReqVerifPcktReroutFailRep(FwSmDesc_t smDesc, unsigned short tcFailureCode)
{
  prData_t prData;

  prData.smDesc = smDesc;
  prData.ushortParam1 = tcFailureCode;
  FwPrSetData(prDescServReqVerifPcktReroutFail, &prData);
  FwPrRun(prDescServReqVerifPcktReroutFail);

  return;
}

