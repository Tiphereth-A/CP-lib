#ifndef TIFA_LIBS_UTIL_SIMD
#define TIFA_LIBS_UTIL_SIMD

#pragma GCC target("avx2")
#pragma GCC optimize("O3,unroll-loops")

#include <immintrin.h>

namespace tifa_libs {

using m256 = __m256i;

#define ALIGN __attribute__((aligned(64)))

#define SIMD_SET(x) _mm256_set1_epi32(x)
#define SIMD_SET64(x) _mm256_set1_epi64x(x)
#define SIMD_LOAD(p) _mm256_loadu_si256((__m256i*)(p))
#define SIMD_STORE(p, A) _mm256_storeu_si256((__m256i*)(p), A)

#define SIMD_AND(a, b) _mm256_and_si256(a, b)
#define SIMD_OR(a, b) _mm256_or_si256(a, b)
#define SIMD_XOR(a, b) _mm256_xor_si256(a, b)

#define SIMD_ADD(a, b) _mm256_add_epi32(a, b)
#define SIMD_SUB(a, b) _mm256_sub_epi32(a, b)
#define SIMD_CMP(a, b) _mm256_cmpgt_epi32(a, b)

#define SIMD_GETMOD(a, MOD) SUB(a, AND(CMP(a, MOD), MOD))
#define SIMD_MADD(a, b, MOD) GETMOD(ADD(a, b), MOD)
#define SIMD_MSUB(a, b, MOD) GETMOD(SUB(ADD(a, MOD), b), MOD)

#define SIMD_SETLO(a) _mm256_shuffle_epi32(a, 0xA0)
#define SIMD_SETHI(a) _mm256_shuffle_epi32(a, 0xF9)
#define SIMD_CAST64(a) AND(a, SET64(0xFFFFFFFF))
#define SIMD_ADD64(a, b) _mm256_add_epi64(a, b)

}  // namespace tifa_libs

#endif