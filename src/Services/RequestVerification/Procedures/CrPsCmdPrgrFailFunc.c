/**
 * @file CrPsCmdPrgrFailFunc.c
 * @ingroup Serv1
 * @ingroup procedures
 *
 * @brief This procedure is run when a command has failed its progress check.
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 17:58:12
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

/** CrPsCmdPrgrFail function definitions */
#include "CrPsCmdPrgrFailCreate.h"

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
#include <DataPool/CrPsDpServReqVerif.h>

#include <stdlib.h>
#include <time.h>

static FwSmDesc_t rep;


/* ----------------------------------------------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------------------ */
/** Action for node N2. */
void CrPsCmdPrgrFailN2(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* Retrieve an OutComponent of type (1,6) from the OutFactory */
  
  /* Create out component */
  rep = CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, CRPS_REQVERIF_PROG_FAIL, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N3. */
void CrPsCmdPrgrFailN3(FwPrDesc_t prDesc)
{
  CrPsRepErrCode_t errCode;

  CRFW_UNUSED(prDesc);

  /* Generate error report OUTFACTORY_FAIL */

  errCode = crOutfactoryFail;
  CrPsRepErr(errCode, CRPS_REQVERIF, CRPS_REQVERIF_PROG_FAIL, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N4. */
void CrPsCmdPrgrFailN4(FwPrDesc_t prDesc)
{
  CrFwDestSrc_t     source;
  CrPsFailData_t    VerFailData;
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
  setVerFailedPrgrRepRid(pckt, Rid);

  /* Set step Id */
  setVerFailedPrgrRepStepId(pckt, (CrPsStepId_t)prData->ushortParam1);

  /* Set failCodeAccFailed = discriminant */
  setVerFailedPrgrRepFailureCode(pckt, (CrPsFailCode_t)prData->ushortParam2);

  /* Set verFailData */
  VerFailData = getDpverFailData();
  setVerFailedPrgrRepFailureData(pckt, VerFailData); 

  /* Set the destination of the report to the source of the in-coming packet */
  source = CrFwPcktGetSrc(inPckt);
  CrFwOutCmpSetDest(rep, source);

  /* Load report in the Outloader */
  CrFwOutLoaderLoad(rep);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N5. */
void CrPsCmdPrgrFailN5(FwPrDesc_t prDesc)
{
  CrFwCounterU4_t nOfPrgrFailed;

  CRFW_UNUSED(prDesc);
  
  /* Increment data pool variable nOfPrgrFailed */

  nOfPrgrFailed = getDpnOfPrgrFailed();
  nOfPrgrFailed += 1;
  setDpnOfPrgrFailed(nOfPrgrFailed);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N6. */
void CrPsCmdPrgrFailN6(FwPrDesc_t prDesc)
{
  CrFwTypeId_t     PacketId;
  CrFwCmpData_t   *inData;
  CrFwInCmdData_t *inSpecificData;
  CrFwPckt_t       inPckt;
  FwSmDesc_t       smDesc;
  prData_t        *prData;

  /* Update data pool variable pcktIdPrgrFailed, failCodePrgrFailed and prgrStepFailed */

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);
  smDesc = prData->smDesc;

   /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* Set pcktIdPrgrFailed */
  PacketId = CrFwPcktGetApid(inPckt); /* --- adaptation point CrFwPckt ---> */
  setDppcktIdPrgrFailed(PacketId);

  /* Set failCodePrgrFailed */
  setDpfailCodePrgrFailed(prData->ushortParam2);

  /* Set prgrStepFailed */
  setDpstepPrgrFailed(prData->ushortParam1);

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsCmdPrgrFailG1(FwPrDesc_t prDesc)
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

