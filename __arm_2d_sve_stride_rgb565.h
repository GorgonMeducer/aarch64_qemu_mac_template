/******************************************************************************
 *  Copyright 2026 Gorgon Meducer (Email:embedded_zhuoran@hotmail.com)        *
 *                                                                            *
 *  Licensed under the Apache License, Version 2.0 (the "License");           *
 *  you may not use this file except in compliance with the License.          *
 *  You may obtain a copy of the License at                                   *
 *                                                                            *
 *     http://www.apache.org/licenses/LICENSE-2.0                             *
 *                                                                            *
 *  Unless required by applicable law or agreed to in writing, software       *
 *  distributed under the License is distributed on an "AS IS" BASIS,         *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 *  See the License for the specific language governing permissions and       *
 *  limitations under the License.                                            *
 *                                                                            *
 ******************************************************************************/

#if !defined(__ARM_2D_SVE_STRIDE_RGB565_H__)                                    \
    && (defined(__ARM_FEATURE_SVE2)                                             \
    && __ARM_FEATURE_SVE2)
#define __ARM_2D_SVE_STRIDE_RGB565_H__

/*----------------------------------------------------------------------------*
 * Colour Filling                                                             *
 *----------------------------------------------------------------------------*/
__STATIC_INLINE
ARM_NONNULL(1)
void __arm_2d_sve_rgb16_fill_colour(uint16_t * __RESTRICT phwTarget,
                                    size_t uStride,
                                    uint16_t hwColour)
{
    size_t n = 0;

    svuint16_t vColour = svdup_u16(hwColour);
    do {
        svbool_t vTailPred = svwhilelt_b16(n, uStride);
        
        svst1_u16(vTailPred, phwTarget, vColour);
        
        phwTarget += svlenu16();
        n += svlenu16();
    } while(n < uStride);
}

__STATIC_INLINE
ARM_NONNULL(1)
void __arm_2d_sve_rgb565_fill_colour_with_opacity(   
                                                uint16_t * __RESTRICT phwTarget,
                                                size_t uStride,
                                                uint16_t hwColour,
                                                uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_rgb16__(uStride, vTailPred) {

        svuint16x3_t tColour16x3 = 
            __arm_2d_sve_rgb565_unpack(svdup_u16(hwColour));
        svuint16x3_t vTarget16x3 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwTarget));

        __arm_2d_sve_stride_ccc_foreach_chn__(  tColour16x3,
                                                vTarget16x3,
            __svu16_target__ = __arm_2d_sve_chn_blend_with_opacity(
                                                    __svu16_source__,
                                                    __svu16_target__,
                                                    hwOpacity);
        );

        svst1_u16(  vTailPred, 
                    phwTarget, 
                    __arm_2d_sve_rgb565_pack(vTarget16x3));

        phwTarget += __iteration_advance__;
    }
}


__STATIC_INLINE
ARM_NONNULL(1)
void __arm_2d_sve_rgb565_fill_colour_with_source_mask(   
                                                uint16_t * __RESTRICT phwTarget,
                                                uint8_t * __RESTRICT pchMask,
                                                size_t uStride,
                                                uint16_t hwColour)
{
    __arm_2d_sve_stride_loop_rgb16__(uStride, vTailPred) {

        svuint16x3_t tColour16x3 = 
            __arm_2d_sve_rgb565_unpack(svdup_u16(hwColour));
        svuint16x3_t vTarget16x3 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwTarget));
        
        svuint16_t vMask = svld1ub_u16(vTailPred, pchMask);

        __arm_2d_sve_stride_ccc_foreach_chn__(  tColour16x3,
                                                vTarget16x3,
            __svu16_target__ = __arm_2d_sve_chn_blend_with_mask(
                                                    __svu16_source__,
                                                    __svu16_target__,
                                                    vMask);
        );

        svst1_u16(  vTailPred, 
                    phwTarget, 
                    __arm_2d_sve_rgb565_pack(vTarget16x3));

        phwTarget += __iteration_advance__;
        pchMask += __iteration_advance__;
    }
}


