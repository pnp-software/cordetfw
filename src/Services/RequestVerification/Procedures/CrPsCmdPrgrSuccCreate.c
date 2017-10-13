/**
 * @file CrPsCmdPrgrSuccCreate.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 17:59:40
 */

#include "CrPsCmdPrgrSuccCreate.h"

/** FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include <CrFwConstants.h>
/** CrPsCmdPrgrSucc function definitions */
#include <stdlib.h>
#include "CrPsDebug.h"

/* ----------------------------------------------------------------------------------------------------------------- */
/** Guard on the Control Flow from DECISION2 to N4. */
FwPrBool_t CrPsCmdPrgrSuccG1E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
  /* [ Else ] */
  DEBUGP_1("CrPsCmdPrgrSuccG1E");
  return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsCmdPrgrSuccCreate(void* prData)
{
	const FwPrCounterU2_t DECISION2 = 1;		/* The identifier of decision node DECISION2 in procedure CrPsCmdPrgrSucc */
	const FwPrCounterU2_t N_OUT_OF_DECISION2 = 2;	/* The number of control flows out of decision node DECISION2 in procedure CrPsCmdPrgrSucc */

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
	FwPrAddActionNode(prDesc, CrPsCmdPrgrSucc_N2, &CrPsCmdPrgrSuccN2);
	FwPrAddDecisionNode(prDesc, DECISION2, N_OUT_OF_DECISION2);
	FwPrAddActionNode(prDesc, CrPsCmdPrgrSucc_N3, &CrPsCmdPrgrSuccN3);
	FwPrAddActionNode(prDesc, CrPsCmdPrgrSucc_N4, &CrPsCmdPrgrSuccN4);
	FwPrAddFlowIniToAct(prDesc, CrPsCmdPrgrSucc_N2, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmdPrgrSucc_N2, DECISION2, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmdPrgrSucc_N3, &CrPsCmdPrgrSuccG1);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmdPrgrSucc_N4, &CrPsCmdPrgrSuccG1E);
	FwPrAddFlowActToFin(prDesc, CrPsCmdPrgrSucc_N3, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsCmdPrgrSucc_N4, NULL);

	return prDesc;
}
