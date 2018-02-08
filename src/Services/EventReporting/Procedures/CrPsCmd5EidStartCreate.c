/**
 * @file CrPsCmd5EidStartCreate.c
 * @ingroup Serv5
 * @ingroup procedures
 *
 * @brief Create one instance of the CrPsCmd5EidStart procedure
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:17:44
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
 
#include "CrPsCmd5EidStartCreate.h"

/** FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "CrFwConstants.h"

/** CrPsCmd5EidStart function definitions */
#include <stdlib.h>

/** Guard on the Control Flow from DECISION1 to DECISION3. */
FwPrBool_t CrPsCmd5EidStartG1E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/** Guard on the Control Flow from DECISION3 to N4. */
FwPrBool_t CrPsCmd5EidStartG2E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/** Guard on the Control Flow from DECISION4 to N7. */
FwPrBool_t CrPsCmd5EidStartG3E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsCmd5EidStartCreate(void* prData)
{
	const FwPrCounterU2_t DECISION1 = 1;		/* The identifier of decision node DECISION1 in procedure CrPsCmd5EidStart */
	const FwPrCounterU2_t N_OUT_OF_DECISION1 = 2;	/* The number of control flows out of decision node DECISION1 in procedure CrPsCmd5EidStart */
	const FwPrCounterU2_t DECISION3 = 2;		/* The identifier of decision node DECISION3 in procedure CrPsCmd5EidStart */
	const FwPrCounterU2_t N_OUT_OF_DECISION3 = 2;	/* The number of control flows out of decision node DECISION3 in procedure CrPsCmd5EidStart */
	const FwPrCounterU2_t DECISION4 = 3;		/* The identifier of decision node DECISION4 in procedure CrPsCmd5EidStart */
	const FwPrCounterU2_t N_OUT_OF_DECISION4 = 2;	/* The number of control flows out of decision node DECISION4 in procedure CrPsCmd5EidStart */

	/** Create the procedure */
	FwPrDesc_t prDesc = FwPrCreate(
		6,	/* N_ANODES - The number of action nodes */
		3,	/* N_DNODES - The number of decision nodes */
		13,	/* N_FLOWS - The number of control flows */
		6,	/* N_ACTIONS - The number of actions */
		6	/* N_GUARDS - The number of guards */
	);

	/** Configure the procedure */
	FwPrSetData(prDesc, prData);
	FwPrAddActionNode(prDesc, CrPsCmd5EidStart_N4, &CrPsCmd5EidStartN4);
	FwPrAddActionNode(prDesc, CrPsCmd5EidStart_N1, &CrPsCmd5EidStartN1);
	FwPrAddDecisionNode(prDesc, DECISION1, N_OUT_OF_DECISION1);
	FwPrAddActionNode(prDesc, CrPsCmd5EidStart_N2, &CrPsCmd5EidStartN2);
	FwPrAddActionNode(prDesc, CrPsCmd5EidStart_N3, &CrPsCmd5EidStartN3);
	FwPrAddDecisionNode(prDesc, DECISION3, N_OUT_OF_DECISION3);
	FwPrAddDecisionNode(prDesc, DECISION4, N_OUT_OF_DECISION4);
	FwPrAddActionNode(prDesc, CrPsCmd5EidStart_N7, &CrPsCmd5EidStartN7);
	FwPrAddActionNode(prDesc, CrPsCmd5EidStart_N8, &CrPsCmd5EidStartN8);
	FwPrAddFlowIniToAct(prDesc, CrPsCmd5EidStart_N1, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmd5EidStart_N4, DECISION1, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmd5EidStart_N1, DECISION1, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsCmd5EidStart_N2, &CrPsCmd5EidStartG1);
	FwPrAddFlowDecToDec(prDesc, DECISION1, DECISION3, &CrPsCmd5EidStartG1E);
	FwPrAddFlowActToAct(prDesc, CrPsCmd5EidStart_N2, CrPsCmd5EidStart_N3, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmd5EidStart_N3, DECISION3, NULL);
	FwPrAddFlowDecToDec(prDesc, DECISION3, DECISION4, &CrPsCmd5EidStartG2);
	FwPrAddFlowDecToAct(prDesc, DECISION3, CrPsCmd5EidStart_N4, &CrPsCmd5EidStartG2E);
	FwPrAddFlowDecToAct(prDesc, DECISION4, CrPsCmd5EidStart_N8, &CrPsCmd5EidStartG3);
	FwPrAddFlowDecToAct(prDesc, DECISION4, CrPsCmd5EidStart_N7, &CrPsCmd5EidStartG3E);
	FwPrAddFlowActToFin(prDesc, CrPsCmd5EidStart_N7, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsCmd5EidStart_N8, NULL);

	return prDesc;
}