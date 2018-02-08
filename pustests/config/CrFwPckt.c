/**
 * @file CrFwPckt.c
 * @ingroup PUSTestsuite
 * @ingroup PUSTestconfig 
 *
 * Default implementation of the packet interface of <code>CrFwPckt.h</code>.
 * The implementation of this interface is one of the adaptation points of the
 * CORDET Framework.
 * This file provides a default implementation which is primarily intended to
 * support testing.
 * It is expected that applications will provide their own implementation.
 * Application will therefore normally replace this file with their own file
 * providing their application-specific implementation.
 *
 * This implementation pre-allocates the memory for a predefined number of packets
 * of fixed size.
 * Packets can be either "in use" or "not in use".
 * A packet is in use if it has been requested through a call to <code>::CrFwPcktMake</code>
 * and has not yet been released through a call to <code>::CrFwPcktRelease</code>.
 *
 * The implementation provided in this file uses global data structures to hold
 * the pool of pre-allocated packets.
 *
 * A packet encapsulates a command or a report and it holds all the attributes of the
 * command or report.
 * The layout of a packet is defined by the value of the <code>offsetYyy</code> constants
 * which defines the offset within a packet at which attribute "Yyy" is stored.
 *
 * The setter functions for the packet attributes assume that the packet length is
 * adequate to hold the attributes.
 * Compliance with this constraint is not checked by the setter functions.
 * Its violation may result in memory corruption.
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 *
 * last modification: 22.01.2018
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#include "CrFwConstants.h"
#include "CrPsUserConstants.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "Pckt/CrFwPckt.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include <Services/General/CrPsPktServReqVerif.h>
#include <Services/General/CrPsPktServHk.h>
#include <Services/General/CrPsPktServEvt.h>
#include <Services/General/CrPsPktServTest.h>

/**
 * The array holding the packets.
 * Packets are stored in this array in blocks of size CR_FW_MAX_PCKT_LENGTH.
 */
static char pcktArray[CR_FW_MAX_NOF_PCKTS*CR_FW_MAX_PCKT_LENGTH];

/**
 * The array holding the "in use" status of the packets.
 * A packet is in use if it has been requested through a call to the "make" function
 * and has not yet been released through a call to the "release" function.
 */
static CrFwBool_t pcktInUse[CR_FW_MAX_NOF_PCKTS] = {0};

/** The number of currently allocated packets. */
static CrFwCounterU2_t nOfAllocatedPckts = 0;

/*static const CrFwPcktLength_t offsetPar = sizeof(TmHeader_t);*/
/*internal functions*/
/*-----------------------------------------------------------------------------------------*/

CrFwGroup_t CrFwPcktGetPcat(CrFwPckt_t pckt) {
	CrPsApid_t apid;
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		apid = getTmHeaderAPID(pckt);
	}
	else
	{
		apid = getTcHeaderAPID(pckt);
	}
	return (apid & 0x000f);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetPcat(CrFwPckt_t pckt, CrFwGroup_t pcat) {
	CrPsApid_t apid;
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		apid = getTmHeaderAPID(pckt);
		setTmHeaderAPID (pckt, (apid & 0x07f0)|(pcat & 0x000f));
	}
	else
	{
		apid = getTcHeaderAPID(pckt);
		setTcHeaderAPID (pckt, (apid & 0x07f0)|(pcat & 0x000f));
	}
}

/*-----------------------------------------------------------------------------------------*/
CrFwDestSrc_t CrFwPcktGetPid(CrFwPckt_t pckt)
{
	/*SO WIE IN CHEOPS (PID ist nur ein TEIL der Appid)*/
	/* maske ist 0x07f0 ( also 0000011111110000 ) */
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		return (getTmHeaderAPID(pckt) & 0x07f0) >> 4;
	}
	else
	{
		return (getTcHeaderAPID(pckt) & 0x07f0) >> 4;
	}
}


/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetPid(CrFwPckt_t pckt, unsigned short pid)
{
	/*SO WIE IN CHEOPS (PID ist nur ein TEIL der Appid)*/
	/* maske ist 0x07f0 ( also 0000011111110000 ) */
	CrPsApid_t apid;
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		apid = getTmHeaderAPID(pckt);
		apid = (apid & 0xf80f) | ((pid<<4) & 0x07f0);
		setTmHeaderAPID(pckt, apid);
	}
	else
	{
		apid = getTcHeaderAPID(pckt);
		apid = (apid & 0xf80f) | ((pid<<4) & 0x07f0);
		setTcHeaderAPID(pckt, apid);
	}
}

