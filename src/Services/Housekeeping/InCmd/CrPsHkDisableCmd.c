/**
 * @file CrPsHkDisableCmd.c
 *
 * Implementation of the Command (3,6) to Disable Periodic Generation of a Housekeeping Report Structure in-coming command packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsHkDisableCmd.h"

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
void CrPsHkDisableCmdStartAction(FwSmDesc_t smDesc)
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
  nmbN = getHkDisableCmdN(pckt);

  for (k=0; k<nmbN; k++)
    {
      sid[k] = getHkDisableCmdRepStrucIdItem(pckt, k+1); 
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
void CrPsHkDisableCmdProgressAction(FwSmDesc_t smDesc)
{
  CrPsSid_t           sid[HK_N_REP_DEF+1];
  CrPsSid_t           rdlSid, rdlSlot;
  CrFwBool_t          isEnabled;
  CrFwCounterU4_t     nmbN;
  CrFwCounterU4_t     k;
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;

  /* Set to false the enable flag of the entries in the RDL corresponding to the SIDs which have been 
   * identified as valid by the Start Action and then set the action outcome to ’completed’ */

  /* Get in data */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get number N of OneShot requests */
  nmbN = getHkDisableCmdN(pckt);

  for (k=0; k<nmbN; k++)
    {
      sid[k] = getHkDisableCmdRepStrucIdItem(pckt, k+1); 

      /* look for the slot */
      for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
        {
          rdlSid = getDpsidItem(rdlSlot);

          if (sid[k] == rdlSid)
            break;
        }

      isEnabled = 0;
      setDpisEnabledItem(rdlSlot, isEnabled);
    }

  cmpData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkDisableCmdTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t*   inData;

  /* Set action outcome to 'success' */

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}
