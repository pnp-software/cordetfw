/**
 * \file
 *
 * Implementation of TM(13,2) LptDownInterRep.
 *
 * \note This file was generated on 2017-11-22 12:47:43
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSLPTDOWNINTERREP_H_
#define CRPSLPTDOWNINTERREP_H_

#include "CrPsDpTypes.h"

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Enable check of TM(13,2) LptDownInterRep.
 * Report is enabled if the LPT State Machine is in state DOWN_TRANSFER
 * \param smDesc The state machine descriptor.
 * \return The enable check result.
 */
CrFwBool_t CrPsLptDownInterRepEnableCheck(FwSmDesc_t smDesc);

/**
 * Repeat check of TM(13,2) LptDownInterRep.
 * Report is repeated as long as lptRemSize is greater than partSize
 * \param smDesc The state machine descriptor.
 * \return The repeat check result.
 */
CrFwBool_t CrPsLptDownInterRepRepeatCheck(FwSmDesc_t smDesc);

/**
 * Update action of TM(13,2) LptDownInterRep.
 * Load the next part of the large packet from the LPT Buffer; set the
 * transaction identifier equal to largeMsgTransId; set the part number equal
 * to partSeqNmb; increase partSeqNmb; and decrement lptRemSize by partSize
 * \param smDesc The state machine descriptor.
 */
void CrPsLptDownInterRepUpdateAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSLPTDOWNINTERREP_H */
