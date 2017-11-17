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
#include <DataPool/CrPsDpServHk.h>
#include <DataPool/CrPsDpServEvt.h>
#include <Services/General/CrPsPktServReqVerif.h>
#include <CrPsDebug.h>

#define MAX_CHAR 255u
#define MAX_SHORT 65535u
#define MAX_INT 4294967295u
#define MIN_VAL 0u

uint8_t testentry(uint32_t id, uint8_t size)
{
  uint8_t testset[size], testget[size], dest[size], i, success;
  size_t lene;
  uint32_t nume;
  success = 0;

  /*to ensure that testget is not 0 or 255 set the first entry to any number*/
  testget[0] = 3;
  dest[0] = 3;

  /*set all entries to minimal value*/
  for (i=0;i<size;i++)
  {
    testset[i] = MIN_VAL;
  }
  if (setDpValue(id, &testset) == 0)
  {
    return 0;
  }
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
  getDpValueEx(id, dest, &lene, &nume);
  if (memcmp(testset, dest, size))
  {
    return 0;
  }
  if (lene*nume != size)
  {
    return 0;
  }


  /*to ensure that testget is not 0 or 255 set the first entry to any number*/
  testget[0] = 3;
  dest[0] = 3;

  /*set all entries to maximal value*/
  for (i=0;i<size;i++)
  {
    testset[i] = MAX_CHAR;
  }
  if (setDpValue(id, &testset) == 0)
  {
    return 0;
  }
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
  getDpValueEx(id, dest, &lene, &nume);
  if (memcmp(testset, dest, size))
  {
    return 0;
  }
  if (lene*nume != size)
  {
    return 0;
  }

  /*to ensure that testget is not 0 or 255 set the first entry to any number*/
  testget[0] = 3;
  dest[0] = 3;

  /*set all entries to random value*/
  for (i=0;i<size;i++)
  {
    testset[i] = rand() % MAX_CHAR+1;
  }
  if (setDpValue(id, &testset) == 0)
  {
    return 0;
  }
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
  getDpValueEx(id, dest, &lene, &nume);
  if (memcmp(testset, dest, size))
  {
    return 0;
  }
  if (lene*nume != size)
  {
    return 0;
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

/* TODO size_t getDpValueEx(ParameterId_t id, void* dest, size_t* pElementLength, unsigned int* pNElements) aufrufen auch für id == NULL !!*/

/* TODO size_t getDpSize(ParameterId_t id) if id == NULL aufrufen "" */

/* TODO size_t getDpVarSize(ParameterId_t id) aufrufen !!*/

/* TODO size_t getDpParamSize(ParameterId_t id) aufrufen !!*/



/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsDataPoolTestCase1()
{
  /* Test the generic Datapool Getter and Setter */
  unsigned int i;
  size_t lene;
  uint32_t nume;
  uint8_t dest[1];
  uint8_t testval;
  uint8_t maxval=MAX_CHAR;
  
  
  #if 0
  DEBUGP_TSDP("GetDpSize(DpIdParamsLowest): %lu, \n",getDpSize(DpIdParamsLowest));
  DEBUGP_TSDP("GetDpSize(DpIdVarsHighest+1): %lu, \n",getDpSize(DpIdVarsHighest+1));

  DEBUGP_TSDP("getDpParamSize(DpIdParamsLowest): %lu, \n",getDpParamSize(DpIdParamsLowest));
  DEBUGP_TSDP("getDpParamSize(DpIdVarsHighest+1): %lu, \n",getDpParamSize(DpIdVarsHighest+1));  

  DEBUGP_TSDP("getDpVarSize(DpIdVarsLowest): %lu, \n",getDpVarSize(DpIdVarsLowest));
  DEBUGP_TSDP("getDpVarSize(DpIdVarsHighest+1): %lu, \n",getDpVarSize(DpIdVarsHighest+1));

  DEBUGP_TSDP("DpIdParamsLowest: %d \n", DpIdParamsLowest);
  DEBUGP_TSDP("DpIdParamsHighest: %d \n", DpIdParamsHighest);

  DEBUGP_TSDP("DpIdVarsLowest: %d \n", DpIdVarsLowest);
  DEBUGP_TSDP("DpIdVarsHighest: %d \n", DpIdVarsHighest);
#endif


  for (i=DpIdParamsLowest;i<=DpIdParamsHighest;i++)
  {
    DEBUGP_TSDP("getDpSize(%d): %lu\n", i, getDpSize(i));
    DEBUGP_TSDP("getDpParamSize(%d): %lu\n", i, getDpParamSize(i));
    DEBUGP_TSDP("getDpVarSize(%d): %lu\n", i, getDpVarSize(i));
    if (getDpSize(i) != getDpParamSize(i))
    {
      return 0;
    }
    if (testentry(i, getDpSize(i)) == 0)
    {
      return 0;
    }
  }

  for (i=DpIdVarsLowest;i<=DpIdVarsHighest;i++)
  {
    DEBUGP_TSDP("getDpSize(%d): %lu\n", i, getDpSize(i));
    DEBUGP_TSDP("getDpParamSize(%d): %lu\n", i, getDpParamSize(i));
    DEBUGP_TSDP("getDpVarSize(%d): %lu\n", i, getDpVarSize(i));
    if (getDpSize(i) != getDpVarSize(i))
    {
      return 0;
    }
    if (testentry(i, getDpSize(i)) == 0)
    {
      return 0;
    }
  }

  testval = 3;
  DEBUGP_TSDP("testval: %d \n", testval);
  DEBUGP_TSDP("Set a wrong Datapool Entry with a too high ID (hightes ID +1) to 255 and check if nothing is set! \n");
  
  if (setDpValue(DpIdVarsHighest+1, &maxval) != 0)
  {
    return 0;
  }
  if (getDpValue(DpIdVarsHighest+1, &testval) != 0)
  {
    return 0;
  }
  if (getDpSize(DpIdVarsHighest+1) != 0)
  {
    return 0;
  }
  if( getDpValueEx(DpIdVarsHighest+1, dest, &lene, &nume) != 0)
  {
    return 0;
  }

  return 1;
}


/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsDataPoolTestCase2()
{
  /*Service 17: TestService Test the Datapool Getter and Setter*/
  
  unsigned int i, pos, len;
  unsigned short destId, destIdDp;
  unsigned short* destIdArray;
  unsigned short* testarrayptr;
  DpServTestParams_t test; 
  
  initDpServTest();

  /* Set and re-read single data pool parameter */
  setDpAreYouAliveTimeOut(MIN_VAL);
  DEBUGP_TSDP("getDpAreYouAliveTimeOut() -> MIN_VAL: %u \n",getDpAreYouAliveTimeOut());
  if (getDpAreYouAliveTimeOut() != MIN_VAL)
  {
    return 0;
  }
  setDpAreYouAliveTimeOut(MAX_INT);
  DEBUGP_TSDP("getDpAreYouAliveTimeOut() -> MAX_INT: %u \n",getDpAreYouAliveTimeOut());
  if (getDpAreYouAliveTimeOut() != MAX_INT)
  {
    return 0;
  }

  setDpAreYouAliveSrc(MIN_VAL);
  DEBUGP_TSDP("getDpAreYouAliveSrc() -> MIN_VAL: %u \n",getDpAreYouAliveSrc());
  if (getDpAreYouAliveSrc() != MIN_VAL)
  {
    return 0;
  }

  setDpAreYouAliveSrc(MAX_SHORT);
  DEBUGP_TSDP("getDpAreYouAliveSrc() -> MAX_SHORT: %u \n",getDpAreYouAliveSrc());
  if (getDpAreYouAliveSrc() != MAX_SHORT)
  {
    return 0;
  }

  setDpOnBoardConnectDest(MIN_VAL);
  DEBUGP_TSDP("getDpOnBoardConnectDest() -> MIN_VAL: %u \n",getDpOnBoardConnectDest());
  if (getDpOnBoardConnectDest() != MIN_VAL)
  {
    return 0;
  }
  setDpOnBoardConnectDest(MAX_SHORT);
  DEBUGP_TSDP("getDpOnBoardConnectDest() -> MAX_SHORT: %u \n",getDpOnBoardConnectDest());
  if (getDpOnBoardConnectDest() != MAX_SHORT)
  {
    return 0;
  }

  len = sizeof(test.OnBoardConnectDestLst)/sizeof(test.OnBoardConnectDestLst[0]); 
  DEBUGP_TSDP("Arraysize of OnBoardConnectDestLst: %u Elements \n", len);
  for (i=0; i<len; i++)
  {
    setDpOnBoardConnectDestLstItem(i, MIN_VAL);
    DEBUGP_TSDP("getDpOnBoardConnectDestLstItem(i) -> MIN_VAL: %u \n",getDpOnBoardConnectDestLstItem(i));
    if(getDpOnBoardConnectDestLstItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpOnBoardConnectDestLstItem(i, MAX_SHORT);
    DEBUGP_TSDP("getDpOnBoardConnectDestLstItem(i) -> MAX_SHORT: %u \n",getDpOnBoardConnectDestLstItem(i));
    if(getDpOnBoardConnectDestLstItem(i) != MAX_SHORT)
    {
      return 0;
    }
  }
  testarrayptr = getDpOnBoardConnectDestLstArray();
  for (i =0;i<len;i++)
  {
    DEBUGP_TSDP("testarrayptr[i] -> MAX_SHORT: %u \n",testarrayptr[i]);
    if(testarrayptr[i] != MAX_SHORT)
      return 0;
  }


  initDpServTest();
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


  return 1;
}

/* ---------------------------------------------------------------------------------------------*/

CrFwBool_t CrPsDataPoolTestCase3()
{
  /*Service 1: Request Verification Test the Datapool Getter and Setter*/

  /*initialize Request Verification Service Datapool Entries*/
  initDpServReqVerif();

  /*Set and Get all Datapool Entries with 0 and maximal value*/
  setDpfailCodeAccFailed(MIN_VAL);
  DEBUGP_TSDP("getDpfailCodeAccFailed() -> MIN_VAL: %u \n",getDpfailCodeAccFailed());
  if (getDpfailCodeAccFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpfailCodeAccFailed(MAX_SHORT);
  DEBUGP_TSDP("getDpfailCodeAccFailed() -> MAX_SHORT: %u \n",getDpfailCodeAccFailed());
  if (getDpfailCodeAccFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDpfailCodePrgrFailed(MIN_VAL);
  DEBUGP_TSDP("getDpfailCodePrgrFailed() -> MIN_VAL: %u \n",getDpfailCodePrgrFailed());
  if (getDpfailCodePrgrFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpfailCodePrgrFailed(MAX_SHORT);
  DEBUGP_TSDP("getDpfailCodePrgrFailed() -> MAX_SHORT: %u \n",getDpfailCodePrgrFailed());
  if (getDpfailCodePrgrFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDpfailCodeStartFailed(MIN_VAL);
  DEBUGP_TSDP("getDpfailCodeStartFailed() -> MIN_VAL: %u \n",getDpfailCodeStartFailed());
  if (getDpfailCodeStartFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpfailCodeStartFailed(MAX_SHORT);
  DEBUGP_TSDP("getDpfailCodeStartFailed() -> MAX_SHORT: %u \n",getDpfailCodeStartFailed());
  if (getDpfailCodeStartFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDpfailCodeTermFailed(MIN_VAL);
  DEBUGP_TSDP("getDpfailCodeTermFailed() -> MIN_VAL: %u \n",getDpfailCodeTermFailed());
  if (getDpfailCodeTermFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpfailCodeTermFailed(MAX_SHORT);
  DEBUGP_TSDP("getDpfailCodeTermFailed() -> MAX_SHORT: %u \n",getDpfailCodeTermFailed());
  if (getDpfailCodeTermFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDpinvDestRerouting(MIN_VAL);
  DEBUGP_TSDP("getDpinvDestRerouting() -> MIN_VAL: %u \n",getDpinvDestRerouting());
  if (getDpinvDestRerouting() != MIN_VAL)
  {
    return 0;
  }
  setDpinvDestRerouting(MAX_SHORT);
  DEBUGP_TSDP("getDpinvDestRerouting() -> MAX_SHORT: %u \n",getDpinvDestRerouting());
  if (getDpinvDestRerouting() != MAX_SHORT)
  {
    return 0;
  }

  setDpnOfAccFailed(MIN_VAL);
  DEBUGP_TSDP("getDpnOfAccFailed() -> MIN_VAL: %u \n",getDpnOfAccFailed());
  if (getDpnOfAccFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfAccFailed(MAX_INT);
  DEBUGP_TSDP("getDpnOfAccFailed() -> MAX_INT: %u \n",getDpnOfAccFailed());
  if (getDpnOfAccFailed() != MAX_INT)
  {
    return 0;
  }

  setDpnOfPrgrFailed(MIN_VAL);
  DEBUGP_TSDP("getDpnOfPrgrFailed() -> MIN_VAL: %u \n",getDpnOfPrgrFailed());
  if (getDpnOfPrgrFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfPrgrFailed(MAX_INT);
  DEBUGP_TSDP("getDpnOfPrgrFailed() -> MAX_INT: %u \n",getDpnOfPrgrFailed());
  if (getDpnOfPrgrFailed() != MAX_INT)
  {
    return 0;
  }

  setDpnOfReroutingFailed(MIN_VAL);
  DEBUGP_TSDP("getDpnOfReroutingFailed() -> MIN_VAL: %u \n",getDpnOfReroutingFailed());
  if (getDpnOfReroutingFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfReroutingFailed(MAX_INT);
  DEBUGP_TSDP("getDpnOfReroutingFailed() -> MAX_INT: %u \n",getDpnOfReroutingFailed());
  if (getDpnOfReroutingFailed() != MAX_INT)
  {
    return 0;
  }

  setDpnOfStartFailed(MIN_VAL);
  DEBUGP_TSDP("getDpnOfStartFailed() -> MIN_VAL: %u \n",getDpnOfStartFailed());
  if (getDpnOfStartFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfStartFailed(MAX_INT);
  DEBUGP_TSDP("getDpnOfStartFailed() -> MAX_INT: %u \n",getDpnOfStartFailed());
  if (getDpnOfStartFailed() != MAX_INT)
  {
    return 0;
  }

  setDpnOfTermFailed(MIN_VAL);
  DEBUGP_TSDP("getDpnOfTermFailed() -> MIN_VAL: %u \n",getDpnOfTermFailed());
  if (getDpnOfTermFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfTermFailed(MAX_INT);
  DEBUGP_TSDP("getDpnOfTermFailed() -> MAX_INT: %u \n",getDpnOfTermFailed());
  if (getDpnOfTermFailed() != MAX_INT)
  {
    return 0;
  }

  setDppcktIdAccFailed(MIN_VAL);
  DEBUGP_TSDP("getDppcktIdAccFailed() -> MIN_VAL: %u \n",getDppcktIdAccFailed());
  if (getDppcktIdAccFailed() != MIN_VAL)
  {
    return 0;
  }
  setDppcktIdAccFailed(MAX_SHORT);
  DEBUGP_TSDP("getDppcktIdAccFailed() -> MAX_SHORT: %u \n",getDppcktIdAccFailed());
  if (getDppcktIdAccFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDppcktIdPrgrFailed(MIN_VAL);
  DEBUGP_TSDP("getDppcktIdPrgrFailed() -> MIN_VAL: %u \n",getDppcktIdPrgrFailed());
  if (getDppcktIdPrgrFailed() != MIN_VAL)
  {
    return 0;
  }
  setDppcktIdPrgrFailed(MAX_SHORT);
  DEBUGP_TSDP("getDppcktIdPrgrFailed() -> MAX_SHORT: %u \n",getDppcktIdPrgrFailed());
  if (getDppcktIdPrgrFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDppcktIdReroutingFailed(MIN_VAL);
  DEBUGP_TSDP("getDppcktIdReroutingFailed() -> MIN_VAL: %u \n",getDppcktIdReroutingFailed());
  if (getDppcktIdReroutingFailed() != MIN_VAL)
  {
    return 0;
  }
  setDppcktIdReroutingFailed(MAX_SHORT);
  DEBUGP_TSDP("getDppcktIdReroutingFailed() -> MAX_SHORT: %u \n",getDppcktIdReroutingFailed());
  if (getDppcktIdReroutingFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDppcktIdStartFailed(MIN_VAL);
  DEBUGP_TSDP("getDppcktIdStartFailed() -> MIN_VAL: %u \n",getDppcktIdStartFailed());
  if (getDppcktIdStartFailed() != MIN_VAL)
  {
    return 0;
  }
  setDppcktIdStartFailed(MAX_SHORT);
  DEBUGP_TSDP("getDppcktIdStartFailed() -> MAX_SHORT: %u \n",getDppcktIdStartFailed());
  if (getDppcktIdStartFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDppcktIdTermFailed(MIN_VAL);
  DEBUGP_TSDP("getDppcktIdTermFailed() -> MIN_VAL: %u \n",getDppcktIdTermFailed());
  if (getDppcktIdTermFailed() != MIN_VAL)
  {
    return 0;
  }
  setDppcktIdTermFailed(MAX_SHORT);
  DEBUGP_TSDP("getDppcktIdTermFailed() -> MAX_SHORT: %u \n",getDppcktIdTermFailed());
  if (getDppcktIdTermFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDpstepPrgrFailed(MIN_VAL);
  DEBUGP_TSDP("getDpstepPrgrFailed() -> MIN_VAL: %u \n",getDpstepPrgrFailed());
  if (getDpstepPrgrFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpstepPrgrFailed(MAX_SHORT);
  DEBUGP_TSDP("getDpstepPrgrFailed() -> MAX_SHORT: %u \n",getDpstepPrgrFailed());
  if (getDpstepPrgrFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDpverFailData(MIN_VAL);
  DEBUGP_TSDP("getDpverFailData() -> MIN_VAL: %u \n",getDpverFailData());
  if (getDpverFailData() != MIN_VAL)
  {
    return 0;
  }
  setDpverFailData(MAX_INT);
  DEBUGP_TSDP("getDpverFailData() -> MAX_INT: %u \n",getDpverFailData());
  if (getDpverFailData() != MAX_INT)
  {
    return 0;
  }

  return 1;   
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsDataPoolTestCase4()
{
  /*Service 3: Housekeeping Test the Datapool Getter and Setter*/
  unsigned int i, len;
  unsigned char* testchararrptr;
  unsigned short* testshortarrptr;
  unsigned int* testintarrptr;
  DpServHkParams_t testparams;
  DpServHkVars_t testvals;

  /*initialize Housekeeping Service Datapool Entries*/
  initDpServHk();

  len = sizeof(testparams.debugVarAddr)/sizeof(testparams.debugVarAddr[0]); 
  DEBUGP_TSDP("Arraysize of debugVarAddr: %u Elements \n", len);
  for (i=0; i<len; i++)
  {
    setDpdebugVarAddrItem(i, MIN_VAL);
    DEBUGP_TSDP("getDpdebugVarAddrItem(i) -> MIN_VAL: %u \n",getDpdebugVarAddrItem(i));
    if(getDpdebugVarAddrItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpdebugVarAddrItem(i, MAX_INT);
    DEBUGP_TSDP("getDpdebugVarAddrItem(i) -> MAX_INT: %u \n",getDpdebugVarAddrItem(i));
    if(getDpdebugVarAddrItem(i) != MAX_INT)
    {
      return 0;
    }
  }
  testintarrptr = getDpdebugVarAddrArray();
  for (i =0;i<len;i++)
  {
    DEBUGP_TSDP("testintarrptr[i] -> MAX_INT: %u \n",testintarrptr[i]);
    if(testintarrptr[i] != MAX_INT)
      return 0;
  }

  len = sizeof(testparams.dest)/sizeof(testparams.dest[0]); 
  DEBUGP_TSDP("Arraysize of dest: %u Elements \n", len);
  for (i=0; i<len; i++)
  {
    setDpdestItem(i, MIN_VAL);
    DEBUGP_TSDP("getDpdestItem(i) -> MIN_VAL: %u \n",getDpdestItem(i));
    if(getDpdestItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpdestItem(i, MAX_SHORT);
    DEBUGP_TSDP("getDpdestItem(i) -> MAX_SHORT: %u \n",getDpdestItem(i));
    if(getDpdestItem(i) != MAX_SHORT)
    {
      return 0;
    }
  }
  testshortarrptr = getDpdestArray();
  for (i =0;i<len;i++)
  {
    DEBUGP_TSDP("testshortarrptr[i] -> MAX_SHORT: %u \n",testshortarrptr[i]);
    if(testshortarrptr[i] != MAX_SHORT)
      return 0;
  }

  len = sizeof(testparams.isEnabled)/sizeof(testparams.isEnabled[0]); 
  DEBUGP_TSDP("Arraysize of isEnabled: %u Elements \n", len);
  for (i=0; i<len; i++)
  {
    setDpisEnabledItem(i, MIN_VAL);
    DEBUGP_TSDP("getDpisEnabledItem(i) -> MIN_VAL: %u \n",getDpisEnabledItem(i));
    if(getDpisEnabledItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpisEnabledItem(i, MAX_CHAR);
    DEBUGP_TSDP("getDpisEnabledItem(i) -> MAX_CHAR: %u \n",getDpisEnabledItem(i));
    if(getDpisEnabledItem(i) != MAX_CHAR)
    {
      return 0;
    }
  }
  testchararrptr = getDpisEnabledArray();
  for (i =0;i<len;i++)
  {
    DEBUGP_TSDP("testchararrptr[i] -> MAX_CHAR: %u \n",testchararrptr[i]);
    if(testchararrptr[i] != MAX_CHAR)
      return 0;
  }

  len = sizeof(testparams.sid)/sizeof(testparams.sid[0]); 
  DEBUGP_TSDP("Arraysize of sid: %u Elements \n", len);
  for (i=0; i<len; i++)
  {
    setDpsidItem(i, MIN_VAL);
    DEBUGP_TSDP("getDpsidItem(i) -> MIN_VAL: %u \n",getDpsidItem(i));
    if(getDpsidItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpsidItem(i, MAX_CHAR);
    DEBUGP_TSDP("getDpsidItem(i) -> MAX_CHAR: %u \n",getDpsidItem(i));
    if(getDpsidItem(i) != MAX_CHAR)
    {
      return 0;
    }
  }
  testchararrptr = getDpsidArray();
  for (i =0;i<len;i++)
  {
    DEBUGP_TSDP("testshortarrptr[i] -> MAX_CHAR: %u \n",testchararrptr[i]);
    if(testchararrptr[i] != MAX_CHAR)
      return 0;
  }

  len = sizeof(testvals.cycleCnt)/sizeof(testvals.cycleCnt[0]); 
  DEBUGP_TSDP("Arraysize of cycleCnt: %u Elements \n", len);
  for (i=0; i<len; i++)
  {
    setDpcycleCntItem(i, MIN_VAL);
    DEBUGP_TSDP("getDpcycleCntItem(i) -> MIN_VAL: %u \n",getDpcycleCntItem(i));
    if(getDpcycleCntItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpcycleCntItem(i, MAX_INT);
    DEBUGP_TSDP("getDpcycleCntItem(i) -> MAX_INT: %u \n",getDpcycleCntItem(i));
    if(getDpcycleCntItem(i) != MAX_INT)
    {
      return 0;
    }
  }
  testintarrptr = getDpcycleCntArray();
  for (i =0;i<len;i++)
  {
    DEBUGP_TSDP("testintarrptr[i] -> MAX_INT: %u \n",testintarrptr[i]);
    if(testintarrptr[i] != MAX_INT)
      return 0;
  }

  len = sizeof(testvals.debugVar)/sizeof(testvals.debugVar[0]); 
  DEBUGP_TSDP("Arraysize of debugVar: %u Elements \n", len);
  for (i=0; i<len; i++)
  {
    setDpdebugVarItem(i, MIN_VAL);
    DEBUGP_TSDP("getDpdebugVarItem(i) -> MIN_VAL: %u \n",getDpdebugVarItem(i));
    if(getDpdebugVarItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpdebugVarItem(i, MAX_INT);
    DEBUGP_TSDP("getDpdebugVarItem(i) -> MAX_INT: %u \n",getDpdebugVarItem(i));
    if(getDpdebugVarItem(i) != MAX_INT)
    {
      return 0;
    }
  }
  testintarrptr = getDpdebugVarArray();
  for (i =0;i<len;i++)
  {
    DEBUGP_TSDP("testintarrptr[i] -> MAX_INT: %u \n",testintarrptr[i]);
    if(testintarrptr[i] != MAX_INT)
      return 0;
  }

  len = sizeof(testvals.lstId)/sizeof(testvals.lstId[0]); 
  DEBUGP_TSDP("Arraysize of lstId: %u Elements \n", len);
  for (i=0; i<len; i++)
  {
    setDplstIdItem(i, MIN_VAL);
    DEBUGP_TSDP("getDplstIdItem(i) -> MIN_VAL: %u \n",getDplstIdItem(i));
    if(getDplstIdItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDplstIdItem(i, MAX_SHORT);
    DEBUGP_TSDP("getDplstIdItem(i) -> MAX_SHORT: %u \n",getDplstIdItem(i));
    if(getDplstIdItem(i) != MAX_SHORT)
    {
      return 0;
    }
  }
  testshortarrptr = getDplstIdArray();
  for (i =0;i<len;i++)
  {
    DEBUGP_TSDP("testshortarrptr[i] -> MAX_SHORT: %u \n",testshortarrptr[i]);
    if(testshortarrptr[i] != MAX_SHORT)
      return 0;
  }

  len = sizeof(testvals.lstNSampRep)/sizeof(testvals.lstNSampRep[0]); 
  DEBUGP_TSDP("Arraysize of lstNSampRep: %u Elements \n", len);
  for (i=0; i<len; i++)
  {
    setDplstNSampRepItem(i, MIN_VAL);
    DEBUGP_TSDP("getDplstNSampRepItem(i) -> MIN_VAL: %u \n",getDplstNSampRepItem(i));
    if(getDplstNSampRepItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDplstNSampRepItem(i, MAX_SHORT);
    DEBUGP_TSDP("getDplstNSampRepItem(i) -> MAX_SHORT: %u \n",getDplstNSampRepItem(i));
    if(getDplstNSampRepItem(i) != MAX_SHORT)
    {
      return 0;
    }
  }
  testshortarrptr = getDplstNSampRepArray();
  for (i =0;i<len;i++)
  {
    DEBUGP_TSDP("testshortarrptr[i] -> MAX_SHORT: %u \n",testshortarrptr[i]);
    if(testshortarrptr[i] != MAX_SHORT)
      return 0;
  }

  len = sizeof(testvals.lstSampleRep)/sizeof(testvals.lstSampleRep[0]); 
  DEBUGP_TSDP("Arraysize of lstSampleRep: %u Elements \n", len);
  for (i=0; i<len; i++)
  {
    setDplstSampleRepItem(i, MIN_VAL);
    DEBUGP_TSDP("getDplstSampleRepItem(i) -> MIN_VAL: %u \n",getDplstSampleRepItem(i));
    if(getDplstSampleRepItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDplstSampleRepItem(i, MAX_SHORT);
    DEBUGP_TSDP("getDplstSampleRepItem(i) -> MAX_SHORT: %u \n",getDplstSampleRepItem(i));
    if(getDplstSampleRepItem(i) != MAX_SHORT)
    {
      return 0;
    }
  }
  testshortarrptr = getDplstSampleRepArray();
  for (i =0;i<len;i++)
  {
    DEBUGP_TSDP("testshortarrptr[i] -> MAX_SHORT: %u \n",testshortarrptr[i]);
    if(testshortarrptr[i] != MAX_SHORT)
      return 0;
  }

  len = sizeof(testvals.nSimple)/sizeof(testvals.nSimple[0]); 
  DEBUGP_TSDP("Arraysize of nSimple: %u Elements \n", len);
  for (i=0; i<len; i++)
  {
    setDpnSimpleItem(i, MIN_VAL);
    DEBUGP_TSDP("getDpnSimpleItem(i) -> MIN_VAL: %u \n",getDpnSimpleItem(i));
    if(getDpnSimpleItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpnSimpleItem(i, MAX_SHORT);
    DEBUGP_TSDP("getDpnSimpleItem(i) -> MAX_SHORT: %u \n",getDpnSimpleItem(i));
    if(getDpnSimpleItem(i) != MAX_SHORT)
    {
      return 0;
    }
  }
  testshortarrptr = getDpnSimpleArray();
  for (i =0;i<len;i++)
  {
    DEBUGP_TSDP("testshortarrptr[i] -> MAX_SHORT: %u \n",testshortarrptr[i]);
    if(testshortarrptr[i] != MAX_SHORT)
      return 0;
  }

  len = sizeof(testvals.sampleBufId)/sizeof(testvals.sampleBufId[0]); 
  DEBUGP_TSDP("Arraysize of sampleBufId: %u Elements \n", len);
  for (i=0; i<len; i++)
  {
    setDpsampleBufIdItem(i, MIN_VAL);
    DEBUGP_TSDP("getDpsampleBufIdItem(i) -> MIN_VAL: %u \n",getDpsampleBufIdItem(i));
    if(getDpsampleBufIdItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpsampleBufIdItem(i, MAX_SHORT);
    DEBUGP_TSDP("getDpsampleBufIdItem(i) -> MAX_SHORT: %u \n",getDpsampleBufIdItem(i));
    if(getDpsampleBufIdItem(i) != MAX_SHORT)
    {
      return 0;
    }
  }
  testshortarrptr = getDpsampleBufIdArray();
  for (i =0;i<len;i++)
  {
    DEBUGP_TSDP("testshortarrptr[i] -> MAX_SHORT: %u \n",testshortarrptr[i]);
    if(testshortarrptr[i] != MAX_SHORT)
      return 0;
  }

  return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsDataPoolTestCase5()
{
  /*Service 5: Event Reporting Test the Datapool Getter and Setter*/
  unsigned int i, len;
  unsigned char* testarrptr;
  DpServEvtVars_t testvals;
  CrFwTimeStamp_t tim0, timmax;

  for (i=0;i<6;i++)
  {
    tim0.t[i]=0;
    timmax.t[i]=255u;
  }


  initDpServEvt();

  len = sizeof(testvals.isEidEnabled)/sizeof(testvals.isEidEnabled[0]); 
  DEBUGP_TSDP("Arraysize of isEidEnabled: %u Elements \n", len);
  for (i=0; i<len; i++)
  {
    setDpisEidEnabledItem(i, MIN_VAL);
    DEBUGP_TSDP("getDpisEidEnabledItem(i) -> MIN_VAL: %u \n",getDpisEidEnabledItem(i));
    if(getDpisEidEnabledItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpisEidEnabledItem(i, MAX_CHAR);
    DEBUGP_TSDP("getDpisEidEnabledItem(i) -> MAX_CHAR: %u \n",getDpisEidEnabledItem(i));
    if(getDpisEidEnabledItem(i) != MAX_CHAR)
    {
      return 0;
    }
  }
  testarrptr = getDpisEidEnabledArray();
  for (i =0;i<len;i++)
  {
    DEBUGP_TSDP("testarrptr[i] -> MAX_CHAR: %u \n",testarrptr[i]);
    if(testarrptr[i] != MAX_CHAR)
      return 0;
  }

  setDplastEvtEid_1(MIN_VAL);
  DEBUGP_TSDP("getDplastEvtEid_1() -> MIN_VAL: %u \n",getDplastEvtEid_1());
  if (getDplastEvtEid_1() != MIN_VAL)
  {
    return 0;
  }
  setDplastEvtEid_1(MAX_CHAR);
  DEBUGP_TSDP("getDplastEvtEid_1() -> MAX_CHAR: %u \n",getDplastEvtEid_1());
  if (getDplastEvtEid_1() != MAX_CHAR)
  {
    return 0;
  }

  setDplastEvtEid_2(MIN_VAL);
  DEBUGP_TSDP("getDplastEvtEid_2() -> MIN_VAL: %u \n",getDplastEvtEid_2());
  if (getDplastEvtEid_2() != MIN_VAL)
  {
    return 0;
  }
  setDplastEvtEid_2(MAX_CHAR);
  DEBUGP_TSDP("getDplastEvtEid_2() -> MAX_CHAR: %u \n",getDplastEvtEid_2());
  if (getDplastEvtEid_2() != MAX_CHAR)
  {
    return 0;
  }

  getDplastEvtEid_3(MIN_VAL);
  DEBUGP_TSDP("getDplastEvtEid_3() -> MIN_VAL: %u \n",getDplastEvtEid_3());
  if (getDplastEvtEid_3() != MIN_VAL)
  {
    return 0;
  }
  getDplastEvtEid_3(MAX_CHAR);
  DEBUGP_TSDP("getDplastEvtEid_3() -> MAX_CHAR: %u \n",getDplastEvtEid_3());
  if (getDplastEvtEid_3() != MAX_CHAR)
  {
    return 0;
  }

  setDplastEvtEid_4(MIN_VAL);
  DEBUGP_TSDP("getDplastEvtEid_4() -> MIN_VAL: %u \n",getDplastEvtEid_4());
  if (getDplastEvtEid_4() != MIN_VAL)
  {
    return 0;
  }
  setDplastEvtEid_4(MAX_CHAR);
  DEBUGP_TSDP("getDplastEvtEid_4() -> MAX_CHAR: %u \n",getDplastEvtEid_4());
  if (getDplastEvtEid_4() != MAX_CHAR)
  {
    return 0;
  }

  setDplastEvtTime_1(tim0);
  DEBUGP_TSDP("getDplastEvtTime_1() -> MIN_VAL: %u \n",getDplastEvtTime_1().t[0]);
  if (memcmp(getDplastEvtTime_1().t, tim0.t, sizeof(tim0))!=0)
  {
    return 0;
  }
  setDplastEvtTime_1(timmax);
  DEBUGP_TSDP("getDplastEvtTime_1() -> MAX_INT: %u \n",getDplastEvtTime_1().t[0]);
  if (memcmp(getDplastEvtTime_1().t, timmax.t, sizeof(timmax))!=0)
  {
    return 0;
  }

  setDplastEvtTime_2(tim0);
  DEBUGP_TSDP("getDplastEvtTime_2() -> MIN_VAL: %u \n",getDplastEvtTime_2().t[0]);
  if (memcmp(getDplastEvtTime_2().t, tim0.t, sizeof(tim0))!=0)
  {
    return 0;
  }
  setDplastEvtTime_2(timmax);
  DEBUGP_TSDP("getDplastEvtTime_2() -> MAX_INT: %u \n",getDplastEvtTime_2().t[0]);
  if (memcmp(getDplastEvtTime_2().t, timmax.t, sizeof(timmax))!=0)
  {
    return 0;
  }

  setDplastEvtTime_3(tim0);
  DEBUGP_TSDP("getDplastEvtTime_3() -> MIN_VAL: %u \n",getDplastEvtTime_3().t[0]);
  if (memcmp(getDplastEvtTime_3().t, tim0.t, sizeof(tim0))!=0)
  {
    return 0;
  }
  setDplastEvtTime_3(timmax);
  DEBUGP_TSDP("getDplastEvtTime_3() -> MAX_INT: %u \n",getDplastEvtTime_3().t[0]);
  if (memcmp(getDplastEvtTime_3().t, timmax.t, sizeof(timmax))!=0)
  {
    return 0;
  }

  setDplastEvtTime_4(tim0);
  DEBUGP_TSDP("getDplastEvtTime_4() -> MIN_VAL: %u \n",getDplastEvtTime_4().t[0]);
  if (memcmp(getDplastEvtTime_4().t, tim0.t, sizeof(tim0))!=0)
  {
    return 0;
  }
  setDplastEvtTime_4(timmax);
  DEBUGP_TSDP("getDplastEvtTime_4() -> MAX_INT: %u \n",getDplastEvtTime_4().t[0]);
  if (memcmp(getDplastEvtTime_4().t, timmax.t, sizeof(timmax))!=0)
  {
    return 0;
  }

  setDpnOfDetectedEvts_1(MIN_VAL);
  DEBUGP_TSDP("getDpnOfDetectedEvts_1() -> MIN_VAL: %u \n",getDpnOfDetectedEvts_1());
  if (getDpnOfDetectedEvts_1() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfDetectedEvts_1(MAX_CHAR);
  DEBUGP_TSDP("getDpnOfDetectedEvts_1() -> MAX_CHAR: %u \n",getDpnOfDetectedEvts_1());
  if (getDpnOfDetectedEvts_1() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfDetectedEvts_2(MIN_VAL);
  DEBUGP_TSDP("getDpnOfDetectedEvts_2() -> MIN_VAL: %u \n",getDpnOfDetectedEvts_2());
  if (getDpnOfDetectedEvts_2() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfDetectedEvts_2(MAX_CHAR);
  DEBUGP_TSDP("getDpnOfDetectedEvts_2() -> MAX_CHAR: %u \n",getDpnOfDetectedEvts_2());
  if (getDpnOfDetectedEvts_2() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfDetectedEvts_3(MIN_VAL);
  DEBUGP_TSDP("getDpnOfDetectedEvts_3() -> MIN_VAL: %u \n",getDpnOfDetectedEvts_3());
  if (getDpnOfDetectedEvts_3() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfDetectedEvts_3(MAX_CHAR);
  DEBUGP_TSDP("getDpnOfDetectedEvts_3() -> MAX_CHAR: %u \n",getDpnOfDetectedEvts_3());
  if (getDpnOfDetectedEvts_3() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfDetectedEvts_4(MIN_VAL);
  DEBUGP_TSDP("getDpnOfDetectedEvts_4() -> MIN_VAL: %u \n",getDpnOfDetectedEvts_4());
  if (getDpnOfDetectedEvts_4() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfDetectedEvts_4(MAX_CHAR);
  DEBUGP_TSDP("getDpnOfDisabledEid_4() -> MAX_CHAR: %u \n",getDpnOfDisabledEid_4());
  if (getDpnOfDisabledEid_4() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfDisabledEid_1(MIN_VAL);
  DEBUGP_TSDP("getDpnOfDisabledEid_1() -> MIN_VAL: %u \n",getDpnOfDisabledEid_1());
  if (getDpnOfDisabledEid_1() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfDisabledEid_1(MAX_CHAR);
  DEBUGP_TSDP("getDpnOfDisabledEid_1() -> MAX_CHAR: %u \n",getDpnOfDisabledEid_1());
  if (getDpnOfDisabledEid_1() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfDisabledEid_2(MIN_VAL);
  DEBUGP_TSDP("getDpnOfDisabledEid_2() -> MIN_VAL: %u \n",getDpnOfDisabledEid_2());
  if (getDpnOfDisabledEid_2() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfDisabledEid_2(MAX_CHAR);
  DEBUGP_TSDP("getDpnOfDisabledEid_2() -> MAX_CHAR: %u \n",getDpnOfDisabledEid_2());
  if (getDpnOfDisabledEid_2() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfDisabledEid_3(MIN_VAL);
  DEBUGP_TSDP("getDpnOfDisabledEid_3() -> MIN_VAL: %u \n",getDpnOfDisabledEid_3());
  if (getDpnOfDisabledEid_3() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfDisabledEid_3(MAX_CHAR);
  DEBUGP_TSDP("getDpnOfDisabledEid_3() -> MAX_CHAR: %u \n",getDpnOfDisabledEid_3());
  if (getDpnOfDisabledEid_3() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfDisabledEid_4(MIN_VAL);
  DEBUGP_TSDP("getDpnOfDisabledEid_4() -> MIN_VAL: %u \n",getDpnOfDisabledEid_4());
  if (getDpnOfDisabledEid_4() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfDisabledEid_4(MAX_CHAR);
  DEBUGP_TSDP("getDpnOfDisabledEid_4() -> MAX_CHAR: %u \n",getDpnOfDisabledEid_4());
  if (getDpnOfDisabledEid_4() != MAX_CHAR)
  {
    return 0;
  }
  
  setDpnOfGenEvtRep_1(MIN_VAL);
  DEBUGP_TSDP("getDpnOfGenEvtRep_1() -> MIN_VAL: %u \n",getDpnOfGenEvtRep_1());
  if (getDpnOfGenEvtRep_1() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfGenEvtRep_1(MAX_CHAR);
  DEBUGP_TSDP("getDpnOfGenEvtRep_1() -> MAX_CHAR: %u \n",getDpnOfGenEvtRep_1());
  if (getDpnOfGenEvtRep_1() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfGenEvtRep_2(MIN_VAL);
  DEBUGP_TSDP("getDpnOfGenEvtRep_2() -> MIN_VAL: %u \n",getDpnOfGenEvtRep_2());
  if (getDpnOfGenEvtRep_2() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfGenEvtRep_2(MAX_CHAR);
  DEBUGP_TSDP("getDpnOfGenEvtRep_2() -> MAX_CHAR: %u \n",getDpnOfGenEvtRep_2());
  if (getDpnOfGenEvtRep_2() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfGenEvtRep_3(MIN_VAL);
  DEBUGP_TSDP("getDpnOfGenEvtRep_3() -> MIN_VAL: %u \n",getDpnOfGenEvtRep_3());
  if (getDpnOfGenEvtRep_3() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfGenEvtRep_3(MAX_CHAR);
  DEBUGP_TSDP("getDpnOfGenEvtRep_3() -> MAX_CHAR: %u \n",getDpnOfGenEvtRep_3());
  if (getDpnOfGenEvtRep_3() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfGenEvtRep_4(MIN_VAL);
  DEBUGP_TSDP("getDpnOfGenEvtRep_4() -> MIN_VAL: %u \n",getDpnOfGenEvtRep_4());
  if (getDpnOfGenEvtRep_4() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfGenEvtRep_4(MAX_CHAR);
  DEBUGP_TSDP("getDpnOfGenEvtRep_4() -> MAX_CHAR: %u \n",getDpnOfGenEvtRep_4());
  if (getDpnOfGenEvtRep_4() != MAX_CHAR)
  {
    return 0;
  }






  return 1;
}