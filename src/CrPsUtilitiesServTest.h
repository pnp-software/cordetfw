/**
 * @file CrPsUtilitiesServTest.h
 * @ingroup Utilities
 * @ingroup Serv17
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

#ifndef CRPS_UTILITIES_SERVTEST_H_
#define CRPS_UTILITIES_SERVTEST_H_

#include <CrFwConstants.h>

/**
 * Initialization of CORDET Framework PUS Extension application-specific components
 * @return nothing
 */
void CrPsInitServTestApp(unsigned short onBoardTestConnectAppId);

/**
 * Initialization of CORDET Framework PUS Extension components
 * @return nothing
 */
int CrPsInitServTest();

/**
 * Execution of CORDET Framework PUS Extension components
 * @return nothing
 */
void CrPsExecServTest();

/**
 * Getter for TestOnBoardConnStart procedure descriptor
 */
FwPrDesc_t getPrDescServTestOnBoardConnStart();

/**
 * Getter for TestOnBoardConnPrgr procedure descriptor
 */
FwPrDesc_t getPrDescServTestOnBoardConnPrgr();

#endif /* CRPS_UTILITIES_SERVTEST_H_ */
