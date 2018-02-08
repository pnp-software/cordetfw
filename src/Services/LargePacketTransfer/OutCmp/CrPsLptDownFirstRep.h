/**
 * @file CrPsLptDownFirstRep.h
 * @ingroup Serv13
 * @ingroup OutCmp
 *
 * @brief Implementation of TM(13,1) LptDownFirstRep.
 *
 * @note This file was generated on 2017-11-22 12:47:43
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

#ifndef CRPSLPTDOWNFIRSTREP_H_
#define CRPSLPTDOWNFIRSTREP_H_

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Enable check of TM(13,1) LptDownFirstRep.
 * Report is enabled if the LPT State Machine is in state DOWN_TRANSFER
 * \param smDesc The state machine descriptor.
 * \return The enable check result.
 */
CrFwBool_t CrPsLptDownFirstRepEnableCheck(FwSmDesc_t smDesc);

/**
 * Update action of TM(13,1) LptDownFirstRep.
 * Load the first part of the large packet from the LPT Buffer; set the
 * transaction identifier equal to largeMsgTransId ; set the partnumber equal
 * to partSeqNmb ; increment partSeqNmb ; and decrement lptRemSize by partSize
 * \param smDesc The state machine descriptor.
 */
void CrPsLptDownFirstRepUpdateAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSLPTDOWNFIRSTREP_H */
