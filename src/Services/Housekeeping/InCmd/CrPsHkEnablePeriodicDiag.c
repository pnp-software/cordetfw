/**
 * @file CrPsHkEnablePeriodicDiag.c
 *
 * Implementation of the Command (3,7) to Enable Periodic Generation of a Diagnostic Report Structure in-coming command packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsHkEnablePeriodicDiag.h"

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
CrFwBool_t CrPsHkEnablePeriodicDiagReadyCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Return "command is ready" */
  DEBUGP_3("CrPsHkEnablePeriodicDiagReadyCheck()\n");

  return 1;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkEnablePeriodicDiagStartAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t* inData;

  /* Run the procedure Start Action of Multi-SID Command of figure 9.3 */
  DEBUGP_3("CrPsHkEnablePeriodicDiagStartAction()\n");

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkEnablePeriodicDiagProgressAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t*   inData;

  /* For the entries in the RDL corresponding to the SIDs which have been identified as valid by the Start Action: 
   * set enabled flag to true and set the cycle counter to 0. 
   * Set the action outcome to ’completed’ */
  
  DEBUGP_3("CrPsHkEnablePeriodicDiagProgressAction()\n");

  /* Get in data */
  inData  = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkEnablePeriodicDiagTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t*   inData;

  /* Set action outcome to 'success' */
  DEBUGP_3("CrPsHkEnablePeriodicDiagTerminationAction()\n");

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkEnablePeriodicDiagAbortAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Do nothing */
  DEBUGP_3("CrPsHkEnablePeriodicDiagAbortAction()\n");

  return;
}
