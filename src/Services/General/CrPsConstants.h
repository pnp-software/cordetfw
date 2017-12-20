/**
 * @file CrPsConstants.h
 *
 * Header file to define all service and packet identifiers.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#ifndef CRPS_CONSTANTS_H
#define CRPS_CONSTANTS_H

#include <CrPsPkt.h> /* for data structures TmHeader_t and TcHeader_t */
#include <CrPsUserConstants.h> /* for customized data types */

/* ######################################################################################
 * ### Definition of Data Structures
 * ######################################################################################
 */

typedef struct {
  FwSmDesc_t smDesc;
  unsigned short ushortParam1;
  unsigned short ushortParam2;
} prData_t;

typedef struct {
	unsigned short outcome;
} prDataStartAction_t;

typedef struct {
	FwSmDesc_t smDesc;
	CrFwDestSrc_t source;
	unsigned short outcome;
	unsigned short stepId;
} prDataPrgrAction_t;

typedef struct {
	FwSmDesc_t smDesc;
	unsigned char sid;
} prDataHkRepReadyCheck_t;

typedef struct {
	FwSmDesc_t smDesc;
	unsigned char* sidPtr;
} prDescMultiSidCmdStart_t;

typedef struct {
	FwSmDesc_t smDesc;
	unsigned char* sidPtr;
	unsigned short outcome;
} prDescGenerateHkOneShotPrgr_t;

typedef struct {
	FwSmDesc_t smDesc;
	/*unsigned char* sidPtr;*/
} prDescCmd3s1Start_t;

typedef struct {
	FwSmDesc_t smDesc;
	/*unsigned char* sidPtr;*/
} prDescCmd3s3Start_t;

typedef struct {
	FwSmDesc_t smDesc;
	/*unsigned char* sidPtr;*/
} prDescCmd3s9Start_t;

typedef struct {
	FwSmDesc_t smDesc;
	unsigned char* sidPtr;
    unsigned short outcome;
} prDescCmd3s9Prgr_t;

typedef struct {
	FwSmDesc_t smDesc;
	CrPsFlag_t* evtFlagPtr;
	unsigned short* eidPtr;
} prDescCmdEidStart_t;

typedef struct {
	FwSmDesc_t smDesc;
    unsigned short outcome;
} prDescCmd13Start_t;


#define LPT_FAILCODE_NO_FAIL 0
#define LPT_FAILCODE_TIME_OUT 1
#define EVT_DOWN_ABORT 131

/* ######################################################################################
 * ### Identifiers (e.g. service type, service sub-type)
 * ######################################################################################
 */

/**
 * Type identifier of the Request Verification Service.
 */
#define CRPS_REQVERIF 1

/**
 * Subtype identifier of the Request Verification Acceptance Successful out-going report packet.
 */
#define CRPS_REQVERIF_ACC_SUCC 1

/**
 * Subtype identifier of the Request Verification Acceptance Failed out-going report packet.
 */
#define CRPS_REQVERIF_ACC_FAIL 2

/**
 * Subtype identifier of the Request Verification Start Successful out-going report packet.
 */
#define CRPS_REQVERIF_START_SUCC 3

/**
 * Subtype identifier of the Request Verification Start Failed out-going report packet.
 */
#define CRPS_REQVERIF_START_FAIL 4

/**
 * Subtype identifier of the Request Verification Progress Successful out-going report packet.
 */
#define CRPS_REQVERIF_PROG_SUCC 5

/**
 * Subtype identifier of the Request Verification Progress Failed out-going report packet.
 */
#define CRPS_REQVERIF_PROG_FAIL 6

/**
 * Subtype identifier of the Request Verification Termination Successful out-going report packet.
 */
#define CRPS_REQVERIF_TERM_SUCC 7

/**
 * Subtype identifier of the Request Verification Termination Failed out-going report packet.
 */
#define CRPS_REQVERIF_TERM_FAIL 8

/**
 * Subtype identifier of the Request Verification Rerouting Failed out-going report packet.
 */
#define CRPS_REQVERIF_REROUT_FAIL 10

/**
 * Type identifier of the Housekeeping Data Report out-going report packet.
 */
#define CRPS_HK 3

/**
 * Subtype identifier of the Housekeeping Create a Housekeeping Parameter Report Structure command packet.
 */
#define CRPS_HK_CREATE_HKSTRUCT_CMD 1

/**
 * Subtype identifier of the Housekeeping Create a Diagnostic Parameter Report Structure command packet.
 */
