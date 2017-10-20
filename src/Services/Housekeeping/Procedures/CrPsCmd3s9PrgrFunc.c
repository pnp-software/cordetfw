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
#include <CrPsUtilities.h>
#include <CrPsRepErr.h>


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FwSmDesc_t rep;
unsigned char currentSid;
unsigned int iSid;


/* ----------------------------------------------------------------------------------------------------------------- */

/** Action for node N1. */
void CrPsCmd3s9PrgrN1(FwPrDesc_t prDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t pckt;
  prDescCmd3s9Start_t* prDataPtr;
  FwSmDesc_t smDesc;
  CrFwServSubType_t tcServSubType;

  /* Retrieve a (3,10) or (3,12) report from the OutFactory to hold
   * the structurereport for the SID which is being processed */
  
  DEBUGP_3("CrPsCmd3s9PrgrN1.\n");

  /* Get smDesc from prData */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Get inPckt */
  cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get SubType */
  tcServSubType = CrFwPcktGetServSubType(pckt);

  /* Generate report of type (3,10) or (3,12) according to TC(3,9) or TC(3,11) */
  if (tcServSubType == 9)
    {
      rep  = CrFwOutFactoryMakeOutCmp(CRPS_HK, CRPS_HK_HKREP_STRUCT_REP, 0, 0); /* arguments: type, subType, discriminant/evtId, length */
    }
  else if (tcServSubType == 11)
    {
      rep  = CrFwOutFactoryMakeOutCmp(CRPS_HK, CRPS_HK_DIAGREP_STRUCT_REP, 0, 0); /* arguments: type, subType, discriminant/evtId, length */
    }

  return;
}

/** Action for node N2. */
void CrPsCmd3s9PrgrN2(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  /* Load the SID which is being processed in data pool item verFailData */

  DEBUGP_3("CrPsCmd3s9PrgrN2.\n");

  setDpverFailData((uint32_t)currentSid);

  return;
}

/** Action for node N3. */
void CrPsCmd3s9PrgrN3(FwPrDesc_t prDesc)
{
  FwSmDesc_t smDesc;  
  prDescCmd3s9Prgr_t *prDataPtr;
  unsigned short stepIdentifier;
  unsigned short tcFailureCode;

  /* Run the Command Progress Failure Procedure */

  DEBUGP_3("CrPsCmd3s9PrgrN3.\n");

  /* Get smDesc from prData */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  stepIdentifier = iSid;
  tcFailureCode = OUTFACTORY_FAIL; /* TODO: check if correct use for Service 1 reports */
  SendReqVerifPrgrFailRep(smDesc, stepIdentifier, tcFailureCode);

  return;
}

/** Action for node N4. */
void CrPsCmd3s9PrgrN4(FwPrDesc_t prDesc)
{
  CrPsRepErrCode_t errCode;
  CRFW_UNUSED(prDesc);

  /* Generate error report OUTFACTORY_FAIL */

  DEBUGP_3("CrPsCmd3s9PrgrN4.\n");

  errCode = crOutfactoryFail;
  CrPsRepErr(errCode, CRPS_REQVERIF, CRPS_REQVERIF_PROG_FAIL, 0);

  return;
}

