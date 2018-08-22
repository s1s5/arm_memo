/**
 * Copyright 2015- Co. Ltd. sizebook
 * @file layout.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-08-22 12:13:02
 */
#include <arm_neon.h>

#include <stdio.h>
#include <assert.h>


int main(int argc, char **argv) {
    // {
    //     uint8_t *src = new uint8_t[32];
    //     uint8_t *dst = new uint8_t[32];
    //     for (int i = 0; i < 32; i++) {
    //         src[i] = i;
    //         dst[i] = 0xff;
    //     }

    //     uint8x8_t v8_0 = vld1_u8(src);
    //     uint8x8_t v8_1 = vld1_u8(src + 8);

    //     uint8x8_t v8_2 = vzip1_u8(v8_0, v8_1);
    //     vst1_u8(dst, v8_2);
    //     for (int i = 0; i < 8; i++) {
    //         printf("%d\n", dst[i]);
    //     }
    // }

    {
        uint8_t *src = new uint8_t[32];
        uint8_t *dst = new uint8_t[32];
        for (int i = 0; i < 32; i++) {
            src[i] = i;
            dst[i] = 0xff;
        }

        uint8x8_t v8_0 = vld1_u8(src);
        uint8x8_t v8_1 = vld1_u8(src + 16);

        {  // zip
            uint8x8x2_t v8_2 = vzip_u8(v8_0, v8_1);
            vst1_u8(dst, v8_2.val[0]);
            // val[0] = {0, 16, 1, 17, 2, 18, 3, 19};
            for (int i = 0; i < 8; i++) {
                if ((i & 1) == 0) {
                    assert(dst[i] == src[i / 2]);
                } else {
                    assert(dst[i] == src[i / 2 + 16]);
                }
            }
            
            vst1_u8(dst, v8_2.val[1]);
            // val[1] = {4, 20, 5, 21, 6, 22, 7, 23};
            for (int i = 0; i < 8; i++) {
                if ((i & 1) == 0) {
                    assert(dst[i] == src[i / 2 + 4]);
                } else {
                    assert(dst[i] == src[i / 2 + 16 + 4]);
                }
            }

            vst2_u8(dst, v8_2);
            // dst = {0, 4, 16, 20, 1, 5, 17, 21, 2, 6, 18, 22, 3, 7, 19, 23}
            for (int i = 0; i < 16; i++) {
                switch (i % 4) {
                    case 0:
                        assert(dst[i] == src[i / 4]);
                        break;
                    case 1:
                        assert(dst[i] == src[i / 4 + 4]);
                        break;
                    case 2:
                        assert(dst[i] == src[i / 4 + 16]);
                        break;
                    case 3:
                        assert(dst[i] == src[i / 4 + 16 + 4]);
                        break;
                }
            }
        }
        {
            uint8x8x2_t v8_2 = vuzp_u8(v8_0, v8_1);
            vst1_u8(dst, v8_2.val[0]);
            // val[0] = {0, 2, 4, 6, 16, 18, 20, 22}
            for (int i = 0; i < 8; i++) {
                if (i < 4) {
                    assert(dst[i] == src[2 * i]);
                } else {
                    assert(dst[i] == src[2 * (i - 4) + 16]);
                }
            }

            vst1_u8(dst, v8_2.val[1]);
            // val[1] = {1, 3, 5, 7, 17, 19, 21, 23}
            for (int i = 0; i < 8; i++) {
                if (i < 4) {
                    assert(dst[i] == src[2 * i + 1]);
                } else {
                    assert(dst[i] == src[2 * (i - 4) + 16 + 1]);
                }
            }

            vst2_u8(dst, v8_2);
            // dst = {0, 1, 2, 3, 4, 5, 6, 7, 16, 17, 18, 19, 20, 21, 22, 23}
            for (int i = 0; i < 16; i++) {
                if (i < 8) {
                    assert(dst[i] == src[i]);
                } else {
                    assert(dst[i] == src[(i - 8) + 16]);
                }
            }
        }
    }

    return 0;
}

