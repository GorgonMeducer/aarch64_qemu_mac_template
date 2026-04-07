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

#if !defined(__ARM_2D_SVE_STRIDE_CCCN888_H__)                                   \
    && (defined(__ARM_FEATURE_SVE2)                                             \
    && __ARM_FEATURE_SVE2)
#define __ARM_2D_SVE_STRIDE_CCCN888_H__

/*----------------------------------------------------------------------------*
 * Colour Filling                                                             *
 *----------------------------------------------------------------------------*/
__STATIC_INLINE
ARM_NONNULL(1)
void __arm_2d_sve_cccn888_fill_colour(  uint32_t * __RESTRICT pwTarget,
                                        size_t uStride,
                                        uint32_t wColour)
{
    size_t n = 0;

    svuint32_t vColour = svdup_u32(wColour);
    do {
        svbool_t vTailPred = svwhilelt_b32(n, uStride);
        
        svst1_u32(vTailPred, pwTarget, vColour);
        
        pwTarget += svlenu32();
        n += svlenu32();
    } while(n < uStride);
}

__STATIC_INLINE
ARM_NONNULL(1)
void __arm_2d_sve_cccn888_fill_colour_with_opacity(   
                                                uint32_t * __RESTRICT pwTarget,
                                                size_t uStride,
                                                uint32_t wColour,
                                                uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        svuint16x4_t vColour16x4 = svcreate4_u16(
                                        svdup_u16( ((uint8_t *)&wColour)[0]),
                                        svdup_u16( ((uint8_t *)&wColour)[1]),
                                        svdup_u16( ((uint8_t *)&wColour)[2]),
                                        svdup_u16( ((uint8_t *)&wColour)[3]));

        /* process low half */
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vColour16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_opacity(  __svu16_source__, 
                                                        __svu16_target__, 
                                                        hwOpacity);

        );

        /* process high half */
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vColour16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_opacity(  __svu16_source__, 
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
ARM_NONNULL(1)
void __arm_2d_sve_cccn888_fill_colour_with_source_mask(   
                                                uint32_t * __RESTRICT pwTarget,
                                                uint8_t * __RESTRICT pchMask,
                                                size_t uStride,
                                                uint32_t wColour)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        svuint8_t vu8Mask = svld1_u8(vTailPred, pchMask);
        svuint16x4_t vColour16x4 = svcreate4_u16(
                                        svdup_u16( ((uint8_t *)&wColour)[0]),
                                        svdup_u16( ((uint8_t *)&wColour)[1]),
                                        svdup_u16( ((uint8_t *)&wColour)[2]),
                                        svdup_u16( ((uint8_t *)&wColour)[3]));

        /* process low half */
        svuint16_t vMaskLow = svunpklo_u16(vu8Mask);
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vColour16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask( __svu16_source__, 
                                                    __svu16_target__, 
                                                    vMaskLow);

        );

        /* process high half */
        svuint16_t vMaskHigh = svunpkhi_u16(vu8Mask);

        __arm_2d_sve_stride_ccca_foreach_chn012__(  vColour16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask( __svu16_source__, 
                                                    __svu16_target__, 
                                                    vMaskHigh);
        );

        svst4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwTarget += __iteration_advance__;
        pchMask += __iteration_advance__;
    }
}


