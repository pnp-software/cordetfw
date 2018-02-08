/**
 * @file CrPsPktUtil.c
 * @ingroup Utilities
 * @ingroup pktgetset
 *
 * @brief generic Interface for accessing fields in packets.
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

#include <CrPsUserConstants.h>

/**
 * Generic Getter for Int Values from a Packet
 * \param p Pointer to the packet.
 * \param pos Position of the Int Value
 * \return integer Value from the packet starting at position "pos"
 */
uint32_t getPcktInt(void* p, uint32_t pos)
{
  uint32_t t;
  (void)memcpy(&t, &((uint8_t*)p)[pos], sizeof(t));
  return __builtin_bswap32(t);
}

/**
 * Generic Getter for Short Values from a Packet
 * \param p Pointer to the packet.
 * \param pos Position of the Short Value
 * \return short Value from the packet starting at position "pos"
 */
uint16_t getPcktShort(void* p, uint32_t pos)
{
  uint16_t t;
  (void)memcpy(&t, &((uint8_t*)p)[pos], sizeof(t));
  return __builtin_bswap16(t);
}

/**
 * Generic Getter for Character Values from a Packet
 * \param p Pointer to the packet.
 * \param pos Position of the Character Value
 * \return char Value from the packet starting at position "pos"
 */
uint8_t getPcktChar(void* p, uint32_t pos)
{
  uint8_t t;
  (void)memcpy(&t, &((uint8_t*)p)[pos], sizeof(t));
  return t;
}

/**
 * Generic Setter for Int Values from a Packet
 * \param p Pointer to the packet.
 * \param pos Position of the Int Value
 * \param t The Value to be set into the Packet
 */
void setPcktInt(void* p, uint32_t pos, uint32_t t)
{
  t=__builtin_bswap32(t);
  (void)memcpy(&((uint8_t*)p)[pos], &t, sizeof(t));
}

/**
 * Generic Setter for Short Values from a Packet
 * \param p Pointer to the packet.
 * \param pos Position of the Short Value
 * \param t The Value to be set into the Packet
 */
void setPcktShort(void* p, uint32_t pos, uint16_t t)
{
  t=__builtin_bswap16(t);
  (void)memcpy(&((uint8_t*)p)[pos], &t, sizeof(t));
}

/**
 * Generic Setter for Character Values from a Packet
 * \param p Pointer to the packet.
 * \param pos Position of the Character Value
 * \param t The Value to be set into the Packet
 */
void setPcktChar(void* p, uint32_t pos, uint8_t t)
{
  (void)memcpy(&((uint8_t*)p)[pos], &t, sizeof(t));
}


/*----------------------------------------------------------------------------*/
