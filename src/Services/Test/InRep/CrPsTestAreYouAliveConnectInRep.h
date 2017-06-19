/**
 * @file CrPsTestAreYouAliveConnectInRep.h
 *
 * Declaration of the Are-You-Alive Test in-coming report packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#ifndef CRPS_TEST_AREYOUALIVE_CONNECT_INREP_H
#define CRPS_TEST_AREYOUALIVE_CONNECT_INREP_H

/*#include "FwProfile/FwSmCore.h"*/
#include "CrFwConstants.h"

/**
 * Validity check of the Are-YouAlive Test in-coming report packet.
 * Compute the CRC for the report and returns true if the CRC is correct and false otherwise.
 * @param smDesc the state machine descriptor
 * @return the validity check result
 */
CrFwBool_t CrPsTestAreYouAliveConnectInRepValidityCheck(FwPrDesc_t prDesc);

/**
 * Update action of the Are-YouAlive Test in-coming report packet.
 * @param prDesc the procedure descriptor
 */
void CrPsTestAreYouAliveConnectInRepUpdateAction(FwPrDesc_t prDesc);

#endif /* CRPS_TEST_AREYOUALIVE_CONNECT_INREP_H */

