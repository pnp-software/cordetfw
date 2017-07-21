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



/* ######################################################################################
 * ### Definition of Data Structures
 * ######################################################################################
 */

typedef struct {
  FwSmDesc_t smDesc;
  unsigned short ushortParam1;
  unsigned short ushortParam2;
} prData_t;


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
#define OFFSET_PAR_LENGTH_OUT_REP_PCKT 16

/**
 * The length offset for the in-coming command.
 */
#define OFFSET_PAR_LENGTH_IN_CMD_PCKT 10

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
#define CRPS_REQVERIF_ACC_SUCC_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 2 + CRC_LENGTH)

/**
 * Length of the Request Verification Acceptance Failed out-going report packet.
 */
#define CRPS_REQVERIF_ACC_FAIL_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 11 + CRC_LENGTH)

/**
 * Length of the Request Verification Start Successful out-going report packet.
 */
#define CRPS_REQVERIF_START_SUCC_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 2 + CRC_LENGTH)

/**
 * Length of the Request Verification Start Failed out-going report packet.
 */
#define CRPS_REQVERIF_START_FAIL_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 11 + CRC_LENGTH)

/**
 * Length of the Request Verification Progress Successful out-going report packet.
 */
#define CRPS_REQVERIF_PROG_SUCC_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 4 + CRC_LENGTH)

/**
 * Length of the Request Verification Progress Failed out-going report packet.
 */
#define CRPS_REQVERIF_PROG_FAIL_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 13 + CRC_LENGTH)

/**
 * Length of the Request Verification Termination Successful out-going report packet.
 */
#define CRPS_REQVERIF_TERM_SUCC_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 2 + CRC_LENGTH)

/**
 * Length of the Request Verification Termination Failed out-going report packet.
 */
#define CRPS_REQVERIF_TERM_FAIL_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 11 + CRC_LENGTH)

/**
 * Length of the Request Verification Termination Failed out-going report packet.
 */
#define CRPS_REQVERIF_REROUT_FAIL_LENGTH (OFFSET_PAR_LENGTH_OUT_REP_PCKT + 11 + CRC_LENGTH)

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



