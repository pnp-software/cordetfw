/**
 * @file CrPsLptUpLastCmd.h
 * @ingroup Serv13
 * @ingroup InCmd
 *
 * @brief Implementation of TC(13,11) LptUpLastCmd.
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

#ifndef CRPSLPTUPLASTCMD_H_
#define CRPSLPTUPLASTCMD_H_

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
