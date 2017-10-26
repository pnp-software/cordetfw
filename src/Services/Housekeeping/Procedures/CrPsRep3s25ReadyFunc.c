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
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwSmConfig.h"

#include <CrPsUserConstants.h>
#include <CrPsUtilitiesServHk.h>
#include <DataPool/CrPsDpServHk.h>
#include <Services/General/CrPsConstants.h>
#include "CrPsDebug.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* ----------------------------------------------------------------------------------------------------------------- */

/** Action for node N1. */
void CrPsRep3s25ReadyN1(FwPrDesc_t prDesc)
{
  CrPsSid_t                sid, rdlSid, rdlSlot;
  prDataHkRepReadyCheck_t *prDataPtr;

  /* Set Cycle Counter to zero */

  /* Get SID from prData */
  prDataPtr = FwPrGetData(prDesc);
  sid = prDataPtr->sid;

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {
      rdlSid = getDpsidItem(rdlSlot);
      
      if (sid == rdlSid)
        break;
    }

  setDpcycleCntItem(rdlSlot, 0);

  return;
}

/** Action for node N2. */
void CrPsRep3s25ReadyN2(FwPrDesc_t prDesc)
{
  prDataHkRepReadyCheck_t *prDataPtr;
  CrFwCmpData_t           *cmpData;
  FwSmDesc_t               smDesc;

  /* Ready Check returns 'Ready' */

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
  prDataHkRepReadyCheck_t *prDataPtr;
  CrFwCmpData_t           *cmpData;
  FwSmDesc_t               smDesc;

  /* Ready Check returns 'Not Ready' */

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
  CrPsSid_t                sid, rdlSid, rdlSlot;
  CrFwCounterU4_t          cycleCnt;
  prDataHkRepReadyCheck_t *prDataPtr;

  /* Increment Cycle Counter */

  /* Get SID from prData */
  prDataPtr = FwPrGetData(prDesc);
  sid = prDataPtr->sid;

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {
      rdlSid = getDpsidItem(rdlSlot);
      
      if (sid == rdlSid)
        break;
    }

  cycleCnt = getDpcycleCntItem(rdlSlot);
  cycleCnt++;
  setDpcycleCntItem(rdlSlot, cycleCnt);

  return;
}

/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION1 to N3. */
FwPrBool_t CrPsRep3s25ReadyG1(FwPrDesc_t prDesc)
{
  CrPsSid_t                sid, rdlSid, rdlSlot;
  CrFwCounterU4_t          cycleCnt;
  CrFwBool_t               rdlEnabled;
  prDataHkRepReadyCheck_t *prDataPtr;

  /*  Flag_1 */
  /* [ (Cycle Counter != 0) || (SID is not enabled in RDL) ] */

  /* Get SID from prData */
  prDataPtr = FwPrGetData(prDesc);
  sid = prDataPtr->sid;

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {
      rdlSid = getDpsidItem(rdlSlot);
      
      if (sid == rdlSid)
        break;
    }

  /* Get Cycle Counter from RDL */
  cycleCnt = getDpcycleCntItem(rdlSlot);

  /* Get isEnabled from RDL */
  rdlEnabled = getDpisEnabledItem(rdlSlot);

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
  CrPsSid_t                sid, rdlSid, rdlSlot;
  CrFwCounterU4_t          cycleCnt;
  CrPsCollectInterval_t    period;
  prDataHkRepReadyCheck_t *prDataPtr;

  /* (Cycle Counter == Period) && (SID is Defined) */

  /* Get SID from prData */
  prDataPtr = FwPrGetData(prDesc);
  sid = prDataPtr->sid;

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {
      rdlSid = getDpsidItem(rdlSlot);
      
      if (sid == rdlSid)
        break;
    }

  /* Get Cycle Counter from RDL */
  cycleCnt = getDpcycleCntItem(rdlSlot);

  /* Get Period from RDL */
  period = getDpperiodItem(rdlSlot);

  if ((cycleCnt == period) && (rdlSlot < HK_N_REP_DEF))
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/** Guard on the Control Flow from DECISION2 to Final Node. */
FwPrBool_t CrPsRep3s25ReadyGoToFin(FwPrDesc_t prDesc)
{
  CrPsSid_t                sid, rdlSid, rdlSlot;
  prDataHkRepReadyCheck_t *prDataPtr;

  /* (SID is not Defined) */

  /* Get SID from prData */
  prDataPtr = FwPrGetData(prDesc);
  sid = prDataPtr->sid;

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {
      rdlSid = getDpsidItem(rdlSlot);
      
      if (sid == rdlSid)
        break;
    }

  if (rdlSlot == HK_N_REP_DEF)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/** Guard on the Control Flow from DECISION2 to DECISION1. */
FwPrBool_t CrIaReadyChk3s25ReadyGoToDec(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* [ Else ] */

  return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */

