/**
 * @file CrPsCmd3s10StartCreate.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:16:40
 */

#include "CrPsCmd3s10StartCreate.h"

/** CR Framework function definitions*/
#include "CrFwConstants.h"

/** FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"

/** CrPsCmd3s10Start function definitions */
#include <stdlib.h>
#include "CrPsDebug.h"

/** Guard on the Control Flow from DECISION1 to DECISION2. */
FwPrBool_t CrPsCmd3s10StartG1E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	DEBUGP_3("CrPsCmd3s10StartG1E.\n");
	return 1;
}

/** Guard on the Control Flow from DECISION2 to N4. */
FwPrBool_t CrPsCmd3s10StartG2E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	DEBUGP_3("CrPsCmd3s10StartG2E.\n");
	return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsCmd3s10StartCreate(void* prData)
{
	const FwPrCounterU2_t DECISION1 = 1;		/* The identifier of decision node DECISION1 in procedure CrPsCmd3s10Start */
	const FwPrCounterU2_t N_OUT_OF_DECISION1 = 2;	/* The number of control flows out of decision node DECISION1 in procedure CrPsCmd3s10Start */
	const FwPrCounterU2_t DECISION2 = 2;		/* The identifier of decision node DECISION2 in procedure CrPsCmd3s10Start */
	const FwPrCounterU2_t N_OUT_OF_DECISION2 = 2;	/* The number of control flows out of decision node DECISION2 in procedure CrPsCmd3s10Start */

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
	FwPrAddActionNode(prDesc, CrPsCmd3s10Start_N1, &CrPsCmd3s10StartN1);
	FwPrAddDecisionNode(prDesc, DECISION1, N_OUT_OF_DECISION1);
	FwPrAddActionNode(prDesc, CrPsCmd3s10Start_N2, &CrPsCmd3s10StartN2);
	FwPrAddDecisionNode(prDesc, DECISION2, N_OUT_OF_DECISION2);
	FwPrAddActionNode(prDesc, CrPsCmd3s10Start_N3, &CrPsCmd3s10StartN3);
	FwPrAddActionNode(prDesc, CrPsCmd3s10Start_N4, &CrPsCmd3s10StartN4);
	FwPrAddFlowIniToAct(prDesc, CrPsCmd3s10Start_N1, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmd3s10Start_N1, DECISION1, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsCmd3s10Start_N2, &CrPsCmd3s10StartG1);
	FwPrAddFlowDecToDec(prDesc, DECISION1, DECISION2, &CrPsCmd3s10StartG1E);
	FwPrAddFlowActToFin(prDesc, CrPsCmd3s10Start_N2, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmd3s10Start_N3, &CrPsCmd3s10StartG2);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmd3s10Start_N4, &CrPsCmd3s10StartG2E);
	FwPrAddFlowActToAct(prDesc, CrPsCmd3s10Start_N3, CrPsCmd3s10Start_N2, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsCmd3s10Start_N4, NULL);

	return prDesc;
}