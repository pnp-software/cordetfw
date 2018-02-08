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
 * This file is part of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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
