/**
 * @file
 * @ingroup outMngGroup
 * Definition of the OutLoader component.
 *
 * After a user application has obtained an OutComponent component from an OutFactory,
 * it loads it into the OutLoader.
 * This component is responsible for selecting the appropriate OutManager to process
 * the out-going command or report.
 * For this purpose, the OutLoader maintains a list of all OutManagers in an application
 * (the List of OutManagers or LOM).
 *
 * The OutLoader is defined as an extension of the Base Component (see <code>CrFwBaseCmp.h</code>).
 * The OutLoader component offers one operation – the Load operation – to load an OutComponent
 * into an OutLoader.
 * This operation executes the behaviour shown in the figure below.
 *
 * When the Load operation is called, the OutLoader decides to which OutManager in the LOM to load
 * an OutComponent.
 * The policy for selecting the OutManager in the LOM is an adaptation point.
 * After the OutComponent is loaded into the selected OutManager, the procedure may activate
 * the selected OutManager (i.e. it may release the thread which is controlling the execution of
 * the selected OutManager).
 * This is useful where there is a need to process the out-going command or report as soon as
 * it is loaded into the OutManager (since the command or report is only processed when the
 * OutManager is executed).
 *
 * <b>Mode of Use of an OutLoader Component</b>
 *
 * The configuration of the OutLoader components is defined statically in
 * <code>CrFwOutLoaderUserPar.h</code>.
 *
 * The OutLoader component is created with function <code>::CrFwOutLoaderMake</code>.
 * After being created, the OutLoader must be initialized and reset.
 * This is done with functions <code>::CrFwCmpInit</code> and <code>::CrFwCmpReset</code>.
 * Nominally, after being initialized and reset the OutLoader State Machine should be
 * in state CONFIGURED (this can be checked by verifying that function <code>FwSmGetCurState</code>
 * returns CR_FW_BASE_STATE_CONFIGURED).
 *
 * Note that the OutLoader is a singleton and an application can only have one instance of
 * an OutLoader.
 *
 * An OutLoader offers a Load operation (<code>::CrFwOutLoaderLoad</code>) through which
 * an OutComponent can be loaded into an OutManager.
 * This operation is normally called by a user component after it has configured an OutComponent
 * and when it wishes the OutComponent to be sent to its destination.
 *
 * The OutLoader autonomously selects the OutManager to which an OutComponent should be loaded.
 * The selection algorithm is an adaptation point for the OutLoader.
 *
 * By default, the initialization, reset and shutdown operations are the same as on the
 * Base Component but these operations are implemented as adaptation points so that the
 * user has a chance to use them to initialize or reset the data structures which are used
 * to control the selection of the OutManager where an out-going command or report is loaded.
 *
 * @image html OutLoaderLoad.png
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

#ifndef CRFW_OUT_LOADER_H_
#define CRFW_OUT_LOADER_H_

#include "FwProfile/FwSmConstants.h"
#include "FwProfile/FwPrConstants.h"
#include "Pckt/CrFwPcktQueue.h"
#include "CrFwConstants.h"

/**
 * Type for a pointer to a function implementing the OutManager Selection Operation.
 * The OutManager Selection Operation is one of the adaptation points of the framework.
 * A function which implements this operation takes an OutComponent as argument and returns
 * the OutManager where the OutComponent should be loaded.
 */
typedef FwSmDesc_t (*CrFwOutManagerSelect_t)(FwSmDesc_t outCmp);

/**
 * Type for a pointer to a function implementing the OutManager Activation Operation.
 * The OutManager Activation Operation is one of the adaptation points of the framework.
 * This function can be used to activate an OutManager.
 * An OutManager is activated by releasing the thread which controls its execution.
 */
typedef void (*CrFwOutManagerActivate_t)(FwSmDesc_t outManager);

/**
 * Factory function to retrieve the OutLoader State Machine instance.
 * The first time this function is called, it creates the OutLoader instance.
 * Subsequent calls returns the same instance.
 *
 * The first time this function is called, it returns the OutLoader
 * State Machine which has been started but which still needs to be initialized and
 * configured.
 * @return the descriptor of the OutLoader State Machine or NULL
 * if the state machine could not be created.
 */
FwSmDesc_t CrFwOutLoaderMake();

/**
 * Load an OutComponent into its OutManager.
 * This function runs the procedure shown in the figure below.
 * The procedure has two adaptation points which are defined by specifying two functions
 * in <code>CrFwOutLoaderUserPar.h</code>.
 *
 * @image html OutLoaderLoad.png
 * @param outCmp the descriptor of the OutComponent to be loaded in the OutManager
 */
void CrFwOutLoaderLoad(FwSmDesc_t outCmp);

/**
 * Default implementation of the OutManager Selection Operation.
 * This implementation always returns the first OutManager (i.e. the OutManager returned
 * by <code>::CrFwOutManagerMake</code> when it is called with an argument equal
 * to zero).
 * @param outCmp the descriptor of the OutComponent loaded into the OutLoader (this
 * argument is not used in this implementation)
 * @return the first OutManager
 */
FwSmDesc_t CrFwOutLoaderDefOutManagerSelect(FwSmDesc_t outCmp);

/**
 * Default implementation of the OutManager Activation Operation.
 * This implementation returns without doing anything.
 * @param outManager the descriptor of the OutManager to be activated (this
 * argument is not used in this implementation)
 */
void CrFwOutLoadDefOutManagerActivate(FwSmDesc_t outManager);

#endif /* CRFW_OUT_LOADER_H_ */
