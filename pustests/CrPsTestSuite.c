/**
 * @file CrPsTestSuite.c
 * @ingropu PUSTestsuite
 *
 * Test Suite for the PUS extension of the CORDET Framework.
 * This file defines the <code>main</code> program for the PUS test suite.
 * The PUS test suite executes a number of test cases in sequence and reports
 * the outcome of each test case.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** The number of tests in the test suite. */
#define NOF_TESTS 23

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
#include "CrPsLptTestCases.h"


/**
 * Main program for the test suite.
 * The test suite executes a number of test cases in sequence and reports
 * the outcome of each test case.
 * A test case can either fail or succeed and reports its outcome as boolean.
 * @return always returns EXIT_SUCCESS
 */
int main() {
	uint32_t i;
	CrFwBool_t testOutcome;
	CrFwConfigCheckOutcome_t configCheckOutcome;
	char* testNames[NOF_TESTS];
	typedef CrFwBool_t (*testCase_t)();
	testCase_t testCases[NOF_TESTS]; /* array of pointers to SM test case functions */

	/* Check consistency of configuration parameters */
	configCheckOutcome = CrFwAuxConfigCheck();
	if (configCheckOutcome != crConsistencyCheckSuccess) {
		if (configCheckOutcome == crOutRegistryConfigParInconsistent)
			printf("Consistency check of OutRegistry parameters failed\n");
		if (configCheckOutcome == crOutFactoryConfigParInconsistent)
			printf("Consistency check of OutFactory parameters failed\n");
		if (configCheckOutcome == crInFactoryInCmdConfigParInconsistent)
			printf("Consistency check of InCommand parameters in InFactory failed\n");
		if (configCheckOutcome == crInFactoryInRepConfigParInconsistent)
			printf("Consistency check of InRepot parameters in InFactory failed\n");
		return EXIT_SUCCESS;
	}
	printf("Consistency check of configuration parameters ran successfully...\n");

	/* Set the names of the SM tests and the functions executing the tests */
    i=0;

	/*Getter and Setter*/
	testNames[i] = "Pusext_PacketGetterSetter_TestCase1";
	testCases[i] = &CrPsPcktGetSetTestCase1;
	i+=1;
	testNames[i] = "Pusext_PacketGetterSetter_TestCase2";
	testCases[i] = &CrPsPcktGetSetTestCase2;
	i+=1;
	testNames[i] = "Pusext_PacketGetterSetter_TestCase3";
	testCases[i] = &CrPsPcktGetSetTestCase3;
	i+=1;
	testNames[i] = "Pusext_PacketGetterSetter_TestCase4";
	testCases[i] = &CrPsPcktGetSetTestCase4;
	i+=1;

	/*Service 1*/
	testNames[i] = "Pusext_ServVeri_TestCase1";
	testCases[i] = &CrPsServVeriTestCase1;
	i+=1;
	/*Servuce 17*/
	testNames[i] = "Pusext_ServTestConn_TestCase1";
	testCases[i] = &CrPsServTestConnTestCase1;
	i+=1;
	testNames[i] = "Pusext_ServTestConn_TestCase2";
	testCases[i] = &CrPsServTestConnTestCase2;
	i+=1;
	testNames[i] = "Pusext_ServTestConn_TestCase3";
	testCases[i] = &CrPsServTestConnTestCase3;
	i+=1;
	
	/*DataPool*/
	testNames[i] = "Pusext_DataPool_TestCase1";
	testCases[i] = &CrPsDataPoolTestCase1;
	i+=1;
	testNames[i] = "Pusext_DataPool_TestCase2";
	testCases[i] = &CrPsDataPoolTestCase2;
	i+=1;
	testNames[i] = "Pusext_DataPool_TestCase3";
	testCases[i] = &CrPsDataPoolTestCase3;
	i+=1;
    testNames[i] = "Pusext_DataPool_TestCase4";
	testCases[i] = &CrPsDataPoolTestCase4;
	i+=1;
	testNames[i] = "Pusext_DataPool_TestCase5";
	testCases[i] = &CrPsDataPoolTestCase5;
	i+=1;
	testNames[i] = "Pusext_DataPool_TestCase6";
	testCases[i] = &CrPsDataPoolTestCase6;
	i+=1;
	
		/*Service 3*/
	testNames[i] = "Pusext_Housekeeping_TestCase1";
	testCases[i] = &CrPsHkTestCase1;
	i+=1;
	testNames[i] = "Pusext_Housekeeping_TestCase2";
	testCases[i] = &CrPsHkTestCase2;
	i+=1;
	testNames[i] = "Pusext_Housekeeping_TestCase3";
	testCases[i] = &CrPsHkTestCase3;
	i+=1;
	testNames[i] = "Pusext_Housekeeping_TestCase4";
	testCases[i] = &CrPsHkTestCase4;
	i+=1;

	/*Service 5*/
	testNames[i] = "Pusext_EventReporting_TestCase1";
	testCases[i] = &CrPsEvtTestCase1;
	i+=1;

	/*Service ¹3*/
	testNames[i] = "Pusext_LargePacketTransfer_TestCase1";
	testCases[i] = &CrPsLptTestCase1;
	i+=1;
	testNames[i] = "Pusext_LargePacketTransfer_TestCase2";
	testCases[i] = &CrPsLptTestCase2;
	i+=1;
	testNames[i] = "Pusext_LargePacketTransfer_TestCase3";
	testCases[i] = &CrPsLptTestCase3;
	i+=1;
	testNames[i] = "Pusext_LargePacketTransfer_TestCase4";
	testCases[i] = &CrPsLptTestCase4;
	i+=1;

	/* Run test cases in sequence */
	for (i=0; i<NOF_TESTS; i++) {
		testOutcome = testCases[i]();
		if (testOutcome == 1)
		{
			printf("Test case %s ran successfully ...\n", testNames[i]);
		}
		else
		{
			printf("Test case %s failed!\n", testNames[i]);
		}
	}

	return EXIT_SUCCESS;
}

