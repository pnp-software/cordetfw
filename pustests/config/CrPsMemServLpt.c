/**
 * @file CrPsMemServLpt.c
 * @ingroup PUSTestsuite
 * @ingroup PUSTestconfig 
 *
 * @brief Adaptation Points for the Large Packet Transfer Service
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

/** The maximum size in number of bytes of a packet */
#define LPTSIZE 4000

/**
 * The array holding the packets.
 * Packets are stored in this array in blocks of size LPTSIZE.
 */
static char memArray[LPTSIZE];

/**
 * Getter function for the Address of the Data
 * @param LptBuffer The number ot the Large Packet Transfer Buffer 
 * @return Pointer to the memory array of the LptBuffer
 */
uint32_t* getLptMemStartAddr(uint32_t LptBuffer) /* Adaptation Point */
{
  (void)LptBuffer;

  return (uint32_t*)memArray;
}

/**
 * Getter function to return the size of the Data
 * @param LptBuffer The number ot the Large Packet Transfer Buffer 
 * @return LPTSIZE The size of the LptBuffer
 */
uint32_t getLptMemSize(uint32_t LptBuffer) /* Adaptation Point */
{
  (void)LptBuffer;

  return (uint32_t)LPTSIZE;
}
