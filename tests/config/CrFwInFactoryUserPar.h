/**
 * @file
 * @ingroup crConfigGroup
 * User-modifiable parameters for the InFactory component (see <code>CrFwInFactory.h</code>).
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

#ifndef CRFW_INFACTORY_USERPAR_H_
#define CRFW_INFACTORY_USERPAR_H_

#include "CrFwInCmdSample1.h"
#include "CrFwInRepSample1.h"
#include "InCmd/CrFwInCmd.h"
#include "InRep/CrFwInRep.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/**
 * The maximum number of components representing an incoming command which may be allocated
 * at any one time.
 * This constant must be a positive integer smaller than the range of
 * <code>::CrFwInFactoryPoolIndex_t</code>.
 */
#define CR_FW_INFACTORY_MAX_NOF_INCMD 5

/**
 * The maximum number of InReports which may be allocated at any one time.
 * This constant must be smaller than the range of <code>::CrFwInFactoryPoolIndex_t</code>.
 */
#define CR_FW_INFACTORY_MAX_NOF_INREP 5

/**
 * The total number of kinds of incoming commands supported by the application.
 * An incoming command kind is defined by the triplet: [service type, service sub-type,
 * discriminant value].
 * The value of this constant must be the same as the number of rows of the
 * initializer <code>#CR_FW_INCMD_INIT_KIND_DESC</code> and it must be smaller
 * than the range of the <code>::CrFwCmdRepKindIndex_t</code> type.
 *
 * This constant is used as the size of a statically declared array.
 * Hence, a value of zero may not be allowed by some compilers.
 * 
 * @AP IFT-01: Maximum Number of InReports which can be allocated by InFactory
 * @AP IFT-02: Maximum Number of InCommands which can be allocated by InFactory
 */
#define CR_FW_INCMD_NKINDS 3

/**
 * The total number of kinds of incoming reports supported by the application.
 * An incoming report kind is defined by the triplet: [service type, service sub-type,
 * discriminant value].
 * The value of this constant must be the same as the number of rows of the
 * initializer <code>#CR_FW_INREP_INIT_KIND_DESC</code> and it must be smaller
 * than the range of the <code>::CrFwCmdRepKindIndex_t</code> type.
 *
 * This constant is used as the size of a statically declared array.
 * Hence, a value of zero may not be allowed by some compilers.
 */
#define CR_FW_INREP_NKINDS 4

/**
 * Definition of the incoming command kinds supported by an application.
 * An application supports a number of service types and, for each service type, it supports
 * a number of sub-types.
 * Each sub-type may support a range of discriminant values.
 * An incoming command kind is defined by the triplet: [service type, service sub-type,
 * discriminant].
 *
 * Each line in this initializer describes one incoming command kind.
 * If the discriminant field is different from zero, then the line describes the characteristics
 * of the command of that specific kind (as identified by the triplet
 * [service type, service sub-type, discriminant]).
 * If, instead, the discriminant is equal to zero, then the line describes the default characteristics
 * of all commmands of the given type and sub-type.
 *
 * The elements in each line are as follows:
 * - The service type.
 * - The service sub-type.
 * - The discriminant value. A value of zero indicates either that no discriminant is
 *   associated to commands of that type and sub-type or else that all commands of
 *   that type and sub-type have the same characteristics.
 * - The expected length of the incoming command. A value of zero indicates that the length
 *   of the command is not statically known.
 * - The function implementing the Validity Check Operation for this kind of incoming command
 *   (this must be a function pointer of type <code>::CrFwInCmdValidityCheck_t</code>;
 *   function <code>::CrFwPrCheckAlwaysTrue</code> can be used as a default).
 * - The function implementing the Ready Check Operation for this kind of incoming command
 *   (this must be a function pointer of type <code>::CrFwInCmdReadyCheck_t</code>;
 *   function <code>::CrFwSmCheckAlwaysTrue</code> can be used as a default).
 * - The function implementing the Start Action Operation for this kind of incoming command
 *   (this must be a function pointer of type <code>::CrFwInCmdStartAction_t</code>;
 *   function <code>::CrFwSmEmptyAction</code> can be used as a default).
 * - The function implementing the Progress Action Operation for this kind of incoming command
 *   (this must be a function pointer of type <code>::CrFwInCmdProgressAction_t</code>;
 *   function <code>::CrFwSmEmptyAction</code> can be used as a default).
 * - The function implementing the Termination Action Operation for this kind of incoming command
 *   (this must be a function pointer of type <code>::CrFwInCmdTerminationAction_t</code>;
 *   function <code>::CrFwSmSuccessAction</code> can be used as a default).
 * - The function implementing the Abort Action Operation for this kind of incoming command
 *   (this must be a function pointer of type <code>::CrFwInCmdAbortAction_t</code>;
 *   function <code>::CrFwSmEmptyAction</code> can be used as a default).
 * .
 * The list of service descriptors must satisfy the following constraints:
 * - The number of lines must be the same as <code>::CR_FW_INCMD_NKINDS</code>.
 * - The values of the service types, sub-types and discriminant must be lower than
 * 	 <code>#CR_FW_MAX_SERV_TYPE</code>, <code>#CR_FW_MAX_SERV_SUBTYPE</code> and
 * 	 <code>#CR_FW_MAX_DISCRIMINANT</code>.
 * - The service types must be listed in increasing order.
 * - The service sub-types within a service type must be listed in increasing order.
 * - The discriminant values within a service type/sub-type must be listed in increasing order.
 * .
 * The last four constraints are checked by the auxiliary function
 * <code>::CrFwAuxInFactoryInCmdConfigCheck</code>.
 *
 * The initializer values defined below are those which are used for the framework Test Suite.
 * The function pointers in the last row are those of the Sample InCommand defined in
 * <code>CrFwInCommandSample1.h</code>.
 * 
 * @AP ICM-03: Configuration Check in Reset Procedure of InCommand 
 * @AP ICM-07: Ready Check of InCommand 
 * @AP ICM-08: Start Action of InCommand 
 * @AP ICM-09: Progress Action of InCommand 
 * @AP ICM-10: Termination Action of InCommand 
 * @AP ICM-11: Abort Action of InCommand 
 * @AP IFT-03: InReport Kinds Supported by InFactory 
 * @AP IFT-04: InCommand Kinds Supported by InFactory 
 */
