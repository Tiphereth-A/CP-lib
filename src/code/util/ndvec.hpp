#ifndef TIFALIBS_UTIL_NDVEC
#define TIFALIBS_UTIL_NDVEC

#include "util.hpp"

namespace tifa_libs {

template <u32 N, class Tp>
struct ndvec : public vec<ndvec<N - 1, Tp>> {
  static_assert(N, "N should be positive");
  using base_tp = ndvec<N - 1, Tp>;
  using base = vec<base_tp>;
  template <class T, typename... Ts>
  ndvec(T &&n, Ts &&...args) : base(n, base_tp(args...)) {}
  constexpr u32 dim() const { return N; }
  template <class T>
  void fill(T &&x) {
    for (auto &i : *this) i.fill(x);
  }
};
template <class Tp>
struct ndvec<1, Tp> : public vec<Tp> {
  using base = vec<Tp>;
  template <class T>
  ndvec(T &&n) : base(n) {}
  constexpr u32 dim() const { return 1; }
  template <class T>
  void fill(T &&x) { std::fill(this->begin(), this->end(), x); }
};

}  // namespace tifa_libs

#endif