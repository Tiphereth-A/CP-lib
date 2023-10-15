#ifndef TIFA_LIBS_UTIL_TRAITS
#define TIFA_LIBS_UTIL_TRAITS

#include "util.hpp"

namespace tifa_libs {

template <typename T>
using remove_cvref_t = typename std::remove_cv_t<typename std::remove_reference_t<T>>;

template <class T>
using is_iterable = typename std::conditional_t<std::is_same_v<decltype(std::declval<remove_cvref_t<T>>().begin()), typename remove_cvref_t<T>::iterator> && std::is_same_v<decltype(std::declval<remove_cvref_t<T>>().end()), typename remove_cvref_t<T>::iterator>, std::true_type, std::false_type>;

template <class T>
using is_container = typename std::conditional_t<is_iterable<T>::value && !std::is_base_of_v<T, std::basic_string<typename T::value_type>>, std::true_type, std::false_type>;

template <class T>
using is_int = typename std::conditional_t<std::is_integral_v<T> || std::is_same_v<T, i128> || std::is_same_v<T, u128>, std::true_type, std::false_type>;

template <class T>
using is_sint = typename std::conditional_t<(is_int<T>::value && std::is_signed_v<T>) || std::is_same_v<T, i128>, std::true_type, std::false_type>;

template <class T>
using is_uint = typename std::conditional_t<(is_int<T>::value && std::is_unsigned_v<T>) || std::is_same_v<T, u128>, std::true_type, std::false_type>;

template <class T>
using to_uint = typename std::conditional_t<std::is_same_v<T, i128>, u128, typename std::conditional_t<std::is_signed_v<T>, std::make_unsigned<T>, std::common_type<T>>>;

}  // namespace tifa_libs

#endif