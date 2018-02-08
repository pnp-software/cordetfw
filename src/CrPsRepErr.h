/**
 * @file CrPsRepErr.h
 * @ingroup PUSconfig
 * 
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
 * @author Christian Reimers <christian.reimersy@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * 
 * last modification: 22.01.2018
 *
 * @copyright Department of Astrophysics, University of Vienna, 2017, All Rights Reserved
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#ifndef CRPS_REPERR_H_
#define CRPS_REPERR_H_

/* Include Framework Files */
#include "CrFwConstants.h"
/* Include Configuration Files */
#include "CrFwUserConstants.h"
#include "CrPsUserConstants.h"


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
