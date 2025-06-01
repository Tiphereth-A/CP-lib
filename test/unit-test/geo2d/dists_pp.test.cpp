#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo2d/dist_pp.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using geo::dist_PP;
using geo::point;

template <class T, int p>
void test_norm_subadditivity(point<T> CR x, point<T> CR y) {
  point<T> O(0, 0), xy = x + y;

  T dx = dist_PP<T, p>(x, O), dy = dist_PP<T, 1>(y, O), dxy = dist_PP<T, p>(xy, O);
  check_bool(!is_gt(dxy, dx + dy), check_param(x), check_param(y), check_param(xy), check_param(dx), check_param(dy), check_param(dxy));
}

template <class T, int p>
void test_norm_absolute_homogeneity(point<T> CR x, T s) {
  point<T> O(0, 0), sx = s * x;

  T dx = dist_PP<T, p>(x, O), dsx = dist_PP<T, p>(sx, O);
  check_bool(is_eq(dsx, std::abs(s) * dx), check_param(x), check_param(s), check_param(sx), check_param(dx), check_param(std::abs(s) * dx), check_param(dsx));
}

template <class T, int p>
void test_norm_non_negativity(point<T> CR x) {
  point<T> O(0, 0);

  T dx = dist_PP<T, p>(x, O);
  check_bool(is_pos(dx), check_param(x), check_param(dx));
  T dO = dist_PP<T, p>(O, O);
  check_bool(is_zero(dO), check_param(dO));
}

template <class T>
void test_norm_equivalence(point<T> CR x) {
  point<T> O(0, 0);

  if CEXP (!std::is_integral_v<T>) {
    T d1x = dist_PP<T, 1>(x, O), d2x = dist_PP(x, O), dinfx = dist_PP<T, 0>(x, O);

    check_bool(!is_lt(d1x, d2x) && !is_lt(d2x, d1x / 2), check_param(x), check_param(d1x), check_param(d2x), check_param(d1x / 2));
    check_bool(!is_lt(d2x, dinfx) && !is_lt(dinfx, d2x / 2), check_param(x), check_param(d2x), check_param(dinfx), check_param(d2x / 2));
    check_bool(!is_lt(dinfx * 2, d1x) && !is_lt(d1x, dinfx), check_param(x), check_param(dinfx * 2), check_param(d1x), check_param(dinfx));
  } else {
    T d1x = dist_PP<T, 1>(x, O), dinfx = dist_PP<T, 0>(x, O);

    check_bool(!is_lt(dinfx * 2, d1x) && !is_lt(d1x, dinfx), check_param(x), check_param(dinfx * 2), check_param(d1x), check_param(dinfx));
  }
}

template <class T, int p>
void test_distance_translation_invariant(point<T> CR x, point<T> CR y, point<T> CR a) {
  point<T> xa = x + a, ya = y + a;

  T dxy = dist_PP<T, p>(x, y), dxaya = dist_PP<T, p>(xa, ya);
  check_bool(is_eq(dxy, dxaya), check_param(x), check_param(y), check_param(a), check_param(xa), check_param(ya), check_param(dxy), check_param(dxaya));
}

template <class T, int p>
void test_distance_absolute_homogeneity(point<T> CR x, point<T> CR y, T s) {
  point<T> sx = s * x, sy = s * y;

  T dxy = dist_PP<T, p>(x, y), dsxsy = dist_PP<T, p>(sx, sy);
  check_bool(is_eq(dsxsy, std::abs(s) * dxy), check_param(x), check_param(y), check_param(s), check_param(sx), check_param(sy), check_param(dxy), check_param(dsxsy));
}

template <class T, int p>
void single_test(point<T> CR x, point<T> CR y, point<T> CR a, T s) {
  // norm properties
  test_norm_subadditivity<T, p>(x, y);
  test_norm_subadditivity<T, p>(y, x);
  test_norm_absolute_homogeneity<T, p>(x, s);
  test_norm_absolute_homogeneity<T, p>(y, s);
  test_norm_non_negativity<T, p>(x);
  test_norm_non_negativity<T, p>(y);

  // distance properties
  test_distance_translation_invariant<T, p>(x, y, a);
  test_distance_translation_invariant<T, p>(y, x, a);
  test_distance_absolute_homogeneity<T, p>(x, y, s);
  test_distance_absolute_homogeneity<T, p>(y, x, s);
}

template <arithm_c T>
void test(T lim) {
  rand::Gen<T> g(std::is_signed_v<T> ? -lim : 0, lim);
  test_norm_equivalence(point{g(), g()});
  single_test<T, 0>(point{g(), g()}, point{g(), g()}, point{g(), g()}, g());
  single_test<T, 1>(point{g(), g()}, point{g(), g()}, point{g(), g()}, g());
  if CEXP (std::floating_point<T>) {
    single_test<T, 2>(point{g(), g()}, point{g(), g()}, point{g(), g()}, g());
    single_test<T, 3>(point{g(), g()}, point{g(), g()}, point{g(), g()}, g());
    single_test<T, 4>(point{g(), g()}, point{g(), g()}, point{g(), g()}, g());
    single_test<T, 5>(point{g(), g()}, point{g(), g()}, point{g(), g()}, g());
    single_test<T, 6>(point{g(), g()}, point{g(), g()}, point{g(), g()}, g());
    single_test<T, 7>(point{g(), g()}, point{g(), g()}, point{g(), g()}, g());
    single_test<T, 8>(point{g(), g()}, point{g(), g()}, point{g(), g()}, g());
    single_test<T, 9>(point{g(), g()}, point{g(), g()}, point{g(), g()}, g());
    single_test<T, 10>(point{g(), g()}, point{g(), g()}, point{g(), g()}, g());
    single_test<T, 11>(point{g(), g()}, point{g(), g()}, point{g(), g()}, g());
    single_test<T, 12>(point{g(), g()}, point{g(), g()}, point{g(), g()}, g());
    single_test<T, 13>(point{g(), g()}, point{g(), g()}, point{g(), g()}, g());
    single_test<T, 14>(point{g(), g()}, point{g(), g()}, point{g(), g()}, g());
    single_test<T, 15>(point{g(), g()}, point{g(), g()}, point{g(), g()}, g());
  }
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::ts_example_00: test<i32>(1e4); break;
    case unittest::ts_example_01: test<i64>(1e4); break;
    case unittest::ts_random_00: test<f64>(1e4); break;
    case unittest::ts_random_01: test<f128>(1e4); break;
    case unittest::ts_random_02: test<i64>(1e5); break;
    case unittest::ts_random_03: test<f64>(1e5); break;
    case unittest::ts_random_04: test<f128>(1e5); break;
    case unittest::ts_random_05: test<i64>(1e9); break;
    case unittest::ts_random_06: test<f64>(1e9); break;
    case unittest::ts_random_07: test<f64>(1e9); break;
    case unittest::ts_random_08: test<f128>(1e9); break;
    case unittest::ts_random_09: break;
    default: break;
  }

  unittest::post_test();
}