/*CrFwPckt.h Functions*/
/*-----------------------------------------------------------------------------------------*/
CrFwPckt_t CrFwPcktMake(CrFwPcktLength_t pcktLength) {
	CrFwCounterU2_t i;
	if (pcktLength > CR_FW_MAX_PCKT_LENGTH) {
		CrFwSetAppErrCode(crPcktAllocationFail);
		return NULL;
	}

	if (pcktLength < 1) {
		CrFwSetAppErrCode(crPcktAllocationFail);
		return NULL;
	}

	for (i=0; i<CR_FW_MAX_NOF_PCKTS; i++) {
		if (pcktInUse[i] == 0) {
			pcktInUse[i] = 1;
			setTmHeaderPcktDataLen((&pcktArray[i*CR_FW_MAX_PCKT_LENGTH]), pcktLength);
			nOfAllocatedPckts++;
			return (&pcktArray[i*CR_FW_MAX_PCKT_LENGTH]);
		}
	}
	CrFwSetAppErrCode(crPcktAllocationFail);
	return NULL;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktRelease(CrFwPckt_t pckt) {
	CrFwCounterU2_t i;

	for (i=0; i<CR_FW_MAX_NOF_PCKTS; i++) {
		if (pckt == &pcktArray[i*CR_FW_MAX_PCKT_LENGTH]) {
			if (pcktInUse[i] == 0) {
				CrFwSetAppErrCode(crPcktRelErr);
			} else {
				nOfAllocatedPckts--;
				pcktInUse[i] = 0;
			}
			return;
		}
	}

	CrFwSetAppErrCode(crPcktRelErr);
	return;
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwPcktIsAvail(CrFwPcktLength_t pcktLength) {
	CrFwCounterU2_t i;

	if (pcktLength > CR_FW_MAX_PCKT_LENGTH)
		return 0;

	if (pcktLength < 1)
		return 0;

	for (i=0; i<CR_FW_MAX_NOF_PCKTS; i++) {
		if (pcktInUse[i] == 0)
			return 1;
	}
	return 0;
}



/*-----------------------------------------------------------------------------------------*/
CrFwCounterU2_t CrFwPcktGetNOfAllocated() {
	return nOfAllocatedPckts;
}

/*-----------------------------------------------------------------------------------------*/
CrFwPcktLength_t CrFwPcktGetMaxLength() {
	return CR_FW_MAX_PCKT_LENGTH;
}

/*-----------------------------------------------------------------------------------------*/
CrFwPcktLength_t CrFwPcktGetLength(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		return (CrFwPcktLength_t) getTmHeaderPcktDataLen(pckt);
	}
	else
	{
		return (CrFwPcktLength_t) getTcHeaderPcktDataLen(pckt);
	}
}

/*-----------------------------------------------------------------------------------------*/
CrFwCmdRepType_t CrFwPcktGetCmdRepType(CrFwPckt_t p){
	if (getTcHeaderPcktType(p) == 0)
	{
		return crRepType;
	}
	else
	{
		return crCmdType;
	}
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetCmdRepType(CrFwPckt_t pckt, CrFwCmdRepType_t type) {
	if (type == crRepType)
	{
		setTmHeaderPcktType(pckt, 0);
	}
	else
	{
		setTcHeaderPcktType(pckt, 1);
	}
}

CrFwInstanceId_t CrFwPcktGetCmdRepId(CrFwPckt_t pckt) {
	/* Field not present */
	(void)(pckt);
	return 0;
}

void CrFwPcktSetCmdRepId(CrFwPckt_t pckt, CrFwInstanceId_t id) {
	/* Field not present */
	(void)(pckt);
	(void)(id);
}

/*-----------------------------------------------------------------------------------------*/
CrFwSeqCnt_t CrFwPcktGetSeqCnt(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		return (CrFwSeqCnt_t) getTmHeaderSeqCount(pckt);
	}
	else
	{
		return (CrFwSeqCnt_t) getTcHeaderSeqCount(pckt);
	}
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetSeqCnt(CrFwPckt_t pckt, CrFwSeqCnt_t seqCnt) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		setTmHeaderSeqCount(pckt, seqCnt);
	}
	else
	{
		setTcHeaderSeqCount(pckt, seqCnt);
	}	
}

