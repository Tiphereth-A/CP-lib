#ifndef TIFA_LIBS_UTIL_SIMD
#define TIFA_LIBS_UTIL_SIMD

#pragma GCC target("sse4.2,avx2,avx512f")
#pragma GCC optimize("O3,unroll-loops")
#include <immintrin.h>

using m128 = __m128i;
using m256 = __m256i;
using m512 = __m512i;

#define SSE42 __attribute__((target("sse4.2")))
#define AVX2 __attribute__((target("avx2")))
#define AVX512F __attribute__((target("avx512f")))

#define ALIGN32 __attribute__((aligned(32)))
#define ALIGN64 __attribute__((aligned(64)))

#endif