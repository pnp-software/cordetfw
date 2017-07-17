/**
 * @file
 *
 * Implementation of test cases for Service Components.
 *
 * @author Christian Reimers <christian.reimersy@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * @copyright Department of Astrophysics, University of Vienna, 2017, All Rights Reserved
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

#include "CrFwRepErrStub.h"
#include "CrFwInStreamSocket.h"
#include "CrFwClientSocket.h"
#include "CrFwServerSocket.h"
#include "CrFwOutStreamSocket.h"
#include "CrFwInStreamTestCases.h"
#include "CrFwRepInCmdOutcomeStub.h"
#include "CrFwInStreamStub.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include configuration files */
#include "CrFwInStreamUserPar.h" /* TODO: CrPsInStreamUserPar.h" */
#include "CrFwOutRegistryUserPar.h" /* TODO: CrPsOutRegistryUserPar.h */
/* Include framework files */
#include "CrFwCmpData.h"
#include "OutRegistry/CrFwOutRegistry.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "InCmd/CrFwInCmd.h"
#include "InFactory/CrFwInFactory.h"
#include "OutFactory/CrFwOutFactory.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"


#include "Services/RequestVerification/OutCmp/CrPsReqVerifAccFail.h"
#include "Services/RequestVerification/OutCmp/CrPsReqVerifAccSucc.h"
#include "Services/RequestVerification/OutCmp/CrPsReqVerifProgFail.h"
#include "Services/RequestVerification/OutCmp/CrPsReqVerifProgSucc.h"
#include "Services/RequestVerification/OutCmp/CrPsReqVerifStartFail.h"
#include "Services/RequestVerification/OutCmp/CrPsReqVerifStartSucc.h"
#include "Services/RequestVerification/OutCmp/CrPsReqVerifTermFail.h"
#include "Services/RequestVerification/OutCmp/CrPsReqVerifTermSucc.h"


/* Include system files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsServVeriTestCase1()
{
  FwSmDesc_t inFactory, inCmd;
  CrFwPckt_t pckt;
  
  /* Instantiate the InFactory */
  inFactory = CrFwInFactoryMake();

  /* Initialize and Configure InFactory and check success */
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  if (!CrFwCmpIsInConfigured(inFactory))
    return 0;

   printf("nummer: %d \n",CrFwPcktGetNOfAllocated());   
  /* Allocate the Sample1 InCommand */
  pckt = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,1);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetCmdRepId(pckt,0);
  CrFwPcktSetSrc(pckt,1);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt, 1, 1, 1, 1);	/* all acknowledgement of success */
  CrFwPcktSetSeqCnt(pckt,2);
  inCmd = CrFwInFactoryMakeInCmd(pckt);
  
  /* Checking to get coverage*/
  /* there is no content in any of the functions so nothing gan be probed*/
  printf("checking ---CrPsReqVerifAccFail.c---\n");
  CrPsReqVerifAccFailUpdateAction(inCmd);
  
  printf("checking ---CrPsReqVerifAccSucc.c---\n");
  CrPsReqVerifAccSuccUpdateAction(inCmd);
  
  printf("checking ---CrPsReqVerifProgFail.c---\n");
  CrPsReqVerifProgFailUpdateAction(inCmd);
  
  printf("checking ---CrPsReqVerifProgSucc.c---\n");
  CrPsReqVerifProgSuccUpdateAction(inCmd);
  
  printf("checking ---CrPsReqVerifStartFail.c---\n");
  CrPsReqVerifStartFailUpdateAction(inCmd);
  
  printf("checking ---CrPsReqVerifStartSucc.c---\n");
  CrPsReqVerifStartSuccUpdateAction(inCmd);
  
  printf("checking ---CrPsReqVerifTermFail.c---\n");
  CrPsReqVerifTermFailUpdateAction(inCmd);
  
  printf("checking ---CrPsReqVerifTermSucc.c---\n");
  CrPsReqVerifTermSuccUpdateAction(inCmd);
  
  printf("done with checking ------\n");

  /* Shutdown the InFactory and check that no InCommands are allocated */
  CrFwCmpShutdown(inFactory);
  if (CrFwCmpIsStarted(inFactory) != 0)
    return 0;
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  printf("nummer: %d \n",CrFwPcktGetNOfAllocated());

  /* Restart and initialize the InFactory */
  FwSmStart(inFactory);
  CrFwCmpInit(inFactory);
  printf("nummer: %d \n",CrFwPcktGetNOfAllocated());  
  return 1;
}

/* ---------------------------------------------------------------------------------------------*/

CrFwBool_t CrPsServVeriTestCase2()
{



  return 1;
}

/* ---------------------------------------------------------------------------------------------*/