/*-----------------------------------------------------------------------------------------*/
CrFwTimeStamp_t CrFwPcktGetTimeStamp(CrFwPckt_t pckt) {
	CrFwTimeStamp_t time;

	getTmHeaderTime(pckt, &time);

	return time;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetTimeStamp(CrFwPckt_t pckt, CrFwTimeStamp_t timeStamp) {

	setTmHeaderTime(pckt, &timeStamp);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetServType(CrFwPckt_t pckt, CrFwServType_t servType) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		setTmHeaderServType(pckt, servType);
	}
	else
	{
		setTcHeaderServType(pckt, servType);
	}
}

/*-----------------------------------------------------------------------------------------*/
CrFwServType_t CrFwPcktGetServType(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		return (CrFwServSubType_t) getTmHeaderServType(pckt);
	}
	else
	{
		return (CrFwServSubType_t) getTcHeaderServType(pckt);
	}
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetServSubType(CrFwPckt_t pckt, CrFwServSubType_t servSubType) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		setTmHeaderServSubType(pckt, servSubType);
	}
	else
	{
		setTcHeaderServSubType(pckt, servSubType);
	}
}

/*-----------------------------------------------------------------------------------------*/
CrFwServSubType_t CrFwPcktGetServSubType(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		return (CrFwServSubType_t) getTmHeaderServSubType(pckt);
	}
	else
	{
		return (CrFwServSubType_t) getTcHeaderServSubType(pckt);
	}
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetDiscriminant(CrFwPckt_t pckt, CrFwDiscriminant_t discriminant) {

	/*TODO: is a switch more performant?*/
	if (CrFwPcktGetServType(pckt) == 1)
	{
		if(CrFwPcktGetServSubType(pckt) == 2)
		{
			/*Packet 1.2 - Failed Acceptance Verification Report*/
			setVerFailedAccRepFailureCode(pckt, discriminant);			
		}
		if(CrFwPcktGetServSubType(pckt) == 4)
		{
			/*Packet 1.4 - Failed Start of Execution Verification Report*/
			setVerFailedStartRepFailureCode(pckt, discriminant);			
		}	
		if(CrFwPcktGetServSubType(pckt) == 6)
		{
			/*Packet 1.6 - Failed Progress of Execution Verification Report*/
			setVerFailedPrgrRepFailureCode(pckt, discriminant);			
		}
		if(CrFwPcktGetServSubType(pckt) == 8)
		{
			/*Packet 1.8 - Failed Completion of Execution Verification Report*/
			setVerFailedTermRepFailureCode(pckt, discriminant);			
		}
		if(CrFwPcktGetServSubType(pckt) == 10)
		{
			/*Packet 1.10 - Failed Routing Verification Report*/
			setVerFailedRoutingRepFailureCode(pckt, discriminant);
		}
	}
	/*Service 3*/
	if (CrFwPcktGetServType(pckt) == 3)
	{
		if(CrFwPcktGetServSubType(pckt) == 1)
		{
			/*Packet 3.1 - Create Housekeeping Parameter Report Structure Command*/
			setHkCreateCmdRepStrucId(pckt, discriminant);
		}
		if(CrFwPcktGetServSubType(pckt) == 2)
		{
			/*Packet 3.2 - Create Diagnostic Parameter Report Structure Command*/
			setHkCreateCmdRepStrucId(pckt, discriminant);
		}
		if(CrFwPcktGetServSubType(pckt) == 10)
		{
			/*Packet 3.10 - Housekeeping Parameter Report Structure Report*/
			setHkRepStructRepRepStrucId(pckt, discriminant);
		}
		if(CrFwPcktGetServSubType(pckt) == 12)
		{
			/*Packet 3.12 - Diagnostic Parameter Report Structure Report*/
			setHkRepStructRepRepStrucId(pckt, discriminant);
		}
		if(CrFwPcktGetServSubType(pckt) == 25)
		{
			/*Packet 3.25 - Housekeeping Parameter Report*/
			setHkRepRepStrucId(pckt, discriminant);
		}
		if(CrFwPcktGetServSubType(pckt) == 26)
		{
			/*Packet 3.26 - Diagnostic Parameter Report*/
			setHkRepRepStrucId(pckt, discriminant);
		}
	}

/*Service 5 */
	if (CrFwPcktGetServType(pckt) == 5)
	{
		if(CrFwPcktGetServSubType(pckt) == 1)
		{
			/*Packet 5.1 - Informative Event Report (Level 1)*/
			setEvtRep1EventId(pckt, discriminant);
		}
		if(CrFwPcktGetServSubType(pckt) == 2)
		{
			/*Packet 5.2 - Low Severity Event Report (Level 2)*/
			setEvtRep2EventId(pckt, discriminant);			
		}
		if(CrFwPcktGetServSubType(pckt) == 3)
		{
			/*Packet 5.3 - Medium Severity Event Report (Level 3)*/
			setEvtRep3EventId(pckt, discriminant);
		}
		if(CrFwPcktGetServSubType(pckt) == 4)
		{
			/*Packet 5.4 - High Severity Event Report (Level 4)*/
			setEvtRep4EventId(pckt, discriminant);			
		}	
	}

/*TODO: add all IF'S (service 1 .. the failcode acts as discriminant*/
	
}

