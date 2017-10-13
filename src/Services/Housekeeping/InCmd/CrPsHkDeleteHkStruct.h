/**
 * @file CrPsHkDeleteHkStruct.h
 *
 * Command (3,3) to Delete a Housekeeping Report Structure
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#ifndef CRPS_HK_DELETE_HKSTRUCT_H
#define CRPS_HK_DELETE_HKSTRUCT_H

#include "CrFwConstants.h"

/**
 * ReadyCheck of the Command (3,3) to Delete a Housekeeping Report Structure in-coming command packet.
 * Return “command is ready"
 * @param smDesc the state machine descriptor
 * @return always TRUE
 */
CrFwBool_t CrPsHkDeleteHkStructReadyCheck(FwSmDesc_t smDesc);

/**
 * Start action of the Command (3,3) to Delete a Housekeeping Report Structure in-coming command packet.
 * Run the procedure Start Action of HkDelete Command of figure 9.2
 * @param smDesc the state machine descriptor
 */
void CrPsHkDeleteHkStructStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of the Command (3,3) to Delete a Housekeeping Report Structure in-coming command packet.
 * Delete the entries in the RDL corresponding to the SIDs which have been identified as valid by the Start Action 
 * and then set the action outcome to ’completed’
 * @param smDesc the state machine descriptor
 */
void CrPsHkDeleteHkStructProgressAction(FwSmDesc_t smDesc);

/**
 * Termination Action of the Command (3,3) to Delete a Housekeeping Report Structure in-coming command packet.
 * Set action outcome to ’success’
 * @param smDesc the state machine descriptor
 */
void CrPsHkDeleteHkStructTerminationAction(FwSmDesc_t smDesc);

/**
 * Abort Action of the Command (3,3) to Delete a Housekeeping Report Structure in-coming command packet.
 * Do nothing
 * @param smDesc the state machine descriptor
 */
void CrPsHkDeleteHkStructAbortAction(FwSmDesc_t smDesc);



#endif /* CRPS_HK_DELETE_HKSTRUCT_H */

