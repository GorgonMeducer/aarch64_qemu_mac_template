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

#if !defined(__ARM_2D_SVE_STRIDE_CCCA8888_H__) && (defined(__ARM_FEATURE_SVE2) && __ARM_FEATURE_SVE2)
#define __ARM_2D_SVE_STRIDE_CCCN8888_H__

/*----------------------------------------------------------------------------*
 * Blending to CCCN888                                                        *
 *----------------------------------------------------------------------------*/

__STATIC_INLINE
ARM_NONNULL(1, 2)
void __arm_2d_sve_ccca8888_blend_to_cccn888(uint32_t *__RESTRICT pwSource,
                                            uint32_t *__RESTRICT pwTarget,
                                            size_t uStride)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

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
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceLow16x4,
                                                 vTargetLow16x4,

                                                 svuint16_t vMask = svget4(vSourceLow16x4, 3);

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_mask(__svu16_source__,
                                                                                                     __svu16_target__,
                                                                                                     vMask);

        );

        /* process high half */
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceHigh16x4,
                                                 vTargetHigh16x4,

                                                 svuint16_t vMask = svget4(vSourceHigh16x4, 3);

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_mask(__svu16_source__,
                                                                                                     __svu16_target__,
                                                                                                     vMask););

        svst4ub_u16(vTailPred,
                    (uint8_t *)pwTarget,
                    vTargetLow16x4,
                    vTargetHigh16x4);

        pwSource += __iteration_advance__;
        pwTarget += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2)
void __arm_2d_sve_ccca8888_blend_to_cccn888_with_opacity(
    uint32_t *__RESTRICT pwSource,
    uint32_t *__RESTRICT pwTarget,
    size_t uStride,
    uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

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
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceLow16x4,
                                                 vTargetLow16x4,

                                                 svuint16_t vMask = svget4(vSourceLow16x4, 3);

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_mask_and_opacity(
                                                     __svu16_source__,
                                                     __svu16_target__,
                                                     vMask,
                                                     hwOpacity););

        /* process high half */
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceHigh16x4,
                                                 vTargetHigh16x4,

                                                 svuint16_t vMask = svget4(vSourceHigh16x4, 3);

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_mask_and_opacity(
                                                     __svu16_source__,
                                                     __svu16_target__,
                                                     vMask,
                                                     hwOpacity););

        svst4ub_u16(vTailPred,
                    (uint8_t *)pwTarget,
                    vTargetLow16x4,
                    vTargetHigh16x4);

        pwSource += __iteration_advance__;
        pwTarget += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3)
void __arm_2d_sve_ccca8888_blend_to_cccn888_with_target_mask(
    uint32_t *__RESTRICT pwSource,
    uint32_t *__RESTRICT pwTarget,
    uint8_t *__RESTRICT pchTargetMask,
    size_t uStride)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

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

        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);

        /* process low half */
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceLow16x4,
                                                 vTargetLow16x4,

                                                 svuint16_t vMask = svget4(vSourceLow16x4, 3);

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_masks(__svu16_source__,
                                                                                                      __svu16_target__,
                                                                                                      vMask,
                                                                                                      vTargetMaskLow););

        /* process high half */
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceHigh16x4,
                                                 vTargetHigh16x4,

                                                 svuint16_t vMask = svget4(vSourceHigh16x4, 3);

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_masks(
                                                     __svu16_source__,
                                                     __svu16_target__,
                                                     vMask,
                                                     vTargetMaskHigh););

        svst4ub_u16(vTailPred,
                    (uint8_t *)pwTarget,
                    vTargetLow16x4,
                    vTargetHigh16x4);

        pwSource += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
        pwTarget += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3)
void __arm_2d_sve_ccca8888_blend_to_cccn888_with_source_mask(
    uint32_t *__RESTRICT pwSource,
    uint8_t *__RESTRICT pchSourceMask,
    uint32_t *__RESTRICT pwTarget,
    size_t uStride)
{
    return __arm_2d_sve_ccca8888_blend_to_cccn888_with_target_mask(pwSource,
                                                                   pwTarget,
                                                                   pchSourceMask,
                                                                   uStride);
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3)
void __arm_2d_sve_ccca8888_blend_to_cccn888_with_target_mask_and_opacity(
    uint32_t *__RESTRICT pwSource,
    uint32_t *__RESTRICT pwTarget,
    uint8_t *__RESTRICT pchTargetMask,
    size_t uStride,
    uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

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

        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);

        /* process low half */
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceLow16x4,
                                                 vTargetLow16x4,

                                                 svuint16_t vMask = svget4(vSourceLow16x4, 3);

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_masks_and_opacity(
                                                     __svu16_source__,
                                                     __svu16_target__,
                                                     vMask,
                                                     vTargetMaskLow,
                                                     hwOpacity););

        /* process high half */
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceHigh16x4,
                                                 vTargetHigh16x4,

                                                 svuint16_t vMask = svget4(vSourceHigh16x4, 3);

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_masks_and_opacity(
                                                     __svu16_source__,
                                                     __svu16_target__,
                                                     vMask,
                                                     vTargetMaskHigh,
                                                     hwOpacity););

        svst4ub_u16(vTailPred,
                    (uint8_t *)pwTarget,
                    vTargetLow16x4,
                    vTargetHigh16x4);

        pwSource += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
        pwTarget += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3)
void __arm_2d_sve_ccca8888_blend_to_cccn888_with_source_mask_and_opacity(
    uint32_t *__RESTRICT pwSource,
    uint8_t *__RESTRICT pchSourceMask,
    uint32_t *__RESTRICT pwTarget,
    size_t uStride,
    uint16_t hwOpacity)
{
    return __arm_2d_sve_ccca8888_blend_to_cccn888_with_target_mask_and_opacity(
        pwSource,
        pwTarget,
        pchSourceMask,
        uStride,
        hwOpacity);
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3, 4)
void __arm_2d_sve_ccca8888_blend_to_cccn888_with_masks_and_opacity(
    uint32_t *__RESTRICT pwSource,
    uint8_t *__RESTRICT pchSourceMask,
    uint32_t *__RESTRICT pwTarget,
    uint8_t *__RESTRICT pchTargetMask,
    size_t uStride,
    uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

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
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceLow16x4,
                                                 vTargetLow16x4,

                                                 svuint16_t vMask = svget4(vSourceLow16x4, 3);

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_3masks_and_opacity(
                                                     __svu16_source__,
                                                     __svu16_target__,
                                                     vMask,
                                                     vSourceMaskLow,
                                                     vTargetMaskLow,
                                                     hwOpacity););

        /* process high half */
        svuint16_t vSourceMaskHigh = svunpkhi_u16(vu8SourceMask);
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceHigh16x4,
                                                 vTargetHigh16x4,

                                                 svuint16_t vMask = svget4(vSourceHigh16x4, 3);

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_3masks_and_opacity(
                                                     __svu16_source__,
                                                     __svu16_target__,
                                                     vMask,
                                                     vSourceMaskHigh,
                                                     vTargetMaskHigh,
                                                     hwOpacity););

        svst4ub_u16(vTailPred,
                    (uint8_t *)pwTarget,
                    vTargetLow16x4,
                    vTargetHigh16x4);

        pwSource += __iteration_advance__;
        pchSourceMask += __iteration_advance__;
        pwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3, 4)
