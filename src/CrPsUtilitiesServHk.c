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

#include "CrPsUtilitiesServHk.h"
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
#include <Services/Housekeeping/Procedures/CrPsCmd3s1StartCreate.h>
#include <Services/Housekeeping/Procedures/CrPsCmd3s3StartCreate.h>
#include <Services/Housekeeping/Procedures/CrPsCmd3s9PrgrCreate.h>
#include <Services/Housekeeping/Procedures/CrPsRep3s25ReadyCreate.h>
#include <Services/Housekeeping/Procedures/CrPsCmd3SidStartCreate.h>
#include <Services/Housekeeping/Procedures/CrPsCmd3s27PrgrCreate.h>

#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServHk.h>

#include <stdio.h>
#include <stdlib.h>

/* global handles for the procedures */
FwPrDesc_t prDescHkCmd3s1Start, prDescHkCmd3s3Start, prDescCmd3s9Prgr, prDescHkRepReadyCheck;
FwPrDesc_t prDescMultiSidCmdStart, prDescGenerateHkOneShotPrgr;


/**
 * Initialization of CORDET Framework PUS Extension components
 */
int CrPsInitServHk()
{
  printf("CrPsInitServHk()\n");

  /***********************************************************************/
  /* Service Housekeeping Create Hk ParRep Procedure                     */
  /***********************************************************************/
  prDescHkCmd3s1Start = CrPsCmd3s1StartCreate(NULL);
  if (FwPrCheck(prDescHkCmd3s1Start) != prSuccess)
    {
      printf("The procedure CrPsCmd3s1Start is NOT properly configured ... FAILURE\n");
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Housekeeping Delete HK Struct Procedure                     */
  /***********************************************************************/
  prDescHkCmd3s3Start = CrPsCmd3s3StartCreate(NULL);
  if (FwPrCheck(prDescHkCmd3s3Start) != prSuccess)
    {
      printf("The procedure CrPsCmd3s3Start is NOT properly configured ... FAILURE\n");
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Housekeeping HkRep Ready Check Procedure                    */
  /***********************************************************************/
  prDescHkRepReadyCheck = CrPsRep3s25ReadyCreate(NULL);
  if (FwPrCheck(prDescHkRepReadyCheck) != prSuccess)
    {
      printf("The procedure CrPsRep3s25Ready is NOT properly configured ... FAILURE\n");
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Housekeeping Multi-SID Command Procedure                    */
  /***********************************************************************/
  prDescMultiSidCmdStart = CrPsCmd3SidStartCreate(NULL);
  if (FwPrCheck(prDescMultiSidCmdStart) != prSuccess) {
    printf("The procedure CrPsCmd3SidStart is NOT properly configured ... FAILURE\n");
    return EXIT_FAILURE;
  }

  /***********************************************************************/
  /* Service Housekeeping HkRepStructCmd Command Procedure               */
  /***********************************************************************/
  prDescCmd3s9Prgr = CrPsCmd3s9PrgrCreate(NULL);
  if (FwPrCheck(prDescCmd3s9Prgr) != prSuccess) {
    printf("The procedure CrPsCmd3s9Prgr is NOT properly configured ... FAILURE\n");
    return EXIT_FAILURE;
  }

  /***********************************************************************/
  /* Service Housekeeping Generate One-Shot HK Report Procedure          */
  /***********************************************************************/
  prDescGenerateHkOneShotPrgr = CrPsCmd3s27PrgrCreate(NULL);
  if (FwPrCheck(prDescGenerateHkOneShotPrgr) != prSuccess) {
    printf("The procedure CrPsCmd3s27Prgr is NOT properly configured ... FAILURE\n");
    return EXIT_FAILURE;
  }

  /* initialize Datapool Values */
  initDpServHk(); 

  return EXIT_SUCCESS;
}

/**
 * Execution of CORDET Framework PUS Extension components
 */
void CrPsExecServHk()
{
  printf("CrPsExecServHk()\n");

  return;
}
