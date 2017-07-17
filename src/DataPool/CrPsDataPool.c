/**
 * @file CrPsDataPool.c
 * 
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
 * @author P&P Software GmbH / Department of Astrophysics, University of Vienna
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

/**
* Generated on 2017-06-06 16:26:33
*/
#include <stdlib.h>
#include <string.h>

#include "CrPsDataPool.h"
#include "CrPsDpServTest.h"

typedef struct {
	void* addr;
	size_t length;
} DpMetaInfoEntry_t;

static DpMetaInfoEntry_t dpMetaInfo[] = {
	{(void*)&dpServTest.AreYouAliveSrc,        sizeof(dpServTest.AreYouAliveSrc)       },
	{(void*)&dpServTest.AreYouAliveTimeOut,    sizeof(dpServTest.AreYouAliveTimeOut)   },
	{(void*)&dpServTest.OnBoardConnectDest,    sizeof(dpServTest.OnBoardConnectDest)   },
	{(void*)&dpServTest.OnBoardConnectDestLst, sizeof(dpServTest.OnBoardConnectDestLst)},
};

/* ------------------------------------------------------------------------------------ */
void getDpValue(DatapoolId_t id, void* dest)
{
	DpMetaInfoEntry_t* entry;
	entry = &dpMetaInfo[id];
	(void)memcpy(dest, entry->addr, entry->length);
}

/* ------------------------------------------------------------------------------------ */
void setDpValue(DatapoolId_t id, const void* src)
{
	DpMetaInfoEntry_t* entry;
	entry = &dpMetaInfo[id];
	(void)memcpy(entry->addr, src, entry->length);
}
