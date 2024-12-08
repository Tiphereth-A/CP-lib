#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/rand/gen.hpp"

#include "../../../code/util/fp_func.hpp"
#include "../base.hpp"

template <class T>
void test() {
  using res_t = std::conditional_t<sizeof(T) <= 4, u32, u64>;
  res_t seed = (res_t)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
  tifa_libs::rand::Gen<T> g1;
  std::conditional_t<std::is_same_v<res_t, u32>, std::mt19937, std::mt19937_64> g2;
  g1.seed(seed);
  g2.seed(seed);
  const u32 N = 5'000'000;
  T a = std::numeric_limits<T>::min() / 3, b = std::numeric_limits<T>::max() / 3;
  g1.range(a, b);
  std::conditional_t<std::is_integral_v<T>, std::uniform_int_distribution<T>, std::uniform_real_distribution<T>> u(a, b);
  flt_ (u32, i, 0, N) {
    res_t x = g1.next(), y = g2();
    check(x, y, check_param(seed), check_param(i));
  }
  int cnt_eq = 0;
  flt_ (u32, i, 0, N) {
    T x2 = g1(), y2 = u(g2);
    cnt_eq += tifa_libs::is_eq(x2, y2);
    if (i < 64) std::cerr << x2 << ' ' << y2 << '\n';
  };
  check_bool(cnt_eq == N, check_param(cnt_eq));
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test<char>(); break;
    case tifa_libs::unittest::ts_example_01: test<i8>(); break;
    case tifa_libs::unittest::ts_random_00: test<u8>(); break;
    case tifa_libs::unittest::ts_random_01: test<i16>(); break;
    case tifa_libs::unittest::ts_random_02: test<u16>(); break;
    case tifa_libs::unittest::ts_random_03: test<i32>(); break;
    case tifa_libs::unittest::ts_random_04: test<u32>(); break;
    case tifa_libs::unittest::ts_random_05: test<i64>(); break;
    case tifa_libs::unittest::ts_random_06: test<u64>(); break;
    case tifa_libs::unittest::ts_random_07: test<f32>(); break;
    case tifa_libs::unittest::ts_random_08: test<f64>(); break;
    case tifa_libs::unittest::ts_random_09: test<f128>(); break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}