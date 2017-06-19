/**
 * @file CrPsUtilities.c
 *
 * Implementation of the utility functions of the CORDET Framework PUS Extension
 *
 * @author code generator
 * edited: Christian Reimers
 * 25.05.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsUtilities.h"
#include "CrPsPcktUtilities.h"
#include "Pckt/CrFwPckt.h"

/* CrFramework includes */
#include <OutFactory/CrFwOutFactory.h>
#include <OutLoader/CrFwOutLoader.h>

/* FwProfile includes */
#include <FwProfile/FwPrCore.h>
#include <FwProfile/FwPrConfig.h>

#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsParamSetter.h>
#include <Services/Test/Procedures/CrPsCmd17s3StartCreate.h>
#include <Services/Test/Procedures/CrPsCmd17s3PrgrCreate.h>

#include <DataPool/CrPsDataPool.h>
#include <DataPool/DpServTest.h>

#include <stdio.h>
#include <stdlib.h>

/* global handles for the procedures */
FwPrDesc_t prDescServTestOnBoardConnStart, prDescServTestOnBoardConnPrgr;


/**
 * Initialization of CORDET Framework PUS Extension application-specific components
 */
void CrPsInitApp(unsigned short onBoardTestConnectAppId)
{
  unsigned short destId;
  unsigned int i, pos;

  printf("CrPsInitApp(%d): Mult = %d\n", onBoardTestConnectAppId, 10);

  /*************************************************************/
  /* Service Test On-Board Connection Data Pool Initialization */
  /*************************************************************/
  for (i=0; i<10; i++)
    {
      pos = i;
      destId = getDpOnBoardConnectDestLstItem(pos);
      printf("CrPsInitApp(): got destId %d at slot %d from data pool\n", destId, i);
      if (destId == 0) /* got empty#include <> slot */
        {
          printf("CrPsInitApp(): new slot for appId found: pos = %d\n", pos);
          setDpOnBoardConnectDestLstItem(pos, onBoardTestConnectAppId);
          return;
        }
    }

  printf("CrPsInitApp(): no empty slot found!\n");
  return;
}

/**
 * Initialization of CORDET Framework PUS Extension components
 */
int CrPsInit()
{
  printf("CrPsInit()\n");

  /*************************************************************/
  /* Service Test On-Board Connection Start Procedure          */
  /*************************************************************/
  prDescServTestOnBoardConnStart = CrPsCmd17s3StartCreate(NULL);
  if (FwPrCheck(prDescServTestOnBoardConnStart) != prSuccess)
    {
      printf("Service Test On-Board Connection Start PR is NOT properly configured ... FAILURE\n");
      return EXIT_FAILURE;
    }

  /*************************************************************/
  /* Service Test On-Board Connection Progress Procedure       */
  /*************************************************************/
  prDescServTestOnBoardConnPrgr = CrPsCmd17s3PrgrCreate(NULL);
  if (FwPrCheck(prDescServTestOnBoardConnPrgr) != prSuccess)
    {
      printf("Service Test On-Board Connection Progress PR is NOT properly configured ... FAILURE\n");
      return EXIT_FAILURE;
    }

  /*************************************************************/
  /* Initialization of Data Pool variables and parameter       */
  /*************************************************************/
  setDpAreYouAliveTimeOut(10);

  return EXIT_SUCCESS;
}

/**
 * Execution of CORDET Framework PUS Extension components
 */
void CrPsExec()
{
  printf("CrPsExec()\n");

  FwPrExecute(prDescServTestOnBoardConnStart);
  /*FwPrExecute(prDescServTestOnBoardConnPrgr);*/

  return;
}

/**
 * Generate a Request Verification Acceptance Successful out-going report.
 * @return nothing
 */
