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
  retif_((str.length() <= 1024), str, std::format("{}... (length = {})", str.substr(0, 1024), std::to_string(str.length())));
}

template <class T, class... Ts>
void check_(strnv pretty_func, strnv got_str, T CR got, strnv want_str, T CR want, Ts... param) {
  if CEXP (sizeof...(param) == 0) {
    if (got != want) throw std::runtime_error(std::format("{}: got \"{}\" = {}, want \"{}\" = {}", pretty_func, got_str, to_str(got), want_str, to_str(want)));
  } else {
    if (got != want) throw std::runtime_error(std::format("{}: got \"{}\" = {}, want \"{}\" = {} with", pretty_func, got_str, to_str(got), want_str, to_str(want)) + (std::format(" {} = {};", param.first, ::tifa_libs::unittest::detail__::to_str(param.second)) + ...));
  }
}

template <class... Ts>
void check_bool_(strnv pretty_func, strnv expression, bool res, Ts... param) {
  if CEXP (sizeof...(param) == 0) {
    if (!res) throw std::runtime_error(std::format("{} :\"{}\" failed", pretty_func, expression));
  } else {
    if (!res) throw std::runtime_error(std::format("{} :\"{}\" failed with", pretty_func, expression) + (std::format(" {} = {};", param.first, ::tifa_libs::unittest::detail__::to_str(param.second)) + ...));
  }
}

template <class clock_t = std::chrono::high_resolution_clock, class duration_t = std::chrono::microseconds>
requires specialized_from_v<duration_t, std::chrono::duration>
struct timer {
  void tic(int line_num) NE {
    s_line_num = line_num;
    const std::lock_guard<std::mutex> lock(s_clock_mutex);
    s_clock_start = clock_t::now();
  }
  void tac() NE {
    const std::lock_guard<std::mutex> lock(s_clock_mutex);
    s_clock_end = clock_t::now();
  }
  operator strn() { return std::format("{} passed in line {}", std::chrono::duration_cast<duration_t>(s_clock_end - s_clock_start), s_line_num); }

 private:
  std::mutex s_clock_mutex;
  std::chrono::time_point<clock_t> s_clock_start, s_clock_end;
  int s_line_num;
};
inline timer default_timer;

}  // namespace detail__

// clang-format off
enum class TC : u8 { example_00, example_01, random_00, random_01, random_02, random_03, random_04, random_05, random_06, random_07, random_08, random_09 };
// clang-format on

inline const std::map<pttu, TC> testcase_id{
    {{1234, 5678}, TC::example_00},
    {{1000000000, 1000000000}, TC::example_01},
    {{192279220, 156648746}, TC::random_00},
    {{264704197, 120999146}, TC::random_01},
    {{682152023, 451794314}, TC::random_02},
    {{627477696, 504915182}, TC::random_03},
    {{729561619, 415335212}, TC::random_04},
    {{173330281, 220603612}, TC::random_05},
    {{841413509, 58432763}, TC::random_06},
    {{251229786, 256388306}, TC::random_07},
    {{118232767, 222490630}, TC::random_08},
    {{907649120, 290651129}, TC::random_09},
    {{0, 1}, TC::example_00},
    {{0, 2}, TC::example_01},
    {{0, 3}, TC::random_00},
    {{0, 4}, TC::random_01},
    {{0, 5}, TC::random_02},
    {{0, 6}, TC::random_03},
    {{0, 7}, TC::random_04},
    {{0, 8}, TC::random_05},
    {{0, 9}, TC::random_06},
    {{0, 10}, TC::random_07},
    {{0, 11}, TC::random_08},
    {{0, 12}, TC::random_09}};

inline void post_test([[maybe_unused]] pttu CR p = {0, 0}) NE {
  static pttu p_{0, 0};
  if (p.first || p.second) {
    p_ = p;
    return;
  }
  std::cout << p_.first + p_.second << '\n';
  exit(0);
}

inline TC pre_test() NE {
  pttu p;
  std::cin >> p.first >> p.second;
  post_test(p);
  return testcase_id.at(p);
}

#define timer_(...)                                             \
  ::tifa_libs::unittest::detail__::default_timer.tic(__LINE__); \
  __VA_ARGS__;                                                  \
  ::tifa_libs::unittest::detail__::default_timer.tac();         \
  std::cerr << (strn)::tifa_libs::unittest::detail__::default_timer << '\n'

#define check(got, want, ...) ::tifa_libs::unittest::detail__::check_(__PRETTY_FUNCTION__, #got, got, #want, want __VA_OPT__(, ) __VA_ARGS__)
#define check_bool(expression, ...) ::tifa_libs::unittest::detail__::check_bool_(__PRETTY_FUNCTION__, #expression, expression __VA_OPT__(, ) __VA_ARGS__)
#define check_param(x) \
  std::pair<std::string, decltype(x)> { #x, x }

inline ptt<strn> get_fname_in_ans(strnv source_oj, strnv source_id, strnv data) NE {
  std::cerr << std::format("===== {} start =====\n", __PRETTY_FUNCTION__);
  strn path = std::format("data/{}/{}/{}", source_oj, source_id, data);
  strn fi = path + ".in", fo = path + ".out", fa = path + ".ans";
  std::filebuf fb;
  if (!fb.open(fi, std::ios::in)) {
    std::cerr << "error: failed opening " << fi << '\n';
    exit(1);
  }
  fb.close();
  if (fb.open(fo, std::ios::in)) fa = fo;
  else {
    std::cerr << std::format("warning: failed opening {}, trying {}\n", fo, fa);
    if (!fb.open(fa, std::ios::in)) {
      std::cerr << "error: failed opening " << fa << '\n';
      exit(1);
    }
  }
  fb.close();
  std::cerr << "fname_in: " << fi << '\n';
  std::cerr << "fname_ans: " << fa << '\n';
  std::cerr << std::format("===== {} end =====\n", __PRETTY_FUNCTION__);
  return {fi, fa};
}

}  // namespace tifa_libs::unittest

#endif