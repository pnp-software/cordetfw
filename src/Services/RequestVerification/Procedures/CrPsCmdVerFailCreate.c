/**
 * @file CrPsCmdVerFailCreate.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 18:1:13
 */

#include "CrPsCmdVerFailCreate.h"

/** FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"

/** CrPsCmdVerFail function definitions */
#include <stdlib.h>

/* ----------------------------------------------------------------------------------------------------------------- */
/** Guard on the Control Flow from DECISION2 to N4. */
FwPrBool_t CrPsCmdVerFailG1E(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* [ Else ] */

  return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsCmdVerFailCreate(void* prData)
{
	const FwPrCounterU2_t DECISION2 = 1;		/* The identifier of decision node DECISION2 in procedure CrPsCmdVerFail */
	const FwPrCounterU2_t N_OUT_OF_DECISION2 = 2;	/* The number of control flows out of decision node DECISION2 in procedure CrPsCmdVerFail */

	/** Create the procedure */
	FwPrDesc_t prDesc = FwPrCreate(
		5,	/* N_ANODES - The number of action nodes */
		1,	/* N_DNODES - The number of decision nodes */
		8,	/* N_FLOWS - The number of control flows */
		5,	/* N_ACTIONS - The number of actions */
		2	/* N_GUARDS - The number of guards */
	);

	/** Configure the procedure */
	FwPrSetData(prDesc, prData);
	FwPrAddActionNode(prDesc, CrPsCmdVerFail_N2, &CrPsCmdVerFailN2);
	FwPrAddDecisionNode(prDesc, DECISION2, N_OUT_OF_DECISION2);
	FwPrAddActionNode(prDesc, CrPsCmdVerFail_N3, &CrPsCmdVerFailN3);
	FwPrAddActionNode(prDesc, CrPsCmdVerFail_N4, &CrPsCmdVerFailN4);
	FwPrAddActionNode(prDesc, CrPsCmdVerFail_N5, &CrPsCmdVerFailN5);
	FwPrAddActionNode(prDesc, CrPsCmdVerFail_N6, &CrPsCmdVerFailN6);
	FwPrAddFlowIniToAct(prDesc, CrPsCmdVerFail_N2, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmdVerFail_N2, DECISION2, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmdVerFail_N3, &CrPsCmdVerFailG1);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmdVerFail_N4, &CrPsCmdVerFailG1E);
	FwPrAddFlowActToFin(prDesc, CrPsCmdVerFail_N3, NULL);
	FwPrAddFlowActToAct(prDesc, CrPsCmdVerFail_N4, CrPsCmdVerFail_N5, NULL);
	FwPrAddFlowActToAct(prDesc, CrPsCmdVerFail_N5, CrPsCmdVerFail_N6, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsCmdVerFail_N6, NULL);

	return prDesc;
}
