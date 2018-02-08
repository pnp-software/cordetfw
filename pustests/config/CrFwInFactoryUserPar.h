/**
 * @file CrFwInFactoryUserPar.h
 * @ingroup PUSTestsuite
 * @ingroup PUSTestconfig 
 *
 * @brief User-modifiable parameters for the InFactory component (see <code>CrFwInFactory.h</code>).
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

#ifndef CRFW_INFACTORY_USERPAR_H_
#define CRFW_INFACTORY_USERPAR_H_

#include "Services/Test/InCmd/CrPsTestAreYouAliveConnection.h"
#include "Services/Test/InRep/CrPsTestAreYouAliveConnectInRep.h"
#include "Services/Test/InCmd/CrPsTestOnBoardConnection.h"

#include "Services/Housekeeping/InCmd/CrPsHkRepStructCmd.h"
#include "Services/Housekeeping/InCmd/CrPsHkOneShotCmd.h"
#include "Services/Housekeeping/InCmd/CrPsHkEnableCmd.h"
#include "Services/Housekeeping/InCmd/CrPsHkDisableCmd.h"
#include "Services/Housekeeping/InCmd/CrPsHkDeleteCmd.h"
#include "Services/Housekeeping/InCmd/CrPsHkCreateCmd.h"

#include "Services/EventReporting/InCmd/CrPsEvtDisableCmd.h"
#include "Services/EventReporting/InCmd/CrPsEvtEnableCmd.h"
#include "Services/EventReporting/InCmd/CrPsEvtRepDisabledCmd.h"

#include "Services/LargePacketTransfer/InCmd/CrPsLptAbortDownCmd.h"
#include "Services/LargePacketTransfer/InCmd/CrPsLptStartDownCmd.h"
#include "Services/LargePacketTransfer/InCmd/CrPsLptUpFirstCmd.h"
#include "Services/LargePacketTransfer/InCmd/CrPsLptUpInterCmd.h"
#include "Services/LargePacketTransfer/InCmd/CrPsLptUpLastCmd.h"

#include "UtilityFunctions/CrFwUtilityFunctions.h"
/**
 * The maximum number of components representing an incoming command which may be allocated
 * at any one time.
 * This constant must be a positive integer smaller than the range of
 * <code>::CrFwInFactoryPoolIndex_t</code>.
 */
#define CR_FW_INFACTORY_MAX_NOF_INCMD 5

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
 */
#define CR_FW_INCMD_NKINDS 25

/**
 * Definition of the incoming command kinds supported by an application.
 * An application supports a number of service types and, for each service type, it supports
 * a number of sub-types.
 * Each sub-type may support a range of discriminant values.
 * An incoming command kind is defined by the triplet: [service type, service sub-type,
 * discriminant].
 *
 * Each line in this initializer describes one incoming command kind.
 * The elements in each line are as follows:
 * - The service type.
 * - The service sub-type.
 * - The discriminant value. A value of zero indicates either that no discriminant is
 *   associated to commands/reports of that type and sub-type or else that all commands/reports of
 *   this type and sub-type have the same characteristics.
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
 *   function <code>::CrFwSmEmptyAction</code> can be used as a default).
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
 */
