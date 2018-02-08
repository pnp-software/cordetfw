/**
 * @file CrPsCmd17s3StartFunc.c
 * @ingroup Serv17
 * @ingroup procedures 
 *
 * @brief This procedure is run by the Start Action of the command (17,3)
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: May 23 2017 23:40:11
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

/** CrPsCmd17s3Start function definitions */
#include "CrPsCmd17s3StartCreate.h"

/** FW Profile function definitions */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"

/* Framework function definitions */
#include "Pckt/CrFwPckt.h"
#include "OutFactory/CrFwOutFactory.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"
#include "CrFwCmpData.h"

#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServTest.h>

#include <Services/General/CrPsConstants.h>
#include <Services/Test/InCmd/CrPsTestOnBoardConnection.h> /* for global handles */

#include <CrPsRepErr.h>
#include <CrPsUtilitiesServTest.h>

#include <stdlib.h>
#include <time.h>

static FwSmDesc_t cmd;


/* ------------------------------------------------------------------------------------ */
/* Action for node N1. */
void CrPsTestOnBoardConnectionStartN1(FwPrDesc_t prDesc)
{
  CrPsDestSrc_t areYouAliveSrc; 

  CRFW_UNUSED(prDesc);

  /* Set areYouAliveSrc to zero */

  areYouAliveSrc = 0;
  setDpAreYouAliveSrc(areYouAliveSrc);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N2. */
void CrPsTestOnBoardConnectionStartN2(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  /* Retrieve an OutComponent of type (17,1) from the OutFactory */

  /* Create out component */
  cmd = CrFwOutFactoryMakeOutCmp(CRPS_TEST, CRPS_TEST_AREYOUALIVE_CONNECTION_CMD, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N3. */
void CrPsTestOnBoardConnectionStartN3(FwPrDesc_t prDesc)
{
  CrPsRepErrCode_t errCode;

  CRFW_UNUSED(prDesc);

  /* Generate error report OUTFACTORY_FAIL */

  errCode = crOutfactoryFail;
  CrPsRepErr(errCode, CRPS_TEST, CRPS_TEST_AREYOUALIVE_CONNECTION_CMD, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N4. */
void CrPsTestOnBoardConnectionStartN4(FwPrDesc_t prDesc)
{
  CrFwDestSrc_t destId;

  CRFW_UNUSED(prDesc);

  /* Configure (17,1) OutComponent */

  /* Get destination Id of target application */
  destId = (CrFwDestSrc_t)getDpOnBoardConnectDest();

  /* Set out component parameters */
  CrFwOutCmpSetDest(cmd, destId);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N5. */
void CrPsTestOnBoardConnectionStartN5(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* Load OutComponent in OutLoader */

  CrFwOutLoaderLoad(cmd);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N7. */
void CrPsTestOnBoardConnectionStartN7(FwPrDesc_t prDesc)
{
  FwSmDesc_t     smDesc;
  CrFwCmpData_t *cmpData;

  /* Set outcome of Start Action to 'success' */

  /* Get smDesc from InCmd */
  smDesc = FwPrGetData(prDesc);

  /* Set outcome in InCmd prData to 'success' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N8. */
void CrPsTestOnBoardConnectionStartN8(FwPrDesc_t prDesc)
{
  FwSmDesc_t     smDesc;
  CrFwCmpData_t *cmpData;

  /* Set outcome of Start Action to 'failure' with failure code VER_REP_CR_FD */

  /* Get smDesc from InCmd */
  smDesc = FwPrGetData(prDesc);

  /* Set outcome in InCmd prData to 'failure' (VER_REP_CR_FD) */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = VER_REP_CR_FD;

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N9. */
void CrPsTestOnBoardConnectionStartN9(FwPrDesc_t prDesc)
{
  FwSmDesc_t          rep;
  prDataPrgrAction_t *prDataPrgrActionPtr;

  CRFW_UNUSED(prDesc);

  /* Retrieve an OutComponent of type (17,4) from the OutFactory */

  /* Create out component */
  rep = CrFwOutFactoryMakeOutCmp(CRPS_TEST, CRPS_TEST_ONBOARD_CONNECTION_REP, 0, 0);

  /* Initialize and set prData of procedure */
  prDataPrgrActionPtr = (prDataPrgrAction_t *)malloc(sizeof(prDataPrgrAction_t));
  prDataPrgrActionPtr->smDesc = rep;
  FwPrSetData(getPrDescServTestOnBoardConnPrgr(), prDataPrgrActionPtr);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N10. */
void CrPsTestOnBoardConnectionStartN10(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* Release (17,1) OutComponent */
  CrFwOutFactoryReleaseOutCmp(cmd);

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/* Guard on the Control Flow from DECISION1 to N1. */
FwPrBool_t CrPsTestOnBoardConnectionStartG1(FwPrDesc_t prDesc)
{
  CrFwCounterU4_t i, pos;
  CrPsApid_t      appId;
  CrPsDestSrc_t   destId;

  CRFW_UNUSED(prDesc);

  /* [ Identifier of target application is legal ] */

  /* get requested target application ID */
  appId = getDpOnBoardConnectDest();

  /* get all target application IDs and check them */
  for (i=0; i<10; i++)
    {
      pos = i;
      destId = getDpOnBoardConnectDestLstItem(pos);
      if (destId == appId)
        return 1;
    }

  return 0;
}

/* ------------------------------------------------------------------------------------ */
/* Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsTestOnBoardConnectionStartG2(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* [ OutFactory fails to generate OutComponent ] */

  if (cmd == NULL)
    {
      return 1;
    }
  else
    {
      return 0;
    }

}

/* ------------------------------------------------------------------------------------ */
/* Guard on the Control Flow from DECISION3 to N4. */
FwPrBool_t CrPsTestOnBoardConnectionStartG3(FwPrDesc_t prDesc)
{
  FwSmDesc_t          rep;
  prDataPrgrAction_t *prDataPrgrActionPtr;

  CRFW_UNUSED(prDesc);

  /* [ OutFactory returns OutComponent ] */

  prDataPrgrActionPtr = FwPrGetData(getPrDescServTestOnBoardConnPrgr());
  rep = prDataPrgrActionPtr->smDesc;

  if (rep != NULL)
    {
      return 1;
    }
  else
    {
      return 0;
    }
    
}
