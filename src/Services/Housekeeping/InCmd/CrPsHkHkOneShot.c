/**
 * @file CrPsHkHkOneShot.c
 *
 * Implementation of the Command (3,27) to Generate One-Shot Housekeeping Report in-coming command packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsHkHkOneShot.h"

/* CrFramework includes */
#include <Pckt/CrFwPckt.h>
#include <OutFactory/CrFwOutFactory.h>
#include <OutCmp/CrFwOutCmp.h>
#include <OutLoader/CrFwOutLoader.h>
#include <CrFwCmpData.h>

/* FwProfile includes */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"

#include <CrPsUtilities.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktHk.h>

#include <stdio.h>
#include "CrPsDebug.h"


/* ------------------------------------------------------------------------------------ */
CrFwBool_t CrPsHkHkOneShotReadyCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Return "command is ready" */
  DEBUGP_3("CrPsHkHkOneShotReadyCheck()\n");

  return 1;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkHkOneShotStartAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  prDescMultiSidCmdStart_t prData;
  unsigned char sid[10];
  uint32_t nmbN;
  unsigned int k;

  /* Run the procedure Start Action of Multi-SID Command of figure 9.3 */
  DEBUGP_3("CrPsHkHkOneShotStartAction()\n");

  /* Get in data */
  cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get number N of OneShot requests */
  nmbN = getHkOneShotDiagCmdN(pckt);
  printf("CrPsHkHkOneShotStartAction: N = %d \n", nmbN);

  for (k=0; k<nmbN; k++)
    {
      sid[k] = getHkOneShotHkCmdHKRepStrucID(pckt); /* TODO: should be enumerated values */
      printf("CrPsHkHkOneShotStartAction: SID[%d] = %d\n", k, sid[k]);
    }
  sid[k] = 0;
  printf("CrPsHkHkOneShotStartAction: last SID[%d] = %d\n", k, sid[k]);

/*  sid[0] = 1;
  sid[1] = 2;
  sid[2] = 0;
  */

  /* Set prData of procedure   */
  /* initial setting of prData */
  prData.smDesc = smDesc;
  prData.sidPtr = sid;
  FwPrSetData(prDescMultiSidCmdStart, &prData);

  FwPrRun(prDescMultiSidCmdStart);

  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  printf("CrPsHkHkOneShotStartAction: outcome = %d \n", cmpData->outcome);

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkHkOneShotProgressAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t* cmpData;
  prDescGenerateHkOneShotPrgr_t prData;
  unsigned char sid[10];

  /* Run the procedure Progress Action of Generate One-Shot Housekeeping Report of figure 9.6 */

  DEBUGP_3("CrPsHkHkOneShotProgressAction()\n");

  /* Get in data */
  cmpData  = (CrFwCmpData_t*)FwSmGetData(smDesc);

  sid[0] = 1;
  sid[1] = 2;
  sid[2] = 0;

  /* Set prData of procedure   */
  /* initial setting of prData */
  prData.smDesc = smDesc;
  prData.sidPtr = sid;
  FwPrSetData(prDescGenerateHkOneShotPrgr, &prData);

  FwPrRun(prDescGenerateHkOneShotPrgr);

  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  printf("CrPsHkHkOneShotProgressAction: outcome = %d \n", cmpData->outcome);

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkHkOneShotTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t* inData;
  /*prDataPrgrAction_t* prDataPrgrActionPtr;*/
  /*unsigned short outcome;*/

  /* Set action outcome to ’success’ if all valid SIDs in the command were successfully processed by the progress action; 
   * set it to ’failure’ otherwise */
  DEBUGP_3("CrPsHkHkOneShotTerminationAction()\n");

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

#if 0  
  /* Get procedure parameters */
  prDataPrgrActionPtr = (prDataPrgrAction_t*) FwPrGetData(prDescGenerateHkOneShotPrgr);

  /* Get the Outcome*/
  outcome = prDataPrgrActionPtr->outcome;
  
  if (outcome == 1)
    {
      inData->outcome = 1;
    }
  else if ((outcome == 0) || (outcome > 2))
    {
      inData->outcome = 0;
    }
#endif

  inData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkHkOneShotAbortAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Do nothing */
  DEBUGP_3("CrPsHkHkOneShotAbortAction()\n");

  return;
}
