/**
 * @file
 * @ingroup crOpenIfGroup
 * Interface to the Application Start-Up Procedure.
 * The Application Start-Up Procedure is started by the Application
 * State Machine (see <code>CrFwAppSm.h</code>).
 * It executes while the state machine is in state START_UP.
 * This procedure is responsible for creating, initializing and configuring all
 * the application components and for performing any other initialization action
 * for the application.
 * The Application Start-Up Procedure is entirely application-specific.
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

#ifndef CRFW_APP_START_UP_PROC_H_
#define CRFW_APP_START_UP_PROC_H_

#include "FwSmConstants.h"
#include "FwPrConstants.h"
#include "CrFwConstants.h"

/**
 * Retrieve the singleton instance of the Application Start-Up Procedure.
 * @return the singleton instance of the Application Start-Up Procedure.
 */
FwPrDesc_t CrFwAppSmGetAppStartUpProc();

#endif /* CRFW_APP_START_UP_PROC_H_ */
