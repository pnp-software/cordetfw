/**
 * @file
 *
 * Implementation of test cases for the Utility Functions.
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

#include <stdlib.h>
#include "CrFwUtilityFunctionsTestCases.h"
/* Include framework files */
#include "UtilityFunctions/CrFwUtilityFunctions.h"

/** The even size of the test array */
#define CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE 20
/** The odd size of the test array */
#define CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE 21

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwUtilityFunctionsTestCase1() {
	CrFwCmdRepKindKey_t testArray1[CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE];
	CrFwCmdRepKindKey_t testArray2[CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE];
	CrFwCmdRepKindKey_t testArray3[1];
	CrFwCmdRepKindIndex_t i;

	/* Fill up the test arrays */
	for (i=0; i<CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE; i++)
		testArray1[i] = (CrFwCmdRepKindKey_t)(2*i+4);

	for (i=0; i<CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE; i++)
		testArray2[i] = (CrFwCmdRepKindKey_t)(2*i+4);

	testArray3[0] = 5;

	if (CrFwFindCmdRepKindIndex(testArray1,CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE,8) != 2)
		return 0;
	if (CrFwFindCmdRepKindIndex(testArray2,CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE,8) != 2)
		return 0;

	if (CrFwFindCmdRepKindIndex(testArray1,CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE,10) != 3)
		return 0;
	if (CrFwFindCmdRepKindIndex(testArray2,CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE,10) != 3)
		return 0;

	if (CrFwFindCmdRepKindIndex(testArray1,CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE,4) != 0)
		return 0;
	if (CrFwFindCmdRepKindIndex(testArray2,CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE,4) != 0)
		return 0;

	if (CrFwFindCmdRepKindIndex(testArray1,CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE,
	                            2*CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE+4) != CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE)
		return 0;
	if (CrFwFindCmdRepKindIndex(testArray2,CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE,
	                            2*CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE+4) != CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE)
		return 0;

	if (CrFwFindCmdRepKindIndex(testArray1,CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE,2) !=
	        CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE)
		return 0;
	if (CrFwFindCmdRepKindIndex(testArray2,CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE,2) !=
	        CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE)
		return 0;

	if (CrFwFindCmdRepKindIndex(testArray1,CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE,60) !=
	        CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE)
		return 0;
	if (CrFwFindCmdRepKindIndex(testArray2,CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE,60) !=
	        CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE)
		return 0;

	if (CrFwFindCmdRepKindIndex(testArray1,CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE,11) !=
	        CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE)
		return 0;
	if (CrFwFindCmdRepKindIndex(testArray2,CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE,11) !=
	        CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE)
		return 0;

	if (CrFwFindCmdRepKindIndex(testArray3,1,5) != 0)
		return 0;

	if (CrFwFindCmdRepKindIndex(testArray3,1,6) != 1)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwUtilityFunctionsTestCase2() {

	if (CrFwSmCheckAlwaysTrue(NULL) != 1)
		return 0;

	CrFwSmEmptyAction(NULL);

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}
