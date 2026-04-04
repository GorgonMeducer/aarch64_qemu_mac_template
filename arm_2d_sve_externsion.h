#if !defined(__SVE_2D_EXTENSION_H__)                                            \
    && (defined(__ARM_FEATURE_SVE2)                                             \
    && __ARM_FEATURE_SVE2)
#define __SVE_2D_EXTENSION_H__

#include <arm_sve.h>
#include <stdint.h>

#define svlenu8()   svcntb_pat(SV_ALL)
#define svlenu16()  (svcntb_pat(SV_ALL) / sizeof(uint16_t))
#define svlenu32()  (svcntb_pat(SV_ALL) / sizeof(uint32_t))
#define svlenu64()  (svcntb_pat(SV_ALL) / sizeof(uint64_t))

#define svlens8()   svlenu8()
#define svlens16()  svlenu16()
#define svlens32()  svlenu32()
#define svlens64()  svlenu64()

static inline
__attribute__((nonnull(2,3,4)))
void svld4u8_u16(   svbool_t vPred, 
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

static inline 
__attribute__((nonnull(2,3,4)))
void svst4u8_u16(   svbool_t vPred, 
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

/*! \note the Element of vMask is no bigger than 0xFF
 */
static inline
svuint16_t __arm_2d_sve_chn_blend_with_mask(svuint16_t vSource, svuint16_t vTarget, svuint16_t vMask)
{
    vMask = svadd_u16_m(svcmpeq_n_u16(svptrue_b16(), vMask, 255), 
                        vMask, 
                        svdup_u16(1));

    vTarget = vSource * vMask + vTarget * (256 - vMask);
    return vTarget >> 8;
}

#endif