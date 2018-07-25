/**
 * @file
 * @ingroup inMngGroup
 * Definition of the InReport Component of the framework.
 *
 * An InReport encapsulates an incoming report in a service user application.
 * The InReport is responsible for storing the attributes of an incoming report
 * and for executing the conditional checks and actions associated to the report.
 * The behaviour of an InReport is defined by the InReport State Machine
 * (see figure below).
 *
 * <b>Mode of Use of an InReport Component</b>
 *
 * InReports are created dynamically by the InLoader when it processes an incoming
 * packet which holds a report.
 * The InReport component is created through a call to the factory function
 * <code>::CrFwInFactoryMakeInRep</code>.
 * The InLoader loads the InReport into an InManager who is then responsible for
 * executing it and, eventually, for returning it to the InFactory.
 *
 * An InReport encapsulates an incoming report of a certain kind.
 * The "kind" of an incoming command is defined by the triplet:
 * [service type, service sub-type, discriminant].
 * InReports are adapted to a certain incoming report kind by modifying the
 * implementation of the following operations:
 * - Validity Check Operation
 * - Update Action Operation
 * .
 * This operation is statically defined for each kind of InReport in
 * <code>CrFwInFactoryUserPar.h</code>.
 * This header file defines default values for the Update Action Operation.
 * The default for the Configuration Check Operation is the function
 * <code>::CrFwBaseCmpDefConfigCheck</code>.
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

#ifndef CRFW_INREP_H_
#define CRFW_INREP_H_

/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwPrConstants.h"
/* Include configuration files */
#include "Pckt/CrFwPcktQueue.h"
#include "CrFwUserConstants.h"
/* Include framework files */
#include "CrFwConstants.h"

/**
 * Return the source of the InReport.
 * @param smDesc the descriptor of the InRep State MachineStream
 * @return the source of the InReport
 */
CrFwDestSrc_t CrFwInRepGetSrc(FwSmDesc_t smDesc);

/**
 * Return the group of the InReport.
 * @param smDesc the descriptor of the InRep State MachineStream
 * @return the group of the InReport
 */
CrFwGroup_t CrFwInRepGetGroup(FwSmDesc_t smDesc);

/**
 * Return the type of the InReport.
 * @param smDesc the descriptor of the InRep State MachineStream
 * @return the type of the InReport
 */
CrFwServType_t CrFwInRepGetServType(FwSmDesc_t smDesc);

/**
 * Return the sub-type of the InReport.
 * @param smDesc the descriptor of the InRep State MachineStream
 * @return the sub-type of the InReport
 */
CrFwServType_t CrFwInRepGetServSubType(FwSmDesc_t smDesc);

/**
 * Return the discriminant of the InReport.
 * @param smDesc the descriptor of the InRep State MachineStream
 * @return the discriminant of the InReport
 */
CrFwDiscriminant_t CrFwInRepGetDiscriminant(FwSmDesc_t smDesc);

/**
 * Return the sequence counter of the InReport.
 * @param smDesc the descriptor of the InRep State MachineStream
 * @return the sequence counter of the InReport
 */
CrFwSeqCnt_t CrFwInRepGetSeqCnt(FwSmDesc_t smDesc);

/**
 * Return the start address of the parameter area of the InReport.
 * The InReport is encapsulated in a packet.
 * The parameter area of the InReport is the part of the packet which is reserved to the
 * storage of the parameters of the InReport.
 * The parameter area consists of an uninterrupted sequence of bytes.
 * The size of the parameter area is returned by function <code>::CrFwInRepGetParLength</code>.
 * @param smDesc the descriptor of the Base State Machine of the InReport
 * @return the start address of the InReport parameter area.
 */
char* CrFwInRepGetParStart(FwSmDesc_t smDesc);

/**
 * Return the length in bytes of the parameter area of the InReport.
 * The InReport is encapsulated in a packet.
 * The parameter area of the InReport is the part of the packet which is reserved to the
 * storage of the parameters of the InReport.
 * The parameter area consists of an uninterrupted sequence of bytes.
 * The start address of the parameter area is returned by function <code>::CrFwInRepGetParStart</code>.
 * @param smDesc the descriptor of the Base State Machine of the InReport
 * @return the length in bytes of the InReport parameter area
 */
CrFwPcktLength_t CrFwInRepGetParLength(FwSmDesc_t smDesc);

/**
 * Configuration check for an InReport.
 * This function executes the Validity Check of the InReport and sets the
 * action outcome to 1 if the Validity Check returns true and sets it to
 * zero if it returns false.
 *
 * This function is not intended to be called by applications.
 * It is declared as a public function because it is needed by the
 * InFactory (see <code>CrFwInFactory.h</code>).
 * @param prDesc the descriptor of the InReport Configuration Procedure.
 */
void CrFwInRepConfigCheck(FwPrDesc_t prDesc);

/**
 * Return the pointer to the packet which holds the InReport.
 * The InReport is encapsulated in a packet.
 * This function returns this packet.
 * The packet is only initialized if the InReport has been correctly de-serialized.
 * This is normally the case if the InReport has been successfully returned by the InFactory.
 * The length of the packet is stored in the packet itself and can be retrieved
 * with function <code>::CrFwPcktGetLength</code>.
 * @param smDesc the descriptor of the Base State Machine of the InReport
 * @return the pointer to the packet holding the InReport.
 */
CrFwPckt_t CrFwInRepGetPckt(FwSmDesc_t smDesc);

#endif /* CRFW_INREP_H_ */
