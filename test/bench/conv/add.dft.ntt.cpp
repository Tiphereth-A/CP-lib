#include <benchmark/benchmark.h>

#include "../../../src/conv/add/dft/lib.hpp"
#include "../../../src/conv/trans/ntt/lib.hpp"
#include "../../../src/math/ds/mint/bs/lib.hpp"
#include "../../../src/math/ds/mint/ms/lib.hpp"
#include "../../../src/math/ds/mint/ms64/lib.hpp"

using namespace tifa_libs;

CEXP u32 MOD = 998244353;

using bs = mint_bs<MOD>;
using ms = mint_ms<MOD>;
using ms64 = mint_ms64<MOD>;

#define _TEST(type)                                                          \
  void CONV_same_length_##type(benchmark::State& state) {                    \
    ntt<type> core;                                                          \
    vec<type> a((usz)state.range(0)), b((usz)state.range(0));                \
    for (usz i = 0; i < (usz)state.range(0); i++) {                          \
      a[i] = i + 1234;                                                       \
      b[i] = i + 5678;                                                       \
    }                                                                        \
    for (auto _ : state) {                                                   \
      benchmark::DoNotOptimize(conv_dft(core, a, b));                        \
    }                                                                        \
  }                                                                          \
  BENCHMARK(CONV_same_length_##type)->RangeMultiplier(2)->Range(1, 1 << 20); \
  BENCHMARK(CONV_same_length_##type)->DenseRange(1, 100, 1);                 \
                                                                             \
  void CONV_long_empty_##type(benchmark::State& state) {                     \
    ntt<type> core;                                                          \
    vec<type> a((usz)state.range(0)), b;                                     \
    for (usz i = 0; i < (usz)state.range(0); i++) {                          \
      a[i] = i + 1234;                                                       \
    }                                                                        \
    for (auto _ : state) {                                                   \
      benchmark::DoNotOptimize(conv_dft(core, a, b));                        \
      benchmark::DoNotOptimize(conv_dft(core, b, a));                        \
    }                                                                        \
  }                                                                          \
  BENCHMARK(CONV_long_empty_##type)->RangeMultiplier(2)->Range(1, 1 << 20)

_TEST(bs);
_TEST(ms);
_TEST(ms64);

BENCHMARK_MAIN();
