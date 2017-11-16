/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-10-13 12:48:17
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSDPSERVEVT_H_
#define CRPSDPSERVEVT_H_

#include <CrFwUserConstants.h> 
#include <CrPsUserConstants.h>

#include "CrPsDpTypes.h"

/**
 * Type description
 */
typedef struct {
  /**
   * Array of EVT_N_EID elements holding the enable status of the event
   * identifiers
   */
  CrPsFlag_t isEidEnabled[EVT_N_EID];
  /**
   * Event identifier of the last generated level 1 event report
   */
  CrPsEid_t lastEvtEid_1;
  /**
   * Event identifier of the last generated level 2 event report
   */
  CrPsEid_t lastEvtEid_2;
  /**
   * Event identifier of the last generated level 3 event report
   */
  CrPsEid_t lastEvtEid_3;
  /**
   * Event identifier of the last generated level 4event report
   */
  CrPsEid_t lastEvtEid_4;
  /**
   * Time when the last level 1 event report was generated
   */
  CrFwTimeStamp_t lastEvtTime_1;
  /**
   * Time when the last level 2 event report was generated
   */
  CrFwTimeStamp_t lastEvtTime_2;
  /**
   * Time when the last level 3 event report was generated
   */
  CrFwTimeStamp_t lastEvtTime_3;
  /**
   * Time when the last level 4 event report was generated
   */
  CrFwTimeStamp_t lastEvtTime_4;
  /**
   * Number of detected occurrences of level 1 events
   */
  CrPsNumberU4_t nOfDetectedEvts_1;
  /**
   * Number of detected occurrences of level 2 events
   */
  CrPsNumberU4_t nOfDetectedEvts_2;
  /**
   * Number of detected occurrences of level 3 events
   */
  CrPsNumberU4_t nOfDetectedEvts_3;
  /**
   * Number of detected occurrences of level 4 events
   */
  CrPsNumberU4_t nOfDetectedEvts_4;
  /**
   * Number of event identifiers of level 1 which are disabled
   */
  CrPsNumberU2_t nOfDisabledEid_1;
  /**
   * Number of event identifiers of level 2 which are disabled
   */
  CrPsNumberU2_t nOfDisabledEid_2;
  /**
   * Number of event identifiers of level 3 which are disabled
   */
  CrPsNumberU2_t nOfDisabledEid_3;
  /**
   * Number of event identifiers of level 4 which are disabled
   */
  CrPsNumberU2_t nOfDisabledEid_4;
  /**
   * Number of generated level 1 event reports
   */
  CrPsNumberU4_t nOfGenEvtRep_1;
  /**
   * Number of generated level 2 event reports
   */
  CrPsNumberU4_t nOfGenEvtRep_2;
  /**
   * Number of generated level 3 event reports
   */
  CrPsNumberU4_t nOfGenEvtRep_3;
  /**
   * Number of generated level 4 event reports
   */
  CrPsNumberU4_t nOfGenEvtRep_4;
} DpServEvtVars_t;

extern DpServEvtVars_t dpServEvtVars;

/**
 * Initialises ServEvt
 */
void initDpServEvt(void);

/**
 * Gets the datapool array isEidEnabled
 * \return The datapool array isEidEnabled
 */
static inline CrPsFlag_t* getDpisEidEnabledArray()
{
  return &dpServEvtVars.isEidEnabled[0];
}

/**
 * Gets the value of the i-th element in the datapool array isEidEnabled
 * \param i Index variable
 * \return The i-th element in the datapool array isEidEnabled
 */
static inline CrPsFlag_t getDpisEidEnabledItem(int i)
{
  return dpServEvtVars.isEidEnabled[i];
}

/**
 * Sets the value of the i-th element in the datapool array isEidEnabled
 * \param i Index variable
 * \param isEidEnabled The value to be stored into the i-th element of
 * datapool array isEidEnabled.
 */
static inline void setDpisEidEnabledItem(int i, CrPsFlag_t isEidEnabled)
{
  dpServEvtVars.isEidEnabled[i] = isEidEnabled;
}

/**
 * Gets the value of the datapool item lastEvtEid_1
 * \return The value of datapool item lastEvtEid_1
 */
static inline CrPsEid_t getDplastEvtEid_1()
{
  return dpServEvtVars.lastEvtEid_1;
}

