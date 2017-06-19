/**
 * @file CrPsTestAreYouAliveConnection.h
 *
 * Declaration of the Perform Connection Test in-coming command packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#ifndef CRPS_TEST_AREYOUALIVE_CONNECTION_H
#define CRPS_TEST_AREYOUALIVE_CONNECTION_H

#include "CrFwConstants.h"

/**
 * ReadyCheck of the Perform Connection Test in-coming command packet.
 * Dummy that returns always TRUE
 * @param smDesc the state machine descriptor
 * @return always TRUE
 */
CrFwBool_t CrPsTestAreYouAliveConnectionReadyCheck(FwSmDesc_t smDesc);

/**
 * Start action of the Perform Connection Test in-coming command packet.
 * Set the action outcome to 'success'
 * @param smDesc the state machine descriptor
 */
void CrPsTestAreYouAliveConnectionStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of the Perform Connection Test in-coming command packet.
 * Load report (17,2); set the action outcome to 'completed'
 * @param smDesc the state machine descriptor
 */
void CrPsTestAreYouAliveConnectionProgressAction(FwSmDesc_t smDesc);

/**
 * Termination Action of the Perform Connection Test in-coming command packet.
 * Always generates outcome=1
 * @param smDesc the state machine descriptor
 */
void CrPsTestAreYouAliveConnectionTerminationAction(FwSmDesc_t smDesc);

/**
 * Abort Action of the Perform Connection Test in-coming command packet.
 * Always generates outcome=1
 * @param smDesc the state machine descriptor
 */
void CrPsTestAreYouAliveConnectionAbortAction(FwSmDesc_t smDesc);



#endif /* CRPS_TEST_AREYOUALIVE_CONNECTION_H */

