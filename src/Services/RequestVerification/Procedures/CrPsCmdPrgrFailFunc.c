/**
 * @file CrPsCmdPrgrFailFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 17:58:12
 */

/** CrPsCmdPrgrFail function definitions */
#include "CrPsCmdPrgrFailCreate.h"

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
void CrPsCmdPrgrFailN2(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Retrieve an OutComponent of type (1,6) from the OutFactory */

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N3. */
void CrPsCmdPrgrFailN3(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Generate error report OUTFACTORY_FAIL */

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N4. */
void CrPsCmdPrgrFailN4(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Configure report and load it in the OutLoader */

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N5. */
void CrPsCmdPrgrFailN5(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Increment data pool variable nOfPrgrFailed */

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N6. */
void CrPsCmdPrgrFailN6(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Update data pool variable pcktIdPrgrFailed, failCodePrgrFailed and prgrStepFailed */

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/* Guard on the Control Flow from DECISION1 to N3. */
FwPrBool_t CrPsCmdPrgrFailG1(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* [ OutFactory fails to generate OutComponent ] */

  return 1;
}
