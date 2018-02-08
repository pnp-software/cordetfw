/**
 * @file CrPsLptUpInterCmd.h
 * @ingroup Serv13
 * @ingroup InCmd
 *
 * @brief Implementation of TC(13,10) LptUpInterCmd.
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

#ifndef CRPSLPTUPINTERCMD_H_
#define CRPSLPTUPINTERCMD_H_

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
