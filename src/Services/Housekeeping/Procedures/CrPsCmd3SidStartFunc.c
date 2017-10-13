/**
 * @file CrPsCmd3SidStartFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:17:19
 */

/** CrPsCmd3SidStart function definitions */
#include "CrPsCmd3SidStartCreate.h"

/** CR Framework function definitions*/
#include "CrFwConstants.h"

/* CrFramework includes */
#include "OutCmp/CrFwOutCmp.h"
#include "CrFwCmpData.h"
#include "Pckt/CrFwPckt.h"

/** FW Profile function definitions */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"

#include <CrPsUserConstants.h>
#include <CrPsUtilities.h>
#include <CrPsDebug.h>
#include <DataPool/CrPsDpHk.h>
#include <Services/General/CrPsConstants.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VER_ILL_SID 101

unsigned int i, iSidFail;


/* ----------------------------------------------------------------------------------------------------------------- */

/** Action for node N1. */
void CrPsCmd3SidStartN1(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  /*Set i equal to 1 */

  DEBUGP_3("CrPsCmd3SidStartN1.\n");

  i = 0;
  iSidFail = 0;
  printf("CrPsCmd3SidStartN1: i = %d\n", i);

  return;
}

/** Action for node N2. */
void CrPsCmd3SidStartN2(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  /*Load invalid SID in data pool item verFailData */

  DEBUGP_3("CrPsCmd3SidStartN2.\n");

  iSidFail++;

  return;
}

/** Action for node N3. */
void CrPsCmd3SidStartN3(FwPrDesc_t prDesc)
{
  FwSmDesc_t smDesc;	
  unsigned short tcFailureCode;

  CRFW_UNUSED(prDesc);
  /* Run Command Verification Failure Procedure to generate (1,4) report with failure code VER_ILL_SID */

  DEBUGP_3("CrPsCmd3SidStartN3.\n");

  /* TODO: Get smDesc from prData */
  smDesc = 0;

  tcFailureCode = VER_ILL_SID;
  SendReqVerifAccFailRep(smDesc, tcFailureCode);

  return;
}

/** Action for node N4. */
void CrPsCmd3SidStartN4(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  /*Increment i */

  DEBUGP_3("CrPsCmd3SidStartN4.\n");

  i++;
  printf("CrPsCmd3SidStartN4: i = %d\n", i);

  return;
}

/** Action for node N7. */
void CrPsCmd3SidStartN7(FwPrDesc_t prDesc)
{
  prDescMultiSidCmdStart_t* prDataPtr;
  CrFwCmpData_t* cmpData;
  FwSmDesc_t smDesc;

  /*Set action outcome to 'success' */

  DEBUGP_3("CrPsCmd3SidStartN7.\n");

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Set outcome in InCmd prData to 'success' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = 1;
  FwSmSetData(smDesc, cmpData);

  /* ONLY FOR TEST PURPOSES */
{
  unsigned char* sid;
  int k;

  sid = prDataPtr->sidPtr;

  for (k=0; k<10; k++)
    {
      if (sid[k] == 0)
      	break;

      printf("SID[%d] = %d\n", k, sid[k]);
    }
}

  return;
}

/** Action for node N8. */
void CrPsCmd3SidStartN8(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  /*Set action outcome to 'failure' with failure code VER_SID_START_FD */

  DEBUGP_3("CrPsCmd3SidStartN8.\n");

  /* Set outcome in InCmd prData to 'failure' */ 

  return;	
}

/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION1 to N2. */
FwPrBool_t CrPsCmd3SidStartG1(FwPrDesc_t prDesc)
{
  unsigned char sid, rdlSid, rdlSlot;

  CRFW_UNUSED(prDesc);
  /*The i-th SID is not in the RDL */

  DEBUGP_3("CrPsCmd3SidStartG1.\n");

  /* Get i-th SID */
  sid = 1;

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {

      rdlSid = getDpsidItem(rdlSlot);
      printf("SID in RDL[%d] = %d\n", rdlSlot, rdlSid);
      
      if (sid == rdlSid)
        break;
    }

  /* sid not found in list */
  if (rdlSlot == HK_N_REP_DEF)
    {
      printf("SID %d not found!\n", sid);
      return 1;
    }
  else
    {
      return 0;
    }
}

/** Guard on the Control Flow from DECISION3 to DECISION4. */
FwPrBool_t CrPsCmd3SidStartG2(FwPrDesc_t prDesc)
{
  unsigned int iMax;

  CRFW_UNUSED(prDesc);
  /*The i-th SID was the last SID in the command*/

  DEBUGP_3("CrPsCmd3SidStartG2.\n");

  /* TODO: Get iMax from prData */
  iMax = 2;

  if (i == iMax)
    {
      return 1;
    }
  else
  	{
	  return 0;  		
  	}
}

/** Guard on the Control Flow from DECISION4 to N8. */
FwPrBool_t CrPsCmd3SidStartG3(FwPrDesc_t prDesc)
{
  unsigned int iMax;

  CRFW_UNUSED(prDesc);
  /*All SIDs in the command are invalid */
	
  DEBUGP_3("CrPsCmd3SidStartG3.\n");

  /* TODO: Get iMax from prData */
  iMax = 2;

  if (iSidFail == iMax)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/* ----------------------------------------------------------------------------------------------------------------- */

