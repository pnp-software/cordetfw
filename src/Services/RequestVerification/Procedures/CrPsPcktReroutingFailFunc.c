/**
 * @file CrPsPcktReroutingFailFunc.c
 * @ingroup Serv1
 * @ingroup procedures
 *
 * @brief This procedure is run when the InLoader has found a packet with invalid destination
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 18:26:2
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

/** CrPsPcktReroutingFail function definitions */
#include "CrPsPcktReroutingFailCreate.h"

/** FW Profile function definitions */
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwSmConfig.h"

#include "Pckt/CrFwPckt.h" /* --- interface to adaptation point CrFwPckt --- */
#include <CrFwCmpData.h>
#include <BaseCmp/CrFwBaseCmp.h>
#include <OutFactory/CrFwOutFactory.h>
#include <OutLoader/CrFwOutLoader.h>
#include <OutCmp/CrFwOutCmp.h>

#include <CrPsUserConstants.h>
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
/** Action for node N1. */
void CrPsPcktReroutingFailN1(FwPrDesc_t prDesc)
{
  CrFwCmpData_t   *inData;
  CrFwInRepData_t *inSpecificData;
  CrFwPckt_t       inPckt;
  FwSmDesc_t       smDesc;
  prData_t        *prData;
  CrPsRepErrCode_t errCode;

  /* Generate error report INLOADER_INV_DEST */

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);
  smDesc = prData->smDesc;

   /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInRepData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  errCode = crInloaderInvDest;
  CrPsRepErr(errCode, CrFwPcktGetServType(inPckt), CrFwPcktGetServSubType(inPckt), CrFwPcktGetDiscriminant(inPckt));
  
  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N2. */
void CrPsPcktReroutingFailN2(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* Retrieve an OutComponent of type (1,10) from the OutFactory */

  /* Create out component */
  rep = CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, CRPS_REQVERIF_REROUT_FAIL, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N3. */
void CrPsPcktReroutingFailN3(FwPrDesc_t prDesc)
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
void CrPsPcktReroutingFailN4(FwPrDesc_t prDesc)
{
  CrFwDestSrc_t     source;
  CrPsFailData_t    VerFailData;
  CrFwCmpData_t*    inData;
  CrFwInCmdData_t*  inSpecificData;
  CrFwPckt_t        inPckt;
  CrPsRid_t         Rid;
  FwSmDesc_t        smDesc;
  prData_t*         prData;
  CrFwCmpData_t*    cmpDataStart;
  CrFwOutCmpData_t* cmpSpecificData;
  CrFwPckt_t        pckt;

  cmpDataStart    = (CrFwCmpData_t   *) FwSmGetData(rep);
  cmpSpecificData = (CrFwOutCmpData_t *) cmpDataStart->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Configure report (1,10) and load it in the OutLoader */

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);

  smDesc = prData->smDesc;

   /* Get in packet */
  inData          = FwSmGetData(smDesc);
  inSpecificData  = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt          = inSpecificData->pckt;

  /* set Packet request ID */
  Rid = getPcktRid(inPckt);
  setVerFailedRoutingRepRid(pckt, Rid);

  /* Set failCodeAccFailed */
  setVerFailedRoutingRepFailureCode(pckt, (CrPsFailCode_t)INLOADER_INV_DEST); 

  /* Set verFailData */
  VerFailData = getDpverFailData(); /* get it from data pool */
  setVerFailedRoutingRepFailureData(pckt, VerFailData); 

  /* Set the destination of the report to the source of the in-coming packet */
  source = CrFwPcktGetSrc(inPckt);
  CrFwOutCmpSetDest(rep, source);

  /* Load report in the Outloader */
  CrFwOutLoaderLoad(rep);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N5. */
void CrPsPcktReroutingFailN5(FwPrDesc_t prDesc)
{
  CrFwCounterU4_t nOfReroutingFailed;

  CRFW_UNUSED(prDesc);

  /* Increment data pool variable nOfReroutingFailed */

  nOfReroutingFailed = getDpnOfReroutingFailed();
  nOfReroutingFailed += 1;
  setDpnOfReroutingFailed(nOfReroutingFailed);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N6. */
void CrPsPcktReroutingFailN6(FwPrDesc_t prDesc)
{
  CrFwTypeId_t     PacketId;
  CrFwCmpData_t   *inData;
  CrFwInCmdData_t *inSpecificData;
  CrFwPckt_t       inPckt;
  FwSmDesc_t       smDesc;
  prData_t        *prData;

  /* Update data pool variable pcktIdRerouting, invDestRerouting */

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);
  smDesc = prData->smDesc;

   /* Get in packet */
  inData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  inSpecificData = (CrFwInCmdData_t*)inData->cmpSpecificData;
  inPckt         = inSpecificData->pckt;

  /* Set pcktIdRerouting */
  PacketId = CrFwPcktGetApid(inPckt); /* --- adaptation point CrFwPckt ---> */
  setDppcktIdReroutingFailed(PacketId);

  /* Set invDestRerouting */
  setDpinvDestRerouting(prData->ushortParam1);

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION1 to N1. */
FwPrBool_t CrPsPcktReroutingFailG1(FwPrDesc_t prDesc)
{
  FwSmDesc_t smDesc;
  prData_t  *prData;

  /* [ Packet encapsulates a report ] */

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);
  smDesc = prData->smDesc;

  if (CrFwCmpGetTypeId(smDesc) == CR_FW_INREPORT_TYPE)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/** Guard on the Control Flow from DECISION1 to N2. */
FwPrBool_t CrPsPcktReroutingFailG1E(FwPrDesc_t prDesc)
{
  FwSmDesc_t smDesc;
  prData_t  *prData;

  /* [ Packet encapsulates a command ] */

  /* Get procedure parameters */
  prData = FwPrGetData(prDesc);
  smDesc = prData->smDesc;

  if (CrFwCmpGetTypeId(smDesc) == CR_FW_INCOMMAND_TYPE)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/** Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsPcktReroutingFailG2(FwPrDesc_t prDesc)
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

