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

#if !defined(__SVE_2D_EXTENSION_H__)                                            \
    && (defined(__ARM_FEATURE_SVE2)                                             \
    && __ARM_FEATURE_SVE2)
#define __SVE_2D_EXTENSION_H__

#include <arm_sve.h>
#include <stdint.h>

#ifndef __STATIC_INLINE
#   define __STATIC_INLINE      static inline
#endif

/*!
 * \brief a wrapper for __attribute__((nonnull))
 */
#ifndef ARM_NONNULL
#   define ARM_NONNULL(...)     __attribute__((nonnull(__VA_ARGS__)))
#endif

#ifndef __RESTRICT
#   define __RESTRICT   restrict
#endif

#define svlenu8()   svcntb_pat(SV_ALL)
#define svlenu16()  (svcntb_pat(SV_ALL) / sizeof(uint16_t))
#define svlenu32()  (svcntb_pat(SV_ALL) / sizeof(uint32_t))
#define svlenu64()  (svcntb_pat(SV_ALL) / sizeof(uint64_t))

#define svlens8()   svlenu8()
#define svlens16()  svlenu16()
#define svlens32()  svlenu32()
#define svlens64()  svlenu64()

#define __arm_2d_sve_stride_loop_ccca8888__(__stride_size, __pred_name)         \
    for (   svbool_t __pred_name, *pTemp = &__pred_name;                        \
            pTemp != NULL;                                                      \
            pTemp = NULL)                                                       \
        for (   size_t PERFC_SAFE_NAME(n) = 0,                                  \
                __iteration_advance__ = svlenu32() * 4;                         \
                ({  __pred_name = svwhilelt_b8( PERFC_SAFE_NAME(n),             \
                                                (__stride_size));               \
                    PERFC_SAFE_NAME(n) < (__stride_size);                       \
                });                                                             \
                PERFC_SAFE_NAME(n) += __iteration_advance__)

#define __arm_2d_sve_stride_loop_rgb32__(__stride_size, __pred_name)            \
            __arm_2d_sve_stride_loop_ccca8888__(__stride_size, __pred_name)

#define __arm_2d_sve_stride_loop_rgb16__(__stride_size, __pred_name)            \
    for (   svbool_t __pred_name, *pTemp = &__pred_name;                        \
            pTemp != NULL;                                                      \
            pTemp = NULL)                                                       \
        for (   size_t PERFC_SAFE_NAME(n) = 0,                                  \
                __iteration_advance__ = svlenu16();                             \
                ({  __pred_name = svwhilelt_b16(PERFC_SAFE_NAME(n),             \
                                                (__stride_size));               \
                    PERFC_SAFE_NAME(n) < (__stride_size);                       \
                });                                                             \
                PERFC_SAFE_NAME(n) += __iteration_advance__)

#define __arm_2d_sve_stride_ccc_foreach_chn__(  __source_u16x3,                 \
                                                __target_u16x3,                 \
                                                ...)                            \
        do {                                                                    \
            const uint8_t __chn_idx__ = 0;                                      \
            (void)__chn_idx__;                                                  \
            svuint16_t __svu16_source__ = svget3((__source_u16x3), 0);          \
            svuint16_t __svu16_target__ = svget3((__target_u16x3), 0);          \
            __VA_ARGS__                                                         \
            __target_u16x3 = svset3(__target_u16x3, 0, __svu16_target__);       \
        } while(0);                                                             \
        do {                                                                    \
            const uint8_t __chn_idx__ = 1;                                      \
            (void)__chn_idx__;                                                  \
            svuint16_t __svu16_source__ = svget3((__source_u16x3), 1);          \
            svuint16_t __svu16_target__ = svget3((__target_u16x3), 1);          \
            __VA_ARGS__                                                         \
            __target_u16x3 = svset3(__target_u16x3, 1, __svu16_target__);       \
        } while(0);                                                             \
        do {                                                                    \
            const uint8_t __chn_idx__ = 2;                                      \
            (void)__chn_idx__;                                                  \
            svuint16_t __svu16_source__ = svget3((__source_u16x3), 2);          \
            svuint16_t __svu16_target__ = svget3((__target_u16x3), 2);          \
            __VA_ARGS__                                                         \
            __target_u16x3 = svset3(__target_u16x3, 2, __svu16_target__);       \
        } while(0);                                                             \

