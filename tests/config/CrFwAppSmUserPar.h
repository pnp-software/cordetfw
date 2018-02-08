/**
 * @file
 * @ingroup crConfigGroup
 * User-modifiable parameters for the Application State Machine (see <code>CrFwAppSm.h</code>).
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#ifndef CRFW_APPSM_USERPAR_H_
#define CRFW_APPSM_USERPAR_H_

#include "CrFwAppSmTestCases.h"

/**
 * The pointer to the state machine embedded in state START-UP.
 * The value of this constant must be either NULL (if no state machine is embedded in
 * START-UP) or a pointer of type <code>FwSmDesc_t</code>.
 * The default value for this adaptation point is NULL.
 *
 * The value of the adaptation point defined in this file is the one used for the test cases
 * of <code>CrFwAppSmTestCases.h</code>.
 */
#define CR_FW_APPSM_STARTUP_ESM CrFwAppSmTestCasesGetStartUpEsm()

/**
 * The pointer to the state machine embedded in state NORMAL.
 * The value of this constant must be either NULL (if no state machine is embedded in
 * NORMAL) or a pointer of type <code>FwSmDesc_t</code>.
 * The default value for this adaptation point is NULL.
 *
 * The value of the adaptation point defined in this file is the one used for the test cases
 * of <code>CrFwAppSmTestCases.h</code>.
 */
#define CR_FW_APPSM_NORMAL_ESM CrFwAppSmTestCasesGetNormalEsm()

/**
 * The pointer to the state machine embedded in state RESET.
 * The value of this constant must be either NULL (if no state machine is embedded in
 * RESET) or a pointer of type <code>FwSmDesc_t</code>.
 * The default value for this adaptation point is NULL.
 *
 * The value of the adaptation point defined in this file is the one used for the test cases
 * of <code>CrFwAppSmTestCases.h</code>.
 */
#define CR_FW_APPSM_RESET_ESM CrFwAppSmTestCasesGetResetEsm()

/**
 * The pointer to the state machine embedded in state SHUTDOWN.
 * The value of this constant must be either NULL (if no state machine is embedded in
 * SHUTDOWN) or a pointer of type <code>FwSmDesc_t</code>.
 * The default value for this adaptation point is NULL.
 *
 * The value of the adaptation point defined in this file is the one used for the test cases
 * of <code>CrFwAppSmTestCases.h</code>.
 */
#define CR_FW_APPSM_SHUTDOWN_ESM NULL

#endif /* CRFW_APPSM_USERPAR_H_ */