#define CRPS_HK_CREATE_DIAGSTRUCT_CMD 2

/**
 * Subtype identifier of the Housekeeping Delete a Housekeeping Parameter Report Structure command packet.
 */
#define CRPS_HK_DELETE_HKSTRUCT_CMD 3

/**
 * Subtype identifier of the Housekeeping Delete a Diagnostic Parameter Report Structure command packet.
 */
#define CRPS_HK_DELETE_DIAGSTRUCT_CMD 4

/**
 * Subtype identifier of the Housekeeping Enable Periodic Generation of a Housekeeping Parameter Report Structure command packet.
 */
#define CRPS_HK_ENABLE_PERIODICHK_CMD 5

/**
 * Subtype identifier of the Housekeeping Disable Periodic Generation of a Housekeeping Parameter Report Structure command packet.
 */
#define CRPS_HK_DISABLE_PERIODICHK_CMD 6

/**
 * Subtype identifier of the Housekeeping Enable Periodic Generation of a Diagnostic Parameter Report Structure command packet.
 */
#define CRPS_HK_ENABLE_PERIODICDIAG_CMD 7

/**
 * Subtype identifier of the Housekeeping Disable Periodic Generation of a Diagnostic Parameter Report Structure command packet.
 */
#define CRPS_HK_DISABLE_PERIODICDIAG_CMD 8

/**
 * Subtype identifier of the Housekeeping Report Housekeeping Parameter Report Structure command packet.
 */
#define CRPS_HK_HKREP_STRUCT_CMD 9

/**
 * Subtype identifier of the Housekeeping Housekeeping Parameter Report Structure Report out-going report packet.
 */
#define CRPS_HK_HKREP_STRUCT_REP 10

/**
 * Subtype identifier of the Housekeeping Report Diagnostic Parameter Report Structure command packet.
 */
#define CRPS_HK_DIAGREP_STRUCT_CMD 11

 /**
 * Subtype identifier of the Housekeeping Diagnostic Parameter Report Structure Report out-going report packet.
 */
#define CRPS_HK_DIAGREP_STRUCT_REP 12

/**
 * Subtype identifier of the Housekeeping Housekeeping Parameter Report out-going report packet.
 */
#define CRPS_HK_HKPARAM_REP 25

 /**
 * Subtype identifier of the Housekeeping Diagnostic Parameter Report out-going report packet.
 */
#define CRPS_HK_DIAGPARAM_REP 26

/**
 * Subtype identifier of the Housekeeping Generate One-Shot Report for Housekeeping Parameters command packet.
 */
#define CRPS_HK_HKONESHOT_CMD 27

 /**
 * Subtype identifier of the Housekeeping Generate One-Shot Report for Diagnostic Parameters command packet.
 */
#define CRPS_HK_DIAGONESHOT_CMD 28

/**
 * Type identifier of the Event Reporting Service.
 */
#define CRPS_EVT 5

/**
 * Subtype identifier of the Event Report Severity Level 1 out-going report packet.
 */
#define CRPS_EVT_SEVLEVEL1_REP 1

/**
 * Subtype identifier of the Event Report Severity Level 2 out-going report packet.
 */
#define CRPS_EVT_SEVLEVEL2_REP 2

/**
 * Subtype identifier of the Event Report Severity Level 3 out-going report packet.
 */
#define CRPS_EVT_SEVLEVEL3_REP 3

/**
 * Subtype identifier of the Event Report Severity Level 4 out-going report packet.
 */
#define CRPS_EVT_SEVLEVEL4_REP 4

/**
 * Subtype identifier of the Event Report Enable in-coming command packet.
 */
#define CRPS_EVT_ENABLE_CMD 5

/**
 * Subtype identifier of the Event Report Disable in-coming command packet.
 */
#define CRPS_EVT_DISABLE_CMD 6

 /**
 * Subtype identifier of the Event Report Report Disabled in-coming command packet.
 */
#define CRPS_EVT_REPDISABLED_CMD 7

 /**
 * Subtype identifier of the Event Report Report Disabled out-going report packet.
 */
#define CRPS_EVT_REPDISABLED_REP 8

/**
 * Type identifier of the Large Packet Transfer Service.
 */
#define CRPS_LPT 13

/**
 * Subtype identifier of the Large Packet Transfer First Downlink Part out-going report packet.
 */
#define CRPS_LPT_DOWNFIRST_REP 1

/**
 * Subtype identifier of the Large Packet Transfer Intermediate Downlink Part out-going report packet.
 */
#define CRPS_LPT_DOWNINTER_REP 2

