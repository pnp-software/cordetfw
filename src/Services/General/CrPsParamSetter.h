/**
 * @file CrPsParamSetter.h
 *
 * Declaration of the setter operations for all parameters of all out-going packets.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#ifndef CRPS_PARAM_SETTER_H
#define CRPS_PARAM_SETTER_H

#include <FwSmCore.h>
#include <CrFwConstants.h>

/* ------------------------------------------------------------------------------------ */

/**
 * Put Function 8 Bit
 * Puts a value to the destination using a specific bitOffset
 * @param value The value to be put into the destination
 * @param bitOffset Offset in bits
 * @param dest The destination where to set the value
 */
void PutBit8 (unsigned char value, unsigned int bitOffset, unsigned char *dest);

/**
 * Put Function 8 Bit for n bits
 * Puts n values to the destination using a specific bitOffset
 * uses n times the PutBit8 functio
 * @param value The values to be put into the destination
 * @param bitOffset Offset in bits
 * @param dest The destination where to set the value
 */
void PutNBits8 (unsigned int value, unsigned int bitOffset, unsigned int nbits, unsigned char *dest);

/* ------------------------------------------------------------------------------------ */

/**
 * Sets the value of the parameter tcPacketId
 * @param smDesc the descriptor of the Base State Machine
 * @param tcPacketId the TC packet ID
 */
void CrPsServReqVerifAccSuccParamSetTcPacketId(FwSmDesc_t smDesc, unsigned short tcPacketId);

/**
 * Sets the value of the parameter tcPacketSeqCtrl
 * @param smDesc the descriptor of the Base State Machine
 * @param tcPacketId the TC packet Sequence Ctrl
 */
void CrPsServReqVerifAccSuccParamSetTcPacketSeqCtrl(FwSmDesc_t smDesc, unsigned short tcPacketSeqCtrl);

/* ------------------------------------------------------------------------------------ */

/**
 * Sets the value of the parameter appId
 * @param smDesc the descriptor of the Base State Machine
 * @param appId the Application ID
 */
void CrPsServTestOnBoardConnectParamSetAppId(FwSmDesc_t smDesc, unsigned short appId);

/* ------------------------------------------------------------------------------------ */

/**
 * Generic setter
 * Set data at specific position in data segment of PUS packet
 * @param smDesc the descriptor of the Base State Machine
 * @param ucharValue unsigned char value to be set
 * @param pos the position where to set the value
 */
void CrPsSetUCharValue(FwSmDesc_t smDesc, unsigned char ucharValue, unsigned int pos);

/**
 * Generic setter
 * Set data at specific position in data segment of PUS packet
 * @param smDesc the descriptor of the Base State Machine
 * @param ushortValue the unisgned short value to be set
 * @param pos the position where to set the value
 */
void CrPsSetUShortValue(FwSmDesc_t smDesc, unsigned short ushortValue, unsigned int pos);

/**
 * Generic setter
 * Set data at specific position in data segment of PUS packet
 * @param smDesc the descriptor of the Base State Machine
 * @param uintValue the unsigned integer value to be set
 * @param pos the position where to set the value
 */
void CrPsSetUIntValue(FwSmDesc_t smDesc, unsigned int uintValue, unsigned int pos);

/* ------------------------------------------------------------------------------------ */

#endif /* CRPS_PARAM_SETTER_H */
