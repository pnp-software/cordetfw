/**
 * @file CrFwCmpData.h
 * @ingroup PUSTestsuite
 * @ingroup PUSTestconfig 
 * Definition of the Framework Component Data (FCD) Type.
 * Each Framework Component has one instance of a FCD.
 * This data structure is used to exchange input and output data with the actions
 * and guards of the framework components.
 * An instance of this data structure is attached to each state machine descriptor
 * (using function <code>FwSmSetData</code>) and to each procedure descriptor
 * (using function <code>FwPrsetData</code>) used in the framework.
 * The state machines and procedures which belong to the same Framework Component share
 * the same FCD instance.
 *
 * All the framework components are derived from the Base Component of
 * <code>CrFwBaseCmp.h</code>.
 * Hence, a framework component needs two sets of data: the base data which
 * are the data needed by the functions defined on the Base Component and the
 * derived data which are the data needed by the functions defined on the
 * derived component.
 * The FCD Type is accordingly split into two parts: one part defining the base
 * data and another part defining the derived data.
 *
 * Framework users may have to modify the definition of the FCD Type if they wish
 * to introduce new components which are derived from the Base Component (see
 * detailed description of <code>::CrFwCmpData_t</code> type).
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 *
 * last modification: 22.01.2018
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#ifndef CRFW_COMPDATA_H_
#define CRFW_COMPDATA_H_

#include "CrFwUserConstants.h"
#include "FwPrConstants.h"
#include "OutStream/CrFwOutStream.h"
#include "InStream/CrFwInStream.h"
#include "InCmd/CrFwInCmd.h"
#include "InRep/CrFwInRep.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutManager/CrFwOutManager.h"
#include "InManager/CrFwInManager.h"
#include "InLoader/CrFwInLoader.h"

/**
 * Type for the Framework Component Data (FCD).
 * The FCD Type is defined as a structure with a number of fixed fields and one
 * open "component-specific" field (a pointer to <code>void</code>).
 * The fixed fields define the base data of the FCD (i.e. the data which are used
 * by the Base Component part of a Framework Component).
 * The component-specific field can be used for additional data which are specific
 * to each type of component derived from the Base Component.
 *
 * As an example, consider the case of an OutStream framework component (see
 * <code>CrFwOutStream.h</code>).
 * The fixed fields in the FCD type cover the part of the OutStream data which
 * is inherited from the Base Component.
 * The <code>cmpSpecificData</code> field covers the data which are specific
 * to the OutStream type.
 *
 * The content of the <code>cmpSpecificData</code> must be cast to the appropriate
 * type depending on the type of component which is being manipulated.
 * Thus, for instance, in the case of OutStream component, the <code>cmpSpecificData</code>
 * field must be cast to a pointer of type: <code>::CrFwOutStreamData_t</code>.
 * The component-specific data types are defined in <code>CrFwConstants.h</code>.
 *
 * This type is user-configurable to cover the case where an application developer
 * needs additional data to be attached to the component instances.
 */
typedef struct CrFwCmpData {
	/** The instance identifier of the framework component. */
	CrFwInstanceId_t instanceId;
	/** The type identifier of the framework component. */
	CrFwTypeId_t typeId;
	/**
	 * The outcome of an action or check executed by a state machine or by one of its procedures.
	 * In many cases, an action or a check have an outcome.
	 * This is a generic field where that outcome can be stored.
	 * Module <code>CrFwUtilityFunctions.h</code> defines convenience functions which check whether
	 * the outcome is equal to a certain value.
	 * Where the logical outcome is either "success" or "failure", the value of '1' is used
	 * to represent "success" and the value of '0' is used to represent "failure".
	 */
	CrFwOutcome_t outcome;
	/** The Component Initialization Procedure (CIP) (see <code>CrFwInitProc.h</code>). */
	FwPrDesc_t initProc;
	/** The Component Reset Procedure (CRP) (see <code>CrFwResetProc.h</code>). */
	FwPrDesc_t resetProc;
	/** The Component Execution Procedure (CEP) (see <code>CrFwBaseCmp.h</code>). */
	FwPrDesc_t execProc;
	/** Derived data which are specific to each type of framework component.  */
	void* cmpSpecificData;
} CrFwCmpData_t;

#endif /* CRFW_COMPDATA_H_ */
