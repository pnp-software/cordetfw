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


/** Type used for the Application ID of a packet. */
typedef uint16_t CrPsApid_t;

/** Type used for the Timeout for packets*/
typedef uint32_t CrPsTimeOut_t;

/** Type used for the Destination or Source of a packet. */
typedef uint16_t CrPsDestSrc_t;

/** Type used for the Sequence Control of a packet. */
typedef uint16_t CrPsSeqCtrl_t;

/** Type used for the Failure Code of a packet. */
typedef uint16_t CrPsFailCode_t;

/** Type used for the Failure Data of a packet. */
typedef uint32_t CrPsFailData_t;

/** Type used for the Step ID of a packet. */
typedef uint32_t CrPsStepId_t;

/** Type used for the Parameter ID of a packet. */
typedef uint16_t CrPsParamId_t;

/** Type used for the Parameter Report Structure ID of a packet. */
typedef uint8_t CrPsSid_t;

/** Type used for the Collection Interval of a packet. */
typedef uint32_t CrPsCollectInterval_t;

/* Type used as a period e.g.(collection period) */
typedef uint32_t CrPsPeriod_t;

/** Type used for the Repetition Number of a packet. */
typedef uint32_t CrPsRepNum_t;

/** Type used for the Status of a packet. */
typedef uint8_t CrPsStatus_t;

/** Type used for Parameter Values of unsigned 32bit Integers. */
typedef uint32_t CrPsParamValueU4_t;

/* Type used as an unsigned integer value 32 bit */
typedef uint32_t CrPsValueU4_t;

/** Type used for Event Id of a Packet */
typedef uint16_t CrPsEid_t;

/** Type used for the Auxiliary Data of a packet. */
typedef uint32_t CrPsAux_t;

/* Type used for Addresses*/
typedef uint32_t CrPsAddr_t;

/* Type used as a Flag e.g.(Enable/Disable)  */
typedef uint8_t CrPsFlag_t;

/* Type used as a Number 16 bit*/
typedef uint16_t CrPsNumberU2_t;

/* Type used for a repetition count */
typedef uint16_t CrPsRepetition_t;

/* Type used for a 32 bit Number */
typedef uint32_t CrPsNumberU4_t;

/* Type used for a Group*/
typedef uint16_t CrPsGroup_t;

/* Type used as the Transaction Identifier*/
typedef uint32_t CrPsTid_t;

/* Type used as size of Packets*/
typedef uint32_t CrPsSize_t;

/* Type used for a reason of a failure*/
typedef uint32_t CrPsFailReason_t;

/* Type used as an identifier of the number of parts of a packet */
typedef uint16_t CrPsPart_t;


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


/* Service 17: Test Service Constants */
/** Maximum number of target applications for On-Board-Connection Test */
#define TEST_MAX_APP 10

/* Service 3: Housekeeping Constants*/
/** Number of Report Definitions in the Report Definition List
  * (maximum number of housekeeping/diagnostic reports)*/
#define HK_N_REP_DEF 5

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
#define EVT_N_EID 5

/** Array of EVT_N_EID elements holding the event identifiers in
  * ascending order*/
#define EVT_EID {1,2,3,4,5}

/** Array of EVT N EID elements holding the severity level of the
  * event identifiers*/
#define EVT_EID_LEVEL {1,2,3,4,1}

/* Number of Large Packet Transfer Buffers available for down- or up-link of large packets */
#define LPT_N_BUF 5


/** Failure Codes for Service 5 (Event Report) */
/* Generated when an attempt to retrieve a report from the OutFactory has failed */
#define OUTFACTORY_FAIL   100

/* Generated by InLoader when it receives a report with an invalid destination */
#define INLOADER_INV_DEST 101

/* Failure Code for a error in the Part Number of a Packet for Service 13 */
#define PART_NMB_ERR      131

/** Outcome Failure Codes for Service 3 (Housekeeping) */
/*Failure code for start action of commands (3,1) and (3,2) when they attempt to create a new report at a time when the RDL is already full */
#define VER_FULL_RDL     201

/* Failure code for start action of commands (3,1) and (3,2) when their report configuration data violate an RDL constraint of table 9.1 */
#define VER_RDL_CONSTR   202

/* Failure code for start action of commands (3,1) and (3,2) when attempt to create a new report with a SID which is already in use*/
#define VER_SID_IN_USE   203

/* Failure code for start action of commands (3,1) and (3,2) when they carry the same data item identifier twice */
#define VER_DUPL_DI      204

/* Failure code for start actions when they unsuccessfully attempt to create a new report from the OutFactory */
#define VER_REP_CR_FD    205

/* Failure code for start actions when the Load operation in the OutLoader has failed */
#define VER_OUTLOADER_FD 206

/* Failure code for multi-instruction start service action 3 of commands when all the SIDs in the command are found to be invalid */
#define VER_SID_START_FD 207

/**/
#define VER_S3S_START_FD 208

/** Failure Codes of Service 3 (Housekeeping) for Service 1 (Request Verification) */
/* Failure code for start action of a service 5 command when an illegal EID is encountered */
#define VER_ILL_SID      211

/*Failure code for start action of commands (3,3) and (3,4) when a SID which is enabled is encountered */
#define VER_ENABLED_SID  212

/** Outcome Failure Codes for Service 5 (Event Report) */
#define VER_EID_START_FD 221

/** Failure Codes of Service 5 (Event Report) for Service 1 (Request Verification) */
#define VER_ILL_EID      225




#endif /* CRPS_USERCONSTANTS_H_ */
