#ifndef TIFALIBS_EDH_HAMMING
#define TIFALIBS_EDH_HAMMING

#include "../ds/dbitset.hpp"

namespace tifa_libs {

class hamming {
  static CEXP u32 get_m(u64 n) NE {
    u32 m = (u32)std::bit_width(n);
    if ((1_u64 << m) - m - 1 < n) ++m;
    return m;
  }
  static CEXP auto get_nm(u64 len) NE {
    u32 m = (u32)std::bit_width(len - 1);
    return std::make_pair(len - m - 1, m);
  }

 public:
  static CEXP auto encode(ds::dbitset CR msg) NE {
    const u64 n = msg.size(), m = get_m(n), len = n + m + 1;
    ds::dbitset code(len);
    flt_ (u64, i, 1, len, j = 0)
      if (!std::has_single_bit(i)) code.set(i, msg[j++]);
    u64 _ = 0;
    for (u64 j = code.find_next(0); j < len; j = code.find_next(j)) _ ^= j;
    for (u64 i = 1; i < len; i *= 2)
      if (_ & i) code.flip(i);
    code.set(0, code.parity());
    return code;
  }
  // {@code code} will be auto corrected if possible
  static CEXP auto decode(ds::dbitset& code) NE {
    auto const [n, m] = get_nm(code.size());
    std::optional<ds::dbitset> ret;
    usz err = 0;
    for (u64 i = code.find_next(0); i < code.size(); i = code.find_next(i)) err ^= i;
    if (err) {
      if (!code.parity()) return ret;
      code.flip(err);
    }
    ret.emplace(n);
    ds::dbitset::word_t _ = 0;
    u32 wj = 0;
    flt_ (u64, i, 1, code.size(), j = 0) {
      if (std::has_single_bit(i)) continue;
      if (code[i]) _ |= ((ds::dbitset::word_t)1 << j);
      if (++j == ds::dbitset::word_width) ret->raw()[wj++] = _, j = _ = 0;
    }
    if (_) ret->raw()[wj] = _;
    return ret;
  }
};
}  // namespace tifa_libs

#endif