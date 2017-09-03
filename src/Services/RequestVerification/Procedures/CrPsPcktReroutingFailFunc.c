/**
 * @file CrPsPcktReroutingFailFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 18:26:2
 */

/** CrPsPcktReroutingFail function definitions */
#include "CrPsPcktReroutingFailCreate.h"

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
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsDpPktServReqVerif.h>
#include <DataPool/CrPsDpServReqVerif.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FwSmDesc_t cmd, rep;


/* ----------------------------------------------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------------------ */
/** Action for node N1. */
void CrPsPcktReroutingFailN1(FwPrDesc_t prDesc)
{
  CrFwCmpData_t*   inData;
  CrFwInRepData_t* inSpecificData;
  CrFwPckt_t       inPckt;

  FwSmDesc_t  smDesc;
  prData_t* prData;
  CrPsRepErrCode_t errCode;

  /* Generate error report INLOADER_INV_DEST */
  /*printf("CrPsPcktReroutingFailN1: Generate error report INLOADER_INV_DEST\n");*/

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);
  smDesc = prData->smDesc;

   /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInRepData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  errCode = crInloaderInvDest;
  CrPsRepErr(errCode, CrFwPcktGetServType(inPckt), CrFwPcktGetServSubType(inPckt), CrFwPcktGetDiscriminant(inPckt));

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N2. */
void CrPsPcktReroutingFailN2(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* Retrieve an OutComponent of type (1,10) from the OutFactory */
  /*printf("CrPsPcktReroutingFailN2: Retrieve an OutComponent of type (1,10) from the OutFactory\n");*/

  /* Create out component */
  rep = CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, CRPS_REQVERIF_REROUT_FAIL, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N3. */
void CrPsPcktReroutingFailN3(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  CrPsRepErrCode_t errCode;

  /* Generate error report OUTFACTORY_FAIL */
  /*printf("CrPsPcktReroutingFailN3: Generate error report OUTFACTORY_FAIL\n");*/

  errCode = crOutfactoryFail;
  CrPsRepErr(errCode, CRPS_REQVERIF, CRPS_REQVERIF_PROG_SUCC, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N4. */
void CrPsPcktReroutingFailN4(FwPrDesc_t prDesc)
{
  CrFwDestSrc_t source;
  unsigned short tcPacketId;
  unsigned char tcType, tcSubtype, tcDiscriminant;
  unsigned int tcVerFailData;

  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;

  FwSmDesc_t  smDesc;
  prData_t* prData;

  /* Configure report (1,10) and load it in the OutLoader */
  /*printf("CrPsPcktReroutingFailN4: Configure report (1,10) and load it in the OutLoader\n");*/

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);

  smDesc = prData->smDesc;

   /* Get in packet */
  inData          = FwSmGetData(smDesc);
  inSpecificData  = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt          = inSpecificData->pckt;


  /* Set pcktIdAccFailed */
  tcPacketId = CrFwPcktGetPid(inPckt); /* --- adaptation point CrFwPckt ---> */
  setVerFailedRoutingRep0TcPacketId(rep, tcPacketId);

  /* Set failCodeAccFailed */
  /*CrPsServReqVerifVerFailParamSetFailureCode(rep, INLOADER_INV_DEST);*/
  setVerFailedRoutingRep0TcFailureCode(rep, INLOADER_INV_DEST); 

  /* Set Type of the command */
  tcType = CrFwPcktGetServType(inPckt); /* --- adaptation point CrFwPckt ---> */
  setVerFailedRoutingRep0TcType(rep, tcType);

  /* Set Subtype of the command */
  tcSubtype = CrFwPcktGetServSubType(inPckt); /* --- adaptation point CrFwPckt ---> */
  setVerFailedRoutingRep0TcSubtype(rep, tcSubtype);

  /* Set Discriminant of the command */
  tcDiscriminant = CrFwPcktGetDiscriminant(inPckt); /* --- adaptation point CrFwPckt ---> */
  setVerFailedRoutingRep0TcFailureCode(rep, tcDiscriminant); /* Discriminant acts as FailureCode*/

  /* Set verFailData */
  tcVerFailData = getDpverFailData(); /* get it from data pool */
  setVerFailedRoutingRep0invDest(rep, tcVerFailData); 

  /* Set the destination of the report to the source of the in-coming packet */
  source = CrFwPcktGetSrc(inPckt);
  CrFwOutCmpSetDest(rep, source);

  /* Load report in the Outloader */
  CrFwOutLoaderLoad(rep);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N5. */
void CrPsPcktReroutingFailN5(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  unsigned int nOfReroutingFailed;

  /* Increment data pool variable nOfReroutingFailed */
  /*printf("CrPsPcktReroutingFailN5: Increment data pool variable nOfReroutingFailed\n");*/

  nOfReroutingFailed = getDpnOfReroutingFailed();
  nOfReroutingFailed += 1;
  setDpnOfReroutingFailed(nOfReroutingFailed);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N6. */
void CrPsPcktReroutingFailN6(FwPrDesc_t prDesc)
{
  unsigned short tcPacketId;

  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;

  FwSmDesc_t  smDesc;
  prData_t* prData;

  /* Update data pool variable pcktIdRerouting, invDestRerouting */
  /*printf("CrPsPcktReroutingFailN6: Update data pool variable pcktIdRerouting, invDestRerouting\n");*/

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);
  smDesc = prData->smDesc;

   /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* Set pcktIdRerouting */
  tcPacketId = CrFwPcktGetPid(inPckt); /* --- adaptation point CrFwPckt ---> */
  setDppcktIdReroutingFailed(tcPacketId);

  /* Set invDestRerouting */
  setDpinvDestRerouting(prData->ushortParam1);

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION1 to N1. */
FwPrBool_t CrPsPcktReroutingFailG1(FwPrDesc_t prDesc)
{
  FwSmDesc_t  smDesc;
  prData_t* prData;

  /* [ Packet encapsulates a report ] */
  /*printf("CrPsPcktReroutingFailG1: Guard on the Control Flow from DECISION1 to N1.\n");*/

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
FwPrBool_t CrPsPcktReroutingFailG1E(FwPrDesc_t prDesc)
{
  FwSmDesc_t  smDesc;
  prData_t* prData;

  /* [ Packet encapsulates a command ] */
  /*printf("CrPsPcktReroutingFailG1E: Guard on the Control Flow from DECISION1 to N2.\n");*/

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
FwPrBool_t CrPsPcktReroutingFailG2(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* [ OutFactory fails to generate OutComponent ] */
  /*printf("CrPsPcktReroutingFailG2: Guard on the Control Flow from DECISION2 to N3.\n");*/
  
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

