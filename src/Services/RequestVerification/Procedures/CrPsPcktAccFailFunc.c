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

#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsParamSetter.h>
#include <CrPsPcktUtilities.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

FwSmDesc_t cmd, rep;

/* ----------------------------------------------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------------------ */
/** Action for node N1. */
void CrPsPcktAccFailN1(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* TODO: Generate error report INLOADER_ACC_FAIL */

  printf("CrPsPcktAccFailN1: Generate error report INLOADER_ACC_FAIL\n");

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N2. */
void CrPsPcktAccFailN2(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Retrieve an OutComponent of type (1,2) from the OutFactory */

  printf("CrPsPcktAccFailN2: Retrieve an OutComponent of type (1,2) from the OutFactory\n");

  /* Create out component */
  rep = CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, CRPS_REQVERIF_ACC_FAIL, 0, 0);

#if 0
  /* --- FOR TESTING --- */
{
  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;

  FwSmDesc_t  smDesc;
  FwSmDesc_t* prData;

  CrFwCmdRepType_t inPcktType;

  prData = (unsigned short*)FwPrGetData(prDesc);

  printf("CrPsPcktAccFailN2: prData[0]: smDesc = %d\n", prData[0]);
  printf("CrPsPcktAccFailN2: prData[1]: failCode = %d\n", prData[1]);

  smDesc = prData[0];

   /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* Get packet type */
  inPcktType = CrFwPcktGetCmdRepType(inPckt);
  if (inPcktType == crRepType)
    {
      printf("CrPsPcktAccFailN2: Packet Type is Report.\n");
    }
  else if (inPcktType == crCmdType)
    {
      printf("CrPsPcktAccFailN2: Packet Type is Command.\n");
    }
  else
    {
      printf("CrPsPcktAccFailN2: UNKNOWN PACKET TYPE!\n");
    }
}
#endif

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N3. */
void CrPsPcktAccFailN3(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* TODO: Generate error report OUTFACTORY_FAIL */

  printf("CrPsPcktAccFailN3: Generate error report OUTFACTORY_FAIL\n");

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N4. */
void CrPsPcktAccFailN4(FwPrDesc_t __attribute__((unused)) prDesc)
{
  CrFwDestSrc_t source;
  unsigned short tcPacketId;
  unsigned char tcType, tcSubtype, tcDiscriminant;
  unsigned int tcVerFailData;

  CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;

  FwSmDesc_t  smDesc;
  FwSmDesc_t* prData;

  /* Configure report (1,2) and load it in the OutLoader */

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);

  smDesc = prData[0];

   /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* Set pcktIdAccFailed */
  tcPacketId = CrFwPcktGetPid(inPckt); /* --- adaptation point CrFwPckt ---> */
  CrPsServReqVerifAccFailParamSetPacketId(rep, tcPacketId);

  /* Set failCodeAccFailed */
  CrPsServReqVerifAccFailParamSetFailureCode(rep, (uintptr_t)prData[1]);

  /* Set Type of the command */
  tcType = CrFwPcktGetServType(inPckt); /* --- adaptation point CrFwPckt ---> */
  CrPsServReqVerifAccFailParamSetType(rep, tcType);

  /* Set Subtype of the command */
  tcSubtype = CrFwPcktGetServSubType(inPckt); /* --- adaptation point CrFwPckt ---> */
  CrPsServReqVerifAccFailParamSetSubtype(rep, tcSubtype);

  /* Set Discriminant of the command */
  tcDiscriminant = CrFwPcktGetDiscriminant(inPckt); /* --- adaptation point CrFwPckt ---> */
  CrPsServReqVerifAccFailParamSetDiscriminant(rep, tcDiscriminant);

  /* TODO: Set verFailData */
  tcVerFailData = 12345; /* TODO: get it from data pool */
  CrPsServReqVerifAccFailParamSetVerFailData(rep, tcVerFailData);

  /* Set the destination of the report to the source of the in-coming packet */
  source = CrFwPcktGetSrc(inPckt);
  CrFwOutCmpSetDest(rep, source);

  /* Load report in the Outloader */
  CrFwOutLoaderLoad(rep);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N5. */
void CrPsPcktAccFailN5(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /*unsigned short nOfAccFailed;*/

  /* TODO: Increment data pool variable nOfAccFailed */

  printf("CrPsPcktAccFailN5: Increment data pool variable nOfAccFailed\n");

#if 0
  CrIaCopy(NOFACCFAILED_ID, &nOfAccFailed);
  nOfAccFailed += 1;
  CrIaPaste(NOFACCFAILED_ID, &nOfAccFailed);
#endif

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N6. */
void CrPsPcktAccFailN6(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* TODO: Update data pool variable pcktIdAccFailed, failCodeAccFailed */

  printf("CrPsPcktAccFailN6: Update data pool variable pcktIdAccFailed, failCodeAccFailed\n");

#if 0
  CrIaPaste(PCKTIDACCFAILED_ID, &pcktIdAccFailed);

  CrIaPaste(FAILCODEACCFAILED_ID, &failCodeAccFailed);
#endif

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION1 to N1. */
FwPrBool_t CrPsPcktAccFailG1(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /*CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;*/

  FwSmDesc_t  smDesc;
  FwSmDesc_t* prData;

  /*CrFwCmdRepType_t inPcktType;*/

  /* [ Packet encapsulates a report ] */

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);
  smDesc = prData[0];

  if (CrFwCmpGetTypeId(smDesc) == CR_FW_INREPORT_TYPE)
    {
      return 1;
    }
  else
    {
      return 0;
    }

#if 0
   /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* Get packet type */
  inPcktType = CrFwPcktGetCmdRepType(inPckt);
  if (inPcktType == crRepType)
    {
      return 1;
    }
  else
    {
      return 0;
    }
#endif

}

/** Guard on the Control Flow from DECISION1 to N2. */
FwPrBool_t CrPsPcktAccFailG1E(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /*CrFwCmpData_t*   inData;
  CrFwInCmdData_t* inSpecificData;
  CrFwPckt_t       inPckt;*/

  FwSmDesc_t  smDesc;
  FwSmDesc_t* prData;

  /*CrFwCmdRepType_t inPcktType;*/

  /* [ Packet encapsulates a command ] */

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);
  smDesc = prData[0];

  if (CrFwCmpGetTypeId(smDesc) == CR_FW_INCOMMAND_TYPE)
    {
      return 1;
    }
  else
    {
      return 0;
    }

#if 0
   /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* Get packet type */
  inPcktType = CrFwPcktGetCmdRepType(inPckt);
  if (inPcktType == crCmdType)
    {
      return 1;
    }
  else
    {
      return 0;
    }
#endif

}

/** Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsPcktAccFailG2(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* [ OutFactory fails to generate OutComponent ] */

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

