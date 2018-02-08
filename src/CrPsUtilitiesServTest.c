/**
 * @file CrPsUtilitiesServTest.c
 * @ingroup Utilities
 * @ingroup Serv17
 *
 * @brief Implementation of the utility functions of the CORDET Framework PUS Extension Service 17 (Test)
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

#include "CrPsUtilitiesServTest.h"
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
#include <Services/Test/Procedures/CrPsCmd17s3StartCreate.h>
#include <Services/Test/Procedures/CrPsCmd17s3PrgrCreate.h>

#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServTest.h>
#include <DataPool/CrPsDpServReqVerif.h>
#include <DataPool/CrPsDpServHk.h>
#include <DataPool/CrPsDpServEvt.h>
/*hier CrPsDpPkt dateien hinzufügen!*/

#include <stdlib.h>

/* global handles for the procedures */
FwPrDesc_t prDescServTestOnBoardConnStart, prDescServTestOnBoardConnPrgr;


/**
 * Initialization of CORDET Framework PUS Extension application-specific components
 */
void CrPsInitServTestApp(unsigned short onBoardTestConnectAppId)
{
  uint16_t destId;
  uint32_t i, pos;

  /*************************************************************/
  /* Service Test On-Board Connection Data Pool Initialization */
  /*************************************************************/
  for (i=0; i<10; i++)
    {
      pos = i;
      destId = getDpOnBoardConnectDestLstItem(pos);
      if (destId == 0) /* got empty#include <> slot */
        {
          setDpOnBoardConnectDestLstItem(pos, onBoardTestConnectAppId);
          return;
        }
    }

  return;
}

/**
 * Initialization of CORDET Framework PUS Extension components
 */
int CrPsInitServTest()
{

  /***********************************************************************/
  /* Initialization of Data Pool variables and parameter                 */
  /***********************************************************************/
  setDpAreYouAliveTimeOut(10);

  /***********************************************************************/
  /* Service Test On-Board Connection Start Procedure                    */
  /***********************************************************************/
  prDescServTestOnBoardConnStart = CrPsCmd17s3StartCreate(NULL);
  if (FwPrCheck(prDescServTestOnBoardConnStart) != prSuccess)
    {
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Test On-Board Connection Progress Procedure                 */
  /***********************************************************************/
  prDescServTestOnBoardConnPrgr = CrPsCmd17s3PrgrCreate(NULL);
  if (FwPrCheck(prDescServTestOnBoardConnPrgr) != prSuccess)
    {
      return EXIT_FAILURE;
    }

  /* initialize Datapool Values */
  initDpServTest();

  return EXIT_SUCCESS;
}

/**
 * Execution of CORDET Framework PUS Extension components
 */
void CrPsExecServTest()
{

  FwPrExecute(prDescServTestOnBoardConnStart);
  /*FwPrExecute(prDescServTestOnBoardConnPrgr);*/

  return;
}

/**
 * Getter for TestOnBoardConnStart procedure descriptor
 */
inline FwPrDesc_t getPrDescServTestOnBoardConnStart()
{
  return prDescServTestOnBoardConnStart;
}

/**
 * Getter for TestOnBoardConnPrgr procedure descriptor
 */
inline FwPrDesc_t getPrDescServTestOnBoardConnPrgr()
{
  return prDescServTestOnBoardConnPrgr;
}
