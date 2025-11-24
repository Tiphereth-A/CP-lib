#ifndef TIFALIBS_EDH_BASE64
#define TIFALIBS_EDH_BASE64

#include "../util/alias_others.hpp"

namespace tifa_libs {

class base64 {
  static CEXP char base[66] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/.";
  // clang-format off
  static CEXP char ibase(char c) NE { if('a' <= c)return c - 0x47; else if('A' <= c)return c - 0x41; else if('0' <= c)return c + 0x04; else if('+' == c)return 0x3E; else if('/' == c)return 0x3F; return 0x40; }
  // clang-format on

 public:
  static CEXP strn encode(spn<usz> a) NE {
    const usz x = max(a), N = a.size(), B = max(6_usz, (usz)std::bit_width(x));
    strn S((B * N + 11) / 6, 0);
    S[0] = (char)B;
    flt_ (usz, i, 0, N)
      flt_ (usz, j, 0, B)
        if ((a[i] >> j) & 1) S[(i * B + j) / 6 + 1] |= 1 << ((i * B + j) % 6);
    for (auto& c : S) c = base[(usz)c];
    return S;
  }
  static CEXP vec<usz> decode(strn S) NE {
    for (auto& c : S) c = ibase(c);
    const usz B = (usz)S[0], M = (usz)S.size() - 1;
    vec<usz> a(6 * M / B, 0);
    flt_ (usz, i, 0, M)
      flt_ (usz, j, 0, 6)
        if ((S[i + 1] >> j) & 1) a[(i * 6 + j) / B] |= usz(1) << ((i * 6 + j) % B);
    return a;
  }
};

}  // namespace tifa_libs

#endif