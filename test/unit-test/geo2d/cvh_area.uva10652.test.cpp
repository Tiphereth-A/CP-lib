#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo2d/cvh.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f64;
using Point2 = geo::point<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

CEXP data_t PI = pi_v<data_t>;

strn single_proceed(std::istream& fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(1);

  u32 n;
  fin >> n;
  vec<Point2> v;
  data_t x, y, w, h, phi;
  data_t ans = 0;
  flt_ (u32, i, 1, n + 1) {
    fin >> x >> y >> w >> h >> phi;
    phi = phi * PI / 180;
    if (phi < 0) phi += 2 * PI;
    phi = -phi;
    ans += w * h;
    Point2 c{x, y};
    v.emplace_back(c + Point2{w / 2, h / 2}.do_rot(phi));
    v.emplace_back(c + Point2{-w / 2, h / 2}.do_rot(phi));
    v.emplace_back(c + Point2{w / 2, -h / 2}.do_rot(phi));
    v.emplace_back(c + Point2{-w / 2, -h / 2}.do_rot(phi));
  }
  ss << ans * 100 / ConvexHull2{v}.init().area() << " %\n";

  return ss.str();
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("uva", "10652", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t;
  u32 testcase = 0;
  fin >> t;
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
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::ts_example_00: test("1"); break;
    case unittest::ts_example_01: test("2"); break;
    case unittest::ts_random_00: test("3"); break;
    case unittest::ts_random_01: test("4"); break;
    case unittest::ts_random_02: break;
    case unittest::ts_random_03: break;
    case unittest::ts_random_04: break;
    case unittest::ts_random_05: break;
    case unittest::ts_random_06: break;
    case unittest::ts_random_07: break;
    case unittest::ts_random_08: break;
    case unittest::ts_random_09: break;
    default: break;
  }

  unittest::post_test();
}