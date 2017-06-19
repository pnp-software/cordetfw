/**
 * @file CrPsTestAreYouAliveConnectionRep.h
 *
 * Declaration of the Perform Connection Test in-coming command packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#ifndef CRPS_TEST_AREYOUALIVE_CONNECTION_REP_H
#define CRPS_TEST_AREYOUALIVE_CONNECTION_REP_H

#include "FwProfile/FwSmCore.h"
#include "CrFwConstants.h"


/**
 * EnableCheck of the Perform Connection Test in-coming command packet.
 * Dummy that returns always TRUE
 * @param smDesc the state machine descriptor
 * @return always TRUE
 */
CrFwBool_t CrPsTestAreYouAliveConnectionRepEnableCheck(FwSmDesc_t smDesc);

/**
 * ReadyCheck of the Perform Connection Test in-coming command packet.
 * Dummy that returns always TRUE
 * @param smDesc the state machine descriptor
 * @return always TRUE
 */
CrFwBool_t CrPsTestAreYouAliveConnectionRepReadyCheck(FwSmDesc_t smDesc);

/**
 * RepeatCheck of the Perform Connection Test in-coming command packet.
 * Dummy that returns always FALSE
 * @param smDesc the state machine descriptor
 * @return always FALSE
 */
CrFwBool_t CrPsTestAreYouAliveConnectionRepRepeatCheck(FwSmDesc_t smDesc);

/**
 * Update action of the Perform Connection Test in-coming command packet.
 * Always generates outcome=1
 * @param smDesc the state machine descriptor
 */
void CrPsTestAreYouAliveConnectionRepUpdateAction(FwSmDesc_t smDesc);



#endif /* CRPS_TEST_AREYOUALIVE_CONNECTION_REP_H */

