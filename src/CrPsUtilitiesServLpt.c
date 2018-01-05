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

#include "CrPsUtilitiesServLpt.h"
#include "Pckt/CrFwPckt.h"     /* --- interface to adaptation point CrFwPckt --- */

/* CrFramework includes */
#include <OutFactory/CrFwOutFactory.h>
#include <OutLoader/CrFwOutLoader.h>
#include <CrFwCmpData.h>

/* FwProfile includes */
#include <FwPrCore.h>
#include <FwPrConfig.h>
#include <FwSmConfig.h>

#include <Services/General/CrPsConstants.h>
#include <Services/LargePacketTransfer/Procedures/CrPsLptUpCmdStartCreate.h>
#include <Services/LargePacketTransfer/StateMachines/CrPsLptCreate.h>

#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServLpt.h>

#include <time.h>
#include <stdlib.h>

/* global handles for the procedures */
FwPrDesc_t prDescLptUpCmdStart; 
FwSmDesc_t smDescLpt;


/**
 * Initialization of CORDET Framework PUS Extension components
 */
int CrPsInitServLpt()
{
  /***********************************************************************/
  /* Service Large Packet Transfer Procedure                             */
  /***********************************************************************/
  prDescLptUpCmdStart = CrPsLptUpCmdStartCreate(NULL);
  if (FwPrCheck(prDescLptUpCmdStart) != prSuccess)
    {
      return EXIT_FAILURE;
    }

  /***********************************************************************/
  /* Service Large Packet Transfer State Machine                         */
  /***********************************************************************/
  smDescLpt = CrPsLptCreate(NULL);
  if (FwSmCheckRec(smDescLpt) != smSuccess)
    {
      return EXIT_FAILURE;
    }
  FwSmStart(smDescLpt);

  /* initialize Datapool Values */
  initDpServLpt(); 
  
  {
    setDplptSizeItem(0, getLptMemSize(0));
  }
  return EXIT_SUCCESS;
}

/**
 * Execution of CORDET Framework PUS Extension components
 */
void CrPsExecServLptSm()
{
  FwSmMakeTrans(smDescLpt, Execute);

  return;
}

/**
 * Execution of CORDET Framework PUS Extension components
 */
void CrPsExecServLpt()
{
  /* NOP */

  return;
}

/**
 * Getter for LptUpCmdStart procedure descriptor
 */
inline FwPrDesc_t getPrDescLptUpCmdStart()
{
  return prDescLptUpCmdStart;
}

/**
 * Getter for Lpt state machine descriptor
 */
inline FwSmDesc_t getSmDescLpt()
{
  return smDescLpt;
}

/**
 * Provide the current time.
 *
 * This function implements the CORDET interface from CrFwTime.h. Time is
 * provided as a 32-bit integer of which the MSB 8 bits are set to zero and the
 * remaining 24 bits comply with the CUC time format (the 0
 *
 * \note This implementation uses a fixed value of `1413208149`. This is the
 *       output of `date +%s` at some time in October 2014.
 * \todo Reimplement for the final application.
 */
CrFwTimeStamp_t CrFwGetCurrentTimeServer()
{
  struct timespec now;
  time_t coarse;
  unsigned int fine;
  CrFwTimeStamp_t ts; /* unsigned char struct.t[6] */
  
  clock_gettime(CLOCK_REALTIME, &now);
  coarse = now.tv_sec;
  fine = (unsigned int)(32.768 * (float)now.tv_nsec / (float)1000000);
    
  ts.t[3] = coarse & 0xff;
  ts.t[2] = (coarse >> 8) & 0xff;
  ts.t[1] = (coarse >> 16) & 0xff;
  ts.t[0] = (coarse >> 24) & 0xff;
  ts.t[4] = (fine >> 7) & 0x7f;
  ts.t[5] = fine & 0xfe;
  
  return ts;
}
