/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Interface for the OutStream stub.
 * The OutStream stub is used in the CORDET Test Suite to verify the implementation
 * of the OutStream component (see <code>CrFwOutStream.h</code>).
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

#ifndef CRFW_OUTSTREAMSTUB_H_
#define CRFW_OUTSTREAMSTUB_H_

/* Include configuration files */
#include "CrFwUserConstants.h"
/* Include Framework Files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"

/**
 * Dummy implementation of an initialization or configuration check for an OutStream.
 * The outcome of this check is given by the value of a settable flag (<code>checkFlag</code>)
 * whose value is set through function <code>::CrFwOutStreamStubSetCheckFlag</code>.
 * @param prDesc the initialization or configuration procedure descriptor (this parameter
 * is not used).
 */
void CrFwOutStreamStubDummyCheck(FwPrDesc_t prDesc);

/**
 * Set the value of the check flag which determines the outcome of the dummy check of
 * <code>::CrFwOutStreamStubDummyCheck</code>.
 * @param flag the check flag
 */
void CrFwOutStreamStubSetCheckFlag(CrFwBool_t flag);

/**
 * Dummy implementation of a configuration action for an OutStream.
 * The outcome of this implementation is given by the value of a settable flag
 * (<code>actionFlag</code>) whose value is set through function
 * <code>::CrFwOutStreamStubSetActionFlag</code>.
 *
 * Like all application-specific OutStream Initialization Actions, this function
 * also calls the default OutStream Initialization Action (<code>::CrFwOutStreamDefInitAction</code>)
 * to ensure that default initialization actions are performed.
 * The <code>::CrFwOutStreamDefInitAction</code> function dynamically allocates
 * memory for an internal OutStream data structure. In order to avoid memory
 * leaks, function <code>::CrFwOutStreamDefInitAction</code> is only called if
 * the OutStream data structure has not yet been initialized.
 *
 * @param prDesc the initialization or configuration procedure descriptor (this parameter
 * is not used).
 */
void CrFwOutStreamStubInitAction(FwPrDesc_t prDesc);

/**
 * Dummy implementation of a configuration action for an OutStream.
 * The outcome of this implementation is given by the value of a settable flag
 * (<code>actionFlag</code>) whose value is set through function
 * <code>::CrFwOutStreamStubSetActionFlag</code>.
 *
 * Like all application-specific OutStream Configuration Actions, this function
 * also calls the default OutStream Configuration Action.
 *
 * @param prDesc the initialization or configuration procedure descriptor (this parameter
 * is not used).
 */
void CrFwOutStreamStubConfigAction(FwPrDesc_t prDesc);

/**
 * Set the value of the action flag which determines the outcome of the initialization of
 * configuration action.
 * @param flag the action flag
 */
void CrFwOutStreamStubSetActionFlag(CrFwBool_t flag);

/**
 * Stub function implementing the hand-over operation for the OutStream.
 * This function increments a counter when it is called and returns
 * the value of a pre-defined flag.
 * The value of the counter can be read with function
 * <code>::CrFwOutStreamStubGetHandoverCnt</code>.
 * The value of the flag can be set with function
 * <code>::CrFwOutStreamStubSetHandoverFlag</code>.
 * @param pckt the packet (not used in this stub)
 * @return the value of flag <code>pcktHandOverFlag</code>
 */
CrFwBool_t CrFwOutStreamStubPcktHandover(CrFwPckt_t pckt);

/**
 * Return the value of the handover counter which is incremented
 * by the packet handover function in <code>::CrFwOutStreamStubPcktHandover</code>.
 * @return the value of the handover counter
 */
CrFwCounterU1_t CrFwOutStreamStubGetHandoverCnt();

/**
 * Set the value of the handover flag which determines the outcome of the packet
 * handover in <code>::CrFwOutStreamStubPcktHandover</code>.
 * @param flag the handover flag
 */
void CrFwOutStreamStubSetHandoverFlag(CrFwBool_t flag);

/**
 * Stub function implementing the shutdown operation for an OutStream.
 * This function increments a counter and then calls the default shutdown
 * operation (<code>::CrFwOutStreamDefShutdownAction</code>).
 * The value of the counter can be read with function
 * <code>::CrFwOutStreamStubGetHandoverCnt</code>.
 * @param smDesc the state machine descriptor of the OutStream
 */
void CrFwOutStreamStubShutdown(FwSmDesc_t smDesc);

/**
 * Return the value of the shutdown counter which is incremented
 * by the packet shutdown function in <code>::CrFwOutStreamStubShutdown</code>.
 * @return the value of the shutdown counter
 */
CrFwCounterU1_t CrFwOutStreamStubGetShutdownCnt();

#endif /* CRFW_OUTSTREAMSTUB_H_ */
