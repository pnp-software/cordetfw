/**
 * @file CrPsPcktUtilities.h
 * @ingroup CrIaDemo
 *
 * 
 *
 * @author C. Reimers and M. Rockenbauer 19.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#ifndef CRPSPCKTUTILITIES_H
#define CRPSPCKTUTILITIES_H

#include "CrFwConstants.h"


/*Functions*/
/* ------------------------------------------------------------------------------------ */
unsigned short CrFwPcktGetSeqCtrl(CrFwPckt_t pckt);
void CrFwPcktSetSeqCtrl(CrFwPckt_t pckt, unsigned short psc);

unsigned short CrFwPcktGetApid(CrFwPckt_t pckt);
void CrFwPcktSetApid(CrFwPckt_t pckt, unsigned short apid);



#endif /* CRPSPCKTUTILITIES_H */
