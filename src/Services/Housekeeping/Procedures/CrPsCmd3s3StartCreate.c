/**
 * @file CrPsCmd3s3StartCreate.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:15:26
 */

#include "CrPsCmd3s3StartCreate.h"

/** CR Framework function definitions*/
#include "CrFwConstants.h"

/** FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"

/** CrPsCmd3s3Start function definitions */
#include <stdlib.h>
#include "CrPsDebug.h"

/** Guard on the Control Flow from DECISION1 to DECISION2. */
FwPrBool_t CrPsCmd3s3StartG1E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/** Guard on the Control Flow from DECISION2 to DECISION3. */
FwPrBool_t CrPsCmd3s3StartG2E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/** Guard on the Control Flow from DECISION3 to N4. */
FwPrBool_t CrPsCmd3s3StartG3E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/** Guard on the Control Flow from DECISION4 to N7. */
FwPrBool_t CrPsCmd3s3StartG4E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsCmd3s3StartCreate(void* prData)
{
	const FwPrCounterU2_t DECISION1 = 1;		/* The identifier of decision node DECISION1 in procedure CrPsCmd3s3Start */
	const FwPrCounterU2_t N_OUT_OF_DECISION1 = 2;	/* The number of control flows out of decision node DECISION1 in procedure CrPsCmd3s3Start */
	const FwPrCounterU2_t DECISION2 = 2;		/* The identifier of decision node DECISION2 in procedure CrPsCmd3s3Start */
	const FwPrCounterU2_t N_OUT_OF_DECISION2 = 2;	/* The number of control flows out of decision node DECISION2 in procedure CrPsCmd3s3Start */
	const FwPrCounterU2_t DECISION3 = 3;		/* The identifier of decision node DECISION3 in procedure CrPsCmd3s3Start */
	const FwPrCounterU2_t N_OUT_OF_DECISION3 = 2;	/* The number of control flows out of decision node DECISION3 in procedure CrPsCmd3s3Start */
	const FwPrCounterU2_t DECISION4 = 4;		/* The identifier of decision node DECISION4 in procedure CrPsCmd3s3Start */
	const FwPrCounterU2_t N_OUT_OF_DECISION4 = 2;	/* The number of control flows out of decision node DECISION4 in procedure CrPsCmd3s3Start */

	/** Create the procedure */
	FwPrDesc_t prDesc = FwPrCreate(
		8,	/* N_ANODES - The number of action nodes */
		4,	/* N_DNODES - The number of decision nodes */
		17,	/* N_FLOWS - The number of control flows */
		8,	/* N_ACTIONS - The number of actions */
		8	/* N_GUARDS - The number of guards */
	);

	/** Configure the procedure */
	FwPrSetData(prDesc, prData);
	FwPrAddActionNode(prDesc, CrPsCmd3s3Start_N4, &CrPsCmd3s3StartN4);
	FwPrAddActionNode(prDesc, CrPsCmd3s3Start_N1, &CrPsCmd3s3StartN1);
	FwPrAddDecisionNode(prDesc, DECISION1, N_OUT_OF_DECISION1);
	FwPrAddActionNode(prDesc, CrPsCmd3s3Start_N2, &CrPsCmd3s3StartN2);
	FwPrAddActionNode(prDesc, CrPsCmd3s3Start_N3, &CrPsCmd3s3StartN3);
	FwPrAddDecisionNode(prDesc, DECISION2, N_OUT_OF_DECISION2);
	FwPrAddActionNode(prDesc, CrPsCmd3s3Start_N5, &CrPsCmd3s3StartN5);
	FwPrAddActionNode(prDesc, CrPsCmd3s3Start_N6, &CrPsCmd3s3StartN6);
	FwPrAddDecisionNode(prDesc, DECISION3, N_OUT_OF_DECISION3);
	FwPrAddDecisionNode(prDesc, DECISION4, N_OUT_OF_DECISION4);
	FwPrAddActionNode(prDesc, CrPsCmd3s3Start_N7, &CrPsCmd3s3StartN7);
	FwPrAddActionNode(prDesc, CrPsCmd3s3Start_N8, &CrPsCmd3s3StartN8);
	FwPrAddFlowIniToAct(prDesc, CrPsCmd3s3Start_N1, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmd3s3Start_N4, DECISION1, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmd3s3Start_N1, DECISION1, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsCmd3s3Start_N2, &CrPsCmd3s3StartG1);
	FwPrAddFlowDecToDec(prDesc, DECISION1, DECISION2, &CrPsCmd3s3StartG1E);
	FwPrAddFlowActToAct(prDesc, CrPsCmd3s3Start_N2, CrPsCmd3s3Start_N3, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmd3s3Start_N3, DECISION2, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmd3s3Start_N5, &CrPsCmd3s3StartG2);
	FwPrAddFlowDecToDec(prDesc, DECISION2, DECISION3, &CrPsCmd3s3StartG2E);
	FwPrAddFlowActToAct(prDesc, CrPsCmd3s3Start_N5, CrPsCmd3s3Start_N6, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmd3s3Start_N6, DECISION3, NULL);
	FwPrAddFlowDecToDec(prDesc, DECISION3, DECISION4, &CrPsCmd3s3StartG3);
	FwPrAddFlowDecToAct(prDesc, DECISION3, CrPsCmd3s3Start_N4, &CrPsCmd3s3StartG3E);
	FwPrAddFlowDecToAct(prDesc, DECISION4, CrPsCmd3s3Start_N8, &CrPsCmd3s3StartG4);
	FwPrAddFlowDecToAct(prDesc, DECISION4, CrPsCmd3s3Start_N7, &CrPsCmd3s3StartG4E);
	FwPrAddFlowActToFin(prDesc, CrPsCmd3s3Start_N7, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsCmd3s3Start_N8, NULL);

	return prDesc;
}
