/**
 * @file CrPsCmdVerSuccFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 18:2:22
 */

/** CrPsCmdVerSucc function definitions */
#include "CrPsCmdVerSuccCreate.h"

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
#include <Services/General/CrPsPktServReqVerif.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "CrPsDebug.h"

FwSmDesc_t cmd, rep;

/* ----------------------------------------------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------------------ */
/** Action for node N2. */
void CrPsCmdVerSuccN2(FwPrDesc_t prDesc)
{
  prData_t* prData;

  /* Retrieve an OutComponent of type (1,1), (1,3) or (1,7) from the OutFactory */
  DEBUGP_1("CrPsCmdVerSuccN2: Retrieve an OutComponent of type (1,1), (1,3) or (1,7) from the OutFactory\n");

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);
  rep = NULL;
  /* Create out component */
  rep = CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, prData->ushortParam1, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N3. */
void CrPsCmdVerSuccN3(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  CrPsRepErrCode_t errCode;

  /* Generate error report OUTFACTORY_FAIL */
  DEBUGP_1("CrPsCmdVerSuccN3: Generate error report OUTFACTORY_FAIL\n");

  errCode = crOutfactoryFail;
  CrPsRepErr(errCode, CRPS_TEST, CRPS_TEST_AREYOUALIVE_CONNECTION_CMD, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N4. */
void CrPsCmdVerSuccN4(FwPrDesc_t prDesc)
{
  CrFwDestSrc_t source;
  unsigned short tcPacketId, tcSeqCtrl;

  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;

  FwSmDesc_t  smDesc;
  prData_t* prData;

  CrFwCmpData_t*   cmpDataStart;
  CrFwOutCmpData_t* cmpSpecificData;
  CrFwPckt_t pckt;

  cmpDataStart    = (CrFwCmpData_t   *) FwSmGetData(rep);
  cmpSpecificData = (CrFwOutCmpData_t *) cmpDataStart->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Configure report and load it in the OutLoader */
  DEBUGP_1("CrPsCmdVerSuccN4: Configure report and load it in the OutLoader\n");

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);

  /*smDesc = prData[0];*/
  smDesc = prData->smDesc;

   /* Get in packet */
  inData         = FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  tcPacketId = CrFwPcktGetApid(inPckt); /* --- adaptation point CrFwPckt ---> */

  if (prData->ushortParam1 == CRPS_REQVERIF_ACC_SUCC)
  {
    /* 1.1 */
    /* Set pcktIdAccFailed */
    setVerSuccessAccRepTcPacketId(pckt, tcPacketId);
  }

  if (prData->ushortParam1 == CRPS_REQVERIF_START_SUCC)
  {
    /* 1.3 */
    /* Set pcktIdAccFailed */
    setVerSuccessStartRepTcPacketId(pckt, tcPacketId);
  }

  if (prData->ushortParam1 == CRPS_REQVERIF_TERM_SUCC)
  {
    /* 1.7 */
    /* Set pcktIdAccFailed */
    setVerSuccessTermRepTcPacketId(pckt, tcPacketId);
  }

  /* Set packetSeqCtrl */
  tcSeqCtrl = CrFwPcktGetSeqCtrl(inPckt); /* --- adaptation point CrFwPckt ---> */
  setVerSuccessAccRepTcPacketSeqCtrl(pckt, tcSeqCtrl);

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
FwPrBool_t CrPsCmdVerSuccG1(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* [ OutFactory fails to generate OutComponent ] */  
  DEBUGP_1("CrPsCmdVerSuccG1: Guard on the Control Flow from DECISION2 to N3 \n");
  
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

