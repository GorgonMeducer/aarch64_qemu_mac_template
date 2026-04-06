#include <stdio.h>
#include <arm_sve.h>
#include <arm_acle.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include <stdlib.h>

#include "sve_util.h"
#include "arm_2d_sve_extension.h"

__attribute__((nonnull(1,2)))
void sve_tester(uint32_t * __restrict pwSource, 
                uint32_t * __restrict pwTarget, 
                uint8_t * __restrict pchSourceMask,
                size_t uStride);

int main(void) {
    printf("Hello from AArch64 Linux!\n");
    printf("Compiled on MacOS, running in QEMU.\n");

    printf("SVE Vector Length: %zu bits\r\n", svlen(svundef_u8()) * 8);

#if 0
    svuint16_t v16Input = svundef_u16();
    svuint16_t v16Input2 = svundef_u16();
    svuint32_t v32Input3 = svundef_u32();

    svbool_t vPred1 = svptrue_pat_b16(SV_VL1);
    svbool_t vPred2 = svptrue_pat_b16(SV_VL6);
    //svbool_t vPred3 = svdup_n_b8(true);

    //vPred1 &= vPred2;

    vPred2 &= ~vPred1;

    

    printf("[%08x]\r\n", *(uint32_t *)&vPred2);

    //SVT_INIT_PRED(vPred, 0xFF, 0x10, 0x00, 0x00);

    SVT_PRINT_PRED(vPred2, uint16_t);

    SVT_INIT_VECOTR(v16Input, uint16_t, 1, 2, 3, 4, 5, 6, 7, 8, 9,10);
    SVT_INIT_VECOTR(v16Input2, uint16_t, 0xFFFF, 0xFFFF, 0xAAAA);
    SVT_INIT_VECOTR(v32Input3, uint32_t, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 , 16);

    v16Input2 += 1; //v16Input;

    SVT_PRINT_VECTOR(v16Input, uint16_t, "0x%04"PRIx16);
    SVT_PRINT_VECTOR(v16Input2, uint16_t, "0x%04"PRIx16);
    SVT_PRINT_VECTOR(v32Input3, uint32_t, "0x%08"PRIx32);

#endif

#define PIXEL_COUNT             128

#define INPUT_BUFFER_SIZE       (sizeof(uint32_t) * PIXEL_COUNT)
#define OUTPUT_BUFFER_SIZE      (sizeof(uint32_t) * PIXEL_COUNT)
#define MASK_SIZE               (sizeof(uint8_t) * PIXEL_COUNT)

    uint8_t *pchSource = (uint8_t *)malloc(INPUT_BUFFER_SIZE);
    assert(NULL != pchSource);

    for (size_t n = 0; n < INPUT_BUFFER_SIZE; n++) {
        uint8_t chData = n;//(n & 0x3) | ((n & ~0x03) << 2);
        pchSource[n] = chData;
    }

    uint8_t *pchTarget = (uint8_t *)malloc(OUTPUT_BUFFER_SIZE);
    assert(NULL != pchTarget);
    memset(pchTarget, 0xFF, OUTPUT_BUFFER_SIZE);

    uint8_t *pchSourceMask = (uint8_t *)malloc(MASK_SIZE);
    assert(NULL != pchSourceMask);
    for (size_t n = 0; n < PIXEL_COUNT; n++) {
        pchSourceMask[n] = n & 0xFF;
    }

    uint8_t *pchTargetMask = (uint8_t *)malloc(MASK_SIZE);
    assert(NULL != pchTargetMask);
    for (size_t n = 0; n < PIXEL_COUNT; n++) {
        pchTargetMask[n] = 0xFF;
    }

#if 0
    __arm_2d_sve_cccn888_blend_with_opacity((uint32_t *)pchSource, 
                                            (uint32_t *)pchTarget, 
                                            OUTPUT_BUFFER_SIZE / sizeof(uint32_t), 
                                            128);

    
    __arm_2d_sve_cccn888_blend_with_masks(  (uint32_t *)pchSource, 
                                            (uint32_t *)pchTarget, 
                                            pchMask,
                                            pchMask,
                                            OUTPUT_BUFFER_SIZE / sizeof(uint32_t));

    __arm_2d_sve_cccn888_fill_colour_with_source_masks((uint32_t *)pchTarget, pchMask, pchMask, 17, 0x00804020);
    
#endif
    __arm_2d_sve_cccn888_reverse_fill_colour_with_masks((uint32_t *)pchTarget, pchSourceMask + MASK_SIZE - 1, pchTargetMask, MASK_SIZE, 0x00000000);
    //sve_tester((uint32_t *)pchSource + 20 - 1, (uint32_t *)pchTarget, pchMask + 20 - 1, 20);



    SVT_PRINT_BUFFER(pchSource, uint8_t, "%02"PRIx8, 64);
    SVT_PRINT_BUFFER(pchTarget, uint8_t, "%02"PRIx8, 64);

    
    free(pchSource);
    free(pchTarget);
    free(pchSourceMask);
    free(pchTargetMask);

    return 0;
}

