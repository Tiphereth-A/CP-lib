#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo2d/dist_pp.hpp"
#include "../../../code/geo2d/dist_pp_ch.hpp"
#include "../../../code/geo2d/dist_pp_ma.hpp"
#include "../../../code/rand/gen.hpp"
#include "../base.hpp"

using tifa_libs::is_gt, tifa_libs::is_eq, tifa_libs::is_lt;
using tifa_libs::is_pos, tifa_libs::is_zero;
using tifa_libs::geo::dist_PP_Ma, tifa_libs::geo::dist_PP, tifa_libs::geo::dist_PP_Ch;
using tifa_libs::geo::point;

template <class T>
void test_norm_subadditivity(point<T> const& x, point<T> const& y) {
  point<T> O(0, 0), xy = x + y;

  T d1x = dist_PP_Ma(x, O), d1y = dist_PP_Ma(y, O), d1xy = dist_PP_Ma(xy, O);
  check_bool(!is_gt(d1xy, d1x + d1y), check_param(x), check_param(y), check_param(xy), check_param(d1x), check_param(d1y), check_param(d1xy));

  if constexpr (!std::is_integral_v<T>) {
    T d2x = dist_PP(x, O), d2y = dist_PP(y, O), d2xy = dist_PP(xy, O);
    check_bool(!is_gt(d2xy, d2x + d2y), check_param(x), check_param(y), check_param(xy), check_param(d2x), check_param(d2y), check_param(d2xy));
  }

  T dinfx = dist_PP_Ch(x, O), dinfy = dist_PP_Ch(y, O), dinfxy = dist_PP_Ch(xy, O);
  check_bool(!is_gt(dinfxy, dinfx + dinfy), check_param(x), check_param(y), check_param(xy), check_param(dinfx), check_param(dinfy), check_param(dinfxy));
}

template <class T>
void test_norm_absolute_homogeneity(point<T> const& x, T s) {
  point<T> O(0, 0), sx = s * x;

  T d1x = dist_PP_Ma(x, O), d1sx = dist_PP_Ma(sx, O);
  check_bool(is_eq(d1sx, std::abs(s) * d1x), check_param(x), check_param(s), check_param(sx), check_param(d1x), check_param(d1sx));

  if constexpr (!std::is_integral_v<T>) {
    T d2x = dist_PP(x, O), d2sx = dist_PP(sx, O);
    check_bool(is_eq(d2sx, std::abs(s) * d2x), check_param(x), check_param(s), check_param(sx), check_param(d2x), check_param(d2sx));
  }

  T dinfx = dist_PP_Ch(x, O), dinfsx = dist_PP_Ch(sx, O);
  check_bool(is_eq(dinfsx, std::abs(s) * dinfx), check_param(x), check_param(s), check_param(sx), check_param(dinfx), check_param(dinfsx));
}

template <class T>
void test_norm_non_negativity(point<T> const& x) {
  point<T> O(0, 0);

  T d1x = dist_PP_Ma(x, O);
  check_bool(is_pos(d1x), check_param(x), check_param(d1x));
  T d1O = dist_PP_Ma(O, O);
  check_bool(is_zero(d1O), check_param(d1O));

  if constexpr (!std::is_integral_v<T>) {
    T d2x = dist_PP(x, O);
    check_bool(is_pos(d2x), check_param(x), check_param(d2x));
    T d2O = dist_PP(O, O);
    check_bool(is_zero(d2O), check_param(d2O));
  }

  T dinfx = dist_PP_Ch(x, O);
  check_bool(is_pos(dinfx), check_param(x), check_param(dinfx));
  T dinfO = dist_PP_Ch(O, O);
  check_bool(is_zero(dinfO), check_param(dinfO));
}

template <class T>
void test_norm_equivalence(point<T> const& x) {
  point<T> O(0, 0);

  if constexpr (!std::is_integral_v<T>) {
    T d1x = dist_PP_Ma(x, O), d2x = dist_PP(x, O), dinfx = dist_PP_Ch(x, O);

    check_bool(!is_lt(d1x, d2x) && !is_lt(d2x, d1x / 2), check_param(x), check_param(d1x), check_param(d2x), check_param(d1x / 2));
    check_bool(!is_lt(d2x, dinfx) && !is_lt(dinfx, d2x / 2), check_param(x), check_param(d2x), check_param(dinfx), check_param(d2x / 2));
    check_bool(!is_lt(dinfx * 2, d1x) && !is_lt(d1x, dinfx), check_param(x), check_param(dinfx * 2), check_param(d1x), check_param(dinfx));
  } else {
    T d1x = dist_PP_Ma(x, O), dinfx = dist_PP_Ch(x, O);

    check_bool(!is_lt(dinfx * 2, d1x) && !is_lt(d1x, dinfx), check_param(x), check_param(dinfx * 2), check_param(d1x), check_param(dinfx));
  }
}

