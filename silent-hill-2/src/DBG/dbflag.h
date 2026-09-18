#ifndef DBFLAG_H
#define DBFLAG_H

#include "common.h"

int dbFlagReserve(u_int flag /* r2 */, char* explain_message /* r2 */);

u_int dbFlag(u_int flag /* r2 */);

void dbFlagSet(u_int flag /* r2 */);

#endif // DBFLAG_H
