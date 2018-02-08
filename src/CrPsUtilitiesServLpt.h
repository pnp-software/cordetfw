/**
 * @file CrPsUtilitiesServLpt.h
 * @ingroup Utilities
 * @ingroup Serv13
 *
 * @brief Interface through which applications can initialize and execute framework PUS extension components
 *
 * @author Christian Reimers <christian.reimers@univie.ac.at>
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

#ifndef CRPS_UTILITIES_SERVLPT_H_
#define CRPS_UTILITIES_SERVLPT_H_

#include <CrFwConstants.h>

/* global handles for the procedures */
extern uint32_t DownTransferLptBufferId;
extern uint32_t UpTransferLptBufferId;


/**
 * Initialization of CORDET Framework PUS Extension components
 * @return nothing
 */
int CrPsInitServLpt();

/**
 * Execution of CORDET Framework PUS Extension components
 * @return nothing
 */
void CrPsExecServLpt();

/**
 * Execution of CORDET Framework PUS Extension components
 * @return nothing
 */
void CrPsExecServLptSm();

/**
 * Getter for LptUpCmdStart procedure descriptor
 */
FwPrDesc_t getPrDescLptUpCmdStart();

/**
 * Getter for Lpt state machine descriptor
 */
FwSmDesc_t getSmDescLpt();

/**
 * Getter function for the Address of the Data
 * @param LptBuffer The number ot the Large Packet Transfer Buffer 
 * @return Pointer to the memory array of the LptBuffer
 */
uint32_t* getLptMemStartAddr(uint32_t LptBuffer); /* Adaptation Point */

/**
 * Getter function to return the size of the Data
 * @param LptBuffer The number ot the Large Packet Transfer Buffer 
 * @return LPTSIZE The size of the LptBuffer
 */
uint32_t getLptMemSize(uint32_t LptBuffer); /* Adaptation Point */

/**
 * Provide the current time.
 *
 * This function implements the CORDET interface from CrFwTime.h. Time is
 * provided as a 32-bit integer of which the MSB 8 bits are set to zero and the
 * remaining 24 bits comply with the CUC time format (the 0
 *
 * \note This implementation uses a fixed value of `1413208149`. This is the
 *       output of `date +%s` at some time in October 2014.
 * \TODO Reimplement for the final application.
 */
CrFwTimeStamp_t CrFwGetCurrentTimeServer();

#endif /* CRPS_UTILITIES_SERVLPT_H_ */
