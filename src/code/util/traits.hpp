#ifndef TIFALIBS_UTIL_TRAITS
#define TIFALIBS_UTIL_TRAITS
// clang-format off
#include "util.hpp"

namespace tifa_libs {

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
template <class T> concept mint_c = requires(T x) { {x.mod()} -> uint_c; {x.val()} -> uint_c; };
template <class T> concept dft_c = requires(T x, vec<TPN T::data_t> v, u32 n) { {x.size()} -> std::same_as<u32>; x.bzr(n); x.dif(v, n); x.dit(v, n); };
template <class T> concept ntt_c = dft_c<T> && requires(T x) { T::max_size; T::G; };
template <class T> concept container_c = range<T> && !std::is_array_v<std::remove_cvref_t<T>> && !std::same_as<std::remove_cvref_t<T>, strn> && !std::same_as<std::remove_cvref_t<T>, strnv>;
//! weighted or unweighted
template <class T> concept sparse_graph_c = requires(T g) { g.cnt_arc; g.deg_in; g.deg_out; g.size(); g.foreach(0, fn_0); } && (requires(T g) { g.add_arc(0, 0); g.add_edge(0, 0); } || requires(T g) { g.add_arc(0, 0, {}); g.add_edge(0, 0, {}); });
//! weighted or unweighted
template <class T> concept alist_c = sparse_graph_c<T> && requires(T g) { {g[0]} -> common_range; g.build(); };
//! weighted or unweighted
template <class T> concept eog_c = sparse_graph_c<T> && requires(T g) { g.head; g.e; g.pop_startwith(0); };
//! weighted or unweighted
template <class T> concept tree_c = alist_c<T> && requires(T g) { g.root; };
// weighted
template <class T> concept sparse_graphw_c = sparse_graph_c<T> && !std::is_void_v<TPN T::w_t> && requires(T g, TPN T::w_t w) { g.add_arc(0, 0, w); g.add_edge(0, 0, w); };
// weighted
template <class T> concept alistw_c = alist_c<T> && sparse_graphw_c<T> && (requires(T g) { g[0].begin()->first; g[0].begin()->second; } || requires(T g) { g[0].begin()->to; g[0].begin()->cost; });
// weighted
template <class T> concept eogw_c = eog_c<T> && sparse_graphw_c<T> && requires(T g) { g[0].to; g[0].w; g[0].nxt; };
// weighted
template <class T> concept treew_c = tree_c<T> && alistw_c<T>;
// tree pointer (for DS)
template <class P> concept tp_ds_c = requires(P p) { p->ch; std::is_array_v<decltype(p->ch)>; std::rank_v<decltype(p->ch)> == 1; };
// binary tree pointer (for DS)
template <class P> concept tp2_ds_c = tp_ds_c<P> && std::extent_v<decltype(std::declval<P>()->ch)> == 2;
template <class T> concept istream_c = std::derived_from<T, std::istream> || requires(T is, T& (*func)(T&)) { {is >> func} -> std::same_as<T&>; };
template <class T> concept ostream_c = std::derived_from<T, std::ostream> || requires(T os, T& (*func)(T&)) { {os << func} -> std::same_as<T&>; };
template <class T> concept dsu_c = requires(T dsu, u32 x, u32 y) { {dsu.find(x)} -> std::same_as<i32>; {dsu.size()} -> std::same_as<u32>; {dsu.size(x)} -> std::same_as<u32>; {dsu.same(x, y)} -> std::same_as<bool>; {dsu.merge(x, y)} -> std::same_as<bool>; };

template <class T> struct to_sint : std::make_signed<T> {};
template <> struct to_sint<u128> { using type = i128; };
template <> struct to_sint<i128> { using type = i128; };
template <class T> using to_sint_t = TPN to_sint<T>::type;
template <class T> struct to_uint : std::make_unsigned<T> {};
template <> struct to_uint<u128> { using type = u128; };
template <> struct to_uint<i128> { using type = u128; };
template <class T> using to_uint_t = TPN to_uint<T>::type;
template <arithm_c T> struct to_bigger : std::make_unsigned<T> {};
#define _2(w,ww) template <> struct to_bigger<i##w> { using type = i##ww; }; template <> struct to_bigger<u##w> { using type = u##ww; }
#define _3(w,ww) _2(w,ww); template <> struct to_bigger<f##w> { using type = f##ww; }
_2(8, 16); _2(16, 32); _3(32, 64); _3(64, 128);
#undef _3
#undef _2
template <class T> using to_bigger_t = TPN to_bigger<T>::type;

//! only for template without non-type argument
template <class, template <class...> class> CEXP bool specialized_from_v = false;
template <template <class...> class T, class... Args> CEXP bool specialized_from_v<T<Args...>, T> = true;
static_assert(specialized_from_v<vecu, std::vector>);
template <arithm_c T> CEXP T inf_v = [] {
    if CEXP(sint_c<T>) return T(to_uint_t<T>(-1) / 4 - 1);
    else if CEXP(uint_c<T>) return T(-1) / 2 - 1;
    else return std::numeric_limits<T>::max() / 2 - 1;
}();

}  // namespace tifa_libs
// clang-format on
#endif