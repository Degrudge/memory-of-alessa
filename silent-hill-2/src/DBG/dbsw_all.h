#ifndef DBSW_ALL_H
#define DBSW_ALL_H

#include "SH2_common/pad.h"
#include "DBG/dbsw_sys.h"
#include "DBG/dbswitch.h"

void dbSwitchAllInit(signed int enable /* r16 */);

static void dbSwitchHelpPrint();

int dbSwitchIsVisible();

void dbSwitchAllPrint();



#endif // DBSW_ALL_H