void __arm_2d_sve_ccca8888_blend_to_cccn888_with_masks(
    uint32_t *__RESTRICT pwSource,
    uint8_t *__RESTRICT pchSourceMask,
    uint32_t *__RESTRICT pwTarget,
    uint8_t *__RESTRICT pchTargetMask,
    size_t uStride)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

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
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceLow16x4,
                                                 vTargetLow16x4,

                                                 svuint16_t vMask = svget4(vSourceLow16x4, 3);

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_3masks(
                                                     __svu16_source__,
                                                     __svu16_target__,
                                                     vMask,
                                                     vSourceMaskLow,
                                                     vTargetMaskLow););

        /* process high half */
        svuint16_t vSourceMaskHigh = svunpkhi_u16(vu8SourceMask);
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceHigh16x4,
                                                 vTargetHigh16x4,

                                                 svuint16_t vMask = svget4(vSourceHigh16x4, 3);

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_3masks(
                                                     __svu16_source__,
                                                     __svu16_target__,
                                                     vMask,
                                                     vSourceMaskHigh,
                                                     vTargetMaskHigh););

        svst4ub_u16(vTailPred,
                    (uint8_t *)pwTarget,
                    vTargetLow16x4,
                    vTargetHigh16x4);

        pwSource += __iteration_advance__;
        pchSourceMask += __iteration_advance__;
        pwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

/*----------------------------------------------------------------------------*
 * Blending to CCCN888 with X-mirroring                                       *
 *----------------------------------------------------------------------------*/

__STATIC_INLINE
ARM_NONNULL(1, 2, 3, 4)
void __arm_2d_sve_ccca8888_reserve_blend_to_cccn888_with_masks_and_opacity(
    uint32_t *__RESTRICT pwSource,
    uint8_t *__RESTRICT pchSourceMask,
    uint32_t *__RESTRICT pwTarget,
    uint8_t *__RESTRICT pchTargetMask,
    size_t uStride,
    uint16_t hwOpacity)
{
    /* generate one-pass addresses */
    pwSource += 1;
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

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
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceHigh16x4,
                                                 vTargetLow16x4,

                                                 svuint16_t vMask = svrev(svget4(vSourceHigh16x4, 3));

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_3masks_and_opacity(
                                                     svrev(__svu16_source__),
                                                     __svu16_target__,
                                                     vMask,
                                                     vSourceMaskHigh,
                                                     vTargetMaskLow,
                                                     hwOpacity););

        /* process high half */
        svuint16_t vSourceMaskLow = svrev(svunpklo_u16(vu8SourceMask));
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceLow16x4,
                                                 vTargetHigh16x4,

                                                 svuint16_t vMask = svrev(svget4(vSourceLow16x4, 3));

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_3masks_and_opacity(
                                                     svrev(__svu16_source__),
                                                     __svu16_target__,
                                                     vMask,
                                                     vSourceMaskLow,
                                                     vTargetMaskHigh,
                                                     hwOpacity););

        svst4ub_u16(vTailPred,
                    (uint8_t *)pwTarget,
                    vTargetLow16x4,
                    vTargetHigh16x4);

        pwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3, 4)
void __arm_2d_sve_ccca8888_reserve_blend_to_cccn888_with_masks(
    uint32_t *__RESTRICT pwSource,
    uint8_t *__RESTRICT pchSourceMask,
    uint32_t *__RESTRICT pwTarget,
    uint8_t *__RESTRICT pchTargetMask,
    size_t uStride)
{
    /* generate one-pass addresses */
    pwSource += 1;
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

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
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceHigh16x4,
                                                 vTargetLow16x4,

                                                 svuint16_t vMask = svrev(svget4(vSourceHigh16x4, 3));

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_3masks(
                                                     svrev(__svu16_source__),
                                                     __svu16_target__,
                                                     vMask,
                                                     vSourceMaskHigh,
                                                     vTargetMaskLow););

        /* process high half */
        svuint16_t vSourceMaskLow = svrev(svunpklo_u16(vu8SourceMask));
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceLow16x4,
                                                 vTargetHigh16x4,

                                                 svuint16_t vMask = svrev(svget4(vSourceLow16x4, 3));

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_3masks(
                                                     svrev(__svu16_source__),
                                                     __svu16_target__,
                                                     vMask,
                                                     vSourceMaskLow,
                                                     vTargetMaskHigh););

        svst4ub_u16(vTailPred,
                    (uint8_t *)pwTarget,
                    vTargetLow16x4,
                    vTargetHigh16x4);

        pwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3)
void __arm_2d_sve_ccca8888_reserve_blend_to_cccn888_with_source_mask_and_opacity(
    uint32_t *__RESTRICT pwSource,
    uint8_t *__RESTRICT pchSourceMask,
    uint32_t *__RESTRICT pwTarget,
    size_t uStride,
    uint16_t hwOpacity)
{
    /* generate one-pass addresses */
    pwSource += 1;
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

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
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceHigh16x4,
                                                 vTargetLow16x4,

                                                 svuint16_t vMask = svrev(svget4(vSourceHigh16x4, 3));

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_masks_and_opacity(
                                                     svrev(__svu16_source__),
                                                     __svu16_target__,
                                                     vMask,
                                                     vSourceMaskHigh,
                                                     hwOpacity););

        /* process high half */
        svuint16_t vSourceMaskLow = svrev(svunpklo_u16(vu8SourceMask));
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceLow16x4,
                                                 vTargetHigh16x4,

                                                 svuint16_t vMask = svrev(svget4(vSourceLow16x4, 3));

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_masks_and_opacity(
                                                     svrev(__svu16_source__),
                                                     __svu16_target__,
                                                     vMask,
                                                     vSourceMaskLow,
                                                     hwOpacity););

        svst4ub_u16(vTailPred,
                    (uint8_t *)pwTarget,
                    vTargetLow16x4,
                    vTargetHigh16x4);

        pwTarget += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3)
