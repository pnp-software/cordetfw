/**
 * @file
 * @ingroup crOpenIfGroup
 * Interface for reporting an error detected by a PUS Extension component.
 * When a PUS Extension component encounters an error, it reports it by calling one of
 * the functions defined by this header file (error report).
 *
 * An error report is defined by the following attributes:
 * - The error code: a positive integer which identifies the type of
 *   error.
 * - The source type identifier: the type identifier of the component which
 *   generated the error report.
 * - The source instance identifier: the instance identifier of the component
 *   which generated the error report.
 * - The error parameters: any additional parameters which are useful to
 *   characterize the circumstances in which the error arose.
 * .
 * The type and number of error parameters depends on the type of error which is being
 * reported.
 * This interface defines several error reporting functions, one for each set of
 * error parameter types.
 *
 * In general, the implementation of this interface is entirely application-specific
 * but a simple default implementation is provided in <code>CrFwRepErr.c</code>.
 * This default implementation is primarily intended for testing and demonstration
 * purposes.
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

#ifndef CRPS_REPERR_H_
#define CRPS_REPERR_H_

/* Include Framework Files */
#include "CrFwConstants.h"
/* Include Configuration Files */
#include "CrFwUserConstants.h"
#include "CrPsUserConstants.h"

#define OUTFACTORY_FAIL   100
#define INLOADER_INV_DEST 101

/**
 * Report an error which has no parameters attached to it.
 * This function generate an error report without error parameters.
 * @param errCode the error code
 * @param repType the type of the component which raises the error report
 * @param repServSubType the sub type of the component which raises the error report
 * @param repDiscriminant the discriminant of the component which raises the error report
 */
void CrPsRepErr(CrPsRepErrCode_t errCode, CrFwServType_t repType, CrFwServSubType_t repSubType, CrFwDiscriminant_t repDiscriminant);

/**
 * Report an error which has two parameters attached to it representing the instance identifier
 * of a component other than the originator of the error report (the secondary instance
 * identifier) and a command or report destination.
 * This function generate an error report with two parameters.
 * @param errCode the error code
 * @param instanceId the instance identifier of the component which raises the error report
 * @param typeId the type identifier of the component which raises the error report
 * @param secondaryInstanceId instance identifier of a component other than the originator of the error
 * report
 * @param dest a command or report destination
 */
void CrFwRepErrInstanceIdAndDest(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId,
                                 CrFwInstanceId_t instanceId, CrFwInstanceId_t secondaryInstanceId, CrFwDestSrc_t dest);

#endif /* CRPS_REPERR_H_ */
