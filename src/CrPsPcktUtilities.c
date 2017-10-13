/**
 * @file CrPsPcktUtilities.c
 * @ingroup CrIaDemo
 *
 * 
 *
 * @author C. Reimers and M. Rockenbauer 19.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

/* Includes */
#include "CrPsPcktUtilities.h"
#include "CrPsDebug.h"
#include "CrPsPkt.h"
#include "Pckt/CrFwPckt.h"
#include "CrFwConstants.h"



unsigned short CrFwPcktGetSeqCtrl(CrFwPckt_t pckt)
{
	unsigned int seqflags, seqcount;

	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		seqflags = getTmHeaderSeqFlags(pckt);
		seqcount = getTmHeaderSeqCount(pckt);
	}
	else
	{
		seqflags = getTcHeaderSeqFlags(pckt);
		seqcount = getTcHeaderSeqCount(pckt);
	}
	
	return ((seqflags << 14) & 0xc000) | (seqcount & 0x3fff);
}


void CrFwPcktSetSeqCtrl(CrFwPckt_t pckt, unsigned short psc)
{
	unsigned int seqflags, seqcount;

	seqflags = ((psc & 0xc000)>>14)&0x0003;
	seqcount = psc & 0x3fff;

	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		setTmHeaderSeqFlags(pckt, seqflags);
		setTmHeaderSeqCount(pckt, seqcount);
	}
	else
	{
		setTmHeaderSeqFlags(pckt, seqflags);
		setTmHeaderSeqCount(pckt, seqcount);
	}

	return;
}

unsigned short CrFwPcktGetApid(CrFwPckt_t pckt)
{
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		return getTmHeaderAPID(pckt);
	}
	else
	{
		return getTcHeaderAPID(pckt);
	}
}

void CrFwPcktSetApid(CrFwPckt_t pckt, unsigned short apid)
{
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
	{
		setTmHeaderAPID(pckt, apid);
	}
	else
	{
		setTcHeaderAPID(pckt, apid);
	}
}

/*PCAT getter für Group getter (und setter)*/

/*discriminante if service type subservicetype*/


