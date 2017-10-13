/**
 * @file CrPsHkDiagPeriodicRep.c
 * @ingroup CrIaServices
 * @authors FW Profile code generator, P&P Software GmbH, 2015; Institute for Astrophysics, 2015-2016
 *
 * @brief Implementation of the Periodic Diagnostic Report (3,26) out-going report packet.
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

#include "CrPsHkDiagPeriodicRep.h"

#include <FwPrConfig.h>
#include <FwSmConfig.h>

#include <OutCmp/CrFwOutCmp.h>
#include <Pckt/CrFwPckt.h>

#include <CrFwCmpData.h>

#include <stdlib.h>
#include <stdio.h>
#include "CrPsDebug.h"

CrFwBool_t CrPsHkDiagPeriodicRepEnableCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  /* The enable status is read from the isEnabled field of the Report Definition corresponding to the report’s SID */

  DEBUGP_3("CrPsHkDiagPeriodicRepEnableCheck: TBD \n");

  return 1;
}

CrFwBool_t CrPsHkDiagPeriodicRepReadyCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Run the procedure Ready Check of HkRep Report of figure 9.5 */

  DEBUGP_3("CrPsHkDiagPeriodicRepReadyCheck: TBD \n");

  return 1;
}



CrFwBool_t CrPsHkDiagPeriodicRepRepeatCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);

  /* Report is always repeated */

  DEBUGP_3("CrPsHkDiagPeriodicRepRepeatCheck:  \n");

  return 1;
}


void CrPsHkDiagPeriodicRepUpdateAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  CrFwDiscriminant_t  disc;
  unsigned char       sid;

  /* Load the value of the simply-commutated data items from the data pool 
   * and that of the super-commutated data items from the Sampling Buffer 
   * associated to the report’s SID according to the Report Definition. */

  /* Get packet and discriminant */
  cmpData	        = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt		        = cmpSpecificData->pckt;
  disc            = CrFwPcktGetDiscriminant(pckt);

  /* Set SID equal to discriminant */
  sid = (unsigned char) disc;
  CRFW_UNUSED(sid);

  DEBUGP_3("CrPsHkDiagPeriodicRepUpdateAction: TBD \n");

  return;
}