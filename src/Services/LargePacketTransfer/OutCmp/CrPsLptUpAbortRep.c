/**
 * @file CrPsLptUpAbortRep.c
 * @ingroup Serv13
 * @ingroup OutCmp
 *
 * @brief Implementation of TM(13,16) LptUpAbortRep.
 *
 * @note This file was generated on 2017-11-22 12:47:43
 *
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

#include "CrPsLptUpAbortRep.h"

/* CrFramework includes */
#include "OutCmp/CrFwOutCmp.h"
#include "CrFwCmpData.h"
#include "Pckt/CrFwPckt.h"

/* FwProfile includes */
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwSmConfig.h"

#include <CrPsUtilitiesServLpt.h>
#include <DataPool/CrPsDpServLpt.h>
#include <Services/General/CrPsPktServLpt.h>


/**
 * Update action of TM(13,16) LptUpAbortRep.
 * The large message transaction identifier is taken from parameter
 * largeMsgTransId and the failure reason is read from variable lptFailCode.
 * \param smDesc The state machine descriptor.
 */
void CrPsLptUpAbortRepUpdateAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwOutCmpData_t   *cmpSpecificData;
  CrFwPckt_t          pckt;
  uint32_t            LptBufferId = UpTransferLptBufferId;
  CrPsTid_t           Tid;
  CrPsFailCode_t      FailReason;

  cmpData         = (CrFwCmpData_t    *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwOutCmpData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* The large message transaction identifier is taken from parameter largeMsgTransId and ... */
  Tid = getDplargeMsgTransIdItem(LptBufferId);
  setLptUpAbortRepTid(pckt, Tid);

  /* ... the failure reason is read from variable lptFailReason. */
  FailReason = getDplptFailCodeItem(LptBufferId);
  setLptUpAbortRepFailReason(pckt, FailReason);

  return;
}
