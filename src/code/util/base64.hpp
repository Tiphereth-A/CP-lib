#ifndef TIFA_LIBS_UTIL_BASE64
#define TIFA_LIBS_UTIL_BASE64

#include "../bit/cntl0.hpp"
#include "util.hpp"

namespace tifa_libs::util {

class Base64 {
  static_assert(std::is_integral_v<size_t>);

  static constexpr char base[66] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/.";
  static constexpr char ibase(char c) {
    // clang-format off
    return 'a' <= c ? 0x1A + c - 'a' :
           'A' <= c ? 0x00 + c - 'A' :
           '0' <= c ? 0x34 + c - '0' :
           '+' == c ? 0x3E :
           '/' == c ? 0x3F : 0x40;
    // clang-format on
  }

 public:
  static std::string encode(vec<size_t> const &a) {
    size_t x = *std::max_element(a.begin(), a.end()), y = *std::min_element(a.begin(), a.end());
    size_t N = a.size(), B = std::max(size_t(6), (sizeof(size_t) * 8 - (size_t)(y < 0 ? 0 : bit::cntl0(x))));
    std::string S((B * N + 11) / 6, 0);
    S[0] = (char)B;
    for (size_t i = 0; i < N; ++i)
      for (size_t j = 0; j < B; ++j)
        if ((a[i] >> j) & 1) S[(i * B + j) / 6 + 1] |= 1 << ((i * B + j) % 6);
    for (auto &c : S) c = base[(size_t)c];
    return S;
  }
  static vec<size_t> decode(std::string S) {
    for (auto &c : S) c = ibase(c);
    size_t B = (size_t)S[0], M = (size_t)S.size() - 1;
    vec<size_t> a(6 * M / B, 0);
    for (size_t i = 0; i < M; ++i)
      for (size_t j = 0; j < 6; ++j)
        if ((S[i + 1] >> j) & 1) a[(i * 6 + j) / B] |= size_t(1) << ((i * 6 + j) % B);
    return a;
  }
};

}  // namespace tifa_libs::util

#endif