__STATIC_INLINE
ARM_NONNULL(1)
void __arm_2d_sve_rgb565_fill_colour_with_source_mask_and_opacity(   
                                                uint16_t * __RESTRICT phwTarget,
                                                uint8_t * __RESTRICT pchMask,
                                                size_t uStride,
                                                uint16_t hwColour,
                                                uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_rgb16__(uStride, vTailPred) {

        svuint16x3_t tColour16x3 = 
            __arm_2d_sve_rgb565_unpack(svdup_u16(hwColour));
        svuint16x3_t vTarget16x3 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwTarget));
        
        svuint16_t vMask = svld1ub_u16(vTailPred, pchMask);

        __arm_2d_sve_stride_ccc_foreach_chn__(  tColour16x3,
                                                vTarget16x3,
            __svu16_target__ = __arm_2d_sve_chn_blend_with_mask_and_opacity(
                                                    __svu16_source__,
                                                    __svu16_target__,
                                                    vMask,
                                                    hwOpacity);
        );

        svst1_u16(  vTailPred, 
                    phwTarget, 
                    __arm_2d_sve_rgb565_pack(vTarget16x3));

        phwTarget += __iteration_advance__;
        pchMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1)
void __arm_2d_sve_rgb565_fill_colour_with_masks(   
                                            uint16_t * __RESTRICT phwTarget,
                                            uint8_t * __RESTRICT pchSourceMask,
                                            uint8_t * __RESTRICT pchTargetMask,
                                            size_t uStride,
                                            uint16_t hwColour)
{
    __arm_2d_sve_stride_loop_rgb16__(uStride, vTailPred) {

        svuint16x3_t tColour16x3 = 
            __arm_2d_sve_rgb565_unpack(svdup_u16(hwColour));
        svuint16x3_t vTarget16x3 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwTarget));
        
        svuint16_t vSourceMask = svld1ub_u16(vTailPred, pchSourceMask);
        svuint16_t vTargetMask = svld1ub_u16(vTailPred, pchTargetMask);

        __arm_2d_sve_stride_ccc_foreach_chn__(  tColour16x3,
                                                vTarget16x3,

            __svu16_target__ = __arm_2d_sve_chn_blend_with_masks(
                                                    __svu16_source__,
                                                    __svu16_target__,
                                                    vSourceMask,
                                                    vTargetMask);
        );

        svst1_u16(  vTailPred, 
                    phwTarget, 
                    __arm_2d_sve_rgb565_pack(vTarget16x3));

        phwTarget += __iteration_advance__;
        pchSourceMask += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1)
void __arm_2d_sve_rgb565_fill_colour_with_masks_and_opacity(   
                                            uint16_t * __RESTRICT phwTarget,
                                            uint8_t * __RESTRICT pchSourceMask,
                                            uint8_t * __RESTRICT pchTargetMask,
                                            size_t uStride,
                                            uint16_t hwColour,
                                            uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_rgb16__(uStride, vTailPred) {

        svuint16x3_t tColour16x3 = 
            __arm_2d_sve_rgb565_unpack(svdup_u16(hwColour));
        svuint16x3_t vTarget16x3 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwTarget));
        
        svuint16_t vSourceMask = svld1ub_u16(vTailPred, pchSourceMask);
        svuint16_t vTargetMask = svld1ub_u16(vTailPred, pchTargetMask);

        __arm_2d_sve_stride_ccc_foreach_chn__(  tColour16x3,
                                                vTarget16x3,

            __svu16_target__ = __arm_2d_sve_chn_blend_with_masks_and_opacity(
                                                    __svu16_source__,
                                                    __svu16_target__,
                                                    vSourceMask,
                                                    vTargetMask,
                                                    hwOpacity);
        );

        svst1_u16(  vTailPred, 
                    phwTarget, 
                    __arm_2d_sve_rgb565_pack(vTarget16x3));

        phwTarget += __iteration_advance__;
        pchSourceMask += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}