__attribute__((nonnull(1,2)))
void sve_tester(uint32_t * __restrict pwSource, 
                uint32_t * __restrict pwTarget, 
                uint8_t * __restrict pchSourceMask,
                size_t uStride)
{

#if 1

    /* generate one-pass address */
    pwSource += 1;
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred){

        svbool_t vTailPredRev = svrev_b8(vTailPred);

        SVT_PRINT_PRED(vTailPred, uint8_t);
        SVT_PRINT_PRED(vTailPredRev, uint8_t);

        pwSource -= __iteration_advance__;
        pchSourceMask -= __iteration_advance__;

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        svld4u8_u16(vTailPredRev, (uint8_t *)pwSource, &vSourceLow16x4, &vSourceHigh16x4);
        svld4u8_u16(vTailPred, (uint8_t *)pwTarget, &vTargetLow16x4, &vTargetHigh16x4);

        svuint8_t vu8SourceMask = svld1_u8(vTailPredRev, pchSourceMask);

        SVT_PRINT_VECTOR(vu8SourceMask, uint8_t, "0x%02"PRIx8);

        svuint16_t vSourceMaskHigh = svrev(svunpkhi_u16(vu8SourceMask));

        /* process low half */
        __arm_2d_sve_stride_ccca_foreach_chn__(vSourceHigh16x4, vTargetLow16x4,

            if (__chn_idx__ == 3) {
                SVT_PRINT_VECTOR(svrev(vSourceMaskHigh), uint16_t, "0x%04"PRIx16);
                __svu16_target__ = vSourceMaskHigh;
            } else {
                SVT_PRINT_VECTOR(__svu16_source__, uint16_t, "0x%04"PRIx16);
                __svu16_source__ = svrev(__svu16_source__);
                

                __svu16_target__ = __svu16_source__;
            }

        );

        /* process high half */
        svuint16_t vSourceMaskLow = svrev(svunpklo_u16(vu8SourceMask));

        __arm_2d_sve_stride_ccca_foreach_chn__(vSourceLow16x4, vTargetHigh16x4,

            if (__chn_idx__ == 3) {
                __svu16_target__ = vSourceMaskLow;
                SVT_PRINT_VECTOR(svrev(vSourceMaskLow), uint16_t, "0x%04"PRIx16);
            } else {
                SVT_PRINT_VECTOR(__svu16_source__, uint16_t, "0x%04"PRIx16);
                __svu16_source__ = svrev(__svu16_source__);
                

                __svu16_target__ = __svu16_source__;
            }
        );

        svst4u8_u16(vTailPred, (uint8_t *)pwTarget, &vTargetLow16x4, &vTargetHigh16x4);

        pwTarget += __iteration_advance__;
    }

#endif

#if 0
    svbool_t vPred = svdup_n_b8(true);
    SVT_INIT_PRED(vPred, 0b00010101, 0b00010101, 0b00010101, 0b00010101);

    svuint16_t vInput16 = svld1ub_u16(vPred, pchSource);

    vInput16 = svdup_u16_m(vInput16, ~vPred, 0x00FF);

    SVT_PRINT_VECTOR(vInput16, uint16_t, "0x%04"PRIx8);
#endif

#if 0
    svuint32_t vIndex32 = svindex_u32(3, 4);
    
    svuint32_t vAlpha0 = svld1ub_gather_offset_u32(svptrue_b32(), pchSource, vIndex32);

    pchSource += svlen_u32(vAlpha0) * sizeof(uint32_t);

    svuint32_t vAlpha1 = svld1ub_gather_offset_u32(svptrue_b32(), pchSource, vIndex32);

    //vAlpha0 = svrev_u32(vAlpha0);

    svuint16_t vAlpha3 = svuzp1_u16(svreinterpret_u16_u32(vAlpha0),
                                     svreinterpret_u16_u32(vAlpha1));

    SVT_PRINT_VECTOR(vAlpha0, uint32_t, "0x%08"PRIx32);
    SVT_PRINT_VECTOR(vAlpha1, uint32_t, "0x%08"PRIx32);

    SVT_PRINT_VECTOR(svreinterpret_u16_u32(vAlpha0), uint16_t, "0x%04"PRIx16);
    SVT_PRINT_VECTOR(svreinterpret_u16_u32(vAlpha1), uint16_t, "0x%04"PRIx16);
    SVT_PRINT_VECTOR(vAlpha3, uint16_t, "0x%04"PRIx16);
#endif
}
