/**
 * @file CrPsHkRepStructRep.h
 * @ingroup Serv3
 * @ingroup OutCmp 
 *
 * @brief Declaration of the Housekeeping Structure Report (3,10) or Disgnostic Structure Report (3,12) out-going report packet.
 *
 * @author PnP Generator
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

#ifndef CRPS_HK_REPSTRUCT_REP_H
#define CRPS_HK_REPSTRUCT_REP_H

#include <FwSmCore.h>
#include <CrFwConstants.h>


/**
 * Update action of the Housekeeping Structure Report (3,10) out-going report packet.
 * Load the SID definition from the RDL
 * @param smDesc the state machine descriptor
 */
void CrPsHkRepStructRepUpdateAction(FwSmDesc_t smDesc);

#endif /* CRPS_HK_REPSTRUCT_REP_H */