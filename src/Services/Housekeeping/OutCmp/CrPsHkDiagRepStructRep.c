/**
 * @file CrPsHkDiagRepStructRep.c
 * @ingroup CrIaServices
 * @authors FW Profile code generator, P&P Software GmbH, 2015; Institute for Astrophysics, 2015-2016
 *
 * @brief Implementation of the Diagnostic Structure Report (3,12) out-going report packet.
 *
 * @copyright
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */

#include "CrPsHkDiagRepStructRep.h"

#include <FwPrConfig.h>
#include <FwSmConfig.h>

#include <OutCmp/CrFwOutCmp.h>
#include <Pckt/CrFwPckt.h>

#include <CrFwCmpData.h>

#include <stdlib.h>
#include <stdio.h>
#include "CrPsDebug.h"

CrFwBool_t CrPsHkDiagRepStructRepEnableCheck(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  CrFwDiscriminant_t  disc;
  unsigned char       sid;

  /* The enable status is read from the isEnabled field of the Report Definition corresponding to the report’s SID */

  /* Get packet and discriminant */
  cmpData         = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;
  disc            = CrFwPcktGetDiscriminant(pckt);

  /* Set SID equal to discriminant */
  sid = (unsigned char) disc;
  CRFW_UNUSED(sid);

  DEBUGP_3("CrPsHkDiagRepStructRepEnableCheck: The enable status is read from the isEnabled field of the Report Definition \n");

  return 1;
}

CrFwBool_t CrPsHkDiagRepStructRepReadyCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Report is always ready */

  DEBUGP_3("CrPsHkDiagRepStructRepReadyCheck:  \n");

  return 1;
}



CrFwBool_t CrPsHkDiagRepStructRepRepeatCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Report is never repeated */

  DEBUGP_3("CrPsHkDiagRepStructRepRepeatCheck:  \n");

  return 0;
}


void CrPsHkDiagRepStructRepUpdateAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  CrFwDiscriminant_t  disc;
  unsigned char       sid;

  /* Load the SID definition from the RDL */

  /* Get packet and discriminant */
  cmpData	        = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt		        = cmpSpecificData->pckt;
  disc            = CrFwPcktGetDiscriminant(pckt);

  /* Set SID equal to discriminant */
  sid = (unsigned char) disc;
  CRFW_UNUSED(sid);

  DEBUGP_3("CrPsHkDiagRepStructRepUpdateAction: TBD \n");

  return;
}