/**
 * @file CrPsTestAreYouAliveConnectInRep.h
 * @ingroup Serv17
 * @ingroup InRep 
 *
 * @brief Declaration of the Are-You-Alive Test in-coming report packet.
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

#ifndef CRPS_TEST_AREYOUALIVE_CONNECT_INREP_H
#define CRPS_TEST_AREYOUALIVE_CONNECT_INREP_H

/*#include "FwProfile/FwSmCore.h"*/
#include "CrFwConstants.h"

/**
 * Update action of the Are-YouAlive Test in-coming report packet.
 * @param prDesc the procedure descriptor
 */
void CrPsTestAreYouAliveConnectInRepUpdateAction(FwPrDesc_t prDesc);

#endif /* CRPS_TEST_AREYOUALIVE_CONNECT_INREP_H */

