/**
 * @file CrPsEvtRepDisabledCmd.h
 * @ingroup Serv5
 * @ingroup InCmd
 *
 * @brief Implementation of TC(5,7) EvtRepDisabledCmd.
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

#ifndef CRPSSPCEVTREPDISABLEDCMD_H_
#define CRPSSPCEVTREPDISABLEDCMD_H_

#include <CrFwConstants.h>

/**
 * Start action of TC(5,7) EvtRepDisabledCmd.
 * Retrieve (5,8) report from OutFactory and set action outcome
 * to “success’ if retrieval succeeds. If the retrieval fails, generate
 * error report OUTFACTORY FAILED and set outcome of Start
 * Action to ’failed’
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtRepDisabledCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(5,7) EvtRepDisabledCmd.
 * Configure the (5,8) report with a destination equal to the source
 * of the (5,7) command, load it in the OutLoader, and set the
 * action outcome to ’completed’
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtRepDisabledCmdProgressAction(FwSmDesc_t smDesc);

/**
 * Termination action of TC(5,7) EvtRepDisabledCmd.
 * Set action outcome to ’success’
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtRepDisabledCmdTerminationAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSSPCEVTREPDISABLEDCMD_H */
