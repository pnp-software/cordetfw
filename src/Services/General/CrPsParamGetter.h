/**
 * @file CrPsParamGetter.h
 *
 * Declaration of the getter operations for all parameters of all in-coming packets.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#ifndef CRPS_PARAM_GETTER_H
#define CRPS_PARAM_GETTER_H

#include <Pckt/CrFwPckt.h>
#include <CrFwConstants.h>


/**
 * Gets the value of the parameter Application Id of the Test On-Board Connection Report packet.
 * @param appId ID to the parameter that will be filled with data from the packet.
 * @param pckt Pointer to the packet.
 */
void CrPsServTestOnBoardConnectParamGetAppId(unsigned short * appId, CrFwPckt_t pckt);
unsigned int CrPsGetUIntValue(FwSmDesc_t smDesc, unsigned int pos);
unsigned short CrPsGetUShortValue(FwSmDesc_t smDesc, unsigned int pos);
unsigned char CrPsGetUCharValue(FwSmDesc_t smDesc, unsigned int pos);

#endif /* CRPS_PARAM_GETTER_H */
