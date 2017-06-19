/**
 * @file CrPsReqVerifAccFail.c
 * @ingroup CrPsServices
 * @authors FW Profile code generator, P&P Software GmbH, 2015; Institute for Astrophysics, 2015-2016
 *
 * @brief Implementation of the Telecommand Acceptance Report – Failure out-going report packet.
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

#include "CrPsReqVerifAccFail.h"


void CrPsReqVerifAccFailUpdateAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc); /* remove if smDesc is used in this function */
  /* Implement the action logic here: */

  /* Load the value of the report parameters */
  /* NOT USED: done in IfswUtilities function, which packs and finalizes out-going packet */

  return;
}

