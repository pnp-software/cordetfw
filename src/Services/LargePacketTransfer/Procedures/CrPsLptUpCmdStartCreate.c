/**
 * @file CrPsLptUpCmdStartCreate.c
 * @ingroup Serv13
 * @ingroup procedures
 *
 * @brief Create one instance of the CrPsLptUpCmdStart procedure
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Nov 26 2017 12:7:49
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

#include "CrPsLptUpCmdStartCreate.h"

/** CR Framework function definitions*/
#include "CrFwConstants.h"

/** FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"

/** CrPsLptUpCmdStart function definitions */
#include <stdlib.h>


/**
 * Guard on the Control Flow from DECISION1 to DECISION2.
 * Else 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
static FwPrBool_t code90177(FwPrDesc_t prDesc) /*TODO change the name */
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/**
 * Guard on the Control Flow from DECISION2 to N4.
 * Else 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
static FwPrBool_t code70152(FwPrDesc_t prDesc) /*TODO change the name */
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsLptUpCmdStartCreate(void* prData)
{
	const FwPrCounterU2_t DECISION1 = 1;		/* The identifier of decision node DECISION1 in procedure CrPsLptUpCmdStart */
	const FwPrCounterU2_t N_OUT_OF_DECISION1 = 2;	/* The number of control flows out of decision node DECISION1 in procedure CrPsLptUpCmdStart */
	const FwPrCounterU2_t DECISION2 = 2;		/* The identifier of decision node DECISION2 in procedure CrPsLptUpCmdStart */
	const FwPrCounterU2_t N_OUT_OF_DECISION2 = 2;	/* The number of control flows out of decision node DECISION2 in procedure CrPsLptUpCmdStart */

	/** Create the procedure */
	FwPrDesc_t prDesc = FwPrCreate(
		4,	/* N_ANODES - The number of action nodes */
		2,	/* N_DNODES - The number of decision nodes */
		9,	/* N_FLOWS - The number of control flows */
		4,	/* N_ACTIONS - The number of actions */
		4	/* N_GUARDS - The number of guards */
	);

	/** Configure the procedure */
	FwPrSetData(prDesc, prData);
	FwPrAddActionNode(prDesc, CrPsLptUpCmdStart_N1, &CrPsLptUpCmdStartN1);
	FwPrAddDecisionNode(prDesc, DECISION1, N_OUT_OF_DECISION1);
	FwPrAddActionNode(prDesc, CrPsLptUpCmdStart_N2, &CrPsLptUpCmdStartN2);
	FwPrAddDecisionNode(prDesc, DECISION2, N_OUT_OF_DECISION2);
	FwPrAddActionNode(prDesc, CrPsLptUpCmdStart_N3, &CrPsLptUpCmdStartN3);
	FwPrAddActionNode(prDesc, CrPsLptUpCmdStart_N4, &CrPsLptUpCmdStartN4);
	FwPrAddFlowIniToAct(prDesc, CrPsLptUpCmdStart_N1, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsLptUpCmdStart_N1, DECISION1, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsLptUpCmdStart_N2, &CrPsLptUpCmdStartG1);
	FwPrAddFlowDecToDec(prDesc, DECISION1, DECISION2, &code90177);
	FwPrAddFlowActToFin(prDesc, CrPsLptUpCmdStart_N2, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsLptUpCmdStart_N3, &CrPsLptUpCmdStartNG2);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsLptUpCmdStart_N4, &code70152);
	FwPrAddFlowActToAct(prDesc, CrPsLptUpCmdStart_N3, CrPsLptUpCmdStart_N2, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsLptUpCmdStart_N4, NULL);

	return prDesc;
}