/*----------------------------------------------------------------------------*
 * Colour Filling with X Mirroring                                            *
 *----------------------------------------------------------------------------*/

__STATIC_INLINE
ARM_NONNULL(1)
void __arm_2d_sve_rgb565_reverse_fill_colour_with_source_mask(   
                                                uint16_t * __RESTRICT phwTarget,
                                                uint8_t * __RESTRICT pchSourceMask,
                                                size_t uStride,
                                                uint16_t hwColour)
{
    /* generate the one-pass address */
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_rgb16__(uStride, vTailPred) {

        svuint16x3_t tColour16x3 = 
            __arm_2d_sve_rgb565_unpack(svdup_u16(hwColour));
        svuint16x3_t vTarget16x3 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwTarget));
        
        pchSourceMask -= __iteration_advance__;
        svuint16_t vSourceMask = 
            svrev(svld1ub_u16(svrev_b16(vTailPred), pchSourceMask));

        __arm_2d_sve_stride_ccc_foreach_chn__(  tColour16x3,
                                                vTarget16x3,
            __svu16_target__ = __arm_2d_sve_chn_blend_with_mask(
                                                    __svu16_source__,
                                                    __svu16_target__,
                                                    vSourceMask);
        );

        svst1_u16(  vTailPred, 
                    phwTarget, 
                    __arm_2d_sve_rgb565_pack(vTarget16x3));

        phwTarget += __iteration_advance__;
    }
}



__STATIC_INLINE
ARM_NONNULL(1)
void __arm_2d_sve_rgb565_reverse_fill_colour_with_source_mask_and_opacity(   
                                                uint16_t * __RESTRICT phwTarget,
                                                uint8_t * __RESTRICT pchSourceMask,
                                                size_t uStride,
                                                uint16_t hwColour,
                                                uint16_t hwOpacity)
{
    /* generate the one-pass address */
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_rgb16__(uStride, vTailPred) {

        svuint16x3_t tColour16x3 = 
            __arm_2d_sve_rgb565_unpack(svdup_u16(hwColour));
        svuint16x3_t vTarget16x3 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwTarget));
        
        pchSourceMask -= __iteration_advance__;
        svuint16_t vSourceMask = 
            svrev(svld1ub_u16(svrev_b16(vTailPred), pchSourceMask));

        __arm_2d_sve_stride_ccc_foreach_chn__(  tColour16x3,
                                                vTarget16x3,
            __svu16_target__ = __arm_2d_sve_chn_blend_with_mask_and_opacity(
                                                            __svu16_source__,
                                                            __svu16_target__,
                                                            vSourceMask,
                                                            hwOpacity);
        );

        svst1_u16(  vTailPred, 
                    phwTarget, 
                    __arm_2d_sve_rgb565_pack(vTarget16x3));

        phwTarget += __iteration_advance__;
    }
}



__STATIC_INLINE
ARM_NONNULL(1)
void __arm_2d_sve_rgb565_reverse_fill_colour_with_masks(   
                                            uint16_t * __RESTRICT phwTarget,
                                            uint8_t * __RESTRICT pchSourceMask,
                                            uint8_t * __RESTRICT pchTargetMask,
                                            size_t uStride,
                                            uint16_t hwColour)
{
    /* generate the one-pass address */
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_rgb16__(uStride, vTailPred) {

        svuint16x3_t tColour16x3 = 
            __arm_2d_sve_rgb565_unpack(svdup_u16(hwColour));
        svuint16x3_t vTarget16x3 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwTarget));
        
        pchSourceMask -= __iteration_advance__;
        svuint16_t vSourceMask = 
            svrev(svld1ub_u16(svrev_b16(vTailPred), pchSourceMask));
        svuint16_t vTargetMask = svld1ub_u16(vTailPred, pchSourceMask);

        __arm_2d_sve_stride_ccc_foreach_chn__(  tColour16x3,
                                                vTarget16x3,
            __svu16_target__ = __arm_2d_sve_chn_blend_with_masks(
                                                            __svu16_source__,
                                                            __svu16_target__,
                                                            vSourceMask,
                                                            vTargetMask);
        );

        svst1_u16(  vTailPred, 
                    phwTarget, 
                    __arm_2d_sve_rgb565_pack(vTarget16x3));

        phwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1)
