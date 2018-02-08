/**
 * @file CrPsDpServReqVerif.h
 * @ingroup Serv1
 * @ingroup DataPool
 *
 * @brief Interface for accessing data pool items.
 *
 * @note This file was generated on 2017-10-13 12:48:17
 * @author PnP Generator
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

#ifndef CRPSDPSERVREQVERIF_H_
#define CRPSDPSERVREQVERIF_H_

#include <CrFwUserConstants.h>
#include <CrPsUserConstants.h>

/**
 * Type description
 */
typedef struct {
  /**
   * Failure code of last command which failed its Acceptance
   */
  CrPsFailCode_t failCodeAccFailed;
  /**
   * Failure code of last command which failed its Progress Check
   */
  CrPsFailCode_t failCodePrgrFailed;
  /**
   * Failure code of last command which failed its Start Check
   */
  CrPsFailCode_t failCodeStartFailed;
  /**
   * Failure code of last command which failed its Termination
   */
  CrPsFailCode_t failCodeTermFailed;
  /**
   * Destination of last command for which re-routing failed
   */
  CrPsDestSrc_t invDestRerouting; /* TODO vorher uint32_t*/
  /**
   * Number of commands which have failed their acceptance check
   */
  CrFwCounterU4_t nOfAccFailed;
  /**
   * Number of commands which have failed their Progress Check
   */
  CrFwCounterU4_t nOfPrgrFailed;
  /**
   * Number of commands for which re-routing failed
   */
  CrFwCounterU4_t nOfReroutingFailed;
  /**
   * Number of commands which have failed their Start Check since
   */
  CrFwCounterU4_t nOfStartFailed;
  /**
   * Number of commands which have failed their Termination
   */
  CrFwCounterU4_t nOfTermFailed;
  /**
   * Packet identifier of last command which failed its Acceptance
   */
  CrFwTypeId_t pcktIdAccFailed;
  /**
   * Packet identifier of last command which failed its Progress
   */
  CrFwTypeId_t pcktIdPrgrFailed;
  /**
   * Packet identifier of last command for which re-routing failed
   */
  CrFwTypeId_t pcktIdReroutingFailed;
  /**
   * Packet identifier of last command which failed its Start Check
   */
  CrFwTypeId_t pcktIdStartFailed;
  /**
   * Packet identifier of last command which failed its Termination
   */
  CrFwTypeId_t pcktIdTermFailed;
  /**
   * Step identifier of last command which failed its Progress Check
   */
  CrPsStepId_t stepPrgrFailed; /* TODO vorher wars ein uint16_t */
  /**
   * Verification Failure Data (data item of fixed size but variable
   */
  CrPsFailData_t verFailData;
} DpServReqVerifVars_t;

extern DpServReqVerifVars_t dpServReqVerifVars;

/**
 * Initialises ServReqVerif
 */
void initDpServReqVerif(void);

/**
 * Gets the value of the datapool item failCodeAccFailed
 * \return The value of datapool item failCodeAccFailed
 */
static inline CrPsFailCode_t getDpfailCodeAccFailed()
{
  return dpServReqVerifVars.failCodeAccFailed;
}

/**
 * Sets the value of the datapool item failCodeAccFailed
 * \param failCodeAccFailed The value to be stored into the datapool item
 * failCodeAccFailed.
 */
static inline void setDpfailCodeAccFailed(CrPsFailCode_t failCodeAccFailed)
{
  dpServReqVerifVars.failCodeAccFailed = failCodeAccFailed;
}

/**
 * Gets the value of the datapool item failCodePrgrFailed
 * \return The value of datapool item failCodePrgrFailed
 */
static inline CrPsFailCode_t getDpfailCodePrgrFailed()
{
  return dpServReqVerifVars.failCodePrgrFailed;
}

/**
 * Sets the value of the datapool item failCodePrgrFailed
 * \param failCodePrgrFailed The value to be stored into the datapool item
 * failCodePrgrFailed.
 */
static inline void setDpfailCodePrgrFailed(CrPsFailCode_t failCodePrgrFailed)
{
  dpServReqVerifVars.failCodePrgrFailed = failCodePrgrFailed;
}

/**
 * Gets the value of the datapool item failCodeStartFailed
 * \return The value of datapool item failCodeStartFailed
 */
static inline CrPsFailCode_t getDpfailCodeStartFailed()
{
  return dpServReqVerifVars.failCodeStartFailed;
}

/**
 * Sets the value of the datapool item failCodeStartFailed
 * \param failCodeStartFailed The value to be stored into the datapool item
 * failCodeStartFailed.
 */
