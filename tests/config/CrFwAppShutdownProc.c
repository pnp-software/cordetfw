/**
 * @file
 * @ingroup CrTestSuiteGroup
 *
 * Default implementation of the Application Shutdown Procedure of <code>CrFwAppShutdownProc.h</code>.
 * The implementation of this procedure is one of the adaptation points of the
 * CORDET Framework.
 * This file provides a default implementation which is primarily intended to
 * support testing.
 * It is expected that applications will provide their own implementation.
 * Application will therefore normally replace this file with their own file
 * providing their application-specific implementation of the Application Shutdown Procedure.
 *
 * This implementation defines a dummy procedure as in the figure below.
 * @image html DummyApp.png
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of CORDET Framework.
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

#include <stdlib.h>
/* Include FW Profile Files */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include Framework Files */
#include "CrFwConstants.h"
#include "AppStartUp/CrFwAppResetProc.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"

/** The singleton instance of the Application Shutdown Procedure */
FwPrDesc_t shutdownPrDesc;

/*-----------------------------------------------------------------------------------------*/
FwPrDesc_t CrFwAppSmGetAppShutdownProc() {
	const FwPrCounterS1_t nOfANodes = 1;	/* Number of action nodes */
	const FwPrCounterS1_t nOfDNodes = 0;	/* Number of decision nodes */
	const FwPrCounterS1_t nOfFlows = 2;		/* Number of control flows */
	const FwPrCounterS1_t nOfActions = 1;	/* Number of actions */
	const FwPrCounterS1_t nOfGuards = 1;	/* Number of guards */
	const FwPrCounterS1_t N1 = 1;			/* Identifier of first action node */

	if (shutdownPrDesc != NULL)
		return shutdownPrDesc;

	/* Create the initialization procedure */
	shutdownPrDesc = FwPrCreate(nOfANodes, nOfDNodes, nOfFlows, nOfActions, nOfGuards);

	/* Configure the initialization procedure */
	FwPrAddActionNode(shutdownPrDesc, N1, &CrFwPrEmptyAction);
	FwPrAddFlowIniToAct(shutdownPrDesc, N1, NULL);
	FwPrAddFlowActToFin(shutdownPrDesc, N1, &CrFwWaitOnePrCycle);

	return shutdownPrDesc;
}