/*-----------------------------------------------------------------------------------------*/
CrFwDiscriminant_t CrFwPcktGetDiscriminant(CrFwPckt_t pckt) {

/*TODO add all IF'S (service 1 .. the failcode acts as discriminant*/
	if (CrFwPcktGetServType(pckt) == 1)
	{
		if(CrFwPcktGetServSubType(pckt) == 2)
		{
			/*Packet 1.2 - Failed Acceptance Verification Report*/
			return (CrFwDiscriminant_t) getVerFailedAccRepFailureCode(pckt);			
		}
		if(CrFwPcktGetServSubType(pckt) == 4)
		{
			/*Packet 1.4 - Failed Start of Execution Verification Report*/
			return (CrFwDiscriminant_t) getVerFailedStartRepFailureCode(pckt);			
		}	
		if(CrFwPcktGetServSubType(pckt) == 6)
		{
			/*Packet 1.6 - Failed Progress of Execution Verification Report*/
			return (CrFwDiscriminant_t) getVerFailedPrgrRepFailureCode(pckt);			
		}
		if(CrFwPcktGetServSubType(pckt) == 8)
		{
			/*Packet 1.8 - Failed Completion of Execution Verification Report*/
			return (CrFwDiscriminant_t) getVerFailedTermRepFailureCode(pckt);			
		}
		if(CrFwPcktGetServSubType(pckt) == 10)
		{
			/*Packet 1.10 - Failed Routing Verification Report*/
			return (CrFwDiscriminant_t) getVerFailedRoutingRepFailureCode(pckt);
		}
	}

/*Service 3*/
	if (CrFwPcktGetServType(pckt) == 3)
	{
		if(CrFwPcktGetServSubType(pckt) == 1)
		{
			/*Packet 3.1 - Create Housekeeping Parameter Report Structure Command*/
			return (CrFwDiscriminant_t) getHkCreateCmdRepStrucId(pckt);
		}
		if(CrFwPcktGetServSubType(pckt) == 2)
		{
			/*Packet 3.2 - Create Diagnostic Parameter Report Structure Command*/
			return (CrFwDiscriminant_t) getHkCreateCmdRepStrucId(pckt);
		}
		if(CrFwPcktGetServSubType(pckt) == 10)
		{
			/*Packet 3.10 - Housekeeping Parameter Report Structure Report*/
			return (CrFwDiscriminant_t) getHkRepStructRepRepStrucId(pckt);
		}
		if(CrFwPcktGetServSubType(pckt) == 12)
		{
			/*Packet 3.12 - Diagnostic Parameter Report Structure Report*/
			return (CrFwDiscriminant_t) getHkRepStructRepRepStrucId(pckt);
		}
			if(CrFwPcktGetServSubType(pckt) == 25)
		{
			/*Packet 3.25 - Housekeeping Parameter Report*/
			return (CrFwDiscriminant_t) getHkRepRepStrucId(pckt);
		}
		if(CrFwPcktGetServSubType(pckt) == 26)
		{
			/*Packet 3.26 - Diagnostic Parameter Report*/
			return (CrFwDiscriminant_t) getHkRepRepStrucId(pckt);
		}
	}

/*Service 5 */
	if (CrFwPcktGetServType(pckt) == 5)
	{
		if(CrFwPcktGetServSubType(pckt) == 1)
		{
			/*Packet 5.1 - Informative Event Report (Level 1)*/
			return (CrFwDiscriminant_t) getEvtRep1EventId(pckt);
		}
		if(CrFwPcktGetServSubType(pckt) == 2)
		{
			/*Packet 5.2 - Low Severity Event Report (Level 2)*/
			return (CrFwDiscriminant_t) getEvtRep2EventId(pckt);			
		}
		if(CrFwPcktGetServSubType(pckt) == 3)
		{
			/*Packet 5.3 - Medium Severity Event Report (Level 3)*/
			return (CrFwDiscriminant_t) getEvtRep3EventId(pckt);
		}
		if(CrFwPcktGetServSubType(pckt) == 4)
		{
			/*Packet 5.4 - High Severity Event Report (Level 4)*/
			return (CrFwDiscriminant_t) getEvtRep4EventId(pckt);			
		}	
	}

	return 0;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetDest(CrFwPckt_t pckt, CrFwDestSrc_t dest) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		setTmHeaderDestId(pckt, dest);
	}
	else
	{
		CrFwPcktSetPid(pckt, dest);
	}
}

