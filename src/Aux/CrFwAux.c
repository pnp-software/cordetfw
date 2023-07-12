/**
 * @file
 * @ingroup auxGroup
 * Implementation of Auxiliary Module.
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

#include <stdlib.h>
/* Include framework files */
#include "CrFwConstants.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "CrFwAux.h"
#include "OutCmp/CrFwOutCmp.h"
/* Include configuration files */
#include "CrFwInRegistryUserPar.h"
#include "CrFwOutRegistryUserPar.h"
#include "CrFwOutFactoryUserPar.h"
#include "CrFwInFactoryUserPar.h"
#include "CrFwInStreamUserPar.h"
#include "CrFwOutStreamUserPar.h"
#include "CrFwOutManagerUserPar.h"

/** Array of OutComponent descriptors. */
static CrFwOutCmpKindDesc_t outCmpKindDesc[CR_FW_OUTCMP_NKINDS] = CR_FW_OUTCMP_INIT_KIND_DESC;

/** Array of InCommand descriptors. */
static CrFwInCmdKindDesc_t inCmdKindDesc[CR_FW_INCMD_NKINDS] = CR_FW_INCMD_INIT_KIND_DESC;

/** Array of InReport service descriptors. */
static CrFwInRepKindDesc_t inRepKindDesc[CR_FW_INREP_NKINDS] = CR_FW_INREP_INIT_KIND_DESC;

/** Array of service descriptors. */
static CrFwServDesc_t servDesc[CR_FW_OUTREGISTRY_NSERV] = CR_FW_OUTREGISTRY_INIT_SERV_DESC;

/** The sizes of the packet queues in the InStream components. */
static CrFwCounterU1_t inStreamPcktQueueSize[CR_FW_NOF_INSTREAM] = CR_FW_INSTREAM_PQSIZE;

/** The sizes of the POCL in the OutManager components. */
static CrFwCounterU1_t outManagerPoclSize[CR_FW_NOF_OUTMANAGER] = CR_FW_OUTMANAGER_POCLSIZE;

/** The sizes of the packet queues in the OutStream components. */
static CrFwCounterU1_t outStreamPcktQueueSize[CR_FW_NOF_OUTSTREAM] = CR_FW_OUTSTREAM_PQSIZE;

/** The (destination, outStream) pairs */
static CrFwDestSrc_t outStreamDest[CR_FW_OUTSTREAM_NOF_DEST][2] = CR_FW_OUTSTREAM_DEST_PAIRS;

/** The (source, inStream) pairs */
static CrFwDestSrc_t inStreamSrc[CR_FW_INSTREAM_NOF_SRCS][2] = CR_FW_INSTREAM_SRC_PAIRS;

/* -------------------------------------------------------------------------- */
CrFwConfigCheckOutcome_t CrFwAuxConfigCheck() {

	if (CrFwAuxOutRegistryConfigCheck() == 0)
		return crOutRegistryConfigParInconsistent;

	if (CrFwAuxOutFactoryConfigCheck() == 0)
		return crOutFactoryConfigParInconsistent;

	if (CrFwAuxInFactoryInCmdConfigCheck() == 0)
		return crInFactoryInCmdConfigParInconsistent;

	if (CrFwAuxInFactoryInRepConfigCheck() == 0)
		return crInFactoryInRepConfigParInconsistent;

	if (CrFwAuxOutStreamConfigCheck() == 0)
		return crOutStreamConfigParInconsistent;

	if (CrFwAuxInStreamConfigCheck() == 0)
		return crInStreamConfigParInconsistent;

	if (CrFwAuxInRegistryConfigCheck() == 0)
		return crInRegistryConfigParInconsistent;

	return crConsistencyCheckSuccess;
}

/* -------------------------------------------------------------------------- */
CrFwBool_t CrFwAuxOutStreamConfigCheck() {
	unsigned int i;

	if (CR_FW_NOF_OUTSTREAM < 1)
		return 0;

	if (CR_FW_OUTSTREAM_NOF_DEST < 1)
		return 0;

	for (i=0; i<CR_FW_OUTSTREAM_NOF_DEST; i++) {
		if (outStreamDest[i][1] >= CR_FW_NOF_OUTSTREAM)
			return 0;
		if (outStreamDest[i][0] < 1)
			return 0;
	}

	for (i=0; i<CR_FW_NOF_OUTSTREAM; i++)
		if (outStreamPcktQueueSize[i] < 1)
			return 0;

	if (CR_FW_OUTSTREAM_NOF_GROUPS < 1)
		return 0;

	return 1;
}

