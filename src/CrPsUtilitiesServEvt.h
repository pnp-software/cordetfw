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

#ifndef CRPS_UTILITIES_SERVEVT_H_
#define CRPS_UTILITIES_SERVEVT_H_

#include <CrFwConstants.h>


/* global handles for the procedures */
extern FwPrDesc_t prDescEvtCmd5EidStart;


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

#endif /* CRPS_UTILITIES_SERVEVT_H_ */
