/**
 * \file
 *
 * Implementation of TM(5,8) EvtRepDisabledRep.
 *
 * \note This file was generated on 2017-09-19 12:36:09
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSSPCEVTREPDISABLEDREP_H_
#define CRPSSPCEVTREPDISABLEDREP_H_

#include "CrPsDpTypes.h"

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Enable check of TM(5,8) EvtRepDisabledRep.
 * Report is always enabled
 * \param smDesc The state machine descriptor.
 * \return The enable check result.
 */
CrFwBool_t CrPsEvtRepDisabledRepEnableCheck(FwSmDesc_t smDesc);

/**
 * Ready check of TM(5,8) EvtRepDisabledRep.
 * Report is always ready
 * \param smDesc The state machine descriptor.
 * \return The ready check result.
 */
CrFwBool_t CrPsEvtRepDisabledRepReadyCheck(FwSmDesc_t smDesc);

/**
 * Repeat check of TM(5,8) EvtRepDisabledRep.
 * Report is never repeated
 * \param smDesc The state machine descriptor.
 * \return The repeat check result.
 */
CrFwBool_t CrPsEvtRepDisabledRepRepeatCheck(FwSmDesc_t smDesc);

/**
 * Update action of TM(5,8) EvtRepDisabledRep.
 * Load the list of disabled event identifiers from arrays isEidEn-
 * abled1 to isEidEnabled4
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtRepDisabledRepUpdateAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSSPCEVTREPDISABLEDREP_H */
