/**
 * @file CrPsPktServEvtSupp.h
 * @ingroup Serv5
 * @ingroup pktgetset
 *
 * @brief auxiliary Interface for accessing fields in packets of service "ServEvt".
 *
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * 
 * last modification: 22.01.2018
 * 
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#ifndef CRPSPKTSERVEVTSUPP_H_
#define CRPSPKTSERVEVTSUPP_H_

#include <CrPsUserConstants.h>
#include <DataPool/CrPsDpServEvt.h>


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
