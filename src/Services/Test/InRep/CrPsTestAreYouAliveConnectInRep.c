/**
 * @file CrPsTestAreYouAliveConnectInRep.c
 * @ingroup Serv17
 * @ingroup InRep 
 *
 * @brief Implementation of the Service Are-You-Alive Test in-coming report packet.
 *
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

#include "CrPsTestAreYouAliveConnectInRep.h"

#include <FwPrConfig.h>
#include <FwSmConfig.h>

#include <Pckt/CrFwPckt.h>
#include <CrFwCmpData.h>

#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServTest.h>

#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServTest.h>

/**
 * @brief Update action of the Service Are-You-Alive Test in-coming report
 *
 * @param[in]  prDesc procedure descriptor
 * @param[out] none
 */
void CrPsTestAreYouAliveConnectInRepUpdateAction(FwPrDesc_t prDesc)
{
  CrFwCmpData_t   *inData;
  CrFwInRepData_t *inSpecificData;
  CrFwPckt_t       inPckt;
  CrFwDestSrc_t    sourceId; /* unsigned char */

  /* Get in packet */
  inData         = (CrFwCmpData_t*)FwPrGetData(prDesc);
  inSpecificData = (CrFwInRepData_t*)(inData->cmpSpecificData);
  inPckt         = inSpecificData->pckt;

  /* Get source ID within packet */
  sourceId = CrFwPcktGetSrc(inPckt);

  /* Store Are-You-Alive source in data pool */
  setDpAreYouAliveSrc((unsigned short)sourceId);

  inData->outcome = 1;

  return;
}