/*-----------------------------------------------------------------------------------------*/
CrFwDestSrc_t CrFwPcktGetDest(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		return (CrFwDestSrc_t) getTmHeaderDestId(pckt);
	}
	else
	{
		return (CrFwDestSrc_t) CrFwPcktGetPid(pckt);
	}
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetSrc(CrFwPckt_t pckt, CrFwDestSrc_t src) {
	if (CrFwPcktGetCmdRepType(pckt) == crCmdType)
	{
		setTcHeaderSrcId(pckt, src);
	}
	else
	{
		CrFwPcktSetPid(pckt, src);
	}
}

/*-----------------------------------------------------------------------------------------*/
CrFwDestSrc_t CrFwPcktGetSrc(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crCmdType)
	{
		return (CrFwDestSrc_t) getTcHeaderSrcId(pckt);
	}
	else
	{
		return (CrFwDestSrc_t) CrFwPcktGetPid(pckt);
	}
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetAckLevel(CrFwPckt_t pckt, CrFwBool_t accept, CrFwBool_t start,
                         CrFwBool_t progress, CrFwBool_t term) {
	if (CrFwPcktGetCmdRepType(pckt) == crCmdType)
	{
		setTcHeaderAckAccFlag(pckt, accept);
		setTcHeaderAckStartFlag(pckt, start);
		setTcHeaderAckProgFlag(pckt, progress);
		setTcHeaderAckTermFlag(pckt, term);
	}
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwPcktIsAcceptAck(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crCmdType)
	{
		return (CrFwBool_t) getTcHeaderAckAccFlag(pckt);
	}
	return 0;
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwPcktIsStartAck(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crCmdType)
	{
		return (CrFwBool_t) getTcHeaderAckStartFlag(pckt);
	}
	return 0;
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwPcktIsProgressAck(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crCmdType)
	{
		return (CrFwBool_t) getTcHeaderAckProgFlag(pckt);
	}
	return 0;
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwPcktIsTermAck(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crCmdType)
	{
		return (CrFwBool_t) getTcHeaderAckTermFlag(pckt);
	}
	return 0;
}

/*-----------------------------------------------------------------------------------------*/
char* CrFwPcktGetParStart(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		return (CrFwPckt_t) &pckt[sizeof(TmHeader_t)];
	}
	else
	{
		return (CrFwPckt_t) &pckt[sizeof(TcHeader_t)];
	}
}

/*-----------------------------------------------------------------------------------------*/
CrFwPcktLength_t CrFwPcktGetParLength(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		return (CrFwPcktLength_t) (CrFwPcktGetLength(pckt)-sizeof(TmHeader_t));
	}
	else
	{
		return (CrFwPcktLength_t) (CrFwPcktGetLength(pckt)-sizeof(TcHeader_t));
	}
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetGroup(CrFwPckt_t pckt, CrFwGroup_t group) {
	CrFwPcktSetPcat(pckt, group+1);
}

/*-----------------------------------------------------------------------------------------*/
CrFwGroup_t CrFwPcktGetGroup(CrFwPckt_t pckt) {
	return CrFwPcktGetPcat(pckt)-1;
}




