/**
 * @file CrPsHkDiagOneShotRep.c
 * @ingroup CrIaServices
 * @authors FW Profile code generator, P&P Software GmbH, 2015; Institute for Astrophysics, 2015-2016
 *
 * @brief Implementation of the One-Shot Diagnostic Report (response to command (3,28)) out-going report packet.
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

#include "CrPsHkDiagOneShotRep.h"

#include <FwPrConfig.h>
#include <FwSmConfig.h>

#include <OutCmp/CrFwOutCmp.h>
#include <Pckt/CrFwPckt.h>

#include <CrFwCmpData.h>

#include <stdlib.h>
#include <stdio.h>
#include "CrPsDebug.h"

CrFwBool_t CrPsHkDiagOneShotRepEnableCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  /* Report is always enabled */

  DEBUGP_3("CrPsHkDiagOneShotRepEnableCheck: \n");

  return 1;
}

CrFwBool_t CrPsHkDiagOneShotRepReadyCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Report is always ready */

  DEBUGP_3("CrPsHkDiagOneShotRepReadyCheck:  \n");

  return 1;
}



CrFwBool_t CrPsHkDiagOneShotRepRepeatCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Report is never repeated */

  DEBUGP_3("CrPsHkDiagOneShotRepRepeatCheck:  \n");

  return 0;
}


void CrPsHkDiagOneShotRepUpdateAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  CrFwDiscriminant_t  disc;
  unsigned char       sid;

  /* Load the value of the simply-commutated data items from the data pool 
   * and that of the super-commutated data items from the Sampling Buffer associated to the report’s SID 
   * according to the Report Definition. */

  /* Get packet and discriminant */
  cmpData	        = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt		        = cmpSpecificData->pckt;
  disc            = CrFwPcktGetDiscriminant(pckt);

  /* Set SID equal to discriminant */
  sid = (unsigned char) disc;
  CRFW_UNUSED(sid);

  DEBUGP_3("CrPsHkDiagOneShotRepUpdateAction: TBD \n");

  return;
}