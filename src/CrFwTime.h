/**
 * @file
 * @ingroup crOpenIfGroup
 *
 * Interface through which framework components access the current time.
 * Framework component need access to the current time to time-stamp out-going
 * command and report packets.
 *
 * This interface recognizes three formats for the application time:
 * - The "standard format" where the time is expressed as a float representing
 *   the fractional number of time units elapsed since some specific event
 * - The "time-stamp format" used in the time-stamp of the commands and reports
 * - The "cycle format" where the time is expressed as an integer number
 *   of cycle elapsed since some specific event (e.g. the latest application start)
 * .
 * This interface offers functions to retrieve the current time in all three formats
 * and it offers function to convert times between standard and time-stamp format.
 *
 * All applications must support the time-stamp format (because this is needed for
 * the time-stamping of commands and reports) but support for the other
 * two time formats is optional.
 *
 * The implementation of this interface is entirely application-specific.
 * A simple default implementation is provided in <code>CrFwTime.c</code>.
 * This default implementation is primarily intended for testing and demonstration
 * purposes.
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

#ifndef CRFW_TIME_H_
#define CRFW_TIME_H_

/* Include Framework Files */
#include "CrFwConstants.h"
/* Include Configuration Files */
#include "CrFwUserConstants.h"

/**
 * Return the current application time in standard format.
 * If the host application does not support this time format, then this function
 * is implemented to return zero.
 * @return the current time in standard format or zero if this format is not supported.
 */
CrFwTime_t CrFwGetCurrentTime();

/**
 * Return the current time in the format used for the command and report time-stamp.
 * @return the current time.
 */
CrFwTimeStamp_t CrFwGetCurrentTimeStamp();

/**
 * Return the current time in "cycle format" (integer number of cycles elapsed since
 * some event).
 * If the host application does not support the "cycle format", this function
 * returns zero.
 * @return the current time in cycle format or zero if the cycle format is not supported.
 */
CrFwTimeCyc_t CrFwGetCurrentCycTime();

/**
 * Convert a time value from standard time format to time-stamp format.
 * @param stdTime the time in standard format
 * @return the time in time-stamp format
 */
CrFwTimeStamp_t CrFwStdTimeToTimeStamp(CrFwTime_t stdTime);

/**
 * Convert a time value from time-stamp format to standard time format.
 * @param timeStamp the time in time-stamp format
 * @return the time in standard format
 */
CrFwTime_t CrFwTimeStampToStdTime(CrFwTimeStamp_t timeStamp);

#endif /* CRFW_TIME_H_ */
