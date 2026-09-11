#ifndef DBSWITCH_H
#define DBSWITCH_H

typedef enum DBSW_ID {
    DBSW_SYS = 0,
    DBSW_MAP = 1,
    DB_SWITCH_MAX = 2,
} DBSW_ID;

int dbSwitchSet(DBSW_ID _X /* r2 */, int Y /* r2 */, int set /* r2 */);

int dbSwitch(enum DBSW_ID _X /* r2 */, int Y /* r2 */);

#endif // DBSWITCH_H
