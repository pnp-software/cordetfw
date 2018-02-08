/**
 * @file CrPsUtilitiesServReqVerif.c
 * @ingroup Utilities
 * @ingroup Serv1
 *
 * @brief Implementation of the utility functions of the CORDET Framework PUS Extension Service 1 (Request Verification)
 *
 * @author Christian Reimers <christian.reimers@univie.ac.at>
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

#include "CrPsUtilitiesServReqVerif.h"
#include "Pckt/CrFwPckt.h"     /* --- interface to adaptation point CrFwPckt --- */

/* CrFramework includes */
#include <OutFactory/CrFwOutFactory.h>
#include <OutLoader/CrFwOutLoader.h>
#include <CrFwCmpData.h>

/* FwProfile includes */
#include <FwPrCore.h>
#include <FwPrConfig.h>
#include <FwSmConfig.h>

#include <Services/General/CrPsConstants.h>
#include <Services/RequestVerification/Procedures/CrPsPcktReroutingFailCreate.h>
#include <Services/RequestVerification/Procedures/CrPsPcktAccFailCreate.h>
#include <Services/RequestVerification/Procedures/CrPsCmdVerSuccCreate.h>
#include <Services/RequestVerification/Procedures/CrPsCmdVerFailCreate.h>
#include <Services/RequestVerification/Procedures/CrPsCmdPrgrSuccCreate.h>
#include <Services/RequestVerification/Procedures/CrPsCmdPrgrFailCreate.h>

#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServReqVerif.h>

#include <stdlib.h>


/* global handles for the procedures */
FwPrDesc_t prDescServReqVerifPcktReroutFail, prDescServReqVerifPcktAccFail;
FwPrDesc_t prDescServReqVerifCmdVerSucc, prDescServReqVerifCmdVerFail;
FwPrDesc_t prDescServReqVerifCmdPrgrSucc, prDescServReqVerifCmdPrgrFail;


/**
 * Initialization of CORDET Framework PUS Extension components
 */
