#include "sh2_common.h"
#include "GFW/sh2_DrawEnvData.h"

typedef struct shDBG_font_Packet {
    // total size: 0x40150
    Q_WORDDATA* Qtail; // offset 0x0, size 0x4
    Q_WORDDATA* QKick; // offset 0x4, size 0x4
    Q_WORDDATA* QAddr; // offset 0x8, size 0x4
    Q_WORDDATA* Q; // offset 0xC, size 0x4
    Q_WORDDATA dbg_font_env[16]; // offset 0x10, size 0x100
    Q_WORDDATA ret_font_packet[4]; // offset 0x110, size 0x40
    Q_WORDDATA dbg_font_packet[16384]; // offset 0x150, size 0x40000
} shDBG_font_Packet;
extern shDBG_font_Packet sh_DBGFontPacket; // size: 0x40150, address: 0x11765C0

INCLUDE_ASM("asm/nonmatchings/DBG/shDBG_fontHandle", shDBG_font_init);

INCLUDE_ASM("asm/nonmatchings/DBG/shDBG_fontHandle", shDBG_InitFontEnv);

INCLUDE_ASM("asm/nonmatchings/DBG/shDBG_fontHandle", _shDBG_print_string);

INCLUDE_ASM("asm/nonmatchings/DBG/shDBG_fontHandle", shDBG_print_string);

#ifdef NEVER
void shDBG_font_PrintDrawAll(void) {
    if (Env_ctl.stat_ctl_2.uc8[0] != 4) {
        (sh_DBGFontPacket.Qtail)->ui32[0] = DMAnext;
        (sh_DBGFontPacket.Qtail)->ui32[1] = (u_int) &sh_DBGFontPacket.ret_font_packet;
        (sh_DBGFontPacket.Qtail)->ul64[1] = 0;
        d1cSend(sh_DBGFontPacket.dbg_font_env);
    }
}
#endif

INCLUDE_RODATA("asm/nonmatchings/DBG/shDBG_fontHandle", @51_0x00395AB0);

INCLUDE_RODATA("asm/nonmatchings/DBG/shDBG_fontHandle", @52_0x00395AE0);
