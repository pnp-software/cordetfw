/**
 * @file DpServTest.c
 * ???
 * Interface for accessing data pool items.
 *
 * A data pool is created by three structures encapsulating data related
 * to CORDET Framework and the PUS Extension to the CORDET Framework
 *
 * The data pool items can be also accessed by provided functions. These function
 * allows reading and modifying the data pool items by an unique identifier.
 *
 * Data items in the data pool may be either of primitive type or of array type.
 * To each data item a multiplicity is associated.
 * If the multiplicity is equal to 1, then the data item is of primitive type.
 * If the multiplicity is greater than 1, then the data type is of array type
 * and the multiplicity is the size of the array.
 *
 * @note This code was generated.
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

/**
* Generated on 2017-06-06 16:26:33
*/
#include "DpServTest.h"

DpServTest_t dpServTest;
