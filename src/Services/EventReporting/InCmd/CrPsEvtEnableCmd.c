/**
 * \file
 *
 * Implementation of TC(5,5) EvtEnableCmd.
 *
 * \note This file was generated on 2017-09-19 12:36:09
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include <CrFwCmpData.h>

#include <FwSmConfig.h>
#include "FwPrConfig.h"
#include "FwPrCore.h"

#include <Services/General/CrPsConstants.h>

#include <DataPool/CrPsDpServEvt.h>
#include <CrPsUtilitiesServEvt.h>
#include "Services/EventReporting/Procedures/CrPsCmd5EidStartCreate.h"
#include "CrPsEvtEnableCmd.h"
#include "CrPsDebug.h"

CrPsFlag_t evtFlag[EVT_N_EID];


/**
 * Start action of TC(5,5) EvtEnableCmd.
 * Run the procedure Start Action of Multi-EID Command of
 * figure 10.1
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtEnableCmdStartAction(FwSmDesc_t smDesc)
{
  prDescCmdEidStart_t prData;

  /* Set prData of procedure   */
  /* initial setting of prData */
  prData.smDesc = smDesc;
  prData.evtFlagPtr = evtFlag;
  FwPrSetData(prDescEvtCmd5EidStart, &prData);

  FwPrRun(prDescEvtCmd5EidStart);

  return ;
}

/**
 * Progress action of TC(5,5) EvtEnableCmd.
 * For each valid EID found by the Start Action of the command:
 * set the corresponding element of the array isEidEnabled to true
 * and then decrement nDisabledEid x (’x’ is the severity level of
 * the EID). Set the action outcome to ’completed’.
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtEnableCmdProgressAction(FwSmDesc_t smDesc)
{
  CrFwCounterU2_t     evtSlot;
  CrFwBool_t          isEnabled;
  uint8_t             evtEidLevelArray[EVT_N_EID] = EVT_EID_LEVEL;
  uint8_t             evtEidLevel;
  CrPsFlag_t          evtEidFlag;
  CrPsNumberU2_t      nmbDisEvtLevel;
  CrFwCmpData_t      *cmpData;

  /* Get in data */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);

  for (evtSlot = 0; evtSlot < EVT_N_EID; evtSlot++)
    {
      evtEidFlag = evtFlag[evtSlot];
      printf("CrPsEvtEnableCmdProgressAction: evtSlot = %d, evtEidFlag = %d\n", evtSlot, evtEidFlag);

      if (evtEidFlag == 1)
        {
          isEnabled = 1;
          setDpisEidEnabledItem(evtSlot, isEnabled);

          /* Get the severity level */
          evtEidLevel = evtEidLevelArray[evtSlot];

          switch (evtEidLevel)
          {
            case CRPS_EVT_SEVLEVEL1_REP:
              nmbDisEvtLevel = getDpnOfDisabledEid_1();
              nmbDisEvtLevel--;
              setDpnOfDisabledEid_1(nmbDisEvtLevel);
              break;
            case CRPS_EVT_SEVLEVEL2_REP:
              nmbDisEvtLevel = getDpnOfDisabledEid_2();
              nmbDisEvtLevel--;
              setDpnOfDisabledEid_2(nmbDisEvtLevel);        
              break;
            case CRPS_EVT_SEVLEVEL3_REP:
              nmbDisEvtLevel = getDpnOfDisabledEid_3();
              nmbDisEvtLevel--;
              setDpnOfDisabledEid_3(nmbDisEvtLevel);
              break;
            case CRPS_EVT_SEVLEVEL4_REP:
              nmbDisEvtLevel = getDpnOfDisabledEid_4();
              nmbDisEvtLevel--;
              setDpnOfDisabledEid_4(nmbDisEvtLevel);
              break;
            default: /*TODO can not be reached, because in the EVT_EID_LEVEL should not be a other entry !? */
              break;
          }

        }

    }

  cmpData->outcome = 1;  

  return ;  
}

/**
 * Termination action of TC(5,5) EvtEnableCmd.
 * Set action outcome to ’success’
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtEnableCmdTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t *inData;

  /* Set action outcome to 'success' */

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return ;
}
