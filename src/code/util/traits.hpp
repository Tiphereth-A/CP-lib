#ifndef TIFALIBS_UTIL_TRAITS
#define TIFALIBS_UTIL_TRAITS
// clang-format off
#include "util.hpp"

namespace tifa_libs {

template <class T> concept iterable_c = requires(T v) { { v.begin() } -> std::same_as<TPN T::iterator>; { v.end() } -> std::same_as<TPN T::iterator>; };
template <class T> concept container_c = iterable_c<T> && !std::same_as<std::remove_cvref_t<T>, strn> && !std::same_as<std::remove_cvref_t<T>, strnv>;
//! only for template without non-type argument
template <class, template <class...> class> CEXP bool specialized_from_v = false;
template <template <class...> class T, class... Args> CEXP bool specialized_from_v<T<Args...>, T> = true;
static_assert(specialized_from_v<vecu, std::vector>);

template <class T> CEXP bool is_char_v = std::is_same_v<T, char> || std::is_same_v<T, signed char> || std::is_same_v<T, unsigned char>;
template <class T> concept char_c = is_char_v<T>;
#pragma GCC diagnostic ignored "-Wpedantic"
template <class T> CEXP bool is_s128_v = std::is_same_v<T, __int128_t> || std::is_same_v<T, __int128>;
template <class T> concept s128_c = is_s128_v<T>;
template <class T> CEXP bool is_u128_v = std::is_same_v<T, __uint128_t> || std::is_same_v<T, unsigned __int128>;
template <class T> concept u128_c = is_u128_v<T>;
template <class T> CEXP bool is_i128_v = is_s128_v<T> || is_u128_v<T>;
template <class T> concept i128_c = is_u128_v<T>;
#pragma GCC diagnostic warning "-Wpedantic"
template <class T> CEXP bool is_int_v = std::is_integral_v<T> || is_i128_v<T>;
template <class T> concept int_c = is_int_v<T>;
template <class T> CEXP bool is_sint_v = is_s128_v<T> || (is_int_v<T> && std::is_signed_v<T>);
template <class T> concept sint_c = is_sint_v<T>;
template <class T> CEXP bool is_uint_v = is_u128_v<T> || (is_int_v<T> && std::is_unsigned_v<T>);
template <class T> concept uint_c = is_uint_v<T>;
template <class T> CEXP bool is_arithm_v = std::is_arithmetic_v<T> || is_int_v<T>;
template <class T> concept arithm_c = is_arithm_v<T>;
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