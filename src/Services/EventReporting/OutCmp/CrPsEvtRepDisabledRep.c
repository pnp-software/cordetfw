/**
 * \file
 *
 * Implementation of TM(5,8) EvtRepDisabledRep.
 *
 * \note This file was generated on 2017-09-19 12:36:09
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsEvtRepDisabledRep.h"

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

#include <DataPool/CrPsDpServEvt.h>
#include <Services/General/CrPsPktServEvt.h>
#include <Services/General/CrPsPktServEvtSupp.h>
#include <CrPsUserConstants.h>
#include <CrPsDebug.h>


/**
 * Update action of TM(5,8) EvtRepDisabledRep.
 * Load the list of disabled event identifiers from arrays isEidEn-
 * abled1 to isEidEnabled4
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtRepDisabledRepUpdateAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t       *cmpData;
  CrFwOutCmpData_t    *cmpSpecificData;
  CrFwPckt_t           pckt;
  CrFwCounterU2_t      evtSlot, pos;
  CrPsEid_t            evtEid;
  CrPsEid_t            evtEidArray[EVT_N_EID] = EVT_EID;

  /* Get packet */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwOutCmpData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  pos = 0;

  for (evtSlot = 0; evtSlot < EVT_N_EID; evtSlot++)
    {
      if (getDpisEidEnabledItem(evtSlot) == 0)
        {
          pos++;

          evtEid = evtEidArray[evtSlot];
   
          setEvtRepDisabledRepEventIdItem(pckt, pos, evtEid);
        }
    }

  return ;
}
