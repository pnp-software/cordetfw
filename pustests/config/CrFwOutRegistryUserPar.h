/**
 * @file CrFwOutRegistryUserPar.h
 * @ingroup PUSTestsuite
 * @ingroup PUSTestconfig 
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
#define CR_FW_OUTREGISTRY_NSERV 25

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
	{ { 1,  1, 0, 0, 1, 1, NULL},\
	  { 1,  2, 0, 0, 1, 1, NULL},\
	  { 1,  3, 0, 0, 1, 1, NULL},\
	  { 1,  4, 0, 0, 1, 1, NULL},\
	  { 1,  5, 0, 0, 1, 1, NULL},\
	  { 1,  6, 0, 0, 1, 1, NULL},\
	  { 1,  7, 0, 0, 1, 1, NULL},\
	  { 1,  8, 0, 0, 1, 1, NULL},\
	  { 1, 10, 0, 0, 1, 1, NULL},\
	  { 3, 10, 3, 0, 1, 1, NULL},\
	  { 3, 12, 3, 0, 1, 1, NULL},\
	  { 3, 25, 3, 0, 1, 1, NULL},\
	  { 3, 26, 3, 0, 1, 1, NULL},\
	  { 5,  1, 1, 0, 1, 1, NULL}, \
	  { 5,  2, 1, 0, 1, 1, NULL}, \
	  { 5,  3, 1, 0, 1, 1, NULL}, \
	  { 5,  4, 1, 0, 1, 1, NULL}, \
	  { 5,  8, 0, 0, 1, 1, NULL}, \
	  {13,  1, 0, 0, 1, 1, NULL}, \
	  {13,  2, 0, 0, 1, 1, NULL}, \
	  {13,  3, 0, 0, 1, 1, NULL}, \
	  {13, 16, 0, 0, 1, 1, NULL}, \
	  {17,  1, 0, 0, 1, 1, NULL},\
	  {17,  2, 0, 0, 1, 1, NULL},\
	  {17,  4, 0, 0, 1, 1, NULL} \
	}


#endif /* CRFW_OUTREGISTRY_USERPAR_H_ */
