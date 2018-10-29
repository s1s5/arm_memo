/**
 * Copyright 2015- Co. Ltd. sizebook
 * @file arithmetic.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-08-29 12:08:23
 */
#include <arm_neon.h>

#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv) {

    uint8_t src0[8] = {
        0, 1, 2, 3, 4, 5, 6, 7,
    };

    uint8_t src1[8] = {
        8, 0, 7, 1, 6, 2, 5, 3, 
    };

    uint8x8_t v0 = vld1_u8(src0);
    uint8x8_t v1 = vld1_u8(src1);

    uint8x8_t v2 = vpadd_u8(v0, v1);

    uint8_t buf[8];
    vst1_u8(buf, v2);
    for (int i = 0; i < 8; i++) {
        printf("%3d ", (int)buf[i]);
    }
    printf("\n");
    
    return 0;
}
