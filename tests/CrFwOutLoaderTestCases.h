/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the OutLoader Component (see <code>CrFwOutLoader.h</code>).
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

#ifndef CRFW_OUTLOADER_TESTCASES_H_
#define CRFW_OUTLOADER_TESTCASES_H_

#include "CrFwConstants.h"

/**
 * Check the configuration and operation of the OutLoader.
 * The following actions are performed in this test:
 * - The OutLoader is created and it is checked that it is in state CREATED.
 * - The OutLoader is created a second time and it is checked that the same instance as in
 *   the first creation operation is returned.
 * - The OutLoader is initialized and reset and it is checked that it is in state CONFIGURED.
 * - The instance identifier and the type identifier of the OutLoader is checked.
 * - The first OutManager is created and configured.
 * - The OutFactory is created and configured.
 * - An OutComponent is created and configured.
 * - An OutComponent is loaded into the OutLoader and it is checked that the OutLoader
 *   loads it into the first OutManager.
 * - The OutManager is filled so that its POCL becomes full
 * - An OutComponent is loaded into the OutLoader and it is checked that operation fails
 *   and that the OutComponent is released
 * .
 * @verify Base Component SM Transition: IPS->CREATED
 * @verify Base Component SM Transition: CREATED->INITIALIZED
 * @verify Base Component SM Transition: INITIALIZED->CONFIGURED
 * @verify OutLoader Load Procedure: success branch
 * @verify OutLoader Load Procedure: failure branch
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutLoaderTestCase1();

#endif /* CRFW_OUTLOADER_TESTCASES_H_ */
