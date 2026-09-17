#include "dbswitch.h"

extern /* static */ u_int dbSwitchStat[2]; // size: 0x8, address: 0x34C4A8
extern /* static */ int dbSwitchX; // size: 0x4, address: 0x11B6E48
extern /* static */ int dbSwitchY; // size: 0x4, address: 0x11B6E50
extern /* static */ int dbSwitchDispF; // size: 0x4, address: 0x11B6E58

void dbSwitchDispIndicator(int enable /* r2 */, int o /* r2 */, int x /* r2 */, int dx /* r2 */, int dy /* r2 */) {
    int just, bit, Y; // r2
    char* sym[2][2] = {"-\n", "\x8a-\n", "0\n", "\x8a\x4f\n"}; // r29+0x20

    if (enable) {

        dy = -dy;
        if (x || o) {

            dx = dy = 0;
        }

        if (x) dbSwitchDispF = !dbSwitchDispF;
        if (dbSwitchDispF) {

            dbSwitchX += dx;
            dbSwitchY += dy;
            if (dbSwitchX < 0)     dbSwitchX = 0;
            if (dbSwitchX > 1)     dbSwitchX = 1;
            if (dbSwitchY < 0)     dbSwitchY = 0;
            if (dbSwitchY > 31u)   dbSwitchY = 31;
            if (o) {
                dbSwitchStat[dbSwitchX] = dbSwitchStat[dbSwitchX] ^ 1 << dbSwitchY;
            }
            dbfntprintfR("%1X\n", dbSwitchX);

            for (just = 0; just < 32u; just++) {

                if (!(just % 8)) dbfntprintR("\n");

                bit = (dbSwitchStat[dbSwitchX] & 1 << just) != 0;
                Y = dbSwitchY == just;
                dbfntprintR(sym[bit][Y]);
            }
        }
    }
}




int dbSwitchDispEnable(int enable) {
    if (enable < 0) enable = dbSwitchDispF;
    else dbSwitchDispF = enable;
    return enable;
}

int dbSwitchInit(DBSW_ID _X, u_long bit_pattern) {
    int X;
    X = _X;

    if (X < DBSW_SYS) return 0;
    if (X > DBSW_MAP) return 0;

    dbSwitchStat[X] = bit_pattern;
    return 1;
}

int dbSwitchSet(DBSW_ID _X /* r2 */, int Y /* r2 */, int set /* r2 */) {
    int X;
    int *temp;
    X = _X;

    if (X < DBSW_SYS)   return 0;
    if (X > DBSW_MAP)   return 0;
    if (Y < 0)          return 0;
    if (Y > 31u)        return 0;

    if (set) {
        temp = &dbSwitchStat[X];
        SET_BIT(*temp, Y);
    } else {
        UNSET_BIT(dbSwitchStat[X], Y);
    }
    return 1;
}

int dbSwitch(DBSW_ID _X /* r2 */, int Y /* r2 */) {
    int X;
    X = _X;

    if (X < DBSW_SYS)   return 0;
    if (X > DBSW_MAP)   return 0;
    if (Y < 0)          return 0;
    if (Y > 31u)        return 0;

    if (dbSwitchDispF) {
        return (dbSwitchStat[X] & 1 << Y) != 0;
    }

    return 0;
}



int dbSwitchGetPos(int * Xp /* r2 */, int * Yp /* r2 */) {
    if (Xp) *Xp = dbSwitchX;
    if (Yp) *Yp = dbSwitchY;

    return dbSwitch(dbSwitchX, dbSwitchY);
}
