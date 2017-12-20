/**
 * \file
 *
 * Implementation of TC(13,130) LptAbortDownCmd.
 *
 * \note This file was generated on 2017-11-22 12:47:44
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSLPTABORTDOWNCMD_H_
#define CRPSLPTABORTDOWNCMD_H_

#include "CrPsDpTypes.h"

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Start action of TC(13,130) LptAbortDownCmd.
 * Determine the identifier of the LPT Buffer for the up-transfer by
 * computing: (x MOD LPT_N_BUF) where `x' is the Large Message Transaction
 * Identifier. Set action outcome to 'success' if the LPT State Machine is in
 * state DOWN_TRANSFER; otherwise set the action outcome to `failure'
 * \param smDesc The state machine descriptor.
 */
void CrPsLptAbortDownCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(13,130) LptAbortDownCmd.
 * Send command Abort to the LPT State Machine
 * \param smDesc The state machine descriptor.
 */
void CrPsLptAbortDownCmdProgressAction(FwSmDesc_t smDesc);

/**
 * Termination action of TC(13,130) LptAbortDownCmd.
 * Set action outcome to 'success'
 * \param smDesc The state machine descriptor.
 */
void CrPsLptAbortDownCmdTerminationAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSLPTABORTDOWNCMD_H */
