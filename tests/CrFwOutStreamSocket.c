/**
 * @file
 *
 * Implementation of Socket-Based OutStream.
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
#include "CrFwOutStreamSocket.h"
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

/** Set the port number (must be same as the port number specified in <code>CrFwOutStreamSocket.c</code> */
static unsigned short portno = 0;

/** The file descriptors for the socket */
static int sockfd;

/** The file descriptors for the socket */
static int newsockfd;

/** Socket variable */
static struct sockaddr_in cli_addr;

/** Socket variable */
static socklen_t clilen;

/**
 * Entry point for the thread which waits for the incoming connection from the InStream.
 * @param ptr unused argument (required with compatibility with pthread create function)
 */
static void* acceptThreadEntry(void* ptr);

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamSocketInitAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	struct sockaddr_in serv_addr, cli_addr;
	pthread_t acceptThread;
	pthread_attr_t attr;

	/* Create the socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("CrFwInStreamSocketInitAction, Socket creation");
		outStreamData->outcome = 0;
		return;
	}

	bzero((char*) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("CrFwOutStreamSocketInitAction, Bind Socket");
		outStreamData->outcome = 0;
		return;
	}
	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	/* Create thread which will accept the connection call from the InStream */
	pthread_attr_init(&attr);
	if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0) {
		perror("CrFwOutStreamSocketInitAction, set detached state");
		outStreamData->outcome = 0;
		return;
	}
	if (pthread_create(&acceptThread, &attr, acceptThreadEntry, NULL) < 0) {
		outStreamData->outcome = 0;
		return;
	};

	/* Execute default initialization action for OutStream */
	CrFwOutStreamDefInitAction(prDesc);
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamSocketShutdownAction(FwSmDesc_t smDesc) {
	CrFwOutStreamDefShutdownAction(smDesc);
	close(newsockfd);
	close(sockfd);
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutStreamSocketPcktHandover(CrFwPckt_t pckt) {
	unsigned int len = (int)CrFwPcktGetLength(pckt);
	long int n;

	n = write(newsockfd, pckt, len);

	if (n < 0)
		return 0;

	if (n != (int)CrFwPcktGetLength(pckt))  {
		printf("CrFwOutStreamSocketInitAction: error writing to socket\n");
		return 0;
	}

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
static void* acceptThreadEntry(void* ptr) {
	(void)(ptr);

	/* The call to accept blocks until a matching connect is done by the InStream */
	newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
	if (newsockfd < 0) {
		perror("CrFwInStreamSocketInitAction, Socket Accept");
	}
	return NULL;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamSocketInitCheck(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamData = (CrFwCmpData_t*)FwPrGetData(prDesc);

	if (portno < 2000)
		outStreamData->outcome = 0;
	else
		outStreamData->outcome = 1;

	return;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamSocketConfigCheck(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamData = (CrFwCmpData_t*)FwPrGetData(prDesc);

	if (newsockfd > 0)
		outStreamData->outcome = 1;
	else
		outStreamData->outcome = 0;

	return;
}

/* ---------------------------------------------------------------------------------------------*/
void CrFwOutStreamSocketSetPort(unsigned short n) {
	portno = n;
}

