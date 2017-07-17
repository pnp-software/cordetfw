/**
 * @file
 *
 * Implementation of test cases for DataPool Components.
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

/* Include framework files */
#include "CrFwCmpData.h"
#include "InStream/CrFwInStream.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutFactory/CrFwOutFactory.h"
#include "InFactory/CrFwInFactory.h"
#include "Pckt/CrFwPckt.h"

#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include system files */
#include <stdio.h>
#include <unistd.h>

#include <Services/General/CrPsParamSetter.h>
#include <Services/General/CrPsParamGetter.h>
#include <CrFwOutCmpSample1.h>
#include <DataPool/CrPsDataPool.h>
#include <DataPool/CrPsDpServTest.h>


/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsDataPoolTestCase1()
{
  unsigned int i, pos;
  unsigned short AreYouAliveSrc, areYouAliveSrcDp ;
  unsigned short destId, destIdDp;
  unsigned short* destIdArray, TestValue;

  /* Set and re-read single data pool parameter */

  AreYouAliveSrc = 1;
  setDpAreYouAliveSrc(AreYouAliveSrc);
  areYouAliveSrcDp = getDpAreYouAliveSrc();
  printf ("CrFwDataPoolTestCase1 - AreYouAliveSrc: %d = %d \n", AreYouAliveSrc, areYouAliveSrcDp);
  if (AreYouAliveSrc != areYouAliveSrcDp)
    return 0;

  /* Set and re-read data pool parameter array (default values) */
  for (i=0; i<10; i++)
    {
      pos = i;
      destId = getDpOnBoardConnectDestLstItem(pos);
      setDpOnBoardConnectDestLstItem(pos, destId + 1);
      destIdDp = getDpOnBoardConnectDestLstItem(pos);
      printf ("CrFwDataPoolTestCase1 - default destId[%d]: %d = %d - 1 \n", pos, destId, destIdDp);
      if ( destId != destIdDp - 1 )
        return 0;
    }

  /* Set and re-read data pool parameter array (preset values) */
  for (i=0; i<10; i++)
    {
      pos = i;
      setDpOnBoardConnectDestLstItem(pos, pos + 1);
    }
  for (i=0; i<10; i++)
    {
      pos = i;
      destId = getDpOnBoardConnectDestLstItem(pos);
      printf ("CrFwDataPoolTestCase1 - preset destId[%d]: %d = %d \n", pos, destId, pos + 1);
      if ( destId != pos + 1 )
        return 0;
    }

  /* Get whole data pool parameter array previously set */
  destIdArray = getDpOnBoardConnectDestLstArray();
  for (i=0; i<10; i++)
    {
      pos = i;
      printf ("CrFwDataPoolTestCase1 - array destId[%d]: %d = %d \n", pos, destIdArray[pos], pos + 1);
      if ( destIdArray[pos] != pos + 1 )
        return 0;
    }

    
    /* get and reset ID 0 Value of the DataPool (AreYouAliveSrc) it should be 1*/
    getDpValue(0, &TestValue);
    if (TestValue != AreYouAliveSrc)
      return 0;
    
    setDpValue(0, &TestValue);
    if (getDpAreYouAliveSrc() != AreYouAliveSrc)
      return 0;

        
  return 1;
}

/* ---------------------------------------------------------------------------------------------*/

