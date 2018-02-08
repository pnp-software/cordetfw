/**
 * @file
 * @ingroup crOpenIfGroup
 * Interface to the Application Reset Procedure.
 * The Application Reset Procedure is started by the Application
 * State Machine (see <code>CrFwAppSm.h</code>).
 * It executes while the state machine is in state RESET.
 * This procedure is responsible for resetting all
 * the application components and for performing any other reset action
 * for the application.
 * The Application Reset Procedure is entirely application-specific.
 * This header file declares a function to retrieve a pointer to the procedure
 * descriptor.
 * The implementation of this file provides an implementation of the procedure
 * and is therefore application-specific.
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

#ifndef CRFW_APP_RESET_PROC_H_
#define CRFW_APP_RESET_PROC_H_

#include "FwSmConstants.h"
#include "FwPrConstants.h"
#include "CrFwConstants.h"

/**
 * Retrieve the singleton instance of the Application Reset Procedure.
 * @return the singleton instance of the Application Reset Procedure.
 */
FwPrDesc_t CrFwAppSmGetAppResetProc();

#endif /* CRFW_APP_RESET_PROC_H_ */
