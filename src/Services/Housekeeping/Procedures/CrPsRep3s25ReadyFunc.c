/**
 * @file CrPsRep3s25ReadyFunc.c
 * @ingroup Serv3
 * @ingroup procedures
 *
 * @brief Implements the ReadyCheck for Housekeeping/Diagnostic reports (3,25) and (3,26)
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jan 3 2018 14:31:12
 *
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * 
 * last modification: 22.01.2018
 * 
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
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

#include <stdlib.h>
#include <time.h>


/* ----------------------------------------------------------------------------------------------------------------- */

/** Action for node N1. */
void CrPsRep3s25ReadyN1(FwPrDesc_t prDesc)
{
  prDataHkRepReadyCheck_t *prDataPtr;

  /* Set Cycle Counter to zero */

  /* Get prData */
  prDataPtr = FwPrGetData(prDesc);

  setDpcycleCntItem(prDataPtr->rdlSlot, 0);

  return;
}

/** Action for node N2. */
void CrPsRep3s25ReadyN2(FwPrDesc_t prDesc)
{
  prDataHkRepReadyCheck_t *prDataPtr;
  CrFwCmpData_t           *cmpData;

  /* Ready Check returns 'Ready' */
  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);

  cmpData = (CrFwCmpData_t*) FwSmGetData(prDataPtr->smDesc);
  cmpData->outcome = 1;
  FwSmSetData(prDataPtr->smDesc, cmpData);

  return;
}

/** Action for node N3. */
void CrPsRep3s25ReadyN3(FwPrDesc_t prDesc)
{
  prDataHkRepReadyCheck_t *prDataPtr;
  CrFwCmpData_t           *cmpData;
  
  /* Ready Check returns 'Not Ready' */
  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);

  cmpData = (CrFwCmpData_t*) FwSmGetData(prDataPtr->smDesc);
  cmpData->outcome = 0;
  FwSmSetData(prDataPtr->smDesc, cmpData);

  return;
}

/** Action for node N4. */
void CrPsRep3s25ReadyN4(FwPrDesc_t prDesc)
{
  CrFwCounterU4_t          cycleCnt;
  prDataHkRepReadyCheck_t *prDataPtr;

  /* Increment Cycle Counter */

  /* Get prData */
  prDataPtr = FwPrGetData(prDesc);

  cycleCnt = getDpcycleCntItem(prDataPtr->rdlSlot);
  cycleCnt++;
  setDpcycleCntItem(prDataPtr->rdlSlot, cycleCnt);

  return;
}

/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION1 to N3. */
FwPrBool_t CrPsRep3s25ReadyG1(FwPrDesc_t prDesc)
{
  CrFwCounterU4_t          cycleCnt;
  CrFwBool_t               rdlEnabled;
  prDataHkRepReadyCheck_t *prDataPtr;

  /*  Flag_1 */
  /* [ (Cycle Counter != 0) || (SID is not enabled in RDL) ] */

  /* Get prData */
  prDataPtr = FwPrGetData(prDesc);

  /* Get Cycle Counter from RDL */
  cycleCnt = getDpcycleCntItem(prDataPtr->rdlSlot);

  /* Get isEnabled from RDL */
  rdlEnabled = getDpisEnabledItem(prDataPtr->rdlSlot);



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
  CrFwCounterU4_t          cycleCnt;
  CrPsCollectInterval_t    period;
  prDataHkRepReadyCheck_t *prDataPtr;

  /* (Cycle Counter == Period) && (SID is Defined) */

  /* Get prData */
  prDataPtr = FwPrGetData(prDesc);

  /* Get Cycle Counter from RDL */
  cycleCnt = getDpcycleCntItem(prDataPtr->rdlSlot);

  /* Get Period from RDL */
  period = getDpperiodItem(prDataPtr->rdlSlot);

  if ((cycleCnt == period) && (prDataPtr->rdlSlot < HK_N_REP_DEF))
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
  prDataHkRepReadyCheck_t *prDataPtr;

  /* (SID is not Defined) */

  /* Get prData */
  prDataPtr = FwPrGetData(prDesc);

  if (prDataPtr->rdlSlot == HK_N_REP_DEF)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/* ----------------------------------------------------------------------------------------------------------------- */