int CrPsInitServReqVerif()
{

  /***********************************************************************/
  /* Service Request Verification Packet Rerouting Failure Procedure     */
  /***********************************************************************/
  prDescServReqVerifPcktReroutFail = CrPsPcktReroutingFailCreate(NULL);
  if (FwPrCheck(prDescServReqVerifPcktReroutFail) != prSuccess)
    {
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Request Verification Packet Acceptance Failure Procedure    */
  /***********************************************************************/
  prDescServReqVerifPcktAccFail = CrPsPcktAccFailCreate(NULL);
  if (FwPrCheck(prDescServReqVerifPcktAccFail) != prSuccess)
    {
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Request Verification Command Verification Success Procedure */
  /***********************************************************************/
  prDescServReqVerifCmdVerSucc = CrPsCmdVerSuccCreate(NULL);
  if (FwPrCheck(prDescServReqVerifCmdVerSucc) != prSuccess)
    {
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Request Verification Command Verification Failure Procedure */
  /***********************************************************************/
  prDescServReqVerifCmdVerFail = CrPsCmdVerFailCreate(NULL);
  if (FwPrCheck(prDescServReqVerifCmdVerFail) != prSuccess)
    {
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Request Verification Command Progress Success Procedure     */
  /***********************************************************************/
  prDescServReqVerifCmdPrgrSucc = CrPsCmdPrgrSuccCreate(NULL);
  if (FwPrCheck(prDescServReqVerifCmdPrgrSucc) != prSuccess)
    {
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Request Verification Command Progress Failure Procedure     */
  /***********************************************************************/
  prDescServReqVerifCmdPrgrFail = CrPsCmdPrgrFailCreate(NULL);
  if (FwPrCheck(prDescServReqVerifCmdPrgrFail) != prSuccess)
    {
      return EXIT_FAILURE;
    }

  /* initialize Datapool Values */
  initDpServReqVerif();

  return EXIT_SUCCESS;
}

/**
 * Execution of CORDET Framework PUS Extension components
 */
void CrPsExecServReqVerif()
{
  return;
}

/**
 * Getter for ReqVerifPcktReroutFail procedure descriptor
 */
inline FwPrDesc_t getPrDescServReqVerifPcktReroutFail()
{
  return prDescServReqVerifPcktReroutFail;
}

/**
 * Getter for ReqVerifPcktAccFail procedure descriptor
 */
inline FwPrDesc_t getPrDescServReqVerifPcktAccFail()
{
  return prDescServReqVerifPcktAccFail;
}

/**
 * Getter for ReqVerifCmdVerSucc procedure descriptor
 */
inline FwPrDesc_t getPrDescServReqVerifCmdVerSucc()
{
  return prDescServReqVerifCmdVerSucc;
}

/**
 * Getter for ReqVerifCmdVerFail procedure descriptor
 */
inline FwPrDesc_t getPrDescServReqVerifCmdVerFail()
{
  return prDescServReqVerifCmdVerFail;
}

/**
 * Getter for ReqVerifCmdPrgrSucc procedure descriptor
 */
inline FwPrDesc_t getPrDescServReqVerifCmdPrgrSucc()
{
  return prDescServReqVerifCmdPrgrSucc;
}

/**
 * Getter for ReqVerifCmdPrgrFail procedure descriptor
 */
inline FwPrDesc_t getPrDescServReqVerifCmdPrgrFail()
{
  return prDescServReqVerifCmdPrgrFail;
}

/**
 * Generate a Request Verification Acceptance/Start/Termination Successful out-going report.
 * @return nothing
 */
void SendReqVerifAccSuccRep(FwSmDesc_t smDesc, uint16_t reqVerifAccSuccType)
{
  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;
  CrFwBool_t       isAckFlag;
  prData_t         prData;

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
void SendReqVerifAccFailRep(FwSmDesc_t smDesc, CrPsFailCode_t FailureCode)
{
  prData_t prData;

  prData.smDesc = smDesc;
  prData.ushortParam1 = FailureCode;
  FwPrSetData(prDescServReqVerifPcktAccFail, &prData);
  FwPrRun(prDescServReqVerifPcktAccFail);

  return;
}

/**
 * Generate a Request Verification Start/Termination Failed out-going report.
 * @return nothing
 */
void SendReqVerifCmdFailRep(FwSmDesc_t smDesc, uint16_t reqVerifCmdFailType, CrPsFailCode_t FailureCode)
{
  prData_t prData;

  prData.smDesc = smDesc;
  prData.ushortParam1 = FailureCode;
  prData.ushortParam2 = reqVerifCmdFailType;
  FwPrSetData(prDescServReqVerifCmdVerFail, &prData);
  FwPrRun(prDescServReqVerifCmdVerFail);

  return;
}

/**
 * Generate a Request Verification Progress Successful out-going report.
 * @return nothing
 */
void SendReqVerifPrgrSuccRep(FwSmDesc_t smDesc, CrPsStepId_t stepIdentifier)
{
  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;
  CrFwBool_t       isAckFlag;
  prData_t         prData;

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

/**
 * Generate a Request Verification Progress Failed out-going report.
 * @return nothing
 */
void SendReqVerifPrgrFailRep(FwSmDesc_t smDesc, CrPsStepId_t stepIdentifier, CrPsFailCode_t FailureCode)
{
  prData_t prData;

  prData.smDesc = smDesc;
  prData.ushortParam1 = stepIdentifier;
  prData.ushortParam2 = FailureCode;
  FwPrSetData(prDescServReqVerifCmdPrgrFail, &prData);
  FwPrRun(prDescServReqVerifCmdPrgrFail);

  return;
}

/**
 * Generate a Request Verification Package Rerouting Failed out-going report.
 * @return nothing
 */
void SendReqVerifPcktReroutFailRep(FwSmDesc_t smDesc, CrPsFailCode_t FailureCode)
{
  prData_t prData;

  prData.smDesc = smDesc;
  prData.ushortParam1 = FailureCode;
  FwPrSetData(prDescServReqVerifPcktReroutFail, &prData);
  FwPrRun(prDescServReqVerifPcktReroutFail);

  return;
}