void __arm_2d_sve_ccca8888_reserve_blend_to_cccn888_with_source_mask(
    uint32_t *__RESTRICT pwSource,
    uint8_t *__RESTRICT pchSourceMask,
    uint32_t *__RESTRICT pwTarget,
    size_t uStride)
{
    /* generate one-pass addresses */
    pwSource += 1;
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

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
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceHigh16x4,
                                                 vTargetLow16x4,

                                                 svuint16_t vMask = svrev(svget4(vSourceHigh16x4, 3));

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_masks(svrev(__svu16_source__),
                                                                                                      __svu16_target__,
                                                                                                      vMask,
                                                                                                      vSourceMaskHigh););

        /* process high half */
        svuint16_t vSourceMaskLow = svrev(svunpklo_u16(vu8SourceMask));
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceLow16x4,
                                                 vTargetHigh16x4,

                                                 svuint16_t vMask = svrev(svget4(vSourceLow16x4, 3));

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_masks(svrev(__svu16_source__),
                                                                                                      __svu16_target__,
                                                                                                      vMask,
                                                                                                      vSourceMaskLow););

        svst4ub_u16(vTailPred,
                    (uint8_t *)pwTarget,
                    vTargetLow16x4,
                    vTargetHigh16x4);

        pwTarget += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3)
void __arm_2d_sve_ccca8888_reserve_blend_to_cccn888_with_target_mask_and_opacity(
    uint32_t *__RESTRICT pwSource,
    uint32_t *__RESTRICT pwTarget,
    uint8_t *__RESTRICT pchTargetMask,
    size_t uStride,
    uint16_t hwOpacity)
{
    /* generate one-pass addresses */
    pwSource += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

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
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceHigh16x4,
                                                 vTargetLow16x4,

                                                 svuint16_t vMask = svrev(svget4(vSourceHigh16x4, 3));

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_masks_and_opacity(
                                                     svrev(__svu16_source__),
                                                     __svu16_target__,
                                                     vMask,
                                                     vTargetMaskLow,
                                                     hwOpacity););

        /* process high half */
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceLow16x4,
                                                 vTargetHigh16x4,

                                                 svuint16_t vMask = svrev(svget4(vSourceLow16x4, 3));

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_masks_and_opacity(
                                                     svrev(__svu16_source__),
                                                     __svu16_target__,
                                                     vMask,
                                                     vTargetMaskHigh,
                                                     hwOpacity););

        svst4ub_u16(vTailPred,
                    (uint8_t *)pwTarget,
                    vTargetLow16x4,
                    vTargetHigh16x4);

        pwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3)
void __arm_2d_sve_ccca8888_reserve_blend_to_cccn888_with_target_mask(
    uint32_t *__RESTRICT pwSource,
    uint32_t *__RESTRICT pwTarget,
    uint8_t *__RESTRICT pchTargetMask,
    size_t uStride)
{
    /* generate one-pass addresses */
    pwSource += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

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
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceHigh16x4,
                                                 vTargetLow16x4,

                                                 svuint16_t vMask = svrev(svget4(vSourceHigh16x4, 3));

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_masks(svrev(__svu16_source__),
                                                                                                      __svu16_target__,
                                                                                                      vMask,
                                                                                                      vTargetMaskLow););

        /* process high half */
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceLow16x4,
                                                 vTargetHigh16x4,

                                                 svuint16_t vMask = svrev(svget4(vSourceLow16x4, 3));

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_masks(svrev(__svu16_source__),
                                                                                                      __svu16_target__,
                                                                                                      vMask,
                                                                                                      vTargetMaskHigh););

        svst4ub_u16(vTailPred,
                    (uint8_t *)pwTarget,
                    vTargetLow16x4,
                    vTargetHigh16x4);

        pwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2)
void __arm_2d_sve_ccca8888_reserve_blend_to_cccn888_with_opacity(
    uint32_t *__RESTRICT pwSource,
    uint32_t *__RESTRICT pwTarget,
    size_t uStride,
    uint16_t hwOpacity)
{
    /* generate one-pass addresses */
    pwSource += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

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
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceHigh16x4,
                                                 vTargetLow16x4,

                                                 svuint16_t vMask = svrev(svget4(vSourceHigh16x4, 3));

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_mask_and_opacity(
                                                     svrev(__svu16_source__),
                                                     __svu16_target__,
                                                     vMask,
                                                     hwOpacity););

        /* process high half */
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceLow16x4,
                                                 vTargetHigh16x4,

                                                 svuint16_t vMask = svrev(svget4(vSourceLow16x4, 3));

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_mask_and_opacity(
                                                     svrev(__svu16_source__),
                                                     __svu16_target__,
                                                     vMask,
                                                     hwOpacity););

        svst4ub_u16(vTailPred,
                    (uint8_t *)pwTarget,
                    vTargetLow16x4,
                    vTargetHigh16x4);

        pwTarget += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2)
void __arm_2d_sve_ccca8888_reserve_blend_to_cccn888(
    uint32_t *__RESTRICT pwSource,
    uint32_t *__RESTRICT pwTarget,
    size_t uStride)
{
    /* generate one-pass addresses */
    pwSource += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

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
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceHigh16x4,
                                                 vTargetLow16x4,

                                                 svuint16_t vMask = svrev(svget4(vSourceHigh16x4, 3));

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_mask(svrev(__svu16_source__),
                                                                                                     __svu16_target__,
                                                                                                     vMask););

        /* process high half */
        __arm_2d_sve_pixel_ccca_foreach_chn012__(vSourceLow16x4,
                                                 vTargetHigh16x4,

                                                 svuint16_t vMask = svrev(svget4(vSourceLow16x4, 3));

                                                 __svu16_target__ = __arm_2d_sve_chn_blend_with_mask(svrev(__svu16_source__),
                                                                                                     __svu16_target__,
                                                                                                     vMask););

        svst4ub_u16(vTailPred,
                    (uint8_t *)pwTarget,
                    vTargetLow16x4,
                    vTargetHigh16x4);

        pwTarget += __iteration_advance__;
    }
}

/*----------------------------------------------------------------------------*
 * Blending to RGB565                                                         *
 *----------------------------------------------------------------------------*/

