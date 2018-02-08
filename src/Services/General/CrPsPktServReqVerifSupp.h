/**
 * @file CrPsPktServReqVerifSupp.h
 * @ingroup Serv1
 * @ingroup pktgetset
 *
 * @brief auxiliary Interface for accessing fields in packets of service "ServReqVerif".
 *
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * 
 * last modification: 25.01.2018
 * 
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#ifndef CRPSPKTSERVREQVERIFSUPP_H_
#define CRPSPKTSERVREQVERIFSUPP_H_

#include <CrPsUserConstants.h>


/**
 * Get "RequestId" from "VerSuccessAcc" packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
CrPsRid_t getVerSuccessAccRepRid(void* p);

/**
 * Set "RequestId" in "VerSuccessAcc" packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
void setVerSuccessAccRepRid(void* p, CrPsRid_t Rid);

/**
 * Get "RequestId" from "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
CrPsRid_t getVerFailedAccRepRid(void* p);

/**
 * Set "RequestId" in "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
void setVerFailedAccRepRid(void* p, CrPsRid_t Rid);

/**
 * Get "RequestId" from "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
CrPsRid_t getVerSuccessStartRepRid(void* p);

/**
 * Set "RequestId" in "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
void setVerSuccessStartRepRid(void* p, CrPsRid_t Rid);

/**
 * Get "RequestId" from "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
CrPsRid_t getVerFailedStartRepRid(void* p);

/**
 * Set "RequestId" in "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
void setVerFailedStartRepRid(void* p, CrPsRid_t Rid);

/**
 * Get "RequestId" from "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
CrPsRid_t getVerSuccessPrgrRepRid(void* p);

/**
 * Set "RequestId" in "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
void setVerSuccessPrgrRepRid(void* p, CrPsRid_t Rid);

/**
 * Get "RequestId" from "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
CrPsRid_t getVerFailedPrgrRepRid(void* p);

/**
 * Set "RequestId" in "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
void setVerFailedPrgrRepRid(void* p, CrPsRid_t Rid);

/**
 * Get "RequestId" from "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
CrPsRid_t getVerSuccessTermRepRid(void* p);

/**
 * Set "RequestId" in "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
void setVerSuccessTermRepRid(void* p, CrPsRid_t Rid);

/**
 * Get "RequestId" from "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
CrPsRid_t getVerFailedTermRepRid(void* p);

/**
 * Set "RequestId" in "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
void setVerFailedTermRepRid(void* p, CrPsRid_t Rid);

/**
 * Get "RequestId" from "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
CrPsRid_t getVerFailedRoutingRepRid(void* p);

/**
 * Set "RequestId" in "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
void setVerFailedRoutingRepRid(void* p, CrPsRid_t Rid);


/*----------------------------------------------------------------------------*/
#endif /* CRPSPKTSERVREQVERIFSUPP_H */
