/**
 * @file CrPsCmd3s3StartFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:15:26
 */

/** CrPsCmd3s3Start function definitions */
#include "CrPsCmd3s3StartCreate.h"

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
void CrPsCmd3s3StartN1(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Set i equal to 1 */

	DEBUGP_3("CrPsCmd3s3StartN1.\n");
}

/** Action for node N2. */
void CrPsCmd3s3StartN2(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Load invalid SID in data pool item verFailData  */

	DEBUGP_3("CrPsCmd3s3StartN2.\n");
}

/** Action for node N3. */
void CrPsCmd3s3StartN3(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Run Command Verification Failure Procedure to generate (1,4) report with failure code VER_ILL_SID */

	DEBUGP_3("CrPsCmd3s3StartN3.\n");
}

/** Action for node N4. */
void CrPsCmd3s3StartN4(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Increment i */

	DEBUGP_3("CrPsCmd3s3StartN4.\n");
}

/** Action for node N5. */
void CrPsCmd3s3StartN5(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Load the enabled SID in data pool verFailData  */

	DEBUGP_3("CrPsCmd3s3StartN5.\n");
}

/** Action for node N6. */
void CrPsCmd3s3StartN6(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Run Command Verification Failure Procedure to generate (1,4) report with failure code VER_ENABLED_SID  */

	DEBUGP_3("CrPsCmd3s3StartN6.\n");
}

/** Action for node N7. */
void CrPsCmd3s3StartN7(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Set action outcome to 'success'  */

	DEBUGP_3("CrPsCmd3s3StartN7.\n");
}

/** Action for node N8. */
void CrPsCmd3s3StartN8(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* Set action outcome to 'failure' with failure code VER_S3S_START_FD  */

	DEBUGP_3("CrPsCmd3s3StartN8.\n");
}

/** Guard on the Control Flow from DECISION1 to N2. */
FwPrBool_t CrPsCmd3s3StartG1(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* The i-th SID is not in the RDL  */

	DEBUGP_3("CrPsCmd3s3StartG1.\n");
	return 0;
}

/** Guard on the Control Flow from DECISION2 to N5. */
FwPrBool_t CrPsCmd3s3StartG2(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* The i-th SID is enabled in the RDL   */

	DEBUGP_3("CrPsCmd3s3StartG2.\n");
	return 0;
}

/** Guard on the Control Flow from DECISION3 to DECISION4. */
FwPrBool_t CrPsCmd3s3StartG3(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* The i-th SID was the last SID in the command  */

	DEBUGP_3("CrPsCmd3s3StartG3.\n");
	return 0;
}

/** Guard on the Control Flow from DECISION4 to N8. */
FwPrBool_t CrPsCmd3s3StartG4(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	/* All SIDs in the command are invalid  */

	DEBUGP_3("CrPsCmd3s3StartG4.\n");
	return 0;
}

/* ----------------------------------------------------------------------------------------------------------------- */

