/**
 * @file CrPsHkOneShotCmd.h
 *
 * Command (3,27) to Generate One-Shot Housekeeping Report
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#ifndef CRPS_HK_ONESHOT_CMD_H
#define CRPS_HK_ONESHOT_CMD_H

#include "CrFwConstants.h"

/**
 * ReadyCheck of the Command (3,27) to Generate One-Shot Housekeeping Report in-coming command packet.
 * Return “command is ready"
 * @param smDesc the state machine descriptor
 * @return always TRUE
 */
CrFwBool_t CrPsHkOneShotCmdReadyCheck(FwSmDesc_t smDesc);

/**
 * Start action of the Command (3,27) to Generate One-Shot Housekeeping Report in-coming command packet.
 * Run the procedure Start Action of Multi-SID Command of figure 9.3
 * @param smDesc the state machine descriptor
 */
void CrPsHkOneShotCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of the Command (3,27) to Generate One-Shot Housekeeping Report in-coming command packet.
 * Run the procedure Progress Action of Generate One-Shot Housekeeping Report of figure 9.6
 * @param smDesc the state machine descriptor
 */
void CrPsHkOneShotCmdProgressAction(FwSmDesc_t smDesc);

/**
 * Termination Action of the Command (3,27) to Generate One-Shot Housekeeping Report in-coming command packet.
 * Set action outcome to ’success’ if all valid SIDs in the command were successfully processed by the progress action; 
 * set it to ’failure’ otherwise
 * @param smDesc the state machine descriptor
 */
void CrPsHkOneShotCmdTerminationAction(FwSmDesc_t smDesc);

/**
 * Abort Action of the Command (3,27) to Generate One-Shot Housekeeping Report in-coming command packet.
 * Do nothing
 * @param smDesc the state machine descriptor
 */
void CrPsHkOneShotCmdAbortAction(FwSmDesc_t smDesc);



#endif /* CRPS_HK_ONESHOT_CMD_H */

