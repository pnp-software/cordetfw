/**
 * \file
 *
 * Implementation of TM(13,1) LptDownFirstRep.
 *
 * \note This file was generated on 2017-11-22 12:47:43
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSLPTDOWNFIRSTREP_H_
#define CRPSLPTDOWNFIRSTREP_H_

#include "CrPsDpTypes.h"

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Enable check of TM(13,1) LptDownFirstRep.
 * Report is enabled if the LPT State Machine is in state DOWN_TRANSFER
 * \param smDesc The state machine descriptor.
 * \return The enable check result.
 */
CrFwBool_t CrPsLptDownFirstRepEnableCheck(FwSmDesc_t smDesc);

/**
 * Update action of TM(13,1) LptDownFirstRep.
 * Load the first part of the large packet from the LPT Buffer; set the
 * transaction identifier equal to largeMsgTransId ; set the partnumber equal
 * to partSeqNmb ; increment partSeqNmb ; and decrement lptRemSize by partSize
 * \param smDesc The state machine descriptor.
 */
void CrPsLptDownFirstRepUpdateAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSLPTDOWNFIRSTREP_H */
