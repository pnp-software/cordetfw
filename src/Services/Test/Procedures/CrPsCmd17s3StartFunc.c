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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VER_REP_CR_FD 3

FwSmDesc_t cmd, rep;


/* ------------------------------------------------------------------------------------ */
/* Action for node N1. */
void CrPsTestOnBoardConnectionStartN1(FwPrDesc_t __attribute__((unused)) prDesc)
{
  unsigned short areYouAliveSrc;

  /* Set areYouAliveSrc to zero */

  printf("CrPsTestOnBoardConnectionStartN1()\n");

  areYouAliveSrc = 0;
  setDpAreYouAliveSrc(areYouAliveSrc);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N2. */
void CrPsTestOnBoardConnectionStartN2(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Retrieve an OutComponent of type (17,1) from the OutFactory */

  printf("CrPsTestOnBoardConnectionStartN2()\n");

  /* Create out component */
  cmd = CrFwOutFactoryMakeOutCmp(CRPS_TEST, CRPS_TEST_AREYOUALIVE_CONNECTION_CMD, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N3. */
void CrPsTestOnBoardConnectionStartN3(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* TODO: Generate error report OUTFACTORY_FAIL */

  printf("CrPsTestOnBoardConnectionStartN3()\n");

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N4. */
void CrPsTestOnBoardConnectionStartN4(FwPrDesc_t __attribute__((unused)) prDesc)
{
  unsigned short destId;

  /* Configure (17,1) OutComponent */

  printf("CrPsTestOnBoardConnectionStartN4()\n");

  /* Get destination Id of target application */
  destId = getDpOnBoardConnectDest();
  printf("CrPsTestOnBoardConnectionStartN4(): destId = %d\n", destId);

  /* Set out component parameters */
  CrFwOutCmpSetDest(cmd, (CrFwDestSrc_t)destId);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N5. */
void CrPsTestOnBoardConnectionStartN5(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Load OutComponent in OutLoader */

  printf("CrPsTestOnBoardConnectionStartN5()\n");

  CrFwOutLoaderLoad(cmd);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N7. */
void CrPsTestOnBoardConnectionStartN7(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Set outcome of Start Action to 'success' */

  printf("CrPsTestOnBoardConnectionStartN7()\n");

  /*cmpDataStart->outcome = 1;*/

  outcomeStart = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N8. */
void CrPsTestOnBoardConnectionStartN8(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Set outcome of Start Action to 'failure' with failure code VER_REP_CR_FD */

  printf("CrPsTestOnBoardConnectionStartN8()\n");

  /*cmpDataStart->outcome = VER_REP_CR_FD;*/
  outcomeStart = VER_REP_CR_FD;

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N9. */
void CrPsTestOnBoardConnectionStartN9(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Retrieve an OutComponent of type (17,4) from the OutFactory */

  printf("CrPsTestOnBoardConnectionStartN9()\n");

  /* Create out component */
  rep = CrFwOutFactoryMakeOutCmp(CRPS_TEST, CRPS_TEST_ONBOARD_CONNECTION_REP, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N10. */
void CrPsTestOnBoardConnectionStartN10(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* Release (17,1) OutComponent */

  printf("CrPsTestOnBoardConnectionStartN10()\n");

  CrFwOutFactoryReleaseOutCmp(cmd);

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/* Guard on the Control Flow from DECISION1 to N1. */
FwPrBool_t CrPsTestOnBoardConnectionStartG1(FwPrDesc_t __attribute__((unused)) prDesc)
{
  unsigned int i, pos;
  unsigned short appId, destId;

  /* [ Identifier of target application is legal ] */

  printf("CrPsTestOnBoardConnectionStartG1()\n");

  /* get requested target application ID */
  appId = getDpOnBoardConnectDest();

  /* get all target application IDs and check them */
  for (i=0; i<10; i++)
    {
      pos = i;
      destId = getDpOnBoardConnectDestLstItem(pos);
      printf("CrPsTestOnBoardConnectionStartG1(): appId = %d, destId = %d, pos = %d\n", appId, destId, pos);
      if (destId == appId)
        return 1;
    }

  return 0;
}

/* ------------------------------------------------------------------------------------ */
/* Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsTestOnBoardConnectionStartG2(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* [ OutFactory fails to generate OutComponent ] */

  printf("CrPsTestOnBoardConnectionStartG2()\n");

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
FwPrBool_t CrPsTestOnBoardConnectionStartG3(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* [ OutFactory returns OutComponent ] */

  printf("CrPsTestOnBoardConnectionStartG3()\n");

  if (rep != NULL)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}
