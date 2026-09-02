#include "DBG/dbsw_all.h"

void dbSwitchAllInit(int enable) {
    dbSwitchDispEnable(enable != 0);
    if (enable) {
        dbSwitchSysInit();
        dbSwitchMapInit();
    }
}

void dbSwitchHelpPrint() {
    int on; // r16
    char* help; // r17
    int X; // r29+0x38
    int Y; // r29+0x3C

    help = NULL;
    on = dbSwitchGetPos(&X, &Y);
    switch (X) {                                 /* irregular */
    case 0:
        help = dbSwitchSysHelp(Y);
        break;
    case 1:
        help = dbSwitchMapHelp(Y);
        break;
    }

    if (help == NULL) {
        help = "(NO HELP)";
    }

    dbfntprintfR("%s:%s\n", help, on ? "ON" : "OFF");
}

int dbSwitchIsVisible() {
    int disp; // r2
    int notonlyport1; // r2
    int port; // r16

    port = shPadGetPort();
    notonlyport1 = dbSwitchSysPrintNotOnlyPort1();
    disp = port == 1;
    if (!disp) {
        disp = notonlyport1 != 0;
    }
    return disp;
}

void dbSwitchAllPrint() {
    int disp; // r18
    int loop; // r16
    int X; // r29+0x6C

    disp = dbSwitchIsVisible();
    dbSwitchGetPos(&X, 0);
    dbfntlocateR(496, 44);
    if (disp) {
        dbSwitchDispIndicator(disp,
                              shPadRepeat(1, PAD_KEY_CIRCLE) != 0,
                              shPadRepeat(1, PAD_KEY_CROSS) != 0,
                              (shPadRepeat(1, PAD_KEY_DPAD_RIGHT) != 0) - (shPadRepeat(1, PAD_KEY_DPAD_LEFT) != 0),
                              (shPadRepeat(1, PAD_KEY_DPAD_UP) != 0) - (shPadRepeat(1, PAD_KEY_DPAD_DOWN) != 0));
    } else {
        dbSwitchDispIndicator(disp, 0, shPadRepeat(1, PAD_KEY_CIRCLE) != 0, 0, 0);
    }
    if (shPadPress(1, PAD_KEY_L1)) {
        if (((shPadPress(1, PAD_KEY_SQUARE)) && (shPadTrigger(1, PAD_KEY_TRIANGLE))) || ((shPadPress(1, PAD_KEY_TRIANGLE)) && (shPadTrigger(1, PAD_KEY_SQUARE)))) {
            dbSwitchAllInit(!dbSwitchDispEnable(-1));
        } else {
            if (shPadTrigger(1, PAD_KEY_TRIANGLE)) {
                dbSwitchInit(X, (0xFFFFL << 0x10 | 0xFFFF));
            }
            if (shPadTrigger(1, PAD_KEY_SQUARE)) {
                dbSwitchInit(X, 0);
            }
        }
    }
    if (disp) {
        dbfntlocateR(496, 44);
        if (dbSwitchSysPrintHelp()) {
            dbSwitchHelpPrint();
        }

        for (loop = 0; loop < 2; loop++) {
            if ((loop == X) || (dbSwitchSysPrintAllPages())) {
                switch (loop) {                   /* irregular */
                case 0:
                    dbSwitchSysPrint();
                    break;
                case 1:
                    dbSwitchMapPrint();
                    break;
                }
            }
        }
    }
}
