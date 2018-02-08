/**
 * @file CrPsUtilitiesServEvt.h
 * @ingroup Utilities
 * @ingroup Serv5
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

#ifndef CRPS_UTILITIES_SERVEVT_H_
#define CRPS_UTILITIES_SERVEVT_H_

#include <CrFwConstants.h>


/**
 * Initialization of CORDET Framework PUS Extension components
 * @return nothing
 */
int CrPsInitServEvt();

/**
 * Execution of CORDET Framework PUS Extension components
 * @return nothing
 */
void CrPsExecServEvt();

/**
 * Getter for EvtCmd5EidStart procedure descriptor
 */
FwPrDesc_t getPrDescEvtCmd5EidStart();

#endif /* CRPS_UTILITIES_SERVEVT_H_ */