void SendReqVerifAccSuccRep(CrFwPckt_t pckt)
{
  FwSmDesc_t rep;
  CrFwDestSrc_t source;
  CrFwBool_t isAcceptAck;
  /*unsigned char sid, tcType, tcSubtype;*/
  /*unsigned short tcPacketId, tcPacketSeqCtrl, tcLength, tcReceivedBytes, tcReceivedCrc, tcCalculatedCrc, tcFailureCode;*/
  unsigned short tcPacketId, tcPacketSeqCtrl, tcReceivedBytes;
  /*unsigned short nofTcAcc, seqCntLastAccTc;*/
  unsigned short seqCntLastAccTc;

/*
  CrIaCopy(NOFTCACC_ID, &nofTcAcc);
  nofTcAcc += 1;
  CrIaPaste(NOFTCACC_ID, &nofTcAcc);
*/

  source = CrFwPcktGetSrc(pckt); /* --> ADAPTATION POINT <-- */
  printf("SendTcAccRepSucc: source = %d\n", source);

  seqCntLastAccTc = CrFwPcktGetSeqCnt(pckt); /* --> ADAPTATION POINT <-- */
  CRFW_UNUSED(seqCntLastAccTc)

  /*
  if (source==CR_FW_CLIENT_GRD)
    {
      CrIaPaste(SEQCNTLASTACCTCFROMGRD_ID, &seqCntLastAccTc);
      printf("SendTcAccRepSucc: set SeqCntLastAccTcFromGrd = %d\n", seqCntLastAccTc);
    }
  else if (source==CR_FW_CLIENT_OBC)
    {
      CrIaPaste(SEQCNTLASTACCTCFROMOBC_ID, &seqCntLastAccTc);
      printf("SendTcAccRepSucc: set SeqCntLastAccTcFromObc = %d\n", seqCntLastAccTc);
    }
*/
  
  tcReceivedBytes = CrFwPcktGetParLength(pckt); /* TODO: check, if an other length is a better indicator */ /* --> ADAPTATION POINT <-- */
  printf("SendTcAccRepSucc: CrFwPcktGetParLength(pckt) = %d\n", tcReceivedBytes);
  
  isAcceptAck = CrFwPcktIsAcceptAck(pckt); /* --> ADAPTATION POINT <-- */
  printf("SendTcAccRepSucc: CrFwPcktIsAcceptAck(pckt) = %d\n", isAcceptAck);

  if (isAcceptAck==1)
    {
      /* send (1,1) TC acceptance report - success */
      /* Create out component */
      rep = (FwSmDesc_t) CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, CRPS_REQVERIF_ACC_SUCC, 0, 0);
      if (rep == NULL) 
	{
	  /* TODO: enter event
	     unsigned short evt_data[2] = {cpu_to_be16(192), cpu_to_be16(1)};
	     CrIaEvtRep(3, EVT_TRANSF_FULL, evt_data); */
	  return;
	}
      
      /* Set out component parameters */

      tcPacketId = CrFwPcktGetPid(pckt); /* --> ADAPTATION POINT <-- */
      CrPsServReqVerifAccSuccParamSetTcPacketId(rep, tcPacketId);

      tcPacketSeqCtrl = CrFwPcktGetSeqCnt(pckt); /* --> ADAPTATION POINT <-- */
      CrPsServReqVerifAccSuccParamSetTcPacketSeqCtrl(rep, tcPacketSeqCtrl);
      
      CrFwOutCmpSetDest(rep, source);
      
      CrFwOutLoaderLoad(rep);
    }

  return;
}

/**
 * Generate a Request Verification Acceptance Failed out-going report.
 * @return nothing
 */
void SendReqVerifAccFailRep(CrFwPckt_t pckt, unsigned short tcFailureCode)
{
  CRFW_UNUSED(pckt);
  CRFW_UNUSED(tcFailureCode);
  return;
}

/**
 * Generate a Request Verification Start Successful out-going report.
 * @return nothing
 */
void SendReqVerifStartSuccRep(CrFwPckt_t pckt)
{
  FwSmDesc_t rep;
  CrFwDestSrc_t source;
  CrFwBool_t isStartAck;
  unsigned char tcType, tcSubtype;
  unsigned short tcPacketId, tcPacketSeqCtrl;
  
  CRFW_UNUSED(tcSubtype);
  CRFW_UNUSED(tcType);
  
  isStartAck = CrFwPcktIsStartAck(pckt); /* --> ADAPTATION POINT <-- */
  
  if (isStartAck==1)
    {
      /* send (1,3) TC start report - success */
      /* Create out component */
      rep = (FwSmDesc_t) CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, CRPS_REQVERIF_START_SUCC, 0, 0);
      if (rep == NULL) 
	{
	  /* TODO: enter event
	     unsigned short evt_data[2] = {cpu_to_be16(192), cpu_to_be16(1)};
	     CrIaEvtRep(3, EVT_TRANSF_FULL, evt_data); */
	  return;
	}
      
      /* Set out component parameters */

      tcPacketId = CrFwPcktGetPid(pckt); /* --> ADAPTATION POINT <-- */
      CrPsServReqVerifAccSuccParamSetTcPacketId(rep, tcPacketId); /* TODO: implement own Setter for Start Success */

      tcPacketSeqCtrl = CrFwPcktGetSeqCnt(pckt); /* --> ADAPTATION POINT <-- */
      CrPsServReqVerifAccSuccParamSetTcPacketSeqCtrl(rep, tcPacketSeqCtrl); /* TODO: implement own Setter for Start Success */
      
      source = CrFwPcktGetSrc(pckt); /* --> ADAPTATION POINT <-- */
      CrFwOutCmpSetDest(rep, source);
      
      CrFwOutLoaderLoad(rep);
    }
  
  return;
}

