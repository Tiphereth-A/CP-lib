#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo2d/cvh.hpp"

#include "../base.hpp"

using data_t = f64;
using Point2 = tifa_libs::geo::point<data_t>;
using Line2 = tifa_libs::geo::line<data_t>;
using ConvexHull2 = tifa_libs::geo::cvh<data_t>;

constexpr data_t PI = std::numbers::pi_v<data_t>;

strn single_proceed(std::istream &fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(2);

  set_eps<data_t>(1e-9);
  u32 n;
  fin >> n;
  data_t a, b, r;
  fin >> b >> a >> r;
  Point2 d[4]{Point2{a / 2 - r, b / 2 - r}, Point2{-a / 2 + r, b / 2 - r}, Point2{a / 2 - r, -b / 2 + r}, Point2{-a / 2 + r, -b / 2 + r}};
  vec<Point2> vp;
  vp.reserve(n);
  data_t x, y, theta;
  for (u32 i = 1; i <= n; ++i) {
    fin >> x >> y >> theta;
    Point2 c{x, y};
    for (const auto &j : d) vp.push_back(c + rot(j, theta));
  }
  ss << ConvexHull2(vp).circum() + r * PI * 2;

  return ss.str();
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = tifa_libs::unittest::get_fname_in_ans("bzoj", "2829", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t = 1;
  u32 testcase = 0;
  // fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    strn got = single_proceed(fin);
    while (isspace(got.back())) got.pop_back();
    strn want;
    flt_ (u32, i, 0, 1) {
      strn _;
      std::getline(fans, _);
      while (isspace(_.back())) _.pop_back();
      if (i) want += ' ';
      want += _;
    }
    check(got, want, check_param(testcase));
  }
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test("1"); break;
    case tifa_libs::unittest::ts_example_01: test("2"); break;
    case tifa_libs::unittest::ts_random_00: test("3"); break;
    case tifa_libs::unittest::ts_random_01: test("4"); break;
    case tifa_libs::unittest::ts_random_02: test("5"); break;
    case tifa_libs::unittest::ts_random_03: test("6"); break;
    case tifa_libs::unittest::ts_random_04: test("7"); break;
    case tifa_libs::unittest::ts_random_05: test("8"); break;
    case tifa_libs::unittest::ts_random_06: test("9"); break;
    case tifa_libs::unittest::ts_random_07: test("10"); break;
    case tifa_libs::unittest::ts_random_08: break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}