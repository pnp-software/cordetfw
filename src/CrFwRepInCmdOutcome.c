/**
 * @file CrFwRepInCmdOutcome.c
 * @ingroup CrIaDemo
 *
 * Implementation of the error reporting interface of the IASW Application.
 *
 * \see CrFwRepErr.h
 *
 * This implementation writes the InCommand Outcome Reports to standard output.
 *
 * @authors V. Cechticky and A. Pasetti
 * @copyright P&P Software GmbH, 2014
 */

#include "CrFwRepInCmdOutcome.h"

/* Include FW Profile Files*/
#include "FwSmConfig.h"
#include "FwPrConfig.h"

/* Include Framework Files */
#include <CrFwConstants.h>
#include <Pckt/CrFwPckt.h>
#include <OutFactory/CrFwOutFactory.h>
#include <OutLoader/CrFwOutLoader.h>
#include <CrFwCmpData.h>

/* Include PUS Extension Files*/
#include <CrPsUtilities.h>
#include <Services/General/CrPsConstants.h>

/* Include Standard Files*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*-----------------------------------------------------------------------------------------*/
void CrFwRepInCmdOutcome(CrFwRepInCmdOutcome_t outcome, CrFwInstanceId_t instanceId, CrFwServType_t servType,
                         CrFwServSubType_t servSubType, CrFwDiscriminant_t disc, CrFwOutcome_t failCode, FwSmDesc_t inCmd)
{
  unsigned short stepIdentifier;
  prDataPrgrAction_t* prDataPrgrAction;

  printf("########## CrFwRepInCmdOutcome: unexpected outcome report %d for InCommand %d,\n", outcome, instanceId);
  printf("                     service type %d, service sub-type %d, and discriminant %d\n", servType, servSubType, disc);
  printf("\n>>>\n>>> Result with Code %d: \n", failCode);

  switch (outcome)
  {
    case crCmdAckAccFail:
      printf ("########## CrFwRepInCmdOutcome: Acceptance Failed, Send TM(1,2)\n");
      /* Send Request Verification Acceptance Failed out-going report */
      SendReqVerifAccFailRep(inCmd, failCode);
      break;
    case crCmdAckAccSucc:
      printf ("########## CrFwRepInCmdOutcome: Acceptance Success, Send TM(1,1)\n");
      /* Send Request Verification Acceptance Successful out-going report */
      SendReqVerifAccSuccRep(inCmd, CRPS_REQVERIF_ACC_SUCC);    
      break;
    case crCmdAckStrFail:
      printf ("########## CrFwRepInCmdOutcome: Start Failed, Send TM(1,4)\n");
      /* Send Request Verification Start Failed out-going report */
      SendReqVerifCmdFailRep(inCmd, CRPS_REQVERIF_START_FAIL, failCode);
      break;
    case crCmdAckStrSucc:
      printf ("########## CrFwRepInCmdOutcome: Start Success, Send TM(1,3)\n"); 
      /* Send Request Verification Start Successful out-going report */
      SendReqVerifAccSuccRep(inCmd, CRPS_REQVERIF_START_SUCC);  
      break;
    case crCmdAckPrgFail:
      printf ("########## CrFwRepInCmdOutcome: Progress Failed, Send TM(1,6)\n");
      /* Get procedure parameters */
      prDataPrgrAction = (prDataPrgrAction_t *)FwPrGetData(prDescServTestOnBoardConnPrgr);
      stepIdentifier = prDataPrgrAction->stepId;
      /* Send Request Verification Progress Failed out-going report */
      SendReqVerifPrgrFailRep(inCmd, stepIdentifier, failCode);
      break;
    case crCmdAckPrgSucc:
      printf ("########## CrFwRepInCmdOutcome: Progress Success, Send TM(1,5)\n");
      /* Get procedure parameters */
      prDataPrgrAction = (prDataPrgrAction_t *)FwPrGetData(prDescServTestOnBoardConnPrgr);
      if (prDataPrgrAction != NULL)
        {
          stepIdentifier = prDataPrgrAction->stepId;
        }
      else
        {
          stepIdentifier = 1;
        }
      /* Send Request Verification Progress Successful out-going report */
      SendReqVerifPrgrSuccRep(inCmd, stepIdentifier);
      break;
    case crCmdAckTrmFail:
      printf ("########## CrFwRepInCmdOutcome: Termination Failed, Send TM(1,8)\n");
      /* Send Request Verification Termination Failed out-going report */
      SendReqVerifCmdFailRep(inCmd, CRPS_REQVERIF_TERM_FAIL, failCode);
      break;
    case crCmdAckTrmSucc:
      printf ("########## CrFwRepInCmdOutcome: Termination Success, Send TM(1,7)\n");
      /* Send Request Verification Termination Successful out-going report */
      SendReqVerifAccSuccRep(inCmd, CRPS_REQVERIF_TERM_SUCC);   
      break;
    default:
      printf ("########## CrFwRepInCmdOutcome: unknown outcome\n");
      break;
  }

  switch (failCode)
  {
    case 0:
      printf("########## failed ...");
      break;
    case 1:
      printf("########## success/completed ...");
      break;
    case 2:
      printf("########## continue ...");
      break;
    case 3:
      printf("########## failed with cause: InCmd is not accepted\n>>> -> leads to action ...");
      /*SendReqVerifCmdFailRep(inCmd, CRPS_REQVERIF_START_FAIL, failCode);*/
      break;
    case 4:
      printf("########## failed with cause: InCmd can not processed successfully due to timeout\n>>> -> leads to action ...");
      /*SendReqVerifPrgrFailRep(inCmd, 0, failCode);*/
      break;
    default:
      printf("########## unknown\n>>> -> leads to action ...");
      break;
   }

  printf("\n>>>\n");

  return;
}
