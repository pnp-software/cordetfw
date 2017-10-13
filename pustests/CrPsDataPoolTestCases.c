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

#include <CrFwOutCmpSample1.h>
#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServTest.h>
#include <DataPool/CrPsDpServReqVerif.h>
#include <DataPool/CrPsDpHk.h>
#include <DataPool/CrPsDpEvt.h>
#include <Services/General/CrPsPktServReqVerif.h>
#include <CrPsDebug.h>


uint8_t testentry(uint32_t id, uint8_t size)
{
  uint8_t testset[size], testget[size], i, success;
  success = 0;

  /*to ensure that testget is not 0 or 255 set the first entry to any number*/
  testget[0] = 3;
  /*set all entries to minimal value*/
  for (i=0;i<size;i++)
  {
    testset[i] = 0;
  }
  setDpValue(id, &testset);
  if (getDpValue(id, &testget) == 0)
  {
    return 0;
  }
  for (i=0; i<size;i++)
  {
    if (testset[i] == testget[i]) 
    {
      success = 1;
    }
    else
    {
      return 0;      
    }
  }

  /*to ensure that testget is not 0 or 255 set the first entry to any number*/
  testget[0] = 3;

  /*set all entries to maximal value*/
  for (i=0;i<size;i++)
  {
    testset[i] = 255;
  }
  setDpValue(id, &testset);
  if (getDpValue(id, &testget) == 0)
  {
    return 0;
  }
  for (i=0; i<size;i++)
  {
    if (testset[i] == testget[i]) 
    {
      success = 1;
    }
    else
    {
      return 0;      
    }
  }

  /*to ensure that testget is not 0 or 255 set the first entry to any number*/
  testget[0] = 3;

  /*set all entries to random value*/
  for (i=0;i<size;i++)
  {
    testset[i] = rand() % 256;
  }
  setDpValue(id, &testset);
  if (getDpValue(id, &testget) == 0)
  {
    return 0;
  }
  for (i=0; i<size;i++)
  {
    if (testset[i] == testget[i]) 
    {
      success = 1;
    }
    else
    {
      return 0;      
    }
  }

  if (success == 1)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}



/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsDataPoolTestCase1()
{
  /* Test the generic Datapool Getter and Setter */
  unsigned int i, testnix;

  uint8_t testval;
  uint8_t maxval=255;
  
  /* get and reset ID 19 Value of the DataPool (AreYouAliveSrc) it should be 1*/
  DEBUGP_TSDP("GetDpSize(DpIdParamsLowest): %d, \n",getDpSize(DpIdParamsLowest));
  DEBUGP_TSDP("GetDpSize(DpIdVarsHighest+1): %d, \n",getDpSize(DpIdVarsHighest+1));

  DEBUGP_TSDP("getDpParamSize(DpIdParamsLowest): %d, \n",getDpParamSize(DpIdParamsLowest));
  DEBUGP_TSDP("getDpParamSize(DpIdVarsHighest+1): %d, \n",getDpParamSize(DpIdVarsHighest+1));  

  DEBUGP_TSDP("getDpVarSize(DpIdVarsLowest): %d, \n",getDpVarSize(DpIdVarsLowest));
  DEBUGP_TSDP("getDpVarSize(DpIdVarsHighest+1): %d, \n",getDpVarSize(DpIdVarsHighest+1));

  DEBUGP_TSDP("DpIdParamsLowest: %d \n", DpIdParamsLowest);
  DEBUGP_TSDP("DpIdParamsHighest: %d \n", DpIdParamsHighest);

  DEBUGP_TSDP("DpIdVarsLowest: %d \n", DpIdVarsLowest);
  DEBUGP_TSDP("DpIdVarsHighest: %d \n", DpIdVarsHighest);



  for (i=DpIdParamsLowest;i<=DpIdParamsHighest;i++)
  {
    DEBUGP_TSDP("getDpSize(%d): %d\n", i, getDpSize(i));
    DEBUGP_TSDP("getDpParamSize(%d): %d\n", i, getDpParamSize(i));
    DEBUGP_TSDP("getDpVarSize(%d): %d\n", i, getDpVarSize(i));
    if (testentry(i, getDpSize(i)) == 0)
    {
      return 0;
    }
  }

  for (i=DpIdVarsLowest;i<=DpIdVarsHighest;i++)
  {
    DEBUGP_TSDP("getDpSize(%d): %d\n", i, getDpSize(i));
    DEBUGP_TSDP("getDpParamSize(%d): %d\n", i, getDpParamSize(i));
    DEBUGP_TSDP("getDpVarSize(%d): %d\n", i, getDpVarSize(i));
    if (testentry(i, getDpSize(i)) == 0)
    {
      return 0;
    }
  }

  testval = 3;
  DEBUGP_TSDP("testval: %d \n", testval);
  DEBUGP_TSDP("Set a wrong Datapool Entry with a too high ID (hightes ID +1) to 255 and check if nothing is set! \n");
  setDpValue(DpIdVarsHighest+1, &maxval);
  testnix = getDpValue(DpIdVarsHighest+1, &testval);
  DEBUGP_TSDP("testval: %d \n", testval);
  if (testnix != 0)
  {
    return 0;
  }






  return 1;
}


