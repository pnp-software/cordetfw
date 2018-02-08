/**
 * @file CrFwAppSmTestCases.c
 * @ingroup PUSTestsuite
 *
 * @brief Implementation of test cases for the Application State Machine.
 *
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
#include "CrFwAppSmTestCases.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmSCreate.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include framework files */
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "AppStartUp/CrFwAppSm.h"
#include "AppStartUp/CrFwAppResetProc.h"
#include "AppStartUp/CrFwAppShutdownProc.h"
#include "AppStartUp/CrFwAppStartUpProc.h"
/* Include configuration files */
#include "CrFwAppSmUserPar.h"

/* Dummy state machine to be embedded in state START-UP of the Application State Machine */
FW_SM_INST_NOCPS(startUpEsmDesc, 1, 1, 0, 0)

/* Dummy state machine to be embedded in state NORMAL of the Application State Machine */
FW_SM_INST_NOCPS(normalEsmDesc, 1, 1, 0, 0)

/* Dummy state machine to be embedded in state RESET of the Application State Machine */
FW_SM_INST_NOCPS(resetEsmDesc, 1, 1, 0, 0)

/* ---------------------------------------------------------------------------------------------*/

FwSmDesc_t CrFwAppSmTestCasesGetStartUpEsm() {
	return &startUpEsmDesc;
}

FwSmDesc_t CrFwAppSmTestCasesGetNormalEsm()  {
	return &normalEsmDesc;
}

FwSmDesc_t CrFwAppSmTestCasesGetResetEsm()  {
	return &resetEsmDesc;
}
