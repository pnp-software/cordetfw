/**
 * @file
 * @ingroup crOpenIfGroup
 * Interface for creating and accessing a report or command packet.
 * An application instantiated from the CORDET Framework interacts with other
 * framework applications by exchanging with them commands and reports.
 * When commands and reports travel from one application to another, they
 * take the form of packets.
 *
 * A packet is an ordered sequence of bytes which contain all the information
 * required to reconstruct a report or a command.
 * Although the exact layout of packets is not defined at framework level,
 * the framework defines, through this header file, an interface for creating and
 * accessing the data in a packet.
 *
 * This interface defines a packet factory, namely a function which allows
 * a new packet to be created and an existing packet to be released.
 *
 * A packet encapsulates either a command or a report.
 * This interface defines functions through which the attributes of the encapsulated
 * command or report can be retrieved from a packet or can be set in a packet.
 * For attributes other than the command or report parameters, getter and setter
 * functions are defined.
 * For the command or report parameters, getter functions are provided which return:
 * the start address of the parameter area of the packet and its size.
 * The parameter area is the part of a packet which is reserved to the storage
 * of the parameters of the command or report encapsulated by the packet.
 *
 * In general, the implementation of this interface is entirely application-specific
 * but a simple default implementation is provided in <code>CrFwPckt.c</code>.
 * This default implementation is primarily intended for testing and demonstration
 * purposes.
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */
 
#ifndef CRFW_PACKET_H_
#define CRFW_PACKET_H_

/* Include Framework Files */
#include "CrFwConstants.h"
/* Include Configuration Files */
#include "CrFwUserConstants.h"

/**
 * Make function for command or report packets.
 * This function returns an unconfigured packet of the specified length.
 * An unconfigured packet of length L consists of a sequence of L bytes.
 * The function allocates the memory for the packet and returns a pointer to the
 * allocated memory.
 *
 * The memory allocated to the packet remains reserved to the packet until the
 * packet is released through a call to function <code>::CrFwPcktRelease</code>.
 * The content of the packet returned by this function is undefined.
 * The way the memory is allocated and released is implementation-specific.
 *
 * If the allocation of the memory for the new packet failed, the function returns
 * NULL.
 * Depending on the implementation, allocation memory failure may result in
 * the application error code being set to <code>crPcktAllocationFail</code>.
 *
 * The packet length must be a positive integer.
 * If a negative or a zero value is used, the function returns NULL.
 * Depending on the implementation, this may also result in
 * the application error code being set to <code>crPcktAllocationFail</code>.
 * @param pcktLength the length of the packet in bytes (a positive integer)
 * @return a new packet or NULL if it was not possible to allocate the memory
 * for the packet or if the packet length was not a positive integer
 */
CrFwPckt_t CrFwPcktMake(CrFwPcktLength_t pcktLength);

/**
 * Release function for command or report packets.
 * The argument of this function must be a packet which was created using function
 * <code>CrFwPcktMake</code>.
 * This function releases the memory which was allocated to the argument packet.
 * After this function is called, the argument packet cannot be used.
 *
 * An attempt to release a packet which had already been released, or to release a
 * non-existent packet results in the application
 * error code being set to: <code>::crPcktRelErr</code>.
 * @param pckt the packet to be released
 */
void CrFwPcktRelease(CrFwPckt_t pckt);

/**
 * Check whether a packet of a specified length is available.
 * A packet of length L is available if a call to function <code>::CrFwPcktMake</code>
 * with argument L would return a non-NULL value.
 * Applications typically implement the <code>CrFwPckt.h</code> interface to manage a pool of
 * pre-allocated memory from which packets are allocated using function
 * <code>::CrFwPcktMake</code> and are released using function <code>::CrFwPcktRelease</code>.
 * This function does not change the state of the pool from which the packets
 * are allocated. It only verifies whether the allocation of a packet of a given
 * length would be possible at the time the function is called.
 *
 * The packet length must be a positive integer.
 * If a negative or a zero value is used, the function returns false.
 * @param pcktLength the length of the packet in bytes (a positive integer)
 * @return true if a packet of the specified length is available, false otherwise
 * of if the length is not a positive integer
 */
CrFwBool_t CrFwPcktIsAvail(CrFwPcktLength_t pcktLength);

/**
 * Return the number of packets which are currently allocated.
 * This function returns the number of packets which have been successfully
 * allocated through calls to <code>::CrFwPcktMake</code> and have not yet been
 * released through calls to <code>::CrFwPcktRelease</code>.
 * @return the number of packets which are currently allocated.
 */
CrFwCounterU2_t CrFwPcktGetNOfAllocated();

/**
 * Return the maximum length of a packet in number of bytes.
 * Some implementation may restrict the maximum length of a packet.
 * This function allows this maximum length to be retrieved.
 * If the function returns a value of zero, then no restriction on the length of
 * a packet is defined by the implementation.
 * @return the maximum length of a packet in number of bytes or zero if no restriction
 * on the packet length exists.
 */
