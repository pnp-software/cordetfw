/**
 * @file CrPsCmd17s3StartFunc.c
 * @ingroup CrIaDemo
 *
 * ???
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

/** CrPsCmd17s3Start function definitions */
#include "CrPsCmd17s3StartCreate.h"

/** FW Profile function definitions */
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"

/* Framework function definitions */
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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CrPsDebug.h"

FwSmDesc_t cmd;


/* ------------------------------------------------------------------------------------ */
/* Action for node N1. */
void CrPsTestOnBoardConnectionStartN1(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  CrPsDestSrc_t areYouAliveSrc; /*TODO ... hoffentlich haben wir hier kein durcheinander mit short und char (crps oder crfw descs/rc) */

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
  CRFW_UNUSED(prDesc);
  CrPsRepErrCode_t errCode;

  /* Generate error report OUTFACTORY_FAIL */

  errCode = crOutfactoryFail;
  CrPsRepErr(errCode, CRPS_TEST, CRPS_TEST_AREYOUALIVE_CONNECTION_CMD, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N4. */
void CrPsTestOnBoardConnectionStartN4(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  CrFwDestSrc_t destId;

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
  prDataStartAction_t prDataStartAction;

  /* Set outcome of Start Action to 'success' */

  prDataStartAction.outcome = 1;
  FwPrSetData(prDesc, &prDataStartAction);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N8. */
void CrPsTestOnBoardConnectionStartN8(FwPrDesc_t prDesc)
{
  prDataStartAction_t prDataStartAction;

  /* Set outcome of Start Action to 'failure' with failure code VER_REP_CR_FD */

  prDataStartAction.outcome = VER_REP_CR_FD;
  FwPrSetData(prDesc, &prDataStartAction);

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
  FwPrSetData(prDescServTestOnBoardConnPrgr, prDataPrgrActionPtr);

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
  CRFW_UNUSED(prDesc);
  CrFwCounterU4_t i, pos;
  CrPsApid_t      appId;
  CrPsDestSrc_t   destId;

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

  prDataPrgrActionPtr = FwPrGetData(prDescServTestOnBoardConnPrgr);
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