/**
 * Generate a Request Verification Start Failed out-going report.
 * @return nothing
 */
void SendReqVerifStartFailRep(CrFwPckt_t pckt, unsigned short tcFailureCode, unsigned short wrongParamPosition, unsigned short wrongParamValue)
{
  FwSmDesc_t rep;
  CrFwDestSrc_t source;
  unsigned char tcType, tcSubtype;
  unsigned short tcPacketId, tcPacketSeqCtrl, seqCntLastStartFailTc;  
  /*unsigned short tcPacketId, tcPacketSeqCtrl, nofStartFailedTc, seqCntLastStartFailTc;*/
  CRFW_UNUSED(tcFailureCode);
  CRFW_UNUSED(wrongParamPosition);
  CRFW_UNUSED(wrongParamValue);
  CRFW_UNUSED(tcSubtype);
  CRFW_UNUSED(tcType);
  /*
  CrIaCopy(NOFSTARTFAILEDTC_ID, &nofStartFailedTc);
  nofStartFailedTc += 1;
  CrIaPaste(NOFSTARTFAILEDTC_ID, &nofStartFailedTc);
*/

  seqCntLastStartFailTc = CrFwPcktGetSeqCnt(pckt);
/*  CrIaPaste(SEQCNTLASTSTARTFAILTC_ID, &seqCntLastStartFailTc);*/
  printf("SendTcStartRepFail: set SeqCntLastStartFailTc = %d\n", seqCntLastStartFailTc);

  /* send (1,4) TC start report - failure */
  /* Create out component */
  rep = (FwSmDesc_t) CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, CRPS_REQVERIF_START_FAIL, 0, 0);
  if (rep == NULL) 
    {
      /* TODO: enter event
         unsigned short evt_data[2] = {cpu_to_be16(192), cpu_to_be16(1)};
         CrIaEvtRep(3, EVT_TRANSF_FULL, evt_data); */
       return;
    }    
      
  /* Set out component parameters */

  tcPacketId = CrFwPcktGetPid(pckt); /* --> ADAPTATION POINT <-- */
  CrPsServReqVerifAccSuccParamSetTcPacketId(rep, tcPacketId);  /* TODO: implement own Setter for Progress Success */

  tcPacketSeqCtrl = CrFwPcktGetSeqCnt(pckt); /* --> ADAPTATION POINT <-- */
  CrPsServReqVerifAccSuccParamSetTcPacketSeqCtrl(rep, tcPacketSeqCtrl);  /* TODO: implement own Setter for Progress Success */

#if 0
  tcType = CrFwPcktGetServType(pckt); /* --> ADAPTATION POINT <-- */
  CrIaServ1StartFailParamSetTcType(rep, tcType);  /* TODO: implement own Setter for Progress Success */

  tcSubtype = CrFwPcktGetServSubType(pckt); /* --> ADAPTATION POINT <-- */
  CrIaServ1StartFailParamSetTcSubtype(rep, tcSubtype);  /* TODO: implement own Setter for Progress Success */

  CrIaServ1StartFailParamSetWrongParamPosition(rep, wrongParamPosition);  /* TODO: implement own Setter for Progress Success */

  CrIaServ1StartFailParamSetWrongParamValue(rep, wrongParamValue);  /* TODO: implement own Setter for Progress Success */

  CrIaServ1StartFailParamSetTcFailureCode(rep, tcFailureCode);  /* TODO: implement own Setter for Progress Success */
#endif

  source = CrFwPcktGetSrc(pckt); /* --> ADAPTATION POINT <-- */
  CrFwOutCmpSetDest(rep, source);
      
  CrFwOutLoaderLoad(rep);
  
  return;
}

