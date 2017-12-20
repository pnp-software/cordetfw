/**
 * \file
 *
 * Implementation of TM(13,16) LptUpAbortRep.
 *
 * \note This file was generated on 2017-11-22 12:47:43
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSLPTUPABORTREP_H_
#define CRPSLPTUPABORTREP_H_

#include "CrPsDpTypes.h"

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Update action of TM(13,16) LptUpAbortRep.
 * The large message transaction identifier is taken from parameter
 * largeMsgTransId and the failure reason is read from variable lptFailCode.
 * \param smDesc The state machine descriptor.
 */
void CrPsLptUpAbortRepUpdateAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSLPTUPABORTREP_H */
