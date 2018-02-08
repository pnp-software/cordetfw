/**
 * @file CrPsHkRep.h
 * @ingroup Serv3
 * @ingroup OutCmp
 *
 * @brief Declaration of the Periodic Housekeeping Report (3,25) or Periodic Diagnostic Report (3,26) out-going report packet.
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

#ifndef CRPS_HK_HKREP_H
#define CRPS_HK_HKREP_H

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Enable check of the Periodic Housekeeping Report (3,25) out-going report packet.
 * The enable status is read from the isEnabled field of the Report Definition corresponding to the report’s SID
 * @param smDesc the state machine descriptor
 * @return the enable check result
 */
CrFwBool_t CrPsHkRepEnableCheck(FwSmDesc_t smDesc);

/**
 * Ready check of the Periodic Housekeeping Report (3,25) out-going report packet.
 * Run the procedure Ready Check of HkRep Report of figure 9.5
 * @param smDesc the state machine descriptor
 * @return the ready check result
 */
CrFwBool_t CrPsHkRepReadyCheck(FwSmDesc_t smDesc);

/**
 * Update action of the Periodic Housekeeping Report (3,25) out-going report packet.
 * Load the value of the simply-commutated data items from the data pool 
 * and that of the super-commutated data items from the Sampling Buffer 
 * associated to the report’s SID according to the Report Definition
 * @param smDesc the state machine descriptor
 */
void CrPsHkRepUpdateAction(FwSmDesc_t smDesc);

#endif /* CRPS_HK_HKREP_H */