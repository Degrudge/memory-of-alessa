#include "DBG/dbsw_sys.h"
#include "dbsw_sys.h"

#pragma divbyzerocheck off

char* dbSwitchSysHelp(int Y /* r2 */) {
    char* help;

    help = NULL;
    switch (Y) {
        case 0:
            return "display this help";
        case 1:
            return "enable pad port for debug";
        case 2:
            return "display switch indicator not-only port 1";
        case 3:
            return "display all switch pages";
        case 4:
            return "display RTC";
        case 5:
            return "display File Server status";
        case 6:
            return "display Load and Init command Server Status";
        case 7:
            return "verbose at command server status";
        case 8:
            return "display default language by ps2 system configuration";
        case 19:
            return "display special characters(0x20-0x9F)";
        case 9:
            return "display allinfo at pad(0,0)";
        case 10:
            return "display pad step at pad(0,0)";
        case 11:
            return "display paddata at pad(0,0)";
        case 12:
            return "display keydata at pad(0,0)";
        case 13:
            return "display allinfo at pad(1,0)";
        case 14:
            return "display pad step at pad(1,0)";
        case 15:
            return "display paddata at pad(1,0)";
        case 16:
            return "display keydata at pad(1,0)";
        case 17:
            return "semaphore param.";
        case 18:
            return "thread param.";
        case 30:
            return "debug menu from soft reset.";
        case 31:
            help = "movie dummy step.";
        /* fallthrough */
        default:
            return help;
    }
}

static int dbSwitchSys(int Y /* r2 */) {
    return dbSwitch(0, Y);
}

static void dbSwitchSetSys(int Y /* r2 */, int on /* r2 */) {
    dbSwitchSet(0, Y, on);
}

// thanks: Bl00D4NGEL
static void printR_date(void) {
    int var;
    char* str; // r16
    Old_Rtc rtc[1];
    char strbuf[32]; // r29+0x20

    shCdReadClock(&rtc);
    str = strbuf;
    str += sh2ScfMakeDateStrByLocalTimeFromJST(strbuf, &rtc);
    str += sprintf(str, " ");
    sh2ScfMakeTimeStrByLocalTimeFromJST(str, &rtc);
    dbfntprintfR("%s\n", strbuf);
}

static void printR_cmdserv(CmdServStat* stat /* r18 */, char* prefix /* r17 */, signed int* exec /* r2 */) {
    char sym, syms[4] = {'|', '/', '-', '\\'};
    sym = ' ';
    if (exec != NULL) {
        if (stat->clen != 0) {
            sym = syms[(++*exec) % 4];
        } else {
            *exec = 0;
        }
    }
    dbfntprintfR(
        dbSwitchSys(7)
            ? "%s: %3d%1c(%03d-%03d) (%3d/%3d)\n"
            : "%s: %3d%1c\n",
        prefix,
        stat->clen % 1000,
        sym,
        stat->id % stat->clen,
        stat->last_id % stat->clen,
        stat->qlen % stat->clen,
        stat->qsize % stat->clen);
}
// thanks: Sassy Gaur (Anon)
static void printR_fileserv(void) {
    CmdServStat stat[1]; // r29+0x10
    static int exec[1];  // @ 0x0034DB98 // >:\

    fsGetStat(stat);
    printR_cmdserv(stat, "fs", exec);
}

static void printR_loadinit(void) {
    CmdServStat stat[1]; // r29+0x10
    static int exec[1];  // @ 0x0034DB98 // >:\

    lisGetStat(stat);
    printR_cmdserv(stat, "lis", exec);
}

static void printR_test(void) {
    dbfntprintR("[ !\"#$%&' ()*+,-./]\n[01234567 89:;<=>?]\n[@ABCDEFG HIJKLMNO]\n[PQRSTUVW XYZ[\\]^_]\n[`abcdefg hijklmno]\n[pqrstuvw xyz{|}~\x7F]\n[\x80\x81\x82\x83\x84\x85\x86\x87 \x88\x89\x8A\x8B\x8C\x8D\x8E\x8F]\n[\x90\x91\x92\x93\x94\x95\x96\x97 \x98\x99\x9A\x9B\x9C\x9D\x9E\x9F]\n");
}

static void printR_padstep(int port /* r8 */, int slot /* r2 */) {
    dbfntprintfR("pad(%d,%d) trans step: %04x\n", port, slot, libShPadStep[port][slot]);
}
INCLUDE_ASM("asm/nonmatchings/DBG/dbsw_sys", printR_paddata);

static void printR_keydata(shGameKeyData* key /* r16 */) {

    dbfntprintfR("type:%1d  DRINK:%1d\nRADIO:%1d  LIGHT:%1d\nITEM:%1d    MAP:%1d\nDECIDE:%1d CANCEL:%1d\n",
                 key->f.type,
                 key->f.DRINK,
                 key->f.RADIO,
                 key->f.LIGHT,
                 key->f.ITEM,
                 key->f.MAP,
                 key->f.DECIDE,
                 key->f.CANCEL);
    dbfntprintfR("SKIP:%1d  PAUSE:%1d\nACTION:%1d   DASH:%1d\nLSLIDE:%1d RSLIDE:%1d\nREADY:%1d   VIEW:%1d\n",
                 key->f.SKIP,
                 key->f.CANCEL,
                 key->f.ACTION,
                 key->f.DASH,
                 key->f.LSLIDE,
                 key->f.RSLIDE,
                 key->f.READY,
                 key->f.VIEW);
    dbfntprintfR("A(X,Y):(%+1d,%+1d)\nB(X,Y):(%+1d,%+1d)\nC(X,Y):(%+1d,%+1d)\nlen:%5d\n",
                 key->f.AX,
                 key->f.AY,
                 key->f.BX,
                 key->f.BY,
                 key->f.CX,
                 key->f.CY,
                 key->f.len);
}

