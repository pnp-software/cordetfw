/**
 * @file CrPsHkDeleteDiagStruct.c
 *
 * Implementation of the Command (3,4) to Delete a Diagnostic Report Structure in-coming command packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsHkDeleteDiagStruct.h"

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
CrFwBool_t CrPsHkDeleteDiagStructReadyCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Return "command is ready" */
  DEBUGP_3("CrPsHkDeleteDiagStructReadyCheck()\n");

  return 1;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkDeleteDiagStructStartAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t* inData;

  /* Run the procedure Start Action of HkDelete Command of figure 9.2 */
  DEBUGP_3("CrPsHkDeleteDiagStructStartAction()\n");

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkDeleteDiagStructProgressAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t*   inData;

  /* Delete the entries in the RDL corresponding to the SIDs which have been identified as valid by the Start Action 
     and then set the action outcome to ’completed’ */
  DEBUGP_3("CrPsHkDeleteDiagStructProgressAction()\n");

  /* Get in data */
  inData  = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkDeleteDiagStructTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t*   inData;

  /* Set action outcome to 'success' */
  DEBUGP_3("CrPsHkDeleteDiagStructTerminationAction()\n");

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkDeleteDiagStructAbortAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Do nothing */
  DEBUGP_3("CrPsHkDeleteDiagStructAbortAction()\n");

  return;
}
