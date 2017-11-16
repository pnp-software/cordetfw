/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-10-13 12:48:17
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSDPSERVTEST_H_
#define CRPSDPSERVTEST_H_

#include <CrFwUserConstants.h>
#include <CrPsUserConstants.h>
#include <CrPsDpTypes.h>

/**
 * Type description
 */
typedef struct {
  /**
   * Time-out for the Are-You-Alive Test initiated in response to an
   * Is-Application-Process-Alive Test
   */
  CrPsTimeOut_t AreYouAliveTimeOut;
  /**
   * List of identifiers of target applications for an On-Board-Connection
   * Test
   */
  CrPsDestSrc_t OnBoardConnectDestLst[TEST_MAX_APP];
} DpServTestParams_t;

/**
 * Type description
 */
typedef struct {
  /**
   * Source of the latest (17,2) report received in response to a (17,1)
   * command triggered by a (17,3) command
   */
  CrPsDestSrc_t AreYouAliveSrc;
  /**
   * Destination of the (17,1) triggered by a (17,3) command
   */
  CrPsDestSrc_t OnBoardConnectDest;
} DpServTestVars_t;

extern DpServTestParams_t dpServTestParams;
extern DpServTestVars_t dpServTestVars;

/**
 * Initialises ServTest
 */
void initDpServTest(void);

/**
 * Gets the value of the datapool item AreYouAliveTimeOut
 * \return The value of datapool item AreYouAliveTimeOut
 */
static inline CrPsTimeOut_t getDpAreYouAliveTimeOut()
{
  return dpServTestParams.AreYouAliveTimeOut;
}

/**
 * Sets the value of the datapool item AreYouAliveTimeOut
 * \param AreYouAliveTimeOut The value to be stored into the datapool item
 * AreYouAliveTimeOut.
 */
static inline void setDpAreYouAliveTimeOut(CrPsTimeOut_t AreYouAliveTimeOut)
{
  dpServTestParams.AreYouAliveTimeOut = AreYouAliveTimeOut;
}

/**
 * Gets the datapool array OnBoardConnectDestLst
 * \return The datapool array OnBoardConnectDestLst
 */
static inline CrPsDestSrc_t* getDpOnBoardConnectDestLstArray()
{
  return &dpServTestParams.OnBoardConnectDestLst[0];
}

/**
 * Gets the value of the i-th element in the datapool array
 * OnBoardConnectDestLst
 * \param i Index variable
 * \return The i-th element in the datapool array OnBoardConnectDestLst
 */
static inline CrPsDestSrc_t getDpOnBoardConnectDestLstItem(int i)
{
  return dpServTestParams.OnBoardConnectDestLst[i];
}

/**
 * Sets the value of the i-th element in the datapool array
 * OnBoardConnectDestLst
 * \param i Index variable
 * \param OnBoardConnectDestLst The value to be stored into the i-th element
 * of datapool array OnBoardConnectDestLst.
 */
static inline void setDpOnBoardConnectDestLstItem(int i, CrPsDestSrc_t OnBoardConnectDestLst)
{
  dpServTestParams.OnBoardConnectDestLst[i] = OnBoardConnectDestLst;
}

/**
 * Gets the value of the datapool item AreYouAliveSrc
 * \return The value of datapool item AreYouAliveSrc
 */
static inline CrPsDestSrc_t getDpAreYouAliveSrc()
{
  return dpServTestVars.AreYouAliveSrc;
}

/**
 * Sets the value of the datapool item AreYouAliveSrc
 * \param AreYouAliveSrc The value to be stored into the datapool item
 * AreYouAliveSrc.
 */
static inline void setDpAreYouAliveSrc(CrPsDestSrc_t AreYouAliveSrc)
{
  dpServTestVars.AreYouAliveSrc = AreYouAliveSrc;
}

/**
 * Gets the value of the datapool item OnBoardConnectDest
 * \return The value of datapool item OnBoardConnectDest
 */
static inline CrPsDestSrc_t getDpOnBoardConnectDest()
{
  return dpServTestVars.OnBoardConnectDest;
}

/**
 * Sets the value of the datapool item OnBoardConnectDest
 * \param OnBoardConnectDest The value to be stored into the datapool item
 * OnBoardConnectDest.
 */
static inline void setDpOnBoardConnectDest(CrPsDestSrc_t OnBoardConnectDest)
{
  dpServTestVars.OnBoardConnectDest = OnBoardConnectDest;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSDPSERVTEST_H */
