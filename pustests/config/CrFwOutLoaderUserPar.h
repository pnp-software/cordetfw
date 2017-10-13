/**
 * @file
 * @ingroup crConfigGroup
 * User-modifiable parameters for the OutLoader component (see <code>CrFwOutLoader.h</code>).
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

#ifndef CRFW_OUTLOADER_USERPAR_H_
#define CRFW_OUTLOADER_USERPAR_H_

/**
 * The function implementing the OutManager Selection Operation for the OutLoader.
 * The value of this constant must be a function pointer of type:
 * <code>::CrFwOutManagerSelect_t</code>.
 * As default value for this adaptation point, the OutLoader defines function
 * <code>::CrFwOutLoaderDefOutManagerSelect</code>.
 *
 * The OutManager Selection Operation defined in this file is the one used for the test cases
 * of <code>CrFwOutLoaderTestCases.h</code>.
 */
#define CR_FW_OUTLOADER_OUTMANAGER_SELECT &CrFwOutLoaderDefOutManagerSelect

/**
 * The function implementing the OutManager Activation Operation for the OutLoader.
 * The value of this constant must be a function pointer of type:
 * <code>::CrFwOutManagerActivate_t</code>.
 * As default value for this adaptation point, the OutLoader defines function
 * <code>::CrFwOutLoadDefOutManagerActivate</code>.
 *
 * The OutManager Activation Operation defined in this file is the one used for the test cases
 * of <code>CrFwOutLoaderTestCases.h</code>.
 */
#define CR_FW_OUTLOADER_OUTMANAGER_ACTIVATE &CrFwOutLoadDefOutManagerActivate

/**
 * The function implementing the Initialization Check of the OutLoader component.
 * The OutLoader component is derived from the Base Component and it therefore
 * inherits its Initialization Procedure (see <code>CrFwInitProc.h</code>).
 * The initialization procedure must be configured with two actions:
 * the Initialization Action and the Initiation Check.
 * This constant defines the function implementing the Initialization Check
 * for the the OutLoader component.
 * This value of this constant must be a function pointer of type:
 * <code>FwPrAction_t</code>.
 * As default value for this adaptation point, function <code>::CrFwBaseCmpDefInitCheck</code>
 * defined on the Base Component may be used.
 *
 * The value of the constant in this file is the one used for the test cases
 * of <code>CrFwOutLoaderTestCases.h</code>.
 */
#define CR_FW_OUTLOADER_INITCHECK &CrFwBaseCmpDefInitCheck

/**
 * The function implementing the Initialization Action of the OutLoader component.
 * The OutLoader component is derived from the Base Component and it therefore
 * inherits its Initialization Procedure (see <code>CrFwInitProc.h</code>).
 * The initialization procedure must be configured with two actions:
 * the Initialization Action and the Initiation Check.
 * This constant defines the function implementing the Initialization Action
 * for the the OutLoader component.
 * This value of this constant must be a function pointer of type:
 * <code>FwPrAction_t</code>.
 * As default value for this adaptation point, function <code>::CrFwBaseCmpDefInitAction</code>
 * defined on the Base Component may be used.
 *
 * The value of the constant in this file is the one used for the test cases
 * of <code>CrFwOutLoaderTestCases.h</code>.
 */
#define CR_FW_OUTLOADER_INITACTION &CrFwBaseCmpDefInitAction

/**
 * The function implementing the Configuration Check of the OutLoader component.
 * The OutLoader component is derived from the Base Component and it therefore
 * inherits its Configuration Procedure (see <code>CrFwResetProc.h</code>).
 * The configuration procedure must be configured with two actions:
 * the Configuration Action and the Configuration Check.
 * This constant defines the function implementing the Configuration Check
 * for the the OutLoader component.
 * This value of this constant must be a function pointer of type:
 * <code>FwPrAction_t</code>.
 * As default value for this adaptation point, function <code>::CrFwBaseCmpDefConfigCheck</code>
 * defined on the Base Component may be used.
 *
 * The value of the constant in this file is the one used for the test cases
 * of <code>CrFwOutLoaderTestCases.h</code>.
 */
#define CR_FW_OUTLOADER_CONFIGCHECK &CrFwBaseCmpDefConfigCheck

/**
 * The function implementing the Configuration Action of the OutLoader component.
 * The OutLoader component is derived from the Base Component and it therefore
 * inherits its Configuration Procedure (see <code>CrFwResetProc.h</code>).
 * The configuration procedure must be configured with two actions:
 * the Configuration Action and the Configuration Check.
 * This constant defines the function implementing the Configuration Action
 * for the the OutLoader component.
 * This value of this constant must be a function pointer of type:
 * <code>FwPrAction_t</code>.
 * As default value for this adaptation point, function <code>::CrFwBaseCmpDefConfigAction</code>
 * defined on the Base Component may be used.
 *
 * The value of the constant in this file is the one used for the test cases
 * of <code>CrFwOutLoaderTestCases.h</code>.
 */
#define CR_FW_OUTLOADER_CONFIGACTION &CrFwBaseCmpDefConfigAction

/**
 * The function implementing the Shutdown Action of the OutLoader component.
 * The OutLoader component is derived from the Base Component and it therefore
 * inherits its Shutdown Action (see <code>CrFwBaseCmp.h</code>).
 * This constant defines the shutdown function for the the OutLoader component.
 * The value of this constant must be a function pointer of type:
 * <code>FwSmAction_t</code>.
 * As default value for this adaptation point, function <code>::CrFwBaseCmpDefShutdownAction</code>
 * defined on the Base Component may be used.
 *
 * The value of the constant in this file is the one used for the test cases
 * of <code>CrFwOutLoaderTestCases.h</code>.
 */
#define CR_FW_OUTLOADER_SHUTDOWNACTION &CrFwBaseCmpDefShutdownAction

#endif /* CRFW_OUTLOADER_USERPAR_H_ */
