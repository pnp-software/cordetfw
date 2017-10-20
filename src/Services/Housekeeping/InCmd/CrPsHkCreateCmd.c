/**
 * @file CrPsHkCreateCmd.c
 *
 * Implementation of the Command (3,1) to Create a Housekeeping Report Structure in-coming command packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsHkCreateCmd.h"

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
#include <Services/General/CrPsPktServHk.h>
#include <CrPsUserConstants.h>
#include <DataPool/CrPsDpServHk.h>

#include <stdio.h>
#include "CrPsDebug.h"


/* ------------------------------------------------------------------------------------ */
void CrPsHkCreateCmdStartAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  prDescCmd3s1Start_t prData;

  /* Run the procedure Start Action of HkCreate Command of figure 9.1 */
  DEBUGP_3("CrPsHkCreateCmdStartAction()\n");

  /* Set prData of procedure   */
  /* initial setting of prData */
  prData.smDesc = smDesc;
  FwPrSetData(prDescHkCmd3s1Start, &prData);

  FwPrRun(prDescHkCmd3s1Start);

  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  printf("CrPsHkCreateCmdStartAction: outcome = %d \n", cmpData->outcome);

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkCreateCmdProgressAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t pckt;

  unsigned char rdlSlot, rdlSid;

  unsigned char sid;
  unsigned int period;
  CrFwBool_t isEnabled;

  /* Add the definition of the new report to the RDL, set its enabled status to ’disabled’, and set the action outcome to ’completed’ */
  DEBUGP_3("CrPsHkCreateCmdProgressAction()\n");

  /* Get inPckt */
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* look for a free slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {
      rdlSid = getDpsidItem(rdlSlot);
      printf("SID in RDL[%d] = %d\n", rdlSlot, rdlSid);
      
      if (rdlSid == 0)
        break;
    }

  /* Get SID and add in RDL */
  sid = getHkCreateCmdRepStrucId(pckt);
  setDpsidItem(rdlSlot, (uint16_t)sid);
  
  /* Get Collection Interval (= period) and add in RDL */
  period = getHkCreateCmdCollectionInterval(pckt);
  setDpperiodItem(rdlSlot, period);

  /* Set enabled status to 'disabled' */
  isEnabled = 0;
  setDpisEnabledItem(rdlSlot, isEnabled);

  cmpData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkCreateCmdTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t*   inData;

  /* Set action outcome to 'success' */
  DEBUGP_3("CrPsHkCreateCmdTerminationAction()\n");

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

