/**
 * @file CrPsCmd17s3StartCreate.c
 * @ingroup CrIaDemo
 *
 * ???
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsCmd17s3StartCreate.h"

/** FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"

/** CrPsCmd17s3Start function definitions */
#include <stdlib.h>
#include <stdio.h>
#include "CrPsDebug.h"

/* ------------------------------------------------------------------------------------ */
/**
 * Guard on the Control Flow from DECISION1 to N8.
 *  Else
 * @param smDesc the procedure descriptor
 * @return 1
 */
FwPrBool_t CrPsTestOnBoardConnectionStartG1E(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  return 1;
}
/* ------------------------------------------------------------------------------------ */
/**
 * Guard on the Control Flow from DECISION2 to N9.
 *  Else
 * @param smDesc the procedure descriptor
 * @return 1
 */
FwPrBool_t CrPsTestOnBoardConnectionStartG2E(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  return 1;
}
/* ------------------------------------------------------------------------------------ */
/**
 * Guard on the Control Flow from DECISION3 to N10.
 *  Else
 * @param smDesc the procedure descriptor
 * @return 1
 */
FwPrBool_t CrPsTestOnBoardConnectionStartG3E(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);
  
  return 1;
}

/* ------------------------------------------------------------------------------------ */
FwPrDesc_t CrPsCmd17s3StartCreate(void* prData)
{
  const FwPrCounterU2_t DECISION1 = 1;		/* The identifier of decision node DECISION1 in procedure CrPsCmd17s3Start */
  const FwPrCounterU2_t N_OUT_OF_DECISION1 = 2;	/* The number of control flows out of decision node DECISION1 in procedure CrPsCmd17s3Start */
  const FwPrCounterU2_t DECISION2 = 2;		/* The identifier of decision node DECISION2 in procedure CrPsCmd17s3Start */
  const FwPrCounterU2_t N_OUT_OF_DECISION2 = 2;	/* The number of control flows out of decision node DECISION2 in procedure CrPsCmd17s3Start */
  const FwPrCounterU2_t DECISION3 = 3;		/* The identifier of decision node DECISION3 in procedure CrPsCmd17s3Start */
  const FwPrCounterU2_t N_OUT_OF_DECISION3 = 2;	/* The number of control flows out of decision node DECISION3 in procedure CrPsCmd17s3Start */

  /** Create the procedure */
  FwPrDesc_t prDesc = FwPrCreate(
                        9,	/* N_ANODES - The number of action nodes */
                        3,	/* N_DNODES - The number of decision nodes */
                        16,	/* N_FLOWS - The number of control flows */
                        9,	/* N_ACTIONS - The number of actions */
                        6	/* N_GUARDS - The number of guards */
                      );

  /** Configure the procedure */
  FwPrSetData(prDesc, prData);
  FwPrAddActionNode(prDesc, CrPsCmd17s3Start_N1, &CrPsTestOnBoardConnectionStartN1);
  FwPrAddActionNode(prDesc, CrPsCmd17s3Start_N2, &CrPsTestOnBoardConnectionStartN2);
  FwPrAddDecisionNode(prDesc, DECISION1, N_OUT_OF_DECISION1);
  FwPrAddActionNode(prDesc, CrPsCmd17s3Start_N3, &CrPsTestOnBoardConnectionStartN3);
  FwPrAddActionNode(prDesc, CrPsCmd17s3Start_N5, &CrPsTestOnBoardConnectionStartN5);
  FwPrAddActionNode(prDesc, CrPsCmd17s3Start_N8, &CrPsTestOnBoardConnectionStartN8);
  FwPrAddActionNode(prDesc, CrPsCmd17s3Start_N7, &CrPsTestOnBoardConnectionStartN7);
  FwPrAddDecisionNode(prDesc, DECISION2, N_OUT_OF_DECISION2);
  FwPrAddActionNode(prDesc, CrPsCmd17s3Start_N4, &CrPsTestOnBoardConnectionStartN4);
  FwPrAddActionNode(prDesc, CrPsCmd17s3Start_N9, &CrPsTestOnBoardConnectionStartN9);
  FwPrAddDecisionNode(prDesc, DECISION3, N_OUT_OF_DECISION3);
  FwPrAddActionNode(prDesc, CrPsCmd17s3Start_N10, &CrPsTestOnBoardConnectionStartN10);
  FwPrAddFlowIniToDec(prDesc, DECISION2, NULL);
  FwPrAddFlowActToAct(prDesc, CrPsCmd17s3Start_N1, CrPsCmd17s3Start_N2, NULL);
  FwPrAddFlowActToDec(prDesc, CrPsCmd17s3Start_N2, DECISION1, NULL);
  FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsCmd17s3Start_N3, &CrPsTestOnBoardConnectionStartG2);
  FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsCmd17s3Start_N9, &CrPsTestOnBoardConnectionStartG2E);
  FwPrAddFlowActToAct(prDesc, CrPsCmd17s3Start_N3, CrPsCmd17s3Start_N8, NULL);
  FwPrAddFlowActToAct(prDesc, CrPsCmd17s3Start_N5, CrPsCmd17s3Start_N7, NULL);
  FwPrAddFlowActToFin(prDesc, CrPsCmd17s3Start_N8, NULL);
  FwPrAddFlowActToFin(prDesc, CrPsCmd17s3Start_N7, NULL);
  FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmd17s3Start_N1, &CrPsTestOnBoardConnectionStartG1);
  FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmd17s3Start_N8, &CrPsTestOnBoardConnectionStartG1E);
  FwPrAddFlowActToAct(prDesc, CrPsCmd17s3Start_N4, CrPsCmd17s3Start_N5, NULL);
  FwPrAddFlowActToDec(prDesc, CrPsCmd17s3Start_N9, DECISION3, NULL);
  FwPrAddFlowDecToAct(prDesc, DECISION3, CrPsCmd17s3Start_N4, &CrPsTestOnBoardConnectionStartG3);
  FwPrAddFlowDecToAct(prDesc, DECISION3, CrPsCmd17s3Start_N10, &CrPsTestOnBoardConnectionStartG3E);
  FwPrAddFlowActToAct(prDesc, CrPsCmd17s3Start_N10, CrPsCmd17s3Start_N3, NULL);

  return prDesc;
}
