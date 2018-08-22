/**
 * Copyright 2015- Co. Ltd. sizebook
 * @file reciprocal_inv.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-08-22 16:15:12
 */
#include <arm_neon.h>

#include <stdio.h>
#include <math.h>
#include <assert.h>


int main(int argc, char **argv) {
    float value[4] = {2.0f, 3.0f, 4.0f, 5.0f}, test[4];
    float32x4_t v = vld1q_f32(value);
    float32x4_t e = vrecpeq_f32(v);

    for (int try_cnt = 0; try_cnt < 3; try_cnt++) {
        // d2 = vmulq_f32(d0, v);
        e = vmulq_f32(e, vrecpsq_f32(v, e));

        // d0 = vrsqrtsq_f32(d0, v);
        vst1q_f32(test, e);
        for (int i = 0; i < 4; i++) {
            printf("%f(%f, %e), ", test[i], 1.0 / (value[i]), test[i] - 1.0 / (value[i]));
        }
        printf("\n");
    }

}

