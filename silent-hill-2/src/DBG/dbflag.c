#include "dbflag.h"

extern /* static */ u_int dbflag_reserved; // size: 0x4, address: 0x116DD40
extern /* static */ char* dbflag_explain[32]; // size: 0x80, address: 0x33DE50
extern int execEnv_debug_flag; // size: 0x4, address: 0x5526A0

int dbFlagReserve(u_int flag /* r2 */, char * explain_message /* r2 */) {
    u_int check; // r16
    char** explain; // r17
    if (dbflag_reserved & flag) {

        verbose(1,
                "dbflag.c:44> can't reserved debug flag : %08x : %s\n",
                flag,
                explain_message);

        verbose(2,
                "dbflag.c:46> alreday reserved          : %08x\n",
                dbflag_reserved);

        for (check = 1, explain = dbflag_explain; check != 0; check*=2, explain++) {
            if (check & dbflag_reserved) {
                verbose(3,
                        "dbflag.c:52> flag report               : %08x : %s\n", check,
                        *explain ? *explain : "(no message: why?)");
            }
        }
        return 0;
    }
    for (check = 1, explain = dbflag_explain; check != 0; check*=2, explain+=1) {
        if (check & flag) {
            dbflag_reserved |= check;
            *explain = explain_message;
        }
    }
    verbose(4,
            "dbflag.c:64> reserved debug flag : %08x : %s\n",
            flag,
            explain_message);
    return 1;
}

u_int dbFlag(u_int flag) {
    return execEnv_debug_flag & flag;
}

void dbFlagSet(u_int flag) {
    execEnv_debug_flag |= flag;
}
