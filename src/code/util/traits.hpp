#ifndef TIFALIBS_UTIL_TRAITS
#define TIFALIBS_UTIL_TRAITS

#include "util.hpp"

namespace tifa_libs {

template <class T>
concept iterable_c = requires(T v) {
  { v.begin() } -> std::same_as<typename T::iterator>;
  { v.end() } -> std::same_as<typename T::iterator>;
};

template <class T>
concept container_c = iterable_c<T> && !std::derived_from<T, std::basic_string<typename T::value_type>>;

template <class T>
constexpr bool is_char_v = std::is_same_v<T, char> || std::is_same_v<T, signed char> || std::is_same_v<T, unsigned char>;
template <class T>
concept char_c = is_char_v<T>;

template <class T>
constexpr bool is_s128_v = std::is_same_v<T, __int128_t> || std::is_same_v<T, __int128>;
template <class T>
concept s128_c = is_s128_v<T>;

template <class T>
constexpr bool is_u128_v = std::is_same_v<T, __uint128_t> || std::is_same_v<T, unsigned __int128>;
template <class T>
concept u128_c = is_u128_v<T>;

template <class T>
constexpr bool is_int_v = std::is_integral_v<T> || is_s128_v<T> || is_u128_v<T>;
template <class T>
concept int_c = is_int_v<T>;

template <class T>
constexpr bool is_sint_v = is_s128_v<T> || (is_int_v<T> && std::is_signed_v<T>);
template <class T>
concept sint_c = is_sint_v<T>;

template <class T>
constexpr bool is_uint_v = is_u128_v<T> || (is_int_v<T> && std::is_unsigned_v<T>);
template <class T>
concept uint_c = is_uint_v<T>;

template <class T>
concept mint_c = requires(T x) {
  { x.mod() } -> uint_c;
  { x.val() } -> uint_c;
};

template <class T>
constexpr bool is_arithm_v = std::is_arithmetic_v<T> || is_int_v<T>;
template <class T>
concept arithm_c = is_arithm_v<T>;

template <class T>
using to_uint_t = typename std::conditional_t<std::is_same_v<T, i128>, u128, std::make_unsigned_t<T>>;

}  // namespace tifa_libs

#endif