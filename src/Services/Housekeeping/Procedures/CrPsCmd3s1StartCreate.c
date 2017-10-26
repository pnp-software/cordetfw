/**
 * @file CrPsCmd3s1StartCreate.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:15:56
 */

#include "CrPsCmd3s1StartCreate.h"

/** CR Framework function definitions*/
#include "CrFwConstants.h"

/** FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"

/** CrPsCmd3s1Start function definitions */
#include <stdlib.h>
#include "CrPsDebug.h"

/** Guard on the Control Flow from DECISION1 to DECISION2. */
FwPrBool_t CrPsCmd3s1StartG1E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/** Guard on the Control Flow from DECISION2 to DECISION3. */
FwPrBool_t CrPsCmd3s1StartG2E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/** Guard on the Control Flow from DECISION3 to DECISION4. */
FwPrBool_t CrPsCmd3s1StartG3E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/** Guard on the Control Flow from DECISION4 to N2. */
FwPrBool_t CrPsCmd3s1StartG4E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/** Guard on the Control Flow from DECISION5 to N4. */
FwPrBool_t CrPsCmd3s1StartG5E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/** Guard on the Control Flow from DECISION6 to N11. */
FwPrBool_t CrPsCmd3s1StartG6E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsCmd3s1StartCreate(void* prData)
{
	const FwPrCounterU2_t DECISION1 = 1;		/* The identifier of decision node DECISION1 in procedure CrPsCmd3s1Start */
	const FwPrCounterU2_t N_OUT_OF_DECISION1 = 2;	/* The number of control flows out of decision node DECISION1 in procedure CrPsCmd3s1Start */
	const FwPrCounterU2_t DECISION2 = 2;		/* The identifier of decision node DECISION2 in procedure CrPsCmd3s1Start */
	const FwPrCounterU2_t N_OUT_OF_DECISION2 = 2;	/* The number of control flows out of decision node DECISION2 in procedure CrPsCmd3s1Start */
	const FwPrCounterU2_t DECISION3 = 3;		/* The identifier of decision node DECISION3 in procedure CrPsCmd3s1Start */
	const FwPrCounterU2_t N_OUT_OF_DECISION3 = 2;	/* The number of control flows out of decision node DECISION3 in procedure CrPsCmd3s1Start */
	const FwPrCounterU2_t DECISION4 = 4;		/* The identifier of decision node DECISION4 in procedure CrPsCmd3s1Start */
	const FwPrCounterU2_t N_OUT_OF_DECISION4 = 2;	/* The number of control flows out of decision node DECISION4 in procedure CrPsCmd3s1Start */
	const FwPrCounterU2_t DECISION5 = 5;		/* The identifier of decision node DECISION5 in procedure CrPsCmd3s1Start */
	const FwPrCounterU2_t N_OUT_OF_DECISION5 = 2;	/* The number of control flows out of decision node DECISION5 in procedure CrPsCmd3s1Start */
	const FwPrCounterU2_t DECISION6 = 6;		/* The identifier of decision node DECISION6 in procedure CrPsCmd3s1Start */
	const FwPrCounterU2_t N_OUT_OF_DECISION6 = 2;	/* The number of control flows out of decision node DECISION6 in procedure CrPsCmd3s1Start */

	/** Create the procedure */
	FwPrDesc_t prDesc = FwPrCreate(
		11,	/* N_ANODES - The number of action nodes */
		6,	/* N_DNODES - The number of decision nodes */
		24,	/* N_FLOWS - The number of control flows */
		11,	/* N_ACTIONS - The number of actions */
		12	/* N_GUARDS - The number of guards */
	);

	/** Configure the procedure */
	FwPrSetData(prDesc, prData);
	FwPrAddDecisionNode(prDesc, DECISION1, N_OUT_OF_DECISION1);
	FwPrAddActionNode(prDesc, CrPsCmd3s1Start_N1, &CrPsCmd3s1StartN1);
	FwPrAddDecisionNode(prDesc, DECISION2, N_OUT_OF_DECISION2);
	FwPrAddDecisionNode(prDesc, DECISION3, N_OUT_OF_DECISION3);
	FwPrAddActionNode(prDesc, CrPsCmd3s1Start_N4, &CrPsCmd3s1StartN4);
	FwPrAddDecisionNode(prDesc, DECISION4, N_OUT_OF_DECISION4);
	FwPrAddActionNode(prDesc, CrPsCmd3s1Start_N2, &CrPsCmd3s1StartN2);
	FwPrAddDecisionNode(prDesc, DECISION5, N_OUT_OF_DECISION5);
	FwPrAddActionNode(prDesc, CrPsCmd3s1Start_N3, &CrPsCmd3s1StartN3);
	FwPrAddDecisionNode(prDesc, DECISION6, N_OUT_OF_DECISION6);
	FwPrAddActionNode(prDesc, CrPsCmd3s1Start_N5, &CrPsCmd3s1StartN5);
	FwPrAddActionNode(prDesc, CrPsCmd3s1Start_N6, &CrPsCmd3s1StartN6);
	FwPrAddActionNode(prDesc, CrPsCmd3s1Start_N7, &CrPsCmd3s1StartN7);
	FwPrAddActionNode(prDesc, CrPsCmd3s1Start_N8, &CrPsCmd3s1StartN8);
	FwPrAddActionNode(prDesc, CrPsCmd3s1Start_N9, &CrPsCmd3s1StartN9);
	FwPrAddActionNode(prDesc, CrPsCmd3s1Start_N10, &CrPsCmd3s1StartN10);
	FwPrAddActionNode(prDesc, CrPsCmd3s1Start_N11, &CrPsCmd3s1StartN11);
	FwPrAddFlowIniToDec(prDesc, DECISION1, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsCmd3s1Start_N1, &CrPsCmd3s1StartG1);
	FwPrAddFlowDecToDec(prDesc, DECISION1, DECISION2, &CrPsCmd3s1StartG1E);
	FwPrAddFlowActToFin(prDesc, CrPsCmd3s1Start_N1, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmd3s1Start_N8, &CrPsCmd3s1StartG2);
	FwPrAddFlowDecToDec(prDesc, DECISION2, DECISION3, &CrPsCmd3s1StartG2E);
	FwPrAddFlowDecToAct(prDesc, DECISION3, CrPsCmd3s1Start_N7, &CrPsCmd3s1StartG3);
	FwPrAddFlowDecToDec(prDesc, DECISION3, DECISION4, &CrPsCmd3s1StartG3E);
	FwPrAddFlowActToDec(prDesc, CrPsCmd3s1Start_N4, DECISION6, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION4, CrPsCmd3s1Start_N9, &CrPsCmd3s1StartG4);
	FwPrAddFlowDecToAct(prDesc, DECISION4, CrPsCmd3s1Start_N2, &CrPsCmd3s1StartG4E);
	FwPrAddFlowActToDec(prDesc, CrPsCmd3s1Start_N2, DECISION5, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION5, CrPsCmd3s1Start_N3, &CrPsCmd3s1StartG5);
	FwPrAddFlowDecToAct(prDesc, DECISION5, CrPsCmd3s1Start_N4, &CrPsCmd3s1StartG5E);
	FwPrAddFlowActToAct(prDesc, CrPsCmd3s1Start_N3, CrPsCmd3s1Start_N10, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION6, CrPsCmd3s1Start_N5, &CrPsCmd3s1StartG6);
	FwPrAddFlowDecToAct(prDesc, DECISION6, CrPsCmd3s1Start_N11, &CrPsCmd3s1StartG6E);
	FwPrAddFlowActToAct(prDesc, CrPsCmd3s1Start_N5, CrPsCmd3s1Start_N6, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsCmd3s1Start_N6, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsCmd3s1Start_N7, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsCmd3s1Start_N8, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsCmd3s1Start_N9, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsCmd3s1Start_N10, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsCmd3s1Start_N11, NULL);

	return prDesc;
}
