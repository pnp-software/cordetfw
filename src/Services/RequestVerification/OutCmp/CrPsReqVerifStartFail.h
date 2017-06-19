/**
 * @file CrPsReqVerifStartFail.h
 *
 * Declaration of the Telecommand Start Report – Failure out-going report packet.
 *
 * @author code generator
 * @copyright P&P Software GmbH, 2015
 */

#ifndef CRPS_REQVERIF_START_FAIL_H
#define CRPS_REQVERIF_START_FAIL_H

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Update action of the Telecommand Start Report – Failure telemetry packet.
 * Load the value of the report parameters
 * @param smDesc the state machine descriptor
 */
void CrPsReqVerifStartFailUpdateAction(FwSmDesc_t smDesc);

#endif /* CRPS_REQVERIF_START_FAIL_H */

