#ifndef TIFALIBS_UTIL_TRAITS
#define TIFALIBS_UTIL_TRAITS

#include "util.hpp"

namespace tifa_libs {

template <class T>
using is_iterable = typename std::conditional_t<std::is_same_v<decltype(std::declval<std::remove_cvref_t<T>>().begin()), typename std::remove_cvref_t<T>::iterator> && std::is_same_v<decltype(std::declval<std::remove_cvref_t<T>>().end()), typename std::remove_cvref_t<T>::iterator>, std::true_type, std::false_type>;
template <class T>
concept iterable_c = is_iterable<T>::value;

template <class T>
using is_container = typename std::conditional_t<is_iterable<T>::value && !std::is_base_of_v<T, std::basic_string<typename T::value_type>>, std::true_type, std::false_type>;
template <class T>
concept container_c = is_iterable<T>::value;

template <class T>
using is_char = typename std::conditional_t<std::is_same_v<T, char> || std::is_same_v<T, signed char> || std::is_same_v<T, unsigned char>, std::true_type, std::false_type>;
template <class T>
concept char_c = is_char<T>::value;

template <class T>
using is_s128 = typename std::conditional<std::is_same_v<T, __int128_t> || std::is_same_v<T, __int128>, std::true_type, std::false_type>::type;
template <class T>
concept s128_c = is_s128<T>::value;

template <class T>
using is_u128 = typename std::conditional<std::is_same_v<T, __uint128_t> || std::is_same_v<T, unsigned __int128>, std::true_type, std::false_type>::type;
template <class T>
concept u128_c = is_u128<T>::value;

template <class T>
using is_int = typename std::conditional_t<std::is_integral_v<T> || is_s128<T>::value || is_u128<T>::value, std::true_type, std::false_type>;
template <class T>
concept int_c = is_int<T>::value;

template <class T>
using is_sint = typename std::conditional_t<is_s128<T>::value || (is_int<T>::value && std::is_signed_v<T>), std::true_type, std::false_type>;
template <class T>
concept sint_c = is_sint<T>::value;

template <class T>
using is_uint = typename std::conditional_t<is_u128<T>::value || (is_int<T>::value && std::is_unsigned_v<T>), std::true_type, std::false_type>;
template <class T>
concept uint_c = is_uint<T>::value;

template <class T>
using is_mint = typename std::conditional_t<is_uint<decltype(std::declval<std::remove_cvref_t<T>>().mod())>::value && is_uint<decltype(std::declval<std::remove_cvref_t<T>>().val())>::value, std::true_type, std::false_type>;
template <class T>
concept mint_c = is_mint<T>::value;

template <class T>
using is_arithm = typename std::conditional_t<std::is_arithmetic_v<T> || is_int<T>::value, std::true_type, std::false_type>;
template <class T>
concept arithm_c = is_arithm<T>::value;

template <class T>
using to_u128 = typename std::conditional<std::is_same_v<T, __int128_t>, __uint128_t, unsigned __int128>;

template <class T>
using to_uint_t = typename std::conditional_t<std::is_same_v<T, i128>, to_u128<T>, typename std::conditional_t<std::is_signed_v<T>, std::make_unsigned<T>, std::common_type<T>>>::type;

}  // namespace tifa_libs

#endif