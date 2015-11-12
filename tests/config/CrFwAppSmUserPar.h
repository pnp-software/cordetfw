/**
 * @file
 * @ingroup crConfigGroup
 * User-modifiable parameters for the Application State Machine (see <code>CrFwAppSm.h</code>).
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
