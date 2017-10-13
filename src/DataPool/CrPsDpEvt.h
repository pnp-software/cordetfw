/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-10-03 10:29:40
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSDPEVT_H_
#define CRPSDPEVT_H_

#include "CrPsDpTypes.h"

/**
 * Type description
 */
typedef struct {
  /**
   * Array of EVT_N_EID elements holding the enable status of the event
   * identifiers
   */
  uint8_t isEidEnabled[3];
  /**
   * Event identifier of the last generated level 1 event report
   */
  uint8_t lastEvtEid_1;
  /**
   * Event identifier of the last generated level 2 event report
   */
  uint8_t lastEvtEid_2;
  /**
   * Event identifier of the last generated level 3 event report
   */
  uint8_t lastEvtEid_3;
  /**
   * Event identifier of the last generated level 4event report
   */
  uint8_t lastEvtEid_4;
  /**
   * Time when the last level 1 event report was generated
   */
  uint32_t lastEvtTime_1;
  /**
   * Time when the last level 2 event report was generated
   */
  uint32_t lastEvtTime_2;
  /**
   * Time when the last level 3 event report was generated
   */
  uint32_t lastEvtTime_3;
  /**
   * Time when the last level 4 event report was generated
   */
  uint32_t lastEvtTime_4;
  /**
   * Number of detected occurrences of level 1 events
   */
  uint8_t nOfDetectedEvts_1;
  /**
   * Number of detected occurrences of level 2 events
   */
  uint8_t nOfDetectedEvts_2;
  /**
   * Number of detected occurrences of level 3 events
   */
  uint8_t nOfDetectedEvts_3;
  /**
   * Number of detected occurrences of level 4 events
   */
  uint8_t nOfDetectedEvts_4;
  /**
   * Number of event identifiers of level 1 which are disabled
   */
  uint8_t nOfDisabledEid_1;
  /**
   * Number of event identifiers of level 2 which are disabled
   */
  uint8_t nOfDisabledEid_2;
  /**
   * Number of event identifiers of level 3 which are disabled
   */
  uint8_t nOfDisabledEid_3;
  /**
   * Number of event identifiers of level 4 which are disabled
   */
  uint8_t nOfDisabledEid_4;
  /**
   * Number of generated level 1 event reports
   */
  uint8_t nOfGenEvtRep_1;
  /**
   * Number of generated level 2 event reports
   */
  uint8_t nOfGenEvtRep_2;
  /**
   * Number of generated level 3 event reports
   */
  uint8_t nOfGenEvtRep_3;
  /**
   * Number of generated level 4 event reports
   */
  uint8_t nOfGenEvtRep_4;
} DpEvtVars_t;

extern DpEvtVars_t dpEvtVars;

/**
 * Initialises Evt
 */
void initDpEvt(void);

/**
 * Gets the datapool array isEidEnabled
 * \return The datapool array isEidEnabled
 */
static inline uint8_t* getDpisEidEnabledArray()
{
  return &dpEvtVars.isEidEnabled[0];
}

/**
 * Gets the value of the i-th element in the datapool array isEidEnabled
 * \param i Index variable
 * \return The i-th element in the datapool array isEidEnabled
 */
static inline uint8_t getDpisEidEnabledItem(int i)
{
  return dpEvtVars.isEidEnabled[i];
}

/**
 * Sets the value of the i-th element in the datapool array isEidEnabled
 * \param i Index variable
 * \param isEidEnabled The value to be stored into the i-th element of
 * datapool array isEidEnabled.
 */
static inline void setDpisEidEnabledItem(int i, uint8_t isEidEnabled)
{
  dpEvtVars.isEidEnabled[i] = isEidEnabled;
}

/**
 * Gets the value of the datapool item lastEvtEid_1
 * \return The value of datapool item lastEvtEid_1
 */
static inline uint8_t getDplastEvtEid_1()
{
  return dpEvtVars.lastEvtEid_1;
}

/**
 * Sets the value of the datapool item lastEvtEid_1
 * \param lastEvtEid_1 The value to be stored into the datapool item
 * lastEvtEid_1.
 */
