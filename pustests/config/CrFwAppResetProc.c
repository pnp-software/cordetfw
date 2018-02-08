/**
 * @file CrFwAppResetProc.c
 * @ingroup PUSTestsuite
 * @ingroup PUSTestconfig 
 *
 * Default implementation of the Application Reset Procedure of <code>CrFwAppResetProc.h</code>.
 * The implementation of this procedure is one of the adaptation points of the
 * CORDET Framework.
 * This file provides a default implementation which is primarily intended to
 * support testing.
 * It is expected that applications will provide their own implementation.
 * Application will therefore normally replace this file with their own file
 * providing their application-specific implementation of the Application Reset Procedure.
 *
 * This implementation defines a dummy procedure as in the figure below.
 * @image html DummyApp.png
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
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

/** The singleton instance of the Application Reset Procedure */
FwPrDesc_t resetPrDesc;

/*-----------------------------------------------------------------------------------------*/
FwPrDesc_t CrFwAppSmGetAppResetProc() {
	const FwPrCounterS1_t nOfANodes = 1;	/* Number of action nodes */
	const FwPrCounterS1_t nOfDNodes = 0;	/* Number of decision nodes */
	const FwPrCounterS1_t nOfFlows = 2;		/* Number of control flows */
	const FwPrCounterS1_t nOfActions = 1;	/* Number of actions */
	const FwPrCounterS1_t nOfGuards = 1;	/* Number of guards */
	const FwPrCounterS1_t N1 = 1;			/* Identifier of first action node */

	if (resetPrDesc != NULL)
		return resetPrDesc;

	/* Create the initialization procedure */
	resetPrDesc = FwPrCreate(nOfANodes, nOfDNodes, nOfFlows, nOfActions, nOfGuards);

	/* Configure the initialization procedure */
	FwPrAddActionNode(resetPrDesc, N1, &CrFwPrEmptyAction);
	FwPrAddFlowIniToAct(resetPrDesc, N1, NULL);
	FwPrAddFlowActToFin(resetPrDesc, N1, &CrFwWaitOnePrCycle);

	return resetPrDesc;
}
