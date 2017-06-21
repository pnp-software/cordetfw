/**
 * @file CrPsCmd17s3PrgrCreate.c
 * @ingroup CrIaDemo
 *
 * ???
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsCmd17s3PrgrCreate.h"

/** FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"

/** CrPsCmd17s3Prgr function definitions */
#include <stdlib.h>

/* ------------------------------------------------------------------------------------ */
FwPrDesc_t CrPsCmd17s3PrgrCreate(void* prData)
{
  const FwPrCounterU2_t DECISION1 = 1;		/* The identifier of decision node DECISION1 in procedure CrPsCmd17s3Prgr */
  const FwPrCounterU2_t N_OUT_OF_DECISION1 = 3;	/* The number of control flows out of decision node DECISION1 in procedure CrPsCmd17s3Prgr */

  /** Create the procedure */
  FwPrDesc_t prDesc = FwPrCreate(
                        4,	/* N_ANODES - The number of action nodes */
                        1,	/* N_DNODES - The number of decision nodes */
                        8,	/* N_FLOWS - The number of control flows */
                        4,	/* N_ACTIONS - The number of actions */
                        3	/* N_GUARDS - The number of guards */
                      );

  /** Configure the procedure */
  FwPrSetData(prDesc, prData);
  FwPrAddDecisionNode(prDesc, DECISION1, N_OUT_OF_DECISION1);
  FwPrAddActionNode(prDesc, CrPsCmd17s3Prgr_N1, &CrPsTestOnBoardConnectionPrgrN1);
  FwPrAddActionNode(prDesc, CrPsCmd17s3Prgr_N2, &CrPsTestOnBoardConnectionPrgrN2);
  FwPrAddActionNode(prDesc, CrPsCmd17s3Prgr_N3, &CrPsTestOnBoardConnectionPrgrN3);
  FwPrAddActionNode(prDesc, CrPsCmd17s3Prgr_N4, &CrPsTestOnBoardConnectionPrgrN4);
  FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsCmd17s3Prgr_N1, &CrPsTestOnBoardConnectionPrgrG11);
  FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsCmd17s3Prgr_N2, &CrPsTestOnBoardConnectionPrgrG12);
  FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsCmd17s3Prgr_N3, &CrPsTestOnBoardConnectionPrgrG13);
  FwPrAddFlowActToFin(prDesc, CrPsCmd17s3Prgr_N1, NULL);
  FwPrAddFlowActToFin(prDesc, CrPsCmd17s3Prgr_N2, NULL);
  FwPrAddFlowActToAct(prDesc, CrPsCmd17s3Prgr_N3, CrPsCmd17s3Prgr_N4, NULL);
  FwPrAddFlowIniToDec(prDesc, DECISION1, NULL);
  FwPrAddFlowActToFin(prDesc, CrPsCmd17s3Prgr_N4, NULL);

  return prDesc;
}
