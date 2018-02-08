/**
 * @file CrPsEvtRepDisabledRep.h
 * @ingroup Serv5
 * @ingroup OutCmp
 *
 * @brief Implementation of TM(5,8) EvtRepDisabledRep.
 *
 * @note This file was generated on 2017-09-19 12:36:09
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

#ifndef CRPSSPCEVTREPDISABLEDREP_H_
#define CRPSSPCEVTREPDISABLEDREP_H_

#include <CrFwConstants.h>

/**
 * Update action of TM(5,8) EvtRepDisabledRep.
 * Load the list of disabled event identifiers from arrays isEidEn-
 * abled1 to isEidEnabled4
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtRepDisabledRepUpdateAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSSPCEVTREPDISABLEDREP_H */
