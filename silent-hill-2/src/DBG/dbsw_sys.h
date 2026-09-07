#ifndef DBSW_SYS_H
#define DBSW_SYS_H

// total size: 0x14
typedef struct CmdServStat {
    // Members
     int qsize; // offset 0x0, size 0x4
     int qlen; // offset 0x4, size 0x4
     int id; // offset 0x8, size 0x4
     int last_id; // offset 0xC, size 0x4
     int clen; // offset 0x10, size 0x4
} CmdServStat;

// total size: 0x8
typedef struct timeDate/* @anon0 */ {
    // Members
    u_char stat; // offset 0x0, size 0x1
    u_char second; // offset 0x1, size 0x1
    u_char minute; // offset 0x2, size 0x1
    u_char hour; // offset 0x3, size 0x1
    u_char pad; // offset 0x4, size 0x1
    u_char day; // offset 0x5, size 0x1
    u_char month; // offset 0x6, size 0x1
    u_char year; // offset 0x7, size 0x1
} timeDate;

typedef union shGameKeyData {
    u_long bit; // offset 0x0, size 0x4
    // total size: 0x8
    struct /* @anon1 */ {
        // Members
        u_long type : 1; // offset 0x0, size 0x4
        u_long DRINK : 1; // offset 0x0, size 0x4
        u_long RADIO : 1; // offset 0x0, size 0x4
        u_long LIGHT : 1; // offset 0x0, size 0x4
        u_long ITEM : 1; // offset 0x0, size 0x4
        u_long MAP : 1; // offset 0x0, size 0x4
        u_long DECIDE : 1; // offset 0x0, size 0x4
        u_long CANCEL : 1; // offset 0x0, size 0x4
        u_long SKIP : 1; // offset 0x0, size 0x4
        u_long PAUSE : 1; // offset 0x0, size 0x4
        u_long ACTION : 2; // offset 0x0, size 0x4
        u_long DASH : 2; // offset 0x0, size 0x4
        u_long LSLIDE : 2; // offset 0x0, size 0x4
        u_long RSLIDE : 2; // offset 0x0, size 0x4
        u_long READY : 2; // offset 0x0, size 0x4
        u_long VIEW : 2; // offset 0x0, size 0x4
        u_long frame_m1 : 2; // offset 0x0, size 0x4
        long AX : 4; // offset 0x0, size 0x4
        long AY : 4; // offset 0x0, size 0x4
        long BX : 2; // offset 0x0, size 0x4
        long BY : 2; // offset 0x0, size 0x4
        long CX : 4; // offset 0x0, size 0x4
        long CY : 4; // offset 0x0, size 0x4
        u_long reserve : 2; // offset 0x0, size 0x4
        u_long trg : 1; // offset 0x0, size 0x4
        u_long rpt : 1; // offset 0x0, size 0x4
        u_long len : 16; // offset 0x0, size 0x4
    } f; // offset 0x0, size 0x8
} shGameKeyData;

char * dbSwitchSysHelp(int Y /* r2 */);

static int dbSwitchSys(int Y /* r2 */);

static void dbSwitchSetSys(int Y /* r2 */, int on /* r2 */);

static void printR_date(void);

static void printR_cmdserv(CmdServStat* stat /* r18 */, char* prefix /* r17 */, int* exec /* r2 */);

static void printR_fileserv(void);

static void printR_loadinit(void);

static void printR_test(void);

static void printR_padstep(int port /* r8 */, int slot /* r2 */);

static void printR_paddata(char* paddata /* r2 */);

static void printR_keydata(shGameKeyData* key /* r16 */);

static void printR_padport(int port /* r22 */, int slot /* r21 */, int pad_normalize /* r20 */, int pad_adjust /* r19 */, int dispstep /* r18 */, int disppad /* r17 */, int dispkey /* r16 */);

static void printR_pad00(void);

static void printR_pad10(void);

static void printR_lang(void);

void dbSwitchSysPrint(void);

int dbSwitchSysPrintHelp(void);

int dbSwitchSysPadPort(void);

int dbSwitchSysPrintAllPages(void);

int dbSwitchSysPrintNotOnlyPort1(void);

void dbSwitchSysInit(void);

#endif // DBSW_SYS_H
