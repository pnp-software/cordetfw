/**
 * \file
 *
 * Implementation of TC(13,10) LptUpInterCmd.
 *
 * \note This file was generated on 2017-11-22 12:47:43
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSLPTUPINTERCMD_H_
#define CRPSLPTUPINTERCMD_H_

#include "CrPsDpTypes.h"

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Start action of TC(13,10) LptUpInterCmd.
 * Run the Procedure Up-Transfer Start Action of Figure ??
 * \param smDesc The state machine descriptor.
 */
void CrPsLptUpInterCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(13,10) LptUpInterCmd.
 * Copy the up-transfer data to LPT Buffer and increment lptSize by the amount
 * of copied data; set lptTime to the current time; set patSeqNmb to the part
 * sequence number carried by the command
 * \param smDesc The state machine descriptor.
 */
void CrPsLptUpInterCmdProgressAction(FwSmDesc_t smDesc);

/**
 * Termination action of TC(13,10) LptUpInterCmd.
 * Set action outcome to 'success'
 * \param smDesc The state machine descriptor.
 */
void CrPsLptUpInterCmdTerminationAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSLPTUPINTERCMD_H */