void __arm_2d_sve_rgb565_reverse_fill_colour_with_masks_and_opacity(   
                                            uint16_t * __RESTRICT phwTarget,
                                            uint8_t * __RESTRICT pchSourceMask,
                                            uint8_t * __RESTRICT pchTargetMask,
                                            size_t uStride,
                                            uint16_t hwColour,
                                            uint16_t hwOpacity)
{
    /* generate the one-pass address */
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_rgb16__(uStride, vTailPred) {

        svuint16x3_t tColour16x3 = 
            __arm_2d_sve_rgb565_unpack(svdup_u16(hwColour));
        svuint16x3_t vTarget16x3 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwTarget));
        
        pchSourceMask -= __iteration_advance__;
        svuint16_t vSourceMask = 
            svrev(svld1ub_u16(svrev_b16(vTailPred), pchSourceMask));
        svuint16_t vTargetMask = svld1ub_u16(vTailPred, pchSourceMask);

        __arm_2d_sve_stride_ccc_foreach_chn__(  tColour16x3,
                                                vTarget16x3,
            __svu16_target__ = __arm_2d_sve_chn_blend_with_masks_and_opacity(
                                                            __svu16_source__,
                                                            __svu16_target__,
                                                            vSourceMask,
                                                            vTargetMask,
                                                            hwOpacity);
        );

        svst1_u16(  vTailPred, 
                    phwTarget, 
                    __arm_2d_sve_rgb565_pack(vTarget16x3));

        phwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}



/*----------------------------------------------------------------------------*
 * Blending                                                                   *
 *----------------------------------------------------------------------------*/


__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_rgb16_blend(  uint16_t * __RESTRICT phwSource,
                                uint16_t * __RESTRICT phwTarget,
                                size_t uStride)
{
    size_t n = 0;

    do {
        svbool_t vTailPred = svwhilelt_b16(n, uStride);
        
        svst1_u16(  vTailPred, 
                    phwTarget, 
                    svld1_u16(vTailPred, phwSource));
        
        phwTarget += svlenu16();
        phwSource += svlenu16();
        n += svlenu16();
    } while(n < uStride);
}

__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_rgb565_blend_with_opacity(    uint16_t * __RESTRICT phwSource,
                                                uint16_t * __RESTRICT phwTarget,
                                                size_t uStride,
                                                uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_rgb16__(uStride, vTailPred) {

        svuint16x3_t vSource16x4 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwSource));

        svuint16x3_t vTarget16x4 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwTarget));

        __arm_2d_sve_stride_ccc_foreach_chn__(vSource16x4, vTarget16x4,
        
            __svu16_target__ = __arm_2d_sve_chn_blend_with_opacity(
                                                            __svu16_source__,
                                                            __svu16_target__,
                                                            hwOpacity);
        );

        svst1_u16(vTailPred, phwTarget, __arm_2d_sve_rgb565_pack(vTarget16x4));

        phwSource += __iteration_advance__;
        phwTarget += __iteration_advance__;
    }
}



