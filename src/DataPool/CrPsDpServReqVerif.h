/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-10-13 12:48:17
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSDPSERVREQVERIF_H_
#define CRPSDPSERVREQVERIF_H_

#include "CrPsDpTypes.h"
#include <stdio.h>
/**
 * Type description
 */
typedef struct {
  /**
   * Failure code of last command which failed its Acceptance
   */
  uint16_t failCodeAccFailed;
  /**
   * Failure code of last command which failed its Progress Check
   */
  uint16_t failCodePrgrFailed;
  /**
   * Failure code of last command which failed its Start Check
   */
  uint16_t failCodeStartFailed;
  /**
   * Failure code of last command which failed its Termination
   */
  uint16_t failCodeTermFailed;
  /**
   * Destination of last command for which re-routing failed
   */
  uint32_t invDestRerouting;
  /**
   * Number of commands which have failed their acceptance check
   */
  uint32_t nOfAccFailed;
  /**
   * Number of commands which have failed their Progress Check
   */
  uint32_t nOfPrgrFailed;
  /**
   * Number of commands for which re-routing failed
   */
  uint32_t nOfReroutingFailed;
  /**
   * Number of commands which have failed their Start Check since
   */
  uint32_t nOfStartFailed;
  /**
   * Number of commands which have failed their Termination
   */
  uint32_t nOfTermFailed;
  /**
   * Packet identifier of last command which failed its Acceptance
   */
  uint16_t pcktIdAccFailed;
  /**
   * Packet identifier of last command which failed its Progress
   */
  uint16_t pcktIdPrgrFailed;
  /**
   * Packet identifier of last command for which re-routing failed
   */
  uint16_t pcktIdReroutingFailed;
  /**
   * Packet identifier of last command which failed its Start Check
   */
  uint16_t pcktIdStartFailed;
  /**
   * Packet identifier of last command which failed its Termination
   */
  uint16_t pcktIdTermFailed;
  /**
   * Step identifier of last command which failed its Progress Check
   */
  uint16_t stepPrgrFailed;
  /**
   * Verification Failure Data (data item of fixed size but variable
   */
  uint32_t verFailData;
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
static inline uint16_t getDpfailCodeAccFailed()
{
  return dpServReqVerifVars.failCodeAccFailed;
}

/**
 * Sets the value of the datapool item failCodeAccFailed
 * \param failCodeAccFailed The value to be stored into the datapool item
 * failCodeAccFailed.
 */
static inline void setDpfailCodeAccFailed(uint16_t failCodeAccFailed)
{
  dpServReqVerifVars.failCodeAccFailed = failCodeAccFailed;
}

/**
 * Gets the value of the datapool item failCodePrgrFailed
 * \return The value of datapool item failCodePrgrFailed
 */
static inline uint16_t getDpfailCodePrgrFailed()
{
  return dpServReqVerifVars.failCodePrgrFailed;
}

/**
 * Sets the value of the datapool item failCodePrgrFailed
 * \param failCodePrgrFailed The value to be stored into the datapool item
 * failCodePrgrFailed.
 */
static inline void setDpfailCodePrgrFailed(uint16_t failCodePrgrFailed)
{
  dpServReqVerifVars.failCodePrgrFailed = failCodePrgrFailed;
}

/**
 * Gets the value of the datapool item failCodeStartFailed
 * \return The value of datapool item failCodeStartFailed
 */
static inline uint16_t getDpfailCodeStartFailed()
{
  return dpServReqVerifVars.failCodeStartFailed;
}

/**
 * Sets the value of the datapool item failCodeStartFailed
 * \param failCodeStartFailed The value to be stored into the datapool item
 * failCodeStartFailed.
 */
static inline void setDpfailCodeStartFailed(uint16_t failCodeStartFailed)
{
  dpServReqVerifVars.failCodeStartFailed = failCodeStartFailed;
}

/**
 * Gets the value of the datapool item failCodeTermFailed
 * \return The value of datapool item failCodeTermFailed
 */
static inline uint16_t getDpfailCodeTermFailed()
{
  return dpServReqVerifVars.failCodeTermFailed;
}

/**
 * Sets the value of the datapool item failCodeTermFailed
 * \param failCodeTermFailed The value to be stored into the datapool item
 * failCodeTermFailed.
 */
static inline void setDpfailCodeTermFailed(uint16_t failCodeTermFailed)
{
  dpServReqVerifVars.failCodeTermFailed = failCodeTermFailed;
}

/**
 * Gets the value of the datapool item invDestRerouting
 * \return The value of datapool item invDestRerouting
 */
static inline uint32_t getDpinvDestRerouting()
{
  return dpServReqVerifVars.invDestRerouting;
}

/**
 * Sets the value of the datapool item invDestRerouting
 * \param invDestRerouting The value to be stored into the datapool item
 * invDestRerouting.
 */
static inline void setDpinvDestRerouting(uint32_t invDestRerouting)
{
  dpServReqVerifVars.invDestRerouting = invDestRerouting;
}

/**
 * Gets the value of the datapool item nOfAccFailed
 * \return The value of datapool item nOfAccFailed
 */
static inline uint32_t getDpnOfAccFailed()
{
  return dpServReqVerifVars.nOfAccFailed;
}

/**
 * Sets the value of the datapool item nOfAccFailed
 * \param nOfAccFailed The value to be stored into the datapool item
 * nOfAccFailed.
 */
static inline void setDpnOfAccFailed(uint32_t nOfAccFailed)
{
  dpServReqVerifVars.nOfAccFailed = nOfAccFailed;
}

/**
 * Gets the value of the datapool item nOfPrgrFailed
 * \return The value of datapool item nOfPrgrFailed
 */
static inline uint32_t getDpnOfPrgrFailed()
{
  return dpServReqVerifVars.nOfPrgrFailed;
}

/**
 * Sets the value of the datapool item nOfPrgrFailed
 * \param nOfPrgrFailed The value to be stored into the datapool item
 * nOfPrgrFailed.
 */
static inline void setDpnOfPrgrFailed(uint32_t nOfPrgrFailed)
{
  dpServReqVerifVars.nOfPrgrFailed = nOfPrgrFailed;
}

/**
 * Gets the value of the datapool item nOfReroutingFailed
 * \return The value of datapool item nOfReroutingFailed
 */
static inline uint32_t getDpnOfReroutingFailed()
{
  return dpServReqVerifVars.nOfReroutingFailed;
}

/**
 * Sets the value of the datapool item nOfReroutingFailed
 * \param nOfReroutingFailed The value to be stored into the datapool item
 * nOfReroutingFailed.
 */
static inline void setDpnOfReroutingFailed(uint32_t nOfReroutingFailed)
{
  dpServReqVerifVars.nOfReroutingFailed = nOfReroutingFailed;
}

/**
 * Gets the value of the datapool item nOfStartFailed
 * \return The value of datapool item nOfStartFailed
 */
static inline uint32_t getDpnOfStartFailed()
{
  return dpServReqVerifVars.nOfStartFailed;
}

/**
 * Sets the value of the datapool item nOfStartFailed
 * \param nOfStartFailed The value to be stored into the datapool item
 * nOfStartFailed.
 */
static inline void setDpnOfStartFailed(uint32_t nOfStartFailed)
{
  dpServReqVerifVars.nOfStartFailed = nOfStartFailed;
}

/**
 * Gets the value of the datapool item nOfTermFailed
 * \return The value of datapool item nOfTermFailed
 */
static inline uint32_t getDpnOfTermFailed()
{
  return dpServReqVerifVars.nOfTermFailed;
}

/**
 * Sets the value of the datapool item nOfTermFailed
 * \param nOfTermFailed The value to be stored into the datapool item
 * nOfTermFailed.
 */
static inline void setDpnOfTermFailed(uint32_t nOfTermFailed)
{
  dpServReqVerifVars.nOfTermFailed = nOfTermFailed;
}

/**
 * Gets the value of the datapool item pcktIdAccFailed
 * \return The value of datapool item pcktIdAccFailed
 */
static inline uint16_t getDppcktIdAccFailed()
{
  return dpServReqVerifVars.pcktIdAccFailed;
}

/**
 * Sets the value of the datapool item pcktIdAccFailed
 * \param pcktIdAccFailed The value to be stored into the datapool item
 * pcktIdAccFailed.
 */
static inline void setDppcktIdAccFailed(uint16_t pcktIdAccFailed)
{
  dpServReqVerifVars.pcktIdAccFailed = pcktIdAccFailed;
}

/**
 * Gets the value of the datapool item pcktIdPrgrFailed
 * \return The value of datapool item pcktIdPrgrFailed
 */
static inline uint16_t getDppcktIdPrgrFailed()
{
  return dpServReqVerifVars.pcktIdPrgrFailed;
}

/**
 * Sets the value of the datapool item pcktIdPrgrFailed
 * \param pcktIdPrgrFailed The value to be stored into the datapool item
 * pcktIdPrgrFailed.
 */
static inline void setDppcktIdPrgrFailed(uint16_t pcktIdPrgrFailed)
{
  dpServReqVerifVars.pcktIdPrgrFailed = pcktIdPrgrFailed;
}

/**
 * Gets the value of the datapool item pcktIdReroutingFailed
 * \return The value of datapool item pcktIdReroutingFailed
 */
static inline uint16_t getDppcktIdReroutingFailed()
{
  return dpServReqVerifVars.pcktIdReroutingFailed;
}

/**
 * Sets the value of the datapool item pcktIdReroutingFailed
 * \param pcktIdReroutingFailed The value to be stored into the datapool item
 * pcktIdReroutingFailed.
 */
static inline void setDppcktIdReroutingFailed(uint16_t pcktIdReroutingFailed)
{
  dpServReqVerifVars.pcktIdReroutingFailed = pcktIdReroutingFailed;
}

/**
 * Gets the value of the datapool item pcktIdStartFailed
 * \return The value of datapool item pcktIdStartFailed
 */
static inline uint16_t getDppcktIdStartFailed()
{
  return dpServReqVerifVars.pcktIdStartFailed;
}

/**
 * Sets the value of the datapool item pcktIdStartFailed
 * \param pcktIdStartFailed The value to be stored into the datapool item
 * pcktIdStartFailed.
 */
static inline void setDppcktIdStartFailed(uint16_t pcktIdStartFailed)
{
  dpServReqVerifVars.pcktIdStartFailed = pcktIdStartFailed;
}

/**
 * Gets the value of the datapool item pcktIdTermFailed
 * \return The value of datapool item pcktIdTermFailed
 */
static inline uint16_t getDppcktIdTermFailed()
{
  return dpServReqVerifVars.pcktIdTermFailed;
}

/**
 * Sets the value of the datapool item pcktIdTermFailed
 * \param pcktIdTermFailed The value to be stored into the datapool item
 * pcktIdTermFailed.
 */
static inline void setDppcktIdTermFailed(uint16_t pcktIdTermFailed)
{
  dpServReqVerifVars.pcktIdTermFailed = pcktIdTermFailed;
}

/**
 * Gets the value of the datapool item stepPrgrFailed
 * \return The value of datapool item stepPrgrFailed
 */
static inline uint16_t getDpstepPrgrFailed()
{
  return dpServReqVerifVars.stepPrgrFailed;
}

/**
 * Sets the value of the datapool item stepPrgrFailed
 * \param stepPrgrFailed The value to be stored into the datapool item
 * stepPrgrFailed.
 */
static inline void setDpstepPrgrFailed(uint16_t stepPrgrFailed)
{
  dpServReqVerifVars.stepPrgrFailed = stepPrgrFailed;
}

/**
 * Gets the value of the datapool item verFailData
 * \return The value of datapool item verFailData
 */
static inline uint32_t getDpverFailData()
{
  return dpServReqVerifVars.verFailData;
}

/**
 * Sets the value of the datapool item verFailData
 * \param verFailData The value to be stored into the datapool item
 * verFailData.
 */
static inline void setDpverFailData(uint32_t verFailData)
{
  dpServReqVerifVars.verFailData = verFailData;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSDPSERVREQVERIF_H */