/**
 * Sets the value of the datapool item lastEvtEid_1
 * \param lastEvtEid_1 The value to be stored into the datapool item
 * lastEvtEid_1.
 */
static inline void setDplastEvtEid_1(CrPsEid_t lastEvtEid_1)
{
  dpServEvtVars.lastEvtEid_1 = lastEvtEid_1;
}

/**
 * Gets the value of the datapool item lastEvtEid_2
 * \return The value of datapool item lastEvtEid_2
 */
static inline CrPsEid_t getDplastEvtEid_2()
{
  return dpServEvtVars.lastEvtEid_2;
}

/**
 * Sets the value of the datapool item lastEvtEid_2
 * \param lastEvtEid_2 The value to be stored into the datapool item
 * lastEvtEid_2.
 */
static inline void setDplastEvtEid_2(CrPsEid_t lastEvtEid_2)
{
  dpServEvtVars.lastEvtEid_2 = lastEvtEid_2;
}

/**
 * Gets the value of the datapool item lastEvtEid_3
 * \return The value of datapool item lastEvtEid_3
 */
static inline CrPsEid_t getDplastEvtEid_3()
{
  return dpServEvtVars.lastEvtEid_3;
}

/**
 * Sets the value of the datapool item lastEvtEid_3
 * \param lastEvtEid_3 The value to be stored into the datapool item
 * lastEvtEid_3.
 */
static inline void setDplastEvtEid_3(CrPsEid_t lastEvtEid_3)
{
  dpServEvtVars.lastEvtEid_3 = lastEvtEid_3;
}

/**
 * Gets the value of the datapool item lastEvtEid_4
 * \return The value of datapool item lastEvtEid_4
 */
static inline CrPsEid_t getDplastEvtEid_4()
{
  return dpServEvtVars.lastEvtEid_4;
}

/**
 * Sets the value of the datapool item lastEvtEid_4
 * \param lastEvtEid_4 The value to be stored into the datapool item
 * lastEvtEid_4.
 */
static inline void setDplastEvtEid_4(CrPsEid_t lastEvtEid_4)
{
  dpServEvtVars.lastEvtEid_4 = lastEvtEid_4;
}

/**
 * Gets the value of the datapool item lastEvtTime_1
 * \return The value of datapool item lastEvtTime_1
 */
static inline CrFwTimeStamp_t getDplastEvtTime_1()
{
  return dpServEvtVars.lastEvtTime_1;
}

/**
 * Sets the value of the datapool item lastEvtTime_1
 * \param lastEvtTime_1 The value to be stored into the datapool item
 * lastEvtTime_1.
 */
static inline void setDplastEvtTime_1(CrFwTimeStamp_t lastEvtTime_1)
{
  dpServEvtVars.lastEvtTime_1 = lastEvtTime_1;
}

/**
 * Gets the value of the datapool item lastEvtTime_2
 * \return The value of datapool item lastEvtTime_2
 */
static inline CrFwTimeStamp_t getDplastEvtTime_2()
{
  return dpServEvtVars.lastEvtTime_2;
}

/**
 * Sets the value of the datapool item lastEvtTime_2
 * \param lastEvtTime_2 The value to be stored into the datapool item
 * lastEvtTime_2.
 */
static inline void setDplastEvtTime_2(CrFwTimeStamp_t lastEvtTime_2)
{
  dpServEvtVars.lastEvtTime_2 = lastEvtTime_2;
}

/**
 * Gets the value of the datapool item lastEvtTime_3
 * \return The value of datapool item lastEvtTime_3
 */
static inline CrFwTimeStamp_t getDplastEvtTime_3()
{
  return dpServEvtVars.lastEvtTime_3;
}

/**
 * Sets the value of the datapool item lastEvtTime_3
 * \param lastEvtTime_3 The value to be stored into the datapool item
 * lastEvtTime_3.
 */
static inline void setDplastEvtTime_3(CrFwTimeStamp_t lastEvtTime_3)
{
  dpServEvtVars.lastEvtTime_3 = lastEvtTime_3;
}

/**
 * Gets the value of the datapool item lastEvtTime_4
 * \return The value of datapool item lastEvtTime_4
 */
static inline CrFwTimeStamp_t getDplastEvtTime_4()
{
  return dpServEvtVars.lastEvtTime_4;
}

