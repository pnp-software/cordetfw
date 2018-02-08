/**
 * @file CrPsHkEnableCmd.h
 * @ingroup Serv3
 * @ingroup InCmd
 *
 * @brief Command (3,5) to Enable Periodic Generation of a Housekeeping Report Structure
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

#ifndef CRPS_HK_ENABLE_CMD_H
#define CRPS_HK_ENABLE_CMD_H

#include "CrFwConstants.h"

/**
 * ReadyCheck of the Command (3,5) to Enable Periodic Generation of a Housekeeping Report Structure in-coming command packet.
 * Return “command is ready"
 * @param smDesc the state machine descriptor
 * @return always TRUE
 */
CrFwBool_t CrPsHkEnableCmdReadyCheck(FwSmDesc_t smDesc);

/**
 * Start action of the Command (3,5) to Enable Periodic Generation of a Housekeeping Report Structure in-coming command packet.
 * Run the procedure Start Action of Multi-SID Command of figure 9.3
 * @param smDesc the state machine descriptor
 */
void CrPsHkEnableCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of the Command (3,5) to Enable Periodic Generation of a Housekeeping Report Structure in-coming command packet.
 * For the entries in the RDL corresponding to the SIDs which have been identified as valid by the Start Action: 
 * set enabled flag to true and set the cycle counter to 0. 
 * Set the action outcome to ’completed’
 * @param smDesc the state machine descriptor
 */
void CrPsHkEnableCmdProgressAction(FwSmDesc_t smDesc);

/**
 * Termination Action of the Command (3,5) to Enable Periodic Generation of a Housekeeping Report Structure in-coming command packet.
 * Set action outcome to ’success’
 * @param smDesc the state machine descriptor
 */
void CrPsHkEnableCmdTerminationAction(FwSmDesc_t smDesc);

/**
 * Abort Action of the Command (3,5) to Enable Periodic Generation of a Housekeeping Report Structure in-coming command packet.
 * Do nothing
 * @param smDesc the state machine descriptor
 */
void CrPsHkEnableCmdAbortAction(FwSmDesc_t smDesc);



#endif /* CRPS_HK_ENABLE_CMD_H */

