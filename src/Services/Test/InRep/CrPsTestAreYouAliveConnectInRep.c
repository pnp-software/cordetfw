/**
 * @file CrPsTestAreYouAliveConnectInRep.c
 * @ingroup
 *
 * @brief Implementation of the Service Are-You-Alive Test in-coming report packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
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

#include <stdio.h>
#include "CrPsDebug.h"

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