__STATIC_INLINE
ARM_NONNULL(1, 2)
void __arm_2d_sve_ccca8888_blend_to_rgb565(uint32_t *__RESTRICT pwSource,
                                           uint16_t *__RESTRICT phwTarget,
                                           size_t uStride)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x3_t vTargetLow16x3 = svundef3_u16();
        svuint16x3_t vTargetHigh16x3 = svundef3_u16();

        svld4ub_u16(vTailPred,
                    (uint8_t *)pwSource,
                    &vSourceLow16x4,
                    &vSourceHigh16x4);

        svuint16x3_t vSourceLow16x3 = svcreate3_u16(svget4(vSourceLow16x4, 0),
                                                    svget4(vSourceLow16x4, 1),
                                                    svget4(vSourceLow16x4, 2));

        svuint16x3_t vSourceHigh16x3 = svcreate3_u16(
            svget4(vSourceHigh16x4, 0),
            svget4(vSourceHigh16x4, 1),
            svget4(vSourceHigh16x4, 2));

        svld3rgb565_u16(vTailPred,
                        phwTarget,
                        &vTargetLow16x3,
                        &vTargetHigh16x3);

        /* process low half */
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceLow16x3,
                                             vTargetLow16x3,

                                             svuint16_t vMask = svget4(vSourceLow16x4, 3);

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_mask(__svu16_source__,
                                                                                                 __svu16_target__,
                                                                                                 vMask);

        );

        /* process high half */
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceHigh16x3,
                                             vTargetHigh16x3,

                                             svuint16_t vMask = svget4(vSourceHigh16x4, 3);

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_mask(__svu16_source__,
                                                                                                 __svu16_target__,
                                                                                                 vMask););

        svst3rgb565_u16(vTailPred,
                        phwTarget,
                        vTargetLow16x3,
                        vTargetHigh16x3);

        pwSource += __iteration_advance__;
        phwTarget += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2)
void __arm_2d_sve_ccca8888_blend_to_rgb565_and_opacity(
    uint32_t *__RESTRICT pwSource,
    uint16_t *__RESTRICT phwTarget,
    size_t uStride,
    uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x3_t vTargetLow16x3 = svundef3_u16();
        svuint16x3_t vTargetHigh16x3 = svundef3_u16();

        svld4ub_u16(vTailPred,
                    (uint8_t *)pwSource,
                    &vSourceLow16x4,
                    &vSourceHigh16x4);

        svuint16x3_t vSourceLow16x3 = svcreate3_u16(svget4(vSourceLow16x4, 0),
                                                    svget4(vSourceLow16x4, 1),
                                                    svget4(vSourceLow16x4, 2));

        svuint16x3_t vSourceHigh16x3 = svcreate3_u16(
            svget4(vSourceHigh16x4, 0),
            svget4(vSourceHigh16x4, 1),
            svget4(vSourceHigh16x4, 2));

        svld3rgb565_u16(vTailPred,
                        phwTarget,
                        &vTargetLow16x3,
                        &vTargetHigh16x3);

        /* process low half */
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceLow16x3,
                                             vTargetLow16x3,

                                             svuint16_t vMask = svget4(vSourceLow16x4, 3);

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_mask_and_opacity(
                                                 __svu16_source__,
                                                 __svu16_target__,
                                                 vMask,
                                                 hwOpacity);

        );

        /* process high half */
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceHigh16x3,
                                             vTargetHigh16x3,

                                             svuint16_t vMask = svget4(vSourceHigh16x4, 3);

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_mask_and_opacity(
                                                 __svu16_source__,
                                                 __svu16_target__,
                                                 vMask,
                                                 hwOpacity););

        svst3rgb565_u16(vTailPred,
                        phwTarget,
                        vTargetLow16x3,
                        vTargetHigh16x3);

        pwSource += __iteration_advance__;
        phwTarget += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3)
void __arm_2d_sve_ccca8888_blend_to_rgb565_with_target_mask(
    uint32_t *__RESTRICT pwSource,
    uint16_t *__RESTRICT phwTarget,
    uint8_t *__RESTRICT pchTargetMask,
    size_t uStride)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x3_t vTargetLow16x3 = svundef3_u16();
        svuint16x3_t vTargetHigh16x3 = svundef3_u16();

        svld4ub_u16(vTailPred,
                    (uint8_t *)pwSource,
                    &vSourceLow16x4,
                    &vSourceHigh16x4);

        svuint16x3_t vSourceLow16x3 = svcreate3_u16(svget4(vSourceLow16x4, 0),
                                                    svget4(vSourceLow16x4, 1),
                                                    svget4(vSourceLow16x4, 2));

        svuint16x3_t vSourceHigh16x3 = svcreate3_u16(
            svget4(vSourceHigh16x4, 0),
            svget4(vSourceHigh16x4, 1),
            svget4(vSourceHigh16x4, 2));

        svld3rgb565_u16(vTailPred,
                        phwTarget,
                        &vTargetLow16x3,
                        &vTargetHigh16x3);

        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);

        /* process low half */
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceLow16x3,
                                             vTargetLow16x3,

                                             svuint16_t vMask = svget4(vSourceLow16x4, 3);

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_masks(__svu16_source__,
                                                                                                  __svu16_target__,
                                                                                                  vMask,
                                                                                                  vTargetMaskLow);

        );

        /* process high half */
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceHigh16x3,
                                             vTargetHigh16x3,

                                             svuint16_t vMask = svget4(vSourceHigh16x4, 3);

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_masks(__svu16_source__,
                                                                                                  __svu16_target__,
                                                                                                  vMask,
                                                                                                  vTargetMaskHigh););

        svst3rgb565_u16(vTailPred,
                        phwTarget,
                        vTargetLow16x3,
                        vTargetHigh16x3);

        pwSource += __iteration_advance__;
        phwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3)
void __arm_2d_sve_ccca8888_blend_to_rgb565_with_source_mask(
    uint32_t *__RESTRICT pwSource,
    uint8_t *__RESTRICT pchSourceMask,
    uint16_t *__RESTRICT phwTarget,
    size_t uStride)
{
    return __arm_2d_sve_ccca8888_blend_to_rgb565_with_target_mask(
        pwSource,
        phwTarget,
        pchSourceMask,
        uStride);
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3)
void __arm_2d_sve_ccca8888_blend_to_rgb565_with_target_mask_and_opacity(
    uint32_t *__RESTRICT pwSource,
    uint16_t *__RESTRICT phwTarget,
    uint8_t *__RESTRICT pchTargetMask,
    size_t uStride,
    uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x3_t vTargetLow16x3 = svundef3_u16();
        svuint16x3_t vTargetHigh16x3 = svundef3_u16();

        svld4ub_u16(vTailPred,
                    (uint8_t *)pwSource,
                    &vSourceLow16x4,
                    &vSourceHigh16x4);

        svuint16x3_t vSourceLow16x3 = svcreate3_u16(svget4(vSourceLow16x4, 0),
                                                    svget4(vSourceLow16x4, 1),
                                                    svget4(vSourceLow16x4, 2));

        svuint16x3_t vSourceHigh16x3 = svcreate3_u16(
            svget4(vSourceHigh16x4, 0),
            svget4(vSourceHigh16x4, 1),
            svget4(vSourceHigh16x4, 2));

        svld3rgb565_u16(vTailPred,
                        phwTarget,
                        &vTargetLow16x3,
                        &vTargetHigh16x3);

        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);

        /* process low half */
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceLow16x3,
                                             vTargetLow16x3,

                                             svuint16_t vMask = svget4(vSourceLow16x4, 3);

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_masks_and_opacity(
                                                 __svu16_source__,
                                                 __svu16_target__,
                                                 vMask,
                                                 vTargetMaskLow,
                                                 hwOpacity);

        );

        /* process high half */
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceHigh16x3,
                                             vTargetHigh16x3,

                                             svuint16_t vMask = svget4(vSourceHigh16x4, 3);

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_masks_and_opacity(
                                                 __svu16_source__,
                                                 __svu16_target__,
                                                 vMask,
                                                 vTargetMaskHigh,
                                                 hwOpacity););

        svst3rgb565_u16(vTailPred,
                        phwTarget,
                        vTargetLow16x3,
                        vTargetHigh16x3);

        pwSource += __iteration_advance__;
        phwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3)
