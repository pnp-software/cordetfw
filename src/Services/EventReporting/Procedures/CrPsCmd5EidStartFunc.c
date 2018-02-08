/**
 * @file CrPsCmd5EidStartFunc.c
 * @ingroup Serv5
 * @ingroup procedures
 *
 * @brief Create one instance of the CrPsCmd5EidStart procedure
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:17:44
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

/** CrPsCmd5EidStart function definitions */
#include "CrPsCmd5EidStartCreate.h"

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
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServEvt.h>
#include <Services/General/CrPsPktServEvtSupp.h>
#include <CrPsUtilitiesServReqVerif.h>
#include <CrPsUserConstants.h>

#include <stdlib.h>
#include <time.h>

CrFwCounterU4_t i, iEidFail;
CrPsNumberU4_t  iMax;
CrPsEid_t       currentEid;
CrFwCounterU2_t currentEvtSlot;


/* ----------------------------------------------------------------------------------------------------------------- */

/** Action for node N1. */
void CrPsCmd5EidStartN1(FwPrDesc_t prDesc)
{
  CrFwCmpData_t       *cmpData;
  CrFwInCmdData_t     *cmpSpecificData;
  CrFwPckt_t           pckt;
  FwSmDesc_t           smDesc;  
  prDescCmdEidStart_t *prDataPtr;
  CrFwServSubType_t    servSubType;
  CrFwCounterU2_t      evtSlot;
  CrPsEid_t            evtEid;
  CrPsEid_t            evtEidArray[EVT_N_EID] = EVT_EID;
  CrPsFlag_t*          evtFlagPtr;
  uint32_t             j;

  /* Set i equal to 1 */

  i = 1;
  iEidFail = 0;

  /* Get prData */
  prDataPtr = FwPrGetData(prDesc);
 
  /* Initialize flag array */
  evtFlagPtr = (CrPsFlag_t*)prDataPtr->evtFlagPtr;
  for (j=0; j<EVT_N_EID; j++)
    {
       *(evtFlagPtr + j) = 0;
    }

  /* Get smDesc from prData */
  smDesc = prDataPtr->smDesc;

  /* Get in data */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  servSubType = CrFwPcktGetServSubType(pckt);

  /* Get first EID and iMax */
  switch(servSubType)
  {
    case CRPS_EVT_ENABLE_CMD:
      currentEid = getEvtEnableCmdEventIdItem(pckt, i);
      iMax = getEvtEnableCmdN(pckt); 
      break;
      
    case CRPS_EVT_DISABLE_CMD:
      currentEid = getEvtDisableCmdEventIdItem(pckt, i);
      iMax = getEvtDisableCmdN(pckt); 
      break;

    default:
      currentEid = 0;
      iMax = 1;
      break;
  }

  /* look for the slot */
  for (evtSlot = 0; evtSlot < EVT_N_EID; evtSlot++)
    {
      evtEid = evtEidArray[evtSlot];
      
      if (currentEid == evtEid)
        break;
    }

currentEvtSlot = evtSlot;

  if (evtSlot < EVT_N_EID)
    {
      /* Set selected first EID in flag array */
      *(evtFlagPtr + currentEvtSlot) = 1;
    }

  return;
}

/** Action for node N2. */
void CrPsCmd5EidStartN2(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* Load invalid EID in
     data pool item verFailData */

  iEidFail++;
  setDpverFailData((CrPsFailData_t)currentEid);

  return;
}

/** Action for node N3. */
void CrPsCmd5EidStartN3(FwPrDesc_t prDesc)
{
  prDescCmdEidStart_t *prDataPtr;
  FwSmDesc_t           smDesc;

  /* Run Command Verification
     Failure Procedure to generate (1,4) 
     report with failure code VER_ILL_EID */

  /* Get smDesc from prData */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  SendReqVerifCmdFailRep(smDesc, CRPS_REQVERIF_START_FAIL, VER_ILL_EID);  

  return;
}

/** Action for node N4. */
void CrPsCmd5EidStartN4(FwPrDesc_t prDesc)
{
  CrFwCmpData_t       *cmpData;
  CrFwInCmdData_t     *cmpSpecificData;
  CrFwPckt_t           pckt;
  FwSmDesc_t           smDesc;  
  prDescCmdEidStart_t *prDataPtr;
  CrFwServSubType_t    servSubType;
  CrFwCounterU2_t      evtSlot;
  CrPsEid_t            evtEid;
  CrPsEid_t            evtEidArray[EVT_N_EID] = EVT_EID;
  CrPsFlag_t*          evtFlagPtr;

  /* Increment i */

  i++;

  /* Get smDesc from prData */
  prDataPtr = FwPrGetData(prDesc);
  evtFlagPtr = prDataPtr->evtFlagPtr;
  smDesc = prDataPtr->smDesc;

  /* Get in data */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  servSubType = CrFwPcktGetServSubType(pckt);

  /* Get next EID */
  switch(servSubType)
  {
    case CRPS_EVT_ENABLE_CMD:
      currentEid = getEvtEnableCmdEventIdItem(pckt, i);
      iMax = getEvtEnableCmdN(pckt); 
      break;
      
    case CRPS_EVT_DISABLE_CMD:
      currentEid = getEvtDisableCmdEventIdItem(pckt, i);
      iMax = getEvtDisableCmdN(pckt); 
      break;

    default:  /*TODO (01.02.2018)can never be reached, because of N1 */
      currentEid = 0;
      iMax = 1;
      break;
  }

  /* look for the slot */
  for (evtSlot = 0; evtSlot < EVT_N_EID; evtSlot++)
    {
      evtEid = evtEidArray[evtSlot];
      
      if (currentEid == evtEid)
        break;
    }

      currentEvtSlot = evtSlot;

  if (evtSlot < EVT_N_EID)
    {
      /* Set selected first EID in flag array */
      *(evtFlagPtr + currentEvtSlot) = 1;
    }

  return;
}

/** Action for node N7. */
void CrPsCmd5EidStartN7(FwPrDesc_t prDesc)
{
  prDescCmdEidStart_t *prDataPtr;
  CrFwCmpData_t       *cmpData;
  FwSmDesc_t           smDesc;

  /* Set action outcome to 'success' */

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
void CrPsCmd5EidStartN8(FwPrDesc_t prDesc)
{
  prDescCmdEidStart_t *prDataPtr;
  CrFwCmpData_t       *cmpData;
  FwSmDesc_t           smDesc;

  /* Set action outcome to 'failure'
     with failure code VER_EID_START_FD */

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Set outcome in InCmd prData to 'failure' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = VER_EID_START_FD;
  FwSmSetData(smDesc, cmpData);

  return;
}

/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION1 to N2. */
FwPrBool_t CrPsCmd5EidStartG1(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* The i-th EID is not in EVT_EID */

  /* EID not found in list */

  /*TODO ist nie erfüllt !!!*/
  if (currentEvtSlot == EVT_N_EID)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/** Guard on the Control Flow from DECISION3 to DECISION4. */
FwPrBool_t CrPsCmd5EidStartG2(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* The i-th EID was the last EID in the command */

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
FwPrBool_t CrPsCmd5EidStartG3(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* All EIDs in the command are invalid */

  if (iEidFail == iMax)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/* ----------------------------------------------------------------------------------------------------------------- */

