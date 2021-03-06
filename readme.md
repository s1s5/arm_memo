# arm memo

## data types
`<type>x<lanes>_t`
- type : int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, float32_t, float64_t, float16_t
- lanes: 要素数
- 64bit : 
int8x8_t, int16x4_t, int32x2_t, int64x1_t, uint8x8_t, uint16x4_t, uint32x2_t, uint64x1_t, float32x2_t, float64x1_t, float16x4_t
- 128bit : 
int8x16_t, int16x8_t, int32x4_t, int64x2_t, uint8x16_t, uint16x8_t, uint32x4_t, uint64x2_t, float32x4_t, float64x2_t, float16x8_t

# 関数規則
`v<prefix><関数名><suffix>_<データタイプ>`が基本的な関数。

`v<prefix><関数名><suffix>_n_<データタイプ>`は引数にスカラ値がある場合使われる

`v<prefix><関数名><suffix>_lane_<データタイプ>`が引数に要素インデクスが指定できる場合に使われる


- 関数名は
  - `add`, `sub`, `mul`, `div` : 四則演算
  - `mla` : arg0 + arg1 * arg2
  - `mls` : arg0 - arg1 * arg2
  - `fma` : 
  - `fms` : 
  - `abd` : Absolute difference
  - `aba` : Absolute difference and accumulate
  - `rnd` : round
  - `abs` : 
  - `neg` : 
  - `recpe` / `recps` / `rsqrte` / `rsqrts` : reciprocal_inv.cpp, reciprocal_square.cpp参照
  - `sqrt` : 
  - `dot` : 
  - 比較系
    - `min` / `max` : 
    - `c**`, `ca**` : `**`の部分は{`eq`: `=`, `ge`: `>=`, `le`: `<=`, `gt`: `>`, `lt`: `<`}. `ca`の場合は絶対値比較
  - 特殊
    - `tbl` / `tbx` : 
  - ビット演算系
    - `shl` / `shr` : 
    - `sli` / `sri` : 
    - `tst` : test bits
    - `and`, `orr`, `eor` : 
    - `mvn` : Bitwise not
    - `bic` : bit clear
    - `cls` / `clz` / `cnt` : 
  - 型変換系
    - `cvt` : int -> floatとかの型変換
    - `mov` : int8x8 -> int16x8とかのデータのbit数を変換
    - `reinterpret` : 単なるcast
  - レジスタ書き込み、読み込み系
    - `ld*` / `st*` : neonレジスタとのデータコピー, 2,3,4ではinterleavedに要素のロード・ストアが行われる
    - `get` / `set` : 特定の要素の取得/設定をポインタを使わずにできる
    - `dup` : 全ベクタに固定の値の代入
  - 配置換え系
    - `ext` : 
    - `zip` / `uzp` : layout.cpp参照
    - `trn` : 
    - `rev` : 
    - `get` / `set` : vget_{high, low}_**はlowがインデクスの小さい半分の要素、highはインデクスの大きい半分の要素の取得
    - `combine` : ２つのint8x8_tとかを統合してint8x16_tにする


- `prefix`は
  - `h` : 演算結果を２で割るまで一気にやる
  - `rh` : 演算結果を２で割り、結果をroundするまで一気にやる
  - `q` : 演算結果をデータタイプで丸める
  - `r` : 結果を丸める
  - `d` : doubling
  - `p` : pairwise, 隣接する要素と足し合わせる
  - `u` : 
  - `s` : 

- `suffix`は
  - `l` : 演算結果のbit数が増えるパターン
  - `w` : bit数が多いものとの演算
  - `hn` : 上位ビットのみ演算対象にする？
  - `x` : extended??
  - `u` : signed -> unsigned
  - `n` : 演算結果のbit数が減るパターン
  - `v` : across vector, reduce. aarch64のときのみ。全要素の足し算とか。
  - `e` : Reciprocalステップの一番最初
  - `s` : Reciprocalステップ

