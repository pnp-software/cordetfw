/**
 * @file
 * This header file declares the function to create one instance of the CrPsCmd3s3Start procedure.
 * The procedure is configured with a set of function pointers representing the non-default
 * actions and guards of the procedure. Some of these functions may also be declared in
 * this header file in accordance with the configuration of the procedure in the FW Profile
 * Editor. In the latter case, the user has to provide an implementation for these functions
 * in a user-supplied body file.
 *
 * This header file has been automatically generated by the FW Profile Editor.
 * The procedure created by this file is shown in the figure below.
 * @image html CrPsCmd3s3Start.png
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:15:26
 */

/** Make sure to include this header file only once */
#ifndef CRPSCMD3S3START_H_
#define CRPSCMD3S3START_H_

/** FW Profile function definitions */
#include "FwPrConstants.h"

/** Action node identifiers */
#define CrPsCmd3s3Start_N1 (1)		/* The identifier of action node N1 in procedure CrPsCmd3s3Start */
#define CrPsCmd3s3Start_N2 (2)		/* The identifier of action node N2 in procedure CrPsCmd3s3Start */
#define CrPsCmd3s3Start_N3 (3)		/* The identifier of action node N3 in procedure CrPsCmd3s3Start */
#define CrPsCmd3s3Start_N4 (4)		/* The identifier of action node N4 in procedure CrPsCmd3s3Start */
#define CrPsCmd3s3Start_N5 (5)		/* The identifier of action node N5 in procedure CrPsCmd3s3Start */
#define CrPsCmd3s3Start_N6 (6)		/* The identifier of action node N6 in procedure CrPsCmd3s3Start */
#define CrPsCmd3s3Start_N7 (7)		/* The identifier of action node N7 in procedure CrPsCmd3s3Start */
#define CrPsCmd3s3Start_N8 (8)		/* The identifier of action node N8 in procedure CrPsCmd3s3Start */

/**
 * Create a new procedure descriptor.
 * This interface creates the procedure descriptor dynamically.
 * @param prData the pointer to the procedure data.
 * A value of NULL is legal (note that the default value of the pointer
 * to the procedure data when the procedure is created is NULL).
 * @return the pointer to the procedure descriptor
 */
FwPrDesc_t CrPsCmd3s3StartCreate(void* prData);

/**
 * Action for node N1.
 * Set i equal to 1
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s3StartN1(FwPrDesc_t prDesc);

/**
 * Action for node N2.
 * <pre>
 * Load invalid SID in
 * data pool item verFailData
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s3StartN2(FwPrDesc_t prDesc);

/**
 * Action for node N3.
 * <pre>
 * Run Command Verification
 * Failure Procedure to generate (1,4) 
 * report with failure code VER_ILL_SID
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s3StartN3(FwPrDesc_t prDesc);

/**
 * Action for node N4.
 * Increment i
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s3StartN4(FwPrDesc_t prDesc);

/**
 * Action for node N5.
 * <pre>
 * Load the enabled
 * SID in data pool verFailData
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s3StartN5(FwPrDesc_t prDesc);

/**
 * Action for node N6.
 * <pre>
 * Run Command Verification
 * Failure Procedure to generate (1,4)
 * report with failure code VER_ENABLED_SID
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s3StartN6(FwPrDesc_t prDesc);

/**
 * Action for node N7.
 * <pre>
 * Set action
 * outcome to 'success'
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s3StartN7(FwPrDesc_t prDesc);

/**
 * Action for node N8.
 * <pre>
 * Set action outcome to 'failure'
 * with failure code VER_S3S_START_FD
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s3StartN8(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION1 to N2.
 * <pre>
 *  The i-th SID is not
 * in the RDL 
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s3StartG1(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION1 to DECISION2.
 *  Else 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s3StartG1E(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION2 to N5.
 * <pre>
 *  The i-th SID is
 * enabled in the RDL 
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s3StartG2(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION2 to DECISION3.
 *  Else 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s3StartG2E(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION3 to DECISION4.
 * <pre>
 *  The i-th SID was the last
 * SID in the command 
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s3StartG3(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION3 to N4.
 *  Else 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s3StartG3E(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION4 to N8.
 * <pre>
 *  All SIDs in the
 * command are invalid 
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s3StartG4(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION4 to N7.
 *  Else 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s3StartG4E(FwPrDesc_t prDesc);

#endif /* CrPsCmd3s3StartCreate_H_ */