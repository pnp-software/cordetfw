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

#ifndef CRFW_APP_RESET_PROC_H_
#define CRFW_APP_RESET_PROC_H_

#include "FwProfile/FwSmConstants.h"
#include "FwProfile/FwPrConstants.h"
#include "CrFwConstants.h"

/**
 * Retrieve the singleton instance of the Application Reset Procedure.
 * @return the singleton instance of the Application Reset Procedure.
 */
FwPrDesc_t CrFwAppSmGetAppResetProc();

#endif /* CRFW_APP_RESET_PROC_H_ */