/**
 * Subtype identifier of the Large Packet Transfer Last Downlink Part out-going report packet.
 */
#define CRPS_LPT_DOWNLAST_REP 3

/**
 * Subtype identifier of the Large Packet Transfer First Uplink Part command packet.
 */
#define CRPS_LPT_UPFIRST_CMD 9

/**
 * Subtype identifier of the Large Packet Transfer Intermediate Uplink Part command packet.
 */
#define CRPS_LPT_UPINTER_CMD 10

/**
 * Subtype identifier of the Large Packet Transfer Last Uplink Part command packet.
 */
#define CRPS_LPT_UPLAST_CMD 11

/**
 * Subtype identifier of the Large Packet Transfer Abort Uplink out-going report packet.
 */
#define CRPS_LPT_UPABORT_REP 16

/**
 * Subtype identifier of the Large Packet Transfer Start Downlink command packet.
 */
#define CRPS_LPT_STARTDOWN_CMD 129

/**
 * Subtype identifier of the Large Packet Transfer Abort Downlink command packet.
 */
#define CRPS_LPT_ABORTDOWN_CMD 130

/**
 * Type identifier of the Test Service.
 */
#define CRPS_TEST 17

/**
 * Subtype identifier of the Test AreYouAlive Connection in-coming command packet.
 */
#define CRPS_TEST_AREYOUALIVE_CONNECTION_CMD 1

/**
 * Subtype identifier of the Test AreYouAlive Connection out-going report packet.
 */
#define CRPS_TEST_AREYOUALIVE_CONNECTION_REP 2

/**
 * Subtype identifier of the Test On-Board Connection in-coming command packet.
 */
#define CRPS_TEST_ONBOARD_CONNECTION_CMD 3

/**
 * Subtype identifier of the Test On-Board Connection out-going report packet.
 */
#define CRPS_TEST_ONBOARD_CONNECTION_REP 4


/* ######################################################################################
 * ### Lengths of Packet Fields (e.g. headers)
 * ######################################################################################
 */

/**
 * The length offset for the out-going report.
 */
#define OFFSET_PAR_LENGTH_OUT_REP_PCKT sizeof(TmHeader_t)

/**
 * The length offset for the in-coming command.
 */
#define OFFSET_PAR_LENGTH_IN_CMD_PCKT sizeof(TcHeader_t)

/**
 * The length of CRC.
 */ 
#define CRC_LENGTH 2


/* ######################################################################################
 * ### Total Packet Lengths
 * ######################################################################################
 */

/**
 * Length of the Request Verification Acceptance Successful out-going report packet.
 */
#define CRPS_REQVERIF_ACC_SUCC_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 6 + CRC_LENGTH)

/**
 * Length of the Request Verification Acceptance Failed out-going report packet.
 */
#define CRPS_REQVERIF_ACC_FAIL_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 11 + CRC_LENGTH)

/**
 * Length of the Request Verification Start Successful out-going report packet.
 */
#define CRPS_REQVERIF_START_SUCC_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 6 + CRC_LENGTH)

/**
 * Length of the Request Verification Start Failed out-going report packet.
 */
#define CRPS_REQVERIF_START_FAIL_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 11 + CRC_LENGTH)

/**
 * Length of the Request Verification Progress Successful out-going report packet.
 */
#define CRPS_REQVERIF_PROG_SUCC_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 8 + CRC_LENGTH)

/**
 * Length of the Request Verification Progress Failed out-going report packet.
 */
#define CRPS_REQVERIF_PROG_FAIL_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 13 + CRC_LENGTH)

/**
 * Length of the Request Verification Termination Successful out-going report packet.
 */
#define CRPS_REQVERIF_TERM_SUCC_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 6 + CRC_LENGTH)

/**
 * Length of the Request Verification Termination Failed out-going report packet.
 */
#define CRPS_REQVERIF_TERM_FAIL_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 11 + CRC_LENGTH)

/**
 * Length of the Request Verification Termination Failed out-going report packet.
 */
#define CRPS_REQVERIF_REROUT_FAIL_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 11 + CRC_LENGTH)

/**
 * Length of the Housekeeping Create a Housekeeping Parameter Report Structure command packet.
 */
#define CRPS_HK_CREATE_HKSTRUCT_CMD_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10 + CRC_LENGTH)

/**
 * Length of the Housekeeping Create a Diagnostic Parameter Report Structure command packet.
 */
#define CRPS_HK_CREATE_DIAGSTRUCT_CMD_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10 + CRC_LENGTH)

