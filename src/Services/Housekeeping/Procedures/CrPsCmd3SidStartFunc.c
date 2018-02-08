/**
 * @file CrPsCmd3SidStartFunc.c
 * @ingroup Serv3
 * @ingroup procedures
 *
 * @brief Start Action for service 3 commands which carry a list of SIDs
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:17:19
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

/** CrPsCmd3SidStart function definitions */
#include "CrPsCmd3SidStartCreate.h"

/** CR Framework function definitions*/
#include "CrFwConstants.h"
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

#include <DataPool/CrPsDpServReqVerif.h>
#include <DataPool/CrPsDpServHk.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServHk.h>
#include <Services/General/CrPsPktServHkSupp.h>
#include <CrPsUtilitiesServHk.h>
#include <CrPsUtilitiesServReqVerif.h>
#include <CrPsUserConstants.h>

#include <stdlib.h>
#include <time.h>

CrFwCounterU4_t i, iSidFail, iMax;
CrPsSid_t       currentSid;


/* ----------------------------------------------------------------------------------------------------------------- */

/** Action for node N1. */
void CrPsCmd3SidStartN1(FwPrDesc_t prDesc)
{
  CrFwCmpData_t            *cmpData;
  CrFwInCmdData_t          *cmpSpecificData;
  CrFwPckt_t                pckt;
  FwSmDesc_t                smDesc;  
  prDescMultiSidCmdStart_t *prDataPtr;
  CrFwServSubType_t         servSubType;

  /*Set i equal to 1 */
  i = 0;
  iSidFail = 0;

  /* Get smDesc from prData */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Get in data */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  servSubType = CrFwPcktGetServSubType(pckt);

  switch(servSubType)
  {
    case CRPS_HK_ENABLE_PERIODICHK_CMD:
      currentSid = getHkEnableCmdRepStrucIdItem(pckt, i+1); 
      iMax = getHkEnableCmdN(pckt); 
      break;
    case CRPS_HK_ENABLE_PERIODICDIAG_CMD:
      currentSid = getHkEnableCmdRepStrucIdItem(pckt, i+1); 
      iMax = getHkEnableCmdN(pckt); 
      break;

    case CRPS_HK_DISABLE_PERIODICHK_CMD:
      currentSid = getHkDisableCmdRepStrucIdItem(pckt, i+1); 
      iMax = getHkDisableCmdN(pckt); 
      break;
    case CRPS_HK_DISABLE_PERIODICDIAG_CMD:
      currentSid = getHkDisableCmdRepStrucIdItem(pckt, i+1); 
      iMax = getHkDisableCmdN(pckt);     
      break;

    case CRPS_HK_HKREP_STRUCT_CMD:
      currentSid = getHkRepStructCmdRepStrucIdItem(pckt, i+1); 
      iMax = getHkRepStructCmdN(pckt); 
      break;
    case CRPS_HK_DIAGREP_STRUCT_CMD:
      currentSid = getHkRepStructCmdRepStrucIdItem(pckt, i+1); 
      iMax = getHkRepStructCmdN(pckt); 
      break;

    case CRPS_HK_HKONESHOT_CMD:
      currentSid = getHkOneShotCmdRepStrucIdItem(pckt, i+1); 
      iMax = getHkOneShotCmdN(pckt); 
      break;
    case CRPS_HK_DIAGONESHOT_CMD:
      currentSid = getHkOneShotCmdRepStrucIdItem(pckt, i+1); 
      iMax = getHkOneShotCmdN(pckt); 
      break;

    default:
      currentSid = 0;
      iMax = 1;
      break;
  }

  return;
}

/** Action for node N2. */
void CrPsCmd3SidStartN2(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  /*Load invalid SID in data pool item verFailData */

  iSidFail++;
  setDpverFailData((CrPsFailData_t)currentSid);

  return;
}