#define __arm_2d_sve_stride_ccca_foreach_chn012__(  __source_u16x4,             \
                                                    __target_u16x4,             \
                                                    ...)                        \
        do {                                                                    \
            const uint8_t __chn_idx__ = 0;                                      \
            (void)__chn_idx__;                                                  \
            svuint16_t __svu16_source__ = svget4((__source_u16x4), 0);          \
            svuint16_t __svu16_target__ = svget4((__target_u16x4), 0);          \
            __VA_ARGS__                                                         \
            __target_u16x4 = svset4(__target_u16x4, 0, __svu16_target__);       \
        } while(0);                                                             \
        do {                                                                    \
            const uint8_t __chn_idx__ = 1;                                      \
            (void)__chn_idx__;                                                  \
            svuint16_t __svu16_source__ = svget4((__source_u16x4), 1);          \
            svuint16_t __svu16_target__ = svget4((__target_u16x4), 1);          \
            __VA_ARGS__                                                         \
            __target_u16x4 = svset4(__target_u16x4, 1, __svu16_target__);       \
        } while(0);                                                             \
        do {                                                                    \
            const uint8_t __chn_idx__ = 2;                                      \
            (void)__chn_idx__;                                                  \
            svuint16_t __svu16_source__ = svget4((__source_u16x4), 2);          \
            svuint16_t __svu16_target__ = svget4((__target_u16x4), 2);          \
            __VA_ARGS__                                                         \
            __target_u16x4 = svset4(__target_u16x4, 2, __svu16_target__);       \
        } while(0)

#define __arm_2d_sve_stride_ccca_foreach_chn__( __source_u16x4,                 \
                                                __target_u16x4,                 \
                                                ...)                            \
        do {                                                                    \
            const uint8_t __chn_idx__ = 0;                                      \
            (void)__chn_idx__;                                                  \
            svuint16_t __svu16_source__ = svget4((__source_u16x4), 0);          \
            svuint16_t __svu16_target__ = svget4((__target_u16x4), 0);          \
            __VA_ARGS__                                                         \
            __target_u16x4 = svset4(__target_u16x4, 0, __svu16_target__);       \
        } while(0);                                                             \
        do {                                                                    \
            const uint8_t __chn_idx__ = 1;                                      \
            (void)__chn_idx__;                                                  \
            svuint16_t __svu16_source__ = svget4((__source_u16x4), 1);          \
            svuint16_t __svu16_target__ = svget4((__target_u16x4), 1);          \
            __VA_ARGS__                                                         \
            __target_u16x4 = svset4(__target_u16x4, 1, __svu16_target__);       \
        } while(0);                                                             \
        do {                                                                    \
            const uint8_t __chn_idx__ = 2;                                      \
            (void)__chn_idx__;                                                  \
            svuint16_t __svu16_source__ = svget4((__source_u16x4), 2);          \
            svuint16_t __svu16_target__ = svget4((__target_u16x4), 2);          \
            __VA_ARGS__                                                         \
            __target_u16x4 = svset4(__target_u16x4, 2, __svu16_target__);       \
        } while(0);                                                             \
        do {                                                                    \
            const uint8_t __chn_idx__ = 3;                                      \
            (void)__chn_idx__;                                                  \
            svuint16_t __svu16_source__ = svget4((__source_u16x4), 3);          \
            svuint16_t __svu16_target__ = svget4((__target_u16x4), 3);          \
            __VA_ARGS__                                                         \
            __target_u16x4 = svset4(__target_u16x4, 3, __svu16_target__);       \
        } while(0)


__STATIC_INLINE
svuint16x3_t __arm_2d_sve_rgb565_unpack(svuint16_t vPixels)
{
    svuint16x3_t vRGB16x3 = svundef3_u16();

    /* extract and zero-exten blue channel */
    vRGB16x3 = svset3_u16(vRGB16x3, 0, (vPixels & 0x1F) << 3);

    /* extract and zero-exten green channel */
    vRGB16x3 = svset3_u16(vRGB16x3, 1, (vPixels & (0x3F << 5)) >> 3);

    /* extract and zero-exten green channel */
    vRGB16x3 = svset3_u16(vRGB16x3, 2, (vPixels & (0x1F << 11)) >> 8);

    return vRGB16x3;
}

__STATIC_INLINE
svuint16_t __arm_2d_sve_rgb565_pack(svuint16x3_t vRGB16x3)
{
    return  (svget3_u16(vRGB16x3, 0) >> 3)
        |   ((svget3_u16(vRGB16x3, 1) & (0x3F << 2)) << 3)
        |   ((svget3_u16(vRGB16x3, 2) & (0x1F << 3)) << 8);
}

__STATIC_INLINE
ARM_NONNULL(2,3,4)
void svld4ub_u16(   svbool_t vPred, 
                    uint8_t *pchSource, 
                    svuint16x4_t *pvLow, 
                    svuint16x4_t *pvHigh )
{
    svuint8x4_t vInput8x4 = svld4_u8(vPred, pchSource);

    *pvLow = svset4_u16(*pvLow, 0, svunpklo_u16(svget4_u8(vInput8x4, 0)));
    *pvLow = svset4_u16(*pvLow, 1, svunpklo_u16(svget4_u8(vInput8x4, 1)));
    *pvLow = svset4_u16(*pvLow, 2, svunpklo_u16(svget4_u8(vInput8x4, 2)));
    *pvLow = svset4_u16(*pvLow, 3, svunpklo_u16(svget4_u8(vInput8x4, 3)));
    
    *pvHigh = svset4_u16(*pvHigh, 0, svunpkhi_u16(svget4_u8(vInput8x4, 0)));
    *pvHigh = svset4_u16(*pvHigh, 1, svunpkhi_u16(svget4_u8(vInput8x4, 1)));
    *pvHigh = svset4_u16(*pvHigh, 2, svunpkhi_u16(svget4_u8(vInput8x4, 2)));
    *pvHigh = svset4_u16(*pvHigh, 3, svunpkhi_u16(svget4_u8(vInput8x4, 3)));
}

