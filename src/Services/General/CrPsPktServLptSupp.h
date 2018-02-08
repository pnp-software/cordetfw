/**
 * \file CrPsPktServLptSupp.h
 * @ingroup Serv13
 * @ingroup pktgetset
 *
 * @brief auxiliary Interface for accessing fields in packets of service "ServLPT".
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

#ifndef CRPSPKTSERVLPTSUPP_H_
#define CRPSPKTSERVLPTSUPP_H_

#include "CrPsUserConstants.h"

/**
 * Get "Part" from "LptUpLastCmd" packet.
 * \param p Pointer to the packet.
 * \param o offset in parts (PartNumber)
 * \return Value of "Part".
 */
CrPsPart_t getLptUpLastCmdPart(void* p, uint32_t o);

/**
 * Set "Part" in "LptUpLastCmd" packet.
 * \param p Pointer to the packet.
 * \param Part Value of "Part" to be set in packet.
 * \param o offset in parts (PartNumber)
 */
void setLptUpLastCmdPart(void* p, CrPsPart_t Part, uint32_t o);

/**
 * Get "Part" from "LptUpInterCmd" packet.
 * \param p Pointer to the packet.
 * \param o offset in parts (PartNumber)
 * \return Value of "Part".
 */
CrPsPart_t getLptUpInterCmdPart(void* p, uint32_t o);

/**
 * Set "Part" in "LptUpInterCmd" packet.
 * \param p Pointer to the packet.
 * \param Part Value of "Part" to be set in packet.
 * \param o offset in parts (PartNumber)
 */
void setLptUpInterCmdPart(void* p, CrPsPart_t Part, uint32_t o);

/**
 * Get "Part" from "LptUpFirstCmd" packet.
 * \param p Pointer to the packet.
 * \param o offset in parts (PartNumber)
 * \return Value of "Part".
 */
CrPsPart_t getLptUpFirstCmdPart(void* p, uint32_t o);

/**
 * Set "Part" in "LptUpFirstCmd" packet.
 * \param p Pointer to the packet.
 * \param Part Value of "Part" to be set in packet.
 * \param o offset in parts (PartNumber)
 */
void setLptUpFirstCmdPart(void* p, CrPsPart_t Part, uint32_t o);

/**
 * Get "Part" from "LptDownLastRep" packet.
 * \param p Pointer to the packet.
 * \param o offset in parts (PartNumber)
 * \return Value of "Part".
 */
CrPsPart_t getLptDownLastRepPart(void* p, uint32_t o);

/**
 * Set "Part" in "LptDownLastRep" packet.
 * \param p Pointer to the packet.
 * \param Part Value of "Part" to be set in packet.
 * \param o offset in parts (PartNumber)
 */
void setLptDownLastRepPart(void* p,  unsigned char * Part, unsigned short length);

/**
 * Get "Part" from "LptDownInterRep" packet.
 * \param p Pointer to the packet.
 * \param o offset in parts (PartNumber)
 * \return Value of "Part".
 */
CrPsPart_t getLptDownInterRepPart(void* p, uint32_t o);

/**
 * Set "Part" in "LptDownInterRep" packet.
 * \param p Pointer to the packet.
 * \param Part Value of "Part" to be set in packet.
 * \param o offset in parts (PartNumber)
 */
void setLptDownInterRepPart(void* p,  unsigned char * Part, unsigned short length);

/**
 * Get "Part" from "LptDownFirstRep" packet.
 * \param p Pointer to the packet.
 * \param o offset in parts (PartNumber)
 * \return Value of "Part".
 */
CrPsPart_t getLptDownFirstRepPart(void* p, uint32_t o);

/**
 * Set "Part" in "LptDownFirstRep" packet.
 * \param p Pointer to the packet.
 * \param Part Value of "Part" to be set in packet.
 * \param o offset in parts (PartNumber)
 */
/*void setLptDownFirstRepPart(void* p, CrPsPart_t Part, uint32_t o);*/
void setLptDownFirstRepPart(void* p,  unsigned char * Part, unsigned short length);


/*----------------------------------------------------------------------------*/
#endif /* CRPSPKTSERVLPTSUPP_H */
