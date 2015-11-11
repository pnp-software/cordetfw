/**
 * @file
 * @ingroup inMngGroup
 * Definition of the InFactory component.
 *
 * The InFactory component offers an interface through which incoming report components
 * (InReports, see <code>CrFwInRep.h</code>) or incoming command components
 * (InCommands, see <code>CrFwInCmd.h</code> be allocated and released.
 *
 * The InFactory is implemented as an extension of the Base Component of
 * <code>CrFwBaseCmp.h</code>.
 * The InFactory is a singleton component.
 *
 * This interface provides a function to create the InFactory, it provides
 * functions to create an InReport or an InCommand of a specified kind,
 * and it provides functions to release previously allocated InReports or
 * InCommands.
 *
 * The InFactory maintains a pool of pre-allocated InReports and a pool
 * of pre-allocated InCommands
 * (the sizes of the pools are defined in <code>CrFwInFactoryUserPar.h</code>).
 * Memory for the pools is allocated when the InFactory is initialized and is only
 * released if the InFactory is shutdown.
 * Items in the pool are marked as "in use" when they are allocated to an application
 * and are marked as "not in use" when they are released.
 * No memory allocation operations (<code>malloc/free</code>) are therefore performed
 * when InReports or InCommands are allocated or released.
 * When the InFactory is reset, all the items in the pool are marked as "not in use".
 *
 * <b>Mode of Use of an InFactory Component</b>
 *
 * The configuration of the InFactory component is defined statically in
 * <code>CrFwInFactoryUserPar.h</code>.
 *
 * The InFactory is created with function <code>::CrFwInFactoryMake</code>.
 * After being created, the InFactory must be initialized and reset.
 * This is done with functions <code>::CrFwCmpInit</code> and <code>::CrFwCmpReset</code>.
 * Nominally, after being initialized and reset the InFactory State Machine should be
 * in state CONFIGURED (this can be checked by verifying that function <code>FwSmGetCurState</code>
 * returns CR_FW_BASE_STATE_CONFIGURED).
 *
 * After being configured, the InFactory is ready to manage the creation and release
 * process for InReports and InCommands.
 * An InReport is created with function <code>::CrFwInFactoryMakeInRep</code> and it
 * is released with function <code>::CrFwInFactoryReleaseInRep</code>.
 * Similarly, an InCommand is created with function <code>::CrFwInFactoryMakeInCmd</code> and it
 * is released with function <code>::CrFwInFactoryReleaseInCmd</code>.
 *
 * An InReport wraps a packet holding an incoming report and an InCommand wraps a packet
 * holding an incoming command.
 * The packet holding the report or command is passed as an argument to the make function which
 * creates the InReport or InCommand component.
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

#ifndef CRFW_INFACTORY_H_
#define CRFW_INFACTORY_H_

/* Include Framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwProfile/FwSmConstants.h"
#include "FwProfile/FwSmCore.h"

/**
 * Factory function for the singleton instance of the InFactory.
 * The first time it is called, this function creates the InFactory singleton instance.
 * Subsequent calls return the same instance.
 * The first time this function is called, it returns the InFactory in state CREATED.
 * @return the OutFactory singleton instance.
 */
FwSmDesc_t CrFwInFactoryMake();

/**
 * Make function for a component encapsulating an incoming report (InReport).
 * This function initializes and resets a component before returning it.
 * Under nominal conditions, the component returned by this function is
 * therefore in state CONFIGURED (but it could be in state INITIALIZED
 * if the InReport's configuration check fails).
 *
 * An InReport encapsulates an incoming packet holding a report.
 * The packet is passed as an argument to this function.
 * The packet holds all the information about the incoming report.
 * In particular, it holds the information about the report kind (as determined
 * by the triplet: [service type, service sub-type, discriminant]).
 * This function checks the report kind and, if it finds that it is illegal,
 * it returns NULL and sets the application error code to: <code>::crIllInRepKind</code>).
 * If instead the command is legal, this function uses it to configure the InReport.
 * The configuration information is retrieved from <code>CrFwInFactoryUserPar</code>.
 *
 * If the allocation of the memory for the new InReport fails, the function
 * returns NULL.
 * Allocation memory failure results in the application error code being set
 * to <code>crInRepAllocationFail</code>.
 *
 * When an InReport created by this function is no longer needed,
 * it should be returned to the factory by calling <code>CrFwInRepReleaseInRep</code>.
 *
 * The instance identifier of the InReport created by this function is equal to
 * the number of InReports created by the factory since it was last reset.
 *
 * If the InFactory is reset, then all the InReports which had been created
 * by the factory are released.
 *
 * @param pckt the packet holding the InReport
 * @return a new InReport or NULL if it was not possible to allocate the memory
 * for the InReport.
 */
