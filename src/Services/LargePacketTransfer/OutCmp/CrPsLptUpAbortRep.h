/**
 * @file CrPsLptUpAbortRep.h
 * @ingroup Serv13
 * @ingroup OutCmp
 *
 * @brief Implementation of TM(13,16) LptUpAbortRep.
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

#ifndef CRPSLPTUPABORTREP_H_
#define CRPSLPTUPABORTREP_H_

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Update action of TM(13,16) LptUpAbortRep.
 * The large message transaction identifier is taken from parameter
 * largeMsgTransId and the failure reason is read from variable lptFailCode.
 * \param smDesc The state machine descriptor.
 */
void CrPsLptUpAbortRepUpdateAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSLPTUPABORTREP_H */
