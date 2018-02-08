/**
 * @file
 * @ingroup crConfigGroup
 * User-modifiable parameters for the InLoader components (see <code>CrFwInLoader.h</code>).
 * This file defines all the user-modifiable parameters for the InLoader.
 * Users will normally have to modify this file as part of the framework instantiation process.
 *
 * The parameters defined in this file determine the configuration of the InLoader singleton
 * component.
 * The value of these parameters cannot be changed dynamically.
 *
 * The default values defined in this file are those used for the testing of the
 * CORDET Framework.
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

#ifndef CR_FW_INLOADER_USERPAR_H_
#define CR_FW_INLOADER_USERPAR_H_

#include "InLoader/CrFwInLoader.h"
#include "CrFwInLoaderTestCases.h"

/**
 * The function which determines the re-routing destination of a packet.
 * This function must conform to the prototype defined by <code>::CrFwInLoaderGetReroutingDest_t</code>.
 * The function specified here is the re-routing destination function used for the Test Suite.
 */
#define CR_FW_INLOADER_DET_REROUTING_DEST CrFwInLoaderTestCaseGetReroutingDestination

/**
 * The function which determines the InManager into which an InReport or InCommand must be loaded.
 * This function must conform to the prototype defined by <code>::CrFwInLoaderGetInManager_t</code>.
 * The function specified here is the default re-routing destination function defined in
 * <code>CrFwInLoader.h</code>.
 */
#define CR_FW_INLOADER_SEL_INMANAGER CrFwInLoaderDefGetInManager

#endif /* CR_FW_INLOADER_USERPAR_H_ */
