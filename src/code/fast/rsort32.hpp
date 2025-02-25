#ifndef TIFALIBS_FAST_RSORT32
#define TIFALIBS_FAST_RSORT32

#include "../util/util.hpp"

namespace tifa_libs {

template <class C>
requires(std::is_array_v<C> && std::integral<decltype(std::declval<C>()[0])> && sizeof(std::declval<C>()[0]) == 4) || (std::contiguous_iterator<TPN C::iterator> && std::integral<TPN C::value_type> && sizeof(TPN C::value_type) == 4)
void rsort32(C& a) NE {
  if (a.size() <= 1) return;
  u32 _0[256]{}, _1[256]{}, _2[256]{}, _3[256]{};
  const u32 n = (u32)a.size();
  vecu b(n);
  u32 *a_ = (u32*)a.data(), *b_ = (u32*)b.data();
  for (u32 *_ = a_ + n, *i = a_; i < _; ++i) ++_0[*i & 255], ++_1[*i >> 8 & 255], ++_2[*i >> 16 & 255], ++_3[*i >> 24 & 255];
  flt_ (u32, i, 1, 256) _0[i] += _0[i - 1], _1[i] += _1[i - 1], _2[i] += _2[i - 1], _3[i] += _3[i - 1];
  for (u32* i = a_ + n; --i >= a_;) b_[--_0[*i & 255]] = *i;
  for (u32* i = b_ + n; --i >= b_;) a_[--_1[*i >> 8 & 255]] = *i;
  for (u32* i = a_ + n; --i >= a_;) b_[--_2[*i >> 16 & 255]] = *i;
  for (u32* i = b_ + n; --i >= b_;) a_[--_3[*i >> 24 & 255]] = *i;
  if CEXP (std::is_signed_v<TPN C::value_type>) {
    u32 i = n;
    while (i && a[i - 1] < 0) --i;
    rotate(a_, a_ + n, a_ + i);
  }
}
template <class C>
requires(std::is_array_v<C> && std::integral<decltype(std::declval<C>()[0])> && sizeof(std::declval<C>()[0]) == 4) || range<C>
void sort(C& a) NE {
  if CEXP (std::is_array_v<C> || (std::contiguous_iterator<TPN C::iterator> && std::integral<TPN C::value_type> && sizeof(TPN C::value_type) == 4)) rsort32(a);
  else std::ranges::sort(a);
}

}  // namespace tifa_libs

#endif