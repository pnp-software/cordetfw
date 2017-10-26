/**
 * @file CrPsCmd3s27PrgrFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:17:0
 */

/** CrPsCmd3s27Prgr function definitions */
#include "CrPsCmd3s27PrgrCreate.h"

/** CR Framework function definitions*/
#include "CrFwConstants.h"

/* CrFramework includes */
#include "Pckt/CrFwPckt.h"
#include "OutFactory/CrFwOutFactory.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"
#include "CrFwCmpData.h"

/** FW Profile function definitions */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"

#include <CrPsUserConstants.h>
#include <DataPool/CrPsDpServReqVerif.h>
#include <DataPool/CrPsDpServHk.h>
#include <Services/General/CrPsConstants.h>
#include <CrPsDebug.h>
#include <CrPsUtilitiesServHk.h>
#include <CrPsUtilitiesServReqVerif.h>
#include <CrPsRepErr.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FwSmDesc_t      rep;
CrPsSid_t       currentSid;
CrFwCounterU4_t iSid;


/* ----------------------------------------------------------------------------------------------------------------- */

/** Action for node N1. */
void CrPsCmd3s27PrgrN1(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* Retrieve a HkOneShotRep report from the OutFactory to hold the one-shot report for the SID */

  /* Create out component */
  rep  = CrFwOutFactoryMakeOutCmp(CRPS_HK, CRPS_HK_HKPARAM_REP, 2, 0);/* arguments: type, subType, discriminant/evtId, length */

  return;
}

/** Action for node N2. */
void CrPsCmd3s27PrgrN2(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* Load the SID which is being processed in data pool item verFailData */

  setDpverFailData((uint32_t)currentSid);

  return;
}

/** Action for node N3. */
void CrPsCmd3s27PrgrN3(FwPrDesc_t prDesc)
{
  FwSmDesc_t                     smDesc;  
  prDescGenerateHkOneShotPrgr_t *prDataPtr;
  CrPsStepId_t                   stepIdentifier; /*war unsigned short StepId ist aber 32 bit*/
  CrPsFailCode_t                 tcFailureCode;

  /* Run the Command Progress Failure Procedure */

  /* Get smDesc from prData */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  stepIdentifier = iSid;
  tcFailureCode = OUTFACTORY_FAIL; /* TODO: check if correct use for Service 1 reports */
  SendReqVerifPrgrFailRep(smDesc, stepIdentifier, tcFailureCode);

  return;
}

/** Action for node N4. */
void CrPsCmd3s27PrgrN4(FwPrDesc_t prDesc)
{
  CrPsRepErrCode_t errCode;
  CRFW_UNUSED(prDesc);

  /* Generate error report OUTFACTORY_FAIL */

  errCode = crOutfactoryFail;
  CrPsRepErr(errCode, CRPS_REQVERIF, CRPS_REQVERIF_PROG_FAIL, 0);

  return;
}

/** Action for node N5. */
void CrPsCmd3s27PrgrN5(FwPrDesc_t prDesc)
{
  CrFwCmpData_t       *cmpData;
  CrFwInCmdData_t     *cmpSpecificData;
  CrFwPckt_t           pckt;  
  prDescGenerateHkOneShotPrgr_t *prDataPtr;
  FwSmDesc_t           smDesc;
  CrFwDestSrc_t dest;

  /* Configure the HkOneShotRep report with the SID being processed and load it in the OutLoader */

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Get inPckt */
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt = cmpSpecificData->pckt;

  dest = CrFwPcktGetSrc(pckt);
  CrFwOutCmpSetDest(rep, dest);

  /* Load the OutRep in the OutLoader */
  CrFwOutLoaderLoad(rep);

  return;
}

/** Action for node N6. */
void CrPsCmd3s27PrgrN6(FwPrDesc_t prDesc)
{
  prDescGenerateHkOneShotPrgr_t *prDataPtr;
  CrFwCmpData_t                 *cmpData;
  FwSmDesc_t                     smDesc;

  /* Set action outcome to: 'completed' */

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Set outcome in InCmd prData to 'completed' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = 1;
  FwSmSetData(smDesc, cmpData);

  return;
}

/** Action for node N7. */
void CrPsCmd3s27PrgrN7(FwPrDesc_t prDesc)
{
  prDescGenerateHkOneShotPrgr_t *prDataPtr;
  CrFwCmpData_t                 *cmpData;
  FwSmDesc_t                     smDesc;

  /* Set action outcome to 'continue' */

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Set outcome in InCmd prData to 'continue' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = 2;
  FwSmSetData(smDesc, cmpData);

  return;
}

/** Action for node N8. */
void CrPsCmd3s27PrgrN8(FwPrDesc_t prDesc)
{
  prDescGenerateHkOneShotPrgr_t *prDataPtr;
  CrPsSid_t                     *sid;

  /* Start processing the first valid SID in the command */

  /* Get sid from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  sid = prDataPtr->sidPtr;

  /* Get first SID */
  iSid = 0;
  currentSid = sid[iSid];

  return;	
}

/** Action for node N9. */
void CrPsCmd3s27PrgrN9(FwPrDesc_t prDesc)
{
  prDescGenerateHkOneShotPrgr_t *prDataPtr;
  CrPsSid_t                     *sid;

  /* Process the next valid SID in the command */

  /* Get sid from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  sid = prDataPtr->sidPtr;

  /* Get next SID from InCmd */
  iSid++;
  currentSid = sid[iSid];

  return;
}

/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION1 to N2. */
FwPrBool_t CrPsCmd3s27PrgrG1(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* OutFactory fails to return a report */

  if (rep == NULL)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/** Guard on the Control Flow from DECISION2 to N6. */
FwPrBool_t CrPsCmd3s27PrgrG2(FwPrDesc_t prDesc)
{
  prDescGenerateHkOneShotPrgr_t *prDataPtr;
  CrPsSid_t                     *sid;

  /* This SID was the last valid SID in the (3,27) or (3,28) */

  /* Get sid from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  sid = prDataPtr->sidPtr;

  /* Check next SID. If 0 the current SID was the last valid one. */
  if (sid[iSid + 1] == 0)
    {
      return 1;
    }
  else
  	{
      return 0;
  	}
}

/** Guard on the Control Flow from N7 to N9. */
FwPrBool_t CrPsCmd3s27PrgrG3(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* Next Execution  */

  if (FwPrGetNodeExecCnt(prDesc))
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/* ----------------------------------------------------------------------------------------------------------------- */

