/**
 * Copyright 2015- Co. Ltd. sizebook
 * @file reciprocal_square.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-08-22 13:23:02
 */
#include <arm_neon.h>

#include <stdio.h>
#include <math.h>
#include <assert.h>


int main(int argc, char **argv) {
    // "vrsqrte.f32         d0, d0\n\t"       // d0 = ~ 1.0 / sqrt(d0)
    // "vmul.f32 d2, d0, d1\n\t"              // d2 = d0 * d1
    // "vrsqrts.f32         d3, d2, d0\n\t"   // d3 = (3 - d0 * d2) / 2
    // "vmul.f32 d0, d0, d3\n\t"              // d0 = d0 * d3

    float value[4] = {2.0f, 3.0f, 4.0f, 5.0f}, test[4];
    float32x4_t v = vld1q_f32(value);
    float32x4_t d0 = vrsqrteq_f32(v), d2, d3;

    // vst1q_f32(test, d0);
    // for (int i = 0; i < 4; i++) {
    //     printf("%f(%f, %e), ", test[i], 1.0 / sqrt(value[i]), test[i] - 1.0 / sqrt(value[i]));
    // }
    // printf("\n");

    for (int try_cnt = 0; try_cnt < 5; try_cnt++) {
        // d2 = vmulq_f32(d0, v);
        // d3 = vrsqrtsq_f32(d0, d2);
        // d0 = vmulq_f32(d0, d3);

        d0 = vmulq_f32(d0, vrsqrtsq_f32(d0, vmulq_f32(d0, v)));


        vst1q_f32(test, d0);
        for (int i = 0; i < 4; i++) {
            printf("%f(%f, %e), ", test[i], 1.0 / sqrt(value[i]), test[i] - 1.0 / sqrt(value[i]));
        }
        printf("\n");
    }

}
