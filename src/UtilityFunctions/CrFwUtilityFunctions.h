/**
 * @file
 * @ingroup utilityFunctionsGroup
 * Definition of the utility functions for the CORDET Framework.
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2025, All Rights Reserved
 *
 * This file is part of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#ifndef CRFW_UTILITY_FUNCTIONS_H_
#define CRFW_UTILITY_FUNCTIONS_H_

/* Include FW Profile Files */
#include "FwSmConstants.h"
#include "FwPrConstants.h"
/* Include Framework Files */
#include "CrFwConstants.h"
/* Include Configuration Files */
#include "CrFwUserConstants.h"

/**
 * Return the value of the application error code.
 * The application error code is set by a framework function when when either
 * of the following situations arises:
 * - a framework function has been called by the application code with an illegal
 *   parameter values or in an illegal context and execution of the function with the illegal
 *   values would cause an internal framework data structure to be corrupted.
 * - a framework function which releases dynamically allocated framework components has been
 *   asked to either release a non-allocated component or to release a component which had
 *   already been released.
 * .
 * Nominally, the application error code should be equal to: <code>::crNoAppErr</code>.
 * If the application error code has a different value, then it is likely that the
 * framework is not configured as the user intended.
 * @return the application error code
 */
CrFwAppErrCode_t CrFwGetAppErrCode();

/**
 * Set the value of the application error code (see <code>::CrFwGetAppErrCode</code>).
 * @param errCode the application error code
 */
void CrFwSetAppErrCode(CrFwAppErrCode_t errCode);

/**
 * Convenience function to set the outcome field of the component data of a procedure.
 * This function assumes that the data attached to the procedure descriptor is a pointer to
 * type <code>::CrFwCmpData</code>).
 * This type is a data structure which includes an 'outcome' field and this function sets this
 * field to the value of the argument <code>outcome</code>.
 * Each procedure is free to set its own convention for the interpretation of the outcome
 * but, for procedures defined at CORDET Framework level, a value of 0 means "failure" and a value of
 * 1 means "success".
 * @param prDesc the procedure descriptor
 * @param outcome the value of the procedure outcome
 */
void CrFwSetPrOutcome(FwPrDesc_t prDesc, CrFwOutcome_t outcome);

/**
 * Convenience function to check whether the outcome of the last check or action
 * is equal to 1 ("true" or "success").
 * This function returns "true" if and only if the outcome field of the component data (see
 * <code>::CrFwCmpData</code>) is equal to 1.
 * This function is intended to be used as a guard in a procedure.
 * @param prDesc the procedure descriptor
 * @return return 1 if the outcome is 1 and return 0 otherwise
 */
FwPrBool_t CrFwIsPrOutcomeOne(FwPrDesc_t prDesc);

/**
 * Convenience function to set the outcome of the last check or action of a state machine.
 * This function assumes that the data attached to the state machine descriptor is a pointer to
 * type <code>::CrFwCmpData</code>).
 * This type is a data structure which includes an 'outcome' field and this function sets this
 * field to the value of the argument <code>outcome</code>.
 * Each state machine is free to set its own convention for the interpretation of the outcome.
 * For state machines representing commands and reports, a value of 1 means "success", and a value
 * different from 1 means "failure".
 * In the latter case, the value of the outcome is the failure code describing the reason for the
 * failure.
 * @param smDesc the state machine descriptor
 * @param outcome the value of the state machine outcome
 */
void CrFwSetSmOutcome(FwSmDesc_t smDesc, CrFwOutcome_t outcome);

/**
 * Convenience function to get the outcome of the last check or action of a state machine.
 * This function assumes that the data attached to the state machine descriptor is a pointer to
 * type <code>::CrFwCmpData</code>).
 * This type is a data structure which includes an 'outcome' field and this function sets this
 * field to the value of the argument <code>outcome</code>.
 * Each state machine is free to set its own convention for the interpretation of the outcome.
 * For state machines representing commands and reports, a value of 1 means "success", and a value
 * different from 1 means "failure".
 * In the latter case, the value of the outcome is the failure code describing the reason for the
 * failure.
 * @param smDesc the state machine descriptor
 * @return outcome the value of the state machine outcome
 */
CrFwOutcome_t CrFwGetSmOutcome(FwSmDesc_t smDesc);

/**
 * Convenience function to check whether the outcome of the last check or action
 * is equal to 0 ("false").
 * This function returns "true" if and only if the outcome field of the component data (see
 * <code>::CrFwCmpData</code>) is equal to 0.
 * This function is intended to be used as a guard in a state machine.
 * @param smDesc the state machine descriptor
 * @return return 1 if the outcome is 0 and return 0 otherwise
 */
FwSmBool_t CrFwIsSmOutcomeZero(FwSmDesc_t smDesc);

