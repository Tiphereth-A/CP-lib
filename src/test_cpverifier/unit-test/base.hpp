#ifndef TIFALIBS_UNITTEST_BASE
#define TIFALIBS_UNITTEST_BASE

#include "../../code/rand/gen.hpp"
#include "../../code/util/ios128.hpp"
#include "../../code/util/ios_container.hpp"
#include "../../code/util/ios_pair.hpp"
#include "../../code/util/ios_tuple.hpp"
#include "../../code/util/util.hpp"

namespace tifa_libs::unittest {

namespace detail__ {

template <class T>
strn to_str(T const &x) {
  static std::stringstream ss;
  ss.clear();
  ss << std::fixed << std::setprecision(12) << x;
  strn s;
  std::getline(ss, s);
  return s;
}

template <class T, class... Ts>
void check_(strn const &pretty_func, T const &got, T const &want, Ts... param) {
  if constexpr (sizeof...(param) == 0) {
    if (got != want) throw std::runtime_error(pretty_func + ": " + "| got " + to_str(got) + ", want " + to_str(want));
  } else if constexpr (sizeof...(param) == 1) {
    if (got != want) throw std::runtime_error(pretty_func + ": " + (param + ...) + strn(", ") + "| got " + to_str(got) + ", want " + to_str(want));
  } else if (got != want) throw std::runtime_error(pretty_func + ": " + ((param + strn(", ")) + ...) + "| got " + to_str(got) + ", want " + to_str(want));
}

template <class... Ts>
void check_bool_(strn const &pretty_func, strn const &expression, bool res, Ts... param) {
  if constexpr (sizeof...(param) == 0) {
    if (!res) throw std::runtime_error(pretty_func + ": " + expression + " failed");
  } else if constexpr (sizeof...(param) == 1) {
    if (!res) throw std::runtime_error(pretty_func + ": " + (param + ...) + strn(", ") + "| " + expression + " failed");
  } else if (!res) throw std::runtime_error(pretty_func + ": " + ((param + strn(", ")) + ...) + "| " + expression + " failed");
}
}  // namespace detail__

enum TESTCASE { ts_local,
                ts_example_00,
                ts_example_01,
                ts_random_00,
                ts_random_01,
                ts_random_02,
                ts_random_03,
                ts_random_04,
                ts_random_05,
                ts_random_06,
                ts_random_07,
                ts_random_08,
                ts_random_09 };

inline const std::map<ptt<u32>, TESTCASE> testcase_id{
    {{1234, 5678}, ts_example_00},
    {{1000000000, 1000000000}, ts_example_01},
    {{192279220, 156648746}, ts_random_00},
    {{264704197, 120999146}, ts_random_01},
    {{682152023, 451794314}, ts_random_02},
    {{627477696, 504915182}, ts_random_03},
    {{729561619, 415335212}, ts_random_04},
    {{173330281, 220603612}, ts_random_05},
    {{841413509, 58432763}, ts_random_06},
    {{251229786, 256388306}, ts_random_07},
    {{118232767, 222490630}, ts_random_08},
    {{907649120, 290651129}, ts_random_09}};

inline void post_test([[maybe_unused]] ptt<u32> const &p = {0, 0}) {
#ifndef LOCAL_
  static ptt<u32> p_{0, 0};
  if (p.first || p.second) {
    p_ = p;
    return;
  }
  std::cout << p_.first + p_.second << '\n';
  exit(0);
#endif
}

inline TESTCASE pre_test() {
#ifndef LOCAL_
  ptt<u32> p;
  std::cin >> p.first >> p.second;
  post_test(p);
  return testcase_id.at(p);
#else
  return ts_local;
#endif
}

#pragma GCC diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#define check(got, want, check_params...) ::tifa_libs::unittest::detail__::check_(__PRETTY_FUNCTION__, got, want, ##check_params)
#define check_bool(expression, check_params...) ::tifa_libs::unittest::detail__::check_bool_(__PRETTY_FUNCTION__, #expression, expression, ##check_params)
#define check_param(x) #x " = " + ::tifa_libs::unittest::detail__::to_str(x)

}  // namespace tifa_libs::unittest

#endif