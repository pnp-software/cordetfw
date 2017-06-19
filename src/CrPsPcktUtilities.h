/**
 * @file CrPsPcktUtilities.h
 * @ingroup CrIaDemo
 *
 * 
 *
 * @author C. Reimers and M. Rockenbauer 19.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#ifndef CRPSPCKTUTILITIES_H
#define CRPSPCKTUTILITIES_H

/* Includes */
#include <CrFwConstants.h>

/**
 * The size of a small packet in bytes.
 */
#define CR_APP1_MAX_SIZE_PCKT_SMALL 100

/**
 * The size of a large packets in bytes. This is the maximum size of a TM/TC
 * packet.
 */
#define CR_APP1_MAX_SIZE_PCKT_LARGE 1048

/**
 * The number of pre-allocated small packets.
 */
#define CR_APP1_NOF_PCKT_SMALL 73 /* value from DD-001 issue 2.2 p 32 */

/**
 * The number of pre-allocated large packets.
 */
#define CR_APP1_NOF_PCKT_LARGE 164 /* value from DD-001 issue 2.2 p 32 */

/** Offset of the packet id field. */
#define OFFSET_ID_FIELD 0

/** Offset of the packet sequence control field. */
#define OFFSET_SEQ_CTRL_FIELD 2

/** Offset of the length field. */
#define OFFSET_LENGTH_FIELD 4

/** Offset of the data field for TC/TM */
#define OFFSET_DATA_FIELD_TC_TM 6

/** Offset of the application data for commands. */
#define OFFSET_SRC_DATA_CMD 11

/** Offset of the application data for reports. */
#define OFFSET_SRC_DATA_REP 17

/** Offset for the parameter length */
#define OFFSET_PAR_LENGTH_TC 10
#define OFFSET_PAR_LENGTH_TM 16

/** Length of the packet without the packet data field */
#define SRC_PCKT_HDR_LENGTH  6GetP

/** Defines for the version number within the packet id field */
#define VERSION_MASK          0xE0
#define VERSION_SHIFT         5
/** Defines for the packet type within the packet id field */
#define PCKT_TYPE_MASK        0x10
#define PCKT_TYPE_SHIFT       4
/** Defines for the data field header flag within the packet id field */
#define HDR_FLAG_MASK         0x08
#define HDR_FLAG_SHIFT        3
/** Defines for the APID (application process id) */
#define PID0_MASK             0x07
#define PID1_MASK             0xF0
#define PID1_SHIFT            4
#define PCAT_MASK             0x0F
#define PCAT_OFFSET           1

/** Mask of the sequence flags within the packet sequence control field. */
#define SEQ_FLAGS_MASK        0xC0
#define SEQ_FLAGS_SHIFT       6
/** Mask of the sequence count within the packet sequence control field. */
#define SEQ_COUNT_MASK        0x3FFF

/** Mask of the CCSDS secondary header flag within the data field header. */
#define CCSDS_MASK            0x80
#define CCSDS_SHIFT           7
/** Mask of the PUS version within the data field header. */
#define PUS_VER_MASK          0x70
#define PUS_VER_SHIFT         4
/** Mask for all acknolegde flags in a TC */
#define ACK_MASK              0x0F
/** Mask of the ack flag A (acceptance) within the data field header. */
#define ACK_A_MASK            0x01
#define ACK_A_SHIFT           0
/** Mask of the ack flag SE (start execution) within the data field header. */
#define ACK_SE_MASK           0x02
#define ACK_SE_SHIFT          1
/** Mask of the ack flag PE (progress execution) within the data field header. */
#define ACK_PE_MASK           0x04
#define ACK_PE_SHIFT          2
/** Mask of the ack flag CE (completion execution) within the data field header. */
#define ACK_CE_MASK           0x08
#define ACK_CE_SHIFT          3
/** Offset of the service type in the data field header */
#define SRV_TYPE_OFFSET       1
/** Offset of the service subtype in the data field header */
#define SRV_SUBTYPE_OFFSET    2
/** Offset of the source id (in TC) and destination id (TM) in the data field header */
#define SRC_DEST_OFFSET       3
/** Offset of the SC Time field in the data field header */
#define SC_TIME_OFFSE
/*Functions*/
/* ------------------------------------------------------------------------------------ */

CrFwDestSrc_t CrFwPcktGetPid(CrFwPckt_t pckt);

void CrFwPcktSetPid(CrFwPckt_t pckt, CrFwDestSrc_t pid);

#endif /* CRPSPCKTUTILITIES_H */