/**
 * Sets the value of the datapool item lastEvtTime_4
 * \param lastEvtTime_4 The value to be stored into the datapool item
 * lastEvtTime_4.
 */
static inline void setDplastEvtTime_4(CrFwTimeStamp_t lastEvtTime_4)
{
  dpServEvtVars.lastEvtTime_4 = lastEvtTime_4;
}

/**
 * Gets the value of the datapool item nOfDetectedEvts_1
 * \return The value of datapool item nOfDetectedEvts_1
 */
static inline CrPsNumberU4_t getDpnOfDetectedEvts_1()
{
  return dpServEvtVars.nOfDetectedEvts_1;
}

/**
 * Sets the value of the datapool item nOfDetectedEvts_1
 * \param nOfDetectedEvts_1 The value to be stored into the datapool item
 * nOfDetectedEvts_1.
 */
static inline void setDpnOfDetectedEvts_1(CrPsNumberU4_t nOfDetectedEvts_1)
{
  dpServEvtVars.nOfDetectedEvts_1 = nOfDetectedEvts_1;
}

/**
 * Gets the value of the datapool item nOfDetectedEvts_2
 * \return The value of datapool item nOfDetectedEvts_2
 */
static inline CrPsNumberU4_t getDpnOfDetectedEvts_2()
{
  return dpServEvtVars.nOfDetectedEvts_2;
}

/**
 * Sets the value of the datapool item nOfDetectedEvts_2
 * \param nOfDetectedEvts_2 The value to be stored into the datapool item
 * nOfDetectedEvts_2.
 */
static inline void setDpnOfDetectedEvts_2(CrPsNumberU4_t nOfDetectedEvts_2)
{
  dpServEvtVars.nOfDetectedEvts_2 = nOfDetectedEvts_2;
}

/**
 * Gets the value of the datapool item nOfDetectedEvts_3
 * \return The value of datapool item nOfDetectedEvts_3
 */
static inline CrPsNumberU4_t getDpnOfDetectedEvts_3()
{
  return dpServEvtVars.nOfDetectedEvts_3;
}

/**
 * Sets the value of the datapool item nOfDetectedEvts_3
 * \param nOfDetectedEvts_3 The value to be stored into the datapool item
 * nOfDetectedEvts_3.
 */
static inline void setDpnOfDetectedEvts_3(CrPsNumberU4_t nOfDetectedEvts_3)
{
  dpServEvtVars.nOfDetectedEvts_3 = nOfDetectedEvts_3;
}

/**
 * Gets the value of the datapool item nOfDetectedEvts_4
 * \return The value of datapool item nOfDetectedEvts_4
 */
static inline CrPsNumberU4_t getDpnOfDetectedEvts_4()
{
  return dpServEvtVars.nOfDetectedEvts_4;
}

/**
 * Sets the value of the datapool item nOfDetectedEvts_4
 * \param nOfDetectedEvts_4 The value to be stored into the datapool item
 * nOfDetectedEvts_4.
 */
static inline void setDpnOfDetectedEvts_4(CrPsNumberU4_t nOfDetectedEvts_4)
{
  dpServEvtVars.nOfDetectedEvts_4 = nOfDetectedEvts_4;
}

/**
 * Gets the value of the datapool item nOfDisabledEid_1
 * \return The value of datapool item nOfDisabledEid_1
 */
static inline CrPsNumberU2_t getDpnOfDisabledEid_1()
{
  return dpServEvtVars.nOfDisabledEid_1;
}

/**
 * Sets the value of the datapool item nOfDisabledEid_1
 * \param nOfDisabledEid_1 The value to be stored into the datapool item
 * nOfDisabledEid_1.
 */
static inline void setDpnOfDisabledEid_1(CrPsNumberU2_t nOfDisabledEid_1)
{
  dpServEvtVars.nOfDisabledEid_1 = nOfDisabledEid_1;
}

/**
 * Gets the value of the datapool item nOfDisabledEid_2
 * \return The value of datapool item nOfDisabledEid_2
 */
static inline CrPsNumberU2_t getDpnOfDisabledEid_2()
{
  return dpServEvtVars.nOfDisabledEid_2;
}

/**
 * Sets the value of the datapool item nOfDisabledEid_2
 * \param nOfDisabledEid_2 The value to be stored into the datapool item
 * nOfDisabledEid_2.
 */
