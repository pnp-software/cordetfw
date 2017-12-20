/**
 * \file
 *
 * Implementation of TC(13,129) LptStartDownCmd.
 *
 * \note This file was generated on 2017-11-22 12:47:43
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsLptStartDownCmd.h"

#include <CrFwCmpData.h>
#include <FwSmConfig.h>

#include <CrPsUtilitiesServLpt.h>
#include <CrPsUserConstants.h>
#include <Services/General/CrPsPktServLpt.h>
#include <Services/LargePacketTransfer/StateMachines/CrPsLptCreate.h>

unsigned int DownTransferLptBufferId;


/**
 * Start action of TC(13,129) LptStartDownCmd.
 * Determine the identifier of the LPT Buffer for the down-transfer by
 * computing: (x MOD LPT_N_BUF) where `x' is the Large Message Transaction
 * Identifier. Set action outcome to 'success' if the LPT State Machine is in
 * state INACTIVE; otherwise set the action outcome to `failure'
 * \param smDesc The state machine descriptor.
 */
void CrPsLptStartDownCmdStartAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t        *inData;
  CrFwInCmdData_t      *cmpSpecificData;
  CrFwPckt_t            inPckt;
  CrPsTid_t Tid;
  unsigned int LptBufferId;
  unsigned short sm_state;

  CRFW_UNUSED(smDesc);

  /* Get inPckt */
  inData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) inData->cmpSpecificData;
  inPckt            = cmpSpecificData->pckt;

  /* Determine the identifier of the LPT Buffer */
  Tid = getLptStartDownCmdTid(inPckt);
  LptBufferId = Tid % LPT_N_BUF;

  /* Set DownTransferLptBufferId for current Down Transfer */
  DownTransferLptBufferId = LptBufferId;

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  sm_state = FwSmGetCurState(smDescLpt);
  if (sm_state == CrPsLpt_INACTIVE)
    {
      inData->outcome = 1;
    }
  else
    {
      inData->outcome = 0;
    }

  return;
}

/**
 * Progress action of TC(13,129) LptStartDownCmd.
 * Send command StartDownTransfer to the LPT State Machine
 * \param smDesc The state machine descriptor.
 */
void CrPsLptStartDownCmdProgressAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t *inData;

  CRFW_UNUSED(smDesc);

  FwSmMakeTrans(smDescLpt, StartDownTransfer);

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

/**
 * Termination action of TC(13,129) LptStartDownCmd.
 * Set action outcome to 'success'
 * \param smDesc The state machine descriptor.
 */
void CrPsLptStartDownCmdTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t *inData;

  /* Set action outcome to 'success' */

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