/**
 * Generate a Request Verification Progress Successful out-going report.
 * @return nothing
 */
void SendReqVerifProgSuccRep(CrFwPckt_t pckt)
{
  FwSmDesc_t rep;
  CrFwDestSrc_t source;
  CrFwBool_t isProgressAck;
  unsigned char tcType, tcSubtype;
  unsigned short tcPacketId, tcPacketSeqCtrl;
  /*unsigned short tcPacketId, tcPacketSeqCtrl, nofTcTerm;*/

  CRFW_UNUSED(tcSubtype);
  CRFW_UNUSED(tcType);

/*
  CrIaCopy(NOFTCTERM_ID, &nofTcTerm);
  nofTcTerm += 1;
  CrIaPaste(NOFTCTERM_ID, &nofTcTerm);
*/

  isProgressAck = CrFwPcktIsProgressAck(pckt); /* --> ADAPTATION POINT <-- */

  if (isProgressAck==1)
    {
      /* send (1,7) TC termination report - success */
      /* Create out component */
      rep = (FwSmDesc_t) CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, CRPS_REQVERIF_PROG_SUCC, 0, 0);
      if (rep == NULL) 
	{
	  /* TODO: enter event
	     unsigned short evt_data[2] = {cpu_to_be16(192), cpu_to_be16(1)};
	     CrIaEvtRep(3, EVT_TRANSF_FULL, evt_data); */
	  return;
	}
      
      /* Set out component parameters */

      tcPacketId = CrFwPcktGetPid(pckt); /* --> ADAPTATION POINT <-- */
      CrPsServReqVerifAccSuccParamSetTcPacketId(rep, tcPacketId); /* TODO: implement own Setter for Progress Success */

      tcPacketSeqCtrl = CrFwPcktGetSeqCnt(pckt); /* --> ADAPTATION POINT <-- */
      CrPsServReqVerifAccSuccParamSetTcPacketSeqCtrl(rep, tcPacketSeqCtrl); /* TODO: implement own Setter for Progress Success */
      
      source = CrFwPcktGetSrc(pckt); /* --> ADAPTATION POINT <-- */
      CrFwOutCmpSetDest(rep, source);
      
      CrFwOutLoaderLoad(rep);
    }
  
  return;
}

/**
 * Generate a Request Verification Progress Failed out-going report.
 * @return nothing
 */
void SendReqVerifProgFailRep(CrFwPckt_t pckt, unsigned short tcFailureCode, unsigned short wrongParamPosition, unsigned short wrongParamValue)
{
  FwSmDesc_t rep;
  CrFwDestSrc_t source;
  /*unsigned char tcType, tcSubtype;*/
  unsigned short tcPacketId, tcPacketSeqCtrl, seqCntLastProgFailTc;
  /*unsigned short tcPacketId, tcPacketSeqCtrl, nofProgFailedTc, seqCntLastProgFailTc;*/
  CRFW_UNUSED(tcFailureCode);
  CRFW_UNUSED(wrongParamPosition);
  CRFW_UNUSED(wrongParamValue);
    
/*
  CrIaCopy(NOFPROGFAILEDTC_ID, &nofProgFailedTc);
  nofProgFailedTc += 1;
  CrIaPaste(NOFPROGFAILEDTC_ID, &nofProgFailedTc);
*/

  seqCntLastProgFailTc = CrFwPcktGetSeqCnt(pckt);
/*  CrIaPaste(SEQCNTLASTPROGFAILTC_ID, &seqCntLastProgFailTc);*/
  printf("SendTcProgRepFail: set SeqCntLastProgFailTc = %d\n", seqCntLastProgFailTc);

  /* send (1,4) TC start report - failure */
  /* Create out component */
  rep = (FwSmDesc_t) CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, CRPS_REQVERIF_PROG_FAIL, 0, 0);
  if (rep == NULL) 
    {
      /* TODO: enter event
         unsigned short evt_data[2] = {cpu_to_be16(192), cpu_to_be16(1)};
         CrIaEvtRep(3, EVT_TRANSF_FULL, evt_data); */
      return;
    }
      
  /* Set out component parameters */

  tcPacketId = CrFwPcktGetPid(pckt); /* --> ADAPTATION POINT <-- */
  CrPsServReqVerifAccSuccParamSetTcPacketId(rep, tcPacketId); /* TODO: implement own Setter for Progress Success */

  tcPacketSeqCtrl = CrFwPcktGetSeqCnt(pckt); /* --> ADAPTATION POINT <-- */
  CrPsServReqVerifAccSuccParamSetTcPacketSeqCtrl(rep, tcPacketSeqCtrl); /* TODO: implement own Setter for Progress Success */

