// competitive-verifier: STANDALONE

#include "../../../src/util/func_fp/lib.hpp"
#include "../../../src/util/rand/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
template <class T>
void test() {
  using res_t = std::conditional_t<sizeof(T) <= 4, u32, u64>;
  res_t seed = (res_t)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
  rand_gen<T> g1;
  std::conditional_t<std::is_same_v<res_t, u32>, std::mt19937, std::mt19937_64> g2;
  g1.seed(seed);
  g2.seed(seed);
  const u32 N = 5'000'000;
  T a = std::numeric_limits<T>::min() / 3, b = std::numeric_limits<T>::max() / 3;
  g1.range(a, b);
  std::conditional_t<std::is_integral_v<T>, std::uniform_int_distribution<T>, std::uniform_real_distribution<T>> u(a, b);
  flt_ (u32, i, 0, N) {
#pragma GCC diagnostic ignored "-Wconversion"
    res_t x = g1.next(), y = g2();
#pragma GCC diagnostic warning "-Wconversion"
    check(x, y, check_param(seed), check_param(i));
  }
  int cnt_eq = 0;
  flt_ (u32, i, 0, N) {
    T x2 = g1(), y2 = u(g2);
    cnt_eq += is_eq(x2, y2);
    if (i < 64) std::cerr << x2 << ' ' << y2 << '\n';
  };
  check_bool(cnt_eq == N, check_param(cnt_eq));
}

int main() {
  timer_(test<char>());
  timer_(test<i8>());
  timer_(test<u8>());
  timer_(test<i16>());
  timer_(test<u16>());
  timer_(test<i32>());
  timer_(test<u32>());
  timer_(test<i64>());
  timer_(test<u64>());
  timer_(test<f32>());
  timer_(test<f64>());
  timer_(test<f128>());
}