# 関数
- [ ] int8x8_t vadd_s8(int8x8_t a, int8x8_t b)
- [ ] int16x8_t vaddl_s8(int8x8_t a, int8x8_t b), int16x8_t vaddl_high_s8(int8x16_t a, int8x16_t b), int16_t vaddlv_s8(int8x8_t a) << ????
- [ ] int16x8_t vaddw_s8(int16x8_t a, int8x8_t b)
- [ ] Vector halving add: int8x8_t vhadd_s8(int8x8_t a, int8x8_t b)
- [ ] Vector rounding halving add: int8x8_t vrhadd_s8(int8x8_t a, int8x8_t b)
- [ ] Vector saturating add: int8x8_t vqadd_s8(int8x8_t a, int8x8_t b), int8_t vuqaddb_s8(int8_t a, uint8_t b) << ????
- [ ] Vector add high half: int8x8_t vaddhn_s16(int16x8_t a, int16x8_t b)
- [ ] Vector rounding add high half: int8x8_t vraddhn_s16(int16x8_t a, int16x8_t b)
- [ ] Vector multiply: int8x8_t vmul_s8(int8x8_t a, int8x8_t b), int16x4_t vmul_lane_s16(int16x4_t a, int16x4_t v, const int lane)
- [ ] Vector multiply extended: float32x2_t vmulx_f32(float32x2_t a, float32x2_t b), float32x2_t vmulx_lane_f32(float32x2_t a, float32x2_t v, const int lane)
- [ ] Vector divide: float32x2_t vdiv_f32(float32x2_t a, float32x2_t b) f32, f64, f16しかない
- [ ] Vector multiply accumulate: int8x8_t vmla_s8(int8x8_t a, int8x8_t b, int8x8_t c)
- [ ] Vector multiply accumulate long: int16x8_t vmlal_s8(int16x8_t a, int8x8_t b, int8x8_t c)
- [ ] Vector multiply subtract: int8x8_t vmls_s8(int8x8_t a, int8x8_t b, int8x8_t c)
- [ ] Vector multiply subtract long: int16x8_t vmlsl_s8(int16x8_t a, int8x8_t b, int8x8_t c)
- [ ] Vector fused multiply accumulate: float32x2_t vfma_f32(float32x2_t a, float32x2_t b, float32x2_t c), float32x2_t vfma_lane_f32(float32x2_t a, float32x2_t b, float32x2_t v, const int lane)
- [ ] Vector fused multiply subtract: float32x2_t vfms_f32(float32x2_t a, float32x2_t b, float32x2_t c)
- [ ] Vector saturating doubling multiply high: int16x4_t vqdmulh_s16(int16x4_t a, int16x4_t b), int16_t vqdmulhh_lane_s16(int16_t a, int16x4_t v, const int lane)
- [ ] Vector saturating rounding doubling multiply high: int16x4_t vqrdmulh_s16(int16x4_t a, int16x4_t b), int16_t vqrdmulhh_lane_s16(int16_t a, int16x4_t v, const int lane)
- [ ] Vector saturating doubling multiply accumulate long: int32x4_t vqdmlal_s16(int32x4_t a, int16x4_t b, int16x4_t c), int32_t vqdmlalh_lane_s16(int32_t a, int16_t b, int16x4_t v, const int lane)
- [ ] Vector saturating doubling multiply subtract long: int32x4_t vqdmlsl_s16(int32x4_t a, int16x4_t b, int16x4_t c), int32_t vqdmlslh_lane_s16(int32_t a, int16_t b, int16x4_t v, const int lane)
- [ ] Vector long multiply: int16x8_t vmull_s8(int8x8_t a, int8x8_t b), int32x4_t vmull_high_lane_s16(int16x8_t a, int16x4_t v, const int lane)
- [ ] Vector saturating doubling long multiply: int32x4_t vqdmull_s16(int16x4_t a, int16x4_t b), int32_t vqdmullh_lane_s16(int16_t a, int16x4_t v, const int lane)
- [ ] Vector subtract: int8x8_t vsub_s8(int8x8_t a, int8x8_t b)
- [ ] Vector long subtract: int16x8_t vsubl_s8(int8x8_t a, int8x8_t b)
- [ ] Vector wide subtract: int16x8_t vsubw_s8(int16x8_t a, int8x8_t b)
- [ ] Vector halving subtract: int8x8_t vhsub_s8(int8x8_t a, int8x8_t b)
- [ ] Vector saturating subtract: int8x8_t vqsub_s8(int8x8_t a, int8x8_t b)
- [ ] Vector subtract high half: int8x8_t vsubhn_s16(int16x8_t a, int16x8_t b), int8x16_t vsubhn_high_s16(int8x8_t r, int16x8_t a, int16x8_t b)
- [ ] Vector rounding subtract high half: int8x8_t vrsubhn_s16(int16x8_t a, int16x8_t b), int8x16_t vrsubhn_high_s16(int8x8_t r, int16x8_t a, int16x8_t b)
- [ ] Vector compare equal: uint8x8_t vceq_s8(int8x8_t a, int8x8_t b)
- [ ] Vector compare greater-than or equal: uint8x8_t vcge_s8(int8x8_t a, int8x8_t b)
- [ ] Vector compare less-than or equal: uint8x8_t vcle_s8(int8x8_t a, int8x8_t b)
- [ ] Vector compare greater-than: uint8x8_t vcgt_s8(int8x8_t a, int8x8_t b)
- [ ] Vector compare less-than: uint8x8_t vclt_s8(int8x8_t a, int8x8_t b)
- [ ] Vector compare absolute greater-than or equal: uint32x2_t vcage_f32(float32x2_t a, float32x2_t b)
- [ ] Vector compare absolute less-than or equal: uint32x2_t vcale_f32(float32x2_t a, float32x2_t b)
- [ ] Vector compare absolute greater-than: uint32x2_t vcagt_f32(float32x2_t a, float32x2_t b)
- [ ] Vector compare absolute less-than: uint32x2_t vcalt_f32(float32x2_t a, float32x2_t b)
- [ ] Vector test bits: uint8x8_t vtst_s8(int8x8_t a, int8x8_t b)
- [ ] Absolute difference: int8x8_t vabd_s8(int8x8_t a, int8x8_t b)
- [ ] Absolute difference - long: int16x8_t vabdl_s8(int8x8_t a, int8x8_t b)
- [ ] Absolute difference and accumulate: int8x8_t vaba_s8(int8x8_t a, int8x8_t b, int8x8_t c)
- [ ] Absolute difference and accumulate - long: int16x8_t vabal_s8(int16x8_t a, int8x8_t b, int8x8_t c)
- [ ] Maximum: int8x8_t vmax_s8(int8x8_t a, int8x8_t b)
- [ ] Minimum: int8x8_t vmin_s8(int8x8_t a, int8x8_t b)
- [ ] Vector shift left: int8x8_t vshl_s8(int8x8_t a, int8x8_t b)
- [ ] Vector saturating shift left: int8x8_t vqshl_s8(int8x8_t a, int8x8_t b)
- [ ] Vector rounding shift left: int8x8_t vrshl_s8(int8x8_t a, int8x8_t b)
- [ ] Vector saturating rounding shift left: int8x8_t vqrshl_s8(int8x8_t a, int8x8_t b)
- [ ] Vector shift right: int8x8_t vshr_n_s8(int8x8_t a, const int n)
- [ ] Vector rounding shift right: int8x8_t vrshr_n_s8(int8x8_t a, const int n)
- [ ] Vector shift right and accumulate: int8x8_t vsra_n_s8(int8x8_t a, int8x8_t b, const int n)
- [ ] Vector rounding shift right and accumulate: int8x8_t vrsra_n_s8(int8x8_t a, int8x8_t b, const int n)
- [ ] Vector signed->unsigned saturating shift left: uint8x8_t vqshlu_n_s8(int8x8_t a, const int n)
- [ ] Vector narrowing saturating shift right: int8x8_t vshrn_n_s16(int16x8_t a, const int n), int8x16_t vshrn_high_n_s16(int8x8_t r, int16x8_t a, const int n)
- [ ] Vector signed->unsigned narrowing saturating shift right by constant: uint8x8_t vqshrun_n_s16(int16x8_t a, const int n)
- [ ] Vector signed->unsigned rounding narrowing saturating shift right by constant: uint8x8_t vqrshrun_n_s16(int16x8_t a, const int n)
- [ ] Vector rounding narrowing shift right: int8x8_t vrshrn_n_s16(int16x8_t a, const int n)
- [ ] Vector rounding narrowing saturating shift right: int8x8_t vqrshrn_n_s16(int16x8_t a, const int n)
- [ ] Vector widening shift left: int16x8_t vshll_n_s8(int8x8_t a, const int n)
- [ ] Vector shift right and insert: int8x8_t vsri_n_s8(int8x8_t a, int8x8_t b, const int n)
- [ ] Shift right and insert: int64_t vsrid_n_s64(int64_t a, int64_t b, const int n)
- [ ] Vector shift left and insert: int8x8_t vsli_n_s8(int8x8_t a, int8x8_t b, const int n)
- [ ] Vector convert: int32x2_t vcvt_s32_f32(float32x2_t a)
- [ ] Vector round: float32x2_t vrnd_f32(float32x2_t a)
- [ ] Vector narrow integer: int8x8_t vmovn_s16(int16x8_t a)
- [ ] Vector long move: int16x8_t vmovl_s8(int8x8_t a)
- [ ] Vector saturating narrow integer: int8x8_t vqmovn_s16(int16x8_t a), int8x16_t vqmovn_high_s16(int8x8_t r, int16x8_t a)
- [ ] Vector multiply accumulate with scalar: int16x4_t vmla_lane_s16(int16x4_t a, int16x4_t b, int16x4_t v, const int lane)
- [ ] Vector widening multiply accumulate with scalar: int32x4_t vmlal_lane_s16(int32x4_t a, int16x4_t b, int16x4_t v, const int lane)
- [ ] Vector widening saturating doubling multiply accumulate with scalar: int32x4_t vqdmlal_lane_s16(int32x4_t a, int16x4_t b, int16x4_t v, const int lane)
- [ ] Vector multiply subtract with scalar: int16x4_t vmls_lane_s16(int16x4_t a, int16x4_t b, int16x4_t v, const int lane)
- [ ] Vector widening multiply subtract with scalar: int32x4_t vmlsl_lane_s16(int32x4_t a, int16x4_t b, int16x4_t v, const int lane)
- [ ] Vector widening saturating doubling multiply subtract with scalar: int32x4_t vqdmlsl_lane_s16(int32x4_t a, int16x4_t b, int16x4_t v, const int lane)
- [ ] Vector multiply by scalar: int16x4_t vmul_n_s16(int16x4_t a, int16_t b)
- [ ] Vector long multiply with scalar: int32x4_t vmull_n_s16(int16x4_t a, int16_t b)
- [ ] Vector saturating doubling long multiply with scalar: int32x4_t vqdmull_n_s16(int16x4_t a, int16_t b)
- [ ] Vector saturating doubling long multiply by scalar: int32x4_t vqdmull_lane_s16(int16x4_t a, int16x4_t v, const int lane)
- [ ] Vector saturating doubling multiply high with scalar: int16x4_t vqdmulh_n_s16(int16x4_t a, int16_t b)
- [ ] Vector saturating doubling multiply high by scalar: int16x4_t vqdmulh_lane_s16(int16x4_t a, int16x4_t v, const int lane)
- [ ] Vector saturating rounding doubling multiply high with scalar: int16x4_t vqrdmulh_n_s16(int16x4_t a, int16_t b)
- [ ] Vector rounding saturating doubling multiply high by scalar: int16x4_t vqrdmulh_lane_s16(int16x4_t a, int16x4_t v, const int lane)
- [ ] Absolute: int8x8_t vabs_s8(int8x8_t a)
- [ ] Saturating absolute: int8x8_t vqabs_s8(int8x8_t a)
- [ ] Negate: int8x8_t vneg_s8(int8x8_t a)
- [ ] Saturating Negate: int8x8_t vqneg_s8(int8x8_t a)
- [ ] Count leading sign bits: int8x8_t vcls_s8(int8x8_t a)
- [ ] Count leading zeros: int8x8_t vclz_s8(int8x8_t a)
- [ ] Count number of set bits: int8x8_t vcnt_s8(int8x8_t a)
- [x] Reciprocal estimate: uint32x2_t vrecpe_u32(uint32x2_t a)
- [x] Reciprocal estimate/step and 1/sqrt estimate/step: float32x2_t vrecps_f32(float32x2_t a, float32x2_t b)
- [ ] Vector square root: float32x2_t vsqrt_f32(float32x2_t a)
- [x] Reciprocal square root estimate: uint32x2_t vrsqrte_u32(uint32x2_t a)
- [x] Reciprocal square root step: float32x2_t vrsqrts_f32(float32x2_t a, float32x2_t b)
- [ ] Bitwise not: int8x8_t vmvn_s8(int8x8_t a)
- [ ] Bitwise and: int8x8_t vand_s8(int8x8_t a, int8x8_t b)
- [ ] Bitwise or: int8x8_t vorr_s8(int8x8_t a, int8x8_t b)
- [ ] Bitwise exclusive or (EOR or XOR): int8x8_t veor_s8(int8x8_t a, int8x8_t b)
- [ ] Bit clear: int8x8_t vbic_s8(int8x8_t a, int8x8_t b)
- [ ] Bitwise OR complement: int8x8_t vorn_s8(int8x8_t a, int8x8_t b)
- [ ] Bitwise select: int8x8_t vbsl_s8(uint8x8_t a, int8x8_t b, int8x8_t c)
- [ ] Vector copy: int8x8_t vcopy_lane_s8(int8x8_t a, const int lane1, int8x8_t b, const int lane2)
- [ ] Reverse bit order: int8x8_t vrbit_s8(int8x8_t a)
- [ ] Create vector from bit pattern: int8x8_t vcreate_s8(uint64_t a)
- [ ] Vector duplicate: int8x8_t vdup_n_s8(int8_t value)
- [ ] Vector move: int8x8_t vmov_n_s8(int8_t value)
- [ ] Vector combine: int8x16_t vcombine_s8(int8x8_t low, int8x8_t high)
- [x] Vector extract: int8x8_t vget_high_s8(int8x16_t a)
- [ ] Vector extract: int8x8_t vext_s8(int8x8_t a, int8x8_t b, const int n)
- [x] Vector load: int8x8_t vld1_s8(int8_t const * ptr), int8x8_t vld1_lane_s8(int8_t const * ptr, int8x8_t src, const int lane), int8x8_t vld1_dup_s8(int8_t const * ptr)
- [x] Vector store: void vst1_s8(int8_t * ptr, int8x8_t val), void vst1_lane_s8(int8_t * ptr, int8x8_t val, const int lane), 
- [x] 2-element vector load: int8x8x2_t vld2_s8(int8_t const * ptr)
- [x] 3-element vector load: int8x8x3_t vld3_s8(int8_t const * ptr)
- [x] 4-element vector load: int8x8x4_t vld4_s8(int8_t const * ptr)
- [x] 2-element vector store: void vst2_s8(int8_t * ptr, int8x8x2_t val)
- [x] 3-element vector store: void vst3_s8(int8_t * ptr, int8x8x3_t val)
- [x] 4-element vector store: void vst4_s8(int8_t * ptr, int8x8x4_t val)
- [x] Pairwise add: int8x8_t vpadd_s8(int8x8_t a, int8x8_t b)
- [x] Long pairwise add: int16x4_t vpaddl_s8(int8x8_t a)
- [x] Long pairwise add and accumulate: int16x4_t vpadal_s8(int16x4_t a, int8x8_t b)
- [ ] Folding maximum of adjacent pairs: int8x8_t vpmax_s8(int8x8_t a, int8x8_t b)
- [ ] Folding minimum of adjacent pairs: int8x8_t vpmin_s8(int8x8_t a, int8x8_t b)
- [x] Add across vector: int8_t vaddv_s8(int8x8_t a)
- [ ] Reverse vector elements (swap endianness): int8x8_t vrev64_s8(int8x8_t vec)
- [ ] Zip vectors: int8x8_t vzip1_s8(int8x8_t a, int8x8_t b)
- [ ] Unzip vectors: int8x8_t vuzp1_s8(int8x8_t a, int8x8_t b)
- [ ] Transpose elements: int8x8_t vtrn1_s8(int8x8_t a, int8x8_t b)
- [ ] Table look-up: int8x8_t vtbl1_s8(int8x8_t a, int8x8_t b)
- [ ] Extended table look-up: int8x8_t vtbx1_s8(int8x8_t a, int8x8_t b, int8x8_t c)
- [x] Extract lanes from a vector: uint8_t vget_lane_u8(uint8x8_t v, const int lane)
- [x] Set lanes within a vector: uint8x8_t vset_lane_u8(uint8_t a, uint8x8_t v, const int lane)
- [ ] Vector reinterpret cast operations: int16x4_t vreinterpret_s16_s8(int8x8_t a)
- [ ] AES cryptography: uint8x16_t vaeseq_u8(uint8x16_t data, uint8x16_t key)
- [ ] SHA1 cryptography: uint32x4_t vsha1cq_u32(uint32x4_t hash_abcd, uint32_t hash_e, uint32x4_t wk)
- [ ] SHA2-256 cryptography: uint32x4_t vsha256hq_u32(uint32x4_t hash_abcd, uint32x4_t hash_efgh, uint32x4_t wk)
- [ ] CRC-32 checksum: uint32_t __crc32b(uint32_t a, uint8_t b)
- [ ] Signed Saturating Rounding Doubling Multiply Accumulate: int16x4_t vqrdmlah_s16(int16x4_t a, int16x4_t b, int16x4_t c)
- [ ] Signed Saturating Rounding Doubling Multiply Subtract: int16x4_t vqrdmlsh_s16(int16x4_t a, int16x4_t b, int16x4_t c)
- [ ] Dot Product unsigned arithmetic: uint32x2_t vdot_u32(uint32x2_t r, uint8x8_t a, uint8x8_t b)
- [ ] Three-way Exclusive OR: uint8x16_t veor3q_u8(uint8x16_t a, uint8x16_t b, uint8x16_t c)
- [ ] Floating-point fused Multiply-Add Long to accumulator: float32x2_t vfmlal_low_u32(float32x2_t r, float16x4_t a, float16x4_t b)
- [ ] Floating-point fused Multiply-Subtract Long from accumulator: float32x2_t vfmlsl_low_u32(float32x2_t r, float16x4_t a, float16x4_t b)


- [intrinsics](/intrinsics.md)

# サンプル

``` shell
$ cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE=../../work/sizebook/engine/cmake/toolchain-rpi.cmake <project_dir>
```