void __arm_2d_sve_ccca8888_blend_to_rgb565_with_source_mask_and_opacity(
    uint32_t *__RESTRICT pwSource,
    uint8_t *__RESTRICT pchSourceMask,
    uint16_t *__RESTRICT phwTarget,
    size_t uStride,
    uint16_t hwOpacity)
{
    __arm_2d_sve_ccca8888_blend_to_rgb565_with_target_mask_and_opacity(
        pwSource,
        phwTarget,
        pchSourceMask,
        uStride,
        hwOpacity);
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3, 4)
void __arm_2d_sve_ccca8888_blend_to_rgb565_with_masks(
    uint32_t *__RESTRICT pwSource,
    uint8_t *__RESTRICT pchSourceMask,
    uint16_t *__RESTRICT phwTarget,
    uint8_t *__RESTRICT pchTargetMask,
    size_t uStride)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x3_t vTargetLow16x3 = svundef3_u16();
        svuint16x3_t vTargetHigh16x3 = svundef3_u16();

        svld4ub_u16(vTailPred,
                    (uint8_t *)pwSource,
                    &vSourceLow16x4,
                    &vSourceHigh16x4);

        svuint16x3_t vSourceLow16x3 = svcreate3_u16(svget4(vSourceLow16x4, 0),
                                                    svget4(vSourceLow16x4, 1),
                                                    svget4(vSourceLow16x4, 2));

        svuint16x3_t vSourceHigh16x3 = svcreate3_u16(
            svget4(vSourceHigh16x4, 0),
            svget4(vSourceHigh16x4, 1),
            svget4(vSourceHigh16x4, 2));

        svld3rgb565_u16(vTailPred,
                        phwTarget,
                        &vTargetLow16x3,
                        &vTargetHigh16x3);

        svuint8_t vu8SourceMask = svld1_u8(vTailPred, pchSourceMask);
        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);

        /* process low half */
        svuint16_t vSourceMaskLow = svunpklo_u16(vu8SourceMask);
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceLow16x3,
                                             vTargetLow16x3,

                                             svuint16_t vMask = svget4(vSourceLow16x4, 3);

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_3masks(
                                                 __svu16_source__,
                                                 __svu16_target__,
                                                 vMask,
                                                 vSourceMaskLow,
                                                 vTargetMaskLow);

        );

        /* process high half */
        svuint16_t vSourceMaskHigh = svunpkhi_u16(vu8SourceMask);
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceHigh16x3,
                                             vTargetHigh16x3,

                                             svuint16_t vMask = svget4(vSourceHigh16x4, 3);

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_3masks(
                                                 __svu16_source__,
                                                 __svu16_target__,
                                                 vMask,
                                                 vSourceMaskHigh,
                                                 vTargetMaskHigh););

        svst3rgb565_u16(vTailPred,
                        phwTarget,
                        vTargetLow16x3,
                        vTargetHigh16x3);

        pwSource += __iteration_advance__;
        pchSourceMask += __iteration_advance__;
        phwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3, 4)
void __arm_2d_sve_ccca8888_blend_to_rgb565_with_masks_and_opacity(
    uint32_t *__RESTRICT pwSource,
    uint8_t *__RESTRICT pchSourceMask,
    uint16_t *__RESTRICT phwTarget,
    uint8_t *__RESTRICT pchTargetMask,
    size_t uStride,
    uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x3_t vTargetLow16x3 = svundef3_u16();
        svuint16x3_t vTargetHigh16x3 = svundef3_u16();

        svld4ub_u16(vTailPred,
                    (uint8_t *)pwSource,
                    &vSourceLow16x4,
                    &vSourceHigh16x4);

        svuint16x3_t vSourceLow16x3 = svcreate3_u16(svget4(vSourceLow16x4, 0),
                                                    svget4(vSourceLow16x4, 1),
                                                    svget4(vSourceLow16x4, 2));

        svuint16x3_t vSourceHigh16x3 = svcreate3_u16(
            svget4(vSourceHigh16x4, 0),
            svget4(vSourceHigh16x4, 1),
            svget4(vSourceHigh16x4, 2));

        svld3rgb565_u16(vTailPred,
                        phwTarget,
                        &vTargetLow16x3,
                        &vTargetHigh16x3);

        svuint8_t vu8SourceMask = svld1_u8(vTailPred, pchSourceMask);
        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);

        /* process low half */
        svuint16_t vSourceMaskLow = svunpklo_u16(vu8SourceMask);
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceLow16x3,
                                             vTargetLow16x3,

                                             svuint16_t vMask = svget4(vSourceLow16x4, 3);

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_3masks_and_opacity(
                                                 __svu16_source__,
                                                 __svu16_target__,
                                                 vMask,
                                                 vSourceMaskLow,
                                                 vTargetMaskLow,
                                                 hwOpacity);

        );

        /* process high half */
        svuint16_t vSourceMaskHigh = svunpkhi_u16(vu8SourceMask);
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceHigh16x3,
                                             vTargetHigh16x3,

                                             svuint16_t vMask = svget4(vSourceHigh16x4, 3);

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_3masks_and_opacity(
                                                 __svu16_source__,
                                                 __svu16_target__,
                                                 vMask,
                                                 vSourceMaskHigh,
                                                 vTargetMaskHigh,
                                                 hwOpacity););

        svst3rgb565_u16(vTailPred,
                        phwTarget,
                        vTargetLow16x3,
                        vTargetHigh16x3);

        pwSource += __iteration_advance__;
        pchSourceMask += __iteration_advance__;
        phwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

/*----------------------------------------------------------------------------*
 * Blending to RGB565 with X mirroring                                        *
 *----------------------------------------------------------------------------*/