static inline void setDplastEvtEid_1(uint8_t lastEvtEid_1)
{
  dpEvtVars.lastEvtEid_1 = lastEvtEid_1;
}

/**
 * Gets the value of the datapool item lastEvtEid_2
 * \return The value of datapool item lastEvtEid_2
 */
static inline uint8_t getDplastEvtEid_2()
{
  return dpEvtVars.lastEvtEid_2;
}

/**
 * Sets the value of the datapool item lastEvtEid_2
 * \param lastEvtEid_2 The value to be stored into the datapool item
 * lastEvtEid_2.
 */
static inline void setDplastEvtEid_2(uint8_t lastEvtEid_2)
{
  dpEvtVars.lastEvtEid_2 = lastEvtEid_2;
}

/**
 * Gets the value of the datapool item lastEvtEid_3
 * \return The value of datapool item lastEvtEid_3
 */
static inline uint8_t getDplastEvtEid_3()
{
  return dpEvtVars.lastEvtEid_3;
}

/**
 * Sets the value of the datapool item lastEvtEid_3
 * \param lastEvtEid_3 The value to be stored into the datapool item
 * lastEvtEid_3.
 */
static inline void setDplastEvtEid_3(uint8_t lastEvtEid_3)
{
  dpEvtVars.lastEvtEid_3 = lastEvtEid_3;
}

/**
 * Gets the value of the datapool item lastEvtEid_4
 * \return The value of datapool item lastEvtEid_4
 */
static inline uint8_t getDplastEvtEid_4()
{
  return dpEvtVars.lastEvtEid_4;
}

/**
 * Sets the value of the datapool item lastEvtEid_4
 * \param lastEvtEid_4 The value to be stored into the datapool item
 * lastEvtEid_4.
 */
static inline void setDplastEvtEid_4(uint8_t lastEvtEid_4)
{
  dpEvtVars.lastEvtEid_4 = lastEvtEid_4;
}

/**
 * Gets the value of the datapool item lastEvtTime_1
 * \return The value of datapool item lastEvtTime_1
 */
static inline uint32_t getDplastEvtTime_1()
{
  return dpEvtVars.lastEvtTime_1;
}

/**
 * Sets the value of the datapool item lastEvtTime_1
 * \param lastEvtTime_1 The value to be stored into the datapool item
 * lastEvtTime_1.
 */
static inline void setDplastEvtTime_1(uint32_t lastEvtTime_1)
{
  dpEvtVars.lastEvtTime_1 = lastEvtTime_1;
}

/**
 * Gets the value of the datapool item lastEvtTime_2
 * \return The value of datapool item lastEvtTime_2
 */
static inline uint32_t getDplastEvtTime_2()
{
  return dpEvtVars.lastEvtTime_2;
}

/**
 * Sets the value of the datapool item lastEvtTime_2
 * \param lastEvtTime_2 The value to be stored into the datapool item
 * lastEvtTime_2.
 */
static inline void setDplastEvtTime_2(uint32_t lastEvtTime_2)
{
  dpEvtVars.lastEvtTime_2 = lastEvtTime_2;
}

/**
 * Gets the value of the datapool item lastEvtTime_3
 * \return The value of datapool item lastEvtTime_3
 */
static inline uint32_t getDplastEvtTime_3()
{
  return dpEvtVars.lastEvtTime_3;
}

/**
 * Sets the value of the datapool item lastEvtTime_3
 * \param lastEvtTime_3 The value to be stored into the datapool item
 * lastEvtTime_3.
 */
static inline void setDplastEvtTime_3(uint32_t lastEvtTime_3)
{
  dpEvtVars.lastEvtTime_3 = lastEvtTime_3;
}

/**
 * Gets the value of the datapool item lastEvtTime_4
 * \return The value of datapool item lastEvtTime_4
 */
static inline uint32_t getDplastEvtTime_4()
{
  return dpEvtVars.lastEvtTime_4;
}

/**
 * Sets the value of the datapool item lastEvtTime_4
 * \param lastEvtTime_4 The value to be stored into the datapool item
 * lastEvtTime_4.
 */
