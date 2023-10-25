#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/conv/karatsuba.hpp"

#include "../../../code/math/mint_d31.hpp"
#include "../../../code/math/mint_d63.hpp"
#include "../../../code/math/mint_ds.hpp"
#include "../../../code/math/mint_s30.hpp"
#include "../../../code/math/mint_s63.hpp"
#include "../../../code/math/mint_ss.hpp"
#include "../../../code/math/nimber.hpp"
#include "../../../code/rand/gen.hpp"
#include "../base.hpp"

tifa_libs::rand::Gen<std::uniform_int_distribution<u64>> g;

template <class T>
void test_karatsuba(u64 n) {
  vec<T> a(n), b(n);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
  for (auto& i : a) i = T(g());
  for (auto& i : b) i = T(g());
#pragma GCC diagnostic pop
  vec<T> c = tifa_libs::math::conv_naive(a, b), d = tifa_libs::math::karatsuba(a, b);
  check(d, c);
}

int main() {
  tifa_libs::unittest::pre_test();

  tifa_libs::math::mint_d31<-1>::set_mod(1000000000 + 7);
  tifa_libs::math::mint_d63<-1>::set_mod(1000000000 + 7);
  tifa_libs::math::mint_ds<-1>::set_mod(1000000000 + 7);

  test_karatsuba<tifa_libs::math::mint_s30<998244353>>(100);
  test_karatsuba<tifa_libs::math::mint_s63<998244353>>(100);
  test_karatsuba<tifa_libs::math::mint_ss<998244353>>(100);
  test_karatsuba<tifa_libs::math::mint_d31<-1>>(100);
  test_karatsuba<tifa_libs::math::mint_d63<-1>>(100);
  test_karatsuba<tifa_libs::math::mint_ds<-1>>(100);
  test_karatsuba<u32>(100);
  test_karatsuba<u64>(100);
  test_karatsuba<tifa_libs::math::nimber16>(100);
  test_karatsuba<tifa_libs::math::nimber32>(100);
  test_karatsuba<tifa_libs::math::nimber64>(100);

  tifa_libs::unittest::post_test();
}