/** Action for node N3. */
void CrPsCmd3SidStartN3(FwPrDesc_t prDesc)
{
  FwSmDesc_t                smDesc;	
  prDescMultiSidCmdStart_t *prDataPtr;

  /* Run Command Verification Failure Procedure to generate (1,4) report with failure code VER_ILL_SID */
  /* Get smDesc from prData */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  SendReqVerifCmdFailRep(smDesc, CRPS_REQVERIF_START_FAIL, VER_ILL_SID);  

  return;
}

/** Action for node N4. */
void CrPsCmd3SidStartN4(FwPrDesc_t prDesc)
{
  CrFwCmpData_t            *cmpData;
  CrFwInCmdData_t          *cmpSpecificData;
  CrFwPckt_t                pckt;
  FwSmDesc_t                smDesc;  
  prDescMultiSidCmdStart_t *prDataPtr;
  CrFwServSubType_t         servSubType;

  /*Increment i */
  i++;

  /* Get smDesc from prData */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Get in data */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  servSubType = CrFwPcktGetServSubType(pckt);

  switch(servSubType)
  {
    case CRPS_HK_ENABLE_PERIODICHK_CMD:
      currentSid = getHkEnableCmdRepStrucIdItem(pckt, i+1); 
      break;
    case CRPS_HK_ENABLE_PERIODICDIAG_CMD:
      currentSid = getHkEnableCmdRepStrucIdItem(pckt, i+1); 
      break;

    case CRPS_HK_DISABLE_PERIODICHK_CMD:
      currentSid = getHkDisableCmdRepStrucIdItem(pckt, i+1); 
      break;
    case CRPS_HK_DISABLE_PERIODICDIAG_CMD:
      currentSid = getHkDisableCmdRepStrucIdItem(pckt, i+1); 
      break;

    case CRPS_HK_HKREP_STRUCT_CMD:
      currentSid = getHkRepStructCmdRepStrucIdItem(pckt, i+1); 
      break;
    case CRPS_HK_DIAGREP_STRUCT_CMD:
      currentSid = getHkRepStructCmdRepStrucIdItem(pckt, i+1); 
      break;

    case CRPS_HK_HKONESHOT_CMD:
      currentSid = getHkOneShotCmdRepStrucIdItem(pckt, i+1); 
      break;
    case CRPS_HK_DIAGONESHOT_CMD:
      currentSid = getHkOneShotCmdRepStrucIdItem(pckt, i+1); 
      break;

    default: /*TODO (01.02.2018) can not be reached because(N1 maxsid is set to 1 !)*/
      currentSid = 0;
      break;
  }

  return;
}

/** Action for node N7. */
void CrPsCmd3SidStartN7(FwPrDesc_t prDesc)
{
  prDescMultiSidCmdStart_t *prDataPtr;
  CrFwCmpData_t            *cmpData;
  FwSmDesc_t                smDesc;

  /*Set action outcome to 'success' */
  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Set outcome in InCmd prData to 'success' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = 1;
  FwSmSetData(smDesc, cmpData);

  return;
}

/** Action for node N8. */
void CrPsCmd3SidStartN8(FwPrDesc_t prDesc)
{
  prDescMultiSidCmdStart_t *prDataPtr;
  CrFwCmpData_t            *cmpData;
  FwSmDesc_t                smDesc;
  
  /*Set action outcome to 'failure' with failure code VER_SID_START_FD */
  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Set outcome in InCmd prData to 'failure' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = VER_SID_START_FD;
  FwSmSetData(smDesc, cmpData);

  return;	
}

/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION1 to N2. */
FwPrBool_t CrPsCmd3SidStartG1(FwPrDesc_t prDesc)
{
  CrPsSid_t rdlSid, rdlSlot;

  CRFW_UNUSED(prDesc);
  /*The i-th SID is not in the RDL */

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {
      rdlSid = getDpsidItem(rdlSlot);
      
      if (currentSid == rdlSid)
        break;
    }

  /* sid not found in list */
  if (rdlSlot == HK_N_REP_DEF)
    {
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
  CRFW_UNUSED(prDesc);

  /*The i-th SID was the last SID in the command*/
  if (i == iMax-1)
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
  CRFW_UNUSED(prDesc);

  /*All SIDs in the command are invalid */
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

