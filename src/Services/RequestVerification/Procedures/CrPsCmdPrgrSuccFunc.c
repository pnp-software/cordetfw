/**
 * @file CrPsCmdPrgrSuccFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 17:59:40
 */

/** CrPsCmdPrgrSucc function definitions */
#include "CrPsCmdPrgrSuccCreate.h"

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
void CrPsCmdPrgrSuccN2(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Retrieve an OutComponent of type (1,5) from the OutFactory */

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N3. */
void CrPsCmdPrgrSuccN3(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Generate error report OUTFACTORY_FAIL */

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N4. */
void CrPsCmdPrgrSuccN4(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Configure report and load it in the OutLoader */

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/* Guard on the Control Flow from DECISION1 to N3. */
FwPrBool_t CrPsCmdPrgrSuccG1(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* [ OutFactory fails to generate OutComponent ] */

  return 1;
}
