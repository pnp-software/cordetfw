/**
 * @file CrPsUtilities.c
 *
 * Implementation of the utility functions of the CORDET Framework PUS Extension
 *
 * @author code generator
 * edited: Christian Reimers
 * 25.05.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
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

#include <stdio.h>
#include <stdlib.h>

/* global handles for the procedures */
FwPrDesc_t prDescEvtCmd5EidStart; 

/**
 * Initialization of CORDET Framework PUS Extension components
 */
int CrPsInitServEvt()
{
  printf("CrPsInitServEvt()\n");

  /***********************************************************************/
  /* Service Event Reporting Procedure                                   */
  /***********************************************************************/
  prDescEvtCmd5EidStart = CrPsCmd5EidStartCreate(NULL);
  if (FwPrCheck(prDescEvtCmd5EidStart) != prSuccess)
    {
      printf("The procedure prDescEvtCmd5EidStart is NOT properly configured ... FAILURE\n");
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
  printf("CrPsExecServEvt()\n");

  return;
}

/**
 * Getter for EvtCmd5EidStart procedure descriptor
 */
inline FwPrDesc_t getPrDescEvtCmd5EidStart()
{
  return prDescEvtCmd5EidStart;
}
