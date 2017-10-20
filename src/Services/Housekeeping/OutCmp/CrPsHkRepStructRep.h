/**
 * @file CrPsHkRepStructRep.h
 *
 * Declaration of the Housekeeping Structure Report (3,10) or Disgnostic Structure Report (3,12) out-going report packet.
 *
 * @author code generator
 * @copyright P&P Software GmbH, 2015
 */

#ifndef CRPS_HK_REPSTRUCT_REP_H
#define CRPS_HK_REPSTRUCT_REP_H

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Enable check of the Housekeeping Structure Report (3,10) out-going report packet.
 * The enable status is read from the isEnabled field of the Report Definition corresponding to the report’s SID
 * @param smDesc the state machine descriptor
 * @return the enable check result
 */
CrFwBool_t CrPsHkRepStructRepEnableCheck(FwSmDesc_t smDesc);

/**
 * Update action of the Housekeeping Structure Report (3,10) out-going report packet.
 * Load the SID definition from the RDL
 * @param smDesc the state machine descriptor
 */
void CrPsHkRepStructRepUpdateAction(FwSmDesc_t smDesc);

#endif /* CRPS_HK_REPSTRUCT_REP_H */