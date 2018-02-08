/**
 * @file CrPsPktServHkSupp.h
 * @ingroup Serv3
 * @ingroup pktgetset
 *
 * @brief auxiliary Interface for accessing fields in packets of service "ServHk".
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

#ifndef CRPSPKTSERVHKSUPP_H_
#define CRPSPKTSERVHKSUPP_H_

#include "CrPsUserConstants.h"
#include "CrFwUserConstants.h"


/**
 * Get the offset of the "SCSampleRepNum" field in a HkCreate packet.
 * The offset depend on the "NFA" Value.
 * \param p Pointer to the packet.
 * \param NFA Value
 * \return the offset of the "NFA" th. "SCSampleRepNum" field.
 */
CrPsRepNum_t getHkCreateCmdOffsetSCS(void* p, CrFwCounterU4_t NFA);

/**
 * Get the offset of the "N2" field in a HkCreate packet.
 * The offset depend on the "NFA" Value.
 * \param p Pointer to the packet.
 * \param NFA Value
 * \return the offset of the "NFA" th. "N2" field.
 */
uint32_t getHkCreateCmdOffsetN2(void* p, CrFwCounterU4_t NFA);

/**
 * Get the offset of the "N2ParamId" field in a HkCreate packet.
 * The offset depend on the "NFA" and the N2 Value.
 * \param p Pointer to the packet.
 * \param NFA Value
 * \param N2 Value
 * \return the offset of the "NFA" th. Group and the "N2" th. N2ParamId field.
 */
uint32_t getHkCreateCmdOffsetN2ParamId(void* p, CrFwCounterU4_t NFA, CrFwCounterU4_t N2);

/**
 * Get "NFA" from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "NFA".
 */
CrFwCounterU4_t getHkCreateCmdNFA(void* p);

/**
 * Set "NFA" in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of "NFA" to be set in packet.
 */
void setHkCreateCmdNFA(void* p, CrFwCounterU4_t NFA);

/**
 * Get "N1ParamId" arrayItem from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of ParamIdArray Item.
 * \return N1ParamId Array Item Value.
 */
CrPsParamId_t getHkCreateCmdN1ParamIdItem(void* p, CrFwCounterU4_t N);

/**
 * Set "N1ParamId" arrayItem in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param N Value of the "N" th ParamIdArray Item.
 * \param N1ParamId Variable from where arrayItem data are copied.
 */
void setHkCreateCmdN1ParamIdItem(void* p, CrFwCounterU4_t N, CrPsParamId_t N1ParamId);

/**
 * Get "N2" from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \return Value of "N2".
 */
CrFwCounterU4_t getHkCreateCmdN2(void* p, CrFwCounterU4_t NFA);

/**
 * Set "N2" in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param N2 Value of "N2" to be set in packet.
 */
void setHkCreateCmdN2(void* p, CrFwCounterU4_t NFA, CrFwCounterU4_t N2);

/**
 * Get "SCSampleRepNum" from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \return Value of "SCSampleRepNum".
 */
CrPsRepNum_t getHkCreateCmdSCSampleRepNumItem(void* p, CrFwCounterU4_t NFA);

/**
 * Set "SCSampleRepNum" in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param SCSampleRepNum Value of "SCSampleRepNum" to be set in packet.
 */
void setHkCreateCmdSCSampleRepNumItem(void* p, CrFwCounterU4_t NFA, CrPsRepNum_t SCSampleRepNum);

/**
 * Get "N2ParamID" from "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param N2 Value of the "N2" th Item.
 * \return Value of "N2ParamID".
 */
CrPsParamId_t getHkCreateCmdN2ParamIdItem(void* p, CrFwCounterU4_t NFA, CrFwCounterU4_t N2);

/**
 * Set "N2ParamID" in "HkCreateCmd" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param N2 Value of the "N2" th Item.
 * \param N2ParamId Value of "N2ParamID" to be set in packet.
 */
void setHkCreateCmdN2ParamIdItem(void* p, CrFwCounterU4_t NFA, CrFwCounterU4_t N2, CrPsParamId_t N2ParamId);

/**
 * Get the offset of the "SCSampleRepNum" field in a HkRepStruct packet.
 * The offset depend on the "NFA" Value.
 * \param p Pointer to the packet.
 * \param NFA Value
 * \return the offset of the "NFA" th. "SCSampleRepNum" field.
 */
uint32_t getHkRepStructRepOffsetSCS(void* p, CrFwCounterU4_t NFA);

/**
 * Get the offset of the "N2" field in a HkRepStruct packet.
 * The offset depend on the "NFA" Value.
 * \param p Pointer to the packet.
 * \param NFA Value
 * \return the offset of the "NFA" th. "N2" field.
 */
uint32_t getHkRepStructRepOffsetN2(void* p, CrFwCounterU4_t NFA);

/**
 * Get the offset of the "N2ParamId" field in a HkCreate packet.
 * The offset depend on the "NFA" and the N2 Value.
 * \param p Pointer to the packet.
 * \param NFA Value
 * \param N2 Value
 * \return the offset of the "NFA" th. Group and the "N2" th. N2ParamId field.
 */
uint32_t getHkRepStructRepOffsetN2ParamId(void* p, CrFwCounterU4_t NFA, CrFwCounterU4_t N2);
/**
 * Get "NFA" from "HkCreateDiagParCmd" packet.
 * \param p Pointer to the packet.
 * \return Value of "NFA".
 */                    
CrFwCounterU4_t getHkRepStructRepNFA(void* p);
/**
 * Set "NFA" in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param src Value of "NFA" to be set in packet.
 */
