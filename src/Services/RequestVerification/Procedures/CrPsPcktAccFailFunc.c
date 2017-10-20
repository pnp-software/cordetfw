/**
 * @file CrPsPcktAccFailFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 18:24:51
 */

/** CrPsPcktAccFail function definitions */
#include "CrPsPcktAccFailCreate.h"

/** FW Profile function definitions */
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwSmConfig.h"

#include "Pckt/CrFwPckt.h" /* --- interface to adaptation point CrFwPckt --- */
#include <CrFwCmpData.h>
#include <BaseCmp/CrFwBaseCmp.h>
#include <OutFactory/CrFwOutFactory.h>
#include <OutLoader/CrFwOutLoader.h>
#include <OutCmp/CrFwOutCmp.h>

#include <CrPsPcktUtilities.h>
#include <CrPsRepErr.h>
#include <DataPool/CrPsDpServReqVerif.h>
#include <Services/General/CrPsPktServReqVerif.h>
#include <Services/General/CrPsConstants.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "CrPsDebug.h"

FwSmDesc_t cmd, rep;

/* ----------------------------------------------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------------------ */
/** Action for node N1. */
void CrPsPcktAccFailN1(FwPrDesc_t prDesc)
{
  CrFwCmpData_t*   inData;
  CrFwInRepData_t* inSpecificData;
  CrFwPckt_t       inPckt;

  FwSmDesc_t  smDesc;
  prData_t* prData;
  CrPsRepErrCode_t errCode;

  /* Generate error report INLOADER_ACC_FAIL */
  DEBUGP_1("CrPsPcktAccFailN1: Generate error report INLOADER_ACC_FAIL\n");

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);
  smDesc = prData->smDesc;

   /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInRepData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  errCode = crInloaderAccFail;
  CrPsRepErr(errCode, CrFwPcktGetServType(inPckt), CrFwPcktGetServSubType(inPckt), CrFwPcktGetDiscriminant(inPckt));

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N2. */
void CrPsPcktAccFailN2(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* Retrieve an OutComponent of type (1,2) from the OutFactory */
  DEBUGP_1("CrPsPcktAccFailN2: Retrieve an OutComponent of type (1,2) from the OutFactory\n");

  /* Create out component */
  rep = CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, CRPS_REQVERIF_ACC_FAIL, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N3. */
void CrPsPcktAccFailN3(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  CrPsRepErrCode_t errCode;

  /* Generate error report OUTFACTORY_FAIL */
  DEBUGP_1("CrPsPcktAccFailN3: Generate error report OUTFACTORY_FAIL\n");

  errCode = crOutfactoryFail;
  CrPsRepErr(errCode, CRPS_REQVERIF, CRPS_REQVERIF_PROG_SUCC, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N4. */
void CrPsPcktAccFailN4(FwPrDesc_t prDesc)
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
  
  CrFwCmpData_t*   cmpDataStart;
  CrFwOutCmpData_t* cmpSpecificData;
  CrFwPckt_t pckt;

  cmpDataStart    = (CrFwCmpData_t   *) FwSmGetData(rep);
  cmpSpecificData = (CrFwOutCmpData_t *) cmpDataStart->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Configure report (1,2) and load it in the OutLoader */
  DEBUGP_1("CrPsPcktAccFailN4: \n");

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);
  smDesc = prData->smDesc;

   /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* Set pcktIdAccFailed */
  tcPacketId = CrFwPcktGetApid(inPckt); /* --- adaptation point CrFwPckt ---> */
  setVerFailedAccRepTcPacketId(pckt, tcPacketId);

  /* Set packetSeqCtrl */
  tcSeqCtrl = CrFwPcktGetSeqCtrl(inPckt); /* --- adaptation point CrFwPckt ---> */
  setVerFailedAccRepTcPacketSeqCtrl(pckt, tcSeqCtrl);

  /* Set Type of the command */
  tcType = CrFwPcktGetServType(inPckt); /* --- adaptation point CrFwPckt ---> */
  setVerFailedAccRepTcType(pckt, tcType);

  /* Set Subtype of the command */
  tcSubtype = CrFwPcktGetServSubType(inPckt); /* --- adaptation point CrFwPckt ---> */
  setVerFailedAccRepTcSubtype(pckt, tcSubtype);

  /* Set failCodeAccFailed */
  setVerFailedAccRepTcFailureCode(pckt, prData->ushortParam1);
  //CRFW_UNUSED(tcVerFailData);
  /* Set verFailData */
  tcVerFailData = getDpverFailData();
  setVerFailedAccRepTcFailureData(pckt, tcVerFailData);

  /* Set the destination of the report to the source of the in-coming packet */
  source = CrFwPcktGetSrc(inPckt);
  CrFwOutCmpSetDest(rep, source);

  /* Load report in the Outloader */
  CrFwOutLoaderLoad(rep);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N5. */
void CrPsPcktAccFailN5(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  unsigned short nOfAccFailed;

  /* Increment data pool variable nOfAccFailed */
  DEBUGP_1("CrPsPcktAccFailN5: Increment data pool variable nOfAccFailed\n");

  nOfAccFailed = getDpnOfAccFailed();
  nOfAccFailed += 1;
  setDpnOfAccFailed(nOfAccFailed);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N6. */
void CrPsPcktAccFailN6(FwPrDesc_t prDesc)
{
  unsigned short tcPacketId;

  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;

  FwSmDesc_t  smDesc;
  prData_t* prData;

  /* Update data pool variable pcktIdAccFailed, failCodeAccFailed */
  DEBUGP_1("CrPsPcktAccFailN6: Update data pool variable pcktIdAccFailed, failCodeAccFailed\n");

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);
  smDesc = prData->smDesc;

   /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* Set pcktIdAccFailed */
  tcPacketId = CrFwPcktGetApid(inPckt); /* --- adaptation point CrFwPckt ---> */
  setDppcktIdAccFailed(tcPacketId);

  /* Set failCodeAccFailed */
  setDpfailCodeAccFailed(prData->ushortParam1);

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION1 to N1. */
FwPrBool_t CrPsPcktAccFailG1(FwPrDesc_t prDesc)
{
  FwSmDesc_t  smDesc;
  prData_t* prData;

  /* [ Packet encapsulates a report ] */
  DEBUGP_1("CrPsPcktAccFailG1: Guard on the Control Flow from DECISION1 to N1\n");

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);
  smDesc = prData->smDesc;

  if (CrFwCmpGetTypeId(smDesc) == CR_FW_INREPORT_TYPE)
    {
      return 1;
    }
  else
    {
      return 0;
    }

}

/** Guard on the Control Flow from DECISION1 to N2. */
FwPrBool_t CrPsPcktAccFailG1E(FwPrDesc_t prDesc)
{
  FwSmDesc_t  smDesc;
  prData_t* prData;

  /* [ Packet encapsulates a command ] */
  DEBUGP_1("CrPsPcktAccFailG1E: Guard on the Control Flow from DECISION1 to N2\n");

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);
  smDesc = prData->smDesc;

  if (CrFwCmpGetTypeId(smDesc) == CR_FW_INCOMMAND_TYPE)
    {
      return 1;
    }
  else
    {
      return 0;
    }

}

/** Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsPcktAccFailG2(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* [ OutFactory fails to generate OutComponent ] */
  DEBUGP_1("CrPsPcktAccFailG2: Guard on the Control Flow from DECISION2 to N3\n");

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

