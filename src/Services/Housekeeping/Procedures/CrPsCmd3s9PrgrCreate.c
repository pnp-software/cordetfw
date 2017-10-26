/**
 * @file CrPsCmd3s9PrgrCreate.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:16:17
 */

#include "CrPsCmd3s9PrgrCreate.h"

/** CR Framework function definitions*/
#include "CrFwConstants.h"

/** FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"

/** CrPsCmd3s9Prgr function definitions */
#include <stdlib.h>
#include "CrPsDebug.h"

/** Guard on the Control Flow from DECISION1 to N5. */
FwPrBool_t CrPsCmd3s9PrgrG1E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/** Guard on the Control Flow from DECISION2 to N7. */
FwPrBool_t CrPsCmd3s9PrgrG2E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsCmd3s9PrgrCreate(void* prData)
{
	const FwPrCounterU2_t DECISION1 = 1;		/* The identifier of decision node DECISION1 in procedure CrPsCmd3s9Prgr */
	const FwPrCounterU2_t N_OUT_OF_DECISION1 = 2;	/* The number of control flows out of decision node DECISION1 in procedure CrPsCmd3s9Prgr */
	const FwPrCounterU2_t DECISION2 = 2;		/* The identifier of decision node DECISION2 in procedure CrPsCmd3s9Prgr */
	const FwPrCounterU2_t N_OUT_OF_DECISION2 = 2;	/* The number of control flows out of decision node DECISION2 in procedure CrPsCmd3s9Prgr */

	/** Create the procedure */
	FwPrDesc_t prDesc = FwPrCreate(
		9,	/* N_ANODES - The number of action nodes */
		2,	/* N_DNODES - The number of decision nodes */
		14,	/* N_FLOWS - The number of control flows */
		9,	/* N_ACTIONS - The number of actions */
		5	/* N_GUARDS - The number of guards */
	);

	/** Configure the procedure */
	FwPrSetData(prDesc, prData);
	FwPrAddActionNode(prDesc, CrPsCmd3s9Prgr_N1, &CrPsCmd3s9PrgrN1);
	FwPrAddDecisionNode(prDesc, DECISION1, N_OUT_OF_DECISION1);
	FwPrAddActionNode(prDesc, CrPsCmd3s9Prgr_N2, &CrPsCmd3s9PrgrN2);
	FwPrAddActionNode(prDesc, CrPsCmd3s9Prgr_N3, &CrPsCmd3s9PrgrN3);
	FwPrAddActionNode(prDesc, CrPsCmd3s9Prgr_N4, &CrPsCmd3s9PrgrN4);
	FwPrAddActionNode(prDesc, CrPsCmd3s9Prgr_N5, &CrPsCmd3s9PrgrN5);
	FwPrAddDecisionNode(prDesc, DECISION2, N_OUT_OF_DECISION2);
	FwPrAddActionNode(prDesc, CrPsCmd3s9Prgr_N6, &CrPsCmd3s9PrgrN6);
	FwPrAddActionNode(prDesc, CrPsCmd3s9Prgr_N7, &CrPsCmd3s9PrgrN7);
	FwPrAddActionNode(prDesc, CrPsCmd3s9Prgr_N8, &CrPsCmd3s9PrgrN8);
	FwPrAddActionNode(prDesc, CrPsCmd3s9Prgr_N9, &CrPsCmd3s9PrgrN9);
	FwPrAddFlowIniToAct(prDesc, CrPsCmd3s9Prgr_N8, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmd3s9Prgr_N1, DECISION1, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsCmd3s9Prgr_N2, &CrPsCmd3s9PrgrG1);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsCmd3s9Prgr_N5, &CrPsCmd3s9PrgrG1E);
	FwPrAddFlowActToAct(prDesc, CrPsCmd3s9Prgr_N2, CrPsCmd3s9Prgr_N4, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmd3s9Prgr_N3, DECISION2, NULL);
	FwPrAddFlowActToAct(prDesc, CrPsCmd3s9Prgr_N4, CrPsCmd3s9Prgr_N3, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmd3s9Prgr_N5, DECISION2, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmd3s9Prgr_N6, &CrPsCmd3s9PrgrG2);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmd3s9Prgr_N7, &CrPsCmd3s9PrgrG2E);
	FwPrAddFlowActToFin(prDesc, CrPsCmd3s9Prgr_N6, NULL);
	FwPrAddFlowActToAct(prDesc, CrPsCmd3s9Prgr_N7, CrPsCmd3s9Prgr_N9, &CrPsCmd3s9PrgrG3);
	FwPrAddFlowActToAct(prDesc, CrPsCmd3s9Prgr_N8, CrPsCmd3s9Prgr_N1, NULL);
	FwPrAddFlowActToAct(prDesc, CrPsCmd3s9Prgr_N9, CrPsCmd3s9Prgr_N1, NULL);

	return prDesc;
}
