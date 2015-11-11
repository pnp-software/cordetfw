/**
 * @file
 * @ingroup baseCmpGroup
 * Component Reset Procedure (CRP) for the Base Component.
 * The CRP is one of the procedures which implement the behaviour of the
 * Base Component (see <code>CrFwBaseCmp.h</code>).
 * The CRP is shown as an activity diagram in the right-hand side of the
 * figure below.
 *
 * The CRP (like the Base Component) is a singleton.
 * This header file gives access to the singleton instance of the CRP.
 * This header file also gives access to the functions which implement the
 * two actions of the CRP.
 * These actions represent adaptation points of the framework and they are
 * therefore made externally accessible so that derived component may override
 * them.
 *
 * All components derived from the Base Component need an own version of
 * the CRP.
 * They obtain it by extending the CRP instance defined in this file.
 * @image html InitializationAndReset.png
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

#ifndef CRFW_RESET_PROC_H_
#define CRFW_RESET_PROC_H_

#include "FwProfile/FwSmConstants.h"
#include "FwProfile/FwPrConstants.h"
#include "CrFwConstants.h"

/**
 * Retrieve the singleton instance of the CRP.
 * This function returns the descriptor of the CRP.
 * Note that no data are attached to the descriptor as it is returned by this
 * function.
 * The CRP descriptor returned by this function is therefore not ready to be
 * executed.
 * It can only be executed after the procedure data have been loaded into it.
 * @return the descriptor of the CRP or NULL if the procedure could not be created.
 */
FwPrDesc_t CrFwCmpGetResetProc();

/**
 * Function which performs the default Configuration Check of the CRP.
 * This function implements one of the actions of the CRP.
 * In general, the Configuration Check for a component checks that all
 * parameters required for the component configuration have legal values.
 *
 * This function assumes the procedure data to be of type <code>::CrFwCmpData_t</code>.
 * It uses the <code>outcome</code> field of this data structure to store the
 * outcome of the configuration check.
 *
 * This function implements the Configuration Check for the Base Component
 * which always returns an outcome of "check successful" (i.e. always sets the
 * outcome check to TRUE).
 *
 * This action is an adaptation point for the framework.
 * Components which extend the Base Component (and which therefore must also extend
 * the CRP) may want to override this function to implement their own configuration
 * behaviour).
 * @param prDesc the CIP descriptor
 */
void CrFwBaseCmpDefConfigCheck(FwPrDesc_t prDesc);

/**
 * Function which performs the default Configuration Action of the CRP.
 * This function implements one of the actions of the CRP.
 * In general, the Configuration Action for a component initializes all data structures
 * required by the component and performs other configuration actions as required.
 * The configuration action has an outcome: it can either succeed or it can fail.
 *
 * This function assumes the procedure data to be of type <code>::CrFwCmpData_t</code>.
 * It uses the <code>outcome</code> field of this data structure to store the
 * outcome of the configuration action (a value of "true" means that the configuration
 * action was successful).
 *
 * This function implements the Configuration Action for the Base Component
 * which does nothing and always returns an outcome of "action successful" (i.e.
 * always sets the outcome check to TRUE).
 *
 * This action is an adaptation point of the framework.
 * Components which extend the Base Component (and which therefore must also extend
 * the CRP) may want to override this function to implement their own configuration
 * behaviour).
 * @param prDesc the CRP descriptor
 */
void CrFwBaseCmpDefConfigAction(FwPrDesc_t prDesc);

#endif /* CRFW_RESET_PROC_H_ */
