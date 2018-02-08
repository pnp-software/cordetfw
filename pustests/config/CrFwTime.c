/**
 * @file CrFwTime.c
 * @ingroup PUSTestsuite
 * @ingroup PUSTestconfig 
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

#include <stdlib.h>
#include "CrFwConstants.h"
#include "CrFwTime.h"

#include <time.h>   /* for time()   */
#include <string.h> /* for memcpy() */

/** The <code>::CrFwGetCurrentTime</code> increments this counter and then returns its value */



/*-----------------------------------------------------------------------------------------*/
CrFwTimeStamp_t CrFwGetCurrentTime() {
  int now;
  CrFwTimeStamp_t ts;
  now = (int)time(NULL);
  memcpy(&ts, &now, sizeof(int));
  return ts;
}


