/**
 * @file CrPsPcktReroutingFailCreate.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 18:26:2
 */

#include "CrPsPcktReroutingFailCreate.h"

/** FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include <CrFwConstants.h>
/** CrPsPcktReroutingFail function definitions */
#include <stdlib.h>
#include "CrPsDebug.h"

/* ----------------------------------------------------------------------------------------------------------------- */
/** Guard on the Control Flow from DECISION2 to N4. */
FwPrBool_t CrPsPcktReroutingFailG2E(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  /* [ Else ] */
  return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsPcktReroutingFailCreate(void* prData)
{
	const FwPrCounterU2_t DECISION1 = 1;		/* The identifier of decision node DECISION1 in procedure CrPsPcktReroutingFail */
	const FwPrCounterU2_t N_OUT_OF_DECISION1 = 2;	/* The number of control flows out of decision node DECISION1 in procedure CrPsPcktReroutingFail */
	const FwPrCounterU2_t DECISION2 = 2;		/* The identifier of decision node DECISION2 in procedure CrPsPcktReroutingFail */
	const FwPrCounterU2_t N_OUT_OF_DECISION2 = 2;	/* The number of control flows out of decision node DECISION2 in procedure CrPsPcktReroutingFail */

	/** Create the procedure */
	FwPrDesc_t prDesc = FwPrCreate(
		6,	/* N_ANODES - The number of action nodes */
		2,	/* N_DNODES - The number of decision nodes */
		11,	/* N_FLOWS - The number of control flows */
		6,	/* N_ACTIONS - The number of actions */
		4	/* N_GUARDS - The number of guards */
	);

	/** Configure the procedure */
	FwPrSetData(prDesc, prData);
	FwPrAddActionNode(prDesc, CrPsPcktReroutingFail_N1, &CrPsPcktReroutingFailN1);
	FwPrAddDecisionNode(prDesc, DECISION1, N_OUT_OF_DECISION1);
	FwPrAddActionNode(prDesc, CrPsPcktReroutingFail_N2, &CrPsPcktReroutingFailN2);
	FwPrAddDecisionNode(prDesc, DECISION2, N_OUT_OF_DECISION2);
	FwPrAddActionNode(prDesc, CrPsPcktReroutingFail_N3, &CrPsPcktReroutingFailN3);
	FwPrAddActionNode(prDesc, CrPsPcktReroutingFail_N4, &CrPsPcktReroutingFailN4);
	FwPrAddActionNode(prDesc, CrPsPcktReroutingFail_N5, &CrPsPcktReroutingFailN5);
	FwPrAddActionNode(prDesc, CrPsPcktReroutingFail_N6, &CrPsPcktReroutingFailN6);
	FwPrAddFlowIniToDec(prDesc, DECISION1, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsPcktReroutingFail_N1, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsPcktReroutingFail_N1, &CrPsPcktReroutingFailG1);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsPcktReroutingFail_N2, &CrPsPcktReroutingFailG1E);
	FwPrAddFlowActToDec(prDesc, CrPsPcktReroutingFail_N2, DECISION2, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsPcktReroutingFail_N3, &CrPsPcktReroutingFailG2);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsPcktReroutingFail_N4, &CrPsPcktReroutingFailG2E);
	FwPrAddFlowActToFin(prDesc, CrPsPcktReroutingFail_N3, NULL);
	FwPrAddFlowActToAct(prDesc, CrPsPcktReroutingFail_N4, CrPsPcktReroutingFail_N5, NULL);
	FwPrAddFlowActToAct(prDesc, CrPsPcktReroutingFail_N5, CrPsPcktReroutingFail_N6, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsPcktReroutingFail_N6, NULL);

	return prDesc;
}