/**
 * Length of the Housekeeping Delete a Housekeeping Parameter Report Structure command packet.
 */
#define CRPS_HK_DELETE_HKSTRUCT_CMD_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10 + CRC_LENGTH)

/**
 * Length of the Housekeeping Delete a Diagnostic Parameter Report Structure command packet.
 */
#define CRPS_HK_DELETE_DIAGSTRUCT_CMD_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10 + CRC_LENGTH)

/**
 * Length of the Housekeeping Enable Periodic Generation of a Housekeeping Parameter Report Structure command packet.
 */
#define CRPS_HK_ENABLE_PERIODICHK_CMD_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10 + CRC_LENGTH)

/**
 * Length of the Housekeeping Disable Periodic Generation of a Housekeeping Parameter Report Structure command packet.
 */
#define CRPS_HK_DISABLE_PERIODICHK_CMD_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10 + CRC_LENGTH)

/**
 * Length of the Housekeeping Enable Periodic Generation of a Diagnostic Parameter Report Structure command packet.
 */
#define CRPS_HK_ENABLE_PERIODICDIAG_CMD_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10 + CRC_LENGTH)

/**
 * Length of the Housekeeping Disable Periodic Generation of a Diagnostic Parameter Report Structure command packet.
 */
#define CRPS_HK_DISABLE_PERIODICDIAG_CMD_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10 + CRC_LENGTH)

/**
 * Length of the Housekeeping Report Housekeeping Parameter Report Structure command packet.
 */
#define CRPS_HK_HKREP_STRUCT_CMD_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10 + CRC_LENGTH)

/**
 * Length of the Housekeeping Housekeeping Parameter Report Structure Report out-going report packet.
 */
#define CRPS_HK_HKREP_STRUCT_REP_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10 + CRC_LENGTH)

/**
 * Length of the Housekeeping Report Diagnostic Parameter Report Structure command packet.
 */
#define CRPS_HK_DIAGREP_STRUCT_CMD_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10 + CRC_LENGTH)

 /**
 * Length of the Housekeeping Diagnostic Parameter Report Structure Report out-going report packet.
 */
#define CRPS_HK_DIAGREP_STRUCT_REP_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10 + CRC_LENGTH)

/**
 * Length of the Housekeeping Housekeeping Parameter Report out-going report packet.
 */
#define CRPS_HK_HKPARAM_REP_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10 + CRC_LENGTH)

 /**
 * Length of the Housekeeping Diagnostic Parameter Report out-going report packet.
 */
#define CRPS_HK_DIAGPARAM_REP_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10 + CRC_LENGTH)

/**
 * Length of the Housekeeping Generate One-Shot Report for Housekeeping Parameters command packet.
 */
#define CRPS_HK_HKONESHOT_CMD_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10 + CRC_LENGTH)

 /**
 * Length of the Housekeeping Generate One-Shot Report for Diagnostic Parameters command packet.
 */
#define CRPS_HK_DIAGONESHOT_CMD_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10 + CRC_LENGTH)


/**
 * Length of the Event Report out-going report packet.
 */
#define CRPS_EVT__REP_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 10 + CRC_LENGTH) /*TODO .. hier noch die korrekten längen angeben!!*/

/**
 * Length of the Large Packet Transfer out-going report packet.
 */
#define CRPS_LPT__REP_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 982 + CRC_LENGTH) /*TODO .. hier noch die korrekten längen angeben!!*/

#define CRPS_LPT_UPABORT_REP_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 6 + CRC_LENGTH)


/**
 * Length of the Perform Connection Test Are-You-Alive in-coming command packet.
 */
#define CRPS_TEST_AREYOUALIVE_CONNECTION_CMD_LENGTH (OFFSET_PAR_LENGTH_IN_CMD_PCKT + CRC_LENGTH)

/**
 * Length of the Link Connection Are-You-Alive Report out-going report packet.
 */
#define CRPS_TEST_AREYOUALIVE_CONNECTION_REP_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + CRC_LENGTH)

/**
 * Length of the Perform Connection Test On-Board Connection in-coming command packet.
 */
#define CRPS_TEST_ONBOARD_CONNECTION_CMD_LENGTH (OFFSET_PAR_LENGTH_IN_CMD_PCKT + 2 + CRC_LENGTH)

/**
 * Length of the Link Connection On-Board Connection Report out-going report packet.
 */
#define CRPS_TEST_ONBOARD_CONNECTION_REP_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 2 + CRC_LENGTH)



#endif /* CRPS_CONSTANTS_H */



