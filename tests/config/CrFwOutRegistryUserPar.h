/**
 * @file
 * @ingroup crConfigGroup
 * User-modifiable parameters for the OutRegistry component (see <code>CrFwOutRegistry.h</code>).
 * This header file defines the set of services to be provided by the application.
 * A service is defined in terms of the following characteristics:
 * - The service type identifier
 * - The service sub-type identifier
 * - The range of discriminant values for that service type and sub-type
 * .
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of CORDET Framework.
 *
 * CORDET Framework is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CORDET Framework is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CORDET Framework.  If not, see <http://www.gnu.org/licenses/>.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#ifndef CRFW_OUTREGISTRY_USERPAR_H_
#define CRFW_OUTREGISTRY_USERPAR_H_

/**
 * The maximum number of out-going commands or reports which can be tracked by the OutRegistry.
 * This constant must be smaller than the range of <code>::CrFwTrackingIndex_t</code>.
 */
#define CR_FW_OUTREGISTRY_N 64

/**
 * The total number of service types/sub-types provided by the application.
 * An application provides a number of service types and, for each service type, it supports
 * a number of sub-types.
 * This constant defines the total number of [service type, service sub-type] pairs supported
 * by the application.
 * This constant must be smaller than the range of: <code>CrFwCmdRepIndex_t</code>.
 */
#define CR_FW_OUTREGISTRY_NSERV 10

/**
 * Definition of the range of out-going services supported by an application.
 * An application supports a number of service types and, for each service type, it supports
 * a number of sub-types.
 * Each sub-type may support a range of discriminant values.
 * Each line in this initializer describes one [service type, service sub-type] pair which is
 * supported by the application.
 * The elements in each line are as follows:
 * - The service type
 * - The service sub-type
 * - The maximum value of the discriminant for commands or reports of that type and
 *   sub-type. A value of zero indicates that no discriminant is associated to commands
 *   or report of that type and sub-type.
 * .
 * The list of service descriptors must satisfy the following constraints:
 * - The number of lines must be the same as <code>#CR_FW_OUTREGISTRY_NSERV</code>.
 * - The service types must be listed in increasing order.
 * - The service sub-types within a service type must be listed in increasing order.
 * - The set of service type and sub-types must be consistent with the service types and
 *   sub-types declared in the <code>#CR_FW_OUTCMP_INIT_KIND_DESC</code> initializer.
 * .
 * Compliance with the last three constraints is checked by
 * <code>::CrFwAuxOutRegistryConfigCheck</code>.
 */
#define CR_FW_OUTREGISTRY_INIT_SERV_DESC \
	{ {1, 1, 0, 0, 0, 0, 0},  \
	  {1, 2, 10, 0, 0, 0, 0},  \
	  {1, 7, 0, 0, 0, 0, 0},  \
	  {1, 8, 10, 0, 0, 0, 0},  \
	  {5, 1, 10, 0, 0, 0, 0},  \
	  {5, 2, 20, 0, 0, 0, 0},  \
	  {5, 3, 31, 0, 0, 0, 0},  \
	  {5, 4, 40, 0, 0, 0, 0},  \
	  {25, 3, 50, 0, 0, 0, 0},  \
	  {50, 1, 0, 0, 0, 0, 0},  \
	}

#endif /* CRFW_OUTREGISTRY_USERPAR_H_ */
