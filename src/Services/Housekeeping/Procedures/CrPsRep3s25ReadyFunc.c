/**
 * @file CrPsRep3s25ReadyFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Oct 3 2017 22:4:57
 */

#include "CrFwConstants.h"
/** CrPsRep3s25Ready function definitions */
#include "CrPsRep3s25ReadyCreate.h"

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
#include <DataPool/CrPsDpHk.h>
#include <Services/General/CrPsConstants.h>
#include <CrPsDebug.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* ----------------------------------------------------------------------------------------------------------------- */

/** Action for node N1. */
void CrPsRep3s25ReadyN1(FwPrDesc_t prDesc)
{
  unsigned char sid, rdlSid, rdlSlot;
  prDataHkRepReadyCheck_t* prDataPtr;

  /* Set Cycle Counter to zero */
  DEBUGP_3("  Action for node N1.\n");

  /* Get SID from prData */
  prDataPtr = FwPrGetData(prDesc);
  sid = prDataPtr->sid;
  printf("CrPsRep3s25ReadyN1: SID = %d\n", sid);

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {

      rdlSid = getDpsidItem(rdlSlot);
      printf("SID in RDL[%d] = %d\n", rdlSlot, rdlSid);
      
      if (sid == rdlSid)
        break;
    }

  setDpcycleCntItem(rdlSlot, 0);

  return;
}

/** Action for node N2. */
void CrPsRep3s25ReadyN2(FwPrDesc_t prDesc)
{
  prDataHkRepReadyCheck_t* prDataPtr;
  CrFwCmpData_t* cmpData;
  FwSmDesc_t smDesc;

  /* Ready Check returns 'Ready' */
  DEBUGP_3("  Action for node N2.\n");

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = 1;
  FwSmSetData(smDesc, cmpData);

  return;
}

/** Action for node N3. */
void CrPsRep3s25ReadyN3(FwPrDesc_t prDesc)
{
  prDataHkRepReadyCheck_t* prDataPtr;
  CrFwCmpData_t* cmpData;
  FwSmDesc_t smDesc;

  /* Ready Check returns 'Not Ready' */
  DEBUGP_3("  Action for node N3.\n");

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = 0;
  FwSmSetData(smDesc, cmpData);

  return;
}

/** Action for node N4. */
void CrPsRep3s25ReadyN4(FwPrDesc_t prDesc)
{
  unsigned char sid, rdlSid, rdlSlot;
  unsigned int cycleCnt;
  prDataHkRepReadyCheck_t* prDataPtr;

  /* Increment Cycle Counter */
  DEBUGP_3("  Action for node N4.\n");

  /* Get SID from prData */
  prDataPtr = FwPrGetData(prDesc);
  sid = prDataPtr->sid;
  printf("CrPsRep3s25ReadyN4: SID = %d\n", sid);

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {

      rdlSid = getDpsidItem(rdlSlot);
      printf("SID in RDL[%d] = %d\n", rdlSlot, rdlSid);
      
      if (sid == rdlSid)
        break;
    }

  cycleCnt = getDpcycleCntItem(rdlSlot);
  cycleCnt++;
  printf("CrPsRep3s25ReadyN4: cycleCnt = %d\n", cycleCnt);
  setDpcycleCntItem(rdlSlot, cycleCnt);

  return;
}

/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION1 to N3. */
FwPrBool_t CrPsRep3s25ReadyG1(FwPrDesc_t prDesc)
{
  unsigned char sid, rdlSid, rdlSlot;
  unsigned int cycleCnt;
  CrFwBool_t rdlEnabled;
  prDataHkRepReadyCheck_t* prDataPtr;

  /*  Flag_1 */
  /* [ (Cycle Counter != 0) || (SID is not enabled in RDL) ] */
  DEBUGP_3("  Guard on the Control Flow from DECISION1 to N3.\n");

  /* Get SID from prData */
  prDataPtr = FwPrGetData(prDesc);
  sid = prDataPtr->sid;
  printf("CrPsRep3s25ReadyG1: SID = %d\n", sid);

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {

      rdlSid = getDpsidItem(rdlSlot);
      printf("SID in RDL[%d] = %d\n", rdlSlot, rdlSid);
      
      if (sid == rdlSid)
        break;
    }

  /* Get Cycle Counter from RDL */
  cycleCnt = getDpcycleCntItem(rdlSlot);
  printf("CrPsRep3s25ReadyG1: cycleCnt = %d\n", cycleCnt);

  /* Get isEnabled from RDL */
  rdlEnabled = getDpisEnabledItem(rdlSlot);
  printf("CrPsRep3s25ReadyG1: isEnabled = %d\n", rdlEnabled);

  if ((cycleCnt != 0) || (rdlEnabled == 0))
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/** Guard on the Control Flow from N4 to DECISION2. */
FwPrBool_t CrPsRep3s25ReadyG2(FwPrDesc_t prDesc)
{
  /* Next Execution */
  DEBUGP_3("  Guard on the Control Flow from N4 to DECISION2.\n");

  printf("CrPsRep3s25ReadyG2: FwPrGetNodeExecCnt(prDesc) = %d\n", FwPrGetNodeExecCnt(prDesc));

  if (FwPrGetNodeExecCnt(prDesc))
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/** Guard on the Control Flow from DECISION2 to N1. */
FwPrBool_t CrIaReadyChk3s25ReadyGoToRst(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* CrIaReadyChk3s25ReadyGoToRst */
	DEBUGP_3("  Guard on the Control Flow from DECISION2 to N1.\n");
	return 1;
}

/** Guard on the Control Flow from DECISION2 to Final Node. */
FwPrBool_t CrPsRep3s25ReadyGoToFin(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* SID is not defined */
	DEBUGP_3("  Guard on the Control Flow from DECISION2 to Final Node.\n");
	return 0;
}

/** Guard on the Control Flow from DECISION2 to DECISION1. */
FwPrBool_t CrIaReadyChk3s25ReadyGoToDec(FwPrDesc_t prDesc)
{
  unsigned char sid, rdlSid, rdlSlot;
  unsigned int cycleCnt;
  unsigned short period = 8; /* cycles; all 4 seconds (4sec * 2cycles/sec) */
  prDataHkRepReadyCheck_t* prDataPtr;

  /* (Cycle Counter != Period) && (SID is Defined) */
  DEBUGP_3("  Guard on the Control Flow from DECISION2 to DECISION1.\n");

  /* Get SID from prData */
  prDataPtr = FwPrGetData(prDesc);
  sid = prDataPtr->sid;
  printf("CrIaReadyChk3s25ReadyGoToDec: SID = %d\n", sid);

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {

      rdlSid = getDpsidItem(rdlSlot);
      printf("SID in RDL[%d] = %d\n", rdlSlot, rdlSid);
      
      if (sid == rdlSid)
        break;
    }

  /* Get Cycle Counter from RDL */
  cycleCnt = getDpcycleCntItem(rdlSlot);
  printf("CrIaReadyChk3s25ReadyGoToDec: cycleCnt = %d\n", cycleCnt);

  /* Get Period from RDL */
  /* TODO: need setDpperiodItem() and getDpperiodItem() */

  if ((cycleCnt != period) && (sid != 0))
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/* ----------------------------------------------------------------------------------------------------------------- */

