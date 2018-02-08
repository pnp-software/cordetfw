/**
 * @file CrPsHkRepStructCmd.h
 * @ingroup Serv3
 * @ingroup InCmd
 *
 * @brief Command (3,9) to Report Structure of a Housekeeping Report
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

#ifndef CRPS_HK_REPSTRUCT_CMD_H
#define CRPS_HK_REPSTRUCT_CMD_H

#include "CrFwConstants.h"

/**
 * Start action of the Command (3,9) to Report Structure of a Housekeeping Report in-coming command packet.
 * Run the procedure Start Action of Multi-SID Command of figure 9.3
 * @param smDesc the state machine descriptor
 */
void CrPsHkRepStructCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of the Command (3,9) to Report Structure of a Housekeeping Report in-coming command packet.
 * Run the procedure Progress Action of Report Housekeeping Structure of figure 9.4
 * @param smDesc the state machine descriptor
 */
void CrPsHkRepStructCmdProgressAction(FwSmDesc_t smDesc);

/**
 * Termination Action of the Command (3,9) to Report Structure of a Housekeeping Report in-coming command packet.
 * Set action outcome to ’success’ if all valid SIDs in the command were successfully processed by the progress action; 
 * set it to ’failure’ otherwise
 * @param smDesc the state machine descriptor
 */
void CrPsHkRepStructCmdTerminationAction(FwSmDesc_t smDesc);


#endif /* CRPS_HK_REPSTRUCT_CMD_H */

