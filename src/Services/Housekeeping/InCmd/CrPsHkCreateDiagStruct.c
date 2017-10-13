/**
 * @file CrPsHkCreateDiagStruct.c
 *
 * Implementation of the Command (3,2) to Create a Diagnostic Report Structure in-coming command packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsHkCreateDiagStruct.h"

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
CrFwBool_t CrPsHkCreateDiagStructReadyCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Return "command is ready" */
  DEBUGP_3("CrPsHkCreateDiagStructReadyCheck()\n");

  return 1;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkCreateDiagStructStartAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t* inData;

  /* Run the procedure Start Action of HkCreate Command of figure 9.1 */
  DEBUGP_3("CrPsHkCreateDiagStructStartAction()\n");

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkCreateDiagStructProgressAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t*   inData;

  /* Add the definition of the new report to the RDL, set its enabled status to ’disabled’, and set the action outcome to ’completed’ */
  DEBUGP_3("CrPsHkCreateDiagStructProgressAction()\n");

  /* Get in data */
  inData  = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkCreateDiagStructTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t*   inData;

  /* Set action outcome to 'success' */
  DEBUGP_3("CrPsHkCreateDiagStructTerminationAction()\n");

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkCreateDiagStructAbortAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Do nothing */
  DEBUGP_3("CrPsHkCreateDiagStructAbortAction()\n");

  return;
}
