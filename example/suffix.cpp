/**
 * Copyright 2015- Co. Ltd. sizebook
 * @file suffix.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-08-22 11:56:25
 */
#include <arm_neon.h>

#include <stdio.h>
#include <assert.h>


int main(int argc, char **argv) {

#if defined(__aarch64__)
    {  // 'v' : Add across vector
        uint8_t src[8] = {0, 1, 2, 3, 4, 5, 6, 7};
        uint8x8_t v8 = vld1_u8(src);
        uint8_t result = vaddv_u8(v8);
        assert(result == 28);
    }
#endif  // defined(__aarch64__)
    return 0;
}

