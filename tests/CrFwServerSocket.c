/**
 * @file
 *
 * Implementation of interface to server socket.
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
#include "CrFwServerSocket.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include configuration files */
#include "CrFwOutStreamUserPar.h"
#include "CrFwCmpData.h"
/* Include framework files */
#include "OutStream/CrFwOutStream.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include file for socket implementation */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <strings.h>

/** Set the port number (must be same as the port number specified in <code>CrFwServerSocket.c</code> */
static unsigned short portno = 0;

/** The file descriptors for the socket */
static int sockfd = 0;

/** The file descriptors for the socket */
static int newsockfd;

/** Socket variable */
static struct sockaddr_in cli_addr;

/** Socket variable */
static socklen_t clilen;

/** The maximum size of an incoming packet */
static unsigned int pcktMaxLength;

/** The Read Buffer */
static unsigned char* readBuffer;

/**
 * Entry point for the thread which waits for the incoming connection from the client socket.
 * @param ptr unused argument (required with compatibility with pthread create function)
 */
static void* acceptThreadEntry(void* ptr);

/* ---------------------------------------------------------------------------------------------*/
void CrFwServerSocketInitAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* streamData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	struct sockaddr_in serv_addr, cli_addr;
	pthread_t acceptThread;
	pthread_attr_t attr;

	/* Check if server socket has already been initialized */
	if (sockfd != 0) {
		if (streamData->typeId == CR_FW_INSTREAM_TYPE)
			CrFwInStreamDefInitAction(prDesc);
		else
			CrFwOutStreamDefInitAction(prDesc);
		return;
	}

	/* Create the read buffer */
	pcktMaxLength = (int)CrFwPcktGetMaxLength();
	readBuffer = malloc((FwPrCounterU4_t)(pcktMaxLength*sizeof(char)));

	/* Create the socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("CrFwServerSocketInitAction, Socket creation");
		streamData->outcome = 0;
		return;
	}

	bzero((char*) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("CrFwServerSocketInitAction, Bind Socket");
		streamData->outcome = 0;
		return;
	}
	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	/* Create thread which will accept the connection call from the client socket */
	pthread_attr_init(&attr);
	if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0) {
		perror("CrFwServerSocketInitAction, set detached state");
		streamData->outcome = 0;
		return;
	}
	if (pthread_create(&acceptThread, NULL, acceptThreadEntry, NULL) < 0) {
		streamData->outcome = 0;
		return;
	};

	/* Execute default initialization action for OutStream/InStream */
	if (streamData->typeId == CR_FW_INSTREAM_TYPE)
		CrFwInStreamDefInitAction(prDesc);
	else
		CrFwOutStreamDefInitAction(prDesc);
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwServerSocketShutdownAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* streamData = (CrFwCmpData_t*)FwSmGetData(smDesc);

	if (streamData->typeId == CR_FW_INSTREAM_TYPE)
		CrFwInStreamDefShutdownAction(smDesc);
	else if (streamData->typeId == CR_FW_OUTSTREAM_TYPE)
		CrFwOutStreamDefShutdownAction(smDesc);
	else {
		perror("CrFwServerSocketShutdownAction, Incorrect caller type");
		return;
	}
	if (sockfd != 0) {
		free(readBuffer);
		close(newsockfd);
		close(sockfd);
		sockfd = 0;
	}
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwServerSocketConfigAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* streamData = (CrFwCmpData_t*)FwPrGetData(prDesc);

	/* Clear Read Buffer */
	readBuffer[0] = 0;

	if (streamData->typeId == CR_FW_INSTREAM_TYPE)
		CrFwInStreamDefConfigAction(prDesc);
	else
		CrFwOutStreamDefConfigAction(prDesc);
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwServerSocketPoll() {
	long int n;
	FwSmDesc_t inStream;

	if (readBuffer[0] != 0) {
		/* src = CrFwPcktGetSrc((CrFwPckt_t)readBuffer); */
		/* inStream = CrFwGetInStream(src); */
		inStream = CrFwInStreamMake(6);
		CrFwInStreamPcktAvail(inStream);
		return;
	}

	n = read(newsockfd, readBuffer, pcktMaxLength);
	if (n == -1)	/* no data are available from the socket */
		return;
	if (n == 0)	{
		printf("CrFwServerSocketPoll: ERROR reading from socket\n");
		return;
	}
	if (n == readBuffer[0]) {	/* a valid packet has arrived */
		/* src = CrFwPcktGetSrc((CrFwPckt_t)readBuffer); */
		/* inStream = CrFwGetInStream(src); */
		inStream = CrFwInStreamMake(6);
		CrFwInStreamPcktAvail(inStream);
		return;
	}
	if (n != readBuffer[0]) {
		printf("CrFwServerSocketPoll: invalid packet received from socket\n");
		readBuffer[0] = 0;
		return;
	}
}