/* -------------------------------------------------------------------------- */
CrFwBool_t CrFwAuxInStreamConfigCheck() {
	unsigned int i;

	if (CR_FW_NOF_INSTREAM < 1)
		return 0;

	if (CR_FW_INSTREAM_NOF_SRCS < 1)
		return 0;

	for (i=0; i<CR_FW_INSTREAM_NOF_SRCS; i++) {
		if (inStreamSrc[i][1] >= CR_FW_NOF_INSTREAM)
			return 0;
		if (inStreamSrc[i][0] < 1)
			return 0;
	}

	for (i=0; i<CR_FW_NOF_INSTREAM; i++)
		if (inStreamPcktQueueSize[i] < 1)
			return 0;

	if (CR_FW_INSTREAM_NOF_GROUPS < 1)
		return 0;

	return 1;
}

/* -------------------------------------------------------------------------- */
CrFwBool_t CrFwAuxOutRegistryConfigCheck() {
	CrFwCmdRepIndex_t i;
	CrFwCmdRepKindIndex_t j;
	CrFwCounterU1_t k;
	CrFwServType_t servType;
	CrFwServSubType_t servSubType;
	CrFwBool_t found;

	if (CR_FW_OUTREGISTRY_N < 1)
		return 0;

	for (i=0; i<(CR_FW_OUTREGISTRY_NSERV-1); i++) {
		if (servDesc[i].servType > servDesc[i+1].servType)
			/* The following can be dead code, depending on the specific
			 * instantiation of the FW Profile.*/
			return 0;
		if (servDesc[i].servType == servDesc[i+1].servType)
			if (servDesc[i].servSubType > servDesc[i+1].servSubType)
				/* The following can be dead code, depending on the specific
				 * instantiation of the FW Profile.*/
				return 0;
	}

	for (i=0; i<CR_FW_OUTREGISTRY_NSERV; i++) {
		servType = servDesc[i].servType;
		servSubType = servDesc[i].servSubType;
		found = 0;
		for (j=0; j<CR_FW_OUTCMP_NKINDS; j++) {
			if (outCmpKindDesc[j].servType == servType)
				if (outCmpKindDesc[j].servSubType == servSubType) {
					found = 1;
					break;
				}
			if (outCmpKindDesc[j].servType > servType)
				break;
		}
		if (found == 0)
			/* The following can be dead code, depending on the specific
			 * instantiation of the FW Profile.*/
			return 0;
	}

    for (i=0; i<CR_FW_OUTREGISTRY_NSERV; i++) {
        if (servDesc[i].lowerBoundDisc > servDesc[i].upperBoundDisc)
            return 0;
    }

	for (k=0; k<CR_FW_NOF_INSTREAM; k++)
		/* The following can be dead code, depending on the specific
		 * instantiation of the FW Profile.*/
		if (inStreamPcktQueueSize[k]<1)
			return 0;

	for (k=0; k<CR_FW_NOF_OUTSTREAM; k++)
		/* The following can be dead code, depending on the specific
		 * instantiation of the FW Profile.*/
		if (outStreamPcktQueueSize[k]<1)
			return 0;

	for (k=0; k<CR_FW_NOF_OUTMANAGER; k++)
		/* The following can be dead code, depending on the specific
		 * instantiation of the FW Profile.*/
		if (outManagerPoclSize[k]<1)
			return 0;

	return 1;
}

