/**
 * @file CrPsHkDiagOneShotRep.h
 *
 * Declaration of the One-Shot Diagnostic Report (response to command (3,28)) out-going report packet.
 *
 * @author code generator
 * @copyright P&P Software GmbH, 2015
 */

#ifndef CRPS_HK_DIAGONESHOT_REP_H
#define CRPS_HK_DIAGONESHOT_REP_H

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Enable check of the One-Shot Diagnostic Report (response to command (3,28)) out-going report packet.
 * Report is always enabled
 * @param smDesc the state machine descriptor
 * @return the enable check result
 */
CrFwBool_t CrPsHkDiagOneShotRepEnableCheck(FwSmDesc_t smDesc);

/**
 * Ready check of the One-Shot Diagnostic Report (response to command (3,28)) out-going report packet.
 * Report is always ready
 * @param smDesc the state machine descriptor
 * @return the ready check result
 */
CrFwBool_t CrPsHkDiagOneShotRepReadyCheck(FwSmDesc_t smDesc);

/**
 * Repeat check of the One-Shot Diagnostic Report (response to command (3,28)) out-going report packet.
 * Report is never repeated
 * @param smDesc the state machine descriptor
 * @return the repeat check result
 */
CrFwBool_t CrPsHkDiagOneShotRepRepeatCheck(FwSmDesc_t smDesc);

/**
 * Update action of the One-Shot Diagnostic Report (response to command (3,28)) out-going report packet.
 * Load the value of the simply-commutated data items from the data pool 
 * and that of the super-commutated data items from the Sampling Buffer associated to the report’s SID 
 * according to the Report Definition.
 * @param smDesc the state machine descriptor
 */
void CrPsHkDiagOneShotRepUpdateAction(FwSmDesc_t smDesc);

#endif /* CRPS_HK_DIAGONESHOT_REP_H */