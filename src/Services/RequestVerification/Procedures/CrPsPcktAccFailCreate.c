/**
 * @file CrPsPcktAccFailCreate.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 18:24:51
 */

#include "CrPsPcktAccFailCreate.h"

/** FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include <CrFwConstants.h>

/** CrPsPcktAccFail function definitions */
#include <stdlib.h>

/* ----------------------------------------------------------------------------------------------------------------- */
/** Guard on the Control Flow from DECISION2 to N4. */
FwPrBool_t CrPsPcktAccFailG2E(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  /* [ Else ] */

  return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsPcktAccFailCreate(void* prData)
{
	const FwPrCounterU2_t DECISION1 = 1;		/* The identifier of decision node DECISION1 in procedure CrPsPcktAccFail */
	const FwPrCounterU2_t N_OUT_OF_DECISION1 = 2;	/* The number of control flows out of decision node DECISION1 in procedure CrPsPcktAccFail */
	const FwPrCounterU2_t DECISION2 = 2;		/* The identifier of decision node DECISION2 in procedure CrPsPcktAccFail */
	const FwPrCounterU2_t N_OUT_OF_DECISION2 = 2;	/* The number of control flows out of decision node DECISION2 in procedure CrPsPcktAccFail */

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
	FwPrAddActionNode(prDesc, CrPsPcktAccFail_N1, &CrPsPcktAccFailN1);
	FwPrAddDecisionNode(prDesc, DECISION1, N_OUT_OF_DECISION1);
	FwPrAddActionNode(prDesc, CrPsPcktAccFail_N2, &CrPsPcktAccFailN2);
	FwPrAddDecisionNode(prDesc, DECISION2, N_OUT_OF_DECISION2);
	FwPrAddActionNode(prDesc, CrPsPcktAccFail_N3, &CrPsPcktAccFailN3);
	FwPrAddActionNode(prDesc, CrPsPcktAccFail_N4, &CrPsPcktAccFailN4);
	FwPrAddActionNode(prDesc, CrPsPcktAccFail_N5, &CrPsPcktAccFailN5);
	FwPrAddActionNode(prDesc, CrPsPcktAccFail_N6, &CrPsPcktAccFailN6);
	FwPrAddFlowIniToDec(prDesc, DECISION1, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsPcktAccFail_N1, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsPcktAccFail_N1, &CrPsPcktAccFailG1);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsPcktAccFail_N2, &CrPsPcktAccFailG1E);
	FwPrAddFlowActToDec(prDesc, CrPsPcktAccFail_N2, DECISION2, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsPcktAccFail_N3, &CrPsPcktAccFailG2);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsPcktAccFail_N4, &CrPsPcktAccFailG2E);
	FwPrAddFlowActToFin(prDesc, CrPsPcktAccFail_N3, NULL);
	FwPrAddFlowActToAct(prDesc, CrPsPcktAccFail_N4, CrPsPcktAccFail_N5, NULL);
	FwPrAddFlowActToAct(prDesc, CrPsPcktAccFail_N5, CrPsPcktAccFail_N6, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsPcktAccFail_N6, NULL);

	return prDesc;
}
