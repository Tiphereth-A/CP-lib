#ifndef TIFALIBS_UNITTEST_BASE
#define TIFALIBS_UNITTEST_BASE

#include "../../code/io/ios128.hpp"
#include "../../code/io/ios_container.hpp"
#include "../../code/io/ios_pair.hpp"
#include "../../code/io/ios_tuple.hpp"
#include "../../code/rand/gen.hpp"
#include "../../code/util/util.hpp"

namespace tifa_libs::unittest {

namespace detail__ {

template <class T>
strn to_str(T CR x) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(12) << x;
  auto str = ss.str();
  return str.length() <= 1024 ? str : str.substr(0, 1024) + "... (length = " + std::to_string(str.length()) + ")";
}

template <class T, class... Ts>
void check_(strn CR pretty_func, strn CR got_str, T CR got, strn CR want_str, T CR want, Ts... param) {
  if CEXP (sizeof...(param) == 0) {
    if (got != want) throw std::runtime_error(pretty_func + ": got \"" + got_str + "\" = " + to_str(got) + ", want \"" + want_str + "\" = " + to_str(want));
  } else {
    if (got != want) throw std::runtime_error(pretty_func + ": got \"" + got_str + "\" = " + to_str(got) + ", want \"" + want_str + "\" = " + to_str(want) + " with" + ((" " + param.first + " = " + ::tifa_libs::unittest::detail__::to_str(param.second) + " ;") + ...));
  }
}

template <class... Ts>
void check_bool_(strn CR pretty_func, strn CR expression, bool res, Ts... param) {
  if CEXP (sizeof...(param) == 0) {
    if (!res) throw std::runtime_error(pretty_func + " :\"" + expression + "\" failed");
  } else {
    if (!res) throw std::runtime_error(pretty_func + " :\"" + expression + "\" failed with" + ((" " + param.first + " = " + ::tifa_libs::unittest::detail__::to_str(param.second) + " ;") + ...));
  }
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

inline void post_test([[maybe_unused]] ptt<u32> CR p = {0, 0}) {
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

#define check(got, want, ...) ::tifa_libs::unittest::detail__::check_(__PRETTY_FUNCTION__, #got, got, #want, want __VA_OPT__(, ) __VA_ARGS__)
#define check_bool(expression, ...) ::tifa_libs::unittest::detail__::check_bool_(__PRETTY_FUNCTION__, #expression, expression __VA_OPT__(, ) __VA_ARGS__)
#define check_param(x) \
  std::pair<std::string, decltype(x)> { #x " = ", x }

}  // namespace tifa_libs::unittest

#endif