__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_rgb565_blend_with_source_mask(uint16_t * __RESTRICT phwSource,
                                                 uint8_t * __RESTRICT pchSourceMask,
                                                 uint16_t * __RESTRICT phwTarget,
                                                 size_t uStride)
{
    __arm_2d_sve_stride_loop_rgb16__(uStride, vTailPred) {

        svuint16x3_t vSource16x4 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwSource));

        svuint16x3_t vTarget16x4 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwTarget));

        svuint16_t vSourceMask = svld1ub_u16(vTailPred, pchSourceMask);

        __arm_2d_sve_stride_ccc_foreach_chn__(vSource16x4, vTarget16x4,
        
            __svu16_target__ = __arm_2d_sve_chn_blend_with_mask(
                                                            __svu16_source__,
                                                            __svu16_target__,
                                                            vSourceMask);
        );

        svst1_u16(vTailPred, phwTarget, __arm_2d_sve_rgb565_pack(vTarget16x4));

        phwSource += __iteration_advance__;
        phwTarget += __iteration_advance__;
        pchSourceMask += __iteration_advance__;
    }
}



#define __arm_2d_sve_rgb565_blend_with_target_mask(__source_ptr,               \
                                                    __target_ptr,               \
                                                    __target_mask_ptr,          \
                                                    __stride)                   \
    __arm_2d_sve_rgb565_blend_with_source_mask((__source_ptr),                 \
                                                (__target_mask_ptr),            \
                                                (__target_ptr),                 \
                                                (__stride))


__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_rgb565_blend_with_source_mask_and_opacity(
                                                uint16_t * __RESTRICT phwSource,
                                                uint8_t * __RESTRICT pchSourceMask,
                                                uint16_t * __RESTRICT phwTarget,
                                                size_t uStride,
                                                uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_rgb16__(uStride, vTailPred) {

        svuint16x3_t vSource16x4 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwSource));

        svuint16x3_t vTarget16x4 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwTarget));

        svuint16_t vSourceMask = svld1ub_u16(vTailPred, pchSourceMask);

        __arm_2d_sve_stride_ccc_foreach_chn__(vSource16x4, vTarget16x4,
        
            __svu16_target__ = __arm_2d_sve_chn_blend_with_mask_and_opacity(
                                                            __svu16_source__,
                                                            __svu16_target__,
                                                            vSourceMask,
                                                            hwOpacity);
        );

        svst1_u16(vTailPred, phwTarget, __arm_2d_sve_rgb565_pack(vTarget16x4));

        phwSource += __iteration_advance__;
        phwTarget += __iteration_advance__;
        pchSourceMask += __iteration_advance__;
    }
}



#define __arm_2d_sve_rgb565_blend_with_target_mask_and_opacity(                \
                                                    __source_ptr,               \
                                                    __target_ptr,               \
                                                    __target_mask_ptr,          \
                                                    __stride,                   \
                                                    __opacity)                  \
    __arm_2d_sve_rgb565_blend_with_source_mask_and_opacity(                    \
                                                (__source_ptr),                 \
                                                (__target_mask_ptr),            \
                                                (__target_ptr),                 \
                                                (__stride),                     \
                                                (__opacity))


__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_rgb565_blend_with_masks( uint16_t * __RESTRICT phwSource,
                                            uint8_t * __RESTRICT pchSourceMask,
                                            uint16_t * __RESTRICT phwTarget,
                                            uint8_t * __RESTRICT pchTargetMask,
                                            size_t uStride)
{
    __arm_2d_sve_stride_loop_rgb16__(uStride, vTailPred) {

        svuint16x3_t vSource16x4 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwSource));

        svuint16x3_t vTarget16x4 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwTarget));

        svuint16_t vSourceMask = svld1ub_u16(vTailPred, pchSourceMask);
        svuint16_t vTargetMask = svld1ub_u16(vTailPred, pchTargetMask);

        __arm_2d_sve_stride_ccc_foreach_chn__(vSource16x4, vTarget16x4,
        
            __svu16_target__ = __arm_2d_sve_chn_blend_with_masks(
                                                            __svu16_source__,
                                                            __svu16_target__,
                                                            vSourceMask,
                                                            vTargetMask);
        );

        svst1_u16(vTailPred, phwTarget, __arm_2d_sve_rgb565_pack(vTarget16x4));

        phwSource += __iteration_advance__;
        phwTarget += __iteration_advance__;
        pchSourceMask += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }

}


