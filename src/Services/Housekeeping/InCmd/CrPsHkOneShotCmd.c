/**
 * @file CrPsHkOneShotCmd.c
 *
 * Implementation of the Command (3,27) to Generate One-Shot Housekeeping Report in-coming command packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsHkOneShotCmd.h"

/* CrFramework includes */
#include <Pckt/CrFwPckt.h>
#include <OutFactory/CrFwOutFactory.h>
#include <OutCmp/CrFwOutCmp.h>
#include <OutLoader/CrFwOutLoader.h>
#include <CrFwCmpData.h>

/* FwProfile includes */
#include <FwPrConfig.h>
#include <FwSmConfig.h>
#include <FwPrCore.h>

#include <CrPsUserConstants.h>
#include <CrPsUtilities.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServHk.h>
#include <Services/General/CrPsPktServHkSupp.h>
#include <DataPool/CrPsDpServHk.h>

#include <stdio.h>
#include "CrPsDebug.h"

/* ------------------------------------------------------------------------------------ */
void CrPsHkOneShotCmdStartAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  prDescMultiSidCmdStart_t prData;
  unsigned char sid[HK_MAX_N_REP+1];
  uint32_t nmbN;
  unsigned int k;

  /* Run the procedure Start Action of Multi-SID Command of figure 9.3 */
  DEBUGP_3("CrPsHkOneShotCmdStartAction()\n");

  /* Get in data */
  cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get number N of OneShot requests */
  nmbN = getHkOneShotCmdN(pckt);
  printf("CrPsHkOneShotCmdStartAction: N = %d \n", nmbN);

  for (k=0; k<nmbN; k++)
    {
      sid[k] = getHkOneShotCmdRepStrucIdItem(pckt, nmbN); 
      printf("CrPsHkOneShotCmdStartAction: SID[%d] = %d\n", k, sid[k]);
    }
  sid[k] = 0;
  printf("CrPsHkOneShotCmdStartAction: last SID[%d] = %d\n", k, sid[k]);

  /* Set prData of procedure   */
  /* initial setting of prData */
  prData.smDesc = smDesc;
  prData.sidPtr = sid;
  FwPrSetData(prDescMultiSidCmdStart, &prData);

  FwPrRun(prDescMultiSidCmdStart);

  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  printf("CrPsHkOneShotCmdStartAction: outcome = %d \n", cmpData->outcome);

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkOneShotCmdProgressAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t     *cmpData;
  CrFwInCmdData_t   *cmpSpecificData;
  CrFwPckt_t         pckt;
  unsigned char sid, rdlSid, rdlSlot;
  unsigned int N, i;

  /* For the entries in the RDL corresponding to the SIDs which have been identified as valid 
  by the Start Action: set enabled flag to true, set the cycle counter equal to the period. 
  Set the action outcome to 'completed' */

  DEBUGP_3("CrPsHkOneShotCmdProgressAction()\n");

  /* Get in data */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;
  
  /*Get number of SID's*/
  N = getHkOneShotCmdN(pckt);

  for (i = 1; i<N; i++)
  {
    /*Get SID from packet*/
    sid = getHkOneShotCmdRepStrucIdItem(pckt, i);

    /* look for the slot */
    for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {

      rdlSid = getDpsidItem(rdlSlot);
      printf("SID in RDL[%d] = %d\n", rdlSlot, rdlSid);
      
      if (sid == rdlSid)
      {
        /*Set enable flag to true and set the cycle counter equal to the period*/
        setDpisEnabledItem(rdlSlot, 1);
        setDpcycleCntItem(rdlSlot, getDpperiodItem(rdlSlot));
        break;
      }
      else
      {
        /*ERROR sid not in list!!!*/
        /*?? set outcome to 0ß ??*/
        cmpData->outcome = 0;
        return;
      }
    }
  }

  /* Set the outcome to completed */
  cmpData->outcome = 1;

  printf("CrPsHkOneShotCmdProgressAction: outcome = %d \n", cmpData->outcome);

  return;

}

/* ------------------------------------------------------------------------------------ */
void CrPsHkOneShotCmdTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t* inData;
  prDescGenerateHkOneShotPrgr_t* prDataPrgrActionPtr;
  unsigned short outcome;

  /* Set action outcome to ’success’ if all valid SIDs in the command were successfully processed by the progress action; 
   * set it to ’failure’ otherwise */
  DEBUGP_3("CrPsHkOneShotCmdTerminationAction()\n");

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  /* Get procedure parameters */
  prDataPrgrActionPtr = (prDescGenerateHkOneShotPrgr_t*) FwPrGetData(prDescGenerateHkOneShotPrgr);

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

  return;
}

