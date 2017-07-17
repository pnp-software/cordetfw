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
/** Action for node N2. */
void CrPsCmdPrgrFailN2(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Retrieve an OutComponent of type (1,6) from the OutFactory */

  printf("CrPsCmdPrgrFailN2: Retrieve an OutComponent of type (1,6) from the OutFactory\n");

  /* Create out component */
  rep = CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, CRPS_REQVERIF_PROG_FAIL, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N3. */
void CrPsCmdPrgrFailN3(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* TODO: Generate error report OUTFACTORY_FAIL */

  printf("CrPsCmdPrgrFailN3: Generate error report OUTFACTORY_FAIL\n");

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N4. */
void CrPsCmdPrgrFailN4(FwPrDesc_t __attribute__((unused)) prDesc)
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

  /* Configure report and load it in the OutLoader */

  printf("CrPsCmdPrgrFailN4: Configure report and load it in the OutLoader\n");

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);

  smDesc = prData[0];

   /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* Set pcktIdAccFailed */
  tcPacketId = CrFwPcktGetPid(inPckt); /* --- adaptation point CrFwPckt ---> */
  CrPsServReqVerifPrgrFailParamSetPacketId(rep, tcPacketId);

  /* Set stepId */
  CrPsServReqVerifPrgrFailParamSetStepId(rep, (uintptr_t)prData[1]);

  /* Set failCodeAccFailed */
  CrPsServReqVerifPrgrFailParamSetFailureCode(rep, (uintptr_t)prData[2]);

  /* Set Type of the command */
  tcType = CrFwPcktGetServType(inPckt); /* --- adaptation point CrFwPckt ---> */
  CrPsServReqVerifPrgrFailParamSetType(rep, tcType);

  /* Set Subtype of the command */
  tcSubtype = CrFwPcktGetServSubType(inPckt); /* --- adaptation point CrFwPckt ---> */
  CrPsServReqVerifPrgrFailParamSetSubtype(rep, tcSubtype);

  /* Set Discriminant of the command */
  tcDiscriminant = CrFwPcktGetDiscriminant(inPckt); /* --- adaptation point CrFwPckt ---> */
  CrPsServReqVerifPrgrFailParamSetDiscriminant(rep, tcDiscriminant);

  /* TODO: Set verFailData */
  tcVerFailData = 54321; /* TODO: get it from data pool */
  CrPsServReqVerifPrgrFailParamSetVerFailData(rep, tcVerFailData);

  /* Set the destination of the report to the source of the in-coming packet */
  source = CrFwPcktGetSrc(inPckt);
  CrFwOutCmpSetDest(rep, source);

  /* Load report in the Outloader */
  CrFwOutLoaderLoad(rep);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N5. */
void CrPsCmdPrgrFailN5(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Increment data pool variable nOfPrgrFailed */

  printf("CrPsCmdPrgrFailN5: Increment data pool variable nOfPrgrFailed\n");

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N6. */
void CrPsCmdPrgrFailN6(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Update data pool variable pcktIdPrgrFailed, failCodePrgrFailed and prgrStepFailed */

  printf("CrPsCmdPrgrFailN6: Update data pool variable pcktIdPrgrFailed, failCodePrgrFailed and prgrStepFailed\n");

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsCmdPrgrFailG1(FwPrDesc_t __attribute__((unused)) prDesc)
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

