/**
 * @file CrPsUtilitiesServHk.h
 * @ingroup Utilities
 * @ingroup Serv3
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

#ifndef CRPS_UTILITIES_SERVHK_H_
#define CRPS_UTILITIES_SERVHK_H_

#include <CrFwConstants.h>


/**
 * Initialization of CORDET Framework PUS Extension components
 * @return nothing
 */
int CrPsInitServHk();

/**
 * Execution of CORDET Framework PUS Extension components
 * @return nothing
 */
void CrPsExecServHk();

/**
 * Getter for HkCmd3s1Start procedure descriptor
 */
FwPrDesc_t getPrDescHkCmd3s1Start();

/**
 * Getter for HkCmd3s3Start procedure descriptor
 */
FwPrDesc_t getPrDescHkCmd3s3Start();

/**
 * Getter for HkRepReadyCheck procedure descriptor
 */
FwPrDesc_t getPrDescHkRepReadyCheck();

/**
 * Getter for MultiSidCmdStart procedure descriptor
 */
FwPrDesc_t getPrDescMultiSidCmdStart();

/**
 * Getter for Cmd3s9Prgr procedure descriptor
 */
FwPrDesc_t getPrDescCmd3s9Prgr();

#endif /* CRPS_UTILITIES_SERVHK_H_ */
