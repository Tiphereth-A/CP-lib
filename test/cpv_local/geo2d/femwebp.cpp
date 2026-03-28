// competitive-verifier: STANDALONE

#include "../../../src/geo2d/femwebp/lib.hpp"
#include "../../../src/util/rand/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;

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
  rand_gen<T> g(std::is_signed_v<T> ? -lim : 0, lim);

  vec<point<T>> v;
  while (v.size() < n) v.emplace_back(g(), g());
}

int main() {
  timer_(test<f64>(1e5, 3));
  timer_(test<f128>(1e5, 3));
  timer_(test<f64>(1e9, 3));
  timer_(test<f128>(1e9, 3));
  timer_(test<f64>(1e5, 10));
  timer_(test<f128>(1e5, 10));
  timer_(test<f64>(1e9, 10));
  timer_(test<f128>(1e9, 10));
  timer_(test<f64>(1e5, 50));
  timer_(test<f128>(1e5, 50));
  timer_(test<f64>(1e9, 50));
  timer_(test<f128>(1e9, 50));
}