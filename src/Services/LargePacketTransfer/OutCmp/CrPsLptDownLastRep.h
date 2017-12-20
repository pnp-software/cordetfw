/**
 * \file
 *
 * Implementation of TM(13,3) LptDownLastRep.
 *
 * \note This file was generated on 2017-11-22 12:47:43
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSLPTDOWNLASTREP_H_
#define CRPSLPTDOWNLASTREP_H_

#include "CrPsDpTypes.h"

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Enable check of TM(13,3) LptDownLastRep.
 * Report is enabled if the LPT State Machine is in state DOWN_TRANSFER
 * \param smDesc The state machine descriptor.
 * \return The enable check result.
 */
CrFwBool_t CrPsLptDownLastRepEnableCheck(FwSmDesc_t smDesc);

/**
 * Update action of TM(13,3) LptDownLastRep.
 * Load the last part of the large packet from the LPT Buffer, set the
 * transaction identifier equal to largeMsgTransId; set the partnumber equal
 * to partSeqNmb
 * \param smDesc The state machine descriptor.
 */
void CrPsLptDownLastRepUpdateAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSLPTDOWNLASTREP_H */
