/**
 * @file CrPsLptUpFirstCmd.h
 * @ingroup Serv13
 * @ingroup InCmd
 *
 * @brief Implementation of TC(13,9) LptUpFirstCmd.
 *
 * @note This file was generated on 2017-11-22 12:47:43
 *
 * @author PnP Generator
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

#ifndef CRPSLPTUPFIRSTCMD_H_
#define CRPSLPTUPFIRSTCMD_H_

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Start action of TC(13,9) LptUpFirstCmd.
 * Determine the identifier of the LPT Buffer for the up-transfer by
 * computing: (x MOD LPT_N_BUF) where `x' is the Large Message Transaction
 * Identifier. Set action outcome to 'success' if the Part Sequence Number is
 * equal to 1 and the LPT State Machine is in state INACTIVE; otherwise set
 * the action outcome to `failure'
 * \param smDesc The state machine descriptor.
 */
void CrPsLptUpFirstCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(13,9) LptUpFirstCmd.
 * Send command StartUpTransfer to LPT State Machine; copy the up-transfer
 * data to LPT Buffer and set lptSize to be equal to the amout of copied data;
 * set lptTime to the current time; set partSeqNmb to 1; set lptSrc to the
 * source of the command
 * \param smDesc The state machine descriptor.
 */
void CrPsLptUpFirstCmdProgressAction(FwSmDesc_t smDesc);

/**
 * Termination action of TC(13,9) LptUpFirstCmd.
 * Set action outcome to 'success'
 * \param smDesc The state machine descriptor.
 */
void CrPsLptUpFirstCmdTerminationAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSLPTUPFIRSTCMD_H */
