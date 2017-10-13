/**
 * @file CrPsTestAreYouAliveConnectionRep.c
 *
 * Implementation of the Perform Connection Test in-coming command packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsTestAreYouAliveConnectionRep.h"
#include "Services/General/CrPsConstants.h"

/* CrFramework includes */
#include "Pckt/CrFwPckt.h"
#include "OutFactory/CrFwOutFactory.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"

#include "CrFwCmpData.h"
#include "FwSmConfig.h"
#include <stdio.h>
#include "CrPsDebug.h"


/* ------------------------------------------------------------------------------------ */
CrFwBool_t CrPsTestAreYouAliveConnectionRepEnableCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_17("CrPsTestAreYouAliveConnectionRepEnableCheck()\n");

  return 1; /*always True*/
}

/* ------------------------------------------------------------------------------------ */
CrFwBool_t CrPsTestAreYouAliveConnectionRepReadyCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_17("CrPsTestAreYouAliveConnectionRepReadyCheck()\n");

  return 1; /*always True*/
}

/* ------------------------------------------------------------------------------------ */
CrFwBool_t CrPsTestAreYouAliveConnectionRepRepeatCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  DEBUGP_17("CrPsTestAreYouAliveConnectionRepRepeatCheck()\n");

  return 0; /*always False*/
}

/* ------------------------------------------------------------------------------------ */
void CrPsTestAreYouAliveConnectionRepUpdateAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t* cmpData;
  DEBUGP_17("CrPsTestAreYouAliveConnectionRepUpdateAction()\n");
  cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpData->outcome = 1;

  return;
}

