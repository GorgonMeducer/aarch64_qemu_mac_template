#if !defined(__ARM_2D_SVE_STRIDE_CCCN888_H__)                                   \
    && (defined(__ARM_FEATURE_SVE2)                                             \
    && __ARM_FEATURE_SVE2)
#define __ARM_2D_SVE_STRIDE_CCCN888_H__




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

        svld4u8_u16(vTailPred, 
                    (uint8_t *)pwSource, 
                    &vSourceLow16x4, 
                    &vSourceHigh16x4);

        svld4u8_u16(vTailPred, 
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

        svst4u8_u16(vTailPred, 
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
                                                 uint32_t * __RESTRICT pwTarget,
                                                 uint8_t * __RESTRICT pchMask,
                                                 size_t uStride)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        svld4u8_u16(vTailPred, 
                    (uint8_t *)pwSource, 
                    &vSourceLow16x4, 
                    &vSourceHigh16x4);

        svld4u8_u16(vTailPred, 
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

        svst4u8_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwSource += __iteration_advance__;
        pwTarget += __iteration_advance__;
        pchMask  += __iteration_advance__;
    }
}


__STATIC_INLINE
ARM_NONNULL(1,2)
void __arm_2d_sve_cccn888_blend_with_source_mask_and_opacity(
                                                uint32_t * __RESTRICT pwSource,
                                                uint32_t * __RESTRICT pwTarget,
                                                uint8_t * __RESTRICT pchMask,
                                                size_t uStride,
                                                uint16_t hwOpacity)
{
    __arm_2d_sve_stride_loop_ccca8888__(uStride, vTailPred) {

        svuint16x4_t vSourceLow16x4 = svundef4_u16();
        svuint16x4_t vSourceHigh16x4 = svundef4_u16();

        svuint16x4_t vTargetLow16x4 = svundef4_u16();
        svuint16x4_t vTargetHigh16x4 = svundef4_u16();

        svld4u8_u16(vTailPred, 
                    (uint8_t *)pwSource, 
                    &vSourceLow16x4, 
                    &vSourceHigh16x4);

        svld4u8_u16(vTailPred, 
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

        svst4u8_u16(vTailPred, 
                    (uint8_t *)pwTarget, 
                    &vTargetLow16x4, 
                    &vTargetHigh16x4);

        pwSource += __iteration_advance__;
        pwTarget += __iteration_advance__;
        pchMask  += __iteration_advance__;
    }
}




#endif