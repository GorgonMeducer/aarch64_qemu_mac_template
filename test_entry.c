#include <stdio.h>
#include <arm_sve.h>
#include <arm_acle.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include <stdlib.h>

//#include "sve_util.h"
//#include "arm_2d_sve_extension.h"

#if 0
#undef sdl_sve_rgb32_blend_op_fill_alpha
#define sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx)                     \
            if (sve_src_chn_idx == (ma_alpha_chn_idx)) {                        \
                /* fill alpha */                                                \
                sve_target_u16 = svdup_u16(0xFF);                               \
            } else {                                                            \
                svuint16_t vMask = svget4(sve_source_u16x4, (ma_alpha_chn_idx));\
                sve_target_u16                                                  \
                    = sdl_sve_chn_blend_with_mask(  sve_source_u16,             \
                                                    sve_target_u16,             \
                                                    vMask);                     \
            }

#undef sdl_sve_rgb32_blend_op_copy_alpha
#define sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx)                     \
            if (sve_src_chn_idx == (ma_alpha_chn_idx)) {                        \
                svuint16_t vMask = svget4(sve_source_u16x4, (ma_alpha_chn_idx));\
                sve_target_u16                                                  \
                    = sdl_sve_chn_blend_with_mask(  svdup_u16(0xFF),            \
                                                    sve_target_u16,             \
                                                    vMask);                     \
            } else {                                                            \
                svuint16_t vMask = svget4(sve_source_u16x4, (ma_alpha_chn_idx));\
                sve_target_u16                                                  \
                    = sdl_sve_chn_blend_with_mask(  sve_source_u16,             \
                                                    sve_target_u16,             \
                                                    vMask);                     \
            }

#undef sdl_sve_rgb32_blend_to_rgb565_op
#define sdl_sve_rgb32_blend_to_rgb565_op(ma_alpha_chn_idx)                      \
        do {                                                                    \
            svuint16_t vMask = svget4(sve_source_u16x4, (ma_alpha_chn_idx));    \
                sve_target_u16                                                  \
                    = sdl_sve_chn_blend_with_mask(  sve_source_u16,             \
                                                    sve_target_u16,             \
                                                    vMask);                     \
        } while(0)
#else

#undef sdl_sve_rgb32_blend_op_fill_alpha
#define sdl_sve_rgb32_blend_op_fill_alpha(ma_alpha_chn_idx)                     \
        do {                                                                    \
            if (sve_src_chn_idx == (ma_alpha_chn_idx)) {                        \
                /* fill alpha */                                                \
                sve_target_u16 = svdup_u16(0xFF);                               \
            } else {                                                            \
                sve_target_u16 = sve_source_u16;                                \
            }                                                                   \
        } while(0)

#undef sdl_sve_rgb32_blend_op_copy_alpha
#define sdl_sve_rgb32_blend_op_copy_alpha(ma_alpha_chn_idx)                     \
        do {                                                                    \
                sve_target_u16 = sve_source_u16;                                \
        } while(0)

#undef sdl_sve_rgb32_blend_to_rgb565_op
#define sdl_sve_rgb32_blend_to_rgb565_op(ma_alpha_chn_idx)                      \
        do {                                                                    \
            sve_target_u16 = sve_source_u16;                                    \
            SVT_PRINT_VECTOR(sve_target_u16, uint16_t, "%04x");                 \
        } while(0)

#endif

#include "SDL_sve2_swizzle.h"


__attribute__((nonnull(1,2)))
void sve_tester(uint32_t * __restrict pwSource, 
                uint32_t * __restrict pwTarget, 
                uint8_t * __restrict pchSourceMask,
                size_t uStride);