CrFwPcktLength_t CrFwPcktGetMaxLength();

/**
 * Return the type of a packet (either a command packet or a report packet).
 * @param pckt the packet
 * @return the type of the entity (a command or a report) encapsulated by the packet.
 */
CrFwCmdRepType_t CrFwPcktGetCmdRepType(CrFwPckt_t pckt);

/**
 * Set the type of a packet (either a command packet or a report packet).
 * @param pckt the packet
 * @param type the type of the entity (a command or a report) encapsulated by the packet.
 */
void CrFwPcktSetCmdRepType(CrFwPckt_t pckt, CrFwCmdRepType_t type);

/**
 * Return the length (in number of bytes) of a packet.
 * @param pckt the packet.
 * @return the length (in number of bytes) of the packet.
 */
CrFwPcktLength_t CrFwPcktGetLength(CrFwPckt_t pckt);

/**
 * Return the sequence counter of the command or report encapsulated in a packet.
 * @param pckt the packet.
 * @return the sequence counter.
 */
CrFwSeqCnt_t CrFwPcktGetSeqCnt(CrFwPckt_t pckt);

/**
 * Set the sequence counter of the command or report encapsulated in a packet.
 * @param pckt the packet.
 * @param seqCnt the sequence counter.
 */
void CrFwPcktSetSeqCnt(CrFwPckt_t pckt, CrFwSeqCnt_t seqCnt);

/**
 * Return the time stamp of the command or report encapsulated in a packet.
 * @param pckt the packet.
 * @return the time stamp.
 */
CrFwTimeStamp_t CrFwPcktGetTimeStamp(CrFwPckt_t pckt);

/**
 * Set the time stamp of the command or report encapsulated in a packet.
 * @param pckt the packet.
 * @param timeStamp the time stamp.
 */
void CrFwPcktSetTimeStamp(CrFwPckt_t pckt, CrFwTimeStamp_t timeStamp);

/**
 * Return the discriminant of the command or report encapsulated in a packet.
 * Not all commands and reports have a discriminant field.
 * If the argument packet holds a command or report which does not have a discriminant
 * field, the behaviour of this function is undefined.
 * @param pckt the packet.
 * @return the discriminant.
 */
CrFwDiscriminant_t CrFwPcktGetDiscriminant(CrFwPckt_t pckt);

/**
 * Set the discriminant of the command or report encapsulated in a packet.
 * Not all commands and reports have a discriminant field.
 * If the argument packet holds a command or report which does not have a discriminant
 * field, the behaviour of this function is undefined.
 * @param pckt the packet.
 * @param discriminant the discriminant.
 */
void CrFwPcktSetDiscriminant(CrFwPckt_t pckt, CrFwDiscriminant_t discriminant);

/**
 * Set the service type of the command or report encapsulated in a packet.
 * @param pckt the packet.
 * @param servType the service type.
 */
void CrFwPcktSetServType(CrFwPckt_t pckt, CrFwServType_t servType);

/**
 * Return the service type of the command or report encapsulated in a packet.
 * @param pckt the packet.
 * @return the service type.
 */
CrFwServType_t CrFwPcktGetServType(CrFwPckt_t pckt);

/**
 * Set the service sub-type of the command or report encapsulated in a packet.
 * @param pckt the packet.
 * @param servSubType the service sub-type.
 */
void CrFwPcktSetServSubType(CrFwPckt_t pckt, CrFwServSubType_t servSubType);

/**
 * Return the service sub-type of the command or report encapsulated in a packet.
 * @param pckt the packet.
 * @return the service sub-type.
 */
CrFwServSubType_t CrFwPcktGetServSubType(CrFwPckt_t pckt);

/**
 * Set the group of the command/report encapsulated in a packet.
 * @param pckt the packet.
 * @param group the destination or source group of the packet.
 */
void CrFwPcktSetGroup(CrFwPckt_t pckt, CrFwGroup_t group);

/**
 * Return the group of the command/report encapsulated in a packet.
 * @param pckt the packet.
 * @return the destination or source group of the packet.
 */
CrFwGroup_t CrFwPcktGetGroup(CrFwPckt_t pckt);

/**
 * Set the destination of the command or report encapsulated in a packet.
 * @param pckt the packet.
 * @param dest the destination of the packet.
 */
void CrFwPcktSetDest(CrFwPckt_t pckt, CrFwDestSrc_t dest);

/**
 * Return the destination of the command or report encapsulated in a packet.
 * @param pckt the packet.
 * @return the destination of the packet.
 */
CrFwDestSrc_t CrFwPcktGetDest(CrFwPckt_t pckt);

/**
 * Set the source of the command or report encapsulated in a packet.
 * @param pckt the packet.
 * @param src the source of the packet.
 */
