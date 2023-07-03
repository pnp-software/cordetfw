/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the Utility Functions (see <code>CrFwUtilityFunctions.h</code>).
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

#ifndef CRFW_UTILITYFUNCTIONS_TESTCASES_H_
#define CRFW_UTILITYFUNCTIONS_TESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmCore.h"

/**
 * Test the <code>::CrFwFindKeyIndex</code> function.
 * The following actions are performed in this test:
 * - A test array of type <code>::CrFwCmdRepKindKey_t</code> is set up and filled with key values
 *   in increasing order to simulate an array of report or command kinds. The size of this test array
 *   is an even integer.
 * - The test array is searched through function <code>:.CrFwFindKeyIndex</code> for a key
 *   which is present in the array in an odd-numbered intermediate position.
 * - The test array is searched through function <code>:.CrFwFindKeyIndex</code> for a key
 *   which is present in the array in an even-numbered intermediate position.
 * - The test array is searched through function <code>:.CrFwFindKeyIndex</code> for the first
 *   key in the array.
 * - The test array is searched through function <code>:.CrFwFindKeyIndex</code> for a key
 *   which is smaller than all the key in the test array.
 * - The test array is searched through function <code>:.CrFwFindKeyIndex</code> for a key
 *   which is larger than all the key in the test array.
 * - The test array is searched through function <code>:.CrFwFindKeyIndex</code> for a key
 *   which is within the range of keys stored in the test array but is not present in the array.
 * - The same steps as above are repeated for a test array with a size equal to an odd number.
 * - A test array of size 1 is defined and both a successful and a failed search are verified.
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwUtilityFunctionsTestCase1();

/**
 * Test the convenience utility functions which are not exercised in other test cases.
 * The following actions are performed in this test:
 * - Function <code>::CrFwSmCheckAlwaysTrue</code> is called with a dummy argument and it is
 *   verified that it returns 1.
 * - Function <code>::CrFwSmEmptyAction</code> is called with a dummy argument and it is
 *   verified that it returns without doing anything.
 * - Function <code>::CrFwSmSuccessAction</code> is called with a command as dummy argument and it is
 *   verified that it returns after setting its success outcome to 1.
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwUtilityFunctionsTestCase2();

#endif /* CRFW_UTILITYFUNCTIONS_TESTCASES_H_ */
