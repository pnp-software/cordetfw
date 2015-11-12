/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the OutLoader Component (see <code>CrFwOutLoader.h</code>).
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
 * .
 * @verify Base Component SM Transition: IPS->CREATED
 * @verify Base Component SM Transition: CREATED->INITIALIZED
 * @verify Base Component SM Transition: INITIALIZED->CONFIGURED
 * @verify OutLoader Load Procedure
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutLoaderTestCase1();

#endif /* CRFW_OUTLOADER_TESTCASES_H_ */
