/**
 * @file CrFwInLoaderTestCases.c
 * @ingroup PUSTestsuite
 *
 * @brief Implementation of test cases for InLoader component.
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

#include <stdio.h>
#include <stdlib.h>
#include "CrFwInLoaderTestCases.h"
#include "CrFwRepInCmdOutcomeStub.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include framework files */
#include "InRegistry/CrFwInRegistry.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "InRep/CrFwInRep.h"
#include "InCmd/CrFwInCmd.h"
#include "InStream/CrFwInStream.h"
#include "OutStream/CrFwOutStream.h"
#include "InFactory/CrFwInFactory.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include configuration files */
#include "CrFwInRegistryUserPar.h"
#include "CrFwInLoaderUserPar.h"
#include "CrFwInStreamStub.h"
#include "CrFwOutStreamStub.h"
#include "CrFwRepErrStub.h"
#include "CrFwInFactoryUserPar.h"
#include "CrFwOutFactoryUserPar.h"
#include "CrFwCmpData.h"
#include "CrFwRepInCmdOutcome.h"

/** Return value of function <code>CrFwInLoaderDefGetReroutingDestination</code>. */
static CrFwDestSrc_t reroutingDest = 0;

/* ---------------------------------------------------------------------------------------------*/
CrFwDestSrc_t CrFwInLoaderTestCaseGetReroutingDestination(CrFwDestSrc_t pcktDest) {
	(void)(pcktDest);
	return reroutingDest;
}

