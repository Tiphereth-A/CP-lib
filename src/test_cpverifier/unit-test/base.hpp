#ifndef TIFA_LIBS_UNITTEST_BASE
#define TIFA_LIBS_UNITTEST_BASE

#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../code/util/util.hpp"

namespace tifa_libs::unittest {

namespace detail__ {

template <class T>
inline std::string to_str(T const& x) {
  static std::stringstream ss;
  ss.clear();
  ss << x;
  std::string s;
  std::getline(ss, s);
  return s;
}

template <class T, class... Ts>
inline void check_(const char pretty_func[], T const& got, T const& want, Ts... param) {
  if (got != want) throw std::runtime_error(pretty_func + ((param + std::string(", ")) + ...) + "got " + to_str(got) + ", want " + to_str(want));
}

}  // namespace detail__

inline void post_test() {
  u32 a, b;
  std::cin >> a >> b;
  std::cout << a + b << '\n';
}

#define CHECK_(got, want, ...) ::tifa_libs::unittest::detail__::check_(__PRETTY_FUNCTION__, got, want, __VA_ARGS__)
#define check(...) CHECK_(__VA_ARGS__)
#define check_param(x) #x " = " + ::tifa_libs::unittest::detail__::to_str(x)

}  // namespace tifa_libs::unittest

#endif