static inline void setDplastEvtTime_4(uint32_t lastEvtTime_4)
{
  dpEvtVars.lastEvtTime_4 = lastEvtTime_4;
}

/**
 * Gets the value of the datapool item nOfDetectedEvts_1
 * \return The value of datapool item nOfDetectedEvts_1
 */
static inline uint8_t getDpnOfDetectedEvts_1()
{
  return dpEvtVars.nOfDetectedEvts_1;
}

/**
 * Sets the value of the datapool item nOfDetectedEvts_1
 * \param nOfDetectedEvts_1 The value to be stored into the datapool item
 * nOfDetectedEvts_1.
 */
static inline void setDpnOfDetectedEvts_1(uint8_t nOfDetectedEvts_1)
{
  dpEvtVars.nOfDetectedEvts_1 = nOfDetectedEvts_1;
}

/**
 * Gets the value of the datapool item nOfDetectedEvts_2
 * \return The value of datapool item nOfDetectedEvts_2
 */
static inline uint8_t getDpnOfDetectedEvts_2()
{
  return dpEvtVars.nOfDetectedEvts_2;
}

/**
 * Sets the value of the datapool item nOfDetectedEvts_2
 * \param nOfDetectedEvts_2 The value to be stored into the datapool item
 * nOfDetectedEvts_2.
 */
static inline void setDpnOfDetectedEvts_2(uint8_t nOfDetectedEvts_2)
{
  dpEvtVars.nOfDetectedEvts_2 = nOfDetectedEvts_2;
}

/**
 * Gets the value of the datapool item nOfDetectedEvts_3
 * \return The value of datapool item nOfDetectedEvts_3
 */
static inline uint8_t getDpnOfDetectedEvts_3()
{
  return dpEvtVars.nOfDetectedEvts_3;
}

/**
 * Sets the value of the datapool item nOfDetectedEvts_3
 * \param nOfDetectedEvts_3 The value to be stored into the datapool item
 * nOfDetectedEvts_3.
 */
static inline void setDpnOfDetectedEvts_3(uint8_t nOfDetectedEvts_3)
{
  dpEvtVars.nOfDetectedEvts_3 = nOfDetectedEvts_3;
}

/**
 * Gets the value of the datapool item nOfDetectedEvts_4
 * \return The value of datapool item nOfDetectedEvts_4
 */
static inline uint8_t getDpnOfDetectedEvts_4()
{
  return dpEvtVars.nOfDetectedEvts_4;
}

/**
 * Sets the value of the datapool item nOfDetectedEvts_4
 * \param nOfDetectedEvts_4 The value to be stored into the datapool item
 * nOfDetectedEvts_4.
 */
static inline void setDpnOfDetectedEvts_4(uint8_t nOfDetectedEvts_4)
{
  dpEvtVars.nOfDetectedEvts_4 = nOfDetectedEvts_4;
}

/**
 * Gets the value of the datapool item nOfDisabledEid_1
 * \return The value of datapool item nOfDisabledEid_1
 */
static inline uint8_t getDpnOfDisabledEid_1()
{
  return dpEvtVars.nOfDisabledEid_1;
}

/**
 * Sets the value of the datapool item nOfDisabledEid_1
 * \param nOfDisabledEid_1 The value to be stored into the datapool item
 * nOfDisabledEid_1.
 */
static inline void setDpnOfDisabledEid_1(uint8_t nOfDisabledEid_1)
{
  dpEvtVars.nOfDisabledEid_1 = nOfDisabledEid_1;
}

/**
 * Gets the value of the datapool item nOfDisabledEid_2
 * \return The value of datapool item nOfDisabledEid_2
 */
static inline uint8_t getDpnOfDisabledEid_2()
{
  return dpEvtVars.nOfDisabledEid_2;
}

/**
 * Sets the value of the datapool item nOfDisabledEid_2
 * \param nOfDisabledEid_2 The value to be stored into the datapool item
 * nOfDisabledEid_2.
 */
static inline void setDpnOfDisabledEid_2(uint8_t nOfDisabledEid_2)
{
  dpEvtVars.nOfDisabledEid_2 = nOfDisabledEid_2;
}

