/**
 * @file CrPsHkEnablePeriodicHk.c
 *
 * Implementation of the Command (3,5) to Enable Periodic Generation of a Housekeeping Report Structure in-coming command packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsHkEnablePeriodicHk.h"

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
#include <CrPsUtilities.h>
 #include <DataPool/CrPsDpHk.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktHk.h>

#include <stdio.h>
#include "CrPsDebug.h"


/* ------------------------------------------------------------------------------------ */
CrFwBool_t CrPsHkEnablePeriodicHkReadyCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Return "command is ready" */
  DEBUGP_3("CrPsHkEnablePeriodicHkReadyCheck()\n");

  return 1;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkEnablePeriodicHkStartAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  prDescMultiSidCmdStart_t prData;
  unsigned char sid[10];
  uint32_t nmbN;
  unsigned int k;

  /* Run the procedure Start Action of Multi-SID Command of figure 9.3 */
  DEBUGP_3("CrPsHkEnablePeriodicHkStartAction()\n");

  /* Get in data */
  cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get number N of OneShot requests */
  nmbN = getHkEnableHkParCmdN(pckt);
  printf("CrPsHkEnablePeriodicHkStartAction: N = %d \n", nmbN);

  for (k=0; k<nmbN; k++)
    {
      sid[k] = getHkEnableHkParCmdHKRepStrucID(pckt); /* TODO: should be enumerated values */
      printf("CrPsHkEnablePeriodicHkStartAction: SID[%d] = %d\n", k, sid[k]);
    }
  sid[k] = 0;
  printf("CrPsHkEnablePeriodicHkStartAction: last SID[%d] = %d\n", k, sid[k]);

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
void CrPsHkEnablePeriodicHkProgressAction(FwSmDesc_t smDesc)
{
  unsigned char sid[10];
  unsigned char rdlSid, rdlSlot;
  uint8_t isEnabled;
  uint32_t nmbN;
  uint32_t cycleCnt;
  unsigned int k;
  CrFwDestSrc_t dest;
  FwSmDesc_t rep;

  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;

  /* For the entries in the RDL corresponding to the SIDs which have been identified as valid by the Start Action: 
   * set enabled flag to true and set the cycle counter to 0. 
   * Set the action outcome to ’completed’ */
  
  DEBUGP_3("CrPsHkEnablePeriodicHkProgressAction()\n");

  /* Get in data */
  cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get number N of OneShot requests */
  nmbN = getHkEnableHkParCmdN(pckt);
  printf("CrPsHkEnablePeriodicHkProgressAction: N = %d \n", nmbN);

  for (k=0; k<nmbN; k++)
    {
      sid[k] = getHkEnableHkParCmdHKRepStrucID(pckt); /* TODO: should be enumerated values */
      printf("CrPsHkEnablePeriodicHkProgressAction: SID[%d] = %d\n", k, sid[k]);

      /* look for the slot */
      for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
        {

          rdlSid = getDpsidItem(rdlSlot);
          printf("SID in RDL[%d] = %d\n", rdlSlot, rdlSid);

          if (sid[k] == rdlSid)
            break;
        }

      isEnabled = 1;
      setDpisEnabledItem(rdlSlot, isEnabled);

      cycleCnt = 0;
      setDpcycleCntItem(rdlSlot, cycleCnt);

      /* TODO: have to be generated and loaded to OutLoader */
      rep  = CrFwOutFactoryMakeOutCmp(CRPS_HK, CRPS_HK_HKPARAM_REP, sid[k], 0);/* arguments: type, subType, discriminant/evtId, length */
      dest = 1;
      CrFwOutCmpSetDest(rep, dest);
      CrFwOutLoaderLoad(rep); 
    }

  cmpData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkEnablePeriodicHkTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t*   inData;

  /* Set action outcome to 'success' */
  DEBUGP_3("CrPsHkEnablePeriodicHkTerminationAction()\n");

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsHkEnablePeriodicHkAbortAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Do nothing */
  DEBUGP_3("CrPsHkEnablePeriodicHkAbortAction()\n");

  return;
}
