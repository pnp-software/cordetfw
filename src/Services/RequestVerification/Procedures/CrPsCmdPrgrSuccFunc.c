/**
 * @file CrPsCmdPrgrSuccFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 17:59:40
 */

/** CrPsCmdPrgrSucc function definitions */
#include "CrPsCmdPrgrSuccCreate.h"

/** FW Profile function definitions */
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwSmConfig.h"

#include "Pckt/CrFwPckt.h" /* --- interface to adaptation point CrFwPckt --- */
#include <CrFwCmpData.h>
#include <OutFactory/CrFwOutFactory.h>
#include <OutLoader/CrFwOutLoader.h>
#include <OutCmp/CrFwOutCmp.h>

#include <CrPsPcktUtilities.h>
#include <CrPsRepErr.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsDpPktServReqVerif.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

FwSmDesc_t cmd, rep;

/* ----------------------------------------------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------------------ */
/** Action for node N2. */
void CrPsCmdPrgrSuccN2(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* Retrieve an OutComponent of type (1,5) from the OutFactory */
  /*printf("CrPsCmdPrgrSuccN2: Retrieve an OutComponent of type (1,5) from the OutFactory\n");*/

  /* Create out component */
  rep = CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, CRPS_REQVERIF_PROG_SUCC, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N3. */
void CrPsCmdPrgrSuccN3(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  CrPsRepErrCode_t errCode;

  /* Generate error report OUTFACTORY_FAIL */
  /*printf("CrPsCmdPrgrSuccN3: Generate error report OUTFACTORY_FAIL\n");*/

  errCode = crOutfactoryFail;
  CrPsRepErr(errCode, CRPS_REQVERIF, CRPS_REQVERIF_PROG_SUCC, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N4. */
void CrPsCmdPrgrSuccN4(FwPrDesc_t prDesc)
{
  CrFwDestSrc_t source;
  unsigned short tcPacketId;

  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;

  FwSmDesc_t  smDesc;
  prData_t* prData; 

  /* Configure report and load it in the OutLoader */
  /*printf("CrPsCmdPrgrSuccN4: Configure report and load it in the OutLoader\n");*/

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);

  smDesc = prData->smDesc;

   /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* Set pcktIdAccFailed */
  tcPacketId = CrFwPcktGetPid(inPckt); /* --- adaptation point CrFwPckt ---> */
  /*CrPsServReqVerifPrgrSuccParamSetPacketId(rep, tcPacketId);*/
  setVerSuccessPrgrRep0TcPacketId(rep, tcPacketId);

  /* Set pcktIdAccFailed */
  tcPacketId = CrFwPcktGetPid(inPckt); /* --- adaptation point CrFwPckt ---> */
  /*CrPsServReqVerifPrgrSuccParamSetStepId(rep, prData->ushortParam1);*/
  setVerSuccessPrgrRep0StepId(rep, prData->ushortParam1);

  /* Set the destination of the report to the source of the in-coming packet */
  source = CrFwPcktGetSrc(inPckt);
  CrFwOutCmpSetDest(rep, source);

  /* Load report in the Outloader */
  CrFwOutLoaderLoad(rep);

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsCmdPrgrSuccG1(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* [ OutFactory fails to generate OutComponent ] */
  /*printf("CrPsCmdPrgrSuccG1: Guard on the Control Flow from DECISION2 to N3\n");*/

  if (rep == NULL)
    {
      return 1;
    }
  else
    {
      return 0;
    }

}

/* ----------------------------------------------------------------------------------------------------------------- */

