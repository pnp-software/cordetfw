/**
 * @file
 * @ingroup crPsUtilities
 * Interface through which applications can initialize and execute framework PUS extension components
 *
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @copyright P&P Software GmbH, 2013 / Department of Astrophysics, University of Vienna, All Rights Reserved
 * @version GPLv3_0.7.1
 *
 * This file is part of CORDET Framework PUS Extension.
 *
 * CORDET Framework is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CORDET Framework is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CORDET Framework.  If not, see <http://www.gnu.org/licenses/>.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#ifndef CRPS_UTILITIES_H_
#define CRPS_UTILITIES_H_

#include <CrFwConstants.h>

/* global handles for the procedures */
extern FwPrDesc_t prDescServTestOnBoardConnStart, prDescServTestOnBoardConnPrgr;
extern FwPrDesc_t prDescServReqVerifPcktReroutFail, prDescServReqVerifPcktAccFail;
extern FwPrDesc_t prDescServReqVerifCmdVerSucc, prDescServReqVerifCmdVerFail;
extern FwPrDesc_t prDescServReqVerifCmdPrgrSucc, prDescServReqVerifCmdPrgrFail;
extern FwPrDesc_t prDescHkCmd3s1Start, prDescHkRepReadyCheck;
extern FwPrDesc_t prDescMultiSidCmdStart, prDescGenerateHkOneShotPrgr;


/**
 * Initialization of CORDET Framework PUS Extension application-specific components
 * @return nothing
 */
void CrPsInitApp(unsigned short onBoardTestConnectAppId);

/**
 * Initialization of CORDET Framework PUS Extension components
 * @return nothing
 */
int CrPsInit();

/**
 * Execution of CORDET Framework PUS Extension components
 * @return nothing
 */
void CrPsExec();

/**
 * Generate a Request Verification Acceptance/Start/Termination Successful out-going report.
 * @return nothing
 */
void SendReqVerifAccSuccRep(FwSmDesc_t smDesc, unsigned short reqVerifAccSuccType);

/**
 * Generate a Request Verification Acceptance Failed out-going report.
 * @return nothing
 */
void SendReqVerifAccFailRep(FwSmDesc_t smDesc, unsigned short tcFailureCode);


/**
 * Generate a Request Verification Start/Termination Failed out-going report.
 * @return nothing
 */
void SendReqVerifCmdFailRep(FwSmDesc_t smDesc, unsigned short reqVerifCmdFailType, unsigned short tcFailureCode);

/**
 * Generate a Request Verification Progress Successful out-going report.
 * @return nothing
 */
void SendReqVerifPrgrSuccRep(FwSmDesc_t smDesc, unsigned short stepIdentifier);

/**
 * Generate a Request Verification Progress Failed out-going report.
 * @return nothing
 */
void SendReqVerifPrgrFailRep(FwSmDesc_t smDesc, unsigned short stepIdentifier, unsigned short tcFailureCode);

/**
 * Generate a Request Verification Packet Rerouting Failed out-going report.
 * @return nothing
 */
void SendReqVerifPcktReroutFailRep(FwSmDesc_t smDesc, unsigned short tcFailureCode);

#endif /* CRPS_UTILITIES_H_ */
