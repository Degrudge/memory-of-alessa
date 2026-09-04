#include "sh2_common.h"

#include "gs.h"

#include "Event/event.h"

#include "GFW/sh2_GsAllEnv.h"
#include "GFW/sh2gfw_2d_filters.h"
#include "GFW/sh2gfw_macros.h"

#include "SH2_common/sh2dt.h"

#include "view/camera_dat.h"

#include "data/daily.thu/data_movie.h"
#include "data/daily.thu/data_demo_first_toilet.h"

/* data */
static float stg_toilet_wvp[4] = { 0.0f, 0.0f, 450.0f, 1.0f };

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_toilet", stg_toilet_EvProgPrologueInToilet);

/* static */ void stg_toilet_EvStageInit(void) {
    return;
}

/* static */ int stg_toilet_EvBgmControl(void) {
    if (GET_GAME_FLAG(GAME_FLAG_36)) {
        return 1;
    }
    return !GET_GAME_FLAG(GAME_FLAG_33) ? 4 : 0;
}

/* @todo migrate */
#line 207
int stg_toilet_Kari_hisyakai(int KeyAlpha) {
    static Q_WORDDATA qwd[32];
    sceVu0IVECTOR ivt; // r29+0x30
    sceVu0FMATRIX wsm; // r29+0x40
    int id = 0; // r2

    
    
    sceVu0CopyMatrix(wsm, cam0.view_screen);
    sceVu0RotTransPers(ivt, wsm, stg_toilet_wvp, 1);

    SET_DMATAG(qwd, id, DMAcnt | 7, 0, 0, SCE_VIF1_SET_DIRECT(7, 0));

    SET_GIFTAG(qwd, id, SCE_GIF_SET_TAG(6, SCE_GS_TRUE, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD);

    qwd[id++] = shGs_AllEnv.Now_DrawEnv.frame_normal;


    
    
    
    
    
    
    
    
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEST_1, SCE_GS_SET_TEST(SCE_GS_FALSE, SCE_GS_ALPHA_ALWAYS, 0, 0, 0, 1, SCE_GS_TRUE, SCE_GS_DEPTH_GEQUAL));

    
    
    
    
    SET_ADDRESS_DATA(qwd, id, SCE_GS_ZBUF_1, SCE_GS_SET_ZBUF(0xE0000 / 2048, SCE_GS_PSMZ16S, SCE_GS_FALSE));


    
    
    qwd[id].ul64[0] = SCE_GS_SET_TEX1(0, 0, SCE_GS_LINEAR, SCE_GS_LINEAR, 0, 0, 0); qwd[id++].ul64[1] = SCE_GS_TEX1_1;



    SET_ADDRESS_DATA(qwd, id, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP(SCE_GS_CLAMP, SCE_GS_CLAMP, 0, 0, 0, 0));


    
    SET_ADDRESS_DATA(qwd, id, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(0, 2, 2, 1, 255));

    
    SET_DMATAG(qwd, id, DMAcnt | 5, 0, 0, SCE_VIF1_SET_DIRECT(5, 0));
    qwd[id].ul64[0] = SCE_GIF_SET_TAG(1, SCE_GS_TRUE, SCE_GS_TRUE, 
                                      SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0), SCE_GIF_PACKED, 4);
    qwd[id++].ul64[1] = GIF_REGLIST(SCE_GS_RGBAQ, SCE_GS_XYZ2, SCE_GS_RGBAQ, SCE_GS_XYZ2);

    
    SET_QWORD_U32(qwd, id, 0, 0, 0, KeyAlpha);

    qwd[id].ul64[0] = SH_GIF_PACK_XY(Q4(1792.0f), Q4(1792.0f)), qwd[id++].ul64[1] = ivt[2];

    SET_QWORD_U32(qwd, id, 0, 0, 0, KeyAlpha);

    qwd[id].ul64[0] = SH_GIF_PACK_XY(Q4(2304.0f), Q4(2304.0f)), qwd[id++].ul64[1] = ivt[2];

    qwd[id].ul128 = 0;
    qwd[id++].ui32[0] = DMAend; /* SET_DMA_END(qwd); */

    d1cSend(qwd);
    
    return ivt[2] >> 4;

}
#undef qwd

/* static */ float stg_toilet_LinearTrim(float Yen, float Yst, float Xen, float Xst, float Parm) {
    return Yst + (((Yen - Yst) * (Parm - Xst)) / (Xen - Xst));
}

// https://decomp.me/scratch/dHOre
INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_toilet", stg_toilet_Toilet_Dof_Filter);
