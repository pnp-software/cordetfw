/**
 * @file CrPsCmdVerSuccFunc.c
 * @ingroup Serv1
 * @ingroup procedures
 *
 * @brief This procedure is run when a command has passed its acceptance, start or termination check
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 18:2:22
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

/** CrPsCmdVerSucc function definitions */
#include "CrPsCmdVerSuccCreate.h"

/** FW Profile function definitions */
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwSmConfig.h"

#include "Pckt/CrFwPckt.h" /* --- interface to adaptation point CrFwPckt --- */
#include <CrFwCmpData.h>
#include <OutFactory/CrFwOutFactory.h>
#include <OutLoader/CrFwOutLoader.h>
#include <OutCmp/CrFwOutCmp.h>

#include <CrPsRepErr.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServReqVerif.h>
#include <Services/General/CrPsPktServReqVerifSupp.h>
#include <Services/General/CrPsPktUtil.h>

#include <stdlib.h>
#include <time.h>

static FwSmDesc_t rep;

/* ----------------------------------------------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------------------ */
/** Action for node N2. */
void CrPsCmdVerSuccN2(FwPrDesc_t prDesc)
{
  prData_t* prData;

  /* Retrieve an OutComponent of type (1,1), (1,3) or (1,7) from the OutFactory */

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);
  rep = NULL;

  /* Create out component */
  rep = CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, prData->ushortParam1, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N3. */
void CrPsCmdVerSuccN3(FwPrDesc_t prDesc)
{
  CrPsRepErrCode_t errCode;

  CRFW_UNUSED(prDesc);
  
  /* Generate error report OUTFACTORY_FAIL */

  errCode = crOutfactoryFail;
  CrPsRepErr(errCode, CRPS_TEST, CRPS_TEST_AREYOUALIVE_CONNECTION_CMD, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N4. */
void CrPsCmdVerSuccN4(FwPrDesc_t prDesc)
{
  CrFwDestSrc_t     source;
  CrFwCmpData_t    *inData;
  CrFwInCmdData_t  *inSpecificData;
  CrFwPckt_t        inPckt;
  FwSmDesc_t        smDesc;
  prData_t         *prData;
  CrFwCmpData_t    *cmpDataStart;
  CrFwOutCmpData_t *cmpSpecificData;
  CrFwPckt_t        pckt;
  CrPsRid_t         Rid; /* The request ID containing the packet version number the packet id and the packet sequence control */

  cmpDataStart    = (CrFwCmpData_t   *) FwSmGetData(rep);
  cmpSpecificData = (CrFwOutCmpData_t *) cmpDataStart->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Configure report and load it in the OutLoader */

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);

  /*smDesc = prData[0];*/
  smDesc = prData->smDesc;

   /* Get in packet */
  inData         = FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  Rid = getPcktRid(inPckt);

  if (prData->ushortParam1 == CRPS_REQVERIF_ACC_SUCC)
  {
    /* 1,1 */
    /* Set pcktIdAccFailed */
    setVerSuccessAccRepRid(pckt, Rid);
  }

  if (prData->ushortParam1 == CRPS_REQVERIF_START_SUCC)
  {
    /* 1,3 */
    /* Set pcktIdAccFailed */
    setVerSuccessStartRepRid(pckt, Rid);
  }

  if (prData->ushortParam1 == CRPS_REQVERIF_TERM_SUCC)
  {
    /* 1,7 */
    /* Set pcktIdAccFailed */
    setVerSuccessTermRepRid(pckt, Rid);
  }

  /* Set the destination of the report to the source of the in-coming packet */
  source = CrFwPcktGetSrc(inPckt);
  CrFwOutCmpSetDest(rep, source);

  /* Load report in the Outloader */
  CrFwOutLoaderLoad(rep);

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsCmdVerSuccG1(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* [ OutFactory fails to generate OutComponent ] */  
  
  if (rep == NULL)
    {
      return 1;
    }
  else
    {
      return 0;
    }

}

/* ----------------------------------------------------------------------------------------------------------------- */

