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
#include "Pckt/CrFwPckt.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include system files */
#include <stdio.h>
#include <unistd.h>

#include <Services/General/CrPsParamSetter.h>
#include <CrFwOutCmpSample1.h>
#include <DataPool/CrPsDataPool.h>
#include <DataPool/DpServTest.h>


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
    FwSmDesc_t outFactory, outCmp;
    CrFwPckt_t pckt;
        
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

  /* Initialize and Configure OutFactory and check success */
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;

  /* Allocate two OutComponents */
  outCmp = CrFwOutFactoryMakeOutCmp(17,2,0,0);

  /* Perform a configuration check on one of the OutComponents */
  if (FwSmCheckRec(outCmp) != smSuccess)
    {
      return 0;
    }
  
    ucharvalue= 50;
    ushortvalue=5000;
    uintvalue = 500000;
    
  
    CrPsSetUCharValue(outCmp, ucharvalue, 1);
    printf("\n\n\n\n\n");
  
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
    
    CrPsSetUShortValue(outCmp, ushortvalue, 2);

    
    pckt = CrFwOutCmpSample1GetPckt(outCmp);
    printf("\n");
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
    
    
    CrPsSetUIntValue(outCmp, uintvalue, 4);
    
    pckt = CrFwOutCmpSample1GetPckt(outCmp);
    printf("\n");
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

