/**
 * @file CrPsUserConstants.h
 * @ingroup CrIaDemo
 *
 * Header file to define all user-configurable constants and types for the IASW
 * Application.
 *
 * The content of this file is taken over unchanged from the framework-provided
 * default with the exception of the following items:
 *
 *  - The value of the application identifier (20 for the IASW).
 *  - The maximum value of the service type, sub-type and discriminant
 *    attributes
 *
 * @authors V. Cechticky and A. Pasetti
 * edited: Markus Rockenbauer
 * 25.04.2017
 * @copyright P&P Software GmbH, 2014
 */

#ifndef CRPS_USERCONSTANTS_H_
#define CRPS_USERCONSTANTS_H_


/**
 * Identifier for the errors reported through the error reporting interface of <code>CrFwRepErr.h</code>.
 * When a framework component encounters a non-nominal situation during its normal operation,
 * it reports it as an error using the services defined by the <code>CrFwRepErr.h</code>
 * interface.
 * Each error situation is characterized by an error code.
 * This enumerated type defines all the error codes.
 */
typedef enum
{
  /** The Inloader acceptance of a component failed (see <code>CrPsRepErr.h</code>) */
  crInloaderAccFail = 2,
  /** The Inloader detects an invalid destination (see <code>CrPsRepErr.h</code>) */
  crInloaderInvDest = 3,
  /** The Outfactory failed to make the component (see <code>CrPsRepErr.h</code>) */
  crOutfactoryFail = 4
} CrPsRepErrCode_t;


#endif /* CRPS_USERCONSTANTS_H_ */