__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_rgb565_blend_with_masks_and_opacity(
                                                uint16_t * __RESTRICT phwSource,
                                                uint8_t * __RESTRICT pchSourceMask,
                                                uint16_t * __RESTRICT phwTarget,
                                                uint8_t * __RESTRICT pchTargetMask,
                                                size_t uStride,
                                                uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_rgb16__(uStride, vTailPred) {

        svuint16x3_t vSource16x4 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwSource));

        svuint16x3_t vTarget16x4 = 
            __arm_2d_sve_rgb565_unpack(svld1_u16(vTailPred, phwTarget));

        svuint16_t vSourceMask = svld1ub_u16(vTailPred, pchSourceMask);
        svuint16_t vTargetMask = svld1ub_u16(vTailPred, pchTargetMask);

        __arm_2d_sve_stride_ccc_foreach_chn__(vSource16x4, vTarget16x4,
        
            __svu16_target__ = __arm_2d_sve_chn_blend_with_masks_and_opacity(
                                                            __svu16_source__,
                                                            __svu16_target__,
                                                            vSourceMask,
                                                            vTargetMask,
                                                            hwOpacity);
        );

        svst1_u16(vTailPred, phwTarget, __arm_2d_sve_rgb565_pack(vTarget16x4));

        phwSource += __iteration_advance__;
        phwTarget += __iteration_advance__;
        pchSourceMask += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}


#if 0

/*----------------------------------------------------------------------------*
 * Blending with X mirroring                                                  *
 *----------------------------------------------------------------------------*/

