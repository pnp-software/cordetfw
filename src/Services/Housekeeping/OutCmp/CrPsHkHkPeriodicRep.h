/**
 * @file CrPsHkHkPeriodicRep.h
 *
 * Declaration of the Periodic Housekeeping Report (3,25) out-going report packet.
 *
 * @author code generator
 * @copyright P&P Software GmbH, 2015
 */

#ifndef CRPS_HK_HKPERIODIC_REP_H
#define CRPS_HK_HKPERIODIC_REP_H

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Enable check of the Periodic Housekeeping Report (3,25) out-going report packet.
 * The enable status is read from the isEnabled field of the Report Definition corresponding to the report’s SID
 * @param smDesc the state machine descriptor
 * @return the enable check result
 */
CrFwBool_t CrPsHkHkPeriodicRepEnableCheck(FwSmDesc_t smDesc);

/**
 * Ready check of the Periodic Housekeeping Report (3,25) out-going report packet.
 * Run the procedure Ready Check of HkRep Report of figure 9.5
 * @param smDesc the state machine descriptor
 * @return the ready check result
 */
CrFwBool_t CrPsHkHkPeriodicRepReadyCheck(FwSmDesc_t smDesc);

/**
 * Repeat check of the Periodic Housekeeping Report (3,25) out-going report packet.
 * Report is always repeated
 * @param smDesc the state machine descriptor
 * @return the repeat check result
 */
CrFwBool_t CrPsHkHkPeriodicRepRepeatCheck(FwSmDesc_t smDesc);

/**
 * Update action of the Periodic Housekeeping Report (3,25) out-going report packet.
 * Load the value of the simply-commutated data items from the data pool 
 * and that of the super-commutated data items from the Sampling Buffer 
 * associated to the report’s SID according to the Report Definition
 * @param smDesc the state machine descriptor
 */
void CrPsHkHkPeriodicRepUpdateAction(FwSmDesc_t smDesc);

#endif /* CRPS_HK_HKPERIODIC_REP_H */