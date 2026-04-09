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

#if !defined(__ARM_2D_SVE_STRIDE_CCCA8888_H__)                                  \
    && (defined(__ARM_FEATURE_SVE2)                                             \
    && __ARM_FEATURE_SVE2)
#define __ARM_2D_SVE_STRIDE_CCCN8888_H__


/*----------------------------------------------------------------------------*
 * Blending to CCCN888                                                        *
 *----------------------------------------------------------------------------*/


__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_ccca8888_blend_to_cccn888(    uint32_t * __RESTRICT pwSource,
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

        /* process low half */
        __arm_2d_sve_pixel_ccca_foreach_chn012__(   vSourceLow16x4, 
                                                    vTargetLow16x4,

            svuint16_t vMask = svget4(vSourceLow16x4, 3);

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask( __svu16_source__, 
                                                    __svu16_target__, 
                                                    vMask);

        );

        /* process high half */
        __arm_2d_sve_pixel_ccca_foreach_chn012__(   vSourceHigh16x4, 
                                                    vTargetHigh16x4,

            svuint16_t vMask = svget4(vSourceHigh16x4, 3);

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask( __svu16_source__, 
                                                    __svu16_target__, 
                                                    vMask);
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
void __arm_2d_sve_ccca8888_blend_to_cccn888_with_opacity(    
                                                uint32_t * __RESTRICT pwSource,
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
        __arm_2d_sve_pixel_ccca_foreach_chn012__(   vSourceLow16x4, 
                                                    vTargetLow16x4,

            svuint16_t vMask = svget4(vSourceLow16x4, 3);

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask_and_opacity( 
                                                    __svu16_source__, 
                                                    __svu16_target__, 
                                                    vMask,
                                                    hwOpacity);
        );

        /* process high half */
        __arm_2d_sve_pixel_ccca_foreach_chn012__(   vSourceHigh16x4, 
                                                    vTargetHigh16x4,

            svuint16_t vMask = svget4(vSourceHigh16x4, 3);

            __svu16_target__ 
                = __arm_2d_sve_chn_blend_with_mask_and_opacity( 
                                                    __svu16_source__, 
                                                    __svu16_target__, 
                                                    vMask,
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


#endif  /* __ARM_2D_SVE_STRIDE_CCCN8888_H__ */