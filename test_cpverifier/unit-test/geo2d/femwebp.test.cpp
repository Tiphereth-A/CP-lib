#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo2d/femwebp.hpp"

#include "../base.hpp"

using tifa_libs::geo::point;

template <class T>
void single_test(vec<point<T>> CR v) {
  check_bool(v.size() >= 3, check_param(v));

  point<T> fw = femwebp(v);

  point<T> sum;
  for (auto CR i : v)
    if (i != fw) sum += (i - fw).do_unit();
  check_bool(tifa_libs::is_lt(sum.norm(), (T)1), check_param(v), check_param(fw), check_param(sum));
}

template <tifa_libs::arithm_c T>
void test(T lim) {
  tifa_libs::rand::Gen<T> g(std::is_signed_v<T> ? -lim : 0, lim);

  vec<point<T>> v{point<T>(g(), g()), point<T>(g(), g()), point<T>(g(), g())};
  single_test(v);
  v.emplace_back(g(), g());
  single_test(v);
  while (v.size() < 10) v.emplace_back(g(), g());
  single_test(v);
  while (v.size() < 50) v.emplace_back(g(), g());
  single_test(v);
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test<f64>(1e5); break;
    case tifa_libs::unittest::ts_example_01: test<f128>(1e5); break;
    case tifa_libs::unittest::ts_random_00: test<f64>(1e9); break;
    case tifa_libs::unittest::ts_random_01: test<f128>(1e9); break;
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