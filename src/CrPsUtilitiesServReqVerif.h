/**
 * @file CrPsUtilitiesServReqVerif.h
 * @ingroup Utilities
 * @ingroup Serv1
 *
 * @brief Interface through which applications can initialize and execute framework PUS extension components
 *
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * 
 * last modification: 22.01.2018
 * 
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#ifndef CRPS_UTILITIES_SERVREQVERIF_H_
#define CRPS_UTILITIES_SERVREQVERIF_H_

#include <CrFwConstants.h>
#include "CrPsUserConstants.h"



/**
 * Initialization of CORDET Framework PUS Extension components
 * @return nothing
 */
int CrPsInitServReqVerif();

/**
 * Execution of CORDET Framework PUS Extension components
 * @return nothing
 */
void CrPsExecServReqVerif();

/**
 * Getter for ReqVerifPcktReroutFail procedure descriptor
 */
FwPrDesc_t getPrDescServReqVerifPcktReroutFail();

/**
 * Getter for ReqVerifPcktAccFail procedure descriptor
 */
FwPrDesc_t getPrDescServReqVerifPcktAccFail();

/**
 * Getter for ReqVerifCmdVerSucc procedure descriptor
 */
FwPrDesc_t getPrDescServReqVerifCmdVerSucc();

/**
 * Getter for ReqVerifCmdVerFail procedure descriptor
 */
FwPrDesc_t getPrDescServReqVerifCmdVerFail();

/**
 * Getter for ReqVerifCmdPrgrSucc procedure descriptor
 */
FwPrDesc_t getPrDescServReqVerifCmdPrgrSucc();

/**
 * Getter for ReqVerifCmdPrgrFail procedure descriptor
 */
FwPrDesc_t getPrDescServReqVerifCmdPrgrFail();

/**
 * Generate a Request Verification Acceptance/Start/Termination Successful out-going report.
 * @return nothing
 */
void SendReqVerifAccSuccRep(FwSmDesc_t smDesc, uint16_t reqVerifAccSuccType);

/**
 * Generate a Request Verification Acceptance Failed out-going report.
 * @return nothing
 */
void SendReqVerifAccFailRep(FwSmDesc_t smDesc, CrPsFailCode_t FailureCode);

/**
 * Generate a Request Verification Start/Termination Failed out-going report.
 * @return nothing
 */
void SendReqVerifCmdFailRep(FwSmDesc_t smDesc, uint16_t reqVerifCmdFailType, CrPsFailCode_t FailureCode);

/**
 * Generate a Request Verification Progress Successful out-going report.
 * @return nothing
 */
void SendReqVerifPrgrSuccRep(FwSmDesc_t smDesc, CrPsStepId_t stepIdentifier);

/**
 * Generate a Request Verification Progress Failed out-going report.
 * @return nothing
 */
void SendReqVerifPrgrFailRep(FwSmDesc_t smDesc, CrPsStepId_t stepIdentifier, CrPsFailCode_t FailureCode);

/**
 * Generate a Request Verification Packet Rerouting Failed out-going report.
 * @return nothing
 */
void SendReqVerifPcktReroutFailRep(FwSmDesc_t smDesc, CrPsFailCode_t FailureCode);

#endif /* CRPS_UTILITIES_SERVREQVERIF_H_ */