static inline void setDpnOfDisabledEid_2(CrPsNumberU2_t nOfDisabledEid_2)
{
  dpServEvtVars.nOfDisabledEid_2 = nOfDisabledEid_2;
}

/**
 * Gets the value of the datapool item nOfDisabledEid_3
 * \return The value of datapool item nOfDisabledEid_3
 */
static inline CrPsNumberU2_t getDpnOfDisabledEid_3()
{
  return dpServEvtVars.nOfDisabledEid_3;
}

/**
 * Sets the value of the datapool item nOfDisabledEid_3
 * \param nOfDisabledEid_3 The value to be stored into the datapool item
 * nOfDisabledEid_3.
 */
static inline void setDpnOfDisabledEid_3(CrPsNumberU2_t nOfDisabledEid_3)
{
  dpServEvtVars.nOfDisabledEid_3 = nOfDisabledEid_3;
}

/**
 * Gets the value of the datapool item nOfDisabledEid_4
 * \return The value of datapool item nOfDisabledEid_4
 */
static inline CrPsNumberU2_t getDpnOfDisabledEid_4()
{
  return dpServEvtVars.nOfDisabledEid_4;
}

/**
 * Sets the value of the datapool item nOfDisabledEid_4
 * \param nOfDisabledEid_4 The value to be stored into the datapool item
 * nOfDisabledEid_4.
 */
static inline void setDpnOfDisabledEid_4(CrPsNumberU2_t nOfDisabledEid_4)
{
  dpServEvtVars.nOfDisabledEid_4 = nOfDisabledEid_4;
}

/**
 * Gets the value of the datapool item nOfGenEvtRep_1
 * \return The value of datapool item nOfGenEvtRep_1
 */
static inline CrPsNumberU4_t getDpnOfGenEvtRep_1()
{
  return dpServEvtVars.nOfGenEvtRep_1;
}

/**
 * Sets the value of the datapool item nOfGenEvtRep_1
 * \param nOfGenEvtRep_1 The value to be stored into the datapool item
 * nOfGenEvtRep_1.
 */
static inline void setDpnOfGenEvtRep_1(CrPsNumberU4_t nOfGenEvtRep_1)
{
  dpServEvtVars.nOfGenEvtRep_1 = nOfGenEvtRep_1;
}

/**
 * Gets the value of the datapool item nOfGenEvtRep_2
 * \return The value of datapool item nOfGenEvtRep_2
 */
static inline CrPsNumberU4_t getDpnOfGenEvtRep_2()
{
  return dpServEvtVars.nOfGenEvtRep_2;
}

/**
 * Sets the value of the datapool item nOfGenEvtRep_2
 * \param nOfGenEvtRep_2 The value to be stored into the datapool item
 * nOfGenEvtRep_2.
 */
static inline void setDpnOfGenEvtRep_2(CrPsNumberU4_t nOfGenEvtRep_2)
{
  dpServEvtVars.nOfGenEvtRep_2 = nOfGenEvtRep_2;
}

/**
 * Gets the value of the datapool item nOfGenEvtRep_3
 * \return The value of datapool item nOfGenEvtRep_3
 */
static inline CrPsNumberU4_t getDpnOfGenEvtRep_3()
{
  return dpServEvtVars.nOfGenEvtRep_3;
}

/**
 * Sets the value of the datapool item nOfGenEvtRep_3
 * \param nOfGenEvtRep_3 The value to be stored into the datapool item
 * nOfGenEvtRep_3.
 */
static inline void setDpnOfGenEvtRep_3(CrPsNumberU4_t nOfGenEvtRep_3)
{
  dpServEvtVars.nOfGenEvtRep_3 = nOfGenEvtRep_3;
}

/**
 * Gets the value of the datapool item nOfGenEvtRep_4
 * \return The value of datapool item nOfGenEvtRep_4
 */
static inline CrPsNumberU4_t getDpnOfGenEvtRep_4()
{
  return dpServEvtVars.nOfGenEvtRep_4;
}

/**
 * Sets the value of the datapool item nOfGenEvtRep_4
 * \param nOfGenEvtRep_4 The value to be stored into the datapool item
 * nOfGenEvtRep_4.
 */
static inline void setDpnOfGenEvtRep_4(CrPsNumberU4_t nOfGenEvtRep_4)
{
  dpServEvtVars.nOfGenEvtRep_4 = nOfGenEvtRep_4;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSDPSERVEVT_H */
