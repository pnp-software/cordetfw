/**
 * @file
 * @ingroup pcktGroup
 * Implementation of Packet Queue Management.
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

#include <stdlib.h>
#include "../CrFwConstants.h"
#include "CrFwPckt.h"
#include "CrFwPcktQueue.h"

/*-----------------------------------------------------------------------------------------*/
CrFwPckt_t CrFwPcktQueuePop(CrFwPcktQueue_t pcktQueue) {
	CrFwCounterU1_t posOldest;
	CrFwPckt_t oldestPckt;

	if (!pcktQueue->isEmpty) {
		posOldest = pcktQueue->oldestItem;
		oldestPckt = pcktQueue->pckt[posOldest];
		if (posOldest < (pcktQueue->size-1))
			pcktQueue->oldestItem++;
		else
			pcktQueue->oldestItem = 0;
		if (pcktQueue->oldestItem == pcktQueue->nextFreeItem)
			pcktQueue->isEmpty = 1;
		return oldestPckt;
	} else
		return NULL;
}

/*-----------------------------------------------------------------------------------------*/
CrFwPckt_t CrFwPcktQueueGetOldest(CrFwPcktQueue_t pcktQueue) {
	if (!pcktQueue->isEmpty)
		return pcktQueue->pckt[pcktQueue->oldestItem];
	else
		return NULL;
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwPcktQueuePush(CrFwPcktQueue_t pcktQueue, CrFwPckt_t pckt) {
	if (pcktQueue->isEmpty == 1) {
		pcktQueue->pckt[0] = pckt;
		pcktQueue->nextFreeItem = 1;
		pcktQueue->oldestItem =0;
		pcktQueue->isEmpty = 0;
		return 1;
	}

	if (pcktQueue->nextFreeItem == pcktQueue->oldestItem)
		return 0;

	pcktQueue->pckt[pcktQueue->nextFreeItem] = pckt;
	if (pcktQueue->nextFreeItem < (pcktQueue->size-1))
		pcktQueue->nextFreeItem++;
	else
		pcktQueue->nextFreeItem = 0;
	return 1;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktQueueReset(CrFwPcktQueue_t pcktQueue) {
	CrFwCounterU1_t i;

	if (pcktQueue->isEmpty == 1)
		return;

	if (pcktQueue->oldestItem < pcktQueue->nextFreeItem) {
		for (i=pcktQueue->oldestItem; i<pcktQueue->nextFreeItem; i++)
			CrFwPcktRelease(pcktQueue->pckt[i]);
		pcktQueue->isEmpty = 1;
		return;
	}

	for (i=pcktQueue->oldestItem; i<pcktQueue->size; i++)
		CrFwPcktRelease(pcktQueue->pckt[i]);
	for (i=0; i<pcktQueue->nextFreeItem; i++)
		CrFwPcktRelease(pcktQueue->pckt[i]);
	pcktQueue->isEmpty = 1;
	return;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktQueueInit(CrFwPcktQueue_t pcktQueue, CrFwCounterU1_t size) {
	CrFwCounterU1_t i;

	if (pcktQueue->pckt != NULL)
		return;

	pcktQueue->pckt = malloc(size*sizeof(CrFwPckt_t));
	for (i=0; i<size; i++)
		pcktQueue->pckt[i] = NULL;
	pcktQueue->isEmpty = 1;
	pcktQueue->nextFreeItem = 0;
	pcktQueue->oldestItem = 0;
	pcktQueue->size = size;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktQueueShutdown(CrFwPcktQueue_t pcktQueue) {
	CrFwPcktQueueReset(pcktQueue);
	free(pcktQueue->pckt);
	pcktQueue->pckt = NULL;
	pcktQueue->size = 0;
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwPcktQueueIsEmpty(CrFwPcktQueue_t pcktQueue) {
	return pcktQueue->isEmpty;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwPcktQueueGetNOfPckts(CrFwPcktQueue_t pcktQueue) {

	if (pcktQueue->isEmpty == 1)
		return 0;

	if (pcktQueue->oldestItem < pcktQueue->nextFreeItem)
		return (CrFwCounterU1_t)(pcktQueue->nextFreeItem - pcktQueue->oldestItem);

	return (CrFwCounterU1_t)(pcktQueue->size - (pcktQueue->oldestItem - pcktQueue->nextFreeItem));
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrFwPcktQueueGetSize(CrFwPcktQueue_t pcktQueue) {
	return pcktQueue->size;
}
