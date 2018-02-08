/**
 * @file CrPsDataPoolTestCases.c
 * @ingroup PUSTestsuite
 *
 * @brief Implementation of the test cases for the Datapool Component.
 *
 * @author Christian Reimers <christian.reimersy@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 *
 * last modification: 22.01.2018
 * 
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

/* Include system files */
#include <unistd.h>
#include <stdlib.h>

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
#include "UtilityFunctions/CrFwUtilityFunctions.h"

#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServTest.h>
#include <DataPool/CrPsDpServReqVerif.h>
#include <DataPool/CrPsDpServHk.h>
#include <DataPool/CrPsDpServEvt.h>
#include <DataPool/CrPsDpServLpt.h>
#include <Services/General/CrPsPktServReqVerif.h>

#define MAX_CHAR 255u
#define MAX_SHORT 65535u
#define MAX_INT 4294967295u
#define MIN_VAL 0u

uint8_t testentry(uint32_t id, uint8_t size)
{
  uint8_t testset[MAX_CHAR], testget[MAX_CHAR], dest[MAX_CHAR], i, success;
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

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsDataPoolTestCase1()
{
  /* Test the generic Datapool Getter and Setter */
  uint32_t i;
  size_t lene;
  uint32_t nume;
  uint8_t dest[1];
  uint8_t testval;
  uint8_t maxval=MAX_CHAR;
  
  for (i=DpIdParamsLowest;i<=DpIdParamsHighest;i++)
  {
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
  
  uint32_t i, pos, len;
  unsigned short destId, destIdDp;
  unsigned short* destIdArray;
  unsigned short* testarrayptr;
  DpServTestParams_t test; 
  
  initDpServTest();

  /* Set and re-read single data pool parameter */
  setDpAreYouAliveTimeOut(MIN_VAL);
  if (getDpAreYouAliveTimeOut() != MIN_VAL)
  {
    return 0;
  }
  setDpAreYouAliveTimeOut(MAX_INT);
  if (getDpAreYouAliveTimeOut() != MAX_INT)
  {
    return 0;
  }

  setDpAreYouAliveSrc(MIN_VAL);
  if (getDpAreYouAliveSrc() != MIN_VAL)
  {
    return 0;
  }

  setDpAreYouAliveSrc(MAX_SHORT);
  if (getDpAreYouAliveSrc() != MAX_SHORT)
  {
    return 0;
  }

  setDpOnBoardConnectDest(MIN_VAL);
  if (getDpOnBoardConnectDest() != MIN_VAL)
  {
    return 0;
  }
  setDpOnBoardConnectDest(MAX_SHORT);
  if (getDpOnBoardConnectDest() != MAX_SHORT)
  {
    return 0;
  }

  len = sizeof(test.OnBoardConnectDestLst)/sizeof(test.OnBoardConnectDestLst[0]); 
  for (i=0; i<len; i++)
  {
    setDpOnBoardConnectDestLstItem(i, MIN_VAL);
    if(getDpOnBoardConnectDestLstItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpOnBoardConnectDestLstItem(i, MAX_SHORT);
    if(getDpOnBoardConnectDestLstItem(i) != MAX_SHORT)
    {
      return 0;
    }
  }
  testarrayptr = getDpOnBoardConnectDestLstArray();
  for (i =0;i<len;i++)
  {
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
      if ( destId != pos + 1 )
        return 0;
    }

  /* Get whole data pool parameter array previously set */
  destIdArray = getDpOnBoardConnectDestLstArray();
  for (i=0; i<10; i++)
    {
      pos = i;
      if ( destIdArray[pos] != pos + 1 )
        return 0;
    }

  /* Call the GetSize Functions with an invalid ID */
  if(getDpVarSize(0)!=0)
    return 0;

  if(getDpParamSize(0)!=0)
    return 0;

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
  if (getDpfailCodeAccFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpfailCodeAccFailed(MAX_SHORT);
  if (getDpfailCodeAccFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDpfailCodePrgrFailed(MIN_VAL);
  if (getDpfailCodePrgrFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpfailCodePrgrFailed(MAX_SHORT);
  if (getDpfailCodePrgrFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDpfailCodeStartFailed(MIN_VAL);
  if (getDpfailCodeStartFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpfailCodeStartFailed(MAX_SHORT);
  if (getDpfailCodeStartFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDpfailCodeTermFailed(MIN_VAL);
  if (getDpfailCodeTermFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpfailCodeTermFailed(MAX_SHORT);
  if (getDpfailCodeTermFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDpinvDestRerouting(MIN_VAL);
  if (getDpinvDestRerouting() != MIN_VAL)
  {
    return 0;
  }
  setDpinvDestRerouting(MAX_SHORT);
  if (getDpinvDestRerouting() != MAX_SHORT)
  {
    return 0;
  }

  setDpnOfAccFailed(MIN_VAL);
  if (getDpnOfAccFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfAccFailed(MAX_INT);
  if (getDpnOfAccFailed() != MAX_INT)
  {
    return 0;
  }

  setDpnOfPrgrFailed(MIN_VAL);
  if (getDpnOfPrgrFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfPrgrFailed(MAX_INT);
  if (getDpnOfPrgrFailed() != MAX_INT)
  {
    return 0;
  }

  setDpnOfReroutingFailed(MIN_VAL);
  if (getDpnOfReroutingFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfReroutingFailed(MAX_INT);
  if (getDpnOfReroutingFailed() != MAX_INT)
  {
    return 0;
  }

  setDpnOfStartFailed(MIN_VAL);
  if (getDpnOfStartFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfStartFailed(MAX_INT);
  if (getDpnOfStartFailed() != MAX_INT)
  {
    return 0;
  }

  setDpnOfTermFailed(MIN_VAL);
  if (getDpnOfTermFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfTermFailed(MAX_INT);
  if (getDpnOfTermFailed() != MAX_INT)
  {
    return 0;
  }

  setDppcktIdAccFailed(MIN_VAL);
  if (getDppcktIdAccFailed() != MIN_VAL)
  {
    return 0;
  }
  setDppcktIdAccFailed(MAX_SHORT);
  if (getDppcktIdAccFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDppcktIdPrgrFailed(MIN_VAL);
  if (getDppcktIdPrgrFailed() != MIN_VAL)
  {
    return 0;
  }
  setDppcktIdPrgrFailed(MAX_SHORT);
  if (getDppcktIdPrgrFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDppcktIdReroutingFailed(MIN_VAL);
  if (getDppcktIdReroutingFailed() != MIN_VAL)
  {
    return 0;
  }
  setDppcktIdReroutingFailed(MAX_SHORT);
  if (getDppcktIdReroutingFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDppcktIdStartFailed(MIN_VAL);
  if (getDppcktIdStartFailed() != MIN_VAL)
  {
    return 0;
  }
  setDppcktIdStartFailed(MAX_SHORT);
  if (getDppcktIdStartFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDppcktIdTermFailed(MIN_VAL);
  if (getDppcktIdTermFailed() != MIN_VAL)
  {
    return 0;
  }
  setDppcktIdTermFailed(MAX_SHORT);
  if (getDppcktIdTermFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDpstepPrgrFailed(MIN_VAL);
  if (getDpstepPrgrFailed() != MIN_VAL)
  {
    return 0;
  }
  setDpstepPrgrFailed(MAX_SHORT);
  if (getDpstepPrgrFailed() != MAX_SHORT)
  {
    return 0;
  }

  setDpverFailData(MIN_VAL);
  if (getDpverFailData() != MIN_VAL)
  {
    return 0;
  }
  setDpverFailData(MAX_INT);
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
  uint32_t i, len;
  unsigned char* testchararrptr;
  unsigned short* testshortarrptr;
  unsigned int* testintarrptr;
  DpServHkParams_t testparams;
  DpServHkVars_t testvals;

  /*initialize Housekeeping Service Datapool Entries*/
  initDpServHk();

  len = sizeof(testparams.debugVarAddr)/sizeof(testparams.debugVarAddr[0]); 
  for (i=0; i<len; i++)
  {
    setDpdebugVarAddrItem(i, MIN_VAL);
    if(getDpdebugVarAddrItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpdebugVarAddrItem(i, MAX_INT);
    if(getDpdebugVarAddrItem(i) != MAX_INT)
    {
      return 0;
    }
  }
  testintarrptr = getDpdebugVarAddrArray();
  for (i =0;i<len;i++)
  {
    if(testintarrptr[i] != MAX_INT)
      return 0;
  }

  len = sizeof(testparams.dest)/sizeof(testparams.dest[0]); 
  for (i=0; i<len; i++)
  {
    setDpdestItem(i, MIN_VAL);
    if(getDpdestItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpdestItem(i, MAX_SHORT);
    if(getDpdestItem(i) != MAX_SHORT)
    {
      return 0;
    }
  }
  testshortarrptr = getDpdestArray();
  for (i =0;i<len;i++)
  {
    if(testshortarrptr[i] != MAX_SHORT)
      return 0;
  }

  len = sizeof(testparams.isEnabled)/sizeof(testparams.isEnabled[0]); 
  for (i=0; i<len; i++)
  {
    setDpisEnabledItem(i, MIN_VAL);
    if(getDpisEnabledItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpisEnabledItem(i, MAX_CHAR);
    if(getDpisEnabledItem(i) != MAX_CHAR)
    {
      return 0;
    }
  }
  testchararrptr = getDpisEnabledArray();
  for (i =0;i<len;i++)
  {
    if(testchararrptr[i] != MAX_CHAR)
      return 0;
  }

  len = sizeof(testparams.sid)/sizeof(testparams.sid[0]); 
  for (i=0; i<len; i++)
  {
    setDpsidItem(i, MIN_VAL);
    if(getDpsidItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpsidItem(i, MAX_CHAR);
    if(getDpsidItem(i) != MAX_CHAR)
    {
      return 0;
    }
  }
  testchararrptr = getDpsidArray();
  for (i =0;i<len;i++)
  {
    if(testchararrptr[i] != MAX_CHAR)
      return 0;
  }

  len = sizeof(testvals.cycleCnt)/sizeof(testvals.cycleCnt[0]); 
  for (i=0; i<len; i++)
  {
    setDpcycleCntItem(i, MIN_VAL);
    if(getDpcycleCntItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpcycleCntItem(i, MAX_INT);
    if(getDpcycleCntItem(i) != MAX_INT)
    {
      return 0;
    }
  }
  testintarrptr = getDpcycleCntArray();
  for (i =0;i<len;i++)
  {
    if(testintarrptr[i] != MAX_INT)
      return 0;
  }

  len = sizeof(testvals.debugVar)/sizeof(testvals.debugVar[0]); 
  for (i=0; i<len; i++)
  {
    setDpdebugVarItem(i, MIN_VAL);
    if(getDpdebugVarItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpdebugVarItem(i, MAX_INT);
    if(getDpdebugVarItem(i) != MAX_INT)
    {
      return 0;
    }
  }
  testintarrptr = getDpdebugVarArray();
  for (i =0;i<len;i++)
  {
    if(testintarrptr[i] != MAX_INT)
      return 0;
  }

  len = sizeof(testvals.lstId)/sizeof(testvals.lstId[0]); 
  for (i=0; i<len; i++)
  {
    setDplstIdItem(i, MIN_VAL);
    if(getDplstIdItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDplstIdItem(i, MAX_SHORT);
    if(getDplstIdItem(i) != MAX_SHORT)
    {
      return 0;
    }
  }
  testshortarrptr = getDplstIdArray();
  for (i =0;i<len;i++)
  {
    if(testshortarrptr[i] != MAX_SHORT)
      return 0;
  }

  len = sizeof(testvals.lstNSampRep)/sizeof(testvals.lstNSampRep[0]); 
  for (i=0; i<len; i++)
  {
    setDplstNSampRepItem(i, MIN_VAL);
    if(getDplstNSampRepItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDplstNSampRepItem(i, MAX_SHORT);
    if(getDplstNSampRepItem(i) != MAX_SHORT)
    {
      return 0;
    }
  }
  testshortarrptr = getDplstNSampRepArray();
  for (i =0;i<len;i++)
  {
    if(testshortarrptr[i] != MAX_SHORT)
      return 0;
  }

  len = sizeof(testvals.lstSampleRep)/sizeof(testvals.lstSampleRep[0]); 
  for (i=0; i<len; i++)
  {
    setDplstSampleRepItem(i, MIN_VAL);
    if(getDplstSampleRepItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDplstSampleRepItem(i, MAX_SHORT);
    if(getDplstSampleRepItem(i) != MAX_SHORT)
    {
      return 0;
    }
  }
  testshortarrptr = getDplstSampleRepArray();
  for (i =0;i<len;i++)
  {
    if(testshortarrptr[i] != MAX_SHORT)
      return 0;
  }

  len = sizeof(testvals.nSimple)/sizeof(testvals.nSimple[0]); 
  for (i=0; i<len; i++)
  {
    setDpnSimpleItem(i, MIN_VAL);
    if(getDpnSimpleItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpnSimpleItem(i, MAX_SHORT);
    if(getDpnSimpleItem(i) != MAX_SHORT)
    {
      return 0;
    }
  }
  testshortarrptr = getDpnSimpleArray();
  for (i =0;i<len;i++)
  {
    if(testshortarrptr[i] != MAX_SHORT)
      return 0;
  }

  len = sizeof(testvals.sampleBufId)/sizeof(testvals.sampleBufId[0]); 
  for (i=0; i<len; i++)
  {
    setDpsampleBufIdItem(i, MIN_VAL);
    if(getDpsampleBufIdItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpsampleBufIdItem(i, MAX_SHORT);
    if(getDpsampleBufIdItem(i) != MAX_SHORT)
    {
      return 0;
    }
  }
  testshortarrptr = getDpsampleBufIdArray();
  for (i =0;i<len;i++)
  {
    if(testshortarrptr[i] != MAX_SHORT)
      return 0;
  }

  return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsDataPoolTestCase5()
{
  /*Service 5: Event Reporting Test the Datapool Getter and Setter*/
  uint32_t i, len;
  unsigned char* testarrptr;
  DpServEvtVars_t testvals;
  CrFwTimeStamp_t tim0, timmax, ret;

  for (i=0;i<6;i++)
  {
    tim0.t[i]=0;
    timmax.t[i]=255u;
  }


  initDpServEvt();

  len = sizeof(testvals.isEidEnabled)/sizeof(testvals.isEidEnabled[0]); 
  for (i=0; i<len; i++)
  {
    setDpisEidEnabledItem(i, MIN_VAL);
    if(getDpisEidEnabledItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDpisEidEnabledItem(i, MAX_CHAR);
    if(getDpisEidEnabledItem(i) != MAX_CHAR)
    {
      return 0;
    }
  }
  testarrptr = getDpisEidEnabledArray();
  for (i =0;i<len;i++)
  {
    if(testarrptr[i] != MAX_CHAR)
      return 0;
  }

  setDplastEvtEid_1(MIN_VAL);
  if (getDplastEvtEid_1() != MIN_VAL)
  {
    return 0;
  }
  setDplastEvtEid_1(MAX_CHAR);
  if (getDplastEvtEid_1() != MAX_CHAR)
  {
    return 0;
  }

  setDplastEvtEid_2(MIN_VAL);
  if (getDplastEvtEid_2() != MIN_VAL)
  {
    return 0;
  }
  setDplastEvtEid_2(MAX_CHAR);
  if (getDplastEvtEid_2() != MAX_CHAR)
  {
    return 0;
  }

  setDplastEvtEid_3(MIN_VAL);
  if (getDplastEvtEid_3() != MIN_VAL)
  {
    return 0;
  }
  setDplastEvtEid_3(MAX_CHAR);
  if (getDplastEvtEid_3() != MAX_CHAR)
  {
    return 0;
  }

  setDplastEvtEid_4(MIN_VAL);
  if (getDplastEvtEid_4() != MIN_VAL)
  {
    return 0;
  }
  setDplastEvtEid_4(MAX_CHAR);
  if (getDplastEvtEid_4() != MAX_CHAR)
  {
    return 0;
  }

  setDplastEvtTime_1(tim0);
  ret = getDplastEvtTime_1();
  if (memcmp(ret.t, tim0.t, sizeof(tim0)))
  {
    return 0;
  }
  setDplastEvtTime_1(timmax);
  ret = getDplastEvtTime_1();
  if (memcmp(ret.t, timmax.t, sizeof(timmax)))
  {
    return 0;
  }

  setDplastEvtTime_2(tim0);
  ret = getDplastEvtTime_2();
  if (memcmp(ret.t, tim0.t, sizeof(tim0)))
  {
    return 0;
  }
  setDplastEvtTime_2(timmax);
  ret = getDplastEvtTime_2();
  if (memcmp(ret.t, timmax.t, sizeof(timmax)))
  {
    return 0;
  }

  setDplastEvtTime_3(tim0);
  ret = getDplastEvtTime_3();
  if (memcmp(ret.t, tim0.t, sizeof(tim0)))
  {
    return 0;
  }
  setDplastEvtTime_3(timmax);
  ret = getDplastEvtTime_3();
  if (memcmp(ret.t, timmax.t, sizeof(timmax)))
  {
    return 0;
  }

  setDplastEvtTime_4(tim0);
  ret = getDplastEvtTime_4();
  if (memcmp(ret.t, tim0.t, sizeof(tim0)))
  {
    return 0;
  }
  setDplastEvtTime_4(timmax);
  ret = getDplastEvtTime_4();
  if (memcmp(ret.t, timmax.t, sizeof(timmax)))
  {
    return 0;
  }

  setDpnOfDetectedEvts_1(MIN_VAL);
  if (getDpnOfDetectedEvts_1() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfDetectedEvts_1(MAX_CHAR);
  if (getDpnOfDetectedEvts_1() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfDetectedEvts_2(MIN_VAL);
  if (getDpnOfDetectedEvts_2() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfDetectedEvts_2(MAX_CHAR);
  if (getDpnOfDetectedEvts_2() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfDetectedEvts_3(MIN_VAL);
  if (getDpnOfDetectedEvts_3() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfDetectedEvts_3(MAX_CHAR);
  if (getDpnOfDetectedEvts_3() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfDetectedEvts_4(MIN_VAL);
  if (getDpnOfDetectedEvts_4() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfDetectedEvts_4(MAX_CHAR);
  if (getDpnOfDetectedEvts_4() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfDisabledEid_1(MIN_VAL);
  if (getDpnOfDisabledEid_1() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfDisabledEid_1(MAX_CHAR);
  if (getDpnOfDisabledEid_1() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfDisabledEid_2(MIN_VAL);
  if (getDpnOfDisabledEid_2() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfDisabledEid_2(MAX_CHAR);
  if (getDpnOfDisabledEid_2() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfDisabledEid_3(MIN_VAL);
  if (getDpnOfDisabledEid_3() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfDisabledEid_3(MAX_CHAR);
  if (getDpnOfDisabledEid_3() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfDisabledEid_4(MIN_VAL);
  if (getDpnOfDisabledEid_4() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfDisabledEid_4(MAX_CHAR);
  if (getDpnOfDisabledEid_4() != MAX_CHAR)
  {
    return 0;
  }
  
  setDpnOfGenEvtRep_1(MIN_VAL);
  if (getDpnOfGenEvtRep_1() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfGenEvtRep_1(MAX_CHAR);
  if (getDpnOfGenEvtRep_1() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfGenEvtRep_2(MIN_VAL);
  if (getDpnOfGenEvtRep_2() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfGenEvtRep_2(MAX_CHAR);
  if (getDpnOfGenEvtRep_2() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfGenEvtRep_3(MIN_VAL);
  if (getDpnOfGenEvtRep_3() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfGenEvtRep_3(MAX_CHAR);
  if (getDpnOfGenEvtRep_3() != MAX_CHAR)
  {
    return 0;
  }

  setDpnOfGenEvtRep_4(MIN_VAL);
  if (getDpnOfGenEvtRep_4() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfGenEvtRep_4(MAX_CHAR);
  if (getDpnOfGenEvtRep_4() != MAX_CHAR)
  {
    return 0;
  }

  return 1;
}


/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsDataPoolTestCase6()
{
  /*Service 13: Large Packet Transfer Test the Datapool Getter and Setter*/
  uint32_t i, len;
  uint32_t* testarrptr32;
  uint16_t* testarrptr16;
  CrFwTimeStamp_t* testarrptrtim;
  CrFwTimeStamp_t tim0, timmax, ret;
  DpServLptParams_t testparams;
  DpServLptVars_t testvars;

  for (i=0;i<6;i++)
  {
    tim0.t[i]=0;
    timmax.t[i]=255u;
  }

  initDpServLpt();

  len = sizeof(testparams.lptTimeOut)/sizeof(testparams.lptTimeOut[0]); 
  for (i=0; i<len; i++)
  {
    setDplptTimeOutItem(i, MIN_VAL);
    if(getDplptTimeOutItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDplptTimeOutItem(i, MAX_INT);
    if(getDplptTimeOutItem(i) != MAX_INT)
    {
      return 0;
    }
  }
  testarrptr32 = getDplptTimeOutArray();
  for (i =0;i<len;i++)
  {
    if(testarrptr32[i] != MAX_INT)
      return 0;
  }

  len = sizeof(testvars.largeMsgTransId)/sizeof(testvars.largeMsgTransId[0]); 
  for (i=0; i<len; i++)
  {
    setDplargeMsgTransIdItem(i, MIN_VAL);
    if(getDplargeMsgTransIdItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDplargeMsgTransIdItem(i, MAX_INT);
    if(getDplargeMsgTransIdItem(i) != MAX_INT)
    {
      return 0;
    }
  }
  testarrptr32 = getDplargeMsgTransIdArray();
  for (i =0;i<len;i++)
  {
    if(testarrptr32[i] != MAX_INT)
      return 0;
  }

  len = sizeof(testvars.lptFailCode)/sizeof(testvars.lptFailCode[0]); 
  for (i=0; i<len; i++)
  {
    setDplptFailCodeItem(i, MIN_VAL);
    if(getDplptFailCodeItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDplptFailCodeItem(i, MAX_SHORT);
    if(getDplptFailCodeItem(i) != MAX_SHORT)
    {
      return 0;
    }
  }
  testarrptr16 = getDplptFailCodeArray();
  for (i =0;i<len;i++)
  {
    if(testarrptr16[i] != MAX_SHORT)
      return 0;
  }

  len = sizeof(testvars.lptRemSize)/sizeof(testvars.lptRemSize[0]); 
  for (i=0; i<len; i++)
  {
    setDplptRemSizeItem(i, MIN_VAL);
    if(getDplptRemSizeItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDplptRemSizeItem(i, MAX_INT);
    if(getDplptRemSizeItem(i) != MAX_INT)
    {
      return 0;
    }
  }
  testarrptr32 = getDplptRemSizeArray();
  for (i =0;i<len;i++)
  {
    if(testarrptr32[i] != MAX_INT)
      return 0;
  }

  len = sizeof(testvars.lptSize)/sizeof(testvars.lptSize[0]); 
  for (i=0; i<len; i++)
  {
    setDplptSizeItem(i, MIN_VAL);
    if(getDplptSizeItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDplptSizeItem(i, MAX_INT);
    if(getDplptSizeItem(i) != MAX_INT)
    {
      return 0;
    }
  }
  testarrptr32 = getDplptSizeArray();
  for (i =0;i<len;i++)
  {
    if(testarrptr32[i] != MAX_INT)
      return 0;
  }


  len = sizeof(testvars.lptSize)/sizeof(testvars.lptSize[0]); 
  for (i=0; i<len; i++)
  {
    setDplptSizeItem(i, MIN_VAL);
    if(getDplptSizeItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDplptSizeItem(i, MAX_INT);
    if(getDplptSizeItem(i) != MAX_INT)
    {
      return 0;
    }
  }
  testarrptr32 = getDplptSizeArray();
  for (i =0;i<len;i++)
  {
    if(testarrptr32[i] != MAX_INT)
      return 0;
  }

  len = sizeof(testvars.lptSrc)/sizeof(testvars.lptSrc[0]); 
  for (i=0; i<len; i++)
  {
    setDplptSrcItem(i, MIN_VAL);
    if(getDplptSrcItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDplptSrcItem(i, MAX_SHORT);
    if(getDplptSrcItem(i) != MAX_SHORT)
    {
      return 0;
    }
  }
  testarrptr16 = getDplptSrcArray();
  for (i =0;i<len;i++)
  {
    if(testarrptr16[i] != MAX_SHORT)
      return 0;
  }

  len = sizeof(testvars.lptTime)/sizeof(testvars.lptTime[0]); 
  for (i=0; i<len; i++)
  {
    setDplptTimeItem(i, tim0);
    ret = getDplptTimeItem(i);
    if(memcmp(ret.t, tim0.t, sizeof(tim0)))
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDplptTimeItem(i, timmax);
    ret = getDplptTimeItem(i);
    if(memcmp(ret.t, timmax.t, sizeof(timmax)))
    {
      return 0;
    }
  }
  testarrptrtim = getDplptTimeArray();
  for (i =0;i<len;i++)
  {
    if(memcmp(testarrptrtim[i].t, timmax.t, sizeof(timmax)))
      return 0;
  }

  setDpnOfDownlinks(MIN_VAL);
  if (getDpnOfDownlinks() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfDownlinks(MAX_INT);
  if (getDpnOfDownlinks() != MAX_INT)
  {
    return 0;
  }

  setDpnOfUplinks(MIN_VAL);
  if (getDpnOfUplinks() != MIN_VAL)
  {
    return 0;
  }
  setDpnOfUplinks(MAX_INT);
  if (getDpnOfUplinks() != MAX_INT)
  {
    return 0;
  }

  len = sizeof(testvars.partSeqNmb)/sizeof(testvars.partSeqNmb[0]); 
  for (i=0; i<len; i++)
  {
    setDppartSeqNmbItem(i, MIN_VAL);
    if(getDppartSeqNmbItem(i) != MIN_VAL)
    {
      return 0;
    }
  }
  for (i=0; i<len; i++)
  {
    setDppartSeqNmbItem(i, MAX_INT);
    if(getDppartSeqNmbItem(i) != MAX_INT)
    {
      return 0;
    }
  }
  testarrptr32 = getDppartSeqNmbArray();
  for (i =0;i<len;i++)
  {
    if(testarrptr32[i] != MAX_INT)
      return 0;
  }

  return 1;
}
