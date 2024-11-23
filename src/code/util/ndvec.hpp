#ifndef TIFALIBS_UTIL_NDVEC
#define TIFALIBS_UTIL_NDVEC

#include "util.hpp"

namespace tifa_libs {

template <u32 N, class Tp>
struct ndvec : public vec<ndvec<N - 1, Tp>> {
  static_assert(N, "N should be positive");
  using base_tp = ndvec<N - 1, Tp>;
  using base = vec<base_tp>;

  template <class... Ts>
  CEXP ndvec(std::integral auto n, Ts &&...args) : base(n, base_tp(args...)) {}

  CEXP u32 dim() const { return N; }
  template <class T>
  CEXP void fill(T &&x) {
    for (auto &i : *this) i.fill(std::forward<T>(x));
  }
};
template <class Tp>
struct ndvec<1, Tp> : public vec<Tp> {
  using base = vec<Tp>;

  CEXP ndvec(std::integral auto n) : base(n) {}

  CEXP u32 dim() const { return 1; }
  template <class T>
  CEXP void fill(T &&x) { std::fill(this->begin(), this->end(), std::forward<T>(x)); }
};

}  // namespace tifa_libs

#endif