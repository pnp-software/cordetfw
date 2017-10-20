/**
 * @file CrPsHkDisableCmd.h
 *
 * Command (3,6) to Disable Periodic Generation of a Housekeeping Report Structure
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
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