__STATIC_INLINE
ARM_NONNULL(1, 2, 3, 4)
void __arm_2d_sve_ccca8888_reverse_blend_to_rgb565_with_masks_and_opacity(
    uint32_t *__RESTRICT pwSource,
    uint8_t *__RESTRICT pchSourceMask,
    uint16_t *__RESTRICT phwTarget,
    uint8_t *__RESTRICT pchTargetMask,
    size_t uStride,
    uint16_t hwOpacity)
{
    /* generate one-pass addresses */
    pwSource += 1;
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

        svbool_t vTailPredRev = svrev_b8(vTailPred);

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x3_t vTargetLow16x3 = svundef3_u16();
        svuint16x3_t vTargetHigh16x3 = svundef3_u16();

        pwSource -= __iteration_advance__;
        svld4ub_u16(vTailPredRev,
                    (uint8_t *)pwSource,
                    &vSourceLow16x4,
                    &vSourceHigh16x4);

        svuint16x3_t vSourceLow16x3 = svcreate3_u16(svget4(vSourceLow16x4, 0),
                                                    svget4(vSourceLow16x4, 1),
                                                    svget4(vSourceLow16x4, 2));

        svuint16x3_t vSourceHigh16x3 = svcreate3_u16(
            svget4(vSourceHigh16x4, 0),
            svget4(vSourceHigh16x4, 1),
            svget4(vSourceHigh16x4, 2));

        svld3rgb565_u16(vTailPred,
                        phwTarget,
                        &vTargetLow16x3,
                        &vTargetHigh16x3);

        pchSourceMask -= __iteration_advance__;
        svuint8_t vu8SourceMask = svld1_u8(vTailPredRev, pchSourceMask);
        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);

        /* process low half */
        svuint16_t vSourceMaskHigh = svrev(svunpkhi_u16(vu8SourceMask));
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceHigh16x3,
                                             vTargetLow16x3,

                                             svuint16_t vMask = svrev(svget4(vSourceHigh16x4, 3));

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_3masks_and_opacity(
                                                 svrev(__svu16_source__),
                                                 __svu16_target__,
                                                 vMask,
                                                 vSourceMaskHigh,
                                                 vTargetMaskLow,
                                                 hwOpacity);

        );

        /* process high half */
        svuint16_t vSourceMaskLow = svrev(svunpklo_u16(vu8SourceMask));
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceLow16x3,
                                             vTargetHigh16x3,

                                             svuint16_t vMask = svrev(svget4(vSourceLow16x4, 3));

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_3masks_and_opacity(
                                                 svrev(__svu16_source__),
                                                 __svu16_target__,
                                                 vMask,
                                                 vSourceMaskLow,
                                                 vTargetMaskHigh,
                                                 hwOpacity););

        svst3rgb565_u16(vTailPred,
                        phwTarget,
                        vTargetLow16x3,
                        vTargetHigh16x3);

        phwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3, 4)
void __arm_2d_sve_ccca8888_reverse_blend_to_rgb565_with_masks(
    uint32_t *__RESTRICT pwSource,
    uint8_t *__RESTRICT pchSourceMask,
    uint16_t *__RESTRICT phwTarget,
    uint8_t *__RESTRICT pchTargetMask,
    size_t uStride)
{
    /* generate one-pass addresses */
    pwSource += 1;
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

        svbool_t vTailPredRev = svrev_b8(vTailPred);

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x3_t vTargetLow16x3 = svundef3_u16();
        svuint16x3_t vTargetHigh16x3 = svundef3_u16();

        pwSource -= __iteration_advance__;
        svld4ub_u16(vTailPredRev,
                    (uint8_t *)pwSource,
                    &vSourceLow16x4,
                    &vSourceHigh16x4);

        svuint16x3_t vSourceLow16x3 = svcreate3_u16(svget4(vSourceLow16x4, 0),
                                                    svget4(vSourceLow16x4, 1),
                                                    svget4(vSourceLow16x4, 2));

        svuint16x3_t vSourceHigh16x3 = svcreate3_u16(
            svget4(vSourceHigh16x4, 0),
            svget4(vSourceHigh16x4, 1),
            svget4(vSourceHigh16x4, 2));

        svld3rgb565_u16(vTailPred,
                        phwTarget,
                        &vTargetLow16x3,
                        &vTargetHigh16x3);

        pchSourceMask -= __iteration_advance__;
        svuint8_t vu8SourceMask = svld1_u8(vTailPredRev, pchSourceMask);
        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);

        /* process low half */
        svuint16_t vSourceMaskHigh = svrev(svunpkhi_u16(vu8SourceMask));
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceHigh16x3,
                                             vTargetLow16x3,

                                             svuint16_t vMask = svrev(svget4(vSourceHigh16x4, 3));

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_3masks(
                                                 svrev(__svu16_source__),
                                                 __svu16_target__,
                                                 vMask,
                                                 vSourceMaskHigh,
                                                 vTargetMaskLow);

        );

        /* process high half */
        svuint16_t vSourceMaskLow = svrev(svunpklo_u16(vu8SourceMask));
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceLow16x3,
                                             vTargetHigh16x3,

                                             svuint16_t vMask = svrev(svget4(vSourceLow16x4, 3));

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_3masks(
                                                 svrev(__svu16_source__),
                                                 __svu16_target__,
                                                 vMask,
                                                 vSourceMaskLow,
                                                 vTargetMaskHigh););

        svst3rgb565_u16(vTailPred,
                        phwTarget,
                        vTargetLow16x3,
                        vTargetHigh16x3);

        phwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3)
