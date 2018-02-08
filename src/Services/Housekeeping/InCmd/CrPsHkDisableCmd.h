/**
 * @file CrPsHkDisableCmd.h
 * @ingroup Serv3
 * @ingroup InCmd
 *
 * @brief Command (3,6) to Disable Periodic Generation of a Housekeeping Report Structure
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

#ifndef CRPS_HK_DISABLE_CMD_H
#define CRPS_HK_DISABLE_CMD_H

#include "CrFwConstants.h"

/**
 * Start action of the Command (3,6) to Disable Periodic Generation of a Housekeeping Report Structure in-coming command packet.
 * Run the procedure Start Action of Multi-SID Command of figure 9.3
 * @param smDesc the state machine descriptor
 */
void CrPsHkDisableCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of the Command (3,6) to Disable Periodic Generation of a Housekeeping Report Structure in-coming command packet.
 * Set to false the enable flag of the entries in the RDL corresponding to the SIDs which have been 
 * identified as valid by the Start Action and then set the action outcome to ’completed’
 * @param smDesc the state machine descriptor
 */
void CrPsHkDisableCmdProgressAction(FwSmDesc_t smDesc);

/**
 * Termination Action of the DCommand (3,6) to Disable Periodic Generation of a Housekeeping Report Structure in-coming command packet.
 * Set action outcome to ’success’
 * @param smDesc the state machine descriptor
 */
void CrPsHkDisableCmdTerminationAction(FwSmDesc_t smDesc);

#endif /* CRPS_HK_DISABLE_CMD_H */

