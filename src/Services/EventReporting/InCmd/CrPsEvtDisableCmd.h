/**
 * @file CrPsEvtDisableCmd.h
 * @ingroup Serv5
 * @ingroup InCmd
 *
 * @brief Implementation of TC(5,6) EvtDisableCmd.
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

#ifndef CRPSSPCEVTDISABLECMD_H_
#define CRPSSPCEVTDISABLECMD_H_

#include <CrFwConstants.h>

/**
 * Start action of TC(5,6) EvtDisableCmd.
 * Run the procedure Start Action of Multi-EID Command of
 * figure 10.1
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtDisableCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(5,6) EvtDisableCmd.
 * For each valid EID found by the Start Action of the command:
 * set the corresponding element of the array isEidEnabled to false
 * and then increment nDisabledEid x (’x’ is the severity level of
 * the EID). Set the action outcome to ’completed’.
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtDisableCmdProgressAction(FwSmDesc_t smDesc);

/**
 * Termination action of TC(5,6) EvtDisableCmd.
 * Set action outcome to ’success’
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtDisableCmdTerminationAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSSPCEVTDISABLECMD_H */
