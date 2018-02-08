/**
 * @file
 * @ingroup inMngGroup
 * Execution Procedure for the InReport Component.
 * This procedure has single node which executes the Update Action of the
 * InReport (see figure below).
 * This header file gives access to a make function which creates a new
 * instance of the procedure.
 *
 * @image html InReportExecution.png
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

#ifndef CRFW_INREP_EXEC_PROC_H_
#define CRFW_INREP_EXEC_PROC_H_

/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwPrConstants.h"
/* Include framework files */
#include "CrFwConstants.h"

/**
 * Create a new instance of the InReport Execution Procedure.
 * This function returns the descriptor of newly created InReport Execution Procedure.
 * Note that no data are attached to the descriptor as it is returned by this
 * function.
 * @return the descriptor of the InReport Execution Procedure or NULL if the
 * procedure could not be created.
 */
FwPrDesc_t CrFwInRepExecProcMake();

#endif /* CRFW_INREP_EXEC_PROC_H_ */
