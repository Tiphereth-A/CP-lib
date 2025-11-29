#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo2d/cvh.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f64;
using Point2 = geo::point<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

strn single_proceed(u32 l, std::istream& fin) {
  std::stringstream ss;

  vec<Point2> vpl(l);
  fin >> vpl;
  u32 s;
  fin >> s;
  vec<Point2> vps(s);
  fin >> vps;
  ConvexHull2 poly{vpl};
  ss << std::ranges::count_if(vps, [&poly](Point2 CR p) -> bool { return poly.contains(p); }) << '\n';

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("uva", "13024", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 l;
  u32 testcase = 0;
  while (fin >> l) {
    ++testcase;
    strn got = single_proceed(l, fin);
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
    case unittest::TC::example_00: test("1"); break;
    case unittest::TC::example_01: test("2"); break;
    case unittest::TC::random_00: break;
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