CrFwBool_t CrPsDataPoolTestCase2()
{
    /*Test the generic functionality of the ParamSetter*/
    unsigned char ucharvalue;
    unsigned int uintvalue, value, bitoffset, nbits;
    unsigned short ushortvalue;
    unsigned char* dummydest;
    unsigned char test;
    FwSmDesc_t inFactory, outFactory, outCmp, inRep, inCmd;
    CrFwPckt_t pckt, pckt1, pckt2;
        
    /* test the putnbits8 function from the paramsetter*/
    /* set a variable to 1 and check if it works*/
    test = 97;
    dummydest = &test;

    value = 0;
    bitoffset = 0;
    nbits = 7;
    PutNBits8(value, bitoffset, nbits, dummydest);

    value = 1;
    bitoffset=7;
    nbits=1;
    PutNBits8(value, bitoffset, nbits, dummydest);

    if (*dummydest != 1)
      return 0;
    
  /* Instantiate the OutFactory */
  outFactory = CrFwOutFactoryMake();
  inFactory = CrFwInFactoryMake();
      printf("aa");
  /* Initialize and Configure OutFactory and check success */
  CrFwCmpInit(outFactory);
  CrFwCmpInit(inFactory);
  CrFwCmpReset(outFactory);
  CrFwCmpReset(inFactory);  
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;
  if (!CrFwCmpIsInConfigured(inFactory))
    return 0;

  /* Allocate three Components */
    /* Allocate the Sample1 InCommand */
  pckt1 = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt1,17);
  CrFwPcktSetServSubType(pckt1,2);
  CrFwPcktSetDiscriminant(pckt1,0);  
  CrFwPcktSetCmdRepId(pckt1,0);
  CrFwPcktSetSrc(pckt1,1);
  CrFwPcktSetDest(pckt1,1);
  CrFwPcktSetGroup(pckt1,1);
  CrFwPcktSetAckLevel(pckt1, 1, 1, 1, 1);	/* all acknowledgement of success */
  CrFwPcktSetSeqCnt(pckt1,2);  

  pckt2 = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt2,17);
  CrFwPcktSetServSubType(pckt2,1);
  CrFwPcktSetDiscriminant(pckt2,0);  
  CrFwPcktSetCmdRepId(pckt2,0);
  CrFwPcktSetSrc(pckt2,1);
  CrFwPcktSetDest(pckt2,1);
  CrFwPcktSetGroup(pckt2,1);
  CrFwPcktSetAckLevel(pckt2, 1, 1, 1, 1);	/* all acknowledgement of success */
  CrFwPcktSetSeqCnt(pckt2,2); 
  outCmp = CrFwOutFactoryMakeOutCmp(17,2,0,100);
  inRep = CrFwInFactoryMakeInRep(pckt1);
  inCmd = CrFwInFactoryMakeInCmd(pckt2);

  /* Perform a configuration check on one of the OutComponents */
  if (FwSmCheckRec(outCmp) != smSuccess)
    {
      return 0;
    }
  /* Check InCommand state */
  if (!CrFwCmpIsInConfigured(inCmd))
    return 0;
  
  /* Check InCommand state */
  if (!CrFwCmpIsInConfigured(inRep))
    return 0;
  
  ucharvalue= 234;
  ushortvalue=12345;
  uintvalue = 5554446;
    
  printf("\n\n\n\n\n");
  CrPsSetUCharValue(outCmp, ucharvalue, 1);
  CrPsSetUCharValue(inRep, ucharvalue, 1);
  CrPsSetUCharValue(inCmd, ucharvalue, 1);
  CrPsSetUCharValue(outFactory, ucharvalue, 1);
  printf("CrPsGetUCharValue: %d \n",CrPsGetUCharValue(outCmp,1) );
  printf("CrPsGetUCharValue: %d \n",CrPsGetUCharValue(inRep,1) );
  printf("CrPsGetUCharValue: %d \n",CrPsGetUCharValue(inCmd,1) );
  printf("CrPsGetUCharValue: %d \n",CrPsGetUCharValue(outFactory,1) );
    
    
  pckt = CrFwOutCmpSample1GetPckt(outCmp);
  printf("Test 13: %u \n",pckt[13]);
  printf("Test 14: %u \n",pckt[14]);
  printf("Test 15: %u \n",pckt[15]);
  printf("Test 16: %u \n",pckt[16]);
  printf("Test 17: %u \n",pckt[17]);
  printf("Test 18: %u \n",pckt[18]);
  printf("Test 19: %u \n",pckt[19]);
  printf("Test 20: %u \n",pckt[20]);  
  printf("Test 21: %u \n",pckt[21]);
  printf("Test 22: %u \n",pckt[22]);
  printf("Test 23: %u \n",pckt[23]);
  printf("Test 24: %u \n",pckt[24]);
  printf("Test 25: %u \n",pckt[25]);
  printf("Test 26: %u \n",pckt[26]);
  printf("Test 27: %u \n",pckt[27]);
  printf("Test 28: %u \n",pckt[28]);
  printf("Test 29: %u \n",pckt[29]);
  printf("Test 30: %u \n",pckt[30]);  
  
  
  CrPsSetUShortValue(outCmp, ushortvalue, 5);
  CrPsSetUShortValue(inRep, ushortvalue, 5);
  CrPsSetUShortValue(inCmd, ushortvalue, 5);
  CrPsSetUShortValue(outFactory, ucharvalue, 5);
  printf("CrPsGetUShortValue: %d \n",CrPsGetUShortValue(outCmp,5) );
  printf("CrPsGetUShortValue: %d \n",CrPsGetUShortValue(inRep,5) );
  printf("CrPsGetUShortValue: %d \n",CrPsGetUShortValue(inCmd,5) );
  printf("CrPsGetUShortValue: %d \n",CrPsGetUShortValue(outFactory,5) );
  
  
  pckt = CrFwOutCmpSample1GetPckt(outCmp);
  printf("\n");
  printf("CrPsGetUShortValue: %d \n",CrPsGetUShortValue(outCmp,2) );
  printf("Test 13: %u \n",pckt[13]);
  printf("Test 14: %u \n",pckt[14]);
  printf("Test 15: %u \n",pckt[15]);
  printf("Test 16: %u \n",pckt[16]);
  printf("Test 17: %u \n",pckt[17]);
  printf("Test 18: %u \n",pckt[18]);
  printf("Test 19: %u \n",pckt[19]);
  printf("Test 20: %u \n",pckt[20]);  
  printf("Test 21: %u \n",pckt[21]);
  printf("Test 22: %u \n",pckt[22]);
  printf("Test 23: %u \n",pckt[23]);
  printf("Test 24: %u \n",pckt[24]);
  printf("Test 25: %u \n",pckt[25]);
  printf("Test 26: %u \n",pckt[26]);
  printf("Test 27: %u \n",pckt[27]);
  printf("Test 28: %u \n",pckt[28]);
  printf("Test 29: %u \n",pckt[29]);
  printf("Test 30: %u \n",pckt[30]);   
  
  
  CrPsSetUIntValue(outCmp, uintvalue, 10);
  CrPsSetUIntValue(inRep, uintvalue, 10);
  CrPsSetUIntValue(inCmd, uintvalue, 10);
  CrPsSetUIntValue(outFactory, uintvalue, 10);
  printf("CrPsGetUIntValue: %d \n",CrPsGetUIntValue(outCmp,10) );
  printf("CrPsGetUIntValue: %d \n",CrPsGetUIntValue(inRep,10) );
  printf("CrPsGetUIntValue: %d \n",CrPsGetUIntValue(inCmd,10) );
  printf("CrPsGetUIntValue: %d \n",CrPsGetUIntValue(outFactory,10) );
  pckt = CrFwOutCmpSample1GetPckt(outCmp);
  printf("\n");  
  printf("CrPsGetUIntValue: %d \n",CrPsGetUIntValue(outCmp,4) );
  printf("Test 13: %u \n",pckt[13]);
  printf("Test 14: %u \n",pckt[14]);
  printf("Test 15: %u \n",pckt[15]);
  printf("Test 16: %u \n",pckt[16]);
  printf("Test 17: %u \n",pckt[17]);
  printf("Test 18: %u \n",pckt[18]);
  printf("Test 19: %u \n",pckt[19]);
  printf("Test 20: %u \n",pckt[20]);  
  printf("Test 21: %u \n",pckt[21]);
  printf("Test 22: %u \n",pckt[22]);
  printf("Test 23: %u \n",pckt[23]);
  printf("Test 24: %u \n",pckt[24]);
  printf("Test 25: %u \n",pckt[25]);
  printf("Test 26: %u \n",pckt[26]);
  printf("Test 27: %u \n",pckt[27]);
  printf("Test 28: %u \n",pckt[28]);
  printf("Test 29: %u \n",pckt[29]);
  printf("Test 30: %u \n",pckt[30]);   
  
  /*TODO .. report error if Value not set*/
  /* Release the OutComponent and reset the OutFactory */
  CrFwOutFactoryReleaseOutCmp(outCmp);
  CrFwCmpReset(outFactory);

  return 1;   
}

