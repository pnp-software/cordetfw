/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the InReport Component (see <code>CrFwInRep.h</code>).
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

#ifndef CRFW_INREP_TESTCASES_H_
#define CRFW_INREP_TESTCASES_H_

#include "CrFwConstants.h"

/**
 * Check the configuration of a newly created InReport.
 * The following actions are performed in this test:
 * - The InFactory is reset and then two InReports are retrieved from the InFactory
 *   and it is checked that their instance identifier and type identifier are correct.
 * - It is checked that the InReports are initially in state CONFIGURED.
 * - It is checked that the InReport is correctly configured.
 * - It is checked that the service type and sub-type and the discriminant value of the
 *   InReport are correct.
 * - It is checked that the InReport source, group and sequence counter are correctly set.
 * - The function to retrieve the packet holding an InReport is checked
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInRepTestCase1();

/**
 * Check the failure of the Validity Check of an InReport.
 * The following actions are performed in this test:
 * - The InFactory is reset and then one Sample1 InReport (see <code>CrFwInRepSample1.h</code>) is
 *   retrieved from the InFactory.
 * - The validity check of the InReport is configured to return: "not valid" and it is checked that
 *   that the InReport is returned by the InFactory in state INITIALIZED.
 * - It is checked that the InReport's type as computed by the Validity Check of the Sample1 InReport
 *   is correct.
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInRepTestCase2();

/**
 * Check the update action of an InReport.
 * The following actions are performed in this test:
 * - The InFactory is reset and then one Sample1 InReport (see <code>CrFwInRepSample1.h</code>) is
 *   retrieved from the InFactory.
 * - The validity check of the InReport is configured to return: "valid".
 * - The InReport is executed and it is checked that the Update Action has been executed once.
 * - The InReport is executed again and it is checked that the Update Action is not executed.
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInRepTestCase3();


#endif /* CRFW_INREP_TESTCASES_H_ */
