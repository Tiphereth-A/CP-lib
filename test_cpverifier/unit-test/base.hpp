#ifndef TIFALIBS_UNITTEST_BASE
#define TIFALIBS_UNITTEST_BASE

#include "../../include/io/ios128.hpp"
#include "../../include/io/ios_container.hpp"
#include "../../include/io/ios_pair.hpp"
#include "../../include/io/ios_tuple.hpp"
#include "../../include/rand/gen.hpp"

namespace tifa_libs::unittest {

namespace detail__ {

template <class T>
strn to_str(T CR x) NE {
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

enum TESTCASE { ts_example_00,
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

inline const std::map<pttu, TESTCASE> testcase_id{
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
    {{907649120, 290651129}, ts_random_09},
    {{0, 1}, ts_example_00},
    {{0, 2}, ts_example_01},
    {{0, 3}, ts_random_00},
    {{0, 4}, ts_random_01},
    {{0, 5}, ts_random_02},
    {{0, 6}, ts_random_03},
    {{0, 7}, ts_random_04},
    {{0, 8}, ts_random_05},
    {{0, 9}, ts_random_06},
    {{0, 10}, ts_random_07},
    {{0, 11}, ts_random_08},
    {{0, 12}, ts_random_09}};

inline void post_test([[maybe_unused]] pttu CR p = {0, 0}) NE {
  static pttu p_{0, 0};
  if (p.first || p.second) {
    p_ = p;
    return;
  }
  std::cout << p_.first + p_.second << '\n';
  exit(0);
}

inline TESTCASE pre_test() NE {
  pttu p;
  std::cin >> p.first >> p.second;
  post_test(p);
  return testcase_id.at(p);
}

#define check(got, want, ...) ::tifa_libs::unittest::detail__::check_(__PRETTY_FUNCTION__, #got, got, #want, want __VA_OPT__(, ) __VA_ARGS__)
#define check_bool(expression, ...) ::tifa_libs::unittest::detail__::check_bool_(__PRETTY_FUNCTION__, #expression, expression __VA_OPT__(, ) __VA_ARGS__)
#define check_param(x) \
  std::pair<std::string, decltype(x)> { #x, x }

inline ptt<strn> get_fname_in_ans(strn CR source_oj, strn CR source_id, strn CR data) NE {
  std::cerr << "===== " << __PRETTY_FUNCTION__ << " start =====\n";
  strn path = "data/" + source_oj + "/" + source_id + "/" + data;
  strn fi = path + ".in", fo = path + ".out", fa = path + ".ans";
  std::filebuf fb;
  if (!fb.open(fi, std::ios::in)) {
    std::cerr << "error: failed opening " << fi << '\n';
    exit(1);
  }
  fb.close();
  if (fb.open(fo, std::ios::in)) fa = fo;
  else {
    std::cerr << "warning: failed opening " << fo << ", trying " << fa << '\n';
    if (!fb.open(fa, std::ios::in)) {
      std::cerr << "error: failed opening " << fa << '\n';
      exit(1);
    }
  }
  fb.close();
  std::cerr << "fname_in: " << fi << '\n';
  std::cerr << "fname_ans: " << fa << '\n';
  std::cerr << "====== " << __PRETTY_FUNCTION__ << " end ======\n";
  return {fi, fa};
}

}  // namespace tifa_libs::unittest

#endif