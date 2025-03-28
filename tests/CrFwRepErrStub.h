/**
 * @file
 * @ingroup CrTestSuiteGroup
 * The CORDET Framework defines an interface for generating error reports (see
 * <code>CrFwRepErr.h</code>).
 * A stub implementation for this interface is provided in <code>CrFwRepErr.c</code>.
 * The present module defines the public functions which are implemented by
 * <code>CrFwRepErr.c</code> but which are not declared in <code>CrFwRepErr.h</code>.
 * Thus, the complete interface of the error reporting stub implemented in
 * <code>CrFwRepErr.c</code> is provided in:
 * - <code>CrFwRepErr.h</code> (interface defined at framework level)
 * - this module (interface defined for testing purposes)
 * .
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#ifndef CRFW_REPERRSTUB_H_
#define CRFW_REPERRSTUB_H_

/* Include Framework Files */
#include "CrFwConstants.h"
/* Include Configuration Files */
#include "CrFwUserConstants.h"

/**
 * Return the position in the error report array at which the next error report will be written.
 * @return the position in the error report array at which the next error report will be written
 */
CrFwCounterU2_t CrFwRepErrStubGetPos();

/**
 * Reset the error reporting interface.
 * This effectively deletes all error reports created since the last reset.
 */
void CrFwRepErrStubReset();

/**
 * Return the error code of the error report at position
 * <code>errRepPos</code>.
 * This function is provided for convenience during testing.
 * It is not part of the error reporting interface.
 * @param errRepPos the position in the error reporting array
 * @return the error code
 */
CrFwRepErrCode_t CrFwRepErrStubGetErrCode(CrFwCounterU2_t errRepPos);

/**
 * Return the type identifier of the error report at position
 * <code>errRepPos</code>.
 * This function is provided for convenience during testing.
 * It is not part of the error reporting interface.
 * @param errRepPos the position in the error reporting array
 * @return the error code
 */
CrFwTypeId_t CrFwRepErrStubGetTypeId(CrFwCounterU2_t errRepPos);

/**
 * Return the instance identifier of the error report at position
 * <code>errRepPos</code>.
 * This function is provided for convenience during testing.
 * It is not part of the error reporting interface.
 * @param errRepPos the position in the error reporting array
 * @return the error code
 */
CrFwInstanceId_t CrFwRepErrStubGetInstanceId(CrFwCounterU2_t errRepPos);

/**
 * Return the array holding the parameters associated to the error
 * report at position <code>errRepPos</code>.
 * This function is provided for convenience during testing.
 * It is not part of the error reporting interface.
 * @param errRepPos the position in the error reporting array
 * @return the error code
 */
CrFwCounterU1_t* CrFwRepErrStubGetParArray(CrFwCounterU2_t errRepPos);

/**
 * Return the destination associated to the error report at
 * position <code>errRepPos</code>.
 * This function assumes that the error report at position
 * <code>errRepPos</code> was created with a call to
 * <code>::CrFwRepErrDestSrc</code>.
 * @param errRepPos the position in the error reporting array
 * @return the destination
 */
CrFwDestSrc_t CrFwRepErrStubGetDest(CrFwCounterU2_t errRepPos);

/**
 * Return the expected sequence counter associated to the error report at
 * position <code>errRepPos</code>.
 * This function assumes that the error report at position
 * <code>errRepPos</code> was created with a call to
 * <code>::CrFwRepErrSeqCnt</code>.
 * @param errRepPos the position in the error reporting array
 * @return the expected sequence counter
 */
CrFwSeqCnt_t CrFwRepErrStubGetExpSeqCnt(CrFwCounterU2_t errRepPos);

/**
 * Return the actual sequence counter associated to the error report at
 * position <code>errRepPos</code>.
 * This function assumes that the error report at position
 * <code>errRepPos</code> was created with a call to
 * <code>::CrFwRepErrSeqCnt</code>.
 * @param errRepPos the position in the error reporting array
 * @return the actual sequence counter
 */
CrFwSeqCnt_t CrFwRepErrStubGetActualSeqCnt(CrFwCounterU2_t errRepPos);

#endif /* CRFW_REPERRSTUB_H_ */
