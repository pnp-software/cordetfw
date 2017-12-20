/**
 * \file
 *
 * Implementation of TC(13,129) LptStartDownCmd.
 *
 * \note This file was generated on 2017-11-22 12:47:43
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSLPTSTARTDOWNCMD_H_
#define CRPSLPTSTARTDOWNCMD_H_

#include "CrPsDpTypes.h"

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Start action of TC(13,129) LptStartDownCmd.
 * Determine the identifier of the LPT Buffer for the up-transfer by
 * computing: (x MOD LPT_N_BUF) where `x' is the Large Message Transaction
 * Identifier. Set action outcome to 'success' if the LPT State Machine is in
 * state INACTIVE; otherwise set the action outcome to `failure'
 * \param smDesc The state machine descriptor.
 */
void CrPsLptStartDownCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(13,129) LptStartDownCmd.
 * Send command StartDownTransfer to the LPT State Machine
 * \param smDesc The state machine descriptor.
 */
void CrPsLptStartDownCmdProgressAction(FwSmDesc_t smDesc);

/**
 * Termination action of TC(13,129) LptStartDownCmd.
 * Set action outcome to 'success'
 * \param smDesc The state machine descriptor.
 */
void CrPsLptStartDownCmdTerminationAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSLPTSTARTDOWNCMD_H */
