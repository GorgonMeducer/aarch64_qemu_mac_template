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

#ifndef __SVE_UTIL_H__
#define __SVE_UTIL_H__

#undef __PERFC_CONNECT2
#undef __PERFC_CONNECT3
#undef __PERFC_CONNECT4
#undef __PERFC_CONNECT5
#undef __PERFC_CONNECT6
#undef __PERFC_CONNECT7
#undef __PERFC_CONNECT8
#undef __PERFC_CONNECT9

#undef PERFC_CONNECT2
#undef PERFC_CONNECT3
#undef PERFC_CONNECT4
#undef PERFC_CONNECT5
#undef PERFC_CONNECT6
#undef PERFC_CONNECT7
#undef PERFC_CONNECT8
#undef PERFC_CONNECT9
#undef ALT_PERFC_CONNECT2

#undef SAFE_NAME
#undef PERFC_SAFE_NAME

#undef PERFC_CONNECT

#undef __MACRO_EXPANDING
#define __MACRO_EXPANDING(...)                      __VA_ARGS__

#define __PERFC_CONNECT2(__A, __B)                        __A##__B
#define __PERFC_CONNECT3(__A, __B, __C)                   __A##__B##__C
#define __PERFC_CONNECT4(__A, __B, __C, __D)              __A##__B##__C##__D
#define __PERFC_CONNECT5(__A, __B, __C, __D, __E)                               \
                                    __A##__B##__C##__D##__E
#define __PERFC_CONNECT6(__A, __B, __C, __D, __E, __F)                          \
                                    __A##__B##__C##__D##__E##__F
#define __PERFC_CONNECT7(__A, __B, __C, __D, __E, __F, __G)                     \
                                    __A##__B##__C##__D##__E##__F##__G
#define __PERFC_CONNECT8(__A, __B, __C, __D, __E, __F, __G, __H)                \
                                    __A##__B##__C##__D##__E##__F##__G##__H
#define __PERFC_CONNECT9(__A, __B, __C, __D, __E, __F, __G, __H, __I)           \
                                    __A##__B##__C##__D##__E##__F##__G##__H##__I


#define ALT_PERFC_CONNECT2(__A, __B)        __PERFC_CONNECT2(__A, __B)
#define PERFC_CONNECT2(__A, __B)            __PERFC_CONNECT2(__A, __B)
#define PERFC_CONNECT3(__A, __B, __C)       __PERFC_CONNECT3(__A, __B, __C)
#define PERFC_CONNECT4(__A, __B, __C, __D)                                      \
                __PERFC_CONNECT4(__A, __B, __C, __D)
#define PERFC_CONNECT5(__A, __B, __C, __D, __E)                                 \
                __PERFC_CONNECT5(__A, __B, __C, __D, __E)
#define PERFC_CONNECT6(__A, __B, __C, __D, __E, __F)                            \
                __PERFC_CONNECT6(__A, __B, __C, __D, __E, __F)
#define PERFC_CONNECT7(__A, __B, __C, __D, __E, __F, __G)                       \
                __PERFC_CONNECT7(__A, __B, __C, __D, __E, __F, __G)
#define PERFC_CONNECT8(__A, __B, __C, __D, __E, __F, __G, __H)                  \
                __PERFC_CONNECT8(__A, __B, __C, __D, __E, __F, __G, __H)
#define PERFC_CONNECT9(__A, __B, __C, __D, __E, __F, __G, __H, __I)             \
                __PERFC_CONNECT9(__A, __B, __C, __D, __E, __F, __G, __H, __I)

#define PERFC_CONNECT(...)                                                      \
            ALT_PERFC_CONNECT2( PERFC_CONNECT,                                  \
                                __PLOOC_VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)

#ifndef __PLOOC_VA_NUM_ARGS_IMPL
#   define __PLOOC_VA_NUM_ARGS_IMPL( _0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,     \
                                    _12,_13,_14,_15,_16,__N,...)      __N
#endif

#ifndef __PLOOC_VA_NUM_ARGS
#define __PLOOC_VA_NUM_ARGS(...)                                                \
            __PLOOC_VA_NUM_ARGS_IMPL( 0,##__VA_ARGS__,16,15,14,13,12,11,10,9,   \
                                      8,7,6,5,4,3,2,1,0)
#endif


#define SAFE_NAME(__NAME)           PERFC_CONNECT3(__,__NAME,__LINE__)
#define PERFC_SAFE_NAME(__name)     PERFC_CONNECT3(__,__name,__LINE__)

#define ARM_2D_SAFE_NAME            PERFC_SAFE_NAME

#undef __perfc_using1
#undef __perfc_using2
#undef __perfc_using3
#undef __perfc_using4
#undef perfc_using

#define __perfc_using1(__declare)                                               \
            for (__declare,                                                     \
                *PERFC_CONNECT3(__perfc_using_, __LINE__,_ptr) = NULL;          \
                 PERFC_CONNECT3(__perfc_using_, __LINE__,_ptr)++ == NULL;       \
                )