template <class T>
void test_distance_translation_invariant(point<T> const& x, point<T> const& y, point<T> const& a) {
  point<T> xa = x + a, ya = y + a;

  T d1xy = dist_PP_Ma(x, y), d1xaya = dist_PP_Ma(xa, ya);
  check_bool(is_eq(d1xy, d1xaya), check_param(x), check_param(y), check_param(a), check_param(xa), check_param(ya), check_param(d1xy), check_param(d1xaya));

  if constexpr (!std::is_integral_v<T>) {
    T d2xy = dist_PP(x, y), d2xaya = dist_PP(xa, ya);
    check_bool(is_eq(d2xy, d2xaya), check_param(x), check_param(y), check_param(a), check_param(xa), check_param(ya), check_param(d2xy), check_param(d2xaya));
  }

  T dinfxy = dist_PP_Ch(x, y), dinfxaya = dist_PP_Ch(xa, ya);
  check_bool(is_eq(dinfxy, dinfxaya), check_param(x), check_param(y), check_param(a), check_param(xa), check_param(ya), check_param(dinfxy), check_param(dinfxaya));
}

template <class T>
void test_distance_absolute_homogeneity(point<T> const& x, point<T> const& y, T s) {
  point<T> sx = s * x, sy = s * y;

  T d1xy = dist_PP_Ma(x, y), d1sxsy = dist_PP_Ma(sx, sy);
  check_bool(is_eq(d1sxsy, std::abs(s) * d1xy), check_param(x), check_param(y), check_param(s), check_param(sx), check_param(sy), check_param(d1xy), check_param(d1sxsy));

  if constexpr (!std::is_integral_v<T>) {
    T d2xy = dist_PP(x, y), d2sxsy = dist_PP(sx, sy);
    check_bool(is_eq(d2sxsy, std::abs(s) * d2xy), check_param(x), check_param(y), check_param(s), check_param(sx), check_param(sy), check_param(d2xy), check_param(d2sxsy));
  }

  T dinfxy = dist_PP_Ch(x, y), dinfsxsy = dist_PP_Ch(sx, sy);
  check_bool(is_eq(dinfsxsy, std::abs(s) * dinfxy), check_param(x), check_param(y), check_param(s), check_param(sx), check_param(sy), check_param(dinfxy), check_param(dinfsxsy));
}

template <class T>
void single_test(point<T> const& x, point<T> const& y, point<T> const& a, T s) {
  // norm properties
  test_norm_subadditivity(x, y);
  test_norm_subadditivity(y, x);
  test_norm_absolute_homogeneity(x, s);
  test_norm_absolute_homogeneity(y, s);
  test_norm_non_negativity(x);
  test_norm_non_negativity(y);
  test_norm_equivalence(x);
  test_norm_equivalence(y);

  // distance properties
  test_distance_translation_invariant(x, y, a);
  test_distance_translation_invariant(y, x, a);
  test_distance_absolute_homogeneity(x, y, s);
  test_distance_absolute_homogeneity(y, x, s);
}

template <class T, std::enable_if_t<std::is_arithmetic_v<T>>* = nullptr>
void test(T lim) {
  tifa_libs::rand::Gen<std::conditional_t<std::is_integral_v<T>, std::uniform_int_distribution<T>, std::uniform_real_distribution<T>>> g(std::is_signed_v<T> ? -lim : 0, lim);
  single_test(point<T>(g(), g()), point<T>(g(), g()), point<T>(g(), g()), g());
}

int main() {
  tifa_libs::unittest::pre_test();

  test<i32>(1e4);
  test<i64>(1e4);
  test<f64>(1e4);
  test<f128>(1e4);

  test<i64>(1e5);
  test<f64>(1e5);
  test<f128>(1e5);

  test<i64>(1e9);
  test<f64>(1e9);
  test<f128>(1e9);

  tifa_libs::unittest::post_test();
}