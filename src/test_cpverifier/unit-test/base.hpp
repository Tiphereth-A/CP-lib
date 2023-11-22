#ifndef TIFA_LIBS_UNITTEST_BASE
#define TIFA_LIBS_UNITTEST_BASE

#include "../../code/util/ios_container.hpp"
#include "../../code/util/ios_pair.hpp"
#include "../../code/util/ios_tuple.hpp"
#include "../../code/util/util.hpp"

namespace tifa_libs::unittest {

namespace detail__ {

template <class T>
std::string to_str(T const &x) {
  static std::stringstream ss;
  ss.clear();
  ss << x;
  std::string s;
  std::getline(ss, s);
  return s;
}

template <class T, class... Ts>
void check_(std::string const &pretty_func, T const &got, T const &want, Ts... param) {
  if constexpr (sizeof...(param) == 0) {
    if (got != want) throw std::runtime_error(pretty_func + ": " + "| got " + to_str(got) + ", want " + to_str(want));
  } else if constexpr (sizeof...(param) == 1) {
    if (got != want) throw std::runtime_error(pretty_func + ": " + (param + ...) + std::string(", ") + "| got " + to_str(got) + ", want " + to_str(want));
  } else if (got != want) throw std::runtime_error(pretty_func + ": " + ((param + std::string(", ")) + ...) + "| got " + to_str(got) + ", want " + to_str(want));
}

template <class... Ts>
void check_bool_(std::string const &pretty_func, std::string const &expression, bool res, Ts... param) {
  if constexpr (sizeof...(param) == 0) {
    if (!res) throw std::runtime_error(pretty_func + ": " + expression + " failed");
  } else if constexpr (sizeof...(param) == 1) {
    if (!res) throw std::runtime_error(pretty_func + ": " + (param + ...) + std::string(", ") + "| " + expression + " failed");
  } else if (!res) throw std::runtime_error(pretty_func + ": " + ((param + std::string(", ")) + ...) + "| " + expression + " failed");
}
}  // namespace detail__

template <bool always_test = false>
void post_test([[maybe_unused]] u32 a = 1000000000, [[maybe_unused]] u32 b = 1000000000) {
#ifndef LOCAL_
  std::cout << a + b << '\n';
  if constexpr (!always_test)
    if (a != 1000000000 || b != 1000000000) exit(0);
#endif
}

template <bool always_test = false>
void pre_test() {
#ifndef LOCAL_
  u32 a, b;
  std::cin >> a >> b;
  if (a != 1000000000 || b != 1000000000) post_test<always_test>(a, b);
#endif
}

#pragma GCC diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#define check(got, want, check_params...) ::tifa_libs::unittest::detail__::check_(__PRETTY_FUNCTION__, got, want, ##check_params)
#define check_bool(expression, check_params...) ::tifa_libs::unittest::detail__::check_bool_(__PRETTY_FUNCTION__, #expression, expression, ##check_params)
#define check_param(x) #x " = " + ::tifa_libs::unittest::detail__::to_str(x)

}  // namespace tifa_libs::unittest

#endif