#define __perfc_using2(__declare, __on_leave_expr)                              \
            for (__declare,                                                     \
                *PERFC_CONNECT3(__perfc_using_, __LINE__,_ptr) = NULL;          \
                 PERFC_CONNECT3(__perfc_using_, __LINE__,_ptr)++ == NULL;       \
                 (__on_leave_expr)                                              \
                )

#define __perfc_using3(__declare, __on_enter_expr, __on_leave_expr)             \
            for (__declare,                                                     \
                *PERFC_CONNECT3(__perfc_using_, __LINE__,_ptr) = NULL;          \
                 PERFC_CONNECT3(__perfc_using_, __LINE__,_ptr)++ == NULL ?      \
                    ((__on_enter_expr),1) : 0;                                  \
                 (__on_leave_expr)                                              \
                )

#define __perfc_using4(__dcl1, __dcl2, __on_enter_expr, __on_leave_expr)        \
            for (__dcl1, __dcl2,                                                \
                *PERFC_CONNECT3(__perfc_using_, __LINE__,_ptr) = NULL;          \
                 PERFC_CONNECT3(__perfc_using_, __LINE__,_ptr)++ == NULL ?      \
                    ((__on_enter_expr),1) : 0;                                  \
                 (__on_leave_expr)                                              \
                )

#define perfc_using(...)                                                        \
                PERFC_CONNECT2( __perfc_using,                                  \
                                __PLOOC_VA_NUM_ARGS(__VA_ARGS__))               \
                                    (__VA_ARGS__)

#undef __perfc_with2
#undef __perfc_perfc_with3
#undef perfc_with

#define __perfc_with1(__addr)                                                   \
            perfc_using(__typeof__(*__addr) *_=(__addr))

#define __perfc_with2(__type, __addr)                                           \
            perfc_using(__type *_=(__addr))
#define __perfc_with3(__type, __addr, __item)                                   \
            perfc_using(__type *_=(__addr), *__item = _, _=_,_=_ )

#define perfc_with(...)                                                         \
            PERFC_CONNECT2( __perfc_with,                                       \
                            __PLOOC_VA_NUM_ARGS(__VA_ARGS__))                   \
                                (__VA_ARGS__)

#undef perfc_foreach2
#undef perfc_foreach3
#undef perfc_foreach

#define perfc_foreach1(__array)                                                 \
            perfc_using(__typeof__(__array[0]) *_ = __array)                    \
            for (   uint_fast32_t PERFC_SAFE_NAME(count) = dimof(__array);      \
                    PERFC_SAFE_NAME(count) > 0;                                 \
                    _++, PERFC_SAFE_NAME(count)--                               \
                )

#define perfc_foreach2(__type, __array)                                         \
            perfc_using(__type *_ = __array)                                    \
            for (   uint_fast32_t PERFC_SAFE_NAME(count) = dimof(__array);      \
                    PERFC_SAFE_NAME(count) > 0;                                 \
                    _++, PERFC_SAFE_NAME(count)--                               \
                )

#define perfc_foreach3(__type, __array, __item)                                 \
            perfc_using(__type *_ = __array, *__item = _, _ = _, _ = _ )        \
            for (   uint_fast32_t PERFC_SAFE_NAME(count) = dimof(__array);      \
                    PERFC_SAFE_NAME(count) > 0;                                 \
                    _++, __item = _, PERFC_SAFE_NAME(count)--                   \
                )

#define perfc_foreach(...)                                                      \
            PERFC_CONNECT2( perfc_foreach,                                      \
                            __PLOOC_VA_NUM_ARGS(__VA_ARGS__))                   \
                                (__VA_ARGS__)


#ifndef UNUSED_PARAM
#   define UNUSED_PARAM(__VAR)     (void)(__VAR)
#endif

#ifndef MIN
#   define MIN(__a, __b)  ((__a) <= (__b) ? (__a) : (__b))
#endif

#ifndef MAX
#   define MAX(__a, __b)  ((__a) >= (__b) ? (__a) : (__b))
#endif

#ifndef dimof
#   define dimof(__array)          (sizeof(__array)/sizeof(__array[0]))
#endif

/* ---------------------------------------------------------------------------*
 * SVE Test Helper                                                            *
 * ---------------------------------------------------------------------------*/

