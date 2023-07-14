/**
 * @file
 * @ingroup baseCmpGroup
 * Component Initialization Procedure (CIP) for the Base Component.
 * The CIP is one of the procedures which implement the behaviour of the
 * Base Component (see <code>CrFwBaseCmp.h</code>).
 * The CIP is shown as an activity diagram in the left-hand side of the
 * figure below.
 *
 * The CIP (like the Base Component) is a singleton.
 * This header file gives access to the singleton instance of the CIP.
 * This header file also gives access to the functions which implement the
 * two actions of the CIP.
 * These actions represent adaptation points of the framework and they are
 * therefore made externally accessible so that derived component may override
 * them.
 *
 * All components derived from the Base Component need an own version of
 * the CIP.
 * They obtain it by extending the CIP instance defined in this file.
 * @image html InitializationAndReset.png
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

#ifndef CRFW_INIT_PROC_H_
#define CRFW_INIT_PROC_H_

#include "FwSmConstants.h"
#include "FwPrConstants.h"
#include "CrFwConstants.h"

/**
 * Retrieve the singleton instance of the CIP.
 * This function returns the descriptor of the CIP.
 * Note that no data are attached to the descriptor as it is returned by this
 * function.
 * The CIP descriptor returned by this function is therefore not ready to be
 * executed.
 * It can only be executed after the procedure data have been loaded into it.
 * @return the descriptor of the CIP or NULL if the procedure could not be created.
 */
FwPrDesc_t CrFwCmpGetInitProc();

/**
 * Function which performs the default Initialization Check of the CIP.
 * This function implements one of the actions of the CIP.
 * In general, the Initialization Check for a component checks that all
 * parameters required for the component initialization have legal values.
 *
 * The Initialization Check has an outcome.
 * This function assumes the procedure data to be of type <code>::CrFwCmpData_t</code>.
 * It uses the <code>outcome</code> field of this data structure to store the
 * outcome of the initialization check.
 * If the outcome of the Initialization Check is "check successful", then the
 * outcome field is set equal to 1.
 * If the outcome of the Initialization Check is "check failed", then the
 * outcome field is set equal to 0.
 *
 * This function implements the Initialization Check for the Base Component which
 * always returns an outcome of "check successful" (i.e. always sets the outcome field to 1).
 *
 * This action is an adaptation point for the framework.
 * Components which extend the Base Component (and which therefore must also extend
 * the CIP) may want to override this function to implement their own initialization
 * behaviour).
 * @param prDesc the CIP descriptor
 */
void CrFwBaseCmpDefInitCheck(FwPrDesc_t prDesc);

/**
 * Function which performs the default Initialization Action of the CIP.
 * This function implements one of the actions of the CIP.
 * In general, the Initialization Action for a component creates all data structures
 * required by the component and performs other initialization actions as required.
 *
 * The Initialization Action has an outcome.
 * This function assumes the procedure data to be of type <code>::CrFwCmpData_t</code>.
 * It uses the <code>outcome</code> field of this data structure to store the
 * outcome of the initialization action.
 * If the outcome of the Initialization Action is "action successful", then the
 * outcome field is set equal to 1.
 * If the outcome of the Initialization Action is "action failed", then the
 * outcome field is set equal to 0.
 *
 * This function assumes the procedure data to be of type <code>::CrFwCmpData_t</code>.
 * It uses the <code>outcome</code> field of this data structure to store the
 * outcome of the initialization action (a value of "true" means that the
 * initialization action was successful).
 *
 * This function implements the Initialization Action for the Base Component
 * which does nothing and always returns an outcome of "action successful" (i.e.
 * always sets the outcome field to 1).
 *
 * This action is an adaptation point of the framework.
 * Components which extend the Base Component (and which therefore must also extend
 * the CIP) may want to override this function to implement their own initialization
 * behaviour).
 * @param prDesc the CIP descriptor
 */
void CrFwBaseCmpDefInitAction(FwPrDesc_t prDesc);

#endif /* CRFW_INIT_PROC_H_ */