__STATIC_INLINE
ARM_NONNULL(1)
void __arm_2d_sve_cccn888_fill_colour_with_source_mask_and_opacity(   
                                                uint32_t * __RESTRICT pwTarget,
                                                uint8_t * __RESTRICT pchMask,
                                                size_t uStride,
                                                uint32_t wColour,
                                                uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        svuint8_t vu8Mask = svld1_u8(vTailPred, pchMask);
        svuint16x4_t vColour16x4 = svcreate4_u16(
                                        svdup_u16( ((uint8_t *)&wColour)[0]),
                                        svdup_u16( ((uint8_t *)&wColour)[1]),
                                        svdup_u16( ((uint8_t *)&wColour)[2]),
                                        svdup_u16( ((uint8_t *)&wColour)[3]));

        /* process low half */
        svuint16_t vMaskLow = svunpklo_u16(vu8Mask);
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vColour16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask_and_opacity( 
                                                    __svu16_source__, 
                                                    __svu16_target__, 
                                                    vMaskLow,
                                                    hwOpacity);

        );

        /* process high half */
        svuint16_t vMaskHigh = svunpkhi_u16(vu8Mask);

        __arm_2d_sve_stride_ccca_foreach_chn012__(  vColour16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask_and_opacity( 
                                                    __svu16_source__, 
                                                    __svu16_target__, 
                                                    vMaskHigh,
                                                    hwOpacity);
        );

        svst4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwTarget += __iteration_advance__;
        pchMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1)
void __arm_2d_sve_cccn888_fill_colour_with_masks(   
                                            uint32_t * __RESTRICT pwTarget,
                                            uint8_t * __RESTRICT pchSourceMask,
                                            uint8_t * __RESTRICT pchTargetMask,
                                            size_t uStride,
                                            uint32_t wColour)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        svuint8_t vu8SourceMask = svld1_u8(vTailPred, pchSourceMask);
        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);
        svuint16x4_t vColour16x4 = svcreate4_u16(
                                        svdup_u16( ((uint8_t *)&wColour)[0]),
                                        svdup_u16( ((uint8_t *)&wColour)[1]),
                                        svdup_u16( ((uint8_t *)&wColour)[2]),
                                        svdup_u16( ((uint8_t *)&wColour)[3]));

        /* process low half */
        svuint16_t vSourceMaskLow = svunpklo_u16(vu8SourceMask);
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vColour16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_masks(__svu16_source__, 
                                                    __svu16_target__, 
                                                    vSourceMaskLow,
                                                    vTargetMaskLow);

        );

        /* process high half */
        svuint16_t vSourceMaskHigh = svunpkhi_u16(vu8SourceMask);
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);

        __arm_2d_sve_stride_ccca_foreach_chn012__(  vColour16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_masks(__svu16_source__, 
                                                    __svu16_target__, 
                                                    vSourceMaskHigh,
                                                    vTargetMaskHigh);
        );

        svst4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwTarget += __iteration_advance__;
        pchSourceMask += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1)
void __arm_2d_sve_cccn888_fill_colour_with_masks_and_opacity(   
                                            uint32_t * __RESTRICT pwTarget,
                                            uint8_t * __RESTRICT pchSourceMask,
                                            uint8_t * __RESTRICT pchTargetMask,
                                            size_t uStride,
                                            uint32_t wColour,
                                            uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        svuint8_t vu8SourceMask = svld1_u8(vTailPred, pchSourceMask);
        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);
        svuint16x4_t vColour16x4 = svcreate4_u16(
                                        svdup_u16( ((uint8_t *)&wColour)[0]),
                                        svdup_u16( ((uint8_t *)&wColour)[1]),
                                        svdup_u16( ((uint8_t *)&wColour)[2]),
                                        svdup_u16( ((uint8_t *)&wColour)[3]));

        /* process low half */
        svuint16_t vSourceMaskLow = svunpklo_u16(vu8SourceMask);
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vColour16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_masks_and_opacity( 
                                                    __svu16_source__, 
                                                    __svu16_target__, 
                                                    vSourceMaskLow,
                                                    vTargetMaskLow,
                                                    hwOpacity);

        );

        /* process high half */
        svuint16_t vSourceMaskHigh = svunpkhi_u16(vu8SourceMask);
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);

        __arm_2d_sve_stride_ccca_foreach_chn012__(  vColour16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_masks_and_opacity( 
                                                    __svu16_source__, 
                                                    __svu16_target__, 
                                                    vSourceMaskHigh,
                                                    vTargetMaskHigh,
                                                    hwOpacity);
        );

        svst4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwTarget += __iteration_advance__;
        pchSourceMask += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}


