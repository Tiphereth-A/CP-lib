#ifndef TIFALIBS_CONV_DFT_TRAITS
#define TIFALIBS_CONV_DFT_TRAITS

#include "../util/util.hpp"

namespace tifa_libs {

template <class T>
concept dft_c = requires(T x, vec<typename T::data_t> v, u32 n) {
  { x.size() } -> std::same_as<u32>;
  x.bzr(n);
  x.dif(v, n);
  x.dit(v, n);
};

template <class T>
concept ntt_c = dft_c<T> && requires(T x) {
  T::max_size;
  T::G;
};

}  // namespace tifa_libs

#endif