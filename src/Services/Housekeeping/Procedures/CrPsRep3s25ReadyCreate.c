/**
 * @file CrPsRep3s25ReadyCreate.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Oct 3 2017 22:4:57
 */
#include "CrFwConstants.h"

#include "CrPsRep3s25ReadyCreate.h"

/** FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"

/** CrPsRep3s25Ready function definitions */
#include <stdlib.h>

/** Guard on the Control Flow from DECISION1 to N2. */
FwPrBool_t CrPsRep3s25ReadyG1E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsRep3s25ReadyCreate(void* prData)
{
	const FwPrCounterU2_t DECISION1 = 1;		/* The identifier of decision node DECISION1 in procedure CrPsRep3s25Ready */
	const FwPrCounterU2_t N_OUT_OF_DECISION1 = 2;	/* The number of control flows out of decision node DECISION1 in procedure CrPsRep3s25Ready */
	const FwPrCounterU2_t DECISION2 = 2;		/* The identifier of decision node DECISION2 in procedure CrPsRep3s25Ready */
	const FwPrCounterU2_t N_OUT_OF_DECISION2 = 3;	/* The number of control flows out of decision node DECISION2 in procedure CrPsRep3s25Ready */

	/** Create the procedure */
	FwPrDesc_t prDesc = FwPrCreate(
		4,	/* N_ANODES - The number of action nodes */
		2,	/* N_DNODES - The number of decision nodes */
		10,	/* N_FLOWS - The number of control flows */
		4,	/* N_ACTIONS - The number of actions */
		6	/* N_GUARDS - The number of guards */
	);

	/** Configure the procedure */
	FwPrSetData(prDesc, prData);
	FwPrAddActionNode(prDesc, CrPsRep3s25Ready_N1, &CrPsRep3s25ReadyN1);
	FwPrAddDecisionNode(prDesc, DECISION1, N_OUT_OF_DECISION1);
	FwPrAddActionNode(prDesc, CrPsRep3s25Ready_N2, &CrPsRep3s25ReadyN2);
	FwPrAddActionNode(prDesc, CrPsRep3s25Ready_N3, &CrPsRep3s25ReadyN3);
	FwPrAddActionNode(prDesc, CrPsRep3s25Ready_N4, &CrPsRep3s25ReadyN4);
	FwPrAddDecisionNode(prDesc, DECISION2, N_OUT_OF_DECISION2);
	FwPrAddFlowActToDec(prDesc, CrPsRep3s25Ready_N1, DECISION1, NULL);
	FwPrAddFlowIniToAct(prDesc, CrPsRep3s25Ready_N1, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsRep3s25Ready_N3, &CrPsRep3s25ReadyG1);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsRep3s25Ready_N2, &CrPsRep3s25ReadyG1E);
	FwPrAddFlowActToAct(prDesc, CrPsRep3s25Ready_N2, CrPsRep3s25Ready_N4, NULL);
	FwPrAddFlowActToAct(prDesc, CrPsRep3s25Ready_N3, CrPsRep3s25Ready_N4, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsRep3s25Ready_N4, DECISION2, &CrPsRep3s25ReadyG2);
	FwPrAddFlowDecToDec(prDesc, DECISION2, DECISION1, &CrIaReadyChk3s25ReadyGoToDec);
	FwPrAddFlowDecToFin(prDesc, DECISION2, &CrPsRep3s25ReadyGoToFin);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsRep3s25Ready_N1, &CrIaReadyChk3s25ReadyGoToRst);

	return prDesc;
}