/* -------------------------------------------------------------------------- */
CrFwBool_t CrFwAuxOutFactoryConfigCheck() {
	CrFwCmdRepIndex_t j;
	CrFwCmdRepKindIndex_t i;
	CrFwServType_t servType;
	CrFwServSubType_t servSubType;
	CrFwDiscriminant_t disc;
	CrFwBool_t found;

	if ((CR_FW_OUTFACTORY_MAX_NOF_OUTCMP < 1) && (CR_FW_OUTCMP_NKINDS > 0))
		return 0;

	for (i=0; i<(CR_FW_OUTCMP_NKINDS-1); i++) {
		if (outCmpKindDesc[i].servType > outCmpKindDesc[i+1].servType)
			return 0;

		if (outCmpKindDesc[i].servType == outCmpKindDesc[i+1].servType)
			if (outCmpKindDesc[i].servSubType > outCmpKindDesc[i+1].servSubType)
				return 0;

		if (outCmpKindDesc[i].servType == outCmpKindDesc[i+1].servType)
			if (outCmpKindDesc[i].servSubType == outCmpKindDesc[i+1].servSubType)
				if (outCmpKindDesc[i].discriminant > outCmpKindDesc[i+1].discriminant)
					return 0;

		if (outCmpKindDesc[i].pcktLength < 1)
			return 0;
	}

	for (i=0; i<CR_FW_OUTCMP_NKINDS; i++) {
		servType = outCmpKindDesc[i].servType;
		servSubType = outCmpKindDesc[i].servSubType;
		disc = outCmpKindDesc[i].discriminant;
		found = 0;
		for (j=0; j<CR_FW_OUTREGISTRY_NSERV; j++) {
			if (servDesc[j].servType == servType)
				if (servDesc[j].servSubType == servSubType)
                    if (disc == 0) {
                        found = 1;
                        break;
                    }
				    if (disc <= servDesc[j].upperBoundDisc)
					    if (disc >= servDesc[j].lowerBoundDisc) {
					        found = 1;
					        break;
					    }
			if (servDesc[j].servType > servType)
				break;
		}
		if (found == 0)
			return 0;
	}

	return 1;
}

/* -------------------------------------------------------------------------- */
CrFwBool_t CrFwAuxInFactoryInCmdConfigCheck() {
	CrFwCmdRepKindIndex_t i;

	if ((CR_FW_INFACTORY_MAX_NOF_INCMD < 1) && (CR_FW_OUTCMP_NKINDS > 0))
		return 0;

	for (i=0; i<(CR_FW_INCMD_NKINDS-1); i++) {
		if (inCmdKindDesc[i].servType > inCmdKindDesc[i+1].servType)
			return 0;

		if (inCmdKindDesc[i].servType == inCmdKindDesc[i+1].servType)
			if (inCmdKindDesc[i].servSubType > inCmdKindDesc[i+1].servSubType)
				return 0;

		if (inCmdKindDesc[i].servType == inCmdKindDesc[i+1].servType)
			if (inCmdKindDesc[i].servSubType == inCmdKindDesc[i+1].servSubType)
				if (inCmdKindDesc[i].discriminant > inCmdKindDesc[i+1].discriminant)
					return 0;
	}

	for (i=0; i<CR_FW_INCMD_NKINDS; i++) {
		if (inCmdKindDesc[i].servType > CR_FW_MAX_SERV_TYPE)
			return 0;

		if (inCmdKindDesc[i].servSubType > CR_FW_MAX_SERV_SUBTYPE)
			return 0;

		if (inCmdKindDesc[i].discriminant > CR_FW_MAX_DISCRIMINANT)
			return 0;
	}

	return 1;
}

/* -------------------------------------------------------------------------- */
CrFwBool_t CrFwAuxInFactoryInRepConfigCheck() {
	CrFwCmdRepKindIndex_t i;

	if ((CR_FW_INFACTORY_MAX_NOF_INREP < 1) && (CR_FW_INREP_NKINDS > 0))
		return 0;

	for (i=0; i<(CR_FW_INREP_NKINDS-1); i++) {
		if (inRepKindDesc[i].servType > inRepKindDesc[i+1].servType)
			return 0;

		if (inRepKindDesc[i].servType == inRepKindDesc[i+1].servType)
			if (inRepKindDesc[i].servSubType > inRepKindDesc[i+1].servSubType)
				return 0;

		if (inRepKindDesc[i].servType == inRepKindDesc[i+1].servType)
			if (inRepKindDesc[i].servSubType == inRepKindDesc[i+1].servSubType)
				if (inRepKindDesc[i].discriminant > inRepKindDesc[i+1].discriminant)
					return 0;
	}

	for (i=0; i<CR_FW_INREP_NKINDS; i++) {
		if (inRepKindDesc[i].servType > CR_FW_MAX_SERV_TYPE)
			return 0;

		if (inRepKindDesc[i].servSubType > CR_FW_MAX_SERV_SUBTYPE)
			return 0;

		if (inRepKindDesc[i].discriminant > CR_FW_MAX_DISCRIMINANT)
			return 0;
	}

	return 1;
}

CrFwBool_t CrFwAuxInFactoryInRegistryConfigCheck() {
	if (CR_FW_INREGISTRY_N < 1)
		return 0;
	
	return 1;
}