__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_rgb565_reverse_blend(uint16_t * __RESTRICT pwSource,
                                        uint16_t * __RESTRICT pwTarget,
                                        size_t uStride)
{
    /* generate one pass addresses*/
    pwSource += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svbool_t vTailPredRev = svrev_b8(vTailPred);

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        pwSource -= __iteration_advance__;

        svld4ub_u16(vTailPredRev, 
                    (uint8_t *)pwSource, 
                    &vSourceLow16x4, 
                    &vSourceHigh16x4);

        /* process low half */
        __arm_2d_sve_stride_ccca_foreach_chn__( vSourceHigh16x4, 
                                                vTargetLow16x4,
            __svu16_target__ = svrev(__svu16_source__);
        );

        /* process high half */
        __arm_2d_sve_stride_ccca_foreach_chn__( vSourceLow16x4, 
                                                vTargetHigh16x4,
            __svu16_target__ = svrev(__svu16_source__);
        );

        svst4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwTarget += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_rgb565_reverse_blend_with_opacity(   
                                                uint16_t * __RESTRICT pwSource,
                                                uint16_t * __RESTRICT pwTarget,
                                                size_t uStride,
                                                uint16_t hwOpacity)
{
    /* generate one pass addresses*/
    pwSource += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svbool_t vTailPredRev = svrev_b8(vTailPred);

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        pwSource -= __iteration_advance__;

        svld4ub_u16(vTailPredRev, 
                    (uint8_t *)pwSource, 
                    &vSourceLow16x4, 
                    &vSourceHigh16x4);

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        /* process low half */
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceHigh16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_opacity(  svrev(__svu16_source__), 
                                                        __svu16_target__, 
                                                        hwOpacity);

        );

        /* process high half */
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceLow16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_opacity(  svrev(__svu16_source__), 
                                                        __svu16_target__, 
                                                        hwOpacity);
        );

        svst4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwTarget += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_rgb565_reverse_blend_with_source_mask(
                                                uint16_t * __RESTRICT pwSource,
                                                uint8_t * __RESTRICT pchSourceMask,
                                                uint16_t * __RESTRICT pwTarget,
                                                size_t uStride)
{
    /* generate one pass addresses*/
    pwSource += 1;
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svbool_t vTailPredRev = svrev_b8(vTailPred);

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        pwSource -= __iteration_advance__;
        svld4ub_u16(vTailPredRev, 
                    (uint8_t *)pwSource, 
                    &vSourceLow16x4, 
                    &vSourceHigh16x4);

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pchSourceMask -= __iteration_advance__;
        svuint8_t vu8SourceMask = svld1_u8(vTailPredRev, pchSourceMask);
        
        /* process low half */
        svuint16_t vSourceMaskHigh = svrev(svunpkhi_u16(vu8SourceMask));
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceHigh16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask( svrev(__svu16_source__), 
                                                    __svu16_target__,
                                                    vSourceMaskHigh);

        );

        /* process high half */
        svuint16_t vSourceMaskLow = svrev(svunpklo_u16(vu8SourceMask));
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceLow16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask( svrev(__svu16_source__), 
                                                    __svu16_target__, 
                                                    vSourceMaskLow);
        );

        svst4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwTarget += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_rgb565_reverse_blend_with_source_mask_and_opacity(
                                                uint16_t * __RESTRICT pwSource,
                                                uint8_t * __RESTRICT pchSourceMask,
                                                uint16_t * __RESTRICT pwTarget,
                                                size_t uStride,
                                                uint16_t hwOpacity)
{
    /* generate one pass addresses*/
    pwSource += 1;
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svbool_t vTailPredRev = svrev_b8(vTailPred);

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        pwSource -= __iteration_advance__;
        svld4ub_u16(vTailPredRev, 
                    (uint8_t *)pwSource, 
                    &vSourceLow16x4, 
                    &vSourceHigh16x4);

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pchSourceMask -= __iteration_advance__;
        svuint8_t vu8SourceMask = svld1_u8(vTailPredRev, pchSourceMask);
        
        /* process low half */
        svuint16_t vSourceMaskHigh = svrev(svunpkhi_u16(vu8SourceMask));
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceHigh16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask_and_opacity( 
                                                    svrev(__svu16_source__), 
                                                    __svu16_target__,
                                                    vSourceMaskHigh,
                                                    hwOpacity);

        );

        /* process high half */
        svuint16_t vSourceMaskLow = svrev(svunpklo_u16(vu8SourceMask));
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceLow16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask_and_opacity( 
                                                    svrev(__svu16_source__),
                                                    __svu16_target__, 
                                                    vSourceMaskLow,
                                                    hwOpacity);
        );

        svst4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwTarget += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_rgb565_reverse_blend_with_target_mask(
                                                uint16_t * __RESTRICT pwSource,
                                                uint16_t * __RESTRICT pwTarget,
                                                uint8_t * __RESTRICT pchTargetMask,
                                                size_t uStride)
{
    /* generate the one pass address*/
    pwSource += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svbool_t vTailPredRev = svrev_b8(vTailPred);

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        pwSource -= __iteration_advance__;
        svld4ub_u16(vTailPredRev, 
                    (uint8_t *)pwSource, 
                    &vSourceLow16x4, 
                    &vSourceHigh16x4);

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);
        
        /* process low half */
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceHigh16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask( svrev(__svu16_source__), 
                                                    __svu16_target__,
                                                    vTargetMaskLow);

        );

        /* process high half */
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceLow16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask( svrev(__svu16_source__), 
                                                    __svu16_target__, 
                                                    vTargetMaskHigh);
        );

        svst4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_rgb565_reverse_blend_with_target_mask_and_opacity(
                                                uint16_t * __RESTRICT pwSource,
                                                uint16_t * __RESTRICT pwTarget,
                                                uint8_t * __RESTRICT pchTargetMask,
                                                size_t uStride,
                                                uint16_t hwOpacity)
{
    /* generate the one pass address*/
    pwSource += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svbool_t vTailPredRev = svrev_b8(vTailPred);

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        pwSource -= __iteration_advance__;
        svld4ub_u16(vTailPredRev, 
                    (uint8_t *)pwSource, 
                    &vSourceLow16x4, 
                    &vSourceHigh16x4);

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);
        
        /* process low half */
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceHigh16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask_and_opacity( 
                                                    svrev(__svu16_source__), 
                                                    __svu16_target__,
                                                    vTargetMaskLow,
                                                    hwOpacity);

        );

        /* process high half */
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceLow16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask_and_opacity( 
                                                    svrev(__svu16_source__), 
                                                    __svu16_target__, 
                                                    vTargetMaskHigh,
                                                    hwOpacity);
        );

        svst4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_rgb565_reverse_blend_with_masks( 
                                            uint16_t * __RESTRICT pwSource,
                                            uint8_t * __RESTRICT pchSourceMask,
                                            uint16_t * __RESTRICT pwTarget,
                                            uint8_t * __RESTRICT pchTargetMask,
                                            size_t uStride)
{
    /* generate one pass addresses*/
    pwSource += 1;
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svbool_t vTailPredRev = svrev_b8(vTailPred);

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        pwSource -= __iteration_advance__;
        svld4ub_u16(vTailPredRev, 
                    (uint8_t *)pwSource, 
                    &vSourceLow16x4, 
                    &vSourceHigh16x4);

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pchSourceMask -= __iteration_advance__;
        svuint8_t vu8SourceMask = svld1_u8(vTailPredRev, pchSourceMask);
        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);

        /* process low half */
        svuint16_t vSourceMaskHigh = svrev(svunpkhi_u16(vu8SourceMask));
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceHigh16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_masks(svrev(__svu16_source__), 
                                                    __svu16_target__,
                                                    vSourceMaskHigh,
                                                    vTargetMaskLow);
        );

        /* process high half */
        svuint16_t vSourceMaskLow = svrev(svunpklo_u16(vu8SourceMask));
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceLow16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_masks(svrev(__svu16_source__), 
                                                    __svu16_target__, 
                                                    vSourceMaskLow,
                                                    vTargetMaskHigh);
        );

        svst4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}