/*----------------------------------------------------------------------------*
 * Colour Filling with X Mirroring                                            *
 *----------------------------------------------------------------------------*/

__STATIC_INLINE
ARM_NONNULL(1)
void __arm_2d_sve_cccn888_reverse_fill_colour_with_source_mask(   
                                                uint32_t * __RESTRICT pwTarget,
                                                uint8_t * __RESTRICT pchMask,
                                                size_t uStride,
                                                uint32_t wColour)
{
    /* generate one-pass address */
    pchMask += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pchMask -= __iteration_advance__;
        svuint8_t vu8Mask = svld1_u8(svrev_b8(vTailPred), pchMask);

        svuint16x4_t vColour16x4 = svcreate4_u16(
                                        svdup_u16( ((uint8_t *)&wColour)[0]),
                                        svdup_u16( ((uint8_t *)&wColour)[1]),
                                        svdup_u16( ((uint8_t *)&wColour)[2]),
                                        svdup_u16( ((uint8_t *)&wColour)[3]));

        /* process low half */
        svuint16_t vMaskHigh = svrev(svunpkhi_u16(vu8Mask));
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vColour16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask( __svu16_source__, 
                                                    __svu16_target__, 
                                                    vMaskHigh);

        );

        /* process high half */
        svuint16_t vMaskLow = svrev(svunpklo_u16(vu8Mask));

        __arm_2d_sve_stride_ccca_foreach_chn012__(  vColour16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask( __svu16_source__, 
                                                    __svu16_target__, 
                                                    vMaskLow);
        );

        svst4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwTarget += __iteration_advance__;
    }
}


