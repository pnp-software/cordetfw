/**
 * @file CrPsCmdVerFailFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 18:1:13
 */

/** CrPsCmdVerFail function definitions */
#include "CrPsCmdVerFailCreate.h"

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
#include <DataPool/CrPsDpServReqVerif.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

FwSmDesc_t cmd, rep;

/* ----------------------------------------------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------------------ */
/** Action for node N2. */
void CrPsCmdVerFailN2(FwPrDesc_t prDesc)
{
  prData_t* prData;

  /* Retrieve an OutComponent of type (1,4) or (1,8) from the OutFactory */
  /*printf("CrPsCmdVerFailN2: Retrieve an OutComponent of type (1,4) or (1,8) from the OutFactory\n");*/

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);

  /* Create out component */
  rep = CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, prData->ushortParam2, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N3. */
void CrPsCmdVerFailN3(FwPrDesc_t prDesc)
{
  prData_t* prData;
  CrPsRepErrCode_t errCode;

  /* Generate error report OUTFACTORY_FAIL */
  /*printf("CrPsCmdVerFailN3: Generate error report OUTFACTORY_FAIL\n");*/

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);

  errCode = crOutfactoryFail;
  CrPsRepErr(errCode, CRPS_REQVERIF, prData->ushortParam2, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N4. */
void CrPsCmdVerFailN4(FwPrDesc_t prDesc)
{
  CrFwDestSrc_t source;
  unsigned short tcPacketId;
  unsigned char tcType, tcSubtype, tcDiscriminant;

  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;

  FwSmDesc_t  smDesc;
  prData_t* prData;

  /* Configure report and load it in the OutLoader */
  /*printf("CrPsCmdVerFailN4: Configure report and load it in the OutLoader\n");*/

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);

  smDesc = prData->smDesc;

   /* Get in packet */
  inData         = FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  if (prData->ushortParam2 == 4)
  {
    /* 1.4 */
    /* Set pcktIdAccFailed */
    tcPacketId = CrFwPcktGetPid(inPckt); /* --- adaptation point CrFwPckt ---> */
    setVerFailedStartRep0TcPacketId(rep, tcPacketId);

    /* Set failCodeAccFailed */
    setVerFailedStartRep0TcFailureCode(rep, prData->ushortParam1);

    /* Set Type of the command */
    tcType = CrFwPcktGetServType(inPckt); /* --- adaptation point CrFwPckt ---> */
    setVerFailedStartRep0TcType(rep, tcType);

    /* Set Subtype of the command */
    tcSubtype = CrFwPcktGetServSubType(inPckt); /* --- adaptation point CrFwPckt ---> */
    setVerFailedStartRep0TcSubtype(rep, tcSubtype);

    /* Set Discriminant of the command */
    tcDiscriminant = CrFwPcktGetDiscriminant(inPckt); /* --- adaptation point CrFwPckt ---> */
    setVerFailedStartRep0TcFailureCode(rep, tcDiscriminant);
  }

  if (prData->ushortParam2 == 8)
  {
    /* 1.8 */
    /* Set pcktIdAccFailed */
    tcPacketId = CrFwPcktGetPid(inPckt); /* --- adaptation point CrFwPckt ---> */
    setVerFailedTermRepTcPacketId(rep, tcPacketId);

    /* Set failCodeAccFailed */
    setVerFailedTermRepTcFailureCode(rep, prData->ushortParam1);
  
    /* Set Type of the command */
    tcType = CrFwPcktGetServType(inPckt); /* --- adaptation point CrFwPckt ---> */
    setVerFailedTermRepTcType(rep, tcType);

    /* Set Subtype of the command */
    tcSubtype = CrFwPcktGetServSubType(inPckt); /* --- adaptation point CrFwPckt ---> */
    setVerFailedTermRepTcSubtype(rep, tcSubtype);

    /* Set Discriminant of the command */
    tcDiscriminant = CrFwPcktGetDiscriminant(inPckt); /* --- adaptation point CrFwPckt ---> */
    setVerFailedTermRepTcFailureCode(rep, tcDiscriminant);
  }

  /* Set the destination of the report to the source of the in-coming packet */
  source = CrFwPcktGetSrc(inPckt);
  CrFwOutCmpSetDest(rep, source);

  /* Load report in the Outloader */
  CrFwOutLoaderLoad(rep);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N5. */
void CrPsCmdVerFailN5(FwPrDesc_t prDesc)
{
  prData_t* prData;
  unsigned int nOfStartFailed, nOfTermFailed;

  /* Increment data pool variable nOfXyFailed */
  /*printf("CrPsCmdVerFailN5: Increment data pool variable nOfXyFailed\n");*/

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);

  if (prData->ushortParam2 == CRPS_REQVERIF_START_FAIL)
    {
      nOfStartFailed = getDpnOfStartFailed();
      nOfStartFailed += 1;
      setDpnOfStartFailed(nOfStartFailed);
    }
  else if (prData->ushortParam2 == CRPS_REQVERIF_TERM_FAIL)
    {
      nOfTermFailed = getDpnOfTermFailed();
      nOfTermFailed += 1;
      setDpnOfTermFailed(nOfTermFailed);
    }

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N6. */
void CrPsCmdVerFailN6(FwPrDesc_t prDesc)
{
  unsigned short tcPacketId;

  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;

  FwSmDesc_t  smDesc;
  prData_t* prData;

  /* Update data pool variable pcktIdXyFailed and failCodeXyFailed */
  /*printf("CrPsCmdVerFailN6: Update data pool variable pcktIdXyFailed and failCodeXyFailed\n");*/

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);

  smDesc = prData->smDesc;

   /* Get in packet */
  inData         = FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* Set pcktIdAccFailed */
  tcPacketId = CrFwPcktGetPid(inPckt); /* --- adaptation point CrFwPckt ---> */

  if (prData->ushortParam2 == CRPS_REQVERIF_START_FAIL)
    {
      /* Set pcktIdStartFailed */
      setDppcktIdStartFailed(tcPacketId);

      /* Set failCodeStartFailed */
      setDpfailCodeStartFailed(prData->ushortParam1);
    }
  else if (prData->ushortParam2 == CRPS_REQVERIF_TERM_FAIL)
    {
      /* Set pcktIdTermFailed */
      setDppcktIdTermFailed(tcPacketId);

      /* Set failCodeTermFailed */
      setDpfailCodeTermFailed(prData->ushortParam1);
    }

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsCmdVerFailG1(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* [ OutFactory fails to generate OutComponent ] */
  /*printf("CrPsCmdVerFailG1: Guard on the Control Flow from DECISION2 to N3 \n");*/
  
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

