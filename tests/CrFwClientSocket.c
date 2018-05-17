/**
 * @file
 *
 * Implementation of interface to control the client socket.
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
#include "CrFwClientSocket.h"
#include "CrFwConstants.h"
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
#include <strings.h>

/** Required for backward compatibility */
#define h_addr h_addr_list[0]

/** The port number */
static unsigned short portno = 0;

/** The host name */
static char* hostName = NULL;

/** The file descriptor for the socket */
static int sockfd = 0;

/** The maximum size of an incoming packet */
static unsigned int pcktMaxLength;

/** The Read Buffer */
static unsigned char* readBuffer;

/* ---------------------------------------------------------------------------------------------*/
void CrFwClientSocketInitAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* streamData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	struct sockaddr_in serv_addr;
	struct hostent* server;
	int flags;

	if (sockfd != 0) {	/* Check if socket is already initialized */
		if (streamData->typeId == CR_FW_INSTREAM_TYPE)
			CrFwInStreamDefInitAction(prDesc);
		else
			CrFwOutStreamDefInitAction(prDesc);
		return;
	}

	/* Create the read buffer */
	pcktMaxLength = (int)CrFwPcktGetMaxLength();
	readBuffer = malloc((FwPrCounterU4_t)(pcktMaxLength*sizeof(char)));

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("CrFwClientSocketInitAction, Socket Creation");
		streamData->outcome = 0;
		return;
	}

	/* Set the socket to non-blocking mode */
	if ((flags = fcntl(sockfd, F_GETFL, 0)) < 0) {
		perror("CrFwClientSocketInitAction, Set socket attributes");
		streamData->outcome = 0;
		return;
	}
	if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) < 0) {
		perror("CrFwClientSocketInitAction, Set socket attributes");
		streamData->outcome = 0;
		return;
	}

	server = gethostbyname(hostName);
	if (server == NULL) {
		perror("CrFwClientSocketInitAction, Get host name");
		streamData->outcome = 0;
		return;
	}

	bzero((char*) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char*)server->h_addr,
	      (char*)&serv_addr.sin_addr.s_addr,
	      (long unsigned int)server->h_length);
	serv_addr.sin_port = (unsigned short int)htons(portno);

	if (connect(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0) {
		if (errno != EINPROGRESS) {
			perror("CrFwClientSocketInitAction, Connect Socket");
			streamData->outcome = 0;
			return;
		}
	}

	/* Execute default initialization action for OutStream/InStream */
	if (streamData->typeId == CR_FW_INSTREAM_TYPE)
		CrFwInStreamDefInitAction(prDesc);
	else
		CrFwOutStreamDefInitAction(prDesc);
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwClientSocketShutdownAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* streamData = (CrFwCmpData_t*)FwSmGetData(smDesc);

	if (streamData->typeId == CR_FW_INSTREAM_TYPE)
		CrFwInStreamDefShutdownAction(smDesc);
	else if (streamData->typeId == CR_FW_OUTSTREAM_TYPE)
		CrFwOutStreamDefShutdownAction(smDesc);
	else {
		perror("CrFwClientSocketShutdownAction, Incorrect caller type");
		return;
	}

	if (sockfd == 0) 	/* Check if socket was already shutdown */
		return;
	free(readBuffer);
	close(sockfd);
	sockfd = 0;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwClientSocketInitCheck(FwPrDesc_t prDesc) {
	CrFwCmpData_t* prData = (CrFwCmpData_t*)FwPrGetData(prDesc);

	if (pcktMaxLength > 255) {
		prData->outcome = 0;
		return;
	}

	if (portno == 0) {
		prData->outcome = 0;
		return;
	}

	if (hostName == NULL) {
		prData->outcome = 0;
		return;
	}

	prData->outcome = 1;
	return;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwClientSocketConfigAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* streamData = (CrFwCmpData_t*)FwPrGetData(prDesc);

	/* Clear Read Buffer */
	readBuffer[0] = 0;

	if (streamData->typeId == CR_FW_INSTREAM_TYPE)
		CrFwInStreamDefConfigAction(prDesc);
	else if (streamData->typeId == CR_FW_OUTSTREAM_TYPE)
		CrFwOutStreamDefConfigAction(prDesc);
	else {
		perror("CrFwClientSocketConfigAction, Incorrect caller type");
		return;
	}
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwClientSocketPoll() {
	long int n;
	FwSmDesc_t inStream;

	if (readBuffer[0] != 0) {
		/* src = CrFwPcktGetSrc((CrFwPckt_t)readBuffer); */
		/* inStream = CrFwGetInStream(src); */
		inStream = CrFwInStreamMake(5);
		CrFwInStreamPcktAvail(inStream);
		return;
	}

	n = read(sockfd, readBuffer, pcktMaxLength);
	if (n == -1)	/* no data are available from the socket */
		return;
	if (n == 0)	{
		printf("CrFwClientSocketPoll: ERROR reading from socket\n");
		return;
	}
	if (n == readBuffer[0]) {	/* a valid packet has arrived */
		/* src = CrFwPcktGetSrc((CrFwPckt_t)readBuffer); */
		/* inStream = CrFwGetInStream(src); */
		inStream = CrFwInStreamMake(5);
		CrFwInStreamPcktAvail(inStream);
		return;
	}
	if (n != readBuffer[0]) {
		printf("CrFwClientSocketPoll: invalid packet received from socket\n");
		readBuffer[0] = 0;
		return;
	}
}

/* ---------------------------------------------------------------------------------------------*/
CrFwPckt_t CrFwClientSocketPcktCollect(CrFwDestSrc_t src) {
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
CrFwBool_t CrFwClientSocketIsPcktAvail(CrFwDestSrc_t src) {
	long int n;
	CrFwDestSrc_t pcktSrc;

	if (readBuffer[0] != 0) {
		return 1;
	}

	n = read(sockfd, readBuffer, pcktMaxLength);
	if (n == -1)	/* no data are available from the socket */
		return 0;

	if (n == 0)	{
		printf("CrFwClientSocketIsPcktAvail: ERROR reading from socket\n");
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
		printf("CrFwClientSocketIsPcktAvail: invalid packet received from socket\n");
		readBuffer[0] = 0;
		return 0;
	}

	return 0;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwClientSocketPcktHandover(CrFwPckt_t pckt) {
	unsigned int len = (unsigned int)CrFwPcktGetLength(pckt);
	long int n;

	n = write(sockfd, pckt, len);

	if (n < 0)
		return 0;

	if (n != (int)CrFwPcktGetLength(pckt))  {
		printf("CrFwClientSocketPcktHandover: error writing to socket\n");
		return 0;
	}

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwClientSocketSetPort(unsigned short n) {
	portno = n;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwClientSocketSetHost(char* name) {
	hostName = name;
}