int main(void) {
    printf("Hello from AArch64 Linux!\n");
    printf("Compiled on MacOS, running in QEMU.\n");

    printf("SVE Vector Length: %zu bits\r\n", svlen(svundef_u8()) * 8);


#define PIXEL_COUNT             128

#define INPUT_BUFFER_SIZE       (sizeof(uint32_t) * PIXEL_COUNT)
#define OUTPUT_BUFFER_SIZE      (sizeof(uint32_t) * PIXEL_COUNT)
#define MASK_SIZE               (sizeof(uint8_t) * PIXEL_COUNT)

    uint8_t *pchSource = (uint8_t *)malloc(INPUT_BUFFER_SIZE);
    assert(NULL != pchSource);

    for (size_t n = 0; n < INPUT_BUFFER_SIZE; n++) {
        uint8_t chData = n;//(n & 0x3) | ((n & ~0x03) << 2);
        pchSource[n] = chData;
    #if 1
        if ((n & 0x03) == 0x03) {
            pchSource[n] = 0xFF;
        }
    #endif
    }

    uint8_t *pchTarget = (uint8_t *)malloc(OUTPUT_BUFFER_SIZE);
    assert(NULL != pchTarget);
    memset(pchTarget, 0xFF, OUTPUT_BUFFER_SIZE);

    uint8_t *pchSourceMask = (uint8_t *)malloc(MASK_SIZE);
    assert(NULL != pchSourceMask);
    for (size_t n = 0; n < PIXEL_COUNT; n++) {
        pchSourceMask[n] = n;
    }

    uint8_t *pchTargetMask = (uint8_t *)malloc(MASK_SIZE);
    assert(NULL != pchTargetMask);
    for (size_t n = 0; n < PIXEL_COUNT; n++) {
        pchTargetMask[n] = 0xFF;
    }

    /*
    sdl_sve_accc8888_blend_to_nccc888_fill_alpha
    sdl_sve_accc8888_blend_to_nccc888_copy_alpha
    sdl_sve_ccca8888_blend_to_cccn888_fill_alpha
    sdl_sve_ccca8888_blend_to_cccn888_copy_alpha
    sdl_sve_a123_blend_to_321a_fill_alpha
    sdl_sve_a123_blend_to_321a_copy_alpha
    sdl_sve_123a_blend_to_a321_fill_alpha
    sdl_sve_123a_blend_to_a321_copy_alpha
    sdl_sve_accc_blend_to_ccca_fill_alpha
    sdl_sve_accc_blend_to_ccca_copy_alpha
    sdl_sve_ccca_blend_to_accc_fill_alpha
    sdl_sve_ccca_blend_to_accc_copy_alpha
    sdl_sve_a123_blend_to_a321_fill_alpha
    sdl_sve_a123_blend_to_a321_copy_alpha
    sdl_sve_123a_blend_to_321a_fill_alpha
    sdl_sve_123a_blend_to_321a_copy_alpha
    sdl_sve_argb8888_blend_to_rgb565
    sdl_sve_rgba8888_blend_to_rgb565
    sdl_sve_bgra8888_blend_to_rgb565
    sdl_sve_abgr8888_blend_to_rgb565
    */
    sdl_sve_a123_blend_to_321a_copy_alpha(  
                                            pchSource, 
                                            INPUT_BUFFER_SIZE / 2, 
                                            pchTarget, 
                                            OUTPUT_BUFFER_SIZE / 2, 
                                            OUTPUT_BUFFER_SIZE / 2, 
                                            2);

    SVT_PRINT_BUFFER(pchSource, INPUT_BUFFER_SIZE, uint32_t, "%08"PRIx32, 16);
    SVT_PRINT_BUFFER(pchTarget, OUTPUT_BUFFER_SIZE, uint32_t, "%08"PRIx32, 16);
    //SVT_PRINT_BUFFER(pchTarget, OUTPUT_BUFFER_SIZE / 2, uint16_t, "%04"PRIx16, 16);

    
    free(pchSource);
    free(pchTarget);
    free(pchSourceMask);
    free(pchTargetMask);

    return 0;
}

