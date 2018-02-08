/**
 * @file
 * @ingroup pcktGroup
 * Definition and management of packet queues.
 * An application instantiated from the CORDET Framework interacts with other
 * framework applications by exchanging with them commands and reports.
 * When commands and reports travel from one application to another, they
 * take the form of packets.
 *
 * A packet is an ordered sequence of bytes which contain all the information
 * required to reconstruct a report or a command.
 * Although the exact layout of packets is not defined at framework level,
 * the framework defines in <code>CrFwPckt.h</code> an interface for creating and
 * accessing a packet.
 *
 * Components which send or receive packets need to manage packet queues.
 * A packet queue is a data structure which holds a set of packets and manages
 * them in FIFO order.
 * This file defines a type for packet queues and defines the operations
 * for managing a packet queue.
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

#ifndef CRFW_PACKETQUEUE_H_
#define CRFW_PACKETQUEUE_H_

/* Include Framework Files */
#include "CrFwConstants.h"
/* Include Configuration Files */
#include "CrFwUserConstants.h"

/**
 * Pop a packet from the packet queue.
 * If the packet queue is not empty, this function returns the oldest packet
 * in the queue.
 * If the packet queue is empty, this function returns NULL.
 * @param pcktQueue the packet queue.
 * @return the oldest packet on the packet or NULL if the packet queue was empty.
 */
CrFwPckt_t CrFwPcktQueuePop(CrFwPcktQueue_t pcktQueue);

/**
 * Return the oldest packet from the queue without removing it from the queue.
 * If the packet queue is not empty, this function returns the oldest packet
 * in the queue but does not remove the packet from queue.
 * If the packet queue is empty, this function returns NULL.
 * @param pcktQueue the packet queue.
 * @return the oldest packet on the packet or NULL if the packet queue was empty.
 */
CrFwPckt_t CrFwPcktQueueGetOldest(CrFwPcktQueue_t pcktQueue);

/**
 * Push a packet onto the packet queue.
 * If the packet queue is not full, this function adds the packet to the packet
 * queue and return 1.
 * If the packet queue is full, this function does nothing and returns 0.
 * @param pcktQueue the packet queue
 * @param pckt the packet to be pushed onto the packet queue.
 * @return 1 if the push operation was successful, or 0 if the push operation failed
 * because the packet queue was full.
 */
CrFwBool_t CrFwPcktQueuePush(CrFwPcktQueue_t pcktQueue, CrFwPckt_t pckt);

/**
 * Initializes the packet queue.
 * This function allocates the memory for the packet queue and then initializes
 * it to represent an empty packet queue.
 * The initialization of a packet queue can only be done once.
 * If the packet queue has already been initialized, this function returns without
 * doing anything.
 * The situation where the memory allocation operation for the packet queue fails
 * is not handled and will result in undefined behaviour (probably, a run-time exception).
 * @param pcktQueue the packet queue.
 * @param size the size of the packet queue
 */
void CrFwPcktQueueInit(CrFwPcktQueue_t pcktQueue, CrFwCounterU1_t size);

/**
 * Reset the packet queue.
 * This function clears all entries in the packet queue and releases all packets
 * which are in the packet queue.
 * @param pcktQueue the packet queue.
 */
void CrFwPcktQueueReset(CrFwPcktQueue_t pcktQueue);

/**
 * Shutdown the packet queue.
 * This function resets the packet queue (using function <code>::CrFwPcktQueueReset</code>)
 * and then releases the memory which allocated for the packet queue through function
 * <code>::CrFwPcktQueueInit</code>.
 * @param pcktQueue the packet queue.
 */
void CrFwPcktQueueShutdown(CrFwPcktQueue_t pcktQueue);

/**
 * Return 1 if the packet queue is empty and 0 otherwise.
 * @param pcktQueue the packet queue.
 * @return 1 if the packet queue is empty and 0 otherwise.
 */
CrFwBool_t CrFwPcktQueueIsEmpty(CrFwPcktQueue_t pcktQueue);

/**
 * Return the number of packets currently in the packet queue.
 * @param pcktQueue the packet queue
 * @return the number of packets currently in the packet queue.
 */
CrFwCounterU1_t CrFwPcktQueueGetNOfPckts(CrFwPcktQueue_t pcktQueue);

/**
 * Return the size of the packet queue.
 * @param pcktQueue the packet queue
 * @return the packet queue size.
 */
CrFwCounterU1_t CrFwPcktQueueGetSize(CrFwPcktQueue_t pcktQueue);

#endif /* CRFW_PACKETQUEUE_H_ */
