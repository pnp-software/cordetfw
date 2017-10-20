/**
 * @file CrPsHkDeleteCmd.h
 *
 * Command (3,3) to Delete a Housekeeping Report Structure
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
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

