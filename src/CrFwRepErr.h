/**
 * @file
 * @ingroup crOpenIfGroup
 * Interface for reporting an error detected by a framework component.
 * When a framework component encounters an error, it reports it by calling one of
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
 * Not all functions defined in this interface are used by the CORDET Framework.
 * Some are intended for use by application components.
 *
 * The range of error codes is defined in type <code>::CrFwRepErrCode_t</code>.
 * Note that this is a configurable type that users are expected to extend with
 * their own error codes.
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
 * This file is part of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#ifndef CRFW_REPERR_H_
#define CRFW_REPERR_H_

/* Include Framework Files */
#include "CrFwConstants.h"
/* Include Configuration Files */
#include "CrFwUserConstants.h"

/**
 * Report an error which has no parameters attached to it.
 * This function generate an error report without error parameters.
 * @param errCode the error code
 * @param instanceId the instance identifier of the component which raises the error report
 * @param typeId the type identifier of the component which raises the error report
 */
void CrFwRepErr(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId, CrFwInstanceId_t instanceId);

/**
 * Report an error which has one single parameter attached to it representing a command
 * or report destination or source.
 * This function generate an error report with one parameter.
 * @param errCode the error code
 * @param instanceId the instance identifier of the component which raises the error report
 * @param typeId the type identifier of the component which raises the error report
 * @param destSrc the invalid destination or source
 */
void CrFwRepErrDestSrc(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId, CrFwInstanceId_t instanceId,
                       CrFwDestSrc_t destSrc);

/**
 * Report an error which has one single parameter attached to it representing a command
 * or report group.
 * This function generate an error report with one parameter.
 * @param errCode the error code
 * @param instanceId the instance identifier of the component which raises the error report
 * @param typeId the type identifier of the component which raises the error report
 * @param group the invalid group
 */
void CrFwRepErrGroup(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId, CrFwInstanceId_t instanceId,
                     CrFwGroup_t group);

/**
 * Report an error which has two parameters attached to it representing expected and
 * actual sequence counter values.
 * This function generate an error report with two parameters.
 * @param errCode the error code
 * @param instanceId the instance identifier of the component which raises the error report
 * @param typeId the type identifier of the component which raises the error report
 * @param expSeqCnt the expected sequence counter
 * @param actSeqCnt the actual sequence counter
 * @param pckt a packet holding a command or report (this is a pointer which is only guaranteed valid
 * during the function execution)
 */
void CrFwRepErrSeqCnt(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId, CrFwInstanceId_t instanceId,
                      CrFwSeqCnt_t expSeqCnt, CrFwSeqCnt_t actSeqCnt, CrFwPckt_t pckt);

/**
 * Report an error which has two parameters attached to it representing the instance identifier
 * of a component other than the originator of the error report (the secondary instance
 * identifier) and the outcome field of a component's data.
 * This function generate an error report with two parameters.
 * @param errCode the error code
 * @param instanceId the instance identifier of the component which raises the error report
 * @param typeId the type identifier of the component which raises the error report
 * @param secondaryInstanceId instance identifier of a component other than the originator of the error
 * report
 * @param outcome outcome field of a component's data
 */
void CrFwRepErrInstanceIdAndOutcome(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId,
                                    CrFwInstanceId_t instanceId, CrFwInstanceId_t secondaryInstanceId, CrFwOutcome_t outcome);

/**
 * Report an error which has three parameters attached to it representing the instance identifier
 * of a component other than the originator of the error report (the secondary instance
 * identifier), a command or report destination and a command or report packet.
 * This function generate an error report with two parameters.
 * @param errCode the error code
 * @param instanceId the instance identifier of the component which raises the error report
 * @param typeId the type identifier of the component which raises the error report
 * @param secondaryInstanceId instance identifier of a component other than the originator of the error
 * report
 * @param dest a command or report destination
 * @param pckt a packet holding a command or report (this is a pointer which is only guaranteed valid
 * during the function execution)
 */
void CrFwRepErrInstanceIdAndDest(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId,
                                 CrFwInstanceId_t instanceId, CrFwInstanceId_t secondaryInstanceId,
								 CrFwDestSrc_t dest, CrFwPckt_t pckt);

/**
 * Report an error which has one parameter attached to it representing a command or report packet.
 * This function generate an error report with one parameter.
 * @param errCode the error code
 * @param instanceId the instance identifier of the component which raises the error report
 * @param typeId the type identifier of the component which raises the error report
 * @param pckt a packet holding a command or report (this is a pointer which is only guaranteed valid
 * during the function execution)
 */
void CrFwRepErrPckt(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId,
                                    CrFwInstanceId_t instanceId, CrFwPckt_t pckt);

/**
 * Report an error which has one parameter attached to it representing an report component.
 * This function generate an error report with one parameter.
 * @param errCode the error code
 * @param instanceId the instance identifier of the component which raises the error report
 * @param typeId the type identifier of the component which raises the error report
 * @param rep a component holding a report
 */
void CrFwRepErrRep(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId,
                                    CrFwInstanceId_t instanceId, FwSmDesc_t rep);

/**
 * Report an error which has one parameter attached to it representing a command component.
 * This function generate an error report with one parameter.
 * @param errCode the error code
 * @param instanceId the instance identifier of the component which raises the error report
 * @param typeId the type identifier of the component which raises the error report
 * @param cmd a component holding a command
 */
void CrFwRepErrCmd(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId,
                                    CrFwInstanceId_t instanceId, FwSmDesc_t cmd);


/**
 * Report an error which has three parameters attached to it representing the kind of a report
 * or command as given by the triplet [type, sub-type, discriminant].
 * This function generate an error report with three parameters.
 * @param errCode the error code
 * @param instanceId the instance identifier of the component which raises the error report
 * @param typeId the type identifier of the component which raises the error report
 * @param type a report or command service
 */
void CrFwRepErrKind(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId,
                                    CrFwInstanceId_t instanceId, CrFwServType_t  servType,
									CrFwServSubType_t servSubType, CrFwDiscriminant_t disc);


#endif /* CRFW_REPERR_H_ */