__STATIC_INLINE
ARM_NONNULL(1)
void __arm_2d_sve_cccn888_reverse_fill_colour_with_source_mask_and_opacity(   
                                                uint32_t * __RESTRICT pwTarget,
                                                uint8_t * __RESTRICT pchMask,
                                                size_t uStride,
                                                uint32_t wColour,
                                                uint16_t hwOpacity)
{
    /* generate one-pass address */
    pchMask += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pchMask -= __iteration_advance__;
        svuint8_t vu8Mask = svld1_u8(svrev_b8(vTailPred), pchMask);

        svuint16x4_t vColour16x4 = svcreate4_u16(
                                        svdup_u16( ((uint8_t *)&wColour)[0]),
                                        svdup_u16( ((uint8_t *)&wColour)[1]),
                                        svdup_u16( ((uint8_t *)&wColour)[2]),
                                        svdup_u16( ((uint8_t *)&wColour)[3]));

        /* process low half */
        svuint16_t vMaskHigh = svrev(svunpkhi_u16(vu8Mask));
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vColour16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask_and_opacity( 
                                                    __svu16_source__, 
                                                    __svu16_target__, 
                                                    vMaskHigh,
                                                    hwOpacity);

        );

        /* process high half */
        svuint16_t vMaskLow = svrev(svunpklo_u16(vu8Mask));

        __arm_2d_sve_stride_ccca_foreach_chn012__(  vColour16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask_and_opacity( 
                                                    __svu16_source__, 
                                                    __svu16_target__, 
                                                    vMaskLow,
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
ARM_NONNULL(1)
void __arm_2d_sve_cccn888_reverse_fill_colour_with_masks(   
                                            uint32_t * __RESTRICT pwTarget,
                                            uint8_t * __RESTRICT pchSourceMask,
                                            uint8_t * __RESTRICT pchTargetMask,
                                            size_t uStride,
                                            uint32_t wColour)
{
    /* generate the one pass address for the source mask only */
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pchSourceMask -= __iteration_advance__;
        svuint8_t vu8SourceMask = svld1_u8(svrev_b8(vTailPred), pchSourceMask);
        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);
        svuint16x4_t vColour16x4 = svcreate4_u16(
                                        svdup_u16( ((uint8_t *)&wColour)[0]),
                                        svdup_u16( ((uint8_t *)&wColour)[1]),
                                        svdup_u16( ((uint8_t *)&wColour)[2]),
                                        svdup_u16( ((uint8_t *)&wColour)[3]));

        /* process low half */
        svuint16_t vSourceMaskHigh = svrev(svunpkhi_u16(vu8SourceMask));
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vColour16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_masks(__svu16_source__, 
                                                    __svu16_target__, 
                                                    vSourceMaskHigh,
                                                    vTargetMaskLow);

        );

        /* process high half */
        svuint16_t vSourceMaskLow = svrev(svunpklo_u16(vu8SourceMask));
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);

        __arm_2d_sve_stride_ccca_foreach_chn012__(  vColour16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_masks(__svu16_source__, 
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
ARM_NONNULL(1)
void __arm_2d_sve_cccn888_reverse_fill_colour_with_masks_and_opacity(   
                                            uint32_t * __RESTRICT pwTarget,
                                            uint8_t * __RESTRICT pchSourceMask,
                                            uint8_t * __RESTRICT pchTargetMask,
                                            size_t uStride,
                                            uint32_t wColour,
                                            uint16_t hwOpacity)
{
    /* generate the one pass address for the source mask only */
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pchSourceMask -= __iteration_advance__;
        svuint8_t vu8SourceMask = svld1_u8(svrev_b8(vTailPred), pchSourceMask);
        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);
        svuint16x4_t vColour16x4 = svcreate4_u16(
                                        svdup_u16( ((uint8_t *)&wColour)[0]),
                                        svdup_u16( ((uint8_t *)&wColour)[1]),
                                        svdup_u16( ((uint8_t *)&wColour)[2]),
                                        svdup_u16( ((uint8_t *)&wColour)[3]));

        /* process low half */
        svuint16_t vSourceMaskHigh = svrev(svunpkhi_u16(vu8SourceMask));
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vColour16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_masks_and_opacity( 
                                                    __svu16_source__, 
                                                    __svu16_target__, 
                                                    vSourceMaskHigh,
                                                    vTargetMaskLow,
                                                    hwOpacity);

        );

        /* process high half */
        svuint16_t vSourceMaskLow = svrev(svunpklo_u16(vu8SourceMask));
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);

        __arm_2d_sve_stride_ccca_foreach_chn012__(  vColour16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_masks_and_opacity( 
                                                    __svu16_source__, 
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

/*----------------------------------------------------------------------------*
 * Blending                                                                   *
 *----------------------------------------------------------------------------*/


__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_cccn888_blend(uint32_t * __RESTRICT pwSource,
                                uint32_t * __RESTRICT pwTarget,
                                size_t uStride)
{
    size_t n = 0;

    do {
        svbool_t vTailPred = svwhilelt_b32(n, uStride);
        
        svst1_u32(  vTailPred, 
                    pwTarget, 
                    svld1_u32(vTailPred, pwSource));
        
        pwTarget += svlenu32();
        pwSource += svlenu32();
        n += svlenu32();
    } while(n < uStride);
}

__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_cccn888_blend_with_opacity(   uint32_t * __RESTRICT pwSource,
                                                uint32_t * __RESTRICT pwTarget,
                                                size_t uStride,
                                                uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwSource, 
                    &vSourceLow16x4, 
                    &vSourceHigh16x4);

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        /* process low half */
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceLow16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_opacity(  __svu16_source__, 
                                                        __svu16_target__, 
                                                        hwOpacity);

        );

        /* process high half */
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceHigh16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_opacity(  __svu16_source__, 
                                                        __svu16_target__, 
                                                        hwOpacity);
        );

        svst4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwSource += __iteration_advance__;
        pwTarget += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_cccn888_blend_with_source_mask(uint32_t * __RESTRICT pwSource,
                                                 uint8_t * __RESTRICT pchMask,
                                                 uint32_t * __RESTRICT pwTarget,
                                                 size_t uStride)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwSource, 
                    &vSourceLow16x4, 
                    &vSourceHigh16x4);

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        svuint8_t vu8Mask = svld1_u8(vTailPred, pchMask);
        svuint16_t vMaskLow = svunpklo_u16(vu8Mask);

        /* process low half */
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceLow16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask( __svu16_source__, 
                                                    __svu16_target__,
                                                    vMaskLow);

        );

        svuint16_t vMaskHigh = svunpkhi_u16(vu8Mask);

        /* process high half */
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceHigh16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask( __svu16_source__, 
                                                    __svu16_target__, 
                                                    vMaskHigh);
        );

        svst4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwSource += __iteration_advance__;
        pwTarget += __iteration_advance__;
        pchMask  += __iteration_advance__;
    }
}

