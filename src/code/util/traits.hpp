#ifndef TIFALIBS_UTIL_TRAITS
#define TIFALIBS_UTIL_TRAITS
// clang-format off
#include "util.hpp"

namespace tifa_libs {

template <class T> concept container_c = range<T> && !std::same_as<std::remove_cvref_t<T>, strn> && !std::same_as<std::remove_cvref_t<T>, strnv>;
//! only for template without non-type argument
template <class, template <class...> class> CEXP bool specialized_from_v = false;
template <template <class...> class T, class... Args> CEXP bool specialized_from_v<T<Args...>, T> = true;
static_assert(specialized_from_v<vecu, std::vector>);

template <class T> concept char_c = std::same_as<T, char> || std::same_as<T, signed char> || std::same_as<T, unsigned char>;
#pragma GCC diagnostic ignored "-Wpedantic"
template <class T> concept s128_c = std::same_as<T, __int128_t> || std::same_as<T, __int128>;
template <class T> concept u128_c = std::same_as<T, __uint128_t> || std::same_as<T, unsigned __int128>;
template <class T> concept i128_c = s128_c<T> || u128_c<T>;
#pragma GCC diagnostic warning "-Wpedantic"
template <class T> concept imost64_c = std::integral<T> && sizeof(T) * __CHAR_BIT__ <= 64;
template <class T> concept smost64_c = imost64_c<T> && std::signed_integral<T>;
template <class T> concept umost64_c = imost64_c<T> && std::unsigned_integral<T>;
template <class T> concept int_c = i128_c<T> || imost64_c<T>;
template <class T> concept sint_c = s128_c<T> || smost64_c<T>;
template <class T> concept uint_c = u128_c<T> || umost64_c<T>;
template <class T> concept arithm_c = std::is_arithmetic_v<T> || int_c<T>;
template <class T> concept mint_c = requires(T x) { { x.mod() } -> uint_c; { x.val() } -> uint_c; };
template <class T> concept dft_c = requires(T x, vec<TPN T::data_t> v, u32 n) { { x.size() } -> std::same_as<u32>; x.bzr(n); x.dif(v, n); x.dit(v, n); };
template <class T> concept ntt_c = dft_c<T> && requires(T x) { T::max_size; T::G; };
//! weighted or unweighted
template <class T> concept adjlist_c = requires(T g) { g[0].begin(); g[0].end(); g.build(); g.size(); g.cnt_arc; g.deg_in; g.deg_out; };
// weighted
template <class T> concept adjlistw_c = adjlist_c<T> && !std::is_void_v<TPN T::w_t> && (requires(T g) { g[0].begin()->first; g[0].begin()->second; } || requires(T g) { g[0].begin()->to; g[0].begin()->cost; });
//! weighted or unweighted
template <class T> concept tree_c = adjlist_c<T> && requires(T g) { g.root; };
// weighted
template <class T> concept treew_c = adjlistw_c<T> && requires(T g) { g.root; };
// tree pointer (for DS)
template <class P> concept tp_ds_c = requires(P p) { p->ch; std::is_array_v<decltype(p->ch)>; std::rank_v<decltype(p->ch)> == 1; };
// binary tree pointer (for DS)
template <class P> concept tp2_ds_c = tp_ds_c<P> && std::extent_v<decltype(std::declval<P>()->ch)> == 2;
template <class T> concept istream_c = std::derived_from<T, std::istream> || requires(T is, T& (*func)(T&)) { { is >> func } -> std::same_as<T&>; };
template <class T> concept ostream_c = std::derived_from<T, std::ostream> || requires(T os, T& (*func)(T&)) { { os << func } -> std::same_as<T&>; };

template <class T> struct to_sint : std::make_signed<T> {};
template <> struct to_sint<u128> { using type = i128; };
template <> struct to_sint<i128> { using type = i128; };
template <class T> using to_sint_t = TPN to_sint<T>::type;
template <class T> struct to_uint : std::make_unsigned<T> {};
template <> struct to_uint<u128> { using type = u128; };
template <> struct to_uint<i128> { using type = u128; };
template <class T> using to_uint_t = TPN to_uint<T>::type;

}  // namespace tifa_libs
// clang-format on
#endif