/** Action for node N5. */
void CrPsCmd3s9PrgrN5(FwPrDesc_t prDesc)
{
  CrFwDestSrc_t dest;

  unsigned int i, j;

  unsigned char rdlSid, rdlSlot;
  uint8_t PeriodicGenActionStatus = 1;
  uint32_t CollectionInterval;
  uint32_t N1;
  uint16_t N1ParamId;
  uint32_t NFA;
  uint32_t SCSampleRepNum;
  uint32_t N2;
  uint16_t N2ParamId;
  unsigned int offset;

  CRFW_UNUSED(prDesc);
  /* Configure the (3,10) or (3,12) report with the SID being processed and load it in the OutLoader */

  DEBUGP_3("CrPsCmd3s9PrgrN5.\n");

  /* TODO: set RDL information in out-going report packet */
  /* Get report structure ID (SID) and set in out-going report packet */
  setHkRepStructRepRepStrucId(rep, currentSid);

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {
      rdlSid = getDpsidItem(rdlSlot);
      printf("SID in RDL[%d] = %d\n", rdlSlot, rdlSid);

      if (currentSid == rdlSid)
        break;
    }  

  /* Get periodic generation action status and set in out-going report packet */
  setHkRepStructRepPeriodicGenActionStatus(rep, PeriodicGenActionStatus);

  /* Get collection interval and set in out-going report packet */
  CollectionInterval = getDpperiodItem(rdlSlot);
  setHkRepStructRepCollectionInterval(rep, CollectionInterval);

  /* Get N1 and set in out-going report packet */
  N1 = getDpnSimpleItem(rdlSlot);

  /* Get N1 parameter IDs and set them in out-going report packet */
  for (i=0; i<N1; i++)
    {
      N1ParamId = getDplstIdItem(rdlSlot*HK_MAX_N_ITEMS + i);
      setHkRepStructRepN1ParamIdItem(rep, i+1, N1ParamId);
    }

  /* Get NFA and set in out-going report packet */
  NFA = getNFA(rdlSlot);
  setHkRepStructRepNFA(rep, NFA);

  offset = 0;

  for (i=0; i<NFA; i++)
    {
      /* Get sample repition number and set in out-going report packet */
      SCSampleRepNum = getDplstSampleRepItem(rdlSlot*HK_MAX_N_GR + i);
      setHkRepStructRepSCSampleRepNumItem(rep, i+1, SCSampleRepNum);

      /* Get N2 and set in out-going report packet */
      N2 = getDplstNSampRepItem(rdlSlot*HK_MAX_N_GR + i);
      setHkRepStructRepN2(rep, i+1, N2);

      /* Get N2 parameter IDs and set them in out-going report packet */
      for (j=0; j<N2; j++)
        {
          N2ParamId = getDplstIdItem(rdlSlot*HK_MAX_N_ITEMS + N1 + offset + j);
          setHkRepStructRepN2ParamIdItem(rep, i+1, j+1, N2ParamId);
        }

      /* update offset */
      offset += N2;
    }

  dest = 1;
  CrFwOutCmpSetDest(rep, dest);

  CrFwOutLoaderLoad(rep);

  return;
}

/** Action for node N6. */
void CrPsCmd3s9PrgrN6(FwPrDesc_t prDesc)
{
  prDescCmd3s9Prgr_t* prDataPtr;
  CrFwCmpData_t* cmpData;
  FwSmDesc_t smDesc;

  /* Set action outcome to: 'completed' */

  DEBUGP_3("CrPsCmd3s9PrgrN6.\n");

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Set outcome in InCmd prData to 'success' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = 1;
  FwSmSetData(smDesc, cmpData);

  return;  
}

/** Action for node N7. */
void CrPsCmd3s9PrgrN7(FwPrDesc_t prDesc)
{
  prDescCmd3s9Prgr_t* prDataPtr;
  CrFwCmpData_t* cmpData;
  FwSmDesc_t smDesc;

  /* Set action outcome to: 'continue' */

  DEBUGP_3("CrPsCmd3s9PrgrN7.\n");

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Set outcome in InCmd prData to 'success' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = 2;
  FwSmSetData(smDesc, cmpData);

  return;
}

/** Action for node N8. */
void CrPsCmd3s9PrgrN8(FwPrDesc_t prDesc)
{
  prDescCmd3s9Prgr_t* prDataPtr;
  unsigned char* sid;

  /* Start processing the first valid SID in the command */

  DEBUGP_3("CrPsCmd3s9PrgrN8.\n");

  /* Get sid from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  sid = prDataPtr->sidPtr;

  /* Get first SID */
  iSid = 0;
  currentSid = sid[iSid];
  printf("CrPsCmd3s9PrgrN8. SID = %d\n", currentSid);

  return;
}

/** Action for node N9. */
void CrPsCmd3s9PrgrN9(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  /* Process the next valid SID in the command */

  DEBUGP_3("CrPsCmd3s9PrgrN9.\n");

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

  DEBUGP_3("CrPsCmd3s9PrgrG1.\n");

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
  prDescCmd3s9Prgr_t* prDataPtr;
  unsigned char* sid;

  /* This SID was the last valid SID in the (3,9) or (3,11)  */

  DEBUGP_3("CrPsCmd3s9PrgrG2.\n");

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

  DEBUGP_3("CrPsCmd3s9PrgrG3.\n");

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

