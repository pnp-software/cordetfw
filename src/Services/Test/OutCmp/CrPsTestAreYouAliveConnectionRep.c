/**
 * @file CrPsTestAreYouAliveConnectionRep.c
 * @ingroup Serv17
 * @ingroup OutCmp 
 *
 * @brief Implementation of the Perform Connection Test in-coming command packet.
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

#include "CrPsTestAreYouAliveConnectionRep.h"
#include "Services/General/CrPsConstants.h"

/* CrFramework includes */
#include "Pckt/CrFwPckt.h"
#include "OutFactory/CrFwOutFactory.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"

#include "CrFwCmpData.h"
#include "FwSmConfig.h"

/* ------------------------------------------------------------------------------------ */
void CrPsTestAreYouAliveConnectionRepUpdateAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t* cmpData;
  cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpData->outcome = 1;

  return;
}