#if 0
  tcType = CrFwPcktGetServType(pckt); /* --> ADAPTATION POINT <-- */
  CrIaServ1ProgFailParamSetTcType(rep, tcType); /* TODO: implement own Setter for Progress Success */

  tcSubtype = CrFwPcktGetServSubType(pckt); /* --> ADAPTATION POINT <-- */
  CrIaServ1ProgFailParamSetTcSubtype(rep, tcSubtype); /* TODO: implement own Setter for Progress Success */

  CrIaServ1ProgFailParamSetWrongParamPosition(rep, wrongParamPosition); /* TODO: implement own Setter for Progress Success */

  CrIaServ1ProgFailParamSetWrongParamValue(rep, wrongParamValue); /* TODO: implement own Setter for Progress Success */

  CrIaServ1ProgFailParamSetTcFailureCode(rep, tcFailureCode); /* TODO: implement own Setter for Progress Success */
#endif

  source = CrFwPcktGetSrc(pckt); /* --> ADAPTATION POINT <-- */
  CrFwOutCmpSetDest(rep, source);
      
  CrFwOutLoaderLoad(rep);
  
  return;
}

/**
 * Generate a Request Verification Termination Successful out-going report.
 * @return nothing
 */
void SendReqVerifTermSuccRep(CrFwPckt_t pckt)
{
  FwSmDesc_t rep;
  CrFwDestSrc_t source;
  CrFwBool_t isTermAck;
  unsigned char tcType, tcSubtype;
  unsigned short tcPacketId, tcPacketSeqCtrl;
  /*unsigned short tcPacketId, tcPacketSeqCtrl, nofTcTerm;*/

  CRFW_UNUSED(tcSubtype);
  CRFW_UNUSED(tcType);

/*
  CrIaCopy(NOFTCTERM_ID, &nofTcTerm);
  nofTcTerm += 1;
  CrIaPaste(NOFTCTERM_ID, &nofTcTerm);
*/

  isTermAck = CrFwPcktIsTermAck(pckt); /* --> ADAPTATION POINT <-- */

  if (isTermAck==1)
    {
      /* send (1,7) TC termination report - success */
      /* Create out component */
      rep = (FwSmDesc_t) CrFwOutFactoryMakeOutCmp(CRPS_REQVERIF, CRPS_REQVERIF_TERM_SUCC, 0, 0);
      if (rep == NULL) 
	{
	  /* TODO: enter event
	     unsigned short evt_data[2] = {cpu_to_be16(192), cpu_to_be16(1)};
	     CrIaEvtRep(3, EVT_TRANSF_FULL, evt_data); */
	  return;
	}
      
      /* Set out component parameters */

      tcPacketId = CrFwPcktGetPid(pckt); /* --> ADAPTATION POINT <-- */
      CrPsServReqVerifAccSuccParamSetTcPacketId(rep, tcPacketId); /* TODO: implement own Setter for Termination Success */

      tcPacketSeqCtrl = CrFwPcktGetSeqCnt(pckt); /* --> ADAPTATION POINT <-- */
      CrPsServReqVerifAccSuccParamSetTcPacketSeqCtrl(rep, tcPacketSeqCtrl); /* TODO: implement own Setter for Termination Success */
      
      source = CrFwPcktGetSrc(pckt); /* --> ADAPTATION POINT <-- */
      CrFwOutCmpSetDest(rep, source);
      
      CrFwOutLoaderLoad(rep);
    }
  
  return;
}

/**
 * Generate a Request Verification Termination Failed out-going report.
 * @return nothing
 */
void SendReqVerifTermFailRep(CrFwPckt_t pckt, unsigned short tcFailureCode, unsigned short wrongParamPosition, unsigned short wrongParamValue)
{
  CRFW_UNUSED(pckt);
  CRFW_UNUSED(tcFailureCode);
  CRFW_UNUSED(wrongParamPosition);
  CRFW_UNUSED(wrongParamValue);
  return;
}
