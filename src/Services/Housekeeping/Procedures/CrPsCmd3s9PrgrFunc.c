/**
 * @file CrPsCmd3s9PrgrFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:16:17
 */

/** CrPsCmd3s9Prgr function definitions */
#include "CrPsCmd3s9PrgrCreate.h"

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
#include <Services/General/CrPsPktServHk.h>
#include <Services/General/CrPsPktServHkSupp.h>
#include <CrPsDebug.h>
#include <CrPsUtilitiesServHk.h>
#include <CrPsRepErr.h>


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FwSmDesc_t      rep;
CrPsSid_t       currentSid;
CrFwCounterU4_t iSid;


/* ----------------------------------------------------------------------------------------------------------------- */

/** Action for node N1. */
void CrPsCmd3s9PrgrN1(FwPrDesc_t prDesc)
{
  CrFwCmpData_t       *cmpData;
  CrFwInCmdData_t     *cmpSpecificData;
  CrFwPckt_t           pckt;
  prDescCmd3s9Start_t *prDataPtr;
  FwSmDesc_t           smDesc;
  CrFwServSubType_t    tcServSubType;

  /* Retrieve a (3,10) or (3,12) report from the OutFactory to hold
   * the structurereport for the SID which is being processed */
  
  /* Get smDesc from prData */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Get inPckt */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get SubType */
  tcServSubType = CrFwPcktGetServSubType(pckt);

  /* Generate report of type (3,10) or (3,12) according to TC(3,9) or TC(3,11) */
  if (tcServSubType == 9)
    {
      rep  = CrFwOutFactoryMakeOutCmp(CRPS_HK, CRPS_HK_HKREP_STRUCT_REP, currentSid, getHkRepStructSize(currentSid)); /* arguments: type, subType, discriminant/evtId, length */
    }
  else if (tcServSubType == 11)
    {
      rep  = CrFwOutFactoryMakeOutCmp(CRPS_HK, CRPS_HK_DIAGREP_STRUCT_REP, currentSid, getHkRepStructSize(currentSid)); /* arguments: type, subType, discriminant/evtId, length */
    }

  return;
}

/** Action for node N2. */
void CrPsCmd3s9PrgrN2(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  /* Load the SID which is being processed in data pool item verFailData */

  setDpverFailData((uint32_t)currentSid);

  return;
}

/** Action for node N3. */
void CrPsCmd3s9PrgrN3(FwPrDesc_t prDesc)
{
  FwSmDesc_t          smDesc;  
  prDescCmd3s9Prgr_t *prDataPtr;
  CrPsStepId_t        stepIdentifier;  /*StepID ist 32 bit .. war aber unsigned short*/
  CrPsFailCode_t      tcFailureCode;

  /* Run the Command Progress Failure Procedure */

  /* Get smDesc from prData */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  stepIdentifier = iSid;
  tcFailureCode = OUTFACTORY_FAIL; /* TODO: check if correct use for Service 1 reports */

  CRFW_UNUSED(smDesc);
  CRFW_UNUSED(tcFailureCode);
  CRFW_UNUSED(stepIdentifier);

  /*SendReqVerifPrgrFailRep(smDesc, stepIdentifier, tcFailureCode);*/ /* TODO: can not be sent: segmentation fault 
    pckt can not be retrieved by cmpSpecificData->pckt in CrFwOutCmp: CrFwOutCmpSetDest(FwSmDesc_t smDesc, CrFwDestSrc_t dest) */

  return;
}

/** Action for node N4. */
void CrPsCmd3s9PrgrN4(FwPrDesc_t prDesc)
{
  CrPsRepErrCode_t errCode;
  CRFW_UNUSED(prDesc);

  /* Generate error report OUTFACTORY_FAIL */

  errCode = crOutfactoryFail;
  CrPsRepErr(errCode, CRPS_REQVERIF, CRPS_REQVERIF_PROG_FAIL, 0);

  return;
}

/** Action for node N5. */
void CrPsCmd3s9PrgrN5(FwPrDesc_t prDesc)
{
  CrFwCmpData_t       *cmpData;
  CrFwInCmdData_t     *cmpSpecificData;
  CrFwPckt_t           pckt;  
  prDescCmd3s9Prgr_t  *prDataPtr;
  FwSmDesc_t           smDesc;
  CrFwDestSrc_t dest;

  /* Configure the (3,10) or (3,12) report with the SID being processed and load it in the OutLoader */

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Get inPckt */
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt = cmpSpecificData->pckt;

  dest = CrFwPcktGetSrc(pckt);
  CrFwOutCmpSetDest(rep, dest);

  CrFwOutLoaderLoad(rep);

  return;
}

/** Action for node N6. */
void CrPsCmd3s9PrgrN6(FwPrDesc_t prDesc)
{
  prDescCmd3s9Prgr_t *prDataPtr;
  CrFwCmpData_t      *cmpData;
  FwSmDesc_t          smDesc;

  /* Set action outcome to: 'completed' */

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Set outcome in prData */
  prDataPtr->outcome = 1;
  FwPrSetData(prDesc, prDataPtr);

  /* Set outcome in InCmd prData to 'success' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = 1;
  FwSmSetData(smDesc, cmpData);

  return;  
}

/** Action for node N7. */
void CrPsCmd3s9PrgrN7(FwPrDesc_t prDesc)
{
  prDescCmd3s9Prgr_t *prDataPtr;
  CrFwCmpData_t      *cmpData;
  FwSmDesc_t          smDesc;

  /* Set action outcome to: 'continue' */

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;
  
  /* Set outcome in prData */
  prDataPtr->outcome = 2;
  FwPrSetData(prDesc, prDataPtr);

  /* Set outcome in InCmd prData to 'continue' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = 2;
  FwSmSetData(smDesc, cmpData);

  return;
}

/** Action for node N8. */
void CrPsCmd3s9PrgrN8(FwPrDesc_t prDesc)
{
  prDescCmd3s9Prgr_t *prDataPtr;
  CrPsSid_t          *sid;

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
void CrPsCmd3s9PrgrN9(FwPrDesc_t prDesc)
{
  prDescCmd3s9Prgr_t *prDataPtr;
  CrPsSid_t          *sid;

  /* Process the next valid SID in the command */

  /* Get sid from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  sid = prDataPtr->sidPtr;

  /* Get next SID */
  iSid++;
  currentSid = sid[iSid];

  return;
}

/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION1 to N2. */
FwPrBool_t CrPsCmd3s9PrgrG1(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* OutFactory fails to return a report  */

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
FwPrBool_t CrPsCmd3s9PrgrG2(FwPrDesc_t prDesc)
{
  prDescCmd3s9Prgr_t *prDataPtr;
  CrPsSid_t          *sid;

  /* This SID was the last valid SID in the (3,9) or (3,11)  */

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
FwPrBool_t CrPsCmd3s9PrgrG3(FwPrDesc_t prDesc)
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

