/**
 * @file CrPsHkCreateDiagStruct.h
 *
 * Command (3,2) to Create a Diagnostic Report Structure
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#ifndef CRPS_HK_CREATE_DIAGSTRUCT_H
#define CRPS_HK_CREATE_DIAGSTRUCT_H

#include "CrFwConstants.h"

/**
 * ReadyCheck of the Command (3,2) to Create a Diagnostic Report Structure in-coming command packet.
 * Return “command is ready"
 * @param smDesc the state machine descriptor
 * @return always TRUE
 */
CrFwBool_t CrPsHkCreateDiagStructReadyCheck(FwSmDesc_t smDesc);

/**
 * Start action of the Command (3,2) to Create a Diagnostic Report Structure in-coming command packet.
 * Run the procedure Start Action of HkCreate Command of figure 9.1
 * @param smDesc the state machine descriptor
 */
void CrPsHkCreateDiagStructStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of the Command (3,2) to Create a Diagnostic Report Structure in-coming command packet.
 * Add the definition of the new report to the RDL, set its enabled status to ’disabled’, and set the action outcome to ’completed’
 * @param smDesc the state machine descriptor
 */
void CrPsHkCreateDiagStructProgressAction(FwSmDesc_t smDesc);

/**
 * Termination Action of the Command (3,2) to Create a Diagnostic Report Structure in-coming command packet.
 * Set action outcome to ’success’
 * @param smDesc the state machine descriptor
 */
void CrPsHkCreateDiagStructTerminationAction(FwSmDesc_t smDesc);

/**
 * Abort Action of the Command (3,2) to Create a Diagnostic Report Structure in-coming command packet.
 * Do nothing
 * @param smDesc the state machine descriptor
 */
void CrPsHkCreateDiagStructAbortAction(FwSmDesc_t smDesc);



#endif /* CRPS_HK_CREATE_DIAGSTRUCT_H */

