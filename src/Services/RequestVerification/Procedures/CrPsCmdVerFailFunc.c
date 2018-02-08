/**
 * @file CrPsCmdVerFailFunc.c
 * @ingroup Serv1
 * @ingroup procedures
 *
 * @brief This procedure is run when a command has failed its start check or its termination check
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 18:1:13
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
 
/** CrPsCmdVerFail function definitions */
#include "CrPsCmdVerFailCreate.h"

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
void CrPsCmdVerFailN2(FwPrDesc_t prDesc)
{
  prData_t* prData;

  /* Retrieve an OutComponent of type (1,4) or (1,8) from the OutFactory */

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);

  /* Create out component */
  rep = CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, prData->ushortParam2, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N3. */
void CrPsCmdVerFailN3(FwPrDesc_t prDesc)
{
  prData_t        *prData;
  CrPsRepErrCode_t errCode;

  /* Generate error report OUTFACTORY_FAIL */

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);

  errCode = crOutfactoryFail;
  CrPsRepErr(errCode, CRPS_REQVERIF, prData->ushortParam2, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N4. */
void CrPsCmdVerFailN4(FwPrDesc_t prDesc)
{
  CrFwDestSrc_t source;
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
  inData         = FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  Rid = getPcktRid(inPckt);

  if (prData->ushortParam2 == 4)
  {
    /* 1,4 */
    /* set Packet request ID */
    setVerFailedStartRepRid(pckt, Rid);

    /* Set failCodeAccFailed */
    setVerFailedStartRepFailureCode(pckt, (CrPsFailCode_t)prData->ushortParam1);

    /* Set verFailData */
    VerFailData = getDpverFailData();
    setVerFailedStartRepFailureData(pckt, VerFailData);
  }

  if (prData->ushortParam2 == 8)
  {
    /* 1,8 */
    /* set Packet request ID */
    setVerFailedTermRepRid(pckt, Rid);

    /* Set failCodeAccFailed */
    setVerFailedTermRepFailureCode(pckt, (CrPsFailCode_t)prData->ushortParam1);
  
    /* Set verFailData */
    VerFailData = getDpverFailData();
    setVerFailedTermRepFailureData(pckt, VerFailData);
  }

  /* Set the destination of the report to the source of the in-coming packet */
  source = CrFwPcktGetSrc(inPckt);
  CrFwOutCmpSetDest(rep, source);

  /* Load report in the Outloader */
  CrFwOutLoaderLoad(rep);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N5. */
void CrPsCmdVerFailN5(FwPrDesc_t prDesc)
{
  prData_t        *prData;
  CrFwCounterU4_t  nOfStartFailed, nOfTermFailed;

  /* Increment data pool variable nOfXyFailed */

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);

  if (prData->ushortParam2 == CRPS_REQVERIF_START_FAIL)
    {
      nOfStartFailed = getDpnOfStartFailed();
      nOfStartFailed += 1;
      setDpnOfStartFailed(nOfStartFailed);
    }
  else if (prData->ushortParam2 == CRPS_REQVERIF_TERM_FAIL)
    {
      nOfTermFailed = getDpnOfTermFailed();
      nOfTermFailed += 1;
      setDpnOfTermFailed(nOfTermFailed);
    }

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N6. */
void CrPsCmdVerFailN6(FwPrDesc_t prDesc)
{
  CrFwTypeId_t     PacketId;
  CrFwCmpData_t   *inData;
  CrFwInCmdData_t *inSpecificData;
  CrFwPckt_t       inPckt;
  FwSmDesc_t       smDesc;
  prData_t        *prData;

  /* Update data pool variable pcktIdXyFailed and failCodeXyFailed */

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);

  smDesc = prData->smDesc;

   /* Get in packet */
  inData         = FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* Set pcktIdAccFailed */
  PacketId = (CrFwTypeId_t)CrFwPcktGetApid(inPckt); /* --- adaptation point CrFwPckt ---> */

  if (prData->ushortParam2 == CRPS_REQVERIF_START_FAIL)
    {
      /* Set pcktIdStartFailed */
      setDppcktIdStartFailed(PacketId);

      /* Set failCodeStartFailed */
      setDpfailCodeStartFailed(prData->ushortParam1);
    }
  else if (prData->ushortParam2 == CRPS_REQVERIF_TERM_FAIL)
    {
      /* Set pcktIdTermFailed */
      setDppcktIdTermFailed(PacketId);

      /* Set failCodeTermFailed */
      setDpfailCodeTermFailed(prData->ushortParam1);
    }

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsCmdVerFailG1(FwPrDesc_t prDesc)
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

