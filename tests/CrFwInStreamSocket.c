/**
 * @file
 *
 * Implementation of Socket-Based InStream.
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
static int sockfd;

/** The maximum size of an incoming packet */
static unsigned int pcktMaxLength;

/** The Read Buffer */
static unsigned char* readBuffer;

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamSocketInitAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* inStreamData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	struct sockaddr_in serv_addr;
	struct hostent* server;
	int flags;

	pcktMaxLength = CrFwPcktGetMaxLength();
	readBuffer = malloc((FwPrCounterU4_t)(pcktMaxLength*sizeof(char)));

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("CrFwInStreamSocketInitAction, Socket Creation");
		inStreamData->outcome = 0;
		return;
	}

	/* Set the socket to non-blocking mode */
	if ((flags = fcntl(sockfd, F_GETFL, 0)) < 0) {
		perror("CrFwInStreamSocketInitAction, Set socket attributes");
		inStreamData->outcome = 0;
		return;
	}
	if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) < 0) {
		perror("CrFwInStreamSocketInitAction, Set socket attributes");
		inStreamData->outcome = 0;
		return;
	}

	fcntl(sockfd, F_SETFL, O_NONBLOCK);

	server = gethostbyname(hostName);
	if (server == NULL) {
		perror("CrFwInStreamSocketInitAction, Get host name");
		inStreamData->outcome = 0;
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
			perror("CrFwInStreamSocketInitAction, Connect Socket");
			inStreamData->outcome = 0;
			return;
		}
	}

	CrFwInStreamDefInitAction(prDesc);
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamSocketShutdownAction(FwSmDesc_t smDesc) {
	CrFwInStreamDefShutdownAction(smDesc);
	free(readBuffer);
	close(sockfd);
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamSocketInitCheck(FwPrDesc_t prDesc) {
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
void CrFwInStreamSocketConfigAction(FwPrDesc_t prDesc) {

	/* Clear Read Buffer */
	readBuffer[0] = 0;

	CrFwInStreamDefConfigAction(prDesc);
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamSocketPoll(FwSmDesc_t inStream) {
	long int n;

	n = read(sockfd, readBuffer, pcktMaxLength);
	if (n == -1)	/* no data are available from the socket */
		return;
	if (n == 0)	{
		printf("CrFwInStreamSocketConfigAction: ERROR reading from socket\n");
		return;
	}
	if (n == readBuffer[0]) {	/* a valid packet has arrived */
		CrFwInStreamPcktAvail(inStream);
		return;
	}
	if (n != readBuffer[0]) {
		printf("CrFwInStreamSocketConfigAction: invalid packet received from socket\n");
		return;
	}
}

/* ---------------------------------------------------------------------------------------------*/
CrFwPckt_t CrFwInStreamSocketPcktCollect(CrFwDestSrc_t src) {
	CrFwPckt_t pckt;
	(void)(src);

	if (readBuffer[0] != 0) {
		pckt = CrFwPcktMake((CrFwPcktLength_t)readBuffer[0]);
		memcpy(pckt, readBuffer, readBuffer[0]);
		readBuffer[0] = 0;
		return pckt;
	} else
		return NULL;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwInStreamSocketIsPcktAvail(CrFwDestSrc_t src) {
	long int n;
	(void)(src);

	if (readBuffer[0] != 0) {
		return 1;
	}

	n = read(sockfd, readBuffer, pcktMaxLength);
	if (n == -1)	/* no data are available from the socket */
		return 0;

	if (n == 0)	{
		printf("CrFwInStreamSocketConfigAction: ERROR reading from socket\n");
		return 0;
	}
	if (n == readBuffer[0]) 	/* a valid packet has arrived */
		return 1;

	if (n != readBuffer[0]) {
		printf("CrFwInStreamSocketConfigAction: invalid packet received from socket\n");
		return 0;
	}

	return 0;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamSocketSetPort(unsigned short n) {
	portno = n;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwInStreamSocketSetHost(char* name) {
	hostName = name;
}
