#ifndef TIFALIBS_FAST_RSORT32
#define TIFALIBS_FAST_RSORT32

#include "../util/util.hpp"

namespace tifa_libs {

template <class T>
requires(sizeof(T) == 4)
void rsort32(vec<T>& a) {
  static u32 _0[256], _1[256], _2[256], _3[256];
  u32 n = (u32)a.size();
  vecu b(n);
  u32 *a_ = a.data(), *b_ = b.data();
  for (u32 *_ = a_ + n, *i = a_; i < _; ++i) {
    ++_0[*i & 255];
    ++_1[*i >> 8 & 255];
    ++_2[*i >> 16 & 255];
    ++_3[*i >> 24 & 255];
  }
  for (u32 i = 1; i < 256; ++i) {
    _0[i] += _0[i - 1];
    _1[i] += _1[i - 1];
    _2[i] += _2[i - 1];
    _3[i] += _3[i - 1];
  }
  for (u32* i = a_ + n; --i >= a_;) b_[--_0[*i & 255]] = *i;
  for (u32* i = b_ + n; --i >= b_;) a_[--_1[*i >> 8 & 255]] = *i;
  for (u32* i = a_ + n; --i >= a_;) b_[--_2[*i >> 16 & 255]] = *i;
  for (u32* i = b_ + n; --i >= b_;) a_[--_3[*i >> 24 & 255]] = *i;
  if constexpr (std::is_signed_v<T>) {
    u32 i = n;
    while (i && a[i - 1] < 0) --i;
    std::rotate(a_, a_ + i, a_ + n);
  }
}

}  // namespace tifa_libs

#endif