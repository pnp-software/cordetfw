/**
 * @file CrPsTestOnBoardConnection.h
 * @ingroup Serv17
 * @ingroup InCmd 
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

#ifndef CRPS_TEST_ONBOARD_CONNECTION_H
#define CRPS_TEST_ONBOARD_CONNECTION_H

#include "CrFwConstants.h"

/* global handles */
extern uint16_t timeOut_cnt;

/**
 * Start action of the Perform Connection Test in-coming command packet.
 * Set the action outcome to 'success'
 * @param smDesc the state machine descriptor
 */
void CrPsTestOnBoardConnectionStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of the Perform Connection Test in-coming command packet.
 * Load report (17,2); set the action outcome to 'completed'
 * @param smDesc the state machine descriptor
 */
void CrPsTestOnBoardConnectionProgressAction(FwSmDesc_t smDesc);

/**
 * Termination Action of the Perform Connection Test in-coming command packet.
 * Always generates outcome=1
 * @param smDesc the state machine descriptor
 */
void CrPsTestOnBoardConnectionTerminationAction(FwSmDesc_t smDesc);

#endif /* CRPS_TEST_ONBOARD_CONNECTION_H */

