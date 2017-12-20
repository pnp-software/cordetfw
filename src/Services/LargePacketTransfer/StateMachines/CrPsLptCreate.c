/**
 * @file CrPsLptCreate.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Nov 26 2017 12:16:43
 */

/** CrPsLpt function definitions */
#include "CrPsLptCreate.h"

/** FW Profile function definitions */
#include "FwSmDCreate.h"
#include "FwSmConfig.h"

#include <stdlib.h>

/* ----------------------------------------------------------------------------------------------------------------- */
FwSmDesc_t CrPsLptCreate(void* smData)
{
	const FwSmCounterU2_t N_OUT_OF_INACTIVE = 2;	/* The number of transitions out of state INACTIVE */
	const FwSmCounterU2_t N_OUT_OF_DOWN_TRANSFER = 2;	/* The number of transitions out of state DOWN_TRANSFER */
	const FwSmCounterU2_t N_OUT_OF_UP_TRANSFER = 2;	/* The number of transitions out of state UP_TRANSFER */

	/** Create state machine smDesc */
	FwSmDesc_t smDesc = FwSmCreate(
		3,	/* NSTATES - The number of states */
		0,	/* NCPS - The number of choice pseudo-states */
		7,	/* NTRANS - The number of transitions */
		9,	/* NACTIONS - The number of state and transition actions */
		2	/* NGUARDS - The number of transition guards */
	);

	/** Configure the state machine smDesc */
	FwSmSetData(smDesc, smData);
	FwSmAddState(smDesc, CrPsLpt_INACTIVE, N_OUT_OF_INACTIVE, NULL, NULL, NULL, NULL);
	FwSmAddState(smDesc, CrPsLpt_DOWN_TRANSFER, N_OUT_OF_DOWN_TRANSFER, &CrPsLptDownTransferEntryAction, &CrPsLptDownTransferExitAction, &CrPsLptDownTransferDoAction, NULL);
	FwSmAddState(smDesc, CrPsLpt_UP_TRANSFER, N_OUT_OF_UP_TRANSFER, &CrPsLptUpTransferEntryAction, &CrPsLptUpTransferExitAction, &CrPsLptUpTransferDoAction, NULL);
	FwSmAddTransStaToSta(smDesc, StartUpTransfer, CrPsLpt_INACTIVE, CrPsLpt_UP_TRANSFER, NULL, NULL);
	FwSmAddTransStaToSta(smDesc, StartDownTransfer, CrPsLpt_INACTIVE, CrPsLpt_DOWN_TRANSFER, NULL, NULL);
	FwSmAddTransStaToSta(smDesc, Abort, CrPsLpt_DOWN_TRANSFER, CrPsLpt_INACTIVE, &CrPsLptGenerateAbortEvent, NULL);
	FwSmAddTransStaToSta(smDesc, Execute, CrPsLpt_DOWN_TRANSFER, CrPsLpt_INACTIVE, NULL, &CrPsLptIsTransferFinished);
	FwSmAddTransStaToSta(smDesc, Execute, CrPsLpt_UP_TRANSFER, CrPsLpt_INACTIVE, &CrPsLptLoadReport, &CrPsLptIsFailed);
	FwSmAddTransStaToSta(smDesc, EndUpTransfer, CrPsLpt_UP_TRANSFER, CrPsLpt_INACTIVE, NULL, NULL);
	FwSmAddTransIpsToSta(smDesc, CrPsLpt_INACTIVE, &CrPsLptInitialization);

	return smDesc;
}
