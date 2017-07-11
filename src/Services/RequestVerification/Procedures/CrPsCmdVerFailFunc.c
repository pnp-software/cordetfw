/**
 * @file CrPsCmdVerFailFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 18:1:13
 */

/** CrPsCmdVerFail function definitions */
#include "CrPsCmdVerFailCreate.h"

/** FW Profile function definitions */
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ------------------------------------------------------------------------------------ */
/* Action for node N2. */
void CrPsCmdVerFailN2(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Retrieve an OutComponent of type (1,4) or (1,8) from the OutFactory */

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N3. */
void CrPsCmdVerFailN3(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Generate error report OUTFACTORY_FAIL */

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N4. */
void CrPsCmdVerFailN4(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Configure report and load it in the OutLoader */

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N5. */
void CrPsCmdVerFailN5(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Increment data pool variable nOfXyFailed */

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N6. */
void CrPsCmdVerFailN6(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Update data pool variable pcktIdXyFailed and failCodeXyFailed */

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/* Guard on the Control Flow from DECISION1 to N3. */
FwPrBool_t CrPsCmdVerFailG1(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* [ OutFactory fails to generate OutComponent ] */

  return 1;
}
