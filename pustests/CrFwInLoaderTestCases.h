/**
 * @file CrFwInLoaderTestCases.h
 * @ingroup PUSTestsuite
 *
 * @brief Declaration of the test cases for the InLoader Component (see <code>CrFwInLoader.h</code>).
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

#ifndef CRFW_INLOADER_TESTCASES_H_
#define CRFW_INLOADER_TESTCASES_H_

#include "CrFwConstants.h"
#include "CrFwUserConstants.h"

/**
 * Test implementation of the function which checks the legality of a destination and
 * returns the re-routing destination (adaptation points A7.2.2-9 and A7.2.2-11).
 * This test implementation can be configured to return either zero (to signify that the argument
 * destination is invalid) or a positive integer (to represent a re-routing destination).
 * This function must conform to the prototype defined by <code>::CrFwInLoaderGetReroutingDest_t</code>.
 * @param pcktDest the packet destination.
 * @return the re-routing destination or zero if the argument destination is illegal.
 */
CrFwDestSrc_t CrFwInLoaderTestCaseGetReroutingDestination(CrFwDestSrc_t pcktDest);


#endif /* CRFW_INLOADER_TESTCASES_H_ */
