/**
 * @file CrPsCmd3s1StartFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:15:56
 */

/** CrPsCmd3s1Start function definitions */
#include "CrPsCmd3s1StartCreate.h"

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

#include <CrPsRepErr.h>
#include <CrPsUserConstants.h>
#include <DataPool/CrPsDpServReqVerif.h>
#include <DataPool/CrPsDpServHk.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServHk.h>
#include <CrPsDebug.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FwSmDesc_t rep;
unsigned char rdlSlot;
CrFwCounterU1_t numberOfPendingOutCmpOld;


/* ----------------------------------------------------------------------------------------------------------------- */

/** Action for node N1. */
void CrPsCmd3s1StartN1(FwPrDesc_t prDesc)
{
  prDescCmd3s1Start_t* prDataPtr;
  CrFwCmpData_t* cmpData;
  FwSmDesc_t smDesc;

	/* Set action outcome to 'failure' with failure code VER_FULL_RDL */

	DEBUGP_3("CrPsCmd3s1StartN1.\n");

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Set outcome in InCmd prData to 'failure' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = (unsigned char)VER_FULL_RDL;
  FwSmSetData(smDesc, cmpData);

  return;
}

/** Action for node N2. */
void CrPsCmd3s1StartN2(FwPrDesc_t prDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t pckt;
  prDescCmd3s1Start_t* prDataPtr;
  FwSmDesc_t smDesc;
  CrFwServSubType_t tcServSubType;

  /* Retrieve a report of type (3,25) or (3,26) from the OutFactory */

  DEBUGP_3("CrPsCmd3s1StartN2.\n");

  /* Get smDesc from prData */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Get inPckt */
  cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get SubType */
  tcServSubType = CrFwPcktGetServSubType(pckt);

  /* Generate report of type (3,25) or (3,26) according to TC(3,1) or TC(3,2) */
  if (tcServSubType == 1)
    {
      rep  = CrFwOutFactoryMakeOutCmp(CRPS_HK, CRPS_HK_HKPARAM_REP, 0, 0); /* arguments: type, subType, discriminant/evtId, length */
    }
  else if (tcServSubType == 2)
    {
      rep  = CrFwOutFactoryMakeOutCmp(CRPS_HK, CRPS_HK_DIAGPARAM_REP, 0, 0); /* arguments: type, subType, discriminant/evtId, length */
    }

  return;
}

/** Action for node N3. */
void CrPsCmd3s1StartN3(FwPrDesc_t prDesc)
{
  CrPsRepErrCode_t errCode;
  CRFW_UNUSED(prDesc);

  /* Generate error report OUTFACTORY_FAIL */

  DEBUGP_3("CrPsCmd3s1StartN3.\n");

  errCode = crOutfactoryFail;
  CrPsRepErr(errCode, CRPS_REQVERIF, CRPS_REQVERIF_PROG_FAIL, 0);

  return;
}

/** Action for node N4. */
void CrPsCmd3s1StartN4(FwPrDesc_t prDesc)
{
  FwSmDesc_t outManager;
  CrFwDestSrc_t dest;
  
  CRFW_UNUSED(prDesc);
  /* Load the report in the OutLoader */

  DEBUGP_3("CrPsCmd3s1StartN4.\n");

  /* TODO: get outManager */
  outManager = CrFwOutManagerMake(0);
  numberOfPendingOutCmpOld = CrFwOutManagerGetNOfPendingOutCmp(outManager);

  dest = 1;
  CrFwOutCmpSetDest(rep, dest);

  CrFwOutLoaderLoad(rep);

  return;
}


/** Action for node N5. */
void CrPsCmd3s1StartN5(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  return;
}