static inline void setDpfailCodeStartFailed(CrPsFailCode_t failCodeStartFailed)
{
  dpServReqVerifVars.failCodeStartFailed = failCodeStartFailed;
}

/**
 * Gets the value of the datapool item failCodeTermFailed
 * \return The value of datapool item failCodeTermFailed
 */
static inline CrPsFailCode_t getDpfailCodeTermFailed()
{
  return dpServReqVerifVars.failCodeTermFailed;
}

/**
 * Sets the value of the datapool item failCodeTermFailed
 * \param failCodeTermFailed The value to be stored into the datapool item
 * failCodeTermFailed.
 */
static inline void setDpfailCodeTermFailed(CrPsFailCode_t failCodeTermFailed)
{
  dpServReqVerifVars.failCodeTermFailed = failCodeTermFailed;
}

/**
 * Gets the value of the datapool item invDestRerouting
 * \return The value of datapool item invDestRerouting
 */
static inline CrPsDestSrc_t getDpinvDestRerouting()
{
  return dpServReqVerifVars.invDestRerouting;
}

/**
 * Sets the value of the datapool item invDestRerouting
 * \param invDestRerouting The value to be stored into the datapool item
 * invDestRerouting.
 */
static inline void setDpinvDestRerouting(CrPsDestSrc_t invDestRerouting)
{
  dpServReqVerifVars.invDestRerouting = invDestRerouting;
}

/**
 * Gets the value of the datapool item nOfAccFailed
 * \return The value of datapool item nOfAccFailed
 */
static inline CrFwCounterU4_t getDpnOfAccFailed()
{
  return dpServReqVerifVars.nOfAccFailed;
}

/**
 * Sets the value of the datapool item nOfAccFailed
 * \param nOfAccFailed The value to be stored into the datapool item
 * nOfAccFailed.
 */
static inline void setDpnOfAccFailed(CrFwCounterU4_t nOfAccFailed)
{
  dpServReqVerifVars.nOfAccFailed = nOfAccFailed;
}

/**
 * Gets the value of the datapool item nOfPrgrFailed
 * \return The value of datapool item nOfPrgrFailed
 */
static inline CrFwCounterU4_t getDpnOfPrgrFailed()
{
  return dpServReqVerifVars.nOfPrgrFailed;
}

/**
 * Sets the value of the datapool item nOfPrgrFailed
 * \param nOfPrgrFailed The value to be stored into the datapool item
 * nOfPrgrFailed.
 */
static inline void setDpnOfPrgrFailed(CrFwCounterU4_t nOfPrgrFailed)
{
  dpServReqVerifVars.nOfPrgrFailed = nOfPrgrFailed;
}

/**
 * Gets the value of the datapool item nOfReroutingFailed
 * \return The value of datapool item nOfReroutingFailed
 */
static inline CrFwCounterU4_t getDpnOfReroutingFailed()
{
  return dpServReqVerifVars.nOfReroutingFailed;
}

/**
 * Sets the value of the datapool item nOfReroutingFailed
 * \param nOfReroutingFailed The value to be stored into the datapool item
 * nOfReroutingFailed.
 */
static inline void setDpnOfReroutingFailed(CrFwCounterU4_t nOfReroutingFailed)
{
  dpServReqVerifVars.nOfReroutingFailed = nOfReroutingFailed;
}

/**
 * Gets the value of the datapool item nOfStartFailed
 * \return The value of datapool item nOfStartFailed
 */
static inline CrFwCounterU4_t getDpnOfStartFailed()
{
  return dpServReqVerifVars.nOfStartFailed;
}

/**
 * Sets the value of the datapool item nOfStartFailed
 * \param nOfStartFailed The value to be stored into the datapool item
 * nOfStartFailed.
 */
static inline void setDpnOfStartFailed(CrFwCounterU4_t nOfStartFailed)
{
  dpServReqVerifVars.nOfStartFailed = nOfStartFailed;
}

/**
 * Gets the value of the datapool item nOfTermFailed
 * \return The value of datapool item nOfTermFailed
 */
static inline CrFwCounterU4_t getDpnOfTermFailed()
{
  return dpServReqVerifVars.nOfTermFailed;
}

/**
 * Sets the value of the datapool item nOfTermFailed
 * \param nOfTermFailed The value to be stored into the datapool item
 * nOfTermFailed.
 */
static inline void setDpnOfTermFailed(CrFwCounterU4_t nOfTermFailed)
{
  dpServReqVerifVars.nOfTermFailed = nOfTermFailed;
}

