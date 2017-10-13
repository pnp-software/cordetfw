/**
 * @file
 * @ingroup crConfigGroup
 * User-modifiable parameters for the InManager components (see <code>CrFwInManager.h</code>).
 * This file defines all the user-modifiable parameters for the InManager.
 * Users will normally have to modify this file as part of the framework instantiation process.
 *
 * The parameters defined in this file determine the configuration of the InManager Components.
 * The value of these parameters cannot be changed dynamically.
 *
 * The default values defined in this file are those used for the testing of the
 * CORDET Framework.
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

#ifndef CR_FW_INMANAGER_USERPAR_H_
#define CR_FW_INMANAGER_USERPAR_H_

/**
 * The number of InManager components in the application.
 * The value of this constant must be smaller than the range of the <code>::CrFwCounterU1_t</code>
 * integer type.
 *
 * The number of InManager components defined in this file is the one used for the test cases
 * of <code>CrFwInManagerTestCases.h</code>.
 */
#define CR_FW_NOF_INMANAGER 3

/**
 * The sizes of the Pending Command/Report List (PCRL) of the InManager components.
 * Each InManager has one PCRL.
 * This constant defines the size of the PCRL of the i-th InManager.
 * The size of a PCRL must be a positive integer (i.e. it is not legal
 * to define a zero-size PCRL) in the range of the <code>#CrFwCounterU2_t</code> type.
 *
 * The PCRL sizes defined in this file are those used for the test cases
 * of <code>CrFwInManagerTestCases.h</code>.
 */
#define CR_FW_INMANAGER_PCRLSIZE {3,4,5}

#endif /* CR_FW_INMANAGER_USERPAR_H_ */
