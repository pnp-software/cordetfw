/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-08-22 17:43:36
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSDPPKTSERVTEST_H_
#define CRPSDPPKTSERVTEST_H_

#include <Services/General/CrPsConstants.h>
 
/**
 * Structure for packet AreYouAliveCmd - 0
 */
typedef struct __attribute__((packed, aligned(4))) _AreYouAliveCmd0_t {
  /**
   * Header spacer.
   */
  uint8_t __header[OFFSET_PAR_LENGTH_IN_CMD_PCKT];

  /**
   * Discriminant
   */
  uint16_t Discriminant;
  
} AreYouAliveCmd0_t;

/**
 * Structure for packet AreYouAliveRep - 0
 */
typedef struct __attribute__((packed, aligned(4))) _AreYouAliveRep0_t {
  /**
   * Header spacer.
   */
  uint8_t __header[OFFSET_PAR_LENGTH_OUT_REP_PCKT];

  /**
   * Discriminant
   */
  uint16_t Discriminant;
  
} AreYouAliveRep0_t;

/**
 * Structure for packet OnBoardConnectCmd - 0
 */
typedef struct __attribute__((packed, aligned(4))) _OnBoardConnectCmd0_t {
  /**
   * Header spacer.
   */
  uint8_t __header[OFFSET_PAR_LENGTH_IN_CMD_PCKT];

  /**
   * Discriminant
   */
  uint16_t Discriminant;
  
  /**
   * Application ID
   */
  uint16_t AppId;
  
  /**
   * Destination for 17.3
   */
  uint16_t Dest;
  
} OnBoardConnectCmd0_t;

/**
 * Structure for packet OnBoardConnectRep - 0
 */
typedef struct __attribute__((packed, aligned(4))) _OnBoardConnectRep0_t {
  /**
   * Header spacer.
   */
  uint8_t __header[OFFSET_PAR_LENGTH_OUT_REP_PCKT];

  /**
   * Discriminant
   */
  uint16_t Discriminant;
  
  /**
   * Application ID
   */
  uint16_t AppId;
  
  /**
   * Destination for 17.3
   */
  uint16_t Dest;
  
} OnBoardConnectRep0_t;

/**
 * Get "Discriminant" from "AreYouAliveCmd - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "Discriminant".
 */
static inline uint16_t getAreYouAliveCmd0Discriminant(void* p)
{
  AreYouAliveCmd0_t* t;
  t = (AreYouAliveCmd0_t*)p;
  return t->Discriminant;
}

/**
 * Set "Discriminant" in "AreYouAliveCmd - 0" packet.
 * \param p Pointer to the packet.
 * \param Discriminant Value of "Discriminant" to be set in packet.
 */
static inline void setAreYouAliveCmd0Discriminant(void* p, uint16_t Discriminant)
{
  AreYouAliveCmd0_t* t;
  t = (AreYouAliveCmd0_t*)p;
  t->Discriminant = Discriminant;
}

/**
 * Get "Discriminant" from "AreYouAliveRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "Discriminant".
 */
static inline uint16_t getAreYouAliveRep0Discriminant(void* p)
{
  AreYouAliveRep0_t* t;
  t = (AreYouAliveRep0_t*)p;
  return t->Discriminant;
}

/**
 * Set "Discriminant" in "AreYouAliveRep - 0" packet.
 * \param p Pointer to the packet.
 * \param Discriminant Value of "Discriminant" to be set in packet.
 */
static inline void setAreYouAliveRep0Discriminant(void* p, uint16_t Discriminant)
{
  AreYouAliveRep0_t* t;
  t = (AreYouAliveRep0_t*)p;
  t->Discriminant = Discriminant;
}

/**
 * Get "Discriminant" from "OnBoardConnectCmd - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "Discriminant".
 */
static inline uint16_t getOnBoardConnectCmd0Discriminant(void* p)
{
  OnBoardConnectCmd0_t* t;
  t = (OnBoardConnectCmd0_t*)p;
  return t->Discriminant;
}

/**
 * Set "Discriminant" in "OnBoardConnectCmd - 0" packet.
 * \param p Pointer to the packet.
 * \param Discriminant Value of "Discriminant" to be set in packet.
 */
