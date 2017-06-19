/**
 * @file CrPsReqVerifTermSucc.h
 *
 * Declaration of the Telecommand Termination Report – Success out-going report packet.
 *
 * @author code generator
 * @copyright P&P Software GmbH, 2015
 */

#ifndef CRPS_REQVERIF_TERM_SUCC_H
#define CRPS_REQVERIF_TERM_SUCC_H

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Update action of the Telecommand Termination Report – Success telemetry packet.
 * Load the value of the report parameters
 * @param smDesc the state machine descriptor
 */
void CrPsReqVerifTermSuccUpdateAction(FwSmDesc_t smDesc);

#endif /* CRPS_REQVERIF_TERM_SUCC_H */

