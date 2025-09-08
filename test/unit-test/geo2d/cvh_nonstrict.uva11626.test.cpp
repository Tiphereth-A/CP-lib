#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo2d/cvh.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f64;
using Point2 = geo::point<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

ConvexHull2 single_proceed(std::istream& fin) {
  u32 n;
  fin >> n;
  vec<Point2> v;
  data_t x, y;
  char c;
  flt_ (u32, i, 1, n + 1) {
    fin >> x >> y >> c;
    v.emplace_back(x, y);
  }
  return ConvexHull2{v, false, false};
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("uva", "11626", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t;
  u32 testcase = 0;
  fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    auto got = single_proceed(fin);
    u32 n;
    fans >> n;
    ConvexHull2 want(n);
    fans >> want;
    check(got.vs, want.vs, check_param(testcase));
  }
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test("1"); break;
    case unittest::TC::example_01: test("2"); break;
    case unittest::TC::random_00: test("3"); break;
    case unittest::TC::random_01: break;
    case unittest::TC::random_02: break;
    case unittest::TC::random_03: break;
    case unittest::TC::random_04: break;
    case unittest::TC::random_05: break;
    case unittest::TC::random_06: break;
    case unittest::TC::random_07: break;
    case unittest::TC::random_08: break;
    case unittest::TC::random_09: break;
    default: break;
  }

  unittest::post_test();
}