FwSmDesc_t CrFwInFactoryMakeInRep(CrFwPckt_t pckt);

/**
 * Make function for a component encapsulating an incoming command (InCommand).
 * This function initializes and resets a component before returning it.
 * Under nominal conditions, the component returned by this function is
 * therefore in state CONFIGURED (but it could be in state INITIALIZED
 * if the InCommand's configuration check fails).
 *
 * An InCommand encapsulates an incoming packet holding a command.
 * The packet is passed as an argument to this function.
 * The packet holds all the information about the incoming command.
 * In particular, it holds the information about the command kind (as determined
 * by the triplet: [service type, service sub-type, discriminant]).
 * This function checks the command kind and, if it finds that it is illegal,
 * it returns NULL and sets the application error code to: <code>::crIllInCmdKind</code>).
 * If instead the command is legal, this function uses it to configure the InCommand.
 * The configuration information is retrieved from <code>CrFwInFactoryUserPar</code>.
 *
 * If the allocation of the memory for the new InCommand fails, the function
 * returns NULL.
 * Allocation memory failure results in the application error code being set
 * to <code>::crInCmdAllocationFail</code>.
 *
 * When an InCommand created by this function is no longer needed,
 * it should be returned to the factory by calling <code>::CrFwInFactoryReleaseInCmd</code>.
 *
 * If the InFactory is reset, then all the InCommands which had been created
 * by the factory are released.
 *
 * @param pckt the packet holding the InCommand
 * @return a new InCommand or NULL if it was not possible to allocate the memory
 * for the InCommand or if the packet type is not recognized.
 */
FwSmDesc_t CrFwInFactoryMakeInCmd(CrFwPckt_t pckt);

/**
 * Release function for an InReport.
 * The argument of this function must be an InReport which was created using function
 * <code>::CrFwInFactoryMakeInRep</code>.
 * This function releases the memory which was allocated to the InReport.
 * After this function is called, the InReport cannot be used.
 * The function does not perform any checks on the existence or status of the
 * InReport.
 * An attempt to use an InReport which has been released will result in undefined behaviour.
 *
 * An attempt to release an InReport which had already been released, or to release a
 * non-existent InReport will result in undefined behaviour and in the application
 * error code being set to: <code>::crInRepRelErr</code>.
 *
 * @param inRepInstance the InReport to be released
 */
void CrFwInFactoryReleaseInRep(FwSmDesc_t inRepInstance);

/**
 * Release function for an InCommand.
 * The argument of this function must be an InCommand which was created using function
 * <code>::CrFwInFactoryMakeInCmd</code>.
 * This function releases the memory which was allocated to the InCommand.
 * After this function is called, the InCommand cannot be used.
 * The function does not perform any checks on the existence or status of the
 * InCommand.
 * An attempt to use an InCommand which has been released will result in undefined behaviour.
 *
 * An attempt to release an InCommand which had already been released, or to release a
 * non-existent InCommand will result in undefined behaviour and in the application
 * error code being set to: <code>::crInCmdRelErr</code>.
 *
 * @param inCmdInstance the InCommand to be released
 */
void CrFwInFactoryReleaseInCmd(FwSmDesc_t inCmdInstance);

/**
 * Return the number of InReports which are currently allocated.
 * This function returns the number of InReports which have been successfully
 * allocated through calls to <code>::CrFwInFactoryMakeInRep</code> and have not yet been
 * released through calls to <code>::CrFwInFactoryReleaseInRep</code>.
 * @return the number of InReports  which are currently allocated.
 */
CrFwInFactoryPoolIndex_t CrFwInFactoryGetNOfAllocatedInRep();

/**
 * Return the maximum number of InReports which may be allocated at any one time.
 * @return the maximum number of InReports which may be allocated at any one time
 */
CrFwInFactoryPoolIndex_t CrFwInFactoryGetMaxNOfInRep();

/**
 * Return the number of InCommands which are currently allocated.
 * This function returns the number of InCommands which have been successfully
 * allocated through calls to <code>::CrFwInFactoryMakeInCmd</code> and have not yet been
 * released through calls to <code>::CrFwInFactoryReleaseInCmd</code>.
 * @return the number of InCommands which are currently allocated.
 */
CrFwInFactoryPoolIndex_t CrFwInFactoryGetNOfAllocatedInCmd();

/**
 * Return the maximum number of InCommands which may be allocated at any one time.
 * @return the maximum number of InCommands which may be allocated at any one time
 */
CrFwInFactoryPoolIndex_t CrFwInFactoryGetMaxNOfInCmd();

#endif /* CRFW_INFACTORY_H_ */
