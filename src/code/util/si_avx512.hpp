#ifndef TIFALIBS_UTIL_SI_AVX512
#define TIFALIBS_UTIL_SI_AVX512

#pragma GCC target("avx512f,bmi")
#include <immintrin.h>

#include "util.hpp"

namespace tifa_libs {

using i512 = __m512i;

using i32x16 = i32 __attribute__((vector_size(64)));
using u32x16 = u32 __attribute__((vector_size(64)));
using i64x8 = i64 __attribute__((vector_size(64)));
using u64x8 = u64 __attribute__((vector_size(64)));

inline u32x16 load_u32x16(u32 *ptr) { return (u32x16)(_mm512_load_si512((i512 *)ptr)); }
inline u32x16 loadu_u32x16(u32 *ptr) { return (u32x16)(_mm512_loadu_si512((i512 *)ptr)); }
inline void store_u32x16(u32 *ptr, u32x16 val) { _mm512_store_si512((i512 *)ptr, (i512)(val)); }
inline void storeu_u32x16(u32 *ptr, u32x16 val) { _mm512_storeu_si512((i512 *)ptr, (i512)(val)); }

#pragma GCC diagnostic ignored "-Wsign-conversion"
inline u32x16 set1_u32x16(u32 val) { return (u32x16)(_mm512_set1_epi32(val)); }
inline u64x8 set1_u64x8(u64 val) { return (u64x8)(_mm512_set1_epi64(val)); }

inline u32x16 setr_u32x16_si256(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { return (u32x16)_mm512_broadcast_i64x4(_mm256_setr_epi32(a0, a1, a2, a3, a4, a5, a6, a7)); }
inline u64x8 setr_u64x8_si256(u64 a0, u64 a1, u64 a2, u64 a3) { return (u64x8)_mm512_broadcast_i64x4(_mm256_setr_epi64x(a0, a1, a2, a3)); }
#pragma GCC diagnostic warning "-Wsign-conversion"

inline u64x8 setr_u64x8(u64 a0, u64 a1, u64 a2, u64 a3, u64 a4, u64 a5, u64 a6, u64 a7) { return (u64x8)_mm512_setr_epi64(a0, a1, a2, a3, a4, a5, a6, a7); }

template <int imm8>
u32x16 shuffle_u32x16(u32x16 val) { return (u32x16)(_mm512_shuffle_epi32((i512)(val), (_MM_PERM_ENUM)imm8)); }
inline u32x16 permute_u32x16(u32x16 val, u32x16 p) { return (u32x16)(_mm512_permutexvar_epi32((i512)(p), (i512)(val))); }

template <int imm8>
u32x16 permute_u32x16_epi128(u32x16 a) { return (u32x16)(_mm512_shuffle_i64x2((i512)(a), (i512)(a), imm8)); }

template <int imm16>
u32x16 blend_u32x16(u32x16 a, u32x16 b) { return (u32x16)(_mm512_mask_blend_epi32(imm16, (i512)(a), (i512)(b))); }
template <int imm8>
u32x16 blend_u32x16_si256(u32x16 a, u32x16 b) { return (u32x16)(_mm512_mask_blend_epi32(imm8 | (imm8 << 8), (i512)(a), (i512)(b))); }

#pragma GCC diagnostic ignored "-Wsign-conversion"
inline u32x16 shift_left_u32x16_epi64(u32x16 val, int imm8) { return (u32x16)(_mm512_slli_epi64((i512)(val), imm8)); }
inline u32x16 shift_right_u32x16_epi64(u32x16 val, int imm8) { return (u32x16)(_mm512_srli_epi64((i512)(val), imm8)); }
#pragma GCC diagnostic warning "-Wsign-conversion"

inline u32x16 min_u32x16(u32x16 a, u32x16 b) { return (u32x16)(_mm512_min_epu32((i512)(a), (i512)(b))); }
inline u32x16 mul64_u32x16(u32x16 a, u32x16 b) { return (u32x16)(_mm512_mul_epu32((i512)(a), (i512)(b))); }

}  // namespace tifa_libs

#endif