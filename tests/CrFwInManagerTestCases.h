/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the InManager Component (see <code>CrFwInManager.h</code>).
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

#ifndef CRFW_INMANAGER_TESTCASES_H_
#define CRFW_INMANAGER_TESTCASES_H_

#include "CrFwConstants.h"

/**
 * Check the configuration of a newly created InManager.
 * The following actions are performed in this test:
 * - The first InManager is created and it is checked that it is in state CREATED.
 * - The InManager is initialized and reset and it is checked that it is in state CONFIGURED.
 * - The instance identifier and the type identifier of the InManager is checked.
 * - It is checked that the PCRL is empty and has the expected size.
 * - It is checked that the number of successfully loaded InCommands/InReports is zero
 * - An attempt is made to create an InManager with an illegal identifier and it is
 *   verified that this results in the application error code being set.
 * .
 * @verify Base Component SM Transition: IPS->CREATED
 * @verify Base Component SM Transition: CREATED->INITIALIZED
 * @verify Base Component SM Transition: INITIALIZED->CONFIGURED
 * @verify Application Error: crInManagerIllId
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInManagerTestCase1();

/**
 * Check the load function of an InManager.
 * The following actions are performed in this test:
 * - The second InManager is created, initialized and configured.
 * - The InFactory and InFactory are created, initialized and configured.
 * - The instance identifier of the InManager is checked.
 * - An InReport and an InCommand are loaded into the InManager and it is checked that the
 *   number of loaded components is correctly reported.
 * - More components are loaded until the number of loaded components exceeds the
 *   size of the InManager's PCRL; it is checked that the correct error report is generated.
 * - It is checked that the number of successfully loaded InCommands/InReports is successfully
 *   updated
 * - The InManager is reset and it is checked that the PCRL is cleared and that the number of
 *   loaded InReports/InCommands is reset to zero.
 * .
 * @verify Base Component SM Transition: CONFIGURED->CONFIGURED
 * @verify InManager Load Procedure: PCRL is full
 * @verify InManager Load Procedure: PCRL is not full
 * @verify Error Report: crInManagerPcrlFull
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInManagerTestCase2();

/**
 * Check the execution function of an InManager with one single InReport loaded.
 * The following actions are performed in this test:
 * - An InManager is created, initialized and configured.
 * - The InRegistry is created, initialized and configured.
 * - The InFactory is created, initialized and configured.
 * - The empty InManager is executed twice.
 * - One instance of the Sample 1 InReport is created and it is loaded in the InManager.
 * - The InManager is repeatedly executed and it is checked that the execution is
 *   propagated to the InReport.
 * - The InManager is executed and it is checked that the InReport is
 *   executed and that the InRegistry correctly tracks its change of state.
 * .
 * @verify InManager Execution Procedure: i is smaller or equal to number of items in PCRL
 * @verify InManager Execution Procedure: i is greater than the number of items in PCRL
 * @verify InManager Execution Procedure: Flag_1 is true
 * @verify InManager Load Procedure: PCRL is not full
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInManagerTestCase3();

/**
 * Check the execution function of an InManager with one InCommand loaded.
 * The following actions are performed in this test:
 * - An InManager is created, initialized and configured.
 * - The InRegistry is created, initialized and configured.
 * - The InFactory is created, initialized and configured.
 * - One instance of the Sample 1 InCommand is created and it is loaded in the InManager.
 * - The Sample InCommand is configured to remain pending.
 * - The InManager is repeatedly executed and it is checked that the execution is
 *   propagated to the InCommand and that the InCommand remains loaded in the InManager.
 * - The InCommand is configured to terminate and then the InManager is executed.
 * - The InManager is executed and it is checked that the InCommand is
 *   unloaded and that the InRegistry correctly tracks its change of state.
 * .
 * @verify InManager Execution Procedure: i is smaller or equal to number of items in PCRL
 * @verify InManager Execution Procedure: i is greater than the number of items in PCRL
 * @verify InManager Execution Procedure: Flag_1 is true
 * @verify InManager Execution Procedure: Flag_1 is false
 * @verify InManager Load Procedure: PCRL is not full
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInManagerTestCase4();

/**
 * Check the execution function of an InManager with one InCommand loaded.
 * The following actions are performed in this test:
 * - An InManager is created, initialized and configured.
 * - The InRegistry is created, initialized and configured.
 * - The InFactory is created, initialized and configured.
 * - One instance of the Sample 1 InCommand is created and it is loaded in the InManager.
 * - The Sample InCommand is configured to be aborted.
 * - The InManager is executed and it is checked that the InCommand is
 *   unloaded and that the InRegistry correctly tracks its change of state.
 * .
 * @verify InManager Execution Procedure: i is smaller or equal to number of items in PCRL
 * @verify InManager Execution Procedure: i is greater than the number of items in PCRL
 * @verify InManager Execution Procedure: Flag_1 is true
 * @verify InManager Execution Procedure: Flag_1 is false
 * @verify InManager Load Procedure: PCRL is not full
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInManagerTestCase5();

/**
 * Check the execution function of an InManager with several InReports and InCommands loaded.
 * The following actions are performed in this test:
 * - An InManager is created, initialized and configured.
 * - The InRegistry is created, initialized and configured.
 * - The InFactory and InFactory are created, initialized and configured.
 * - Two instances of Sample 1 InCommands and two instances of "standard" InReports are created.
 * - The InCommands are configured to remain pending.
 * - The InReport and InCommand instances are loaded in the InManager
 * - The InManager is repeatedly executed and it is checked that the InReports are unloaded
 *   and that the InCommands remain loaded.
 * - Two more standard InReports are loaded in the InManager and the InManager is
 *   executed once.
 * - The InManager is executed and it is checked that the standard InReports are
 *   unloaded while the sample InComponents remain pending.
 * - The Sample InCommands are configured to be terminated.
 * - The correct update of the counter of successfully loaded commands and reports is checked
 * - The InManager is executed and it is checked that the InCommands are unloaded.
 * - It is checked that the InRegistry correctly tracks the change of state in the
 *   InReports and InCommands.
 * .
 * @verify InManager Execution Procedure: i is smaller or equal to number of items in PCRL
 * @verify InManager Execution Procedure: i is greater than the number of items in PCRL
 * @verify InManager Execution Procedure: outCmp is in state PENDING
 * @verify InManager Execution Procedure: outCmp is not in state PENDING
 * @verify InManager Load Procedure: PCRL is not full
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInManagerTestCase6();

/**
 * Check the reset function of an InManager.
 * The following actions are performed in this test:
 * - An InManager is created, initialized and configured.
 * - The InRegistry is created, initialized and configured.
 * - The InFactory and InFactory are created, initialized and configured.
 * - Two instances of Sample 1 InCommands and two instances of "standard" InReports are created.
 * - The InManager is reset and it is checked that all InReports and InCommands have been unloaded
 *   and released.
 * .
 * @verify InManager Load Procedure: PCRL is not full
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInManagerTestCase7();

/**
 * Check the shutdown function of an InManager.
 * The following actions are performed in this test:
 * - An InManager is created, initialized and configured.
 * - The InRegistry is created, initialized and configured.
 * - The InFactory and InFactory are created, initialized and configured.
 * - Two instances of Sample 1 InCommands and two instances of "standard" InReports are created.
 * - The InManager is shutdown and it is checked that all InReports and InCommands have been
 *   unloaded and released.
 * - The InManager is started, initialized and reset and it is checked that it re-enters state
 *   CONFIGURED.
 * .
 * @verify InManager Load Procedure: PCRL is not full
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInManagerTestCase8();

#endif /* CRFW_INMANAGER_TESTCASES_H_ */
