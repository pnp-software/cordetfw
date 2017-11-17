/**
 * @file
 * @ingroup crConfigGroup
 * User-modifiable parameters for the OutFactory component (see <code>CrFwOutFactory.h</code>).
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

#ifndef CRFW_OUTFACTORY_USERPAR_H_
#define CRFW_OUTFACTORY_USERPAR_H_

#include "CrFwOutCmpSample1.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include <Services/Test/OutCmp/CrPsTestAreYouAliveConnectionRep.h>
#include <Services/Housekeeping/OutCmp/CrPsHkRep.h> /*Service 3,25 3,26*/
#include <Services/Housekeeping/OutCmp/CrPsHkRepStructRep.h> /*Service 3,10 3,12*/
#include <Services/EventReporting/OutCmp/CrPsEvtRep.h>
#include <Services/EventReporting/OutCmp/CrPsEvtRepDisabledRep.h>

#include <Services/LargePacketTransfer/OutCmp/CrPsLptDownFirstRep.h>
#include <Services/LargePacketTransfer/OutCmp/CrPsLptDownInterRep.h>
#include <Services/LargePacketTransfer/OutCmp/CrPsLptDownLastRep.h>
#include <Services/LargePacketTransfer/OutCmp/CrPsLptUpAbortRep.h>

#include <Services/General/CrPsConstants.h>

/**
 * The maximum number of OutComponents which may be allocated at any one time.
 * This constant must be smaller than the range of <code>::CrFwOutFactoryPoolIndex_t</code>.
 */
#define CR_FW_OUTFACTORY_MAX_NOF_OUTCMP 10

/**
 * The total number of kinds of OutComponents supported by the application.
 * An OutComponent kind is defined by the triplet: [service type, service sub-type,
 * discriminant value].
 * The value of this constant must be the same as the number of rows of the
 * initializer <code>#CR_FW_OUTCMP_INIT_KIND_DESC</code> and it must be smaller
 * than the range of the <code>::CrFwCmdRepKindIndex_t</code> type.
 *
 * This constant is used as the size of a statically declared array.
 * Hence, a value of zero may not be allowed by some compilers.
 */
#define CR_FW_OUTCMP_NKINDS 33

/**
 * Definition of the OutComponent kinds supported by an application.
 * An application supports a number of service types and, for each service type, it supports
 * a number of sub-types.
 * Each sub-type may support a range of discriminant values.
 * An OutComponent kind is defined by the triplet: [service type, service sub-type, discriminant].
 *
 * Each line in this initializer describes one OutComponent kind.
 * If the discriminant field is different from zero, then the line describes the characteristics
 * of the reports/commands of that specific kind (as identified by the triplet
 * [service type, service sub-type, discriminant]).
 * If, instead, the discriminant is equal to zero, then the line describes the default characteristics
 * of all reports/commands of the given type and sub-type.
 *
 * Thus, for instance, line 13 in the example below describes the default characteristics of
 * reports of type 5 and sub-type 4. According to the description at this line, reports of this
 * type/sub-type have a length of 50 bytes.
 * The following three lines describes reports of the same type/sub-type but with discriminants
 * equal to, respectively, 3, 5 and 7. These reports have characteristics which deviate from the
 * default for defined at line 13 (for example, their length is, respectively, 100, 99 and 98
 * bytes instead of the default value of 50 defined at line 13).
 *
 * The elements in each line are as follows:
 * - The service type.
 * - The service sub-type.
 * - The discriminant value.
 * - The command/report flag. A value of 1 indicates that the OutComponent is a command and
 *   a value of 2 indicates that it is a report,
 * - The default length (in number of bytes) of the packet (see <code>CrFwPckt.h</code>) to which
 *   this kind of OutComponent is serialized.
 * - The function implementing the Enable Check Operation for this kind of component
 *   (this must be a function pointer of type <code>::CrFwOutCmpEnableCheck_t</code>;
 *   function <code>::CrFwOutCmpDefEnableCheck</code> can be used as default).
 * - The function implementing the Ready Check Operation for this kind of component
 *   (this must be a function pointer of type <code>::CrFwOutCmpReadyCheck_t</code>;
 *   function <code>::CrFwSmCheckAlwaysTrue</code> can be used as default).
 * - The function implementing the Repeat Check Operation for this kind of component
 *   (this must be a function pointer of type <code>::CrFwOutCmpRepeatCheck_t</code>;
 *   function <code>::CrFwSmCheckAlwaysFalse</code> can be used as default).
 * - The function implementing the Update Operation for this kind of component
 *   (this must be a function pointer of type <code>::CrFwOutCmpUpdate_t</code>;
 *   function <code>::CrFwSmEmptyAction</code> can be used as default).
 * - The function implementing the Serialize Operation for this kind of component
 *   (this must be a function pointer of type <code>::CrFwOutCmpSerialize_t</code>;
 *   function <code>CrFwOutCmpDefSerialize</code> can be used as default).
 * .
 * The list of service descriptors must satisfy the following constraints:
 * - The number of lines must be the same as <code>::CR_FW_OUTCMP_NKINDS</code>.
 * - The set of service types and sub-types and their discriminants must be consistent
 *   with the definition of <code>::CR_FW_OUTREGISTRY_INIT_SERV_DESC</code>.
 * - The service types must be listed in increasing order.
 * - The service sub-types within a service type must be listed in increasing order.
 * - The discriminant values within a service type/sub-type must be listed in increasing order.
 * - The packet length must be greater than zero.
 * - The packet length must be sufficiently large to ensure that all packet attributes can
 *   be stored in the packet.
 * .
 * Constraints 2 to 6 are checked by the auxiliary function
 * <code>::CrFwAuxOutFactoryConfigCheck</code>.
 *
 * The initializer values defined below are which are used for the framework Test Suite.
 * The function pointers in the last row are those of the Sample OutComponent defined in
 * <code>CrFwOutCmpSample1.h</code>.
 */
