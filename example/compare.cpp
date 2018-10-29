/**
 * Copyright 2015- Co. Ltd. sizebook
 * @file compare.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-09-04 11:25:29
 */

#include <arm_neon.h>

#include <stdio.h>
#include <assert.h>


int main(int argc, char **argv) {
    {
        uint8_t *src = new uint8_t[32];
        uint8_t *dst = new uint8_t[32];
        for (int i = 0; i < 32; i++) {
            src[i] = i;
            dst[i] = 0xff;
        }

        uint8x8_t v8_0 = vld1_u8(src);
        uint8x8_t v8_1 = vclt_u8(v8_0, vdup_n_u8(4));

        vst1_u8(dst, v8_1);
        // dst : 255 255 255 255   0   0   0   0
        for (int i = 0; i < 8; i++) {
            printf("%3d ", dst[i]);
        }
        printf("\n");
    }

    {
        float *src = new float[32];
        uint32_t *dst = new uint32_t[32];
        for (int i = 0; i < 32; i++) {
            src[i] = i;
            dst[i] = 255;
        }

        float32x4_t v0 = vld1q_f32(src);
        uint32x4_t v1 = vcltq_f32(v0, vdupq_n_f32(2));

        vst1q_u32(dst, v1);
        // dst : 4294967295 4294967295 0 0
        for (int i = 0; i < 4; i++) {
            printf("%14u ", dst[i]);
        }
        printf("\n");        
    }
    return 0;
}
