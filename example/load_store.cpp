/**
 * Copyright 2015- Co. Ltd. sizebook
 * @file load_store.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-08-22 10:47:13
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
        // ロード
        uint8x8_t v8 = vld1_u8(src);
        // ストア
        vst1_u8(dst, v8);
        for (int i = 0; i < 8; i++) {
            assert(dst[i] == src[i]);  // 同じ値が入る
        }
        assert(dst[8] == 0xff);

        // 部分ロード
        uint8x8_t v8_2 = vld1_lane_u8(src + 8, v8, 4);  // 0 - 7 までしか指定できない
        vst1_u8(dst, v8_2);
        for (int i = 0; i < 8; i++) {
            if (i == 4) {
                assert(dst[i] == src[8]);  // 指定した要素のみ変更される
            } else {
                assert(dst[i] == src[i]);
            }
        }
        assert(dst[8] == 0xff);

        // 部分ストア
        vst1_lane_u8(dst, v8_2, 3);
        for (int i = 0; i < 8; i++) {
            if (i == 0) {
                assert(dst[i] == src[3]);  // 指定した要素のみ抽出される
            } else if (i == 4) {
                assert(dst[i] == src[8]);  // 他のインデクスには影響なし
            } else {
                assert(dst[i] == src[i]);
            }
        }
        assert(dst[8] == 0xff);
    }

    {
        uint8_t *src = new uint8_t[32];
        uint8_t *dst = new uint8_t[32];
        for (int i = 0; i < 32; i++) {
            src[i] = i;
            dst[i] = 0xff;
        }
        // ロード
        uint8x8x2_t v8 = vld2_u8(src);
        // ストア
        vst2_u8(dst, v8);
        for (int i = 0; i < 16; i++) {
            assert(dst[i] == src[i]);  // これは同じになる
            dst[i] = 0xff;
        }
        assert(dst[16] == 0xff);

        // valごとにストア
        vst1_u8(dst, v8.val[0]);
        vst1_u8(dst + 8, v8.val[1]);

        // interleaveされてロードされている
        for (int i = 0; i < 8; i++) {
            assert(dst[i] == src[2 * i]);
        }
        for (int i = 0; i < 8; i++) {
            assert(dst[i + 8] == src[2 * i + 1]);
        }
        assert(dst[16] == 0xff);

        auto v8_2 = vld2_lane_u8(src + 20, v8, 4);  // 0 - 7 までしか指定できない
        vst2_u8(dst, v8_2);
        for (int i = 0; i < 16; i++) {
            if (i == 4 * 2 or i == 4 * 2 + 1) {
                assert(dst[i] == src[(i - 4 * 2) + 20]);
            } else {
                assert(dst[i] == src[i]);  // これは同じになる
            }
        }
        assert(dst[16] == 0xff);

        vst2_lane_u8(dst, v8_2, 3);  // 指定したレーンをストア
        for (int i = 0; i < 16; i++) {
            if (i == 0 or i == 1) {
                assert(dst[i] == src[i + 3 * 2]);
            } else if (i == 4 * 2 or i == 4 * 2 + 1) {
                assert(dst[i] == src[(i - 4 * 2) + 20]);
            } else {
                assert(dst[i] == src[i]);  // これは同じになる
            }
        }
        assert(dst[16] == 0xff);        
    }

    {
        uint8_t *src = new uint8_t[32];
        uint8_t *dst = new uint8_t[32];
        for (int i = 0; i < 32; i++) {
            src[i] = i;
            dst[i] = 0xff;
        }
        // ロード
        uint8x16_t v8 = vld1q_u8(src);
        // ストア
        vst1q_u8(dst, v8);
        for (int i = 0; i < 16; i++) {
            assert(dst[i] == src[i]);  // これは同じになる
            dst[i] = 0xff;
        }
        assert(dst[16] == 0xff);
        
        auto hv8 = vget_high_u8(v8);
        vst1_u8(dst, hv8);
        for (int i = 0; i < 8; i++) {
            assert(dst[i] == src[i + 8]);
            dst[i] = 0xff;
        }
        assert(dst[8] == 0xff);

        auto lv8 = vget_low_u8(v8);
        vst1_u8(dst, lv8);
        for (int i = 0; i < 8; i++) {
            assert(dst[i] == src[i]);
            dst[i] = 0xff;
        }
        assert(dst[8] == 0xff);
        
    }
    return 0;
}
