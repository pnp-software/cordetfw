/**
 * @file CrPsCmd3s10StartFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:16:40
 */

/** CrPsCmd3s10Start function definitions */
#include "CrPsCmd3s10StartCreate.h"

/** CR Framework function definitions*/
#include "CrFwConstants.h"

/** FW Profile function definitions */
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CrPsDebug.h"

/* ----------------------------------------------------------------------------------------------------------------- */

/** Action for node N1. */
void CrPsCmd3s10StartN1(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* etermine the identifier of the LPT Buffer  */

	DEBUGP_3("CrPsCmd3s10StartN1.\n");
}

/** Action for node N2. */
void CrPsCmd3s10StartN2(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Set action  outcome to 'Failure' */
	
	DEBUGP_3("CrPsCmd3s10StartN2.\n");
}

/** Action for node N3. */
void CrPsCmd3s10StartN3(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Set lptFailCode to PART_NMB_ERR */
	
	DEBUGP_3("CrPsCmd3s10StartN3.\n");
}

/** Action for node N4. */
void CrPsCmd3s10StartN4(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Set action outcome to 'Success' */
	
	DEBUGP_3("CrPsCmd3s10StartN4.\n");
}

/** Guard on the Control Flow from DECISION1 to N2. */
FwPrBool_t CrPsCmd3s10StartG1(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* LPT State Machine associated to LPT Buffer is not in state UP_TRANSFER  */
	
	DEBUGP_3("CrPsCmd3s10StartG1.\n");
	return 0;
}

/** Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsCmd3s10StartG2(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Flag_1  */
	
	DEBUGP_3("CrPsCmd3s10StartG2.\n");
	return 0;
}

/* ----------------------------------------------------------------------------------------------------------------- */

