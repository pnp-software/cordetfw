/**
 * @file CrPsReqVerifProgFail.h
 *
 * Declaration of the Telecommand Progress Report – Failure out-going report packet.
 *
 * @author code generator
 * @copyright P&P Software GmbH, 2015
 */

#ifndef CRPS_REQVERIF_PROG_FAIL_H
#define CRPS_REQVERIF_PROG_FAIL_H

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Update action of the Telecommand Progress Report – Failure telemetry packet.
 * Load the value of the report parameters
 * @param smDesc the state machine descriptor
 */
void CrPsReqVerifProgFailUpdateAction(FwSmDesc_t smDesc);

#endif /* CRPS_REQVERIF_PROG_FAIL_H */

