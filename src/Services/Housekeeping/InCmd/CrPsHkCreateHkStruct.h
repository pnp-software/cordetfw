/**
 * @file CrPsHkCreateHkStruct.h
 *
 * Command (3,1) to Create a Housekeeping Report Structure
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#ifndef CRPS_HK_CREATE_HKSTRUCT_H
#define CRPS_HK_CREATE_HKSTRUCT_H

#include "CrFwConstants.h"

/**
 * ReadyCheck of the Command (3,1) to Create a Housekeeping Report Structure in-coming command packet.
 * Return “command is ready"
 * @param smDesc the state machine descriptor
 * @return always TRUE
 */
CrFwBool_t CrPsHkCreateHkStructReadyCheck(FwSmDesc_t smDesc);

/**
 * Start action of the Command (3,1) to Create a Housekeeping Report Structure in-coming command packet.
 * Run the procedure Start Action of HkCreate Command of figure 9.1
 * @param smDesc the state machine descriptor
 */
void CrPsHkCreateHkStructStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of the Command (3,1) to Create a Housekeeping Report Structure in-coming command packet.
 * Add the definition of the new report to the RDL, set its enabled status to ’disabled’, and set the action outcome to ’completed’
 * @param smDesc the state machine descriptor
 */
void CrPsHkCreateHkStructProgressAction(FwSmDesc_t smDesc);

/**
 * Termination Action of the Command (3,1) to Create a Housekeeping Report Structure in-coming command packet.
 * Set action outcome to ’success’
 * @param smDesc the state machine descriptor
 */
void CrPsHkCreateHkStructTerminationAction(FwSmDesc_t smDesc);

/**
 * Abort Action of the Command (3,1) to Create a Housekeeping Report Structure in-coming command packet.
 * Do nothing
 * @param smDesc the state machine descriptor
 */
void CrPsHkCreateHkStructAbortAction(FwSmDesc_t smDesc);



#endif /* CRPS_HK_CREATE_HKSTRUCT_H */

