/**
 * @file
 * @ingroup baseCmpGroup
 * Dummy Component Execution Procedure (CEP) for the Base Component.
 * The CEP is one of the procedures which implement the behaviour of the
 * Base Component (see <code>CrFwBaseCmp.h</code>).
 * This procedure is an adaptation point in the Base Component.
 * The implementation provided in this file is the default defined
 * at the level of the Base Component.
 * Components which extend the Base Component may override it and define
 * their own implementation.
 *
 * The CORDET Framework does not define a generic CEP.
 * This implementation therefore defines a dummy CEP which can be used
 * by components which do not need a CEP.
 * This dummy CEP (see figure below) has one single action node which
 * executes a dummy action every time the procedure is executed.
 * The dummy action can be overridden.
 *
 * The Dummy CEP (like the Base Component) is a singleton.
 * This header file gives access to the singleton instance of the Dummy CEP.
 *
 * @image html DummyExecution.png
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

#ifndef CRFW_DUMMY_EXEC_PROC_H_
#define CRFW_DUMMY_EXEC_PROC_H_

#include "FwSmConstants.h"
#include "FwPrConstants.h"
#include "CrFwConstants.h"

/**
 * Retrieve the singleton instance of the Dummy CEP.
 * This function returns the descriptor of the Dummy CEP.
 * Note that no data are attached to the descriptor as it is returned by this
 * function.
 * @return the descriptor of the CEP or NULL if the procedure could not be created.
 */
FwPrDesc_t CrFwBaseCmpGetDummyExecProc();

/**
 * Dummy action executed in the single node of the Dummy Execution Procedure.
 * This dummy action returns without doing anything.
 * @param prDesc the procedure descriptor
 */
void CwFwBaseCmpDummyExecAction(FwPrDesc_t prDesc);

#endif /* CRFW_DUMMY_EXEC_PROC_H_ */
