/**
 * @file CrPsHkDiagOneShot.c
 *
 * Implementation of the Command (3,28) to Generate One-Shot Diagnostic Report in-coming command packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsHkDiagOneShot.h"

/* CrFramework includes */
#include <Pckt/CrFwPckt.h>
#include <OutFactory/CrFwOutFactory.h>
#include <OutCmp/CrFwOutCmp.h>
#include <OutLoader/CrFwOutLoader.h>
#include <CrFwCmpData.h>

/* FwProfile includes */
#include <FwSmConfig.h>

#include <CrPsUtilities.h>
#include <Services/General/CrPsConstants.h>

#include <stdio.h>
#include "CrPsDebug.h"


/* ------------------------------------------------------------------------------------ */
CrFwBool_t CrPsHkDiagOneShotReadyCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Return "command is ready" */
  DEBUGP_3("CrPsHkDiagOneShotReadyCheck()\n");

  return 1;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkDiagOneShotStartAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t* inData;

  /* Run the procedure Start Action of Multi-SID Command of figure 9.3 */
  DEBUGP_3("CrPsHkDiagOneShotStartAction()\n");

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkDiagOneShotProgressAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t*   inData;

  /* Run the procedure Progress Action of Generate One-Shot Housekeeping Report of figure 9.6 */

  DEBUGP_3("CrPsHkDiagOneShotProgressAction()\n");

  /* Get in data */
  inData  = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkDiagOneShotTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t*   inData;

  /* Set action outcome to ’success’ if all valid SIDs in the command were successfully processed by the progress action; 
   * set it to ’failure’ otherwise */
  DEBUGP_3("CrPsHkDiagOneShotTerminationAction()\n");

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkDiagOneShotAbortAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Do nothing */
  DEBUGP_3("CrPsHkDiagOneShotAbortAction()\n");

  return;
}
