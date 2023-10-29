#ifndef TIFA_LIBS_FAST_MONTGOMERY_SIMD
#define TIFA_LIBS_FAST_MONTGOMERY_SIMD

#include "../util/simd.hpp"

namespace tifa_libs::math {

SSE42 inline m128 my128_mullo_epu32(m128 const &a, m128 const &b) { return _mm_mullo_epi32(a, b); }

SSE42 inline m128 my128_mulhi_epu32(m128 const &a, m128 const &b) {
  m128 a13 = _mm_shuffle_epi32(a, 0xF5), b13 = _mm_shuffle_epi32(b, 0xF5);
  m128 p02 = _mm_mul_epu32(a, b), p13 = _mm_mul_epu32(a13, b13);
  return _mm_unpackhi_epi64(_mm_unpacklo_epi32(p02, p13), _mm_unpackhi_epi32(p02, p13));
}

SSE42 inline m128 montgomery_mul_128(m128 const &a, m128 const &b, m128 const &r, m128 const &m1) {
  return _mm_sub_epi32(_mm_add_epi32(my128_mulhi_epu32(a, b), m1), my128_mulhi_epu32(my128_mullo_epu32(my128_mullo_epu32(a, b), r), m1));
}

SSE42 inline m128 montgomery_add_128(m128 const &a, m128 const &b, m128 const &m2, m128 const &m0) {
  m128 _ = _mm_sub_epi32(_mm_add_epi32(a, b), m2);
  return _mm_add_epi32(_mm_and_si128(_mm_cmpgt_epi32(m0, _), m2), _);
}

SSE42 inline m128 montgomery_sub_128(m128 const &a, m128 const &b, m128 const &m2, m128 const &m0) {
  m128 _ = _mm_sub_epi32(a, b);
  return _mm_add_epi32(_mm_and_si128(_mm_cmpgt_epi32(m0, _), m2), _);
}

AVX2 inline m256 my256_mullo_epu32(m256 const &a, m256 const &b) { return _mm256_mullo_epi32(a, b); }

AVX2 inline m256 my256_mulhi_epu32(m256 const &a, m256 const &b) {
  m256 a13 = _mm256_shuffle_epi32(a, 0xF5), b13 = _mm256_shuffle_epi32(b, 0xF5);
  m256 p02 = _mm256_mul_epu32(a, b), p13 = _mm256_mul_epu32(a13, b13);
  return _mm256_unpackhi_epi64(_mm256_unpacklo_epi32(p02, p13), _mm256_unpackhi_epi32(p02, p13));
}

AVX2 inline m256 montgomery_mul_256(m256 const &a, m256 const &b, m256 const &r, m256 const &m1) { return _mm256_sub_epi32(_mm256_add_epi32(my256_mulhi_epu32(a, b), m1), my256_mulhi_epu32(my256_mullo_epu32(my256_mullo_epu32(a, b), r), m1)); }

AVX2 inline m256 montgomery_add_256(m256 const &a, m256 const &b, m256 const &m2, m256 const &m0) {
  m256 _ = _mm256_sub_epi32(_mm256_add_epi32(a, b), m2);
  return _mm256_add_epi32(_mm256_and_si256(_mm256_cmpgt_epi32(m0, _), m2), _);
}

AVX2 inline m256 montgomery_sub_256(m256 const &a, m256 const &b, m256 const &m2, m256 const &m0) {
  m256 _ = _mm256_sub_epi32(a, b);
  return _mm256_add_epi32(_mm256_and_si256(_mm256_cmpgt_epi32(m0, _), m2), _);
}

}  // namespace tifa_libs::math

#endif