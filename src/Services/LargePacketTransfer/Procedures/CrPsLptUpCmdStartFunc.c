/**
 * @file CrPsLptUpCmdStartFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Nov 26 2017 12:7:49
 */

/** CrPsLptUpCmdStart function definitions */
#include "CrPsLptUpCmdStartCreate.h"

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

#include <CrPsUtilitiesServLpt.h>
#include <DataPool/CrPsDpServLpt.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServLpt.h> 
#include <Services/LargePacketTransfer/StateMachines/CrPsLptCreate.h>

#include <stdlib.h>
#include <time.h>

CrPsTid_t Tid;


/* ----------------------------------------------------------------------------------------------------------------- */

/** Action for node N1. */
void CrPsLptUpCmdStartN1(FwPrDesc_t prDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  prDescCmd13Start_t *prDataPtr;
  FwSmDesc_t          smDesc;

  /* Determine the identifier of the LPT Buffer */

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Get inPckt */
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  Tid = getLptUpInterCmdTid(pckt);

  return;
}

/** Action for node N2. */
void CrPsLptUpCmdStartN2(FwPrDesc_t prDesc)
{
  prDescCmd13Start_t *prDataPtr;
  CrFwCmpData_t      *cmpData;
  FwSmDesc_t          smDesc;

  /* Set action outcome to 'Failure' */

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Set outcome in InCmd prData to 'failure' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = 0;
  FwSmSetData(smDesc, cmpData);

  return;
}

/** Action for node N3. */
void CrPsLptUpCmdStartN3(FwPrDesc_t prDesc)
{
  unsigned int LptBufferId;

  CRFW_UNUSED(prDesc);

  /* Set lptFailCode to PART_NMB_ERR */

  LptBufferId = Tid % LPT_N_BUF;
  setDplptFailCodeItem(LptBufferId, PART_NMB_ERR);

  return;
}

/** Action for node N4. */
void CrPsLptUpCmdStartN4(FwPrDesc_t prDesc)
{
  prDescCmd13Start_t *prDataPtr;
  CrFwCmpData_t      *cmpData;
  FwSmDesc_t          smDesc;

  /* Set action outcome to 'Success' */

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Set outcome in InCmd prData to 'success' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = 1;
  FwSmSetData(smDesc, cmpData);

  return;
}

/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION1 to N2. */
FwPrBool_t CrPsLptUpCmdStartG1(FwPrDesc_t prDesc)
{
  unsigned short sm_state;

  CRFW_UNUSED(prDesc);

  /* LPT State Machine associated to LPT Buffer is not in state UP_TRANSFER */

  sm_state = FwSmGetCurState(getSmDescLpt());
  if (sm_state != CrPsLpt_UP_TRANSFER)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/** Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsLptUpCmdStartNG2(FwPrDesc_t prDesc)
{
  CrFwCmpData_t        *cmpData;
  CrFwInCmdData_t      *cmpSpecificData;
  CrFwPckt_t            pckt;
  CrPsNumberU4_t PartSeqNmbOld, PartSeqNmb;
  unsigned int LptBufferId;
  prDescCmd13Start_t *prDataPtr;
  FwSmDesc_t          smDesc;  

  CRFW_UNUSED(prDesc);

  /* Flag_1 */
  /* ... is true if the part sequence number of the current up-transfer command 
     is out of sequence with the part sequence number of the previous up-transfer
     command for this LPT Buffer */

  LptBufferId = Tid % LPT_N_BUF;

  /* Get smDesc from OutCmp */
  prDataPtr = FwPrGetData(prDesc);
  smDesc = prDataPtr->smDesc;

  /* Get inPckt */
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get PartSeqNum to determine memory address */
  PartSeqNmb = getLptUpFirstCmdPartSeqNmb(pckt);

  PartSeqNmbOld = getDppartSeqNmbItem(LptBufferId);

  if (PartSeqNmb != PartSeqNmbOld + 1)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/* ----------------------------------------------------------------------------------------------------------------- */

