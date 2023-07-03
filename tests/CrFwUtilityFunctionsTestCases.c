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
#include "CrFwOutRegistryUserPar.h"
#include "OutRegistry/CrFwOutRegistry.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "InCmd/CrFwInCmd.h"
#include "InFactory/CrFwInFactory.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
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

	if (CrFwFindKeyIndex(testArray1,CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE,8) != 2)
		return 0;
	if (CrFwFindKeyIndex(testArray2,CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE,8) != 2)
		return 0;

	if (CrFwFindKeyIndex(testArray1,CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE,10) != 3)
		return 0;
	if (CrFwFindKeyIndex(testArray2,CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE,10) != 3)
		return 0;

	if (CrFwFindKeyIndex(testArray1,CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE,4) != 0)
		return 0;
	if (CrFwFindKeyIndex(testArray2,CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE,4) != 0)
		return 0;

	if (CrFwFindKeyIndex(testArray1,CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE,
	                            2*CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE+4) != CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE)
		return 0;
	if (CrFwFindKeyIndex(testArray2,CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE,
	                            2*CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE+4) != CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE)
		return 0;

	if (CrFwFindKeyIndex(testArray1,CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE,2) !=
	        CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE)
		return 0;
	if (CrFwFindKeyIndex(testArray2,CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE,2) !=
	        CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE)
		return 0;

	if (CrFwFindKeyIndex(testArray1,CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE,60) !=
	        CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE)
		return 0;
	if (CrFwFindKeyIndex(testArray2,CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE,60) !=
	        CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE)
		return 0;

	if (CrFwFindKeyIndex(testArray1,CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE,11) !=
	        CR_FW_UTILITYFUNCTIONS_TESTCASES_EVEN_SIZE)
		return 0;
	if (CrFwFindKeyIndex(testArray2,CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE,11) !=
	        CR_FW_UTILITYFUNCTIONS_TESTCASES_ODD_SIZE)
		return 0;

	if (CrFwFindKeyIndex(testArray3,1,5) != 0)
		return 0;

	if (CrFwFindKeyIndex(testArray3,1,6) != 1)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwUtilityFunctionsTestCase2() {
    FwSmDesc_t inFactory, inCmd1;
    CrFwPckt_t pckt1;
    CrFwCrc_t crc;

    /* Instantiate the InFactory */
    inFactory = CrFwInFactoryMake();

    /* Initialize and Configure InFactory and check success */
    CrFwCmpInit(inFactory);
    CrFwCmpReset(inFactory);
    if (!CrFwCmpIsInConfigured(inFactory))
        return 0;

    /* Allocate two InCommands of which one has the correct CRC and one the incorrect CRC */
    pckt1 = CrFwPcktMake(100);
    CrFwPcktSetServType(pckt1,8);
    CrFwPcktSetServSubType(pckt1,1);
    CrFwPcktSetDiscriminant(pckt1,2);
    CrFwPcktSetCmdRepId(pckt1,111);
    CrFwPcktSetSrc(pckt1,11);
    CrFwPcktSetGroup(pckt1,88);
    CrFwPcktSetAckLevel(pckt1,1,0,1,0);
    CrFwPcktSetSeqCnt(pckt1,1111);
    crc = CrFwPcktComputeCrc(pckt1);
    CrFwPcktSetCrc(pckt1, crc);
    inCmd1 = CrFwInFactoryMakeInCmd(pckt1);
	if (CrFwSmCheckAlwaysTrue(NULL) != 1)
		return 0;

	/* Execute the Empty Action */
	CrFwSmEmptyAction(NULL);

	/* Execute the Success Action and verify that it sets the command's outcome to 1 */
	CrFwSetSmOutcome(inCmd1, 0);
	CrFwSmSuccessAction(inCmd1);
	if (CrFwGetSmOutcome(inCmd1) != 1)
	    return 0;

	/* Release the InCommand */
    CrFwInFactoryReleaseInCmd(inCmd1);

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}