#define __arm_2d_sve_cccn888_blend_with_target_mask(__source_ptr,               \
                                                    __target_ptr,               \
                                                    __target_mask_ptr,          \
                                                    __stride)                   \
    __arm_2d_sve_cccn888_blend_with_source_mask((__source_ptr),                 \
                                                (__target_mask_ptr),            \
                                                (__target_ptr),                 \
                                                (__stride))

__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_cccn888_blend_with_source_mask_and_opacity(
                                                uint32_t * __RESTRICT pwSource,
                                                uint8_t * __RESTRICT pchMask,
                                                uint32_t * __RESTRICT pwTarget,
                                                size_t uStride,
                                                uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwSource, 
                    &vSourceLow16x4, 
                    &vSourceHigh16x4);

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        svuint8_t vu8Mask = svld1_u8(vTailPred, pchMask);
        svuint16_t vMaskLow = svunpklo_u16(vu8Mask);

        /* process low half */
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceLow16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask_and_opacity( 
                                                            __svu16_source__, 
                                                            __svu16_target__,
                                                            vMaskLow,
                                                            hwOpacity);
        );

        svuint16_t vMaskHigh = svunpkhi_u16(vu8Mask);
        /* process high half */
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceHigh16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask_and_opacity( 
                                                            __svu16_source__, 
                                                            __svu16_target__, 
                                                            vMaskHigh,
                                                            hwOpacity);
        );

        svst4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwSource += __iteration_advance__;
        pwTarget += __iteration_advance__;
        pchMask  += __iteration_advance__;
    }
}

#define __arm_2d_sve_cccn888_blend_with_target_mask_and_opacity(                \
                                                    __source_ptr,               \
                                                    __target_ptr,               \
                                                    __target_mask_ptr,          \
                                                    __stride,                   \
                                                    __opacity)                  \
    __arm_2d_sve_cccn888_blend_with_source_mask_and_opacity(                    \
                                                (__source_ptr),                 \
                                                (__target_mask_ptr),            \
                                                (__target_ptr),                 \
                                                (__stride),                     \
                                                (__opacity))

__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_cccn888_blend_with_masks( uint32_t * __RESTRICT pwSource,
                                            uint8_t * __RESTRICT pchSourceMask,
                                            uint32_t * __RESTRICT pwTarget,
                                            uint8_t * __RESTRICT pchTargetMask,
                                            size_t uStride)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwSource, 
                    &vSourceLow16x4, 
                    &vSourceHigh16x4);

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        svuint8_t vu8SourceMask = svld1_u8(vTailPred, pchSourceMask);
        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);

        /* process low half */
        svuint16_t vSourceMaskLow = svunpklo_u16(vu8SourceMask);
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceLow16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_masks(__svu16_source__, 
                                                    __svu16_target__,
                                                    vSourceMaskLow,
                                                    vTargetMaskLow);
        );

        /* process high half */
        svuint16_t vSourceMaskHigh = svunpkhi_u16(vu8SourceMask);
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceHigh16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_masks(__svu16_source__, 
                                                    __svu16_target__, 
                                                    vSourceMaskHigh,
                                                    vTargetMaskHigh);
        );

        svst4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwSource += __iteration_advance__;
        pwTarget += __iteration_advance__;
        pchSourceMask += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}