/* ---------------------------------------------------------------------------------------------*/
CrFwPckt_t CrFwServerSocketPcktCollect(CrFwDestSrc_t src) {
	CrFwPckt_t pckt;
	CrFwDestSrc_t pcktSrc;

	if (readBuffer[0] != 0) {
		pcktSrc = CrFwPcktGetSrc((CrFwPckt_t)readBuffer);
		if (src == pcktSrc) {
			pckt = CrFwPcktMake((CrFwPcktLength_t)readBuffer[0]);
			memcpy(pckt, readBuffer, readBuffer[0]);
			readBuffer[0] = 0;
			return pckt;
		} else
			return NULL;
	} else
		return NULL;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwServerSocketIsPcktAvail(CrFwDestSrc_t src) {
	long int n;
	CrFwDestSrc_t pcktSrc;

	if (readBuffer[0] != 0) {
		return 1;
	}

	n = read(newsockfd, readBuffer, pcktMaxLength);
	if (n == -1)	/* no data are available from the socket */
		return 0;

	if (n == 0)	{
		printf("CrFwServerSocketIsPcktAvail: ERROR reading from socket\n");
		return 0;
	}
	if (n == readBuffer[0]) {	/* a valid packet has arrived */
		pcktSrc = CrFwPcktGetSrc((CrFwPckt_t)readBuffer);
		if (src == pcktSrc)
			return 1;
		else
			return 0;
	}

	if (n != readBuffer[0]) {
		printf("CrFwServerSocketIsPcktAvail: invalid packet received from socket\n");
		readBuffer[0] = 0;
		return 0;
	}

	return 0;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwServerSocketPcktHandover(CrFwPckt_t pckt) {
	unsigned int len = CrFwPcktGetLength(pckt);
	long int n;

	n = write(newsockfd, pckt, len);

	if (n < 0)
		return 0;

	if (n != (int)CrFwPcktGetLength(pckt))  {
		printf("CrFwServerSocketPcktHandover: error writing to socket\n");
		return 0;
	}

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
static void* acceptThreadEntry(void* ptr) {
	int flags;
	(void)(ptr);

	/* The call to accept blocks until a matching connect is done by the client socket */
	newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
	if (newsockfd < 0) {
		perror("CrFwServerSocketInitAction, Socket Accept");
	}

	/* Set the socket to non-blocking mode */
	if ((flags = fcntl(newsockfd, F_GETFL, 0)) < 0) {
		perror("CrFwServerSocketInitAction, Set socket attributes");
		return NULL;
	}
	if (fcntl(newsockfd, F_SETFL, flags | O_NONBLOCK) < 0) {
		perror("CrFwServerSocketInitAction, Set socket attributes");
		return NULL;
	}

	return NULL;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwServerSocketInitCheck(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamData = (CrFwCmpData_t*)FwPrGetData(prDesc);

	if (portno < 2000)
		outStreamData->outcome = 0;
	else
		outStreamData->outcome = 1;

	return;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwServerSocketConfigCheck(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamData = (CrFwCmpData_t*)FwPrGetData(prDesc);

	if (newsockfd > 0)
		outStreamData->outcome = 1;
	else
		outStreamData->outcome = 0;

	return;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwServerSocketSetPort(unsigned short n) {
	portno = n;
}
