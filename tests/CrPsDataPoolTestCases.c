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
#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServTest.h>


/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsDataPoolTestCase1()
{
  /*Test the Service 17 Getter and Setter*/
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
    unsigned char test, pos;
    FwSmDesc_t inFactory, outFactory, outCmp, inRep, inCmd;
    CrFwPckt_t pckt1, pckt2;
        
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

  /* Perform a configuration check on the OutComponent */
  if (FwSmCheckRec(outCmp) != smSuccess)
      return 0;
  /* Check InCommand state */
  if (!CrFwCmpIsInConfigured(inCmd))
    return 0;
  
  /* Check InCommand state */
  if (!CrFwCmpIsInConfigured(inRep))
    return 0;
  
  /* Check the generic Setter and Getter*/
  /* use the maximal values of the variables*/
  ucharvalue= 255;
  ushortvalue=65535;
  uintvalue = 4294967295;

  /* Insert the Variables into the first position of the packet*/
  pos=0;
  /* Test the out Component packet with an uchar value*/
  CrPsSetUCharValue(outCmp, ucharvalue, pos);
  if (CrPsGetUCharValue(outCmp, pos) != ucharvalue)
    return 0;

  /* Test the in Report packet with an uchar value*/
  CrPsSetUCharValue(inRep, ucharvalue, pos);
  if (CrPsGetUCharValue(inRep, pos) != ucharvalue)
    return 0;  

  /* Test the in command packet with an uchar value*/
  CrPsSetUCharValue(inCmd, ucharvalue, pos);
  if (CrPsGetUCharValue(inCmd, pos) != ucharvalue)
    return 0;

  /* Test the out Component packet with an ushort value*/
  CrPsSetUShortValue(outCmp, ushortvalue, pos);
  if (CrPsGetUShortValue(outCmp, pos) != ushortvalue)
    return 0;

  /* Test the in Report packet with an ushort value*/
  CrPsSetUShortValue(inRep, ushortvalue, pos);
  if (CrPsGetUShortValue(inRep, pos) != ushortvalue)
    return 0;

  /* Test the in Command packet with an ushort value*/
  CrPsSetUShortValue(inCmd, ushortvalue, pos);
  if (CrPsGetUShortValue(inCmd, pos) != ushortvalue)
    return 0;

  /* Test the out Component packet with an uint value*/
  CrPsSetUIntValue(outCmp, uintvalue, pos);
  if (CrPsGetUIntValue(outCmp, pos) != uintvalue)
    return 0;

  /* Test the in Report packet with an uint value*/
  CrPsSetUIntValue(inRep, uintvalue, pos);
  if (CrPsGetUIntValue(inRep, pos) != uintvalue)
    return 0;

  /* Test the in Command packet with an uint value*/
  CrPsSetUIntValue(inCmd, uintvalue, pos);  
  if (CrPsGetUIntValue(inCmd, pos) != uintvalue)
    return 0;


  /* Insert the Variables into the last position of the packet*/
  pos=100;
  /* Test the out Component packet with an uchar value*/
  CrPsSetUCharValue(outCmp, ucharvalue, pos);
  if (CrPsGetUCharValue(outCmp, pos) != ucharvalue)
    return 0;

  /* Test the in Report packet with an uchar value*/
  CrPsSetUCharValue(inRep, ucharvalue, pos);
  if (CrPsGetUCharValue(inRep, pos) != ucharvalue)
    return 0;  

  /* Test the in command packet with an uchar value*/
  CrPsSetUCharValue(inCmd, ucharvalue, pos);
  if (CrPsGetUCharValue(inCmd, pos) != ucharvalue)
    return 0;
  
  pos=99;
  /* Test the out Component packet with an ushort value*/
  CrPsSetUShortValue(outCmp, ushortvalue, pos);
  if (CrPsGetUShortValue(outCmp, pos) != ushortvalue)
    return 0;

  /* Test the in Report packet with an ushort value*/
  CrPsSetUShortValue(inRep, ushortvalue, pos);
  if (CrPsGetUShortValue(inRep, pos) != ushortvalue)
    return 0;

  /* Test the in Command packet with an ushort value*/
  CrPsSetUShortValue(inCmd, ushortvalue, pos);
  if (CrPsGetUShortValue(inCmd, pos) != ushortvalue)
    return 0;

  pos=97;
  /* Test the out Component packet with an uint value*/
  CrPsSetUIntValue(outCmp, uintvalue, pos);
  if (CrPsGetUIntValue(outCmp, pos) != uintvalue)
    return 0;

  /* Test the in Report packet with an uint value*/
  CrPsSetUIntValue(inRep, uintvalue, pos);
  if (CrPsGetUIntValue(inRep, pos) != uintvalue)
    return 0;

  /* Test the in Command packet with an uint value*/
  CrPsSetUIntValue(inCmd, uintvalue, pos);  
  if (CrPsGetUIntValue(inCmd, pos) != uintvalue)
    return 0;

  /* Insert the Variables into a position of the packet that can not exist*/
  pos=101;
  /* Test the out Component packet with an uchar value*/
  CrPsSetUCharValue(outCmp, ucharvalue, pos);
  if (CrPsGetUCharValue(outCmp, pos) != 0)
    return 0;

  /* Test the in Report packet with an uchar value*/
  CrPsSetUCharValue(inRep, ucharvalue, pos);
  if (CrPsGetUCharValue(inRep, pos) != 0)
    return 0;  

  /* Test the in command packet with an uchar value*/
  CrPsSetUCharValue(inCmd, ucharvalue, pos);
  if (CrPsGetUCharValue(inCmd, pos) != 0)
    return 0;

  /* Test the out Component packet with an ushort value*/
  CrPsSetUShortValue(outCmp, ushortvalue, pos);
  if (CrPsGetUShortValue(outCmp, pos) != 0)
    return 0;

  /* Test the in Report packet with an ushort value*/
  CrPsSetUShortValue(inRep, ushortvalue, pos);
  if (CrPsGetUShortValue(inRep, pos) != 0)
    return 0;

  /* Test the in Command packet with an ushort value*/
  CrPsSetUShortValue(inCmd, ushortvalue, pos);
  if (CrPsGetUShortValue(inCmd, pos) != 0)
    return 0;

  /* Test the out Component packet with an uint value*/
  CrPsSetUIntValue(outCmp, uintvalue, pos);
  if (CrPsGetUIntValue(outCmp, pos) != 0)
    return 0;

  /* Test the in Report packet with an uint value*/
  CrPsSetUIntValue(inRep, uintvalue, pos);
  if (CrPsGetUIntValue(inRep, pos) != 0)
    return 0;

  /* Test the in Command packet with an uint value*/
  CrPsSetUIntValue(inCmd, uintvalue, pos);  
  if (CrPsGetUIntValue(inCmd, pos) != 0)
    return 0;

  /*Test a non existing packet type*/
  pos=0;
  /* Test the out Factory packet with an uchar value (there is no outFactory packet it should fail!)*/
  CrPsSetUCharValue(outFactory, ucharvalue, pos);
  if (CrPsGetUCharValue(outFactory, pos) != 0)
    return 0;
  
  /* Test the out Factory  packet with an ushort value (there is no outFactory packet it should fail!)*/
  CrPsSetUShortValue(outFactory, ushortvalue, pos);
  if (CrPsGetUShortValue(outFactory, pos) != 0)
    return 0;
  
  /* Test the out Factory packet with an uint value (there is no outFactory packet it should fail!)*/
  CrPsSetUIntValue(outFactory, uintvalue, pos);
  if (CrPsGetUIntValue(outFactory, pos) != 0)
    return 0;

  /* Release the OutComponent and reset the OutFactory */
  CrFwOutFactoryReleaseOutCmp(outCmp);
  CrFwCmpReset(outFactory);

  return 1;   
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsDataPoolTestCase3()
{
  /*Test the Service 3 Getter and Setter*/
 /* FwSmDesc_t outFactory, outCmp;
  unsigned short ushortvalue;*/

  /* Instantiate the OutFactory */
  /*outFactory = CrFwOutFactoryMake();*/

  /* Initialize and Configure OutFactory and check success */
 /* CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;
*/
  /* Create out component */
  /*outCmp = (FwSmDesc_t) CrFwOutFactoryMakeOutCmp(1, 1, 0, 100);*/

/*
  CrPsServReqVerifAccSuccParamSetTcPacketId(outCmp, ushortvalue);
  if (CrPsServReqVerifAccSuccParamGetTcPacketId != ushortvalue)
    return 0;
  
*/
  return 1;
}
