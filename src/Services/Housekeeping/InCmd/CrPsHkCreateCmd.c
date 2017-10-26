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

#include <CrPsUtilitiesServHk.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServHk.h>
#include <Services/General/CrPsPktServHkSupp.h>
#include <CrPsUserConstants.h>
#include <DataPool/CrPsDpServHk.h>

#include <stdio.h>
#include "CrPsDebug.h"


/* ------------------------------------------------------------------------------------ */
void CrPsHkCreateCmdStartAction(FwSmDesc_t smDesc)
{
  prDescCmd3s1Start_t prData;

  /* Run the procedure Start Action of HkCreate Command of figure 9.1 */

  /* Set prData of procedure   */
  /* initial setting of prData */
  prData.smDesc = smDesc;
  FwPrSetData(prDescHkCmd3s1Start, &prData);

  FwPrRun(prDescHkCmd3s1Start);

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkCreateCmdProgressAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t        *cmpData;
  CrFwInCmdData_t      *cmpSpecificData;
  CrFwPckt_t            pckt;
  CrPsSid_t             rdlSlot, rdlSid;
  CrFwCounterU4_t       i, j;
  CrPsSid_t             sid;
  CrPsParamId_t         N1ParamId, N2ParamId;
  CrPsCollectInterval_t period;
  CrFwBool_t            isEnabled;
  CrFwCounterU4_t       N1, NFA, N2;
  unsigned int SCSampleRep;

  /* Add the definition of the new report to the RDL, set its enabled status to ’disabled’, and set the action outcome to ’completed’ */

  /* Get inPckt */
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* look for a free slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {
      rdlSid = getDpsidItem(rdlSlot);
      
      if (rdlSid == 0)
        break;
    }

  /* Get SID and add in RDL */
  sid = getHkCreateCmdRepStrucId(pckt);
  setDpsidItem(rdlSlot, (CrPsSid_t)sid);
  
  /* Get Collection Interval (= period) and add in RDL */
  period = getHkCreateCmdCollectionInterval(pckt);
  setDpperiodItem(rdlSlot, period);

  /* Set enabled status to 'disabled' */
  isEnabled = 0;
  setDpisEnabledItem(rdlSlot, isEnabled);

  /* Set the single commutated parameter IDs */
  N1 = getHkCreateCmdN1(pckt);
  setDpnSimpleItem(rdlSlot, N1);
  for (i=0; i<N1; i++)
    {
      N1ParamId = getHkCreateCmdN1ParamIdItem(pckt, i+1);
      setDplstIdItem(HK_MAX_N_ITEMS*rdlSlot + i, N1ParamId);
    }

  /* Set the super commutated parameter IDs */
  NFA = getHkCreateCmdNFA(pckt);
  for (i=0;i<NFA;i++)
    {
      SCSampleRep = getHkCreateCmdSCSampleRepNumItem(pckt, i+1);
      setDplstSampleRepItem(HK_MAX_N_GR*rdlSlot + i, SCSampleRep);
      N2 = getHkCreateCmdN2(pckt, i+1);
      setDplstNSampRepItem(HK_MAX_N_GR*rdlSlot + i, N2);
      for (j=0;j<N2;j++)
        {
          N2ParamId = getHkCreateCmdN2ParamIdItem(pckt, i+1, j+1);
          setDplstIdItem(HK_MAX_N_ITEMS*rdlSlot + N1 + j, N2ParamId);
        }
    }

  cmpData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkCreateCmdTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t*   inData;

  /* Set action outcome to 'success' */

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

