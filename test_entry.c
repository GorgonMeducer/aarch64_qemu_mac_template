#include <stdio.h>
#include <arm_sve.h>
#include <arm_acle.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

#include "sve_util.h"

int main(void) {
    printf("Hello from AArch64 Linux!\n");
    printf("Compiled on MacOS, running in QEMU.\n");

    printf("SVE Vector Length: %zu bits\r\n", svlen(svundef_u8()) * 8);

    svuint16_t v16Input = svundef_u16();
    svuint16_t v16Input2 = svundef_u16();
    svuint32_t v32Input3 = svundef_u32();

    SVT_INIT_VECOTR(v16Input, uint16_t, 1, 2, 3, 4, 5, 6, 7, 8, 9,10);
    SVT_INIT_VECOTR(v16Input2, uint16_t, 0xFFFF, 0xFFFF, 0xAAAA);
    SVT_INIT_VECOTR(v32Input3, uint32_t, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 , 16);

    SVT_PRINT_VECTOR(v16Input, uint16_t, "0x%04"PRIx16);
    SVT_PRINT_VECTOR(v16Input2, uint16_t, "0x%04"PRIx16);
    SVT_PRINT_VECTOR(v32Input3, uint32_t, "0x%08"PRIx32);

    return 0;
}
