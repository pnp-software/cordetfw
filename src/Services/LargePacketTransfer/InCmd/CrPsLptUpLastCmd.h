/**
 * \file
 *
 * Implementation of TC(13,11) LptUpLastCmd.
 *
 * \note This file was generated on 2017-11-22 12:47:43
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSLPTUPLASTCMD_H_
#define CRPSLPTUPLASTCMD_H_

#include "CrPsDpTypes.h"

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Start action of TC(13,11) LptUpLastCmd.
 * Run the Procedure Up-Transfer Start Action of figure ??
 * \param smDesc The state machine descriptor.
 */
void CrPsLptUpLastCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(13,11) LptUpLastCmd.
 * Copy the lptSize up-transfer data to LPT Buffer and increment lptSize by
 * the amount of copied data; set current time; set patSeqNmb to the part
 * sequence number carried by the command; send EndUpTransfer command to LPT
 * State Machine
 * \param smDesc The state machine descriptor.
 */
void CrPsLptUpLastCmdProgressAction(FwSmDesc_t smDesc);

/**
 * Termination action of TC(13,11) LptUpLastCmd.
 * Set action outcome to 'success'
 * \param smDesc The state machine descriptor.
 */
void CrPsLptUpLastCmdTerminationAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSLPTUPLASTCMD_H */
