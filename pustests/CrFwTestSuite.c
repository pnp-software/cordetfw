/**
 * @file
 *
 * Test Suite for CORDET Framework.
 * This file defines the <code>main</code> program for the test suite.
 * The test suite executes a number of test cases in sequence and reports
 * the outcome of each test case.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** The number of tests in the test suite. */
#define NOF_TESTS 16

/* Include framework files */
#include "CrFwConstants.h"
#include "Aux/CrFwAux.h"

/* Include test suite files for tShe PUS extension */
#include "CrPsDataPoolTestCases.h"
#include "CrPsPcktGetSetTestCases.h"
#include "CrPsServiceTestCases.h"
#include "CrPsServiceVeriTestCases.h"
#include "CrPsHkTestCases.h"
#include "CrPsEvtTestCases.h"
#include "CrPsDebug.h"


/**
 * Main program for the test suite.
 * The test suite executes a number of test cases in sequence and reports
 * the outcome of each test case.
 * A test case can either fail or succeed and reports its outcome as boolean.
 * @return always returns EXIT_SUCCESS
 */
int main() {
	int i;
	CrFwBool_t testOutcome;
	CrFwConfigCheckOutcome_t configCheckOutcome;
	char* testNames[NOF_TESTS];
	typedef CrFwBool_t (*testCase_t)();
	testCase_t testCases[NOF_TESTS]; /* array of pointers to SM test case functions */

	/* Check consistency of configuration parameters */
	configCheckOutcome = CrFwAuxConfigCheck();
	if (configCheckOutcome != crConsistencyCheckSuccess) {
		if (configCheckOutcome == crOutRegistryConfigParInconsistent)
			DEBUGP("Consistency check of OutRegistry parameters failed\n");
		if (configCheckOutcome == crOutFactoryConfigParInconsistent)
			DEBUGP("Consistency check of OutFactory parameters failed\n");
		if (configCheckOutcome == crInFactoryInCmdConfigParInconsistent)
			DEBUGP("Consistency check of InCommand parameters in InFactory failed\n");
		if (configCheckOutcome == crInFactoryInRepConfigParInconsistent)
			DEBUGP("Consistency check of InRepot parameters in InFactory failed\n");
		return EXIT_SUCCESS;
	}
	DEBUGP("Consistency check of configuration parameters ran successfully...\n");

	/* Set the names of the SM tests and the functions executing the tests */
     
	/*Servuce 17*/
	testNames[0] = "Pusext_ServTestConn_TestCase1";
	testCases[0] = &CrPsServTestConnTestCase1;
	testNames[1] = "Pusext_ServTestConn_TestCase2";
	testCases[1] = &CrPsServTestConnTestCase2;
	testNames[2] = "Pusext_ServTestConn_TestCase3";
	testCases[2] = &CrPsServTestConnTestCase3;

	/*Service 1*/
	testNames[3] = "Pusext_ServVeri_TestCase1";
	testCases[3] = &CrPsServVeriTestCase1;

	/*DataPool*/
	testNames[4] = "Pusext_DataPool_TestCase1";
	testCases[4] = &CrPsDataPoolTestCase1;
	testNames[5] = "Pusext_DataPool_TestCase2";
	testCases[5] = &CrPsDataPoolTestCase2;
	testNames[6] = "Pusext_DataPool_TestCase3";
	testCases[6] = &CrPsDataPoolTestCase3;
    testNames[7] = "Pusext_DataPool_TestCase4";
	testCases[7] = &CrPsDataPoolTestCase4;
	
	/*Getter and Setter*/
	testNames[8] = "Pusext_PacketGetterSetter_TestCase1";
	testCases[8] = &CrPsPcktGetSetTestCase1;
	testNames[9] = "Pusext_PacketGetterSetter_TestCase2";
	testCases[9] = &CrPsPcktGetSetTestCase2;
	testNames[10] = "Pusext_PacketGetterSetter_TestCase3";
	testCases[10] = &CrPsPcktGetSetTestCase3;


	/*Service 3*/
	testNames[11] = "Pusext_Housekeeping_TestCase1";
	testCases[11] = &CrPsHkTestCase1;
	testNames[12] = "Pusext_Housekeeping_TestCase2";
	testCases[12] = &CrPsHkTestCase2;
	testNames[13] = "Pusext_Housekeeping_TestCase3";
	testCases[13] = &CrPsHkTestCase3;
	testNames[14] = "Pusext_Housekeeping_TestCase4";
	testCases[14] = &CrPsHkTestCase4;

	/*Service 5*/
	testNames[15] = "Pusext_EventReporting_TestCase1";
	testCases[15] = &CrPsEvtTestCase1;



	/* Run test cases in sequence */
	for (i=0; i<NOF_TESTS; i++) {
		testOutcome = testCases[i]();
		if (testOutcome == 1)
		{
			DEBUGP_GREEN("Test case %s ran successfully ...\n", testNames[i]);
		}
		else
		{
			DEBUGP_RED("Test case %s failed!\n", testNames[i]);
		}
	}

	return EXIT_SUCCESS;
}

