/**
 * @file CrPsCmdVerSuccCreate.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 18:2:22
 */

#include "CrPsCmdVerSuccCreate.h"

/** FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"

/** CrPsCmdVerSucc function definitions */
#include <stdlib.h>

/* ----------------------------------------------------------------------------------------------------------------- */
/** Guard on the Control Flow from DECISION2 to N4. */
FwPrBool_t CrPsCmdVerSuccG1E(FwPrDesc_t __attribute__((unused)) prDesc)
{
  /* [ Else ] */

  return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsCmdVerSuccCreate(void* prData)
{
	const FwPrCounterU2_t DECISION2 = 1;		/* The identifier of decision node DECISION2 in procedure CrPsCmdVerSucc */
	const FwPrCounterU2_t N_OUT_OF_DECISION2 = 2;	/* The number of control flows out of decision node DECISION2 in procedure CrPsCmdVerSucc */

	/** Create the procedure */
	FwPrDesc_t prDesc = FwPrCreate(
		3,	/* N_ANODES - The number of action nodes */
		1,	/* N_DNODES - The number of decision nodes */
		6,	/* N_FLOWS - The number of control flows */
		3,	/* N_ACTIONS - The number of actions */
		2	/* N_GUARDS - The number of guards */
	);

	/** Configure the procedure */
	FwPrSetData(prDesc, prData);
	FwPrAddActionNode(prDesc, CrPsCmdVerSucc_N2, &CrPsCmdVerSuccN2);
	FwPrAddDecisionNode(prDesc, DECISION2, N_OUT_OF_DECISION2);
	FwPrAddActionNode(prDesc, CrPsCmdVerSucc_N3, &CrPsCmdVerSuccN3);
	FwPrAddActionNode(prDesc, CrPsCmdVerSucc_N4, &CrPsCmdVerSuccN4);
	FwPrAddFlowIniToAct(prDesc, CrPsCmdVerSucc_N2, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmdVerSucc_N2, DECISION2, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmdVerSucc_N3, &CrPsCmdVerSuccG1);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmdVerSucc_N4, &CrPsCmdVerSuccG1E);
	FwPrAddFlowActToFin(prDesc, CrPsCmdVerSucc_N3, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsCmdVerSucc_N4, NULL);

	return prDesc;
}