__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_cccn888_blend_with_masks_and_opacity(
                                                uint32_t * __RESTRICT pwSource,
                                                uint8_t * __RESTRICT pchSourceMask,
                                                uint32_t * __RESTRICT pwTarget,
                                                uint8_t * __RESTRICT pchTargetMask,
                                                size_t uStride,
                                                uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwSource, 
                    &vSourceLow16x4, 
                    &vSourceHigh16x4);

        svld4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        svuint8_t vu8SourceMask = svld1_u8(vTailPred, pchSourceMask);
        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);

        /* process low half */
        svuint16_t vSourceMaskLow = svunpklo_u16(vu8SourceMask);
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);

        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceLow16x4, 
                                                    vTargetLow16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_masks_and_opacity( 
                                                            __svu16_source__, 
                                                            __svu16_target__,
                                                            vSourceMaskLow,
                                                            vTargetMaskLow,
                                                            hwOpacity);
        );

        /* process high half */
        svuint16_t vSourceMaskHigh = svunpkhi_u16(vu8SourceMask);
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        
        __arm_2d_sve_stride_ccca_foreach_chn012__(  vSourceHigh16x4, 
                                                    vTargetHigh16x4,

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_masks_and_opacity( 
                                                            __svu16_source__, 
                                                            __svu16_target__, 
                                                            vSourceMaskHigh,
                                                            vTargetMaskHigh,
                                                            hwOpacity);
        );

        svst4ub_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwSource += __iteration_advance__;
        pwTarget += __iteration_advance__;
        pchSourceMask += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}


/*----------------------------------------------------------------------------*
 * Blending with X mirroring                                                  *
 *----------------------------------------------------------------------------*/

__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_cccn888_reverse_blend(uint32_t * __RESTRICT pwSource,
                                        uint32_t * __RESTRICT pwTarget,
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
void __arm_2d_sve_cccn888_reverse_blend_with_opacity(   
                                                uint32_t * __RESTRICT pwSource,
                                                uint32_t * __RESTRICT pwTarget,
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
void __arm_2d_sve_cccn888_reverse_blend_with_source_mask(
                                                uint32_t * __RESTRICT pwSource,
                                                uint8_t * __RESTRICT pchSourceMask,
                                                uint32_t * __RESTRICT pwTarget,
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
void __arm_2d_sve_cccn888_reverse_blend_with_source_mask_and_opacity(
                                                uint32_t * __RESTRICT pwSource,
                                                uint8_t * __RESTRICT pchSourceMask,
                                                uint32_t * __RESTRICT pwTarget,
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
void __arm_2d_sve_cccn888_reverse_blend_with_target_mask(
                                                uint32_t * __RESTRICT pwSource,
                                                uint32_t * __RESTRICT pwTarget,
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
void __arm_2d_sve_cccn888_reverse_blend_with_target_mask_and_opacity(
                                                uint32_t * __RESTRICT pwSource,
                                                uint32_t * __RESTRICT pwTarget,
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
void __arm_2d_sve_cccn888_reverse_blend_with_masks( 
                                            uint32_t * __RESTRICT pwSource,
                                            uint8_t * __RESTRICT pchSourceMask,
                                            uint32_t * __RESTRICT pwTarget,
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
void __arm_2d_sve_cccn888_reverse_blend_with_masks_and_opacity( 
                                            uint32_t * __RESTRICT pwSource,
                                            uint8_t * __RESTRICT pchSourceMask,
                                            uint32_t * __RESTRICT pwTarget,
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