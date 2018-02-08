/**
 * @file CrPsRep.c
 * @ingroup Serv5
 * @ingroup OutCmp
 *
 * @brief Implementation of TM(5,x) EvtRep.
 *
 * @note This file was generated on 2017-09-19 12:36:09
 * @author PnP Generator
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * 
 * last modification: 22.01.2018
 * 
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#include "CrPsEvtRep.h"

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

#include <DataPool/CrPsDpServEvt.h>
#include <Services/General/CrPsConstants.h>


/**
 * Enable check of TM(5,x) EvtRep.
 * Update service 5 observable nOfDetectedEvt x (’x’ is the event
 * severity level) and then retrieve the enable status from the Out-
 * Registry as a function of the report type, sub-type and discrimi-
 * nant
 * \param smDesc The state machine descriptor.
 * \return The enable check result.
 */
CrFwBool_t CrPsEvtRepEnableCheck(FwSmDesc_t smDesc)
{
  CrFwCmpData_t       *cmpData;
  CrFwOutCmpData_t    *cmpSpecificData;
  CrFwPckt_t           pckt;
  CrFwServSubType_t    servSubType;
  CrPsNumberU4_t       nOfDetectedEvts;
  CrFwCounterU2_t      evtSlot;
  CrPsEid_t            eid, evtEid;
  CrPsEid_t            evtEidArray[EVT_N_EID] = EVT_EID;  

  /* Get packet */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwOutCmpData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get Severity Level (= Service Sub Type) */
  servSubType = CrFwPcktGetServSubType(pckt);

  /* Update observable nOfDetectedEvt x */
  switch (servSubType)
  {
    case CRPS_EVT_SEVLEVEL1_REP:
      nOfDetectedEvts = getDpnOfDetectedEvts_1();
      nOfDetectedEvts++;
      setDpnOfDetectedEvts_1(nOfDetectedEvts);
      break;
    case CRPS_EVT_SEVLEVEL2_REP:
      nOfDetectedEvts = getDpnOfDetectedEvts_2();
      nOfDetectedEvts++;
      setDpnOfDetectedEvts_2(nOfDetectedEvts);
      break;
    case CRPS_EVT_SEVLEVEL3_REP:
      nOfDetectedEvts = getDpnOfDetectedEvts_3();
      nOfDetectedEvts++;
      setDpnOfDetectedEvts_3(nOfDetectedEvts);
      break;
    case CRPS_EVT_SEVLEVEL4_REP:
      nOfDetectedEvts = getDpnOfDetectedEvts_4();
      nOfDetectedEvts++;
      setDpnOfDetectedEvts_4(nOfDetectedEvts);
      break;
    default:
      break;
  }
  
  /* Get EID */
  eid = CrFwPcktGetDiscriminant(pckt);

  /* look for the slot */
  for (evtSlot = 0; evtSlot < EVT_N_EID; evtSlot++)
    {
      evtEid = evtEidArray[evtSlot];
      
      if (eid == evtEid)
        break;
    }

  if (evtSlot == EVT_N_EID)
    {
      return 0;
    }
  else 
    {
      return getDpisEidEnabledItem(evtSlot);
    }
}

/**
 * Update action of TM(5,1) EvtRep1.
 * Update service 5 observables: nOfGenEvtRep x, lastEvtEid i,
 * lastEvtTime x (’x’ is the event severity level). Note that the pa-
 * rameter values are set by the application which creates the event
 * report at the time it creates the event report.
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtRepUpdateAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t       *cmpData;
  CrFwOutCmpData_t    *cmpSpecificData;
  CrFwPckt_t           pckt;
  CrFwServSubType_t    servSubType;
  CrPsEid_t            eid;
  CrFwTimeStamp_t      timeStamp;
  CrPsNumberU4_t       nOfGenEvtRep;

  /* Get packet */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwOutCmpData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;
  
  /* Get Severity Level (= Service Sub Type) */
  servSubType = CrFwPcktGetServSubType(pckt);

  /* Get EID */
  eid = CrFwPcktGetDiscriminant(pckt);

  /* Get current Time */
  timeStamp = CrFwOutCmpGetTimeStamp(smDesc);

  /* Update observable nOfGenEvtRep x, lastEvtEid i, lastEvtTime x */
  switch (servSubType)
  {
    case CRPS_EVT_SEVLEVEL1_REP:
      nOfGenEvtRep = getDpnOfGenEvtRep_1();
      nOfGenEvtRep++;
      setDpnOfGenEvtRep_1(nOfGenEvtRep);
      setDplastEvtEid_1(eid);
      setDplastEvtTime_1(timeStamp);
      break;
    case CRPS_EVT_SEVLEVEL2_REP:
      nOfGenEvtRep = getDpnOfGenEvtRep_2();
      nOfGenEvtRep++;
      setDpnOfGenEvtRep_2(nOfGenEvtRep);
      setDplastEvtEid_2(eid);
      setDplastEvtTime_2(timeStamp);
      break;
    case CRPS_EVT_SEVLEVEL3_REP:
      nOfGenEvtRep = getDpnOfGenEvtRep_3();
      nOfGenEvtRep++;
      setDpnOfGenEvtRep_3(nOfGenEvtRep);
      setDplastEvtEid_3(eid);
      setDplastEvtTime_3(timeStamp);
      break;
    case CRPS_EVT_SEVLEVEL4_REP:
      nOfGenEvtRep = getDpnOfGenEvtRep_4();
      nOfGenEvtRep++;
      setDpnOfGenEvtRep_4(nOfGenEvtRep);
      setDplastEvtEid_4(eid);
      setDplastEvtTime_4(timeStamp);
      break;
    default:
      break;
  }

  cmpData->outcome = 1;

  return ;
}