static void printR_padport(int port /* r22 */, int slot /* r21 */, int pad_normalize /* r20 */, int pad_adjust /* r19 */, int dispstep /* r18 */, int disppad /* r17 */, int dispkey /* r16 */) {
    shGameKeyData key[1]; // r29+0xA8
    u_char paddata[32];   // r29+0x80

    if (disppad || dispkey) {
        libShPadRead(port, slot, paddata);
        if (pad_normalize) {
            shSysKeyNormalize(paddata);
        }
        if (pad_adjust) {
            shSysKeyAdjust(paddata);
        }
    }
    if (dispstep) {
        printR_padstep(port, slot);
    }
    if (disppad) {
        printR_paddata(paddata);
    }
    if (dispkey) {
        shGameKeyConvert(key, (u_char*) paddata);
        printR_keydata(key);
    }
}

void printR_pad00(void) {

    if (dbSwitchSys(9) && !dbSwitchSys(0xA) && !dbSwitchSys(0xB) && !dbSwitchSys(0xC)) {
        dbSwitchSet(0, 0xA, 1);
        dbSwitchSet(0, 0xB, 1);
        dbSwitchSet(0, 0xC, 1);
    }
    if (!dbSwitchSys(9) && dbSwitchSys(0xA) && dbSwitchSys(0xB) && dbSwitchSys(0xC)) {
        dbSwitchSet(0, 0xA, 0);
        dbSwitchSet(0, 0xB, 0);
        dbSwitchSet(0, 0xC, 0);
    }
    printR_padport(0, 0, 1, 1, dbSwitchSys(0xA), dbSwitchSys(0xB), dbSwitchSys(0xC));
}

void printR_pad10(void) {

    if (dbSwitchSys(0xD) && !dbSwitchSys(0xE) && !dbSwitchSys(0xF) && !dbSwitchSys(0x10)) {
        dbSwitchSet(0, 0xE, 1);
        dbSwitchSet(0, 0xF, 1);
        dbSwitchSet(0, 0x10, 1);
    }
    if (!dbSwitchSys(0xD) && dbSwitchSys(0xE) && dbSwitchSys(0xF) && dbSwitchSys(0x10)) {
        dbSwitchSet(0, 0xE, 0);
        dbSwitchSet(0, 0xF, 0);
        dbSwitchSet(0, 0x10, 0);
    }
    printR_padport(1, 0, 1, 1, dbSwitchSys(0xE), dbSwitchSys(0xF), dbSwitchSys(0x10));
}

void printR_lang(void) {
    char* str;

    switch (sh2ScfGetDefaultLanguage() & 0xFF) {
        case 0:
            str = "JPN";
            break;
        case 1:
            str = "ENG";
            break;
        case 2:
            str = "FRN";
            break;
        case 3:
            str = "GER";
            break;
        case 4:
            str = "ITA";
            break;
        case 5:
            str = "SPN";
            break;
    }
    dbfntprintfR("lang:%s\n", str);
}

void dbSwitchSysPrint(void) {
    int Y = 0;

    for (Y = 0; Y < 32; Y++)
        switch (Y) { /* irregular */
            case 4:
                if (dbSwitchSys(Y) != 0) {
                    printR_date();
                }
                break;
            case 5:
                if (dbSwitchSys(Y) != 0) {
                    printR_fileserv();
                }
                break;
            case 6:
                if (dbSwitchSys(Y) != 0) {
                    printR_loadinit();
                }
                break;
            case 19:
                if (dbSwitchSys(Y) != 0) {
                    printR_test();
                }
                break;
            case 9:
                printR_pad00();
                break;
            case 13:
                printR_pad10();
                break;
            case 8:
                if (dbSwitchSys(Y) != 0) {
                    printR_lang();
                }
                break;
            case 17:
                break;
            case 18:
                if (dbSwitchSys(Y) != 0) {
                    dbScrPrintThreAll();
                }
                break;
        }
}

int dbSwitchSysPrintHelp(void) {
    dbSwitchSys(0);
}

int dbSwitchSysPadPort(void) {
    dbSwitchSys(1);
}

int dbSwitchSysPrintAllPages(void) {
    dbSwitchSys(3);
}

int dbSwitchSysPrintNotOnlyPort1(void) {
    dbSwitchSys(2);
}

void dbSwitchSysInit(void) {
    dbSwitchSetSys(1, 1);
    dbSwitchSetSys(2, 1);
    dbSwitchSetSys(3, 1);
    dbSwitchSetSys(5, 1);
    dbSwitchSetSys(6, 1);
    dbSwitchSetSys(30, 1);
    dbSwitchSetSys(31, 1);
}
