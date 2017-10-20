/**
 * @file CrPsHkDeleteCmd.c
 *
 * Implementation of the Command (3,3) to Delete a Housekeeping Report Structure in-coming command packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsHkDeleteCmd.h"

/** CR Framework function definitions*/
#include "CrFwConstants.h"
#include "Pckt/CrFwPckt.h"
#include "OutFactory/CrFwOutFactory.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"
#include "CrFwCmpData.h"

/** FW Profile function definitions */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"

#include <CrPsUtilities.h>
#include <DataPool/CrPsDpServHk.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServHk.h>
#include <Services/General/CrPsPktServHkSupp.h>

#include <stdio.h>
#include "CrPsDebug.h"


/* ------------------------------------------------------------------------------------ */
void CrPsHkDeleteCmdStartAction(FwSmDesc_t smDesc)
{
  prDescCmd3s3Start_t prData;
  CrFwCmpData_t      *cmpData;

  /* Run the procedure Start Action of HkDelete Command of figure 9.2 */
  DEBUGP_3("CrPsHkDeleteCmdStartAction()\n");

  /* Set prData of procedure   */
  /* initial setting of prData */
  prData.smDesc = smDesc;
  FwPrSetData(prDescHkCmd3s3Start, &prData);

  FwPrRun(prDescHkCmd3s3Start);

  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  printf("CrPsHkDeleteCmdStartAction: outcome = %d \n", cmpData->outcome);

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkDeleteCmdProgressAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  int i, k, N;
  unsigned char rdlSid, rdlSlot;
  uint8_t  sid;
  CrFwBool_t isEnabled;

  /* Delete the entries in the RDL corresponding to the SIDs which have been identified as valid by the Start Action 
     and then set the action outcome to ’completed’ */
  DEBUGP_3("CrPsHkDeleteCmdProgressAction()\n");

  /* Get in data */
  cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get N from inPckt */
  N = (int)getHkDeleteCmdN(pckt);

  for (i=0; i<N; i++)
    {

      /* Get SID from inPckt */
      sid = getHkDeleteCmdRepStrucIdItem(pckt, i);

      /* Check if SID is in the RDL */
      /* look for the slot */
      for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
        {

          rdlSid = getDpsidItem(rdlSlot);
          printf("SID in RDL[%d] = %d\n", rdlSlot, rdlSid);

          if (sid == rdlSid)
            break;
        }    

      if (rdlSlot < HK_N_REP_DEF) 
        {
          /* Check if SID is enabled */   
          isEnabled = (CrFwBool_t)getDpisEnabledItem(rdlSlot);

          if (!isEnabled)
            {
              /* Delete the entries in the RDL */
              setDpdestItem(rdlSlot, 0);
              setDpperiodItem(rdlSlot, 0);
              setDpsidItem(rdlSlot, 0);
              setDpcycleCntItem(rdlSlot, 0);
              setDpnSimpleItem(rdlSlot, 0);
              setDpsampleBufIdItem(rdlSlot, 0);
              for (k=0; k<HK_MAX_N_GR; k++)
                {
                  setDplstSampleRepItem(rdlSlot*HK_MAX_N_GR + k, 0);
                  setDplstNSampRepItem(rdlSlot*HK_MAX_N_GR + k, 0);
                }
              for (k=0; k<HK_MAX_N_ITEMS; k++)
                {
                  setDplstIdItem(rdlSlot*HK_MAX_N_ITEMS + k, 0);
                }
            }    
        }

    }

  cmpData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkDeleteCmdTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t*   inData;

  /* Set action outcome to 'success' */
  DEBUGP_3("CrPsHkDeleteCmdTerminationAction()\n");

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}
