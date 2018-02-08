/**
 * @file
 * @ingroup outMngGroup
 * Definition of the OutFactory component.
 *
 * The OutFactory component offers an interface through which OutComponents
 * (see <code>CrFwOutCmp.h</code>) can be allocated and released.
 * Applications need OutComponents to encapsulate out-going commands or reports.
 * This interface provides the factory functions through which an OutComponent
 * can be created and released.
 *
 * The OutFactory is implemented as an extension of the Base Component of
 * <code>CrFwBaseCmp.h</code>.
 * The OutFactory is a singleton component.
 * This interface provides a function to create the OutFactory and it provides
 * a function to create an OutComponent of a specified kind.
 *
 * The OutFactory maintains a pool of pre-allocated OutComponents (the size of the pool
 * is defined in <code>CrFwOutFactoryUserPar.h</code>).
 * Memory for the pool is allocated when the OutFactory is initialized and is never
 * released afterwards.
 * Items in the pool are marked as "in use" when they are allocated to an application
 * and are marked as "not in use" when they are released.
 * When the OutFactory is reset, all the items in the pool are marked as "not in use".
 * No memory allocation operations (<code>malloc/free</code>) are therefore performed when
 * OutComponents are allocated or released.
 *
 * <b>Mode of Use of an OutFactory Component</b>
 *
 * The configuration of the OutFactory component is defined statically in
 * <code>CrFwOutFactoryUserPar.h</code>.
 *
 * The OutFactory is created with function <code>::CrFwOutFactoryMake</code>.
 * After being created, the OutFactory must be initialized and reset.
 * This is done with functions <code>::CrFwCmpInit</code> and <code>::CrFwCmpReset</code>.
 * Nominally, after being initialized and reset the OutFactory State Machine should be
 * in state CONFIGURED (this can be checked by verifying that function <code>FwSmGetCurState</code>
 * returns CR_FW_BASE_STATE_CONFIGURED).
 *
 * After being configured, the OutFactory is ready to manage the creation and release
 * process for OutComponents.
 * An OutComponent is created with function <code>::CrFwOutFactoryMakeOutCmp</code> and it
 * is released with function <code>::CrFwOutFactoryReleaseOutCmp</code>.
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

#ifndef CRFW_OUTFACTORY_H_
#define CRFW_OUTFACTORY_H_

/* Include Framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmCore.h"

/**
 * Factory function for the singleton instance of the OutFactory.
 * The first time it is called, this function creates the OutFactory singleton instance.
 * Subsequent calls return the same instance.
 * The first time this function is called, it returns the OutFactory in state CREATED.
 * @return the OutFactory singleton instance.
 */
FwSmDesc_t CrFwOutFactoryMake();

