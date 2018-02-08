/**
 * @file CrPsHkCreateCmd.h
 * @ingroup Serv3
 * @ingroup InCmd
 *
 * @brief Command (3,1) to Create a Housekeeping Report Structure
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

#ifndef CRPS_HK_CREATE_CMD_H
#define CRPS_HK_CREATE_CMD_H

#include "CrFwConstants.h"

/**
 * Start action of the Command (3,1) to Create a Housekeeping Report Structure in-coming command packet.
 * Run the procedure Start Action of HkCreate Command of figure 9.1
 * @param smDesc the state machine descriptor
 */
void CrPsHkCreateCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of the Command (3,1) to Create a Housekeeping Report Structure in-coming command packet.
 * Add the definition of the new report to the RDL, set its enabled status to ’disabled’, and set the action outcome to ’completed’
 * @param smDesc the state machine descriptor
 */
void CrPsHkCreateCmdProgressAction(FwSmDesc_t smDesc);

/**
 * Termination Action of the Command (3,1) to Create a Housekeeping Report Structure in-coming command packet.
 * Set action outcome to ’success’
 * @param smDesc the state machine descriptor
 */
void CrPsHkCreateCmdTerminationAction(FwSmDesc_t smDesc);



#endif /* CRPS_HK_CREATE_CMD_H */

