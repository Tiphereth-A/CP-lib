#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo2d/femwebp.hpp"

#include "../base.hpp"

using namespace tifa_libs;
using geo::point;

template <class T>
void single_test(vec<point<T>> CR v) {
  check_bool(v.size() >= 3, check_param(v));

  point<T> fw = femwebp(v);

  point<T> sum;
  for (auto CR i : v)
    if (i != fw) sum += (i - fw).do_unit();
  check_bool(is_lt(sum.norm(), (T)1), check_param(v), check_param(fw), check_param(sum));
}

template <arithm_c T>
void test(T lim, u32 n) {
  rand::gen<T> g(std::is_signed_v<T> ? -lim : 0, lim);

  vec<point<T>> v;
  while (v.size() < n) v.emplace_back(g(), g());
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test<f64>(1e5, 3); break;
    case unittest::TC::example_01: test<f128>(1e5, 3); break;
    case unittest::TC::random_00: test<f64>(1e9, 3); break;
    case unittest::TC::random_01: test<f128>(1e9, 3); break;
    case unittest::TC::random_02: test<f64>(1e5, 10); break;
    case unittest::TC::random_03: test<f128>(1e5, 10); break;
    case unittest::TC::random_04: test<f64>(1e9, 10); break;
    case unittest::TC::random_05: test<f128>(1e9, 10); break;
    case unittest::TC::random_06: test<f64>(1e5, 50); break;
    case unittest::TC::random_07: test<f128>(1e5, 50); break;
    case unittest::TC::random_08: test<f64>(1e9, 50); break;
    case unittest::TC::random_09: test<f128>(1e9, 50); break;
    default: break;
  }

  unittest::post_test();
}