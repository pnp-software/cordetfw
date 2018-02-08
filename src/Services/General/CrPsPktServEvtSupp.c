/**
 * @file CrPsPktServEvtSupp.c
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

#include <Services/General/CrPsPktServEvtSupp.h>
#include <Services/General/CrPsPktServEvt.h>
#include <Pckt/CrFwPckt.h>
#include <CrPsPkt.h>
#include <CrPsUserConstants.h>
#include <DataPool/CrPsDpServEvt.h>
#include <DataPool/CrPsDp.h>

/**
 * Get "EventId" arrayItem from "EvtEnableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of EventIdArray Item.
 * \return EventId Array Item Value.
 */
CrPsEid_t getEvtEnableCmdEventIdItem(void* p, CrPsNumberU4_t N)
{
  CrPsEid_t ret;
  uint32_t pos;

  if(N>0)
    {
      N=N-1;
    }
  pos = sizeof(TcHeader_t)+sizeof(CrPsNumberU4_t)+(sizeof(CrPsEid_t)*N);
  memcpy(&ret, &((uint8_t*)p)[pos], sizeof(CrPsEid_t));
  return __builtin_bswap16(ret);
}

/**
 * Set "EventId" arrayItem in "EvtEnableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of the "N" th EventIdArray Item.
 * \param src Variable from where arrayItem data are copied.
 */
void setEvtEnableCmdEventIdItem(void* p, CrPsNumberU4_t N, CrPsEid_t src)
{
  uint32_t pos;

  if(N>0)
    {
      N=N-1;
    }
  pos = sizeof(TcHeader_t)+sizeof(CrPsNumberU4_t)+(sizeof(CrPsEid_t)*N);
  src = __builtin_bswap16(src);
  memcpy(&((uint8_t*)p)[pos], &src, sizeof(CrPsEid_t));
}

/**
 * Get "EventId" arrayItem from "EvtDisableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of EventIdArray Item.
 * \return EventId Array Item Value.
 */
CrPsEid_t getEvtDisableCmdEventIdItem(void* p, CrPsNumberU4_t N)
{
  CrPsEid_t ret;
  uint32_t pos;

  if(N>0)
    {
      N=N-1;
    }
  pos = sizeof(TcHeader_t)+sizeof(CrPsNumberU4_t)+(sizeof(CrPsEid_t)*N);
  memcpy(&ret, &((uint8_t*)p)[pos], sizeof(CrPsEid_t));
  return __builtin_bswap16(ret);
}

/**
 * Set "EventId" arrayItem in "EvtDisableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of the "N" th EventIdArray Item.
 * \param src Variable from where arrayItem data are copied.
 */
void setEvtDisableCmdEventIdItem(void* p, CrPsNumberU4_t N, CrPsEid_t src)
{
  uint32_t pos;

  if(N>0)
    {
      N=N-1;
    }
  pos = sizeof(TcHeader_t)+sizeof(CrPsNumberU4_t)+(sizeof(CrPsEid_t)*N);;
  src = __builtin_bswap16(src);
  memcpy(&((uint8_t*)p)[pos], &src, sizeof(CrPsEid_t));
}

/**
 * Get "EventId" arrayItem from "EvtRepDisabledRep" packet.
 * \param p Pointer to the packet.
 * \param N Number of EventIdArray Item.
 * \return EventId Array Item Value.
 */
CrPsEid_t getEvtRepDisabledRepEventIdItem(void* p, CrPsNumberU4_t N)
{
  CrPsEid_t ret;
  uint32_t pos;

  if(N>0)
    {
      N=N-1;
    }
  pos = sizeof(TmHeader_t)+(sizeof(CrPsEid_t)*N);
  memcpy(&ret, &((uint8_t*)p)[pos], sizeof(CrPsEid_t));
  return __builtin_bswap16(ret);
}

/**
 * Set "EventId" arrayItem in "EvtRepDisabledRep" packet.
 * \param p Pointer to the packet.
 * \param N Value of the "N" th EventIdArray Item.
 * \param src Variable from where arrayItem data are copied.
 */
void setEvtRepDisabledRepEventIdItem(void* p, CrPsNumberU4_t N, CrPsEid_t src)
{
  uint32_t pos;

  if(N>0)
    {
      N=N-1;
    }
  pos = sizeof(TmHeader_t)+(sizeof(CrPsEid_t)*N);
  src = __builtin_bswap16(src);
  memcpy(&((uint8_t*)p)[pos], &src, sizeof(CrPsEid_t));
}

/**
 * Get the size of a Disabled Event Reporting packet.
 * \param none
 * \return the size of the packet in bytes.
 */
size_t getEvtRepDisabledSize()
{
  size_t       s;
  unsigned int i;
  CrPsFlag_t   isEnabled;

  /* NOTE: can also be calculated from nOfDisabledEid_x data pool entries */

  s=sizeof(TmHeader_t) + 2;

  /* Check for number of disabled EIDs */
  for (i=0; i<EVT_N_EID; i++)
    {
      isEnabled = getDpisEidEnabledItem(i);
      if (isEnabled == 0)
        {
          s += sizeof(CrPsEid_t);
        }
    }

  return s;
}


/*----------------------------------------------------------------------------*/

