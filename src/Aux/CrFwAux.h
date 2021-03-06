/**
 * @file
 * @ingroup auxGroup
 * Auxiliary module to check the static part of an application's configuration.
 * The configuration of an application instantiated from the CORDET Framework is,
 * for the most part, defined statically in files with names like:
 * <code>CrFwXxxUserPar</code> where "Xxx" is the name of the framework component
 * to which the configuration information applies.
 * This module defines a set of functions which check the consistency of the
 * configuration information in these configuration files.
 * A function is defined for each configuration file and, additionally,
 * function <code>::CrFwAuxConfigCheck</code> checks all the configuration files.
 *
 * <b>Mode of Use of the Aux Module</b>
 *
 * Applications would normally use the functions in this module during the
 * application development phase to verify the correctness of the information
 * in the configuration files.
 * Once this correctness has been confirmed, the configuration checks can be
 * omitted.
 * It is therefore not expected that this module will be included in the final
 * executable for an application.
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

#ifndef CRFW_AUX_H_
#define CRFW_AUX_H_

#include "CrFwConstants.h"

/** Type for the outcome of the consistency check on the configuration parameters */
typedef enum {
	/** All configuration consistency checks have been passed  */
	crConsistencyCheckSuccess = 1,
	/** OutRegistry configuration parameters are inconsistent (see <code>CrFwAuxOutRegistryConfigCheck.h</code>) */
	crOutRegistryConfigParInconsistent = 2,
	/** OutFactory configuration parameters are inconsistent (see <code>CrFwAuxOutFactoryConfigCheck.h</code>) */
	crOutFactoryConfigParInconsistent = 3,
	/** InFactory configuration parameters for InCommands are inconsistent (see <code>CrFwAuxInFactoryInCmdConfigCheck.h</code>) */
	crInFactoryInCmdConfigParInconsistent = 4,
	/** InFactory configuration parameters for InReports are inconsistent (see <code>CrFwAuxInFactoryInRepConfigCheck.h</code>) */
	crInFactoryInRepConfigParInconsistent = 5
} CrFwConfigCheckOutcome_t;

/**
 * Check the configuration of an application.
 * This function calls all the configuration check functions and verifies that
 * they all return true (to signify: "no configuration error detected").
 * The function returns false as soon as it encounters a configuration check function
 * which returns false.
 * @return a value from <code>CrFwConfigCheckOutcome_t</code> indicating which configuration
 * check has failed.
 */
CrFwConfigCheckOutcome_t CrFwAuxConfigCheck();

/**
 * Check the configuration of the OutRegistry component.
 * The following checks are performed on the configuration data in
 * <code>CrFwOutRegistryUserPar.h</code>:
 * - CR_FW_OUTREGISTRY_N is greater than zero
 * - The service types are listed in increasing order in the service descriptor
 *   initializer (<code>CR_FW_OUTREGISTRY_INIT_SERV_DESC</code>)
 * - The service sub-types within a type are listed in increasing order in the service
 *   descriptor initializer (<code>CR_FW_OUTREGISTRY_INIT_SERV_DESC</code>)
 * - The service types, sub-types and discriminant values defined in the
 *   <code>#CR_FW_OUTREGISTRY_INIT_SERV_DESC</code> initializer are consistent with
 *   service type, sub-types and discriminant values defined in the
 *   <code>#CR_FW_OUTCMP_INIT_KIND_DESC</code>.
 * - The lower bound of a range of discriminant values in <code>#CR_FW_OUTREGISTRY_INIT_SERV_DESC</code>
 *   is smaller than or equal to the upper bound.
 * - The size of the InStream packet queue is greater than zero.
 * - The size of the OutStream packet queue is greater than zero.
 * - The size of the Pending OutComponent List (POCL) is greater than zero.
 * .
 * @return true if no errors are detected in the configuration data;
 * false otherwise.
 */
CrFwBool_t CrFwAuxOutRegistryConfigCheck();

