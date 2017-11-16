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
#include <CrPsUtilitiesServHk.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServHk.h>
#include <Services/General/CrPsPktServHkSupp.h>
#include <DataPool/CrPsDpServHk.h>

#include <stdio.h>
#include "CrPsDebug.h"

unsigned short nmbSucc;


/* ------------------------------------------------------------------------------------ */
void CrPsHkOneShotCmdStartAction(FwSmDesc_t smDesc)
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

  /* Get number N of OneShot requests */
  nmbN = getHkOneShotCmdN(pckt);

  for (k=0; k<nmbN; k++)
    {
      sid[k] = getHkOneShotCmdRepStrucIdItem(pckt, k+1); 
    }
  sid[k] = 0;

  /* Set prData of procedure   */
  /* initial setting of prData */
  prData.smDesc = smDesc;
  prData.sidPtr = sid;
  FwPrSetData(prDescMultiSidCmdStart, &prData);

  FwPrRun(prDescMultiSidCmdStart);

  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkOneShotCmdProgressAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t     *cmpData;
  CrFwInCmdData_t   *cmpSpecificData;
  CrFwPckt_t         pckt;
  CrPsSid_t          sid, rdlSid, rdlSlot;
  CrFwCounterU4_t    N, i;

  /* For the entries in the RDL corresponding to the SIDs which have been identified as valid 
  by the Start Action: set enabled flag to true, set the cycle counter equal to the period. 
  Set the action outcome to 'completed' */

  /* Get in data */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;
  
  /*Get number of SID's*/
  N = getHkOneShotCmdN(pckt);

  nmbSucc = 0;

  for (i=0; i<N; i++)
  {
    /*Get SID from packet*/
    sid = getHkOneShotCmdRepStrucIdItem(pckt, i+1);

    /* look for the slot */
    for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {
      rdlSid = getDpsidItem(rdlSlot);
      
      if (sid == rdlSid)
        break;
    }

    if (rdlSlot < HK_N_REP_DEF) 
      {
        /*Set enable flag to true and set the cycle counter equal to the period*/
        setDpisEnabledItem(rdlSlot, 1);
        setDpcycleCntItem(rdlSlot, getDpperiodItem(rdlSlot));
        nmbSucc++;
      }
  }

  /* Set the outcome to completed */
  cmpData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkOneShotCmdTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t     *cmpData;
  CrFwInCmdData_t   *cmpSpecificData;
  CrFwPckt_t         pckt;
  CrFwCounterU4_t    N;

  /* Set action outcome to ’success’ if all valid SIDs in the command were successfully processed by the progress action; 
   * set it to ’failure’ otherwise */

  /* Get in data */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;
  
  /*Get number of SID's*/
  N = getHkOneShotCmdN(pckt);
  
  if (nmbSucc == N)
    {
      cmpData->outcome = 1;
    }
  else
    {
      cmpData->outcome = 0;
    }

  return;
}