/**
 * Make function for an OutComponent.
 * This function returns an OutComponent in state CONFIGURED.
 * The OutComponent is reset before being returned to the caller of this
 * function (its State Execution Counter is guaranteed to be equal to zero).
 *
 * The caller specifies the kind of OutComponent it wishes by specifying its type, sub-type,
 * discriminant and the packet length.
 * Of these four parameters, the first three (type, sub-type, and discriminant) are mandatory whereas
 * for the last one (length) a dummy value of zero is possible.
 * Given the type, sub-type and discriminant, the function looks for a matching entry in the
 * <code>::CR_FW_OUTCMP_INIT_KIND_DESC</code> initializer.
 * If no matching entry is found (i.e. if no entry is found with the same values of type, sub-type
 * and discriminant), then the function sets the application error code to <code>crOutCmpAllocationFail</code>
 * and returns a value of NULL.
 * If instead a matching entry is found, two options are possible:
 * - If the length parameter is set to zero, then the function creates and returns an OutComponent with the
 *   characteristics given by the matching entry in the <code>::CR_FW_OUTCMP_INIT_KIND_DESC</code> initializer.
 * - If instead the length parameter has a non-zero value, then the function creates and returns an OutComponent
 *   with the characteristics given by the matching entry in the <code>::CR_FW_OUTCMP_INIT_KIND_DESC</code>
 *   initializer with the exception of the packet length which is set equal to the value specified
 *   in the function call.
 * .
 * Thus, the length value specified in the function call may be used to override the length
 * value specified in the <code>::CR_FW_OUTCMP_INIT_KIND_DESC</code> initializer).
 * This override mechanism is useful for reports or commands whose length must be determined
 * dynamically (as opposed to being statically determined in the
 * <code>::CR_FW_OUTCMP_INIT_KIND_DESC</code> initializer).
 *
 * When an OutComponent is returned by this function, it has the following attributes set:
 * - The OutComponent packet length
 * - The OutComponent command/report type flag (which defines whether the OutComponent is a
 *   report or a command)
 * - The OutComponent source attribute
 * - The OutComponent group attribute
 * - The OutComponent service type
 * - The OutComponent service sub-type
 * - The OutComponent discriminant
 * - The OutComponent sequence counter
 * - The OutComponent instance identifier
 * .
 * The values of type, sub-type, command/report flag and discriminant are derived from the information in the
 * <code>::CR_FW_OUTCMP_INIT_KIND_DESC</code> initializer. The type and sub-type cannot be changed after
 * an OutComponent has been created. Applications can instead override the default setting of the
 * discriminant by using function <code>::CrFwOutCmpSetDiscriminant</code>.
 *
 * As explained above, the value of the packet length is either derived from the
 * <code>::CR_FW_OUTCMP_INIT_KIND_DESC</code> initializer (if the function is called with the
 * length parameter set to zero) or else it is equal to the length parameter in the function call.
 *
 * The value of the instance identifier is built as follows.
 * Let n be the number of OutComponents made by the factory since it was last reset;
 * let APP_ID be the application identifier (see <code>#CR_FW_HOST_APP_ID</code>); let
 * m be the number of bits reserved for the application identifier (see
 * <code>#CR_FW_NBITS_APP_ID</code>); and let s be the number of bits of the instance
 * identifier.
 * The instance identifier is then given by: APP_ID*(2**(s-m))+n.
 * In this formula, the value of n is incremented by 1 every time a new OutComponent is
 * created by the OutFactory and it is reset to 0 when it reaches APP_ID*(2**(s-m)).
 *
 * The value of the sequence counter is initialized to zero.
 *
 * The value of the source attribute is set equal to the identifier of the host application
 * (namely <code>#CR_FW_HOST_APP_ID</code>).
 *
 * The value of the group attribute is set to a default value of zero. Applications can override
 * this default setting by using function <code>::CrFwOutCmpSetGroup</code>.
 *
 * This function allocates the memory for the new OutComponent from a pool of pre-allocated
 * memory which is created when the OutFactory is initialized (see
 * <code>::OutFactoryInitAction</code>).
 * If no free memory is available in the factory pool, this function returns NULL.
 * Allocation memory failure results in the application error code being set
 * to <code>crOutCmpAllocationFail</code>.
 *
 * When an OutComponent created by this function is no longer needed, it should be
 * returned to the factory by calling <code>CrFwOutCmpRelease</code>.
 *
 * If the OutFactory is reset, then all the OutComponents which had been created
 * by the factory are released.
 *
 * @param type the service type of the OutComponent
 * @param subType the service sub-type of the OutComponent
 * @param discriminant the discriminant of the OutComponent
 * @param length either zero (if the packet length is to be taken from the
 * <code>::CR_FW_OUTCMP_INIT_KIND_DESC</code> initializer) or the packet length
 * @return a new OutComponent or NULL if it was not possible to allocate the memory
 * for the OutComponent.
 */
FwSmDesc_t CrFwOutFactoryMakeOutCmp(CrFwServType_t type, CrFwServSubType_t subType,
                                    CrFwDiscriminant_t discriminant, CrFwPcktLength_t length);

/**
 * Release function for an OutComponent.
 * The argument of this function must be an OutComponent which was created using function
 * <code>::CrFwOutFactoryMakeOutCmp</code>.
 * This function releases the memory which was allocated to the OutComponent.
 * After this function is called, the OutComponent cannot be used any longer.
 * The function does not perform any checks on the existence or status of the
 * OutComponent.
 * An attempt to use an OutComponent which has been released will result in undefined behaviour.
 *
 * An attempt to release an OutComponent which had already been released, or to release a
 * non-existent OutComponent will result in undefined behaviour and in the application
 * error code being set to: <code>::crOutCmpRelErr</code>.
 *
 * @param outCmpInstance the OutComponent to be released
 */
void CrFwOutFactoryReleaseOutCmp(FwSmDesc_t outCmpInstance);

/**
 * Return the number of OutComponents which are currently allocated.
 * This function returns the number of OutComponents which have been successfully
 * allocated through calls to <code>::CrFwOutFactoryMakeOutCmp</code> and have not yet been
 * released through calls to <code>::CrFwOutFactoryReleaseOutCmp</code>.
 * @return the number of OutComponents which are currently allocated.
 */
CrFwOutFactoryPoolIndex_t CrFwOutFactoryGetNOfAllocatedOutCmp();

/**
 * Return the maximum number of OutComponents which may be allocated at any one time.
 * @return the maximum number of OutComponents which may be allocated at any one time
 */
CrFwOutFactoryPoolIndex_t CrFwOutFactoryGetMaxNOfOutCmp();

/**
 * Return the number of distinct instance identifiers supported by the OutFactory.
 * The OutFactory allocates the instance identifier of an OutComponent as explained
 * in the documentation of <code>::CrFwOutFactoryMakeOutCmp</code>.
 * @return the maximum number of OutComponents which may be allocated at any one time
 */
CrFwInstanceId_t CrFwOutFactoryGetNOfInstanceId();

#endif /* CRFW_OUTFACTORY_H_ */