void __arm_2d_sve_ccca8888_reverse_blend_to_rgb565_with_source_mask_and_opacity(
    uint32_t *__RESTRICT pwSource,
    uint8_t *__RESTRICT pchSourceMask,
    uint16_t *__RESTRICT phwTarget,
    size_t uStride,
    uint16_t hwOpacity)
{
    /* generate one-pass addresses */
    pwSource += 1;
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

        svbool_t vTailPredRev = svrev_b8(vTailPred);

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x3_t vTargetLow16x3 = svundef3_u16();
        svuint16x3_t vTargetHigh16x3 = svundef3_u16();

        pwSource -= __iteration_advance__;
        svld4ub_u16(vTailPredRev,
                    (uint8_t *)pwSource,
                    &vSourceLow16x4,
                    &vSourceHigh16x4);

        svuint16x3_t vSourceLow16x3 = svcreate3_u16(svget4(vSourceLow16x4, 0),
                                                    svget4(vSourceLow16x4, 1),
                                                    svget4(vSourceLow16x4, 2));

        svuint16x3_t vSourceHigh16x3 = svcreate3_u16(
            svget4(vSourceHigh16x4, 0),
            svget4(vSourceHigh16x4, 1),
            svget4(vSourceHigh16x4, 2));

        svld3rgb565_u16(vTailPred,
                        phwTarget,
                        &vTargetLow16x3,
                        &vTargetHigh16x3);

        pchSourceMask -= __iteration_advance__;
        svuint8_t vu8SourceMask = svld1_u8(vTailPredRev, pchSourceMask);

        /* process low half */
        svuint16_t vSourceMaskHigh = svrev(svunpkhi_u16(vu8SourceMask));
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceHigh16x3,
                                             vTargetLow16x3,

                                             svuint16_t vMask = svrev(svget4(vSourceHigh16x4, 3));

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_masks_and_opacity(
                                                 svrev(__svu16_source__),
                                                 __svu16_target__,
                                                 vMask,
                                                 vSourceMaskHigh,
                                                 hwOpacity);

        );

        /* process high half */
        svuint16_t vSourceMaskLow = svrev(svunpklo_u16(vu8SourceMask));
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceLow16x3,
                                             vTargetHigh16x3,

                                             svuint16_t vMask = svrev(svget4(vSourceLow16x4, 3));

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_masks_and_opacity(
                                                 svrev(__svu16_source__),
                                                 __svu16_target__,
                                                 vMask,
                                                 vSourceMaskLow,
                                                 hwOpacity););

        svst3rgb565_u16(vTailPred,
                        phwTarget,
                        vTargetLow16x3,
                        vTargetHigh16x3);

        phwTarget += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3)
void __arm_2d_sve_ccca8888_reverse_blend_to_rgb565_with_source_mask(
    uint32_t *__RESTRICT pwSource,
    uint8_t *__RESTRICT pchSourceMask,
    uint16_t *__RESTRICT phwTarget,
    size_t uStride)
{
    /* generate one-pass addresses */
    pwSource += 1;
    pchSourceMask += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

        svbool_t vTailPredRev = svrev_b8(vTailPred);

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x3_t vTargetLow16x3 = svundef3_u16();
        svuint16x3_t vTargetHigh16x3 = svundef3_u16();

        pwSource -= __iteration_advance__;
        svld4ub_u16(vTailPredRev,
                    (uint8_t *)pwSource,
                    &vSourceLow16x4,
                    &vSourceHigh16x4);

        svuint16x3_t vSourceLow16x3 = svcreate3_u16(svget4(vSourceLow16x4, 0),
                                                    svget4(vSourceLow16x4, 1),
                                                    svget4(vSourceLow16x4, 2));

        svuint16x3_t vSourceHigh16x3 = svcreate3_u16(
            svget4(vSourceHigh16x4, 0),
            svget4(vSourceHigh16x4, 1),
            svget4(vSourceHigh16x4, 2));

        svld3rgb565_u16(vTailPred,
                        phwTarget,
                        &vTargetLow16x3,
                        &vTargetHigh16x3);

        pchSourceMask -= __iteration_advance__;
        svuint8_t vu8SourceMask = svld1_u8(vTailPredRev, pchSourceMask);

        /* process low half */
        svuint16_t vSourceMaskHigh = svrev(svunpkhi_u16(vu8SourceMask));
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceHigh16x3,
                                             vTargetLow16x3,

                                             svuint16_t vMask = svrev(svget4(vSourceHigh16x4, 3));

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_masks(svrev(__svu16_source__),
                                                                                                  __svu16_target__,
                                                                                                  vMask,
                                                                                                  vSourceMaskHigh);

        );

        /* process high half */
        svuint16_t vSourceMaskLow = svrev(svunpklo_u16(vu8SourceMask));
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceLow16x3,
                                             vTargetHigh16x3,

                                             svuint16_t vMask = svrev(svget4(vSourceLow16x4, 3));

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_masks(svrev(__svu16_source__),
                                                                                                  __svu16_target__,
                                                                                                  vMask,
                                                                                                  vSourceMaskLow););

        svst3rgb565_u16(vTailPred,
                        phwTarget,
                        vTargetLow16x3,
                        vTargetHigh16x3);

        phwTarget += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3)
void __arm_2d_sve_ccca8888_reverse_blend_to_rgb565_with_target_mask_and_opacity(
    uint32_t *__RESTRICT pwSource,
    uint16_t *__RESTRICT phwTarget,
    uint8_t *__RESTRICT pchTargetMask,
    size_t uStride,
    uint16_t hwOpacity)
{
    /* generate one-pass addresses */
    pwSource += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

        svbool_t vTailPredRev = svrev_b8(vTailPred);

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x3_t vTargetLow16x3 = svundef3_u16();
        svuint16x3_t vTargetHigh16x3 = svundef3_u16();

        pwSource -= __iteration_advance__;
        svld4ub_u16(vTailPredRev,
                    (uint8_t *)pwSource,
                    &vSourceLow16x4,
                    &vSourceHigh16x4);

        svuint16x3_t vSourceLow16x3 = svcreate3_u16(svget4(vSourceLow16x4, 0),
                                                    svget4(vSourceLow16x4, 1),
                                                    svget4(vSourceLow16x4, 2));

        svuint16x3_t vSourceHigh16x3 = svcreate3_u16(
            svget4(vSourceHigh16x4, 0),
            svget4(vSourceHigh16x4, 1),
            svget4(vSourceHigh16x4, 2));

        svld3rgb565_u16(vTailPred,
                        phwTarget,
                        &vTargetLow16x3,
                        &vTargetHigh16x3);

        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);

        /* process low half */
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceHigh16x3,
                                             vTargetLow16x3,

                                             svuint16_t vMask = svrev(svget4(vSourceHigh16x4, 3));

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_masks_and_opacity(
                                                 svrev(__svu16_source__),
                                                 __svu16_target__,
                                                 vMask,
                                                 vTargetMaskLow,
                                                 hwOpacity);

        );

        /* process high half */
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceLow16x3,
                                             vTargetHigh16x3,

                                             svuint16_t vMask = svrev(svget4(vSourceLow16x4, 3));

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_masks_and_opacity(
                                                 svrev(__svu16_source__),
                                                 __svu16_target__,
                                                 vMask,
                                                 vTargetMaskHigh,
                                                 hwOpacity););

        svst3rgb565_u16(vTailPred,
                        phwTarget,
                        vTargetLow16x3,
                        vTargetHigh16x3);

        phwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2, 3)
