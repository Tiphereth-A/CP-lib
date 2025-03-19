#ifndef TIFALIBS_UTIL_TRAITS_DS
#define TIFALIBS_UTIL_TRAITS_DS
// clang-format off
#include "alias_num.hpp"

namespace tifa_libs {

// tree pointer (for DS)
template <class P> concept tp_ds_c = requires(P p) { p->ch; std::is_array_v<decltype(p->ch)>; std::rank_v<decltype(p->ch)> == 1; };
// binary tree pointer (for DS)
template <class P> concept tp2_ds_c = tp_ds_c<P> && std::extent_v<decltype(std::declval<P>()->ch)> == 2;
template <class T> concept dsu_c = requires(T dsu, u32 x, u32 y) { {dsu.find(x)} -> std::same_as<i32>; {dsu.size()} -> std::same_as<u32>; {dsu.size(x)} -> std::same_as<u32>; {dsu.same(x, y)} -> std::same_as<bool>; {dsu.merge(x, y)} -> std::same_as<bool>; };

}  // namespace tifa_libs
// clang-format on
#endif