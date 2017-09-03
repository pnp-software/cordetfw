/**
 * @file CrPsCmdPrgrFailCreate.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 17:58:12
 */

#include "CrPsCmdPrgrFailCreate.h"

/** FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include <CrFwConstants.h>
/** CrPsCmdPrgrFail function definitions */
#include <stdlib.h>

/* ----------------------------------------------------------------------------------------------------------------- */
/** Guard on the Control Flow from DECISION2 to N4. */
FwPrBool_t CrPsCmdPrgrFailG1E(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  /* [ Else ] */

  return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsCmdPrgrFailCreate(void* prData)
{
	const FwPrCounterU2_t DECISION2 = 1;		/* The identifier of decision node DECISION2 in procedure CrPsCmdPrgrFail */
	const FwPrCounterU2_t N_OUT_OF_DECISION2 = 2;	/* The number of control flows out of decision node DECISION2 in procedure CrPsCmdPrgrFail */

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
	FwPrAddActionNode(prDesc, CrPsCmdPrgrFail_N2, &CrPsCmdPrgrFailN2);
	FwPrAddDecisionNode(prDesc, DECISION2, N_OUT_OF_DECISION2);
	FwPrAddActionNode(prDesc, CrPsCmdPrgrFail_N3, &CrPsCmdPrgrFailN3);
	FwPrAddActionNode(prDesc, CrPsCmdPrgrFail_N4, &CrPsCmdPrgrFailN4);
	FwPrAddActionNode(prDesc, CrPsCmdPrgrFail_N5, &CrPsCmdPrgrFailN5);
	FwPrAddActionNode(prDesc, CrPsCmdPrgrFail_N6, &CrPsCmdPrgrFailN6);
	FwPrAddFlowIniToAct(prDesc, CrPsCmdPrgrFail_N2, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmdPrgrFail_N2, DECISION2, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmdPrgrFail_N3, &CrPsCmdPrgrFailG1);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmdPrgrFail_N4, &CrPsCmdPrgrFailG1E);
	FwPrAddFlowActToFin(prDesc, CrPsCmdPrgrFail_N3, NULL);
	FwPrAddFlowActToAct(prDesc, CrPsCmdPrgrFail_N4, CrPsCmdPrgrFail_N5, NULL);
	FwPrAddFlowActToAct(prDesc, CrPsCmdPrgrFail_N5, CrPsCmdPrgrFail_N6, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsCmdPrgrFail_N6, NULL);

	return prDesc;
}
