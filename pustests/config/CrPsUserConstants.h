/**
 * @file CrPsUserConstants.h
 * @ingroup CrIaDemo
 *
 * Header file to define all user-configurable constants and types for the IASW
 * Application.
 *
 * The content of this file is taken over unchanged from the framework-provided
 * default with the exception of the following items:
 *
 *  - The value of the application identifier (20 for the IASW).
 *  - The maximum value of the service type, sub-type and discriminant
 *    attributes
 *
 * @authors V. Cechticky and A. Pasetti
 * edited: Markus Rockenbauer
 * 25.04.2017
 * @copyright P&P Software GmbH, 2014
 */

#ifndef CRPS_USERCONSTANTS_H_
#define CRPS_USERCONSTANTS_H_


/**
 * Identifier for the errors reported through the error reporting interface of <code>CrFwRepErr.h</code>.
 * When a framework component encounters a non-nominal situation during its normal operation,
 * it reports it as an error using the services defined by the <code>CrFwRepErr.h</code>
 * interface.
 * Each error situation is characterized by an error code.
 * This enumerated type defines all the error codes.
 */
typedef enum
{
  /** The Inloader acceptance of a component failed (see <code>CrPsRepErr.h</code>) */
  crInloaderAccFail = 2,
  /** The Inloader detects an invalid destination (see <code>CrPsRepErr.h</code>) */
  crInloaderInvDest = 3,
  /** The Outfactory failed to make the component (see <code>CrPsRepErr.h</code>) */
  crOutfactoryFail = 4
} CrPsRepErrCode_t;


/* Service 3: Housekeeping Constants*/
/** Number of Report Definitions in the Report Definition List
  * (maximum number of housekeeping/diagnostic reports)*/
#define HK_N_REP_DEF 3

/** Maximum value of a service 3 Structure Identifier (SID)*/
#define HK_MAX_SID 3

/** Minimum collection period for service 3 reports*/
#define HK_COLLECT_PER 3

/** Maximum number of simply-commutated parameters in a
  * housekeeping/diagnostic report*/
#define HK_MAX_N_SIMPLE 3

/** Maximum number of super-commutated groups in a house-
  * keeping/diagnostic report*/
#define HK_MAX_N_GR 3

/** Maximum value of the repetition number of a super-
  * commutated group in a housekeeping/diagnostic report*/
#define HK_MAX_REP 3

/** Maximum number of data items in a super-commutated groups
  * in a housekeeping/diagnostic report*/
#define HK_MAX_N_REP 3

/** Maximum value of a data pool item identifier*/
#define HK_MAX_ID 3

/** Number of service 3 Sampling Buffers*/
#define HK_N_SAMP_BUF 3

/** Number of debug variables*/
#define HK_N_DEBUG_VAR 3
#define HK_MAX_N_ITEMS 3

/*Service 5: Event Reporting Constants*/
/** Number of event identifiers supported by the application*/
#define EVT_N_EID 3

/** Array of EVT_N_EID elements holding the event identifiers in
  * ascending order*/
#define EVT_EID {1,2,3}

/** Array of EVT N EID elements holding the severity level of the
  * event identifiers*/
#define EVT_EID_LEVEL {1,2,3}


/** Failure Codes for Service 5 (Event Report) */
#define OUTFACTORY_FAIL   100
#define INLOADER_INV_DEST 101

/** Failure Codes for Service 3 (Housekeeping) */
#define VER_FULL_RDL     201
#define VER_RDL_CONSTR   202
#define VER_SID_IN_USE   203
#define VER_DUPL_DI      204
#define VER_REP_CR_FD    205
#define VER_OUTLOADER_FD 206

#endif /* CRPS_USERCONSTANTS_H_ */
