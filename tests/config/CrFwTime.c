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
 * time function <code>::CrFwGetCurrentTime</code> is called.
 * The function returns the value of this integer.
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of CORDET Framework.
 *
 * CORDET Framework is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CORDET Framework is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CORDET Framework.  If not, see <http://www.gnu.org/licenses/>.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#include <stdlib.h>
#include "CrFwConstants.h"
#include "CrFwTime.h"

/** The <code>::CrFwGetCurrentTime</code> increments this counter and then returns its value */
static CrFwTimeStamp_t dummyTime = 0;

/*-----------------------------------------------------------------------------------------*/
CrFwTimeStamp_t CrFwGetCurrentTime() {
	dummyTime++;
	return dummyTime;
}