/** Action for node N6. */
void CrPsCmd3s1StartN6(FwPrDesc_t prDesc)
{
  prDescCmd3s1Start_t* prDataPtr;
  CrFwCmpData_t* cmpData;
  FwSmDesc_t smDesc;

  /* Set action outcome to 'success' */

  DEBUGP_3("CrPsCmd3s1StartN6.\n");

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
void CrPsCmd3s1StartN7(FwPrDesc_t prDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;    
  prDescCmd3s1Start_t* prDataPtr;
  FwSmDesc_t smDesc;
  uint8_t sid;

  /* Set action outcome to 'failure' with code VER_SID_IN_USE and load SID in verFailData data pool item */

  DEBUGP_3("CrPsCmd3s1StartN7.\n");

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Set outcome in InCmd prData to 'failure' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = (unsigned char)VER_SID_IN_USE;
  FwSmSetData(smDesc, cmpData);

  /* Get inPckt */
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get SID from inPckt */
  sid = getHkCreateCmdRepStrucId(pckt);  

  /* Load SID in verFailData data pool item */
  setDpverFailData((uint32_t)sid);

  return;
}

/** Action for node N8. */
void CrPsCmd3s1StartN8(FwPrDesc_t prDesc)
{
  prDescCmd3s1Start_t* prDataPtr;
  CrFwCmpData_t* cmpData;
  FwSmDesc_t smDesc;

  /* Set action outcome to 'failure' with failure code VER_RDL_CONSTR and load identifier of constraint in verFailData */

  DEBUGP_3("CrPsCmd3s1StartN8.\n");

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Set outcome in InCmd prData to 'failure' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = (unsigned char)VER_RDL_CONSTR;
  FwSmSetData(smDesc, cmpData);

  /* Load identifier of constraint in verFailData */
  setDpverFailData((uint32_t)VER_RDL_CONSTR);

  return;
}

/** Action for node N9. */
void CrPsCmd3s1StartN9(FwPrDesc_t prDesc)
{
  prDescCmd3s1Start_t* prDataPtr;
  CrFwCmpData_t* cmpData;
  FwSmDesc_t smDesc;

  /* Set action outcome to 'failure' with code VER_DUPL_DI and load identifier of duplicated DI in verFailData */

  DEBUGP_3("CrPsCmd3s1StartN9.\n");

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Set outcome in InCmd prData to 'failure' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = (unsigned char)VER_DUPL_DI;
  FwSmSetData(smDesc, cmpData);

  /* Load identifier of duplicated DI in verFailData */
  setDpverFailData((uint32_t)VER_DUPL_DI);

  return;
}

/** Action for node N10. */
void CrPsCmd3s1StartN10(FwPrDesc_t prDesc)
{
  prDescCmd3s1Start_t* prDataPtr;
  CrFwCmpData_t* cmpData;
  FwSmDesc_t smDesc;

  /* Set action outcome to 'failure' with failure code VER_REP_CR_FD */

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  DEBUGP_3("CrPsCmd3s1StartN10.\n");

  /* Set outcome in InCmd prData to 'failure' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = (unsigned char)VER_REP_CR_FD;
  FwSmSetData(smDesc, cmpData);

  return;
}

/** Action for node N11. */
void CrPsCmd3s1StartN11(FwPrDesc_t prDesc)
{
  prDescCmd3s1Start_t* prDataPtr;
  CrFwCmpData_t* cmpData;
  FwSmDesc_t smDesc;

  /* Set action outcome to 'failure' with falure code VER_OUTLOADER_FD */

  DEBUGP_3("CrPsCmd3s1StartN11.\n");

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Set outcome in InCmd prData to 'failure' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = (unsigned char)VER_OUTLOADER_FD;
  FwSmSetData(smDesc, cmpData);

  return;
}

/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION1 to N1. */
FwPrBool_t CrPsCmd3s1StartG1(FwPrDesc_t prDesc)
{
  unsigned char rdlSid;

  CRFW_UNUSED(prDesc);
  /* There is no free slot in the RDL  */

  DEBUGP_3("CrPsCmd3s1StartG1.\n");

  /* look for a free slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {
      rdlSid = getDpsidItem(rdlSlot);
      printf("SID in RDL[%d] = %d\n", rdlSlot, rdlSid);
      
      if (rdlSid == 0)
        break;
    }

  if (rdlSlot == HK_N_REP_DEF)
    {
      printf("There is no free slot left!\n");
      return 1;
    }
  else
    {
      printf("A free slot was found at position %d\n", rdlSlot);
	    return 0;
	  }
}

/** Guard on the Control Flow from DECISION2 to N8. */
FwPrBool_t CrPsCmd3s1StartG2(FwPrDesc_t prDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;  
  prDescCmd3s1Start_t* prDataPtr;
  FwSmDesc_t smDesc;
  uint8_t sid;
  uint32_t N1;
  int period;

  /* One or more constraints listed in table 9.1 are not satisfied */

  DEBUGP_3("CrPsCmd3s1StartG2.\n");

  /* Get smDesc from prData */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Get in data */
  cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get sid and check: Integer in range: 1..HK_MAX_SID */
  sid = getHkCreateCmdRepStrucId(pckt);
  if ((sid == 0) || (sid > HK_MAX_SID))
    return 1;

  /* Get period and check: Positive integer */
  period = getHkCreateCmdCollectionInterval(pckt);
  if (period < 0)
    return 1;

  /* Get nSimple and check: Integer in range: 1..HK_MAX_N_SIMPLE */
  N1 = getHkCreateCmdN1(pckt);
  if ((N1 == 0) || (N1 > HK_MAX_N_SIMPLE))
    return 1;

  /* Get lstSampleRep and check: TBV */

  /* Get lstNSampRep and check: TBV */

  /* Get lstId and check: TBV */

  /* Get sampleBufId and check: Integer in range: 1..HK_N_SAMP_BUF */

	return 0;
}

/** Guard on the Control Flow from DECISION3 to N7. */
FwPrBool_t CrPsCmd3s1StartG3(FwPrDesc_t prDesc)
{
  unsigned char rdlSid, sid;

  CRFW_UNUSED(prDesc);
  /* The SID in the command is already in use  */

  DEBUGP_3("CrPsCmd3s1StartG3.\n");

  /* Get sid */
  sid = 1;

  /* look for the same sid in RDL */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {
      rdlSid = getDpsidItem(rdlSlot);
      printf("SID in RDL[%d] = %d\n", rdlSlot, rdlSid);
      
      if (rdlSid == sid)
        break;
    }

  if (rdlSlot == HK_N_REP_DEF)
    {
      printf("The sid is not used.\n");
      return 0;
    }
  else
    {
      printf("The sid is already used at position %d\n", rdlSlot);
      return 1;
    }
}

/** Guard on the Control Flow from DECISION4 to N9. */
FwPrBool_t CrPsCmd3s1StartG4(FwPrDesc_t prDesc)
{
  uint16_t currentDataItem, checkDataItem;
  unsigned int i, k, m;
  unsigned int N1, NFA, N2[10], LSTNMB; /* TODO: set maximum as constant */
  unsigned short dataItemArray[100];    /* TODO: set maximum as constant */

  CRFW_UNUSED(prDesc);
  /* The same data item identifier appears twice in the definition of the new report  */

  DEBUGP_3("CrPsCmd3s1StartG4.\n");

  /* TODO: Get N1 and NFA */
  N1 = 2; /* nSimple */

  /* Calculate number of data items: only nSimple items ... */
  LSTNMB = N1;

  /* TODO: Get N2 NFA times; NFA is number of groups (nGroup) */
  NFA = 2;
  for (i=0; i<NFA; i++)
    {
      N2[i] = 1; /* nRep[GroupX] */
      /* ... add super-cummutated group items */
      LSTNMB += N2[i];
    } 

  /* Collect all data items in an array */
  for (k=0; k<N1; k++)
    {
      dataItemArray[k] = 1; /* TODO: insert getter */
    }

  for (k=0; k<NFA; k++)
    {
      for (m=0; m<N2[k]; m++)
        {
          dataItemArray[N1+k] = 1; /* TODO: insert getter */
        }
    }

  /* Go through all data item identifiers */
  for (i=0; i<LSTNMB; i++)
    {
      /* Get next data item */
      checkDataItem = dataItemArray[i];
      
      for(k=0;k<LSTNMB-i;k++)
        {
          /* Get next data item identifiers coming afterwards */
          currentDataItem = dataItemArray[i+k+1];

          /* Compare with data item identifiers */
          if (checkDataItem == currentDataItem)
            return 1;
        }

    }

  return 0;
}

/** Guard on the Control Flow from DECISION5 to N3. */
FwPrBool_t CrPsCmd3s1StartG5(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Factory fails to return the report  */

	DEBUGP_3("CrPsCmd3s1StartG5.\n");

  if (rep == NULL)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/** Guard on the Control Flow from DECISION6 to N5. */
FwPrBool_t CrPsCmd3s1StartG6(FwPrDesc_t prDesc)
{
  FwSmDesc_t outManager;
  CrFwCounterU1_t numberOfPendingOutCmp;

  CRFW_UNUSED(prDesc);
  /* Load Operation is successful   */

  DEBUGP_3("CrPsCmd3s1StartG6.\n");

  /* TODO: get outManager */
  outManager = CrFwOutManagerMake(0);
  numberOfPendingOutCmp = CrFwOutManagerGetNOfPendingOutCmp(outManager);

  if (numberOfPendingOutCmp == (numberOfPendingOutCmpOld + 1))
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/* ----------------------------------------------------------------------------------------------------------------- */