#define CR_FW_OUTCMP_INIT_KIND_DESC \
	{ /*                                                                       ENABLE CHECK                                  READY CHECK                                  REPEAT CHECK                                  UPDATE ACTION       */ \
      {1, 1,  0,   crRepType,   CRPS_REQVERIF_ACC_SUCC_LENGTH,               &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrFwSmEmptyAction,                              &CrFwOutCmpDefSerialize},\
      {1, 2,  0,   crRepType,   CRPS_REQVERIF_ACC_FAIL_LENGTH,               &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrFwSmEmptyAction,                              &CrFwOutCmpDefSerialize},\
      {1, 3,  0,   crRepType,   CRPS_REQVERIF_START_SUCC_LENGTH,             &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrFwSmEmptyAction,                              &CrFwOutCmpDefSerialize},\
	{1, 4,  0,   crRepType,   CRPS_REQVERIF_START_FAIL_LENGTH,             &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrFwSmEmptyAction,                              &CrFwOutCmpDefSerialize},\
      {1, 5,  0,   crRepType,   CRPS_REQVERIF_PROG_SUCC_LENGTH,              &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrFwSmEmptyAction,                              &CrFwOutCmpDefSerialize},\
      {1, 6,  0,   crRepType,   CRPS_REQVERIF_PROG_FAIL_LENGTH,              &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrFwSmEmptyAction,                              &CrFwOutCmpDefSerialize},\
      {1, 7,  0,   crRepType,   CRPS_REQVERIF_TERM_SUCC_LENGTH,              &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrFwSmEmptyAction,                              &CrFwOutCmpDefSerialize},\
      {1, 8,  0,   crRepType,   CRPS_REQVERIF_TERM_FAIL_LENGTH,              &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrFwSmEmptyAction,                              &CrFwOutCmpDefSerialize},\
	{1, 10, 0,   crRepType,   CRPS_REQVERIF_REROUT_FAIL_LENGTH,            &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrFwSmEmptyAction,                              &CrFwOutCmpDefSerialize},\
      {3, 10, 1,   crRepType,   CRPS_HK_HKREP_STRUCT_REP_LENGTH,             &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrPsHkRepStructRepUpdateAction,                 &CrFwOutCmpDefSerialize},\
      {3, 10, 2,   crRepType,   CRPS_HK_HKREP_STRUCT_REP_LENGTH,             &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrPsHkRepStructRepUpdateAction,                 &CrFwOutCmpDefSerialize},\
      {3, 10, 3,   crRepType,   CRPS_HK_HKREP_STRUCT_REP_LENGTH,             &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrPsHkRepStructRepUpdateAction,                 &CrFwOutCmpDefSerialize},\
      {3, 12, 1,   crRepType,   CRPS_HK_HKREP_STRUCT_REP_LENGTH,             &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrPsHkRepStructRepUpdateAction,                 &CrFwOutCmpDefSerialize},\
      {3, 12, 2,   crRepType,   CRPS_HK_HKREP_STRUCT_REP_LENGTH,             &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrPsHkRepStructRepUpdateAction,                 &CrFwOutCmpDefSerialize},\
      {3, 12, 3,   crRepType,   CRPS_HK_HKREP_STRUCT_REP_LENGTH,             &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrPsHkRepStructRepUpdateAction,                 &CrFwOutCmpDefSerialize},\
      {3, 25, 1,   crRepType,   CRPS_HK_HKPARAM_REP_LENGTH,                  &CrPsHkRepEnableCheck,                        &CrPsHkRepReadyCheck,                        &CrFwSmCheckAlwaysTrue,                       &CrPsHkRepUpdateAction,                          &CrFwOutCmpDefSerialize},\
      {3, 25, 2,   crRepType,   CRPS_HK_HKPARAM_REP_LENGTH,                  &CrPsHkRepEnableCheck,                        &CrPsHkRepReadyCheck,                        &CrFwSmCheckAlwaysTrue,                       &CrPsHkRepUpdateAction,                          &CrFwOutCmpDefSerialize},\
      {3, 25, 3,   crRepType,   CRPS_HK_HKPARAM_REP_LENGTH,                  &CrPsHkRepEnableCheck,                        &CrPsHkRepReadyCheck,                        &CrFwSmCheckAlwaysTrue,                       &CrPsHkRepUpdateAction,                          &CrFwOutCmpDefSerialize},\
      {3, 26, 1,   crRepType,   CRPS_HK_HKPARAM_REP_LENGTH,                  &CrPsHkRepEnableCheck,                        &CrPsHkRepReadyCheck,                        &CrFwSmCheckAlwaysTrue,                       &CrPsHkRepUpdateAction,                          &CrFwOutCmpDefSerialize},\
      {3, 26, 2,   crRepType,   CRPS_HK_HKPARAM_REP_LENGTH,                  &CrPsHkRepEnableCheck,                        &CrPsHkRepReadyCheck,                        &CrFwSmCheckAlwaysTrue,                       &CrPsHkRepUpdateAction,                          &CrFwOutCmpDefSerialize},\
      {3, 26, 3,   crRepType,   CRPS_HK_HKPARAM_REP_LENGTH,                  &CrPsHkRepEnableCheck,                        &CrPsHkRepReadyCheck,                        &CrFwSmCheckAlwaysTrue,                       &CrPsHkRepUpdateAction,                          &CrFwOutCmpDefSerialize},\
      {5, 1,  1,   crRepType,   CRPS_EVT__REP_LENGTH,                        &CrPsEvtRepEnableCheck,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrPsEvtRepUpdateAction,                         &CrFwOutCmpDefSerialize},\
      {5, 2,  1,   crRepType,   CRPS_EVT__REP_LENGTH,                        &CrPsEvtRepEnableCheck,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrPsEvtRepUpdateAction,                         &CrFwOutCmpDefSerialize},\
      {5, 3,  1,   crRepType,   CRPS_EVT__REP_LENGTH,                        &CrPsEvtRepEnableCheck,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrPsEvtRepUpdateAction,                         &CrFwOutCmpDefSerialize},\
      {5, 4,  1,   crRepType,   CRPS_EVT__REP_LENGTH,                        &CrPsEvtRepEnableCheck,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrPsEvtRepUpdateAction,                         &CrFwOutCmpDefSerialize},\
      {5, 8,  0,   crRepType,   CRPS_EVT__REP_LENGTH,                        &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrPsEvtRepDisabledRepUpdateAction,              &CrFwOutCmpDefSerialize},\
      {13, 1, 0,   crRepType,   CRPS_LPT__REP_LENGTH,                        &CrPsLptDownFirstRepEnableCheck,              &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrPsLptDownFirstRepUpdateAction,                &CrFwOutCmpDefSerialize},\
      {13, 2, 0,   crRepType,   CRPS_LPT__REP_LENGTH,                        &CrPsLptDownInterRepEnableCheck,              &CrFwSmCheckAlwaysTrue,                      &CrPsLptDownInterRepRepeatCheck,              &CrPsLptDownInterRepUpdateAction,                &CrFwOutCmpDefSerialize},\
      {13, 3, 0,   crRepType,   CRPS_LPT__REP_LENGTH,                        &CrPsLptDownLastRepEnableCheck,               &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrPsLptDownLastRepUpdateAction,                 &CrFwOutCmpDefSerialize},\
      {13, 16, 0,  crRepType,   CRPS_LPT__REP_LENGTH,                        &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrPsLptUpAbortRepUpdateAction,                  &CrFwOutCmpDefSerialize},\
      {17, 1, 0,   crCmdType,   CRPS_TEST_AREYOUALIVE_CONNECTION_CMD_LENGTH, &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrPsTestAreYouAliveConnectionRepUpdateAction,   &CrFwOutCmpDefSerialize},\
      {17, 2, 0,   crRepType,   CRPS_TEST_AREYOUALIVE_CONNECTION_REP_LENGTH, &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrPsTestAreYouAliveConnectionRepUpdateAction,   &CrFwOutCmpDefSerialize},\
      {17, 4, 0,   crRepType,   CRPS_TEST_ONBOARD_CONNECTION_REP_LENGTH,     &CrFwSmCheckAlwaysTrue,                       &CrFwSmCheckAlwaysTrue,                      &CrFwSmCheckAlwaysFalse,                      &CrFwSmEmptyAction,                              &CrFwOutCmpDefSerialize} \
	}

#endif /* CRFW_OUTFACTORY_USERPAR_H_ */
