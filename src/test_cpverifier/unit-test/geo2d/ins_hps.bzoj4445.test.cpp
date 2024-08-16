#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo2d/ins_hps.hpp"

#include "../base.hpp"

using data_t = f128;
using Point2 = tifa_libs::geo::point<data_t>;
using Line2 = tifa_libs::geo::line<data_t>;
using Polygon2 = tifa_libs::geo::polygon<data_t>;
using ConvexHull2 = tifa_libs::geo::cvh<data_t>;

strn single_proceed(std::istream &fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(4);

  set_eps<data_t>(1e-18);
  u32 n;
  fin >> n;
  vec<Point2> vp(n);
  fin >> vp;
  vec<Line2> vl;
  vl.reserve(n * 2);
  vl.emplace_back(vp[0], vp[1]);
  fle_ (u32, i, 1, n - 1, nexti) {
    nexti = (i + 1) % n;
    data_t a = vp[1].y - vp[0].y - vp[nexti].y + vp[i].y;
    data_t b = vp[0].x - vp[1].x - vp[i].x + vp[nexti].x;
    data_t c = vp[1].x * vp[0].y - vp[0].x * vp[1].y + vp[i].x * vp[nexti].y - vp[nexti].x * vp[i].y;
    vl.emplace_back(vp[i], vp[nexti]);
    if (!tifa_libs::is_zero(a)) vl.emplace_back(-c / a, 0, b - c / a, -a);
    else if (!tifa_libs::is_zero(b)) vl.emplace_back(0, -c / b, b, -a - c / b);
  }
  ss << tifa_libs::geo::ins_hPs(vl).area() / Polygon2{vp}.area();

  return ss.str();
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = tifa_libs::unittest::get_fname_in_ans("bzoj", "4445", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t = 1;
  u32 testcase = 0;
  // fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    strn got = single_proceed(fin);
    strn want;
    std::getline(fans, want);
    while (isspace(got.back())) got.pop_back();
    while (isspace(want.back())) want.pop_back();
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