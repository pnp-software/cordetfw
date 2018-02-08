/**
 * @file CrPsUtilitiesServEvt.c
 * @ingroup Utilities
 * @ingroup Serv5
 *
 * @brief Implementation of the utility functions of the CORDET Framework PUS Extension Service 5 (Event Reporting)
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

#include "CrPsUtilitiesServEvt.h"
#include "Pckt/CrFwPckt.h"     /* --- interface to adaptation point CrFwPckt --- */

/* CrFramework includes */
#include <OutFactory/CrFwOutFactory.h>
#include <OutLoader/CrFwOutLoader.h>
#include <CrFwCmpData.h>

/* FwProfile includes */
#include <FwPrCore.h>
#include <FwPrConfig.h>
#include <FwSmConfig.h>

#include <Services/General/CrPsConstants.h>
#include <Services/EventReporting/Procedures/CrPsCmd5EidStartCreate.h>

#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServEvt.h>

#include <stdlib.h>

/* global handles for the procedures */
FwPrDesc_t prDescEvtCmd5EidStart; 

/**
 * Initialization of CORDET Framework PUS Extension components
 */
int CrPsInitServEvt()
{
  /***********************************************************************/
  /* Service Event Reporting Procedure                                   */
  /***********************************************************************/
  prDescEvtCmd5EidStart = CrPsCmd5EidStartCreate(NULL);
  if (FwPrCheck(prDescEvtCmd5EidStart) != prSuccess)
    {
      return EXIT_FAILURE;
    }

  /* initialize Datapool Values */
  initDpServEvt(); 
  
  return EXIT_SUCCESS;
}

/**
 * Execution of CORDET Framework PUS Extension components
 */
void CrPsExecServEvt()
{
  return;
}

/**
 * Getter for EvtCmd5EidStart procedure descriptor
 */
inline FwPrDesc_t getPrDescEvtCmd5EidStart()
{
  return prDescEvtCmd5EidStart;
}