static inline void setOnBoardConnectCmd0Discriminant(void* p, uint16_t Discriminant)
{
  OnBoardConnectCmd0_t* t;
  t = (OnBoardConnectCmd0_t*)p;
  t->Discriminant = Discriminant;
}

/**
 * Get "AppId" from "OnBoardConnectCmd - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "AppId".
 */
static inline uint16_t getOnBoardConnectCmd0AppId(void* p)
{
  OnBoardConnectCmd0_t* t;
  t = (OnBoardConnectCmd0_t*)p;
  return t->AppId;
}

/**
 * Set "AppId" in "OnBoardConnectCmd - 0" packet.
 * \param p Pointer to the packet.
 * \param AppId Value of "AppId" to be set in packet.
 */
static inline void setOnBoardConnectCmd0AppId(void* p, uint16_t AppId)
{
  OnBoardConnectCmd0_t* t;
  t = (OnBoardConnectCmd0_t*)p;
  t->AppId = AppId;
}

/**
 * Get "Dest" from "OnBoardConnectCmd - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "Dest".
 */
static inline uint16_t getOnBoardConnectCmd0Dest(void* p)
{
  OnBoardConnectCmd0_t* t;
  t = (OnBoardConnectCmd0_t*)p;
  return t->Dest;
}

/**
 * Set "Dest" in "OnBoardConnectCmd - 0" packet.
 * \param p Pointer to the packet.
 * \param Dest Value of "Dest" to be set in packet.
 */
static inline void setOnBoardConnectCmd0Dest(void* p, uint16_t Dest)
{
  OnBoardConnectCmd0_t* t;
  t = (OnBoardConnectCmd0_t*)p;
  t->Dest = Dest;
}

/**
 * Get "Discriminant" from "OnBoardConnectRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "Discriminant".
 */
static inline uint16_t getOnBoardConnectRep0Discriminant(void* p)
{
  OnBoardConnectRep0_t* t;
  t = (OnBoardConnectRep0_t*)p;
  return t->Discriminant;
}

/**
 * Set "Discriminant" in "OnBoardConnectRep - 0" packet.
 * \param p Pointer to the packet.
 * \param Discriminant Value of "Discriminant" to be set in packet.
 */
static inline void setOnBoardConnectRep0Discriminant(void* p, uint16_t Discriminant)
{
  OnBoardConnectRep0_t* t;
  t = (OnBoardConnectRep0_t*)p;
  t->Discriminant = Discriminant;
}

/**
 * Get "AppId" from "OnBoardConnectRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "AppId".
 */
static inline uint16_t getOnBoardConnectRep0AppId(void* p)
{
  OnBoardConnectRep0_t* t;
  t = (OnBoardConnectRep0_t*)p;
  return t->AppId;
}

/**
 * Set "AppId" in "OnBoardConnectRep - 0" packet.
 * \param p Pointer to the packet.
 * \param AppId Value of "AppId" to be set in packet.
 */
static inline void setOnBoardConnectRep0AppId(void* p, uint16_t AppId)
{
  OnBoardConnectRep0_t* t;
  t = (OnBoardConnectRep0_t*)p;
  t->AppId = AppId;
}

/**
 * Get "Dest" from "OnBoardConnectRep - 0" packet.
 * \param p Pointer to the packet.
 * \return Value of "Dest".
 */
static inline uint16_t getOnBoardConnectRep0Dest(void* p)
{
  OnBoardConnectRep0_t* t;
  t = (OnBoardConnectRep0_t*)p;
  return t->Dest;
}

/**
 * Set "Dest" in "OnBoardConnectRep - 0" packet.
 * \param p Pointer to the packet.
 * \param Dest Value of "Dest" to be set in packet.
 */
static inline void setOnBoardConnectRep0Dest(void* p, uint16_t Dest)
{
  OnBoardConnectRep0_t* t;
  t = (OnBoardConnectRep0_t*)p;
  t->Dest = Dest;
}

#endif /* CRPSDPPKTSERVTEST_H */
