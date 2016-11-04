/**
 * @file
 *
 * Implementation of test cases for default implementation of packets.
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of CORDET Framework.
 *
 * CORDET Framework is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CORDET Framework is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CORDET Framework.  If not, see <http://www.gnu.org/licenses/>.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#include <stdio.h>
#include <stdlib.h>
#include "CrFwPacketTestCases.h"
/* Include FW Profile Files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include Framework Files */
#include "Pckt/CrFwPckt.h"
#include "Pckt/CrFwPcktQueue.h"
#include "CrFwConstants.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"

CrFwBool_t CrFwPacketTestCase1() {
	CrFwPckt_t pckt;

	/* Attempt to create a packet with illegal length */
	pckt = CrFwPcktMake((CrFwPcktLength_t)(CrFwPcktGetMaxLength()+1));
	if ((pckt != NULL) || (CrFwGetAppErrCode() != crPcktAllocationFail))
		return 0;
	CrFwSetAppErrCode(crNoAppErr); 	/* reset application error code */

	pckt = CrFwPcktMake(0);
	if ((pckt != NULL) || (CrFwGetAppErrCode() != crPcktAllocationFail))
		return 0;
	CrFwSetAppErrCode(crNoAppErr); 	/* reset application error code */

	/* Make a new packet */
	pckt = CrFwPcktMake(CrFwPcktGetMaxLength());
	if (pckt == NULL)
		return 0;

	/* Check packet length */
	if (CrFwPcktGetLength(pckt) != CrFwPcktGetMaxLength()) {
		CrFwPcktRelease(pckt);
		return 0;
	}

	/* Check setting and getting packet attributes */
	CrFwPcktSetSeqCnt(pckt, 1);
	if (CrFwPcktGetSeqCnt(pckt) != 1) {
		CrFwPcktRelease(pckt);
		return 0;
	}

	CrFwPcktSetTimeStamp(pckt, 0xAABBCCDD);
	if (CrFwPcktGetTimeStamp(pckt) != 0xAABBCCDD) {
		CrFwPcktRelease(pckt);
		return 0;
	}

	CrFwPcktSetDiscriminant(pckt, 257);
	if (CrFwPcktGetDiscriminant(pckt) != 257) {
		CrFwPcktRelease(pckt);
		return 0;
	}

	CrFwPcktSetGroup(pckt, 28);
	if (CrFwPcktGetGroup(pckt) != 28) {
		CrFwPcktRelease(pckt);
		return 0;
	}

	CrFwPcktSetCmdRepType(pckt, crCmdType);
	if (CrFwPcktGetCmdRepType(pckt) != crCmdType) {
		CrFwPcktRelease(pckt);
		return 0;
	}

	CrFwPcktSetCmdRepType(pckt, crRepType);
	if (CrFwPcktGetCmdRepType(pckt) != crRepType) {
		CrFwPcktRelease(pckt);
		return 0;
	}

	CrFwPcktSetServType(pckt, 10);
	if (CrFwPcktGetServType(pckt) != 10) {
		CrFwPcktRelease(pckt);
		return 0;
	}

	CrFwPcktSetServSubType(pckt, 11);
	if (CrFwPcktGetServSubType(pckt) != 11) {
		CrFwPcktRelease(pckt);
		return 0;
	}

	CrFwPcktSetDest(pckt, 34);
	if (CrFwPcktGetDest(pckt) != 34) {
		CrFwPcktRelease(pckt);
		return 0;
	}

	CrFwPcktSetSrc(pckt, 35);
	if (CrFwPcktGetSrc(pckt) != 35) {
		CrFwPcktRelease(pckt);
		return 0;
	}

	CrFwPcktSetCmdRepId(pckt, 256);
	if (CrFwPcktGetCmdRepId(pckt) != 256) {
		CrFwPcktRelease(pckt);
		return 0;
	}

	CrFwPcktSetAckLevel(pckt, 1, 0, 1, 0);
	if (CrFwPcktIsAcceptAck(pckt) != 1) {
		CrFwPcktRelease(pckt);
		return 0;
	}
	if (CrFwPcktIsStartAck(pckt) != 0) {
		CrFwPcktRelease(pckt);
		return 0;
	}
	if (CrFwPcktIsProgressAck(pckt) != 1) {
		CrFwPcktRelease(pckt);
		return 0;
	}
	if (CrFwPcktIsTermAck(pckt) != 0) {
		CrFwPcktRelease(pckt);
		return 0;
	}

	CrFwPcktSetAckLevel(pckt, 0, 1, 1, 0);
	if (CrFwPcktIsAcceptAck(pckt) != 0) {
		CrFwPcktRelease(pckt);
		return 0;
	}
	if (CrFwPcktIsStartAck(pckt) != 1) {
		CrFwPcktRelease(pckt);
		return 0;
	}
	if (CrFwPcktIsProgressAck(pckt) != 1) {
		CrFwPcktRelease(pckt);
		return 0;
	}
	if (CrFwPcktIsTermAck(pckt) != 0) {
		CrFwPcktRelease(pckt);
		return 0;
	}

	/* Release the packet */
	CrFwPcktRelease(pckt);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application error code */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwPacketTestCase2() {
	CrFwPckt_t* pckt;
	CrFwPckt_t extraPckt;
	CrFwCounterU2_t i;

	/* Create array to hold all created packets */
	pckt = malloc(CR_FW_MAX_NOF_PCKTS*sizeof(CrFwPckt_t*));

	/* Create max number of packets */
	for (i=0; i<CR_FW_MAX_NOF_PCKTS; i++) {
		pckt[i] = CrFwPcktMake((CrFwPcktLength_t)(CrFwPcktGetMaxLength()-1));
		if (pckt[i] == NULL)
			return 0;
	}
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	/* Verify that packet availability check returns 'no packet available' */
	if (CrFwPcktIsAvail(1) != 0)
		return 0;

	/* Attempt to create a new packet */
	extraPckt = CrFwPcktMake(CrFwPcktGetMaxLength());
	if ((extraPckt != NULL) || (CrFwGetAppErrCode() != crPcktAllocationFail))
		return 0;
	CrFwSetAppErrCode(crNoAppErr); 	/* reset application error code */

	/* Release one packet and then attempt creation again */
	if (CR_FW_MAX_NOF_PCKTS>1) {
		CrFwPcktRelease(pckt[CR_FW_MAX_NOF_PCKTS-1]);
		if (CrFwPcktIsAvail(1) != 1)
			return 0;	/* Verify that packet availability check returns 'packet is available' */
		pckt[CR_FW_MAX_NOF_PCKTS-1] = NULL;
		extraPckt = CrFwPcktMake(CrFwPcktGetMaxLength());
		if (extraPckt == NULL)
			return 0;
	}

	/* Release and re-allocate all packets in the packet array
	 * (NB one packet is allocated to extraPckt */
	for (i=0; i<CR_FW_MAX_NOF_PCKTS; i++) {
		if (pckt[i] != NULL)
			CrFwPcktRelease(pckt[i]);
	}
	for (i=0; i<CR_FW_MAX_NOF_PCKTS-1; i++) {
		pckt[i] = CrFwPcktMake((CrFwPcktLength_t)(CrFwPcktGetMaxLength()-1));
		if (pckt[i] == NULL)
			return 0;
	}

	/* Release all packets */
	for (i=0; i<CR_FW_MAX_NOF_PCKTS; i++) {
		if (pckt[i] != NULL)
			CrFwPcktRelease(pckt[i]);
	}
	CrFwPcktRelease(extraPckt);
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Attempt releasing a packet a second time */
	CrFwPcktRelease(pckt[0]);
	if (CrFwGetAppErrCode() != crPcktRelErr)
		return 0;
	CrFwSetAppErrCode(crNoAppErr); 	/* reset application error code */

	/* Verify the packet availability check with illegal packet lengths */
	if (CrFwPcktIsAvail(0) != 0)
		return 0;
	if (CrFwPcktIsAvail(CrFwPcktGetMaxLength()+1) != 0)
		return 0;

	/* Free the memory allocated to the packet array */
	free(pckt);

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwPacketQueueTestCase1() {
	CrFwPckt_t pckt, pckt1, pckt2;
	CrFwCounterU1_t i;
	struct CrFwPcktQueue pcktQueue;

	/* Initialize the packet queue */
	pcktQueue.pckt = NULL;

	/* Create the packet queue */
	CrFwPcktQueueInit(&pcktQueue, 10);

	/* Create it again (just to ensure full coverage of packet queue module */
	CrFwPcktQueueInit(&pcktQueue, 10);

	/* Attempt to pop an item from the packet queue */
	pckt = CrFwPcktQueuePop(&pcktQueue);
	if (pckt != NULL)
		return 0;
	if (CrFwPcktQueueGetNOfPckts(&pcktQueue) != 0)
		return 0;
	if (CrFwPcktQueueIsEmpty(&pcktQueue) != 1)
		return 0;

	/* Attempt to retrieve the oldest item from the packet queue */
	pckt = CrFwPcktQueueGetOldest(&pcktQueue);
	if (pckt != NULL)
		return 0;
	if (CrFwPcktQueueGetNOfPckts(&pcktQueue) != 0)
		return 0;
	if (CrFwPcktQueueIsEmpty(&pcktQueue) != 1)
		return 0;

	/* Reset the empty packet queue */
	CrFwPcktQueueReset(&pcktQueue);
	if (CrFwPcktQueueIsEmpty(&pcktQueue) != 1)
		return 0;
	if (CrFwPcktQueueGetNOfPckts(&pcktQueue) != 0)
		return 0;

	/* Push and pop two packets and verify FIFO order */
	pckt1 = CrFwPcktMake(4);
	pckt2 = CrFwPcktMake(4);
	CrFwPcktQueuePush(&pcktQueue, pckt1);
	CrFwPcktQueuePush(&pcktQueue, pckt2);
	if (CrFwPcktQueueGetOldest(&pcktQueue) != pckt1)
		return 0;
	if (CrFwPcktQueueGetNOfPckts(&pcktQueue) != 2)
		return 0;
	if (CrFwPcktQueuePop(&pcktQueue) != pckt1)
		return 0;
	if (CrFwPcktQueuePop(&pcktQueue) != pckt2)
		return 0;
	if (CrFwPcktQueueIsEmpty(&pcktQueue) != 1)
		return 0;
	if (CrFwPcktQueueGetNOfPckts(&pcktQueue) != 0)
		return 0;
	CrFwPcktRelease(pckt1);
	CrFwPcktRelease(pckt2);

	/* Create a situation where oldest packet is behind next free slot in queue */
	CrFwPcktQueueReset(&pcktQueue);
	if (CrFwPcktQueueIsEmpty(&pcktQueue) != 1)
		return 0;
	if (CrFwPcktQueueGetNOfPckts(&pcktQueue) != 0)
		return 0;
	for (i=0; i<CrFwPcktQueueGetSize(&pcktQueue); i++) {
		pckt = CrFwPcktMake(2);
		CrFwPcktQueuePush(&pcktQueue, pckt);
	}	/* Packet queue is now full */
	pckt = CrFwPcktQueuePop(&pcktQueue);
	CrFwPcktRelease(pckt);
	pckt = CrFwPcktQueuePop(&pcktQueue);
	CrFwPcktRelease(pckt);
	pckt = CrFwPcktQueuePop(&pcktQueue);
	CrFwPcktRelease(pckt);	/* The first three slots in the packet queue are now free */
	pckt = CrFwPcktMake(2);
	CrFwPcktQueuePush(&pcktQueue, pckt);
	pckt = CrFwPcktMake(2);
	CrFwPcktQueuePush(&pcktQueue, pckt); /* Only the third slot in the packet queue is free */
	CrFwPcktQueueReset(&pcktQueue);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Release memory allocated to the packet queue */
	free(pcktQueue.pckt);

	return 1;
}

