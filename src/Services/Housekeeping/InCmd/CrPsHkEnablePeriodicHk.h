/**
 * @file CrPsHkEnablePeriodicHk.h
 *
 * Command (3,5) to Enable Periodic Generation of a Housekeeping Report Structure
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#ifndef CRPS_HK_ENABLE_PERIODICHK_H
#define CRPS_HK_ENABLE_PERIODICHK_H

#include "CrFwConstants.h"

/**
 * ReadyCheck of the Command (3,5) to Enable Periodic Generation of a Housekeeping Report Structure in-coming command packet.
 * Return “command is ready"
 * @param smDesc the state machine descriptor
 * @return always TRUE
 */
CrFwBool_t CrPsHkEnablePeriodicHkReadyCheck(FwSmDesc_t smDesc);

/**
 * Start action of the Command (3,5) to Enable Periodic Generation of a Housekeeping Report Structure in-coming command packet.
 * Run the procedure Start Action of Multi-SID Command of figure 9.3
 * @param smDesc the state machine descriptor
 */
void CrPsHkEnablePeriodicHkStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of the Command (3,5) to Enable Periodic Generation of a Housekeeping Report Structure in-coming command packet.
 * For the entries in the RDL corresponding to the SIDs which have been identified as valid by the Start Action: 
 * set enabled flag to true and set the cycle counter to 0. 
 * Set the action outcome to ’completed’
 * @param smDesc the state machine descriptor
 */
void CrPsHkEnablePeriodicHkProgressAction(FwSmDesc_t smDesc);

/**
 * Termination Action of the Command (3,5) to Enable Periodic Generation of a Housekeeping Report Structure in-coming command packet.
 * Set action outcome to ’success’
 * @param smDesc the state machine descriptor
 */
void CrPsHkEnablePeriodicHkTerminationAction(FwSmDesc_t smDesc);

/**
 * Abort Action of the Command (3,5) to Enable Periodic Generation of a Housekeeping Report Structure in-coming command packet.
 * Do nothing
 * @param smDesc the state machine descriptor
 */
void CrPsHkEnablePeriodicHkAbortAction(FwSmDesc_t smDesc);



#endif /* CRPS_HK_ENABLE_PERIODICHK_H */

