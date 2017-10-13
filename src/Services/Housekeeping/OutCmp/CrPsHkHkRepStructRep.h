/**
 * @file CrPsHkHkRepStructRep.h
 *
 * Declaration of the Housekeeping Structure Report (3,10) out-going report packet.
 *
 * @author code generator
 * @copyright P&P Software GmbH, 2015
 */

#ifndef CRPS_HK_HKREPSTRUCT_REP_H
#define CRPS_HK_HKREPSTRUCT_REP_H

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Enable check of the Housekeeping Structure Report (3,10) out-going report packet.
 * The enable status is read from the isEnabled field of the Report Definition corresponding to the report’s SID
 * @param smDesc the state machine descriptor
 * @return the enable check result
 */
CrFwBool_t CrPsHkHkRepStructRepEnableCheck(FwSmDesc_t smDesc);

/**
 * Ready check of the Housekeeping Structure Report (3,10) out-going report packet.
 * Report is always ready
 * @param smDesc the state machine descriptor
 * @return the ready check result
 */
CrFwBool_t CrPsHkHkRepStructRepReadyCheck(FwSmDesc_t smDesc);

/**
 * Repeat check of the Housekeeping Structure Report (3,10) out-going report packet.
 * Report is never repeated
 * @param smDesc the state machine descriptor
 * @return the repeat check result
 */
CrFwBool_t CrPsHkHkRepStructRepRepeatCheck(FwSmDesc_t smDesc);

/**
 * Update action of the Housekeeping Structure Report (3,10) out-going report packet.
 * Load the SID definition from the RDL
 * @param smDesc the state machine descriptor
 */
void CrPsHkHkRepStructRepUpdateAction(FwSmDesc_t smDesc);

#endif /* CRPS_HK_HKREPSTRUCT_REP_H */