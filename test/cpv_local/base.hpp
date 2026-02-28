#ifndef TIFALIBS_UNITTEST_BASE
#define TIFALIBS_UNITTEST_BASE

#include "../../src/io/container/lib.hpp"
#include "../../src/io/i128/lib.hpp"
#include "../../src/io/pair/lib.hpp"
#include "../../src/io/tuple/lib.hpp"

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

}  // namespace detail__

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
  auto passed() CNE { return std::chrono::duration_cast<duration_t>(s_clock_end - s_clock_start); }
  operator strn() { return std::format("{} passed in line {}", passed(), s_line_num); }

 private:
  std::mutex s_clock_mutex;
  std::chrono::time_point<clock_t> s_clock_start, s_clock_end;
  int s_line_num;
};
inline timer default_timer;

#define timer_(...)                                   \
  ::tifa_libs::unittest::default_timer.tic(__LINE__); \
  __VA_ARGS__;                                        \
  ::tifa_libs::unittest::default_timer.tac();         \
  std::cerr << (strn)::tifa_libs::unittest::default_timer << '\n'

#define check(got, want, ...) ::tifa_libs::unittest::detail__::check_(__PRETTY_FUNCTION__, #got, got, #want, want __VA_OPT__(, ) __VA_ARGS__)
#define check_bool(expression, ...) ::tifa_libs::unittest::detail__::check_bool_(__PRETTY_FUNCTION__, #expression, expression __VA_OPT__(, ) __VA_ARGS__)
#define check_param(x) \
  std::pair<std::string, decltype(x)> { #x, x }

inline ptt<strn> get_fname_in_ans(strnv source_oj, strnv source_id, strnv data) NE {
  std::cerr << std::format("===== {} start =====\n", __PRETTY_FUNCTION__);
  strn path = std::format("test/cpv_local/_data/{}/{}/{}", source_oj, source_id, data);
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