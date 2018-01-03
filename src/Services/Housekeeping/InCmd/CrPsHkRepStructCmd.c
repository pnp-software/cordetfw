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

#include <CrPsUtilitiesServHk.h>
#include <CrPsUserConstants.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServHk.h>
#include <Services/General/CrPsPktServHkSupp.h>
#include <CrPsDebug.h>

#include <stdio.h>
#include <stdlib.h>


/* ------------------------------------------------------------------------------------ */
void CrPsHkRepStructCmdStartAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t           *cmpData;
  CrFwInCmdData_t         *cmpSpecificData;
  CrFwPckt_t               pckt;
  prDescMultiSidCmdStart_t prData;
  CrPsSid_t                sid[HK_N_REP_DEF+1];
  CrFwCounterU4_t          nmbN;
  CrFwCounterU4_t          k;

  /* Run the procedure Start Action of Multi-SID Command of figure 9.3 */

  /* Get in data */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get number N of HkRepStructCmd requests */
  nmbN = getHkRepStructCmdN(pckt);

  for (k=0; k<nmbN; k++)
    {
      sid[k] = getHkRepStructCmdRepStrucIdItem(pckt, k+1);
    }
  sid[k] = 0;

  /* Set prData of procedure   */
  /* initial setting of prData */
  prData.smDesc = smDesc;
  prData.sidPtr = sid;
  FwPrSetData(getPrDescMultiSidCmdStart(), &prData);

  FwPrRun(getPrDescMultiSidCmdStart());

  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);

  return;  
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkRepStructCmdProgressAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  prDescCmd3s9Prgr_t *prDataPtr;
  CrPsSid_t           sid[HK_N_REP_DEF+1];
  CrFwCounterU4_t     nmbN;
  CrFwCounterU4_t     k;

  /* Run the procedure Progress Action of Report Housekeeping Structure of figure 9.4 */

  /* Get in data */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get number N of HkRepStructCmd requests */
  nmbN = getHkRepStructCmdN(pckt);

  for (k=0; k<nmbN; k++)
    {
      sid[k] = getHkRepStructCmdRepStrucIdItem(pckt, k+1);
    }
  sid[k] = 0;

  /* Set prData of procedure   */
  /* initial setting of prData */
  prDataPtr = (prDescCmd3s9Prgr_t *)malloc(sizeof(prDescCmd3s9Prgr_t));
  prDataPtr->smDesc = smDesc;
  prDataPtr->sidPtr = sid;
  FwPrSetData(getPrDescCmd3s9Prgr(), prDataPtr);

  FwPrStart(getPrDescCmd3s9Prgr());
  FwPrExecute(getPrDescCmd3s9Prgr());

  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkRepStructCmdTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *inData;
  prDescCmd3s9Prgr_t *prDataPtr;
  unsigned short      outcome;

  /* Set action outcome to ’success’ if all valid SIDs in the command were successfully processed by the progress action; 
   * set it to ’failure’ otherwise */

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  
  /* Get procedure parameters */
  prDataPtr = (prDescCmd3s9Prgr_t*) FwPrGetData(getPrDescCmd3s9Prgr());

  /* Get the Outcome*/
  outcome = prDataPtr->outcome;
  
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
