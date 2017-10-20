/**
 * @file CrPsHkRepStructCmd.c
 *
 * Implementation of the Command (3,9) to Report Structure of a Housekeeping Report in-coming command packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsHkRepStructCmd.h"

/* CrFramework includes */
#include <Pckt/CrFwPckt.h>
#include <OutFactory/CrFwOutFactory.h>
#include <OutCmp/CrFwOutCmp.h>
#include <OutLoader/CrFwOutLoader.h>
#include <CrFwCmpData.h>

/** FW Profile function definitions */
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include <FwSmConfig.h>

#include <CrPsUtilities.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServHk.h>
#include <Services/General/CrPsPktServHkSupp.h>
#include <CrPsDebug.h>

#include <stdio.h>


/* ------------------------------------------------------------------------------------ */
void CrPsHkRepStructCmdStartAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  prDescMultiSidCmdStart_t prData;
  unsigned char sid[10];
  uint32_t nmbN;
  unsigned int k;

  /* Run the procedure Start Action of Multi-SID Command of figure 9.3 */
  DEBUGP_3("CrPsHkRepStructCmdStartAction()\n");

  /* Get in data */
  cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get number N of HkRepStructCmd requests */
  nmbN = getHkRepStructCmdN(pckt);
  printf("CrPsHkRepStructCmdStartAction: N = %d \n", nmbN);

  for (k=0; k<nmbN; k++)
    {
      sid[k] = getHkRepStructCmdRepStrucIdItem(pckt, nmbN); /* TODO: should be enumerated values */
      printf("CrPsHkRepStructCmdStartAction: SID[%d] = %d\n", k, sid[k]);
    }
  sid[k] = 0;
  printf("CrPsHkRepStructCmdStartAction: last SID[%d] = %d\n", k, sid[k]);

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
  printf("CrPsHkRepStructCmdStartAction: outcome = %d \n", cmpData->outcome);

  return;  
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkRepStructCmdProgressAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t     *cmpData;
  prDescCmd3s9Prgr_t prData;

  /* Run the procedure Progress Action of Report Housekeeping Structure of figure 9.4 */

  DEBUGP_3("CrPsHkRepStructCmdProgressAction()\n");

  /* Set prData of procedure   */
  /* initial setting of prData */
  prData.smDesc = smDesc;
  FwPrSetData(prDescCmd3s9Prgr, &prData);

  FwPrRun(prDescCmd3s9Prgr);

  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  printf("CrPsHkRepStructCmdProgressAction: outcome = %d \n", cmpData->outcome);

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkRepStructCmdTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t* inData;
  prDescCmd3s9Prgr_t* prDescCmd3s9PrgrPtr;
  unsigned short outcome;

  /* Set action outcome to ’success’ if all valid SIDs in the command were successfully processed by the progress action; 
   * set it to ’failure’ otherwise */
  DEBUGP_3("CrPsHkRepStructCmdTerminationAction()\n");

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  
  /* Get procedure parameters */
  prDescCmd3s9PrgrPtr = (prDescCmd3s9Prgr_t*) FwPrGetData(prDescCmd3s9Prgr);

  /* Get the Outcome*/
  outcome = prDescCmd3s9PrgrPtr->outcome;
  
  if (outcome == 1)
    {
      inData->outcome = 1;
    }
  else if ((outcome == 0) || (outcome > 2))
    {
      inData->outcome = 0;
    }

  return;
}
