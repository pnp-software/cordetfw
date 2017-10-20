/**
 * \file CrPsPktUtil.h
 *
 * Interface for accessing fields in packets of service "ServHk".
 *
 * \author C. Reimers and M. Rockenbauer 24.10.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#ifndef CRPSPKTUTIL_H_
#define CRPSPKTUTIL_H_

/**
 * Generic Getter for Int Values from a Packet
 * \param p Pointer to the packet.
 * \param pos Position of the Int Value
 * \return integer Value from the packet starting at position "pos"
 */
static inline uint32_t getPcktInt(void* p, uint32_t pos)
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
static inline uint16_t getPcktShort(void* p, uint32_t pos)
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
static inline uint8_t getPcktChar(void* p, uint32_t pos)
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
static inline void setPcktInt(void* p, uint32_t pos, uint32_t t)
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
static inline void setPcktShort(void* p, uint32_t pos, uint16_t t)
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
static inline void setPcktChar(void* p, uint32_t pos, uint8_t t)
{
  (void)memcpy(&((uint8_t*)p)[pos], &t, sizeof(t));
}

/*----------------------------------------------------------------------------*/
#endif /* CRPSPKTUTIL_H */