void setHkRepStructRepNFA(void* p, CrFwCounterU4_t src);

/**
 * Get "N1ParamId" arrayItem from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param N Number of ParamIdArray Item.
 * \return N2ParamId "N" th Array Item Value.
 */
CrPsParamId_t getHkRepStructRepN1ParamIdItem(void* p, CrFwCounterU4_t N);
/**
 * Set "N1ParamId" arrayItem in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param N Number of ParamIdArray Item.
 * \param src Variable from where arrayItem data are copied.
 */
void setHkRepStructRepN1ParamIdItem(void* p, CrFwCounterU4_t N, CrPsParamId_t src);

/**
 * Get "N2" from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \return Value of "N2".
 */
CrFwCounterU4_t getHkRepStructRepN2(void* p, CrFwCounterU4_t NFA);

/**
 * Set "N2" in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param N2 Value of "N2" to be set in packet.
 */
void setHkRepStructRepN2(void* p, CrFwCounterU4_t NFA, CrFwCounterU4_t N2);

/**
 * Get "SCSampleRepNum" from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \return Value of "SCSampleRepNum".
 */
CrPsRepNum_t getHkRepStructRepSCSampleRepNumItem(void* p, CrFwCounterU4_t NFA);

/**
 * Set "SCSampleRepNum" in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param src Value of "SCSampleRepNum" to be set in packet.
 */
void setHkRepStructRepSCSampleRepNumItem(void* p, CrFwCounterU4_t NFA, CrPsRepNum_t src);
/**
 * Get "N2ParamID" from "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param N2 Value of the "N2" th Item.
 * \return Value of "N2ParamID".
 */
CrPsParamId_t getHkRepStructRepN2ParamIdItem(void* p, CrFwCounterU4_t NFA, CrFwCounterU4_t N2);

/**
 * Set "N2ParamID" in "HkRepStructRep" packet.
 * \param p Pointer to the packet.
 * \param NFA Value of the "NFA" th Group.
 * \param N2 Value of the "N2" th Item.
 * \param src Value of "N2ParamID" to be set in packet.
 */
void setHkRepStructRepN2ParamIdItem(void* p, CrFwCounterU4_t NFA, CrFwCounterU4_t N2, CrPsParamId_t src);

/**
 * Get "RepStrucId" from "HkDeleteCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \return Value of "RepStrucId" the "N" th Item of the array.
 */
CrPsSid_t getHkDeleteCmdRepStrucIdItem(void* p, CrFwCounterU4_t N);

/**
 * Set "RepStrucId" in "HkDeleteCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of ParamIdArray Item.
 * \param RepStrucId Value of "RepStrucId" to be set in packet.
 */
void setHkDeleteCmdRepStrucIdItem(void* p, CrFwCounterU4_t N, CrPsSid_t RepStrucId);

/**
 * Get "RepStrucId" from "HkEnableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of ParamIdArray Item.
 * \return Value of "RepStrucId" the "N" th Item of the array.
 */
CrPsSid_t getHkEnableCmdRepStrucIdItem(void* p, CrFwCounterU4_t N);

/**
 * Set "RepStrucId" in "HkEnableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \param RepStrucId Value of "RepStrucId" to be set in packet.
 */
void setHkEnableCmdRepStrucIdItem(void* p, CrFwCounterU4_t N, CrPsSid_t RepStrucId);

/**
 * Get "RepStrucId" from "HkDisableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \return Value of "RepStrucId" the "N" th Item of the array.
 */
CrPsSid_t getHkDisableCmdRepStrucIdItem(void* p, CrFwCounterU4_t N);

/**
 * Set "RepStrucId" in "HkDisableCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \param RepStrucId Value of "RepStrucId" to be set in packet.
 */
void setHkDisableCmdRepStrucIdItem(void* p, CrFwCounterU4_t N, CrPsSid_t RepStrucId);

/**
 * Get "RepStrucId" from "HkRepStructCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \return Value of "RepStrucId" the "N" th Item of the array.
 */
CrPsSid_t getHkRepStructCmdRepStrucIdItem(void* p, CrFwCounterU4_t N);

/**
 * Set "RepStrucId" in "HkRepStructCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \param RepStrucId Value of "RepStrucId" to be set in packet.
 */
void setHkRepStructCmdRepStrucIdItem(void* p, CrFwCounterU4_t N, CrPsSid_t RepStrucId);

/**
 * Get "RepStrucId" from "HkOneShotCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \return Value of "RepStrucId" the "N" th Item of the array.
 */
CrPsSid_t getHkOneShotCmdRepStrucIdItem(void* p, CrFwCounterU4_t N);

/**
 * Set "RepStrucId" in "HkOneShotCmd" packet.
 * \param p Pointer to the packet.
 * \param N Number of Array Item.
 * \param RepStrucId Value of "RepStrucId" to be set in packet.
 */
void setHkOneShotCmdRepStrucIdItem(void* p, CrFwCounterU4_t N, CrPsSid_t RepStrucId);

/*TODO INFO*/
size_t getHkRepStructSize(CrPsSid_t sid);

/*TODO INFO      ??? Never USED !!!  */ 
/*size_t getHkRepSizeFromDp(CrPsSid_t sid);*/

/*TODO INFO*/
size_t getHkRepSizeFromPckt(void* p);

/**
 * Get the size of a Housekeeping packet.
 * \param p Pointer to the packet.
 * \return the size of the packet in bytes.
 */
size_t getHkPcktSize(void* p);

/*----------------------------------------------------------------------------*/
#endif /* CRPSPKTSERVHKSUPP_H */
