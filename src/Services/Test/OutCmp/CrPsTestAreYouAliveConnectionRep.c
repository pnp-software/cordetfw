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
void CrPsTestAreYouAliveConnectionRepUpdateAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t* cmpData;
  cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpData->outcome = 1;

  return;
}