#define CR_FW_INCMD_INIT_KIND_DESC \
	{ {8, 1, 1, 0, &CrFwInCmdDefValidityCheck, &CrFwSmCheckAlwaysTrue, &CrFwSmEmptyAction, \
						&CrFwSmEmptyAction, &CrFwSmSuccessAction, &CrFwSmEmptyAction}, \
	  {8, 1, 2, 40, &CrFwInCmdDefValidityCheck, &CrFwSmCheckAlwaysTrue, &CrFwSmEmptyAction, \
						&CrFwSmEmptyAction, &CrFwSmSuccessAction, &CrFwSmEmptyAction}, \
	  {50, 1, 0, 0, &CrFwInCmdSample1ValidityCheck, &CrFwInCmdSample1ReadyCheck, &CrFwInCmdSample1StartAction, \
						&CrFwInCmdSample1ProgressAction, &CrFwInCmdSample1TerminationAction, &CrFwInCmdSample1AbortAction} \
	}

/**
 * Definition of the incoming report kinds supported by an application.
 * An application supports a number of service types and, for each service type, it supports
 * a number of sub-types.
 * Each sub-type may support a range of discriminant values.
 * An incoming report kind is defined by the triplet: [service type, service sub-type,
 * discriminant].
 *
 * Each line in this initializer describes one incoming report kind.
 * If the discriminant field is different from zero, then the line describes the characteristics
 * of the report of that specific kind (as identified by the triplet
 * [service type, service sub-type, discriminant]).
 * If, instead, the discriminant is equal to zero, then the line describes the default characteristics
 * of all reports of the given type and sub-type.
 * 
 * The elements in each line are as follows:
 * - The service type.
 * - The service sub-type.
 * - The discriminant value. A value of zero indicates either that no discriminant is
 *   associated to reports of that type and sub-type or else that all reports of
 *   that type and sub-type have the same characteristics.
 * - The expected length of the incoming report. A value of zero indicates that the length
 *   of the report is not statically known.
 * - The function implementing the Update Action Operation for this kind of incoming report
 *   (this must be a function pointer of type <code>::CrFwInRepUpdateAction_t</code>;
 *   function <code>::CrFwPrEmptyAction</code> can be used as a default).
 * - The function implementing the Validity Check Operation for this kind of incoming report
 *   (this must be a function pointer of type <code>::CrFwInRepValidityCheck_t</code>;
 *   function <code>::CrFwPrCheckAlwaysTrue</code> can be used as a default).
 * .
 * The list of service descriptors must satisfy the following constraints:
 * - The number of lines must be the same as <code>::CR_FW_INREP_NKINDS</code>.
 * - The values of the service types, sub-types and discriminant must be lower than
 * 	 <code>#CR_FW_MAX_SERV_TYPE</code>, <code>#CR_FW_MAX_SERV_SUBTYPE</code> and
 * 	 <code>#CR_FW_MAX_DISCRIMINANT</code>.
 *   maximum values defined in <code>CrFwUserConstants.h</code> (TBC).
 * - The service types must be listed in increasing order.
 * - The service sub-types within a service type must be listed in increasing order.
 * - The discriminant values within a service type/sub-type must be listed in increasing order.
 * .
 * The last four constraints are checked by the auxiliary function
 * <code>::CrFwAuxInFactoryInRepConfigCheck</code>.
 *
 * The initializer values defined below are those which are used for the framework Test Suite.
 * The function pointers in the last row are those of the Sample InReport defined in
 * <code>CrFwInReportSample1.h</code>.
 * 
 * @AP IRP-03: Configuration Check in Reset Procedure of InReport
 * @AP IRP-07: Update Action of InReport
 */
#define CR_FW_INREP_INIT_KIND_DESC \
	{ {5, 1, 1, 0, &CrFwPrEmptyAction, &CrFwInRepDefValidityCheck}, \
	  {5, 1, 2, 0, &CrFwPrEmptyAction, &CrFwInRepDefValidityCheck}, \
	  {5, 1, 3, 50, &CrFwPrEmptyAction, &CrFwPrCheckAlwaysTrue}, \
	  {40, 1, 0, 0, &CrFwInRepSample1UpdateAction, &CrFwInRepSample1ValidityCheck} \
	}

#endif /* CRFW_INFACTORY_USERPAR_H_ */