__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_rgb565_reverse_blend_with_masks_and_opacity( 
                                            uint16_t * __RESTRICT pwSource,
                                            uint8_t * __RESTRICT pchSourceMask,
                                            uint16_t * __RESTRICT pwTarget,
                                            uint8_t * __RESTRICT pchTargetMask,
                                            size_t uStride,
                                            uint16_t hwOpacity)
{
    /* generate one pass addresses*/
    pwSource += 1;
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svbool_t vTailPredRev = svrev_b8(vTailPred);

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        pwSource -= __iteration_advance__;
        svld4ub_u16(vTailPredRev, 
                    (uint8_t *)pwSource, 
                    &vSourceLow16x4, 
                    &vSourceHigh16x4);

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pchSourceMask -= __iteration_advance__;
        svuint8_t vu8SourceMask = svld1_u8(vTailPredRev, pchSourceMask);
        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);

        /* process low half */
        svuint16_t vSourceMaskHigh = svrev(svunpkhi_u16(vu8SourceMask));
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceHigh16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_masks_and_opacity(
                                                    svrev(__svu16_source__), 
                                                    __svu16_target__,
                                                    vSourceMaskHigh,
                                                    vTargetMaskLow,
                                                    hwOpacity);
        );

        /* process high half */
        svuint16_t vSourceMaskLow = svrev(svunpklo_u16(vu8SourceMask));
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceLow16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_masks_and_opacity(
                                                    svrev(__svu16_source__), 
                                                    __svu16_target__, 
                                                    vSourceMaskLow,
                                                    vTargetMaskHigh,
                                                    hwOpacity);
        );

        svst4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}
#endif

#endif  /* __ARM_2D_SVE_STRIDE_RGB565_H__ */