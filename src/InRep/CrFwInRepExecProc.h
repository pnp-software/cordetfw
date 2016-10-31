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
