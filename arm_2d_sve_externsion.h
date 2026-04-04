#if !defined(__SVE_2D_EXTENSION_H__)                                            \
    && (defined(__ARM_FEATURE_SVE2)                                             \
    && __ARM_FEATURE_SVE2)
#define __SVE_2D_EXTENSION_H__

#include <arm_sve.h>
#include <stdint.h>


static inline
__attribute__((nonnull(2,3,4)))
void svld4u8_u16(svbool_t vPred, uint8_t *pchSource, svuint16x4_t *pvLow, svuint16x4_t *pvHigh )
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
void svst4u8_u16(svbool_t vPred, uint8_t *pchTarget, svuint16x4_t *pvLow, svuint16x4_t *pvHigh)
{
    svuint8x4_t vOutput8x4 = svundef4_u8();

    svuint8_t vCH0u8 = svuzp1_u8( svreinterpret_u8(svget4_u16(*pvLow, 0)),
                                svreinterpret_u8(svget4_u16(*pvHigh, 0)));

    svuint8_t vCH1u8 = svuzp1_u8( svreinterpret_u8(svget4_u16(*pvLow, 1)),
                                svreinterpret_u8(svget4_u16(*pvHigh, 1)));
    
    svuint8_t vCH2u8 = svuzp1_u8( svreinterpret_u8(svget4_u16(*pvLow, 2)),
                                svreinterpret_u8(svget4_u16(*pvHigh, 2)));

    svuint8_t vCH3u8 = svuzp1_u8( svreinterpret_u8(svget4_u16(*pvLow, 3)),
                                svreinterpret_u8(svget4_u16(*pvHigh, 3)));

    vOutput8x4 = svset4_u8(vOutput8x4, 0, vCH0u8);
    vOutput8x4 = svset4_u8(vOutput8x4, 1, vCH1u8);
    vOutput8x4 = svset4_u8(vOutput8x4, 2, vCH2u8);
    vOutput8x4 = svset4_u8(vOutput8x4, 3, vCH3u8);

    svst4_u8(vPred, pchTarget, vOutput8x4 );
}


#endif