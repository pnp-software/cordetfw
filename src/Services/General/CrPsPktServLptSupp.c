/**
 * \file CrPsPktServLptSupp.c
 *
 * Interface for accessing fields in packets of service "ServLpt".
 *
 * \author C. Reimers and M. Rockenbauer 24.10.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include <Services/General/CrPsPktServLptSupp.h>
#include "Services/General/CrPsPktUtil.h"
#include "CrPsUserConstants.h"
#include <Services/General/CrPsPktServLpt.h>
#include <string.h>


/**
 * Get "Part" from "LptUpLastCmd" packet.
 * \param p Pointer to the packet.
 * \param o offset in parts (PartNumber)
 * \return Value of "Part".
 */
CrPsPart_t getLptUpLastCmdPart(void* p, uint32_t o)
{
  CrPsPart_t ret;
  o = sizeof(CrPsPart_t)*o + sizeof(TcHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t);
  memcpy(&ret, &((uint8_t*)p)[o], sizeof(CrPsPart_t));
  return __builtin_bswap16(ret);
}

/**
 * Set "Part" in "LptUpLastCmd" packet.
 * \param p Pointer to the packet.
 * \param Part Value of "Part" to be set in packet.
 * \param o offset in parts (PartNumber)
 */
void setLptUpLastCmdPart(void* p, CrPsPart_t Part, uint32_t o)
{
  o = sizeof(CrPsPart_t)*o + sizeof(TcHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t);
  Part = __builtin_bswap16(Part);
  memcpy(&((uint8_t*)p)[o], &Part, sizeof(CrPsPart_t));
}

/**
 * Get "Part" from "LptUpInterCmd" packet.
 * \param p Pointer to the packet.
 * \param o offset in parts (PartNumber)
 * \return Value of "Part".
 */
CrPsPart_t getLptUpInterCmdPart(void* p, uint32_t o)
{
  CrPsPart_t ret;
  o = sizeof(CrPsPart_t)*o + sizeof(TcHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t);
  memcpy(&ret, &((uint8_t*)p)[o], sizeof(CrPsPart_t));
  return __builtin_bswap16(ret);
}

/**
 * Set "Part" in "LptUpInterCmd" packet.
 * \param p Pointer to the packet.
 * \param Part Value of "Part" to be set in packet.
 * \param o offset in parts (PartNumber)
 */
void setLptUpInterCmdPart(void* p, CrPsPart_t Part, uint32_t o)
{
  o = sizeof(CrPsPart_t)*o + sizeof(TcHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t);
  Part = __builtin_bswap16(Part);
  memcpy(&((uint8_t*)p)[o], &Part, sizeof(CrPsPart_t));
}

/**
 * Get "Part" from "LptUpFirstCmd" packet.
 * \param p Pointer to the packet.
 * \param o offset in parts (PartNumber)
 * \return Value of "Part".
 */
CrPsPart_t getLptUpFirstCmdPart(void* p, uint32_t o)
{
  CrPsPart_t ret;
  o = sizeof(CrPsPart_t)*o + sizeof(TcHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t);
  memcpy(&ret, &((uint8_t*)p)[o], sizeof(CrPsPart_t));
  return __builtin_bswap16(ret);
}

/**
 * Set "Part" in "LptUpFirstCmd" packet.
 * \param p Pointer to the packet.
 * \param Part Value of "Part" to be set in packet.
 * \param o offset in parts (PartNumber)
 */
void setLptUpFirstCmdPart(void* p, CrPsPart_t Part, uint32_t o)
{
  o = sizeof(CrPsPart_t)*o + sizeof(TcHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t);
  Part = __builtin_bswap16(Part);
  memcpy(&((uint8_t*)p)[o], &Part, sizeof(CrPsPart_t));
}

/**
 * Get "Part" from "LptDownLastRep" packet.
 * \param p Pointer to the packet.
 * \param o offset in parts (PartNumber)
 * \return Value of "Part".
 */
CrPsPart_t getLptDownLastRepPart(void* p, uint32_t o)
{
  CrPsPart_t ret;
  o = sizeof(CrPsPart_t)*o + sizeof(TmHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t);
  memcpy(&ret, &((uint8_t*)p)[o], sizeof(CrPsPart_t));
  return __builtin_bswap16(ret);
}

/**
 * Set "Part" in "LptDownLastRep" packet.
 * \param p Pointer to the packet.
 * \param Part Value of "Part" to be set in packet.
 * \param o offset in parts (PartNumber)
 */
void setLptDownLastRepPart(void* p, unsigned char * Part, unsigned short length)
{
  unsigned int o;
  o = sizeof(TmHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t);
  memcpy(&((uint8_t*)p)[o], (uint8_t *)Part, length);
  return;
}

/**
 * Get "Part" from "LptDownInterRep" packet.
 * \param p Pointer to the packet.
 * \param o offset in parts (PartNumber)
 * \return Value of "Part".
 */
CrPsPart_t getLptDownInterRepPart(void* p, uint32_t o)
{
  CrPsPart_t ret;
  o = sizeof(CrPsPart_t)*o + sizeof(TmHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t);
  memcpy(&ret, &((uint8_t*)p)[o], sizeof(CrPsPart_t));
  return __builtin_bswap16(ret);
}

/**
 * Set "Part" in "LptDownInterRep" packet.
 * \param p Pointer to the packet.
 * \param Part Value of "Part" to be set in packet.
 * \param o offset in parts (PartNumber)
 */
void setLptDownInterRepPart(void* p, unsigned char * Part, unsigned short length)
{
  unsigned int o;
  o = sizeof(TmHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t);
  memcpy(&((uint8_t*)p)[o], (uint8_t *)Part, length);
  return;
}

/**
 * Get "Part" from "LptDownFirstRep" packet.
 * \param p Pointer to the packet.
 * \param o offset in parts (PartNumber)
 * \return Value of "Part".
 */
CrPsPart_t getLptDownFirstRepPart(void* p, uint32_t o)
{
  CrPsPart_t ret;
  o = sizeof(CrPsPart_t)*o + sizeof(TmHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t);
  memcpy(&ret, &((uint8_t*)p)[o], sizeof(CrPsPart_t));
  return __builtin_bswap16(ret);
}

/**
 * Set "Part" in "LptDownFirstRep" packet.
 * \param p Pointer to the packet.
 * \param Part Pointer to the Data to be set in packet.
 * \param length size of the Date within the pointer Part to be set.
 */
void setLptDownFirstRepPart(void* p, unsigned char * Part, unsigned short length)
{
  unsigned int o;
  o = sizeof(TmHeader_t) + sizeof(CrPsTid_t) + sizeof(CrPsNumberU4_t);
  memcpy(&((uint8_t*)p)[o], (uint8_t *)Part, length);
  return;
}


/*----------------------------------------------------------------------------*/