/**
 * Check the configuration of the OutFactory component.
 * The following checks are performed on the configuration data in
 * <code>CrFwOutFactoryUserPar.h</code>:
 * - CR_FW_OUTFACTORY_MAX_NOF_OUTCMP is greater than zero if CR_FW_OUTCMP_NKINDS is greater than zero
 * - The service types are listed in increasing order in the service descriptor
 *   initializer (<code>CR_FW_OUTCMP_INIT_KIND_DESC</code>)
 * - The service sub-types within a type are listed in increasing order in the service
 *   descriptor initializer (<code>CR_FW_OUTCMP_INIT_KIND_DESC</code>)
 * - The discriminant values within a type/sub-type are listed in increasing order
 *   in the service descriptor initializer (<code>CR_FW_OUTCMP_INIT_KIND_DESC</code>)
 * - The service types, sub-types and discriminant values defined in the
 *   <code>#CR_FW_OUTCMP_INIT_KIND_DESC</code> initializer are consistent with
 *   service type, sub-types and discriminant values defined in the
 *   <code>#CR_FW_OUTREGISTRY_INIT_SERV_DESC</code>.
 * - The packet lengths specified in <code>#CR_FW_OUTCMP_INIT_KIND_DESC</code> are
 *   greater than zero.
 * .
 * @return true if no errors are detected in the configuration data;
 * false otherwise.
 */
CrFwBool_t CrFwAuxOutFactoryConfigCheck();

/**
 * Check the configuration of the InCommand part of the InFactory component.
 * The following checks are performed on the configuration data in
 * <code>CrFwInFactoryUserPar.h</code>:
 * - CR_FW_INFACTORY_MAX_NOF_INCMD is greater than zero if CR_FW_INCMD_NKINDS is greater than zero
 * - The service types are listed in increasing order in the service descriptor
 *   initializer (<code>CR_FW_INCMD_INIT_KIND_DESC</code>)
 * - The service sub-types within a type are listed in increasing order in the service
 *   descriptor initializer (<code>CR_FW_INCMD_INIT_KIND_DESC</code>)
 * - The discriminant values within a type/sub-type are listed in increasing order
 *   in the service descriptor initializer (<code>CR_FW_INCMD_INIT_KIND_DESC</code>)
 * - The values of the service types, sub-types and discriminant are lower than
 * 	 <code>#CR_FW_MAX_SERV_TYPE</code>, <code>#CR_FW_MAX_SERV_SUBTYPE</code> and
 * 	 <code>#CR_FW_MAX_DISCRIMINANT</code>.
 * .
 * @return true if no errors are detected in the configuration data;
 * false otherwise.
 */
CrFwBool_t CrFwAuxInFactoryInCmdConfigCheck();

/**
 * Check the configuration of the InReport part of the InFactory component.
 * The following checks are performed on the configuration data in
 * <code>CrFwInFactoryUserPar.h</code>:
 * - CR_FW_INFACTORY_MAX_NOF_INREP is greater than zero if CR_FW_INREP_NKINDS is greater than zero
 * - The service types are listed in increasing order in the service descriptor
 *   initializer (<code>CR_FW_INREP_INIT_KIND_DESC</code>)
 * - The service sub-types within a type are listed in increasing order in the service
 *   descriptor initializer (<code>CR_FW_INREP_INIT_KIND_DESC</code>)
 * - The discriminant values within a type/sub-type are listed in increasing order
 *   in the service descriptor initializer (<code>CR_FW_INREP_INIT_KIND_DESC</code>)
 * - The values of the service types, sub-types and discriminant are lower than
 * 	 <code>#CR_FW_MAX_SERV_TYPE</code>, <code>#CR_FW_MAX_SERV_SUBTYPE</code> and
 * 	 <code>#CR_FW_MAX_DISCRIMINANT</code>.
 * .
 * @return true if no errors are detected in the configuration data;
 * false otherwise.
 */
CrFwBool_t CrFwAuxInFactoryInRepConfigCheck();

#endif /* CRFW_AUX_H_ */