#define SVT_PRINT_VECTOR(__VECOTOR, __ELEMENT_T, __FORMAT_STRING)               \
    do {                                                                        \
        int_fast8_t nElementCount = svcntb_pat(SV_ALL) / sizeof(__ELEMENT_T);   \
        uint8_t PERFC_SAFE_NAME(chVectorBuffer)                                 \
                    [nElementCount * sizeof(__ELEMENT_T)];                      \
                                                                                \
        svst1_u8(   svptrue_b8(),                                               \
                    PERFC_SAFE_NAME(chVectorBuffer),                            \
                    svreinterpret_u8(__VECOTOR));                               \
                                                                                \
        __ELEMENT_T *pElement = (__ELEMENT_T *)PERFC_SAFE_NAME(chVectorBuffer); \
        printf("%s\t[", #__VECOTOR);                                            \
        do {                                                                    \
            printf(__FORMAT_STRING"\t", (int)*pElement++);                      \
        } while(--nElementCount);                                               \
        printf("]\r\n");                                                        \
    } while (0)


#define SVT_INIT_VECOTR(__VECTOR, __ELEMENT_T, ...)                             \
    do {                                                                        \
        uint8_t PERFC_SAFE_NAME(chVectorBuffer)[svcntb_pat(SV_ALL)];            \
                                                                                \
        memset( PERFC_SAFE_NAME(chVectorBuffer),                                \
                0,                                                              \
                sizeof(PERFC_SAFE_NAME(chVectorBuffer)));                       \
        memcpy(PERFC_SAFE_NAME(chVectorBuffer),                                 \
                (__ELEMENT_T []){__VA_ARGS__},                                  \
                MIN(sizeof(PERFC_SAFE_NAME(chVectorBuffer)),                    \
                    sizeof((__ELEMENT_T []){__VA_ARGS__})));                    \
                                                                                \
        __VECTOR = svld1(svptrue_b8(),                                          \
                        (__ELEMENT_T *)PERFC_SAFE_NAME(chVectorBuffer));        \
    } while(0)


#define SVT_INIT_PRED(__PREDICT, ...)                                           \
    do {                                                                        \
        uint8_t PERFC_SAFE_NAME(chBuffer)[svlen(svundef_u64())];                \
        memset( PERFC_SAFE_NAME(chBuffer),                                      \
                0,                                                              \
                sizeof(PERFC_SAFE_NAME(chBuffer)));                             \
                                                                                \
        memcpy( PERFC_SAFE_NAME(chBuffer),                                      \
                (uint8_t []){__VA_ARGS__},                                      \
                MIN(sizeof(PERFC_SAFE_NAME(chBuffer)),                          \
                    sizeof((uint8_t []){__VA_ARGS__})));                        \
                                                                                \
        __PREDICT = (*(svbool_t *)PERFC_SAFE_NAME(chBuffer));                   \
    } while(0)

#define SVT_PRINT_PRED(__PREDICT, __TYPE_T)                                     \
    do {                                                                        \
        printf("%8s\t[", #__PREDICT);                                           \
        uint16_t PERFC_SAFE_NAME(hwBuffer)[svlen(svundef_u64()) / 2];           \
        memset( PERFC_SAFE_NAME(hwBuffer),                                      \
                0,                                                              \
                sizeof(PERFC_SAFE_NAME(hwBuffer)));                             \
        *(volatile svbool_t *)PERFC_SAFE_NAME(hwBuffer) = (__PREDICT);          \
                                                                                \
        uint_fast16_t PERFC_SAFE_NAME(nTotalBits) = svlen(svundef_u8());        \
        uint_fast8_t PERFC_SAFE_NAME(nElementBits) = sizeof(__TYPE_T);          \
                                                                                \
        uint16_t *phwPred = PERFC_SAFE_NAME(hwBuffer);                          \
        do {                                                                    \
            uint16_t hwPred = *phwPred++;                                       \
                                                                                \
            for (   uint_fast8_t n = 0;                                         \
                    n < 16;                                                     \
                    n += PERFC_SAFE_NAME(nElementBits)) {                       \
                                                                                \
                if (hwPred & 0x01) {                                            \
                    printf("True ");                                             \
                } else {                                                        \
                    printf("False");                                            \
                }                                                               \
                printf("%*s\t", (int)sizeof(__TYPE_T)-1, "");                   \
                hwPred >>= PERFC_SAFE_NAME(nElementBits);                       \
            }                                                                   \
                                                                                \
            PERFC_SAFE_NAME(nTotalBits) -= 16;                                  \
        } while(PERFC_SAFE_NAME(nTotalBits));                                   \
                                                                                \
        printf("]\r\n");                                                        \
    } while(0)


#define SVT_PRINT_BUFFER(__BUFF_PTR, __SIZE, __TYPE_T, __FMT_STR, __STRIDE)     \
    do {                                                                        \
        __TYPE_T *pBuffer = (__TYPE_T *)__BUFF_PTR;                             \
        size_t nElementCount = (__SIZE) / sizeof(__TYPE_T);                     \
                                                                                \
        size_t nStrideSize = (__STRIDE);                                        \
        size_t nLineCount = 0;                                                  \
                                                                                \
        printf("%s\n\t", #__BUFF_PTR);                                          \
        do {                                                                    \
                                                                                \
            printf(__FMT_STR " ", *pBuffer++);                                  \
            nLineCount++;                                                       \
            if (nLineCount >= nStrideSize) {                                    \
                nLineCount = 0;                                                 \
                printf("\n\t");                                                 \
            }                                                                   \
                                                                                \
        } while(--nElementCount);                                               \
        printf("\n");                                                           \
                                                                                \
    } while(0)





#endif     /* __SVE_UTIL_H__ */