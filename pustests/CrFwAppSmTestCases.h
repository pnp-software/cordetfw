/**
 * @file CrFwAppSmTestCases.h
 * @ingroup PUSTestsuite
 * 
 * @brief Declaration of the test cases for the Application State Machine (see <code>CrFwAppSm.h</code>).
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

#ifndef CRFW_APPSM_TESTCASES_H_
#define CRFW_APPSM_TESTCASES_H_

#include "CrFwConstants.h"


/**
 * Return the dummy state machine to be embedded in state START-UP of the Application
 * State Machine.
 * @return the dummy state machine to be embedded in state START-UP of the Application
 * State Machine.
 */
FwSmDesc_t CrFwAppSmTestCasesGetStartUpEsm();

/**
 * Return the dummy state machine to be embedded in state NORMAL of the Application
 * State Machine.
 * @return the dummy state machine to be embedded in state NORMAL of the Application
 * State Machine.
 */
FwSmDesc_t CrFwAppSmTestCasesGetNormalEsm();

/**
 * Return the dummy state machine to be embedded in state RESET of the Application
 * State Machine.
 * @return the dummy state machine to be embedded in state RESET of the Application
 * State Machine.
 */
FwSmDesc_t CrFwAppSmTestCasesGetResetEsm();

#endif /* CRFW_APPSM_TESTCASES_H_ */
