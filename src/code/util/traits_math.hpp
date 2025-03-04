#ifndef TIFALIBS_UTIL_TRAITS_MATH
#define TIFALIBS_UTIL_TRAITS_MATH
// clang-format off
#include "alias_num.hpp"

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
template <class T> concept dft_c = requires(T x, std::vector<TPN T::data_t> v, u32 n) { {x.size()} -> std::same_as<u32>; x.bzr(n); x.dif(v, n); x.dit(v, n); };
template <class T> concept ntt_c = dft_c<T> && requires(T x) { T::max_size; T::G; };

template <class T> struct to_sint : std::make_signed<T> {};
template <> struct to_sint<u128> { using type = i128; };
template <> struct to_sint<i128> { using type = i128; };
template <class T> using to_sint_t = TPN to_sint<T>::type;
template <class T> struct to_uint : std::make_unsigned<T> {};
template <> struct to_uint<u128> { using type = u128; };
template <> struct to_uint<i128> { using type = u128; };
template <class T> using to_uint_t = TPN to_uint<T>::type;
template <arithm_c T> struct to_bigger : std::make_unsigned<T> {};
#define _(w,ww) template <> struct to_bigger< w> { using type =  ww; } 
#define _2(w,ww) _(i##w,i##ww); _(u##w,u##ww);
_2(8, 16); _2(16, 32); _2(32, 64); _2(64, 128); _(f32, f64); _(f64, f128);
#undef _2
#undef _ 
template <class T> using to_bigger_t = TPN to_bigger<T>::type;

template <arithm_c T> CEXP T inf_v = [] {
    if CEXP(sint_c<T>) return T(to_uint_t<T>(-1) / 4 - 1);
    else if CEXP(uint_c<T>) return T(-1) / 2 - 1;
    else return std::numeric_limits<T>::max() / 2 - 1;
}();

}  // namespace tifa_libs
// clang-format on
#endif