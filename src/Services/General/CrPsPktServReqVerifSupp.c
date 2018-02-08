/**
 * @file CrPsPktServReqVerifSupp.c
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

#include <CrPsPkt.h> /* for data structures TmHeader_t and TcHeader_t */
#include <Services/General/CrPsPktServReqVerifSupp.h>
#include <CrPsUserConstants.h>


/**
 * Get "RequestId" from "VerSuccessAcc" packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
CrPsRid_t getVerSuccessAccRepRid(void* p)
{
  CrPsRid_t ret;
  memcpy(&ret, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(CrPsRid_t));
  return __builtin_bswap32(ret);
}

/**
 * Set "RequestId" in a "VerSuccessAcc" packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
void setVerSuccessAccRepRid(void* p, CrPsRid_t Rid)
{
  Rid = __builtin_bswap32(Rid);
  memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &Rid, sizeof(CrPsRid_t));
}

/**
 * Get "RequestId" from "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
CrPsRid_t getVerFailedAccRepRid(void* p)
{
  CrPsRid_t ret;
  memcpy(&ret, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(CrPsRid_t));
  return __builtin_bswap32(ret);
}

/**
 * Set "RequestId" in a "VerFailedAccRep" packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
void setVerFailedAccRepRid(void* p, CrPsRid_t Rid)
{
  Rid = __builtin_bswap32(Rid);
  memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &Rid, sizeof(CrPsRid_t));
}

/**
 * Get "RequestId" from "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
CrPsRid_t getVerSuccessStartRepRid(void* p)
{
  CrPsRid_t ret;
  memcpy(&ret, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(CrPsRid_t));
  return __builtin_bswap32(ret);
}

/**
 * Set "RequestId" in a "VerSuccessStartRep" packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
void setVerSuccessStartRepRid(void* p, CrPsRid_t Rid)
{
  Rid = __builtin_bswap32(Rid);
  memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &Rid, sizeof(CrPsRid_t));
}

/**
 * Get "RequestId" from "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
CrPsRid_t getVerFailedStartRepRid(void* p)
{
  CrPsRid_t ret;
  memcpy(&ret, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(CrPsRid_t));
  return __builtin_bswap32(ret);
}

/**
 * Set "RequestId" in a "VerFailedStartRep" packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
void setVerFailedStartRepRid(void* p, CrPsRid_t Rid)
{
  Rid = __builtin_bswap32(Rid);
  memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &Rid, sizeof(CrPsRid_t));
}

/**
 * Get "RequestId" from "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
CrPsRid_t getVerSuccessPrgrRepRid(void* p)
{
  CrPsRid_t ret;
  memcpy(&ret, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(CrPsRid_t));
  return __builtin_bswap32(ret);
}

/**
 * Set "RequestId" in a "VerSuccessPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
void setVerSuccessPrgrRepRid(void* p, CrPsRid_t Rid)
{
  Rid = __builtin_bswap32(Rid);
  memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &Rid, sizeof(CrPsRid_t));
}

/**
 * Get "RequestId" from "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
CrPsRid_t getVerFailedPrgrRepRid(void* p)
{
  CrPsRid_t ret;
  memcpy(&ret, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(CrPsRid_t));
  return __builtin_bswap32(ret);
}

/**
 * Set "RequestId" in a "VerFailedPrgrRep" packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
void setVerFailedPrgrRepRid(void* p, CrPsRid_t Rid)
{
  Rid = __builtin_bswap32(Rid);
  memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &Rid, sizeof(CrPsRid_t));
}

/**
 * Get "RequestId" from "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
CrPsRid_t getVerSuccessTermRepRid(void* p)
{
  CrPsRid_t ret;
  memcpy(&ret, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(CrPsRid_t));
  return __builtin_bswap32(ret);
}

/**
 * Set "RequestId" in a "VerSuccessTermRep" packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
void setVerSuccessTermRepRid(void* p, CrPsRid_t Rid)
{
  Rid = __builtin_bswap32(Rid);
  memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &Rid, sizeof(CrPsRid_t));
}

/**
 * Get "RequestId" from "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
CrPsRid_t getVerFailedTermRepRid(void* p)
{
  CrPsRid_t ret;
  memcpy(&ret, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(CrPsRid_t));
  return __builtin_bswap32(ret);
}

/**
 * Set "RequestId" in a "VerFailedTermRep" packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
void setVerFailedTermRepRid(void* p, CrPsRid_t Rid)
{
  Rid = __builtin_bswap32(Rid);
  memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &Rid, sizeof(CrPsRid_t));
}

/**
 * Get "RequestId" from "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \return RequestId Item Value.
 */
CrPsRid_t getVerFailedRoutingRepRid(void* p)
{
  CrPsRid_t ret;
  memcpy(&ret, &((uint8_t*)p)[sizeof(TmHeader_t)], sizeof(CrPsRid_t));
  return __builtin_bswap32(ret);
}

/**
 * Set "RequestId" in a "VerFailedRoutingRep" packet.
 * \param p Pointer to the packet.
 * \param rid Variable from where RequestId is copied.
 */
void setVerFailedRoutingRepRid(void* p, CrPsRid_t Rid)
{
  Rid = __builtin_bswap32(Rid);
  memcpy(&((uint8_t*)p)[sizeof(TmHeader_t)], &Rid, sizeof(CrPsRid_t));
}







/*----------------------------------------------------------------------------*/