/**
 * Gets the value of the datapool item nOfDisabledEid_3
 * \return The value of datapool item nOfDisabledEid_3
 */
static inline uint8_t getDpnOfDisabledEid_3()
{
  return dpEvtVars.nOfDisabledEid_3;
}

/**
 * Sets the value of the datapool item nOfDisabledEid_3
 * \param nOfDisabledEid_3 The value to be stored into the datapool item
 * nOfDisabledEid_3.
 */
static inline void setDpnOfDisabledEid_3(uint8_t nOfDisabledEid_3)
{
  dpEvtVars.nOfDisabledEid_3 = nOfDisabledEid_3;
}

/**
 * Gets the value of the datapool item nOfDisabledEid_4
 * \return The value of datapool item nOfDisabledEid_4
 */
static inline uint8_t getDpnOfDisabledEid_4()
{
  return dpEvtVars.nOfDisabledEid_4;
}

/**
 * Sets the value of the datapool item nOfDisabledEid_4
 * \param nOfDisabledEid_4 The value to be stored into the datapool item
 * nOfDisabledEid_4.
 */
static inline void setDpnOfDisabledEid_4(uint8_t nOfDisabledEid_4)
{
  dpEvtVars.nOfDisabledEid_4 = nOfDisabledEid_4;
}

/**
 * Gets the value of the datapool item nOfGenEvtRep_1
 * \return The value of datapool item nOfGenEvtRep_1
 */
static inline uint8_t getDpnOfGenEvtRep_1()
{
  return dpEvtVars.nOfGenEvtRep_1;
}

/**
 * Sets the value of the datapool item nOfGenEvtRep_1
 * \param nOfGenEvtRep_1 The value to be stored into the datapool item
 * nOfGenEvtRep_1.
 */
static inline void setDpnOfGenEvtRep_1(uint8_t nOfGenEvtRep_1)
{
  dpEvtVars.nOfGenEvtRep_1 = nOfGenEvtRep_1;
}

/**
 * Gets the value of the datapool item nOfGenEvtRep_2
 * \return The value of datapool item nOfGenEvtRep_2
 */
static inline uint8_t getDpnOfGenEvtRep_2()
{
  return dpEvtVars.nOfGenEvtRep_2;
}

/**
 * Sets the value of the datapool item nOfGenEvtRep_2
 * \param nOfGenEvtRep_2 The value to be stored into the datapool item
 * nOfGenEvtRep_2.
 */
static inline void setDpnOfGenEvtRep_2(uint8_t nOfGenEvtRep_2)
{
  dpEvtVars.nOfGenEvtRep_2 = nOfGenEvtRep_2;
}

/**
 * Gets the value of the datapool item nOfGenEvtRep_3
 * \return The value of datapool item nOfGenEvtRep_3
 */
static inline uint8_t getDpnOfGenEvtRep_3()
{
  return dpEvtVars.nOfGenEvtRep_3;
}

/**
 * Sets the value of the datapool item nOfGenEvtRep_3
 * \param nOfGenEvtRep_3 The value to be stored into the datapool item
 * nOfGenEvtRep_3.
 */
static inline void setDpnOfGenEvtRep_3(uint8_t nOfGenEvtRep_3)
{
  dpEvtVars.nOfGenEvtRep_3 = nOfGenEvtRep_3;
}

/**
 * Gets the value of the datapool item nOfGenEvtRep_4
 * \return The value of datapool item nOfGenEvtRep_4
 */
static inline uint8_t getDpnOfGenEvtRep_4()
{
  return dpEvtVars.nOfGenEvtRep_4;
}

/**
 * Sets the value of the datapool item nOfGenEvtRep_4
 * \param nOfGenEvtRep_4 The value to be stored into the datapool item
 * nOfGenEvtRep_4.
 */
static inline void setDpnOfGenEvtRep_4(uint8_t nOfGenEvtRep_4)
{
  dpEvtVars.nOfGenEvtRep_4 = nOfGenEvtRep_4;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSDPEVT_H */
