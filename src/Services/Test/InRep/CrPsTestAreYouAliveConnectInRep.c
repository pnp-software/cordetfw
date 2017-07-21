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

#include <stdio.h>


/**
 * @brief Validity check of the Service Are-You-Alive Test in-coming report
 *
 * @param[in]  prDesc procedure descriptor
 * @param[out] 1, if validity confirmed
 */
CrFwBool_t CrPsTestAreYouAliveConnectInRepValidityCheck(FwPrDesc_t prDesc)
{
  CrFwPckt_t       pckt;
  CrFwCmpData_t   *cmpData;
  CrFwInRepData_t *cmpSpecificData;

  /* Compute the CRC for the report and returns true if the CRC is correct and false otherwise. */

  cmpData         = (CrFwCmpData_t   *) FwPrGetData(prDesc);
  cmpSpecificData = (CrFwInRepData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  CRFW_UNUSED(pckt);

  /* Verify Checksum of incoming packet */

#if 0
  if (!CheckCrc(pckt))
    {
      SendTcAccRepFail(pckt, ACK_WRONG_CHKSM);
      return 0;
    }
#endif

  printf("\n>>>>>>>>>>>\n>>> CrPsTestAreYouAliveConnectInRepValidityCheck entered ...\n>>>>>>>>>>>\n");

  return 1;
}

/**
 * @brief Update action of the Service Are-You-Alive Test in-coming report
 *
 * @param[in]  prDesc procedure descriptor
 * @param[out] none
 */
void CrPsTestAreYouAliveConnectInRepUpdateAction(FwPrDesc_t prDesc)
{
  CrFwCmpData_t* inData;
  CrFwInRepData_t* inSpecificData;
  CrFwPckt_t inPckt;
  CrFwDestSrc_t sourceId; /* unsigned char */

  /* Get in packet */
  inData         = (CrFwCmpData_t*)FwPrGetData(prDesc);
  inSpecificData = (CrFwInRepData_t*)(inData->cmpSpecificData);
  inPckt         = inSpecificData->pckt;

  printf("\n>>>>>>>>>>>\n>>> CrPsTestAreYouAliveConnectInRepUpdateAction entered ...\n>>>>>>>>>>>\n");

  /* Get source ID within packet */
  sourceId = CrFwPcktGetSrc(inPckt);
  printf("CrPsTestAreYouAliveConnectInRepUpdateAction(): sourceId = %d\n", sourceId);

  /* Store Are-You-Alive source in data pool */
  setDpAreYouAliveSrc((unsigned short)sourceId);

  inData->outcome = 1;

  return;
}

