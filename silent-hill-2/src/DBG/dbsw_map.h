#ifndef DBSW_MAP_H
#define DBSW_MAP_H

#include "common.h"

#include "DBG/dbsw_sys.h"
#include "DBG/dbswitch.h"

char* dbSwitchMapHelp(int Y /* r2 */);

static int dbSwitchMap(int Y /* r2 */);

static void printR_mapblock(void);

static void init_map(int i /* r2 */);

void dbSwitchMapPrint(void);

void dbSwitchMapInit(void);

#endif // DBSW_MAP_H
