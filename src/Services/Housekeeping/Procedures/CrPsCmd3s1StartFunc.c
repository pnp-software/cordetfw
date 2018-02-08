/**
 * @file CrPsCmd3s1StartFunc.c
 * @ingroup Serv3
 * @ingroup procedures
 *
 * @brief Start Action for Commands (3,1) and (3,2) to create a new housekeeping/diagnostic report
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:15:26
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

/** CrPsCmd3s1Start function definitions */
#include "CrPsCmd3s1StartCreate.h"

/* CrFramework includes */
#include "Pckt/CrFwPckt.h"
#include "OutFactory/CrFwOutFactory.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"
#include "CrFwCmpData.h"

/** FW Profile function definitions */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"

#include <CrPsRepErr.h>
#include <CrPsUserConstants.h>
#include <DataPool/CrPsDpServReqVerif.h>
#include <DataPool/CrPsDpServHk.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServHk.h>
#include <Services/General/CrPsPktServHkSupp.h>

#include <stdlib.h>
#include <time.h>

static FwSmDesc_t rep;
static CrPsSid_t  rdlSlot;


/* ----------------------------------------------------------------------------------------------------------------- */

/** Action for node N1. */
void CrPsCmd3s1StartN1(FwPrDesc_t prDesc)
{
  CrFwCmpData_t       *cmpData;
  FwSmDesc_t           smDesc;

  /* Set action outcome to 'failure' with failure code VER_FULL_RDL */

  /* Get smDesc from OutCmp */
  smDesc = FwPrGetData(prDesc);

  /* Set outcome in InCmd prData to 'failure' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = (unsigned char)VER_FULL_RDL;
  FwSmSetData(smDesc, cmpData);

  return;
}

/** Action for node N2. */
void CrPsCmd3s1StartN2(FwPrDesc_t prDesc)
{
  CrFwCmpData_t       *cmpData;
  CrFwInCmdData_t     *cmpSpecificData;
  CrFwPckt_t           pckt;
  FwSmDesc_t           smDesc;
  CrFwServSubType_t    tcServSubType;
  CrPsSid_t            sid;

  /* Retrieve a report of type (3,25) or (3,26) from the OutFactory */

  /* Get smDesc from prData */
  smDesc = FwPrGetData(prDesc);

  /* Get inPckt */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get SubType */
  tcServSubType = CrFwPcktGetServSubType(pckt);

  /* Get SID */
  sid = getHkCreateCmdRepStrucId(pckt);

  /* Generate report of type (3,25) or (3,26) according to TC(3,1) or TC(3,2) */
  if (tcServSubType == CRPS_HK_CREATE_HKSTRUCT_CMD)
    {
      rep  = CrFwOutFactoryMakeOutCmp(CRPS_HK, CRPS_HK_HKPARAM_REP, sid, getHkRepSizeFromPckt(pckt)); /* arguments: type, subType, discriminant/evtId, length */
    }
  else if (tcServSubType == CRPS_HK_CREATE_DIAGSTRUCT_CMD)
    {
      rep  = CrFwOutFactoryMakeOutCmp(CRPS_HK, CRPS_HK_DIAGPARAM_REP, sid, getHkRepSizeFromPckt(pckt)); /* arguments: type, subType, discriminant/evtId, length */
    }

  return;
}

/** Action for node N3. */
void CrPsCmd3s1StartN3(FwPrDesc_t prDesc)
{
  CrPsRepErrCode_t errCode;
  CRFW_UNUSED(prDesc);

  /* Generate error report OUTFACTORY_FAIL */

  errCode = crOutfactoryFail;
  CrPsRepErr(errCode, CRPS_REQVERIF, CRPS_REQVERIF_PROG_FAIL, 0);

  return;
}

/** Action for node N4. */
void CrPsCmd3s1StartN4(FwPrDesc_t prDesc)
{
  CrFwCmpData_t       *cmpData;
  CrFwInCmdData_t     *cmpSpecificData;
  CrFwPckt_t           pckt;  
  FwSmDesc_t           smDesc;
  CrFwDestSrc_t dest;
  
  /* Load the report in the OutLoader */

  smDesc = FwPrGetData(prDesc);

  /* Get inPckt */
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt = cmpSpecificData->pckt;

  dest = CrFwPcktGetSrc(pckt);
  CrFwOutCmpSetDest(rep, dest);

  CrFwOutLoaderLoad(rep);

  return;
}

/** Action for node N6. */
void CrPsCmd3s1StartN6(FwPrDesc_t prDesc)
{
  CrFwCmpData_t       *cmpData;
  FwSmDesc_t           smDesc;

  /* Set action outcome to 'success' */

  /* Get smDesc from OutCmp */
  smDesc = FwPrGetData(prDesc);

  /* Set outcome in InCmd prData to 'success' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = 1;
  FwSmSetData(smDesc, cmpData);

  return;
}

/** Action for node N7. */
void CrPsCmd3s1StartN7(FwPrDesc_t prDesc)
{
  CrFwCmpData_t       *cmpData;
  CrFwInCmdData_t     *cmpSpecificData;
  CrFwPckt_t           pckt;    
  FwSmDesc_t           smDesc;
  CrPsSid_t            sid;

  /* Set action outcome to 'failure' with code VER_SID_IN_USE and load SID in verFailData data pool item */

  /* Get smDesc from OutCmp */
  smDesc = FwPrGetData(prDesc);

  /* Set outcome in InCmd prData to 'failure' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = (unsigned char)VER_SID_IN_USE;
  FwSmSetData(smDesc, cmpData);

  /* Get inPckt */
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get SID from inPckt */
  sid = getHkCreateCmdRepStrucId(pckt);  

  /* Load SID in verFailData data pool item */
  setDpverFailData((uint32_t)sid);

  return;
}

/** Action for node N8. */
void CrPsCmd3s1StartN8(FwPrDesc_t prDesc)
{
  CrFwCmpData_t       *cmpData;
  FwSmDesc_t           smDesc;

  /* Set action outcome to 'failure' with failure code VER_RDL_CONSTR and load identifier of constraint in verFailData */

  /* Get smDesc from OutCmp */
  smDesc = FwPrGetData(prDesc);

  /* Set outcome in InCmd prData to 'failure' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = (unsigned char)VER_RDL_CONSTR;
  FwSmSetData(smDesc, cmpData);

  /* Load identifier of constraint in verFailData */
  setDpverFailData((CrFwCounterU4_t)VER_RDL_CONSTR);

  return;
}

/** Action for node N9. */
void CrPsCmd3s1StartN9(FwPrDesc_t prDesc)
{
  CrFwCmpData_t       *cmpData;
  FwSmDesc_t           smDesc;

  /* Set action outcome to 'failure' with code VER_DUPL_DI and load identifier of duplicated DI in verFailData */

  /* Get smDesc from OutCmp */
  smDesc = FwPrGetData(prDesc);

  /* Set outcome in InCmd prData to 'failure' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = (unsigned char)VER_DUPL_DI;
  FwSmSetData(smDesc, cmpData);

  /* Load identifier of duplicated DI in verFailData */
  setDpverFailData((CrPsFailData_t)VER_DUPL_DI);

  return;
}

/** Action for node N10. */
void CrPsCmd3s1StartN10(FwPrDesc_t prDesc)
{
  CrFwCmpData_t       *cmpData;
  FwSmDesc_t           smDesc;

  /* Set action outcome to 'failure' with failure code VER_REP_CR_FD */

  /* Get smDesc from OutCmp */
  smDesc = FwPrGetData(prDesc);

  /* Set outcome in InCmd prData to 'failure' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = (unsigned char)VER_REP_CR_FD;
  FwSmSetData(smDesc, cmpData);

  return;
}

/** Action for node N11. */ /* TODO (01.02.2018): cannot be reached due to Guard always returns 1 */
void CrPsCmd3s1StartN11(FwPrDesc_t prDesc)
{
  CrFwCmpData_t       *cmpData;
  FwSmDesc_t           smDesc;

  /* Set action outcome to 'failure' with falure code VER_OUTLOADER_FD */

  /* Get smDesc from OutCmp */
  smDesc = FwPrGetData(prDesc);

  /* Set outcome in InCmd prData to 'failure' */ 
  cmpData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpData->outcome = (unsigned char)VER_OUTLOADER_FD;
  FwSmSetData(smDesc, cmpData);

  return;
}

/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION1 to N1. */
FwPrBool_t CrPsCmd3s1StartG1(FwPrDesc_t prDesc)
{
  CrPsSid_t rdlSid;

  CRFW_UNUSED(prDesc);
  /* There is no free slot in the RDL  */

  /* look for a free slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {
      rdlSid = getDpsidItem(rdlSlot);
      
      if (rdlSid == 0)
        break;
    }

  if (rdlSlot == HK_N_REP_DEF)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/** Guard on the Control Flow from DECISION2 to N8. */
FwPrBool_t CrPsCmd3s1StartG2(FwPrDesc_t prDesc)
{
  CrFwCmpData_t        *cmpData;
  CrFwInCmdData_t      *cmpSpecificData;
  CrFwPckt_t            pckt;  
  FwSmDesc_t            smDesc;
  CrPsSid_t             sid;
  CrFwCounterU4_t       N1;

  /* One or more constraints listed in table 9.1 are not satisfied */

  /* Get smDesc from prData */
  smDesc = FwPrGetData(prDesc);

  /* Get in data */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get sid and check: Integer in range: 1..HK_MAX_SID */
  sid = getHkCreateCmdRepStrucId(pckt);
  if ((sid == 0) || (sid > HK_MAX_SID))
    return 1;

  /* Get nSimple and check: Integer in range: 1..HK_MAX_N_SIMPLE */
  N1 = getHkCreateCmdN1(pckt);
  if ((N1 == 0) || (N1 > HK_MAX_N_SIMPLE))
    return 1;

  return 0;
}

/** Guard on the Control Flow from DECISION3 to N7. */
FwPrBool_t CrPsCmd3s1StartG3(FwPrDesc_t prDesc)
{
  CrFwCmpData_t       *cmpData;
  CrFwInCmdData_t     *cmpSpecificData;
  CrFwPckt_t           pckt;  
  FwSmDesc_t           smDesc;
  CrPsSid_t            rdlSid, sid;

  /* The SID in the command is already in use  */
 
  /* Get smDesc from prData */
  smDesc = FwPrGetData(prDesc);

  /* Get in data */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get sid */
  sid = getHkCreateCmdRepStrucId(pckt);

  /* look for the same sid in RDL */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {
      rdlSid = getDpsidItem(rdlSlot);
      
      if (rdlSid == sid)
        break;
    }

  if (rdlSlot == HK_N_REP_DEF)
    {
      return 0;
    }
  else
    {
      return 1;
    }
}

/** Guard on the Control Flow from DECISION4 to N9. */
FwPrBool_t CrPsCmd3s1StartG4(FwPrDesc_t prDesc)
{
  CrFwCmpData_t       *cmpData;
  CrFwInCmdData_t     *cmpSpecificData;
  CrFwPckt_t           pckt;  
  FwSmDesc_t           smDesc;
  uint16_t             currentDataItem, checkDataItem;
  CrFwCounterU4_t      i, k, m, a=0;
  CrFwCounterU4_t      N1, NFA, N2[10], LSTNMB; /* TODO: set maximum as constant */
  unsigned short       dataItemArray[100];      /* TODO: set maximum as constant */

  /* The same data item identifier appears twice in the definition of the new report  */

  /* Get smDesc from prData */
  smDesc = FwPrGetData(prDesc);

  /* Get in data */
  cmpData         = (CrFwCmpData_t*)FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;

  /* Get N1 and NFA */
  N1 = getHkCreateCmdN1(pckt); /* nSimple */
  NFA = getHkCreateCmdNFA(pckt); /* number of groups */

  /* Calculate number of data items: only nSimple items ... */
  LSTNMB = N1;

  /* Get N2 NFA times; NFA is number of groups (nGroup) */
  for (i=0; i<NFA; i++)
    {
      N2[i] = getHkCreateCmdN2(pckt, i+1); /* nRep[GroupX] */
      /* ... add super-cummutated group items */
      LSTNMB += N2[i];
    } 

  /* Collect all data items in an array */
  for (k=0; k<N1; k++)
    {
      dataItemArray[k] = getHkCreateCmdN1ParamIdItem(pckt, k+1);
    }

  for (k=0; k<NFA; k++)
    {
      for (m=0; m<N2[k]; m++)
        {
          dataItemArray[N1+a] = getHkCreateCmdN2ParamIdItem(pckt, k+1, m+1);
          a+=1;
        }
    }

  /* Go through all data item identifiers */
  for (i=0; i<LSTNMB; i++)
    {
      /* Get next data item */
      checkDataItem = dataItemArray[i];
      
      for(k=0;k<LSTNMB-i-1;k++)
        {
          /* Get next data item identifiers coming afterwards */
          currentDataItem = dataItemArray[i+k+1];

          /* Compare with data item identifiers */
          if (checkDataItem == currentDataItem)
            return 1;
        }
    }

  return 0;
}

/** Guard on the Control Flow from DECISION5 to N3. */
FwPrBool_t CrPsCmd3s1StartG5(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* Factory fails to return the report  */

  if (rep == NULL)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/** Guard on the Control Flow from DECISION6 to N6. */
FwPrBool_t CrPsCmd3s1StartG6(FwPrDesc_t prDesc)
{
  CRFW_UNUSED(prDesc);

  /* Load Operation is successful   */
  /* TBV: could this be done with checking the numberOfPendingOutCmp */
  /* make a Ticket!! ??? application Error ??? */

  return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */

