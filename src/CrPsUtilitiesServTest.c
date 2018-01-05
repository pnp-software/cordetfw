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

#include <stdio.h>
#include <stdlib.h>

/* global handles for the procedures */
FwPrDesc_t prDescServTestOnBoardConnStart, prDescServTestOnBoardConnPrgr;


/**
 * Initialization of CORDET Framework PUS Extension application-specific components
 */
void CrPsInitServTestApp(unsigned short onBoardTestConnectAppId)
{
  unsigned short destId;
  unsigned int i, pos;

  printf("CrPsInitServTestApp(%d): Mult = %d\n", onBoardTestConnectAppId, 10);

  /*************************************************************/
  /* Service Test On-Board Connection Data Pool Initialization */
  /*************************************************************/
  for (i=0; i<10; i++)
    {
      pos = i;
      destId = getDpOnBoardConnectDestLstItem(pos);
      printf("CrPsInitServTestApp(): got destId %d at slot %d from data pool\n", destId, i);
      if (destId == 0) /* got empty#include <> slot */
        {
          printf("CrPsInitServTestApp(): new slot for appId found: pos = %d\n", pos);
          setDpOnBoardConnectDestLstItem(pos, onBoardTestConnectAppId);
          return;
        }
    }

  printf("CrPsInitServTestApp(): no empty slot found!\n");
  return;
}

/**
 * Initialization of CORDET Framework PUS Extension components
 */
int CrPsInitServTest()
{
  printf("CrPsInitServTest()\n");

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
      printf("Service Test On-Board Connection Start PR is NOT properly configured ... FAILURE\n");
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Test On-Board Connection Progress Procedure                 */
  /***********************************************************************/
  prDescServTestOnBoardConnPrgr = CrPsCmd17s3PrgrCreate(NULL);
  if (FwPrCheck(prDescServTestOnBoardConnPrgr) != prSuccess)
    {
      printf("Service Test On-Board Connection Progress PR is NOT properly configured ... FAILURE\n");
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
  printf("CrPsExecServTest()\n");

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