/**
 * Gets the value of the datapool item pcktIdAccFailed
 * \return The value of datapool item pcktIdAccFailed
 */
static inline CrFwTypeId_t getDppcktIdAccFailed()
{
  return dpServReqVerifVars.pcktIdAccFailed;
}

/**
 * Sets the value of the datapool item pcktIdAccFailed
 * \param pcktIdAccFailed The value to be stored into the datapool item
 * pcktIdAccFailed.
 */
static inline void setDppcktIdAccFailed(CrFwTypeId_t pcktIdAccFailed)
{
  dpServReqVerifVars.pcktIdAccFailed = pcktIdAccFailed;
}

/**
 * Gets the value of the datapool item pcktIdPrgrFailed
 * \return The value of datapool item pcktIdPrgrFailed
 */
static inline CrFwTypeId_t getDppcktIdPrgrFailed()
{
  return dpServReqVerifVars.pcktIdPrgrFailed;
}

/**
 * Sets the value of the datapool item pcktIdPrgrFailed
 * \param pcktIdPrgrFailed The value to be stored into the datapool item
 * pcktIdPrgrFailed.
 */
static inline void setDppcktIdPrgrFailed(CrFwTypeId_t pcktIdPrgrFailed)
{
  dpServReqVerifVars.pcktIdPrgrFailed = pcktIdPrgrFailed;
}

/**
 * Gets the value of the datapool item pcktIdReroutingFailed
 * \return The value of datapool item pcktIdReroutingFailed
 */
static inline CrFwTypeId_t getDppcktIdReroutingFailed()
{
  return dpServReqVerifVars.pcktIdReroutingFailed;
}

/**
 * Sets the value of the datapool item pcktIdReroutingFailed
 * \param pcktIdReroutingFailed The value to be stored into the datapool item
 * pcktIdReroutingFailed.
 */
static inline void setDppcktIdReroutingFailed(CrFwTypeId_t pcktIdReroutingFailed)
{
  dpServReqVerifVars.pcktIdReroutingFailed = pcktIdReroutingFailed;
}

/**
 * Gets the value of the datapool item pcktIdStartFailed
 * \return The value of datapool item pcktIdStartFailed
 */
static inline CrFwTypeId_t getDppcktIdStartFailed()
{
  return dpServReqVerifVars.pcktIdStartFailed;
}

/**
 * Sets the value of the datapool item pcktIdStartFailed
 * \param pcktIdStartFailed The value to be stored into the datapool item
 * pcktIdStartFailed.
 */
static inline void setDppcktIdStartFailed(CrFwTypeId_t pcktIdStartFailed)
{
  dpServReqVerifVars.pcktIdStartFailed = pcktIdStartFailed;
}

/**
 * Gets the value of the datapool item pcktIdTermFailed
 * \return The value of datapool item pcktIdTermFailed
 */
static inline CrFwTypeId_t getDppcktIdTermFailed()
{
  return dpServReqVerifVars.pcktIdTermFailed;
}

/**
 * Sets the value of the datapool item pcktIdTermFailed
 * \param pcktIdTermFailed The value to be stored into the datapool item
 * pcktIdTermFailed.
 */
static inline void setDppcktIdTermFailed(CrFwTypeId_t pcktIdTermFailed)
{
  dpServReqVerifVars.pcktIdTermFailed = pcktIdTermFailed;
}

/**
 * Gets the value of the datapool item stepPrgrFailed
 * \return The value of datapool item stepPrgrFailed
 */
static inline CrPsStepId_t getDpstepPrgrFailed()
{
  return dpServReqVerifVars.stepPrgrFailed;
}

/**
 * Sets the value of the datapool item stepPrgrFailed
 * \param stepPrgrFailed The value to be stored into the datapool item
 * stepPrgrFailed.
 */
static inline void setDpstepPrgrFailed(CrPsStepId_t stepPrgrFailed)
{
  dpServReqVerifVars.stepPrgrFailed = stepPrgrFailed;
}

/**
 * Gets the value of the datapool item verFailData
 * \return The value of datapool item verFailData
 */
static inline CrPsFailData_t getDpverFailData()
{
  return dpServReqVerifVars.verFailData;
}

/**
 * Sets the value of the datapool item verFailData
 * \param verFailData The value to be stored into the datapool item
 * verFailData.
 */
static inline void setDpverFailData(CrPsFailData_t verFailData)
{
  dpServReqVerifVars.verFailData = verFailData;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSDPSERVREQVERIF_H */
