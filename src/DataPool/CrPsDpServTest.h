/**
 * @file CrPsDpServTest.h
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
/* Type description*/
typedef struct {
	unsigned short AreYouAliveSrc; 
	unsigned int AreYouAliveTimeOut;
	unsigned short OnBoardConnectDest;
	unsigned short OnBoardConnectDestLst[10];
} DpServTest_t;

/* Variable description*/
extern DpServTest_t dpServTest;

/**
 * Get the Value from the Datapool item AreYouAliveSrc.
 * @return the Value of AreYouAliveSrc from the Datapool
 */
static inline unsigned short getDpAreYouAliveSrc()
{
	return dpServTest.AreYouAliveSrc;
}

/**
 * Sets the Value from the Datapool item AreYouAliveSrc.
 * @param AreYouAliveSrc The Value that should be stored into the Datapool
 */
static inline void setDpAreYouAliveSrc(unsigned short AreYouAliveSrc)
{
	dpServTest.AreYouAliveSrc = AreYouAliveSrc;
}

/**
 * Get the Value from the Datapool item AreYouAliveTimeOut.
 * @return the Value of AreYouAliveTimeOut from the Datapool
 */
static inline unsigned int getDpAreYouAliveTimeOut()
{
	return dpServTest.AreYouAliveTimeOut;
}

/**
 * Sets the Value from the Datapool item AreYouAliveTimeOut.
 * @param AreYouAliveTimeOut The Value that should be stored into the Datapool
 */
static inline void setDpAreYouAliveTimeOut(unsigned int AreYouAliveTimeOut)
{
	dpServTest.AreYouAliveTimeOut = AreYouAliveTimeOut;
}

/**
 * Get the Value from the Datapool item OnBoardConnectDest.
 * @return the Value of OnBoardConnectDest from the Datapool
 */
static inline unsigned short getDpOnBoardConnectDest()
{
	return dpServTest.OnBoardConnectDest;
}

/**
 * Sets the Value from the Datapool item OnBoardConnectDest.
 * @param OnBoardConnectDest The Value that should be stored into the Datapool
 */
static inline void setDpOnBoardConnectDest(unsigned short OnBoardConnectDest)
{
	dpServTest.OnBoardConnectDest = OnBoardConnectDest;
}

/**
 * Get the Value from the Datapool array OnBoardConnectDestLst.
 * @return the Value of OnBoardConnectDestLst[0] from the Datapool
 */
static inline unsigned short* getDpOnBoardConnectDestLstArray()
{
	return &dpServTest.OnBoardConnectDestLst[0];
}

/**
 * Get the Value from the Datapool array item OnBoardConnectDestLst.
 * @param i the identifier of the array item
 * @return the Value of OnBoardCo?
 */
static inline unsigned short getDpOnBoardConnectDestLstItem(int i)
{
	return dpServTest.OnBoardConnectDestLst[i];
}

/** 
 * Sets the Value from the Datapool array item OnBoardConnectDestLst.
 * @param i the identifier of the array item
 * @param OnBoardConnectDestLst The Value that should be stored into the Datapool
 */
static inline void setDpOnBoardConnectDestLstItem(int i, unsigned short OnBoardConnectDestLst)
{
	dpServTest.OnBoardConnectDestLst[i] = OnBoardConnectDestLst;
}