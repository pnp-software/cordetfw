/**
 * @file CrFwInManagerUserPar.h
 * @ingroup PUSTestsuite
 * @ingroup PUSTestconfig 
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
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 *
 * last modification: 22.01.2018
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
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
#define CR_FW_INMANAGER_PCRLSIZE {30,4,5}

#endif /* CR_FW_INMANAGER_USERPAR_H_ */
