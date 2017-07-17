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
#define NOF_TESTS 11

/* Include framework files */
#include "CrFwConstants.h"
#include "Aux/CrFwAux.h"
/* Include test suite files */
#include "CrFwBaseCmpTestCases.h"
#include "CrFwPacketTestCases.h"
#include "CrFwOutStreamTestCases.h"
#include "CrFwOutCmpTestCases.h"
#include "CrFwOutFactoryTestCases.h"
#include "CrFwInStreamTestCases.h"
#include "CrFwOutRegistryTestCases.h"
#include "CrFwOutManagerTestCases.h"
#include "CrFwOutLoaderTestCases.h"
#include "CrFwUtilityFunctionsTestCases.h"
#include "CrFwInFactoryTestCases.h"
#include "CrFwInCmdTestCases.h"
#include "CrFwInRepTestCases.h"
#include "CrFwInRegistryTestCases.h"
#include "CrFwInManagerTestCases.h"
#include "CrFwInLoaderTestCases.h"
#include "CrFwAppSmTestCases.h"
#include "CrFwSocketTestCases.h"
/* Include test suite files for tShe PUS extension */
#include "CrPsDataPoolTestCases.h"
#include "CrPsServiceTestCases.h"
#include "CrPsServiceVeriTestCases.h"
#include "CrPsServiceOnBoardTestCases.h"

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
        /*
	testNames[0] = "BaseCmp_TestCase1";
	testCases[0] = &CrFwBaseCmpTestCase1;
	testNames[1] = "Packet_TestCase1";
	testCases[1] = &CrFwPacketTestCase1;
	testNames[2] = "Packet_TestCase2";
	testCases[2] = &CrFwPacketTestCase2;
	testNames[3] = "OutStream_TestCase1";
	testCases[3] = &CrFwOutStreamTestCase1;
	testNames[4] = "OutStream_TestCase2";
	testCases[4] = &CrFwOutStreamTestCase2;
	testNames[5] = "OutStream_TestCase3";
	testCases[5] = &CrFwOutStreamTestCase3;
	testNames[6] = "OutStream_TestCase4";
	testCases[6] = &CrFwOutStreamTestCase4;
	testNames[7] = "InStream_TestCase1";
	testCases[7] = &CrFwInStreamTestCase1;
	testNames[8] = "InStream_TestCase2";
	testCases[8] = &CrFwInStreamTestCase2;
	testNames[9] = "InStream_TestCase3";
	testCases[9] = &CrFwInStreamTestCase3;
	testNames[10] = "InStream_TestCase4";
	testCases[10] = &CrFwInStreamTestCase4;
	testNames[11] = "InStream_TestCase5";
	testCases[11] = &CrFwInStreamTestCase5;
	testNames[12] = "InStream_TestCase6";
	testCases[12] = &CrFwInStreamTestCase6;
	testNames[13] = "OutStream_TestCase5";
	testCases[13] = &CrFwOutStreamTestCase5;
	testNames[14] = "PacketQueue_TestCase1";
	testCases[14] = &CrFwPacketQueueTestCase1;
	testNames[15] = "OutRegistry_TestCase1";
	testCases[15] = &CrFwOutRegistryTestCase1;
	testNames[16] = "OutRegistry_TestCase2";
	testCases[16] = &CrFwOutRegistryTestCase2;
	testNames[17] = "OutRegistry_TestCase3";
	testCases[17] = &CrFwOutRegistryTestCase3;
	testNames[18] = "OutRegistry_TestCase4";
	testCases[18] = &CrFwOutRegistryTestCase4;
	testNames[19] = "OutRegistry_TestCase5";
	testCases[19] = &CrFwOutRegistryTestCase5;
	testNames[20] = "OutRegistry_TestCase6";
	testCases[20] = &CrFwOutRegistryTestCase6;
	testNames[21] = "OutRegistry_TestCase7";
	testCases[21] = &CrFwOutRegistryTestCase7;
	testNames[22] = "OutRegistry_TestCase8";
	testCases[22] = &CrFwOutRegistryTestCase8;
	testNames[23] = "OutRegistry_TestCase9";
	testCases[23] = &CrFwOutRegistryTestCase9;
	testNames[24] = "OutFactory_TestCase1";
	testCases[24] = &CrFwOutFactoryTestCase1;
	testNames[25] = "OutFactory_TestCase2";
	testCases[25] = &CrFwOutFactoryTestCase2;
	testNames[26] = "OutFactory_TestCase3";
	testCases[26] = &CrFwOutFactoryTestCase3;
	testNames[27] = "OutCmp_TestCase1";
	testCases[27] = &CrFwOutCmpTestCase1;
	testNames[28] = "OutCmp_TestCase2";
	testCases[28] = &CrFwOutCmpTestCase2;
	testNames[29] = "OutCmp_TestCase3";
	testCases[29] = &CrFwOutCmpTestCase3;
	testNames[30] = "OutCmp_TestCase4";
	testCases[30] = &CrFwOutCmpTestCase4;
	testNames[31] = "OutCmp_TestCase5";
	testCases[31] = &CrFwOutCmpTestCase5;
	testNames[32] = "OutCmp_TestCase6";
	testCases[32] = &CrFwOutCmpTestCase6;
	testNames[33] = "OutManager_TestCase1";
	testCases[33] = &CrFwOutManagerTestCase1;
	testNames[34] = "OutManager_TestCase2";
	testCases[34] = &CrFwOutManagerTestCase2;
	testNames[35] = "OutManager_TestCase3";
	testCases[35] = &CrFwOutManagerTestCase3;
	testNames[36] = "OutManager_TestCase4";
	testCases[36] = &CrFwOutManagerTestCase4;
	testNames[37] = "OutLoader_TestCase1";
	testCases[37] = &CrFwOutLoaderTestCase1;
	testNames[38] = "UtilityFunctions_TestCase1";
	testCases[38] = &CrFwUtilityFunctionsTestCase1;
	testNames[39] = "InFactory_TestCase1";
	testCases[39] = &CrFwInFactoryTestCase1;
	testNames[40] = "InFactory_TestCase2";
	testCases[40] = &CrFwInFactoryTestCase2;
	testNames[41] = "InFactory_TestCase3";
	testCases[41] = &CrFwInFactoryTestCase3;
	testNames[42] = "InFactory_TestCase4";
	testCases[42] = &CrFwInFactoryTestCase4;
	testNames[43] = "InFactory_TestCase5";
	testCases[43] = &CrFwInFactoryTestCase5;
	testNames[44] = "InFactory_TestCase6";
	testCases[44] = &CrFwInFactoryTestCase6;
	testNames[45] = "InFactory_TestCase7";
	testCases[45] = &CrFwInFactoryTestCase7;
	testNames[46] = "OutFactory_TestCase4";
	testCases[46] = &CrFwOutFactoryTestCase4;
	testNames[47] = "InCommand_TestCase1";
	testCases[47] = &CrFwInCmdTestCase1;
	testNames[48] = "InCommand_TestCase2";
	testCases[48] = &CrFwInCmdTestCase2;
	testNames[49] = "InCommand_TestCase3";
	testCases[49] = &CrFwInCmdTestCase3;
	testNames[50] = "InCommand_TestCase4";
	testCases[50] = &CrFwInCmdTestCase4;
	testNames[51] = "InCommand_TestCase5";
	testCases[51] = &CrFwInCmdTestCase5;
	testNames[52] = "InCommand_TestCase6";
	testCases[52] = &CrFwInCmdTestCase6;
	testNames[53] = "InCommand_TestCase7";
	testCases[53] = &CrFwInCmdTestCase7;
	testNames[54] = "InCommand_TestCase8";
	testCases[54] = &CrFwInCmdTestCase8;
	testNames[55] = "InCommand_TestCase9";
	testCases[55] = &CrFwInCmdTestCase9;
	testNames[56] = "InCommand_TestCase10";
	testCases[56] = &CrFwInCmdTestCase10;
	testNames[57] = "InCommand_TestCase11";
	testCases[57] = &CrFwInCmdTestCase11;
	testNames[58] = "InCommand_TestCase12";
	testCases[58] = &CrFwInCmdTestCase12;
	testNames[59] = "InReport_TestCase1";
	testCases[59] = &CrFwInRepTestCase1;
	testNames[60] = "InReport_TestCase2";
	testCases[60] = &CrFwInRepTestCase2;
	testNames[61] = "InReport_TestCase3";
	testCases[61] = &CrFwInRepTestCase3;
	testNames[62] = "InRegistry_TestCase1";
	testCases[62] = &CrFwInRegistryTestCase1;
	testNames[63] = "InRegistry_TestCase2";
	testCases[63] = &CrFwInRegistryTestCase2;
	testNames[64] = "InRegistry_TestCase3";
	testCases[64] = &CrFwInRegistryTestCase3;
	testNames[65] = "InRegistry_TestCase4";
	testCases[65] = &CrFwInRegistryTestCase4;
	testNames[66] = "InManager_TestCase1";
	testCases[66] = &CrFwInManagerTestCase1;
	testNames[67] = "InManager_TestCase2";
	testCases[67] = &CrFwInManagerTestCase2;
	testNames[68] = "InManager_TestCase3";
	testCases[68] = &CrFwInManagerTestCase3;
	testNames[69] = "InManager_TestCase4";
	testCases[69] = &CrFwInManagerTestCase4;
	testNames[70] = "InManager_TestCase5";
	testCases[70] = &CrFwInManagerTestCase5;
	testNames[71] = "InManager_TestCase6";
	testCases[71] = &CrFwInManagerTestCase6;
	testNames[72] = "InManager_TestCase7";
	testCases[72] = &CrFwInManagerTestCase7;
	testNames[73] = "InManager_TestCase8";
	testCases[73] = &CrFwInManagerTestCase8;
	testNames[74] = "InLoader_TestCase1";
	testCases[74] = &CrFwInLoaderTestCase1;
	testNames[75] = "InLoader_TestCase2";
	testCases[75] = &CrFwInLoaderTestCase2;
	testNames[76] = "InLoader_TestCase3";
	testCases[76] = &CrFwInLoaderTestCase3;
	testNames[77] = "InLoader_TestCase4";
	testCases[77] = &CrFwInLoaderTestCase4;
	testNames[78] = "InLoader_TestCase5";
	testCases[78] = &CrFwInLoaderTestCase5;
	testNames[79] = "InLoader_TestCase6";
	testCases[79] = &CrFwInLoaderTestCase6;
	testNames[80] = "InLoader_TestCase7";
	testCases[80] = &CrFwInLoaderTestCase7;
	testNames[81] = "InLoader_TestCase8";
	testCases[81] = &CrFwInLoaderTestCase8;
	testNames[82] = "InLoader_TestCase9";
	testCases[82] = &CrFwInLoaderTestCase9;
	testNames[83] = "InLoader_TestCase10";
	testCases[83] = &CrFwInLoaderTestCase10;
	testNames[84] = "InLoader_TestCase11";
	testCases[84] = &CrFwInLoaderTestCase11;
	testNames[85] = "UtilityFunctions_TestCase2";
	testCases[85] = &CrFwUtilityFunctionsTestCase2;
	testNames[86] = "ApplicationStateMachine_TestCase1";
	testCases[86] = &CrFwAppSmTestCase1;
	testNames[87] = "Socket_TestCase1";
	testCases[87] = &CrFwSocketTestCase1;
	testNames[88] = "Socket_TestCase2";
	testCases[88] = &CrFwSocketTestCase2;
	testNames[89] = "Socket_TestCase3";
	testCases[89] = &CrFwSocketTestCase3;
	testNames[90] = "Socket_TestCase4";
	testCases[90] = &CrFwSocketTestCase4;
	testNames[91] = "OutStream_TestCase6";
	testCases[91] = &CrFwOutStreamTestCase6;
	testNames[92] = "OutCmp_TestCase7";
	testCases[92] = &CrFwOutCmpTestCase7;
	testNames[93] = "OutCmp_TestCase8";
	testCases[93] = &CrFwOutCmpTestCase8;
	testNames[94] = "OutCmp_TestCase9";
	testCases[94] = &CrFwOutCmpTestCase9;
	testNames[95] = "OutStream_TestCase7";
	testCases[95] = &CrFwOutStreamTestCase7;
	testNames[96] = "InStream_TestCase7";
	testCases[96] = &CrFwInStreamTestCase7;
        */
	testNames[0] = "Pusext_DataPool_TestCase1";
	testCases[0] = &CrPsDataPoolTestCase1;
	testNames[1] = "Pusext_DataPool_TestCase2";
	testCases[1] = &CrPsDataPoolTestCase2;
        
        testNames[2] = "Pusext_ServVeri_TestCase1";
	testCases[2] = &CrPsServVeriTestCase1;
        
	testNames[3] = "Pusext_ServTestConn_TestCase1";
	testCases[3] = &CrPsServTestConnTestCase1;
	testNames[4] = "Pusext_ServTestConn_TestCase2";
	testCases[4] = &CrPsServTestConnTestCase2;
	testNames[5] = "Pusext_ServTestConn_TestCase3";
	testCases[5] = &CrPsServTestConnTestCase3;
	testNames[6] = "Pusext_ServTestConn_TestCase4";
	testCases[6] = &CrPsServTestConnTestCase4;
        
	testNames[7] = "Pusext_ServTestOnBoard_TestCase1";
	testCases[7] = &CrPsServTestOnBoardTestCase1;
	testNames[8] = "Pusext_ServTestOnBoard_TestCase2";
	testCases[8] = &CrPsServTestOnBoardTestCase2;
    testNames[9] = "Pusext_ServTestOnBoard_TestCase3";
	testCases[9] = &CrPsServTestOnBoardTestCase3;
    testNames[10] = "Pusext_ServTestOnBoard_TestCase4";
	testCases[10] = &CrPsServTestOnBoardTestCase4;
       

	/* Run test cases in sequence */
	for (i=0; i<NOF_TESTS; i++) {
		testOutcome = testCases[i]();
		if (testOutcome == 1)
			printf("Test case %s ran successfully ...\n", testNames[i]);
		else
			printf("Test case %s failed!\n", testNames[i]);
	}

	return EXIT_SUCCESS;
}

