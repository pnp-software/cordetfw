/**
 * @file CrPsReqVerifTermFail.h
 *
 * Declaration of the Telecommand Termination Report – Failure out-going report packet.
 *
 * @author code generator
 * @copyright P&P Software GmbH, 2015
 */

#ifndef CRPS_REQVERIF_TERM_FAIL_H
#define CRPS_REQVERIF_TERM_FAIL_H

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Update action of the Telecommand Termination Report – Failure telemetry packet.
 * Load the value of the report parameters
 * @param smDesc the state machine descriptor
 */
void CrPsReqVerifTermFailUpdateAction(FwSmDesc_t smDesc);

#endif /* CRPS_REQVERIF_TERM_FAIL_H */

