/**
 * @file CrPsHkEnableCmd.c
 *
 * Implementation of the Command (3,5) to Enable Periodic Generation of a Housekeeping Report Structure in-coming command packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsHkEnableCmd.h"

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

#include <CrPsUserConstants.h>
#include <CrPsUtilitiesServHk.h>
#include <DataPool/CrPsDpServHk.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServHk.h>
#include <Services/General/CrPsPktServHkSupp.h>

#include <stdio.h>
#include "CrPsDebug.h"


/* ------------------------------------------------------------------------------------ */
void CrPsHkEnableCmdStartAction(FwSmDesc_t smDesc)
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
  nmbN = getHkEnableCmdN(pckt);

  for (k=0; k<nmbN; k++)
    {
      sid[k] = getHkEnableCmdRepStrucIdItem(pckt, k+1); 
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
void CrPsHkEnableCmdProgressAction(FwSmDesc_t smDesc)
{
  CrPsSid_t           sid[HK_N_REP_DEF+1];
  CrPsSid_t           rdlSid, rdlSlot;
  CrFwBool_t          isEnabled;
  CrFwCounterU4_t     nmbN;
  CrFwCounterU4_t     cycleCnt;
  CrFwCounterU4_t     k;
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;

  /* For the entries in the RDL corresponding to the SIDs which have been identified as valid by the Start Action: 
   * set enabled flag to true and set the cycle counter to 0. 
   * Set the action outcome to ’completed’ */
  
  /* Get in data */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get number N of OneShot requests */
  nmbN = getHkEnableCmdN(pckt);

  for (k=0; k<nmbN; k++)
    {
      sid[k] = getHkEnableCmdRepStrucIdItem(pckt, k+1); 

      /* look for the slot */
      for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
        {

          rdlSid = getDpsidItem(rdlSlot);

          if (sid[k] == rdlSid)
            break;
        }

      isEnabled = 1;
      setDpisEnabledItem(rdlSlot, isEnabled);

      cycleCnt = 0;
      setDpcycleCntItem(rdlSlot, cycleCnt);

      /* reread and check */
      isEnabled = 0;
      isEnabled = getDpisEnabledItem(rdlSlot);
     
      cycleCnt = 1;
      cycleCnt = getDpcycleCntItem(rdlSlot);
    }

  cmpData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkEnableCmdTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t*   inData;

  /* Set action outcome to 'success' */

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}
