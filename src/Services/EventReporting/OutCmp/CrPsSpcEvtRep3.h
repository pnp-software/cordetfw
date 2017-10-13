/**
 * \file
 *
 * Implementation of TM(5,3) EvtRep3.
 *
 * \note This file was generated on 2017-09-19 12:36:09
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSSPCEVTREP3_H_
#define CRPSSPCEVTREP3_H_

#include "CrPsDpTypes.h"

#include <FwSmCore.h>
#include <CrFwConstants.h>

/**
 * Enable check of TM(5,3) EvtRep3.
 * Update service 5 observable nOfDetectedEvt x (’x’ is the event
 * severity level) and then retrieve the enable status from the Our-
 * Registry as a function of the report type, sub-type and discrimi-
 * nant
 * \param smDesc The state machine descriptor.
 * \return The enable check result.
 */
CrFwBool_t CrPsEvtRep3EnableCheck(FwSmDesc_t smDesc);

/**
 * Ready check of TM(5,3) EvtRep3.
 * Report is always ready
 * \param smDesc The state machine descriptor.
 * \return The ready check result.
 */
CrFwBool_t CrPsEvtRep3ReadyCheck(FwSmDesc_t smDesc);

/**
 * Repeat check of TM(5,3) EvtRep3.
 * Report is never repeated
 * \param smDesc The state machine descriptor.
 * \return The repeat check result.
 */
CrFwBool_t CrPsEvtRep3RepeatCheck(FwSmDesc_t smDesc);

/**
 * Update action of TM(5,3) EvtRep3.
 * Update service 5 observables: nOfGenEvtRep x, lastEvtEid i,
 * lastEvtTime x (’x’ is the event severity level). Note that the pa-
 * rameter values are set by the application which creates the event
 * report at the time it creates the event report.
 * \param smDesc The state machine descriptor.
 */
void CrPsEvtRep3UpdateAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSSPCEVTREP3_H */
