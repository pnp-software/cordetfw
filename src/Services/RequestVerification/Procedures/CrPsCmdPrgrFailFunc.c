/**
 * @file CrPsCmdPrgrFailFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 17:58:12
 */

/** CrPsCmdPrgrFail function definitions */
#include "CrPsCmdPrgrFailCreate.h"

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
#include <DataPool/CrPsDpServReqVerif.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "CrPsDebug.h"

FwSmDesc_t cmd, rep;

/* ----------------------------------------------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------------------ */
/** Action for node N2. */
void CrPsCmdPrgrFailN2(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* Retrieve an OutComponent of type (1,6) from the OutFactory */
  DEBUGP_1("CrPsCmdPrgrFailN2: Retrieve an OutComponent of type (1,6) from the OutFactory\n");

  /* Create out component */
  rep = CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, CRPS_REQVERIF_PROG_FAIL, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N3. */
void CrPsCmdPrgrFailN3(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  CrPsRepErrCode_t errCode;

  /* Generate error report OUTFACTORY_FAIL */
  DEBUGP_1("CrPsCmdPrgrFailN3: Generate error report OUTFACTORY_FAIL\n");

  errCode = crOutfactoryFail;
  CrPsRepErr(errCode, CRPS_REQVERIF, CRPS_REQVERIF_PROG_FAIL, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N4. */
void CrPsCmdPrgrFailN4(FwPrDesc_t prDesc)
{
  CrFwDestSrc_t source;
  unsigned short tcPacketId, tcSeqCtrl;
  unsigned char tcType, tcSubtype;
  uint32_t tcVerFailData;

  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;

  FwSmDesc_t  smDesc;
  prData_t* prData;
  
  CrFwCmpData_t*    cmpDataStart;
  CrFwOutCmpData_t* cmpSpecificData;
  CrFwPckt_t pckt;

  cmpDataStart    = (CrFwCmpData_t   *) FwSmGetData(rep);
  cmpSpecificData = (CrFwOutCmpData_t *) cmpDataStart->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Configure report and load it in the OutLoader */
  DEBUGP_1("CrPsCmdPrgrFailN4: Configure report and load it in the OutLoader\n");

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);

  smDesc = prData->smDesc;

   /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* Set pcktIdAccFailed */
  tcPacketId = CrFwPcktGetApid(inPckt); /* --- adaptation point CrFwPckt ---> */
  setVerFailedPrgrRepTcPacketId(pckt, tcPacketId);

  /* Set pcktSeqCtrl */
  tcSeqCtrl = CrFwPcktGetSeqCtrl(inPckt); /* --- adaptation point CrFwPckt ---> */
  setVerFailedPrgrRepTcPacketSeqCtrl(pckt, tcSeqCtrl);

  /* Set Type of the command */
  tcType = CrFwPcktGetServType(inPckt); /* --- adaptation point CrFwPckt ---> */
  setVerFailedPrgrRepTcType(pckt, tcType);

  /* Set Subtype of the command */
  tcSubtype = CrFwPcktGetServSubType(inPckt); /* --- adaptation point CrFwPckt ---> */
  setVerFailedPrgrRepTcSubtype(pckt, tcSubtype);

  /* Set failCodeAccFailed = discriminant */
  setVerFailedPrgrRepTcFailureCode(pckt, prData->ushortParam2);

  /* Set verFailData */
  tcVerFailData = getDpverFailData();
  setVerFailedPrgrRepTcFailureData(rep, tcVerFailData);

  /* Set the destination of the report to the source of the in-coming packet */
  source = CrFwPcktGetSrc(inPckt);
  CrFwOutCmpSetDest(rep, source);

  /* Load report in the Outloader */
  CrFwOutLoaderLoad(rep);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N5. */
void CrPsCmdPrgrFailN5(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  unsigned int nOfPrgrFailed;

  /* Increment data pool variable nOfPrgrFailed */
  DEBUGP_1("CrPsCmdPrgrFailN5: Increment data pool variable nOfPrgrFailed\n");

  nOfPrgrFailed = getDpnOfPrgrFailed();
  nOfPrgrFailed += 1;
  setDpnOfPrgrFailed(nOfPrgrFailed);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N6. */
void CrPsCmdPrgrFailN6(FwPrDesc_t prDesc)
{
  unsigned short tcPacketId;

  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;

  FwSmDesc_t  smDesc;
  prData_t* prData;

  /* Update data pool variable pcktIdPrgrFailed, failCodePrgrFailed and prgrStepFailed */
  DEBUGP_1("CrPsCmdPrgrFailN6: Update data pool variable pcktIdPrgrFailed, failCodePrgrFailed and prgrStepFailed\n");

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);
  smDesc = prData->smDesc;

   /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* Set pcktIdPrgrFailed */
  tcPacketId = CrFwPcktGetApid(inPckt); /* --- adaptation point CrFwPckt ---> */
  setDppcktIdPrgrFailed(tcPacketId);

  /* Set failCodePrgrFailed */
  setDpfailCodePrgrFailed(prData->ushortParam2);

  /* Set prgrStepFailed */
  setDpstepPrgrFailed(prData->ushortParam1);

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsCmdPrgrFailG1(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* [ OutFactory fails to generate OutComponent ] */
  DEBUGP_1("CrPsCmdPrgrFailG1: Guard on the Control Flow from DECISION2 to N3 \n");

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

