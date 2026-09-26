#include "sh2_common.h"

#include "sce/eeregs.h"

#include "GFW/sh2_GsAllEnv.h"

#include "Multi_thr/intc/syncv.h"

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", all_Frame_Buffer_Clear);

extern Q_WORDDATA mct; // size: 0x10, address: 0x2ADB80

#line 139
void DrawLopp_Pre(void) {
    
    *T0_COUNT = 0;
    mct.ui32[0] = 0;
    
    
    
    
    gs_loppstart_init();
    
    
    
    sh2gfw_init_TexTrans_Manage_Table();
    
    
    
    d2tscClearSlots();
    
    
    
    
    sh2gfw_set_LoopDrawEnv(&shGs_AllEnv);
    
    
    
    
    spkResetOT();
    
    
    
    
    sh2gfw_Init_spkTexManage();
    
    
    
    
    shDBG_font_init(); sh2gfw_init_Perf();
    
    
    
    
    mfontClear();
    

    sh2shd_reset_shadow();
}


INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", kari_drawloop_main_2dSYNC);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", draw_main_3dSYNC);

#line 252
void DrawLopp_Post(void) {
    /* 
    
    there's missing code in this line number gap
    confirmed in a different prototype:
    */
    #ifdef NEVER
    int enable = dbSwitchDispEnable(-1);
    
    if (enable || dbFlag(16))
        shDBG_font_PrintDrawAll(); // not in this prototype
    #endif
    
    
    
    d2sSync(0, -1);
    d1sSync(0, -1);




    
    if (mct.ui32[0] == 0) {
    
        
        shSyncVStart(0);
        shSyncVStart(0);
    
    
    
    
    } else {
    
        
        
        shSyncVStart(0);
    
    
    
    
    
    
    }
    mct.ui32[3]++;
    sh2gfw_InclimentLoopCounter(&shGs_AllEnv);
    
    
    
    
    
    
    
    mct.ui32[1] = mct.ui32[0];
}

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", Get_FrameRate);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", Exec_PreDraw_OVfunc);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", draw_main);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", Noise_and_FontDraw);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", GSFilterExec4NextLoop);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", Calc_Set_Matrix);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", gs_loppstart_init);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", kari_setdmatag_and_draw);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", Draw_Character_And_Shadow);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", Spack_All_Draw);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", FOG_ROOM);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", DrawSpecialPolyforDemo);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", Check_DrawOrder);
