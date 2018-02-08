/**
 * @file CrPsHkDeleteCmd.h
 * @ingroup Serv3
 * @ingroup InCmd
 *
 * @brief Command (3,3) to Delete a Housekeeping Report Structure
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

#ifndef CRPS_HK_DELETE_CMD_H
#define CRPS_HK_DELETE_CMD_H

#include "CrFwConstants.h"

/**
 * Start action of the Command (3,3) to Delete a Housekeeping Report Structure in-coming command packet.
 * Run the procedure Start Action of HkDelete Command of figure 9.2
 * @param smDesc the state machine descriptor
 */
void CrPsHkDeleteCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of the Command (3,3) to Delete a Housekeeping Report Structure in-coming command packet.
 * Delete the entries in the RDL corresponding to the SIDs which have been identified as valid by the Start Action 
 * and then set the action outcome to ’completed’
 * @param smDesc the state machine descriptor
 */
void CrPsHkDeleteCmdProgressAction(FwSmDesc_t smDesc);

/**
 * Termination Action of the Command (3,3) to Delete a Housekeeping Report Structure in-coming command packet.
 * Set action outcome to ’success’
 * @param smDesc the state machine descriptor
 */
void CrPsHkDeleteCmdTerminationAction(FwSmDesc_t smDesc);



#endif /* CRPS_HK_DELETE_CMD_H */

