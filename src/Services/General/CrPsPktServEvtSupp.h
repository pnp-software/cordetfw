/**
 * \file CrPsPktServEvtSupp.h
 *
 * Interface for accessing fields in packets of service "ServEvt".
 *
 * \author C. Reimers and M. Rockenbauer 24.10.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */
#ifndef CRPSPKTSERVEVTSUPP_H_
#define CRPSPKTSERVEVTSUPP_H_

#include "Services/General/CrPsPktUtil.h"
#include <CrPsUserConstants.h>
#include <DataPool/CrPsDpServEvt.h>
#include <stdio.h>


/**
 * Get "EventId" arrayItem from "EvtEnableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of EventIdArray Item.
 * \return EventId Array Item Value.
 */
CrPsEid_t getEvtEnableCmdEventIdItem(void* p, CrPsNumberU4_t N);

/**
 * Set "EventId" arrayItem in "EvtEnableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of the "N" th EventIdArray Item.
 * \param src Variable from where arrayItem data are copied.
 */
void setEvtEnableCmdEventIdItem(void* p, CrPsNumberU4_t N, CrPsEid_t src);

/**
 * Get "EventId" arrayItem from "EvtDisableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of EventIdArray Item.
 * \return EventId Array Item Value.
 */
CrPsEid_t getEvtDisableCmdEventIdItem(void* p, CrPsNumberU4_t N);

/**
 * Set "EventId" arrayItem in "EvtDisableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of the "N" th EventIdArray Item.
 * \param src Variable from where arrayItem data are copied.
 */
void setEvtDisableCmdEventIdItem(void* p, CrPsNumberU4_t N, CrPsEid_t src);

/**
 * Get "EventId" arrayItem from "EvtRepDisabledRep" packet.
 * \param p Pointer to the packet.
 * \param N Number of EventIdArray Item.
 * \return EventId Array Item Value.
 */
CrPsEid_t getEvtRepDisabledRepEventIdItem(void* p, CrPsNumberU4_t N);

/**
 * Set "EventId" arrayItem in "EvtRepDisabledRep" packet.
 * \param p Pointer to the packet.
 * \param N Value of the "N" th EventIdArray Item.
 * \param src Variable from where arrayItem data are copied.
 */
void setEvtRepDisabledRepEventIdItem(void* p, CrPsNumberU4_t N, CrPsEid_t src);

/**
 * Get the size of a Disabled Event Reporting packet.
 * \param none
 * \return the size of the packet in bytes.
 */
size_t getEvtRepDisabledSize();

/*----------------------------------------------------------------------------*/
#endif /* CRPSPKTSERVEVTSUPP_H */
