#ifndef DBSW_SYS_H
#define DBSW_SYS_H

#include "common.h"
#include "SH2_common/pad.h"
#include "DBG/dbswitch.h"
#include "Multi_thr/loadinit/loadinit.h"
#include "Multi_thr/pad/keydata.h"
#include "shPad/lib_sh_pad.h"
//@note: for RTC struct. Probably not a very appropriate include
#include "Multi_thr/filesys/sh_cdvd.h"

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
