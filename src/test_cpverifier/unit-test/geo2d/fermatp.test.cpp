#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo2d/poly_fermatp.hpp"
#include "../../../code/rand/gen.hpp"
#include "../base.hpp"

using tifa_libs::geo::point, tifa_libs::geo::polygon;

template <class T>
void single_test(vec<point<T>> const& v) {
  check_bool(v.size() >= 3, check_param(v));

  polygon<T> poly(v);
  point<T> fp_poly = fermatp(poly);

  point<T> sum(0, 0);
  for (auto const& i : v) sum += (i - fp_poly).do_unit();
  check_bool(tifa_libs::is_lt(sum.norm2(), (T)1), check_param(v), check_param(fp_poly), check_param(sum));
}

template <class T, std::enable_if_t<std::is_arithmetic_v<T>>* = nullptr>
void test(T lim) {
  tifa_libs::rand::Gen<std::conditional_t<std::is_integral_v<T>, std::uniform_int_distribution<T>, std::uniform_real_distribution<T>>> g(std::is_signed_v<T> ? -lim : 0, lim);

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
  tifa_libs::unittest::pre_test();

  test<f64>(1e5);
  test<f128>(1e5);

  test<f64>(1e9);
  test<f128>(1e9);

  tifa_libs::unittest::post_test();
}