// modified from <https://github.com/atcoder/ac-library/blob/master/test/benchmark/convolution.cpp>
#include <benchmark/benchmark.h>

#include "../../../src/conv/add/mtt/lib.hpp"
#include "../../../src/conv/trans/fft_r2/lib.hpp"
#include "../../../src/math/ds/mint/bd/lib.hpp"
#include "../../../src/math/ds/mint/bs/lib.hpp"
#include "../../../src/math/ds/mint/md/lib.hpp"
#include "../../../src/math/ds/mint/md64/lib.hpp"
#include "../../../src/math/ds/mint/ms/lib.hpp"
#include "../../../src/math/ds/mint/ms64/lib.hpp"

using namespace tifa_libs;

CEXP u32 MOD = 1'000'000'007;

using bs = mint_bs<MOD>;
using bd = mint_bd<0>;
using ms = mint_ms<MOD>;
using md = mint_md<0>;
using ms64 = mint_ms64<MOD>;
using md64 = mint_md64<0>;

static auto __STATIC = []() {
  bd::set_mod(MOD);
  md::set_mod(MOD);
  md64::set_mod(MOD);
  return 0;
}();

#define _TEST(type, core_data)                                                             \
  void CONV_same_length_##type##_##core_data(benchmark::State& state) {                    \
    fft_r2<core_data> core;                                                                \
    vec<type> a((usz)state.range(0)), b((usz)state.range(0));                              \
    for (usz i = 0; i < (usz)state.range(0); i++) {                                        \
      a[i] = i + 1234;                                                                     \
      b[i] = i + 5678;                                                                     \
    }                                                                                      \
    for (auto _ : state) {                                                                 \
      benchmark::DoNotOptimize(conv_mtt(core, a, b));                                      \
    }                                                                                      \
  }                                                                                        \
  BENCHMARK(CONV_same_length_##type##_##core_data)->RangeMultiplier(2)->Range(1, 1 << 20); \
  BENCHMARK(CONV_same_length_##type##_##core_data)->DenseRange(1, 100, 1);                 \
                                                                                           \
  void CONV_long_empty_##type##_##core_data(benchmark::State& state) {                     \
    fft_r2<core_data> core;                                                                \
    vec<type> a((usz)state.range(0)), b;                                                   \
    for (usz i = 0; i < (usz)state.range(0); i++) {                                        \
      a[i] = i + 1234;                                                                     \
    }                                                                                      \
    for (auto _ : state) {                                                                 \
      benchmark::DoNotOptimize(conv_mtt(core, a, b));                                      \
      benchmark::DoNotOptimize(conv_mtt(core, b, a));                                      \
    }                                                                                      \
  }                                                                                        \
  BENCHMARK(CONV_long_empty_##type##_##core_data)->RangeMultiplier(2)->Range(1, 1 << 20)