__STATIC_INLINE
ARM_NONNULL(2,3,4)
void svst4ub_u16(   svbool_t vPred, 
                    uint8_t *pchTarget, 
                    svuint16x4_t *pvLow, 
                    svuint16x4_t *pvHigh)
{

    svuint8_t vCH0u8 = svuzp1_u8(   svreinterpret_u8(svget4_u16(*pvLow, 0)),
                                    svreinterpret_u8(svget4_u16(*pvHigh, 0)));

    svuint8_t vCH1u8 = svuzp1_u8(   svreinterpret_u8(svget4_u16(*pvLow, 1)),
                                    svreinterpret_u8(svget4_u16(*pvHigh, 1)));
    
    svuint8_t vCH2u8 = svuzp1_u8(   svreinterpret_u8(svget4_u16(*pvLow, 2)),
                                    svreinterpret_u8(svget4_u16(*pvHigh, 2)));

    svuint8_t vCH3u8 = svuzp1_u8(   svreinterpret_u8(svget4_u16(*pvLow, 3)),
                                    svreinterpret_u8(svget4_u16(*pvHigh, 3)));

    svst4_u8(vPred, pchTarget, svcreate4_u8(vCH0u8, vCH1u8, vCH2u8, vCH3u8));
}

/*! \note the Element range of vMask is [0, 0xFF]
 */
__STATIC_INLINE
svuint16_t __arm_2d_sve_chn_blend_with_mask(svuint16_t vSource, svuint16_t vTarget, svuint16_t vMask)
{
    vMask = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask, 255), 
                        vMask, 
                        svdup_u16(1));

    vTarget = vSource * vMask + vTarget * (256 - vMask);
    return vTarget >> 8;
}

/*! \note the hwOpacity range [0, 0x100]
 */
__STATIC_INLINE
svuint16_t __arm_2d_sve_chn_blend_with_opacity( svuint16_t vSource, 
                                                svuint16_t vTarget, 
                                                uint16_t hwOpacity)
{
    svuint16_t vOpacity = svdup_u16(hwOpacity);

    vTarget = vSource * vOpacity + vTarget * (256 - vOpacity);
    return vTarget >> 8;
}

/*! \note the Element range of vMask is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
__STATIC_INLINE
svuint16_t __arm_2d_sve_chn_blend_with_mask_and_opacity(svuint16_t vSource, 
                                                        svuint16_t vTarget, 
                                                        svuint16_t vMask, 
                                                        uint16_t hwOpacity)
{
    vMask = svsel(  svcmpeq_n_u16(svptrue_b16(), vMask, 255), 
                    svdup_u16(hwOpacity), 
                    (vMask * hwOpacity) >> 8);

    vTarget = vSource * vMask + vTarget * (256 - vMask);
    return vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 */
__STATIC_INLINE
svuint16_t __arm_2d_sve_chn_blend_with_masks(   svuint16_t vSource, 
                                                svuint16_t vTarget, 
                                                svuint16_t vMask0,
                                                svuint16_t vMask1)
{
    vMask1 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask1, 255), 
                         vMask1, 
                         svdup_u16(1));

    svuint16_t vMask = 
        svsel(  svcmpeq_n_u16(svptrue_b16(), vMask0, 255), 
                vMask1, 
                (vMask0 * vMask1) >> 8);

    vTarget = vSource * vMask + vTarget * (256 - vMask);
    return vTarget >> 8;
}

/*! \note the Element range of vMask0/1 is [0, 0xFF]
 *  \note the hwOpacity range [0, 0x100]
 */
__STATIC_INLINE
svuint16_t __arm_2d_sve_chn_blend_with_masks_and_opacity(
                                                svuint16_t vSource, 
                                                svuint16_t vTarget, 
                                                svuint16_t vMask0,
                                                svuint16_t vMask1,
                                                uint16_t hwOpacity)
{
    vMask1 = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask1, 255), 
                         vMask1, 
                         svdup_u16(1));

    svuint16_t vMask = 
        svsel(  svcmpeq_n_u16(svptrue_b16(), vMask0, 255), 
                vMask1, 
                (vMask0 * vMask1) >> 8);

    vMask = svsel(  svcmpeq_n_u16(svptrue_b16(), vMask, 256), 
                    svdup_u16(hwOpacity), 
                    (vMask * hwOpacity) >> 8);

    vTarget = vSource * vMask + vTarget * (256 - vMask);
    return vTarget >> 8;
}


#include "__arm_2d_sve_stride_rgb565.h"
#include "__arm_2d_sve_stride_cccn888.h"

#endif