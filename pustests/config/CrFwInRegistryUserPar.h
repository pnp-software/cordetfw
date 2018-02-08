/**
 * @file CrFwInRegistryUserPar.h
 * @ingroup PUSTestsuite
 * @ingroup PUSTestconfig 
 *
 * @brief User-modifiable parameters for the InRegistry component (see <code>CrFwInRegistry.h</code>).
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

#ifndef CRFW_INREGISTRY_USERPAR_H_
#define CRFW_INREGISTRY_USERPAR_H_

/**
 * The maximum number of commands or reports which can be tracked by the InRegistry.
 * This constant must be smaller than the range of <code>::CrFwTrackingIndex_t</code>.
 */
#define CR_FW_INREGISTRY_N 64

#endif /* CRFW_INREGISTRY_USERPAR_H_ */