/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsDataPoolTestCase2()
{
  /*Service 17: TestService Test the Datapool Getter and Setter*/
  unsigned int i, pos;
  unsigned short AreYouAliveSrc, areYouAliveSrcDp ;
  unsigned short destId, destIdDp;
  unsigned short* destIdArray, TestValue;

  initDpServTest();

  /* Set and re-read single data pool parameter */
  TestValue = 199;
  AreYouAliveSrc = 1;
  setDpAreYouAliveSrc(AreYouAliveSrc);
  areYouAliveSrcDp = getDpAreYouAliveSrc();
  DEBUGP_TSDP("CrFwDataPoolTestCase1 - AreYouAliveSrc: %d = %d \n", AreYouAliveSrc, areYouAliveSrcDp);
  if (AreYouAliveSrc != areYouAliveSrcDp)
    return 0;

  /* Set and re-read data pool parameter array (default values) */
  for (i=0; i<10; i++)
    {
      pos = i;
      destId = getDpOnBoardConnectDestLstItem(pos);
      setDpOnBoardConnectDestLstItem(pos, destId + 1);
      destIdDp = getDpOnBoardConnectDestLstItem(pos);
      DEBUGP_TSDP("CrFwDataPoolTestCase1 - default destId[%d]: %d = %d - 1 \n", pos, destId, destIdDp);
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
      DEBUGP_TSDP("CrFwDataPoolTestCase1 - preset destId[%d]: %d = %d \n", pos, destId, pos + 1);
      if ( destId != pos + 1 )
        return 0;
    }

  /* Get whole data pool parameter array previously set */
  destIdArray = getDpOnBoardConnectDestLstArray();
  for (i=0; i<10; i++)
    {
      pos = i;
      DEBUGP_TSDP("CrFwDataPoolTestCase1 - array destId[%d]: %d = %d \n", pos, destIdArray[pos], pos + 1);
      if ( destIdArray[pos] != pos + 1 )
        return 0;
    }

    /* get and reset ID 19 Value of the DataPool (AreYouAliveSrc) it should be 1*/
    getDpValue(19, &TestValue);
    if (TestValue != AreYouAliveSrc)
      return 0;

    setDpValue(19, &TestValue);
    if (getDpAreYouAliveSrc() != AreYouAliveSrc)
      return 0;
        
  return 1;
}

/* ---------------------------------------------------------------------------------------------*/

CrFwBool_t CrPsDataPoolTestCase3()
{
  /*Service 1: Request Verification Test the Datapool Getter and Setter*/

  initDpServReqVerif();

  return 0;

  return 1;   
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsDataPoolTestCase4()
{
  /*Service 3: Housekeeping Test the Datapool Getter and Setter*/

  initDpHk();

  return 0;

  return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsDataPoolTestCase5()
{
  /*Service 5: Event Reporting Test the Datapool Getter and Setter*/

  initDpEvt();

  return 0;

  return 1;
}