#define CR_FW_INCMD_INIT_KIND_DESC \
      { /*            VALIDITY CHECK                    READY CHECK                                 START ACTION                                 PROGRESS ACTION                                 TERMINATION ACTION                                 ABORT ACTION  */ \
    /*{8,  1, 1,   &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrFwSmEmptyAction,                          &CrFwSmEmptyAction,                             &CrFwSmEmptyAction,                                &CrFwSmEmptyAction}, \*/ \
      {3,  1, 0,   &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsHkCreateCmdStartAction,                 &CrPsHkCreateCmdProgressAction,                 &CrFwSmEmptyAction,                                &CrFwSmEmptyAction}, \
      {3,  1, 1,   &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsHkCreateCmdStartAction,                 &CrPsHkCreateCmdProgressAction,                 &CrFwSmEmptyAction,                                &CrFwSmEmptyAction}, \
      {3,  1, 2,   &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsHkCreateCmdStartAction,                 &CrPsHkCreateCmdProgressAction,                 &CrFwSmEmptyAction,                                &CrFwSmEmptyAction}, \
      {3,  1, 3,   &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsHkCreateCmdStartAction,                 &CrPsHkCreateCmdProgressAction,                 &CrFwSmEmptyAction,                                &CrFwSmEmptyAction}, \
      {3,  2, 3,   &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsHkCreateCmdStartAction,                 &CrPsHkCreateCmdProgressAction,                 &CrFwSmEmptyAction,                                &CrFwSmEmptyAction}, \
      {3,  3, 0,   &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsHkDeleteCmdStartAction,                 &CrPsHkDeleteCmdProgressAction,                 &CrPsHkDeleteCmdTerminationAction,                 &CrFwSmEmptyAction}, \
      {3,  4, 0,   &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsHkDeleteCmdStartAction,                 &CrPsHkDeleteCmdProgressAction,                 &CrPsHkDeleteCmdTerminationAction,                 &CrFwSmEmptyAction}, \
      {3,  5, 0,   &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsHkEnableCmdStartAction,                 &CrPsHkEnableCmdProgressAction,                 &CrPsHkEnableCmdTerminationAction,                 &CrFwSmEmptyAction}, \
      {3,  6, 0,   &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsHkDisableCmdStartAction,                &CrPsHkDisableCmdProgressAction,                &CrPsHkDisableCmdTerminationAction,                &CrFwSmEmptyAction}, \
      {3,  7, 0,   &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsHkEnableCmdStartAction,                 &CrPsHkEnableCmdProgressAction,                 &CrPsHkEnableCmdTerminationAction,                 &CrFwSmEmptyAction}, \
      {3,  8, 0,   &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsHkDisableCmdStartAction,                &CrPsHkDisableCmdProgressAction,                &CrPsHkDisableCmdTerminationAction,                &CrFwSmEmptyAction}, \
      {3,  9, 0,   &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsHkRepStructCmdStartAction,              &CrPsHkRepStructCmdProgressAction,              &CrPsHkRepStructCmdTerminationAction,              &CrFwSmEmptyAction}, \
      {3,  11, 0,  &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsHkRepStructCmdStartAction,              &CrPsHkRepStructCmdProgressAction,              &CrPsHkRepStructCmdTerminationAction,              &CrFwSmEmptyAction}, \
      {3,  27, 0,  &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsHkOneShotCmdStartAction,                &CrPsHkOneShotCmdProgressAction,                &CrPsHkOneShotCmdTerminationAction,                &CrFwSmEmptyAction}, \
      {3,  28, 0,  &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsHkOneShotCmdStartAction,                &CrPsHkOneShotCmdProgressAction,                &CrPsHkOneShotCmdTerminationAction,                &CrFwSmEmptyAction}, \
      {5,  5,  0,  &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsEvtEnableCmdStartAction,                &CrPsEvtEnableCmdProgressAction,                &CrPsEvtEnableCmdTerminationAction,                &CrFwSmEmptyAction}, \
      {5,  6,  0,  &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsEvtDisableCmdStartAction,               &CrPsEvtDisableCmdProgressAction,               &CrPsEvtDisableCmdTerminationAction,               &CrFwSmEmptyAction}, \
      {5,  7,  0,  &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsEvtRepDisabledCmdStartAction,           &CrPsEvtRepDisabledCmdProgressAction,           &CrPsEvtRepDisabledCmdTerminationAction,           &CrFwSmEmptyAction}, \
      {13, 9,   0, &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsLptUpFirstCmdStartAction,               &CrPsLptUpFirstCmdProgressAction,               &CrPsLptUpFirstCmdTerminationAction,               &CrFwSmEmptyAction}, \
      {13, 10,  0, &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsLptUpInterCmdStartAction,               &CrPsLptUpInterCmdProgressAction,               &CrPsLptUpInterCmdTerminationAction,               &CrFwSmEmptyAction}, \
      {13, 11,  0, &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsLptUpLastCmdStartAction,                &CrPsLptUpLastCmdProgressAction,                &CrPsLptUpLastCmdTerminationAction,                &CrFwSmEmptyAction}, \
      {13, 129, 0, &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsLptStartDownCmdStartAction,             &CrPsLptStartDownCmdProgressAction,             &CrPsLptStartDownCmdTerminationAction,             &CrFwSmEmptyAction}, \
      {13, 130, 0, &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsLptAbortDownCmdStartAction,             &CrPsLptAbortDownCmdProgressAction,             &CrPsLptAbortDownCmdTerminationAction,             &CrFwSmEmptyAction}, \
      {17, 1, 0,   &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsTestAreYouAliveConnectionStartAction,   &CrPsTestAreYouAliveConnectionProgressAction,   &CrPsTestAreYouAliveConnectionTerminationAction,   &CrFwSmEmptyAction}, \
      {17, 3, 0,   &CrFwPrCheckAlwaysTrue,           &CrFwSmCheckAlwaysTrue,                     &CrPsTestOnBoardConnectionStartAction,       &CrPsTestOnBoardConnectionProgressAction,       &CrPsTestOnBoardConnectionTerminationAction,       &CrFwSmEmptyAction}  \
	}

/**
 * The maximum number of InReports which may be allocated at any one time.
 * This constant must be smaller than the range of <code>::CrFwInFactoryPoolIndex_t</code>.
 */
#define CR_FW_INFACTORY_MAX_NOF_INREP 5

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
#define CR_FW_INREP_NKINDS 2

/**
 * Definition of the incoming report kinds supported by an application.
 * An application supports a number of service types and, for each service type, it supports
 * a number of sub-types.
 * Each sub-type may support a range of discriminant values.
 * An incoming report kind is defined by the triplet: [service type, service sub-type,
 * discriminant].
 *
 * Each line in this initializer describes one incoming report kind.
 * The elements in each line are as follows:
 * - The service type.
 * - The service sub-type.
 * - The discriminant value. A value of zero indicates either that no discriminant is
 *   associated to commands/reports of that type and sub-type or else that all commands/reports of
 *   this type and sub-type have the same characteristics.
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
 */
#define CR_FW_INREP_INIT_KIND_DESC \
	{ \
      {17, 2, 0, &CrPsTestAreYouAliveConnectInRepUpdateAction,   &CrFwPrCheckAlwaysTrue,   0}, \
      {17, 4, 0, &CrPsTestAreYouAliveConnectInRepUpdateAction,   &CrFwPrCheckAlwaysTrue,   0}  \
	}

#endif /* CRFW_INFACTORY_USERPAR_H_ */
