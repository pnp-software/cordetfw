/**
 * @file
 * @ingroup CrTestSuiteGroup
 *
 * Default implementation of the time interface of <code>CrFwTime.h</code>.
 * The implementation of this interface is one of the adaptation points of the
 * CORDET Framework.
 * This file provides a default implementation which is primarily intended to
 * support testing.
 * It is expected that applications will provide their own implementation.
 * Application will therefore normally replace this file with their own file
 * providing their application-specific implementation.
 *
 * This implementation maintains an integer which is incremented by 1 every
 * time function <code>::CrFwGetCurrentTimeStamp</code> is called.
 * This function represents the "current time" and its value is returned
 * by the various time getter functions defined by this interface.
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#include <stdlib.h>
#include "CrFwConstants.h"
#include "CrFwTime.h"

/** The <code>::CrFwGetCurrentTime</code> increments this counter and then returns its value */
static CrFwTimeStamp_t dummyTime = 0;

/*-----------------------------------------------------------------------------------------*/
CrFwTimeStamp_t CrFwGetCurrentTimeStamp() {
	dummyTime++;
	return dummyTime;
}

/*-----------------------------------------------------------------------------------------*/
CrFwTime_t CrFwGetCurrentTime() {
	return dummyTime;
}

/*-----------------------------------------------------------------------------------------*/
CrFwTimeCyc_t CrFwGetCurrentCycTime() {
	return dummyTime;
}

/*-----------------------------------------------------------------------------------------*/
CrFwTimeStamp_t CrFwStdTimeToTimeStamp(CrFwTime_t stdTime) {
	return (CrFwTimeStamp_t) stdTime;
}

/*-----------------------------------------------------------------------------------------*/
CrFwTime_t CrFwTimeStampToStdTime(CrFwTimeStamp_t timeStamp) {
	return (CrFwTime_t) timeStamp;
}



