/**
 * @file
 *
 * Implementation of test cases for Socket-Based InStream and OutStream Components.
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
#include "CrFwRepErrStub.h"
#include "CrFwInStreamSocket.h"
#include "CrFwClientSocket.h"
#include "CrFwServerSocket.h"
#include "CrFwOutStreamSocket.h"
#include "CrFwInStreamTestCases.h"
#include "CrFwInStreamStub.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include configuration files */
#include "CrFwInStreamUserPar.h"
#include "CrFwCmpData.h"
/* Include framework files */
#include "InStream/CrFwInStream.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include system files */
#include <unistd.h>

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwSocketTestCase1() {
	FwSmDesc_t inStream5, outStream5;
	CrFwPckt_t pcktSend, pcktRec, pcktSend1, pcktRec1, pcktSend2, pcktRec2;

	/* Instantiate and start the socket-based InStream and OutStream */
	inStream5 = CrFwInStreamMake(4);
	if (inStream5 == NULL)
		return 0;
	FwSmStart(inStream5);
	if (!CrFwCmpIsInCreated(inStream5))
		return 0;

	outStream5 = CrFwOutStreamMake(4);
	if (outStream5 == NULL)
		return 0;
	FwSmStart(outStream5);
	if (!CrFwCmpIsInCreated(outStream5))
		return 0;

	/* Set port number and host name */
	CrFwInStreamSocketSetPort(2002);
	CrFwInStreamSocketSetHost("localhost");
	CrFwOutStreamSocketSetPort(2002);

	/* Initialize the OutStream (the server) */
	CrFwCmpInit(outStream5);
	if (!CrFwCmpIsInInitialized(outStream5))
		return 0;

	/* Wait 1-2 seconds */
	sleep(1);

	/* Initialize the InStream (the client) */
	CrFwCmpInit(inStream5);
	if (!CrFwCmpIsInInitialized(inStream5))
		return 0;

	/* Configure the InStream and OutStream */
	CrFwCmpReset(inStream5);
	if (!CrFwCmpIsInConfigured(inStream5)) {
		CrFwCmpShutdown(inStream5);
		CrFwCmpShutdown(outStream5);
		return 0;
	}

	/* Wait 1-2 seconds */
	sleep(1);

	CrFwCmpReset(outStream5);
	if (!CrFwCmpIsInConfigured(outStream5)) {
		CrFwCmpShutdown(inStream5);
		CrFwCmpShutdown(outStream5);
		return 0;
	}

	/* Send a packet through the OutStream */
	pcktSend = CrFwPcktMake(100);
	pcktSend[90] = 99;	/* marker */
	CrFwPcktSetSrc(pcktSend, CR_FW_HOST_APP_ID);
	CrFwOutStreamSend(outStream5, pcktSend);
	CrFwPcktRelease(pcktSend);

	/* Wait 1-2 seconds */
	sleep(1);

	/* Poll the InStream and check that packet was received */
	CrFwInStreamSocketPoll(inStream5);
	pcktRec = CrFwInStreamGetPckt(inStream5);
	if (pcktRec[90] != 99) {
		CrFwCmpShutdown(inStream5);
		CrFwCmpShutdown(outStream5);
		return 0;
	}
	CrFwPcktRelease(pcktRec);

	/* Send two packets through the OutStream */
	pcktSend1 = CrFwPcktMake(100);
	pcktSend1[90] = 11;	/* marker */
	CrFwPcktSetSrc(pcktSend1, CR_FW_HOST_APP_ID);
	CrFwOutStreamSend(outStream5, pcktSend1);
	CrFwPcktRelease(pcktSend1);

	pcktSend2 = CrFwPcktMake(100);
	pcktSend2[90] = 22;	/* marker */
	CrFwPcktSetSrc(pcktSend2, CR_FW_HOST_APP_ID);
	CrFwOutStreamSend(outStream5, pcktSend2);
	CrFwPcktRelease(pcktSend2);

	/* Wait 1-2 seconds */
	sleep(1);

	/* Poll the InStream and check that both packets are received */
	CrFwInStreamSocketPoll(inStream5);
	pcktRec1 = CrFwInStreamGetPckt(inStream5);
	if (pcktRec1[90] != 11) {
		CrFwCmpShutdown(inStream5);
		CrFwCmpShutdown(outStream5);
		return 0;
	}
	pcktRec2 = CrFwInStreamGetPckt(inStream5);
	if (pcktRec2[90] != 22) {
		CrFwCmpShutdown(inStream5);
		CrFwCmpShutdown(outStream5);
		return 0;
	}
	if (CrFwInStreamGetPckt(inStream5) != NULL) {
		CrFwCmpShutdown(inStream5);
		CrFwCmpShutdown(outStream5);
		return 0;
	}
	CrFwPcktRelease(pcktRec1);
	CrFwPcktRelease(pcktRec2);

	/* Poll the InStream and check that nothing is returned */
	CrFwInStreamSocketPoll(inStream5);
	if (CrFwInStreamGetPckt(inStream5) != NULL) {
		CrFwCmpShutdown(inStream5);
		CrFwCmpShutdown(outStream5);
		return 0;
	}

	/* Wait 1-2 seconds */
	sleep(1);

	/* Shutdown the InStream and OutStream (this will close the sockets) */
	CrFwCmpShutdown(inStream5);
	CrFwCmpShutdown(outStream5);

	/* Check that all packets have been de-allocated */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwSocketTestCase2() {
	FwSmDesc_t inStream6, inStream7, outStream6, outStream7;
	CrFwPckt_t pcktSend, pcktRec;

	/* Instantiate and start the socket-based InStreams and OutStreams */
	inStream6 = CrFwInStreamMake(5);
	if (inStream6 == NULL)
		return 0;
	FwSmStart(inStream6);
	if (!CrFwCmpIsInCreated(inStream6))
		return 0;

	inStream7 = CrFwInStreamMake(6);
	if (inStream7 == NULL)
		return 0;
	FwSmStart(inStream7);
	if (!CrFwCmpIsInCreated(inStream7))
		return 0;

	outStream6 = CrFwOutStreamMake(5);
	if (outStream6 == NULL)
		return 0;
	FwSmStart(outStream6);
	if (!CrFwCmpIsInCreated(outStream6))
		return 0;

	outStream7 = CrFwOutStreamMake(6);
	if (outStream7 == NULL)
		return 0;
	FwSmStart(outStream7);
	if (!CrFwCmpIsInCreated(outStream7))
		return 0;

	/* Set port number and host name */
	CrFwClientSocketSetPort(2002);
	CrFwClientSocketSetHost("localhost");
	CrFwServerSocketSetPort(2002);

	/* Initialize the server socket */
	CrFwCmpInit(outStream7);
	if (!CrFwCmpIsInInitialized(outStream7))
		return 0;
	CrFwCmpInit(inStream7);
	if (!CrFwCmpIsInInitialized(inStream7))
		return 0;

	/* Wait 1-2 seconds */
	sleep(1);

	/* Initialize the client socket */
	CrFwCmpInit(inStream6);
	if (!CrFwCmpIsInInitialized(inStream6))
		return 0;
	CrFwCmpInit(outStream6);
	if (!CrFwCmpIsInInitialized(outStream6))
		return 0;

	/* Configure the two sockets and their InStreams/OutStreams */
	CrFwCmpReset(inStream6);
	if (!CrFwCmpIsInConfigured(inStream6))
		return 0;
	CrFwCmpReset(outStream6);
	if (!CrFwCmpIsInConfigured(outStream6))
		return 0;
	sleep(1);
	CrFwCmpReset(inStream7);
	if (!CrFwCmpIsInConfigured(inStream7))
		return 0;
	CrFwCmpReset(outStream7);
	if (!CrFwCmpIsInConfigured(outStream7))
		return 0;

	/* Send a packet from the server socket to the client socket (i.e. from OutStream7 to InStream6) */
	pcktSend = CrFwPcktMake(100);
	CrFwPcktSetSrc(pcktSend,CrFwInStreamGetSrc(inStream6,1));
	CrFwPcktSetDest(pcktSend,CrFwOutStreamGetDest(outStream7,1));
	pcktSend[90] = 99;	/* marker */
	CrFwOutStreamSend(outStream7, pcktSend);
	CrFwPcktRelease(pcktSend);

	/* Wait 1-2 seconds */
	sleep(1);

	/* Poll the client socket and check that packet was received */
	CrFwClientSocketPoll();
	pcktRec = CrFwInStreamGetPckt(inStream6);
	if (pcktRec[90] != 99)
		return 0;
	CrFwPcktRelease(pcktRec);

	/* Send a packet from the client socket to the server socket (i.e. from OutStream6 to InStream7) */
	pcktSend = CrFwPcktMake(100);
	CrFwPcktSetSrc(pcktSend,CrFwInStreamGetSrc(inStream7,1));
	CrFwPcktSetDest(pcktSend,CrFwOutStreamGetDest(outStream6,1));
	pcktSend[90] = 11;	/* marker */
	CrFwOutStreamSend(outStream6, pcktSend);
	CrFwPcktRelease(pcktSend);

	/* Wait 1-2 seconds */
	sleep(1);

	/* Poll the server socket and check that packet was received */
	CrFwServerSocketPoll();
	pcktRec = CrFwInStreamGetPckt(inStream7);
	if (pcktRec[90] != 11)
		return 0;
	CrFwPcktRelease(pcktRec);

	/* Shutdown the InStreams and OutStreams (this will close the sockets) */
	CrFwCmpShutdown(inStream6);
	CrFwCmpShutdown(outStream6);
	CrFwCmpShutdown(inStream7);
	CrFwCmpShutdown(outStream7);

	/* Check that all packets have been de-allocated */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwSocketTestCase3() {
	FwSmDesc_t inStream6, inStream7, outStream6, outStream7;
	CrFwPckt_t pckt1, pckt2, pckt3, pcktRec;
	CrFwDestSrc_t src;

	/* Reset error reporting interface */
	CrFwRepErrStubReset();

	/* Instantiate and start the socket-based InStreams and OutStreams */
	inStream6 = CrFwInStreamMake(5);
	if (inStream6 == NULL)
		return 0;
	FwSmStart(inStream6);
	if (!CrFwCmpIsInCreated(inStream6))
		return 0;

	inStream7 = CrFwInStreamMake(6);
	if (inStream7 == NULL)
		return 0;
	FwSmStart(inStream7);
	if (!CrFwCmpIsInCreated(inStream7))
		return 0;

	outStream6 = CrFwOutStreamMake(5);
	if (outStream6 == NULL)
		return 0;
	FwSmStart(outStream6);
	if (!CrFwCmpIsInCreated(outStream6))
		return 0;

	outStream7 = CrFwOutStreamMake(6);
	if (outStream7 == NULL)
		return 0;
	FwSmStart(outStream7);
	if (!CrFwCmpIsInCreated(outStream7))
		return 0;

	/* Set port number and host name */
	CrFwClientSocketSetPort(2002);
	CrFwClientSocketSetHost("localhost");
	CrFwServerSocketSetPort(2002);

	/* Initialize the server socket */
	CrFwCmpInit(outStream7);
	if (!CrFwCmpIsInInitialized(outStream7))
		return 0;
	CrFwCmpInit(inStream7);
	if (!CrFwCmpIsInInitialized(inStream7))
		return 0;

	/* Wait 1-2 seconds */
	sleep(1);

	/* Initialize the client socket */
	CrFwCmpInit(inStream6);
	if (!CrFwCmpIsInInitialized(inStream6))
		return 0;
	CrFwCmpInit(outStream6);
	if (!CrFwCmpIsInInitialized(outStream6))
		return 0;

	/* Configure the two sockets and their InStreams/OutStreams */
	CrFwCmpReset(inStream6);
	if (!CrFwCmpIsInConfigured(inStream6))
		return 0;
	CrFwCmpReset(outStream6);
	if (!CrFwCmpIsInConfigured(outStream6))
		return 0;
	sleep(1);
	CrFwCmpReset(inStream7);
	if (!CrFwCmpIsInConfigured(inStream7))
		return 0;
	CrFwCmpReset(outStream7);
	if (!CrFwCmpIsInConfigured(outStream7))
		return 0;

	/* Send three packets from the server socket to the client socket */
	pckt1 = CrFwPcktMake(100);
    pckt2 = CrFwPcktMake(100);
	pckt3 = CrFwPcktMake(100);
	pckt1[90] = 99;	/* marker */
	pckt2[90] = 98;	/* marker */
	pckt3[90] = 97;	/* marker */
	src = CrFwInStreamGetSrc(inStream6, 1);
	CrFwPcktSetSrc(pckt1,src);
	CrFwPcktSetSrc(pckt2,src);
	CrFwPcktSetSrc(pckt3,src);
    CrFwPcktSetGroup(pckt1,0);
    CrFwPcktSetGroup(pckt2,0);
    CrFwPcktSetGroup(pckt3,0);
	CrFwOutStreamSend(outStream7, pckt1);
	CrFwOutStreamSend(outStream7, pckt2);
	CrFwOutStreamSend(outStream7, pckt3);
	CrFwPcktRelease(pckt1);
	CrFwPcktRelease(pckt2);
	CrFwPcktRelease(pckt3);

	/* Wait 1-2 seconds */
	sleep(1);

	/* Poll the client socket and check that packets were received */
	CrFwClientSocketPoll();
	pcktRec = CrFwInStreamGetPckt(inStream6);
	if (pcktRec[90] != 99)
		return 0;
	CrFwPcktRelease(pcktRec);
	pcktRec = CrFwInStreamGetPckt(inStream6);
	if (pcktRec[90] != 98)
		return 0;
	CrFwPcktRelease(pcktRec);
	pcktRec = CrFwInStreamGetPckt(inStream6);
	if (pcktRec[90] != 97)
		return 0;
	CrFwPcktRelease(pcktRec);

	/* Send a packet from the client socket to the server socket */
	pckt1 = CrFwPcktMake(100);
	pckt2 = CrFwPcktMake(100);
	pckt3 = CrFwPcktMake(100);
	pckt1[90] = 10;	/* marker */
	pckt2[90] = 11;	/* marker */
	pckt3[90] = 12;	/* marker */
	src = CrFwInStreamGetSrc(inStream7, 1);
	CrFwPcktSetSrc(pckt1,src);
	CrFwPcktSetSrc(pckt2,src);
	CrFwPcktSetSrc(pckt3,src);
    CrFwPcktSetGroup(pckt1,0);
    CrFwPcktSetGroup(pckt2,0);
    CrFwPcktSetGroup(pckt3,0);
	CrFwOutStreamSend(outStream6, pckt1);
	CrFwOutStreamSend(outStream6, pckt2);
	CrFwOutStreamSend(outStream6, pckt3);
	CrFwPcktRelease(pckt1);
	CrFwPcktRelease(pckt2);
	CrFwPcktRelease(pckt3);

	/* Wait 1-2 seconds */
	sleep(1);

	/* Poll the server socket and check that packets were received */
	CrFwServerSocketPoll();
	pcktRec = CrFwInStreamGetPckt(inStream7);
	if (pcktRec[90] != 10)
		return 0;
	CrFwPcktRelease(pcktRec);
	pcktRec = CrFwInStreamGetPckt(inStream7);
	if (pcktRec[90] != 11)
		return 0;
	CrFwPcktRelease(pcktRec);
	pcktRec = CrFwInStreamGetPckt(inStream7);
	if (pcktRec[90] != 12)
		return 0;
	CrFwPcktRelease(pcktRec);

	/* Shutdown the InStreams and OutStreams (this will close the sockets) */
	CrFwCmpShutdown(inStream6);
	CrFwCmpShutdown(outStream6);
	CrFwCmpShutdown(inStream7);
	CrFwCmpShutdown(outStream7);

	/* Check that no errors have been reported */
	if (CrFwRepErrStubGetPos() != 0)
		return 0;

	/* Check that all packets have been de-allocated */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwSocketTestCase4() {
	FwSmDesc_t inStream6, inStream7, outStream6, outStream7;
	CrFwPckt_t sPckt1, sPckt2, sPckt3, cPckt1, cPckt2, cPckt3, pcktRec;
	CrFwDestSrc_t src;

	/* Reset error reporting interface */
	CrFwRepErrStubReset();

	/* Instantiate and start the socket-based InStreams and OutStreams */
	inStream6 = CrFwInStreamMake(5);
	if (inStream6 == NULL)
		return 0;
	FwSmStart(inStream6);
	if (!CrFwCmpIsInCreated(inStream6))
		return 0;

	inStream7 = CrFwInStreamMake(6);
	if (inStream7 == NULL)
		return 0;
	FwSmStart(inStream7);
	if (!CrFwCmpIsInCreated(inStream7))
		return 0;

	outStream6 = CrFwOutStreamMake(5);
	if (outStream6 == NULL)
		return 0;
	FwSmStart(outStream6);
	if (!CrFwCmpIsInCreated(outStream6))
		return 0;

	outStream7 = CrFwOutStreamMake(6);
	if (outStream7 == NULL)
		return 0;
	FwSmStart(outStream7);
	if (!CrFwCmpIsInCreated(outStream7))
		return 0;

	/* Set port number and host name */
	CrFwClientSocketSetPort(2002);
	CrFwClientSocketSetHost("localhost");
	CrFwServerSocketSetPort(2002);

	/* Initialize the server socket */
	CrFwCmpInit(outStream7);
	if (!CrFwCmpIsInInitialized(outStream7))
		return 0;
	CrFwCmpInit(inStream7);
	if (!CrFwCmpIsInInitialized(inStream7))
		return 0;

	/* Wait 1-2 seconds */
	sleep(1);

	/* Initialize the client socket */
	CrFwCmpInit(inStream6);
	if (!CrFwCmpIsInInitialized(inStream6))
		return 0;
	CrFwCmpInit(outStream6);
	if (!CrFwCmpIsInInitialized(outStream6))
		return 0;

	/* Configure the two sockets and their InStreams/OutStreams */
	CrFwCmpReset(inStream6);
	if (!CrFwCmpIsInConfigured(inStream6))
		return 0;
	CrFwCmpReset(outStream6);
	if (!CrFwCmpIsInConfigured(outStream6))
		return 0;
	sleep(1);
	CrFwCmpReset(inStream7);
	if (!CrFwCmpIsInConfigured(inStream7))
		return 0;
	CrFwCmpReset(outStream7);
	if (!CrFwCmpIsInConfigured(outStream7))
		return 0;

	/* Send packets from one socket the other */
	sPckt1 = CrFwPcktMake(100);
	sPckt2 = CrFwPcktMake(100);
	sPckt3 = CrFwPcktMake(100);
	sPckt1[90] = 99;	/* marker */
	sPckt2[90] = 98;	/* marker */
	sPckt3[90] = 97;	/* marker */
	src = CrFwInStreamGetSrc(inStream6, 1);
	CrFwPcktSetSrc(sPckt1,src);
	CrFwPcktSetSrc(sPckt2,src);
	CrFwPcktSetSrc(sPckt3,src);
    CrFwPcktSetGroup(sPckt1,1);
    CrFwPcktSetGroup(sPckt2,1);
    CrFwPcktSetGroup(sPckt3,1);
	cPckt1 = CrFwPcktMake(100);
	cPckt2 = CrFwPcktMake(100);
	cPckt3 = CrFwPcktMake(100);
	cPckt1[90] = 10;	/* marker */
	cPckt2[90] = 11;	/* marker */
	cPckt3[90] = 12;	/* marker */
	src = CrFwInStreamGetSrc(inStream7, 1);
	CrFwPcktSetSrc(cPckt1,src);
	CrFwPcktSetSrc(cPckt2,src);
	CrFwPcktSetSrc(cPckt3,src);
    CrFwPcktSetGroup(cPckt1,0);
    CrFwPcktSetGroup(cPckt2,0);
    CrFwPcktSetGroup(cPckt3,0);

	CrFwOutStreamSend(outStream7, sPckt1);
	CrFwOutStreamSend(outStream7, sPckt2);
	CrFwOutStreamSend(outStream7, sPckt3);
	CrFwOutStreamSend(outStream6, cPckt1);
	CrFwOutStreamSend(outStream6, cPckt2);
	CrFwOutStreamSend(outStream6, cPckt3);
	CrFwPcktRelease(sPckt1);
	CrFwPcktRelease(sPckt2);
	CrFwPcktRelease(sPckt3);
	CrFwPcktRelease(cPckt1);
	CrFwPcktRelease(cPckt2);
	CrFwPcktRelease(cPckt3);

	/* Wait 1-2 seconds */
	sleep(1);

	/* Poll the client socket and check that packets were received */
	CrFwClientSocketPoll();
	pcktRec = CrFwInStreamGetPckt(inStream6);
	if (pcktRec[90] != 99)
		return 0;
	CrFwPcktRelease(pcktRec);
	pcktRec = CrFwInStreamGetPckt(inStream6);
	if (pcktRec[90] != 98)
		return 0;
	CrFwPcktRelease(pcktRec);
	pcktRec = CrFwInStreamGetPckt(inStream6);
	if (pcktRec[90] != 97)
		return 0;
	CrFwPcktRelease(pcktRec);

	/* Poll the server socket and check that packets were received */
	CrFwServerSocketPoll();
	pcktRec = CrFwInStreamGetPckt(inStream7);
	if (pcktRec[90] != 10)
		return 0;
	CrFwPcktRelease(pcktRec);
	pcktRec = CrFwInStreamGetPckt(inStream7);
	if (pcktRec[90] != 11)
		return 0;
	CrFwPcktRelease(pcktRec);
	pcktRec = CrFwInStreamGetPckt(inStream7);
	if (pcktRec[90] != 12)
		return 0;
	CrFwPcktRelease(pcktRec);

	/* Shutdown the InStreams and OutStreams (this will close the sockets) */
	CrFwCmpShutdown(inStream6);
	CrFwCmpShutdown(outStream6);
	CrFwCmpShutdown(inStream7);
	CrFwCmpShutdown(outStream7);

	/* Check that no errors have been reported */
	if (CrFwRepErrStubGetPos() != 0)
		return 0;

	/* Check that all packets have been de-allocated */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}