/**
 * Convenience function to check whether the outcome of the last check or action
 * is equal to 1 ("true").
 * This function returns "true" if and only if the outcome field of the component data (see
 * <code>::CrFwCmpData</code>) is equal to 1.
 * This function is intended to be used as a guard in a state machine.
 * @param smDesc the state machine descriptor
 * @return return 1 if the outcome is 1 and return 0 otherwise
 */
FwSmBool_t CrFwIsSmOutcomeOne(FwSmDesc_t smDesc);

/**
 * Convenience function to check whether the outcome of the last check or action
 * is equal to 2.
 * This function returns "true" if and only if the outcome field of the component data (see
 * <code>::CrFwCmpData</code>) is equal to 2.
 * This function is intended to be used as a guard in a state machine.
 * @param smDesc the state machine descriptor
 * @return return 1 if the outcome is 2 and return 0 otherwise
 */
FwSmBool_t CrFwIsSmOutcomeTwo(FwSmDesc_t smDesc);

/**
 * Convenience function which returns true when a procedure has spent more than one cycle
 * in the current action node.
 * This function can be used as a guard in a procedure where there is a need to express
 * the fact that the procedure should remain only one cycle in a node: the guard is false
 * after the action node has been executed the first time and becomes true after it has been
 * executed the second time.
 * @param prDesc the procedure descriptor
 * @return return 1 if the action of the current node has been executed two or more times;
 * return 0 otherwise.
 */
FwPrBool_t CrFwWaitOnePrCycle(FwPrDesc_t prDesc);

/**
 * Convenience function to be used in a procedure as default implementation for a check
 * which always returns true.
 * @param prDesc the procedure descriptor
 * @return always returns true
 */
CrFwBool_t CrFwPrCheckAlwaysTrue(FwPrDesc_t prDesc);

/**
 * Convenience function to be used in a state machine as default implementation for a check
 * which always returns true.
 * @param smDesc the state machine descriptor
 * @return always returns true
 */
CrFwBool_t CrFwSmCheckAlwaysTrue(FwSmDesc_t smDesc);

/**
 * Convenience function to be used in a state machine as default implementation for a check
 * which always returns false.
 * @param smDesc the state machine descriptor
 * @return always returns false
 */
CrFwBool_t CrFwSmCheckAlwaysFalse(FwSmDesc_t smDesc);

/**
 * Convenience function to be used in a procedure as default implementation for an action
 * which returns without doing anything.
 * @param prDesc the procedure descriptor
 */
void CrFwPrEmptyAction(FwPrDesc_t prDesc);

/**
 * Convenience function to be used in a state machine as default implementation for an action
 * which returns without doing anything.
 * @param smDesc the state machine descriptor
 */
void CrFwSmEmptyAction(FwSmDesc_t smDesc);

/**
 * Convenience function to be used in a state machine as default implementation for an action
 * which sets the action outcome to 1 (corresponding to 'success') and then returns.
 * @param smDesc the state machine descriptor
 */
void CrFwSmSuccessAction(FwSmDesc_t smDesc);

/**
 * Convenience function to retrieve the index of an array where a certain target value is
 * located.
 * This function assumes that the entries in the array are arranged in increasing order.
 * The function finds the index corresponding to a given target key value.
 * If the target key value is not in the array, the function returns the length of the
 * array.
 * @param keyValArray array of key values (key values must be stored in increasing order)
 * @param length length of the array of key values
 * @param targetKey the key value that is searched
 * @return the index in the array where the target key value is located or the length of the
 * array if the target key value is not in the array
 */
CrFwCounterU2_t CrFwFindKeyIndex(CrFwCounterU3_t* keyValArray,
        CrFwCounterU2_t length, CrFwCounterU3_t targetKey);

/**
 * Convenience function to compute the CRC-CCITT-FALSE (also known as CRC-16-CCITT-FALSE) 
 * CRC over the next N bytes of an array of bytes.
 * This function is used where the CRC of a very long array is computed in chunks.
 * The argument <code>crc</code> is the CRC over the first part of the array.
 * The argument data is the pointer to the next N bytes of the array.
 * The functionCRC over the first part of the array is <code>crc</code>.
 * 
 * If there is a need to compute the CRC over one single array of length N, 
 * crcPrev should be set to 0xFFFF. 
 * 
 * The function performs no checks on the validity of the array pointer it is passed.
 * @param crc CRC over the previous chunk of data
 * @param data next chunk of data array over which the CRC should be computed 
 * @param N length of the next chunk of data 
 * @return the CRC computed over the argument array
 */
CrFwCrc_t CrFwUpdateCrc(CrFwCrc_t crc, unsigned char* data, CrFwCounterU3_t N);

#endif /* CRFW_UTILITY_FUNCTIONS_H_ */
