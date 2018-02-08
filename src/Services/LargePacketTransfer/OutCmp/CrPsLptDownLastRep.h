/**
 * @file CrPsLptDownLastRep.h
 * @ingroup Serv13
 * @ingroup OutCmp
 *
 * @brief Implementation of TM(13,3) LptDownLastRep.
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
 
#ifndef CRPSLPTDOWNLASTREP_H_
#define CRPSLPTDOWNLASTREP_H_

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Enable check of TM(13,3) LptDownLastRep.
 * Report is enabled if the LPT State Machine is in state DOWN_TRANSFER
 * \param smDesc The state machine descriptor.
 * \return The enable check result.
 */
CrFwBool_t CrPsLptDownLastRepEnableCheck(FwSmDesc_t smDesc);

/**
 * Update action of TM(13,3) LptDownLastRep.
 * Load the last part of the large packet from the LPT Buffer, set the
 * transaction identifier equal to largeMsgTransId; set the partnumber equal
 * to partSeqNmb
 * \param smDesc The state machine descriptor.
 */
void CrPsLptDownLastRepUpdateAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSLPTDOWNLASTREP_H */
