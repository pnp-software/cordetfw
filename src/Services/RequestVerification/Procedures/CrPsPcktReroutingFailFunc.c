/**
 * @file CrPsPcktReroutingFailFunc.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 18:26:2
 */

/** CrPsPcktReroutingFail function definitions */
#include "CrPsPcktReroutingFailCreate.h"

/** FW Profile function definitions */
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ------------------------------------------------------------------------------------ */
/* Action for node N1. */
void CrPsPcktReroutingFailN1(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Generate error report INLOADER_INV_DEST */

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N2. */
void CrPsPcktReroutingFailN2(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Retrieve an OutComponent of type (1,10) from the OutFactory */

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N3. */
void CrPsPcktReroutingFailN3(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Generate error report OUTFACTORY_FAIL */

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N4. */
void CrPsPcktReroutingFailN4(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Configure report (1,10) and load it in the OutLoader */

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N5. */
void CrPsPcktReroutingFailN5(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Increment data pool variable nOfReroutingFailed */

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N6. */
void CrPsPcktReroutingFailN6(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Update data pool variable pcktIdRerouting, invDestRerouting */

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/* Guard on the Control Flow from DECISION1 to N1. */
FwPrBool_t CrPsPcktReroutingFailG1(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* [ Packet encapsulates a report ] */

  return 1;
}

/* Guard on the Control Flow from DECISION1 to N2. */
FwPrBool_t CrPsPcktReroutingFailG1E(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* [ Packet encapsulates a command ] */

  return 1;
}

/* Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsPcktReroutingFailG2(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* [ OutFactory fails to generate OutComponent ] */

  return 1;
}
