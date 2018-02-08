/**
 * @file CrPsUtilitiesServHk.c
 * @ingroup Utilities
 * @ingroup Serv3
 *
 * @brief Implementation of the utility functions of the CORDET Framework PUS Extension Service 3 (Housekeeping)
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

#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServHk.h>

#include <stdlib.h>

/* global handles for the procedures */
FwPrDesc_t prDescHkCmd3s1Start, prDescHkCmd3s3Start, prDescHkRepReadyCheck;
FwPrDesc_t prDescMultiSidCmdStart, prDescCmd3s9Prgr;


/**
 * Initialization of CORDET Framework PUS Extension components
 */
int CrPsInitServHk()
{
  /***********************************************************************/
  /* Service Housekeeping Create Hk ParRep Procedure                     */
  /***********************************************************************/
  prDescHkCmd3s1Start = CrPsCmd3s1StartCreate(NULL);
  if (FwPrCheck(prDescHkCmd3s1Start) != prSuccess)
    {
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Housekeeping Delete HK Struct Procedure                     */
  /***********************************************************************/
  prDescHkCmd3s3Start = CrPsCmd3s3StartCreate(NULL);
  if (FwPrCheck(prDescHkCmd3s3Start) != prSuccess)
    {
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Housekeeping HkRep Ready Check Procedure                    */
  /***********************************************************************/
  prDescHkRepReadyCheck = CrPsRep3s25ReadyCreate(NULL);
  if (FwPrCheck(prDescHkRepReadyCheck) != prSuccess)
    {
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Housekeeping Multi-SID Command Procedure                    */
  /***********************************************************************/
  prDescMultiSidCmdStart = CrPsCmd3SidStartCreate(NULL);
  if (FwPrCheck(prDescMultiSidCmdStart) != prSuccess) {
    return EXIT_FAILURE;
  }

  /***********************************************************************/
  /* Service Housekeeping HkRepStructCmd Command Procedure               */
  /***********************************************************************/
  prDescCmd3s9Prgr = CrPsCmd3s9PrgrCreate(NULL);
  if (FwPrCheck(prDescCmd3s9Prgr) != prSuccess) {
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
  return;
}

/**
 * Getter for HkCmd3s1Start procedure descriptor
 */
inline FwPrDesc_t getPrDescHkCmd3s1Start()
{
  return prDescHkCmd3s1Start;
}

/**
 * Getter for HkCmd3s3Start procedure descriptor
 */
inline FwPrDesc_t getPrDescHkCmd3s3Start()
{
  return prDescHkCmd3s3Start;
}

/**
 * Getter for HkRepReadyCheck procedure descriptor
 */
inline FwPrDesc_t getPrDescHkRepReadyCheck()
{
  return prDescHkRepReadyCheck;
}

/**
 * Getter for MultiSidCmdStart procedure descriptor
 */
inline FwPrDesc_t getPrDescMultiSidCmdStart()
{
  return prDescMultiSidCmdStart;
}

/**
 * Getter for Cmd3s9Prgr procedure descriptor
 */
inline FwPrDesc_t getPrDescCmd3s9Prgr()
{
  return prDescCmd3s9Prgr;
}
