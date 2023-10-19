#ifndef TIFA_LIBS_UTIL_SIMD
#define TIFA_LIBS_UTIL_SIMD

#pragma GCC target("avx2,avx512f,avx512vl")
#pragma GCC optimize("O3,unroll-loops")
#include <immintrin.h>

namespace tifa_libs {

using m256 = __m256i;

}  // namespace tifa_libs

#endif