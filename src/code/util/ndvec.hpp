#ifndef TIFALIBS_UTIL_NDVEC
#define TIFALIBS_UTIL_NDVEC

#include "util.hpp"

namespace tifa_libs {

template <u32 N, class T>
struct ndvec : vec<T> {
  static_assert(N, "N should be positive");
  arr<u32, N + 1> idxs;

  template <class... Ts>
  CEXPE ndvec(Ts &&...args) { resize(args...); }
  template <class... Ts>
  CEXP void resize(Ts &&...args) {
    static_assert(sizeof...(args) == N);
    u32 n = 0;
    ((idxs[n++] = (u32)args), ...), idxs[N] = 1, partial_sum(idxs.rbegin(), idxs.rend(), idxs.rbegin(), std::multiplies<>{}), vec<T>::resize(idxs[0]);
  }
  template <class... Ts>
  CEXP T &operator()(Ts &&...args) {
    static_assert(sizeof...(args) == N);
    u32 n = 0, idx = 0;
    return ((idx += (u32)args * idxs[++n]), ...), this->operator[](idx);
  }
  template <class... Ts>
  CEXP T CR operator()(Ts &&...args) const {
    static_assert(sizeof...(args) == N);
    u32 n = 0, idx = 0;
    return ((idx += (u32)args * idxs[++n]), ...), this->operator[](idx);
  }
};

}  // namespace tifa_libs

#endif