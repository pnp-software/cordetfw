/**
 * @file
 * @ingroup crConfigGroup
 * User-modifiable parameters for the InRegistry component (see <code>CrFwInRegistry.h</code>).
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

#ifndef CRFW_INREGISTRY_USERPAR_H_
#define CRFW_INREGISTRY_USERPAR_H_

/**
 * The maximum number of commands or reports which can be tracked by the InRegistry.
 * This constant must be smaller than the range of <code>::CrFwTrackingIndex_t</code>.
 */
#define CR_FW_INREGISTRY_N 64

#endif /* CRFW_INREGISTRY_USERPAR_H_ */
