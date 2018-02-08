/**
 * @file CrPsTestAreYouAliveConnectionRep.h
 * @ingroup Serv17
 * @ingroup OutCmp 
 *
 * @brief Declaration of the Perform Connection Test in-coming command packet.
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

#ifndef CRPS_TEST_AREYOUALIVE_CONNECTION_REP_H
#define CRPS_TEST_AREYOUALIVE_CONNECTION_REP_H

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Update action of the Perform Connection Test in-coming command packet.
 * Always generates outcome=1
 * @param smDesc the state machine descriptor
 */
void CrPsTestAreYouAliveConnectionRepUpdateAction(FwSmDesc_t smDesc);

#endif /* CRPS_TEST_AREYOUALIVE_CONNECTION_REP_H */

