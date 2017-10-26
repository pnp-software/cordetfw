/**
 * \file CrPSPktServTest.h
 *
 * Interface for accessing fields in packets of service "ServTest".
 *
 * \note This file was generated on 2017-10-13 12:48:17
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSPKTSERVTEST_H_
#define CRPSPKTSERVTEST_H_

#include "CrPsDpTypes.h"
#include "CrPsUserConstants.h"
#include "CrPsPkt.h"

/**
 * Structure for AreYouAliveCmd
 */
typedef struct __attribute__((packed)) _AreYouAliveCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

} AreYouAliveCmd_t ;

/**
 * Structure for AreYouAliveRep
 */
typedef struct __attribute__((packed)) _AreYouAliveRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

} AreYouAliveRep_t ;

/**
 * Structure for OnBoardConnectCmd
 */
typedef struct __attribute__((packed)) _OnBoardConnectCmd_t {
  /**
   * Packet header.
   */
  TcHeader_t Header;

  /**
   * Application ID
   */
  CrPsApid_t AppId;
  
} OnBoardConnectCmd_t ;

/**
 * Structure for OnBoardConnectRep
 */
typedef struct __attribute__((packed)) _OnBoardConnectRep_t {
  /**
   * Packet header.
   */
  TmHeader_t Header;

  /**
   * Destination for 17.3
   */
  CrPsDestSrc_t Dest;
  
} OnBoardConnectRep_t ;

/**
 * Get "AppId" from "OnBoardConnectCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "AppId".
 */
static inline uint16_t getOnBoardConnectCmdAppId(void* p)
{
  OnBoardConnectCmd_t* t;
  t = (OnBoardConnectCmd_t*)p;
  return __builtin_bswap16(t->AppId);
}

/**
 * Set "AppId" in "OnBoardConnectCmd" packet.
 * \param p Pointer to the packet.
 * \param AppId Value of "AppId" to be set in packet.
 */
static inline void setOnBoardConnectCmdAppId(void* p, uint16_t AppId)
{
  OnBoardConnectCmd_t* t;
  t = (OnBoardConnectCmd_t*)p;
  t->AppId = __builtin_bswap16(AppId);
}

/**
 * Get "Dest" from "OnBoardConnectRep" packet.
 * \param p Pointer to the packet.
 * \return Value of "Dest".
 */
static inline uint16_t getOnBoardConnectRepDest(void* p)
{
  OnBoardConnectRep_t* t;
  t = (OnBoardConnectRep_t*)p;
  return __builtin_bswap16(t->Dest);
}

/**
 * Set "Dest" in "OnBoardConnectRep" packet.
 * \param p Pointer to the packet.
 * \param Dest Value of "Dest" to be set in packet.
 */
static inline void setOnBoardConnectRepDest(void* p, uint16_t Dest)
{
  OnBoardConnectRep_t* t;
  t = (OnBoardConnectRep_t*)p;
  t->Dest = __builtin_bswap16(Dest);
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSPKTSERVTEST_H */
