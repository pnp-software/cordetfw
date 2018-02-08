/**
 * @file CrPsCmdPrgrSuccFunc.c
 * @ingroup Serv1
 * @ingroup procedures
 *
 * @brief This procedure is run when a command has passed its progress check
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 17:59:40
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

/** CrPsCmdPrgrSucc function definitions */
#include "CrPsCmdPrgrSuccCreate.h"

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
void CrPsCmdPrgrSuccN2(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* Retrieve an OutComponent of type (1,5) from the OutFactory */

  /* Create out component */
  rep = CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, CRPS_REQVERIF_PROG_SUCC, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N3. */
void CrPsCmdPrgrSuccN3(FwPrDesc_t prDesc)
{
  CrPsRepErrCode_t errCode;

  CRFW_UNUSED(prDesc);

  /* Generate error report OUTFACTORY_FAIL */

  errCode = crOutfactoryFail;
  CrPsRepErr(errCode, CRPS_REQVERIF, CRPS_REQVERIF_PROG_SUCC, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N4. */
void CrPsCmdPrgrSuccN4(FwPrDesc_t prDesc)
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
  CrPsRid_t         Rid;

  cmpDataStart    = (CrFwCmpData_t   *) FwSmGetData(rep);
  cmpSpecificData = (CrFwOutCmpData_t *) cmpDataStart->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Configure report and load it in the OutLoader */

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);

  smDesc = prData->smDesc;

   /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* set Packet request ID */
  Rid = getPcktRid(inPckt);
  setVerSuccessPrgrRepRid(pckt, Rid);

  /* Set stepId */
  setVerSuccessPrgrRepStepId(pckt, (CrPsStepId_t)prData->ushortParam1);

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
FwPrBool_t CrPsCmdPrgrSuccG1(FwPrDesc_t prDesc)
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

