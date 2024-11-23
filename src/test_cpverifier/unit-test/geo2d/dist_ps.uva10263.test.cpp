#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo2d/dist_ps.hpp"

#include "../base.hpp"

using data_t = f64;
using Point2 = tifa_libs::geo::point<data_t>;
using Line2 = tifa_libs::geo::line<data_t>;

strn single_proceed(data_t x, data_t y, std::istream& fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(4);

  Point2 m{x, y};
  u32 n;
  fin >> n;
  vec<Line2> l;
  l.reserve(n + 1);
  Point2 prev, now;
  fin >> prev;
  flt_ (u32, i, 1, n + 1) {
    fin >> now;
    l.emplace_back(prev, now);
    prev = now;
  }
  if (!n) {
    ss << prev.x << '\n'
       << prev.y << '\n';
    return ss.str();
  }
  data_t ans = std::numeric_limits<data_t>::max();
  Point2 ansP;
  for (auto CR i : l) {
    auto pp = tifa_libs::geo::dist_PS_P(m, i);
    data_t d = tifa_libs::geo::dist_PP(pp, m);
    if (tifa_libs::is_lt(d, ans)) {
      ans = d;
      ansP = pp;
    }
  }
  ss << ansP.x << '\n'
     << ansP.y << '\n';

  return ss.str();
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = tifa_libs::unittest::get_fname_in_ans("uva", "10263", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  data_t x, y;
  u32 testcase = 0;
  while (fin >> x >> y) {
    ++testcase;
    strn got = single_proceed(x, y, fin);
    strn want, want2;
    std::getline(fans, want);
    std::getline(fans, want2);
    while (isspace(got.back())) got.pop_back();
    while (isspace(want.back())) want.pop_back();
    while (isspace(want2.back())) want2.pop_back();
    want += '\n' + want2;
    check(got, want, check_param(testcase));
  }
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test("1"); break;
    case tifa_libs::unittest::ts_example_01: test("2"); break;
    case tifa_libs::unittest::ts_random_00: test("3"); break;
    case tifa_libs::unittest::ts_random_01: break;
    case tifa_libs::unittest::ts_random_02: break;
    case tifa_libs::unittest::ts_random_03: break;
    case tifa_libs::unittest::ts_random_04: break;
    case tifa_libs::unittest::ts_random_05: break;
    case tifa_libs::unittest::ts_random_06: break;
    case tifa_libs::unittest::ts_random_07: break;
    case tifa_libs::unittest::ts_random_08: break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}