void __arm_2d_sve_ccca8888_reverse_blend_to_rgb565_with_target_mask(
    uint32_t *__RESTRICT pwSource,
    uint16_t *__RESTRICT phwTarget,
    uint8_t *__RESTRICT pchTargetMask,
    size_t uStride,
    uint16_t hwOpacity)
{
    /* generate one-pass addresses */
    pwSource += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

        svbool_t vTailPredRev = svrev_b8(vTailPred);

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x3_t vTargetLow16x3 = svundef3_u16();
        svuint16x3_t vTargetHigh16x3 = svundef3_u16();

        pwSource -= __iteration_advance__;
        svld4ub_u16(vTailPredRev,
                    (uint8_t *)pwSource,
                    &vSourceLow16x4,
                    &vSourceHigh16x4);

        svuint16x3_t vSourceLow16x3 = svcreate3_u16(svget4(vSourceLow16x4, 0),
                                                    svget4(vSourceLow16x4, 1),
                                                    svget4(vSourceLow16x4, 2));

        svuint16x3_t vSourceHigh16x3 = svcreate3_u16(
            svget4(vSourceHigh16x4, 0),
            svget4(vSourceHigh16x4, 1),
            svget4(vSourceHigh16x4, 2));

        svld3rgb565_u16(vTailPred,
                        phwTarget,
                        &vTargetLow16x3,
                        &vTargetHigh16x3);

        svuint8_t vu8TargetMask = svld1_u8(vTailPred, pchTargetMask);

        /* process low half */
        svuint16_t vTargetMaskLow = svunpklo_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceHigh16x3,
                                             vTargetLow16x3,

                                             svuint16_t vMask = svrev(svget4(vSourceHigh16x4, 3));

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_masks(svrev(__svu16_source__),
                                                                                                  __svu16_target__,
                                                                                                  vMask,
                                                                                                  vTargetMaskLow);

        );

        /* process high half */
        svuint16_t vTargetMaskHigh = svunpkhi_u16(vu8TargetMask);
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceLow16x3,
                                             vTargetHigh16x3,

                                             svuint16_t vMask = svrev(svget4(vSourceLow16x4, 3));

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_masks(svrev(__svu16_source__),
                                                                                                  __svu16_target__,
                                                                                                  vMask,
                                                                                                  vTargetMaskHigh););

        svst3rgb565_u16(vTailPred,
                        phwTarget,
                        vTargetLow16x3,
                        vTargetHigh16x3);

        phwTarget += __iteration_advance__;
        pchTargetMask += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2)
void __arm_2d_sve_ccca8888_reverse_blend_to_rgb565_with_opacity(
    uint32_t *__RESTRICT pwSource,
    uint16_t *__RESTRICT phwTarget,
    size_t uStride,
    uint16_t hwOpacity)
{
    /* generate one-pass addresses */
    pwSource += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

        svbool_t vTailPredRev = svrev_b8(vTailPred);

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x3_t vTargetLow16x3 = svundef3_u16();
        svuint16x3_t vTargetHigh16x3 = svundef3_u16();

        pwSource -= __iteration_advance__;
        svld4ub_u16(vTailPredRev,
                    (uint8_t *)pwSource,
                    &vSourceLow16x4,
                    &vSourceHigh16x4);

        svuint16x3_t vSourceLow16x3 = svcreate3_u16(svget4(vSourceLow16x4, 0),
                                                    svget4(vSourceLow16x4, 1),
                                                    svget4(vSourceLow16x4, 2));

        svuint16x3_t vSourceHigh16x3 = svcreate3_u16(
            svget4(vSourceHigh16x4, 0),
            svget4(vSourceHigh16x4, 1),
            svget4(vSourceHigh16x4, 2));

        svld3rgb565_u16(vTailPred,
                        phwTarget,
                        &vTargetLow16x3,
                        &vTargetHigh16x3);

        /* process low half */
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceHigh16x3,
                                             vTargetLow16x3,

                                             svuint16_t vMask = svrev(svget4(vSourceHigh16x4, 3));

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_mask_and_opacity(
                                                 svrev(__svu16_source__),
                                                 __svu16_target__,
                                                 vMask,
                                                 hwOpacity);

        );

        /* process high half */
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceLow16x3,
                                             vTargetHigh16x3,

                                             svuint16_t vMask = svrev(svget4(vSourceLow16x4, 3));

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_mask_and_opacity(
                                                 svrev(__svu16_source__),
                                                 __svu16_target__,
                                                 vMask,
                                                 hwOpacity););

        svst3rgb565_u16(vTailPred,
                        phwTarget,
                        vTargetLow16x3,
                        vTargetHigh16x3);

        phwTarget += __iteration_advance__;
    }
}

__STATIC_INLINE
ARM_NONNULL(1, 2)
void __arm_2d_sve_ccca8888_reverse_blend_to_rgb565(
    uint32_t *__RESTRICT pwSource,
    uint16_t *__RESTRICT phwTarget,
    size_t uStride)
{
    /* generate one-pass addresses */
    pwSource += 1;

    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred)
    {

        svbool_t vTailPredRev = svrev_b8(vTailPred);

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x3_t vTargetLow16x3 = svundef3_u16();
        svuint16x3_t vTargetHigh16x3 = svundef3_u16();

        pwSource -= __iteration_advance__;
        svld4ub_u16(vTailPredRev,
                    (uint8_t *)pwSource,
                    &vSourceLow16x4,
                    &vSourceHigh16x4);

        svuint16x3_t vSourceLow16x3 = svcreate3_u16(svget4(vSourceLow16x4, 0),
                                                    svget4(vSourceLow16x4, 1),
                                                    svget4(vSourceLow16x4, 2));

        svuint16x3_t vSourceHigh16x3 = svcreate3_u16(
            svget4(vSourceHigh16x4, 0),
            svget4(vSourceHigh16x4, 1),
            svget4(vSourceHigh16x4, 2));

        svld3rgb565_u16(vTailPred,
                        phwTarget,
                        &vTargetLow16x3,
                        &vTargetHigh16x3);

        /* process low half */
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceHigh16x3,
                                             vTargetLow16x3,

                                             svuint16_t vMask = svrev(svget4(vSourceHigh16x4, 3));

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_mask(svrev(__svu16_source__),
                                                                                                 __svu16_target__,
                                                                                                 vMask);

        );

        /* process high half */
        __arm_2d_sve_pixel_ccc_foreach_chn__(vSourceLow16x3,
                                             vTargetHigh16x3,

                                             svuint16_t vMask = svrev(svget4(vSourceLow16x4, 3));

                                             __svu16_target__ = __arm_2d_sve_chn_blend_with_mask(svrev(__svu16_source__),
                                                                                                 __svu16_target__,
                                                                                                 vMask););

        svst3rgb565_u16(vTailPred,
                        phwTarget,
                        vTargetLow16x3,
                        vTargetHigh16x3);

        phwTarget += __iteration_advance__;
    }
}

#endif /* __ARM_2D_SVE_STRIDE_CCCN8888_H__ */