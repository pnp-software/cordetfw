/**
 * @file
 * @ingroup crOpenIfGroup
 * Interface through which framework components access the current time.
 * Framework component need access to the current time to time-stamp out-going
 * command and report packets.
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
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#ifndef CRFW_TIME_H_
#define CRFW_TIME_H_

/* Include Framework Files */
#include "CrFwConstants.h"
/* Include Configuration Files */
#include "CrFwUserConstants.h"

/**
 * Return the current time.
 * This function generate an error report without error parameters.
 * @return the current time.
 */
CrFwTimeStamp_t CrFwGetCurrentTime();

#endif /* CRFW_TIME_H_ */
