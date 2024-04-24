#ifndef TIFALIBS_EDH_BASE64
#define TIFALIBS_EDH_BASE64

#include "../util/util.hpp"

namespace tifa_libs {

class Base64 {
  static constexpr char base[66] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/.";
  // clang-format off
  static constexpr char ibase(char c) { return 'a' <= c ? c - 0x47 : 'A' <= c ? c - 0x41 : '0' <= c ? c + 0x04 : '+' == c ? 0x3E : '/' == c ? 0x3F : 0x40; }
  // clang-format on

 public:
  static constexpr strn encode(vec<usz> const &a) {
    usz x = *std::ranges::max_element(a);
    std::bit_width(x);
    usz N = a.size(), B = std::max(6_uz, (usz)std::bit_width(x));
    strn S((B * N + 11) / 6, 0);
    S[0] = (char)B;
    for (usz i = 0; i < N; ++i)
      for (usz j = 0; j < B; ++j)
        if ((a[i] >> j) & 1) S[(i * B + j) / 6 + 1] |= 1 << ((i * B + j) % 6);
    for (auto &c : S) c = base[(usz)c];
    return S;
  }
  static constexpr vec<usz> decode(strn S) {
    for (auto &c : S) c = ibase(c);
    usz B = (usz)S[0], M = (usz)S.size() - 1;
    vec<usz> a(6 * M / B, 0);
    for (usz i = 0; i < M; ++i)
      for (usz j = 0; j < 6; ++j)
        if ((S[i + 1] >> j) & 1) a[(i * 6 + j) / B] |= usz(1) << ((i * 6 + j) % B);
    return a;
  }
};

}  // namespace tifa_libs

#endif