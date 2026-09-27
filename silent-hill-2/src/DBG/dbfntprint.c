#include "dbfntprint.h"

static int printline(char* cp /* r2 */, char* top /* r2 */);

static int printlineR(char* cp /* r2 */, char* top /* r2 */);

static void _dbfntprint(char* buf);

static void _dbfntprintR(char* buf /* r2 */);

static int _dbfntvsnprintf(void (* dbfntprintfunc)(char *) /* r19 */, char* buf /* r18 */, int limit /* r17 */, char* fmt /* r2 */, char* argp /* r2 */);

extern DebugPrintInfo d_0x0033BEC0;

#line 39
void dbfntlocate(int x, int y) {
    d_0x0033BEC0.x = x; d_0x0033BEC0.xofs = x;
    d_0x0033BEC0.y = y; d_0x0033BEC0.yofs = y;
}

void dbfntlocateR(int x, int y) {
    d_0x0033BEC0.xofsR = x;
    d_0x0033BEC0.yR = y; d_0x0033BEC0.yofsR = y;
}

int printline(char* cp, char* top) {

    char line[128]; // r29+0x20
    int l; // r16
    l = cp - top;
    if (l > 0) {
        // ensure less than 128 lines
        if (l >= 0x80u) l = 0x7F;
        memcpy(line, top, l);
        line[l] = 0;
        _shDBG_print_string((char* ) &line, d_0x0033BEC0.x, d_0x0033BEC0.y);
    } else {
        l = 0;
    }
    return l;
}

//thanks: Lazy Pig (anon)
int printlineR(char* cp, char* top) {
    char line[128]; // r29+0x20
    int l; // r16

    l = cp - top;
    if (l > 0) {
        // wrap?
        if (l >= 0x80U) {
            top += l - 0x7F;
            l = 0x7F;
        }
        memcpy(line, top, l);
        line[l] = 0;
        _shDBG_print_string(line, d_0x0033BEC0.xofsR - (l * d_0x0033BEC0.w), d_0x0033BEC0.yR);
    } else {
        l = 0;
    }
    return l;
}

void _dbfntprint(char* buf) {
    char * cp; // r16
    char * t; // r2
    cp = buf, t = buf;

    while (*cp != 0) {
        switch (*cp) {
            case '\n':
                printline(cp, t);
                t = cp + 1;
                d_0x0033BEC0.x = d_0x0033BEC0.xofs;
                d_0x0033BEC0.y += d_0x0033BEC0.h;
            default:
                break;
            case '\t':
                d_0x0033BEC0.x += d_0x0033BEC0.w * printline(cp, t);
                t = cp + 1;
                d_0x0033BEC0.x += d_0x0033BEC0.w * d_0x0033BEC0.tab;
                break;
            case '\r':
                printline(cp, t);
                t = cp + 1;
                d_0x0033BEC0.x = d_0x0033BEC0.xofs;
                break;
            case '\b':
                d_0x0033BEC0.x += d_0x0033BEC0.w * printline(cp, t);
                t = cp + 1;
                d_0x0033BEC0.x -= d_0x0033BEC0.w;
                break;
            }
        cp++;
    }
    printline(cp, t);
}

static void _dbfntprintR(char* buf /* r2 */) {
    char* t; // r2
    char* cp; // r16
    t = cp = buf;

    while(*cp != 0) {
        switch (*cp) {                              /* irregular */
            case '\n':
            case '\t':
            case '\b':
                printlineR(cp, t);
                t = cp + 1;
                d_0x0033BEC0.yR += d_0x0033BEC0.h;
                break;
            case '\r':
                printlineR(cp, t);
                t = cp + 1;
                break;
            default:
                break;
        }
        cp++;
    }
    printlineR(cp, t);
}

void dbfntprint(char* buf /* r16 */) {
    if (dbSwitchDispEnable(-1)) _dbfntprint(buf);
}

void dbfntprintR(char* buf /* r16 */) {
    if (dbSwitchDispEnable(-1)) _dbfntprintR(buf);
}

static int _dbfntvsnprintf(void (* dbfntprintfunc)(char *) /* r19 */, char* buf /* r18 */, int limit /* r17 */, char* fmt /* r2 */, char* argp /* r2 */) {
    int len; // r16

    len = vsprintf(buf, fmt, argp);
    if (!(len < limit)) {
        printf(DEBUG_TEXT_ON_LINE(247, "_dbfntvsnprintf strbuf overflow!!\n")
               DEBUG_TEXT_ON_LINE(248, "%s")
               DEBUG_TEXT_ON_LINE(249, "halted by error\n", buf));

        BLOCK_WHILE(true);
    }

    dbfntprintfunc(buf);
    return len;
}

s32 dbfntprintf(char* fmt, ...) {
    va_list argp; // r16
    char buf[512]; // r29+0x20


    va_start(argp, fmt);






    if (dbSwitchDispEnable(-1)) return _dbfntvsnprintf(&dbfntprint, buf, sizeof(buf), fmt, argp);
    return 0;


}

int dbfntprintfR(char * fmt /* r29+0x228 */, ...){
    va_list argp; // r16
    char buf[512]; // r29+0x20


    va_start(argp, fmt);






    if (dbSwitchDispEnable(-1)) return _dbfntvsnprintf(&dbfntprintR, buf, sizeof(buf), fmt, argp);
    return 0;


}
