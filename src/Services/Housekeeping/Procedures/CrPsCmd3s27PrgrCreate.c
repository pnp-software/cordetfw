/**
 * @file CrPsCmd3s27PrgrCreate.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:17:0
 */

#include "CrPsCmd3s27PrgrCreate.h"

/** CR Framework function definitions*/
#include "CrFwConstants.h"

/** FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"

/** CrPsCmd3s27Prgr function definitions */
#include <stdlib.h>
#include "CrPsDebug.h"

/** Guard on the Control Flow from DECISION1 to N5. */
FwPrBool_t CrPsCmd3s27PrgrG1E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	DEBUGP_3("CrPsCmd3s27PrgrG1E.\n");
	return 1;
}

/** Guard on the Control Flow from DECISION2 to N7. */
FwPrBool_t CrPsCmd3s27PrgrG2E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	DEBUGP_3("CrPsCmd3s27PrgrG2E.\n");
	return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsCmd3s27PrgrCreate(void* prData)
{
	const FwPrCounterU2_t DECISION1 = 1;		/* The identifier of decision node DECISION1 in procedure CrPsCmd3s27Prgr */
	const FwPrCounterU2_t N_OUT_OF_DECISION1 = 2;	/* The number of control flows out of decision node DECISION1 in procedure CrPsCmd3s27Prgr */
	const FwPrCounterU2_t DECISION2 = 2;		/* The identifier of decision node DECISION2 in procedure CrPsCmd3s27Prgr */
	const FwPrCounterU2_t N_OUT_OF_DECISION2 = 2;	/* The number of control flows out of decision node DECISION2 in procedure CrPsCmd3s27Prgr */

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
	FwPrAddActionNode(prDesc, CrPsCmd3s27Prgr_N1, &CrPsCmd3s27PrgrN1);
	FwPrAddDecisionNode(prDesc, DECISION1, N_OUT_OF_DECISION1);
	FwPrAddActionNode(prDesc, CrPsCmd3s27Prgr_N2, &CrPsCmd3s27PrgrN2);
	FwPrAddActionNode(prDesc, CrPsCmd3s27Prgr_N3, &CrPsCmd3s27PrgrN3);
	FwPrAddActionNode(prDesc, CrPsCmd3s27Prgr_N4, &CrPsCmd3s27PrgrN4);
	FwPrAddActionNode(prDesc, CrPsCmd3s27Prgr_N5, &CrPsCmd3s27PrgrN5);
	FwPrAddDecisionNode(prDesc, DECISION2, N_OUT_OF_DECISION2);
	FwPrAddActionNode(prDesc, CrPsCmd3s27Prgr_N6, &CrPsCmd3s27PrgrN6);
	FwPrAddActionNode(prDesc, CrPsCmd3s27Prgr_N7, &CrPsCmd3s27PrgrN7);
	FwPrAddActionNode(prDesc, CrPsCmd3s27Prgr_N8, &CrPsCmd3s27PrgrN8);
	FwPrAddActionNode(prDesc, CrPsCmd3s27Prgr_N9, &CrPsCmd3s27PrgrN9);
	FwPrAddFlowIniToAct(prDesc, CrPsCmd3s27Prgr_N8, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmd3s27Prgr_N1, DECISION1, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsCmd3s27Prgr_N2, &CrPsCmd3s27PrgrG1);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsCmd3s27Prgr_N5, &CrPsCmd3s27PrgrG1E);
	FwPrAddFlowActToAct(prDesc, CrPsCmd3s27Prgr_N2, CrPsCmd3s27Prgr_N4, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmd3s27Prgr_N3, DECISION2, NULL);
	FwPrAddFlowActToAct(prDesc, CrPsCmd3s27Prgr_N4, CrPsCmd3s27Prgr_N3, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmd3s27Prgr_N5, DECISION2, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmd3s27Prgr_N6, &CrPsCmd3s27PrgrG2);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmd3s27Prgr_N7, &CrPsCmd3s27PrgrG2E);
	FwPrAddFlowActToFin(prDesc, CrPsCmd3s27Prgr_N6, NULL);
	FwPrAddFlowActToAct(prDesc, CrPsCmd3s27Prgr_N7, CrPsCmd3s27Prgr_N9, NULL); /* VORSICHT VORSICHT --- hier war ein 3. GUARD ?????????*/
	FwPrAddFlowActToAct(prDesc, CrPsCmd3s27Prgr_N8, CrPsCmd3s27Prgr_N1, NULL);
	FwPrAddFlowActToAct(prDesc, CrPsCmd3s27Prgr_N9, CrPsCmd3s27Prgr_N1, NULL);

	return prDesc;
}