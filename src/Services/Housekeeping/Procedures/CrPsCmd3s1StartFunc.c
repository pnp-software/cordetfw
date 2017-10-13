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

#include <CrPsUserConstants.h>
#include <DataPool/CrPsDpHk.h>
#include <Services/General/CrPsConstants.h>
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
  CrFwDestSrc_t dest;

  CRFW_UNUSED(prDesc);
  /* Retrieve a report of type (3,25) or (3,26) from the OutFactory */

  DEBUGP_3("CrPsCmd3s1StartN2.\n");

  /* TODO: TBD how to decide if it is a report of type (3,25) or (3,26) */
  rep  = CrFwOutFactoryMakeOutCmp(CRPS_HK, CRPS_HK_HKPARAM_REP, 1, 0); /* arguments: type, subType, discriminant/evtId, length */
  dest = 1;
  CrFwOutCmpSetDest(rep, dest);

  return;
}

/** Action for node N3. */
void CrPsCmd3s1StartN3(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Generate error report OUTFACTORY_FAIL */

	DEBUGP_3("CrPsCmd3s1StartN3.\n");

  return;
}

/** Action for node N4. */
void CrPsCmd3s1StartN4(FwPrDesc_t prDesc)
{
  FwSmDesc_t outManager;

  CRFW_UNUSED(prDesc);
  /* Load the report in the OutLoader */

  DEBUGP_3("CrPsCmd3s1StartN4.\n");

  /* TODO: get outManager */
  outManager = CrFwOutManagerMake(0);
  numberOfPendingOutCmpOld = CrFwOutManagerGetNOfPendingOutCmp(outManager);

  CrFwOutLoaderLoad(rep);

  return;
}

/** Action for node N5. */
void CrPsCmd3s1StartN5(FwPrDesc_t prDesc)
{
  prDescCmd3s1Start_t* prDataPtr;
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t pckt;
  FwSmDesc_t smDesc;

  uint16_t sid;
  uint8_t isEnabled;
  uint32_t cycleCnt;
  uint16_t dest;
  uint16_t lstId; /* TODO: should be an array */

  /* Add report definition to the RDL and set initial enable status to 'not enabled' */

  DEBUGP_3("CrPsCmd3s1StartN5.\n");

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* TODO: Get inPckt from prData */
  cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  (void)pckt;

  /* add report definition to the RDL */
  sid = 1; /* TODO: use getter */
  cycleCnt = 2; /* TODO: use getter */
  dest = 0; /* TODO: use getter */
  lstId = 234; /* TODO: use getter */
  setDpsidItem(rdlSlot, sid); 
  setDpcycleCntItem(rdlSlot, cycleCnt);
  setDpdestItem(rdlSlot, dest);
  setDplstIdItem(rdlSlot, lstId);

  isEnabled = 0;
  setDpisEnabledItem(rdlSlot, isEnabled);

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
  prDescCmd3s1Start_t* prDataPtr;
  CrFwCmpData_t* cmpData;
  FwSmDesc_t smDesc;

	/* Set action outcome to 'failure' with code VER_SID_IN_USE and load SID in verFailData data pool item */

	DEBUGP_3("CrPsCmd3s1StartN7.\n");

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Set outcome in InCmd prData to 'failure' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = (unsigned char)VER_SID_IN_USE;
  FwSmSetData(smDesc, cmpData);

  /* TODO: Load SID in verFailData data pool item */

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

  /* TODO: Load identifier of constraint in verFailData */

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

  /* TODO: Load identifier of duplicated DI in verFailData */

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
	CRFW_UNUSED(prDesc);
	/* One or more constraints listed in table 9.1 are not satisfied */

  /* Get sid and check: Integer in range: 1..HK_MAX_SID */

  /* Get period and check: Positive integer */

  /* Get nSimple and check: Integer in range: 1..HK_MAX_N_SIMPLE */

  /* Get lstSampleRep and check: TBV */

  /* Get lstNSampRep and check: TBV */

  /* Get lstId and check: TBV */

  /* Get sampleBufId and check: Integer in range: 1..HK_N_SAMP_BUF */

	DEBUGP_3("CrPsCmd3s1StartG2.\n");
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
	CRFW_UNUSED(prDesc);
	/* The same data item identifier appears twice in the definition of the new report  */

	DEBUGP_3("CrPsCmd3s1StartG4.\n");
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

