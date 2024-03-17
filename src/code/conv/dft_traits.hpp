#ifndef TIFALIBS_CONV_DFT_TRAITS
#define TIFALIBS_CONV_DFT_TRAITS

#include "../util/util.hpp"

namespace tifa_libs {

template <class T>
concept dft_c = requires(T x, vec<typename T::data_t> v) {
  { x.size() } -> std::same_as<u32>;
  { x.bzr(0_u32) };
  { x.dif(v, 0_u32) };
  { x.dit(v, 0_u32) };
};

template <class T>
concept ntt_c = dft_c<T> && requires(T x) {
  { T::max_size } -> std::unsigned_integral;
  { T::G } -> std::same_as<typename T::data_t>;
};

}  // namespace tifa_libs

#endif