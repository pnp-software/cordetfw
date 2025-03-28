/**
 * @file
 *
 * Implementation of test cases for OutFactory component.
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#include <stdio.h>
#include <stdlib.h>
#include "CrFwOutFactoryTestCases.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include framework files */
#include "CrFwOutRegistryUserPar.h"
#include "OutRegistry/CrFwOutRegistry.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "OutFactory/CrFwOutFactory.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include configuration files */
#include "CrFwRepErrStub.h"
#include "CrFwOutFactoryUserPar.h"
#include "CrFwCmpData.h"

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutFactoryTestCase1() {
	FwSmDesc_t outFactory1, outFactory2;

	/* Instantiate the OutFactory */
	outFactory1 = CrFwOutFactoryMake();
	if (outFactory1 == NULL)
		return 0;

	/* Instantiate it again and check that same component is returned */
	outFactory2 = CrFwOutFactoryMake();
	if (outFactory1 != outFactory2)
		return 0;

	/* Check configuration of OutFactory */
	if (FwSmCheckRec(outFactory1) != smSuccess)
		return 0;

	/* Initialize and Configure OutFactory and check success */
	CrFwCmpInit(outFactory1);
	CrFwCmpReset(outFactory1);
	if (!CrFwCmpIsInConfigured(outFactory1))
		return 0;

	/* Check max number of OutComponents */
	if (CrFwOutFactoryGetMaxNOfOutCmp() != CR_FW_OUTFACTORY_MAX_NOF_OUTCMP)
		return 0;

	/* Check component type */
	if (CrFwCmpGetInstanceId(outFactory1) != 0)
		return 0;
	if (CrFwCmpGetTypeId(outFactory1) != CR_FW_OUTFACTORY_TYPE)
		return 0;

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutFactoryTestCase2() {
	FwSmDesc_t outFactory, outCmp;
	CrFwCounterU2_t i, errRepPosLocal;
	CrFwCounterU1_t* errRepPar;
	FwSmDesc_t outCmpArray[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];
	CrFwPckt_t pckt[100];  /* it is assumed that CR_FW_MAX_NOF_PCKTS is smaller than 100 */

	/* Instantiate the OutFactory */
	outFactory = CrFwOutFactoryMake();
	if (outFactory == NULL)
		return 0;

	/* Initialize and configure the OutFactory */
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Store the current value of the error report counter */
	errRepPosLocal = CrFwRepErrStubGetPos();

	/* attempt to retrieve an OutComponent with invalid but in-range type */
	outCmp = CrFwOutFactoryMakeOutCmp(3,2,1,0);
	if (outCmp != NULL)
		return 0;

	/* Check that an error report has been generated */
	if (CrFwRepErrStubGetPos() != errRepPosLocal+1)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crOutCmpIllKind)
		return 0;
	if (CrFwRepErrStubGetTypeId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != CR_FW_OUTFACTORY_TYPE)
		return 0;
	if (CrFwRepErrStubGetInstanceId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != 0)
		return 0;
	errRepPar = CrFwRepErrStubGetParArray(CrFwRepErrStubGetPos()-1);
	if (errRepPar[0] != 3)
		return 0;
	if (errRepPar[1] != 2)
		return 0;
	if (errRepPar[2] != 1)
		return 0;

	/* attempt to retrieve an OutComponent with out-of-range type */
	outCmp = CrFwOutFactoryMakeOutCmp(51,2,1,0);
	if (outCmp != NULL)
		return 0;
	if (CrFwRepErrStubGetPos() != errRepPosLocal+2)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crOutCmpIllKind)
		return 0;

	/* attempt to retrieve an OutComponent with invalid but in-range sub-type */
	outCmp = CrFwOutFactoryMakeOutCmp(1,3,1,0);
	if (outCmp != NULL)
		return 0;
	if (CrFwRepErrStubGetPos() != errRepPosLocal+3)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crOutCmpIllKind)
		return 0;

	/* attempt to retrieve an OutComponent with out-of-range sub-type */
	outCmp = CrFwOutFactoryMakeOutCmp(5,5,1,0);
	if (outCmp != NULL)
		return 0;
	if (CrFwRepErrStubGetPos() != errRepPosLocal+4)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crOutCmpIllKind)
		return 0;

	/* attempt to retrieve an OutComponent with invalid but in-range discriminant */
	outCmp = CrFwOutFactoryMakeOutCmp(5,2,15,0);
	if (outCmp != NULL)
		return 0;
	if (CrFwRepErrStubGetPos() != errRepPosLocal+5)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crOutCmpIllKind)
		return 0;

	/* attempt to retrieve an OutComponent with out-of-range sub-type */
	outCmp = CrFwOutFactoryMakeOutCmp(5,2,40,0);
	if (outCmp != NULL)
		return 0;
	if (CrFwRepErrStubGetPos() != errRepPosLocal+6)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crOutCmpIllKind)
		return 0;

	/* Create CR_FW_MAX_NOF_PCKTS packets and then attempt to create an OutComponent */
	for (i=0; i<CR_FW_MAX_NOF_PCKTS; i++) {
		pckt[i] = CrFwPcktMake(CrFwPcktGetMaxLength());
		if (i>99)
			return 0;
	}

	outCmp = CrFwOutFactoryMakeOutCmp(1,8,5,0);
	if (outCmp != NULL)
		return 0;
	if (CrFwRepErrStubGetPos() != errRepPosLocal+7)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crOutCmpAllocationFail)
		return 0;
	if (CrFwRepErrStubGetTypeId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != CR_FW_OUTFACTORY_TYPE)
		return 0;
	if (CrFwRepErrStubGetInstanceId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != 0)
		return 0;
	errRepPar = CrFwRepErrStubGetParArray(CrFwRepErrStubGetPos()-1);
	if (errRepPar[0] != 1)
		return 0;
	if (errRepPar[1] != 8)
		return 0;
	if (errRepPar[2] != 5)
		return 0;
	CrFwSetAppErrCode(crNoAppErr); 	/* Set as part of call to CrFwOutFactoryMakeOutCmp() */

	/* Release all packets */
	for (i=0; i<CR_FW_MAX_NOF_PCKTS; i++)
		CrFwPcktRelease(pckt[i]);

	/* Create CR_FW_OUTFACTORY_MAX_NOF_OUTCMP OutComponent and then attempt to create one more */
	for (i=0; i<CR_FW_OUTFACTORY_MAX_NOF_OUTCMP; i++) {
		outCmpArray[i] = CrFwOutFactoryMakeOutCmp(1,1,0,0);
		if (outCmpArray[i]==NULL)
			return 0;
	}

	outCmp = CrFwOutFactoryMakeOutCmp(5,1,2,0);
	if (outCmp != NULL)
		return 0;
	if (CrFwRepErrStubGetPos() != errRepPosLocal+8)
		return 0;
	if (CrFwRepErrStubGetErrCode((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != crOutFactNoRes)
		return 0;
	if (CrFwRepErrStubGetTypeId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != CR_FW_OUTFACTORY_TYPE)
		return 0;
	if (CrFwRepErrStubGetInstanceId((CrFwCounterU2_t)(CrFwRepErrStubGetPos()-1)) != 0)
		return 0;
	errRepPar = CrFwRepErrStubGetParArray(CrFwRepErrStubGetPos()-1);
	if (errRepPar[0] != 5)
		return 0;
	if (errRepPar[1] != 1)
		return 0;
	if (errRepPar[2] != 2)
		return 0;
	if (errRepPar[3] != 0)
		return 0;

	/* Release all OutComponents */
	for (i=0; i<CR_FW_OUTFACTORY_MAX_NOF_OUTCMP; i++)
		CrFwOutFactoryReleaseOutCmp(outCmpArray[i]);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutFactoryTestCase3() {
	FwSmDesc_t outFactory;
	FwSmDesc_t outCmp1, outCmp2, outCmp3;
	CrFwInstanceId_t id;

	/* Instantiate the OutFactory */
	outFactory = CrFwOutFactoryMake();
	if (outFactory == NULL)
		return 0;

	/* Initialize and Reset the OutFactory */
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Allocate three OutComponents */
	outCmp1 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	id = CrFwCmpGetInstanceId(outCmp1);
	outCmp2 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	outCmp3 = CrFwOutFactoryMakeOutCmp(5,4,20,0);	/* Triplet (5,4,0) is defined  but not (5,4,20) */
	if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 3)
		return 0;

	/* Check the source attributes of the OutComponents */
	if (CrFwOutCmpGetSrc(outCmp1) != CR_FW_HOST_APP_ID)
		return 0;
	if (CrFwOutCmpGetSrc(outCmp2) != CR_FW_HOST_APP_ID)
		return 0;
	if (CrFwOutCmpGetSrc(outCmp3) != CR_FW_HOST_APP_ID)
		return 0;

	/* Reset the OutFactory and check that no OutComponents are allocated */
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;
	if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
		return 0;

	/* Allocate three OutComponents */
	outCmp1 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	outCmp2 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	outCmp3 = CrFwOutFactoryMakeOutCmp(5,1,2,0);
	if (CrFwCmpGetInstanceId(outCmp1) != id)
		return 0;
	if (CrFwCmpGetInstanceId(outCmp2) != id+1)
		return 0;
	if (CrFwCmpGetInstanceId(outCmp3) != id+2)
		return 0;
	if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 3)
		return 0;

	/* Shutdown the OutFactory and check that no OutComponents are allocated */
	CrFwCmpShutdown(outFactory);
	if (CrFwCmpIsStarted(outFactory) != 0)
		return 0;
	if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
		return 0;

	/* Restart OutFactory */
	FwSmStart(outFactory);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrFwOutFactoryTestCase4() {
	FwSmDesc_t outFactory;
	FwSmDesc_t outCmp1, outCmp2, outCmp3, outCmp4;
	CrFwInstanceId_t id, i;

	/* Instantiate the OutFactory */
	outFactory = CrFwOutFactoryMake();
	if (outFactory == NULL)
		return 0;

	/* Initialize and Reset the OutFactory */
	CrFwCmpInit(outFactory);
	CrFwCmpReset(outFactory);
	if (!CrFwCmpIsInConfigured(outFactory))
		return 0;

	/* Allocate three OutComponents */
	outCmp1 = CrFwOutFactoryMakeOutCmp(5,1,2,0);
	id = CrFwCmpGetInstanceId(outCmp1);
	outCmp2 = CrFwOutFactoryMakeOutCmp(5,4,0,0);
	outCmp3 = CrFwOutFactoryMakeOutCmp(1,1,0,70);	/* packet length will be 70 */
	outCmp4 = CrFwOutFactoryMakeOutCmp(1,1,0,0);	/* default packet length will be used */
	if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 4)
		return 0;

	/* Check the length of the OutComponents */
	if (CrFwOutCmpGetLength(outCmp2)!=50)	/* Default length is in CR_FW_OUTCMP_INIT_KIND_DESC */
		return 0;
	if (CrFwOutCmpGetLength(outCmp3)!=70)	/* Overridden length */
		return 0;
	if (CrFwOutCmpGetLength(outCmp4)!=100)	/* Default length is in CR_FW_OUTCMP_INIT_KIND_DESC */
		return 0;

	/* Release the OutComponents */
	CrFwOutFactoryReleaseOutCmp(outCmp2);
	if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 3)
		return 0;
	CrFwOutFactoryReleaseOutCmp(outCmp1);
	if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 2)
		return 0;

	/* Attempt to release an OutComponent twice */
	CrFwOutFactoryReleaseOutCmp(outCmp2);
	if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 2)
		return 0;
	if (CrFwGetAppErrCode() != crOutCmpRelErr)
		return 0;
	CrFwSetAppErrCode(crNoAppErr);

	/* Release the last OutComponents */
	CrFwOutFactoryReleaseOutCmp(outCmp3);
	CrFwOutFactoryReleaseOutCmp(outCmp4);
	if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
		return 0;

	/* Reset the OutFactory */
	CrFwCmpReset(outFactory);

	/* Allocate the max number of OutComponents with distinct Instance Identifiers */
	for (i=1; i<=CrFwOutFactoryGetNOfInstanceId(); i++) {
		outCmp1 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
		CrFwOutFactoryReleaseOutCmp(outCmp1);
	}
	outCmp1 = CrFwOutFactoryMakeOutCmp(1,1,0,0);
	if (CrFwCmpGetInstanceId(outCmp1) != id)
		return 0;
	CrFwOutFactoryReleaseOutCmp(outCmp1);

	/* Check that there are no allocated packets */
	if (CrFwPcktGetNOfAllocated() != 0)
		return 0;

	/* Check application errors */
	if (CrFwGetAppErrCode() != crNoAppErr)
		return 0;

	return 1;
}