void CrFwPcktSetSrc(CrFwPckt_t pckt, CrFwDestSrc_t src);

/**
 * Return the source of the command or report encapsulated in a packet.
 * @param pckt the packet.
 * @return the source of the packet.
 */
CrFwDestSrc_t CrFwPcktGetSrc(CrFwPckt_t pckt);

/**
 * Set the command or report identifier in the command or report encapsulated in a packet.
 * @param pckt the packet.
 * @param id the command or report identifier.
 */
void CrFwPcktSetCmdRepId(CrFwPckt_t pckt, CrFwInstanceId_t id);

/**
 * Return the command or report identifier of the command or report encapsulated in a packet.
 * @param pckt the packet.
 * @return the command or report identifier.
 */
CrFwInstanceId_t CrFwPcktGetCmdRepId(CrFwPckt_t pckt);

/**
 * Compute the CRC in the command or report encapsulated in a packet.
 * @param pckt the packet.
 * @return the command or report CRC.
 */
CrFwCrc_t CrFwPcktComputeCrc(CrFwPckt_t pckt);

/**
 * Set the CRC in the command or report encapsulated in a packet.
 * @param pckt the packet.
 * @param crc the command or report CRC.
 */
void CrFwPcktSetCrc(CrFwPckt_t pckt, CrFwCrc_t crc);

/**
 * Return the CRC of the command or report encapsulated in a packet.
 * @param pckt the packet.
 * @return the command or report CRC.
 */
CrFwCrc_t CrFwPcktGetCrc(CrFwPckt_t pckt);

/**
 * Set the acknowledge level for the command encapsulated in a packet.
 * If the packet on which this function is called does not encapsulate a command, nothing
 * is done.
 * @param pckt the packet.
 * @param accept 1 if acknowledge of command acceptance is desired, 0 otherwise.
 * @param start 1 if acknowledge of command start is desired, 0 otherwise.
 * @param progress 1 if acknowledge of command progress is desired, 0 otherwise.
 * @param term 1 if acknowledge of command acceptance termination is desired, 0 otherwise.
 */
void CrFwPcktSetAckLevel(CrFwPckt_t pckt, CrFwBool_t accept, CrFwBool_t start,
                         CrFwBool_t progress, CrFwBool_t term);

/**
 * Return the acknowledge level for command acceptance for the command encapsulated in the
 * packet.
 * If the packet does not hold a command, the behaviour of the function is undefined.
 * @param pckt a packet encapsulating a command.
 * @return 1 if command acceptance is to be acknowledged, 0 otherwise.
 */
CrFwBool_t CrFwPcktIsAcceptAck(CrFwPckt_t pckt);

/**
 * Return the acknowledge level for command start for the command encapsulated in the
 * packet.
 * If the packet does not hold a command, the behaviour of the function is undefined.
 * @param pckt a packet encapsulating a command.
 * @return 1 if command start is to be acknowledged, 0 otherwise.
 */
CrFwBool_t CrFwPcktIsStartAck(CrFwPckt_t pckt);

/**
 * Return the acknowledge level for command progress for the command encapsulated in the
 * packet.
 * If the packet does not hold a command, the behaviour of the function is undefined.
 * @param pckt a packet encapsulating a command.
 * @return 1 if command progress is to be acknowledged, 0 otherwise.
 */
CrFwBool_t CrFwPcktIsProgressAck(CrFwPckt_t pckt);

/**
 * Return the acknowledge level for command termination for the command encapsulated in the
 * packet.
 * If the packet does not hold a command, the behaviour of the function is undefined.
 * @param pckt a packet encapsulating a command.
 * @return 1 if command termination is to be acknowledged, 0 otherwise.
 */
CrFwBool_t CrFwPcktIsTermAck(CrFwPckt_t pckt);

/**
 * Return the start address of the packet's parameter area.
 * The parameter area is the part of a packet which is reserved to the storage
 * of the parameters of the command or report encapsulated by the packet.
 * The parameter area consists of an uninterrupted sequence of bytes.
 * The size of the parameter area is returned by function <code>::CrFwPcktGetParLength</code>.
 * @param pckt a packet encapsulating a command or a report.
 * @return the start address of the packet's parameter area.
 */
char* CrFwPcktGetParStart(CrFwPckt_t pckt);

/**
 * Return the length in bytes of the packet's parameter area.
 * The parameter area is the part of a packet which is reserved to the storage
 * of the parameters of the command or report encapsulated by the packet.
 * The parameter area consists of an uninterrupted sequence of bytes.
 * The start address of the parameter area is returned by function <code>::CrFwPcktGetParStart</code>.
 * @param pckt a packet encapsulating a command or a report.
 * @return the length in bytes of the packet's parameter area.
 */
CrFwPcktLength_t CrFwPcktGetParLength(CrFwPckt_t pckt);


#endif /* CRFW_PACKET_H_ */
