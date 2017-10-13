/**
 * @file CrPsCmd3s9PrgrFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:16:17
 */

/** CrPsCmd3s9Prgr function definitions */
#include "CrPsCmd3s9PrgrCreate.h"

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
void CrPsCmd3s9PrgrN1(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Retrieve a (3,10) or (3,12) report from the OutFactory to hold
     * the structurereport for the SID which is being processed */

	DEBUGP_3("CrPsCmd3s9PrgrN1.\n");
}

/** Action for node N2. */
void CrPsCmd3s9PrgrN2(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Load the SID which is being processed in data pool item verFailData */

	DEBUGP_3("CrPsCmd3s9PrgrN2.\n");
}

/** Action for node N3. */
void CrPsCmd3s9PrgrN3(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Run the Command Progress Failure Procedure */

	DEBUGP_3("CrPsCmd3s9PrgrN3.\n");
}

/** Action for node N4. */
void CrPsCmd3s9PrgrN4(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Generate error report OUTFACTORY_FAIL */

	DEBUGP_3("CrPsCmd3s9PrgrN4.\n");
}

/** Action for node N5. */
void CrPsCmd3s9PrgrN5(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Configure the (3,10) or (3,12) report with the SID being processed and load it in the OutLoader */

	DEBUGP_3("CrPsCmd3s9PrgrN5.\n");
}

/** Action for node N6. */
void CrPsCmd3s9PrgrN6(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Set action outcome to: 'completed' */

	DEBUGP_3("CrPsCmd3s9PrgrN6.\n");
}

/** Action for node N7. */
void CrPsCmd3s9PrgrN7(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Set action outcome to: 'continue' */

	DEBUGP_3("CrPsCmd3s9PrgrN7.\n");
}

/** Action for node N8. */
void CrPsCmd3s9PrgrN8(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Start processing the first valid SID in the command */

	DEBUGP_3("CrPsCmd3s9PrgrN8.\n");
}

/** Action for node N9. */
void CrPsCmd3s9PrgrN9(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Process the next valid SID in the command */

	DEBUGP_3("CrPsCmd3s9PrgrN9.\n");
}

/** Guard on the Control Flow from DECISION1 to N2. */
FwPrBool_t CrPsCmd3s9PrgrG1(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* OutFactory fails to return a report  */

	DEBUGP_3("CrPsCmd3s9PrgrG1.\n");
	return 0;
}

/** Guard on the Control Flow from DECISION2 to N6. */
FwPrBool_t CrPsCmd3s9PrgrG2(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* This SID was the last valid SID in the (3,9) or (3,11)  */

	DEBUGP_3("CrPsCmd3s9PrgrG2.\n");
	return 0;
}

/** Guard on the Control Flow from N7 to N9. */
FwPrBool_t CrPsCmd3s9PrgrG3(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Next Execution  */

	DEBUGP_3("CrPsCmd3s9PrgrG3.\n");
	return 0;
}

/* ----------------------------------------------------------------------------------------------------------------- */

